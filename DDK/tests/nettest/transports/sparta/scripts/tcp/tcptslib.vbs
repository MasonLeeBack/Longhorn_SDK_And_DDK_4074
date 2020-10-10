'
' Function to establish a connection
'
Function PassiveConnect(fTSSet, fTSPresentInSyn, fTSPresentInSynAck, ulTSValue, ulTSEcho, usSrcPort, usDestPort, ByRef ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulStatus, ulTID, pTCPPacket, ulBytesRcvd, ulCOunter
   
   '
   ' Create the SYN packet
   '   
   Set pSYNPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_SYN, 0)
   pSYNPacket.TCPHeader.TCPOption(0).AddMSS(usMSS)
   if (fTSPresentInSyn) then
      pSYNPacket.TCPHeader.TCPOption(1).AddTS ulTSValue, ulTSEcho
   end if
      
   '
   ' Ask Autosrv to issue an accept, send a SYN and grab the SYN-ACK
   '
   Set pTCPPacket = GrabSynAck(pSYNPacket, usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (pTCPPacket is Nothing) then
      Core.BlockVariation "PassiveConnect: Failed to receive a SYN-ACK"
      PassiveConnect = 1
      exit function   
   end if 
   
   '
   ' Verify that the TS option is present in SYN-ACK only if it was included in the SYN
   '
   if (Not(VerifyTSOption(pTCPPacket, fTSPresentInSyn AND fTSSet))) then   
      Core.log "PassiveConnect: TS option in SYN-ACK not dictated by SYN"
      PassiveConnect = 1
      exit Function
   end if 

   '
   ' Send the ACK
   '
   Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   IFace.Send(pTCPPacket)
   Core.Sleep 500

   '
   ' Check if connection is offloaded
   '
   If Not IsConnectionOffloaded(usSrcPort, usDestPort, ulSessionId) and g_fTestOffload And g_fTOENic Then
      Core.Log "PassiveConnect : Failed to offload the connection"
      PassiveConnect = 3
      Exit function
   End If
      
   PassiveConnect = 0
End Function



 
'
' Function to make the stack do an active connect
'
Function ActiveConnect(fTSSet, fTSPresentInSyn, fTSPresentInSynAck, ulTSValue, ulTSEcho, usSrcPort, usDestPort, ByRef ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulStatus, ulTID, pTCPPacket, ulBytesRcvd
   
   '
   ' Ask Autosrv to issue a connect and grab the SYN
   '
   Set pTCPPacket = GrabSyn(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId, fConnectEx, 100)
   if (pTCPPacket is Nothing) then
      Core.log "ActiveConnect: Failed to receive a SYN"
      ActiveConnect = 1
      exit Function
   end if
 
   '
   ' Verify the SYN contains/not the SACK permit option
   '  
   if (Not(VerifyTSOption(pTCPPacket, fTSPresentInSyn))) then   
      Core.log "ActiveConnect: TS option in SYN not as expected"
      ActiveConnect = 1
      exit Function
   end if

   '
   ' Send the SYN-ACK
   '
   Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, (TCP_SYN or TCP_ACK), 0)
   pTCPPacket.TCPHeader.TCPOption(0).AddMSS(usMSS)
   if (fTSPresentInSynAck) then
      pTCPPacket.TCPHeader.TCPOption(1).AddTS ulTSValue, ulTSEcho
   end if
   IFace.Send(pTCPPacket)
   
  
   '
   ' Grab the ACK
   '
   Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_ACK, 1000)
   if (pTCPPacket is Nothing) then
      Core.log "ActiveConnect: Didn't receive an ACK"
      ActiveConnect = 1
      exit Function
   end if
   
   '
   ' Ensure that the ACK contains the TS option only if enabled during negotiation
   '
   Dim ulIndex, fTSEnabled
   fTSEnabled = fTSPresentInSynAck AND fTSSet
   ulIndex = GetTSOptionIndex(pTCPPacket)
   if ((IsNull(ulIndex) AND fTSEnabled) OR (Not(IsNull(ulIndex)) AND not(fTSEnabled))) then
      Core.log "ActiveConnect: TS option in ACK not as expected"
      ActiveConnect = 1
      exit Function
   end if

   '
   ' Ensure that is TS is present, the echo field is set correctly
   '   
   if Not(IsNull(ulIndex)) then
      if (pTCPPacket.TCPHeader.TCPOption(ulIndex).TsEcho <> ulTSValue) then
         Core.log "ActiveConnect: Incorrect TS echo field in ACK " & pTCPPacket.TCPHeader.TCPOption(ulIndex).TsEcho
         ActiveConnect = 1
         exit Function
      end if
   end if

   '
   ' Check if connection is offloaded
   '
   If Not IsConnectionOffloaded(usSrcPort, usDestPort, ulSessionId) and g_fTestOffload And g_fTOENic Then
      Core.Log "ActiveConnect : Failed to offload the connection"
      ActiveConnect = 3
      Exit function
   End If
   
   ActiveConnect = 0
End Function

'
' A function to validate the TS option in a TCP packet
'
Function ValidateTSOption(pTCPPacket, fTSExpected, ByRef ulLastTSValue, ulExpectedTSEcho)
   Dim ulIndex
   
   '
   ' Check the optione is present only if expected
   '
   ulIndex = GetTSOptionIndex(pTCPPacket)
   if (Not(fTSExpected)) then
      if (Not(IsNull(ulIndex))) then
         Core.Log "ValidateTSOption: TS option present in the packet"
         ValidateTSOption = 1
         exit function
      end if
      
      ValidateTSOption = 0
      exit function
   end if
   if (IsNull(ulIndex)) then
      Core.Log "ValidateTSOption: TS option not present in the packet"
      ValidateTSOption = 1
      exit function
   end if
   
   '
   ' Check that the TS value is not less than the last TS value
   '
   if (pTCPPacket.TCPHeader.TCPOption(ulIndex).TsValue < ulLastTSValue) then
      Core.Log "ValidateTSOption: TS value is smaller " & pTCPPacket.TCPHeader.TCPOption(ulIndex).TsValue & " < " & ulLastTSValue
      ValidateTSOption = 1
      exit function
   end if
   
   '
   ' Check that the TS echo field is set correctly
   '
   if (pTCPPacket.TCPHeader.TCPOption(ulIndex).TsEcho <> ulExpectedTSEcho) then
      Core.Log "ValidateTSOption: TS echo is incorrect " & pTCPPacket.TCPHeader.TCPOption(ulIndex).TsEcho & " <> " & ulExpectedTSEcho
      ValidateTSOption = 1
      exit function
   end if
   
   ulLastTSValue = pTCPPacket.TCPHeader.TCPOption(ulIndex).TsValue
   ValidateTSOption = 0
 
End Function

'
' Function to establish a connection
'
Function PassiveConnectWithoutTS(usSrcPort, usDestPort, ByRef ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulStatus, ulTID, pTCPPacket, ulBytesRcvd, pSYNPacket
   
   '
   ' Create the SYN packet
   '   
   Set pSYNPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_SYN, 0)
   pSYNPacket.TCPHeader.TCPOption(0).AddMSS(usMSS)
      
   '
   ' Ask Autosrv to issue an accept, send a SYN and grab the SYN-ACK
   '
   Set pTCPPacket = GrabSynAck(pSYNPacket, usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (pTCPPacket is Nothing) then
      Core.BlockVariation "PassiveConnect: Failed to receive a SYN-ACK"
      PassiveConnect = 1
      exit function   
   end if 
   
   '
   ' Verify that the TS option is not present in SYN-ACK 
   '
   if (Not(VerifyTSOption(pTCPPacket, FALSE))) then   
      Core.log "PassiveConnectWithoutTS: TS option present in SYN-ACK"
      PassiveConnectWithoutTS = 1
      exit Function
   end if 

   '
   ' Send the ACK
   '
   Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   IFace.Send(pTCPPacket)
   Core.Sleep 500
         
   '
   ' Check if connection is offloaded
   '
   If Not IsConnectionOffloaded(usSrcPort, usDestPort, ulSessionId) and g_fTestOffload And g_fTOENic Then
      Core.Log "PassiveConnectWithoutTS : Failed to offload the connection"
      PassiveConnectWithoutTS = 3
      Exit function
   End If

   PassiveConnectWithoutTS = 0
End Function

'
' Function to make the stack do an active connect
'
Function ActiveConnectWithTS(ByRef ulTSValue, ByRef ulTSEcho, usSrcPort, usDestPort, ByRef ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulStatus, ulTID, pTCPPacket, ulBytesRcvd
   
   '
   ' Ask Autosrv to issue a connect and grab the SYN
   '
   Set pTCPPacket = GrabSyn(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId, fConnectEx, 100)
   if (pTCPPacket is Nothing) then
      Core.log "ActiveConnectWithTS: Failed to receive a SYN"
      ActiveConnectWithTS = 1
      exit Function
   end if
 
   '
   ' Verify the SYN contains the TS option
   '  
   if (Not(VerifyTSOption(pTCPPacket, false))) then   
      Core.log "ActiveConnectWithTS: TS option not present in SYN"
      ActiveConnectWithTS = 1
      exit Function
   end if

   '
   ' Send the SYN-ACK with the TS option
   '
   Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, (TCP_SYN or TCP_ACK), 0)
   pTCPPacket.TCPHeader.TCPOption(0).AddMSS(usMSS)
   pTCPPacket.TCPHeader.TCPOption(1).AddTS ulTSValue, ulTSEcho
   IFace.Send(pTCPPacket)
   
  
   '
   ' Grab the ACK
   '
   Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_ACK, 1000)
   if (pTCPPacket is Nothing) then
      Core.log "ActiveConnectWithTS: Didn't receive an ACK"
      ActiveConnectWithTS = 1
      exit Function
   end if
   
   '
   ' Ensure that the ACK contains the TS option 
   '
   Dim ulIndex
   ulIndex = GetTSOptionIndex(pTCPPacket)
   if (IsNull(ulIndex)) then
      Core.log "ActiveConnectWithTS: TS option not present in ACK"
      ActiveConnectWithTS = 1
      exit Function
   end if

   '
   ' Ensure that is TS is present, the echo field is set correctly
   '   
   if (pTCPPacket.TCPHeader.TCPOption(ulIndex).TsEcho <> ulTSValue) then
      Core.log "ActiveConnectWithTS: Incorrect TS echo field in ACK " & pTCPPacket.TCPHeader.TCPOption(ulIndex).TsEcho
      ActiveConnectWithTS = 1
      exit Function
   end if

   ulTSEcho = pTCPPacket.TCPHeader.TCPOption(ulIndex).TsValue

   '
   ' Check if connection is offloaded
   '
   If Not IsConnectionOffloaded(usSrcPort, usDestPort, ulSessionId) and g_fTestOffload And g_fTOENic Then
      Core.Log "ActiveConnectWithTS : Failed to offload the connection"
      ActiveConnectWithTS = 3
      Exit function
   End If

   ActiveConnectWithTS = 0
End Function



'
' Function to verify the TS option is present/not
'
Function VerifyTSOption(pTCPPacket, fPresent)   
  Dim ulCounter, usKind
   
  For ulCounter = 0 to 39
     usKind = pTCPPacket.TCPHeader.TCPOption(ulCounter).Kind
     if (usKind = TCP_OPTION_TS) then
        if (fPresent) then
           VerifyTSOption = TRUE
        else 
           VerifyTSOption = FALSE
        end if
        Exit Function
     end if
  Next             
   
  VerifyTSOption = Not(fPresent)
End Function


'
' Function to obtain the index of the TS option in the TCP packet. Return NULL if none.
'
Function GetTSOptionIndex(pTCPPacket)
  Dim ulCounter, usKind
   
  For ulCounter = 0 to 39
     usKind = pTCPPacket.TCPHeader.TCPOption(ulCounter).Kind
     if (usKind = TCP_OPTION_TS) then
        GetTSOptionIndex = ulCounter
        Exit Function
     end if
  Next             
   
  GetTSOptionIndex = NULL
End Function



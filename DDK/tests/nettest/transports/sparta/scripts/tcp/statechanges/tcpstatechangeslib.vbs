'
' Function to get a connection in LISTEN state
'     CLOSED -> LISTEN
'
Function CLOSED__LISTEN(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   Dim ulStatus, fStatus, ulTID, pTCPPacket, ulAsyncStatus, ulCounter
      
   For ulCounter = 1 to MAX_PORT_RETRIES    
      '
      ' Retry with a different port
      '
      usDestPort = Core.Random(10000, 20000)
      Core.log "CLOSED__LISTEN: Trying a random port - " & usDestPort
      
      '
      ' Issue a CreateAndAccept
      '
      ulStatus = pControllerObj.CreateAndAccept(SOCK_STREAM, g_szRemoteIpAddress, usDestPort, 5, ulTID, ulSessionId)
      if (ulStatus = 0) then
         exit for
      end if
   Next
   if (ulStatus <> 0) then
       Core.Log "CLOSED__LISTEN: CreateAndAccept - " & ulStatus
       CLOSED__LISTEN = ulStatus
       exit Function
   end if
   
   CLOSED__LISTEN = 0
End Function

'
' Function to get a connection in SYN_SENT state
'     CLOSED -> SYN_SENT
'
Function CLOSED__SYN_SENT(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   Dim pTCPPacket
   
   '
   ' Ask Autosrv to issue a connect/connectex and grab the first SYN
   '
   Set pTCPPacket = GrabSyn(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId, FALSE, NULL)
   if (pTCPPacket is Nothing) then
      Core.log "CLOSED__SYN_SENT: Failed to receive a SYN"
      CLOSED__SYN_SENT = 1
      exit Function
   end if 
           
   CLOSED__SYN_SENT = 0

End Function

'
' Function to get a connection in SYN_RCVD state 
'     CLOSED -> SYN_SENT -> SYN_RCVD     
'
Function CLOSED__SYN_SENT__SYN_RCVD(usSrcPort, usDestPort, ByRef ulSeqNumber, ByRef ulAckNumber, ByRef ulSessionId)
   Dim ulStatus, fStatus
   
   '
   ' Get the connection in SYN_SENT state
   '                                        
   ulStatus = CLOSED__SYN_SENT(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (ulStatus <> 0) then
      Core.Log "CLOSED__SYN_SENT__SYN_RCVD: CLOSED__SYN_SENT - " & ulStatus
      CLOSED__SYN_SENT__SYN_RCVD = ulStatus
      exit Function
   end if
   
   '
   ' Send a SYN and grab the SYN-ACK
   '
   fStatus = SendPacketAndCheckNoResponseEx(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_SYN, (TCP_SYN or TCP_ACK), 500)
   if (fStatus = TRUE) then
      Core.Log "CLOSED__SYN_SENT__SYN_RCVD: No SYN-ACK received on SYN"
      CLOSED__SYN_SENT__SYN_RCVD = 1
      exit Function
   end if 
   
   CLOSED__SYN_SENT__SYN_RCVD = 0
End Function


'
' Function to get a connection in SYN_RCVD state 
'     CLOSED -> LISTEN -> SYN_RCVD     
'
Function CLOSED__LISTEN__SYN_RCVD(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   Dim pTCPPacket, pSYNPacket

   '
   ' Create a SYN packet
   ' 
   Set pSYNPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_SYN, 0)

   
   '
   ' Send the SYN and grab the SYN-ACK
   '                                        
   Set pTCPPacket = GrabSynAck(pSYNPacket, usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (pTCPPacket is Nothing) then
      Core.log "CLOSED__LISTEN__SYN_RCVD: Failed to receive a SYN-ACK"
      CLOSED__LISTEN__SYN_RCVD = 1
      exit Function
   end if 
   
   CLOSED__LISTEN__SYN_RCVD = 0
End Function

'
' Function to get a connection in FIN_WAIT1 state 
'     ESTD -> FIN_WAIT1
'
Function ESTD__FIN_WAIT1(usSrcPort, usDestPort, ByRef ulSeqNumber, ByRef ulAckNumber, ByRef ulSessionId)
   Dim ulStatus, fStatus, ulNumRetries, ulBytesRcvd, ulTID
   
   '
   ' Ask AutoSrv to issue a shutdown
   '
   ulStatus = pControllerObj.Shutdown(ulSessionId, ulTID)
   if (ulStatus <> 0) then
       Core.Log "ESTD__FIN_WAIT1: AsyncShutdown - " & ulStatus
       ESTD__FIN_WAIT1 = ulStatus
       exit Function
   end if
   
   '
   ' Grab the FIN
   '
   Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, usBytesRcvd, TCP_FIN, 20000)
   If (pTCPPacket is Nothing) Then
       Core.Log "ESTD__FIN_WAIT1: No FIN received"
       ESTD__FIN_WAIT1 = 1
       exit Function
   End if
   
   ESTD__FIN_WAIT1 = 0
End Function

'
' Function to get a connection in FIN_WAIT1 state
'     LISTEN -> SYN_RCVD -> ESTD -> FIN_WAIT1
'
Function LISTEN__SYN_RCVD__ESTD__FIN_WAIT1(usSrcPort, usDestPort, ByRef ulSeqNumber, ByRef ulAckNumber, ByRef ulSessionId)
   Dim ulStatus, fStatus, ulNumRetries
   
   '
   ' Get a connection in SYN_RCVD state
   '
   ulStatus = CLOSED__LISTEN__SYN_RCVD(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (ulStatus <> 0) then
       Core.Log "LISTEN__SYN_RCVD__ESTD__FIN_WAIT1: CLOSED__LISTEN__SYN_RCVD - " & ulStatus
       LISTEN__SYN_RCVD__ESTD__FIN_WAIT1 = ulStatus
       exit Function
   end if
   
   '
   ' Send an ACK and get the connection in ESTD state
   '   
   Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   IFace.Send(pTCPPacket)
   
   '
   ' Transition the connection from ESTD to FIN_WAIT1 state
   '
   ulStatus = ESTD__FIN_WAIT1(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (ulStatus <> 0) then
       Core.Log "LISTEN__SYN_RCVD__ESTD__FIN_WAIT1: ESTD__FIN_WAIT1 - " & ulStatus
       LISTEN__SYN_RCVD__ESTD__FIN_WAIT1 = ulStatus
       exit Function
   end if
   
   LISTEN__SYN_RCVD__ESTD__FIN_WAIT1 = 0
End Function

  
'
' Function to get a connection in FIN_WAIT2 state
'     LISTEN -> SYN_RCVD -> ESTD -> FIN_WAIT1 -> FIN_WAIT2
'
Function LISTEN__SYN_RCVD__ESTD__FIN_WAIT2(usSrcPort, usDestPort, ByRef ulSeqNumber, ByRef ulAckNumber, ByRef ulSessionId)
   Dim ulStatus, fStatus, ulNumRetries
   
   '
   ' Get a connection in FIN_WAIT1 state
   '
   ulStatus = LISTEN__SYN_RCVD__ESTD__FIN_WAIT1(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (ulStatus <> 0) then
       Core.Log "LISTEN__SYN_RCVD__ESTD__FIN_WAIT2: LISTEN__SYN_RCVD__ESTD__FIN_WAIT1 - " & ulStatus
       LISTEN__SYN_RCVD__ESTD__FIN_WAIT2 = ulStatus
       exit Function
   end if
   
   '
   ' Send an ACK and get the connection in FIN_WAIT2 state
   '   
   Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   IFace.Send(pTCPPacket)
      
   LISTEN__SYN_RCVD__ESTD__FIN_WAIT2 = 0
End Function


'
' Function to get a connection in CLOSING state
'     LISTEN -> SYN_RCVD -> ESTD -> FIN_WAIT1 -> CLOSING
'
Function LISTEN__SYN_RCVD__ESTD__FIN_WAIT1__CLOSING(usSrcPort, usDestPort, ByRef ulSeqNumber, ByRef ulAckNumber, ByRef ulSessionId)
   Dim ulStatus, fStatus
   
   '
   ' Get a connection in FIN_WAIT1 state
   '
   ulStatus = LISTEN__SYN_RCVD__ESTD__FIN_WAIT1(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (ulStatus <> 0) then
       Core.Log "LISTEN__SYN_RCVD__ESTD__FIN_WAIT1__CLOSING: LISTEN__SYN_RCVD__ESTD__FIN_WAIT1 - " & ulStatus
       LISTEN__SYN_RCVD__ESTD__FIN_WAIT1__CLOSING = ulStatus
       exit Function
   end if
   
   '
   ' Send a FIN with the last ACK, receive an ACK and get the connection in CLOSING state
   '   
   ulAckNumber = ulAckNumber - 1
   fStatus = SendPacketAndCheckNoResponseEx(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, (TCP_FIN or TCP_ACK), TCP_ACK, 500)
   if (fStatus = TRUE) then
      Core.Log "LISTEN__SYN_RCVD__ESTD__FIN_WAIT1__CLOSING: No ACK received on FIN-ACK"
      LISTEN__SYN_RCVD__ESTD__FIN_WAIT1__CLOSING = 1
      exit Function
   end if 
      
   LISTEN__SYN_RCVD__ESTD__FIN_WAIT1__CLOSING = 0
End Function

'
' Function to get a connection in CLOSE_WAIT state
'     LISTEN -> SYN_RCVD -> ESTD -> CLOSE_WAIT
' 
Function LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT(usSrcPort, usDestPort, ByRef ulSeqNumber, ByRef ulAckNumber, ByRef ulSessionId)
   Dim ulStatus, fStatus
   
   '
   ' Get a connection in SYN_SENT state
   '
   ulStatus = CLOSED__SYN_SENT(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (ulStatus <> 0) then
       Core.Log "LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT: CLOSED__SYN_SENT - " & ulStatus
       LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT = ulStatus
       exit Function
   end if
   
   '
   ' Send a SYN-ACK, receive ACK and get the connection in ESTD state
   '
   fStatus = SendPacketAndCheckNoResponseEx(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, (TCP_SYN or TCP_ACK), TCP_ACK, 500)
   if (fStatus = TRUE) then
      Core.Log "LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT: No ACK received on SYN-ACK"
      LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT = 1
      exit Function
   end if 
   
   
   '
   ' Send a FIN, receive an ACK and get the connection in CLOSE_WAIT state
   '   
   fStatus = SendPacketAndCheckNoResponseEx(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, (TCP_FIN or TCP_ACK), TCP_ACK, 500)
   if (fStatus = TRUE) then
      Core.Log "LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT: No ACK received on FIN-ACK"
      LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT = 1
      exit Function
   end if 
      
   LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT = 0
End Function


'
' Function to do the following transition
'     LISTEN (recv SYN, send SYN-ACK) --> SYN_RCVD (recv ACK) --> ESTD
'                           
Function LISTEN__ESTD(usSrcPort, usDestPort, ByRef ulSeqNumber, ByRef ulAckNumber, ByRef ulSessionId)
   Dim ulStatus, fStatus, ulTID, pTCPPacket, ulAsyncStatus
   
   '
   ' Get a connection in SYN_RCVD state
   '   
   ulStatus = CLOSED__LISTEN__SYN_RCVD(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (ulStatus <> 0) then
      Core.Log "LISTEN__ESTD: CLOSED__LISTEN__SYN_RCVD - " & ulStatus
      LISTEN__ESTD = ulStatus
      exit Function
   end if
         
   '
   ' Send an ACK
   '   
   Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   IFace.Send(pTCPPacket)      

   '
   ' Check if connection is offloaded
   '
   If Not IsConnectionOffloaded(usSrcPort, usDestPort, ulSessionId) and g_fTestOffload And g_fTOENic Then
      Core.Log "LISTEN__ESTD : Failed to offload the connection"
      LISTEN__ESTD = 3
      Exit Function
   End If
           
   LISTEN__ESTD = 0

End Function


'
' Function to do the following transition
'     CLOSED (recv SYN, send SYN-ACK) --> SYN_RCVD (recv ACK) --> ESTD
'                           
Function CLOSED__ESTD(usSrcPort, usDestPort, ByRef ulSeqNumber, ByRef ulAckNumber, ByRef ulSessionId)
   Dim ulStatus, fStatus, ulTID, pTCPPacket, ulAsyncStatus
   
   '
   ' Get a connection in SYN_SENT state
   '   
   ulStatus = CLOSED__SYN_SENT(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (ulStatus <> 0) then
      Core.Log "CLOSED__ESTD: CLOSED__SYN_SENT - " & ulStatus
      CLOSED__ESTD = ulStatus
      exit Function
   end if
         
   '
   ' Send a SYN-ACK and grab the ACK
   '
   fStatus = SendPacketAndCheckNoResponseEx(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, (TCP_SYN or TCP_ACK), TCP_ACK, 500)
   if (fStatus = TRUE) then
      Core.Log "CLOSED__ESTD: No ACK received on SYN-ACK"
      CLOSED__ESTD = 1
      exit Function
   end if 
         
   '
   ' Check if connection is offloaded
   '
   If Not IsConnectionOffloaded(usSrcPort, usDestPort, ulSessionId) and g_fTestOffload And g_fTOENic Then
      Core.Log "CLOSED__ESTD : Failed to offload the connection"
      CLOSED__ESTD = 3
      Exit Function
   End If
           
   CLOSED__ESTD = 0

End Function

'
' Function to get a connection in LAST_ACK state
'     LISTEN -> SYN_RCVD -> ESTD -> CLOSE_WAIT -> LAST_ACK
' 
Function LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT__LAST_ACK(usSrcPort, usDestPort, ByRef ulSeqNumber, ByRef ulAckNumber, ByRef ulSessionId)
   Dim ulStatus, fStatus, ulNumRetries, pTCPPacket, ulTID, ulBytesRcvd
   
   '
   ' Get a connection in CLOSE_WAIT state
   '
   ulStatus = LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   if (ulStatus <> 0) then
       Core.Log "LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT__LAST_ACK: LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT - " & ulStatus
       LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT__LAST_ACK = ulStatus
       exit Function
   end if
   
   '
   ' Ask AutoSrv to shutdown the session
   '   
   ulStatus = pControllerObj.Shutdown(ulSessionId, ulTID)
   if (ulStatus <> 0) then
       Core.Log "LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT__LAST_ACK: AsyncShutdown - " & ulStatus
       LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT__LAST_ACK = ulStatus
       exit Function
   end if
   
   '
   ' Grab the FIN-ACK, retry 3 times
   '   
   For ulNumRetries = 1 to 3
      Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, (TCP_FIN or TCP_ACK), 1000)
      If Not (pTCPPacket is Nothing) Then      
         exit For
      end if
   Next   
   if (pTCPPacket is Nothing) then
       Core.Log "LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT__LAST_ACK: No FIN-ACK received" 
       LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT__LAST_ACK = ulStatus
       exit Function
   end if
         
   LISTEN__SYN_RCVD__ESTD__CLOSE_WAIT__LAST_ACK = 0
End Function



'
' A routine to get a connection in TIME_WAIT state
'       
Function GetConnectionInTimeWaitState(usSrcPort, usDestPort, ByRef ulSeqNumber, ByRef ulAckNumber, ByRef ulSessionId, ulNumDataTransfers)
   Dim pTCPPacket, ulTID, ulStatus, ulDummy, ulBufSize, ulAsyncStatus, fStatus, ulBytesRcvd
    
   ulBufSize = 100
    
   '
   ' Ask Autosrv to establish a connection
   '   
   ulStatus = Connect(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId, NULL, 1460)
   if (fStatus = TRUE) then
      Core.Log "GetConnectionInTimeWaitState: Connect - " & ulStatus
      GetConnectionInTimeWaitState = FALSE
      exit Function
   end if 
            
   '
   ' Ask AutoSrv to post a receive
   '
   ulStatus = pControllerObj.Receive(ulSessionId, 0, 0, ulBufSize, ulTID)
   if (ulStatus <> 0) then
       Core.Log "GetConnectionInTimeWaitState: Receive - " & ulStatus
       GetConnectionInTimeWaitState = FALSE
       exit Function
   end if
    
   '
   ' Do the data transfers
   '        
   Dim ulCounter
   For ulCounter = 1 to ulNumDataTransfers
       '
       ' Send data
       '
       Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, (TCP_ACK OR TCP_PUSH), ulBufSize)
       IFace.Send(pTCPPacket)
        
       '
       ' Receive ACK
       '        
       Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_ACK, 500)
       If (pTCPPacket is Nothing) Then    
          Core.Log "GetConnectionInTimeWaitState: Failed to receive a ACK" 
          GetConnectionInTimeWaitState = FALSE
          exit Function
       End if
   Next 

   '
   ' Ask AutoSrv to stop the receive
   '
   ulStatus = pControllerObj.Stop(ulSessionId, ulTID, ulAsyncStatus)
   if (ulStatus <> 0) then
       Core.Log "GetConnectionInTimeWaitState: Stop - " & ulStatus
       GetConnectionInTimeWaitState = FALSE
       exit Function
   end if
    
     
   '
   ' Ask AutoSrv to close the connection
   '
   ulStatus = pControllerObj.Shutdown(ulSessionId, ulTID)
   if (ulStatus <> 0) then
       Core.Log "GetConnectionInTimeWaitState: Shutdown - " & ulStatus
       GetConnectionInTimeWaitState = FALSE
       exit Function
   end if
    
   '
   ' Grab the Fin-Ack 
   '
   Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, (TCP_FIN OR TCP_ACK), 1000)
   If (pTCPPacket is Nothing) Then    
       Core.Log "GetConnectionInTimeWaitState: Failed to receive a FIN-ACK" 
       GetConnectionInTimeWaitState = FALSE
       exit Function
   End if
    
   '
   ' Send a Fin-Ack and grab the ACK
   '    
   fStatus = SendPacketAndCheckNoResponseEx(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, (TCP_FIN or TCP_ACK), TCP_ACK, 500)
   if (fStatus = TRUE) then
      Core.Log "GetConnectionInTimeWaitState: No ACK received on FIN-ACK"
      GetConnectionInTimeWaitState = FALSE
      exit Function
   end if 
    
   GetConnectionInTimeWaitState = TRUE
End Function
          
'
' A function to send a TCP packet and pass back the response
'            
Function SendPacketAndCheckNoResponseEx(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, bFlag, bResponseFlag, ulTimeout)
   Dim pTCPPacket, ulBytesRcvd
  
   '
   ' Send a TCP packet with appropriate flags
   ' 
   Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, bFlag, 0)
   IFace.Send(pTCPPacket)
       
   '
   ' Obtain the response
   '    
   Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, bResponseFlag, ulTimeout)
   If Not(pTCPPacket is Nothing) Then   
      '
      ' Verify the checksum
      ' 
      Dim fChecksum
      fChecksum = pTCPPacket.VerifyChecksum 
      if (fChecksum = FALSE) then
          Core.log "SendPacketAndCheckNoResponseEx: Incorrect xsum"
      end if
      SendPacketAndCheckNoResponseEx = FALSE 
      Exit Function
   End if   

   SendPacketAndCheckNoResponseEx = TRUE
         
End Function          


'
' Function to send data and ensure its received
'
Function CheckDataReceived(usSrcPort, usDestPort, ByRef ulSeqNumber, ByRef ulAckNumber, ByRef ulSessionId)    
   Dim ulStatus, pTCPPacket, ulTID, fStatus, ulBytesSent, ulBytesRcvd, ulAsyncTID
    
   '
   ' Send a data packet
   ' 
   Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, (TCP_ACK or TCP_PUSH), 10)
   IFace.Send(pTCPPacket)

   '
   ' Check that we get an ACK
   '    
   Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_ACK, 500)
   If (pTCPPacket is Nothing) Then
      Core.Log "CheckDataReceived: No ACK received for data"
      CheckDataReceived = 1
      exit Function
   End If   
   
   '
   ' Verify that the data has been received
   '
   ulStatus = pControllerObj.GetSessionStats(ulSessionId, ulBytesSent, ulBytesRcvd)
   if (ulStatus <> 0) then
       Core.Log "CheckDataReceived: GetSessionStats - " & ulStatus
       CheckDataReceived = ulStatus 
       Exit Function
   elseif (ulBytesRcvd <> 10) then 
       Core.Log "CheckDataReceived: Received " & ulBytesRcvd & " bytes" 
       CheckDataReceived = 1
       exit Function  
   end if
       
   CheckDataReceived = ulStatus
   
   
End Function


'
' Function to verify that the TIME_WAIT duration is as expected
' This is done thru continuously sending SYN(s) with an ISN < last seq number till we get a RST
'
Function VerifyTimeWaitDuration(ulExpectedDuration, usSrcPort, usDestPort, ulSeqNumber, ulAckNumber)
   Dim ulStartTime, ulEndTime, ulElapsedTime, fCondition, pTCPPacket, ulBytesRcvd

   ulStartTime = Timer                                         
   
   '
   ' Keep sending SYNs till we get a reset - which is when the TIME_WAIT state expires
   '
   fCondition = TRUE                    
   While (fCondition)
       '
       ' Send a SYN
       ' 
       Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_SYN, 0)
       IFace.Send(pTCPPacket)
       
       '
       ' Get a reset
       '    
       Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_RST, 200)
       If Not (pTCPPacket is Nothing) Then    
          fCondition = FALSE 
       End if      
   Wend
   
   ulEndTime = Timer
   ulElapsedTime = ulEndTime - ulStartTime
   
   if ((ulElapsedTime > ulExpectedDuration*1.10) OR (ulElapsedTime < ulExpectedDuration*0.90)) Then   
       Core.Log "VerifyTimeWaitDuration: TIME_WAIT duration = " & ulElapsedTime
       VerifyTimeWaitDuration = FALSE
       exit Function
   End if 
   
   VerifyTimeWaitDuration =  TRUE
End Function


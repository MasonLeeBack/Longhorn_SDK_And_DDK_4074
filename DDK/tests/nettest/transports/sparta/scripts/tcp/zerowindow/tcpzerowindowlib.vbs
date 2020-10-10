
'
' A function to do the exchange till the first window probe packet is rcvd
'
Function GetToWindowProbeState(usSrcPort, usDestPort, ByRef ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim pTCPPacket, ulDataLength
   
   'Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   'pTCPPacket.TCPHeader.WindowSize = 0
   'IFace.Send(pTCPPacket)
   
   '
   ' Skip the packets sent since the ACK advertizing a zero window 
   '
   do
      set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulDataLength, TCP_ACK, 5000)
      if (pTCPPacket is Nothing) then
         Core.log "GetToWindowProbeState: Didn't receive a packet"
         GetToWindowProbeState = 1
         exit function
      end if       
   loop while (ulDataLength <> 1)
   
   ulAckNumber = ulAckNumber - 1
   GetToWindowProbeState = 0
End Function

'
' Function to respond to zero window probes
'
Function DoZeroWindowProbe(ulNumProbes, usSrcPort, usDestPort, ByRef ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulTimeout, ulCounter, pTCPPacket, pACKPacket, ulDataLength, ulTime

   Set pACKPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)   
   pACKPacket.TCPHeader.WindowSize = 0
   
   '
   ' receive the zero window probe packets
   '
   ulTimeout = CLng(6000)
   ulDataLength = 1
   For ulCounter = 1 to ulNumProbes
      if (ulCounter > 1) then
         if (ulCounter < 7) then
            ulTimeout = ulTimeout * 2
         end if
         set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulDataLength, TCP_ACK, ulTimeout)
         if (pTCPPacket is Nothing) then
            Core.log "DoZeroWindowProbe: Didn't receive a packet"
            DoZeroWindowProbe = 1
            exit function
         end if        
         ulAckNumber = ulAckNumber - 1
      end if       

      if (ulDataLength <> 1) then
         Core.Log "DoZeroWindowProbe: Didn't receive the window probe packet"
         DoZeroWindowProbe = 1
         exit function
      end if   

      if (ulCounter = ulNumProbes) then
         pACKPacket.TCPHeader.WindowSize = DefaultTcpWindowSize
      end if
      pACKPacket.TCPHeader.AckNumber = ulAckNumber
      IFace.Send(pACKPacket)
   Next

   DoZeroWindowProbe = 0

End Function

'
' Function to do data exchange till all the data is received
'
Function DoDataExchange(ulSendDataSize, usSrcPort, usDestPort, ByRef ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulBytesRcvd, pTCPPacket, pACKPacket, ulDataLength
      
   Set pACKPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)   

   '
   ' Do normal data exchange till all the bytes are received
   '
   ulBytesRcvd = 0
   while (ulBytesRcvd <> ulSendDataSize)
      set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulDataLength, TCP_ACK, 200)
      if (pTCPPacket is Nothing) then
         Core.log "Expecting - " & ulSendDataSize & "  Recieved - " & ulBytesRcvd
         Core.log "DoDataExchange: Didn't receive a packet"
         DoDataExchange = 1
         exit function
      end if 
      
      ulBytesRcvd = ulBytesRcvd + ulDataLength
   
      pACKPacket.TCPHeader.AckNumber = ulAckNumber
      IFace.Send(pACKPacket)
   Wend 
   
   DoDataExchange = 0
End Function

                                         


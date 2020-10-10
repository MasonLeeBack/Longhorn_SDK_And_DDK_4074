'
' Function to test the slow start behavior
' This function will test the slow start behavior till the window is open to ulWindowSize
'
Function SlowStart(ulCWnd, ulWindowSize, usSrcPort, usDestPort, ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulStatus, ulTID, pACKPacket, pTCPPacket, ReceiveTimer
   Dim ulBytesRcvd, ulTotalBytesRcvd, ulSendDataSize, ulReceiveTO, ulLastAckNumber
   Dim ulOutstanding, ulNextAckNumber 
   
   '
   ' Calculate the data to be sent. Note that if the window size is not a multiple of MSS, and there
   ' is more data to send, the last segment will be delayed because of silly window avoidance. This 
   ' problem will be seen when the window is fully open. So for that case, we will only send data 
   ' that can fit in the window, so the SWS avoidance doesn't delay the send by ~4 secs.
   '
   ulSendDataSize = ulCWnd
   ulOutstanding = ulCWnd
   do while (ulOutStanding <> ulWindowSize)
      '
      ' Since we have ACKed one segment, outstanding count falls by 1 and CWin increases by 1
      ' so we can send upto 2*usMSS
      '
      if ((ulOutstanding + usMSS) > ulWindowSize) then
         ulSendDataSize = ulSendDataSize + usMSS + ulWindowSize - ulOutstanding
         ulOutstanding = ulWindowSize
      else
         ulSendDataSize = ulSendDataSize + 2*usMSS
         ulOutstanding = ulOutstanding + usMSS
      end if
   loop
   
   ulLastAckNumber = ulAckNumber + ulSendDataSize
   ulReceiveTO = 400
   
   '
   ' Ask Autosrv to do a huge send
   '
   ulStatus = pControllerObj.Send(ulSessionId, 1, 0, ulSendDataSize, ulTID) 
   if (ulStatus <> 0) then
      Core.Log "SlowStart: Send - " & ulStatus
      SlowStart = 1
      exit function
   end if
   
   '
   ' Receive the first data packet
   '
   set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulTotalBytesRcvd, TCP_ACK, 3000)
   if (pTCPPacket is nothing) then
      Core.Log "SlowStart: Failed to receive 1st data packet"
      SlowStart = 2
      exit function
   end if

   '
   ' Receive the data till timeout happens
   '
   Set ReceiveTimer = Sparta.CreateReceiveTimer(ulReceiveTO)
   ulNextAckNumber = ulAckNumber
   do 
      Set pTCPPacket = IFace.ReceiveTimed(ReceiveTimer)
      if not (pTCPPacket is nothing) then
         ulTotalBytesRcvd = ulTotalBytesRcvd + pTCPPacket.IpHeader.DatagramLength - (pTCPPacket.IpHeader.Length)*4 - (pTCPPacket.TcpHeader.HdrLength)*4
         if (pTCPPacket.TCPHeader.SeqNumber <> ulNextAckNumber) then
            'Msgbox("Incorrect packet received")
            Core.log "SlowStart: Incorrect packet received"
            SlowStart = 1
            exit function
         end if
         ulNextAckNumber = ulAckNumber + ulTotalBytesRcvd
      end if
   loop while Not (pTCPPacket is Nothing) 
   
   '
   ' Ensure the data is as per the CWin Size
   '
   if (ulTotalBytesRcvd <> ulCWnd) then
      Core.Log "SlowStart: Didn't receive data based on CWin size " & ulTotalBytesRcvd
      SlowStart = 1
      exit function
   end if 
   
   '
   ' Send an ACK for the entire data
   '
   ulAckNumber = ulAckNumber + usMSS
   Set pACKPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   pACKPacket.TCPHeader.WindowSize = ulWindowSize
   IFace.Send(pACKPacket)   

   '
   ' Check that each ACK causes CWin to increase by MSS
   ' In other words, each ACK should cause the next two segments to be sent
   '
   do while (ulTotalBytesRcvd <> ulSendDataSize)
      ulBytesRcvd = 0
      Set ReceiveTimer = Sparta.CreateReceiveTimer(ulReceiveTO)
      do 
         Dim ulDataLength
         Set pTCPPacket = IFace.ReceiveTimed(ReceiveTimer)
         if not (pTCPPacket is nothing) then
            if (pTCPPacket.TCPHeader.SeqNumber <> ulNextAckNumber) then
               Core.log "SlowStart: Incorrect packet received"
               SlowStart = 1
               exit function
            end if
            ulDataLength = pTCPPacket.IpHeader.DatagramLength - (pTCPPacket.IpHeader.Length)*4 - (pTCPPacket.TcpHeader.HdrLength)*4
            ulNextAckNumber = ulNextAckNumber + ulDataLength
            ulBytesRcvd = ulBytesRcvd + ulDataLength
         end if
      loop while Not (pTCPPacket is Nothing) 
      
      ulTotalBytesRcvd = ulTotalBytesRcvd + ulBytesRcvd
      
      '
      ' The only case where we may not receive 2 segments is if the total data size to
      ' be xmitted is < 2*MSS
      '
      if (ulBytesRcvd <> 2*usMSS) then
         if (ulTotalBytesRcvd <> ulSendDataSize) then
            Core.Log "SlowStart: Didn't receive the expected data " & ulBytesRcvd
            SlowStart = 1
            exit function
         end if
      end if 
      
      '
      ' Send the next ACK
      '   
      ulAckNumber = ulAckNumber + usMSS           
      pACKPacket.TCPHeader.AckNumber = ulAckNumber
      IFace.Send(pACKPacket)
   loop
   
   '
   ' Send an ACK for the unacked data
   '
   ulAckNumber = ulLastAckNumber
   pACKPacket.TCPHeader.AckNumber = ulAckNumber
   IFace.Send(pACKPacket)

   SlowStart = 0
End Function




'
' Function to test the slow start behavior
' This function will test the slow start behavior till the window is open to ulWindowSize
'
Function SlowStartAndOpenWin(ulCWnd, ulFinalCWin, ulWindowSize, usSrcPort, usDestPort, ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulStatus, ulTID, pACKPacket, pTCPPacket, ReceiveTimer
   Dim ulBytesRcvd, ulTotalBytesRcvd, ulSendDataSize, ulReceiveTO, ulLastAckNumber
   Dim ulCurrentCWin, ulNextAckNumber 
   
   '
   ' Calculate the data size to open up the window
   '
   if (ulFinalCWin <= ulCWnd) then
      SlowStartAndOpenWin = 0
      exit function
   end if
  
   if (ulFinalCWin > ulWindowSize) then
      ulFinalCWin = ulWindowSize
   end if 

   '
   ' Find the number of ACKs to open up the window
   '
   ulCurrentCWin = ulCWnd + usMSS
   ulSendDataSize = ulCWnd
   while (ulCurrentCWin < ulFinalCWin)
      if ((ulCurrentCWin + usMSS) > ulFinalCWin) then
         ulSendDataSize = ulSendDataSize + ulFinalCWin - ulCurrentCWin
      else  
         ulSendDataSize = ulSendDataSize + 2*usMSS
      end if      
      ulCurrentCWin = ulCurrentCWin + usMSS
   Wend
      
   '
   ' Ask Autosrv to send the data 
   '
   ulStatus = pControllerObj.Send(ulSessionId, 1, 0, ulSendDataSize, ulTID) 
   if (ulStatus <> 0) then
      Core.Log "SlowStartAndOpenWin: Send - " & ulStatus
      SlowStartAndOpenWin = 1
      exit function
   end if
   
   '
   ' Start receiving the data and verifying the slow start behavior
   '
   ulTotalBytesRcvd = 0
   ulNextAckNumber = ulAckNumber
   bFirstXmit = TRUE
   ulReceiveTO = 400   
   Set pACKPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   pACKPacket.TCPHeader.WindowSize = ulWindowSize

   while (ulTotalBytesRcvd <> ulSendDataSize)
      '
      ' Receive the data till timeout happens
      '
      ulBytesRcvd = 0
      if (ulTotalBytesRcvd = 0) then
         '
         ' Receive the 1st data packet
         '
         set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_ACK, 3000)
         if (pTCPPacket is nothing) then
            Core.Log "SlowStartAndOpenWin: Failed to receive 1st data packet"
            SlowStartAndOpenWin = 2
            exit function
         end if
      end if      

      Set ReceiveTimer = Sparta.CreateReceiveTimer(ulReceiveTO)
      do 
         Dim ulDataLength
         Set pTCPPacket = IFace.ReceiveTimed(ReceiveTimer)
         if not (pTCPPacket is nothing) then
            if (pTCPPacket.TCPHeader.SeqNumber <> ulAckNumber) then
               Core.log "SlowStartAndOpenWin: Incorrect packet received"
               SlowStartAndOpenWin = 1
               exit function
            end if
            ulDataLength = pTCPPacket.IpHeader.DatagramLength - (pTCPPacket.IpHeader.Length)*4 - (pTCPPacket.TcpHeader.HdrLength)*4
            ulAckNumber = ulAckNumber + ulDataLength
            ulBytesRcvd = ulBytesRcvd + ulDataLength
         end if
      loop while Not (pTCPPacket is Nothing) 

      ulTotalBytesRcvd = ulTotalBytesRcvd + ulBytesRcvd

      '
      ' If its the first xmit, we expect CWnd data to be sent without waiting for an ACK
      ' else we expect 2*MSS data to be sent if that much is available for sending
      '
      if (bFirstXmit = TRUE) then
         bFirstXmit = FALSE
         if (ulBytesRcvd <> ulCWnd) then
            Core.Log "SlowStartAndOpenWin: Didn't receive the expected data on first xmit " & ulBytesRcvd
            SlowStartAndOpenWin = 1
            exit function
         end if 
      elseif (ulBytesRcvd <> 2*usMSS) then
         if (ulTotalBytesRcvd <> ulSendDataSize) then
            Core.Log "SlowStartAndOpenWin: Didn't receive the expected data " & ulBytesRcvd
            SlowStartAndOpenWin = 1
            exit function
         end if
      end if 
      
      '
      ' Send the appropriate ACK
      '   
      if (ulTotalBytesRcvd = ulSendDataSize) then
         ulNextAckNumber = ulAckNumber
      else
         ulNextAckNumber = ulNextAckNumber + usMSS           
      end if      
      pACKPacket.TCPHeader.AckNumber = ulNextAckNumber
      IFace.Send(pACKPacket)
   Wend

   SlowStartAndOpenWin = 0
End Function


'
' Function to test the fast rexmit behavior
'
Function FastRexmit(ulCWnd, ulWindowSize, usSrcPort, usDestPort, ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulStatus, ulTID, pACKPacket, pTCPPacket, ReceiveTimer
   Dim ulBytesRcvd, ulReceiveTO, bFirst, bPreRexmit, ulTotalBytesRcvd, ulSendDataSize
   dim ulJunkAckNumber, ulDupAckNumber

   '
   ' Ask Autosrv to do a huge send - max allowed by CWin
   '    
   ulSendDataSize = ulCWnd 
   ulStatus = pControllerObj.Send(ulSessionId, 1, 0, ulSendDataSize, ulTID) 
   if (ulStatus <> 0) then
      Core.Log "FastRexmit: Send - " & ulStatus
      FastRexmit = 1
      exit function
   end if
         
   '
   ' Receive the remaining data and verifying the fast rexmit behavior
   '   
   ulDupAckNumber = ulAckNumber   
   bPreRexmit = true
   ulReceiveTO = 3000
   ulTotalBytesRcvd = 0
   bFirst = true
   Set pACKPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   pACKPacket.TCPHeader.WindowSize = ulWindowSize
   do while ((ulTotalBytesRcvd <> ulSendDataSize) OR (bPreRexmit = TRUE))
      '
      ' Receive a packet
      '
      set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulJunkAckNumber, ulBytesRcvd, TCP_ACK, ulReceiveTO)
      if (pTCPPacket is Nothing) then
         Core.log "FastRexmit: Didn't receive data packet - " & ulTotalBytesRcvd & " <> " & ulSendDataSize
         FastRexmit = 1
         exit function
      end if
      ulReceiveTO = 200

      Core.log "Dup Ack - " & Hex(ulDupAckNumber) & ", Seq - " & Hex(pTCPPacket.TCPHeader.SeqNumber)
      if ((pTCPPacket.TCPHeader.SeqNumber = ulDupAckNumber) and (bFirst = false)) then       
         '
         ' If this is the rexmit, ACK everything till now
         '
         pACKPacket.TCPHeader.AckNumber = ulAckNumber
         IFace.Send(pACKPacket)
         bPreRexmit = FALSE
         Core.log "FastRexmit: Recvd rexmit - " & ulTotalBytesRcvd
      elseif (bPreRexmit = TRUE) then      
         '
         ' If this is pre rexmit, resend the ACK
         '
         IFace.Send(pACKPacket)
         ulTotalBytesRcvd = ulTotalBytesRcvd + ulBytesRcvd
         ulAckNumber = ulJunkAckNumber
         Core.log "FastRexmit: Recvd pre rexmit - " & ulTotalBytesRcvd
      else 
         '
         ' If this is post rexmit, send the ACK for this packet
         '
         ulTotalBytesRcvd = ulTotalBytesRcvd + ulBytesRcvd
         ulAckNumber = ulJunkAckNumber
         pACKPacket.TCPHeader.AckNumber = ulAckNumber
         IFace.Send(pACKPacket)
         Core.log "FastRexmit: Recvd post rexmit - " & ulTotalBytesRcvd
      end if 
      bFirst = false
   loop
End Function



'
' Function to test the fast rexmit behavior - ensure that the third dup ACK causes a 
' rexmit of the packet
'
Function FastRexmitExact(ulWindowSize, usSrcPort, usDestPort, ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulStatus, ulTID, pACKPacket, pTCPPacket, ulReceiveTO, ulBytesRcvd, ulJunkAckNumber
   
   '
   ' Ask Autosrv to do a send of 2 segments
   '    
   ulStatus = pControllerObj.Send(ulSessionId, 1, 0, usMSS*2, ulTID) 
   if (ulStatus <> 0) then
      Core.Log "FastRexmitExact: Send - " & ulStatus
      FastRexmitExact = 1
      exit function
   end if
   
   Set pACKPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   pACKPacket.TCPHeader.WindowSize = ulWindowSize

   '
   ' Receive 2 data packets and resend the last ACK
   '
   ulReceiveTO = 3000
   For ulCounter = 1 to 2
      '
      ' Receive a packet
      '
      set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_ACK, ulReceiveTO)
      if (pTCPPacket is Nothing) then
         Core.log "FastRexmitExact: Didn't receive data packet"
         FastRexmitExact = 1
         exit function
      end if
      
      '
      ' Resend the ACK
      '     
      ulReceiveTO = 200 
      IFace.Send(pACKPacket)
   Next
   
   '
   ' Receive the rexmit
   '
   Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulJunkAckNumber, ulBytesRcvd, TCP_ACK, 200)
   if (pTCPPacket is Nothing) then
      Core.log "FastRexmitExact: Didn't receive rexmitted packet"
      FastRexmitExact = 1
      exit function
   end if
   if (pTCPPacket.TCPHeader.SeqNumber <> pACKPacket.TCPHeader.AckNumber) then
      Core.log "FastRexmitExact: Received packet but not rexmit"
      FastRexmitExact = 1
      exit function
   end if

   '
   ' Ack the entire data
   '
   pACKPacket.TCPHeader.AckNumber = ulAckNumber
   IFace.Send(pACKPacket)
   
   FastRexmitExact = 0
End Function

'
' Function to test congestion avoidance
'
Function CongestionAvoidance(ulCWnd, ulWindowSize, usSrcPort, usDestPort, ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulStatus, ulTID, pACKPacket, pTCPPacket, ReceiveTimer
   Dim ulBytesRcvd, ulReceiveTO, bFirst, bPreRexmit, ulTotalBytesRcvd, ulSendDataSize
   Dim ulCurrentCWin, ulFactor, ulBytesExpected

   '
   ' Calculate the send data size
   '
   ulSendDataSize = ulCWnd - usMSS
   ulCurrentCWin = ulCWnd
   do while (ulCurrentCWin < ulWindowSize)
      ulSendDataSize = ulSendDataSize + ulCurrentCWin + 2*usMSS
      ulCurrentCWin = ulCurrentCWin + usMSS
   loop

   '
   ' Start receiving the data
   '   
   ulTotalBytesRcvd = 0
   ulFactor = Clng(ulCWnd/usMSS) + 1
   ulReceiveTO = 500
   ulBytesExpected = ulCWnd   
   Set pACKPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   pACKPacket.TCPHeader.WindowSize = ulWindowSize
   ulNextAckNumber = ulAckNumber
   ulCurrentCWin = ulCWnd
   
 
   '
   ' Ask Autosrv to do a huge send
   '
   ulStatus = pControllerObj.Send(ulSessionId, 1, 0, ulSendDataSize, ulTID) 
   if (ulStatus <> 0) then
      Core.Log "CongestionAvoidance: Send - " & ulStatus
      CongestionAvoidance = 1
      exit function
   end if
   
      
   While (ulTotalBytesRcvd <> ulSendDataSize)
      '
      ' Receive data till timeout happens
      '        
      ulBytesRcvd = 0
      Set ReceiveTimer = Sparta.CreateReceiveTimer(ulReceiveTO)
      do 
         Dim ulDataLength
         Set pTCPPacket = IFace.ReceiveTimed(ReceiveTimer)
         if not (pTCPPacket is nothing) then
            if (pTCPPacket.TCPHeader.SeqNumber <> ulAckNumber) then
               Core.log "CongestionAvoidance: Incorrect packet received " & Hex(pTCPPacket.TCPHeader.SeqNumber)
               CongestionAvoidance = 1
               exit function
            end if
            ulDataLength = pTCPPacket.IpHeader.DatagramLength - (pTCPPacket.IpHeader.Length)*4 - (pTCPPacket.TcpHeader.HdrLength)*4
            ulAckNumber = ulAckNumber + ulDataLength
            ulBytesRcvd = ulBytesRcvd + ulDataLength
         end if
      loop while Not (pTCPPacket is Nothing) 

      ulTotalBytesRcvd = ulTotalBytesRcvd + ulBytesRcvd
      Core.log "CWin = " & ulCurrentCWin & ", ulBytesExpected = " & ulBytesExpected & ", ulBytesRcvd = " & ulBytesRcvd

      '
      ' Ensure the amount of data received is as expected
      '
      if (ulBytesRcvd <> ulBytesExpected) then
         Core.Log "CongestionAvoidance: Didn't receive expected data " & ulBytesRcvd
         Core.log "Expecting = " & ulBytesExpected & "   Received = " & ulBytesRcvd
         CongestionAvoidance = 1
         exit function
      end if
      
      
      '
      ' Send an ACK for the appropriate packet
      '
      if (ulTotalBytesRcvd = ulSendDataSize) then
         ulNextAckNumber = ulAckNumber
      else
         ulNextAckNumber = ulNextAckNumber + usMSS
      end if
      
      pACKPacket.TCPHeader.AckNumber = ulNextAckNumber
      IFace.Send(pACKPacket)
      ulCurrentCWin = ulCurrentCWin + Clng(Fix(usMSS*(usMSS/ulCurrentCWin)))
      'Core.log "CongestionAvoidance: ulCurrentCWin = " & ulCurrentCWin
      ulBytesExpected = usMSS
      if (ulCurrentCWin >= (ulFactor*usMSS)) then
         ulBytesExpected = 2*usMSS
         ulFactor = ulFactor + 1
      end if

   Wend

End Function

'
' Function to test the window size
'
Function TestWindowSize(ulCWnd, ulWindowSize, usSrcPort, usDestPort, ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulStatus, ulTID, ulBytesRcvd, pTCPPacket, ReceiveTimer, pACKPacket
   
   '
   ' Ask Autosrv to do a send of ulCWnd + delta
   '   
   ulStatus = pControllerObj.Send(ulSessionId, 1, 0, ulCWnd+100, ulTID) 
   if (ulStatus <> 0) then
      Core.Log "TestWindowSize: Send - " & ulStatus
      TestWindowSize = 1
      exit function
   end if
   
   '
   ' Receive the first data packet
   '
   set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_ACK, 3000)
   if (pTCPPacket is nothing) then
      Core.Log "TestWindowSize: Failed to receive 1st data packet"
      TestWindowSize = 2
      exit function
   end if
   
   '
   ' Receive data till TO happens
   '
   Set ReceiveTimer = Sparta.CreateReceiveTimer(500)
   do 
      Dim ulDataLength
      Set pTCPPacket = IFace.ReceiveTimed(ReceiveTimer)
      if not (pTCPPacket is nothing) then
         if (pTCPPacket.TCPHeader.SeqNumber <> ulAckNumber) then
            Core.log "TestWindowSize: Incorrect packet received"
            TestWindowSize = 1
            exit function
         end if
         ulDataLength = pTCPPacket.IpHeader.DatagramLength - (pTCPPacket.IpHeader.Length)*4 - (pTCPPacket.TcpHeader.HdrLength)*4
         ulAckNumber = ulAckNumber + ulDataLength
         ulBytesRcvd = ulBytesRcvd + ulDataLength
      end if
   loop while Not (pTCPPacket is Nothing) 

   
   '
   ' Check that the size of data received is ulCWnd
   '
   if (ulBytesRcvd <> ulCWnd) then
      Core.log "TestWindowSize: Received incorrect data " & ulBytesRcvd
      TestWindowSize = 1
      exit function
   end if
   
   '
   ' Send an ACK
   '   
   Set pACKPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   pACKPacket.TCPHeader.WindowSize = ulWindowSize
   IFace.Send(pACKPacket)
    
   '
   ' Receive the last delta bytes
   '         
   Set pTCPPacket = IFace.ReceiveTimed(500)
   if (pTCPPacket is Nothing) then
      Core.log "TestWindowSize: Didn't receive the last segment"
      TestWindowSize = 1
      exit function
   end if                     
    
   '
   ' Send an ACK
   '
   ulAckNumber = ulAckNumber + 100   
   pACKPacket.TCPHeader.AckNumber = ulAckNumber
   IFace.Send(pACKPacket)

   TestWindowSize = 0
End Function

'
' Function to let the TO expire and have the packet rexmitted
'
Function TimeoutAndRexmit(ulWindowSize, usSrcPort, usDestPort, ulSessionId, ByRef ulSeqNumber, ByRef ulAckNumber)
   Dim ulStatus, ulTID, ulCounter, pTCPPacket

   '
   ' Ask Autosrv to send a packet
   '
   ulStatus = pControllerObj.Send(ulSessionId, 1, 0, usMSS, ulTID) 
   if (ulStatus <> 0) then
      Core.Log "TimeoutAndRexmit: Send - " & ulStatus
      TimeoutAndRexmit = 1
      exit function
   end if

   
   '
   ' Receive the packet and its rexmit
   '
   For ulCounter = 1 to 2 
      Dim ulBytesRcvd
      Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_ACK, 5000) 
      if (pTCPPacket is Nothing) then
         Core.log "TimeoutAndRexmit: Didn't receive the data packet"
         TimeoutAndRexmit = 1
         exit Function
      end if
   Next
   
   '
   ' Send an ACK
   '   
   Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
   pTCPPacket.TCPHeader.WindowSize = ulWindowSize
   IFace.Send(pTCPPacket)

   TimeoutAndRexmit = 0
End Function
 



'==========================================================================
'
' NAME: 	DataCmds.vbs
'
' AUTHOR: 	David Harding , Microsoft
' DATE  : 	1/11/2001
'
' USAGE:	WAN
'
' COMMENT: 	This script contains common data commands for sending data, 
'			receiving data and so on.
'
'==========================================================================
Option Explicit

Function ReceiveData(oReceiver, oSender)
Dim ReceiverAddress
Dim MaxTotalSize, PacketsSent, Received, Resent, MinPacketSize, bRetVal
Dim PacketSizeStep, TotalPackets, PacketSize, MaximumPacketSize

	ReceiverAddress	= Array(CByte(0), CByte(0), CByte(0), CByte(0), CByte(0), CByte(0))
	PacketsSent 	= 0
	Received 		= 0
	Resent 			= 0
	TotalPackets	= 200
	MinPacketSize 	= 64
	PacketSizeStep 	= 200
	MaxTotalSize	= 1514
	MaximumPacketSize	= 0

	oLog.Variation("Query OID_802_3_CURRENT_ADDRESS")
	bRetVal = QueryInfo(oReceiver, OID_802_3_CURRENT_ADDRESS, ReceiverAddress, 6)
	if(bRetVal = false) then 
		call oLog.Failed ("QueryInfo() failed!" , 22875)
		exit function
	end if
	
	oLog.Variation("Query Support Card OID_GEN_MAXIMUM_TOTAL_SIZE")
	bRetVal = QueryInfo(oReceiver, OID_GEN_MAXIMUM_TOTAL_SIZE, MaximumPacketSize, 4)
	if(bRetVal = false) then 
		call oLog.Failed ("QueryInfo() failed!" , 22876)
		exit function
	end if
	
	If(MaxTotalSize < MaximumPacketSize) Then 
		MaximumPacketSize = MaxTotalSize
	End If
	   
    oLog.Variation("Set packet filter to DIRECTED")
	bRetVal = SetPacketFilter(oReceiver, DIRECTED)
	if(bRetVal = false) then
		call oLog.Failed ("SetPacketFilter() failed!" , 22877)
		exit function
	end if      
			      	
	PacketSize = MinPacketSize
	
	Do While(PacketSize <= MaximumPacketSize)
		        					            
   		bRetVal = oReceiver.StartReceive()
    	If(bRetVal = false) Then
    		call oLog.Failed ("StartReceive(Test Card) failed! (Local)" , 22878)
    		Exit Do
    	End If
	            	
      	oLog.Variation("Waiting to receive " & TotalPackets & " packets of size " & FormatNumber(PacketSize,0) & "...")
        bRetVal = oSender.Send(ReceiverAddress, PacketSize, TotalPackets, 0, null)
        if(bRetVal = true) then
        	bRetVal = oSender.WaitSend()
            if(bRetVal = vbTrue) then
            	bRetVal = oSender.GetSendResults(PacketsSent, SEND_FAILURES_FORBIDDEN)
				if(bRetVal = true) then 
              		if(not PacketsSent = TotalPackets) then
                   		call oLog.Failed ("Should have sent " & TotalPackets & " packets!" , 22879)
            		end if
                 end if
          	end if
      	end if
		
		WScript.Sleep(2000)

       	'
        ' get receive results from "receiving" open instance
        '
        bRetVal = oReceiver.StopReceive()
        If(bRetVal = vbTrue) Then
        	bRetVal = oReceiver.GetReceiveResults(Received, Resent)
        	if(bRetVal = true) then 
        		if(not Resent = 0) then 
           			call oLog.Failed ("No packets should have been resent!" , 22880)
        		end if
        		if(not Received = TotalPackets) then
           			call oLog.Failed ("Should have received " & TotalPackets & " packets!" , 22881)
        		end if
       		end if
    	end if
		
		'
		' set up size for next batch of packets
		'
		if(PacketSize = MaximumPacketSize) then
			exit do
		end if
					
		PacketSize = PacketSize + PacketSizeStep		
		if(PacketSize > MaximumPacketSize) then
			PacketSize = MaximumPacketSize
		end if
	    
	loop

End Function

'//////////////////////////////////////////////////////////////////////////////////////////////////
'
'
'//////////////////////////////////////////////////////////////////////////////////////////////////
Function SendData(oSender, oReceiver)
Dim ReceiverAddress
Dim MaxTotalSize, PacketsSent, Received, Resent, MinPacketSize
Dim PacketSizeStep, TotalPackets, PacketSize, MaximumPacketSize
Dim bRetVal, MaxTests, Count
	'
	' Prepare variable to hold mac address
	'
	ReceiverAddress		= Array(CByte(0), CByte(0), CByte(0), CByte(0), CByte(0), CByte(0))
	MaxTests    		= 1
	PacketsSent 		= 0
	Received 			= 0
	Resent 				= 0
	TotalPackets		= 200
	MinPacketSize 		= 64
	PacketSizeStep 		= 200
	MaxTotalSize		= 1514
	MaximumPacketSize	= 0
	Count 				= 0

	oLog.Variation("Query OID_802_3_CURRENT_ADDRESS")
	bRetVal = QueryInfo(oReceiver, OID_802_3_CURRENT_ADDRESS, ReceiverAddress, 6)
	If(bRetVal = false) Then 
		call oLog.Failed ("QueryInfo() failed!", 22882)
		Exit Function
	End If
	
	oLog.Variation("Query OID_GEN_MAXIMUM_TOTAL_SIZE")
	bRetVal = QueryInfo(oSender, OID_GEN_MAXIMUM_TOTAL_SIZE, MaximumPacketSize, 4)
	If(bRetVal = false) Then 
		call oLog.Failed ("QueryInfo() failed!", 22883)
		Exit Function
	ElseIf(MaxTotalSize < MaximumPacketSize) Then 
		MaximumPacketSize = MaxTotalSize
	End If
	
	oLog.Variation("Set packet filter to DIRECTED")
	bRetVal = SetPacketFilter(oReceiver, DIRECTED)
	if(bRetVal = false) then
		call oLog.Failed ("SetPacketFilter() failed!" , 22884)
		exit function
	end if
	   	
	PacketSize = MinPacketSize

	Do While(PacketSize <= MaximumPacketSize)
	      	
		bRetVal = oReceiver.StartReceive()
	    if(bRetVal = false) then
	    	call oLog.Failed ("StartReceive() failed!" , 22885)
	    	exit do
	    end if
	        
		'
	    ' Send x packets to receiver
	    '
	    oLog.Variation("Sending " & TotalPackets & " packets of size " & FormatNumber(PacketSize, 0) & " and verifying receives...")
	    bRetVal = oSender.Send(ReceiverAddress, PacketSize, TotalPackets, 0, null)
	       
	    if(bRetVal = true) then
	    	bRetVal = oSender.WaitSend()
	        if(bRetVal = true) then
	           	bRetVal = oSender.GetSendResults(PacketsSent, SEND_FAILURES_FORBIDDEN)
	            if(bRetVal = true) then 
	         		if(not PacketsSent = TotalPackets) Then
	                	call oLog.Failed ("Should have sent " & TotalPackets & " packets!" , 22886)
	                end if
	           	end if
	       	end if
		end if

		WScript.Sleep(2000)
				
		'
	    ' Check the receivers results to make sure he received all packets
	    '
	   	bRetVal = oReceiver.StopReceive()
	    if(bRetVal = true) then
	    	bRetVal = oReceiver.GetReceiveResults(Received, Resent)
	        if(bRetVal = true) then 
	           	if(not Resent = 0) then 
	               	call oLog.Failed ("No packets should have been resent!" , 22887)
	           	end if
	           	if(not Received = TotalPackets) then
	               	call oLog.Failed ("Should have received " & TotalPackets & " packets!" , 22888)
	           	end if
	       	end if
	 	end if
        	
      	if(PacketSize = MaximumPacketSize) then
       		exit do
      	end if

		PacketSize = PacketSize + PacketSizeStep		
		if(PacketSize > MaximumPacketSize) then
			PacketSize = MaximumPacketSize
		end if
	
	Loop
		
End Function

'//////////////////////////////////////////////////////////////////////////////////////////////////
'
'                                     
'//////////////////////////////////////////////////////////////////////////////////////////////////
Function Performance(oLocalOpen, oRemoteOpen)
Dim ResultSize
Dim MinNumPkts, MedNumPkts, MaxNumPkts, MaximumPacketSize
Dim MaxTotalSize, Mode
Dim PktSizeInc, PktSizeMin, PktSizeMax, PktSizeBreak1, PktSizeBreak2
Dim bResult, bCancelPkts
Dim TestAddr
Dim TestDuration
Dim PacketSize, NumPackets
Dim BytesSent, BytesRecv
Dim PktsPerBurst, Delay
Dim bRetVal

	PacketSize 			= 0
	PktsPerBurst		= 1
	NumPackets			= 0
	Delay				= 0
	bCancelPkts			= vbFalse
	
	PktSizeBreak1 		= 512
	PktSizeBreak2 		= 1024
	
	MinNumPkts 			= 300
	MedNumPkts			= 200
	MaxNumPkts			= 100
	
	MaximumPacketSize 	= 0
	MaxTotalSize 		= 1514
	ResultSize 			= 4
	TestAddr			= NetAddr(&H00&, &H01&, &H02&, &H03&, &H04&, &H05&)
	TestDuration 		= 10

	Do
		oLog.Variation("Set Test Card Packet filter to NONE")
		bRetVal = SetPacketFilter(oLocalOpen, 0)
		If(bRetVal = vbFalse) Then
			call oLog.Failed ("SetPacketFilter() failed!", 22889)
		End If
			
		oLog.Variation("Query Test Card OID_GEN_MAXIMUM_TOTAL_SIZE")
		bRetVal = QueryInfo(oLocalOpen, OID_GEN_MAXIMUM_TOTAL_SIZE, MaximumPacketSize, ResultSize)
		If(MaxTotalSize < MaximumPacketSize) Then MaximumPacketSize = MaxTotalSize
	   	
		PktSizeInc 	= (MaximumPacketSize - 64) / 15 
		PktSizeMin 	= MaximumPacketSize - (15 * PktSizeInc)
		PktSizeMax  = MaximumPacketSize
			
		'
		' First, do send-only test.  Send random_directed packets to oblivion
		'
		PacketSize 	= PktSizeMin
		Mode		= PERFORM_SEND
		While(PacketSize <= PktSizeMax)
			If(PacketSize <= PktSizeBreak1) Then
	   			NumPackets = MinNumPkts
	   		ElseIf(PacketSize <= PktSizeBreak2) Then
	   			NumPackets = MedNumPkts
	   		Else
	      		NumPackets = MaxNumPkts
	   		End If
   		
	   		oLog.Variation("Sending " & NumPackets & " packets of size " & FormatNumber(PacketSize,0) & " to oblivion...")
		   	bResult = oLocalOpen.StartPerformance(Null, _
		   											TestAddr, _
		   											Mode, _
		   											PacketSize, _
		   											PktsPerBurst, _
		   											NumPackets, _
		   											TestDuration, _
		   											Delay, _
		   											bCancelPkts)
		   	If(bResult = vbFalse) Then
		   		call oLog.Failed ("StartPrefomance() failed!" , 22890)
		   		Exit Do
		   	End If
	   	
		   	bResult = oLocalOpen.WaitPerformance()
		   	If(bResult = vbFalse) Then
		   		call oLog.Failed ("WaitPerformance() failed!" , 22891)
		   		Exit Do
		   	End If
		   	    	
		   	bResult = oLocalOpen.GetPerformanceResults(TestDuration, BytesSent, BytesRecv)
			If(bResult = vbFalse) Then
		   		call oLog.Failed ("GetPerformanceResults() failed!" , 22892)
		   		Exit Do
		   	End If
		   	
		   	PacketSize = PacketSize + PktSizeInc
			
		Wend
	
		oLog.Variation("Set Test Card Packet filter to DIRECTED")
		bRetVal = SetPacketFilter(oLocalOpen, DIRECTED)
		If(bRetVal = vbFalse) Then
			call oLog.Failed ("SetPacketFilter() failed!", 22893)
		End If
		
		PacketSize = PktSizeMin
		While(PacketSize <= PktSizeMax)
			If(PacketSize <= PktSizeBreak1) Then
		   		NumPackets = MinNumPkts
		   	ElseIf(PacketSize <= PktSizeBreak2) Then
		   		NumPackets = MedNumPkts
		   	Else
		   		NumPackets = MaxNumPkts
		   	End If
			
			Mode = PERFORM_RECEIVE
	   
	   		oLog.Variation("Sending " & NumPackets & " directed packets of size " & FormatNumber(PacketSize,0) & "...")
	   		bResult = oLocalOpen.StartPerformance(oRemoteOpen, _
	   												TestAddr, _
	   												Mode, _
	   												PacketSize, _
	   												PktsPerBurst, _
	   												NumPackets, _
	   												TestDuration, _
	   												Delay, _
	   												bCancelPkts)
		  	If(bResult = vbFalse) Then
		    	call oLog.Failed ("StartPerformance() failed" , 22894)
		      	Exit Do
		   	End If
   
		   	bResult = oLocalOpen.WaitPerformance()
			If(bResult = vbFalse) Then
		    	call oLog.Failed ("WaitPerformance() failed" , 22895)
		    	Exit Do
		   	End If
			
		   	bResult = oLocalOpen.GetPerformanceResults(TestDuration, BytesSent, BytesRecv)
		   	If(bResult = vbFalse) Then
		   		call oLog.Failed ("GetPerformanceResults() failed" , 22896)
		    	Exit Do
		   	End If
	   
	   		WScript.Sleep(2000)
	
	   		Mode = PERFORM_RECEIVE + PERFORM_VERIFY_RECEIVES
	   	
		   	oLog.Variation("Sending " & NumPackets & " directed packets of size " & FormatNumber(PacketSize,0) & " and verifying receives...")
		   	bResult = oLocalOpen.StartPerformance(oRemoteOpen, _
		   											TestAddr, _ 
		   											Mode, _
		   											PacketSize, _
		   											PktsPerBurst, _
		   											NumPackets, _
		   											TestDuration, _
		   											Delay, _
		   											bCancelPkts)
		  	If(bResult = vbFalse) Then
		    	call oLog.Failed ("StartPerformance() failed" , 22897)
		      	Exit Do
		   	End If
   
		   	bResult = oLocalOpen.WaitPerformance()
			If(bResult = vbFalse) Then
		    	call oLog.Failed ("WaitPerformance() failed" , 22898)
		    	Exit Do
		   	End If
	
		   	bResult = oLocalOpen.GetPerformanceResults(TestDuration, BytesSent, BytesRecv)
		   	If(bResult = vbFalse) Then
		   		call oLog.Failed ("GetPerformanceResults() failed" , 22899)
		    	Exit Do
		   	End If
		   	
		   	WScript.Sleep(2000)
		
		   	PacketSize = PacketSize + PktSizeInc
		   	
		Wend
	
	Loop While(vbFalse)

End Function

'//////////////////////////////////////////////////////////////////////////////////////////////////
'
'
'//////////////////////////////////////////////////////////////////////////////////////////////////
Function ClientStress(oLocalOpen, oRemoteOpen)
Dim Count, ResultSize, MaximumPacketSize, MaxTotalSize
Dim Iterations(10) 
Dim PacketSize(10)
Dim OptionMask(10)
Dim bRetVal

	MaxTotalSize = 1514
	
	ResultSize = 4
	oLog.Variation("Query Support Card (OID_GEN_MAXIMUM_TOTAL_SIZE)")
	bRetVal = QueryInfo(oRemoteOpen, OID_GEN_MAXIMUM_TOTAL_SIZE, MaximumPacketSize, ResultSize)
	If(bRetVal = vbFalse) Then
		call oLog.Failed ("QueryInfo() failed!" , 22900)
		Exit Function
	ElseIf(MaxTotalSize < MaximumPacketSize) Then 
		MaximumPacketSize = MaxTotalSize
	End If
	
	oLog.Variation("Set Test Card packet filter to DIRECTED")
	bRetVal = SetPacketFilter(oLocalOpen, DIRECTED)
	If(bRetVal= vbFalse) Then
		call oLog.Failed ("SetPacketFilter() failed!" , 22901)
	End If

	oLog.Variation("Set Support Card packet filter to DIRECTED")
	bRetVal = SetPacketFilter(oRemoteOpen, DIRECTED)
	If(bRetVal= vbFalse) Then
		call oLog.Failed ("SetPacketFilter() failed!" , 22902)
	End If
	
	'
	' set up variables for all the tests..
	'
	Iterations(0)  = 500
	PacketSize(0)  = MaximumPacketSize
	OptionMask(0)  = STRESS_RANDOMSIZE Or STRESS_ZEROS Or STRESS_ACK Or STRESS_WINDOWING_ON
	
	Iterations(1)  = 500
	PacketSize(1)  = MaximumPacketSize
	OptionMask(1)  = STRESS_RANDOMSIZE Or STRESS_ONES Or STRESS_ACK Or STRESS_WINDOWING_ON
	
	Iterations(2)  = 500
	PacketSize(2)  = 256
	OptionMask(2)  = STRESS_RANDOMSIZE Or STRESS_SMALL Or STRESS_ACK Or STRESS_WINDOWING_ON

	Iterations(3)  = 5
	PacketSize(3)  = 512
	OptionMask(3)  = STRESS_CYCLICAL Or STRESS_RAND Or STRESS_ACK Or STRESS_WINDOWING_ON
	
	Iterations(4)  = 2
	PacketSize(4)  = MaximumPacketSize
	OptionMask(4)  = STRESS_CYCLICAL Or STRESS_RAND Or STRESS_FULLRESP Or STRESS_WINDOWING_ON
	
	Iterations(5)  = 500
	PacketSize(5)  = 100
	OptionMask(5)  = STRESS_FIXEDSIZE Or STRESS_SMALL Or STRESS_ACK Or STRESS_WINDOWING_ON
	
	Iterations(6)  = 500
	PacketSize(6)  = 256
	OptionMask(6)  = STRESS_RANDOMSIZE Or STRESS_SMALL Or STRESS_ACK10 Or STRESS_WINDOWING_ON
	
	Iterations(7)  = 500
	PacketSize(7)  = MaximumPacketSize
	OptionMask(7)  = STRESS_RANDOMSIZE Or STRESS_RAND Or STRESS_NORESP Or STRESS_WINDOWING_OFF

	Iterations(8)  = 500
	PacketSize(8)  = MaximumPacketSize
	OptionMask(8)  = STRESS_RANDOMSIZE Or STRESS_RAND Or STRESS_FULLRESP Or STRESS_WINDOWING_OFF
	
	Iterations(9)  = 500
	PacketSize(9)  = 60
	OptionMask(9)  = STRESS_FIXEDSIZE Or STRESS_RAND Or STRESS_FULLRESP Or STRESS_WINDOWING_OFF
	
	Count = 0
	While(Count < 10)
	
		oLog.Variation("Running stress case " & Count & "...")
		bRetVal = oLocalOpen.StartStress(oRemoteOpen, _
										 PacketSize(Count), _
										 Iterations(Count), _
										 OptionMask(Count), _
										 10)
		If(bRetVal = vbTrue) Then
	   		bRetVal = oLocalOpen.WaitStress()
	      	If(bRetVal = vbTrue) Then
	      		bRetVal = oLocalOpen.GetStressResults()
	      		If(bRetVal = vbFalse) Then
	      			call oLog.Failed ("GetStressResults() failed!" , 22903)
	      		End If
	      	End If
	    Else
	   		call oLog.Failed ("Failed to start stress test!" , 22904)
	   	End If
	
	   	bRetVal = oLocalOpen.GetEvents()
	   	If(bRetVal = vbFalse) Then
	    	Call oLog.Write("GetEvents() failed for Test Card!" )
	   	End If
	
	   	bRetVal = oRemoteOpen.GetEvents()
	   	If(bRetVal = vbFalse) Then
	    	Call oLog.Write("GetEvents() failed for support Card!" )
	   	End If
	
		Count = Count + 1
	   
	   WScript.Sleep(2000)
	
	Wend
	
End Function

'//////////////////////////////////////////////////////////////////////////////////////////////////
'
'
'//////////////////////////////////////////////////////////////////////////////////////////////////
Function ServerStress(oLocalOpen, oRemoteOpen)
Dim Count, ResultSize, MaximumPacketSize, MaxTotalSize
Dim Iterations(10) 
Dim PacketSize(10)
Dim OptionMask(10)
Dim bRetVal

	MaxTotalSize = 1514
	
	ResultSize = 4
	oLog.Variation("Query Support OID_GEN_MAXIMUM_TOTAL_SIZE")
	bRetVal = QueryInfo(oRemoteOpen, OID_GEN_MAXIMUM_TOTAL_SIZE, MaximumPacketSize, ResultSize)
	If(bRetVal = vbFalse) Then
		call oLog.Failed ("QueryInfo() failed!" , 22905)
		Exit Function
	ElseIf(MaxTotalSize < MaximumPacketSize) Then 
		MaximumPacketSize = MaxTotalSize
	End If
	
	oLog.Variation("Set Test Card Packet filter to DIRECTED")
	bRetVal = SetPacketFilter(oLocalOpen, DIRECTED)
	If(bRetVal= vbFalse) Then
		call oLog.Failed ("SetPacketFilter() failed! (Local)" , 22906)
		Exit Function
	End If
	
	oLog.Variation("Set Support Card Packet filter to DIRECTED")
	bRetVal = SetPacketFilter(oRemoteOpen, DIRECTED)
	If(bRetVal= vbFalse) Then
		call oLog.Failed ("SetPacketFilter() failed! (Remote)" , 22907)
		Exit Function
	End If

	'
	' set up variables for all the tests..
	Iterations(0)  = 500
	PacketSize(0)  = MaximumPacketSize
	OptionMask(0)  = STRESS_RANDOMSIZE Or STRESS_ZEROS Or STRESS_ACK Or STRESS_WINDOWING_ON
	
	Iterations(1)  = 500
	PacketSize(1)  = MaximumPacketSize
	OptionMask(1)  = STRESS_RANDOMSIZE Or STRESS_ONES Or STRESS_ACK Or STRESS_WINDOWING_ON
	
	Iterations(2)  = 500
	PacketSize(2)  = 256
	OptionMask(2)  = STRESS_RANDOMSIZE Or STRESS_SMALL Or STRESS_ACK Or STRESS_WINDOWING_ON
	
	Iterations(3)  = 5
	PacketSize(3)  = 512
	OptionMask(3)  = STRESS_CYCLICAL Or STRESS_RAND Or STRESS_ACK Or STRESS_WINDOWING_ON
	
	Iterations(4)  = 2
	PacketSize(4)  = MaximumPacketSize
	OptionMask(4)  = STRESS_CYCLICAL Or STRESS_RAND Or STRESS_FULLRESP Or STRESS_WINDOWING_ON

	Iterations(5)  = 500
	PacketSize(5)  = 100
	OptionMask(5)  = STRESS_FIXEDSIZE Or STRESS_SMALL Or STRESS_ACK Or STRESS_WINDOWING_ON
	
	Iterations(6)  = 500
	PacketSize(6)  = 256
	OptionMask(6)  = STRESS_RANDOMSIZE Or STRESS_SMALL Or STRESS_ACK10 Or STRESS_WINDOWING_ON
	
	Iterations(7)  = 500
	PacketSize(7)  = MaximumPacketSize
	OptionMask(7)  = STRESS_RANDOMSIZE Or STRESS_RAND Or STRESS_NORESP Or STRESS_WINDOWING_OFF
	
	Iterations(8)  = 500
	PacketSize(8)  = MaximumPacketSize
	OptionMask(8)  = STRESS_RANDOMSIZE Or STRESS_RAND Or STRESS_FULLRESP Or STRESS_WINDOWING_OFF
	
	Iterations(9)  = 500
	PacketSize(9)  = 60
	OptionMask(9)  = STRESS_FIXEDSIZE Or STRESS_RAND Or STRESS_FULLRESP Or STRESS_WINDOWING_OFF


	'
	' Now run the tests..
	Count = 0
	While(Count < 10)
		
		oLog.Variation("Running stress case " & Count & "...")
		bRetVal = oRemoteOpen.StartStress(oLocalOpen, _
										  PacketSize(Count), _
										  Iterations(Count), _
										  OptionMask(Count), _
										  10)
		If(bRetVal = vbTrue) Then
	   		bRetVal = oRemoteOpen.WaitStress()
	      	If(bRetVal = vbTrue) Then
	      		bRetVal = oRemoteOpen.GetStressResults()
	      	End If
	    Else
	   		call oLog.Failed ("Failed to start stress test!" , 22908)
	   	End If
	
	   	bRetVal = oLocalOpen.GetEvents()
	   	If(bRetVal = vbFalse) Then
	    	Call oLog.Write("GetEvents() failed for Test Card!" )
	   	End If
	
	   	bRetVal = oRemoteOpen.GetEvents()
	   		If(bRetVal = vbFalse) Then
	    	Call oLog.Write("GetEvents() failed for Support Card!" )
	   	End If

	Count = Count + 1
   
   WScript.Sleep(2000)

Wend

End Function

'<!-- CRC = 0x285e8462 --->
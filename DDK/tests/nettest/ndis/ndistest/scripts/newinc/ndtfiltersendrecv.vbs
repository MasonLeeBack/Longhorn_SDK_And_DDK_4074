Option Explicit



Function SendRecvNetBufferLists (lTestAdapterIndex, lSuppAdapterIndex, oLog)
   Dim oTestCard, oTestOpen, oTestEndPoint
   Dim oSuppCard, oSuppOpen, oSuppEndPoint
   Dim nSendDuration,nTotalNumCallsToSend,nInitialBurstSize
   Dim nNumNetBufferListsPerSend, nNumNetBuffersPerNBL, nNetBufferSize, nMaxMdlSize
   Dim pAdapterList
   Dim oSendCommMgrConfig, oSendNBConfig, oSendMediaConfig, oSendCommMgrStats
   Dim DestAddr, nReceiveDelay
   Dim oRecvCommMgrConfig, oRecvNBConfig, oRecvMediaConfig
   Dim Status
      
   nSendDuration = 2000
   nTotalNumCallsToSend = 200
   nInitialBurstSize = 50

   nNumNetBufferListsPerSend = 2
   nNumNetBuffersPerNBL = 20
   nNetBufferSize = 1000
   nMaxMdlSize = 100

   Set pAdapterList = oNDInfo.AdapterList

   Set oTestCard = New CLanCard6
   If (oTestCard is Nothing) Then
      Exit Function
   End If
 
   Set oTestOpen = oTestCard.vbSetupBasicTest(pAdapterList (lTestAdapterIndex))
   If (oTestOpen is Nothing) Then
      Exit Function
   End If
 
   Set oTestEndPoint = oTestOpen.vbCreateEndPoint(CLENDPOINT)
   If (oTestEndPoint is Nothing) Then
      Exit Function
   End If
 
   If (oTestEndPoint.vbOpenCommunicationChannel(SIMPLE_SEND_COMM_MGR, _
         NDISTEST_CONSTRUCTOR, NDIS_MEDIUM_802_3_MEDIA_MODULE) <> 0) Then
      Exit Function
   End If

   Set oSuppCard = New CLanCard6
   If (oSuppCard is Nothing) Then
      Exit Function
   End If
   
   Set oSuppOpen = oSuppCard.vbSetupBasicTest(pAdapterList (lSuppAdapterIndex))
   If (oSuppOpen is Nothing) Then
      Exit Function
   End If
 
   Set oSuppEndPoint = oSuppOpen.vbCreateEndPoint(CLENDPOINT)
   If (oSuppEndPoint is Nothing) Then
      Exit Function
   End If
 
   If (oSuppEndPoint.vbOpenCommunicationChannel(SIMPLE_SEND_COMM_MGR, _
         NDISTEST_CONSTRUCTOR, NDIS_MEDIUM_802_3_MEDIA_MODULE) <> 0) Then
      Exit Function
   End If

   Call oSuppOpen.vbSetPacketFilter(DIRECTED)
     
   DestAddr = oSuppOpen.vbGetCardAddress
   nReceiveDelay = oSuppOpen.vbGetReceiveDelay
   
   
       ' Create the various config objects to be used
   Set oSendCommMgrConfig = oCoreFactory.CommMgrSendConfig(oTestEndPoint.CommMgrType)
   Set oSendNBConfig = oCoreFactory.ConstructorSendConfig(oTestEndPoint.ConstructorType)
   Set oSendMediaConfig = oCoreFactory.MediaModuleSendConfig(oTestEndPoint.MediaModuleType)
   
       ' Create the various config obects to be used
   Set oRecvCommMgrConfig = oCoreFactory.CommMgrRecvConfig(oSuppEndPoint.CommMgrType)      
   Set oRecvNBConfig = oCoreFactory.ConstructorRecvConfig(oSuppEndPoint.ConstructorType)
   Set oRecvMediaConfig = oCoreFactory.MediaModuleRecvConfig(oSuppEndPoint.MediaModuleType)
   
   
   ' Object to obtain send results from the test card
   Set oSendCommMgrStats = oCoreFactory.CommMgrSendStatistics(oTestEndPoint.CommMgrType)
   
   oSendCommMgrConfig.NumSends = nTotalNumCallsToSend
   '	oSendCommMgrConfig.SendDuration = nSendDuration
   oSendCommMgrConfig.InitialBurstSize = nInitialBurstSize
   
   oSendNBConfig.NumNBLToPreallocate = nInitialBurstSize
   
   ' We want to send to a random destination address
   oSendMediaConfig.DestinationAddress = DestAddr
   
   oSendCommMgrConfig.NumNetBufferListsPerSend = nNumNetBufferListsPerSend
   oSendNBConfig.NumNetBuffersPerNetBufferList = nNumNetBuffersPerNBL
   oSendNBConfig.NetBufferSize = nNetBufferSize
   oSendNBConfig.MaxMdlSize = nMaxMdlSize
   
  
   Status = oSuppEndPoint.vbStartReceive(oRecvCommMgrConfig, oRecvNBConfig, oRecvMediaConfig)
   
   ' Start sending on the open
   Status = oTestEndPoint.vbSendNetBufferLists(oSendCommMgrConfig, oSendNBConfig, oSendMediaConfig)
   If (Status <> 0) then
    Call oLog.Failed ("Failed to start send. Error " & Status, 88888)
   End If

	' Now, wait for the sending to complete on each open
	Status = oTestEndPoint.vbWaitForSendsToComplete(0)


	Status = oTestEndPoint.vbGetSendResults(oSendCommMgrStats, Nothing)
	If (Status <> 0) then
	 Call oLog.Failed ("Failed to get send results. Error " & Status, 88888)
	End If

	' Did all our sends complete?
	If (oSendCommMgrStats.TotalNetBufferListsSent > oSendCommMgrStats.TotalNetBufferListsSendCompleted) Then
	 Call oLog.Failed("Not all the Net Buffer Lists sent were completed", 88888)
	End If

	' Did all our sends complete successfully?
	If (oSendCommMgrStats.TotalNetBufferListsSendCompleted > oSendCommMgrStats.TotalNetBufferListSendsSuccessful) Then
	 Call oLog.Failed("Not all the Net Buffer Lists sent were completed successfully", 88888)
	End If

	WScript.Sleep nReceiveDelay

	' Stop receiving
	Status = oSuppEndPoint.vbStopReceive()
	If (Status <> 0) Then
		Call oLog.Failed ("Failed to stop receive. Error " & Status, 88888)
	End If

	' Obtain receive results from the test card
	Dim oRecvCommMgrStats, oRecvNBStats
	Set oRecvCommMgrStats = oCoreFactory.CommMgrRecvStatistics(oSuppEndPoint.CommMgrType)  
	Set oRecvNBStats = oCoreFactory.ConstructorRecvStatistics(oSuppEndPoint.ConstructorType)  

	Status = oSuppEndPoint.vbGetReceiveResults(oRecvCommMgrStats, oRecvNBStats)
	If (Status <> 0) Then
		Call oLog.Failed ("Failed to get receive results. Error " & Status, 88888)
	End If


    If (oRecvNBStats.TotalNetBufferListsReceived = 0) Then
        oLog.Warned ("Check that the Support and Test Card are connected")        
    ElseIf (oRecvNBStats.TotalNetBufferListsReceived < oSendCommMgrStats.TotalNetBufferListSendsSuccessful) Then
		oLog.Warned ("Received fewer Net Buffers than sent")
	ElseIf (oRecvNBStats.TotalNetBuffersAccepted < oSendCommMgrStats.TotalNetBufferListSendsSuccessful) Then
		oLog.Warned ("The sent Net Buffers were corrupted during communication")
	End If

    Call oSuppOpen.vbSetPacketFilter(CLng(0))

	Call oTestOpen.vbClearEvents()
    Call oSuppOpen.vbClearEvents()



End Function

'<!-- CRC = 0x40a98f81 --->
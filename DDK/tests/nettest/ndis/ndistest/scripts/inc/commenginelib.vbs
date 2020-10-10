

Function FindCommEngineStatisticsObject(oArrStatistics, NumStatistics, ObjectClass, ObjectType)
   Dim oStat

   ' Search through the send statistics list for the one we are interested in
   For Each oStat In oArrStatistics
      If ((oStat.ObjectClass = ObjectClass) And _
          (oStat.ObjectType = ObjectType)) Then
         ' This is the object we are interested
         Set FindCommEngineStatisticsObject = oStat
         Exit Function
      End If
   Next
   ' If not found, return Nothing
   Set FindCommEngineStatisticsObject = Nothing
End Function


Class CSimpleTrafficHelper
   Dim m_oOpen
   Dim m_oEndPoint
   Dim m_NetBuffersSentPerNetBufferList

   Dim TestId
   Dim InitialBurstSize
   Dim InterSendDelay
   Dim MaxMdlSize

   Sub Class_Initialize
      Set m_oOpen = Nothing
      Set m_oEndPoint = Nothing

      m_NetBuffersSentPerNetBufferList = 0

      ' By default, we set the test id to zero, so it is recommended
      ' that the caller sets this value
      TestId = 0

      ' By default, we would use the InitialBurst size same as
      ' the value of NumNetBufferListsPer call to sends
      InitialBurstSize = 0

      ' By default, use a 10 millisecond delay between each
      ' call to NdisSend
      InterSendDelay = 10

      ' By default, we use the same value as the MDL size
      ' as the packet size (ie complete packet in one MDL)
      MaxMdlSize = 0

   End Sub

   Sub Class_Terminate
      Set m_oOpen = Nothing
      Set m_oEndPoint = Nothing
   End Sub

   Function vbSetupForCommunication(oOpen, EndPointType)
      Dim oEndPoint
      Dim StackModuleList(5)
      Dim NumStackModules
      Dim Status

      ' We return status to the callers
      vbSetupForCommunication = NDIS_STATUS_FAILURE

      ' Create the endpoint object
      Set oEndPoint = oOpen.vbCreateEndPoint(EndPointType)
      If (oEndPoint is Nothing) Then
         Exit Function
      End If

      ' Create the endpoint object
      StackModuleList(0) = CLng(SIMPLE_NB_ALLOCATOR_MODULE)
      StackModuleList(1) = CLng(SIMPLE_NDISTEST_PAYLOAD_MODULE)
      StackModuleList(2) = CLng(NDISTEST_HEADER_MODULE)
      StackModuleList(3) = CLng(LLC_SNAP_HEADER_MODULE)
      StackModuleList(4) = CLng(ETHERNET_MEDIA_HEADER_MODULE)
      NumStackModules = 5

      Status = oEndPoint.vbOpenCommunicationChannel(SIMPLE_TRAFFIC_MGR, _
            SIMPLE_NB_MODULE_STACK, StackModuleList, NumStackModules)

      If (Status <> 0) Then
         Set oEndPoint = Nothing
         Exit Function
      End If

      Set m_oOpen = oOpen
      Set m_oEndPoint = oEndPoint
      vbSetupForCommunication = Status
   End Function

   Function vbStartSend(DestinationAddress, PacketSize, _
      NumNetBufferListsPerSend, NumNetBuffersPerNetBufferList, _
      NumCallsToSend, SendDuration)

      Dim Status
      Dim oSendTrafficMgrConfig, oSendModuleStackConfig, oModuleSendConfig
      Dim CurrInitialBurstSize, CurrMaxMdlSize

      Do
         ' If user hasnt explicitly set the initial burst size, use
         ' the same as the num NBLs per send
         If (InitialBurstSize = 0) Then
            CurrInitialBurstSize = NumNetBufferListsPerSend
         Else
            CurrInitialBurstSize = InitialBurstSize
         End If

         ' Same for MaxMdl Size (if not set, use the same as the
         ' packet size)
         If (MaxMdlSize = 0) Then
            CurrMaxMdlSize = PacketSize
         Else
            CurrMaxMdlSize = MaxMdlSize
         End If

         ' Create config objects and configure the various modules
         Set oModuleSendConfig = oCoreFactory.NetBufferModuleSendConfig(SIMPLE_NB_ALLOCATOR_MODULE)
         If (oModuleSendConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         oModuleSendConfig.NumNetBuffersToPreallocate = NumNetBufferListsPerSend
         Status = m_oEndPoint.vbSendConfigureModule(0, SIMPLE_NB_ALLOCATOR_MODULE, oModuleSendConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         Set oModuleSendConfig = oCoreFactory.NetBufferModuleSendConfig(SIMPLE_NDISTEST_PAYLOAD_MODULE)
         If (oModuleSendConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         oModuleSendConfig.MaxMdlSize = CurrMaxMdlSize
         oModuleSendConfig.NetBufferSize = PacketSize
         Status = m_oEndPoint.vbSendConfigureModule(1, SIMPLE_NDISTEST_PAYLOAD_MODULE, oModuleSendConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         Set oModuleSendConfig = oCoreFactory.NetBufferModuleSendConfig(NDISTEST_HEADER_MODULE)
         If (oModuleSendConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         oModuleSendConfig.TestId = TestId
         Status = m_oEndPoint.vbSendConfigureModule(2, NDISTEST_HEADER_MODULE, oModuleSendConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         Set oModuleSendConfig = oCoreFactory.NetBufferModuleSendConfig(ETHERNET_MEDIA_HEADER_MODULE)
         If (oModuleSendConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         oModuleSendConfig.DestinationAddress = DestinationAddress
         Status = m_oEndPoint.vbSendConfigureModule(4, ETHERNET_MEDIA_HEADER_MODULE, oModuleSendConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         Set oSendTrafficMgrConfig = oCoreFactory.TrafficMgrSendConfig(m_oEndPoint.TrafficMgrType)
         If (oModuleSendConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         Set oSendModuleStackConfig = oCoreFactory.NBModuleStackSendConfig(m_oEndPoint.NBModuleStackType)
         If (oModuleSendConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If

         oSendTrafficMgrConfig.NumSends = NumCallsToSend
         oSendTrafficMgrConfig.SendDuration = SendDuration
         oSendTrafficMgrConfig.NumNetBufferListsPerSend = NumNetBufferListsPerSend
         oSendTrafficMgrConfig.NumNetBuffersPerNetBufferList = NumNetBuffersPerNetBufferList
         oSendTrafficMgrConfig.InitialBurstSize = CurrInitialBurstSize

         ' Store the NBs per NBL for later
         m_NetBuffersSentPerNetBufferList = NumNetBuffersPerNetBufferList

         ' Num of net buffer lists to allocate would be the same as the
         ' number we would require (ie. no outstanding NBLs during each call)
         oSendModuleStackConfig.NumNBLToPreallocate = CurrInitialBurstSize

         Status = m_oEndPoint.vbSendNetBufferLists(oSendTrafficMgrConfig, oSendModuleStackConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If
      Loop While(FALSE)

      If (Status <> NDIS_STATUS_SUCCESS) Then
         Call oLog.Failed("StartSend failed", 88888)
         oLog.Write("This is possibly an internal NDISTest error")
      End If

      ' Return the status
      vbStartSend = Status

   End Function

   Function vbWaitForSendsToComplete()
      vbWaitForSendsToComplete = m_oEndPoint.vbWaitForSendsToComplete(0)
      If (vbWaitForSendsToComplete <> NDIS_STATUS_SUCCESS) Then
         Call oLog.Failed("Failed waiting for sends to complete", 88888)
         oLog.Write("Possible reasons for this failure:")
         oLog.Write("1. A previous operation (StartSend, etc) had failed")
         oLog.Write("2. Net Buffer Lists sent are pending and havent been completed")
      End If
   End Function

   Function vbStopSend()
      vbStopSend = m_oEndPoint.vbStopSend(0)
      If (vbStopSend <> NDIS_STATUS_SUCCESS) Then
         Call oLog.Failed("Unable to stop send test", 88888)
         oLog.Write("Possible reasons for this failure:")
         oLog.Write("1. A previous operation (StartSend, etc) had failed")
         oLog.Write("2. Net Buffer Lists sent are pending and havent been completed")
      End If
   End Function

   Function vbGetSendResults(ByRef NetBuffersSent, _
      ByRef NetBufferListSendAttempted, ByRef NetBufferListsSentSuccessfully)

      Dim Status
      Dim oArrSendStatistics, NumSendStatistics
      Dim oSendStat

      Do
         ' Collect the send statistics
         Status = m_oEndPoint.vbGetSendResults(oArrSendStatistics, NumSendStatistics)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         ' Find the traffic manager statistics
         Set oSendStat = FindCommEngineStatisticsObject(oArrSendStatistics, NumSendStatistics, _
            TRAFFIC_MANAGER_OBJECT_CLASS, SIMPLE_TRAFFIC_MGR)
         If (oSendStat is Nothing) Then
            Status = NDIS_STATUS_FAILURE
            Exit Do
         End If

         ' Store the statistics for the caller
         NetBufferListSendAttempted = oSendStat.TotalNetBufferListsSent
         NetBufferListsSentSuccessfully = oSendStat.TotalNetBufferListSendsSuccessful

         ' The number of NET_BUFFERs we sent is obtained from the number of NET_BUFFER_LISTS
         NetBuffersSent = m_NetBuffersSentPerNetBufferList * oSendStat.TotalNetBufferListSendsSuccessful

         Status = NDIS_STATUS_SUCCESS
      Loop While(FALSE)

      If (Status <> NDIS_STATUS_SUCCESS) Then
         Call oLog.Failed("GetSendResults failed", 88888)
         oLog.Write("This is possibly an internal NDISTest error")
      End If

      vbGetSendResults = Status
   End Function

   Function vbStartReceive()
      Dim Status
      Dim oRecvTrafficMgrConfig, oRecvModuleStackConfig, oModuleRecvConfig

      Do
         ' Create config objects and configure the various modules
         Set oModuleRecvConfig = oCoreFactory.NetBufferModuleRecvConfig(NDISTEST_HEADER_MODULE)
         If (oModuleRecvConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         oModuleRecvConfig.TestId = TestId
         Status = m_oEndPoint.vbReceiveConfigureModule(2, NDISTEST_HEADER_MODULE, oModuleRecvConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         Set oModuleRecvConfig = oCoreFactory.NetBufferModuleRecvConfig(ETHERNET_MEDIA_HEADER_MODULE)
         If (oModuleRecvConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         Status = m_oEndPoint.vbReceiveConfigureModule(4, ETHERNET_MEDIA_HEADER_MODULE, oModuleRecvConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         Set oRecvTrafficMgrConfig = oCoreFactory.TrafficMgrRecvConfig(m_oEndPoint.TrafficMgrType)
         If (oModuleRecvConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         Set oRecvModuleStackConfig = oCoreFactory.NBModuleStackRecvConfig(m_oEndPoint.NBModuleStackType)
         If (oModuleRecvConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If

         ' Configure the receive traffic manager and stack and start receives
         Status = m_oEndPoint.vbStartReceive(oRecvTrafficMgrConfig, oRecvModuleStackConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If
      Loop While(FALSE)

      If (Status <> NDIS_STATUS_SUCCESS) Then
         Call oLog.Failed("StartReceive failed", 88888)
         oLog.Write("This is possibly an internal NDISTest error")
      End If

      ' Return the status
      vbStartReceive = Status
   End Function

   Function vbStopReceive()
      vbStopReceive = m_oEndPoint.vbStopReceive()
      If (vbStopReceive <> NDIS_STATUS_SUCCESS) Then
         Call oLog.Failed("Unable to stop receive test", 88888)
         oLog.Write("This could be because a previous operation (StartReceive, etc) had failed")
      End If
   End Function

   Function vbGetReceiveResults(ByRef NumValidNetBuffersReceived, ByRef NumInvalidNetBuffersReceived)
      Dim Status
      Dim oArrRecvStatistics, NumRecvStatistics
      Dim oRecvStat

      Do
         ' Collect the recv statistics
         Status = m_oEndPoint.vbGetReceiveResults(oArrRecvStatistics, NumRecvStatistics)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         ' Find the NDISTest header statistics
         Set oRecvStat = FindCommEngineStatisticsObject(oArrRecvStatistics, NumRecvStatistics, _
            NET_BUFFER_MODULE_OBJECT_CLASS, NDISTEST_HEADER_MODULE)
         If (oRecvStat is Nothing) Then
            Status = NDIS_STATUS_FAILURE
            Exit Do
         End If

         ' Corrupted header and out of order receives are considered invalid
         NumInvalidNetBuffersReceived = oRecvStat.TotalNetBuffersCorrupted _
            + oRecvStat.OutOfOrderNetBuffersReceived

         ' Get the payload statistics
         Set oRecvStat = FindCommEngineStatisticsObject(oArrRecvStatistics, NumRecvStatistics, _
            NET_BUFFER_MODULE_OBJECT_CLASS, SIMPLE_NDISTEST_PAYLOAD_MODULE)
         If (oRecvStat is Nothing) Then
            Status = NDIS_STATUS_FAILURE
            Exit Do
         End If

         ' Add the corrupted packets to our total list
         NumInvalidNetBuffersReceived = oRecvStat.TotalNetBuffersCorrupted

         ' The number of Net buffers we accepted
         NumValidNetBuffersReceived = oRecvStat.TotalNetBuffersAccepted

         Status = NDIS_STATUS_SUCCESS
      Loop While(FALSE)

      If (Status <> NDIS_STATUS_SUCCESS) Then
         Call oLog.Failed("GetReceiveResults failed", 88888)
         oLog.Write("This is possibly an internal NDISTest error")
      End If

      vbGetReceiveResults = Status
   End Function

End Class

'================================================================
Class CStressTrafficHelper
   Dim m_oOpen
   Dim m_oEndPoint
   Dim TestId, NumNBLsToPreallocate
   '=============================================================
   Dim CallsToSend
   Dim NetBuffersSentAtPassive
   Dim NetBuffersSentAtDispatch
   '=============================================================
   Dim NetBuffersPadded, NetBuffersCorrupted, NetBuffersOutOfOrder
   '=============================================================
   Sub Class_Initialize
      Set m_oOpen = Nothing
      Set m_oEndPoint = Nothing

      '=============================================================
      ' By default, we set the test id to zero, so it is recommended
      ' that the caller sets this value
      TestId = 0

      NumNBLsToPreallocate = 100
      '=============================================================      
   End Sub

   Sub Class_Terminate
      Set m_oOpen = Nothing
      Set m_oEndPoint = Nothing
   End Sub

   Function vbSetupForCommunication(oOpen, EndPointType)
      Dim oEndPoint
      Dim StackModuleList(5)
      Dim NumStackModules
      Dim Status

      ' We return status to the callers
      vbSetupForCommunication = NDIS_STATUS_FAILURE

      ' Create the endpoint object
      Set oEndPoint = oOpen.vbCreateEndPoint(EndPointType)
      If (oEndPoint is Nothing) Then
         Exit Function
      End If

      ' Create the endpoint object
      StackModuleList(0) = CLng(EMPTY_NB_ALLOCATOR_MODULE)
      StackModuleList(1) = CLng(STRESS_PAYLOAD_MODULE)
      StackModuleList(2) = CLng(NDISTEST_HEADER_MODULE)
      StackModuleList(3) = CLng(LLC_SNAP_HEADER_MODULE)
      StackModuleList(4) = CLng(ETHERNET_MEDIA_HEADER_MODULE)
      NumStackModules = 5

      Status = oEndPoint.vbOpenCommunicationChannel(STRESS_TRAFFIC_MGR, _
            SIMPLE_NB_MODULE_STACK, StackModuleList, NumStackModules)

      If (Status <> 0) Then
         Set oEndPoint = Nothing
         Exit Function
      End If

      Set m_oOpen = oOpen
      Set m_oEndPoint = oEndPoint
      vbSetupForCommunication = Status
   End Function

   Function vbStartSend(DestinationAddress, _
      oStressTrafficManagerConfig, oStressPayloadModuleConfig _
      )
      
      Dim Status
      Dim oSendModuleStackConfig, oModuleSendConfig

      Do
         ' Create config objects and configure the various modules

         ' EMPTY_NB_ALLOCATOR does not need to be send configured

         ' stress payload module, the complete configuration comes from stress structure
         Status = m_oEndPoint.vbSendConfigureModule(1, STRESS_PAYLOAD_MODULE, _
            oStressPayloadModuleConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         Set oModuleSendConfig = oCoreFactory.NetBufferModuleSendConfig(NDISTEST_HEADER_MODULE)
         If (oModuleSendConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         oModuleSendConfig.TestId = TestId
         Status = m_oEndPoint.vbSendConfigureModule(2, NDISTEST_HEADER_MODULE, oModuleSendConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         Set oModuleSendConfig = oCoreFactory.NetBufferModuleSendConfig(ETHERNET_MEDIA_HEADER_MODULE)
         If (oModuleSendConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         oModuleSendConfig.DestinationAddress = DestinationAddress
         Status = m_oEndPoint.vbSendConfigureModule(4, ETHERNET_MEDIA_HEADER_MODULE, oModuleSendConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         Set oSendModuleStackConfig = oCoreFactory.NBModuleStackSendConfig(m_oEndPoint.NBModuleStackType)
         If (oModuleSendConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If

         oSendModuleStackConfig.NumNBLToPreallocate = NumNBLsToPreallocate
         
         Status = m_oEndPoint.vbSendNetBufferLists(oStressTrafficManagerConfig, oSendModuleStackConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If
      Loop While(FALSE)

      If (Status <> NDIS_STATUS_SUCCESS) Then
         Call oLog.SafeFailed("StartSend failed", 88888)
         oLog.Write("This may be because of a bad test parameter (bad config)")
      End If

      ' Return the status
      vbStartSend = Status

   End Function

   Function vbStartAllSends()
      vbStartAllSends = m_oEndPoint.vbStartAllSends()
   End Function

   Function vbWaitForSendsToComplete()
      vbWaitForSendsToComplete = m_oEndPoint.vbWaitForSendsToComplete(0)
      If (vbWaitForSendsToComplete <> NDIS_STATUS_SUCCESS) Then
         Call oLog.Failed("Failed waiting for sends to complete", 88888)
         oLog.Write("Possible reasons for this failure:")
         oLog.Write("1. A previous operation (StartSend, etc) had failed")
         oLog.Write("2. Net Buffer Lists sent are pending and havent been completed")
      End If
   End Function

   Function vbStopSend()
      vbStopSend = m_oEndPoint.vbStopSend(0)
      If (vbStopSend <> NDIS_STATUS_SUCCESS) Then
         Call oLog.SafeFailed("Unable to stop send test", 88888)
         oLog.Write("Possible reasons for this failure:")
         oLog.Write("1. Net Buffer Lists sent are pending and havent been completed")
         oLog.Write("2. A previous operation (StartSend, etc) had failed")
      End If
   End Function

   Function vbGetSendResults(ByRef NetBuffersSent, _
      ByRef NetBufferListSendAttempted, ByRef NetBufferListsSentSuccessfully)

      Dim Status
      Dim oArrSendStatistics, NumSendStatistics
      Dim oSendStat

      Do
         ' Collect the send statistics
         Status = m_oEndPoint.vbGetSendResults(oArrSendStatistics, NumSendStatistics)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         ' Find the traffic manager statistics
         Set oSendStat = FindCommEngineStatisticsObject(oArrSendStatistics, NumSendStatistics, _
            TRAFFIC_MANAGER_OBJECT_CLASS, STRESS_TRAFFIC_MGR)
         If (oSendStat is Nothing) Then
            Status = NDIS_STATUS_FAILURE
            Exit Do
         End If

         ' Store the statistics for the caller
         NetBufferListSendAttempted = oSendStat.TotalNetBufferListsSent
         NetBufferListsSentSuccessfully = oSendStat.TotalNetBufferListSendsSuccessful
         NetBuffersSent = oSendStat.TotalNetBuffersSent

         CallsToSend = oSendStat.TotalCallsToSend
         NetBuffersSentAtPassive = oSendStat.TotalNetBuffersSentAtPassive
         NetBuffersSentAtDispatch = oSendStat.TotalNetBuffersSentAtDispatch

         Status = NDIS_STATUS_SUCCESS
      Loop While(FALSE)

      If (Status <> NDIS_STATUS_SUCCESS) Then
         Call oLog.SafeFailed("GetSendResults failed", 88888)
         oLog.Write("This is possibly an internal NDISTest error")
      End If

      vbGetSendResults = Status
   End Function

   Function vbStartReceive(VerificationLevel)
      Dim Status
      Dim oRecvTrafficMgrConfig, oRecvModuleStackConfig, oModuleRecvConfig
      Dim PayloadVerificationLevel, HeaderVerificationLevel

      Do
         ' Create config objects and configure the various modules
         Set oModuleRecvConfig = oCoreFactory.NetBufferModuleRecvConfig(STRESS_PAYLOAD_MODULE)
         If (oModuleRecvConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If

         ' Determine what we all will be verifying
         PayloadVerificationLevel = 0
         If ((VerificationLevel And fNDT_NB_MODULE_CHECK_NDISTEST_DATA) <> 0) Then
            ' Verify NDISTest pattern has not been corrupted
            PayloadVerificationLevel = PayloadVerificationLevel Or fNDT_NB_MODULE_CHECK_NDISTEST_DATA
         End If

         If ((VerificationLevel And fNDT_STRESS_MODULE_CHECK_PAYLOAD_LENGTH) <> 0) Then
            ' Keep statistics on number of NET_BUFFERs that have been padded
            PayloadVerificationLevel = PayloadVerificationLevel Or fNDT_STRESS_MODULE_CHECK_PAYLOAD_LENGTH            
         End If         
         oModuleRecvConfig.VerificationLevel = PayloadVerificationLevel
         
         Status = m_oEndPoint.vbReceiveConfigureModule(1, STRESS_PAYLOAD_MODULE, oModuleRecvConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If
         
         Set oModuleRecvConfig = oCoreFactory.NetBufferModuleRecvConfig(NDISTEST_HEADER_MODULE)
         If (oModuleRecvConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If

         HeaderVerificationLevel = 0
         If ((VerificationLevel And fNDT_NB_MODULE_CHECK_NDISTEST_HEADER) <> 0) Then
            ' Verify NDISTest header has not been corrupted
            HeaderVerificationLevel = HeaderVerificationLevel Or fNDT_NB_MODULE_CHECK_NDISTEST_HEADER
         End If

         If ((VerificationLevel And fNDT_NB_MODULE_CHECK_SEQUENCE_NUMBER) <> 0) Then
            ' Verify NDISTest packets are received in sequence (no drops, no out of order receives)
            HeaderVerificationLevel = HeaderVerificationLevel Or fNDT_NB_MODULE_CHECK_SEQUENCE_NUMBER            
         End If
         
         oModuleRecvConfig.TestId = TestId
         oModuleRecvConfig.VerificationLevel = HeaderVerificationLevel
         Status = m_oEndPoint.vbReceiveConfigureModule(2, NDISTEST_HEADER_MODULE, oModuleRecvConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         Set oModuleRecvConfig = oCoreFactory.NetBufferModuleRecvConfig(ETHERNET_MEDIA_HEADER_MODULE)
         If (oModuleRecvConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         Status = m_oEndPoint.vbReceiveConfigureModule(4, ETHERNET_MEDIA_HEADER_MODULE, oModuleRecvConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         Set oRecvTrafficMgrConfig = oCoreFactory.TrafficMgrRecvConfig(m_oEndPoint.TrafficMgrType)
         If (oModuleRecvConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If
         Set oRecvModuleStackConfig = oCoreFactory.NBModuleStackRecvConfig(m_oEndPoint.NBModuleStackType)
         If (oModuleRecvConfig is Nothing) Then
            Status = NDIS_STATUS_RESOURCES
            Exit Do
         End If

         ' Configure the receive traffic manager and stack and start receives
         Status = m_oEndPoint.vbStartReceive(oRecvTrafficMgrConfig, oRecvModuleStackConfig)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If
      Loop While(FALSE)

      If (Status <> NDIS_STATUS_SUCCESS) Then
         Call oLog.SafeFailed("StartReceive failed", 88888)
         oLog.Write("This may be because of a bad test parameter (bad config)")
      End If

      ' Return the status
      vbStartReceive = Status
   End Function

   Function vbStopReceive()
      vbStopReceive = m_oEndPoint.vbStopReceive()
      If (vbStopReceive <> NDIS_STATUS_SUCCESS) Then
         Call oLog.SafeFailed("Unable to stop receive test", 88888)
         oLog.Write("This could be because a previous operation (StartReceive, etc) had failed")
      End If
   End Function

   Function vbGetReceiveResults(ByRef ValidNetBuffersReceived, ByRef InvalidNetBuffersReceived)
      Dim Status
      Dim oArrRecvStatistics, NumRecvStatistics
      Dim oRecvStat

      Do
         ' Collect the recv statistics
         Status = m_oEndPoint.vbGetReceiveResults(oArrRecvStatistics, NumRecvStatistics)
         If (Status <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If

         ' Find the NDISTest header statistics
         Set oRecvStat = FindCommEngineStatisticsObject(oArrRecvStatistics, NumRecvStatistics, _
            NET_BUFFER_MODULE_OBJECT_CLASS, NDISTEST_HEADER_MODULE)
         If (oRecvStat is Nothing) Then
            Status = NDIS_STATUS_FAILURE
            Exit Do
         End If

         ' Corrupted header and out of order receives are considered invalid
         InvalidNetBuffersReceived = oRecvStat.TotalNetBuffersCorrupted _
            + oRecvStat.OutOfOrderNetBuffersReceived
         NetBuffersCorrupted = oRecvStat.TotalNetBuffersCorrupted
         NetBuffersOutOfOrder = oRecvStat.OutOfOrderNetBuffersReceived

         ' Get the payload statistics
         Set oRecvStat = FindCommEngineStatisticsObject(oArrRecvStatistics, NumRecvStatistics, _
            NET_BUFFER_MODULE_OBJECT_CLASS, STRESS_PAYLOAD_MODULE)
         If (oRecvStat is Nothing) Then
            Status = NDIS_STATUS_FAILURE
            Exit Do
         End If

         ' Add the corrupted packets to our total list
         InvalidNetBuffersReceived = InvalidNetBuffersReceived + oRecvStat.TotalNetBuffersCorrupted
         NetBuffersCorrupted = NetBuffersCorrupted + oRecvStat.TotalNetBuffersCorrupted
         
         ' The number of Net buffers we accepted
         ValidNetBuffersReceived = oRecvStat.TotalNetBuffersAccepted

         NetBuffersPadded = oRecvStat.TotalNetBuffersPadded

         Status = NDIS_STATUS_SUCCESS
      Loop While(FALSE)

      If (Status <> NDIS_STATUS_SUCCESS) Then
         Call oLog.SafeFailed("GetReceiveResults failed", 88888)
         oLog.Write("This is possibly an internal NDISTest error")
      End If

      vbGetReceiveResults = Status
   End Function

End Class



'<!-- CRC = 0x81951745 --->
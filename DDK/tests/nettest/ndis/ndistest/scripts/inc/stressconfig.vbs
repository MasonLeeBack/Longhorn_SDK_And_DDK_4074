' Different types of MDL chain allocators
Const STRESS_SIMPLE_MDL_CHAIN_ALLOCATOR      = 1

' Different types of data filler objects
Const STRESS_NORMAL_PATTERN_MAPPING_FILLER   = 1
Const STRESS_PAGE_END_PATTERN_MAPPING_FILLER = 2
Const STRESS_MIXED_PATTERN_MAPPING_FILLER    = 3

' Different types of length fragmenters
Const STRESS_FIXED_LENGTH_FRAGMENTER         = 1
Const STRESS_FIXED_COUNT_FRAGMENTER          = 2
Const STRESS_RANDOM_LENGTH_FRAGMENTER        = 3
Const STRESS_RANDOM_COUNT_FRAGMENTER         = 4
Const STRESS_BIASED_RANDOM_LENGTH_FRAGMENTER = 5

' Different types of length providers
Const STRESS_FIXED_LENGTH_PROVIDER           = 1
Const STRESS_RANDOM_LENGTH_PROVIDER          = 2
Const STRESS_CYCLIC_LENGTH_PROVIDER          = 3

' Different types of NET_BUFFER pad helpers
Const STRESS_DUMMY_NET_BUFFER_PAD_HELPER           = 1
Const STRESS_FIXED_LENGTH_NET_BUFFER_PAD_HELPER    = 2
Const STRESS_RANDOM_LENGTH_NET_BUFFER_PAD_HELPER   = 3

' Stress configuration default values
' This is the default length of data we send out
Const STRESS_DEFAULT_PAYLOAD_LENGTH          = 100

' This is the default length of an MDL
Const STRESS_DEFAULT_MDL_SIZE                = 60

' This is the default number of MDLs we would use 
Const STRESS_DEFAULT_MDL_COUNT               = 5

' This is the default maximum length of a MDL
Const STRESS_MAX_MDL_SIZE_DEFAULT            = 200

' This is the maximum number of MDLs desired
Const STRESS_MAX_MDL_COUNT_DEFAULT           = 20

'=============================================================
' CStressTrafficManagerSendConfig
'=============================================================
Class CStressTrafficManagerSendConfig
   Dim   m_oCOMConfig
   Dim   m_nMaxPendingNetBuffers
   
   Sub Class_Initialize
      ' Create the core config object
      Set m_oCOMConfig = CreateObject("NDTCore6.StressTrafficMgrSendConfig.1")
      
      ' Initialize with defaults
      ResetConfig
   End Sub
   
   Sub Class_Terminate
      Set m_oCOMConfig = Nothing
   End Sub

   Public Property Get COMConfig
      Set COMConfig = m_oCOMConfig
   End Property

   Public Sub ResetConfig
      ' Initialize the default parameters in the config object
      SendMechanism = SEND_AT_PASSIVE     ' Send mechanism is to send at passive
      NdisSendFlags = 0                   ' No flags to NdisSend

      MinimumNetBufferListsPerSend = 1        ' Minimum 1 NBL per NdisSend
      MinimumNetBuffersPerNetBufferList = 1   ' Minimum 1 NB per NBL

      MaximumPendingNetBuffers = 400      ' Default allow max 400 NET_BUFFERs pending at any time
      
      SynchronousStart = FALSE            ' Do not do synchronous start
      SendLatency = 0                     ' Start sending when ready

      InterSendDelay = 0                  ' No delays between 2 calls to send
      SendCompleteTimeout = 10000         ' With pending sendcompletes, expect atleast one
   End Sub

   Public Property Let SendMechanism (nNewVal)
      m_oCOMConfig.SendMechanism = nNewVal
   End Property

   Public Property Let NdisSendFlags (nNewVal)
      m_oCOMConfig.NdisSendFlags = nNewVal
   End Property

   Public Property Let MinimumNetBufferListsPerSend (nNewVal)
      m_oCOMConfig.MinimumNetBufferListsPerSend = nNewVal

   End Property

   Public Property Let MinimumNetBuffersPerNetBufferList (nNewVal)
      m_oCOMConfig.MinimumNetBuffersPerNetBufferList = nNewVal

   End Property

   Public Property Let MaximumPendingNetBuffers (nNewVal)
      m_nMaxPendingNetBuffers = nNewVal
      m_oCOMConfig.MaximumPendingNetBuffers = nNewVal
   End Property

   Public Property Let SynchronousStart (bNewVal)
      m_oCOMConfig.SynchronousStart = bNewVal
   End Property

   Public Property Let SendLatency (nNewTimeInms)
      m_oCOMConfig.SendLatency = nNewTimeInms
   End Property

   Public Property Let InterSendDelay (nNewTimeInms)
      m_oCOMConfig.InterSendDelay = nNewTimeInms
   End Property

   Public Property Let SendCompleteTimeout (nNewTimeInms)
      m_oCOMConfig.SendCompleteTimeout = nNewTimeInms
   End Property

   Public Function SendConfigure(MaxNetBufferListsPerSend, MaxNetBuffersPerNetBufferList, _
      NumCallsToSend, SendDuration)

      ' Do some basic validation of parameters
      If (m_nMaxPendingNetBuffers < (MaxNetBufferListsPerSend * MaxNetBuffersPerNetBufferList)) Then
         oLog.Write ("Maximum number of NET_BUFFERs that can pend < Number of NET_BUFFERs we can send in one call to NdisSend. Adjusting")
         MaximumPendingNetBuffers = (MaxNetBufferListsPerSend * MaxNetBuffersPerNetBufferList)         
      End If

      ' Store the remaining parameters
      m_oCOMConfig.NumSends = NumCallsToSend
      m_oCOMConfig.SendDuration = SendDuration
      m_oCOMConfig.MaximumNetBufferListsPerSend = MaxNetBufferListsPerSend
      m_oCOMConfig.MaximumNetBuffersPerNetBufferList = MaxNetBuffersPerNetBufferList      
   End Function
End Class

'=============================================================
' CStressPayloadSendConfig
'=============================================================
' This is the all encompassing stress config object that corresponds to
' the config object that goes the sys
Class CStressPayloadSendConfig
   Dim   m_oCOMConfig
   
   Sub Class_Initialize
      ' Create the core config object
      Set m_oCOMConfig = CreateObject("NDTCore6.StressPayloadSendConfig.1")
   End Sub
   
   Sub Class_Terminate
      Set m_oCOMConfig = Nothing
   End Sub

   Public Property Get COMConfig
      Set COMConfig = m_oCOMConfig
   End Property


   Public Property Set MDLChainAllocatorConfig(oConfig)
      oConfig.StoreConfiguration(m_oCOMConfig)
   End Property
   
   Public Property Set PayloadDataFillerConfig(oConfig)
      oConfig.StoreConfiguration(m_oCOMConfig)
   End Property

   Public Property Set MDLLengthFragmenterConfig(oConfig)
      oConfig.StoreConfiguration(m_oCOMConfig)
   End Property

   Public Property Set DataLengthProviderConfig(oConfig)
      oConfig.StoreConfiguration(m_oCOMConfig)
   End Property

   Public Property Set NetBufferPadHelperConfig(oConfig)
      oConfig.StoreConfiguration(m_oCOMConfig)
   End Property
End Class
'=============================================================
' Stress factory methods
'=============================================================
Function ConstructMDLChainAllocatorConfig(AllocatorType)
   Select Case AllocatorType
      Case STRESS_SIMPLE_MDL_CHAIN_ALLOCATOR
         Set ConstructMDLChainAllocatorConfig = New CSimpleMdlChainAllocatorConfig
      Case Else
         oLog.Write ("Invalid MDL chain allocator specified: " & AllocatorType)
         Set ConstructMDLChainAllocatorConfig = Nothing
   End Select
End Function

Function ConstructPayloadDataFillerConfig(FillerType)
   Select Case FillerType
      Case STRESS_NORMAL_PATTERN_MAPPING_FILLER
         Set ConstructPayloadDataFillerConfig = New CNormalMappingDataFillerConfig
      Case STRESS_PAGE_END_PATTERN_MAPPING_FILLER
         Set ConstructPayloadDataFillerConfig = New CPageEndMappingDataFillerConfig
      Case STRESS_MIXED_PATTERN_MAPPING_FILLER
         Set ConstructPayloadDataFillerConfig = New CMixedMappingDataFillerConfig
      Case Else
         oLog.Write ("Invalid payload data filler specified: " & FillerType)         
         Set ConstructPayloadDataFillerConfig = Nothing            
   End Select
End Function

Function ConstructMDLLengthFragmenterConfig(FragmenterType)
   Select Case FragmenterType
      Case STRESS_FIXED_LENGTH_FRAGMENTER
         Set ConstructMDLLengthFragmenterConfig = New CFixedLengthFragmenterConfig
      Case STRESS_FIXED_COUNT_FRAGMENTER
         Set ConstructMDLLengthFragmenterConfig = New CFixedCountFragmenterConfig
      Case STRESS_RANDOM_LENGTH_FRAGMENTER
         Set ConstructMDLLengthFragmenterConfig = New CRandomLengthFragmenterConfig
      Case STRESS_RANDOM_COUNT_FRAGMENTER
         Set ConstructMDLLengthFragmenterConfig = New CRandomCountFragmenterConfig
      Case STRESS_BIASED_RANDOM_LENGTH_FRAGMENTER
         Set ConstructMDLLengthFragmenterConfig = New CBiasedRandomLengthFragmenterConfig
      Case Else
         oLog.Write ("Invalid MDL length fragmenter specified: " & FragmenterType)         
         Set ConstructMDLLengthFragmenterConfig = Nothing            
   End Select

End Function

Function ConstructDataLengthProviderConfig(ProviderType)
   Select Case ProviderType
      Case STRESS_FIXED_LENGTH_PROVIDER
         Set ConstructDataLengthProviderConfig = New CFixedLengthProviderConfig
      Case STRESS_RANDOM_LENGTH_PROVIDER
         Set ConstructDataLengthProviderConfig = New CRandomLengthProviderConfig
      Case STRESS_CYCLIC_LENGTH_PROVIDER
         Set ConstructDataLengthProviderConfig = New CCyclicLengthProviderConfig
      Case Else
         oLog.Write ("Invalid data length provider specified: " & ProviderType)         
         Set ConstructDataLengthProviderConfig = Nothing            
   End Select

End Function

Function ConstructNetBufferPadHelperConfig(HelperType)
   Select Case HelperType
      Case STRESS_DUMMY_NET_BUFFER_PAD_HELPER
         Set ConstructNetBufferPadHelperConfig = New CDummyNetBufferPadHelperConfig
      Case STRESS_FIXED_LENGTH_NET_BUFFER_PAD_HELPER
         Set ConstructNetBufferPadHelperConfig = New CFixedNetBufferPadHelperConfig
      Case STRESS_RANDOM_LENGTH_NET_BUFFER_PAD_HELPER
         Set ConstructNetBufferPadHelperConfig = New CRandomNetBufferPadHelperConfig
      Case Else
         oLog.Write ("Invalid NET_BUFFER pad helper specified: " & HelperType)         
         Set ConstructNetBufferPadHelperConfig = Nothing            
   End Select

End Function
'=============================================================
' STRESS_MDL_CHAIN_ALLOCATOR_TYPE
'=============================================================
Class CSimpleMdlChainAllocatorConfig
   Dim NumNetBuffersToPreallocate
   
   Sub Class_Initialize
      NumNetBuffersToPreallocate = 1
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureSimpleMdlChainAllocator(NumNetBuffersToPreallocate)
   End Function
End Class


'=============================================================
' STRESS_DATA_FILLER_TYPE
'=============================================================
Class CNormalMappingDataFillerConfig
   Dim bCreateMdlMap
   Sub Class_Initialize
      bCreateMdlMap = FALSE
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureNormalMappingDataFiller(bCreateMdlMap)
   End Function
End Class

Class CPageEndMappingDataFillerConfig
   Dim bCreateMdlMap
   Sub Class_Initialize
      bCreateMdlMap = FALSE
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigurePageEndMappingDataFiller(bCreateMdlMap)
   End Function
End Class

Class CMixedMappingDataFillerConfig
   Dim bCreateMdlMap
   Sub Class_Initialize
      bCreateMdlMap = FALSE
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureMixedMappingDataFiller(bCreateMdlMap)
   End Function
End Class

'=============================================================
' STRESS_LENGTH_FRAGMENTER_TYPE
'=============================================================
Class CFixedLengthFragmenterConfig
   Dim Length
   Sub Class_Initialize
      Length = STRESS_DEFAULT_MDL_SIZE
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureFixedLengthFragmenter(Length)
   End Function
End Class

Class CFixedCountFragmenterConfig
   Dim Count
   Sub Class_Initialize
      Count = STRESS_DEFAULT_MDL_COUNT
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureFixedCountFragmenter(Count)
   End Function
End Class

Class CRandomLengthFragmenterConfig
   Dim MinLength, MaxLength, MaxCount
   
   Sub Class_Initialize
      MinLength = 0
      MaxLength = STRESS_MAX_MDL_SIZE_DEFAULT
      MaxCount = STRESS_MAX_MDL_COUNT_DEFAULT
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureRandomLengthFragmenter(MinLength, MaxLength, MaxCount)
   End Function
End Class


Class CRandomCountFragmenterConfig
   Dim MinCount, MaxCount

   Sub Class_Initialize
      MinCount = 1
      MaxCount = STRESS_MAX_MDL_COUNT_DEFAULT
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureRandomCountFragmenter(MinCount, MaxCount)
   End Function
End Class

Class CBiasedRandomLengthFragmenterConfig
   Dim BiasedLength, BiasThreshold
   Dim MaxLength, MaxCount

   Sub Class_Initialize
      BiasedLength = 1     ' 1 byte MDLs preferred
      BiasThreshold = 7    ' Use biased length when random number btw 0/10 is > 7 
      MaxLength = STRESS_MAX_MDL_SIZE_DEFAULT
      MaxCount = STRESS_MAX_MDL_COUNT_DEFAULT
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureBiasedRandomLengthFragmenter(BiasedLength, MaxLength, MaxCount, BiasThreshold)
   End Function
End Class

'=============================================================
' STRESS_LENGTH_PROVIDER_TYPE
'=============================================================
Class CFixedLengthProviderConfig
   Dim Length
   Sub Class_Initialize
      Length = STRESS_DEFAULT_PAYLOAD_LENGTH
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureFixedLengthProvider(Length)
   End Function
End Class

Class CRandomLengthProviderConfig
   Dim MinLength, MaxLength
   Sub Class_Initialize
      MinLength = 0
      MaxLength = STRESS_DEFAULT_PAYLOAD_LENGTH
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureRandomLengthProvider(MinLength, MaxLength)
   End Function
End Class

Class CCyclicLengthProviderConfig
   Dim MinLength, MaxLength
   Sub Class_Initialize
      MinLength = 0
      MaxLength = STRESS_DEFAULT_PAYLOAD_LENGTH
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureCyclicLengthProvider(MinLength, MaxLength)
   End Function
End Class

'=============================================================
' STRESS_NET_BUFFER_PAD_HELPER_TYPE
'=============================================================
Class CDummyNetBufferPadHelperConfig
   Sub Class_Initialize
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureDummyNetBufferPadHelper()
   End Function
End Class

Class CFixedNetBufferPadHelperConfig
   Dim DataMdlPrepadSize, DummyMdlPrepadSize
   Dim DataMdlPostpadSize, DummyMdlPostpadSize
   
   Sub Class_Initialize
      DataMdlPrepadSize = 0
      DummyMdlPrepadSize = 0
      DataMdlPostpadSize = 0
      DummyMdlPostpadSize = 0
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureFixedNetBufferPadHelper( _
         DataMdlPrepadSize, DummyMdlPrepadSize, _
         DataMdlPostpadSize, DummyMdlPostpadSize _
         )
   End Function
End Class

Class CRandomNetBufferPadHelperConfig
   Dim MaxDataMdlPrepadSize, MaxDummyMdlPrepadSize
   Dim MaxDataMdlPostpadSize, MaxDummyMdlPostpadSize
   
   Sub Class_Initialize
      MaxDataMdlPrepadSize = 0
      MaxDummyMdlPrepadSize = 0
      MaxDataMdlPostpadSize = 0
      MaxDummyMdlPostpadSize = 0
   End Sub

   ' Save the configuration in the main COM config object
   Function StoreConfiguration(oCOMConfig)
      StoreConfiguration = oCOMConfig.ConfigureRandomNetBufferPadHelper( _
         MaxDataMdlPrepadSize, MaxDummyMdlPrepadSize, _
         MaxDataMdlPostpadSize, MaxDummyMdlPostpadSize _
         )
   End Function
End Class
'=============================================================


'<!-- CRC = 0xa14f4105 --->
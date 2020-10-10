Option Explicit

Class CWin32_NetworkAdapter
   
   Private m_sComputer
   Private m_oWMIService
   Private m_oAdapters
   Private m_oAdapter
   Private m_nCurrent
   Private m_sQuery
     
   Private m_oCollection  
   '================================================================================================='
   Public Sub Class_Initialize()
      
      m_nCurrent        = 0
      m_sComputer       = "."
      m_sQuery          = "SELECT * FROM Win32_NetworkAdapter"
      
      Set m_oWMIService = Nothing
      Set m_oAdapters	= Nothing
      Set m_oAdapter    = Nothing      
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")
      Set m_oCollection = CreateObject("Scripting.Dictionary")
            
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
      
      Set m_oWMIService = Nothing
      Set m_oAdapters	= Nothing
      Set m_oAdapter    = Nothing
      
   End Sub
        
   '================================================================================================='
   Public Property Get vbCount
      vbCount = m_oCollection.Count
   End Property
      
   '================================================================================================='
   Public Function vbConnect(byval sComputer)
   
      m_sComputer = sComputer
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")
      
   End Function
   
   '================================================================================================='
   Public Function vbQuery(byval sQuery)
   On Error Resume Next
   Dim oProcess   : Set oProcess = Nothing
   Dim nIndex     : nIndex       = 0
      
      m_sQuery = sQuery
      
      Set m_oAdapters  = m_oWMIService.ExecQuery(m_sQuery,"WQL",0)
     
      ' Check For Error
      If(Err.Number <> 0) Then
         vbQuery = Err.Number
         Exit Function
      Else
         vbQuery = Err.Number
      End If
      
      For Each oProcess In m_oAdapters
         
         nIndex = nIndex + 1
         m_oCollection.Add nIndex, oProcess
                 
      Next
      
      If(m_oCollection.Count = 0) Then
         vbQuery = WBEM_ERR_FAILED
         Exit Function
      End If
      
      ' Set the process to the first process in the collection
      Set m_oAdapter = m_oCollection.Item(1)
      'm_nCurrent = 1
            
   End Function
   
   '================================================================================================='
   Public Function vbNext
   Dim oProcess   : Set oProcess = Nothing
      
      m_nCurrent = m_nCurrent + 1
      
      ' Wrap around to the beginning of the collection
      If(m_nCurrent = m_oCollection.Count + 1) Then
         m_nCurrent = 1
      End If
      
      Set m_oAdapter = m_oCollection.Item(m_nCurrent)
                  
   End Function   
   
   '###################################### WMI Properties ###########################################'
     
   '================================================================================================='
   Public Property Get Availability
      Availability = m_oAdapter.Availability
   End Property
   
   '================================================================================================='
   Public Property Get AdapterType
      AdapterType = m_oAdapter.AdapterType
   End Property
   
   '================================================================================================='
   Public Property Get AutoSense
      AutoSense = m_oAdapter.AutoSense
   End Property
   
   '================================================================================================='
   Public Property Get Caption
      Caption = m_oAdapter.Caption
   End Property
   
   '================================================================================================='
   Public Property Get ConfigManagerErrorCode
      ConfigManagerErrorCode = m_oAdapter.ConfigManagerErrorCode
   End Property
   
   '================================================================================================='
   Public Property Get ConfigManagerUserConfig
      ConfigManagerUserConfig = m_oAdapter.ConfigManagerUserConfig
   End Property
   
   '================================================================================================='
   Public Property Get CreationClassName
      CreationClassName = m_oAdapter.CreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get Description
      Description = m_oAdapter.Description
   End Property
   
   '================================================================================================='
   Public Property Get DeviceID
      DeviceID = m_oAdapter.DeviceID
   End Property
   
   '================================================================================================='
   Public Property Get ErrorCleared
      ErrorCleared = m_oAdapter.ErrorCleared
   End Property
   
   '================================================================================================='
   Public Property Get ErrorDescription
      ErrorDescription = m_oAdapter.ErrorDescription
   End Property
   
   '================================================================================================='
   Public Property Get Index
      Index = m_oAdapter.Index
   End Property
   
   '================================================================================================='
   Public Property Get InstallDate
      InstallDate = m_oAdapter.InstallDate
   End Property
   
   '================================================================================================='
   Public Property Get Installed
      Installed = m_oAdapter.Installed
   End Property
   
      
   '================================================================================================='
   Public Property Get LastErrorCode
      LastErrorCode = m_oAdapter.LastErrorCode
   End Property
   
   '================================================================================================='
   Public Property Get MACAddress
      MACAddress = m_oAdapter.MACAddress
   End Property
   
   '================================================================================================='
   Public Property Get Manufacturer
      Manufacturer = m_oAdapter.Manufacturer
   End Property
   
   '================================================================================================='
   Public Property Get MaxNumberControlled
      MaxNumberControlled = m_oAdapter.MaxNumberControlled
   End Property
   
   '================================================================================================='
   Public Property Get MaxSpeed
      MaxSpeed = m_oAdapter.MaxSpeed
   End Property
   
   '================================================================================================='
   Public Property Get Name
      Name = m_oAdapter.Name
   End Property
   
   '================================================================================================='
   Public Property Get NetworkAddresses
      NetworkAddresses = m_oAdapter.NetworkAddresses
   End Property
   
   '================================================================================================='
   Public Property Get PermanentAddress
      PermanentAddress = m_oAdapter.PermanentAddress
   End Property
   
   '================================================================================================='
   Public Property Get PNPDeviceID
      PNPDeviceID = m_oAdapter.PNPDeviceID
   End Property
   
   '================================================================================================='
   Public Property Get PowerManagementCapabilities
      PowerManagementCapabilities = m_oAdapter.PowerManagementCapabilities
   End Property
   
   '================================================================================================='
   Public Property Get PowerManagementSupported
      PowerManagementSupported = m_oAdapter.PowerManagementSupported
   End Property
   
   '================================================================================================='
   Public Property Get ProductName
      ProductName = m_oAdapter.ProductName
   End Property
   
   '================================================================================================='
   Public Property Get ServiceName
      ServiceName = m_oAdapter.ServiceName
   End Property
   
   '================================================================================================='
   Public Property Get Speed
      Speed = m_oAdapter.Speed
   End Property
   
   '================================================================================================='
   Public Property Get Status
      Status = m_oAdapter.Status
   End Property
   
   '================================================================================================='
   Public Property Get StatusInfo
      StatusInfo = m_oAdapter.StatusInfo
   End Property
   
   '================================================================================================='
   Public Property Get SystemCreationClassName
      SystemCreationClassName = m_oAdapter.SystemCreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get SystemName
      SystemName = m_oAdapter.SystemName
   End Property
   
   '================================================================================================='
   Public Property Get TimeOfLastReset
      TimeOfLastReset = m_oAdapter.TimeOfLastReset
   End Property
        
   '####################################### WMI Methods #############################################'
      
End Class
'<!-- CRC = 0x30b1e9ba --->
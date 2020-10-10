Option Explicit

Class CWin32_ComputerSystem
   
   Private m_sComputer
   Private m_oWMIService
   Private m_oSystems
   Private m_oSystem
   Private m_nCurrent
   Private m_sQuery
     
   Private m_oCollection  
   '================================================================================================='
   Public Sub Class_Initialize()
      
      m_nCurrent        = 0
      m_sComputer       = "."
      m_sQuery          = "SELECT * FROM Win32_ComputerSystem"
      
      Set m_oWMIService = Nothing
      Set m_oSystems	= Nothing
      Set m_oSystem    = Nothing      
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")
      Set m_oCollection = CreateObject("Scripting.Dictionary")
            
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
      
      Set m_oWMIService = Nothing
      Set m_oSystems	= Nothing
      Set m_oSystem    = Nothing
      
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
      
      Set m_oSystems  = m_oWMIService.ExecQuery(m_sQuery,"WQL",0)
     
      ' Check For Error
      If(Err.Number <> 0) Then
         vbQuery = Err.Number
         Exit Function
      Else
         vbQuery = Err.Number
      End If
      
      For Each oProcess In m_oSystems
         
         nIndex = nIndex + 1
         m_oCollection.Add nIndex, oProcess
                 
      Next
      
      If(m_oCollection.Count = 0) Then
         vbQuery = WBEM_ERR_FAILED
         Exit Function
      End If
      
      ' Set the process to the first process in the collection
      Set m_oSystem = m_oCollection.Item(1)
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
      
      Set m_oSystem = m_oCollection.Item(m_nCurrent)
                  
   End Function   
   
   '###################################### WMI Properties ###########################################'
     
   '================================================================================================='
   Public Property Get AdminPasswordStatus
      AdminPasswordStatus = m_oSystem.AdminPasswordStatus
   End Property
   
   '================================================================================================='
   Public Property Get AutomaticResetBootOption
      AutomaticResetBootOption = m_oSystem.AutomaticResetBootOption
   End Property
   
   '================================================================================================='
   Public Property Get AutomaticResetCapability
      AutomaticResetCapability = m_oSystem.AutomaticResetCapability
   End Property
   
   '================================================================================================='
   Public Property Get BootOptionOnLimit
      BootOptionOnLimit = m_oSystem.BootOptionOnLimit
   End Property
   
   '================================================================================================='
   Public Property Get BootOptionOnWatchDog
      BootOptionOnWatchDog = m_oSystem.BootOptionOnWatchDog
   End Property
   
   '================================================================================================='
   Public Property Get BootROMSupported
      BootROMSupported = m_oSystem.BootROMSupported
   End Property
   
   '================================================================================================='
   Public Property Get BootupState
      BootupState = m_oSystem.BootupState
   End Property
   
   '================================================================================================='
   Public Property Get Caption
      Caption = m_oSystem.Caption
   End Property
   
   '================================================================================================='
   Public Property Get ChassisBootupState
      ChassisBootupState = m_oSystem.ChassisBootupState
   End Property
   
   '================================================================================================='
   Public Property Get CreationClassName
      CreationClassName = m_oSystem.CreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get CurrentTimeZone
      CurrentTimeZone = m_oSystem.CurrentTimeZone
   End Property
   
   '================================================================================================='
   Public Property Get DaylightInEffect
      DaylightInEffect = m_oSystem.DaylightInEffect
   End Property
   
   '================================================================================================='
   Public Property Get Description
      Description = m_oSystem.Description
   End Property
   
   '================================================================================================='
   Public Property Get Domain
      Domain = m_oSystem.Domain
   End Property
   
   '================================================================================================='
   Public Property Get DomainRole
      DomainRole = m_oSystem.DomainRole
   End Property
   
   '================================================================================================='
   Public Property Get FrontPanelResetStatus
      FrontPanelResetStatus = m_oSystem.FrontPanelResetStatus
   End Property
   
   '================================================================================================='
   Public Property Get InfraredSupported
      InfraredSupported = m_oSystem.InfraredSupported
   End Property
   
   '================================================================================================='
   Public Property Get InitialLoadInfo
      InitialLoadInfo = m_oSystem.InitialLoadInfo
   End Property
   
   '================================================================================================='
   Public Property Get InstallDate
      InstallDate = m_oSystem.InstallDate
   End Property
   
   '================================================================================================='
   Public Property Get KeyboardPasswordStatus
      KeyboardPasswordStatus = m_oSystem.KeyboardPasswordStatus
   End Property
   
   '================================================================================================='
   Public Property Get LastLoadInfo
      LastLoadInfo = m_oSystem.LastLoadInfo
   End Property
   
   '================================================================================================='
   Public Property Get Manufacturer
      Manufacturer = m_oSystem.Manufacturer
   End Property
   
   '================================================================================================='
   Public Property Get Model
      Model = m_oSystem.Model
   End Property
   
   '================================================================================================='
   Public Property Get Name
      Name = m_oSystem.Name
   End Property
   
   '================================================================================================='
   Public Property Get NameFormat
      NameFormat = m_oSystem.NameFormat
   End Property
   
   '================================================================================================='
   Public Property Get NetworkServerModeEnabled
      NetworkServerModeEnabled = m_oSystem.NetworkServerModeEnabled
   End Property
   
   '================================================================================================='
   Public Property Get NumberOfProcessors
      NumberOfProcessors = m_oSystem.NumberOfProcessors
   End Property
   
   '================================================================================================='
   Public Property Get OEMLogoBitmap
      OEMLogoBitmap = m_oSystem.OEMLogoBitmap
   End Property
   
   '================================================================================================='
   Public Property Get OEMStringArray
      OEMStringArray = m_oSystem.OEMStringArray
   End Property
   
   '================================================================================================='
   Public Property Get PauseAfterReset
      PauseAfterReset = m_oSystem.PauseAfterReset
   End Property
   
   '================================================================================================='
   Public Property Get PowerManagementCapabilities
      PowerManagementCapabilities = m_oSystem.PowerManagementCapabilities
   End Property
   
   '================================================================================================='
   Public Property Get PowerManagementSupported
      PowerManagementSupported = m_oSystem.PowerManagementSupported
   End Property
   
   '================================================================================================='
   Public Property Get PowerOnPasswordStatus
      PowerOnPasswordStatus = m_oSystem.PowerOnPasswordStatus
   End Property
   
   '================================================================================================='
   Public Property Get PowerState
      PowerState = m_oSystem.PowerState
   End Property
   
   '================================================================================================='
   Public Property Get PowerSupplyState
      PowerSupplyState = m_oSystem.PowerSupplyState
   End Property
   
   '================================================================================================='
   Public Property Get PrimaryOwnerContact
      PrimaryOwnerContact = m_oSystem.PrimaryOwnerContact
   End Property
   
   '================================================================================================='
   Public Property Get PrimaryOwnerName
      PrimaryOwnerName = m_oSystem.PrimaryOwnerName
   End Property
   
   '================================================================================================='
   Public Property Get ResetCapability
      ResetCapability = m_oSystem.ResetCapability
   End Property
   
   '================================================================================================='
   Public Property Get ResetCount
      ResetCount = m_oSystem.ResetCount
   End Property
   
   '================================================================================================='
   Public Property Get ResetLimit
      ResetLimit = m_oSystem.ResetLimit
   End Property
   
   '================================================================================================='
   Public Property Get Roles
      Roles = m_oSystem.Roles
   End Property
   
   '================================================================================================='
   Public Property Get Status
      Status = m_oSystem.Status
   End Property
   
   '================================================================================================='
   Public Property Get SupportContactDescription
      SupportContactDescription = m_oSystem.SupportContactDescription
   End Property
   
   '================================================================================================='
   Public Property Get SystemStartupDelay
      SystemStartupDelay = m_oSystem.SystemStartupDelay
   End Property
   
   '================================================================================================='
   Public Property Get SystemStartupOptions
      SystemStartupOptions = m_oSystem.SystemStartupOptions
   End Property
   
   '================================================================================================='
   Public Property Get SystemStartupSetting
      SystemStartupSetting = m_oSystem.SystemStartupSetting
   End Property
   
   '================================================================================================='
   Public Property Get SystemType
      SystemType = m_oSystem.SystemType
   End Property
   
   '================================================================================================='
   Public Property Get ThermalState
      ThermalState = m_oSystem.ThermalState
   End Property
   
   '================================================================================================='
   Public Property Get TotalPhysicalMemory
      TotalPhysicalMemory = m_oSystem.TotalPhysicalMemory
   End Property
   
   '================================================================================================='
   Public Property Get UserName
      UserName = m_oSystem.UserName
   End Property
   
   '================================================================================================='
   Public Property Get WakeUpType
      WakeUpType = m_oSystem.WakeUpType
   End Property
         
   '####################################### WMI Methods #############################################'
      
End Class
'<!-- CRC = 0x7991f896 --->
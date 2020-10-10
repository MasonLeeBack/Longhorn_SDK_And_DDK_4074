Option Explicit

Class CWin32_OperatingSystem
   
   Private m_sComputer
   Private m_oWMIService
   Private m_oOperatingSystems
   Private m_oOperatingSystem
   Private m_nCurrent
   Private m_sQuery
     
   Private m_oCollection  
   '================================================================================================='
   Public Sub Class_Initialize()
      
      m_nCurrent        = 0
      m_sComputer       = "."
      m_sQuery          = "SELECT * FROM Win32_OperatingSystem"
      
      Set m_oWMIService = Nothing
      Set m_oOperatingSystems	= Nothing
      Set m_oOperatingSystem    = Nothing      
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")
      Set m_oCollection = CreateObject("Scripting.Dictionary")
            
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
      
      Set m_oWMIService = Nothing
      Set m_oOperatingSystems	= Nothing
      Set m_oOperatingSystem    = Nothing
      
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
      
      Set m_oOperatingSystems  = m_oWMIService.ExecQuery(m_sQuery,"WQL",0)
     
      ' Check For Error
      If(Err.Number <> 0) Then
         vbQuery = Err.Number
         Exit Function
      Else
         vbQuery = Err.Number
      End If
      
      For Each oProcess In m_oOperatingSystems
         
         nIndex = nIndex + 1
         m_oCollection.Add nIndex, oProcess
                 
      Next
      
      If(m_oCollection.Count = 0) Then
         vbQuery = WBEM_ERR_FAILED
         Exit Function
      End If
      
      ' Set the process to the first process in the collection
      Set m_oOperatingSystem = m_oCollection.Item(1)
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
      
      Set m_oOperatingSystem = m_oCollection.Item(m_nCurrent)
                  
   End Function   
   
   '###################################### WMI Properties ###########################################'
     
   '================================================================================================='
   Public Property Get BootDevice
      BootDevice = m_oOperatingSystem.BootDevice
   End Property
   
   '================================================================================================='
   Public Property Get BuildNumber
      BuildNumber = m_oOperatingSystem.BuildNumber
   End Property
   
   '================================================================================================='
   Public Property Get BuildType
      BuildType = m_oOperatingSystem.BuildType
   End Property
   
   '================================================================================================='
   Public Property Get Caption
      Caption = m_oOperatingSystem.Caption
   End Property
   
   '================================================================================================='
   Public Property Get CodeSet
      CodeSet = m_oOperatingSystem.CodeSet
   End Property
   
   '================================================================================================='
   Public Property Get CountryCode
      CountryCode = m_oOperatingSystem.CountryCode
   End Property
   
   '================================================================================================='
   Public Property Get CreationClassName
      CreationClassName = m_oOperatingSystem.CreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get CSCreationClassName
      CSCreationClassName = m_oOperatingSystem.CSCreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get CSDVersion
      CSDVersion = m_oOperatingSystem.CSDVersion
   End Property
   
   '================================================================================================='
   Public Property Get CSName
      CSName = m_oOperatingSystem.CSName
   End Property
   
   '================================================================================================='
   Public Property Get CurrentTimeZone
      CurrentTimeZone = m_oOperatingSystem.CurrentTimeZone
   End Property
   
   '================================================================================================='
   Public Property Get Debug
      Debug = m_oOperatingSystem.Debug
   End Property
   
   '================================================================================================='
   Public Property Get Description
      Description = m_oOperatingSystem.Description
   End Property
   
   '================================================================================================='
   Public Property Get Distributed
      Distributed = m_oOperatingSystem.Distributed
   End Property
   
      
   '================================================================================================='
   Public Property Get ForegroundApplicationBoost
      ForegroundApplicationBoost = m_oOperatingSystem.ForegroundApplicationBoost
   End Property
   
   '================================================================================================='
   Public Property Get FreePhysicalMemory
      FreePhysicalMemory = m_oOperatingSystem.FreePhysicalMemory
   End Property
   
   '================================================================================================='
   Public Property Get FreeSpaceInPagingFiles
      FreeSpaceInPagingFiles = m_oOperatingSystem.FreeSpaceInPagingFiles
   End Property
   
   '================================================================================================='
   Public Property Get FreeVirtualMemory
      FreeVirtualMemory = m_oOperatingSystem.FreeVirtualMemory
   End Property
   
   '================================================================================================='
   Public Property Get InstallDate
      InstallDate = m_oOperatingSystem.InstallDate
   End Property
   
   '================================================================================================='
   Public Property Get LastBootUpTime
      LastBootUpTime = m_oOperatingSystem.LastBootUpTime
   End Property
   
   '================================================================================================='
   Public Property Get LocalDateTime
      LocalDateTime = m_oOperatingSystem.LocalDateTime
   End Property
   
   '================================================================================================='
   Public Property Get Locale
      Locale = m_oOperatingSystem.Locale
   End Property
   
   '================================================================================================='
   Public Property Get Manufacturer
      Manufacturer = m_oOperatingSystem.Manufacturer
   End Property
   
   '================================================================================================='
   Public Property Get MaxNumberOfProcesses
      MaxNumberOfProcesses = m_oOperatingSystem.MaxNumberOfProcesses
   End Property
   
   '================================================================================================='
   Public Property Get MaxProcessMemorySize
      MaxProcessMemorySize = m_oOperatingSystem.MaxProcessMemorySize
   End Property
   
   '================================================================================================='
   Public Property Get Name
      Name = m_oOperatingSystem.Name
   End Property
   
   '================================================================================================='
   Public Property Get NumberOfLicensedUsers
      NumberOfLicensedUsers = m_oOperatingSystem.NumberOfLicensedUsers
   End Property
   
   '================================================================================================='
   Public Property Get NumberOfProcesses
      NumberOfProcesses = m_oOperatingSystem.NumberOfProcesses
   End Property
   
   '================================================================================================='
   Public Property Get NumberOfUsers
      NumberOfUsers = m_oOperatingSystem.NumberOfUsers
   End Property
   
   '================================================================================================='
   Public Property Get Organization
      Organization = m_oOperatingSystem.Organization
   End Property
   
   '================================================================================================='
   Public Property Get OSLanguage
      OSLanguage = m_oOperatingSystem.OSLanguage
   End Property
   
   '================================================================================================='
   Public Property Get OSProductSuite
      OSProductSuite = m_oOperatingSystem.OSProductSuite
   End Property
   
   '================================================================================================='
   Public Property Get OSType
      OSType = m_oOperatingSystem.OSType
   End Property
   
   '================================================================================================='
   Public Property Get OtherTypeDescription
      OtherTypeDescription = m_oOperatingSystem.OtherTypeDescription
   End Property
   
   '================================================================================================='
   Public Property Get PlusProductID
      PlusProductID = m_oOperatingSystem.PlusProductID
   End Property
   
   '================================================================================================='
   Public Property Get PlusVersionNumber
      PlusVersionNumber = m_oOperatingSystem.PlusVersionNumber
   End Property
   
   '================================================================================================='
   Public Property Get Primary
      Primary = m_oOperatingSystem.Primary
   End Property
   
   '================================================================================================='
   Public Property Get QuantumLength
      QuantumLength = m_oOperatingSystem.QuantumLength
   End Property
   
   '================================================================================================='
   Public Property Get QuantumType
      QuantumType = m_oOperatingSystem.QuantumType
   End Property
   
   '================================================================================================='
   Public Property Get RegisteredUser
      RegisteredUser = m_oOperatingSystem.RegisteredUser
   End Property
   
   '================================================================================================='
   Public Property Get SerialNumber
      SerialNumber = m_oOperatingSystem.SerialNumber
   End Property
   
   '================================================================================================='
   Public Property Get ServicePackMajorVersion
      ServicePackMajorVersion = m_oOperatingSystem.ServicePackMajorVersion
   End Property
   
   '================================================================================================='
   Public Property Get ServicePackMinorVersion
      ServicePackMinorVersion = m_oOperatingSystem.ServicePackMinorVersion
   End Property
   
   '================================================================================================='
   Public Property Get SizeStoredInPagingFiles
      SizeStoredInPagingFiles = m_oOperatingSystem.SizeStoredInPagingFiles
   End Property
   
   '================================================================================================='
   Public Property Get Status
      Status = m_oOperatingSystem.Status
   End Property
   
   '================================================================================================='
   Public Property Get SystemDevice
      SystemDevice = m_oOperatingSystem.SystemDevice
   End Property
   
   '================================================================================================='
   Public Property Get SystemDirectory
      SystemDirectory = m_oOperatingSystem.SystemDirectory
   End Property
   
   '================================================================================================='
   Public Property Get TotalSwapSpaceSize
      TotalSwapSpaceSize = m_oOperatingSystem.TotalSwapSpaceSize
   End Property
   
   '================================================================================================='
   Public Property Get TotalVirtualMemorySize
      TotalVirtualMemorySize = m_oOperatingSystem.TotalVirtualMemorySize
   End Property
   
   '================================================================================================='
   Public Property Get TotalVisibleMemorySize
      TotalVisibleMemorySize = m_oOperatingSystem.TotalVisibleMemorySize
   End Property
   
   '================================================================================================='
   Public Property Get Version
      Version = m_oOperatingSystem.Version
   End Property
   
   '================================================================================================='
   Public Property Get WindowsDirectory
      WindowsDirectory = m_oOperatingSystem.WindowsDirectory
   End Property
     
   '####################################### WMI Methods #############################################'
   
   '================================================================================================='
   Public Function Reboot()
      Reboot = m_oOperatingSystem.Reboot()
   End Function
   
   '================================================================================================='
   Public Function Shutdown()
      Shutdown = m_oOperatingSystem.Shutdown()
   End Function
   
   '================================================================================================='
   Public Function Win32Shutdown(byref nFlags, byref nReserved)
      Win32Shutdown = m_oOperatingSystem.Win32Shutdown(nFlags, nReserved)
   End Function
   
End Class
'<!-- CRC = 0x6ad531be --->
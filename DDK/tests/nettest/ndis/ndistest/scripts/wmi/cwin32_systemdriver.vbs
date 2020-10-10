Option Explicit

Class CWin32_SystemDriver
   
   Private m_sComputer
   Private m_oWMIService
   Private m_oDrivers
   Private m_oDriver
   Private m_nCurrent
   Private m_sQuery
     
   Private m_oCollection  
   '================================================================================================='
   Public Sub Class_Initialize()
      
      m_nCurrent        = 0
      m_sComputer       = "."
      m_sQuery          = "SELECT * FROM Win32_SystemDriver"
      
      Set m_oWMIService = Nothing
      Set m_oDrivers	= Nothing
      Set m_oDriver    = Nothing      
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")
      Set m_oCollection = CreateObject("Scripting.Dictionary")
            
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
      
      Set m_oWMIService = Nothing
      Set m_oDrivers	= Nothing
      Set m_oDriver    = Nothing
      
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
      
      Set m_oDrivers  = m_oWMIService.ExecQuery(m_sQuery,"WQL",0)
     
      ' Check For Error
      If(Err.Number <> 0) Then
         vbQuery = Err.Number
         Exit Function
      Else
         vbQuery = Err.Number
      End If
      
      For Each oProcess In m_oDrivers
         
         nIndex = nIndex + 1
         m_oCollection.Add nIndex, oProcess
                 
      Next
      
      If(m_oCollection.Count = 0) Then
         vbQuery = WBEM_ERR_FAILED
         Exit Function
      End If
      
      ' Set the process to the first process in the collection
      Set m_oDriver = m_oCollection.Item(1)
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
      
      Set m_oDriver = m_oCollection.Item(m_nCurrent)
                  
   End Function   
   
   '###################################### WMI Properties ###########################################'
     
   '================================================================================================='
   Public Property Get AcceptPause
      AcceptPause = m_oDriver.AcceptPause
   End Property
   
   '================================================================================================='
   Public Property Get AcceptStop
      AcceptStop = m_oDriver.AcceptStop
   End Property
   
   '================================================================================================='
   Public Property Get Caption
      Caption = m_oDriver.Caption
   End Property
   
   '================================================================================================='
   Public Property Get CreationClassName
      CreationClassName = m_oDriver.CreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get Description
      Description = m_oDriver.Description
   End Property
   
   '================================================================================================='
   Public Property Get DesktopInteract
      DesktopInteract = m_oDriver.DesktopInteract
   End Property
   
   '================================================================================================='
   Public Property Get DisplayName
      DisplayName = m_oDriver.DisplayName
   End Property
   
   '================================================================================================='
   Public Property Get ErrorControl
      ErrorControl = m_oDriver.ErrorControl
   End Property
   
   '================================================================================================='
   Public Property Get ExitCode
      ExitCode = m_oDriver.ExitCode
   End Property
   
   '================================================================================================='
   Public Property Get InstallDate
      InstallDate = m_oDriver.InstallDate
   End Property
   
   '================================================================================================='
   Public Property Get Name
      Name = m_oDriver.Name
   End Property
   
   '================================================================================================='
   Public Property Get PathName
      PathName = m_oDriver.PathName
   End Property
   
   '================================================================================================='
   Public Property Get ServiceSpecificExitCode
      ServiceSpecificExitCode = m_oDriver.ServiceSpecificExitCode
   End Property
   
   '================================================================================================='
   Public Property Get ServiceType
      ServiceType = m_oDriver.ServiceType
   End Property
         
   '================================================================================================='
   Public Property Get Started
      Started = m_oDriver.Started
   End Property
   
   '================================================================================================='
   Public Property Get StartMode
      StartMode = m_oDriver.StartMode
   End Property
   
   '================================================================================================='
   Public Property Get StartName
      StartName = m_oDriver.StartName
   End Property
   
   '================================================================================================='
   Public Property Get State
      State = m_oDriver.State
   End Property
   
   '================================================================================================='
   Public Property Get Status
      Status = m_oDriver.Status
   End Property
   
   '================================================================================================='
   Public Property Get SystemCreationClassName
      SystemCreationClassName = m_oDriver.SystemCreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get SystemName
      SystemName = m_oDriver.SystemName
   End Property
   
   '================================================================================================='
   Public Property Get TagId
      TagId = m_oDriver.TagId
   End Property
      
   '####################################### WMI Methods #############################################'
   
   '================================================================================================='
   Public Function StartService()
      StartService = m_oDriver.StartService()
   End Function
   
   '================================================================================================='
   Public Function StopService()
      StopService = m_oDriver.StopService()
   End Function
   
   '================================================================================================='
   Public Function PauseService()
      PauseService = m_oDriver.PauseService()
   End Function
   
   '================================================================================================='
   Public Function ResumeService()
      ResumeService = m_oDriver.ResumeService()
   End Function
   
   '================================================================================================='
   Public Function InterrogateService()
      InterrogateService = m_oDriver.InterrogateService()
   End Function
   
   '================================================================================================='
   Public Function UserControlService(byval nControlCode)
      UserControlService = m_oDriver.UserControlService(nControlCode)
   End Function
   
   '================================================================================================='
   Public Function Create(byval sName, byval sDisplayName, byval sPathName, byval nServiceType, byval nErrorControl,                _ 
                          byval sStartMode, byval bDesktopInteract, byval sStartName, byval sStartPassword, byval sLoadOrderGroup,  _
                          byval aLoadOrderGroupDependencies, byval aServiceDependencies)
                          
      Create = m_oDriver.Create(sName, sDisplayName, sPathName, nServiceType, nErrorControl,                _ 
                                sStartMode, bDesktopInteract, sStartName, sStartPassword, sLoadOrderGroup,  _
                                aLoadOrderGroupDependencies, aServiceDependencies)
                                
   End Function
   
   '================================================================================================='
   Public Function Change(byval sName, byval sDisplayName, byval sPathName, byval nServiceType, byval nErrorControl,                _ 
                          byval sStartMode, byval bDesktopInteract, byval sStartName, byval sStartPassword, byval sLoadOrderGroup,  _
                          byval aLoadOrderGroupDependencies, byval aServiceDependencies)
                          
      Change  = m_oDriver.Change(sName, sDisplayName, sPathName, nServiceType, nErrorControl,                _ 
                                 sStartMode, bDesktopInteract, sStartName, sStartPassword, sLoadOrderGroup,  _
                                 aLoadOrderGroupDependencies, aServiceDependencies)
      
   End Function
   
   '================================================================================================='
   Public Function ChangeStartMode(byval sStartMode)
      ChangeStartMode  = m_oDriver.ChangeStartMode(sStartMode)
   End Function
   
   '================================================================================================='
   Public Function Delete()
      Delete  = m_oDriver.Delete()
   End Function
   
End Class
'<!-- CRC = 0x80bd1541 --->
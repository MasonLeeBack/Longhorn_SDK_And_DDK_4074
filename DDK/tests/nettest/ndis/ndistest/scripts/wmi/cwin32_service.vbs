Option Explicit

Class CWin32_Service
   
   Private m_sComputer
   Private m_oWMIService
   Private m_oServices
   Private m_oService
   Private m_nCurrent
   Private m_sQuery
     
   Private m_oCollection  
   '================================================================================================='
   Public Sub Class_Initialize()
      
      m_nCurrent        = 0
      m_sComputer       = "."
      m_sQuery          = "SELECT * FROM Win32_Service"
      
      Set m_oWMIService = Nothing
      Set m_oServices	= Nothing
      Set m_oService    = Nothing      
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")
      Set m_oCollection = CreateObject("Scripting.Dictionary")
            
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
      
      Set m_oWMIService = Nothing
      Set m_oServices	= Nothing
      Set m_oService    = Nothing
      
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
      
      Set m_oServices  = m_oWMIService.ExecQuery(m_sQuery,"WQL",0)
     
      ' Check For Error
      If(Err.Number <> 0) Then
         vbQuery = Err.Number
         Exit Function
      Else
         vbQuery = Err.Number
      End If
      
      For Each oProcess In m_oServices
         
         nIndex = nIndex + 1
         m_oCollection.Add nIndex, oProcess
                 
      Next
      
      If(m_oCollection.Count = 0) Then
         vbQuery = WBEM_ERR_FAILED
         Exit Function
      End If
      
      ' Set the process to the first process in the collection
      Set m_oService = m_oCollection.Item(1)
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
      
      Set m_oService = m_oCollection.Item(m_nCurrent)
                  
   End Function   
   
   '###################################### WMI Properties ###########################################'
     
   '================================================================================================='
   Public Property Get AcceptPause
      AcceptPause = m_oService.AcceptPause
   End Property
   
   '================================================================================================='
   Public Property Get AcceptStop
      AcceptStop = m_oService.AcceptStop
   End Property
   
   '================================================================================================='
   Public Property Get CheckPoint
      CheckPoint = m_oService.CheckPoint
   End Property
   
   '================================================================================================='
   Public Property Get Caption
      Caption = m_oService.Caption
   End Property
   
   '================================================================================================='
   Public Property Get CreationClassName
      CreationClassName = m_oService.CreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get Description
      Description = m_oService.Description
   End Property
   
   '================================================================================================='
   Public Property Get DesktopInteract
      DesktopInteract = m_oService.DesktopInteract
   End Property
   
   '================================================================================================='
   Public Property Get DisplayName
      DisplayName = m_oService.DisplayName
   End Property
   
   '================================================================================================='
   Public Property Get ErrorControl
      ErrorControl = m_oService.ErrorControl
   End Property
   
   '================================================================================================='
   Public Property Get ExitCode
      ExitCode = m_oService.ExitCode
   End Property
   
   '================================================================================================='
   Public Property Get InstallDate
      InstallDate = m_oService.InstallDate
   End Property
   
   '================================================================================================='
   Public Property Get Name
      Name = m_oService.Name
   End Property
   
   '================================================================================================='
   Public Property Get PathName
      PathName = m_oService.PathName
   End Property
   
   '================================================================================================='
   Public Property Get ProcessId
      ProcessId = m_oService.ProcessId
   End Property
   
   '================================================================================================='
   Public Property Get ServiceSpecificExitCode
      ServiceSpecificExitCode = m_oService.ServiceSpecificExitCode
   End Property
   
   '================================================================================================='
   Public Property Get ServiceType
      ServiceType = m_oService.ServiceType
   End Property
         
   '================================================================================================='
   Public Property Get Started
      Started = m_oService.Started
   End Property
   
   '================================================================================================='
   Public Property Get StartMode
      StartMode = m_oService.StartMode
   End Property
   
   '================================================================================================='
   Public Property Get StartName
      StartName = m_oService.StartName
   End Property
   
   '================================================================================================='
   Public Property Get State
      State = m_oService.State
   End Property
   
   '================================================================================================='
   Public Property Get Status
      Status = m_oService.Status
   End Property
   
   '================================================================================================='
   Public Property Get SystemCreationClassName
      SystemCreationClassName = m_oService.SystemCreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get SystemName
      SystemName = m_oService.SystemName
   End Property
   
   '================================================================================================='
   Public Property Get TagId
      TagId = m_oService.TagId
   End Property
   
   '================================================================================================='
   Public Property Get WaitHint
      WaitHint = m_oService.WaitHint
   End Property
      
   '####################################### WMI Methods #############################################'
   
   '================================================================================================='
   Public Function StartService()
      StartService = m_oService.StartService()
   End Function
   
   '================================================================================================='
   Public Function StopService()
      StopService = m_oService.StopService()
   End Function
   
   '================================================================================================='
   Public Function PauseService()
      PauseService = m_oService.PauseService()
   End Function
   
   '================================================================================================='
   Public Function ResumeService()
      ResumeService = m_oService.ResumeService()
   End Function
   
   '================================================================================================='
   Public Function InterrogateService()
      InterrogateService = m_oService.InterrogateService()
   End Function
   
   '================================================================================================='
   Public Function UserControlService(byval nControlCode)
      UserControlService = m_oService.UserControlService(nControlCode)
   End Function
   
   '================================================================================================='
   Public Function Create(byval sName, byval sDisplayName, byval sPathName, byval nServiceType, byval nErrorControl,                _ 
                          byval sStartMode, byval bDesktopInteract, byval sStartName, byval sStartPassword, byval sLoadOrderGroup,  _
                          byval aLoadOrderGroupDependencies, byval aServiceDependencies)
                          
      Create = m_oService.Create(sName, sDisplayName, sPathName, nServiceType, nErrorControl,                _ 
                                sStartMode, bDesktopInteract, sStartName, sStartPassword, sLoadOrderGroup,  _
                                aLoadOrderGroupDependencies, aServiceDependencies)
                                
   End Function
   
   '================================================================================================='
   Public Function Change(byval sName, byval sDisplayName, byval sPathName, byval nServiceType, byval nErrorControl,                _ 
                          byval sStartMode, byval bDesktopInteract, byval sStartName, byval sStartPassword, byval sLoadOrderGroup,  _
                          byval aLoadOrderGroupDependencies, byval aServiceDependencies)
                          
      Change  = m_oService.Change(sName, sDisplayName, sPathName, nServiceType, nErrorControl,                _ 
                                 sStartMode, bDesktopInteract, sStartName, sStartPassword, sLoadOrderGroup,  _
                                 aLoadOrderGroupDependencies, aServiceDependencies)
      
   End Function
   
   '================================================================================================='
   Public Function ChangeStartMode(byval sStartMode)
      ChangeStartMode  = m_oService.ChangeStartMode(sStartMode)
   End Function
   
   '================================================================================================='
   Public Function Delete()
      Delete  = m_oService.Delete()
   End Function
   
End Class
'<!-- CRC = 0x3c99bbb8 --->
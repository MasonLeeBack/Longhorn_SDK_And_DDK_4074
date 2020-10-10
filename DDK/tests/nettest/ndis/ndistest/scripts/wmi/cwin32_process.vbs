Option Explicit

Class CWin32_Process
   
   Private m_sComputer
   Private m_oWMIService
   Private m_oProcesses
   Private m_oProcess
   Private m_nCurrent
   Private m_sQuery
     
   Private m_oCollection  
   '================================================================================================='
   Public Sub Class_Initialize()
      
      m_nCurrent        = 0
      m_sComputer       = "."
      m_sQuery          = "SELECT * FROM Win32_Process"
      
      Set m_oWMIService = Nothing
      Set m_oProcesses	= Nothing
      Set m_oProcess    = Nothing      
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")
      Set m_oCollection = CreateObject("Scripting.Dictionary")
            
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
      
      Set m_oWMIService = Nothing
      Set m_oProcesses	= Nothing
      Set m_oProcess    = Nothing
      
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
      
      Set m_oProcesses  = m_oWMIService.ExecQuery(m_sQuery,"WQL",0)
     
      ' Check For Error
      If(Err.Number <> 0) Then
         vbQuery = Err.Number
         Exit Function
      Else
         vbQuery = Err.Number
      End If
      
      For Each oProcess In m_oProcesses
         
         nIndex = nIndex + 1
         m_oCollection.Add nIndex, oProcess
                 
      Next
      
      If(m_oCollection.Count = 0) Then
         vbQuery = WBEM_ERR_FAILED
         Exit Function
      End If
      
      ' Set the process to the first process in the collection
      Set m_oProcess = m_oCollection.Item(1)
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
      
      Set m_oProcess = m_oCollection.Item(m_nCurrent)
                  
   End Function   
   
   '###################################### WMI Properties ###########################################'
     
   '================================================================================================='
   Public Property Get Caption
      Caption = m_oProcess.Caption
   End Property
   
   '================================================================================================='
   Public Property Get CreationClassName
      CreationClassName = m_oProcess.CreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get CreationDate
      CreationDate = m_oProcess.CreationDate
   End Property
   
   '================================================================================================='
   Public Property Get CSCreationClassName
      CSCreationClassName = m_oProcess.CSCreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get CSName
      CSName = m_oProcess.CSName
   End Property
   
   '================================================================================================='
   Public Property Get Description
      Description = m_oProcess.Description
   End Property
   
   '================================================================================================='
   Public Property Get ExecutablePath
      ExecutablePath = m_oProcess.ExecutablePath
   End Property
   
   '================================================================================================='
   Public Property Get ExecutionState
      ExecutionState = m_oProcess.ExecutionState
   End Property
   
   '================================================================================================='
   Public Property Get Handle
      Handle = m_oProcess.Handle
   End Property
   
   '================================================================================================='
   Public Property Get HandleCount
      HandleCount = m_oProcess.HandleCount
   End Property
   
   '================================================================================================='
   Public Property Get InstallDate
      InstallDate = m_oProcess.InstallDate
   End Property
   
   '================================================================================================='
   Public Property Get KernelModeTime
      KernelModeTime = m_oProcess.KernelModeTime
   End Property
   
   '================================================================================================='
   Public Property Get MaximumWorkingSetSize
      MaximumWorkingSetSize = m_oProcess.MaximumWorkingSetSize
   End Property
   
   '================================================================================================='
   Public Property Get MinimumWorkingSetSize
      MinimumWorkingSetSize = m_oProcess.MinimumWorkingSetSize
   End Property
   
   '================================================================================================='
   Public Property Get Name
      Name = m_oProcess.Name
   End Property
   
   '================================================================================================='
   Public Property Get OSName
      OSName = m_oProcess.OSName
   End Property
   
   '================================================================================================='
   Public Property Get OtherOperationCount
      OtherOperationCount = m_oProcess.OtherOperationCount
   End Property
   
   '================================================================================================='
   Public Property Get OtherTransferCount
      OtherTransferCount = m_oProcess.OtherTransferCount
   End Property
   
   '================================================================================================='
   Public Property Get PageFaults
      PageFaults = m_oProcess.PageFaults
   End Property
   
   '================================================================================================='
   Public Property Get PageFileUsage
      PageFileUsage = m_oProcess.PageFileUsage
   End Property
   
   '================================================================================================='
   Public Property Get ParentProcessId
      ParentProcessId = m_oProcess.ParentProcessId
   End Property
   
   '================================================================================================='
   Public Property Get PeakPageFileUsage
      PeakPageFileUsage = m_oProcess.PeakPageFileUsage
   End Property
   
   '================================================================================================='
   Public Property Get PeakVirtualSize
      PeakVirtualSize = m_oProcess.PeakVirtualSize
   End Property
   
   '================================================================================================='
   Public Property Get PeakWorkingSetSize
      PeakWorkingSetSize = m_oProcess.PeakWorkingSetSize
   End Property
   
   '================================================================================================='
   Public Property Get Priority
      Priority = m_oProcess.Priority
   End Property
   
   '================================================================================================='
   Public Property Get PrivatePageCount
      PrivatePageCount = m_oProcess.PrivatePageCount
   End Property
   
   '================================================================================================='
   Public Property Get ProcessId
      ProcessId = m_oProcess.ProcessId
   End Property
   
   '================================================================================================='
   Public Property Get QuotaNonPagedPoolUsage
      QuotaNonPagedPoolUsage = m_oProcess.QuotaNonPagedPoolUsage
   End Property
   
   '================================================================================================='
   Public Property Get QuotaPagedPoolUsage
      QuotaPagedPoolUsage = m_oProcess.QuotaPagedPoolUsage
   End Property
   
   '================================================================================================='
   Public Property Get QuotaPeakNonPagedPoolUsage
      QuotaPeakNonPagedPoolUsage = m_oProcess.QuotaPeakNonPagedPoolUsage
   End Property
   
   '================================================================================================='
   Public Property Get QuotaPeakPagedPoolUsage
      QuotaPeakPagedPoolUsage = m_oProcess.QuotaPeakPagedPoolUsage
   End Property
   
   '================================================================================================='
   Public Property Get ReadOperationCount
      ReadOperationCount = m_oProcess.ReadOperationCount
   End Property
   
   '================================================================================================='
   Public Property Get ReadTransferCount
      ReadTransferCount = m_oProcess.ReadTransferCount
   End Property
   
   '================================================================================================='
   Public Property Get SessionId
      SessionId = m_oProcess.SessionId
   End Property
   
   '================================================================================================='
   Public Property Get Status
      Status = m_oProcess.Status
   End Property
   
   '================================================================================================='
   Public Property Get TerminationDate
      TerminationDate = m_oProcess.TerminationDate
   End Property
   
   '================================================================================================='
   Public Property Get ThreadCount
      ThreadCount = m_oProcess.ThreadCount
   End Property
   
   '================================================================================================='
   Public Property Get UserModeTime
      UserModeTime = m_oProcess.UserModeTime
   End Property
   
   '================================================================================================='
   Public Property Get VirtualSize
      VirtualSize = m_oProcess.VirtualSize
   End Property
   
   '================================================================================================='
   Public Property Get WindowsVersion
      WindowsVersion = m_oProcess.WindowsVersion
   End Property
   
   '================================================================================================='
   Public Property Get WorkingSetSize
      WorkingSetSize = m_oProcess.WorkingSetSize
   End Property
   
   '================================================================================================='
   Public Property Get WriteOperationCount
      WriteOperationCount = m_oProcess.WriteOperationCount
   End Property
   
   '================================================================================================='
   Public Property Get WriteTransferCount
      WriteTransferCount = m_oProcess.WriteTransferCount
   End Property
   
   '####################################### WMI Methods #############################################'
      
   '================================================================================================='
   Public Function Create(byval sCommandLine, byval sCurrentDirectory, byref nProcessID)
      Create = WBEM_ERR_FAILED
      Exit Function
      Create = m_oProcess.Create(sCommandLine, sCurrentDirectory, nProcessID)
   End Function
   
   '================================================================================================='
   Public Function Terminate(byval nReason)
      Terminate = m_oProcess.Terminate(nReason)
   End Function
   
   '================================================================================================='
   Public Function GetOwner(byref sUser, byref sDomain)
      GetOwner = m_oProcess.GetOwner(sUser, sDomain)
   End Function
   
   '================================================================================================='
   Public Function GetOwnerSid(byref sSid)
      GetOwnerSid = m_oProcess.GetOwnerSid(sSid)
   End Function
   
End Class
'<!-- CRC = 0xb68cf93e --->
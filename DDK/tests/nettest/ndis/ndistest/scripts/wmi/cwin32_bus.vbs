Option Explicit

Class CWin32_Bus
   
   Private m_sComputer
   Private m_oWMIService
   Private m_oCollection
   Private m_oItem
   Private m_nCurrent
   Private m_sQuery
     
   Private m_oItems  
   '================================================================================================='
   Public Sub Class_Initialize()
      
      m_nCurrent        = 0
      m_sComputer       = "."
      m_sQuery          = "SELECT * FROM Win32_Bus"
      
      Set m_oWMIService = Nothing
      Set m_oCollection	= Nothing
      Set m_oItem    = Nothing      
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")
      Set m_oItems = CreateObject("Scripting.Dictionary")
            
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
      
      Set m_oWMIService = Nothing
      Set m_oCollection	= Nothing
      Set m_oItem    = Nothing
      
   End Sub
        
   '================================================================================================='
   Public Property Get vbCount
      vbCount = m_oItems.Count
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
      
      Set m_oCollection  = m_oWMIService.ExecQuery(m_sQuery,"WQL",0)
     
      ' Check For Error
      If(Err.Number <> 0) Then
         vbQuery = Err.Number
         Exit Function
      Else
         vbQuery = Err.Number
      End If
      
      For Each oProcess In m_oCollection
         
         nIndex = nIndex + 1
         m_oItems.Add nIndex, oProcess
                 
      Next
      
      If(m_oItems.Count = 0) Then
         vbQuery = WBEM_ERR_FAILED
         Exit Function
      End If
      
      ' Set the process to the first process in the collection
      Set m_oItem = m_oItems.Item(1)
      'm_nCurrent = 1
            
   End Function
   
   '================================================================================================='
   Public Function vbNext
   
      m_nCurrent = m_nCurrent + 1
      
      ' Wrap around to the beginning of the collection
      If(m_nCurrent = m_oItems.Count + 1) Then
         m_nCurrent = 1
      End If
      
      Set m_oItem = m_oItems.Item(m_nCurrent)
                  
   End Function   
   
   '###################################### WMI Properties ###########################################'
     
   '================================================================================================='
   Public Property Get Availability
      Availability = m_oItem.Availability
   End Property
   
   '================================================================================================='
   Public Property Get BusNum
      BusNum = m_oItem.BusNum
   End Property
   
   '================================================================================================='
   Public Property Get BusType
      BusType = m_oItem.BusType
   End Property
   
   '================================================================================================='
   Public Property Get Caption
      Caption = m_oItem.Caption
   End Property
   
   '================================================================================================='
   Public Property Get ConfigManagerErrorCode
      ConfigManagerErrorCode = m_oItem.ConfigManagerErrorCode
   End Property
   
   '================================================================================================='
   Public Property Get ConfigManagerUserConfig
      ConfigManagerUserConfig = m_oItem.ConfigManagerUserConfig
   End Property
   
   '================================================================================================='
   Public Property Get CreationClassName
      CreationClassName = m_oItem.CreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get Description
      Description = m_oItem.Description
   End Property
   
   '================================================================================================='
   Public Property Get DeviceID
      DeviceID = m_oItem.DeviceID
   End Property
   
   '================================================================================================='
   Public Property Get ErrorCleared
      ErrorCleared = m_oItem.ErrorCleared
   End Property
   
   '================================================================================================='
   Public Property Get ErrorDescription
      ErrorDescription = m_oItem.ErrorDescription
   End Property
   
   '================================================================================================='
   Public Property Get InstallDate
      InstallDate = m_oItem.InstallDate
   End Property
   
   '================================================================================================='
   Public Property Get LastErrorCode
      LastErrorCode = m_oItem.LastErrorCode
   End Property
   
   '================================================================================================='
   Public Property Get Name
      Name = m_oItem.Name
   End Property
   
   '================================================================================================='
   Public Property Get PNPDeviceID
      PNPDeviceID = m_oItem.PNPDeviceID
   End Property
   
   '================================================================================================='
   Public Property Get PowerManagementCapabilities
      PowerManagementCapabilities = m_oItem.PowerManagementCapabilities
   End Property
   
   '================================================================================================='
   Public Property Get PowerManagementSupported
      PowerManagementSupported = m_oItem.PowerManagementSupported
   End Property
   
   '================================================================================================='
   Public Property Get Status
      Status = m_oItem.Status
   End Property
   
   '================================================================================================='
   Public Property Get StatusInfo
      StatusInfo = m_oItem.StatusInfo
   End Property
   
   '================================================================================================='
   Public Property Get SystemCreationClassName
      SystemCreationClassName = m_oItem.SystemCreationClassName
   End Property
   
   '================================================================================================='
   Public Property Get SystemName
      SystemName = m_oItem.SystemName
   End Property
   
   '####################################### WMI Methods #############################################'
      
End Class
'<!-- CRC = 0x6fdda640 --->
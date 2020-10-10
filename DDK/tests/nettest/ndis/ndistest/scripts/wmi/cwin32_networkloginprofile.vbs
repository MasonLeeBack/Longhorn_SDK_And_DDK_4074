Option Explicit

Class CWin32_NetworkLoginProfile
   
   Private m_sComputer
   Private m_oWMIService
   Private m_oProfiles
   Private m_oProfile
   Private m_nCurrent
   Private m_sQuery
     
   Private m_oCollection  
   '================================================================================================='
   Public Sub Class_Initialize()
      
      m_nCurrent        = 0
      m_sComputer       = "."
      m_sQuery          = "SELECT * FROM Win32_NetworkLoginProfile"
      
      Set m_oWMIService = Nothing
      Set m_oProfiles	= Nothing
      Set m_oProfile    = Nothing      
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")
      Set m_oCollection = CreateObject("Scripting.Dictionary")
            
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
      
      Set m_oWMIService = Nothing
      Set m_oProfiles	= Nothing
      Set m_oProfile    = Nothing
      
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
      
      Set m_oProfiles  = m_oWMIService.ExecQuery(m_sQuery,"WQL",0)
     
      ' Check For Error
      If(Err.Number <> 0) Then
         vbQuery = Err.Number
         Exit Function
      Else
         vbQuery = Err.Number
      End If
      
      For Each oProcess In m_oProfiles
         
         nIndex = nIndex + 1
         m_oCollection.Add nIndex, oProcess
                 
      Next
      
      If(m_oCollection.Count = 0) Then
         vbQuery = WBEM_ERR_FAILED
         Exit Function
      End If
      
      ' Set the process to the first process in the collection
      Set m_oProfile = m_oCollection.Item(1)
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
      
      Set m_oProfile = m_oCollection.Item(m_nCurrent)
                  
   End Function   
   
   '###################################### WMI Properties ###########################################'
     
   '================================================================================================='
   Public Property Get AccountExpires
      AccountExpires = m_oProfile.AccountExpires
   End Property
   
   '================================================================================================='
   Public Property Get AuthorizationFlags
      AuthorizationFlags = m_oProfile.AuthorizationFlags
   End Property
   
   '================================================================================================='
   Public Property Get BadPasswordCount
      BadPasswordCount = m_oProfile.BadPasswordCount
   End Property
   
   '================================================================================================='
   Public Property Get Caption
      Caption = m_oProfile.Caption
   End Property
   
   '================================================================================================='
   Public Property Get CodePage
      CodePage = m_oProfile.CodePage
   End Property
   
   '================================================================================================='
   Public Property Get Comment
      Comment = m_oProfile.Comment
   End Property
   
   '================================================================================================='
   Public Property Get CountryCode
      CountryCode = m_oProfile.CountryCode
   End Property
   
   '================================================================================================='
   Public Property Get Description
      Description = m_oProfile.Description
   End Property
   
   '================================================================================================='
   Public Property Get Flags
      Flags = m_oProfile.Flags
   End Property
   
   '================================================================================================='
   Public Property Get FullName
      FullName = m_oProfile.FullName
   End Property
   
   '================================================================================================='
   Public Property Get HomeDirectory
      HomeDirectory = m_oProfile.HomeDirectory
   End Property
   
   '================================================================================================='
   Public Property Get HomeDirectoryDrive
      HomeDirectoryDrive = m_oProfile.HomeDirectoryDrive
   End Property
   
   '================================================================================================='
   Public Property Get LastLogoff
      LastLogoff = m_oProfile.LastLogoff
   End Property
   
   '================================================================================================='
   Public Property Get LastLogon
      LastLogon = m_oProfile.LastLogon
   End Property
   
      
   '================================================================================================='
   Public Property Get LogonHours
      LogonHours = m_oProfile.LogonHours
   End Property
   
   '================================================================================================='
   Public Property Get LogonServer
      LogonServer = m_oProfile.LogonServer
   End Property
   
   '================================================================================================='
   Public Property Get MaximumStorage
      MaximumStorage = m_oProfile.MaximumStorage
   End Property
   
   '================================================================================================='
   Public Property Get Name
      Name = m_oProfile.Name
   End Property
   
   '================================================================================================='
   Public Property Get NumberOfLogons
      NumberOfLogons = m_oProfile.NumberOfLogons
   End Property
   
   '================================================================================================='
   Public Property Get Parameters
      Parameters = m_oProfile.Parameters
   End Property
   
   '================================================================================================='
   Public Property Get PasswordAge
      PasswordAge = m_oProfile.PasswordAge
   End Property
   
   '================================================================================================='
   Public Property Get PasswordExpires
      PasswordExpires = m_oProfile.PasswordExpires
   End Property
   
   '================================================================================================='
   Public Property Get PrimaryGroupId
      PrimaryGroupId = m_oProfile.PrimaryGroupId
   End Property
   
   '================================================================================================='
   Public Property Get Privileges
      Privileges = m_oProfile.Privileges
   End Property
   
   '================================================================================================='
   Public Property Get Profile
      Profile = m_oProfile.Profile
   End Property
   
   '================================================================================================='
   Public Property Get ScriptPath
      ScriptPath = m_oProfile.ScriptPath
   End Property
   
   '================================================================================================='
   Public Property Get SettingID
      SettingID = m_oProfile.SettingID
   End Property
   
   '================================================================================================='
   Public Property Get UnitsPerWeek
      UnitsPerWeek = m_oProfile.UnitsPerWeek
   End Property
   
   '================================================================================================='
   Public Property Get UserComment
      UserComment = m_oProfile.UserComment
   End Property
   
   '================================================================================================='
   Public Property Get UserId
      UserId = m_oProfile.UserId
   End Property
   
   '================================================================================================='
   Public Property Get UserType
      UserType = m_oProfile.UserType
   End Property
   
   '================================================================================================='
   Public Property Get Workstations
      Workstations = m_oProfile.Workstations
   End Property
     
   '####################################### WMI Methods #############################################'
      
End Class
'<!-- CRC = 0xa98e40e3 --->
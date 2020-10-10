Option Explicit

Class CWin32_BIOS
   
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
      m_sQuery          = "SELECT * FROM Win32_BIOS"
      
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
   Public Property Get BiosCharacteristics
      BiosCharacteristics = m_oItem.BiosCharacteristics
   End Property
   
   '================================================================================================='
   Public Property Get BuildNumber
      BuildNumber = m_oItem.BuildNumber
   End Property
   
   '================================================================================================='
   Public Property Get Caption
      Caption = m_oItem.Caption
   End Property
   
   '================================================================================================='
   Public Property Get CodeSet
      CodeSet = m_oItem.CodeSet
   End Property
   
   '================================================================================================='
   Public Property Get CurrentLanguage
      CurrentLanguage = m_oItem.CurrentLanguage
   End Property
   
   '================================================================================================='
   Public Property Get Description
      Description = m_oItem.Description
   End Property
   
   '================================================================================================='
   Public Property Get IdentificationCode
      IdentificationCode = m_oItem.IdentificationCode
   End Property
   
   '================================================================================================='
   Public Property Get InstallableLanguages
      InstallableLanguages = m_oItem.InstallableLanguages
   End Property
   
   '================================================================================================='
   Public Property Get InstallDate
      InstallDate = m_oItem.InstallDate
   End Property
   
   '================================================================================================='
   Public Property Get LanguageEdition
      LanguageEdition = m_oItem.LanguageEdition
   End Property
   
   '================================================================================================='
   Public Property Get ListOfLanguages
      ListOfLanguages = m_oItem.ListOfLanguages
   End Property
   
   '================================================================================================='
   Public Property Get Manufacturer
      Manufacturer = m_oItem.Manufacturer
   End Property
   
   '================================================================================================='
   Public Property Get Name
      Name = m_oItem.Name
   End Property
   
   '================================================================================================='
   Public Property Get OtherTargetOS
      OtherTargetOS = m_oItem.OtherTargetOS
   End Property
   
   '================================================================================================='
   Public Property Get PrimaryBIOS
      PrimaryBIOS = m_oItem.PrimaryBIOS
   End Property
   
   '================================================================================================='
   Public Property Get ReleaseDate
      ReleaseDate = m_oItem.ReleaseDate
   End Property
   
   '================================================================================================='
   Public Property Get SerialNumber
      SerialNumber = m_oItem.SerialNumber
   End Property
   
   '================================================================================================='
   Public Property Get SMBIOSBIOSVersion
      SMBIOSBIOSVersion = m_oItem.SMBIOSBIOSVersion
   End Property
   
   '================================================================================================='
   Public Property Get SMBIOSMajorVersion
      SMBIOSMajorVersion = m_oItem.SMBIOSMajorVersion
   End Property
   
   '================================================================================================='
   Public Property Get SMBIOSMinorVersion
      SMBIOSMinorVersion = m_oItem.SMBIOSMinorVersion
   End Property
   
   '================================================================================================='
   Public Property Get SMBIOSPresent
      SMBIOSPresent = m_oItem.SMBIOSPresent
   End Property
   
   '================================================================================================='
   Public Property Get SoftwareElementID
      SoftwareElementID = m_oItem.SoftwareElementID
   End Property
   
   '================================================================================================='
   Public Property Get SoftwareElementState
      SoftwareElementState = m_oItem.SoftwareElementState
   End Property
   
   '================================================================================================='
   Public Property Get Status
      Status = m_oItem.Status
   End Property
   
   '================================================================================================='
   Public Property Get TargetOperatingSystem
      TargetOperatingSystem = m_oItem.TargetOperatingSystem
   End Property
   
   '================================================================================================='
   Public Property Get Version
      Version = m_oItem.Version
   End Property
   
   '####################################### WMI Methods #############################################'
      
End Class
'<!-- CRC = 0x109eab9a --->
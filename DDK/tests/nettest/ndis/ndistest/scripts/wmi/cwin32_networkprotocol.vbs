Option Explicit

Class CWin32_NetworkProtocol
   
   Private m_sComputer
   Private m_oWMIService
   Private m_oProtocols
   Private m_oProtocol
   Private m_nCurrent
   Private m_sQuery
     
   Private m_oCollection  
   '================================================================================================='
   Public Sub Class_Initialize()
      
      m_nCurrent        = 0
      m_sComputer       = "."
      m_sQuery          = "SELECT * FROM Win32_NetworkProtocol"
      
      Set m_oWMIService = Nothing
      Set m_oProtocols	= Nothing
      Set m_oProtocol    = Nothing      
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")
      Set m_oCollection = CreateObject("Scripting.Dictionary")
            
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
      
      Set m_oWMIService = Nothing
      Set m_oProtocols	= Nothing
      Set m_oProtocol    = Nothing
      
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
      
      Set m_oProtocols  = m_oWMIService.ExecQuery(m_sQuery,"WQL",0)
     
      ' Check For Error
      If(Err.Number <> 0) Then
         vbQuery = Err.Number
         Exit Function
      Else
         vbQuery = Err.Number
      End If
      
      For Each oProcess In m_oProtocols
         
         nIndex = nIndex + 1
         m_oCollection.Add nIndex, oProcess
                 
      Next
      
      If(m_oCollection.Count = 0) Then
         vbQuery = WBEM_ERR_FAILED
         Exit Function
      End If
      
      ' Set the process to the first process in the collection
      Set m_oProtocol = m_oCollection.Item(1)
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
      
      Set m_oProtocol = m_oCollection.Item(m_nCurrent)
                  
   End Function   
   
   '###################################### WMI Properties ###########################################'
     
   '================================================================================================='
   Public Property Get Caption
      Caption = m_oProtocol.Caption
   End Property
   
   '================================================================================================='
   Public Property Get ConnectionlessService
      ConnectionlessService = m_oProtocol.ConnectionlessService
   End Property
   
   '================================================================================================='
   Public Property Get Description
      Description = m_oProtocol.Description
   End Property
   
   '================================================================================================='
   Public Property Get GuaranteesDelivery
      GuaranteesDelivery = m_oProtocol.GuaranteesDelivery
   End Property
   
   '================================================================================================='
   Public Property Get GuaranteesSequencing
      GuaranteesSequencing = m_oProtocol.GuaranteesSequencing
   End Property
   
   '================================================================================================='
   Public Property Get InstallDate
      InstallDate = m_oProtocol.InstallDate
   End Property
   
   '================================================================================================='
   Public Property Get MaximumAddressSize
      MaximumAddressSize = m_oProtocol.MaximumAddressSize
   End Property
   
   '================================================================================================='
   Public Property Get MaximumMessageSize
      MaximumMessageSize = m_oProtocol.MaximumMessageSize
   End Property
   
   '================================================================================================='
   Public Property Get MessageOriented
      MessageOriented = m_oProtocol.MessageOriented
   End Property
   
   '================================================================================================='
   Public Property Get MinimumAddressSize
      MinimumAddressSize = m_oProtocol.MinimumAddressSize
   End Property
   
   '================================================================================================='
   Public Property Get Name
      Name = m_oProtocol.Name
   End Property
   
   '================================================================================================='
   Public Property Get PseudoStreamOriented
      PseudoStreamOriented = m_oProtocol.PseudoStreamOriented
   End Property
   
   '================================================================================================='
   Public Property Get Status
      Status = m_oProtocol.Status
   End Property
   
   '================================================================================================='
   Public Property Get SupportsBroadcasting
      SupportsBroadcasting = m_oProtocol.SupportsBroadcasting
   End Property
   
      
   '================================================================================================='
   Public Property Get SupportsConnectData
      SupportsConnectData = m_oProtocol.SupportsConnectData
   End Property
   
   '================================================================================================='
   Public Property Get SupportsDisconnectData
      SupportsDisconnectData = m_oProtocol.SupportsDisconnectData
   End Property
   
   '================================================================================================='
   Public Property Get SupportsEncryption
      SupportsEncryption = m_oProtocol.SupportsEncryption
   End Property
   
   '================================================================================================='
   Public Property Get SupportsExpeditedData
      SupportsExpeditedData = m_oProtocol.SupportsExpeditedData
   End Property
   
   '================================================================================================='
   Public Property Get SupportsFragmentation
      SupportsFragmentation = m_oProtocol.SupportsFragmentation
   End Property
   
   '================================================================================================='
   Public Property Get SupportsGracefulClosing
      SupportsGracefulClosing = m_oProtocol.SupportsGracefulClosing
   End Property
   
   '================================================================================================='
   Public Property Get SupportsGuaranteedBandwidth
      SupportsGuaranteedBandwidth = m_oProtocol.SupportsGuaranteedBandwidth
   End Property
   
   '================================================================================================='
   Public Property Get SupportsMulticasting
      SupportsMulticasting = m_oProtocol.SupportsMulticasting
   End Property
   
   '================================================================================================='
   Public Property Get SupportsQualityofService
      SupportsQualityofService = m_oProtocol.SupportsQualityofService
   End Property
           
   '####################################### WMI Methods #############################################'
      
End Class
'<!-- CRC = 0x4e5d5fd5 --->
Option Explicit

Class CWin32_NetworkAdapterConfiguration
   
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
      m_sQuery          = "SELECT * FROM Win32_NetworkAdapterConfiguration"
      
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
   Public Property Get ArpAlwaysSourceRoute
      ArpAlwaysSourceRoute = m_oAdapter.ArpAlwaysSourceRoute
   End Property
   
   '================================================================================================='
   Public Property Get ArpUseEtherSNAP
      ArpUseEtherSNAP = m_oAdapter.ArpUseEtherSNAP
   End Property
   
   '================================================================================================='
   Public Property Get Caption
      Caption = m_oAdapter.Caption
   End Property
   
   '================================================================================================='
   Public Property Get DatabasePath
      DatabasePath = m_oAdapter.DatabasePath
   End Property
   
   '================================================================================================='
   Public Property Get DeadGWDetectEnabled
      DeadGWDetectEnabled = m_oAdapter.DeadGWDetectEnabled
   End Property
   
   '================================================================================================='
   Public Property Get DefaultIPGateway
      DefaultIPGateway = m_oAdapter.DefaultIPGateway
   End Property
   
   '================================================================================================='
   Public Property Get DefaultTOS
      DefaultTOS = m_oAdapter.DefaultTOS
   End Property
   
   '================================================================================================='
   Public Property Get DefaultTTL
      DefaultTTL = m_oAdapter.DefaultTTL
   End Property
   
   '================================================================================================='
   Public Property Get Description
      Description = m_oAdapter.Description
   End Property
   
   '================================================================================================='
   Public Property Get DHCPEnabled
      DHCPEnabled = m_oAdapter.DHCPEnabled
   End Property
   
   '================================================================================================='
   Public Property Get DHCPLeaseExpires
      DHCPLeaseExpires = m_oAdapter.DHCPLeaseExpires
   End Property
   
   '================================================================================================='
   Public Property Get DHCPLeaseObtained
      DHCPLeaseObtained = m_oAdapter.DHCPLeaseObtained
   End Property
   
   '================================================================================================='
   Public Property Get DHCPServer
      DHCPServer = m_oAdapter.DHCPServer
   End Property
   
   '================================================================================================='
   Public Property Get DNSDomain
      DNSDomain = m_oAdapter.DNSDomain
   End Property
         
   '================================================================================================='
   Public Property Get DNSDomainSuffixSearchOrder
      DNSDomainSuffixSearchOrder = m_oAdapter.DNSDomainSuffixSearchOrder
   End Property
   
   '================================================================================================='
   Public Property Get DNSEnabledForWINSResolution
      DNSEnabledForWINSResolution = m_oAdapter.DNSEnabledForWINSResolution
   End Property
   
   '================================================================================================='
   Public Property Get DNSHostName
      DNSHostName = m_oAdapter.DNSHostName
   End Property
   
   '================================================================================================='
   Public Property Get DNSServerSearchOrder
      DNSServerSearchOrder = m_oAdapter.DNSServerSearchOrder
   End Property
   
   '================================================================================================='
   Public Property Get ForwardBufferMemory
      ForwardBufferMemory = m_oAdapter.ForwardBufferMemory
   End Property
   
   '================================================================================================='
   Public Property Get GatewayCostMetric
      GatewayCostMetric = m_oAdapter.GatewayCostMetric
   End Property
   
   '================================================================================================='
   Public Property Get IGMPLevel
      IGMPLevel = m_oAdapter.IGMPLevel
   End Property
   
   '================================================================================================='
   Public Property Get Index
      Index = m_oAdapter.Index
   End Property
   
   '================================================================================================='
   Public Property Get IPAddress
      IPAddress = m_oAdapter.IPAddress
   End Property
   
   '================================================================================================='
   Public Property Get IPEnabled
      IPEnabled = m_oAdapter.IPEnabled
   End Property
   
   '================================================================================================='
   Public Property Get IPFilterSecurityEnabled
      IPFilterSecurityEnabled = m_oAdapter.IPFilterSecurityEnabled
   End Property
   
   '================================================================================================='
   Public Property Get IPPortSecurityEnabled
      IPPortSecurityEnabled = m_oAdapter.IPPortSecurityEnabled
   End Property
   
   '================================================================================================='
   Public Property Get IPSecPermitIPProtocols
      IPSecPermitIPProtocols = m_oAdapter.IPSecPermitIPProtocols
   End Property
   
   '================================================================================================='
   Public Property Get IPSecPermitTCPPorts
      IPSecPermitTCPPorts = m_oAdapter.IPSecPermitTCPPorts
   End Property
   
   '================================================================================================='
   Public Property Get IPSecPermitUDPPorts
      IPSecPermitUDPPorts = m_oAdapter.IPSecPermitUDPPorts
   End Property
   
   '================================================================================================='
   Public Property Get IPSubnet
      IPSubnet = m_oAdapter.IPSubnet
   End Property
   
   '================================================================================================='
   Public Property Get IPUseZeroBroadcast
      IPUseZeroBroadcast = m_oAdapter.IPUseZeroBroadcast
   End Property
   
   '================================================================================================='
   Public Property Get IPXAddress
      IPXAddress = m_oAdapter.IPXAddress
   End Property
   
   '================================================================================================='
   Public Property Get IPXEnabled
      IPXEnabled = m_oAdapter.IPXEnabled
   End Property
   
   '================================================================================================='
   Public Property Get IPXFrameType
      IPXFrameType = m_oAdapter.IPXFrameType
   End Property
   
   '================================================================================================='
   Public Property Get IPXMediaType
      IPXMediaType = m_oAdapter.IPXMediaType
   End Property
   
   '================================================================================================='
   Public Property Get IPXNetworkNumber
      IPXNetworkNumber = m_oAdapter.IPXNetworkNumber
   End Property
   
   '================================================================================================='
   Public Property Get IPXVirtualNetNumber
      IPXVirtualNetNumber = m_oAdapter.IPXVirtualNetNumber
   End Property
   
   '================================================================================================='
   Public Property Get KeepAliveInterval
      KeepAliveInterval = m_oAdapter.KeepAliveInterval
   End Property
   
   '================================================================================================='
   Public Property Get KeepAliveTime
      KeepAliveTime = m_oAdapter.KeepAliveTime
   End Property
   
   '================================================================================================='
   Public Property Get MACAddress
      MACAddress = m_oAdapter.MACAddress
   End Property
   
   '================================================================================================='
   Public Property Get MTU
      MTU = m_oAdapter.MTU
   End Property
   
   '================================================================================================='
   Public Property Get NumForwardPackets
      NumForwardPackets = m_oAdapter.NumForwardPackets
   End Property
   
   '================================================================================================='
   Public Property Get PMTUBHDetectEnabled
      PMTUBHDetectEnabled = m_oAdapter.PMTUBHDetectEnabled
   End Property
   
   '================================================================================================='
   Public Property Get PMTUDiscoveryEnabled
      PMTUDiscoveryEnabled = m_oAdapter.PMTUDiscoveryEnabled
   End Property
   
   '================================================================================================='
   Public Property Get ServiceName
      ServiceName = m_oAdapter.ServiceName
   End Property
   
   '================================================================================================='
   Public Property Get SettingID
      SettingID = m_oAdapter.SettingID
   End Property
   
   '================================================================================================='
   Public Property Get TcpMaxConnectRetransmissions
      TcpMaxConnectRetransmissions = m_oAdapter.TcpMaxConnectRetransmissions
   End Property
   
   '================================================================================================='
   Public Property Get TcpMaxDataRetransmissions
      TcpMaxDataRetransmissions = m_oAdapter.TcpMaxDataRetransmissions
   End Property
   
   '================================================================================================='
   Public Property Get TcpNumConnections
      TcpNumConnections = m_oAdapter.TcpNumConnections
   End Property
   
   '================================================================================================='
   Public Property Get TcpUseRFC1122UrgentPointer
      TcpUseRFC1122UrgentPointer = m_oAdapter.TcpUseRFC1122UrgentPointer
   End Property
   
   '================================================================================================='
   Public Property Get TcpWindowSize
      TcpWindowSize = m_oAdapter.TcpWindowSize
   End Property    
   
   '================================================================================================='
   Public Property Get WINSEnableLMHostsLookup
      WINSEnableLMHostsLookup = m_oAdapter.WINSEnableLMHostsLookup
   End Property    
   
   '================================================================================================='
   Public Property Get WINSHostLookupFile
      WINSHostLookupFile = m_oAdapter.WINSHostLookupFile
   End Property    
   
   '================================================================================================='
   Public Property Get WINSPrimaryServer
      WINSPrimaryServer = m_oAdapter.WINSPrimaryServer
   End Property    
   
   '================================================================================================='
   Public Property Get WINSScopeID
      WINSScopeID = m_oAdapter.WINSScopeID
   End Property    
   
   '================================================================================================='
   Public Property Get WINSSecondaryServer
      WINSSecondaryServer = m_oAdapter.WINSSecondaryServer
   End Property    
   
   '####################################### WMI Methods #############################################'
   
   '================================================================================================='
   Public Function EnableDHCP()
      EnableDHCP = m_oAdapter.EnableDHCP()
   End Function
   
   '================================================================================================='
   Public Function RenewDHCPLease()
      RenewDHCPLease = m_oAdapter.RenewDHCPLease()
   End Function
   
   '================================================================================================='
   Public Function RenewDHCPLeaseAll()
      RenewDHCPLeaseAll = m_oAdapter.RenewDHCPLeaseAll()
   End Function
   
   '================================================================================================='
   Public Function ReleaseDHCPLease()
      ReleaseDHCPLease = m_oAdapter.ReleaseDHCPLease()
   End Function
   
   '================================================================================================='
   Public Function ReleaseDHCPLeaseAll()
      ReleaseDHCPLeaseAll = m_oAdapter.ReleaseDHCPLeaseAll()
   End Function
   
   '================================================================================================='
   Public Function EnableStatic(byval aIPAddress, byval sSubnetMask)
      EnableStatic = m_oAdapter.EnableStatic(aIPAddress, sSubnetMask)
   End Function
   
   '================================================================================================='
   Public Function SetGateways(byval sDefaultIPGateway, byval nGatewayCostMetric)
      SetGateways = m_oAdapter.SetGateways(sDefaultIPGateway, nGatewayCostMetric)
   End Function
   
   '================================================================================================='
   Public Function EnableDNS(byval sDNSHostName, byval sDNSDomain, byval aDNSServerSearchOrder, byval aDNSDomainSuffixSearchOrder)
      EnableDNS = m_oAdapter.EnableDNS(sDNSHostName, sDNSDomain, aDNSServerSearchOrder, aDNSDomainSuffixSearchOrder)
   End Function
   
   '================================================================================================='
   Public Function SetDNSDomain(byval sDNSDomain)
      SetDNSDomain = m_oAdapter.SetDNSDomain(sDNSDomain)
   End Function
   
   '================================================================================================='
   Public Function SetDNSServerSearchOrder(byval aDNSServerSearchOrder)
      SetDNSServerSearchOrder = m_oAdapter.SetDNSServerSearchOrder(aDNSServerSearchOrder)
   End Function
   
   '================================================================================================='
   Public Function SetDNSSuffixSearchOrder(byval aDNSDomainSuffixSearchOrder)
      SetDNSSuffixSearchOrder = m_oAdapter.SetDNSSuffixSearchOrder(aDNSDomainSuffixSearchOrder)
   End Function
   
   '================================================================================================='
   Public Function SetWINSServer(byval sWINSPrimaryServer, byval sWINSSecondaryServer)
      SetWINSServer = m_oAdapter.SetWINSServer(sWINSPrimaryServer, sWINSSecondaryServer)
   End Function
   
   '================================================================================================='
   Public Function EnableWINS(byval bDNSEnabledForWINSResolution, byval bWINSEnableLMHostsLookup, byval sWINSHostLookupFile, byval sWINSScopeID)
      EnableWINS = m_oAdapter.EnableWINS(bDNSEnabledForWINSResolution, bWINSEnableLMHostsLookup, sWINSHostLookupFile, sWINSScopeID)
   End Function
   
   '================================================================================================='
   Public Function EnableIPSec(byval sIPSecPermitTCPPorts, byval sIPSecPermitUDPPorts, byval sIPSecPermitIPProtocols)
      EnableIPSec = m_oAdapter.EnableIPSec(sIPSecPermitTCPPorts, sIPSecPermitUDPPorts, sIPSecPermitIPProtocols)
   End Function
   
   '================================================================================================='
   Public Function DisableIPSec()
      DisableIPSec = m_oAdapter.DisableIPSec()
   End Function
   
   '================================================================================================='
   Public Function SetIPXVirtualNetworkNumber(byval sIPXVirtualNetNumber)
      SetIPXVirtualNetworkNumber = m_oAdapter.SetIPXVirtualNetworkNumber(sIPXVirtualNetNumber)
   End Function
   
   '================================================================================================='
   Public Function SetIPXFrameTypeNetworkPairs(byval aIPXNetworkNumber, byval nIPXFrameType)
      SetIPXFrameTypeNetworkPairs = m_oAdapter.SetIPXFrameTypeNetworkPairs(aIPXNetworkNumber, nIPXFrameType)
   End Function
   
   '================================================================================================='
   Public Function SetDatabasePath(byval sDatabasePath)
      SetDatabasePath = m_oAdapter.SetDatabasePath(sDatabasePath)
   End Function
   
   '================================================================================================='
   Public Function SetIPUseZeroBroadcast(byval bIPUseZeroBroadcast)
      SetIPUseZeroBroadcast = m_oAdapter.SetIPUseZeroBroadcast(bIPUseZeroBroadcast)
   End Function
   
   '================================================================================================='
   Public Function SetArpAlwaysSourceRoute(byval bArpAlwaysSourceRoute)
      SetArpAlwaysSourceRoute = m_oAdapter.SetArpAlwaysSourceRoute(bArpAlwaysSourceRoute)
   End Function
   
   '================================================================================================='
   Public Function SetArpUseEtherSNAP(byval bArpUseEtherSNAP)
      SetArpUseEtherSNAP = m_oAdapter.SetArpUseEtherSNAP(bArpUseEtherSNAP)
   End Function
   
   '================================================================================================='
   Public Function SetDefaultTOS(byval nDefaultTOS)
      SetDefaultTOS = m_oAdapter.SetDefaultTOS(nDefaultTOS)
   End Function
   
   '================================================================================================='
   Public Function SetDefaultTTL(byval nDefaultTTL)
      SetDefaultTTL = m_oAdapter.SetDefaultTTL(nDefaultTTL)
   End Function
   
   '================================================================================================='
   Public Function SetDeadGWDetect(byval bDeadGWDetectEnabled)
      SetDeadGWDetect = m_oAdapter.SetDeadGWDetect(bDeadGWDetectEnabled)
   End Function
   
   '================================================================================================='
   Public Function SetPMTUBHDetect(byval bPMTUBHDetectEnabled)
      SetPMTUBHDetect = m_oAdapter.SetPMTUBHDetect(bPMTUBHDetectEnabled)
   End Function
   
   '================================================================================================='
   Public Function SetPMTUDiscovery(byval bPMTUDiscoveryEnabled)
      SetPMTUDiscovery = m_oAdapter.SetPMTUDiscovery(bPMTUDiscoveryEnabled)
   End Function
   
   '================================================================================================='
   Public Function SetForwardBufferMemory(byval nForwardBufferMemory)
      SetForwardBufferMemory = m_oAdapter.SetForwardBufferMemory(nForwardBufferMemory)
   End Function
   
   '================================================================================================='
   Public Function SetIGMPLevel(byval nIGMPLevel)
      SetIGMPLevel = m_oAdapter.SetIGMPLevel(nIGMPLevel)
   End Function
   
   '================================================================================================='
   Public Function SetKeepAliveInterval(byval nKeepAliveInterval)
      SetKeepAliveInterval = m_oAdapter.SetKeepAliveInterval(nKeepAliveInterval)
   End Function
   
   '================================================================================================='
   Public Function SetKeepAliveTime(byval nKeepAliveTime)
      SetKeepAliveTime = m_oAdapter.SetKeepAliveTime(nKeepAliveTime)
   End Function
   
   '================================================================================================='
   Public Function SetMTU(byval nMTU)
      SetMTU = m_oAdapter.SetMTU(nMTU)
   End Function
   
   '================================================================================================='
   Public Function SetNumForwardPackets(byval nNumForwardPackets)
      SetNumForwardPackets = m_oAdapter.SetNumForwardPackets(nNumForwardPackets)
   End Function
   
   '================================================================================================='
   Public Function SetTcpMaxConnectRetransmissions(byval nTcpMaxConnectRetransmissions)
      SetTcpMaxConnectRetransmissions = m_oAdapter.SetTcpMaxConnectRetransmissions(nTcpMaxConnectRetransmissions)
   End Function
   
   '================================================================================================='
   Public Function SetTcpMaxDataRetransmissions(byval nTcpMaxDataRetransmissions)
      SetTcpMaxDataRetransmissions = m_oAdapter.SetTcpMaxDataRetransmissions(nTcpMaxDataRetransmissions)
   End Function
   
   '================================================================================================='
   Public Function SetTcpNumConnections(byval nTcpNumConnections)
      SetTcpNumConnections = m_oAdapter.SetTcpNumConnections(nTcpNumConnections)
   End Function
   
   '================================================================================================='
   Public Function SetTcpUseRFC1122UrgentPointer(byval bTcpUseRFC1122UrgentPointer)
      SetTcpUseRFC1122UrgentPointer = m_oAdapter.SetTcpUseRFC1122UrgentPointer(bTcpUseRFC1122UrgentPointer)
   End Function
   
   '================================================================================================='
   Public Function SetTcpWindowSize(byval nTcpWindowSize)
      SetTcpWindowSize = m_oAdapter.SetTcpWindowSize(nTcpWindowSize)
   End Function
   
   '================================================================================================='
   Public Function EnableIPFilterSec(byval bIPFilterSecurityEnabled)
      EnableIPFilterSec = m_oAdapter.EnableIPFilterSec(bIPFilterSecurityEnabled)
   End Function
      
End Class
'<!-- CRC = 0xe01e9cec --->
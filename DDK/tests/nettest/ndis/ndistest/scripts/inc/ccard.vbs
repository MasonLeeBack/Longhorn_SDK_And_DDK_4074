

Option Explicit


' This is the global instance of CTestVars used by
' the CCard and COpen classes.
Dim TestVarsObj


'============================================================================================='
'/**
' This class encapsulates the functionality of an Adapter. This object is created
' for each adapter we want to work with and use this object to create Opens on the
' Adapter. CCard keeps track of the Opens made on the adapter for us. It also stores 
' Adapter level properties like the IP Address and Gateway address etc. for the device.
'@author    Adeel Siddiqui (adeels)
'@date      7/13/2001
'@keyword   Adapter,Open,IPAddress,GatewayAddress
'*/
Class CCard
    Private m_Adapter        ' store the instance of adapter created for this card
    Private m_sAdapterName   ' The representation for adapter name! Use for debugging
    Private m_OpenArray      ' A dynamic array to hold instances of open on this card
    Private m_nNumOpen       ' The total number of current opens
    Private m_sIPAddress     ' IP Address for a given adapter
    Private m_GatewayAddress ' MAC Address of the Gateway
    
    Public Sub Class_initialize
'        Set m_OpenArray = Nothing
        Set m_Adapter = Nothing
        m_nNumOpen = 0                ' Initially no opens
        m_GatewayAddress = Array(CByte(0),CByte(0),CByte(0),CByte(0),CByte(0),CByte(0))
        m_sIPAddress = "0.0.0.0"
        
        ' Construct the CTestVar Object
        If (IsEmpty (TestVarsObj)) Then
            Set TestVarsObj = new CTestVars
        End If        
    End Sub
    
    
    '============================================================================================='
    '/**
    '@exclude
    'This is the class destructor which is called to perform cleanup.
    'It deallocates all the Opens made on this Adapter. This automatically
    'invokes NdisClose to be performed on them
    '*/    
    Public Sub Class_Terminate ()
        Dim i
        For i=0 to m_nNumOpen - 1
            If Not (m_OpenArray (i) Is Nothing) Then
                Set m_OpenArray (i) = Nothing
            end if
        Next
    End Sub
    
    '============================================================================================='
    '/**
    'This method is used to retrieve a reference to COM COpen object opened on this adapter.
    '@param lOpenIndex     Index of the Open we want. First Open made is on Index 0 and so on
    '@return Reference of type COpen (COM Object) to the Open specified by lOpenIndex
    '@sa COpen::NdisOpen
    '@code
    'Set ClientOpen = TestCardObj.GetNdisOpen (0)
    'Set SupportOpen = SupportCardObj.GetNdisOpen (0)
    '*/        
    Public Function GetNdisOpen (lOpenIndex)
        if (lOpenIndex > UBound (m_OpenArray)) Then      ' if an invalid index given
            Set GetNdisOpen = Nothing
        else
            Set GetNdisOpen = m_OpenArray(lOpenIndex).NdisOpen  ' return the Open Instance
        End If
    End Function
    
    
    Property Get Adapter ()
        Set Adapter = m_Adapter
    End Property
    
    Property Get GatewayAddress ()
        GatewayAddress = m_GatewayAddress
    End Property
    
    Property Get IPAddress ()
        IPAddress = m_sIPAddress
    End Property
    
    Property Get OpenArray ()
        Set OpenArray = m_OpenArray
    end Property
    
    Property Get NumOpen ()
        NumOpen = m_nNumOpen
    end Property
    
    
    '============================================================================================='
    '/**
    'Use this API to create an instance of Open on an Adapter and do an NdisOpen on
    'that instance. This API is generally helpful in getting a test off to a quick start
    'as almost all tests create atleast one instance of NdisOpen to work with.
    'Internally this API simply calls CCard::CreateAdapter followed by CCard::CreateOpen.
    '@param Adapter  Instance of Adapter usually obtained from NDInfo.AdapterList
    '@return On success, an instance of COpen object opened on the adapter. On failure,
    'this API returns Nothing
    '@sa CCard::CreateAdapter,CreateOpen
    '@code
    'Dim TestCardObj, TestOpenObj
    'Set TestCardObj = new CCard
    'Set TestOpenObj = TestCardObj.SetupBasicTest (oNDInfo.AdapterList (0))
    '*/        
    Public Function SetupBasicTest (Adapter)
        If Adapter.AdapterType = 1 Then
            m_sAdapterName = "Test Adapter"
        Else
            m_sAdapterName = "Support Adapter"
        End If
        
        Set SetupBasicTest = CreateAdapter (Adapter)
        If (not (SetupBasicTest Is Nothing)) Then
            Set SetupBasicTest = CreateOpen ()
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    'This API is used to Create an Open on the Adapter Object. This API will also call an
    'NdisOpen on the created Open. Internally this function calls COpen::CreateOpen followed
    'by COpen::DoOpen.
    '@return Instance of COpen object created if successful, else Nothing
    '@sa COpen::QuickOpen,CreateOpen,DoOpen
    '@code
    'Set OpenTwoObj = SupportCardObj.CreateOpen ()
    'If (OpenTwoObj Is Nothing) Then
    '   Exit Function
    'End If
    '*/
    Public Function CreateOpen ()
        ' The new open instance on this card object
        Dim oOpen, nNdisMedium
        Set oOpen = new COpen
        
        ' Get NdisMedium which is needed for the NdisOpen call
        nNdisMedium = GetNdisMedium ()
        
        If (Not (oOpen.QuickOpen (m_Adapter, nNdisMedium, m_sAdapterName) Is Nothing)) Then
            ' Open succeeded. ReDim the array to required size
            If (IsEmpty (m_OpenArray)) Then
                ReDim m_OpenArray (m_nNumOpen)
            Else
                ReDim Preserve m_OpenArray (m_nNumOpen)
            End if
            Set m_OpenArray (m_nNumOpen) = oOpen
            m_nNumOpen = m_nNumOpen + 1
            Set CreateOpen = oOpen      ' return instance of OpenObj (not ndisopen)
        Else
            Set oOpen = Nothing         ' deallocate memory
            Set CreateOpen = Nothing    ' return failure
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    'This function creates an instance of COM Adapter object and stores it in the
    'm_Adapter member varaible.
    '@param Adapter  Instance of COM Adapter object obtained from NDInfo.AdapterList
    '@return The Adapter object created if successful, else returns Nothing
    '@code
    'If (TestCardObj.CreateAdapter (oNDInfo.AdapterList (0)) Is Nothing) Then
    '   oLog.Failed ("Failed to create Test Adapter object", 88888)
    '   Exit Function
    'End If
    '*/        
    Public Function CreateAdapter (Adapter)
        If Adapter.AdapterType = 1 Then         ' TEST ADAPTER
            m_sAdapterName = "Test Adapter"
        ElseIf Adapter.AdapterType = 2 Then     ' Support Adapter
            m_sAdapterName = "Support Adapter"
        Else
            m_sAdapterName = "Unknown Adapter"
        End If
        
        ' Create test adapter object
        Set m_Adapter = oNDTCore.CreateAdapter(Adapter)
        If (m_Adapter is Nothing) Then
            Call oLog.SafeFailed ("Failed to create " & m_sAdapterName & " object!", 22855)
        End If
        
        Set CreateAdapter = m_Adapter
    End Function
    
    ' This method creates calls IP helper APIs to get ip address and gateway's MAC Address
    Public Function SetGateWayIPAddress ()
        
        ' Create test adapter object
        SetGateWayIPAddress = m_Adapter.GetIPGateway(m_sIPAddress,m_GatewayAddress)
        If (not SetGateWayIPAddress) Then
            Call oLog.SafeFailed ("Failed to get IP and Gateway for " & m_sAdapterName & " adapter!", 22856)
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    'This method returns the Maximum Packet Size supported by the NIC. If the NIC reports
    'the MaxPacketSize as anything less than 40 bytes, or the query OID failes we log a 
    'safe error and report max packet size to the caller as being 50 bytes
    '@return The maximum packet size supported by the NIC
    '@code
    'nMaxPacketSize = TestCardObj.GetMaxPacketSize ()
    '*/        
    Public Function GetMaxPacketSize()
        Dim bResult, nMaxPacketSize
        bResult = QueryInfo(OID_GEN_MAXIMUM_TOTAL_SIZE, nMaxPacketSize, QUERY_GLOBAL_STATS)
        GetMaxPacketSize = nMaxPacketSize
        
        If(bResult) Then
            if (nMaxPacketSize < 40) Then
                Call oLog.SafeFailed ("Invalid MaxPacketSize = " & nMaxPacketSize & " received from " & m_sAdapterName, 22857)
                GetMaxPacketSize = 50
            End If
        Else
            Call oLog.SafeFailed ("Unable to get maximum total size for " & m_sAdapterName, 22858)
            GetMaxPacketSize = 50
        End If
    End Function
    
    '==========================================================================
    '/**
    'This method returns the address that the NIC is currently using
    '@return The address being used by the NIC
    '@code
    'CardAddr = TestCardObj.GetCardAddress ()
    '*/        
    Function GetCardAddress()
        Dim CardAddr, bResult
        Dim Media
        CardAddr = NullAddr()
        
        Media = GetNdisMedium ()
        
        Select Case Media
            Case NDISMEDIUM802_3
                bResult = QueryInfo(OID_802_3_CURRENT_ADDRESS, CardAddr, QUERY_GLOBAL_STATS)
                If (Not bResult) Then
                    call oLog.Failed ("Could not obtain address of " & m_sAdapterName, 22866)
                End If
            Case NDISMEDIUM802_5
                bResult = QueryInfo(OID_802_5_CURRENT_ADDRESS, CardAddr, QUERY_GLOBAL_STATS)
                If (Not bResult) Then
                    call oLog.Failed ("Could not obtain address of " & m_sAdapterName, 22867)
                End If
            Case NDISMEDIUMFDDI
                bResult = QueryInfo(OID_FDDI_LONG_CURRENT_ADDR, CardAddr, QUERY_GLOBAL_STATS)
                If (Not bResult) Then
                    call oLog.Failed ("Could not obtain address of " & m_sAdapterName, 22868)
                End If
            Case Else
                ' fail silently because this is caused during initialization
                ' call oLog.Failed ("GetCardAddress: Unknown media" , 22869)
        End Select
        GetCardAddress = CardAddr
    End Function
    
    '============================================================================================='
    '/**
    'This method is used to get the Physical Medium on which the test is running
    '@return The Physical Medium on success else return zero on failure or if 
    'OID_GEN_PHYSICAL_MEDIUM is not supported
    '@code
    'If (TestCardObj.GetPhysicalMedium () = 0 )Then
    '   oLog.Failed ("Failed to get Physical Medium", 88888)
    '   Exit Function
    'End If
    '*/
    Public Function GetPhysicalMedium()
        Dim locPhysicalMedium, bResult
        
        locPhysicalMedium = 0
        If (m_sAdapterName = "Test Adapter" And IsEmpty (TestVarsObj.PhysicalMedium)) Then
            bResult = QueryInfo(OID_GEN_PHYSICAL_MEDIUM, locPhysicalMedium, QUERY_GLOBAL_STATS)
            
            If (Not bResult) Then
                oLog.Write("Optional oid OID_GEN_PHYSICAL_MEDIUM is not supported for test adapter" )
                GetPhysicalMedium = 0
            ElseIf ((locPhysicalMedium > NDISPHYSICALMEDIUMRESERVED0) And (locPhysicalMedium < NDISPHYSICALMEDIUMMAX)) Then
                GetPhysicalMedium = locPhysicalMedium
                TestVarsObj.PhysicalMedium = locPhysicalMedium
            Else
                oLog.SafeWarned ("Query to OID_GEN_PHYSICAL_MEDIUM returned invalid medium for test adapter")
                GetPhysicalMedium = 0
            End If
        Else
            GetPhysicalMedium = TestVarsObj.PhysicalMedium
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    ' The amount of time that the sender should wait, before it can assume  the
    ' driver/adapter has atleast made an attempt to send all the packets that
    ' were given to it. This time depends on the media.
    '@return The receive delay
    '@code
    '       lRecvDelay = OpenOneObj.GetReceiveDelay()
    '*/
    Function GetReceiveDelay()
        Dim mReceiveDelay
        Dim Media
        
        Media = GetNdisMedium ()
        
        Select Case Media
            Case NDISMEDIUM802_3
                mReceiveDelay = 150
            Case NDISMEDIUM802_5
                mReceiveDelay = 100
            Case NDISMEDIUMFDDI
                mReceiveDelay = 50
                ' NDISMEDIUMIRDA - Added by Suyash Sinha for Irda tests
            Case NDISMEDIUMIRDA
                mReceiveDelay = 500
            Case Else
                oLog.Write("Receive Delay: Unsupported media" )
                mReceiveDelay = 0
        End Select
        GetReceiveDelay = mReceiveDelay
    End Function
    
    '============================================================================================='
    '/**
    ' Returns the broadcast address to be used with the particular media
    '@return The broadcast address
    '@code
    '       lBroadcastAddr = OpenOneObj.GetBroadcastAddress()
    '*/
    Function GetBroadcastAddress()
        Dim lBroadcastAddr
        Dim Media
        
        Media = GetNdisMedium ()
        
        Select Case Media
            Case NDISMEDIUM802_3
                lBroadcastAddr = NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&)
            Case NDISMEDIUM802_5
                lBroadcastAddr = NetAddr(&Hc0&, &H00&, &Hff&, &Hff&, &Hff&, &Hff&)
            Case NDISMEDIUMFDDI
                lBroadcastAddr = NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&)
            Case Else
                oLog.Write("BroadCast Address: UnKnown media. Set to all 1s" )
                lBroadcastAddr = NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&)
        End Select
        GetBroadcastAddress = lBroadcastAddr
    End Function
    
    '============================================================================================='
    '/**
    'This method is used to get the maximum speed of the NIC in kbps
    '@return The link speed on success and -1 on failure
    '@code
    'If (TestCardObj.GetLinkSpeed () < 0 )Then
    '   oLog.Failed ("Failed to get link speed", 88888)
    '   Exit Function
    'End If
    '*/
    Function GetLinkSpeed()
        Dim bResult  
        Dim ulOid
        Dim mLinkSpeed
        
        ulOid = OID_GEN_LINK_SPEED
        bResult = QueryInfo(ulOid, mLinkSpeed, QUERY_GLOBAL_STATS)
        If(bResult) Then 
            oLog.Write("Link speed = " & mLinkSpeed )
        Else
            mLinkSpeed = -1
            oLog.Write("Unable to obtain link speed from " & m_sAdapterName )
        End If
        GetLinkSpeed = mLinkSpeed
    End Function
    
    '============================================================================================='
    '/**
    'This method is used to get the Ndis medium on which the test is running
    'The information is retrieved by querying and OID and is supported only
    'for the test card. Calling this function for Support card will return the
    'Ndis medium as reported by the Test Card.
    '@return The Ndis Medium on success else return zero on failure 
    '@code
    'If (TestCardObj.GetNdisMedium () = 0 )Then
    '   oLog.Failed ("Failed to get Ndis Medium", 88888)
    '   Exit Function
    'End If
    '*/    
    Public Function GetNdisMedium ()
        Dim arrMedia()
        Dim bResult 
        Dim ulOid
        Dim Media
        Dim errStat, lBytesWritten
        
        If (m_sAdapterName = "Test Adapter" And IsEmpty (TestVarsObj.NdisMedium)) Then
            Media = CLng(0)
            
            bResult = NdisIOControl(OID_GEN_MEDIA_IN_USE, arrMedia, lBytesWritten, errStat, QUERY_GLOBAL_STATS)
            If(bResult) Then 
                Media = arrMedia(0)
                TestVarsObj.NdisMedium = Media
            End If
            
            GetNdisMedium = Media
        Else
            GetNdisMedium = TestVarsObj.NdisMedium
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    'QueryInfo is used to query information from the NIC driver from the user mode.
    'This API uses DeviceIOControl calls to query the OID. Please note that QueryInfo
    'does not require an NdisOpen to be made.
    '@param Oid         The Oid to Query
    '@param Datbuffer   The result of query are returned in this variable
    '@param QueryMode   0 QUERY_GLOBAL_STATS    Query the oid across all NIC
    '                   1 QUERY_ALL_STATS       Query all Oids on a NIC
    '                   2 QUERY_SELECTED_STATS  Query a selected Oid
    'Please note that QUERY_ALL_STATS does not return the results in the pData field but    
    '@return   The success status of the QueryInfo method (True/False)
    '*/
    Public Function QueryInfo (Oid, DataBuffer, QueryMode)
        QueryInfo = m_Adapter.QueryInfo (Oid, DataBuffer, QueryMode)
    End Function

    '//===============================================================================================//
    '/**
    'Use this API to send NDIS IO Control Codes to the Net Device. This an alternative
    'to using QueryInfo(NdisRequest) to query get OID's from the network device. This function uses
    'NdisIOControl(DeviceIOControl) to send the query to underlying hardware/driver.
    '@param OidCode		OID to query
    '@param DateBuffer		Buffer to receive response in
    '@param BytesWritten	The number of bytes written in the pvOutBuffer
    '@param ErrorStatus	The Win32 error code in case an error occurs
    '@param QueryMode
    '   QUERY_ALL_STATS      - returns responses for a number of predefined oid queries
    '   QUERY_SELECTED_STATS - returns the response for this single NDIS private oid
    '   QUERY_GLOBAL_STATS   - returns the response for this single oid
   'Please note that QUERY_ALL_STATS does not return the results in the pData field but
    '@return   The success status of the QueryInfo method (True/False)
    '*/
    Public Function NdisIOControl (ByVal Oid, ByRef DataBuffer, ByRef BytesWritten, ByRef ErrorStatus, ByVal QueryMode)
        NdisIOControl = m_Adapter.NdisIOControl(Oid, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
    End Function
    
    '============================================================================================='
    '/**
    'QueryGuid uses WMI to query an oid in the driver.  Internally the OID is converted into
    'a WMI GUID.  The WMI query is made and ndis.sys converts the WMI query into a standard OID query.
    'The driver should see a standard OID query or nothing at all if ndis.sys responds to the OID itself.
    '@param OidGuid  OID to query
    '@param Databuffer     buffer to receive response in
    '@return  The success status of the QueryGuid call (True/False)
    '*/
    Public Function QueryGuid (OidGuid, DataBuffer)
        QueryGuid = m_Adapter.QueryGuid (OidGuid, DataBuffer)
    End Function
    
    Public Function WakeOnLanSupportInfo (ByRef nSystemWakeOnLanSupport)
        Dim WolSupport
        Dim Levels()
        Dim ArraySize, Flags, bResult
        Dim MinMagicPacketWakeUp, MinPatternWakeUp, MinLinkChangeWakeUp

        nSystemWakeOnLanSupport = 0
        
        WolSupport = CLng(0)
        bResult = QueryInfo(OID_PNP_CAPABILITIES, Levels, QUERY_GLOBAL_STATS)
        If (bResult) Then
            ArraySize = UBound(Levels) + 1
            
            If (ArraySize = 16) Then
                '
                ' Levels contains NDIS_PNP_CAPABILITIES structure
                ' which was retieved from driver by sending 
                ' IOCTL_NDIS_QUERY_GLOBAL_STATS ioctl to ndis stack.
                ' As a result of going through COM, Levels is an array of bytes
                ' in BIG ENDIAN format.
                ' The following code coverts the values back to 4 ULONGs
                '   	 
                Flags = Levels(0) + (2^8 * Levels(1)) + (2^16 * Levels(2)) + (2^24 * Levels(3))
                MinMagicPacketWakeUp = Levels(4) + (2^8 * Levels(5)) + (2^16 * Levels(6)) + (2^24 * Levels(7))
                MinPatternWakeUp = Levels(8) + (2^8 * Levels(9)) + (2^16 * Levels(10)) + (2^24 * Levels(11))
                MinLinkChangeWakeUp = Levels(12) + (2^8 * Levels(13)) + (2^16 * Levels(14)) + (2^24 * Levels(15))
                
                If (MinMagicPacketWakeUp > 2) Then
                    WolSupport = WolSupport Or WAKE_UP_MAGIC_PACKET
                End If
                
                If ( MinPatternWakeUp > 2) Then
                    WolSupport = WolSupport Or WAKE_UP_PATTERN_MATCH
                End If
                
                If (MinLinkChangeWakeUp > 2) Then
                    WolSupport = WolSupport Or WAKE_UP_LINK_CHANGE
                End If
                
                ' This bit indicates whether the system and card will work together
                ' in their current abilities.  This bit is set by NDIS and cannot be
                ' modified by the drivers.
                
                ' This part is not used yet, but would be useful in future scripts
                If (Flags And 1) Then
                    nSystemWakeOnLanSupport = 1
                Else
                    If (WolSupport = 0) Then
                        oLog.Write("WakeOnLan is not enabled/supported for this adapter on this machine." )
                    End If
                End If
            Else
                call oLog.Failed ("Internal test error: Unexpected array size " & ArraySize & " from oTestCard.QueryInfo", 22859)
            End If
        End If
        
        WakeOnLanSupportInfo = WolSupport
        
    End Function
    
    '============================================================================================='
    '/**
    ' Wait for the MEDIA_CONNECT_STATUS to change to connected
    '@return  True if could establish link within 90 seconds, else false
    '@code
    '   If (Not TestCard.WaitForLink()) Then
    '       oLog.Write("Unable to establish link status")
    '   End If
    '*/
    Function WaitForLink()
        Dim ConnectStatus
        Dim Connected, lCount
        
        ConnectStatus = 0
        Connected = 0
        lCount = 0
        
        WaitForLink = False
        
        Do While (True)
            ' Sleep for a second
            Wscript.Sleep 1000
            
            If (Not QueryInfo(OID_GEN_MEDIA_CONNECT_STATUS, ConnectStatus, QUERY_GLOBAL_STATS)) Then
                call oLog.Write ("Unable to query media connect status.  If this is transient then it is not a failure." )
            ElseIf (ConnectStatus = Connected) Then
                ' If connected, then we are done! Return success
                WaitForLink = TRUE
                Exit Do
            End If
            
            If (lCount = 90) Then
                call oLog.SafeFailed ("Could not establish the link in 90 seconds! Bailing out", 88888)
                Exit Do
            End If
            
            lCount = lCount + 1
        Loop
    End Function

    
End Class



'============================================================================================='
'/**
'This class stores global variables that can be used by all the objects in the wsf script.
'Example is NdisMedium information which is required for some functions in COpen object and
'is used by some scripts to performs certain functions depending on what the NdisMedium is.
'Ideally we would want these varaibles to be static class members of their respective classes
'(Medium is really a property of the Card) but vbscript does not support static member variables
'as yet
'*/
Class CTestVars
    
    Private m_nNdisMedium
    Private m_nPhysicalMedium
    
    Public Sub Class_Initialize ()
        Dim oTestVars
        
        oTestVars = oNDTSession ("LocalTestVariables")
        If (Not IsEmpty (oTestVars)) Then
            me = oTestVars
        End If
    End Sub
    
    Property Get NdisMedium ()      
        NdisMedium = m_nNdisMedium
    End Property
    Property Let NdisMedium (nNewMedium)
        m_nNdisMedium = nNewMedium
    End Property
    
    Property Get PhysicalMedium ()      
        PhysicalMedium = m_nPhysicalMedium
    End Property
    Property Let PhysicalMedium (nNewMedium)
        m_nPhysicalMedium = nNewMedium
    End Property
End Class

'<!-- CRC = 0xbc1d8243 --->
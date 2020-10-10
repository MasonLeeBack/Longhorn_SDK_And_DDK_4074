'<!-- CRC = 0x7bb283cf -->

'============================================================================================='
Option Explicit
'/**
'This class encapsulate the functionality of the Open COM object and majority of the
'work is done here. Instances of this class are maintained by the Card object on which
'these opens are being made.
'*/
Class COpen
    Private m_NdisOpen       ' The open instance
    Private m_sAdapterName   ' The associated adapter. For debugging purposes
    Private m_MACAddress     ' MAC address of the associated card
    
    Public Sub Class_initialize
        Set m_NdisOpen = Nothing
    End Sub
    
    
    Public Sub Class_Terminate
        if (not m_NdisOpen Is Nothing) then
            'if (not m_NdisOpen.NdisClose ()) Then
            '   Call oLog.SafeFailed ("Could not close " & m_sAdapterName & " open instance", 22839)
            'end If
            ' Set open instance to Nothing
            Set m_NdisOpen = Nothing
        end if
    end Sub
    
    
    Property Get MACAddress ()
        MACAddress = m_MACAddress
    End Property
    Property Let MACAddress (Address)
        m_MACAddress = Address
    End Property
    
    '============================================================================================='
    '/**
    'Returns the instance of COM Open object. This function should be needed only if there
    'is a method provided by COM Open object that COpen does not provide a wrapper for.
    '@return Reference to the COM Open object
    '@sa CCard::GetNdisOpen
    '@code
    'Set OpenOne = OpenOneObj.NdisOpen
    '*/    
    Property Get NdisOpen ()
        Set NdisOpen = m_NdisOpen
    end Property
    
    '============================================================================================='
    '/**
    '@exclude
    'Developers SHOULD NOT have to call this API. The CCard::CreateOpen API should be used
    'instead which uses this API in a safe manner.
    '
    'This API calls COpen::CreateOpen followed by COpen::DoOpen. Its a quicker way to get an
    'Open instance up and running. This method is called by CCard::CreateOpen and dev should
    'use that API to create an Open. If you bypass the CCard::CreateOpen, then the card object will
    'not have added this Open to the list of Open it maintains for the Adapter. This could
    'potenitally cause garbage collection problems and other issues and is discouraged.
    '@return Instance of COM Open object if successful, else Nothing
    '@sa CCard::CreateOpen,SetupBasicTest
    '*/
    Public Function QuickOpen (Adapter, nNdisMedium, strAdapterName)
        m_sAdapterName = strAdapterName
        
        Set QuickOpen = CreateOpen (Adapter, strAdapterName)
        If (not (QuickOpen Is Nothing)) Then
            Set QuickOpen = DoOpen (Adapter, nNdisMedium)
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    '@exclude
    'This API encapsulates the work of CreatOpen API of the COM Open object. This should not
    'be called by the developer. Developer should use CCard::CreateOpen or CCard::SetupBasicTest
    'API's instead
    '@return Reference to the COM Open object created on success, else Nothing
    '@sa CCard::SetupBasicTest,CreateOpen
    '*/
    Public Function CreateOpen (Adapter, strAdapterName)
        m_sAdapterName = strAdapterName
        Set m_NdisOpen = Adapter.CreateOpen()
        If (m_NdisOpen Is Nothing) Then
            Call oLog.SafeFailed ("Failed to create open on " & m_sAdapterName, 22840)
        End If
        
        Set CreateOpen = m_NdisOpen
    End Function    
    
    '============================================================================================='
    '/**
    'Performs an NdisClose on the COM Open object. This is used when the developer explicitly
    'wants to perform a close on the object
    '@return The return status of NdisClose
    '@code
    'bResult = OpenOneObj.Close()
    '*/    
    Public Function Close()
        Close = m_NdisOpen.NdisClose ()
    End Function
    
    '============================================================================================='
    '/**
    'Performs an NdisReset on the COM Open object.
    '@return The return value of the NdisReset
    '@code
    'bResult = OpenOneObj.NdisReset()
    '*/    
    Public Function NdisReset()
        NdisReset = m_NdisOpen.NdisReset ()
    End Function
    
    '============================================================================================='
    '/**
    'This function will return the media events associated with the current open instance. The counts
    'a reset each time a this function is called.
    '@param     nResets         Reference to a variable that will receive the current reset count.
    '@param     nDisconnects    Reference to a variable that will receive the current disconnect count.
    '@param     nConnects       Reference to a variable that will receive the current connect count.
    '@return                    True if the call is successful, otherwise returns false
    '@code
    '    bRetval = Obj.GetEvents(nResets, nDisconnects, nConnects)
    '*/
    Public Function GetEvents(byref nResets, byref nDisconnects,  byref nConnects)
        Dim bRetval
        GetEvents = m_NdisOpen.GetEvents(nResets, nDisconnects, nConnects)
        If (GetEvents = False) Then
            oLog.Write ("GetEvents failed for " & m_sAdapterName )
        End if 
    End Function    
    
    '============================================================================================='
    '/**
    'This function will reset the media events associated with the current open instance. This is used
    'when the script does not need the events, it just wants to reset the counters
    '@return                    True if the call is successful, otherwise returns false
    '@code
    '    bRetval = Obj.ClearEvents()
    '*/
    Public Function ClearEvents()
        Dim bRetval
        ClearEvents = m_NdisOpen.GetEvents()
        If (ClearEvents = False) Then
            oLog.Write ("ClearEvents failed for " & m_sAdapterName )
        End if 
    End Function    
    
    '//===============================================================================================//
    '/**
    'This command will start a process waiting for an event.  Control is returned to the script which
    'later calls EndWaitForEvent.  The EndWaitForEvent will return when a timeout expires or the 
    'event occurs.  The following events can be waited on:
    '      NDIS_STATUS_RESET_START:
    '      NDIS_STATUS_RESET_END:
    '      NDIS_STATUS_MEDIA_CONNECT:
    '      NDIS_STATUS_MEDIA_DISCONNECT:
    '      NDIS_STATUS_WAN_LINE_UP:
    '      NDIS_STATUS_WAN_LINE_DOWN:
    '      NDIS_STATUS_HARDWARE_LINE_UP:
    '      NDIS_STATUS_HARDWARE_LINE_DOWN:
    '      NDIS_STATUS_INTERFACE_UP:
    '      NDIS_STATUS_INTERFACE_DOWN:
    '@param lEvent    Event to wait for       
    '@return True for success
    '@sa EndWaitForEvent
    '@code
    'oLog.Variation("Checking disconnection of card")
    'bResult = WorkOpen.StartWaitForEvent(NDIS_STATUS_MEDIA_DISCONNECT)
    'If (Not bResult) Then
    '   oLog.Write("StartWaitForEvent returned failure" & vblf)
    'End If
    '
    'WshShell.Popup "Disconnect test card from the network, then click OK.", PopupTimeout, "Media Disconnect Detection", vbSystemModal
    '
    'bResult = WorkOpen.EndWaitForEvent(10)
    'If (bResult) Then
    '   oLog.Write("NDIS_STATUS_MEDIA_DISCONNECT indication received" & vblf)
    'Else
    '   call oLog.Failed ("No disconnect indication received" , 23065)
    'End If
    '@endcode
    '*/
    Public Function StartWaitForEvent(lEvent)
        StartWaitForEvent = m_NdisOpen.StartWaitForEvent(lEvent)
    End Function
    
    '//===============================================================================================//
    '/**
    'This command works with StartWaitForEvent. This will return when the timeout expires or the 
    'event occurs.
    '@param lTimeOut  timeout in seconds       
    '@return True for success
    '@sa StartWaitForEvent
    '*/
    Public Function EndWaitForEvent(lTimeOut)
        EndWaitForEvent = m_NdisOpen.EndWaitForEvent(lTimeOut)
    End Function
    
    
    '============================================================================================='
    '/**
    'This function works the same as NdisRequest except that instead of using arrays of data it uses
    'structure objects.
    '@param     nOID          Value that specifies a supported OID.
    '@param     DataArray     Holds results of the request on successful return
    '@param     DataLen       Specifies the size of DataArray in bytes
    '@param     QueryType     Specifies whether this is a query get or set
    '@param     BytesWritten  Returns how many bytes were written by NdisReqeust
    '                         Its the size of valid data in DataArray in bytes
    '@param     BytesNeeded   The number of bytes needed to fulfill this request (if DataLen is not enough)
    '@param     nNdisStatus   Reference to a variable that will receive the ndis status of this call.
    '@return   True if the call was successful, otherwise returns false.
    '@sa       COpen::NdisRequest2
    '@code
    'bRetval = oTestOpen.NdisRequest(SOME_OID_VALUE, Data, DataLen, BytesWritten, BytesNeeded, nStatus)
    '*/
    Public Function NdisRequest(nOID, ByRef DataArray, DataLen, QueryType, ByRef BytesWritten, ByRef BytesNeeded, ByRef nNdisStatus)
        Dim bRetval
        
        NdisRequest = m_NdisOpen.NdisRequest(nOID, DataArray, DataLen, QueryType, BytesWritten, BytesNeeded, nNdisStatus)
        If(Not NdisRequest) Then
            oLog.Write ("NdisRequest failed for " & m_sAdapterName )
            Exit Function
        End If

        If (nNdisStatus = NDIS_STATUS_BUFFER_TOO_SHORT Or nNdisStatus = NDIS_STATUS_INVALID_LENGTH) Then
            If (IsArray (DataArray)) Then
                ' Its an array, lets try increasing the size of the array and redoing the call

                ' The previous call may return a size not a multiple of 4. So, adjust it to a multiple of 4
                Dim NewSize

                If (BytesNeeded Mod 4 > 0) Then
                    NewSize = BytesNeeded\4 + 1
                Else
                    NewSize = BytesNeeded\4
                End If
                oLog.Write ("Insufficient buffer " & DataLen & " provided to NdisRequest. Adjusting buffer size to " & NewSize & " and retrying" )
                ReDim Preserve DataArray(NewSize)
                NdisRequest = m_NdisOpen.NdisRequest(nOID, DataArray, 4 * NewSize, QueryType, BytesWritten, BytesNeeded, nNdisStatus)
                If(Not NdisRequest) then
                    oLog.Write ("NdisRequest failed for " & m_sAdapterName )
                    Exit Function
                End If                
            Else
                NdisRequest = False
            End If
        End If

        If (nNdisStatus <> 0) Then
            oLog.Write ("NdisStatus returned = 0x" & Hex (nNdisStatus))
        End If
    End Function    
    
    '============================================================================================='
    '/**
    'This function works the same as NdisRequest except that instead of using arrays of data it uses
    'structure objects.
    '@param     nOID        Value that specifies a supported OID.
    '@param     oObjStruct  Prevoiusly created structure object.
    '@param     nType       Type of request, can be either REQUEST_QUERY_INFO or REQUEST_SET_INFO
    '@param     nNdisStatus Reference to a variable that will receive the ndis status of this call.
    '@return                True if the call was successful, otherwise returns false.
    '@sa                    CCard::CreateStructObject,COpen::NdisRequest
    '@code
    'bRetval = Obj.NdisRequest2(SOME_OID_VALUE, oStructObj, REQUEST_QUERY_INFO, nStatus)
    '*/
    Public Function NdisRequest2(nOID, byref oObjStruct, nType, byref nNdisStatus)
        Dim bRetval
        
        bRetval = m_NdisOpen.NdisRequest2(nOID, oObjStruct, nType, nNdisStatus)
        if(bRetval = false) then
            Call oLog.SafeFailed ("NdisRequest2 failed for" & m_sAdapterName, 22836)
            exit function
        end if	
        
        NdisRequest2 = true
        
    End Function
    
    '============================================================================================='
    Public Function NdisRequest2a(nOID, byref oObjStruct, nType, byref nNdisStatus, byval nReserved)
        Dim bRetval
        
        bRetval = m_NdisOpen.NdisRequest2(nOID, oObjStruct, nType, nNdisStatus, nReserved)
        if(bRetval = false) then
            Call oLog.SafeFailed ("NdisRequest2 failed for" & m_sAdapterName, 22836)
            exit function
        end if	
        
        NdisRequest2a = true
        
    End Function
    
    
    '============================================================================================='
    '/**
    ' This function queries the specified OID on the open object, and returns the
    ' resulting value, in the result variable. 
    ' @param       nOID         OID to query
    ' @param       Result        The resulting variable
    ' @param       lResultsize  The size allocated to the result variable on the call in, and
    '                                     returns the actual number of bytes written on the call out
    ' @return       True if successful, false otherwise
    ' @code
    ' If (Not OpenObj.QueryInfo (SOME_OID_VALUE, lResult, lResultSize)) Then
    '        oLog.Failed ("Unable to query oid", 23066)
    ' End If     
    '*/
    Public Function QueryInfo(nOID, ByRef Result, ByRef ResultSize)
        Dim BytesWritten, BytesNeeded, NdisStatus
        
        BytesWritten = CLng(0)
        BytesNeeded = CLng(0)
        
        ' The caller generally knows what OID he is querying, and hence can give 
        ' a better message than some general one. So, no failure logging inside this
        ' function
        QueryInfo = NdisRequest( _
                nOID, _
                Result, _
                ResultSize, _
                REQUEST_QUERY_INFO, _
                BytesWritten, _
                BytesNeeded, _
                NdisStatus)
        
        ResultSize =  BytesWritten
        
    End Function
    
    '============================================================================================='
    '/**
    ' This function, prints the information obtained from the query
    ' of the oid into the log file. 
    ' It takes the open instances of the adapter to query, and the
    ' oid to query for
    ' @param       ulOID         OID to query
    ' @return       True if successful, false otherwise
    ' @code
    ' If (Not OpenObj.QueryInfo (SOME_OID_VALUE)) Then
    '        oLog.Failed ("Unable to query oid", 23067)
    ' End If     
    '*/
    
    Function PrintQueryInfo(ulOid)
        Dim BytesWritten, BytesNeeded, NdisStatus
        Dim ResultBuffer()
        Dim BufferSize
        Dim bResult
        
        BufferSize=256
        ReDim ResultBuffer(BufferSize)
        
        BytesWritten = CLng(0)
        BytesNeeded = CLng(0)
        
        bResult = m_NdisOpen.NdisRequest( _
                ulOid, _
                ResultBuffer, _
                BufferSize, _
                REQUEST_QUERY_INFO, _
                BytesWritten, _
                BytesNeeded, _
                NdisStatus)
        
        If (bResult) Then
            If (NdisStatus = NDIS_STATUS_BUFFER_TOO_SHORT Or NdisStatus = NDIS_STATUS_INVALID_LENGTH) Then
                '
                ' Did not allocate enough space for the buffer. Try again
                '
                oLog.Write("Retrying after allocating a larger size for the buffer" )
                BufferSize = 256+BytesNeeded
                ReDim ResultBuffer(BufferSize)
                BytesWritten = CLng(0)
                BytesNeeded = CLng(0)
               
                bResult = m_NdisOpen.NdisRequest( _
                        ulOid, _
                        ResultBuffer, _
                        BufferSize, _
                        REQUEST_QUERY_INFO, _
                        BytesWritten, _
                        BytesNeeded, _
                        NdisStatus)
           End If
        End If
        
        PrintQueryInfo = bResult
    End Function
    
    '==========================================================================
    '/**
    'This method returns the address that the NIC is currently using
    '@return The address being used by the NIC
    '@code
    'CardAddr = OpenOneObj.GetCardAddress ()
    '*/  
    Function GetCardAddress()
        Dim BytesWritten, BytesNeeded
        Dim NdisStatus
        Dim bResult
        
        Dim CardAddr
        CardAddr = NullAddr()
        
        Dim OidValue
        OidValue = 0
        
        Select Case TestVarsObj.NdisMedium
            Case NDISMEDIUM802_3
                OidValue = OID_802_3_CURRENT_ADDRESS
            Case NDISMEDIUM802_5
                OidValue = OID_802_5_CURRENT_ADDRESS
            Case NDISMEDIUMFDDI
                OidValue = OID_FDDI_LONG_CURRENT_ADDR
            Case Else
                call oLog.Failed ("GetCardAddress with unknown media on " & m_sAdapterName , 22870)
        End Select
        
        If (OidValue <> 0) Then
            bResult = NdisRequest( _
                    OidValue, _
                    CardAddr, _
                    6, _
                    REQUEST_QUERY_INFO, _
                    BytesWritten, _
                    BytesNeeded, _
                    NdisStatus)
            
            If (Not bResult) Then
                call oLog.Failed ("Could not obtain address of " & m_sAdapterName , 22871)
            End If
            
            If (NdisStatus <> 0) Then
                oLog.Write("NdisRequest " & OidValue & " returned NdisStatus " & hex(NdisStatus) )
                call oLog.Failed ("Could not obtain address of " & m_sAdapterName , 22871)
            End If
            
        End If         
        
        GetCardAddress = CardAddr
    End Function
    
    '============================================================================================='
    '/**
    '@exclude
    'This API encapsulates the work of NdisOpen API of the COM Open object. This should not
    'be called by the developer. Developer should use CCard::CreateOpen or CCard::SetupBasicTest
    'API's instead
    '@return Reference to the COM Open object on success, else Nothing
    '@sa CCard::SetupBasicTest,CreateOpen
    '*/
    Public Function DoOpen (Adapter, nNdisMedium)
        Dim bResult,bForceNdis30
        
        ' Open instance of the adapter
        bResult = m_NdisOpen.NdisOpen(nNdisMedium, bForceNdis30)
        If (Not bResult) Then
            Call oLog.SafeFailed ("Unable to open instance of " & m_sAdapterName, 22841)
            Set DoOpen = Nothing
        Else
            Set DoOpen = m_NdisOpen
            Initialize ()
        End If
    End Function
    
    '============================================================================================='
    '/**
    'This API encapsulates the work of NdisOpen API of the COM Open object. This is used when
    'the developer has performed an NdisClose, and wants to reopen the object without having
    'to do a CreateOpen
    '@return Reference to the COM Open object on success, else Nothing
    '@sa CCard::SetupBasicTest,CreateOpen
    '*/
    Public Function ReOpen (nNdisMedium)
        Dim bResult,bForceNdis30
        
        ' Open instance of the adapter
        ReOpen = m_NdisOpen.NdisOpen(nNdisMedium, bForceNdis30)
        
        If (Not ReOpen) Then
            Call oLog.SafeFailed ("Unable to open instance of " & m_sAdapterName, 22841)
        Else
            Initialize ()
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    'This function is called immedaitely after an Open has been created and NdisOpen been
    'called on it. Here we include Open specific initializations and queries that might
    'be needed by the wsf script. An example would be to get MAC address of the card and
    'store it for use by the wsf script.
    '@return This function has no return value
    '*/        
    Public Function Initialize ()
       Dim lMedium

       lMedium = TestVarsObj.NdisMedium

       If (lMedium = NDISMEDIUM802_3 Or _
            lMedium = NDISMEDIUM802_5 Or _
            lMedium = NDISMEDIUMFDDI) Then
           MACAddress = GetCardAddress()
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    'This API is used to set assign a unique remote id to the send test we are
    'about to run. This lets us distinguish between sends from different ndistests
    'running on the same network. This can be used when we do not care who
    'is receiving the packet
    '@param nRemoteID  The ID for this test
    '@return This function has no return value
    '@code
    '    OpenOneObj.SetRemoteId (lRemoteId)
    '*/            
    Public Function SetRemoteId (nRemoteId)
        m_NdisOpen.SetRemoteId (nRemoteId)
    End Function
    
    '============================================================================================='
    '/**
    'This API sets the ID that must be in all received packets or they will be ignored
    'This lets us distinguish between sends from different ndistests
    'running on the same network. 
    '@param nLocalID  The ID for this test
    '@return This function has no return value
    '@code
    '    OpenOneObj.SetLocalId (lLocalId)
    '*/            
    Public Function SetLocalId (nLocalId)
        m_NdisOpen.SetLocalId (nLocalId)
    End Function
    
    
    '============================================================================================='
    '/**
    'This API is used to set assign a unique channel/test id to the send test we are
    'about to run. This lets us distinguish between sends from different ndistests
    'running on the same network.
    '@param nChannelID  The ID to assign to this test
    '@return This function has no return value
    '@code
    '    lTestId = oNDTSupp.Random (1, 32765)
    '    OpenOneObj.SetChannelId (lTestId)
    '    OpenTwoObj.SetChannelId (lTestId)
    '*/            
    Public Function SetChannelId (nChannelId)
        SetLocalId (nChannelId)
        SetRemoteId (nChannelId)
    End Function
    
    '============================================================================================='
    '/**
    'This command sends a message to the ndistest.sys protocol to set 
    ' the mode it's packet receive handler will run in.
    '  RECEIVE_DEFAULT             - normal receive, analyze immediately
    '  RECEIVE_NOCOPY              - same as RECEIVE_DEFAULT
    '  RECEIVE_LOOKAHEAD        - same as RECEIVE_DEFAULT but also checks lookahead size
    '  RECEIVE_TRANSFER           - calls NdisTransferData to get the rest of the packet (used by ProtocolReceiveHandler)
    '  RECEIVE_PARTIAL_TRANSFER - same as RECEIVE_TRANSFER but transfers random lengths
    '  RECEIVE_PACKETIGNORE   - returns received packets immediately
    '  RECEIVE_LOCCOPY            - queue the packet to return in 50 milliseconds
    '  RECEIVE_QUEUE                - very similiar to LOCOPY
    '  RECEIVE_DOUBLE_QUEUE   - packet is returned in 100 milliseconds
    '  RECEIVE_TRIPLE_QUEUE     - packet is returned in 150 milliseconds
    '  DEADLOCK_REPRO_FLAG    - special case to to catch a deadlock
    '  RECEIVE_ALLOW_BUSY_NET   - will not require a private network
    '@param nReceiveOption The receive mode we want to use
    '@return This function has no return value
    '@code
    '    OpenOneObj.SetReceiveOption (RECEIVE_DEFAULT Or RECEIVE_TRANSFER)
    '*/
    Public Function SetReceiveOption(nReceiveOption)
        m_NdisOpen.SetReceiveOption(nReceiveOption)
    End Function
    
    '============================================================================================='
    '/**
    'This API is used to start receiving data on an Open instance.
    '@return True on success, else failure
    '@code
    '    If (Not OpenOneObj.StartReceive ()) Then
    '       call oLog.Failed ("Unable to start receiving on Test Open")
    '    End If
    '@sa COpen::StopReceive,VerifiedSend
    '*/
    Public Function StartReceive ()
        StartReceive = m_NdisOpen.StartReceive ()
        If (Not StartReceive) Then
            call oLog.SafeFailed ("Failed on StartReceive on " & m_sAdapterName, 23068)
        End If
    End Function
    
    '============================================================================================='
    '/**
    'Delayed send raw tells the Open to send some data (Without making any changes to it)
    'after nDelay amount of time.
    '@return True on success, else failure
    '@code
    '    If (Not OpenTwoObj.DelayedSendRaw (60, Pattern)) Then
    '       call oLog.Failed ("Unable to get Support card to send delayed pattern")
    '    End If
    '@sa COpen::VerifiedSend
    '*/    
    Public Function DelayedSendRaw(nDelay, nData)
        DelayedSendRaw = m_NdisOpen.DelayedSendRaw (nDelay, nData)
        If (Not DelayedSendRaw) Then
            call oLog.SafeFailed ("Delayed Send Raw failed for " & m_sAdapterName, 23069)
        End If
    End Function
    
    '============================================================================================='
    '/**
    'This API is used to send packets from an open. There are multiple places
    'for this API to fail in and any error that occurs is handled as a safe error.
    'This API, being a verified one, checks to make sure that all packets did get
    'sent and logs a failure if any of the sends fail
    '@param DestAddr       MAC address of the destination card
    '@param nPacketSize    The size of each packet being sent
    '@param nPacketsToSend Number of packets to send! 0 to keep sending till stopped
    '@param nBurstSize     The size of burst to send. 0 if non-bursty traffic
    '@param ResendAddr     The resend address to put in the packet. NULL if no resend needed
    '@return Number of packets sent successfully.
    '@sa COpen::StopSend,GetReceiveResults
    '@code
    '    lPacketsSent = oSuppOpen.VerifiedSend (oTestOpen.MACAddress, 250, 100, 0, oSuppOpen.MACAddress)
    '    if (lPacketsSent < 100) Then
    '       call oLog.Failed ("Some or all of the sends failed", 23070)
    '    End If
    '*/                                                                        
    Public Function VerifiedSend (DestAddr, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
        Dim nPacketsSent
        
        VerifiedSend = 0
        If (Send(DestAddr, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)) Then
            If (WaitSend()) Then
                If(GetSendResults(nPacketsSent, SEND_FAILURES_FORBIDDEN)) Then
                    VerifiedSend = nPacketsSent
                    if (nPacketsSent <> nPacketsToSend) Then
                        call oLog.SafeFailed (m_sAdapterName & " should have sent " & nPacketsToSend & " packets! Sent only " & nPacketsSent , 21311)
                    End If
                Else
                    call oLog.SafeFailed ("Failed to Get Send Results on " & m_sAdapterName, 23071)
                End If
            Else
                call oLog.SafeFailed ("Failed during WaitSend on " & m_sAdapterName, 23072)
            End If
        Else
            call oLog.SafeFailed (m_sAdapterName & " failed to send packets", 23073)
        End If      
    End Function
    
    '============================================================================================='
    '/**
    'This API is used to send packets from an open. There are multiple places
    'for this API to fail in and any error that occurs is handled as a safe error.
    'This API, being a verified one, checks to make sure that all packets did get
    'sent and logs a failure if any of the sends fail
    '@param arrDestAddr    List of MAC address of the destination card
    '@param nNumberAddresses Number of addresses in arrDestAddr structure
    '@param nPacketSize    The size of each packet being sent
    '@param nPacketsToSend Number of packets to send! 0 to keep sending till stopped
    '@param nBurstSize     The size of burst to send. 0 if non-bursty traffic
    '@param ResendAddr     The resend address to put in the packet. NULL if no resend needed
    '@return Number of packets sent successfully.
    '@sa COpen::StopSend,GetReceiveResults
    '@code
    '    lPacketsSent = oSuppOpen.VerifiedSendPackets (arrDestAddr, 4, 250, 100, 0, oSuppOpen.MACAddress)
    '    if (lPacketsSent < 100) Then
    '       call oLog.Failed ("Some or all of the sends failed", 23074)
    '    End If
    '*/                        
    Public Function VerifiedSendPackets (arrDestAddr(), nNumAddresses, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
        Dim nPacketsSent
        Dim nTotalPackets
        VerifiedSendPackets = 0
        nTotalPackets = nNumAddresses * nPacketsToSend
        If (SendPackets(arrDestAddr, nNumAddresses, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)) Then
            If (WaitSend()) Then
                If(GetSendResults(nPacketsSent, SEND_FAILURES_FORBIDDEN)) Then
                    VerifiedSendPackets = nPacketsSent
                    if (nPacketsSent <> nTotalPackets) Then
                        call oLog.SafeFailed (m_sAdapterName & " should have sent " & nTotalPackets & " packets! Sent only " & nPacketsSent , 21311)
                    End If
                Else
                    call oLog.SafeFailed ("Failed to Get Send Results on " & m_sAdapterName, 23075)
                End If
            Else
                call oLog.SafeFailed ("Failed during WaitSend on " & m_sAdapterName, 23076)
            End If
        Else
            call oLog.SafeFailed (m_sAdapterName & " failed to send packets", 23077)
        End If      
    End Function
    
    '============================================================================================='
    '/**
    'This API is used to check the values of packets received and resent
    '@param lRecvExpected  The number of packets that are expected to be received
    '@param lResentExpected The number of packets expected to be resent
    '@param lMinRecvRequired The minimum number of packets that must be 
    '                                       received to avoid failure. 
    '@param lMinResentRequired The minimum number of packets that must be 
    '                                       resent to avoid failure.     
    '@return true when both recv and resent are as expected else false
    '@code
    '    Based on the conditions, we can use any of the following statement
    '    Case 1: lMinimum < Receive <= lTotalPackets
    '       bResult = VerifyReceiveResend (lTotalPackets, lMinimum, lResendExp, lResendMinimum)
    '
    '    Case 2: Receive == lTotalPackets
    '       bResult = VerifyReceiveResend (lTotalPackets, lTotalPackets, lResendExp, lResendMinimum)
    '
    '    Case 3: 0 < Receive <= lTotalPackets ie. receive something
    '       oLog.Mask = oLog.Mask And (Not LOG_WARNING)    'if warning about Recv <= lTotal (but > 0) is not printed
    '       bResult = VerifyReceiveResend (lTotalPackets, 1, lResendExp, lResendMinimum)    
    '       
    '    Case 4: Receive == 0 ie. receive nothing
    '       bResult = VerifyReceiveResend (0, 0, lResendExp, lResendMinimum)    
    '     
    '    Similarly for resent
    '*/ 
    Public Function VerifyReceiveResend(lRecvExpected, lMinRecvRequired, lResendExpected, lMinResendRequired)
        Dim bResult
        Dim lReceived, lResent
        
        bResult = m_NdisOpen.StopReceive()
        If (bResult) Then
            oLog.Write (m_sAdapterName & " should receive " & lRecvExpected & " and resend " & lResendExpected )
            bResult = m_NdisOpen.GetReceiveResults(lReceived, lResent)
            If (bResult) Then       'If test.Failed, bResult is FALSE
                
                ' First check if it resent expected number of packets
                If (lResent <> lResendExpected) Then
                    ' Check if we are allowing it to resend any packets at all (ie lResendExpected != 0)
                    If (lResendExpected = 0) Then
                        Call oLog.SafeFailed ("Should not have resent any packets", 23078)
                    Else
                        ' Okay, so it can resend packets, now check if it did resend an allowable number of packets
                        If (lResent < lMinResendRequired) Then
                            Call oLog.SafeFailed ("Resent less than the required minimum of " & lMinResendRequired , 23079)
                        Else
                            If (lResendExpected = lMinResendRequired) Then
                                Call oLog.SafeFailed("Did not resend expected number of packets" , 23080)
                            Else
                                oLog.SafeWarned("Resent acceptable but less than expected number of packets" & vblf)
                            End If
                        End If
                    End If
                    bResult = False
                End If
                
                If (lReceived <> lRecvExpected) Then
                    If (lRecvExpected = 0) Then
                        Call oLog.SafeFailed ("Should not have received any packets", 23081) 
                    Else
                        If (lReceived < lMinRecvRequired) Then
                            Call oLog.SafeFailed ("Received less than the required minimum of " & lMinRecvRequired , 23082)
                        Else
                            If (lRecvExpected = lMinRecvRequired) Then
                                Call oLog.SafeFailed("Did not receive expected number of packets" , 23083)
                            Else
                                oLog.SafeWarned("Received acceptable but less than expected number of packets" & vblf)
                            End If
                        End If
                    End If
                    bResult = False             
                End If
                
            End If
        Else
            Call oLog.SafeFailed ("Unable to stop receiving on " & m_sAdapterName, 23084)
        End If
        VerifyReceiveResend = bResult
    End Function
    
    '============================================================================================='
    '/**
    'This API is used to stop receiving data on an Open instance.
    '@return True on success, else failure
    '@code
    '    If (Not OpenOneObj.StopReceive ()) Then
    '       call oLog.Failed ("Unable to stop receiving on Test Open")
    '    End If
    '@sa COpen::StartReceive,VerifiedSend
    '*/    
    Public Function StopReceive ()
        StopReceive = m_NdisOpen.StopReceive()
        If Not StopReceive Then
            call oLog.SafeFailed ("Failed during StopReceive on " & m_sAdapterName, 23085)
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    'This function gets the number of packets received and resent (as a result of a 
    'receive) by this Open since the last call to StartReceive
    '@param nPacketsReceived     The number of packets received is returned in this var
    '@param nPacketsResent       The number of packets resent is returned in this var
    '@return True on success, else failure
    '@code
    '    If (Not OpenOneObj.GetReceiveResults (lReceived, lResent)) Then
    '       call oLog.Failed ("Unable to get Receive results")
    '    End If
    '@sa COpen::StartReceive,VerifiedSend
    '*/        
    Public Function GetReceiveResults (ByRef nPacketsReceived, ByRef nPacketsResent)
        GetReceiveResults = m_NdisOpen.GetReceiveResults (nPacketsReceived, nPacketsResent)
        If Not GetReceiveResults Then
            call oLog.SafeFailed ("Failed to get receive results from " & m_sAdapterName, 23086)
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    'This method returns the Maximum Packet Size supported by the NIC. If the NIC reports
    'the MaxPacketSize as anything less than 40 bytes, or the query OID failes we log a 
    'safe error and report max packet size to the caller as being 50 bytes
    '@return The maximum packet size supported by the NIC
    '@code
    'nMaxPacketSize = OpenOneObj.GetMaxPacketSize ()
    '*/ 
    Function GetMaxPacketSize() 
        Dim BytesWritten, BytesNeeded
        Dim NdisStatus
        Dim bResult
        Dim lMaxTotalSize
        
        BytesWritten = CLng(0)
        BytesNeeded = CLng(0)
        
        bResult = NdisRequest( _
                OID_GEN_MAXIMUM_TOTAL_SIZE, _
                lMaxTotalSize, _
                4, _
                REQUEST_QUERY_INFO, _
                BytesWritten, _
                BytesNeeded, _
                NdisStatus)
        
        If(bResult) Then
            If (lMaxTotalSize < 40) Then
                call oLog.SafeFailed ("Invalid value received from " & m_sAdapterName & " for maximum total size" , 23087)
                lMaxTotalSize = 50
            End If
        Else
            call oLog.SafeFailed ("Unable to get maximum total size from " & m_sAdapterName, 23088)
            lMaxTotalSize = 50
        End If
        
        If (NdisStatus <> 0) Then
            oLog.Write("NdisRequest OID_GEN_MAXIMUM_TOTAL_SIZE returned NdisStatus " & hex(NdisStatus) )
            call oLog.SafeFailed ("Unable to get maximum total size from " & m_sAdapterName, 23089)
            lMaxTotalSize = 50
        End If
        
        GetMaxPacketSize = lMaxTotalSize
    End Function
    
    '//===============================================================================================//
    '/**
    'This command is used to send packets over an Open.
    'This command can be used to send lNumPackets number of packets OR
    'keep sending packets for lTestDuration period of time OR
    'send until either lNumPackets have been sent or lTestDuration has been exceeded
    '@param DestAddr		The destination MAC address of the packets in the test
    '@param lPacketSize		Size of the packets to be sent
    '@param lNumPackets		If zero it means ignore this field and keep sending packets
    '						If non-zero, the field specifies the number of packets to send
    '@param lTestDuration	If zero, means ignore this field and keep sending
    '						When non-zero, this field specifies the amount of time in sec to keep
    '						sending the packets for
    '@param ResendAddr	When NULL it means no resend required
    '						else this is the address to resend packets to when received at pvDestAddr
    '@return Returns true on success, false on failure
    '@code
    'This is an example of sending 100 packets of 300 bytes
    'each to the Support Card and requesting it be resent
    'back to the ClientAddress when received
    'bResult = OpenOneObj.Send(SupportAddr, 300, 100, 0, ClientAddress)
    '
    'This is an example of sending packets of 300 bytes
    'each to the Support Card for 100 seconds. There is no
    'resend address so no packets are resent by support card
    'back to the ClientAddress when received
    'bResult = OpenOneObj.Send(SupportAddr, 300, 0, 100, Null)
    '@endcode
    '*/
    Function Send(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
        Send = m_NdisOpen.Send(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
    End Function
    
    '//===============================================================================================//
    '/**
    'This command is used to send packets over an Open to multiple destination
    'This command can be used to send lNumPackets number of packets OR
    'keep sending packets for lTestDuration period of time OR
    'send until either lNumPackets have been sent or lTestDuration has been exceeded
    '@param ArrDestAddr	The array of MAC addresses to send the packets to
    '@param lNumAddresses	The size of the array.
    '@param lPacketSize		Size of the packets to be sent
    '@param lNumPackets		If zero it means ignore this field and keep sending packets
    '						If non-zero, the field specifies the number of packets to send
    '@param lTestDuration	If zero, means ignore this field and keep sending
    '						When non-zero, this field specifies the amount of time in sec to keep
    '						sending the packets for
    '@param ResendAddr	When NULL it means no resend required
    '						else this is the address to resend packets to when received at aDestAddr
    '@return True/False depending on the call
    '@code
    ' This is an example of sending 100 packets of 300 bytes to
    ' each of the 5 Support Addresses and requesting it be resent
    ' back to the ClientAddress when received
    ' Assume there are three open already created on support card(s)
    ' and stored in arrSuppOpen
    
    'Dim ArrSupportAddr (3)
    'ArrSupportAddr (0) = GetCardAddressWithOpen(arrSuppOpen(0), oLog, lMedium)
    'ArrSupportAddr (1) = GetCardAddressWithOpen(arrSuppOpen(1), oLog, lMedium)
    'ArrSupportAddr (2) = GetCardAddressWithOpen(arrSuppOpen(2), oLog, lMedium)
    'bResult = OpenOneObj.SendPackets(ArrSupportAddr, 3, 300, 100, 0, ClientAddress)
    '@endcode
    '*/
    Function SendPackets(ArrDestAddr, lNumAddresses, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
        SendPackets = m_NdisOpen.SendPackets(ArrDestAddr, lNumAddresses, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
    End Function
    
    '//===============================================================================================//
    '/**
    'This command is used to instruct a sending open to stop sending packets.
    'This command is usually used when an open has been asked to keep send packets
    'for a long duration of time and we need to stop the sends now.
    '@return		Returns true on success, false on failure
    '@code
    'bResult = OpenOneObj.StopSend
    '*/
    Function StopSend()
        StopSend = m_NdisOpen.StopSend()
    End Function
    
    '//===============================================================================================//
    '/**
    'This command keeps checking if the sends have completed and if they
    'have, returns. This command usually follows a Send or a StopSend
    'command to make sure we proceed only after all sends have completed
    '@return		Returns true on success, false on failure
    '@code
    'bResult = OpenOneObj.Send (SupportAddress, 300, 100, 0, Null)
    'If (bResult) Then
    '   bResult = OpenOneObj.WaitSend
    '   ...
    'End If
    '*/
    Function WaitSend()
        WaitSend = m_NdisOpen.WaitSend()
    End Function
    
    '//===============================================================================================//
    '/**
    'This command returns the results that were generated when the send or sendpackets command completed.
    '@param lPacketsSent  returns the number of packets sent.
    '@param lSendFailureType Indicates whether send failures are forbidden/allowed/required
    '@return		Returns true on success, false on failure
    '@code
    'bResult = OpenOneObj.GetSendResults(lPacketsSent)
    'If(bResult) Then
    '  oLog.Write("Packets Sent = " & lPacketsSent & vblf)          
    '   If (lPacketsSent <> lTotalPackets) Then
    '      call oLog.Failed("Should have sent " & lTotalPackets & " packets",23090)
    '   End If
    'End If   
    '*/
    Function GetSendResults(ByRef lPacketsSent, lSendFailureType)
        GetSendResults = m_NdisOpen.GetSendResults(lPacketsSent, lSendFailureType)
    End Function
    
    '============================================================================================='
    '/**
    'This API is used to start capturing any IP traffic hitting the Open
    '@return True on success, False on Failure
    '@code
    'If (Not OpenTwoObj.StartIPCapture ()) Then
    '    Exit Function
    'End If
    '*/                                                                    
    Public Function StartIPCapture ()
        StartIPCapture = True
        
        If (Not m_NdisOpen.StartIPCapture()) Then
            call oLog.SafeFailed ("Could not start IP Capture on " & m_sAdapterName, 23091)
            StartIPCapture = False
        End If
    End Function
    
    '//===============================================================================================//
    '/**
    'This command is used to send IP Packets from this open instance handle
    '@param DestAddr		The destination address (MAC) for the IP Packet
    '@param IPVer	    	       Version of IP (V4 or V6)
    '@param Protocol		Protocol Type (TCP, UDP etc)
    '@param lPacketCount	Number of packets to send
    '@param lPacketSize		Size of each packet being sent
    '@param cOptions		Specified TCP Options And/Or IP Options
    '@return    		              Return true on success else failure
    '@code
    'bResult = ClientOpen.VerifiedSendIP(ServerAddress, V4, TCP, 50, 512, TCP_OPTIONS)
    '@endcode
    '*/
    Public Function VerifiedSendIP(DestAddr, IPVer, Protocol, lPacketCount, lPacketSize, cOptions)
        ' Send to the Dest Adapter
        Dim lPacketsSent
        VerifiedSendIP = False
        
        If (m_NdisOpen.SendIP(DestAddr, IPVer, Protocol, lPacketCount, lPacketSize, cOptions)) Then
            If (m_NdisOpen.WaitSend()) Then
                If (m_NdisOpen.GetSendResults(lPacketsSent)) Then
                    if (lPacketsSent <> lPacketCount) Then
                        Call oLog.SafeFailed (m_sAdapterName & "should have sent " & lPacketCount & " packets.", 23092)
                    Else
                        VerifiedSendIP = True        ' Everything went well
                    End If
                Else
                    Call oLog.SafeFailed ("GetSendResults failed on " & m_sAdapterName, 23093)
                End If
            Else
                Call oLog.SafeFailed ("WaitSend failed on " & m_sAdapterName, 23094)
            End If
        Else
            Call oLog.SafeFailed ("Send IP on Open failed on " & m_sAdapterName, 23095)
        End If
        
    End Function
    
    '//===============================================================================================//
    '/**
    'This command collects the results obtained during the IP capture.  It stops the IP capture.
    '@command GetIPCaptureResults
    '@param lPacketCount		Returns the number of Packets received on this open since
    '							the last SetIpCapture call
    '@param lTotalSize		Returns the number of bytes received on this open since
    '							the last SetIpCapture call
    '@param lCksumPassed		Type of checksum that passed if any (TCP_CKSUM or IP_CKSUM)
    '@param lCksumFailed		Type of checksum that failed if any (TCP_CKSUM or IP_CKSUM)
    '@return			Returns True of function success else failure
    '@code
    'bResult = ClientOpen.GetIPCaptureResults (lPacketsReceived, lBytesReceived, lCksumPassed, lCksumFailed)
    '*/
    Public Function GetIPCaptureResults(ByRef lPacketCount, ByRef lTotalSize, ByRef lCksumPassed, ByRef lCksumFailed)
        GetIPCaptureResults = m_NdisOpen.GetIPCaptureResults(lPacketCount, lTotalSize, lCksumPassed, lCksumFailed)
    End Function
    
    '************************************************************************'
    '                                                                        '
    '                       IP Sec Module                                    '
    '                                                                        '
    '************************************************************************'
    
    
    '============================================================================================='
    '/**
    'This API is used to start capturing any IP Sec traffic hitting the Open
    '@return True on success, False on Failure
    '@sa COpen::StopIPSecCapture
    '@code
    'If (Not OpenTwoObj.StartIPSecCapture ()) Then
    '    Exit Function
    'End If
    '*/                                                                    
    Public Function StartIPSecCapture ()
        StartIPSecCapture = True
        
        If (Not m_NdisOpen.StartIPSecCapture()) Then
            call oLog.SafeFailed ("Could not start IP Capture on " & m_sAdapterName, 22842)
            StartIPSecCapture = False
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    'This API is used to send IP Sec traffic out from the Open. There are multiple places
    'for this API to fail in and any error that occurs is handled as a safe error.
    '@param lDestAddr      MAC address of the destination card
    '@param hIPSecOpen     Handle to the local IP Sec Open instance
    '@param IPVer          Version of IP running. V4 or V6
    '@param Protocol       The protocol to use (UDP, TCP etc)
    '@param lPacketCount   Number of packets to send
    '@param lSendDataSize  The size of each packet to send
    '@return True on success, False on Failure
    '@sa COpen::StartIPSecCapture,VerifiedSend
    '@code
    'If (Not OpenOneObj.SendIPSec (OpenTwoObj.MACAddress, hLocalIPSecOpen, V4, UDP, 100, 300)) Then
    '    call oLog.Failed ("SendIPSec command failed!", 23096)
    'End If
    '*/                                                                    
    Public Function SendIPSec (lDestAddr, hIPSecOpen, IPVer, Protocol, lPacketCount, lSendDataSize)
        ' Send to the Dest Adapter
        Dim lPacketsSent
        SendIPSec = False
        
        If (m_NdisOpen.SendIPSec(lDestAddr, hIPSecOpen, IPVer, Protocol, lPacketCount, lSendDataSize)) Then
            If (m_NdisOpen.WaitSend()) Then
                If (m_NdisOpen.GetSendResults(lPacketsSent)) Then
                    if (lPacketsSent <> lPacketCount) Then
                        Call oLog.SafeFailed (m_sAdapterName & " should have sent " & lPacketCount & " packets.", 22843)
                    Else
                        SendIPSec = True        ' Everything went well
                    End If
                Else
                    Call oLog.SafeFailed ("GetSendResults failed on " & m_sAdapterName, 22844)
                End If
            Else
                Call oLog.SafeFailed ("WaitSend failed on " & m_sAdapterName, 22845)
            End If
        Else
            Call oLog.SafeFailed ("Send IP Sec on Open failed on " & m_sAdapterName, 22846)
        End If
    End Function
    
    
    
    '============================================================================================='
    '/**
    'This API Queries the OID_GEN_MAXIMUM_LOOKAHEAD oid on an open instance of the adapter,
    'and returns the result value by reference.
    '@param lMaxLookAhead     Reference to the variable to store the max look ahead value in
    '@return Ndis status of the NdisRequest
    '@code
    'status = OpenOneObj.GetMaxLookahead (lMaxLookahead)
    'If (status <> 0) Then 
    '   call oLog.Failed ("GetMaxLookahead failed with Ndis Status = " & status)
    'End If
    '*/        
    Function GetMaxLookahead(lMaxLookAhead)
        Dim BytesWritten, BytesNeeded
        Dim NdisStatus
        Dim bResult
        Dim templMaxLookahead
        
        BytesWritten = CLng(0)
        BytesNeeded = CLng(0)
        
        bResult = NdisRequest(OID_GEN_MAXIMUM_LOOKAHEAD, _
                templMaxLookahead, 4, REQUEST_QUERY_INFO, _
                BytesWritten, BytesNeeded, NdisStatus)
        
        If (Not bResult) Then
            GetMaxLookahead = 1            ' failure
            Call oLog.SafeFailed ("NdisRequest failed during OID_GEN_MAXIMUM_LOOKAHEAD for " & m_sAdapterName, 22847)
        Else 
            If (NdisStatus <> 0) Then
                GetMaxLookahead = NdisStatus   ' failure
                Call oLog.SafeFailed ("NdisRequest OID_GEN_MAXIMUM_LOOKAHEAD returned failed NdisStatus " & hex(NdisStatus) & " for "  & m_sAdapterName, 22848)
            Else
                GetMaxLookahead = 0            ' Success
                lMaxLookahead = templMaxLookahead
            End If
        End If
        
    End Function
    
    '//===============================================================================================//
    '/**
    'This function sets the Source and Destination IP addresses on open instance
    '@param sSrcIP    IP Address of a given adapter
    '@param sDestIP   IP Address of the adapter destined to receive IP packets
    '@param SrcGWAddr  MAC Address of the adapter's default gateway
    '@return	    Returns true if succesful else return false
    '@code
    'TestIP = "10.10.10.1"
    'SuppIP = "10.10.10.2"
    'TestGWAddr = Array(CByte(0),CByte(1),CByte(2),CByte(3),CByte(4),CByte(5))
    'bResult = oTestOpen.SetIPAddr(TestIP, SuppIP, TestGWAddr)
    '*/
    Function SetIPAddress (sSrcIP, sDstIP, SrcGWAddr)
        SetIPAddress = m_NdisOpen.SetIPAddr(sSrcIP, sDstIP, SrcGWAddr)
        if (not SetIPAddress) Then
            Call oLog.SafeFailed ("SetIPAddr failed for " & m_sAdapterName, 22849)
        end if
    End Function
    
    
    '============================================================================================='
    '/**
    'This API sets the OID_GEN_MAXIMUM_LOOKAHEAD oid on an open instance of the adapter
    'to the specified value of lookahead
    '@param LookAhead     The value to set the Lookahead to
    '@return Ndis status of the NdisRequest
    '@code
    'status = OpenOneObj.SetLookahead (CLng (1))
    'If (status <> 0) Then 
    '   call oLog.Failed ("SetLookahead failed with Ndis Status = " & status)
    'End If
    '*/        
    Function SetLookahead(Lookahead)
        Dim BytesWritten, BytesNeeded, NdisStatus
        Dim tempLookahead, bResult
        
        BytesWritten = CLng(0)
        BytesNeeded = CLng(0)
        tempLookahead = Lookahead
        
        oLog.Write("Setting OID_GEN_CURRENT_LOOKAHEAD to " & Lookahead )
        
        bResult = NdisRequest(OID_GEN_CURRENT_LOOKAHEAD, tempLookahead, 4, _
                REQUEST_SET_INFO, BytesWritten, BytesNeeded, NdisStatus)
        
        If (Not bResult) Then
            NdisStatus = 1          'failure
            Call oLog.SafeFailed ("NdisRequest failed to set look ahead to 0x" & Hex(Lookahead) & " for " & m_sAdapterName, 22850)
        ElseIf (NdisStatus <> 0) Then
            Call oLog.SafeFailed ("NdisRequest OID_GEN_CURRENT_LOOKAHEAD returned NdisStatus " & hex(NdisStatus) & " for " & m_sAdapterName, 22851)
        End If
        
        SetLookahead = NdisStatus
    End Function
    
    
    
    '============================================================================================='
    '/**
    'Sets the packet filter for the open instance
    '@param ParamNewFilter    The filter to set on this Open instance
    '@return Ndis Status of the NdisReqeust if the Request completes.
    '        Returns NDIS_STATUS_UNSUCCESSFUL if NdisRequest does not complete
    '@code
    'If (OpenOneObj.SetPacketFilter (DIRECTED) <> 0) Then 
    '   call oLog.Failed ("SetPacketFilter failed with Ndis Status = " & status)
    'End If
    '*/
    Function SetPacketFilter(ParamNewFilter)
        Dim BytesWritten, BytesNeeded, NdisStatus
        Dim strFilters, NewFilter, bResult
        
        NewFilter = ParamNewFilter  'Do this because NdisRequest can change it
        
        BytesWritten = CLng(0)
        BytesNeeded = CLng(0)
        
        strFilters = "SetPacketFilter is setting the packet filter to "
        
        if (NewFilter = 0)Then
            strFilters = strFilters & "NOTHING "
        End if
        
        if (NewFilter AND DIRECTED)Then
            strFilters = strFilters & "DIRECTED "
        End If
        
        if (NewFilter AND BROADCAST)Then
            strFilters = strFilters & "BROADCAST "
        End If
        
        if (NewFilter AND PROMISCUOUS)Then
            strFilters = strFilters & "PROMISCUOUS "
        End If
        
        if (NewFilter AND MULTICAST)Then
            strFilters = strFilters & "MULTICAST "
        End If
        
        if (NewFilter AND ALL_MULTICAST)Then
            strFilters = strFilters & "ALL_MULTICAST "
        End If
        
        if (NewFilter AND FUNCTIONAL)Then
            strFilters = strFilters & "FUNCTIONAL "
        End If
        
        if (NewFilter AND GROUP_PKT)Then
            strFilters = strFilters & "GROUP "
        End If
        
        if (NewFilter AND MAC_FRAME)Then
            strFilters = strFilters & "MAC_FRAME "
        End If
        
        if (NewFilter AND SOURCE_ROUTING)Then
            strFilters = strFilters & "SOURCE_ROUTING "
        End If
        
        if (NewFilter AND ALL_LOCAL)Then
            strFilters = strFilters & "ALL_LOCAL "
        End If
        
        strFilters = strFilters & vblf
        
        oLog.Write(strFilters)
        
        bResult = NdisRequest(OID_GEN_CURRENT_PACKET_FILTER, _
                NewFilter, 4, REQUEST_SET_INFO, BytesWritten, BytesNeeded, NdisStatus)
        
        If (Not bResult Or NdisStatus <> 0) then
            call oLog.SafeFailed ("Unable to set packet filter for " & m_sAdapterName & " to " & Hex(NewFilter), 22852)
            SetPacketFilter = 1        ' Ndis Status = Failure
        Else
            SetPacketFilter = NdisStatus
        End if
    End Function
    
    
    '============================================================================================='
    '/**
    ' Adds the new multicast address into the multicast address list in the NIC
    ' enabled for packet reception
    '
    '@param NewMulticastAddr       The multicast address to be added
    '@return True on success, false otherwise
    '@code
    'If (Not OpenOneObj.AddMuticastAddr(MultAddr)) Then 
    '   Exit Function
    'End If
    '*/
    Function AddMulticastAddr(ByVal NewMulticastAddr)
        Dim bResult
        Dim ulOid
        Dim ulSizeOid
        Dim BytesWritten, BytesNeeded, NdisStatus
        Dim MaxListSize
        
        Dim MulticastAddrList()
        Dim ListLen
        
        Dim Media
        
        ' Since we have an open object, we have to have TestVarsObj::m_nNdisMedium to be set
        Media = TestVarsObj.NdisMedium
        Do
            bResult = TRUE
            
            '
            ' check for valid medium and set ulOidCode as appropriate
            '
            If((Media = NDISMEDIUM802_3) Or (Media = NDISMEDIUMDIX)) Then
                ulOid = OID_802_3_MULTICAST_LIST
                ulSizeOid = OID_802_3_MAXIMUM_LIST_SIZE 
            ElseIf (Media = NDISMEDIUMFDDI) Then
                ulOid = OID_FDDI_LONG_MULTICAST_LIST
                ulSizeOid = OID_FDDI_LONG_MAX_LIST_SIZE
            Else
                Call oLog.SafeFailed("Add Multicast Address not valid for this mediatype", 23097)
                bResult = FALSE
                Exit Do
            End If
            
            ' Get the maximum number of multicast addresses possible
            MaxListSize = CLng(0)
            BytesWritten = CLng(0)
            BytesNeeded = CLng(0)
            
            bResult = NdisRequest( _
                    ulSizeOid, _
                    MaxListSize, _
                    4, _
                    REQUEST_QUERY_INFO, _
                    BytesWritten, _
                    BytesNeeded, _
                    NdisStatus)
            If(Not bResult) Then
                Call oLog.SafeFailed("Unable to get max multicast list size from " & m_sAdapterName, 23098 )
                Exit Do
            End If
            
            ' The array MulticastAddrList holds the net addresses, in sequence,
            ' with the first 6 bytes forming one address, the next 6 the second, and so on
            
            ' The maximum size of this array is then 6 times the maximum addresses
            ListLen = 6 * MaxListSize
            
            Redim MulticastAddrList(ListLen)
            
            ' Let it be know that MulticastAddrList is an array of bytes
            MulticastAddrList(0) = CByte(MulticastAddrList(0))
            
            bResult = NdisRequest( _
                    ulOid, _
                    MulticastAddrList, _
                    ListLen, _
                    REQUEST_QUERY_INFO, _
                    BytesWritten, _
                    BytesNeeded, _
                    NdisStatus)
            If(Not bResult) Then
                Call oLog.SafeFailed("Unable to obtain old multicast address list from " & m_sAdapterName, 23099 )
                Exit Do
            Else
                ' Actual number of entries in the list
                ListLen = BytesWritten
            End If
            
            If (ListLen = 6*MaxListSize) Then
                ' In this case, the list is full, we should not try
                ' adding this address. But check if the address is already 
                ' present, in which case everything is okay
                
                Dim iIndex
                Dim iCnt
                bResult = FALSE
                iIndex = 0
                For iCnt = 0 To (ListLen \ 6 - 1)
                    If (NetAddrCmpI(MulticastAddrList, NewMulticastAddr, iIndex)) Then
                        bResult = TRUE
                    End If
                    iIndex = iIndex + 6
                Next  
                
                If (bResult) Then
                    oLog.Write("Multicast address to be added already present" )
                Else
                    oLog.Write("Multicast address list full. Could not add" )
                End If
                Exit Do
            End If
            
            ' If the multicast address list already contains the address we wish
            ' to add, we donot worry. We just add the new address. The adapter
            ' should be able to eliminate redundancies
            ' If we wish to remove the copy, we can use the loop from the delete 
            ' command below
            
            MulticastAddrList(ListLen+0) = NewMulticastAddr(0)
            MulticastAddrList(ListLen+1) = NewMulticastAddr(1)
            MulticastAddrList(ListLen+2) = NewMulticastAddr(2)
            MulticastAddrList(ListLen+3) = NewMulticastAddr(3)
            MulticastAddrList(ListLen+4) = NewMulticastAddr(4)
            MulticastAddrList(ListLen+5) = NewMulticastAddr(5)
            
            ListLen = ListLen + 6
            
            BytesWritten = 0
            BytesNeeded = 0 
            
            bResult = NdisRequest( _
                    ulOid, _
                    MulticastAddrList, _
                    ListLen, _
                    REQUEST_SET_INFO, _
                    BytesWritten, _
                    BytesNeeded, _
                    NdisStatus)
            If(Not bResult) Then
                Call oLog.SafeFailed("Unable to add multicast address to list on " & m_sAdapterName, 23100 )
            ElseIf (NdisStatus = NDIS_STATUS_MULTICAST_FULL) Then
                Call oLog.SafeFailed("Multicast address list full on " & m_sAdapterName, 23101)
                bResult = FALSE
            ElseIf (NdisStatus <> 0) Then
                Call oLog.SafeFailed("Add Multicast address returned NdisStatus " & Hex(NdisStatus), 23102)
		bResult = FALSE
            End If
        Loop While(FALSE)
        AddMulticastAddr = bResult
    End Function
    
    '============================================================================================='
    '/**
    ' Removes the given multicast address from the multicast address list
    ' for the NIC.
    '
    '@param OldMulticastAddr       The multicast address to be removed
    '@return True on success, false otherwise
    '@code
    'If (Not OpenOneObj.DeleteMuticastAddr(MultAddr)) Then 
    '   oLog.Write("Unable to remove multicast address")
    'End If
    '*/
    Function DeleteMulticastAddr(ByVal OldMulticastAddr)
        Dim bResult
        Dim ulOid
        Dim ulSizeOid
        Dim BytesWritten, BytesNeeded, NdisStatus
        Dim MaxListSize
        Dim NewListLen
        Dim MulticastAddrList()
        Dim ModMulticastAddrList()
        Dim ListLen
        Dim iCnt
        Dim iNewIndex, iOldIndex
        
        Dim Media
        
        ' Since we have an open object, we have to have TestVarsObj::m_nNdisMedium to be set
        Media = TestVarsObj.NdisMedium
        
        Do
            bResult = TRUE
            
            '
            ' check for valid medium and set ulOidCode as appropriate
            '
            If ((Media = NDISMEDIUM802_3) Or (Media = NDISMEDIUMDIX)) Then
                ulOid = OID_802_3_MULTICAST_LIST
                ulSizeOid = OID_802_3_MAXIMUM_LIST_SIZE 
            ElseIf (Media = NDISMEDIUMFDDI) Then
                ulOid = OID_FDDI_LONG_MULTICAST_LIST
                ulSizeOid = OID_FDDI_LONG_MAX_LIST_SIZE
            Else
                Call oLog.SafeFailed("Delete Multicast Address not valid for this mediatype" , 23103)
                bResult = FALSE
                Exit Do
            End If
            
            ' Get the maximum number of multicast addresses possible
            MaxListSize = CLng(0)
            BytesWritten = CLng(0)
            BytesNeeded = CLng(0)
            bResult = NdisRequest( _
                    ulSizeOid, _
                    MaxListSize, _
                    4, _
                    REQUEST_QUERY_INFO, _
                    BytesWritten, _
                    BytesNeeded, _
                    NdisStatus)
            If(Not bResult) Then
                Call oLog.SafeFailed("Unable to get max multicast list size from " & m_sAdapterName, 23104 )
                Exit Do
            End If
            
            ' The array MulticastAddrList holds the net addresses, in sequence,
            ' with the first 6 bytes forming one address, the next 6 the second, and so on
            
            ' The maximum size of this array is then 6 times the maximum addresses
            ListLen = 6 * MaxListSize
            
            Redim MulticastAddrList(ListLen)
            
            ' Let it be know that MulticastAddrList is an array of bytes
            MulticastAddrList(0) = CByte(MulticastAddrList(0))
            BytesWritten = CLng(0)
            BytesNeeded = CLng(0)
            
            bResult = NdisRequest( _
                    ulOid, _
                    MulticastAddrList, _
                    ListLen, _
                    REQUEST_QUERY_INFO, _
                    BytesWritten, _
                    BytesNeeded, _
                    NdisStatus)
            If(Not bResult) Then
                Call oLog.SafeFailed("Unable to obtain old multicast address list from " & m_sAdapterName, 23105)
                Exit Do
            Else
                ' Actual number of entries in the list
                ListLen = BytesWritten
            End If
            
            ' Maximum filled size of the new list that we would form
            Redim ModMulticastAddrList(ListLen)
            
            iNewIndex = CLng(0)
            iOldIndex = CLng(0)
            
            NewListLen = ListLen
            
            ' Here, we are deleting all the occurences of the address. But,
            ' we can modify to check if the card returns multiple copies of 
            ' an address by removing only the first occurence
            
            For iCnt = 0 To (ListLen \ 6 - 1)
                If (NetAddrCmpI(MulticastAddrList, OldMulticastAddr, iOldIndex)) Then
                    NewListLen = NewListLen - 6
                Else
                    ModMulticastAddrList(iNewIndex)   = MulticastAddrList(iOldIndex)
                    ModMulticastAddrList(iNewIndex+1) = MulticastAddrList(iOldIndex+1)
                    ModMulticastAddrList(iNewIndex+2) = MulticastAddrList(iOldIndex+2)
                    ModMulticastAddrList(iNewIndex+3) = MulticastAddrList(iOldIndex+3)
                    ModMulticastAddrList(iNewIndex+4) = MulticastAddrList(iOldIndex+4)
                    ModMulticastAddrList(iNewIndex+5) = MulticastAddrList(iOldIndex+5)
                    iNewIndex = iNewIndex + 6
                End If
                iOldIndex = iOldIndex + 6
            Next
            
            ' If we had to copy all the old addresses to the new one, we did not find the 
            ' address to delete
            If (NewListLen = ListLen) Then
                Call oLog.SafeFailed("Unable to find the multicast address to delete on " & m_sAdapterName, 23106)           
                Exit Do
            End If
            
            ListLen = NewListLen
            
            BytesWritten = 0
            BytesNeeded = 0 
            
            bResult = NdisRequest( _
                    ulOid, _
                    ModMulticastAddrList, _
                    ListLen, _
                    REQUEST_SET_INFO, _
                    BytesWritten, _
                    BytesNeeded, _
                    NdisStatus)
            If(Not bResult) Then
                Call oLog.SafeFailed("Unable to delete multicast address from list on " & m_sAdapterName, 23107)
                Exit Do
            End If
            
        Loop While (False)
        DeleteMulticastAddr = bResult
    End Function
    
    '============================================================================================='
    '/**
    ' This function sets the current functional address for the
    ' open instance (token ring)
    '@param ParamFunctionalAddr       The functional address to set
    '@return True on success, false otherwise
    '@code
    'If (Not OpenOneObj.SetFunctionalAddr(FuncAddr)) Then 
    '   Exit Function
    'End If
    '*/
    Function SetFunctionalAddr(ParamFunctionalAddr)
        Dim bResult
        Dim ulOid
        Dim BytesWritten, BytesNeeded, NdisStatus
        Dim FunctionalAddr
        
        Dim Media
        
        ' Since we have an open object, we have to have TestVarsObj::m_nNdisMedium to be set
        Media = TestVarsObj.NdisMedium
        
        FunctionalAddr = ParamFunctionalAddr ' Do this because NdisRequest can change it
        
        Do
            bResult = TRUE
            
            '
            ' make sure that this is a valid OID code.  ie, must be token ring
            '  
            If (Media <> NDISMEDIUM802_5) Then
                Call oLog.SafeFailed("SetFunctional not valid for this mediatype", 23108)
                bResult = FALSE
                Exit Do
            End If
            
            ulOid = OID_802_5_CURRENT_FUNCTIONAL
            
            ' Functional address length is a 4 byte array
            bResult = NdisRequest( _
                    ulOid, _
                    FunctionalAddr, _
                    4, _
                    REQUEST_SET_INFO, _
                    BytesWritten, _
                    BytesNeeded, _
                    NdisStatus)
            If(Not bResult) Then
                Call oLog.SafeFailed("Unable to set functional address for " & m_sAdapterName, 23109)   
            End If
            
        Loop While(FALSE)
        '   SetFunctional = bResult
        If (bResult AND NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to set functional address for " & m_sAdapterName, 23110)           
            SetFunctionalAddr = FALSE
        Else
            SetFunctionalAddr = bResult
        End If
        
    End Function
    
    '============================================================================================='
    '/**
    'This function sets the group address for the open instance (token ring only)
    '
    '@param ParamGroupAddr       The group address to be set to
    '@return True on success, false otherwise
    '@code
    'If (Not OpenOneObj.SetGroupAddr(GrpAddr)) Then 
    '   Exit Function
    'End If
    '*/
    Function SetGroupAddr(ParamGroupAddr)
        Dim bResult
        Dim ulOid
        Dim BytesWritten, BytesNeeded, NdisStatus
        Dim GroupAddr
        
        Dim Media
        
        ' Since we have an open object, we have to have TestVarsObj::m_nNdisMedium to be set
        Media = TestVarsObj.NdisMedium
        
        GroupAddr = ParamGroupAddr ' Do this because NdisRequest can change it
        
        Do
            bResult = TRUE
            
            '
            ' make sure that this is a valid OID code.  ie, must be token ring
            '  
            If (Media <> NDISMEDIUM802_5) Then
                Call oLog.SafeFailed("SetGroup not valid for this mediatype", 23111)
                bResult = FALSE
                Exit Do
            End If
            
            ulOid = OID_802_5_CURRENT_GROUP
            
            ' Group address length is a 4 byte array
            bResult = NdisRequest( _
                    ulOid, _
                    GroupAddr, _
                    4, _
                    REQUEST_SET_INFO, _
                    BytesWritten, _
                    BytesNeeded, _
                    NdisStatus)
            If(Not bResult) Then
                Call oLog.SafeFailed("Unable to set group address for " & m_sAdapterName,23112)
            End If
            
        Loop While(FALSE)
        If (bResult AND NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to set group address for " & m_sAdapterName,23113)
            SetGroupAddr = FALSE
        Else
            SetGroupAddr = bResult
        End If
        
    End Function
    
    '**********************************************************'
    '                                                          '
    '          Function related to Task offloading             '
    '                                                          ' 
    '**********************************************************'
    
    '============================================================================================='
    '/**
    'This functions Queries the NIC for its offload capabilities, collects all the information returned,
    'and parses it to set the various global variables to the desired state
    '@return                     True if succeeds/offload capable, else false
    '*/ 
    Function GetTaskOffloadInfo()
        
        GetTaskOffloadInfo = FALSE
        
        Dim bResult, OffloadInfoName
        Dim TaskOffloadSupport, TaskOffloadSupportName
        Dim OffloadInfo
        Dim Idx, Count, NdisStatus, BytesWritten, BytesNeeded 
        Dim OffloadInfoTemp(100)
        Dim lMedium
        
        lMedium = TestVarsObj.NdisMedium
        
        Count = CLng(0)
        ' Set up variables for OID query
        OffloadInfoName = "GlobOffloadInfo"
        TaskOffloadSupportName = "GlobTaskOffloadSupport"		
        OffloadInfo = CLng(0)
        OffloadInfoTemp(0) = CLng(0)
        
        Do
            TaskOffloadSupport = CBool(FALSE)
            
            ' Retreive "TaskOffloadSupport" value from Session Variable
            TaskOffloadSupport = oNDTSession.Variable(TaskOffloadSupportName)	    
            If (Not IsEmpty(TaskOffloadSupport)) Then
                If (TaskOffloadSupport) Then
                    OffloadInfo = oNDTSession.Variable(OffloadInfoName)
                    If(IsEmpty(OffloadInfo)) Then
                        Call oLog.Write("FAILED: Unable to get Task Offload support information, GET Session variable property returned Empty" )
                        Exit Function         
                    End If 	  
                End If
            Else  ' Session variable NOT set yet     
                ' Query OID_TCP_TASK_OFFLOAD
                NdisStatus = 0 ' NDIS_STATUS_SUCCESS
                BytesWritten = CLng(0)
                BytesNeeded = CLng(0)
                
                bResult = NdisRequest(OID_TCP_TASK_OFFLOAD, OffloadInfoTemp, 400, _
                        REQUEST_QUERY_INFO, BytesWritten, BytesNeeded, _
                        NdisStatus)
                If(Not bResult) Then
                    Call oLog.Write("FAILED: Unable to get Task Offload support information" )
                    Exit Function         
                End If
                
                OffloadInfo = OffloadInfoTemp
                
                If(NdisStatus = 0) Then ' NDIS_STATUS_SUCCESS
                    TaskOffloadSupport = TRUE
                    ' Set the OffloadInfo session variable
                    oNDTSession.Variable(OffloadInfoName) = OffloadInfo
                Else
                    TaskOffloadSupport = FALSE
                    If (Count = 0) Then
                        oLog.Write("Adapter does not support task offload" & vbLf)
                    ElseIf (Count = 1) Then
                        oLog.Write("Adapter does not support task offload for Unspecified Encapsulation" & vbLf)                    
                    Else
                        oLog.Write("Adapter does not support task offload for Ethernet SNAP header" & vbLf)
                    End If
                End If
                
                ' Set the TaskOffloadSupport session variable
                oNDTSession.Variable(TaskOffloadSupportName) = TaskOffloadSupport
            End If
            
            ' If Task Offload is supported, parse buffer for each task
            If (TaskOffloadSupport) Then            
                Idx = 0                        
                Do While (Idx < 3)
                    If (Count = 0) Then
                        If (Idx = 0) Then
                            bResult = oNDTCore.ParseOffloadInfo(TCP_IP_CHECKSUM_OFFLOAD_TASK, OffloadInfo, _
                                    GlobCksumTasks, GlobCksumOffloadInfo)
                        ElseIf (Idx = 1) Then
                            bResult = oNDTCore.ParseOffloadInfo(TCP_LARGE_SEND_OFFLOAD_TASK, OffloadInfo, _
                                    GlobLargeSendTasks, GlobLargeSendOffloadInfo)
                        Else ' Idx = 2
                            bResult = oNDTCore.ParseOffloadInfo(IPSEC_OFFLOAD_TASK, OffloadInfo, _
                                    GlobIpsecOffloadTasks, GlobIpsecOffloadInfo)           
                        End If
                    ElseIf (Count = 1) Then ' Unspecified Encapsulation    
                        If (Idx = 0) Then
                            bResult = oNDTCore.ParseOffloadInfo(TCP_IP_CHECKSUM_OFFLOAD_TASK, OffloadInfo, _
                                    GlobUnspecEncapCksumTasks, GlobUnspecEncapCksumOffloadInfo)
                        ElseIf (Idx = 1) Then
                            bResult = oNDTCore.ParseOffloadInfo(TCP_LARGE_SEND_OFFLOAD_TASK, OffloadInfo, _
                                    GlobUnspecEncapLargeSendTasks, GlobUnspecEncapLargeSendOffloadInfo)
                        Else ' Idx = 2
                            bResult = oNDTCore.ParseOffloadInfo(IPSEC_OFFLOAD_TASK, OffloadInfo, _
                                    GlobUnspecEncapIpsecOffloadTasks, GlobUnspecEncapIpsecOffloadInfo)           
                        End If                    
                    Else ' Ethernet SNAP
                        If (Idx = 0) Then
                            bResult = oNDTCore.ParseOffloadInfo(TCP_IP_CHECKSUM_OFFLOAD_TASK, OffloadInfo, _
                                    GlobSnapCksumTasks, GlobSnapCksumOffloadInfo)
                        ElseIf (Idx = 1) Then
                            bResult = oNDTCore.ParseOffloadInfo(TCP_LARGE_SEND_OFFLOAD_TASK, OffloadInfo, _
                                    GlobSnapLargeSendTasks, GlobSnapLargeSendOffloadInfo)
                        Else ' Idx = 2
                            bResult = oNDTCore.ParseOffloadInfo(IPSEC_OFFLOAD_TASK, OffloadInfo, _
                                    GlobSnapIpsecOffloadTasks, GlobSnapIpsecOffloadInfo)           
                        End If
                    End If
                    If(Not bResult) Then
                        Call oLog.Write("FAILED:  Problems encountered while parsing Task offload information" )
                        Exit Function
                    End If    
                    Idx = Idx + 1                
                Loop      
            End If
            
            ' Set Global "TaskOffloadSupport" variable
            If (Count = 0) Then
                GlobTaskOffloadSupport = TaskOffloadSupport
                OffloadInfoName = "GlobUnspecEncapOffloadInfo"
                TaskOffloadSupportName = "GlobUnspecEncapTaskOffloadSupport"		
                OffloadInfoTemp(0) = ENCAPSULATION
                OffloadInfoTemp(1) = CLng (0) ' Unspecified
            ElseIf (Count = 1) Then ' Unspecified Encapsulation
                GlobUnspecEncapTaskOffloadSupport = TaskOffloadSupport
                ' Check if media is Ethernet & re-assign variables & loop again        
                If (lMedium = NDISMEDIUM802_3) Then
                    OffloadInfoName = "GlobSnapOffloadInfo"
                    TaskOffloadSupportName = "GlobSnapTaskOffloadSupport"		
                    OffloadInfoTemp(0) = ENCAPSULATION
                    OffloadInfoTemp(1) = CLng (4) ' LLC-ROUTED
                Else ' NOT Ethernet, so end loop
                    Exit Do    
                End If            
            Else ' Ethernet SNAP
                GlobSnapTaskOffloadSupport = TaskOffloadSupport
            End If 
            
            Count = Count + 1
        Loop While (Count < 3)       
        
        GetTaskOffloadInfo = TRUE
        
    End Function
    
    '============================================================================================='
    '/**
    'This functions Queries the NIC for its offload capabilities using OID_TCP_TASK_OFFLOAD
    '@param OffloadInfoArray     This var tells what type of Offload info are we interested
    '                            querying (SNAP Encapsulation, UnSpecified Encapsulation etc)
    '                            The Offload information returned by the NIC is also placed
    '                            in this variable and returned by reference to the caller
    '@param OffloadInfoLen       Length of the OffloadInfoArray in bytes
    '@param NdisStatus           Return by ref, the NdisStatus of the Request. Remember to set
    '                            this var to success (0) before calling QueryTaskOffloadInfo
    '@return                     True if NdisReqeust succeeds, else false
    '@sa COpen::ParseOffloadInfo
    '@code
    'Dim OffloadInfo (100)
    'OffloadInfo (0) = ENCAPSULATION
    'OffloadInfo (1) = 4         ' LLC SNAP ENCAPSULATION
    'OffloadLen = 400            ' 100 longs = 400 bytes 
    'If (Not QueryTaskOffloadInfo (OffloadInfo, OffloadLen, NdisStatus)) Then
    '    call oLog.Failed ("NdisRequest to OID_TCP_TASK_OFFLOAD failed", 23114)
    'End If
    'If (NdisStatus <> 0) Then      ' If there was a failure
    '   If (NdisStatus = &HC00000BB) Then    ' If error is NDIS_STATUS_NOT_ACCEPTED
    '      oLog.Write ("Task offload for LLC SNAP Encapsulation type not supported")
    '   Else
    '      call oLog.Failed ("NdisRequest failed while querying for Task Offload info")
    '      Exit Function
    '   End If
    'End If
    '*/    
    Public Function QueryTaskOffloadInfo (ByRef OffloadInfoArray, ByRef OffloadInfoLen, ByRef NdisStatus)
        Dim BytesWritten, BytesNeeded      
        QueryTaskOfflaodInfo = NdisRequest(OID_TCP_TASK_OFFLOAD, _
                OffloadInfoArray, _
                OffloadInfoLen, _
                REQUEST_QUERY_INFO, _
                BytesWritten, _
                BytesNeeded, _
                NdisStatus)
        
        If (Not QueryTaskOffloadInfo) Then
            Call oLog.SafeFailed ("Unable to get Task Offload support information from " & m_sAdapterName, 22853)
            Exit Function
        End If
        ' If Ndis Query failed for any reason except NDIS_STATUS_NOT_ACCEPTED
        ' (implies lack of offload support), then report safe failure to log
        If(NdisStatus <> 0 And NdisStatus <> &HC00000BB) Then
            Call oLog.SafeFailed (" NdisRequest to OID_TCP_TASK_OFFLOAD failed with status = " & NdisStatus & " for " & m_sAdapterName)
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    'ParseOffloadInfo takes data returned by the OID_TCP_TASK_OFFLOAD and formats it
    'into appropriate tasks.
    '@param OffloadType    Offload task to parse e.g. TCP_LARGE_SEND_OFFLOAD_TASK
    '@param OffloadInfo    The Offload info data returned by the driver
    '@param 
    Public Function ParseOffloadInfo (OffloadType, OffloadInfo, ByRef NumTask, ByRef TaskArray)
        oLog.Number = 0      ' error status = ok! Helps as this func can return both fail & warn
        ParseOffloadInfo = oNDTCore.ParseOffloadInfo(OffloadType, LocalOffloadInfo, _
                NumTask, TaskArray)
        If (Not ParseOffloadInfo) Then
            Call oLog.SafeFailed ("ParseOffloadInfo failed on test card.", 22854)
            Exit Function
        End If
        ' ** NOTE: A warning is ONLY SET (not logged) for this error! Caller must print if reqd
        if (NumTask = 0) then
            oLog.SetWarning ("Task Offload for this test is not supported by this NIC")
        end if
    End Function
    
    '//===============================================================================================//
    '/**
    'This API is used to offload a task onto an offload capable NIC. The Offload Header
    'info has to be passed in separately as well. 
    '@param alOffloadHdrInfo        Information about Offload Header! Can be array or
    '							a long depending on how much header info is needed
    '@return True on success, else false
    '@code
    'bResult = TestOpenObj.SetOffloadTask(0)        
    '*/
    Public Function SetOffloadTask(alOffloadHdrInfo)
        SetOffloadTask = m_NdisOpen.SetOffLoadTask(alOffloadHdrInfo)
    End Function
    
    '//===============================================================================================//
    '/**
    'This API is used to offload a task onto an offload capable NIC. The Offload Header
    'info has to be passed in separately as well. 
    '@param alOffloadHdrInfo        Information about Offload Header! Can be array or
    '							a long depending on how much header info is needed
    '@param oTask1				A task to offload
    '@return True on success, else false
    '@code
    '   bResult = TestOpenObj.SetOffload1Task(0, CksumOffloadTask)        
    '*/
    Public Function SetOffload1Task(alOffloadHdrInfo, oTask1)
        SetOffload1Task = m_NdisOpen.SetOffLoadTask(alOffloadHdrInfo, oTask1)
    End Function
    
    '//===============================================================================================//
    '/**
    'This API is used to offload a task onto an offload capable NIC. The Offload Header
    'info has to be passed in separately as well. The function can take two tasks to
    'offload (example: offload both largesend and checksum tasks and test).
    '@param alOffloadHdrInfo        Information about Offload Header! Can be array or
    '							a long depending on how much header info is needed
    '@param oTask1				A task to offload
    '@param oTask2				Another task to offload
    '@return True on success, else false
    '@code
    '   bResult = TestOpenObj.SetOffload2Task(0, CksumOffloadTask, LargeSendOffloadTask)        
    '*/
    Public Function SetOffload2Task(alOffloadHdrInfo, oTask1, oTask2)
        SetOffload2Task = m_NdisOpen.SetOffLoadTask(alOffloadHdrInfo, oTask1, oTask2)
    End Function
    
    '//===============================================================================================//
    '/**
    'This command sets the default values on the Open Instance to set the 
    'Encapsulation Type and Size or Self-Checksum-Computation flag
    '@param vOffloadHdrORFlag	Supplies encapsulation type and size or boolean flag
    '							for Self-Checksum-Computation for this Open instance
    '@param pbResult			Returns true if command succeeds, else false
    '@code
    'bResult = ClientOpen.SetIPDefaults (CByte (0))	' Compute Self checksum
    '*/
    Public Function SetIpDefaults(vOffloadHdrORFlag)
        SetIpDefaults = m_NdisOpen.SetIpDefaults(vOffloadHdrORFlag)
    End Function
    
    '//===============================================================================================//
    '/**
    'This command is used to set offload per-packet info for packets sent through this open
    '@param lOffloadBitMask		Defines the offload task for this packet. Example 
    '							CKSUM_OFFLOAD_TX or MSS_RX
    '@param lCksumInfoORMss	Provides details for the selected offload task. Example
    '							V4_CKSUM or the MSS size
    '@return     Returns success or failure in this variable
    '@code
    'lMss = 5120
    'bResult = OpenOne.SetOffloadPktInfo (MSS_TX, lMss)
    '*/
    Public Function SetOffloadPktInfo(lOffloadBitMask, lCksumInfoORMss)
        SetOffloadPktInfo = m_NdisOpen.SetOffloadPktInfo(lOffloadBitMask, lCksumInfoORMss)
    End Function
    
    
    '//===============================================================================================//
    '/**
    'This function retreives the Task Offload Per Packet Information for packets 
    'received on this Open instance
    '@command GetOffloadPktInfo
    '@param lOffloadBitMask					Defines the offload task for this packet.
    '										Example CKSUM_OFFLOAD_TX or MSS_RX
    '@param lCksumPassedORBytesToExpect	Will return the number of packets received
    '										that passed checksum for checksum offload or
    '										bytes received for Largesend offload
    '@param lCksumFailedORPacketsToExpect	Will return the number of packets received
    '										that failed checksum for checksum offload or
    '										packets received for Largesend offload
    '@return					Returns success or failure in this variable
    '@code
    'bResult = ClientOpen.GetOffloadPktInfo (MSS_RX, lBytesToExpect, lPacketsToExpect)
    '*/
    Public Function GetOffloadPktInfo(lOffloadBitMask, ByRef lCksumPassedORBytesToExpect, ByRef lCksumFailedORPacketsToExpect)
        GetOffloadPktInfo = m_NdisOpen.GetOffloadPktInfo(lOffloadBitMask, lCksumPassedORBytesToExpect, lCksumFailedORPacketsToExpect)
    End Function
    
    
    '**********************************************************'
    '                                                          '
    '          Function related to Power Management            '
    '                                                          ' 
    '**********************************************************'
    
    
    '============================================================================================='
    '/**
    ' This function sets Wakeup type information onto the NIC.
    '@param WakeType  The type of event to wakeup on. The values are
    '                 WAKE_UP_MAGIC_PACKET    Wake on receiving a magic packet
    '                 WAKE_UP_PATTERN_MATCH   Wake up on receiving a registered pattern 
    '@return True on success or false if failed to set wakeup type
    '@code
    'If (not oTestOpen.SetWakeupType (WAKE_UP_PATTERN_MATCH)) Then
    '  call oLog.Failed ("Could not set wakeup type on test card", 23115)
    '  Exit Function
    'End If
    '*/
    Public Function SetWakeupType (WakeType)
        If (Not m_NdisOpen.SetWakeupType (WakeType)) Then
            call oLog.SafeFailed ("Unable to set wakeup type for " & m_sAdapterName, 21304)
            SetWakeupType = False
        Else
            SetWakeupType = True
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    ' This function adds the specified wake pattern to the list kept by the NIC
    '@param nNdisStatus  The NdisStatus of the operation is returned in this variable
    '@param Piece1       The fist piece of the pattern
    '@param Offset1      The offset position of of the first piece in the pattern
    '@return True on success or false if failed to set wakeup type
    '@code
    'Piece1 = &H12345&
    'Piece2 = &H6789A&
    'Piece3 = &HBCDEF&
    '
    'If (oTestOpen.AddWakePattern (nNdisStatus, 0, Piece1, 4, Piece2, 8, Piece3)) Then
    '  oLog.Write ("Addition failed")
    'Exit Function
    '*/   
    Public Function AddWakePattern (nNdisStatus, Offset1, Piece1, Offset2, Piece2, Offset3, Piece3)
        AddWakePattern = m_NdisOpen.AddWakePattern (nNdisStatus, CLng (Offset1), CLng (Piece1), _
                CLng (Offset2), CLng (Piece2), CLng (Offset3), CLng (Piece3))
        
        If Not AddWakePattern Or nNdisStatus <> 0 Then
            call oLog.SafeFailed ("Failed to Add Wake Pattern to the " & m_sAdapterName, 23116)
        End If
        
    End Function
    
    
    Public Function RemoveWakePattern (nNdisStatus, Offset1, Piece1, Offset2, Piece2, Offset3, Piece3)
        RemoveWakePattern = m_NdisOpen.RemoveWakePattern (nNdisStatus, CLng (Offset1), CLng (Piece1), _
                CLng (Offset2), CLng (Piece2), CLng (Offset3), CLng (Piece3))
        
        If Not RemoveWakePattern Or nNdisStatus <> 0 Then
            call oLog.SafeFailed ("Failed to Remove Wake Pattern from the " & m_sAdapterName, 23117)
        End If
        
    End Function
    
    '**********************************************************'
    '                                                          '
    '          Function related to IRDA             '
    '                                                          ' 
    '**********************************************************'
    
    '==========================================================================
    '/**
    'Sets the baud rate for the IRDA device instance
    '@param lBaudRate   The baud rate to be set
    '@return The return status from COM::SetBaudRate
    '@code
    '   If (Not OpenOneObj.SetBaudRate(9600))
    '       Call oLog.Failed ("Unable to set baud rate to 9600", 21243)
    '   End If
    '*/  
    Function SetBaudRate(lBaudRate)
        SetBaudRate = m_NdisOpen.SetBaudRate(lBaudRate)
    End Function
    
    '==========================================================================
    '/**
    'Sets the baud rate for the IRDA device instance
    '@param lBaudRate   The baud rate to be set
    '@return True if able to set and verify the baud rate, false other wise
    '@code
    '   If (Not OpenOneObj.SetVerifyBaudRate(9600))
    '       Exit Do
    '   End If
    '*/  
    Function SetVerifyBaudRate(lBaudRate)
        Dim lNewBaudRate
        Dim bResult
        Dim SizeOfLong
        
        SetVerifyBaudRate = True
        
        bResult = SetBaudRate(lBaudRate)
        
        SizeOfLong = 4
        bResult = QueryInfo(OID_IRDA_LINK_SPEED, lNewBaudRate, SizeOfLong)
        
        If (Not bResult) Then
            Call oLog.Failed ("Unable to query current link speed on " & m_sAdapterName , 23118)
            SetVerifyBaudRate = False            
        ElseIf (lNewBaudRate <> lBaudRate) Then
            oLog.Write ("Current baudrate = " & lNewBaudRate & " Expected baudrate = " & lBaudRate & vbLf)
            Call oLog.SafeFailed ("Unable to set baudrate on " & m_sAdapterName , 23119)
            SetVerifyBaudRate = False            
        End If
    End Function
    '==========================================================================
    '/**
    'Gets the turnaround time of the NIC's infrared transceiver.
    '@param lTurnAround     The turnaround time is returned in this variable
    '@return True on success, else false
    '@code
    '   
    '   If (TestOpenObj.GetTurnAround(lTurnAround)) Then
    '       SuppOpenObj.SetTurnAround(lTurnAround)
    '   End If
    '*/  
    Function GetTurnAround(ByRef lTurnAround)
        Dim ResultSize
        ResultSize = 4
        GetTurnAround = QueryInfo(OID_IRDA_TURNAROUND_TIME, lTurnAround, ResultSize)
    End Function
    
    '==========================================================================
    '/**
    'Sets the turnaround time of the NIC's infrared transceiver.
    '@return Nothing
    '@code
    '   
    '   If (TestOpenObj.GetTurnAround(lTurnAround)) Then
    '       SuppOpenObj.SetTurnAround(lTurnAround)
    '   End If
    '*/  
    Sub SetTurnAround(lTurnAround)
        m_NdisOpen.SetTurnAround(lTurnAround)
    End Sub

'==========================================================================
'/**
'Get the number of extra Beginning of Frame (BOF) flags required by the NIC's 
'transceiver to synchronize on a received packet. 
'@param ExtraBofs   The extra BOF flags are returned in this variable
'@return Nothing
'@code
'   
'   If (TestOpenObj.GetExtraBofs(ExtraBofs)) Then
'       SuppOpenObj.SetExtraBofs(ExtraBofs)
'   End If
'*/   
Function GetExtraBofs(ByRef ExtraBofs)
    Dim ResultSize
    ResultSize = 4
    GetExtraBofs = QueryInfo(OID_IRDA_EXTRA_RCV_BOFS, ExtraBofs, ResultSize)
End Function

'==========================================================================
'/**
'Set the number of extra Beginning of Frame (BOF) flags required by the NIC's 
'transceiver to synchronize on a packet. 
'@return Nothing
'@code
'   
'   If (TestOpenObj.GetExtraBofs(ExtraBofs)) Then
'       SuppOpenObj.SetExtraBofs(ExtraBofs)
'   End If
'*/   
Sub SetExtraBofs(lExtraBofs)
     m_NdisOpen.SetExtraBofs(lExtraBofs)
End Sub

'============================================================================================='
 '/**
 'This API is used to check the values of packets received and resent. This is used for IRDA for which we require to use the
 'number of packets resent by the receiver to find the number of packets that the sender can expect to come back to him.
 '@param lRecvExpected  The number of packets that are expected to be received
 '@param lResentExpected The number of packets expected to be resent
 '@param lMinRecvRequired The minimum number of packets that must be 
 '                                       received to avoid failure. 
 '@param lMinResentRequired The minimum number of packets that must be resent to avoid failure. Because
 '                                        of special IRDA priviledges, this parameter is not used.
 '@return true when both recv and resent are as expected else false
 '@sa VerifyReceiveResend
 '
 '*/ 
 Public Function VerifyReceiveResendIRDA(lRecvExpected, lMinRecvRequired, lResendExpected, lMinResendRequired, ByRef lRetResent)
     Dim bResult
     Dim lReceived, lResent

     lRetResent = CLng(0)
     bResult = m_NdisOpen.StopReceive()
     If (bResult) Then
         oLog.Write (m_sAdapterName & " should receive " & lRecvExpected & " and resend " & lResendExpected )
         bResult = m_NdisOpen.GetReceiveResults(lReceived, lResent)
         If (bResult) Then       'If test.Failed, bResult is FALSE

             If (lReceived <> lRecvExpected) Then
                 If (lRecvExpected = 0) Then
                     Call oLog.SafeFailed ("Should not have received any packets", 23120) 
                 Else
                     If (lReceived < lMinRecvRequired) Then
                         Call oLog.SafeFailed ("Received less than the required minimum of " & lMinRecvRequired , 23121)
                     Else
                         If (lRecvExpected = lMinRecvRequired) Then
                             Call oLog.SafeFailed("Did not receive expected number of packets" , 23122)
                         Else
                             oLog.SafeWarned("Received acceptable but less than expected number of packets")
                         End If
                     End If
                 End If
                 bResult = False             
             End If


             lRetResent = lResent
             ' First check if it resent expected number of packets
             If (lResent <> lResendExpected) Then
                 ' Check if we are allowing it to resend any packets at all (ie lResendExpected != 0)
                 If (lResendExpected = 0) Then
                     Call oLog.SafeFailed ("Should not have resent any packets", 23123)
                 Else
                     ' Special case for irda devices. As we received fewer packets, we required
                     ' fewer packets to be resent
                     Dim lFailedRecvs, lRequiredResends
                     lFailedRecvs = lRecvExpected - lReceived
                     lRequiredResends = lResendExpected - lFailedRecvs
                     If (lRequiredResends < 0) Then
                        ' will be logged as a failure by the receive check
                        lRequiredResends = 0
                     End If 
                     
                     If (lResent < lRequiredResends) Then
                         Call oLog.SafeFailed("Did not resend expected number of packets" , 23124)
                     Else
                         oLog.SafeWarned("Resent acceptable but less than expected number of packets")
                         oLog.Write ("This could be because it received fewer packets.")
                     End If
                     
                 End If
                 bResult = False
             End If
                          
         End If
     Else
         Call oLog.SafeFailed ("Unable to stop receiving on " & m_sAdapterName, 23125)
     End If
     VerifyReceiveResendIRDA = bResult
 End Function

 Public Function WakeOnLanSupportInfo (ByRef nSystemWakeOnLanSupport)
     Dim WolSupport
     Dim Levels()
     Dim ArraySize, Flags, bResult
     Dim MinMagicPacketWakeUp, MinPatternWakeUp, MinLinkChangeWakeUp

     nSystemWakeOnLanSupport = 0
     
     WolSupport = CLng(0)
     ReDim Levels(3)
     Levels(0) = CLng(0)
     bResult = QueryInfo(OID_PNP_CAPABILITIES, Levels, 16)
     If (bResult) Then
         ArraySize = UBound(Levels) + 1
         
         If (ArraySize = 4) Then
             '
             ' Levels contains NDIS_PNP_CAPABILITIES structure
             ' which was retieved from driver by using NdisRequest
             '   	 
             Flags = Levels(0)
             MinMagicPacketWakeUp = Levels(1)
             MinPatternWakeUp = Levels(2)
             MinLinkChangeWakeUp = Levels(3)
             
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
             oLog.Write ("Internal test error: Unexpected array size " & ArraySize & " from oTestOpen.QueryInfo")
         End If
     Else
         oLog.Write ("Unable to query OID_PNP_CAPABILITIES. Assuming WOL not supported")
     End If
     
     WakeOnLanSupportInfo = WolSupport
     
 End Function
    
End Class

'<!-- CRC = 0xc6b94fe4 --->
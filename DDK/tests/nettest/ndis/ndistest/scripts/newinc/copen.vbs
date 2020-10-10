Option Explicit

'================================================================================================='
'/**
'This class encapsulates the various operations that can be performed on a NDTCore::Open
'object. It contains all the functions that are common to all types of devices. Specific 
'device types inherit the properties provided by this class and add medium/device type functions
'@sa        CCard, CCLCard, CCLOpen
'@date      01/07/02
'@author    Mitesh Desai
'@alias     miteshd
'*/
Class COpen
   Dim m_oCOMOpen
   Dim m_nNdisMedium
   Dim m_sAdapterType
   
   Private Sub Class_Initialize
      Set m_oCOMOpen = Nothing
   End Sub
   
   Private Sub Class_Terminate
      Set m_oCOMOpen = Nothing
   End Sub
   
   '================================================================================================='
   '/**
   '@exclude
   'This property sets the COM open instance. This is directly called from CCard. It is required to 
   'simulate some characteristics of inheritance that we desire to use in vbscript
   '@params
   '  ! class the com open that we want to set
   '*/
   Public Property Set COMOpen(p_oCOMOpen)
      Set m_oCOMOpen = p_oCOMOpen
   End Property

   '================================================================================================='
   '/**
   'This property would return the COM open instance to the caller. This property
   'should not be used unless absolutely impossible to avoid e.g. stress, which requires
   'two open instances
   '@return    The COM open instance this hierarchy is working with
   '@code
   '  Set oCOMOpen = oTestOpen.COMOpen
   '@endcode
   '*/   
   Public Property Get COMOpen
      Set COMOpen = m_oCOMOpen 
   End Property
   
   '================================================================================================='
   '/**
   '@exclude
   'Used to set the NdisMedium this instance is working with
   '@params
   '  ! number The ndismedium to be set
   '*/   
   Public Property Let NdisMedium (nNdisMedium)
      m_nNdisMedium = nNdisMedium
   End Property
   
   '================================================================================================='
   '/**
   'Returns the ndismedium that the open instance is associated with
   '@return   The ndis medium that this instance is working with
   '*/   
   Public Property Get NdisMedium
      NdisMedium = m_nNdisMedium
   End Property
   
   '================================================================================================='
   '/**
   '@exclude
   'Stores the adapter type that this open instance represents. Helps printing
   'more relevant error messages
   '@params
   '  ! string The adapter type (Test or support) and so on
   '*/   
   Public Property Let AdapterType (sAdapterType)
      m_sAdapterType = sAdapterType
   End Property
   
   '================================================================================================='
   '/**
   'Returns the adapter type to the children classes so as to print the correct error messages
   '@return    Returns "Test Adapter" or "Support Adapter" or similar depending on what is the adapter type
   '*/   
   Public Property Get AdapterType
      AdapterType = m_sAdapterType 
   End Property
   
   
   '================================================================================================='
   '/**
   'This function performs an NdisOpen on the open instance. It binds ndistest.sys to the miniport 
   '@return    TRUE/FALSE depending on success of the operation
   '@code
   '   Set oSuppOpen = oSuppCard.vbCreateOpen
   '   If (oSuppOpen is Nothing) Then
   '      Exit Function
   '   End If
   '
   '   If (Not oSuppOpen.vbNdisOpen) Then
   '      Exit Function
   '   End If
   '@endcode
   '@sa CCard::vbCreateAdapter, CCard::vbCreateOpen
   '*/
   Public Function vbNdisOpen(bForceNdis30)
      ' Open instance of the adapter
      vbNdisOpen = m_oCOMOpen.NdisOpen(m_nNdisMedium, bForceNdis30)
      If (Not vbNdisOpen) Then
         Call oLog.SafeFailed ("Unable to open instance of " & m_sAdapterType, 88888)
      End If
      ' We do not need to keep count of opens because closing will anyways be done
      ' by the dlls, so not an issue
   End Function

    '================================================================================================='
   '/**
   'This function performs an NdisOpen on the open instance. It binds ndistest.sys to the miniport 
   ' It allows Unbind to happen cleanly without causing any issues of outstanding requests
   '@return    TRUE/FALSE depending on success of the operation
   '@code
   '   Set oSuppOpen = oSuppCard.vbCreateOpen
   '   If (oSuppOpen is Nothing) Then
   '      Exit Function
   '   End If
   '
   '   If (Not oSuppOpen.vbNdisOpenUnbindCapable) Then
   '      Exit Function
   '   End If
   '@endcode
   '@sa CCard::vbCreateAdapter, CCard::vbCreateOpen
   '*/
   Public Function vbNdisOpenUnbindCapable()
      ' Open instance of the adapter
      vbNdisOpenUnbindCapable = m_oCOMOpen.NdisOpenUnBindCapable(m_nNdisMedium)
      If (Not vbNdisOpenUnbindCapable) Then
         Call oLog.SafeFailed ("Unable to open instance of " & m_sAdapterType, 88888)
      End If
      ' We do not need to keep count of opens because closing will anyways be done
      ' by the dlls, so not an issue
   End Function
   
   
   '================================================================================================='
   '/**
   'This function queries or sets oids from script.  The parameters are passed to the protocol driver
   'which calls NdisRequest.  The responses are passed back to the script in the cooresponding values.
   'This function allows us to specify if we want to allow resizing of the data buffer if the OID
   'requires more bytes than allocated for the buffer
   '@params
   '  ! number Oid to query or set
   '  ! array/number input and output buffer
   '  ! number length of buffer
   '  ! constant query or set
   '  ! number bytes written, taken from response of NdisRequest call
   '  ! number bytes needed, taken from response of NdisRequest call
   '  ! number ndistatus, taken from response of NdisRequest call
   '  ! bool tells whether we want to allow resizing of data buffer or not
   '@return value for Success(true) or Failure(false)
   '@code
   '  bResult = oTestOpen.vbNdisRequest (OID_GEN_SUPPORTED_LIST, arrList, 256, REQUEST_QUERY_INFO, _
         '                          nBytesWritten, nBytesNeeded, NdisStatus, TRUE)
   '@endcode
   '@sa COpen::vbFastNdisRequest, CCard::vbNdisIOControl
   '*/
   Public Function vbNdisRequest(ByVal nOID, ByRef DataArray, ByVal DataLen, ByVal QueryType, ByRef BytesWritten, ByRef BytesNeeded, ByRef nNdisStatus, ByVal bResize)
      Dim bRetval

      vbNdisRequest = m_oCOMOpen.NdisRequest(nOID, DataArray, DataLen, QueryType, BytesWritten, BytesNeeded, nNdisStatus)
      If(Not vbNdisRequest) Then
         oLog.Write ("NdisRequest failed for " & m_sAdapterType )
         Exit Function
      End If
      
      If (bResize) Then
         If (nNdisStatus = NDIS_STATUS_BUFFER_TOO_SHORT Or nNdisStatus = NDIS_STATUS_INVALID_LENGTH) Then
            If (IsArray (DataArray)) Then
               If (UBound(DataArray) > 0) Then
                  ' Its an array, lets try increasing the size of the array and redoing the call
                  
                  ' The previous call may return a size not a multiple of 4. So, adjust it to a multiple of 4
                  Dim NewSize, BytesProvided

                  If (VarType(DataArray(0)) = vbLong) Then
                     ' if it is a long/integer, the resize is more controlled
                     If (BytesNeeded Mod 4 > 0) Then
                        NewSize = BytesNeeded\4 + 1
                     Else
                        NewSize = BytesNeeded\4
                     End If

                     BytesProvided = 4 * NewSize
                  ElseIf (VarType(DataArray(0)) = vbByte) Then
                     NewSize = BytesNeeded
                     BytesProvided = BytesNeeded
                  Else
                     oLog.Write ("Cannot resize non byte and non long arrays")
                     vbNdisRequest = False
                     Exit Function
                  End If

                  oLog.Write ("Insufficient buffer " & DataLen & " provided to NdisRequest. Adjusting buffer size to " & NewSize & " and retrying" )
                  ReDim Preserve DataArray(NewSize)
                  vbNdisRequest = m_oCOMOpen.NdisRequest(nOID, DataArray, BytesProvided, QueryType, BytesWritten, BytesNeeded, nNdisStatus)
                  If(Not vbNdisRequest) then
                     oLog.Write ("NdisRequest failed for " & m_sAdapterType)
                     Exit Function
                  End If                
               Else 
                  oLog.Write ("Will not resize a non array or zero length data buffer")
               End If
            End If  
         End If
      End If
      
      If (nNdisStatus <> 0) Then
         oLog.Write ("NdisStatus returned = 0x" & Hex (nNdisStatus))
      End If
   End Function    
   
   '============================================================================================='
    '/**
    ' This function works the same as NdisRequest except that instead of using arrays of data it uses
    ' structure objects.
    ' @params
    ' ! constant    Value that specifies a supported OID.
    ' ! object      Prevoiusly created structure object.
    ' ! constant    Type of request, can be either REQUEST_QUERY_INFO or REQUEST_SET_INFO
    ' ! number      Reference to a variable that will receive the ndis status of this call.
    ' @return        
    ' True if the call was successful, otherwise returns false.
    ' @sa 
    ' CCard::CreateStructObject,COpen::NdisRequest
    ' @example
    ' bRetval = Obj.NdisRequest2(SOME_OID_VALUE, oStructObj, REQUEST_QUERY_INFO, nStatus)
    '*/
    Public Function vbNdisRequest2(byval nOID, byref oObjStruct, byval nType, byref nNdisStatus)
    Dim bRetval : bRetval = False
        
        bRetval = m_oCOMOpen.NdisRequest2(nOID, oObjStruct, nType, nNdisStatus)
        If(bRetval = False) Then
            Exit Function
        End If	
        
        vbNdisRequest2 = True
        
    End Function
    
   '================================================================================================='
   '/**
   'Performs an NdisClose on the COM Open object. This is used when the developer explicitly
   'wants to perform a close on the object. It then unbinds ndistest.sys from the miniport.
   'The user need not do this explicitly at the end of the scripts. It will be taken care of
   'by the NDTCore.
   '@return The return status of NdisClose
   '@code
   'bResult = oTestOpen.vbNdisClose()
   '@endcode
   '@sa  COpen::vbNdisOpen
   '*/
   Public Function vbNdisClose()
      vbNdisClose = m_oCOMOpen.NdisClose ()
      If (Not vbNdisClose) Then
         oLog.Write ("Could not close open instance of " & m_sAdapterType)
      End If
   End Function

   '============================================================================================='
   '/**
   'This method returns the Maximum Packet Size supported by the NIC. If the NIC reports
   'the MaxPacketSize as anything less than 40 bytes, or the query OID failes we log a 
   'safe error and report max packet size to the caller as being 50 bytes. The size is 
   'obtained using OID_GEN_MAXIMUM_TOTAL_SIZE
   '@return The maximum packet size supported by the NIC
   '@code
   'nMaxPacketSize = oTestOpen.vbGetMaxPacketSize ()
   '@endcode
   '*/ 
   Function vbGetMaxPacketSize() 
      Dim BytesWritten, BytesNeeded
      Dim NdisStatus
      Dim bResult
      Dim lMaxTotalSize
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      bResult = vbNdisRequest( _
            OID_GEN_MAXIMUM_TOTAL_SIZE, _
            lMaxTotalSize, _
            4, _
            REQUEST_QUERY_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            FALSE)
      
      If(bResult) Then
         If (lMaxTotalSize < 50) Then
            call oLog.SafeFailed ("Invalid value received from " & m_sAdapterType & " for maximum total size" , 88888)
            lMaxTotalSize = 50
         End If
      Else
         call oLog.SafeFailed ("Unable to get maximum total size from " & m_sAdapterType, 88888)
         lMaxTotalSize = 50
      End If
      
      If (NdisStatus <> 0) Then
         call oLog.SafeFailed ("Unable to get maximum total size from " & m_sAdapterType, 88888)
         lMaxTotalSize = 50
      End If
      
      vbGetMaxPacketSize = lMaxTotalSize
   End Function
   
   '================================================================================================='
   '/**
   'This API is used to set assign a unique remote id to the send test we are
   'about to run. This lets us distinguish between sends from different ndistests
   'running on the same network. This can be used when we do not care who
   'is receiving the packet
   '@params
   '  ! number The ID for this test
   '@code
   '  oTestOpen.vbSetRemoteId (lTestId)
   '@endcode
   '@sa COpen::vbSetLocalId, COpen::vbSetChannelId
   '*/
   Public Sub vbSetRemoteId (lTestId)
      m_oCOMOpen.SetRemoteId(lTestId)
   End Sub
   
   '================================================================================================='
   '/**
   'This API sets the ID that must be in all received packets or they will be ignored
   'This lets us distinguish between sends from different ndistests
   'running on the same network.
   '@params
   '  ! number The ID for this test
   '@code
   '  oTestOpen.vbSetLocalId(lTestId)
   '@endcode
   '@sa COpen::vbSetRemoteId, COpen::vbSetChannelId
   '*/
   Public Sub vbSetLocalId (lTestId)
      m_oCOMOpen.SetLocalId(lTestId)
   End Sub

   '================================================================================================='
   '/**
   'This is a quick call that sets both the remote and local id of the open to the same value
   '@params
   '  !  number The value to set the remote and local instance ids to
   '@code
   '  oTestOpen.vbSetChannelId (oNDTSupp.Random(1, 32765))
   '@endcode
   '@sa COpen::vbSetLocalId, COpen::vbSetRemoteId
   '*/
   Public Sub vbSetChannelId (lTestId)
      Me.vbSetRemoteId (lTestId)
      Me.vbSetLocalId (lTestId)
   End Sub
   
   '================================================================================================='
   '/**
   'This API sends a message to the ndistest.sys protocol to set 
   ' the mode it's packet receive handler will run in.<br>
   '  RECEIVE_DEFAULT          - normal receive, analyze immediately<br>
   '  RECEIVE_NOCOPY           - same as RECEIVE_DEFAULT<br>
   '  RECEIVE_LOOKAHEAD        - same as RECEIVE_DEFAULT but also checks lookahead size<br>
   '  RECEIVE_TRANSFER         - calls NdisTransferData to get the rest of the packet (used by ProtocolReceiveHandler)<br>
   '  RECEIVE_PARTIAL_TRANSFER - same as RECEIVE_TRANSFER but transfers random lengths<br>
   '  RECEIVE_PACKETIGNORE     - returns received packets immediately<br>
   '  RECEIVE_LOCCOPY          - queue the packet to return in 50 milliseconds<br>
   '  RECEIVE_QUEUE            - very similiar to LOCOPY<br>
   '  RECEIVE_DOUBLE_QUEUE     - packet is returned in 100 milliseconds<br>
   '  RECEIVE_TRIPLE_QUEUE     - packet is returned in 150 milliseconds<br>
   '  DEADLOCK_REPRO_FLAG      - special case to to catch a deadlock<br>
   '  RECEIVE_ALLOW_BUSY_NET   - will not require a private network<br>
   '  RECEIVE_QUEUE_RETURNS    - hold the packets in a local queue and do not return them
   '@params
   '  ! number The receive mode we want to use
   '@code
   '    oTestOpen.vbSetReceiveOption (RECEIVE_DEFAULT Or RECEIVE_TRANSFER)
   '@endcode
   '*/
   Public Sub vbSetReceiveOption (lReceiveOption)
      m_oCOMOpen.SetReceiveOption(lReceiveOption)
   End Sub
   
   '================================================================================================='
   '/**
   'This API is used to send packets over an Open to multiple destination
   'This API can be used to send lNumPackets number of packets OR
   'keep sending packets for lTestDuration period of time OR
   'send until either lNumPackets have been sent or lTestDuration has been exceeded
   '@params
   '  ! array The array of MAC addresses to send the packets to
   '  ! number The size of the array.
   '  ! number Size of the packets to be sent
   '  ! number If zero it means ignore this field and keep sending packets
   '		If non-zero, the field specifies the number of packets to send
   '  ! number If zero, means ignore this field and keep sending
   '		When non-zero, this field specifies the amount of time in sec to keep
   '		sending the packets for
   '  ! array When NULL it means no resend required
   '		else this is the address to resend packets to when received at aDestAddr
   '@return True/False depending on the call
   '@code
   ' This is an example of sending 100 packets of 300 bytes to
   ' each of the 5 Support Addresses and requesting it be resent
   ' back to the ClientAddress when received
   ' Assume there are three open already created on support card(s)
   ' and stored in arrSuppOpen
   '
   ' Dim ArrSupportAddr (3)
   ' ArrSupportAddr (0) = arrSuppOpen(0).vbGetCardAddress
   ' ArrSupportAddr (1) = arrSuppOpen(1).vbGetCardAddress
   ' ArrSupportAddr (2) = arrSuppOpen(2).vbGetCardAddress
   ' bResult = oTestOpen.vbSendPackets(ArrSupportAddr, 3, 300, 100, 0, ClientAddress)
   '@endcode
   '@sa COpen::vbVerifiedSendPackets, COpen::vbSend
   '*/
   Public Function vbSendPackets(arrDestAddr, lNumAddresses, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
      vbSendPackets = m_oCOMOpen.SendPackets(arrDestAddr, lNumAddresses, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
      If Not vbSendPackets Then
         call oLog.SafeFailed (m_sAdapterType & " failed to send packets", 88888)
      End If
   End Function
   
   '================================================================================================='
   '/**
   'This API is used to send packets over an Open.
   'This API can be used to send lNumPackets number of packets OR
   'keep sending packets for lTestDuration period of time OR
   'send until either lNumPackets have been sent or lTestDuration has been exceeded
   'The command calls NdisSend internally
   '@params
   '  ! array The destination MAC address of the packets in the test
   '  ! number Size of the packets to be sent
   '  ! number If zero it means ignore this field and keep sending packets
	'		If non-zero, the field specifies the number of packets to send
   '  ! number If zero, means ignore this field and keep sending
	'		When non-zero, this field specifies the amount of time in sec to keep
	'		sending the packets for
   '  ! array When NULL it means no resend required
   '     else this is the address to resend packets to when received at pvDestAddr
   '@return Returns true on success, false on failure
   '@code
   ' This is an example of sending 100 packets of 300 bytes
   ' each to the Support Card and requesting it be resent
   ' back to the ClientAddress when received
   '     bResult = ClientOpen.vbSend(SupportAddr, 300, 100, 0, ClientAddress)
   ' This is an example of sending packets of 300 bytes
   ' each to the Support Card for 100 seconds. There is no
   ' resend address so no packets are resent by support card
   ' back to the ClientAddress when received
   '   bResult = ClientOpen.vbSend(SupportAddr, 300, 0, 100, Null)
   '@endcode
   '@sa COpen::vbVerifiedSend, COpen::vbSendPackets
   '*/
   Public Function vbSend(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
      vbSend = m_oCOMOpen.Send(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
      If Not vbSend Then
         call oLog.SafeFailed (m_sAdapterType & " failed to send", 88888)
      End If
   End Function
   
   '===============================================================================================//
   '/**
   'This command returns the results that were generated when the send or sendpackets command completed.
   '@params
   '  ! number returns the number of packets sent.
   '  ! constant This is either - <br>
   '     SEND_FAILURES_FORBIDDEN - send failures generate a variation failure in the log<br>
   '     SEND_FAILURES_ALLOWED - send failures are ignored<br>
   '     SEND_FAILURES_REQUIRED - sends cannot complete successfully
   '@return Returns true on success, false on failure
   '@sa COpen::vbSend,COpen::vbSendPackets
   '@code
   'bResult = oTestOpen.vbGetSendResults(lPacketsSent, SEND_FAILURES_FORBIDDEN)
   '
   'If(bResult) Then
   '   oLog.Write("Packets Sent = " & lPacketsSent & vblf)          
   '   If (lPacketsSent <> lTotalPackets) Then
   '      call oLog.Failed("Should have sent " & lTotalPackets & " packets" & vblf,88888)
   '   End If
   'End If   
   '@endcode
   '*/
   Public Function vbGetSendResults(ByRef lPacketsSent, ByVal lSendFailureType)
      vbGetSendResults = m_oCOMOpen.GetSendResults(lPacketsSent, lSendFailureType)
      If Not vbGetSendResults Then
         call oLog.SafeFailed ("Failed to Get Send Results on " & m_sAdapterType, 88888)
      End If
   End Function
   
   '============================================================================================='
   '/**
   'This API is used to send packets from an open. It sends a bunch of packets in bursts.
   'There are multiple places for this API to fail in and any error that occurs is handled 
   'as a safe error. This API, being a verified one, checks to make sure that all packets 
   'did get sent and logs a failure if any of the sends fail
   '@params 
   '  !  array List of MAC address of the destination card
   '  !  number Number of addresses in arrDestAddr structure
   '  !  number The size of each packet being sent
   '  !  number Number of packets to send! 0 to keep sending till stopped
   '  !  number The size of burst to send. 0 if non-bursty traffic
   '  !  array  The resend address to put in the packet. NULL if no resend needed
   '@return Number of packets sent successfully.
   '@sa COpen::vbSendPackets, COpen::vbVerifiedSend, COpen::vbStopSend
   '@code
   '    lPacketsSent = oSuppOpen.vbVerifiedSendPackets (arrDestAddr, 4, 250, 100, 0, oSuppOpen.MACAddress)
   '    If (lPacketsSent < 100) Then
   '       call oLog.Failed ("Some or all of the sends failed", 88888)
   '    End If
   '@endcode
   '*/                        
   Public Function vbVerifiedSendPackets (arrDestAddr, nNumAddresses, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
      Dim nPacketsSent
      Dim nTotalPackets
      
      vbVerifiedSendPackets = 0
      nTotalPackets = nNumAddresses * nPacketsToSend
      
      If (Me.vbSendPackets(arrDestAddr, nNumAddresses, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)) Then
         If (Me.vbWaitSend) Then
            If(Me.vbGetSendResults(nPacketsSent, SEND_FAILURES_FORBIDDEN)) Then
               vbVerifiedSendPackets = nPacketsSent
               
               If (nPacketsSent <> nTotalPackets) Then
                  call oLog.SafeFailed (m_sAdapterType & " should have sent " & nTotalPackets & " packets! Sent only " & nPacketsSent , 88888)
               End If
            End If
         End If
      End If      
   End Function
   
   '============================================================================================='
   '/**
   'This API is used to send packets from an open. There are multiple places
   'for this API to fail in and any error that occurs is handled as a safe error.
   'This API, being a verified one, checks to make sure that all packets did get
   'sent and logs a failure if any of the sends fail
   '@params
   '  !  array MAC address of the destination card
   '  !  number The size of each packet being sent
   '  !  number Number of packets to send! 0 to keep sending till stopped
   '  !  number The size of burst to send. 0 if non-bursty traffic
   '  !  array The resend address to put in the packet. NULL if no resend needed
   '@return Number of packets sent successfully.
   '@sa COpen::vbSend, COpen::vbVerifiedSendPackets, COpen::vbStopSend
   '@code
   '    lPacketsSent = oSuppOpen.vbVerifiedSend (oTestOpen.MACAddress, 250, 100, 0, oSuppOpen.MACAddress)
   '    if (lPacketsSent < 100) Then
   '       call oLog.Failed ("Some or all of the sends failed", 88888)
   '    End If
   '@endcode
   '*/                                                                        
   Public Function vbVerifiedSend (DestAddr, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
      Dim nPacketsSent
      
      vbVerifiedSend = 0
      If (Me.vbSend(DestAddr, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)) Then
         If (Me.vbWaitSend()) Then
            If(Me.vbGetSendResults(nPacketsSent, SEND_FAILURES_FORBIDDEN)) Then
               vbVerifiedSend = nPacketsSent
               
               if (nPacketsSent <> nPacketsToSend) Then
                  call oLog.SafeFailed (m_sAdapterType & " should have sent " & nPacketsToSend & " packets! Sent only " & nPacketsSent , 88888)
               End If
            End If
         End If
      End If      
   End Function
   
   '===============================================================================================//
   '/**
   'This command keeps checking if the sends have completed and if they
   'have, returns. This command usually follows a Send or a StopSend
   'command to make sure we proceed only after all sends have completed
   '@return		Returns true on success, false on failure
   '@code
   'bResult = oTestOpen.vbSend (SupportAddress, 300, 100, 0, Null)
   'If (bResult) Then
   '   bResult = oTestOpen.vbWaitSend
   '   ...
   'End If
   '@endcode
   '@sa  COpen::vbSend, COpen::vbSendPackets, COpen::vbStopSend
   '*/
   Public Function vbWaitSend()
      vbWaitSend = m_oCOMOpen.WaitSend()
      If Not vbWaitSend Then
         call oLog.SafeFailed ("Failed during WaitSend on " & m_sAdapterType, 88888)
      End If
   End Function
   
   '===============================================================================================//
   '/**
   'This command is used to instruct a sending open to stop sending packets.
   'This command is usually used when an open has been asked to keep send packets
   'for a long duration of time and we need to stop the sends now.
   '@return		Returns true on success, false on failure
   '@code
   'bResult = oTestOpen.vbStopSend
   '@endcode
   '@sa COpen::vbSend, COpen::vbSendPackets, COpen::vbWaitSend
   '*/
   Public Function vbStopSend()
      vbStopSend = m_oCOMOpen.StopSend()
      If Not vbStopSend Then
         call oLog.SafeFailed ("Failed during StopSend on " & m_sAdapterType, 88888)
      End If
   End Function
   
   '============================================================================================='
   '/**
   'This command sends a message to the ndistest.sys protocol to stop receiving packets on this open.
   'After this command is executed any packets that come in on the open are ignored.
   'This is matched with the vbStartReceive command.
   '@return True on success, else failure
   '@code
   '    If (Not oTestOpen.vbStopReceive ()) Then
   '       call oLog.Failed ("Unable to stop receiving on Test Open")
   '    End If
   '@endcode
   '@sa COpen::vbStartReceive, COpen::vbStopSend
   '*/   
   Public Function vbStopReceive ()
      vbStopReceive = m_oCOMOpen.StopReceive()
      If Not vbStopReceive Then
         call oLog.SafeFailed ("Failed during StopReceive on " & m_sAdapterType, 88888)
      End If
   End Function
   
   '============================================================================================='
   '/**
   'This function gets the number of packets received and resent (as a result of a 
   'receive) by this Open since the last call to StartReceive
   '@params 
   '  !  number The number of packets received is returned in this var
   '  !  number The number of packets resent is returned in this var
   '@return True on success, else failure
   '@code
   '    If (Not oTestOpen.vbGetReceiveResults (lReceived, lResent)) Then
   '       call oLog.Failed ("Unable to get Receive results")
   '    End If
   '@endcode
   '@sa COpen::vbStartReceive, COpen::vbStopReceive, COpen::vbVerifyReceiveResendRet
   '*/  
   Public Function vbGetReceiveResults (ByRef nPacketsReceived, ByRef nPacketsResent)
      vbGetReceiveResults = m_oCOMOpen.GetReceiveResults (nPacketsReceived, nPacketsResent)
      If Not vbGetReceiveResults Then
         call oLog.SafeFailed ("Failed to get receive results from " & m_sAdapterType, 88888)
      End If
   End Function
   
   '============================================================================================='
   '/**
   'This API is used to check the values of packets received and resent
   '@params
   '  !  number The number of packets that are expected to be received
   '                      Returns the number of packets actually received
   '  !  number The number of packets expected to be resent
   '                       Returns the number of packets actually resent
   '  !  number The minimum number of packets that must be 
   '                                       received to avoid failure. 
   '  !  number The minimum number of packets that must be 
   '                                       resent to avoid failure.     
   '@return true when both recv and resent are exactly as expected else false
   '@code
   '    Based on the conditions, we can use any of the following statement
   '    Case 1: lMinimum <= Receive <= lTotalPackets
   '       bResult = oTestOpen.vbVerifyReceiveResendRet (lTotalPackets, lMinimum, lResendExp, lResendMinimum)
   '
   '    Case 2: Receive == lTotalPackets
   '       bResult = oTestOpen.vbVerifyReceiveResendRet (lTotalPackets, lTotalPackets, lResendExp, lResendMinimum)
   '
   '    Case 3: 0 < Receive <= lTotalPackets ie. receive something
   '       oLog.Mask = oLog.Mask And (Not LOG_WARNING)    'if warning about Recv <= lTotal (but > 0) is not printed
   '       bResult = oTestOpen.vbVerifyReceiveResendRet (lTotalPackets, 1, lResendExp, lResendMinimum)    
   '       
   '    Case 4: Receive == 0 ie. receive nothing
   '       lRecvPackets = 0
   '       bResult = oTestOpen.vbVerifyReceiveResendRet (lRecvPackets, 0, lResendExp, lResendMinimum)    
   '     
   '    Similarly for resent
   '@endcode
   '@sa COpen::vbGetReceiveResults, COpen::vbVerifiedSend, COpen::vbVerifiedSendPackets
   '*/ 
   Public Function vbVerifyReceiveResendRet(ByRef lRecvExpected, ByVal lMinRecvRequired, ByRef lResendExpected, ByVal lMinResendRequired)
      Dim bResult
      Dim nReceived, nResent
      
      oLog.Write (m_sAdapterType & " should receive " & lRecvExpected & " and resend " & lResendExpected )
      bResult = Me.vbGetReceiveResults(nReceived, nResent)
      If (bResult) Then       'If test.Failed, bResult is FALSE
         
         If (nReceived <> lRecvExpected) Then
            If (lRecvExpected = 0) Then
               Call oLog.SafeFailed ("Should not have received any packets", 88888) 
            Else
               If (nReceived < lMinRecvRequired) Then
                  Call oLog.SafeFailed ("Received less than the required minimum of " & lMinRecvRequired , 88888)
               Else
                  If (lRecvExpected = lMinRecvRequired) Then
                     Call oLog.SafeFailed("Did not receive expected number of packets" , 88888)
                  Else
                     oLog.SafeWarned("Received acceptable but less than expected number of packets" & vblf)
                  End If
               End If
            End If
            bResult = False             
         End If
         lRecvExpected = nReceived
         ' check if it resent expected number of packets
         If (nResent <> lResendExpected) Then
            ' Check if we are allowing it to resend any packets at all (ie lResendExpected != 0)
            If (lResendExpected = 0) Then
               Call oLog.SafeFailed ("Should not have resent any packets", 88888)
            Else
               ' Okay, so it can resend packets, now check if it did resend an allowable number of packets
               If (nResent < lMinResendRequired) Then
                  Call oLog.SafeFailed ("Resent less than the required minimum of " & lMinResendRequired , 88888)
               Else
                  If (lResendExpected = lMinResendRequired) Then
                     Call oLog.SafeFailed("Did not resend expected number of packets" , 88888)
                  Else
                     oLog.SafeWarned("Resent acceptable but less than expected number of packets" & vblf)
                  End If
               End If
            End If
            bResult = False
         End If
         lResendExpected = nResent
      End If
      vbVerifyReceiveResendRet = bResult
   End Function
   
   '============================================================================================='
   '/**
   'This function will reset the media events associated with the current open instance. This is used
   'when the script does not need the events, it just wants to reset the counters
   '@return   True if the call is successful, otherwise returns false
   '@code
   '    bRetval = oTestOpen.vbClearEvents()
   '@endcode
   '@sa COpen::vbGetEvents
   '*/  
   Public Function vbClearEvents
      vbClearEvents = m_oCOMOpen.GetEvents()
      If (vbClearEvents = False) Then
         oLog.Write ("ClearEvents failed for " & m_sAdapterType)
      End if 
   End Function
   
   '============================================================================================='
   '/**
   'This command sends a message to the ndistest.sys protocol to begin receiving packets on this open.
   'Before this command is executed any packets that come in on the open are ignored.
   'This is matched with the vbStopReceive command.
   '@return True on success, else failure
   '@code
   '    If (Not oTestOpen.vbStartReceive ()) Then
   '       call oLog.Failed ("Unable to start receiving on Test Open")
   '    End If
   '@endcode
   '@sa COpen::vbStopReceive, COpen::vbVerifyReceiveResendRet
   '*/
   Public Function vbStartReceive
      vbStartReceive = m_oCOMOpen.StartReceive()
   End Function
   
   '================================================================================================='
   '/**
   'This function is a fast wrapper to ndisrequest. Unlike regular ndisrequest it does not return
   'bytes needed or ndis status. It just queries the OID and stores the result into an out
   'argument. It will resize the buffer only if the input buffer is an array. It can be used to query oids 
   'when we are sure 
   'that the query will succeed or we do not want to investigate failures. The result size make sense
   'only if the return value of the function is true, else it may be corrupted.
   '@params
   '  ! number The OID to query
   '  ! buffer The result buffer (can be an array or a number)
   '  ! number [in] Size of result buffer, [out] size of data in result buffer.
   '@return True if query succeeded with NDIS_STATUS_SUCCESS, false otherwise
   '@code
   '      Dim MacOptions
   '      bResult = oSuppOpen.vbFastNdisRequest(OID_GEN_MAC_OPTIONS, MacOptions, nResultSize)
   '      If (Not bResult) Then
   '         Call oLog.Failed ("Unable to query OID_GEN_MAC_OPTIONS on the test adapter." , 88888)
   '      End If
   '@endcode
   '@sa COpen::vbNdisRequest
   '*/
   Public Function vbFastNdisRequest(ByVal nOID, ByRef Result, ByRef ResultSize)
      Dim BytesWritten, BytesNeeded, NdisStatus
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      ' The caller generally knows what OID he is querying, and hence can give 
      ' a better message than some general one. So, no failure logging inside this
      ' function
      vbFastNdisRequest = Me.vbNdisRequest( _
            nOID, _
            Result, _
            ResultSize, _
            REQUEST_QUERY_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            TRUE)
      
      If (NdisStatus <> 0) Then
         vbFastNdisRequest = FALSE
      End If
      
      ResultSize =  BytesWritten
   End Function
   
   '============================================================================================='
   '/**
   ' This function, prints the information obtained from the query of the oid into the log file. 
   ' It works on the open instances of the adapter to query, and the oid to query for
   ' Internally it is just a wrapper to ndisrequest. It can be used when we do not wish to know
   ' the contents of the query, but want to just put the results of the query into the log
   ' @params  !   number OID to query
   ' @return      True if successful, false otherwise
   ' @code
   ' If (Not oTestOpen.vbPrintNdisRequest(OID_802_3_MULTICAST_LIST)) Then
   '        oLog.Failed ("Unable to query oid", 88888)
   ' End If     
   ' @endcode
   ' @sa COpen::vbNdisRequest, COpen::vbFastNdisRequest
   '*/
   Public Function vbPrintNdisRequest(nOid)
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim ResultBuffer()
      Dim BufferSize
      Dim bResult
      
      BufferSize=256
      ReDim ResultBuffer(BufferSize)
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      ResultBuffer(0) = CByte(0)
      vbPrintNdisRequest = Me.vbNdisRequest( _
            nOid, _
            ResultBuffer, _
            BufferSize, _
            REQUEST_QUERY_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            TRUE)

      If (NdisStatus <> 0) Then
         vbPrintNdisRequest = False
      End If 
   End Function
   
   
   '================================================================================================='
   '/**
   'Performs an NdisReset on the COM Open object.
   '@return    The return status from NdisReset
   '@code   
   '  bResult = oTestOpen.vbNdisReset
   '@endcode
   '*/
   Public Function vbNdisReset
      vbNdisReset = m_oCOMOpen.NdisReset
   End Function
   
   '===============================================================================================//
   '/**
   'This command the number of certain events that have occured on this open.  Many of these are the
   'result of the protocol driver's StatusHandler being called.  The number of resets, disconnects,
   'and connects are returned to the script for special processing if needed.
   'This will keep track of the following events:<br>
   '   ulTotalEvents;             // total count from fields below<br>
   '   ulCompleteOpen;            // ProtocolOpenComplete calls<br>
   '   ulCompleteClose;           // ProtocolCloseComplete calls<br>
   '   ulCompleteSend;            // ProtocolSendComplete calls<br>
   '   ulCompleteTransfer;        // ProtocolTransferComplete calls<br>
   '   ulCompleteReset;           // ProtocolResetComplete calls<br>
   '   ulCompleteRequest;         // ProtocolRequestComplete calls<br>
   '   ulIndicateReceive;         // ProtocolIndicateReceive calls<br>
   '   ulIndicateStatus;          // ProtocolIndicateStatus calls<br>
   '   ulIndicateStatusComplete;  // ProtocolIndicateStatusComplete calls<br>
   '   ulMediaConnect;            // ProtocolIndicateStatus calls with Status = NDIS_STATUS_MEDIA_CONNECT<br>
   '   ulMediaDisConnect;         // ProtocolIndicateStatus calls with Status = NDIS_STATUS_MEDIA_DISCONNECT<br>
   '   ulResetStart;              // ProtocolIndicateStatus calls with Status = NDIS_STATUS_RESET_START <br>
   '   ulResetEnd;                // ProtocolIndicateStatus calls with Status = NDIS_STATUS_RESET_END <br>
   '   ulMultipleResetStart;      // Multiple ProtocolIndicateStatus calls with Status = NDIS_STATUS_RESET_START <br>
   '   ulMultipleResetEnd;        // Multiple ProtocolIndicateStatus calls with Status = NDIS_STATUS_RESET_END <br>
   '   ulBreakpointsHit;          // number of times breakpoint situations hit
   ' A call to vbGetEvents clears all the above events
   '@command GetEvents
   '@params
   '  ! number Number resets that occured
   '  ! number Number of disconnects that occured
   '  ! number Number of connects that occured
   '@return True or false
   '@code
   'Resets = 0
   'Disconnects = 0
   'Connects = 0
   '
   'oLog.Variation("GetEvents for instance 1")
   'bResult = oTestOpen.vbGetEvents(Resets, Disconnects, Connects)
   'If(Not bResult) Then
   '   Call oLog.Write("Get events failed on first open instance" )
   'End If
   'If (Resets <> lNumResets) Then
   '   call oLog.Failed ("Incorrect number of reset events " & Resets & ". Should have been " & lNumResets , 88888)
   'End If      
   '
   'If ((Disconnects <> 0) And (Disconnects <> lNumResets)) Then
   '   call oLog.Failed ("Incorrect number of disconnect events " & Disconnects & ". Should have been 0 or " & lNumResets , 88888)
   'End If
   '
   'If ((Connects <> 0) And (Connects <> lNumResets)) Then
   '   call oLog.Failed ("Incorrect number of connect events " & Connects & ". Should have been 0 or " & lNumResets , 88888)
   'End If
   '
   'If (Connects <> Disconnects) Then
   '   call oLog.Failed ("Disconnect events " & Disconnects & " should equal connect events " & Connects , 88888)
   'End If
   '@endcode
   '@sa  COpen::vbClearEvents
   '*/
   Public Function vbGetEvents(ByRef nResets, ByRef nDisconnects, ByRef nConnects)
      vbGetEvents = m_oCOMOpen.GetEvents (nResets, nDisconnects, nConnects)
   End Function
   
   '===============================================================================================//
   '/**
   'This command is used to start Performance test on Test adapter. As a part of performance test,
   'large number of packets are pre-allocated and sent/received simultaneously on test adapter.
   '@params    
   '  ! class Interface pointer for the Support Open Object
   '  ! array MAC Address where packets are send to
   '  ! constant Mode of test : send mode, receive mode or both send and receive mode
   '     without or without verifying receives
   '  ! number Size of the packet
   '  ! number Packets sent during each burst
   '  ! number Total Packets to be send for this iteration
   '  ! number Time in seconds for the iteration to complete
   '  ! number Delay in milliseconds between sends
   '  ! number Cancel packet sends during this command
   '@return If command succeeds set to TRUE, FALSE otherwise
   '@sa COpen::vbGetPerformanceResults, COpen::vbWaitPerformance
   '@code
   'Mode = PERFORM_RECEIVE + PERFORM_VERIFY_RECEIVES
   'bResult = oTestOpen.vbStartPerformance(oSuppOpen, TestAddr, Mode, lSize, lPktsPerBurst, 0, 30, 0, 0)
   'If (Not bResult) Then
   '    call oLog.Failed ("Unable to execute performance command.", 88888)
   'End If
   '@endcode
   '*/
   Function vbStartPerformance(oRemoteCOMOpen, DestAddr, TestMode, PacketSize, PktsPerBurst, NumPackets, TestDuration, Delay, CancelPkts)
      vbStartPerformance = m_oCOMOpen.StartPerformance (oRemoteCOMOpen, DestAddr, TestMode, PacketSize, PktsPerBurst, NumPackets, TestDuration, Delay, CancelPkts)
   End Function
   
      
   '===============================================================================================//
   '/**
   'This command waits until the driver is done performing a performance test. So the driver is 
   'sending/receiving packets and once it is done it returns the control back to test script.
   '@return If command succeeds set to TRUE, FALSE otherwise
   '@sa COpen::vbStartPerformance, COpen::vbGetPerformanceResults 
   '@code
   'bResult = OpenOne.vbWaitPerformance()
   'If (Not bResult) Then
   '    call oLog.Failed ("Unable to wait for performance tests to complete.", 88888)
   'End If
   '@endcode
   '*/ 
   Public Function vbWaitPerformance ()
      vbWaitPerformance = m_oCOMOpen.WaitPerformance()
   End Function
   
   '===============================================================================================//
   '/**
   'This command gets the results of the previous performance tests. It is expected
   'to be called after waitperformance command.
   '@params
   '  ! number Time duration in which performance test completed
   '  ! number Bytes sent during the performance test
   '  ! number Bytes received during the performance test
   '@return    If command succeeds set to TRUE, FALSE otherwise
   '@sa COpen::vbStartPerformance, COpen::vbWaitPerformance 
   '@code
   'bResult = oTestOpen.vbGetPerformanceResults(lDuration, lBytesSent, lBytesReceived)
   'If (Not bResult) Then
   '    call oLog.Failed ("Unable to get performance results.", 88888)
   'End If
   '@endcode
   '*/
   Public Function vbGetPerformanceResults (nDuration, nBytesSent, nBytesReceived)
      vbGetPerformanceResults = m_oCOMOpen.GetPerformanceResults(nDuration, nBytesSent, nBytesReceived)
   End Function
   
   
   '===============================================================================================//
   '/**
   'The stress test is on the main test commands in the NDIS Test.  It sends packets quickly using
   'many different buffer sizes and packet sizes. The open that this is called on does the sending.
   'Control returns to the script as soon as the Stress test starts.  Test options are:<br>
   '<p>Packet Sizes<br>
   '   FIXEDSIZE        determined by ulPacketSize<br>
   '   RANDOMSIZE       from minimum to ulPacketSize<br>
   '   STRESS_CYCLICAL  from minimum to ulPacketSize increasing by one<br>
   '   STRESS_SMALLSIZE Small packets<br>
   '
   '<p>Buffer Sizes (max 20 buffers)<br>
   '   RAND     Random sizes<br>
   '   SMALL    Lots of little buffers<br>
   '   ZEROS    A number zero length buffers including at the end of chain<br>
   '   ONES     A number buffers that are one byte long<br>
   '
   '<p>Receive/Resend Options<br>
   '   FULL_RESP Respond with a full length packet<br>
   '   NO_RESP   Do not respond<br>
   '   ACK       Respond with a small packet<br>
   '   ACK_10    Respond with 10 small packets<br>
   '
   '<p>Windowing keeps track of how many packets have not been ACKed.
   '@params
   '  ! class This open receives the packets
   '  ! number Size of packets or max packet size if size is variable
   '  ! number Test options - see above
   '  ! number Number of packets or times through loop of packet sizes
   '  ! number Time in seconds test will run (or until all packets have been sent)
   '@return     True if the call is successful, otherwise returns false
   '@sa COpen:vbWaitStress, COpen::vbGetStressResults
   '@code
   'bResult = TestOpen.vbStartStress(SuppOpen, arrPacketSize(nCount), arrOptionMask(nCount), arrIterations(nCount), 0)
   'If (bResult) Then
   '   bResult = TestOpen.vbWaitStress
   '   If (bResult) Then
   '       bResult = TestOpen.vbGetStressResults
   '       If (Not bResult) Then
   '           Call oLog.Failed ("Unable to get stress results from the test adapter." , 88888)
   '       End If
   '   Else
   '       Call oLog.Failed ("Unable to WaitStress on the test adapter." , 88888)
   '   End If
   'Else
   '   Call oLog.Failed ("Unable to start stress on the test adapter." , 88888)
   'End If
   '@endcode
   '*/
   Public Function vbStartStress(oSvrOpen, lPacketSize, lOptionsMask, lIterations, lTestDuration)
      vbStartStress = m_oCOMOpen.StartStress(oSvrOpen.COMOpen, lPacketSize, lOptionsMask, lIterations, lTestDuration)
   End Function
   
   '===============================================================================================//
   '/**
   'This command waits for a stress test to complete.  Control does not return until the test is done.
   'This command is called on the same instance that vbStartStress was called on
   '@return  True if call is successful, otherwise returns false
   '@sa COpen::vbStartStress, COpen::vbGetStressResults
   '@code
   '  bResult = oTestOpen.vbWaitStress
   '@endcode
   '*/
   Public Function vbWaitStress()
      vbWaitStress = m_oCOMOpen.WaitStress()
   End Function
   
   '===============================================================================================//
   '/**
   'This command gets the test results of a completed stress test. This command is called on the
   'instance that sends the packets
   '@return True if the call is successful, otherwise returns false
   '@sa COpen::vbStartStress, COpen::vbWaitStress
   '@code
   '   bResult = oTestOpen.vbGetStressResults
   '@endcode
   '*/
   Public Function vbGetStressResults()
      vbGetStressResults = m_oCOMOpen.GetStressResults()
   End Function
   
   
   '===============================================================================================//
   '/**
   'This command will start a process waiting for an event.  Control is returned to the script which
   'later calls EndWaitForEvent.  The EndWaitForEvent will return when a timeout expires or the 
   'event occurs.  The following events can be waited on:<br>
   '      NDIS_STATUS_RESET_START<br>
   '      NDIS_STATUS_RESET_END<br>
   '      NDIS_STATUS_MEDIA_CONNECT<br>
   '      NDIS_STATUS_MEDIA_DISCONNECT<br>
   '      NDIS_STATUS_WAN_LINE_UP<br>
   '      NDIS_STATUS_WAN_LINE_DOWN<br>
   '      NDIS_STATUS_HARDWARE_LINE_UP<br>
   '      NDIS_STATUS_HARDWARE_LINE_DOWN<br>
   '      NDIS_STATUS_INTERFACE_UP<br>
   '      NDIS_STATUS_INTERFACE_DOWN<br>
   '@params ! number Event to wait for       
   '@return True for success
   '@sa COpen::vbEndWaitForEvent
   '@code
   'oLog.Variation("Checking disconnection of card")
   'bResult = oTestOpen.vbStartWaitForEvent(NDIS_STATUS_MEDIA_DISCONNECT)
   'If (Not bResult) Then
   '   oLog.Write("StartWaitForEvent returned failure" & vblf)
   'End If
   '
   'WshShell.Popup "Disconnect test card from the network, then click OK.", PopupTimeout, "Media Disconnect Detection", vbSystemModal
   '
   'bResult = oTestOpen.vbEndWaitForEvent(10)
   'If (bResult) Then
   '   oLog.Write("NDIS_STATUS_MEDIA_DISCONNECT indication received" & vblf)
   'Else
   '   call oLog.Failed ("No disconnect indication received" , 88888)
   'End If
   '@endcode
   '*/
   Public Function vbStartWaitForEvent(lEvent)
      vbStartWaitForEvent = m_oCOMOpen.StartWaitForEvent(lEvent)
   End Function
   
   '===============================================================================================//
   '/**
   'This command works with StartWaitForEvent. This will return when the timeout expires or the 
   'event occurs.
   '@params ! number Timeout in seconds       
   '@return True for success
   '@sa COpen::vbStartWaitForEvent
   '*/
   Public Function vbEndWaitForEvent(lTimeOut)
      vbEndWaitForEvent = m_oCOMOpen.EndWaitForEvent(lTimeOut)
   End Function
   
End Class

'<!-- CRC = 0x14a6a9e8 --->
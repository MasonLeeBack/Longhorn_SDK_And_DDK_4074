'================================================================================================='
'/**
'This file contains the functions that can be performed on an NDTCore::Open object for LAN
'media only
'@file
'@author    Mitesh Desai
'@alias     miteshd@microsoft.com
'*/
'================================================================================================='
Option Explicit

'================================================================================================='
'3 Document
'/**
'This class encapsulates the various operations that can be performed on a LAN NDTCore::Open
'object. It uses functionality provided by the connection less open object and also augments
'it with additional LAN specific functions
'@sa        CLanCard6, CCLOpen, COffloadOpen
'@date      12/07/2001
'@author    Mitesh Desai
'@alias     miteshd
'*/
Class CLanOpen6
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
   '*/
   Public Property Set COMOpen(p_oCOMOpen)
      Set m_oCOMOpen = p_oCOMOpen
   End Property

   '================================================================================================='
   '/**
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
   'This function returns the MAC address being currently used by the device. It is only
   'valid for Lan media. It will query the appropriate CURRENT_ADDRESS oid to obtain
   'this address.
   '@return    The mac address currently in use by the media (Null Address on error)
   '@code
   '  DestAddr = oSuppOpen.vbGetCardAddress
   '@endcode
   '*/
   Public Function vbGetCardAddress
      Dim CardAddr
      Dim AddrOid

      Select Case Me.NdisMedium
         Case NDISMEDIUM802_3
            AddrOid = OID_802_3_CURRENT_ADDRESS
         Case NDISMEDIUM802_5
            AddrOid = OID_802_5_CURRENT_ADDRESS
         Case NDISMEDIUMFDDI
            AddrOid = OID_FDDI_LONG_CURRENT_ADDR
         Case Else
            AddrOid = 0
            Call oLog.SafeFailed ("GetCardAddress: Unknown media" , 88888)
      End Select

      CardAddr = NullAddr()

      If (AddrOid <> 0) Then
         Dim ErrorStatus
         Dim BytesWritten, BytesNeeded
         Dim NdisStatus

         ErrorStatus = Me.vbNdisRequest( _
               AddrOid, _
               CardAddr, _
               6, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)

         If (ErrorStatus <> 0) Then
            call oLog.SafeFailed ("Could not obtain address of " & m_sAdapterType, 88888)
         End If

         If (NdisStatus <> 0) Then
            call oLog.SafeFailed ("Could not obtain address of " & m_sAdapterType , 88888)
         End If
      End If

      vbGetCardAddress = CardAddr
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
      Dim ErrorStatus
      Dim lMaxTotalSize

      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)

      ErrorStatus = Me.vbNdisRequest( _
            OID_GEN_MAXIMUM_TOTAL_SIZE, _
            lMaxTotalSize, _
            4, _
            REQUEST_QUERY_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            FALSE)

      If(ErrorStatus = 0) Then
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

   '============================================================================================='
   '/**
   ' The amount of time that the sender should wait, before it can assume  the
   ' driver/adapter has atleast made an attempt to send all the packets that
   ' were given to it. This time depends on the media.
   '@return The receive delay
   '@code
   '       lRecvDelay = oTestOpen.vbGetReceiveDelay()
   '@endcode
   '*/
   Public Function vbGetReceiveDelay()
      Select Case Me.NdisMedium
         Case NDISMEDIUM802_3
            vbGetReceiveDelay = 150
         Case NDISMEDIUM802_5
            vbGetReceiveDelay = 100
         Case NDISMEDIUMFDDI
            vbGetReceiveDelay = 50
         Case NDISMEDIUMIRDA
            vbGetReceiveDelay = 500
         Case Else
            oLog.Write("Receive Delay: Unsupported media" )
            vbGetReceiveDelay = 0
      End Select
   End Function



   '================================================================================================='
   '/**
   'This function sets the packet filter. It also prints the filter it is trying to set.
   'Internally it makes a ndisrequest with oid OID_GEN_CURRENT_PACKET_FILTER.
   '@params
   ' ! number The filter we are trying to set
   '@return    True or false depending on whether the oid set was successful or not
   '@code
   '  If (Not oTestOpen.vbSetPacketFilter(DIRECTED)) Then
   '     Exit Function
   '  End If
   '@endcode
   '@sa CLanOpen6::vbGetFilters
   '*/
   Public Function vbSetPacketFilter (ByVal NewFilter)
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim strFilters, ErrorStatus

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

      if (NewFilter AND ALL_FUNCTIONAL)Then
         strFilters = strFilters & "ALL_FUNCTIONAL "
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

      ErrorStatus = Me.vbNdisRequest(OID_GEN_CURRENT_PACKET_FILTER, _
            NewFilter, 4, REQUEST_SET_INFO, BytesWritten, BytesNeeded, NdisStatus, FALSE)

      If (ErrorStatus <> 0 Or NdisStatus <> 0) then
         call oLog.SafeFailed ("Unable to set packet filter for " & m_sAdapterType & " to " & Hex(NewFilter), 22852)
         vbSetPacketFilter = FALSE
      Else
         vbSetPacketFilter = TRUE
      End if
   End Function

   '================================================================================================='
   '/**
   '@exclude
   'This function sets the packet filter. It only prints messages from core, and none on its own.
   'Internally it makes a ndisrequest with oid OID_GEN_CURRENT_PACKET_FILTER. This is a private function
   'for internal use only
   '@params
   ' ! number The filter we are trying to set
   '@return    True or False depending on whether the oid set was successful
   '@code
   '  If (Not oTestOpen.vbSilentSetPacketFilter(DIRECTED)) Then
   '     Exit Function
   '  End If
   '@endcode
   '@sa  CLanOpen6::vbSetPacketFilter
   '*/
   Private Function vbSilentSetPacketFilter(ParamFilterType)
      Dim BytesWritten, BytesNeeded
      Dim NdisStatus, ErrorStatus
      Dim FilterType
      FilterType = ParamFilterType ' Do this because NdisRequest can change it

      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)

      ErrorStatus = Me.vbNdisRequest( _
            OID_GEN_CURRENT_PACKET_FILTER, _
            FilterType, _
            4, _
            REQUEST_SET_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            FALSE)

      vbSilentSetPacketFilter = TRUE
      If (ErrorStatus <> 0 Or NdisStatus <> 0) Then
         vbSilentSetPacketFilter = FALSE
      End If

   End Function


   '==========================================================================
   '/**
   'Gets all the filters supported by the card. The only way to obtain this
   'list is to try setting a filter, and if it suceeds, the filter is assumed
   'to be supported, else not. Because of some internal dependancies, it is
   'necessary that a Card::vbGetPhysicalMedium call must be made before
   'vbGetFilters is invoked
   '@return    Returns a bitmask of the set of filter currently supported
   '@code
   '  AvailFilters = oTestOpen.vbGetFilters()
   '@endcode
   '@sa CLanOpen6::vbSetPacketFilter
   '*/
   Public Function vbGetFilters()
      Dim bResult
      Dim l_nFilters
      Dim Media
      Dim OldFilter, FilterSize

      Media = m_nNdisMedium

      ' obtain the current filter, so that we can restore it at the end of this function
      OldFilter = CLng(0)
      FilterSize = 4
      bResult = Me.vbFastNdisRequest(OID_GEN_CURRENT_PACKET_FILTER, OldFilter, FilterSize)
      If (Not bResult) Then
         oLog.Write ("Unable to obtain pretest filter state. Assuming it is NONE")
         OldFilter = 0
      End If

      l_nFilters = CLng(0)
      If (Media = NDISMEDIUM802_3) Then
         l_nFilters = DIRECTED + BROADCAST + MULTICAST

         bResult = vbSilentSetPacketFilter(ALL_MULTICAST)
         If (bResult) Then
            l_nFilters = l_nFilters + ALL_MULTICAST
         End If
      ElseIf (Media = NDISMEDIUM802_5) Then
         l_nFilters = DIRECTED + BROADCAST + FUNCTIONAL + GROUP_PKT

         bResult = vbSilentSetPacketFilter(ALL_FUNCTIONAL)
         If (bResult) Then
            l_nFilters = l_nFilters + ALL_FUNCTIONAL
         End If

         bResult = vbSilentSetPacketFilter(SOURCE_ROUTING)
         If (bResult) Then
            l_nFilters = l_nFilters + SOURCE_ROUTING
         End If

         bResult = vbSilentSetPacketFilter(MAC_FRAME)
         If (bResult) Then
            l_nFilters = l_nFilters + MAC_FRAME
         End If

      ElseIf (Media = NDISMEDIUMFDDI) Then
         l_nFilters = DIRECTED + BROADCAST + MULTICAST

         bResult = vbSilentSetPacketFilter(ALL_MULTICAST)
         If (bResult) Then
            l_nFilters = l_nFilters + ALL_MULTICAST
         End If

         bResult = vbSilentSetPacketFilter(SOURCE_ROUTING)
         If (bResult) Then
            l_nFilters = l_nFilters + SOURCE_ROUTING
         End If

         bResult = vbSilentSetPacketFilter(MAC_FRAME)
         If (bResult) Then
            l_nFilters = l_nFilters + MAC_FRAME
         End If

         bResult = vbSilentSetPacketFilter(SMT)
         If (bResult) Then
            l_nFilters = l_nFilters + SMT
         End If
      Else
         call oLog.SafeFailed ("vbGetFilters called for invalid media type 0x" & Hex(Media), 88888)
      End If

      bResult = vbSilentSetPacketFilter(PROMISCUOUS)
      If (bResult) Then
         l_nFilters = l_nFilters + PROMISCUOUS
      Else
         ' Error is logged by LogoCheck.wsf
      End If

      bResult = vbSilentSetPacketFilter(ALL_LOCAL)
      If (bResult) Then
         l_nFilters = l_nFilters + ALL_LOCAL
      End If

      bResult = vbSilentSetPacketFilter(OldFilter)
      If (Not bResult) Then
         oLog.Write ("Unable to restore filter to pretest state")
      End If

      vbGetFilters = l_nFilters
   End Function


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
   Public Function vbNdisOpen()
      ' Open instance of the adapter
      vbNdisOpen = m_oCOMOpen.NdisOpen(m_nNdisMedium)
      If (vbNdisOpen <> 0) Then
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
   '@return value for NdisStatus that tells whether we could post the request or not (this
   '        is different from the status returned by NDIS which might be a failure
   '@code
   '  bResult = oTestOpen.vbNdisRequest (OID_GEN_SUPPORTED_LIST, arrList, 256, REQUEST_QUERY_INFO, _
         '                          nBytesWritten, nBytesNeeded, NdisStatus, TRUE)
   '@endcode
   '@sa COpen::vbFastNdisRequest, CCard::vbNdisIOControl
   '*/
   Public Function vbNdisRequest(ByVal nOID, ByRef DataArray, ByVal DataLen, ByVal QueryType, ByRef BytesWritten, ByRef BytesNeeded, ByRef nNdisStatus, ByVal bResize)
      Dim bRetval

      vbNdisRequest = m_oCOMOpen.NdisRequest(nOID, DataArray, DataLen, QueryType, BytesWritten, BytesNeeded, nNdisStatus)
      If(vbNdisRequest <> 0) Then
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
                  If(vbNdisRequest <> 0) then
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

   '================================================================================================='
   '/**
   '*/
   Public Function vbClearEvents
      vbClearEvents = m_oCOMOpen.GetEvents()
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
      If (vbNdisClose <> 0) Then
         oLog.Write ("Could not close open instance of " & m_sAdapterType)
      End If
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
      Dim BytesWritten, BytesNeeded, NdisStatus, ErrorStatus

      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)

      ' The caller generally knows what OID he is querying, and hence can give
      ' a better message than some general one. So, no failure logging inside this
      ' function
      ErrorStatus = Me.vbNdisRequest( _
            nOID, _
            Result, _
            ResultSize, _
            REQUEST_QUERY_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            TRUE)

      vbFastNdisRequest = TRUE
      If (NdisStatus <> 0 Or ErrorStatus <> 0) Then
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
      Dim BytesWritten, BytesNeeded, NdisStatus, ErrorStatus
      Dim ResultBuffer()
      Dim BufferSize
      Dim bResult

      BufferSize=256
      ReDim ResultBuffer(BufferSize)

      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)

      ResultBuffer(0) = CByte(0)
      ErrorStatus = Me.vbNdisRequest( _
            nOid, _
            ResultBuffer, _
            BufferSize, _
            REQUEST_QUERY_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            TRUE)

      vbPrintNdisRequest = TRUE
      If (NdisStatus <> 0 Or ErrorStatus <> 0) Then
         vbPrintNdisRequest = FALSE
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
      Dim NdisStatus, ErrorStatus
      ErrorStatus = m_oCOMOpen.NdisReset(NdisStatus)

      ' Our error status is higher priority than NDIS_STATUS
      If (ErrorStatus <> 0) Then
         vbNdisReset = ErrorStatus
      Else
         vbNdisReset = NdisStatus
      End If

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
      Dim ErrorStatus
      ErrorStatus = m_oCOMOpen.GetEvents (nResets, nDisconnects, nConnects)

      If (ErrorStatus <> 0) Then
         vbGetEvents = FALSE
      Else
         vbGetEvents = TRUE
      End If
   End Function


   '============================================================================================='
   '/**
   'Adds the new multicast address into the multicast address list in the NIC
   'enabled for packet reception. It uses either OID_802_3_MULTICAST_LIST or
   'OID_FDDI_LONG_MULTICAST_LIST for this purpose.
   '@TODO: This function will break after we move to Ndis 6.0
   '@params
   '  !  array The multicast address to be added
   '@return True on success, false otherwise
   '@code
   'If (Not oTestOpen.vbAddMuticastAddr(MultAddr)) Then
   '   Exit Function
   'End If
   '@endcode
   '@sa CLanOpen6::vbRemoveMulticastAddr, CLanOpen6::vbSetPacketFilter
   '*/
   Public Function vbAddMulticastAddr(ByVal NewMulticastAddr)
      Dim bResult, ErrorStatus
      Dim ulOid
      Dim ulSizeOid
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim MaxListSize

      Dim MulticastAddrList()
      Dim ListLen

      Do
         bResult = TRUE

         '
         ' check for valid medium and set ulOidCode as appropriate
         '
         If((m_nNdisMedium = NDISMEDIUM802_3) Or (m_nNdisMedium = NDISMEDIUMDIX)) Then
            ulOid = OID_802_3_MULTICAST_LIST
            ulSizeOid = OID_802_3_MAXIMUM_LIST_SIZE
         ElseIf (m_nNdisMedium = NDISMEDIUMFDDI) Then
            ulOid = OID_FDDI_LONG_MULTICAST_LIST
            ulSizeOid = OID_FDDI_LONG_MAX_LIST_SIZE
         Else
            Call oLog.SafeFailed("Add Multicast Address not valid for this mediatype", 88888)
            bResult = FALSE
            Exit Do
         End If

         ' Get the maximum number of multicast addresses possible
         MaxListSize = CLng(0)
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)

         ErrorStatus = Me.vbNdisRequest( _
               ulSizeOid, _
               MaxListSize, _
               4, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(ErrorStatus <> 0 Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to get max multicast list size from " & m_sAdapterType, 88888 )
            Exit Do
         End If

         ' The array MulticastAddrList holds the net addresses, in sequence,
         ' with the first 6 bytes forming one address, the next 6 the second, and so on

         ' The maximum size of this array is then 6 times the maximum addresses
         ListLen = 6 * MaxListSize

         Redim MulticastAddrList(ListLen-1)

         ' Let it be know that MulticastAddrList is an array of bytes
         MulticastAddrList(0) = CByte(MulticastAddrList(0))

         ErrorStatus = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               TRUE)
         If(ErrorStatus <> 0 Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to obtain old multicast address list from " & m_sAdapterType, 88888 )
            bResult = FALSE
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
                  Exit For
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

         ErrorStatus = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(ErrorStatus <> 0) Then
            Call oLog.SafeFailed("Unable to add multicast address to list on " & m_sAdapterType, 88888 )
         ElseIf (NdisStatus = NDIS_STATUS_MULTICAST_FULL) Then
            Call oLog.SafeFailed("Multicast address list full on " & m_sAdapterType, 88888)
            bResult = FALSE
         ElseIf (NdisStatus <> 0) Then
            Call oLog.SafeFailed("Add Multicast address failed on " & m_sAdapterType, 88888)
            bResult = FALSE
         End If
      Loop While(FALSE)

      If (bResult) Then
         If (ErrorStatus <> 0) Then
            bResult = FALSE
         End If
      End If
      vbAddMulticastAddr = bResult
   End Function

   '============================================================================================='
   '/**
   'Removes the given multicast address from the multicast address list
   'for the NIC.It uses either OID_802_3_MULTICAST_LIST or
   'OID_FDDI_LONG_MULTICAST_LIST for this purpose.
   '@TODO: This function will break after we move to Ndis 6.0
   '@params
   '  !  array The multicast address to be removed
   '@return True on success, false otherwise
   '@code
   'If (Not oTestOpen.vbRemoveMulticastAddr(MultAddr)) Then
   '   oLog.Write("Unable to remove multicast address")
   'End If
   '@endcode
   '@sa CLanOpen6::vbAddMulticastAddr, CLanOpen6::vbSetPacketFilter
   '*/
   Public Function vbRemoveMulticastAddr(ByVal OldMulticastAddr)
      Dim bResult, ErrorStatus
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

      Do
         bResult = TRUE

         '
         ' check for valid medium and set ulOidCode as appropriate
         '
         If ((m_nNdisMedium = NDISMEDIUM802_3) Or (m_nNdisMedium = NDISMEDIUMDIX)) Then
            ulOid = OID_802_3_MULTICAST_LIST
            ulSizeOid = OID_802_3_MAXIMUM_LIST_SIZE
         ElseIf (m_nNdisMedium = NDISMEDIUMFDDI) Then
            ulOid = OID_FDDI_LONG_MULTICAST_LIST
            ulSizeOid = OID_FDDI_LONG_MAX_LIST_SIZE
         Else
            Call oLog.SafeFailed("Delete Multicast Address not valid for this mediatype" , 88888)
            bResult = FALSE
            Exit Do
         End If

         ' Get the maximum number of multicast addresses possible
         MaxListSize = CLng(0)
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)
         ErrorStatus = Me.vbNdisRequest( _
               ulSizeOid, _
               MaxListSize, _
               4, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(ErrorStatus <> 0 Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to get max multicast list size from " & m_sAdapterType, 88888 )
            bResult = FALSE
            Exit Do
         End If

         ' The array MulticastAddrList holds the net addresses, in sequence,
         ' with the first 6 bytes forming one address, the next 6 the second, and so on

         ' The maximum size of this array is then 6 times the maximum addresses
         ListLen = 6 * MaxListSize

         Redim MulticastAddrList(ListLen-1)

         ' Let it be know that MulticastAddrList is an array of bytes
         MulticastAddrList(0) = CByte(MulticastAddrList(0))
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)

         ErrorStatus = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               TRUE)
         If(ErrorStatus <> 0 Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to obtain old multicast address list from " & m_sAdapterType, 88888)
            bResult = FALSE
            Exit Do
         Else
            ' Actual number of entries in the list
            ListLen = BytesWritten
         End If

         ' Maximum filled size of the new list that we would form
         Redim ModMulticastAddrList(ListLen-1)

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
            Call oLog.SafeFailed("Unable to find the multicast address to delete on " & m_sAdapterType, 88888)
            bResult = FALSE
            Exit Do
         End If

         ListLen = NewListLen

         BytesWritten = 0
         BytesNeeded = 0

         ErrorStatus = Me.vbNdisRequest( _
               ulOid, _
               ModMulticastAddrList, _
               ListLen, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(ErrorStatus <> 0 Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to delete multicast address from list on " & m_sAdapterType, 88888)
            bResult = FALSE
         End If

      Loop While (False)

      If (bResult) Then
         If (ErrorStatus <> 0) Then
            bResult = FALSE
         End If
      End If

      vbRemoveMulticastAddr = bResult
   End Function

   '================================================================================================='
   '/**
   'This API is used to Create an EndPoint on the Open Object. This API will also setup the CLanEndPoint
   'object that would be used for all the send/receive operations.
   '@params
   '  !  number The type of endpoint that should be created. If this is a CLENDPOINT,
   '              a CLanEndPoint6 would be created, else a a CLanEndPointEx6 would
   '              be created
   '@return Instance of CLanEndPoint{Ex}6 object created if successful, else Nothing
   '@code
   'Set oSuppEndPoint = oSuppOpen.vbCreateEndPoint (CLENDPOINT)
   'If (oSuppEndPoint Is Nothing) Then
   '   Exit Function
   'End If
   '@endcode
   '@sa  CLanEndPoint6::vbOpenCommunicationChannel, CLanEndPoint6::vbDestroyEndPoint,
   '     CLanEndPointEX6::vbOpenCommunicationChannel, CLanEndPointEx6::vbDestroyEndPoint
   '*/
   Public Function vbCreateEndPoint(EndPointType)
      Dim l_oCOMEndPoint          ' the NDTCore6::Open returned from above

      If (EndPointType = CLENDPOINT) Then
         Set l_oCOMEndPoint = m_oCOMOpen.CreateEndPoint(EndPointType)
      Else ' Ex Version
         Set l_oCOMEndPoint = m_oCOMOpen.CreateEndPointEx(EndPointType)
      End If

      If l_oCOMEndPoint is Nothing Then
         Call oLog.SafeFailed("Failed to create endpoint on " & m_sAdapterType, 88888)
         Set vbCreateEndPoint = Nothing
      Else
         Dim l_oEndPoint
         If (EndPointType = CLENDPOINT) Then
            Set l_oEndPoint = New CLanEndPoint6
         Else
            Set l_oEndPoint = New CLanEndPointEx6
         End If
         Set l_oEndPoint.COMEndPoint = l_oCOMEndPoint
         l_oEndPoint.AdapterType = m_sAdapterType
         l_oEndPoint.EndPointType = EndPointType

         Set vbCreateEndPoint = l_oEndPoint
      End If
   End Function

   '================================================================================================='
   '/**
   'Create a previously created CLanEndPoint6 object
   '@param
   '  !  Object An instance of CLanEndPoint6
   '@return The error status from the operation (0 if sucessful)
   '@code
   'ErrorStatus  = oSuppOpen.vbDestroyEndPoint (oSuppEndPoint)
   '@endcode
   '@sa  CLanEndPoint6::vbCreateEndPoint
   '*/
   Public Function vbDestroyEndPoint(oVBEndPoint)
      If (oVBEndPoint.EndPointType = CLENDPOINT) Then
         vbDestroyEndPoint = m_oCOMOpen.DestroyEndPoint(oVBEndPoint.COMEndPoint)
      Else ' Ex Version
         vbDestroyEndPoint = m_oCOMOpen.DestroyEndPointEx(oVBEndPoint.COMEndPoint)
      End If

      Set oVBEndPoint = Nothing
   End Function

   Public Function vbSetupForCommunication(EndPointType, CommunicationType)
      Dim oHelper, Status

      Set vbSetupForCommunication = Nothing

      ' Create the appropriate type of helper object
      Select Case CommunicationType
         Case SIMPLE_SEND_RECEIVE_TRAFFIC
            ' Create the simple communication helper
            Set oHelper = New CSimpleTrafficHelper
         Case STRESS_SEND_RECEIVE_TRAFFIC
            ' Create the stress communication helper
            Set oHelper = NEw CStressTrafficHelper
         Case Else
            oLog.Write ("Invalid communication test type specified: " & CommunicationType)
            Exit Function
      End Select

      ' We have created the helper object, we go and set it up
      Status = oHelper.vbSetupForCommunication(Me, EndPointType)
      If (Status <> NDIS_STATUS_SUCCESS) Then
         oLog.Write("Helper::SetupForCommunication failed")
         Set oHelper = Nothing
         Exit Function
      End If

      ' If everything succeeds, return the helper object
      Set vbSetupForCommunication = oHelper
   End Function

End Class




'<!-- CRC = 0x14e6cb8c --->
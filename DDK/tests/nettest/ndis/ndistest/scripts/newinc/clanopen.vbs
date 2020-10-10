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
'/**
'This class encapsulates the various operations that can be performed on a LAN NDTCore::Open
'object. It uses functionality provided by the connection less open object and also augments
'it with additional LAN specific functions
'@sa        CLanCard, CCLOpen, COffloadOpen
'@date      12/07/2001
'@author    Mitesh Desai
'@alias     miteshd
'*/
Class CLanOpen
   Dim m_oCLOpen
   Dim m_nPhysicalMedium

   Private Sub Class_Initialize
      Set m_oCLOpen     = Nothing
      m_nPhysicalMedium = -1
   End Sub

   Private Sub Class_Terminate
      Set m_oCLOpen = Nothing
   End Sub


   '================================================================================================='
   '/**
   '@exclude
   'The set property that is used by a CLanCard object to set the connectionless open
   'object that is required by this class. It is a hack used to obtain some kind of
   'inheritance structure in VBScript.
   '@params
   '! class This is the CCLOpen object that was created in the Card hierarchy
   '*/
   Public Property Set CLOpen(p_oCLOpen)
      Set m_oCLOpen = p_oCLOpen
   End Property

   '================================================================================================='
   '/**
   '@sa COpen::COMOpen
   '*/
   Public Property Get COMOpen
      Set COMOpen = m_oCLOpen.COMOpen
   End Property

   '================================================================================================='
   '/**
   '@sa   COpen::NdisMedium
   '*/
   Public Property Get NdisMedium
      NdisMedium = m_oCLOpen.NdisMedium
   End Property

   '================================================================================================='
   '/**
   '@sa COpen::AdapterType
   '*/
   Public Property Get AdapterType
      AdapterType = m_oCLOpen.AdapterType
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
         Dim bResult
         Dim BytesWritten, BytesNeeded
         Dim NdisStatus

         bResult = Me.vbNdisRequest( _
               AddrOid, _
               CardAddr, _
               6, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)

         If (Not bResult) Then
            call oLog.SafeFailed ("Could not obtain address of " & m_oCLOpen.AdapterType, 88888)
         End If

         If (NdisStatus <> 0) Then
            call oLog.SafeFailed ("Could not obtain address of " & m_oCLOpen.AdapterType , 88888)
         End If
      End If

      vbGetCardAddress = CardAddr
   End Function

   '================================================================================================='
   '/**
   '@sa   CCLOpen::vbGetMaxPacketSize
   '*/
   Public Function vbGetMaxPacketSize
      vbGetMaxPacketSize = m_oCLOpen.vbGetMaxPacketSize
   End Function

   '================================================================================================='
   '/**
   '@sa CCLOpen::vbGetReceiveDelay
   '*/
   Public Function vbGetReceiveDelay
      vbGetReceiveDelay = m_oCLOpen.vbGetReceiveDelay
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
   '@sa CLanOpen::vbGetFilters
   '*/
   Public Function vbSetPacketFilter (ByVal NewFilter)
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim strFilters, bResult

      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)

      strFilters = "SetPacketFilter is setting the packet filter to "

      if (NewFilter = 0)Then
         strFilters = strFilters & "NOTHING "
      End if

      if (NewFilter AND DIRECTED)Then
         strFilters = strFilters & "DIRECTED "
         If(m_nPhysicalMedium = NDISPHYSICALMEDIUMWIRELESSLAN) Then
            glPercentToPass = gWlanPercentToPassDirected
         End If
      End If

      if (NewFilter AND BROADCAST)Then
         strFilters = strFilters & "BROADCAST "
         If(m_nPhysicalMedium = NDISPHYSICALMEDIUMWIRELESSLAN) Then
            glPercentToPass = gWlanPercentToPassBroadcast
         End If
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

      bResult = m_oCLOpen.vbNdisRequest(OID_GEN_CURRENT_PACKET_FILTER, _
            NewFilter, 4, REQUEST_SET_INFO, BytesWritten, BytesNeeded, NdisStatus, FALSE)

      If (Not bResult Or NdisStatus <> 0) then
         call oLog.SafeFailed ("Unable to set packet filter for " & m_oCLOpen.AdapterType & " to " & Hex(NewFilter), 22852)
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
   '@sa  CLanOpen::vbSetPacketFilter
   '*/
   Private Function vbSilentSetPacketFilter(ParamFilterType)
      Dim BytesWritten, BytesNeeded
      Dim NdisStatus
      Dim FilterType
      FilterType = ParamFilterType ' Do this because NdisRequest can change it

      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)

      vbSilentSetPacketFilter = Me.vbNdisRequest( _
            OID_GEN_CURRENT_PACKET_FILTER, _
            FilterType, _
            4, _
            REQUEST_SET_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            FALSE)

      If (vbSilentSetPacketFilter AND NdisStatus <> 0) Then
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
   '@sa CLanOpen::vbSetPacketFilter
   '*/
   Public Function vbGetFilters()
      Dim bResult
      Dim l_nFilters
      Dim Media
      Dim OldFilter, FilterSize

      Media = m_oCLOpen.NdisMedium

      ' obtain the current filter, so that we can restore it at the end of this function
      OldFilter = CLng(0)
      FilterSize = 4
      bResult = m_oCLOpen.vbFastNdisRequest(OID_GEN_CURRENT_PACKET_FILTER, OldFilter, FilterSize)
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
   '@sa COpen::vbNdisOpen, CLanCard::vbSetupBasicTest
   '*/
   Public Function vbNdisOpen
   Dim bRetval : bRetval = False

      vbNdisOpen = m_oCLOpen.vbNdisOpen(FALSE)

      If(m_nPhysicalMedium = -1) Then
         bRetval = vbFastNdisRequest(OID_GEN_PHYSICAL_MEDIUM, m_nPhysicalMedium, 4)
      End If

   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbNdisOpenUnbindCapable
   '*/
   Public Function vbNdisOpenUnbindCapable

      vbNdisOpenUnbindCapable = m_oCLOpen.vbNdisOpenUnbindCapable()

   End Function



   '================================================================================================='
   '/**
   '@sa COpen::vbNdisRequest
   '*/
   Public Function vbNdisRequest(ByVal nOID, ByRef DataArray, ByVal DataLen, ByVal QueryType, ByRef BytesWritten, ByRef BytesNeeded, ByRef nNdisStatus, ByVal bResize)
      vbNdisRequest = m_oCLOpen.vbNdisRequest(nOID, DataArray, DataLen, QueryType, BytesWritten, BytesNeeded, nNdisStatus, bResize)
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbSetRemoteId
   '*/
   Public Sub vbSetRemoteId (lTestId)
      m_oCLOpen.vbSetRemoteId lTestId
   End Sub

   '================================================================================================='
   '/**
   '@sa COpen::vbSetLocalId
   '*/
   Public Sub vbSetLocalId (lTestId)
      m_oCLOpen.vbSetLocalId lTestId
   End Sub

   '================================================================================================='
   '/**
   '@sa COpen::vbSetReceiveOption
   '*/
   Public Sub vbSetReceiveOption (lReceiveOption)
      m_oCLOpen.vbSetReceiveOption lReceiveOption
   End Sub

   '================================================================================================='
   '/**
   '@sa COpen::vbSetChannelId
   '*/
   Public Sub vbSetChannelId (lTestId)
      m_oCLOpen.vbSetChannelId lTestId
    End Sub

   '================================================================================================='
   '/**
   '@sa COpen::vbVerifiedSendPackets
   '*/
   Public Function vbVerifiedSendPackets (arrDestAddr, nNumAddresses, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
      vbVerifiedSendPackets = m_oCLOpen.vbVerifiedSendPackets(arrDestAddr, nNumAddresses, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbVerifiedSend
   '*/
   Public Function vbVerifiedSend (DestAddr, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
      vbVerifiedSend = m_oCLOpen.vbVerifiedSend (DestAddr, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
   End Function

   '===============================================================================================//
   '/**
   '@sa COpen::vbSendPackets
   '*/
   Public Function vbSendPackets(arrDestAddr, lNumAddresses, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
      vbSendPackets = m_oCLOpen.vbSendPackets(arrDestAddr, lNumAddresses, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
   End Function

   '===============================================================================================//
   '/**
   '@sa COpen::vbSend
   '*/
   Public Function vbSend(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
      vbSend = m_oCLOpen.vbSend(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
   End Function

   '===============================================================================================//
   '/**
   '@sa COpen::vbStopSend
   '*/
   Public Function vbStopSend
      vbStopSend = m_oCLOpen.vbStopSend
   End Function

   '===============================================================================================//
   '/**
   '@sa COpen::vbWaitSend
   '*/
   Public Function vbWaitSend
      vbWaitSend = m_oCLOpen.vbWaitSend
   End Function

   '===============================================================================================//
   '/**
   '@sa COpen::vbGetSendResults
   '*/
   Public Function vbGetSendResults(ByRef lPacketsSent, ByVal lSendFailureType)
      vbGetSendResults = m_oCLOpen.vbGetSendResults(lPacketsSent, lSendFailureType)
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbStartReceive
   '*/
   Public Function vbStartReceive
      vbStartReceive = m_oCLOpen.vbStartReceive
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbStopReceive
   '*/
   Public Function vbStopReceive
      vbStopReceive = m_oCLOpen.vbStopReceive
   End Function


   '================================================================================================='
   '/**
   '@sa COpen::vbGetReceiveResults
   '*/
   Public Function vbGetReceiveResults (ByRef nPacketsReceived, ByRef nPacketsResent)
      vbGetReceiveResults = m_oCLOpen.vbGetReceiveResults (nPacketsReceived, nPacketsResent)
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbVerifyReceiveResendRet
   '*/
   Public Function vbVerifyReceiveResendRet(ByRef lRecvExpected, ByVal lMinRecvRequired, ByRef lResendExpected, ByVal lMinResendRequired)
      vbVerifyReceiveResendRet = m_oCLOpen.vbVerifyReceiveResendRet(lRecvExpected, lMinRecvRequired, lResendExpected, lMinResendRequired)
   End Function

   '================================================================================================='
   '/**
   'This function is the same as vbVerifyReceiveResendRet, it does not modify the passed variables   '@sa COpen::vbVerifyReceiveResendRet
   '*/
   Public Function vbVerifyReceiveResend(ByVal lRecvExpected, ByVal lMinRecvRequired, ByVal lResendExpected, ByVal lMinResendRequired)
      vbVerifyReceiveResend = Me.vbVerifyReceiveResendRet(lRecvExpected, lMinRecvRequired, lResendExpected, lMinResendRequired)
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbSendRaw
   '*/
   Public Function vbSendRaw(ByVal DataArray)
      vbSendRaw = m_oCLOpen.vbSendRaw(DataArray)
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbClearEvents
   '*/
   Public Function vbClearEvents
      vbClearEvents = m_oCLOpen.vbClearEvents()
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbNdisClose
   '*/
   Public Function vbNdisClose
      vbNdisClose = m_oCLOpen.vbNdisClose
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbFastNdisRequest
   '*/
   Public Function vbFastNdisRequest(ByVal nOID, ByRef Result, ByRef ResultSize)
      vbFastNdisRequest = m_oCLOpen.vbFastNdisRequest(nOID, Result, ResultSize)
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbPrintNdisRequest
   '*/
   Public Function vbPrintNdisRequest(ByVal nOID)
      vbPrintNdisRequest = m_oCLOpen.vbPrintNdisRequest(nOID)
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbNdisReset
   '*/
   Public Function vbNdisReset()
      vbNdisReset = m_oCLOpen.vbNdisReset
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbGetEvents
   '*/
   Public Function vbGetEvents(ByRef nResets, ByRef nDisconnects, ByRef nConnects)
      vbGetEvents = m_oCLOpen.vbGetEvents (nResets, nDisconnects, nConnects)
   End Function


   '================================================================================================='
   '/**
   '@sa COpen::vbStartPerformance
   '*/
   Public Function vbStartPerformance(oRemoteOpen, DestAddr, TestMode, PacketSize, PktsPerBurst, NumPackets, TestDuration, Delay, CancelPkts)
      If (IsNull(oRemoteOpen)) Then
         vbStartPerformance = m_oCLOpen.vbStartPerformance (NULL, DestAddr, TestMode, PacketSize, PktsPerBurst, NumPackets, TestDuration, Delay, CancelPkts)
      Else
         vbStartPerformance = m_oCLOpen.vbStartPerformance (oRemoteOpen.COMOpen, DestAddr, TestMode, PacketSize, PktsPerBurst, NumPackets, TestDuration, Delay, CancelPkts)
      End If
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbWaitPerformance
   '*/
   Public Function vbWaitPerformance ()
      vbWaitPerformance = m_oCLOpen.vbWaitPerformance()
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbGetPerformanceResults
   '*/
   Public Function vbGetPerformanceResults (nDuration, nBytesSent, nBytesReceived)
      vbGetPerformanceResults = m_oCLOpen.vbGetPerformanceResults(nDuration, nBytesSent, nBytesReceived)
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbStartWaitForEvent
   '*/
   Public Function vbStartWaitForEvent(lEvent)
      vbStartWaitForEvent = m_oCLOpen.vbStartWaitForEvent(lEvent)
      If (Not vbStartWaitForEvent) Then
         Call oLog.SafeFailed ("Unable to start wait for event", 88888)
      End If
   End Function

   '===============================================================================================//
   '/**
   '@sa COpen::vbEndWaitForEvent
   '*/
   Public Function vbEndWaitForEvent(lTimeOut)
      vbEndWaitForEvent = m_oCLOpen.vbEndWaitForEvent(lTimeOut)
   End Function

   '===============================================================================================//
   '/**
   '@sa COpen::vbStartStress
   '*/
   Public Function vbStartStress(oSvrOpen, lPacketSize, lOptionsMask, lIterations, lTestDuration)
      vbStartStress = m_oCLOpen.vbStartStress(oSvrOpen, lPacketSize, lOptionsMask, lIterations, lTestDuration)
   End Function

   '===============================================================================================//
   '/**
   '@sa COpen::vbWaitStress
   '*/
   Public Function vbWaitStress()
      vbWaitStress = m_oCLOpen.vbWaitStress()
   End Function

   '===============================================================================================//
   '/**
   '@sa COpen::vbGetStressResults
   '*/
   Public Function vbGetStressResults()
      vbGetStressResults = m_oCLOpen.vbGetStressResults()
   End Function

   '===============================================================================================//
   '/**
   '@sa CCLOpen::vbGetMaxLookahead
   '*/
   Public Function vbGetMaxLookahead(ByRef lMaxLookAhead)
      vbGetMaxLookahead = m_oCLOpen.vbGetMaxLookahead(lMaxLookAhead)
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
   '@sa CLanOpen::vbRemoveMulticastAddr, CLanOpen::vbSetPacketFilter
   '*/
   Public Function vbAddMulticastAddr(ByVal NewMulticastAddr)
      Dim bResult
      Dim ulOid
      Dim ulSizeOid
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim MaxListSize

      Dim MulticastAddrList()
      Dim ListLen

      Dim Media

      Media = m_oCLOpen.NdisMedium
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
            Call oLog.SafeFailed("Add Multicast Address not valid for this mediatype", 88888)
            bResult = FALSE
            Exit Do
         End If

         ' Get the maximum number of multicast addresses possible
         MaxListSize = CLng(0)
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)

         bResult = Me.vbNdisRequest( _
               ulSizeOid, _
               MaxListSize, _
               4, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(Not bResult Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to get max multicast list size from " & m_oCLOpen.AdapterType, 88888 )
            Exit Do
         End If

         ' The array MulticastAddrList holds the net addresses, in sequence,
         ' with the first 6 bytes forming one address, the next 6 the second, and so on

         ' The maximum size of this array is then 6 times the maximum addresses
         ListLen = 6 * MaxListSize

         Redim MulticastAddrList(ListLen-1)

         ' Let it be know that MulticastAddrList is an array of bytes
         MulticastAddrList(0) = CByte(MulticastAddrList(0))

         bResult = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               TRUE)
         If(Not bResult Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to obtain old multicast address list from " & m_oCLOpen.AdapterType, 88888 )
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

         bResult = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(Not bResult) Then
            Call oLog.SafeFailed("Unable to add multicast address to list on " & m_oCLOpen.AdapterType, 88888 )
         ElseIf (NdisStatus = NDIS_STATUS_MULTICAST_FULL) Then
            Call oLog.SafeFailed("Multicast address list full on " & m_oCLOpen.AdapterType, 88888)
            bResult = FALSE
         ElseIf (NdisStatus <> 0) Then
            Call oLog.SafeFailed("Add Multicast address failed on " & m_oCLOpen.AdapterType, 88888)
            bResult = FALSE
         End If
      Loop While(FALSE)
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
   '@sa CLanOpen::vbAddMulticastAddr, CLanOpen::vbSetPacketFilter
   '*/
   Public Function vbRemoveMulticastAddr(ByVal OldMulticastAddr)
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

      Media = m_oCLOpen.NdisMedium

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
            Call oLog.SafeFailed("Delete Multicast Address not valid for this mediatype" , 88888)
            bResult = FALSE
            Exit Do
         End If

         ' Get the maximum number of multicast addresses possible
         MaxListSize = CLng(0)
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)
         bResult = Me.vbNdisRequest( _
               ulSizeOid, _
               MaxListSize, _
               4, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(Not bResult Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to get max multicast list size from " & m_oCLOpen.AdapterType, 88888 )
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

         bResult = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               TRUE)
         If(Not bResult Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to obtain old multicast address list from " & m_oCLOpen.AdapterType, 88888)
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
            Call oLog.SafeFailed("Unable to find the multicast address to delete on " & m_oCLOpen.AdapterType, 88888)
            bResult = FALSE
            Exit Do
         End If

         ListLen = NewListLen

         BytesWritten = 0
         BytesNeeded = 0

         bResult = Me.vbNdisRequest( _
               ulOid, _
               ModMulticastAddrList, _
               ListLen, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(Not bResult Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to delete multicast address from list on " & m_oCLOpen.AdapterType, 88888)
            bResult = FALSE
         End If

      Loop While (False)
      vbRemoveMulticastAddr = bResult
   End Function

   '============================================================================================='
   '/**
   'This function sets the current functional address for the
   'open instance (token ring). It sets the address using the oid
   'OID_802_5_CURRENT_FUNCTIONAL.
   '@TODO: This function may break after we move to Ndis 6.0
   '@params
   '  !  array ParamFunctionalAddr       The functional address to set
   '@return True on success, false otherwise
   '@code
   'If (Not oTestOpen.vbSetFunctionalAddr(FuncAddr)) Then
   '   Exit Function
   'End If
   '@endcode
   '@sa CLanOpen::vbSetGroupAddr, CLanOpen::vbSetPacketFilter
   '*/
   Public Function vbSetFunctionalAddr(ByVal ParamFunctionalAddr)
      Dim bResult
      Dim ulOid
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim FunctionalAddr

      Dim Media

      Media = m_oCLOpen.NdisMedium
      NdisStatus = CLng(0)

      FunctionalAddr = ParamFunctionalAddr ' Do this because NdisRequest can change it

      Do
         bResult = FALSE

         '
         ' make sure that this is a valid OID code.  ie, must be token ring
         '
         If (Media <> NDISMEDIUM802_5) Then
            Call oLog.SafeFailed("SetFunctional not valid for this mediatype", 88888)
            Exit Do
         End If

         ulOid = OID_802_5_CURRENT_FUNCTIONAL

         ' Functional address length is a 4 byte array
         bResult = Me.vbNdisRequest( _
               ulOid, _
               FunctionalAddr, _
               4, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)

      Loop While(FALSE)
      '   SetFunctional = bResult
      If (bResult AND NdisStatus <> 0) Then
         Call oLog.SafeFailed("Unable to set functional address for " & m_oCLOpen.AdapterType, 88888)
         vbSetFunctionalAddr = FALSE
      Else
         vbSetFunctionalAddr = TRUE
      End If

   End Function

   '============================================================================================='
   '/**
   'This function sets the group address for the open instance (token ring only)
   'It sets the address using OID_802_5_CURRENT_GROUP oid.
   '@TODO: This function may break after we move to Ndis 6.0
   '@params
   '  ! array The group address to be set to
   '@return True on success, false otherwise
   '@code
   'If (Not oTestOpen.vbSetGroupAddr(GrpAddr)) Then
   '   Exit Function
   'End If
   '@endcode
   '@sa CLanOpen::vbSetFunctionalAddr, CLanOpen::vbSetPacketFilter
   '*/
   Public Function vbSetGroupAddr(ByVal ParamGroupAddr)
      Dim bResult
      Dim ulOid
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim GroupAddr

      Dim Media

      Media = m_oCLOpen.NdisMedium
      NdisStatus = CLng(0)

      GroupAddr = ParamGroupAddr ' Do this because NdisRequest can change it

      Do
         bResult = FALSE

         '
         ' make sure that this is a valid OID code.  ie, must be token ring
         '
         If (Media <> NDISMEDIUM802_5) Then
            Call oLog.SafeFailed("SetGroup not valid for this mediatype", 88888)
            Exit Do
         End If

         ulOid = OID_802_5_CURRENT_GROUP

         ' Group address length is a 4 byte array
         bResult = Me.vbNdisRequest( _
               ulOid, _
               GroupAddr, _
               4, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)

      Loop While(FALSE)
      If (bResult AND NdisStatus <> 0) Then
         Call oLog.SafeFailed("Unable to set group address for " & m_oCLOpen.AdapterType,88888)
         vbSetGroupAddr = FALSE
      Else
         vbSetGroupAddr = TRUE
      End If

   End Function

   '============================================================================================='
   '/**
   '@sa CCLOpen::vbSetLookahead
   '*/
   Public Function vbSetLookahead(ByVal Lookahead)
      vbSetLookahead = m_oCLOpen.vbSetLookahead (Lookahead)
   End Function

   '===============================================================================================//
   '/**
   'This function sets the Source and Destination IP addresses on open instance
   '@params
   '  ! string IP Address of a given adapter
   '  ! string IP Address of the adapter destined to receive IP packets
   '  ! array  MAC Address of the adapter's default gateway
   '@return	    Returns true if succesful else return false
   '@code
   'TestIP = "10.10.10.1"
   'SuppIP = "10.10.10.2"
   'TestGWAddr = Array(CByte(0),CByte(1),CByte(2),CByte(3),CByte(4),CByte(5))
   'bResult = oTestOpen.vbSetIPAddr(TestIP, SuppIP, TestGWAddr)
   '@endcode
   '*/
   Public Function vbSetIPAddress (sSrcIP, sDstIP, SrcGWAddr)
      Dim oCOMOpen

      Set oCOMOpen = m_oCLOpen.COMOpen
      vbSetIPAddress = oCOMOpen.SetIPAddr(sSrcIP, sDstIP, SrcGWAddr)
      if (not vbSetIPAddress) Then
         Call oLog.SafeFailed ("SetIPAddr failed for " & m_oCLOpen.AdapterType, 22849)
      end if

      Set oCOMOpen = Nothing
   End Function

   '===============================================================================================//
   '/**
   'This API can be used to check if send and receive is working between two devices.
   'The calling device is the sending instance and the passed device is the receiving/resending instance.
   'It setups the instances for sending/receiving/resending and then sends
   'the data and checks if the send/receive/resend was successful.
   'All functions called by this function would log failures and hence the caller may use
   'appropriate masks to avoid any kind of failure logging.
   'This function uses NdisSend to send.
   '@params
   '  ! class  The receiving instance
   '@return	   0 if everything (send-receive?resend) worked<br>
   '           1 if set up error<br>
   '           2 if send-receive failed<br>
   '@code
   '  'Stop logging of failures
   '  nLogMask = oLog.Mask
   '  oLog.Mask = DO_NOTHING
   '  nResult = oTestOpen.vbSimpleSendReceive (oSuppOpen)
   '  oLog.Mask = nLogMask
   '
   '  If (nResult <> 0) Then
   '     Call oLog.Failed ("Send receive does not work after loading/unloading of the driver", 88888)
   '  End If
   '@endcode
   '*/
   Public Function vbSimpleSendReceive (ByVal oRcvrOpen)
      Dim nTestId
      Dim nRetval, bResult, nResult
      Dim nTotalPackets, nPacketSize
      Dim nMinimumPass, nReceiveDelay

      Dim RcvrAddr, SenderAddr

      Const NO_ERROR = 0
      Const SETUP_ERROR = 1
      Const SENDRECV_ERROR = 2

      nRetval = NO_ERROR
      '
      ' Set the packet filters
      '
      If (Not oRcvrOpen.vbSetPacketFilter(DIRECTED)) Then
         nRetval = SETUP_ERROR
      End If

      If (Not Me.vbSetPacketFilter(DIRECTED)) Then
         nRetval = SETUP_ERROR
      End If

      nTestId = oNDTSupp.Random(1, 32765)

      ' set the channel id on sending/receiving sides
      Me.vbSetLocalId (nTestId)
      Me.vbSetRemoteId (nTestId)
      oRcvrOpen.vbSetLocalId (nTestId)
      oRcvrOpen.vbSetRemoteId (nTestId)

      ' Set receive options
      oRcvrOpen.vbSetReceiveOption(RECEIVE_DEFAULT Or RECEIVE_ALLOW_BUSY_NET)

      nTotalPackets = glPacketsToSend
      nPacketSize = glMinimumPacketSize
      nReceiveDelay = Me.vbGetReceiveDelay()

      ' get the address of the receiving nic
      RcvrAddr = oRcvrOpen.vbGetCardAddress()
      SenderAddr = Me.vbGetCardAddress ()

      ' Start receiving on the other open instance
      oRcvrOpen.vbStartReceive()
      Me.vbStartReceive ()

      ' send with resend info
      nResult = Me.vbVerifiedSend(RcvrAddr, nPacketSize, nTotalPackets, 0, SenderAddr)

      If (nResult <> nTotalPackets) Then
         nRetval = nRetval Or SENDRECV_ERROR
      End If

      nMinimumPass = (glPercentToPass * nTotalPackets) / 100

      Wscript.Sleep nReceiveDelay
      '
      ' the receiving card should receive all packets
      '
      bResult = oRcvrOpen.vbStopReceive
      If (bResult) Then
         ' check if received
         bResult = oRcvrOpen.vbVerifyReceiveResend(nTotalPackets, nMinimumPass, nTotalPackets, nMinimumPass)

         If (Not bResult) Then
            nRetval = nRetval Or SENDRECV_ERROR
         End If
      Else
         nRetval = nRetval Or SENDRECV_ERROR
      End If

      Wscript.Sleep nReceiveDelay
      '
      ' the sending should also receive all packets
      '

      bResult = Me.vbStopReceive
      If (bResult) Then
         bResult = Me.vbVerifyReceiveResend(nTotalPackets, nMinimumPass, 0, 0)
         If (Not bResult) Then
            nRetval = nRetval Or SENDRECV_ERROR
         End If
      Else
         nRetval = nRetval Or SENDRECV_ERROR
      End If

      vbSimpleSendReceive = nRetval
   End Function

   '**********************************************************'
   '                                                          '
   '          Function related to priority test               '
   '                                                          '
   '**********************************************************'

   '============================================================================================='
   '/**
   'This function tells the driver to start sending packets to
   'the address specified, with size, count, and resend address
   'also specified
   '@params
   '  ! class  The open instance on the server side
   '  ! array  The destination address
   '  ! number The packet size to use
   '  ! number Number of packets to send
   '  ! number The delay between packets
   '  ! constant Send Mode to use (PRIORITY_SEND, PRIORITY_SEND_PACKETS)
   '@return  TRUE or FALSE depending on the success of the operation
   '@sa  CLanOpen::vbWaitPriority, CLanOpen::vbGetPriorityResults
   '*/
   Public Function vbStartPriority(oRemoteOpen, DestAddr, PacketSize, NumPackets, lDelay, SendMode)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen

      vbStartPriority = oCOMOpen.StartPriority (oRemoteOpen.COMOpen, DestAddr, PacketSize, NumPackets, lDelay, SendMode)
      If (Not vbStartPriority) Then
         Call oLog.SafeFailed ("Unable to start priority tests in " & m_oCLOpen.AdapterType, 21594)
      End If
      Set oCOMOpen = Nothing
   End Function

   '============================================================================================='
   '/**
   ' This function waits until the remote server is done performing a
   ' priority send test, sending packets, then it returns
   '@return TRUE or FALSE depending on the success of the operation
   '@sa  CLanOpen::vbStartPriority, CLanOpen::vbGetPriorityResults
   '*/
   Public Function vbWaitPriority
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen

      vbWaitPriority = oCOMOpen.WaitPriority()
      If (Not vbWaitPriority) Then
         Call oLog.SafeFailed ("Unable to wait for priority tests on " & m_oCLOpen.AdapterType, 21595)
      End If
      Set oCOMOpen = Nothing
   End Function

   '============================================================================================='
   '/**
   'This function logs the results of the previous priority
   'tests.  It expects to be called after a waitpriority
   '@sa  CLanOpen::vbWaitPriority, CLanOpen::vbStartPriority
   '*/
   Public Function vbGetPriorityResults
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen

      vbGetPriorityResults = oCOMOpen.GetPriorityResults()
      If (Not vbGetPriorityResults) Then
         Call oLog.SafeFailed ("Unable to get priority test results on " & m_oCLOpen.AdapterType, 21596)
      End If
      Set oCOMOpen = Nothing
   End Function

   '**********************************************************'
   '                                                          '
   '          Function related to Wake-On-Lan                 '
   '                                                          '
   '**********************************************************'

   '============================================================================================='
   '/**
   'This function adds the specified wake pattern to the list kept by the NIC
   '@params
   '  !  number The NdisStatus of the operation is returned in this variable
   '  !  number The first piece of the pattern
   '  !  number The offset position of of the first piece in the pattern
   '  !  number The next piece of the pattern
   '  !  number The offset position of of the second piece in the pattern
   '  !  number The third piece of the pattern
   '  !  number The offset position of of the third piece in the pattern
   '@return True on success or false if failed to set wakeup type
   '@code
   'Piece1 = &H12345&
   'Piece2 = &H6789A&
   'Piece3 = &HBCDEF&
   '
   'If (oTestOpen.vbAddWakePattern (nNdisStatus, 0, Piece1, 4, Piece2, 8, Piece3)) Then
   '  oLog.Write ("Addition failed")
   'Exit Function
   '@endcode
   '@sa CLanOpen::vbRemoveWakePattern, CLanOpen::vbSetWakeupType
   '*/
   Public Function vbAddWakePattern (nNdisStatus, Offset1, Piece1, Offset2, Piece2, Offset3, Piece3)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      vbAddWakePattern = oCOMOpen.AddWakePattern (nNdisStatus, CLng (Offset1), CLng (Piece1), _
            CLng (Offset2), CLng (Piece2), CLng (Offset3), CLng (Piece3))

      If Not vbAddWakePattern Then
         call oLog.SafeFailed ("Failed to Add Wake Pattern to the " & m_oCLOpen.AdapterType, 88888)
      End If

      Set oCOMOpen = Nothing
   End Function

   '============================================================================================='
   '/**
   'This function removes the specified wake pattern from the list kept by the NIC
   '@params
   '  !  number The NdisStatus of the operation is returned in this variable
   '  !  number The first piece of the pattern
   '  !  number The offset position of of the first piece in the pattern
   '  !  number The next piece of the pattern
   '  !  number The offset position of of the second piece in the pattern
   '  !  number The third piece of the pattern
   '  !  number The offset position of of the third piece in the pattern
   '@return True on success or false if failed to set wakeup type
   '@code
   'Piece1 = &H12345&
   'Piece2 = &H6789A&
   'Piece3 = &HBCDEF&
   '
   'If (oTestOpen.vbRemoveWakePattern (nNdisStatus, 0, Piece1, 4, Piece2, 8, Piece3)) Then
   '  oLog.Write ("Removal failed")
   'Exit Function
   '@endcode
   '@sa CLanOpen::vbAddWakePattern, CLanOpen::vbSetWakeupType
   '*/
   Public Function vbRemoveWakePattern (nNdisStatus, Offset1, Piece1, Offset2, Piece2, Offset3, Piece3)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      vbRemoveWakePattern = oCOMOpen.RemoveWakePattern (nNdisStatus, CLng (Offset1), CLng (Piece1), _
            CLng (Offset2), CLng (Piece2), CLng (Offset3), CLng (Piece3))

      If Not vbRemoveWakePattern Then
         call oLog.SafeFailed ("Failed to Remove Wake Pattern from the " & m_oCLOpen.AdapterType, 88888)
      End If

      Set oCOMOpen = Nothing
   End Function

   '============================================================================================='
   '/**
   'This function sets Wakeup type information onto the NIC.
   '@params !  constant The type of event to wakeup on. The values are<br>
   '                 WAKE_UP_MAGIC_PACKET    Wake on receiving a magic packet<br>
   '                 WAKE_UP_PATTERN_MATCH   Wake up on receiving a registered pattern
   '@return True on success or false if failed to set wakeup type
   '@code
   'If (not oTestOpen.vbSetWakeupType (WAKE_UP_PATTERN_MATCH)) Then
   '  call oLog.Failed ("Could not set wakeup type on test card", 88888)
   '  Exit Function
   'End If
   '@endcode
   '@sa CLanOpen::vbAddWakePattern, CLanOpen::vbDelayedSendRaw, CLanOpen::vbDelayedSendBuffer, CLanCard::vbWakeOnLanSupportInfo
   '*/
   Public Function vbSetWakeupType (WakeType)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen

      vbSetWakeupType = oCOMOpen.SetWakeupType (WakeType)
      If (Not vbSetWakeupType) Then
         call oLog.SafeFailed ("Unable to set wakeup type for " & m_oCLOpen.AdapterType, 21304)
      End If

      Set oCOMOpen = Nothing
   End Function

   '================================================================================================='
   '/**
   'This function queries and parses the OID_PNP_CAPABILITIES on the nic. It finds out if the
   'nic supporst wake up with magic packet, pattern match and link change
   '@params ! number returns the wake on lan capability for the nic on this system
   '@sa CLanOpen::vbSetWakeupType
   '*/
   Public Function vbWakeOnLanSupportInfo (ByRef nSystemWakeOnLanSupport)
      Dim WolSupport
      Dim Levels()
      Dim ArraySize, Flags, bResult
      Dim MinMagicPacketWakeUp, MinPatternWakeUp, MinLinkChangeWakeUp

      nSystemWakeOnLanSupport = 0

      WolSupport = CLng(0)
      ReDim Levels(3)
      Levels(0) = CLng(0)

      bResult = m_oCLOpen.vbFastNdisRequest(OID_PNP_CAPABILITIES, Levels, 16)
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
            If (Flags <> 0) Then
               nSystemWakeOnLanSupport = 1
            Else
               If (WolSupport = 0) Then
                  oLog.Write("WakeOnLan is not enabled/supported for this adapter on this machine." )
               End If
            End If
         Else
            call oLog.SafeFailed ("WakeOnLanSupport query: Unexpected array size " & ArraySize & " from oTestCard.NdisIOControl", 22859)
         End If
      End If

      vbWakeOnLanSupportInfo = WolSupport

   End Function

   '============================================================================================='
   '/**
   'Delayed send raw tells the Open to send some data (Without making any changes to it)
   'after nDelay amount of time.
   '@return True on success, else failure
   '@code
   '    If (Not oSuppOpen.vbDelayedSendRaw (60, Pattern)) Then
   '       call oLog.Failed ("Unable to get Support card to send delayed pattern")
   '    End If
   '@endcode
   '@sa COpen::vbSend, COpen::vbSendPackets, CLanOpen::vbDelayedSendBuffer
   '*/
   Public Function vbDelayedSendRaw(nDelay, Data)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      vbDelayedSendRaw = oCOMOpen.DelayedSendRaw (nDelay, Data)
      If (Not vbDelayedSendRaw) Then
         call oLog.SafeFailed ("Delayed Send Raw failed for " & m_oCLOpen.AdapterType, 88888)
      End If

      Set oCOMOpen = Nothing
   End Function

   '============================================================================================='
   '/**
   'Delayed send Buffer tells the Open to send some data (Without making any changes to it)
   'after nDelay amount of time.
   '@return True on success, else failure
   '@code
   '    If (Not oSuppOpen.vbDelayedSendBuffer (60, BroadcastAddr, Pattern)) Then
   '       call oLog.Failed ("Unable to get Support card to send delayed pattern")
   '    End If
   '@endcode
   '@sa COpen::vbSend, COpen::vbSendPackets, CLanOpen::vbDelayedSendRaw
   '*/
   Public Function vbDelayedSendBuffer(nDelay, DestAddr, Data)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      vbDelayedSendBuffer = oCOMOpen.DelayedSendBuffer (nDelay, DestAddr, Data)
      If (Not vbDelayedSendBuffer) Then
         call oLog.SafeFailed ("Delayed Send Buffer failed for " & m_oCLOpen.AdapterType, 88888)
      End If

      Set oCOMOpen = Nothing
   End Function
End Class



'<!-- CRC = 0xf80bbf38 --->
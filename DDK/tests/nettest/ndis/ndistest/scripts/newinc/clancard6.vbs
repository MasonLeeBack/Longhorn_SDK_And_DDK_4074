Option Explicit

'3 Document
'================================================================================================='
'/**
'This class encapsulates the various operations that can be performed on a LAN NDTCore::Card
'object. It uses functionality provided by the connection less card object and also augments
'it with additional LAN specific functions
'@sa        CLanOpen6
'@date      12/03/2002
'@author    Mitesh Desai
'@alias     miteshd
'*/
Class CLanCard6
   Dim   m_oCOMAdapter       ' The NDTCore6::Card object
   Dim   m_sAdapterType      ' Type of adapter
   Dim   m_nNdisMedium

   Private Sub Class_Initialize
      Set m_oCOMAdapter = Nothing
   End Sub

   Private Sub Class_Terminate
      Set m_oCOMAdapter = Nothing
   End Sub

   '================================================================================================='
   '/**
   '*/
   Public Property Get COMAdapter
      Set COMAdapter = m_oCOMAdapter
   End Property

   '================================================================================================='
   '/**
   '*/
   Public Property Get AdapterType
      AdapterType = m_sAdapterType
   End Property

   '================================================================================================='
   '/**
   '*/
   Public Function vbCreateAdapter(oInfoAdapter)
      vbCreateAdapter = TRUE

      If (oInfoAdapter.AdapterType = 1) Then
         m_sAdapterType = "Test adapter"
      ElseIf (oInfoAdapter.AdapterType = 2) Then
         m_sAdapterType = "Support adapter"
      ElseIf (oInfoAdapter.AdapterType = 3) Then
         m_sAdapterType = "Message adapter"
      ElseIf (oInfoAdapter.AdapterType = 4) Then
         m_sAdapterType = "Virtual Wan adapter"
      Else
         m_sAdapterType = "Unknown adapter"
      End If

      m_nNdisMedium = CLng(oInfoAdapter.NdisMedium)

      Set m_oCOMAdapter = oNDTCore6.CreateAdapter(oInfoAdapter)
      If (m_oCOMAdapter is Nothing) Then
         Call oLog.SafeFailed ("Failed to create " & m_sAdapterType & " object", 88888)
         vbCreateAdapter = FALSE
      End If
   End Function

   '================================================================================================='
   '/**
   'This API is used to Create an Open on the Adapter Object. This API will also setup the CLanOpen
   'object that would be used for all the open operations.
   '@return Instance of CLanOpen object created if successful, else Nothing
   '@code
   'Set oSuppOpen = oSuppCard.vbCreateOpen ()
   'If (oSuppOpen Is Nothing) Then
   '   Exit Function
   'End If
   '@endcode
   '@sa    CLanCard6::vbSetupBasicTest, CLanOpen6::CLOpen
   '*/
   Public Function vbCreateOpen
      Dim l_oCOMOpen          ' the NDTCore6::Open returned from above

      Set l_oCOMOpen = m_oCOMAdapter.CreateOpen(m_nNdisMedium)
      If l_oCOMOpen is Nothing Then
         Call oLog.SafeFailed("Failed to create open on " & m_sAdapterType, 88888)
         Set vbCreateOpen = Nothing
      Else
         Dim l_oOpen
         Set l_oOpen = New CLanOpen6
         Set l_oOpen.COMOpen = l_oCOMOpen
         l_oOpen.NdisMedium = m_nNdisMedium
         l_oOpen.AdapterType = m_sAdapterType
         Set vbCreateOpen = l_oOpen
      End If
   End Function

   '================================================================================================='
   '/**
   '*/
   Public Property Get NdisMedium
      NdisMedium = m_nNdisMedium
   End Property


   '================================================================================================='
   '/**
   'This function works on the adapter object held within the hierarchy,
   'creating an open object and performing an ndisopen on that object.
   'Internally, it relies on vbCreateOpen and vbNdisOpen to do the work
   'for it
   '@return The CLanOpen object that has a "NdisOpened" instance
   '@code
   'Set oTestOpen = oTestCard.vbOpenAdapter
   'If (oTestOpen is Nothing) Then
   '   Exit Function
   'End If
   '@endcode
   '@sa  CLanCard6::vbCreateOpen, CLanOpen6::vbNdisOpen, CLanCard6::vbSetupBasicTest
   '*/
   Public Function vbOpenAdapter
      Dim l_oLanOpen

      Set l_oLanOpen = Me.vbCreateOpen

      If (Not (l_oLanOpen is Nothing)) Then
         If (l_oLanOpen.vbNdisOpen <> 0) Then
            Set l_oLanOpen = Nothing
         End If
      End If

      Set vbOpenAdapter = l_oLanOpen
   End Function

   '================================================================================================='
   '/**
   'This function takes an NDInfo adapter object and returns a CLanOpen object containing
   'a "NdisOpened" instance
   '@params
   '  !  object A NDInfo::Adapter object (element from ndinfo::adapterlist)
   '@return    A CLanOpen object or Nothing depending on success
   '@code
   '   Set oTestCard = New CLanCard6
   '   Set oTestOpen = oTestCard.vbSetupBasicTest(oNDInfo.AdapterList(lTestAdapterIndex))
   '   If (oTestOpen is Nothing) Then
   '     Exit Function
   '   End If
   '@endcode
   '@sa  CLanCard6::vbCreateAdapter, CLanCard6::vbCreateOpen, CLanOpen::vbNdisOpen
   '*/
   Public Function vbSetupBasicTest (oInfoAdapter)
      If (Me.vbCreateAdapter(oInfoAdapter)) Then
         Set vbSetupBasicTest = Me.vbOpenAdapter
      Else
         Set vbSetupBasicTest = Nothing
      End If
   End Function

   '================================================================================================='
   '/**
   '*/
   Public Function vbNdisIOControl(OidList, NumOids, ByRef DataBuffer, BufferLen, ByRef BytesWritten, ByRef ErrorStatus, IoControlCode)
      Dim bRetval
      Dim RequestStatus

      RequestStatus = m_oComAdapter.NdisIoControl(IoControlCode, OidList, NumOids, DataBuffer, BufferLen, BytesWritten, ErrorStatus)
      If(RequestStatus <> 0) Then
          Call oLog.SafeFailed( "First attempt at NdisIoControl failed!!", 88888)
          Exit Function
      End If

      Do While (ErrorStatus = ERROR_INSUFFICIENT_BUFFER Or ErrorStatus = ERROR_MORE_DATA)
         If (IsArray (DataBuffer)) Then
            ' Its an array, lets try increasing the size of the array and redoing the call
            oLog.Write("Insufficient buffer " & BufferLen & " provided to NdisRequest. Adjusting array length to " & BufferLen + 1024 & " and retrying")

            ' The previous call may return a size not a multiple of 4. So, adjust it to a multiple of 4
            BufferLen = BufferLen + 1024

            ReDim Preserve DataBuffer(BufferLen)
         Else
            oLog.Write("Not retrying with data type: " & TypeName(DataBuffer))
            RequestStatus = NDIS_STATUS_FAILURE
            Exit Do
         End If

         ' Retry the request
         RequestStatus = m_oComAdapter.NdisIoControl(IoControlCode, OidList, NumOids, DataBuffer, BufferLen, BytesWritten, ErrorStatus)
         If(RequestStatus <> 0) Then
            Call oLog.SafeFailed( "Second attempt at NdisIoControl failed!!", 88888)
            Exit Do
         End If

      Loop

      If (ErrorStatus <> 0) Then
         oLog.Write ("Status returned = " & ErrorStatus)
      End If

      ' We return the STATUS code returned from the NdisIOControl call
      vbNdisIOControl = RequestStatus
   End Function


   '================================================================================================='
   '/**
   ' This is a backward compatibility function. No new script should use this function (use the
   ' Ex version instead).
   ' This works like the old NdisIoControl and actually allocates space in the input buffer,
   ' and copies the results of NdisIoControl into that buffer and returns that to the caller
   '*/
   Public Function vbFastNdisIOControl(ByVal Oid, ByRef InputBuffer, ByVal QueryMode)
      Dim BytesWritten, NdisIoControlStatus, ErrorStatus
      Dim DataBufferLen

      ' The old scripts do not pass an allocated buffer in, they expect us to create and populate
      ' the buffer
      If (IsArray(InputBuffer)) Then
         If (UBound(InputBuffer) > 0) Then
            If (VarType(InputBuffer(0)) = vbLong) Then
               DataBufferLen = (UBound(InputBuffer) + 1)* 4
               oLog.Write("Long Array  " & DataBufferLen)
            Else
               DataBufferLen = (UBound(InputBuffer) + 1)
               oLog.Write("Byte Array  " & DataBufferLen)
            End If
         Else
            oLog.Write("Empty Array  ")
            DataBufferLen = 0
         End If
      Else
         If (VarType(InputBuffer) = vbLong) Then
            oLog.Write ("Long variable")
            DataBufferLen = 4
         ElseIf (VarType(InputBuffer) = vbEmpty) Then
            ' For empty input variable, the length is zero
            oLog.Write ("Empty variable")
            DataBufferLen = 0
         Else
            oLog.Write ("Byte variable")
            DataBufferLen = 1
         End If
      End If

      ' We always assume that we get called with one (and only one) OID
      NdisIoControlStatus = Me.vbNdisIOControl (Oid, 1, InputBuffer, DataBufferLen, BytesWritten, ErrorStatus, QueryMode)

      If ((NdisIoControlStatus <> 0) Or (ErrorStatus <> 0)) Then
         vbFastNdisIOControl = FALSE
      Else
         vbFastNdisIOControl = TRUE
      End If
   End Function

   '============================================================================================='
   '/**
   'This method returns the Maximum Packet Size supported by the NIC. If the NIC reports
   'the MaxPacketSize as anything less than 40 bytes, or the query OID failes we log a
   'safe error and report max packet size to the caller as being 50 bytes. Internally it
   'is a query to OID_GEN_MAXIMUM_TOTAL_SIZE.
   '@return The maximum packet size supported by the NIC
   '@code
   'nMaxPacketSize = oTestCard.vbGetMaxPacketSize
   '@endcode
   '*/
   Public Function vbGetMaxPacketSize
      Dim bResult, nMaxPacketSize

      bResult = Me.vbFastNdisIOControl(OID_GEN_MAXIMUM_TOTAL_SIZE, nMaxPacketSize, QUERY_GLOBAL_STATS)
      vbGetMaxPacketSize = nMaxPacketSize

      If(bResult) Then
         if (nMaxPacketSize < 50) Then
            Call oLog.SafeFailed ("Invalid MaxPacketSize = " & nMaxPacketSize & " received from " & m_sAdapterType, 88888)
            vbGetMaxPacketSize = 50
         End If
      Else
         Call oLog.SafeFailed ("Unable to get maximum total size for " & m_sAdapterType, 88888)
         vbGetMaxPacketSize = 50
      End If
   End Function

'   '================================================================================================='
'   '/**
'   'This function returns the mac address currently being used by the device. This
'   'function obtains the address by doing an NdisIOControl with the OID. If a CLanOpen
'   'object is present, use CLanOpen::vbGetCardAddress instead
'   '@return    The mac address of the device
'   '@code
'   '  CardAddress = oTestCard.vbGetCardAddress
'   '@endcode
'   '@sa     CLanOpen::vbGetCardAddress
'   '*/
'   Public Function vbGetCardAddress
'      Dim CardAddr, bResult, AddrOid
'
'      Select Case m_nNdisMedium
'         Case NDISMEDIUM802_3
'            AddrOid = OID_802_3_CURRENT_ADDRESS
'         Case NDISMEDIUM802_5
'            AddrOid = OID_802_5_CURRENT_ADDRESS
'         Case NDISMEDIUMFDDI
'            AddrOid = OID_FDDI_LONG_CURRENT_ADDR
'         Case Else
'            AddrOid = 0
'            Call oLog.SafeFailed ("GetCardAddress: Unknown media" , 22869)
'      End Select
'
'      CardAddr = NullAddr()
'
'      If (AddrOid <> 0) Then
'         bResult = Me.vbFastNdisIOControl(AddrOid, CardAddr, QUERY_GLOBAL_STATS)
'         If (Not bResult) Then
'            call oLog.SafeFailed ("Could not obtain address of " & m_sAdapterType, 22866)
'         End If
'      End If
'
'      vbGetCardAddress = CardAddr
'   End Function

   '============================================================================================='
   '/**
   'This method is used to get the Physical Medium on which the test is running. It
   'is a query to the oid OID_GEN_PHYSICAL_MEDIUM.
   '@return The Physical Medium on success else return zero on failure or if
   'OID_GEN_PHYSICAL_MEDIUM is not supported
   '@code
   'If (oTestCard.vbGetPhysicalMedium = 0 )Then
   '   oLog.Failed ("Failed to get Physical Medium", 88888)
   '   Exit Function
   'End If
   '@endcode
   '*/
   Public Function vbGetPhysicalMedium()
      Dim l_nPhysicalMedium, bResult

      l_nPhysicalMedium = 0
      bResult = Me.vbFastNdisIOControl(OID_GEN_PHYSICAL_MEDIUM, l_nPhysicalMedium, QUERY_GLOBAL_STATS)

      If (Not bResult) Then
         oLog.Write("Optional oid OID_GEN_PHYSICAL_MEDIUM is not supported for test adapter" )
         vbGetPhysicalMedium = 0
      ElseIf ((l_nPhysicalMedium > NDISPHYSICALMEDIUMRESERVED0) And (l_nPhysicalMedium < NDISPHYSICALMEDIUMMAX)) Then
         vbGetPhysicalMedium = l_nPhysicalMedium
      Else
         If (l_nPhysicalMedium <> NDISPHYSICALMEDIUMRESERVED0) Then
            oLog.SafeWarned ("Query to OID_GEN_PHYSICAL_MEDIUM returned invalid medium for test adapter")
         End If
         vbGetPhysicalMedium = 0
      End If
   End Function

   '============================================================================================='
   '/**
   'This method is used to get the maximum speed of the NIC in kbps. It is
   'a query to the oid OID_GEN_LINK_SPEED.
   '@return The link speed on success and -1 on failure
   '@code
   'If (oTestCard.vbGetLinkSpeed () < 0 )Then
   '   oLog.Failed ("Failed to get link speed", 88888)
   '   Exit Function
   'End If
   '@endcode
   '*/
   Function vbGetLinkSpeed()
      Dim bResult
      Dim ulOid
      Dim nLinkSpeed

      ulOid = OID_GEN_LINK_SPEED
      bResult = Me.vbFastNdisIOControl(ulOid, nLinkSpeed, QUERY_GLOBAL_STATS)
      If(bResult) Then
         oLog.Write("Link speed = " & nLinkSpeed )
      Else
         nLinkSpeed = -1
         oLog.Write("Unable to obtain link speed from " & m_sAdapterType )
      End If
      vbGetLinkSpeed = nLinkSpeed
   End Function

   '============================================================================================='
   '/**
   'Returns the broadcast address to be used with the particular media
   '@return The broadcast address
   '@code
   '       lBroadcastAddr = oTestCard.vbGetBroadcastAddress()
   '@endcode
   '*/
   Public Function vbGetBroadcastAddress()
      Dim l_nBroadcastAddr

      Select Case m_nNdisMedium
         Case NDISMEDIUM802_3
            l_nBroadcastAddr = NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&)
         Case NDISMEDIUM802_5
            l_nBroadcastAddr = NetAddr(&Hc0&, &H00&, &Hff&, &Hff&, &Hff&, &Hff&)
         Case NDISMEDIUMFDDI
            l_nBroadcastAddr = NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&)
         Case Else
            oLog.Write("BroadCast Address: Unknown media. Set to all 1s" )
            l_nBroadcastAddr = NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&)
      End Select

      vbGetBroadcastAddress = l_nBroadcastAddr
   End Function

   '============================================================================================='
   '/**
   'Wait for the MEDIA_CONNECT_STATUS to change to connected. It does this by repeatedly
   'quering the oid OID_GEN_MEDIA_CONNECT_STATUS until it returns status connected, or
   'until it has queries WaitTime number of times.
   '@params WaitTime  The time to wait for the link to be established
   '@return  True if could establish link before timeout, else false
   '@code
   '   If (Not oTestCard.vbWaitForLink(90)) Then
   '       oLog.Write("Unable to establish link status")
   '   End If
   '@endcode
   '*/
   Function vbWaitForLink(WaitTime)
      Dim ConnectStatus
      Dim Connected, nCount
      Dim bResult

      ConnectStatus = CLng(0)
      Connected = 0
      nCount = 0

      vbWaitForLink = False

      Do While (True)
         ' Sleep for a second
         Wscript.Sleep 1000

         bResult = Me.vbFastNdisIOControl(OID_GEN_MEDIA_CONNECT_STATUS, ConnectStatus, QUERY_GLOBAL_STATS)
         If (Not bResult) Then
            call oLog.Write ("Unable to query media connect status.  If this is transient then it is not a failure." )
         ElseIf (ConnectStatus = Connected) Then
            ' If connected, then we are done! Return success
            vbWaitForLink = TRUE
            Exit Do
         End If

         If (nCount = WaitTime) Then
            call oLog.SafeFailed ("Could not establish the link in " & WaitTime & " seconds! Bailing out", 88888)
            Exit Do
         End If

         nCount = nCount + 1
      Loop
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
      bResult = Me.vbFastNdisIOControl(OID_PNP_CAPABILITIES, Levels, QUERY_GLOBAL_STATS)
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
End Class

'<!-- CRC = 0xe96f185c --->
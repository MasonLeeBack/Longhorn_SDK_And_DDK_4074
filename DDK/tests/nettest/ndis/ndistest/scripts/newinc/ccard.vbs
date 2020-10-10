Option Explicit

'================================================================================================='
'/**
' The base Card class. This class and all its children are the ones which
' generate a NDTCore::Card object and make all the calls available from
' the Adapter interface
' @date     12/05/2001
' @author   Mitesh Desai
' @alias    miteshd@microsoft.com
'*/
Class CCard
   Dim     m_oCOMAdapter         ' The NDTCore::Card object
   Dim     m_sAdapterType      ' Type of adapter
   Dim     m_nNdisMedium

   Private Sub Class_Initialize
      Set m_oCOMAdapter = Nothing

   End Sub

   Private Sub Class_Terminate
      Set m_oCOMAdapter = Nothing
   End Sub

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
   'This property would return the COM card instance to the caller. This property
   'should NOT be used other outside the class hierarchy. It is only provided to allow
   'derived classes to implement media specific tests.
   '
   '@return    The COM card instance this hierarchy is working with
   '@code
   '  Set oCOMCard = oTestCard.COMAdapter
   '@endcode
   '*/
   Public Property Get COMAdapter
      Set COMAdapter = m_oCOMAdapter
   End Property

   '============================================================================================='
   '/**
   'This method is used to get the Ndis medium on which the test is running
   'The information is initially obtained from the adapter object that this
   'CCard instance was created for,
   '@return The Ndis Medium on success else return zero on failure
   '@code
   'If (oTestCard.NdisMedium = 0 )Then
   '   oLog.Failed ("Failed to get Ndis Medium", 88888)
   '   Exit Function
   'End If
   '@endcode
   '@sa CCard::vbGetPhysicalMedium
   '*/
   Public Property Get NdisMedium
      NdisMedium = m_nNdisMedium
   End Property

   '============================================================================================='
   '/**
   'This function creates an instance of COM Adapter object and stores it in the
   'm_Adapter member varaible.
   '@params !  object Instance of COM Adapter object obtained from NDInfo.AdapterList
   '@return The Adapter object created if successful, else returns Nothing
   '@code
   'If (Not oTestCard.vbCreateAdapter (oNDInfo.AdapterList (1))) Then
   '   oLog.Failed ("Failed to create Test Adapter object", 88888)
   '   Exit Function
   'End If
   '@endcode
   '*/
   Public Function vbCreateAdapter(oCOMAdapter)
      vbCreateAdapter = TRUE

      If (oCOMAdapter.AdapterType = 1) Then
         m_sAdapterType = "Test adapter"
      ElseIf (oCOMAdapter.AdapterType = 2) Then
         m_sAdapterType = "Support adapter"
      ElseIf (oCOMAdapter.AdapterType = 3) Then
         m_sAdapterType = "Message adapter"
      ElseIf (oCOMAdapter.AdapterType = 4) Then
         m_sAdapterType = "Virtual Wan adapter"
      Else
         m_sAdapterType = "Unknown adapter"
      End If

      m_nNdisMedium = CLng(oCOMAdapter.NdisMedium)

      Set m_oCOMAdapter = oNDTCore.CreateAdapter(oCOMAdapter)
      If (m_oCOMAdapter is Nothing) Then
         Call oLog.SafeFailed ("Failed to create " & m_sAdapterType & " object", 88888)
         vbCreateAdapter = FALSE
      End If
   End Function


   '================================================================================================='
   '/**
   'This function performs a CreateOpen on the adapter instance. The create open is required to
   'obtain an open instance from the adapter instance in NDTCore. It also creates a COpen
   '(vbscript) object and stores the open instance in it. This is the object that is returned
   '@return object   A COpen object
   '@code
   'Set oSuppOpen = oSuppCard.vbCreateOpen ()
   'If (oSuppOpen Is Nothing) Then
   '   Exit Function
   'End If
   '@endcode
   '*/
   Public Function vbCreateOpen()
      Dim l_oCOMOpen          ' the NDTCore::Open returned from above

      Set l_oCOMOpen = m_oCOMAdapter.CreateOpen()
      If l_oCOMOpen is Nothing Then
         Call oLog.SafeFailed("Failed to create open on " & m_sAdapterType, 88888)
         Set vbCreateOpen = Nothing
      Else
         Dim l_oOpen
         Set l_oOpen = New COpen
         Set l_oOpen.COMOpen = l_oCOMOpen
         l_oOpen.NdisMedium = m_nNdisMedium
         l_oOpen.AdapterType = m_sAdapterType
         Set vbCreateOpen = l_oOpen
      End If

   End Function

   '===============================================================================================//
   '/**
   'Use this API to send NDIS IO Control Codes to the Net Device. This an alternative
   'to using NdisRequest to query get OID's from the network device. This function uses
   'NdisIOControl(DeviceIOControl) to send the query to underlying hardware/driver.
   '@params
   '  !  number OID to query
   '  !  array Buffer to receive response in
   '  !  number The number of bytes written in the pvOutBuffer
   '  !  number The Win32 error code in case an error occurs
   '  !  constant QueryMode<br>
   '   QUERY_ALL_STATS      - returns responses for a number of predefined oid queries<br>
   '   QUERY_SELECTED_STATS - returns the response for this single NDIS private oid<br>
   '   QUERY_GLOBAL_STATS   - returns the response for this single oid<br>
   'Please note that QUERY_ALL_STATS does not return the results in the pData field but
   '@return   The success status of the method (True/False)
   '@sa CCard::vbNdisIOControlEx, CCard::vbFastNdisIOControl
   '@code
   '   GetWakePatternList = oTestCard.vbNdisIoControl (OID_PNP_WAKE_UP_PATTERN_LIST, mPatternList, BytesWritten, ErrorStatus, 2)
   '   If (Not GetWakePatternList Or ErrorStatus <> 0) Then
   '      call oLog.Failed("Unable to get OID_PNP_WAKE_UP_PATTERN_LIST for open instance",88888)
   '      Exit Function
   '   End If
   '@endcode
   '*/
   Public Function vbNdisIOControl(ByVal Oid, ByRef DataBuffer, ByRef BytesWritten, ByRef ErrorStatus, ByVal QueryMode)
      vbNdisIOControl = m_oCOMAdapter.NdisIOControl (Oid, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
      If (ErrorStatus <> 0) Then
         oLog.Write ("NdisIOControl returned error status " & (ErrorStatus))
      End If
   End Function

   '===============================================================================================//
   '/**
   'Use this API to send NDIS IO Control Codes to the Net Device. This an alternative
   'to using NdisRequest to query get OID's from the network device. This function uses
   'DeviceIOControl to send the query to underlying hardware/driver. This function should
   'only be used when we want explicit control over the size of buffer we want to let this
   'query use. Note that it does NOT take an allocated buffer in. The buffer is allocated
   'and returned to you. The size of the buffer allocated would be equal to the parameter
   'passed in. If you do not meet these strict requirements, use Card::vbNdisIOControl.
   '@params
   '  !  number OID to query
   '  !  number The buffer size to use when performing the query
   '  !  array Buffer to receive response in
   '  !  number The number of bytes written in the pvOutBuffer
   '  !  number The Win32 error code in case an error occurs
   '  !  constant QueryMode<br>
   '   QUERY_ALL_STATS      - returns responses for a number of predefined oid queries<br>
   '   QUERY_SELECTED_STATS - returns the response for this single NDIS private oid<br>
   '   QUERY_GLOBAL_STATS   - returns the response for this single oid<br>
   'Please note that QUERY_ALL_STATS does not return the results in the pData field but
   '@return   The success status of the method (True/False)
   '@sa CCard::vbNdisIOControl, CCard::vbFastNdisIOControl
   '@code
   '   GetWakePatternList = oTestCard.vbNdisIoControl (OID_PNP_WAKE_UP_PATTERN_LIST, 256, mPatternList, BytesWritten, ErrorStatus, 2)
   '   If (Not GetWakePatternList Or ErrorStatus <> 0) Then
   '      call oLog.Failed("Unable to get OID_PNP_WAKE_UP_PATTERN_LIST for open instance",88888)
   '      Exit Function
   '   End If
   '@endcode
   '*/
   Public Function vbNdisIOControlEx(ByVal Oid, ByVal ulBufferLen, ByRef DataBuffer, ByRef BytesWritten, ByRef ErrorStatus, ByVal QueryMode)
      vbNdisIOControlEx = m_oCOMAdapter.NdisIOControlEx (Oid, ulBufferLen, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
      If (ErrorStatus <> 0) Then
         oLog.Write ("NdisIOControlEx returned error status " & (ErrorStatus))
      End If
   End Function


   '================================================================================================='
   '/**
   'This is a wrapper to NdisIOControl. It can be used when we do not want extensive error information
   '@params
   '  !  number   The Oid to query
   '  !  array    The data buffer that would hold the information obtained from the query
   '  !  constant The query mode<br>
   '     QUERY_SELECTED_STATS - returns the response for this single NDIS private oid<br>
   '     QUERY_GLOBAL_STATS   - returns the response for this single oid<br>
   '@return The success status of the method (True/False)
   '@code
   '      bResult = oTestCard.vbFastNdisIOControl(OID_GEN_MAXIMUM_TOTAL_SIZE, nMaxTotalSize, QUERY_GLOBAL_STATS)
   '      If(NOT bResult) Then
   '         Call oLog.Failed ("Unable to query OID_GEN_MAXIMUM_TOTAL_SIZE", 88888)
   '      End If
   '@endcode
   '@sa CCard::vbNdisIOControl
   '*/
   Public Function vbFastNdisIOControl(ByVal Oid, ByRef DataBuffer, ByVal QueryMode)
      Dim BytesWritten, ErrorStatus
      vbFastNdisIOControl = Me.vbNdisIOControl (Oid, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
      If ((Not vbFastNdisIOControl) Or (ErrorStatus <> 0)) Then
         vbFastNdisIOControl = FALSE
      End If
   End Function

   '============================================================================================='
   '/**
   'QueryGuid uses WMI to query an oid in the driver.  Internally the OID is converted into
   'a WMI GUID.  The WMI query is made and ndis.sys converts the WMI query into a standard OID query.
   'The driver should see a standard OID query or nothing at all if ndis.sys responds to the OID itself.
   '@params
   '  !  number OID to query
   '  !  number buffer to receive response in
   '@return  The success status of the QueryGuid call (True/False)
   '*/
   Public Function vbQueryGuid (OidGuid, DataBuffer)
      vbQueryGuid = m_oCOMAdapter.QueryGuid (OidGuid, DataBuffer)
   End Function

   '============================================================================================='
   '/**
   'vbWmiRequest uses WMI to query/set a wmi guid in the driver. The WMI request is made and ndis.sys
   'converts the WMI request into a standard OID request. The driver should see a standard OID or
   'nothing at all if ndis.sys responds to the OID itself. This is an extension of CCard::vbQueryGuid,
   'giving the user more control over the buffers and guids he is querying.
   '@params
   '  !  string The guid to query
   '  !  number buffer to send/receive response in
   '  !  number buffer length
   '  !  number Either QUERY_SINGLE_INSTANCE or SET_SINGLE_INSTANCE
   '  !  number Returns the error status reported through wmi
   '  !  number If the error status is ERROR_INSUFFICIENT_BUFFER, then returns required
   '     buffer size
   '@return  The success status of the request call (True/False)
   '@sa  CCard::vbQueryGuid
   '*/
   Public Function vbWmiRequest (strGuid, DataBuffer, BufferLength, RequestType, ErrorStatus, nBytesNeeded)
      vbWmiRequest = m_oCOMAdapter.WmiRequest (strGuid, DataBuffer, BufferLength, RequestType, ErrorStatus, nBytesNeeded)
   End Function

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
            Call oLog.SafeFailed ("Invalid MaxPacketSize = " & nMaxPacketSize & " received from " & m_sAdapterType, 22857)
            vbGetMaxPacketSize = 50
         End If
      Else
         Call oLog.SafeFailed ("Unable to get maximum total size for " & m_sAdapterType, 22858)
         vbGetMaxPacketSize = 50
      End If
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

      ConnectStatus = 0
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

   '============================================================================================='
   '/**
   ' Wait for the MEDIA_CONNECT_STATUS to change to connected. After establishing connected
   ' wait for additional time to handle drivers that returned connected while not yet sure
   '@return  True if could establish link within specified seconds, else false
   '@code
   '   If (Not oTestCard.vbWaitForLinkWithDelay()) Then
   '       oLog.Write("Unable to establish link status")
   '   End If
   '*/
   Function vbWaitForLinkWithDelay(WaitTime, ExtraWaitDelay)

      ' Call actual wait for link function
      vbWaitForLinkWithDelay = vbWaitForLink(WaitTime)

      ' Special case, extra time
      If (vbWaitForLinkWithDelay) Then
        WScript.Sleep ExtraWaitDelay
      End If
   End Function

End Class




'<!-- CRC = 0x3e200978 --->
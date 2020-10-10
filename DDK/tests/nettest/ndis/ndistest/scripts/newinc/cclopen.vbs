Option Explicit

'================================================================================================='
'/**
'This class encapsulates the various operations that can be performed on a connections less
'NDTCore::Open. It uses functionality provided by the open object and also augments
'it with additional connection less device specific functions
'@sa        CCLCard, COpen
'@date      12/07/2002
'@author    Mitesh Desai
'@alias     miteshd
'*/
Class CCLOpen
   Dim m_oOpen
   Private Sub Class_Initialize
      Set m_oOpen = Nothing
   End Sub
   
   Private Sub Class_Terminate
      Set m_oOpen = Nothing
   End Sub
   
   '================================================================================================='
   '/**
   '@exclude
   'This property is used to simulate inheritance in vbscript. It allows us to create the 
   'COpen object from the CCard object and then make CCLOpen hold it.
   '@params
   ' !  class The COpen object created by CCard object
   '*/
   Public Property Set Open(p_oOpen)
      Set m_oOpen = p_oOpen
   End Property
   
   '================================================================================================='
   '/**
   '@sa COpen::COMOpen
   '*/
   Public Property Get COMOpen
      Set COMOpen = m_oOpen.COMOpen
   End Property
   
   '================================================================================================='
   '/**
   '@sa COpen::NdisMedium
   '*/
   Public Property Get NdisMedium
      NdisMedium = m_oOpen.NdisMedium 
   End Property
   
   '================================================================================================='
   '/**
   '@sa COpen::AdapterType
   '*/
   Public Property Get AdapterType
      AdapterType = m_oOpen.AdapterType
   End Property
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisRequest
   '*/
   Public Function vbNdisRequest(ByVal nOID, ByRef DataArray, ByVal DataLen, ByVal QueryType, ByRef BytesWritten, ByRef BytesNeeded, ByRef nNdisStatus, ByVal bResize)
      vbNdisRequest = m_oOpen.vbNdisRequest(nOID, DataArray, DataLen, QueryType, BytesWritten, BytesNeeded, nNdisStatus, bResize)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisRequest2
   '*/
   Public Function vbNdisRequest2(byval nOID, byref oObjStruct, byval nType, byref nNdisStatus)
      vbNdisRequest2 = m_oOpen.vbNdisRequest2(nOID, oObjStruct, nType, nNdisStatus)
   End Function
       
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisOpen
   '*/
   Public Function vbNdisOpen(bNdisMedium)
      vbNdisOpen = m_oOpen.vbNdisOpen(bNdisMedium)
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbNdisOpenUnbindCapable
   '*/
   Public Function vbNdisOpenUnbindCapable()
      vbNdisOpenUnbindCapable = m_oOpen.vbNdisOpenUnbindCapable()
   End Function
   
   
   '================================================================================================='
   '/**
   '@sa COpen::vbGetMaxPacketSize
   '*/
   Public Function vbGetMaxPacketSize
      vbGetMaxPacketSize = m_oOpen.vbGetMaxPacketSize
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

   '============================================================================================='
   '/**
   'This API Queries the OID_GEN_MAXIMUM_LOOKAHEAD oid on an open instance of the adapter,
   'and returns the result value by reference.
   '@params
   '  ! number Reference to the variable to store the max look ahead value in
   '@return Ndis status of the NdisRequest
   '@code
   'status = oTestOpen.vbGetMaxLookahead (lMaxLookahead)
   'If (status <> 0) Then 
   '   call oLog.Failed ("GetMaxLookahead failed with Ndis Status = " & status)
   'End If
   '@endcode
   '@sa CCLOpen::vbSetLookahead
   '*/        
   Public Function vbGetMaxLookahead(ByRef lMaxLookAhead)
      Dim BytesWritten, BytesNeeded
      Dim NdisStatus
      Dim bResult
      Dim templMaxLookahead
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      bResult = m_oOpen.vbNdisRequest(OID_GEN_MAXIMUM_LOOKAHEAD, _
            templMaxLookahead, 4, REQUEST_QUERY_INFO, _
            BytesWritten, BytesNeeded, NdisStatus, FALSE)
      
      If (Not bResult) Then
         vbGetMaxLookahead = &HC0000001&    ' failure
         Call oLog.SafeFailed ("NdisRequest failed during OID_GEN_MAXIMUM_LOOKAHEAD for " & m_oOpen.AdapterType, 22847)
      Else 
         If (NdisStatus <> 0) Then
            vbGetMaxLookahead = NdisStatus   ' failure
            Call oLog.SafeFailed ("NdisRequest for oid OID_GEN_MAXIMUM_LOOKAHEAD failed for "  & m_oOpen.AdapterType, 22848)
         Else
            vbGetMaxLookahead = 0            ' Success
            lMaxLookAhead = templMaxLookahead
         End If
      End If
      
   End Function

   '============================================================================================='
   '/**
   'This API sets the OID_GEN_CURRENT_LOOKAHEAD oid on an open instance of the adapter
   'to the specified value of lookahead
   '@params
   '  !  number The value to set the Lookahead to
   '@return Ndis status of the NdisRequest
   '@code
   'status = oTestOpen.vbSetLookahead (CLng (1))
   'If (status <> 0) Then 
   '   call oLog.Failed ("SetLookahead failed with Ndis Status = " & status)
   'End If
   '@endcode
   '@sa CCLOpen::vbGetMaxLookahead
   '*/        
   Function vbSetLookahead(ByVal Lookahead)
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim bResult
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      oLog.Write("Setting OID_GEN_CURRENT_LOOKAHEAD to " & Lookahead )
      
      bResult = m_oOpen.vbNdisRequest(OID_GEN_CURRENT_LOOKAHEAD, Lookahead, 4, _
            REQUEST_SET_INFO, BytesWritten, BytesNeeded, NdisStatus, FALSE)
      
      If (Not bResult) Then
         NdisStatus = &HC0000001&          'failure
         Call oLog.SafeFailed ("NdisRequest failed to set look ahead to 0x" & Hex(Lookahead) & " for " & m_oOpen.AdapterType, 22850)
      ElseIf (NdisStatus <> 0) Then
         Call oLog.SafeFailed ("NdisRequest for oid OID_GEN_CURRENT_LOOKAHEAD failed for " & m_oOpen.AdapterType, 22851)
      End If
      
      vbSetLookahead = NdisStatus
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbSetRemoteId
   '*/
   Public Sub vbSetRemoteId (lTestId)
      m_oOpen.vbSetRemoteId(lTestId)
   End Sub
   
   '================================================================================================='
   '/**
   '@sa COpen::vbSetLocalId
   '*/
   Public Sub vbSetLocalId (lTestId)
      m_oOpen.vbSetLocalId(lTestId)
   End Sub

   '================================================================================================='
   '/**
   '@sa COpen::vbSetChannelId
   '*/
   Public Sub vbSetChannelId (lTestId)
      m_oOpen.vbSetChannelId lTestId
   End Sub
    
   '================================================================================================='
   '/**
   '@sa COpen::vbSetReceiveOption
   '*/
   Public Sub vbSetReceiveOption (lReceiveOption)
      m_oOpen.vbSetReceiveOption(lReceiveOption)
   End Sub
   
   '================================================================================================='
   '/**
   '@sa COpen::vbStartReceive
   '*/
   Public Function vbStartReceive
      vbStartReceive = m_oOpen.vbStartReceive()
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbStopReceive
   '*/
   Public Function vbStopReceive
      vbStopReceive = m_oOpen.vbStopReceive()
   End Function
   
   '================================================================================================='
   '/**
   'This function invokes the vbGetReceiveResults function in COpen and logs an error if it was
   'no successful. Look at COpen::vbGetReceiveResults for complete information on this command
   '@sa COpen::vbGetReceiveResults
   '*/
   Public Function vbGetReceiveResults (ByRef nPacketsReceived, ByRef nPacketsResent)
      vbGetReceiveResults = m_oOpen.vbGetReceiveResults (nPacketsReceived, nPacketsResent)
      If Not vbGetReceiveResults Then
         call oLog.SafeFailed ("Failed to get receive results from " & m_oOpen.AdapterType, 88888)
      End If
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbVerifiedSendPackets
   '*/
   Public Function vbVerifiedSendPackets (arrDestAddr, nNumAddresses, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
      vbVerifiedSendPackets = m_oOpen.vbVerifiedSendPackets(arrDestAddr, nNumAddresses, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbVerifiedSend
   '*/
   Public Function vbVerifiedSend (DestAddr, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
      vbVerifiedSend = m_oOpen.vbVerifiedSend (DestAddr, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbVerifyReceiveResendRet
   '*/
   Public Function vbVerifyReceiveResendRet(lRecvExpected, lMinRecvRequired, lResendExpected, lMinResendRequired)
      vbVerifyReceiveResendRet = m_oOpen.vbVerifyReceiveResendRet(lRecvExpected, lMinRecvRequired, lResendExpected, lMinResendRequired)
   End Function

   '================================================================================================='
   '/**
   ' This function sends the given data array as a raw stream. This function is used when
   ' we want the packet to conform to a specific format (or we do not want any ndistest headers
   ' in the packet
   '@return TRUE or FALSE depending on the success of the operation
   '@sa  COpen::vbSend, COpen::vbSendPackets
   '*/
   Public Function vbSendRaw(ByVal DataArray)
      Dim oCOMOpen
      Set oCOMOpen = m_oOpen.COMOpen
      
      vbSendRaw = oCOMOpen.SendRaw(DataArray)
      If (Not vbSendRaw) Then
         Call oLog.SafeFailed ("Unable to send raw data on " & m_oOpen.AdapterType, 88888)
      End If
      Set oCOMOpen = Nothing
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisClose
   '*/
   Public Function vbNdisClose
      vbNdisClose = m_oOpen.vbNdisClose
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbClearEvents
   '*/
   Public Function vbClearEvents
      vbClearEvents = m_oOpen.vbClearEvents()
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbFastNdisRequest
   '*/
   Public Function vbFastNdisRequest(ByVal nOID, ByRef Result, ByRef ResultSize)
      vbFastNdisRequest = m_oOpen.vbFastNdisRequest(nOID, Result, ResultSize)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbPrintNdisRequest
   '*/
   Public Function vbPrintNdisRequest(ByVal nOID)
      vbPrintNdisRequest = m_oOpen.vbPrintNdisRequest(nOID)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisReset
   '*/
   Public Function vbNdisReset
      vbNdisReset = m_oOpen.vbNdisReset
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbGetEvents
   '*/
   Public Function vbGetEvents(ByRef nResets, ByRef nDisconnects, ByRef nConnects)
      vbGetEvents = m_oOpen.vbGetEvents (nResets, nDisconnects, nConnects)
   End Function
   
   
   '================================================================================================='
   '/**
   '@sa COpen::vbStartPerformance
   '*/
   Public Function vbStartPerformance(oRemoteCOMOpen, DestAddr, TestMode, PacketSize, PktsPerBurst, NumPackets, TestDuration, Delay, CancelPkts)
      vbStartPerformance = m_oOpen.vbStartPerformance (oRemoteCOMOpen, DestAddr, TestMode, PacketSize, PktsPerBurst, NumPackets, TestDuration, Delay, CancelPkts)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbWaitPerformance
   '*/
   Public Function vbWaitPerformance ()
      vbWaitPerformance = m_oOpen.vbWaitPerformance()
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbGetPerformanceResults
   '*/
   Public Function vbGetPerformanceResults (nDuration, nBytesSent, nBytesReceived)
      vbGetPerformanceResults = m_oOpen.vbGetPerformanceResults(nDuration, nBytesSent, nBytesReceived)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbStartWaitForEvent
   '*/
   Public Function vbStartWaitForEvent(lEvent)
      vbStartWaitForEvent = m_oOpen.vbStartWaitForEvent(lEvent)
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbEndWaitForEvent
   '*/
   Public Function vbEndWaitForEvent(lTimeOut)
      vbEndWaitForEvent = m_oOpen.vbEndWaitForEvent(lTimeOut)
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbStartStress
   '*/
   Public Function vbStartStress(oSvrOpen, lPacketSize, lOptionsMask, lIterations, lTestDuration)
      vbStartStress = m_oOpen.vbStartStress(oSvrOpen, lPacketSize, lOptionsMask, lIterations, lTestDuration)
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbWaitStress
   '*/
   Public Function vbWaitStress()
      vbWaitStress = m_oOpen.vbWaitStress()
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbGetStressResults
   '*/
   Public Function vbGetStressResults()
      vbGetStressResults = m_oOpen.vbGetStressResults()
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbSendPackets
   '*/
   Public Function vbSendPackets(arrDestAddr, lNumAddresses, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
      vbSendPackets = m_oOpen.vbSendPackets(arrDestAddr, lNumAddresses, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbSend
   '*/
   Public Function vbSend(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
      vbSend = m_oOpen.vbSend(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
   End Function   
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbStopSend
   '*/
   Public Function vbStopSend
      vbStopSend = m_oOpen.vbStopSend
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbWaitSend
   '*/
   Public Function vbWaitSend
      vbWaitSend = m_oOpen.vbWaitSend
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbGetSendResults
   '*/
   Public Function vbGetSendResults(ByRef lPacketsSent, ByVal lSendFailureType)
      vbGetSendResults = m_oOpen.vbGetSendResults(lPacketsSent, lSendFailureType)
   End Function
   
End Class


'<!-- CRC = 0x814a2e54 --->
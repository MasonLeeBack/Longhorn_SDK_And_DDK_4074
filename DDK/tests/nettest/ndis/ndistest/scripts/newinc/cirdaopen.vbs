Option Explicit

'================================================================================================='
'/**
'This class encapsulates the various operations that can be performed on an IRDA NDTCore::Open
'object. It uses functionality provided by the connection less open object and also augments
'it with additional IRDA specific functions
'@sa        CIrdaCard, CCLOpen
'@date      12/08/2001
'@author    Mitesh Desai
'@alias     miteshd
'*/
Class CIrdaOpen
   Dim m_oCLOpen
   Dim m_nLastBurstSize

   Private Sub Class_Initialize
      Set m_oCLOpen = Nothing
      m_nLastBurstSize = Null
   End Sub
   
   Private Sub Class_Terminate
      Set m_oCLOpen = Nothing
      m_nLastBurstSize = Null
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
   'This property is used by the vbSimpleSendReceive method. It is used to store the burst size 
   'that was computed by any previous call to vbSimpleSendReceive. Then, any following calls to
   'vbSimpleSendReceive need not query the for a compatible burst size. Setting this value to
   'Null would make the caller requery for the burst size
   '@params number   A compatible burst size that was computed
   '@sa  CIrdaOpen::vbSimpleSendReceive
   '*/
   Public Property Let LastBurstSize (p_nLastBurstSize)
      m_nLastBurstSize = p_nLastBurstSize
   End Property
   
   '================================================================================================='
   '/**
   'This property is requested by the vbSimpleSendReceive method and it returns the burst size that 
   'was stored earlier. A Null indicates that no legal value was stored and the caller needs to 
   'query the nics for an appropriate burst size.
   '@params number   A compatible burst size or Null if not was stored
   '@sa  CIrdaOpen::vbSimpleSendReceive
   '*/
   Public Property Get LastBurstSize
      LastBurstSize = m_nLastBurstSize
   End Property

   '================================================================================================='
   '/**
   '@sa COpen::vbNdisOpen, CLanCard::vbSetupBasicTest
   '*/
   Public Function vbNdisOpen
      vbNdisOpen = m_oCLOpen.vbNdisOpen(FALSE)
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
   '@sa   CCLOpen::vbGetMaxPacketSize
   '*/
   Public Function vbGetMaxPacketSize
      vbGetMaxPacketSize = m_oCLOpen.vbGetMaxPacketSize
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
   '@sa CCLOpen::vbSetLookahead
   '*/        
   Function vbSetLookahead(ByVal Lookahead)
      vbSetLookahead = m_oCLOpen.vbSetLookahead (Lookahead)
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
   Function vbSend(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
      vbSend = m_oCLOpen.vbSend(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
   End Function   
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbStopSend
   '*/
   Function vbStopSend
      vbStopSend = m_oCLOpen.vbStopSend
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbWaitSend
   '*/
   Function vbWaitSend
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
   '@sa COpen::vbSendRaw
   '*/
   Public Function vbSendRaw(ByVal DataArray)
      vbSendRaw = m_oCLOpen.vbSendRaw
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

   '============================================================================================='
   '/**
   'This API is used to check the values of packets received and resent. This is used for IRDA for which we require to use the
   'number of packets resent by the receiver to find the number of packets that the sender can expect to come back to him.
   '@param lRecvExpected  The number of packets that are expected to be received and returns the actual
   '                      number of packets received
   '@param lResentExpected The number of packets expected to be resent and returns the actual number resent
   '@param lMinRecvRequired The minimum number of packets that must be 
   '                                       received to avoid failure. 
   '@param lMinResentRequired The minimum number of packets that must be resent to avoid failure. Because
   '                                        of special IRDA priviledges, this parameter is not used.
   '@return true when both recv and resent are as expected else false
   '*/ 
   Public Function vbVerifyReceiveResendRet(ByRef lRecvExpected, ByVal lMinRecvRequired, ByRef lResendExpected, ByVal lMinResendRequired)
      Dim bResult
      Dim lReceived, lResent
      Dim lRetResent

      lRetResent = CLng(0)
      oLog.Write (m_oCLOpen.AdapterType & " should receive " & lRecvExpected & " and resend " & lResendExpected )
      bResult = Me.vbGetReceiveResults(lReceived, lResent)
      If (bResult) Then       'If test.Failed, bResult is FALSE

          If (lReceived <> lRecvExpected) Then
              If (lRecvExpected = 0) Then
                  Call oLog.SafeFailed ("Should not have received any packets", 88888) 
              Else
                  If (lReceived < lMinRecvRequired) Then
                      Call oLog.SafeFailed ("Received less than the required minimum of " & lMinRecvRequired , 88888)
                  Else
                      If (lRecvExpected = lMinRecvRequired) Then
                          Call oLog.SafeFailed("Did not receive expected number of packets" , 88888)
                      Else
                          oLog.SafeWarned("Received acceptable but less than expected number of packets")
                      End If
                  End If
              End If
              bResult = False             
          End If
          lRecvExpected = lReceived

          lRetResent = lResent
          ' First check if it resent expected number of packets
          If (lResent <> lResendExpected) Then
              ' Check if we are allowing it to resend any packets at all (ie lResendExpected != 0)
              If (lResendExpected = 0) Then
                  Call oLog.SafeFailed ("Should not have resent any packets", 88888)
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
                      Call oLog.SafeFailed("Did not resend expected number of packets" , 88888)
                  Else
                      oLog.SafeWarned("Resent acceptable but less than expected number of packets")
                      oLog.Write ("This could be because it received fewer packets.")
                  End If
                  
              End If
              bResult = False
          End If
                       
      End If
      lResendExpected = lRetResent
      vbVerifyReceiveResendRet = bResult
   End Function

   '================================================================================================='
   '/**
   'This function is the same as vbVerifyReceiveResendRet, it does not modify the passed variables
   '@sa COpen::vbVerifyReceiveResendRet
   '*/
   Public Function vbVerifyReceiveResend(ByVal lRecvExpected, ByVal lMinRecvRequired, ByVal lResendExpected, ByVal lMinResendRequired)
      vbVerifyReceiveResend = m_oCLOpen.vbVerifyReceiveResendRet(lRecvExpected, lMinRecvRequired, lResendExpected, lMinResendRequired)
   End Function


   '**********************************************************'
   '                                                          '
   '          Function related to IRDA             '
   '                                                          ' 
   '**********************************************************'
    
   '==========================================================================
   '/**
   'Sets the baud rate for the IRDA device instance
   '@params ! number The baud rate to be set
   '@return True on success, false otherwise
   '@code
   '   If (Not oTestOpen.vbSetBaudRate(9600))
   '       Call oLog.Failed ("Unable to set baud rate to 9600", 21243)
   '   End If
   '*/  
   Public Function vbSetBaudRate(lBaudRate)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      vbSetBaudRate = oCOMOpen.SetBaudRate(lBaudRate)
      Set oCOMOpen = Nothing
   End Function

   '==========================================================================
   '/**
   'Sets the baud rate for the IRDA device instance and then verifies that it was
   'set correctly. It uses OID_IRDA_LINK_SPEED to do this.
   '@params ! number   The baud rate to be set
   '@return True if able to set and verify the baud rate, false other wise
   '@code
   '   If (Not oTestOpen.vbSetVerifyBaudRate(9600))
   '       Exit Do
   '   End If
   '*/  
   Public Function vbSetVerifyBaudRate(lBaudRate)
      Dim lNewBaudRate
      Dim bResult
      Dim SizeOfLong

      vbSetVerifyBaudRate = True
      bResult = Me.vbSetBaudRate(lBaudRate)

      SizeOfLong = 4
      bResult = Me.vbFastNdisRequest(OID_IRDA_LINK_SPEED, lNewBaudRate, SizeOfLong)

      If (Not bResult) Then
         Call oLog.Failed ("Unable to query current link speed on " & m_oCLOpen.AdapterType , 88888)
         vbSetVerifyBaudRate = False            
      ElseIf (lNewBaudRate <> lBaudRate) Then
         oLog.Write ("Current baudrate = " & lNewBaudRate & " Expected baudrate = " & lBaudRate)
         Call oLog.SafeFailed ("Unable to set baudrate on " & m_oCLOpen.AdapterType , 88888)
         vbSetVerifyBaudRate = False            
      End If
   End Function
   '==========================================================================
   '/**
   'Gets the turnaround time of the NIC's infrared transceiver. It queries the 
   'oid OID_IRDA_TURNAROUND_TIME to get this value.
   '@params  ! number The turnaround time is returned in this variable
   '@return True on success, else false
   '@code
   '   
   '   If (oTestOpen.vbGetTurnAround(lTurnAround)) Then
   '       oSuppOpen.vbSetTurnAround(lTurnAround)
   '   End If
   '*/  
   Public Function vbGetTurnAround(ByRef lTurnAround)
      Dim ResultSize
      ResultSize = 4
      vbGetTurnAround = Me.vbFastNdisRequest(OID_IRDA_TURNAROUND_TIME, lTurnAround, ResultSize)
      If (Not vbGetTurnAround) Then
         oLog.Write ("Unable to read turnaround time from " & m_oCLOpen.AdapterType)
      End If
   End Function

   '==========================================================================
   '/**
   'Sets the turnaround time of the NIC's infrared transceiver.
   '@params ! number The turnaround time to set.
   '@code
   '   
   '   If (oTestOpen.vbGetTurnAround(lTurnAround)) Then
   '       oSuppOpen.vbSetTurnAround(lTurnAround)
   '   End If
   '*/  
   Public Sub vbSetTurnAround(lTurnAround)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      oCOMOpen.SetTurnAround(lTurnAround)
      Set oCOMOpen = Nothing
   End Sub

   '==========================================================================
   '/**
   'Get the number of extra Beginning of Frame (BOF) flags required by the NIC's 
   'transceiver to synchronize on a received packet. It queries the oid 
   'OID_IRDA_EXTRA_RCV_BOFS to get this value.
   '@params  ! number The extra BOF flags are returned in this variable
   '@return Nothing
   '@code
   '   
   '   If (oTestOpen.vbGetExtraBofs(ExtraBofs)) Then
   '       oSuppOpen.vbSetExtraBofs(ExtraBofs)
   '   End If
   '*/   
   Public Function vbGetExtraBofs(ByRef ExtraBofs)
      Dim ResultSize
      ResultSize = 4
      vbGetExtraBofs = Me.vbFastNdisRequest(OID_IRDA_EXTRA_RCV_BOFS, ExtraBofs, ResultSize)
      If (Not vbGetExtraBofs) Then
         oLog.Write ("Unable to read extra receive bofs from " & m_oCLOpen.AdapterType)
      End If

   End Function

   '==========================================================================
   '/**
   'Set the number of extra Beginning of Frame (BOF) flags required by the NIC's 
   'transceiver to synchronize on a packet. 
   '@params ! number    The Extra BOF flags to set
   '@return Nothing
   '@code
   '   
   '   If (oTestOpen.vbGetExtraBofs(ExtraBofs)) Then
   '       oSuppOpen.vbSetExtraBofs(ExtraBofs)
   '   End If
   '*/   
   Public Sub vbSetExtraBofs(lExtraBofs)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      oCOMOpen.SetExtraBofs(lExtraBofs)
      Set oCOMOpen = Nothing
   End Sub

   '================================================================================================='
   '/**
   ' Private function that obtains the maximum supported send window sizes (obtained using the 
   ' query to OID_IRDA_MAX_SEND_WINDOW_SIZE) of the sending and resending
   ' instances and choose the minimum of these two and the global variable glIrdaMaxBurstSize
   ' @params !  class  The other open that we will find a compatible size with
   ' @return   Thee appropriate burst size
   '*/
   Private Function vbCompatibleBurstSize(oRcvrOpen)
      Dim nClientSendWindowSize, nRemoteSendWindowSize, nBurstSize
      Dim SizeOfLong, bResult

      nClientSendWindowSize = CLng(0)
      nRemoteSendWindowSize = CLng(0)
      nBurstSize = CLng(0)
      '
      ' Client will do the sendpackets
      '
      SizeOfLong = 4
      bResult = Me.vbFastNdisRequest(OID_IRDA_MAX_SEND_WINDOW_SIZE, nClientSendWindowSize, SizeOfLong)
      If (Not bResult) Then
         oLog.Write ("OID_IRDA_MAX_SEND_WINDOW_SIZE not supported by " & m_oCLOpen.AdapterType & ", defaulting to BurstSize = 4" & vbLf)
         nBurstSize = glIrdaMaxBurstSize
      Else
         SizeOfLong = 4
         oLog.Write ("Sender's OID_IRDA_MAX_SEND_WINDOW_SIZE = " & nClientSendWindowSize & " pkts " & vbLf)
         bResult = oRcvrOpen.vbFastNdisRequest(OID_IRDA_MAX_SEND_WINDOW_SIZE, nRemoteSendWindowSize, SizeOfLong)
         If (Not bResult) Then
            oLog.Write ("OID_IRDA_MAX_SEND_WINDOW_SIZE not supported by " & oRcvrOpen.AdapterType & ", defaulting to BurstSize = 4" & vbLf)
            nBurstSize = glIrdaMaxBurstSize
         Else
            oLog.Write ("Receiver's OID_IRDA_MAX_SEND_WINDOW_SIZE = " & nRemoteSendWindowSize & " pkts " & vbLf)
            If (nRemoteSendWindowSize > nClientSendWindowSize) Then
               nBurstSize = nClientSendWindowSize
            Else
               nBurstSize = nRemoteSendWindowSize
            End If
         End If
      End If
      If (nBurstSize > glIrdaMaxBurstSize) Then
         nBurstSize = glIrdaMaxBurstSize
      End If
      
      vbCompatibleBurstSize = nBurstSize
   End Function
   
   '===============================================================================================//
   '/**
   'This API can be used to check if send and receive is working between two devices. 
   'The calling device is the sending instance and the passed device is the receiving instance. 
   'It setups the instances for sending/receiving/resending and then sends 
   'the data and checks if the send/receive/resend was successful. 
   'All functions called by this function would log failures and the caller may use 
   'appropriate masks to avoid any kind of failure logging.
   'This function uses NdisSendPackets to send.
   '@params 
   '  ! class  The receiving instance
   '@return	   0 if everything (send-receive/resend) worked<br>
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
      Dim nPacketSize
      Dim nTotalPackets

      Dim nResentPackets
      Dim nBurstSize
      
      Dim nReceiveDelay
      Dim arrSendAddr()

      Dim nRetval, bResult
      Dim TempValue
      Dim nMinimumPass
   
      Const NO_ERROR = 0
      Const SETUP_ERROR = 1
      Const SENDRECV_ERROR = 2
      
      nRetval = NO_ERROR

      '
      ' Compute the burst size to use
      '
      If (IsNull(m_nLastBurstSize) Or IsNull(oRcvrOpen.LastBurstSize)) Then
         ' obtain a burst size compatible between the sending and receiving instance
         nBurstSize = vbCompatibleBurstSize(oRcvrOpen)

         ' Store for future use
         m_nLastBurstSize = nBurstSize
         oRcvrOpen.LastBurstSize = nBurstSize
      ElseIf (m_nLastBurstSize <> oRcvrOpen.LastBurstSize) Then
         ' obtain a burst size compatible between the sending and receiving instance      
         nBurstSize = vbCompatibleBurstSize(oRcvrOpen)

         ' Store for future use
         m_nLastBurstSize = nBurstSize
         oRcvrOpen.LastBurstSize = nBurstSize         
      Else
         ' the burst size was stored by a previous call to SimpleSendReceive, and the
         ' same value was stored for the sender and the receiver. Use it
         nBurstSize = m_nLastBurstSize
      End If

      oLog.Write ("SendPackets will be attempted at BurstSize = " & nBurstSize & " packets" & vbLf)
      nReceiveDelay = Me.vbGetReceiveDelay()
      
      '
      'initialize the array of addresses/bursts
      '
      ReDim arrSendAddr(nBurstSize)
      Dim i   ' local counter
      For i = 0 To (nBurstSize - 1)
         arrSendAddr(i) = NetAddr(&H0&, &H0&, &H0&, &H0&, &H0&, &H0&)
      Next

      '
      ' Set the baud rates, turnaround time, extra BOFs for the test card and support card
      '

      bResult = Me.vbSetVerifyBaudRate(9600)
      If (Not bResult)Then
         nRetval = SETUP_ERROR
      End If

      bResult = oRcvrOpen.vbSetVerifyBaudRate(9600)
      If (Not bResult)Then
         nRetval = SETUP_ERROR
      End If

      bResult = Me.vbGetTurnAround(TempValue)
      If (bResult) Then
         oRcvrOpen.vbSetTurnAround (TempValue)
      End If
      
      bResult = Me.vbGetExtraBofs(TempValue)
      If (bResult) Then
         oRcvrOpen.vbSetExtraBofs (TempValue)
      End If

      bResult = oRcvrOpen.vbGetTurnAround(TempValue)
      If (bResult) Then
         Me.vbSetTurnAround (TempValue)
      End If
      bResult = oRcvrOpen.vbGetExtraBofs(TempValue)
      If (bResult) Then
         Me.vbSetExtraBofs (TempValue)
      End If

      nResentPackets = CLng(0)
      nPacketSize = CLng(68)


      Me.vbSetReceiveOption (RECEIVE_DEFAULT)
      oRcvrOpen.vbStartReceive()
      Me.vbStartReceive()
      
      nTotalPackets = glBurstsToSend * nBurstSize

      If (Me.vbVerifiedSendPackets(arrSendAddr, nBurstSize, nPacketSize, glBurstsToSend, 0, arrSendAddr(0)) < nTotalPackets) Then
         oLog.Write ("Unable to send packets successfully")
         nRetval = SENDRECV_ERROR
      End If
    
      WScript.Sleep nReceiveDelay

      '
      ' get receive results from "receiving" open instance
      '
      nMinimumPass = (glPercentToPassIrdaSlow * nTotalPackets) / 100
      nResentPackets = glBurstsToSend
      bResult = oRcvrOpen.vbStopReceive
      If (bResult) Then
         bResult = oRcvrOpen.vbVerifyReceiveResendRet(nTotalPackets, nMinimumPass, nResentPackets, glBurstsToSend)
         If (Not bResult) Then
            nRetval = SENDRECV_ERROR
         End If
      Else
         nRetval =SENDRECV_ERROR
      End If
      
      WScript.Sleep nReceiveDelay           ' wait for all packets to be received

      '
      ' get receive results from "sending" open instance
      '
      nMinimumPass = (glPercentToPassIrdaSlow * nResentPackets) / 100
      bResult = Me.vbStopReceive
      If (bResult) Then
         bResult = Me.vbVerifyReceiveResend(nResentPackets, nMinimumPass, 0, 0)
         If (Not bResult) Then
            nRetval = SENDRECV_ERROR
         End If
      Else
         nRetval = SENDRECV_ERROR
      End If

      vbSimpleSendReceive = nRetval
   End Function

End Class

'<!-- CRC = 0xad2b9716 --->
Option Explicit

'================================================================================================='
'/**
' * The COffloadOpen class. This is a derived class of CLanOpen. It provides
' * functionality related to offloading. It encompasses all the ipsec/checksum
' * and routines along with wrappers for the necessary lan function
' * @sa       CLanOpen, CLanCard, COffloadOpen
' * @date     12/19/2001
' * @author   Mitesh Desai
' * @alias    miteshd@microsoft.com
'*/
Class COffloadOpen
   Dim m_oLanOpen
   
   Private Sub Class_Initialize
      Set m_oLanOpen = Nothing
   End Sub
   
   Private Sub Class_Terminate
      Set m_oLanOpen = Nothing
   End Sub   

   
   '================================================================================================='
   '/**
   '@exclude
   'The set property that is used by a COffloadCard object to set the connectionless open
   'object that is required by this class. It is a hack used to obtain some kind of 
   'inheritance structure in VBScript.
   '@params
   '! class This is the CLanOpen object that was created in the Card hierarchy
   '*/
   Public Property Set LanOpen(p_oLanOpen)
      Set m_oLanOpen = p_oLanOpen
   End Property

   '================================================================================================='
   '/**
   '@sa COpen::COMOpen
   '*/
   Public Property Get COMOpen
      Set COMOpen = m_oLanOpen.COMOpen
   End Property
   
   '================================================================================================='
   '/**
   '@sa COpen::NdisMedium
   '*/   
   Public Property Get NdisMedium
      NdisMedium = m_oLanOpen.NdisMedium
   End Property

   '================================================================================================='
   '/**
   '@sa COpen::vbNdisOpen
   '*/   
   Public Function vbNdisOpen
      vbNdisOpen = m_oLanOpen.vbNdisOpen
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisRequest
   '*/
   Public Function vbNdisRequest(ByVal nOID, ByRef DataArray, ByVal DataLen, ByVal QueryType, ByRef BytesWritten, ByRef BytesNeeded, ByRef nNdisStatus, ByVal bResize)
      vbNdisRequest = m_oLanOpen.vbNdisRequest(nOID, DataArray, DataLen, QueryType, BytesWritten, BytesNeeded, nNdisStatus, bResize)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbGetEvents
   '*/
   Public Function vbGetEvents(ByRef nResets, ByRef nDisconnects, ByRef nConnects)
      vbGetEvents = m_oLanOpen.vbGetEvents (nResets, nDisconnects, nConnects)
   End Function
   
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisClose
   '*/
   Public Function vbNdisClose
      vbNdisClose = m_oLanOpen.vbNdisClose
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisClose
   '*/
   Public Function vbGetCardAddress
      vbGetCardAddress = m_oLanOpen.vbGetCardAddress
   End Function

   '================================================================================================='
   '/**
   '@sa CCLOpen::vbGetReceiveDelay
   '*/
   Public Function vbGetReceiveDelay
      vbGetReceiveDelay = m_oLanOpen.vbGetReceiveDelay
   End Function

   '================================================================================================='
   '/**
   '@sa   CCLOpen::vbGetMaxPacketSize
   '*/
   Public Function vbGetMaxPacketSize
      vbGetMaxPacketSize = m_oLanOpen.vbGetMaxPacketSize
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisReset
   '*/
   Public Function vbNdisReset()
      vbNdisReset = m_oLanOpen.vbNdisReset
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbSetRemoteId
   '*/
   Public Sub vbSetRemoteId (lTestId)
      m_oLanOpen.vbSetRemoteId lTestId
   End Sub
   
   '================================================================================================='
   '/**
   '@sa COpen::vbSetLocalId
   '*/
   Public Sub vbSetLocalId (lTestId)
      m_oLanOpen.vbSetLocalId lTestId
   End Sub
   
   '================================================================================================='
   '/**
   '@sa COpen::vbSetReceiveOption
   '*/
   Public Sub vbSetReceiveOption (lReceiveOption)
      m_oLanOpen.vbSetReceiveOption lReceiveOption
   End Sub
   
   '================================================================================================='
   '/**
   '@sa CLanOpen::vbSetPacketFilter
   '*/
   Public Function vbSetPacketFilter (ByVal lFilter)
      vbSetPacketFilter = m_oLanOpen.vbSetPacketFilter(lFilter)
   End Function
   
   '================================================================================================='
   '/**
   '@sa CLanOpen::vbGetMaxLookahead
   '*/
   Public Function vbGetMaxLookahead (ByRef lMaxLookahead)
      vbGetMaxLookahead = m_oLanOpen.vbGetMaxLookahead (lMaxLookahead)
   End Function
   
   '================================================================================================='
   '/**
   '@sa CLanOpen::vbSetLookahead
   '*/
   Public Function vbSetLookahead(ByVal Lookahead)
      vbSetLookahead = m_oLanOpen.vbSetLookahead (Lookahead)
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbWaitSend
   '*/
   Function vbWaitSend
      vbWaitSend = m_oLanOpen.vbWaitSend
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbGetSendResults
   '*/
   Public Function vbGetSendResults(ByRef lPacketsSent, ByVal lSendFailureType)
      vbGetSendResults = m_oLanOpen.vbGetSendResults(lPacketsSent, lSendFailureType)
   End Function
   
   
   '**********************************************************'
   '                                                          '
   '          Function related to IP send/receive             '
   '                                                          ' 
   '**********************************************************'

   '===============================================================================================//
   '/**
   'This command sets the default values on the Open Instance to set the 
   'Encapsulation Type and Size or Self-Checksum-Computation flag
   '@params 
   '  ! number Supplies encapsulation type and size or boolean flag
   '	  for Self-Checksum-Computation for this Open instance
   '@return Returns true if command succeeds, else false
   '@syntax bResult = oTestOpen.vbSetIPDefaults (CByte (0))
   '*/
   Public Function vbSetIPDefaults(vOffloadHdrORFlag)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen
   
      vbSetIPDefaults = oCOMOpen.SetIPDefaults(vOffloadHdrORFlag)

      Set oCOMOpen = Nothing
   End Function

   '===============================================================================================//
   '/**
   'Starts to capture any IP packets received on this Open
   '@return Returns true if capture mode starts succesfully. Else false
   '@sa COffloadOpen::vbGetIpCaptureResults
   '@code
   'bResult = oTestOpen.vbStartIpCapture()
   '@endcode
   '*/   
   Public Function vbStartIPCapture
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen
      vbStartIPCapture = True
      
      If (Not oCOMOpen.StartIPCapture()) Then
         call oLog.SafeFailed ("Could not start IP Capture on " & m_oLanOpen.AdapterType, 88888)
         vbStartIPCapture = False
      End If
      Set oCOMOpen = Nothing
   End Function

   '===============================================================================================//
   '/**
   'This command is used to send IP Packets from this open instance handle
   '@params
   '  ! array The destination address (MAC) for the IP Packet
   '  ! constant Version of IP (V4 or V6)
   '  ! constant Protocol Type (TCP, UDP etc)
   '  ! number Number of packets to send
   '  ! number Size of each packet being sent
   '  ! number Specified TCP Options And/Or IP Options
   '@return Return true on success else failure
   '@code
   'bResult = oTestOpen.vbSendIP(ServerAddress, V4, TCP, 50, 512, TCP_OPTIONS)
   '@endcode
   '*/   
   Public Function vbSendIP(DestAddr, IPVer, Protocol, lPacketCount, lPacketSize, cOptions)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen
      
      vbSendIP = oCOMOpen.SendIP(DestAddr, IPVer, Protocol, lPacketCount, lPacketSize, cOptions)

      Set oCOMOpen = Nothing
   End Function

   '===============================================================================================//
   '/**
   'This command collects the results obtained during the IP capture.  It stops the IP capture.
   '@params
   '  ! number Returns the number of Packets received on this open since
   '		the last SetIpCapture call
   '  ! number Returns the number of bytes received on this open since
   ' 		the last SetIpCapture call
   '  ! constant Type of checksum that passed if any (TCP_CKSUM or IP_CKSUM)
   '  ! constant Type of checksum that failed if any (TCP_CKSUM or IP_CKSUM)
   '@return Returns True of function success else failure
   '@sa COffloadOpen::vbSendIP,COffloadOpen::vbStartIpCapture
   '@code
   'bResult = oTestOpen.vbGetIPCaptureResults (lPacketsReceived, lBytesReceived, lCksumPassed, lCksumFailed)
   '@endcode
   '*/
   Public Function vbGetIPCaptureResults(ByRef lPacketCount, ByRef lTotalSize, ByRef lCksumPassed, ByRef lCksumFailed)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen

      vbGetIPCaptureResults = oCOMOpen.GetIPCaptureResults(lPacketCount, lTotalSize, lCksumPassed, lCksumFailed)

      Set oCOMOpen = Nothing
   End Function

   '===============================================================================================//
   '/**
   'This command is used to send IP Packets from this open instance handle
   '@params 
   '  ! array The destination address (MAC) for the IP Packet
   '  ! constant Version of IP (V4 or V6)
   '  ! constant Protocol Type (TCP, UDP etc)
   '  ! number Number of packets to send
   '  ! number Size of each packet being sent
   '  ! number Specified TCP Options And/Or IP Options
   '@return Return true on success else failure
   '@code
   'bResult = oTestOpen.vbVerifiedSendIP(ServerAddress, V4, TCP, 50, 512, TCP_OPTIONS)
   '@endcode
   '*/
   Public Function vbVerifiedSendIP(DestAddr, IPVer, Protocol, lPacketCount, lPacketSize, cOptions)
      ' Send to the Dest Adapter
      Dim l_nPacketsSent
      vbVerifiedSendIP = False
      
      If (Me.vbSendIP(DestAddr, IPVer, Protocol, lPacketCount, lPacketSize, cOptions)) Then
         If (m_oLanOpen.vbWaitSend()) Then
            If (m_oLanOpen.vbGetSendResults(l_nPacketsSent, SEND_FAILURES_FORBIDDEN)) Then
               if (l_nPacketsSent <> lPacketCount) Then
                  Call oLog.SafeFailed (m_oLanOpen.AdapterType & "should have sent " & lPacketCount & " packets.", 88888)
               Else
                  vbVerifiedSendIP = True        ' Everything went well
               End If
            Else
               Call oLog.SafeFailed ("GetSendResults failed on " & m_oLanOpen.AdapterType, 88888)
            End If
         Else
            Call oLog.SafeFailed ("WaitSend failed on " & m_oLanOpen.AdapterType, 88888)
         End If
      Else
         Call oLog.SafeFailed ("Send IP on Open failed on " & m_oLanOpen.AdapterType, 88888)
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
   Function vbGetTaskOffloadInfo()
      
      vbGetTaskOffloadInfo = FALSE
      
      Dim bResult, OffloadInfoName
      Dim TaskOffloadSupport, TaskOffloadSupportName
      Dim OffloadInfo
      Dim Idx, Count, NdisStatus, BytesWritten, BytesNeeded 
      Dim OffloadInfoTemp(100)
      Dim l_nMedium
      
      l_nMedium = m_oLanOpen.NdisMedium
      
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
           
            bResult = m_oLanOpen.vbNdisRequest(OID_TCP_TASK_OFFLOAD, OffloadInfoTemp, 400, _
                  REQUEST_QUERY_INFO, BytesWritten, BytesNeeded, _
                  NdisStatus, FALSE)
            If(Not bResult) Then
               Call oLog.Write("Unable to get Task Offload support information" )
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
            If (l_nMedium = NDISMEDIUM802_3) Then
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
      
      vbGetTaskOffloadInfo = TRUE
      
   End Function
      
   
   '===============================================================================================//
   '/**
   'This API is used to offload a task onto an offload capable NIC. The Offload Header
   'info has to be passed in separately as well. The function can take upto two tasks to
   'offload (example: offload both largesend and checksum tasks and test).
   '@params
   '  ! variant Information about Offload Header! Can be array or
   '		a long depending on how much header info is needed
   '  ! variant a task to offload (Null indicates it is absent)
   '  ! variant another task to offload (Null indicates it is absent)
   '@return True on success, else false
   '@code
   'bResult = TestOpenObj.vbSetOffloadTask(0, Null, Null)
   '@endcode
   '*/
   Public Function vbSetOffloadTask(alOffloadHdrInfo, oTask1, oTask2)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen

      If (IsNull(oTask2)) Then
         If (IsNull (oTask1)) Then
            vbSetOffloadTask = oCOMOpen.SetOffLoadTask(alOffloadHdrInfo)
         Else
            vbSetOffloadTask = oCOMOpen.SetOffLoadTask(alOffloadHdrInfo, oTask1)      
         End If            
      Else
         vbSetOffloadTask = oCOMOpen.SetOffLoadTask(alOffloadHdrInfo, oTask1, oTask2)
      End If

      Set oCOMOpen = Nothing
   End Function
   
   '===============================================================================================//
   '/**
   'This command is used to set offload per-packet info for packets sent through this open
   '@params
   '  ! constant Defines the offload task for this packet. Example 
   '		CKSUM_OFFLOAD_TX or MSS_RX
   '  ! constant Provides details for the selected offload task. Example
   '		V4_CKSUM or the MSS size
   '@return     Returns success or failure in this variable
   '@code
   'lMss = 5120
   'bResult = OpenOne.vbSetOffloadPktInfo (MSS_TX, lMss)
   '@endcode
   '*/
   Public Function vbSetOffloadPktInfo(lOffloadBitMask, lCksumInfoORMss)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen
      
      vbSetOffloadPktInfo = oCOMOpen.SetOffloadPktInfo(lOffloadBitMask, lCksumInfoORMss)

      Set oCOMOpen = Nothing      
   End Function
   
   '===============================================================================================//
   '/**
   'This function retrieves the Task Offload Per Packet Information for packets 
   'received on this Open instance
   '@params
   '  ! constant Defines the offload task for this packet.
   '		Example CKSUM_OFFLOAD_TX or MSS_RX
   '  ! number Will return the number of packets received
   '		that passed checksum for checksum offload or
   '		bytes received for Largesend offload
   '  ! number Will return the number of packets received
   '		that failed checksum for checksum offload or
   '		packets received for Largesend offload
   '@return	   Returns success or failure in this variable
   '@code
   'bResult = oTestOpen.vbGetOffloadPktInfo (MSS_RX, lBytesToExpect, lPacketsToExpect)
   '@endcode
   '*/
   Public Function vbGetOffloadPktInfo(lOffloadBitMask, ByRef lCksumPassedORBytesToExpect, ByRef lCksumFailedORPacketsToExpect)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen
      
      vbGetOffloadPktInfo = oCOMOpen.GetOffloadPktInfo(lOffloadBitMask, lCksumPassedORBytesToExpect, lCksumFailedORPacketsToExpect)

      Set oCOMOpen = Nothing
   End Function
   
   
   '**********************************************************'
   '                                                          '
   '          Function related to IPSec                       '
   '                                                          ' 
   '**********************************************************'
   '===============================================================================================//
   '/**
   'This command adds a Security Association onto an IPSec Offload capable NIC
   '@params
   '  ! object The IPSec SA to offload onto the NIC
   '  ! object Returns a handle to the SA in this variable
   '@return Returns true if function succeeds, else false
   '@sa COffloadOpen::vbDeleteSA
   '@code
   'bResult = oTestOpen.vbAddSA (IPSecSA, hSAObj)
   '@endcode
   '*/
   Public Function vbAddSA(IPSecSA, hHandle)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen

      vbAddSA = oCOMOpen.AddSA(IPSecSA, hHandle)

      Set oCOMOpen = Nothing
   End Function

   '===============================================================================================//
   '/**
   'This command deletes a Security Association from an IPSec Offload capable NIC
   '@params
   '  !  object Handle to the IPSecSA to delete
   '@return Returns true if function succeeds, else false
   '@sa COffloadOpen::vbAddSA
   '@code
   'bResult = oTestOpen.vbDeleteSA (hSAObj)
   '@endcode
   '*/
   Public Function vbDeleteSA(hHandle)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen

      vbDeleteSA = oCOMOpen.DeleteSA(hHandle)

      Set oCOMOpen = Nothing
   End Function


   '===============================================================================================//
   '/**
   'This command sets up a bidirectional IPSec connection b/w two IPSec capable NICs.
   '@params
   '  ! object Handle to the IP Sec Connection established
   '  ! array Array of SA's (can be tunnel or transport SA's)
   '  ! variant Optional! Array of Tunnel SA's or Num of Tunnel SA's (Null when optional)
   '  ! variant Optional! Number of Tunnel SA's (Null when optional)
   '@return Returns true if function succeeds else false
   '@sa COffloadOpen::vbIpSecClose
   '@code
   ' In this example, TransportSAs and TunnelsSAs are 
   ' arrays of size two (on SA each for inbound and 
   ' outbound traffic over a connection)

   ' Example of Transport SA connection
   'bResult = oTestOpen.vbIpSecOpen(hLocal, TransportSAs, Null, Null)
   '         OR
   ' Example of Transport SA connection
   'bResult = oTestOpen.vbIpSecOpen(hLocal, TunnelSAs, 2, Null)
   '         OR
   'Example of both Tranport and Tunnel SA connection
   'bResult = oTestOpen.vbIpSecOpen(hLocal, TransportSAs, TunnelsSAs, 2)
   '@endcode
   '*/   
   Public Function vbIpSecOpen(Handle, SAArray, SAArrayOrNumOfTunnelSAs, NumOfTunnelSAs)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen

      If (IsNull(NumOfTunnelSAs)) Then
         If (IsNull (SAArrayOrNumOfTunnelSAs)) Then
            vbIpSecOpen = oCOMOpen.IpSecOpen(Handle, SAArray)
         Else
            vbIpSecOpen = oCOMOpen.IpSecOpen(Handle, SAArray, SAArrayOrNumOfTunnelSAs)
         End If
      Else
         vbIpSecOpen = oCOMOpen.IpSecOpen(Handle, SAArray, SAArrayOrNumOfTunnelSAs, NumOfTunnelSAs)
      End If

      Set oCOMOpen = Nothing
   End Function
   
   '===============================================================================================//
   '/**
   'Use this command to close an IP Sec connection that was established using COpen::IPSecOpen
   '@params !  object Handle to the IP Sec Connection to close
   '@return Return true on success or false on failure to caller
   '@sa COffloadOpen::vbIpSecOpen
   '@code
   'bResult = oTestOpen.vbIpSecClose (hIpSecConnection)
   '@endcode
   '*/   
   Public Function vbIpSecClose (Handle)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen

      vbIpSecClose = oCOMOpen.IpSecClose (Handle)

      Set oCOMOpen = Nothing
   End Function
   
   '===============================================================================================//
   '/**
   'Starts to capture any IP Sec packets received on this Open
   '@params  ! object Handle to the Open IP Sec Connection (or Null when optional)
   '@return Returns true if succesful else return false
   '@code
   'bResult = oTestOpen.vbStartIpSecCapture(Null)
   '@endcode
   '*/
   Public Function vbStartIPSecCapture (Handle)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen

      If (IsNull(Handle)) Then
         vbStartIPSecCapture = oCOMOpen.StartIPSecCapture ()
      Else
         vbStartIPSecCapture = oCOMOpen.StartIPSecCapture (Handle)
      End If

      Set oCOMOpen = Nothing
   End Function
   
   '===============================================================================================//
   '/**
   'This API is used to send IP Sec traffic out from the Open. There are multiple places
   'for this API to fail in and any error that occurs is handled as a safe error. It also
   'checked the send results to make sure that everything is okay
   '@params 
   '  ! array Associated MAC address of the Open to send to
   '  ! object Handle to the senders IP Sec connection (obtained from IpSecOpen)
   '  ! constant Version of IP (V4 or V6)
   '  ! constant Protocol Type (TCP, UDP etc)
   '  ! number Number of packets to send
   '  ! number Size of each packet being sent
   '  ! number Specified TCP Options And/Or IP Options
   '@return Return true on success of function else failure
   '@sa COpen::vbSendIP
   '@code
   'bResult = oTestOpen.vbVerifiedSendIPSec (DestAddress, hLocalIPSecConn, V4, UDP, 50, 512, IP_OPTION_ROUTERALERT)
   '@endcode
   '*/
   Public Function vbVerifiedSendIPSec(DestAddr, Handle, nVersion, nType, lPacketCount, lPacketSize, lOptions)
      Dim lPacketsSent
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen

      vbVerifiedSendIPSec = False

      If (oCOMOpen.SendIPSec(DestAddr, Handle, nVersion, nType, lPacketCount, lPacketSize, lOptions)) Then
         If (m_oLanOpen.vbWaitSend()) Then
            If (m_oLanOpen.vbGetSendResults(lPacketsSent, SEND_FAILURES_FORBIDDEN)) Then
               If (lPacketsSent <> lPacketCount) Then

               Else
                  vbVerifiedSendIPSec = True   ' Everything went well
               End If
            Else
               Call oLog.SafeFailed ("GetSendResults failed on " & m_oLanOpen.AdapterType, 22844)
            End If
         Else
            Call oLog.SafeFailed ("WaitSend failed on " & m_oLanOpen.AdapterType, 22845)
         End If
      Else
         Call oLog.SafeFailed ("Send IP Sec on Open failed on " & m_oLanOpen.AdapterType, 22846)
      End If

      Set oCOMOpen = Nothing
   End Function

   '===============================================================================================//
   '/**
   'This command collects the results obtained during the IP sec capture.  It stops the IP capture.
   '@params
   '  ! array The statistics collected during the IPSec capture
   '  ! object Either Null or the handle to be used
   '@return Returns True of function success else failure
   '@sa COffloadOpen::vbStartIPSecCapture
   '*/   
   Public Function vbGetIPSecCaptureResults(ByRef IpSecStats, Handle)
      Dim oCOMOpen
      Set oCOMOpen = m_oLanOpen.COMOpen

      If (IsNull (Handle)) Then
         vbGetIpSecCaptureResults = oCOMOpen.GetIPSecCaptureResults(IpSecStats)
      Else
         vbGetIpSecCaptureResults = oCOMOpen.GetIPSecCaptureResults(IpSecStats, Handle)      
      End If      

      Set oCOMOpen = Nothing
   End Function
   
End Class

'<!-- CRC = 0xe3bcdae9 --->
'
' Library for TCP scripts
'

Const DefaultTcpWindowSize                              =  17520
Const DefaultTcpMaxHalfOpen                             =  500
Const DefaultTcpMaxHalfOpenRetried                      =  400
Const DefaultTcpDelAckTicks                             =  2
Const DefaultTcpAckFrequency                            =  2
Const DefaultTcpTimedWaitDelay                          =  120
Const DefaultMSS                                        =  536
Const DefaultTcpZeroProbeRetries                        =  5
Const DefaultKeepAliveInterval                          =  1000
Const DefaultTcpMaxDataRetransmissions                  =  5
Const DefaultTcpMaxConnectRetransmissions               =  2
Const DefaultTcpMaxConnectResponseRetransmissions       =  2
Const DefaultTcpInitialRTT                              =  3000
Const DefaultTTL                                        =  128

const WSAEADDRINUSE                 =  10048
const MAX_PORT_RETRIES              =  10
const AsyncDelay                    =  1500

Const TimeWaitISNDifference         =  128000
Const TCPPARAMPATH                  =  "SYSTEM\CurrentControlSet\Services\Tcpip\Parameters"

Dim g_Common_UnusedArgs  ' unused arguments have not yet been consumed by any function

' g_fTestOffload : command line parameter to test tcpip offload engine NICs
' g_fTOENic : does NIc support TCP/IP Offload Engine
Dim g_fTestOffload, g_fTOENic, g_fCheckOffloadConnection
Dim g_fTOESupportIPv4, g_fTOESupportIPv6, g_fTOESupportSack

'/**
' Function to check the offload status of a TCP connection
'
' !!! This function is called from ActiveConnect and PassiveConnect functions
' !!! If a script uses other functions to establish a connection, this function needs to be called to check offload status
'
' @params
' !fVerion6  TRUE/FALSE depending on whether it's v6/v4
' !usSrcPort  Source port (SPARTA side)
' !usDestPort  Dest port (Stack side)
' !szSrcAddress  Source address (SPARTA side)
' !szDestAddress  Destination address (Stack side)
' !ulSessionId  Session id
' @return true/false if connection is offloaded / not
'*/
Function IsConnectionOffloaded(usSrcPort, usDestPort, ulSessionId)

    Dim OffloadStatus, ulStatus

    IsConnectionOffloaded = False

    ' g_fTestOffload : command line parameter to test tcpip offload engine NICs
    ' g_fTOENic : does NIc support TCP/IP Offload Engine

    If g_fTestOffload And g_fTOENic Then
        '
        ' Make sure to give enough time for the connection to get offloaded
        '
        ' Is 3 secs enough ?
        '
        Core.Sleep 3000
        
        '
        ' Call autosrv to check connection status
        '
        ulStatus = pControllerObj.GetOffloadStatus (false, usSrcPort, usDestPort, g_szLocalSpoofIp, g_szRemoteIpAddress, ulSessionId, OffloadStatus)
        if ulStatus <> 0 then
            Core.FailSev1Variation "IsConnectionOffloaded : Failed to check offload status of the connection"
        else
            if OffloadStatus = 2 then
                IsConnectionOffloaded = True
            end if
        end if
    End If

End Function


'
' Routine to reset a connection
'
Function ResetConnection(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   Dim pTCPPacket, ulTID, ulStatus

   '
   ' Check connection before it is uploaded
   '
   if g_fCheckOffloadConnection then
       If not IsConnectionOffloaded(usSrcPort, usDestPort, ulSessionId) and g_fTestOffload And g_fTOENic Then
          Core.FailSev1Variation "ResetConnection : Failed to offload the connection"
          ResetConnection = 1
          Exit Function
       End If
   end if

   Set pTCPPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_RST, 0)
   IFace.Send(pTCPPacket)
   ulStatus = pControllerObj.Reset(ulSessionId, ulTID)

   ResetConnection = ulStatus
End Function



Function RecvTCPPacket(ByRef pulSeqNumber, ByRef pulAckNumber, ByRef ulBytesRcvd, bTCPFlag, ulTimeout)
   Dim pTCPPacket, pReceiveTimer

   Set pReceiveTimer = Sparta.CreateReceiveTimer(ulTimeout)
   While (TRUE)
      Set pTCPPacket = IFace.ReceiveTimed(pReceiveTimer)
      If (pTCPPacket is Nothing) Then
          Set RecvTCPPacket = Nothing
          Exit Function
      Elseif ((pTCPPacket.TcpHeader.Flag AND bTCPFlag) = bTCPFlag) Then
          '
          ' update the seq and ack numbers
          '
          ulBytesRcvd = pTCPPacket.IpHeader.DatagramLength - (pTCPPacket.IpHeader.Length)*4 - (pTCPPacket.TcpHeader.HdrLength)*4
          '
          ' Treat SYN and FIN as 1 byte packets
          '
          if ((pTCPPacket.TcpHeader.Flag AND TCP_FIN) = TCP_FIN) Then
             ulBytesRcvd = ulBytesRcvd + 1
          elseif ((pTCPPacket.TcpHeader.Flag AND TCP_SYN) = TCP_SYN) Then
             ulBytesRcvd = ulBytesRcvd + 1
          end if
          pulSeqNumber = pTCPPacket.TcpHeader.AckNumber
          pulAckNumber = pTCPPacket.TcpHeader.SeqNumber + ulBytesRcvd

          '
          ' return the packet
          '
          Set RecvTCPPacket = pTCPPacket
          Exit Function
      End If
      Set pTCPPacket = Nothing
   Wend

End function


Function MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, bTCPFlag, usTCPDataLength)
   Dim pPacket
   Dim pSrcMacAddressObject, pg_szRemoteMacAddressObject


   '
   ' Create a TCP packet
   '
   Set pPacket = Sparta.TcpPacket(MediaType)


   '
   ' Set the MAC Header
   '
   Set pSrcMacAddressObject = Sparta.MacAddress(MediaType, g_szLocalMacAddress)
   pPacket.MacHeader.SourceAddress = pSrcMacAddressObject
   Set pRemoteMacAddressObject = Sparta.MacAddress(MediaType, g_szRemoteMacAddress)
   pPacket.MacHeader.DestAddress = pRemoteMacAddressObject
   pPacket.MacHeader.ProtocolType = PROTOCOL_TYPE_IP4

   '
   ' Set the IP Header
   '
   pPacket.IpHeader.Version = 4
   pPacket.IpHeader.TOS = 0
   pPacket.IpHeader.ID = 1
   pPacket.IpHeader.Flag = 0
   pPacket.IpHeader.FragmentOffset = 0
   pPacket.IpHeader.TTL = 10
   pPacket.IpHeader.ProtocolType = PROTOCOL_TYPE_TCP
   pPacket.IpHeader.SourceAddress = g_szLocalSpoofIp
   pPacket.IpHeader.DestAddress = g_szRemoteIpAddress

   '
   ' Set the UDP Header
   '
   pPacket.TcpHeader.SrcPort = usSrcPort
   pPacket.TcpHeader.DestPort = usDestPort
   pPacket.TcpHeader.SeqNumber = ulSeqNumber
   pPacket.TcpHeader.AckNumber = ulAckNumber
   pPacket.TcpHeader.Flag = bTCPFlag


   '
   ' Set the data portion
   '
   pPacket.UserData usTCPDataLength, "Test Data"


   Set pSrcMacAddressObject = Nothing
   Set pg_szRemoteMacAddressObject = Nothing
   Set MakeTCPPacket = pPacket

End Function



'
' Function to set a registry key under Tcpip\Parameters and then reboot the system and wait for
' it to be back up
' Parameters :
'     KeyName  - The name of the key to be set
'     Value    - The value to be assigned to the key
' Return:
'     0/Error-code
'
Function SetRegistryKeyAndReboot(KeyName, Value, Wait)
   Dim Status
   '
   ' Ask AutoSrv to set the registry key
   '
   Status = pControllerObj.SetRegistryValue(HKEY_LOCAL_MACHINE, TCPPARAMPATH, KeyName, Value)
   If (Status <> 0) Then
       Core.Log "Failed to set the registry key value " & Status
       SetRegistryKeyAndReboot = Status
       Exit Function
   End If

   '
   ' Ask AutoSrv to reboot
   '
   Status = pControllerObj.Reboot
   If (Status <> 0) Then
       Core.Log "Failed to reboot " & Status
       SetRegistryKeyAndReboot = Status
       Exit Function
   End If

   '
   ' Wait for the machine to be back up
   '
   if (Wait = TRUE) then
      Status = 1
      While (Status <> 0)
          Core.Sleep(30000)
          Status = pControllerObj.Ping
      Wend
   end if

   SetRegistryKeyAndReboot = 0
End Function


'
' Function to reboot the box and wait/not for it to come back up
'
Function Reboot(fWait)
   Dim ulStatus

   '
   ' Ask AutoSrv to reboot
   '
   ulStatus = pControllerObj.Reboot
   If (ulStatus <> 0) Then
       Core.Log "Reboot: Reboot - " & ulStatus
       Reboot = ulStatus
       Exit Function
   End If

   '
   ' Wait for the machine to be back up
   '
   if (fWait = TRUE) then
      ulStatus = 1
      While (ulStatus <> 0)
          Core.Sleep(5000)
          ulStatus = pControllerObj.Ping
      Wend
   end if

   Reboot = 0
End Function


'
' Function to initiate a TCP connection
'
Function Connect(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId, usWindowSize, usMSS)
   Dim ulStatus, ulBytesRcvd, ulTID, pPacket, ulCounter, fSuccess, pSYNPacket

   fSuccess = FALSE
   For ulCounter = 1 to MAX_PORT_RETRIES
      '
      ' Issue a CreateAndConnect
      '
      ulStatus = pControllerObj.CreateAndConnect(SOCK_STREAM, g_szRemoteIpAddress, usDestPort, g_szLocalSpoofIp, usSrcPort, ulTID, ulSessionId)
      if (ulStatus <> 0) then
         Core.log "Connect: CreateAndConnect - " & ulStatus
      else
         '
         ' Grab the SYN
         '
         Set pPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_SYN, 6000)
         if (pPacket is Nothing) then
            Core.log "Connect: Failed to receive a SYN"
            ulStatus = pControllerObj.Reset(ulSessionId, ulTID)
            Core.Sleep 1000
         else
            fSuccess = TRUE
            exit for
         end if
      end if

      '
      ' Retry with a different port
      '
      usDestPort = Core.Random(10000, 20000)
      Core.log "Connect: Retrying with a different port - " & usDestPort
   Next
   if Not(fSuccess) then
      Connect = 1
      exit function
   end if

   '
   ' Send a SYN-ACK
   '
   Set pSYNPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_SYN or TCP_ACK, 0)
   if Not(IsNull(usWindowSize)) then
      pSYNPacket.TCPHeader.WindowSize = usWindowSize
   end if
   if Not(IsNull(usMSS)) then
      pSYNPacket.TCPHeader.TCPOption(0).AddMSS usMSS
   end if


   For ulCounter = 1 to 3
      IFace.Send(pSYNPacket)

      '
      ' Receive the ACK
      '
      Set pPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_ACK, 5000)
      if Not(pPacket is Nothing) then
         exit for
      end if
      Core.log "Rexmitting SYN-ACK #" & ulCounter
   Next
   if (pPacket is Nothing) then
      Core.log "Connect: Failed to receive an ACK"
      Connect = 1
      exit function
   end if

   '
   ' Check if connection is offloaded
   '
   If Not IsConnectionOffloaded(usSrcPort, usDestPort, ulSessionId) and g_fTestOffload And g_fTOENic Then
      Core.Log "Connect : Failed to offload the connection"
      Connect = 3
      Exit function
   End If

   Connect = 0

End Function


'
' Function to initiate a TCP connection
'
Function ConnectTo(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId, usWindowSize, usMSS, fActive)
   Dim ulStatus, ulBytesRcvd, ulTID, pPacket, ulCounter, fSuccess, pSYNPacket, pACKPacket

   if (fActive) then
      ConnectTo = Connect(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId, usWindowSize, usMSS)
   else
      fSuccess = FALSE
      set pSYNPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_SYN, 0)
      if Not(IsNull(usWindowSize)) then
         pSYNPacket.TCPHeader.WindowSize = usWindowSize
      end if
      if Not(IsNull(usMSS)) then
         pSYNPacket.TCPHeader.TCPOption(0).AddMSS usMSS
      end if

      set pACKPacket = GrabSynAck(pSYNPacket, usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
      if (pACKPacket is nothing) then
         ConnectTo = 2
         exit function
      end if

      set pACKPacket = MakeTCPPacket(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, TCP_ACK, 0)
      if Not(IsNull(usWindowSize)) then
         pSYNPacket.TCPHeader.WindowSize = usWindowSize
      end if
      IFace.Send(pAckPacket)
       '
       ' Check if connection is offloaded
       '
       If Not IsConnectionOffloaded(usSrcPort, usDestPort, ulSessionId) and g_fTestOffload And g_fTOENic Then
          Core.Log "ConnectTo : Failed to offload the connection"
          ConnectTo = 3
          Exit function
       End If
   end if

   ConnectTo = 0

End Function


'
' Function to issue a Connect/ConnectEx and grab the first SYN
'
Function GrabSyn(usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId, fConnectEx, ulDataSize)
   Dim ulStatus, ulTID, pTCPPacket, ulBytesRcvd, ulCounter

   For ulCounter = 1 to MAX_PORT_RETRIES
      '
      ' Obtain a random port
      '
      usDestPort = Core.Random(10000, 20000)
      Core.log "GrabSyn: Trying a random port - " & usDestPort

      '
      ' Issue a CreateAndBind
      '
      ulStatus = pControllerObj.CreateAndBind(SOCK_STREAM, g_szRemoteIpAddress, usDestPort, ulSessionId)
      if (ulStatus <> 0) then
         Core.log "GrabSyn: CreateAndBind - " & ulStatus
      else
         '
         ' Issue a Connect/ConnectEx
         '
         if (fConnectEx) then
            ulStatus = pControllerObj.ConnectEx(ulSessionId, g_szLocalSpoofIp, usSrcPort, ulDataSize, ulTID)
         else
            ulStatus = pControllerObj.Connect(ulSessionId, g_szLocalSpoofIp, usSrcPort, ulTID)
         end if
         if (ulStatus <> 0) then
            Core.log "GrabSyn: ConnectEx - " & ulStatus
            ulStatus = pControllerObj.Close(ulSessionId, ulTID)
            Core.Sleep 1000
         else
            '
            ' Grab the SYN
            '
            Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, TCP_SYN, 6000)
            if (pTCPPacket is Nothing) then
               Core.log "GrabSyn: Failed to receive a SYN"
               ulStatus = pControllerObj.Close(ulSessionId, ulTID)
               Core.Sleep 1000
            else
               Set GrabSyn = pTCPPacket
               exit function
            end if
         end if
      end if
   Next

   Set GrabSyn = Nothing

End Function

'
' Function to get a connection in SYN_RCVD and then to SYN_SENT state
'
Function GrabSynAck(pSYNPacket, usSrcPort, usDestPort, ulSeqNumber, ulAckNumber, ulSessionId)
   Dim ulCounter, ulCounter1, pTCPPacket, ulTID, ulStatus, ulBytesRcvd

   For ulCounter = 1 to MAX_PORT_RETRIES
      '
      ' Retry with a different port
      '
      usDestPort = Core.Random(10000, 20000)
      Core.log "GrabSynAck: Trying a random port - " & usDestPort

      '
      ' Issue a CreateAndAccept
      '
      ulStatus = pControllerObj.CreateAndAccept(SOCK_STREAM, g_szRemoteIpAddress, usDestPort, 5, ulTID, ulSessionId)
      if (ulStatus <> 0) then
         Core.log "GrabSynAck: CreateAndAccept - " & ulStatus
      else
         '
         ' Create a SYN with the appropriate WS factor
         '
         For ulCounter1 = 1 to 3
            pSYNPacket.TCPHeader.DestPort=usDestPort
            IFace.Send(pSYNPacket)
            Set pTCPPacket = RecvTCPPacket(ulSeqNumber, ulAckNumber, ulBytesRcvd, (TCP_SYN or TCP_ACK), 2000)
            if Not(pTCPPacket is Nothing) then
               exit for
            end if
         Next
         if (pTCPPacket is Nothing) then
            Core.log "GrabSynAck: CreateAndAccept - " & ulStatus
            ulStatus = pControllerObj.Reset(ulSessionId, ulTID)
            Core.Sleep 1000
         else
            Set GrabSynAck = pTCPPacket
            exit function
         end if
      end if
   Next

   Set GrabSynAck = Nothing

End Function


'
' Return true if the remote computer has SynAttackProtect enabled
'
Function IsSynAttackProtectOn()
   Dim ulStatus, ulValue
   ulStatus = pControllerObj.GetRegistryValue(HKEY_LOCAL_MACHINE, TcpParamPath, "SynAttackProtect", ulValue)
   if ((ulStatus = 0) and (ulValue <> 0)) then
      IsSynAttackProtectOn = true
   else
      IsSynAttackProtectOn = false
   end if
End Function

'/**
' Function to parse the command line arguments passed to the script
' @params
' !FlagArray  Array of command line flags
' !ValueType  Type of value
' !ValueArray  On return will contain the values succeeding those flags
' @example
'     Consider TestScript.wsf which makes a call to this function
'        <ul>ParseArguments (Array("-v6", "-d"), Array(vbBoolean, vbLong), ValueArray)</ul>
'     If the script is called as follows,
'        <ul>TestScript.wsf -v6 -d 1000</ul>
'     then, ValueArray would be (true, 1000)
' @return nothing
'*/
function ParseArguments (FlagArray, ValueType, ValueArray)
    dim ulLastFlagIndex, ulCounter, ulArgIndex, szUnused, fMatch, arg

    ' Go thru the command line arguments
    '
    ulLastFlagIndex = null
    for ulArgIndex = 0 to WScript.Arguments.Count - 1
        arg = WScript.Arguments(ulArgIndex)

        ' Are we looking for the next value or the next flag
        '
        if (not IsNull (ulLastFlagIndex)) then
            select case (ValueType(ulLastFlagIndex))
            case vbBoolean
                Shout "ParseArguments: Should not require a second value for boolean options"
                Shout "ParseArguments: FlagArray(" & ulLastFlagIndex & ") = " & FlagArray(ulLastFlagIndex)
            case vbLong, vbInteger
                ValueArray(ulLastFlagIndex) = CLng(arg)
            case else
                ValueArray(ulLastFlagIndex) = arg
            end select
            ulLastFlagIndex = null
        else
            '
            ' See if the user has specified this flag
            '
            fMatch = false
            for ulCounter = lBound (FlagArray) to uBound (FlagArray)
                if (StrComp (FlagArray(ulCounter), arg, 1) = 0) then
                    if (ValueType(ulCounter) = vbBoolean) then
                        ValueArray(ulCounter) = true
                    else
                        ulLastFlagIndex = ulCounter
                    end if
                    fMatch = true
                    ' early exit because we matched the option
                    exit for
                end if
            next
            if (not fMatch) then szUnused = szUnused & arg & " "
         end if
    next

    g_Common_UnusedArgs = Split (szUnused)

end function

'/**
' Function to get offload parameters
' @params
' !g_fTOENic : does NIc support TCP/IP Offload Engine
' !g_fTestOffload : command line parameter to test tcpip offload engine NICs
' @return nothing
'*/
Function GetOffloadParameters(ByRef g_fTOENic, ByRef g_fTestOffload)

    Dim ValueArray, ulAdapterIndex, szRemoteIpAddress, ulStatus
    ValueArray = Array(False)
    ParseArguments Array("-offload"), Array(vbBoolean), ValueArray
    
    g_fTOENic = False
    g_fTOESupportIPv4 = False
    g_fTOESupportIPv6 = False
    '
    ' Check arguments to determine if the offload engine will be tested
    '
    g_fTestOffload = ValueArray(0)

    szRemoteIpAddress = g_szRemoteIpAddress
    ulStatus = pControllerObj.GetIndexByIp(szRemoteIpAddress, ulAdapterIndex)

    if ulStatus <> 0 then 
        Shout "GetOffloadParameters: GetInterfaceIndex returned error - " & ulStatus
        Exit function
    end if
         
    '
    ' Determine if NIC supports TCP/IP Offload Engine
    '
    ulStatus = pControllerObj.GetOffloadSupport(ulAdapterIndex, g_fTOESupportIPv4, g_fTOESupportIPv6, g_fTOESupportSack)
    if ulStatus <> 0 then 
        Shout "GetOffloadParameters: GetOffloadSupport returned error - " & ulStatus
        Exit function
    end if

    g_fTOENic = g_fTOESupportIPv4 or g_fTOESupportIPv6
    g_fCheckOffloadConnection = true

End Function

'
' Routine to do the initializations, execute the script and then do the clean up
' Parameters :
'     szLogName      - Name of the log file (without the .log extension)
'     szDisplayTitle - The title to be used in the display pop up
'
Sub StartScript(szLogName, szLogDirectory, szDisplayTitle)
   Dim pMacAddressObj, pPattern, Netmon, fStop


   '===============================================================================
   ' Create the different objects
   '===============================================================================

   set Core = CreateObject("Testcore.base.1")
   Core.SetLogDirectory szLogDirectory
   Core.OpenLog szLogName, TLS_REFRESH
   Core.LogLevel = (Core.LogLevel) - TLS_COMMANDS

   set Sparta = CreateObject("Spartacom.base.1")
   Sparta.InitLogging Core
   Sparta.SetExceptionCallback GetRef("ErrorHandler")

   Dim ValueArray
   ValueArray = Array(false)
   ParseArguments Array("-nocap"), Array(vbBoolean), ValueArray

   fStop = FALSE
   if not ValueArray(0) then
       set Netmon = CreateObject("Netmoncom.base.1")
       if (Netmon is Nothing) then
          Core.log "Failed to create Netmon object"
       else
          Netmon.InitLogging Core

          '
          ' specify the capture interface & capture file name
          '
          ulStatus = Netmon.InitNetmon(g_szLocalMacAddress, szLogDirectory & "\" & szLogName & ".cap")
          if (ulStatus <> 0) then
             Core.log "Failed to initialize Netmon - " & ulStatus
          else
             '
             ' Start the capture
             '
             fStop = TRUE
             ulStatus = Netmon.StartCapture
             if (ulStatus <> 0) then
                Core.log "Failed to start netmon capture - " & ulStatus
             end if
          end if
       end if
   end if

   set IFace = Sparta.DriverInterface(g_szLocalMacAddress)
   if (IFace is Nothing) then
       Core.log "Unable to start driver interface"
       Exit Sub
   end if
   MediaType=IFace.MediaType

   Core.OpenDisplay FALSE
   Core.SetDisplayTitle szDisplayTitle

   '
   ' If AutoSrv required
   '
   set AutoSrv = CreateObject("AutoSrvcom.base.1")
   AutoSrv.InitLogging Core
   Set pControllerObj = AutoSrv.InitController(g_szControllerIp, g_usControllerPort, g_szAutoSrvIp, g_usAutoSrvPort)


   '
   ' If Auto ARPing required
   '
   Set AutoArpObject = Sparta.AutoArp(g_szLocalMacAddress, g_szLocalMacAddress, g_szLocalSpoofIp)




   '===============================================================================
   '           Set the patterns for filtering
   '===============================================================================

   IFace.EnableDirectedReceiveMode
   IFace.EnableBroadcastReceiveMode
   IFace.EnablePatternFiltering

   '
   ' Filter for source MAC address
   '
   Set pMacAddressObj = Sparta.MacAddress(MediaType, g_szRemoteMacAddress)
   Set pPattern = Sparta.CreateMacSrcAddressPattern(MediaType, pMacAddressObj)
   IFace.AddPatternFilter pPattern

   '
   ' Filter for dest MAC address
   '
   Set pMacAddressObj = Sparta.MacAddress(MediaType, g_szLocalMacAddress)
   Set pPattern = Sparta.CreateMacDestAddressPattern(MediaType, pMacAddressObj)
   IFace.AddPatternFilter pPattern

   '
   ' Filter for protocol type
   '
   Set pPattern = Sparta.CreateMacProtocolTypePattern(MediaType, PROTOCOL_TYPE_IP4)
   IFace.AddPatternFilter pPattern

   '
   ' Filter for source IP address
   '
   Set pPattern = Sparta.CreateIpSrcAddressPattern(MediaType, g_szRemoteIpAddress)
   IFace.AddPatternFilter pPattern

   '
   ' Filter for dest IP address
   '
   Set pPattern = Sparta.CreateIpDestAddressPattern(MediaType, g_szLocalSpoofIp)
   IFace.AddPatternFilter pPattern

    '
    ' Get the parameters for offload testing
    '
    'GetOffloadParameters g_fTOENic, g_fTestOffload
    g_fTOENic = FALSE
    g_fTestOffload = FALSE

    if g_fTestOffload and not g_fTOENic then
        Core.Log "Nic does not support TCP/IP Offload Engine"
        Exit Sub
    end if

   '===============================================================================
   ' Execute the script
   '===============================================================================
   Main

   '
   ' Stop the capture
   '
   if (fStop) then
      ulStatus = Netmon.StopCapture
      if (ulStatus <> 0) then
         Core.log "Failed to stop netmon capture - " & ulStatus
      end if
   end if


   '===============================================================================
   ' Clean up
   '===============================================================================
   IFace.DisablePatternFiltering
   set pControllerObj = Nothing
   Set AutoArpObject = Nothing
   Core.CloseDisplay
   Core.CloseLog

End Sub



'
' Function to handle exceptions
'
Function ErrorHandler (ulStatus, szFuncName, szMessage)

   if (ulStatus <> ERROR_TIMEOUT) then
      Core.Log "Status = " & ulStatus & vbLf & "Function = " & szFuncName & vbLf _
                         &  "Message = " & szMessage
   else
      Core.Log "Hit the exception"
   end if

   ErrorHandler = TRUE

End Function

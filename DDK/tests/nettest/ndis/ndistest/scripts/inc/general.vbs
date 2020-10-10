'==========================================================================
' NAME:     general.vbs
'
' AUTHOR:   David Harding , Microsoft Corp.
' DATE  :   4/13/2001
'
' COMMENT:  This script contains two function that all scripts should call
'           to get basic setup and terminate service. Any initialization 
'           or termination you would like all scripts to perform should be 
'           put in these two functions. This includes all class creation
'           and deletion.
'==========================================================================
Option Explicit

Function Initialize()
    Set oLog = new CLog
    '
    ' Storing global log pointer for backward
    ' compatability with older scripts
    Set oNDTLog = oLog.LogPtr
    
    oLog.Mask = LOG_FAILURE Or LOG_WARNING
    
    '
    ' This will dump current test information to the head of each log
    ' This should be the last function call in our current scope.
    DumpTestConfiguration2()
    
    '
    ' This will construct or obtain the global instance of ProtocolBinder
    ' Object for this card and bind/unbind any protocols requested
    oSuppCore.LogPtr = oLog.LogPtr ' oLog (davhar) We need to try to move away from using this global
    If (Not SetProtocolBindings ()) Then
        Call oLog.SafeWarned ("Failed to initialize or setup protocol bindings")
    End If

    '
    ' Do initializations of globals etc that require NDTSession to be present
    '
    InitializeSessionDependents()

End Function

Sub InitializeSessionDependents()
   Dim bUseIPHeaders

   'Adjust glMinimumPacketSize depending on whether we are using IP packets or not
   bUseIPHeaders = oNDTSession("UseIPPackets")
   If (not(IsEmpty (bUseIPHeaders))) Then
       If (bUseIPHeaders = 1) Then
           ' Include IP headers in packetsize
           glMinimumPacketSize = 96
       Else
           glMinimumPacketSize = 64
       End If
   Else
       glMinimumPacketSize = 64
   End If
End Sub   

Function Terminate()
    ' Save the current mask
    Dim nLogMask
    nLogMask = oLog.Mask    ' Save the mask
    oLog.Mask = LOG_FAILURE Or LOG_WARNING
    ' All action in this block gets logged automatically
    If(Not RestoreProtocolBindings) Then
        oLog.SafeWarned ("Could not restore protocl bindings that may have been changed")
    End If
    'Restore Mask 
    oLog.Mask = nLogMask
    
    '
    ' We must tell the logging class that we have completed or
    ' else the script will be tagged with a failure because
    ' we assume the process has been terminated.
    ' This will same failure will be flagged when the user
    ' stops the scripts from the UI
    '
    oLog.LoggingComplete = True
    Set oLog = Nothing
End Function          

Function GetTestIndex()
    GetTestIndex = 1
End Function

Function SetProtocolBindings ()
    Dim ProtocolBinders, oTestProtocolBinder
    Dim TestAdapter,lMedium
    
    Set TestAdapter = oNDInfo.AdapterList(GetTestIndex())
    lMedium = CLng(TestAdapter.NdisMedium)
    if (lMedium = 5) Then ' If modem, dont do anything
        SetProtocolBindings = TRUE
        Exit Function
    End If
    
    oLog.Variation ("Binding/Unbinding Protocols")
    SetProtocolBindings = False    ' Assume failure
    
    ' Get Protocol binder object from Session
    ProtocolBinders = oNDTSession ("ProtocolBinders")
    
    if (IsEmpty (ProtocolBinders)) Then
        ' This means this is the first script trying to change bindings!
        ' The Binder objects do not exist in the NDTSession so create them
        
        ' Create the Protocol Binder object for Test Adapter
        ' Use NDTSession to create the component because NDTSession will NOT
        ' go out of scoping (hence deallocating the object) when this script is done
        Set oTestProtocolBinder = oNDTSession.CreateObject ("CProtocolBinder.WSC")
        If (oTestProtocolBinder Is Nothing) Then
            oLog.SafeWarned ("Error creating object using NDTSession")
            Exit Function
        End if
        
        ReDim ProtocolBinders (0)
        Set ProtocolBinders(0) = oTestProtocolBinder
        Set oTestProtocolBinder.m_oLogRef = oLog      
        If (Not oTestProtocolBinder.Initialize (oNDInfo.AdapterList (GetTestIndex()), oNDInfo.ProtocolList)) Then 
            Exit Function
        End If
        
        Dim nSuppIndex, nIndex
        nSuppIndex = 1
        For nIndex = 2 To (oNDInfo.AdapterList.Count - 1)
           Do
            Dim oSupportProtocolBinder, thisAdapter
            Set thisAdapter = oNDInfo.AdapterList(nIndex)
            
            ' Check if it is a Support Adapter
            If thisAdapter.AdapterType = 2 Then
            
               ' Initialize the server only if it is on a remote machine
               If (thisAdapter.ConnectionID <> 0) Then
                   If (Not oSuppCore.InitializeServer (thisAdapter.ConnectionID)) then
                       oLog.Write ("Could not initialize server for support adapter")
                       Exit Do
                   End If
               End If
               
               ' Create the Protocol Binder object for Support Adapter
               Set oSupportProtocolBinder = oNDTSession.CreateObject ("CProtocolBinder.WSC")
               If (oSupportProtocolBinder Is Nothing) then
                   oLog.Write ("Error creating object using NDTSession")
                   Exit Do
               End if
               
               Set oSupportProtocolBinder.m_oLogRef = oLog
               If (Not oSupportProtocolBinder.Initialize (thisAdapter, oNDInfo.ProtocolList)) Then
                   Exit Do
               End If
               
               ReDim Preserve ProtocolBinders (nSuppIndex)
               Set ProtocolBinders (nSuppIndex) = oSupportProtocolBinder
               nSuppIndex = nSuppIndex + 1
            End If
          Loop While (False)
        Next      
    Else
        ' Put in TEMPORARILY to bind/unbind protocols only the first and last script
        Dim bLastScript
        bLastScript = oNDTSession.Variable ("LastScript")
        if (bLastScript = False) Then
            oLog.Write ("Not changing bindings for this script")
            SetProtocolBindings = True
            Exit Function
        End If
    End If
    
    ' refresh log pointer! Important cos every successive script creates its OWN
    ' oLog object and object in session has reference to previous script's oLog obj
    Dim thisProtocolBinder
    For Each thisProtocolBinder in ProtocolBinders
        Set thisProtocolBinder.m_oLogRef = oLog
        Set thisProtocolBinder.m_oBindCtrl = oSuppCore.CreateBindCtrl (thisProtocolBinder.m_nConnectionID)
        If (thisProtocolBinder.m_oBindCtrl Is Nothing) Then
            oLog.SafeWarned ("Could not create Bind Control Object")
            Exit Function
        End If
        
        Call thisProtocolBinder.GetSupportedProtocols
        
        If (Not thisProtocolBinder.SetUserSpecifiedBindings()) Then 
            Exit Function
        End If
    Next
    
    ' Place the Protocol Binder array in the session (as it may have changed)
    oNDTSession ("ProtocolBinders") = ProtocolBinders
    SetProtocolBindings = True    ' Report a success if got here
End Function


Function RestoreProtocolBindings
    Dim bLastScript
    Dim ProtocolBinders, thisProtocolBinder
    Dim TestAdapter,lMedium
    
    Set TestAdapter = oNDInfo.AdapterList(GetTestIndex())
    lMedium = CLng(TestAdapter.NdisMedium)
    if (lMedium = 5) Then ' If modem, dont do anything
        RestoreProtocolBindings = TRUE
        Exit Function
    End If
    
    RestoreProtocolBindings = False    ' Assume failure
    bLastScript = oNDTSession.Variable ("LastScript")
    
    ' If this is the last script, restore all bindings   
    If (bLastScript) Then
        oLog.Variation ("Restoring any changed bind status of Protocols")
        ProtocolBinders = oNDTSession ("ProtocolBinders")
        If (IsEmpty (ProtocolBinders)) Then
            oLog.SafeWarned ("No state information about protocol binding found in Session")
            Exit Function
        End If
        
        For Each thisProtocolBinder in ProtocolBinders
            If (IsEmpty (thisProtocolBinder)) then
                oLog.SafeWarned ("Protocol Binding object for adapter not found! Should have been created")
                Exit Function
            End If
            
            ' Do the actual restore
            If (not thisProtocolBinder.RestoreBindings()) Then
                Exit Function
            End If
            
            ' Uninitialize the remote server/s
            If (thisProtocolBinder.m_nConnectionID <> 0) Then
                If (Not oSuppCore.UninitializeServer (thisProtocolBinder.m_nConnectionID)) Then
                    Call oLog.SafeWarned ("Failed to uninitialize server")
                End If
            End If
            
            ' Kill the Protocol Binder object
            Call thisProtocolBinder.Terminate
            
            ' Lose the reference to object created so it is released
            oNDTSession.DestroyObject (thisProtocolBinder)
            
        Next
        
        ' Remove the Protocol binding object from the session!
        ' This test may be running in a loop and session is persistant across loop runs
        If (Not oNDTSession.Remove ("ProtocolBinders")) Then
            call oLog.SafeWarned ("Could not remove protocol binder object from the session!" & vblf &_
            "This could cause problems if test is running in a loop")
            Exit Function
        End If
        
    End If
    
    RestoreProtocolBindings = True
End Function

Function DumpTestConfiguration2()
    'Create my own adapter list pointer
    Dim pAdptrLst
    Dim Adptr
    Dim DriverName,DriverBus,DriverPhysicalMedium,DriverMedium, DriverComponentId
    Dim TimeStamp
    Dim Version
    Dim Size
    Dim Checked
    Dim Index
    Dim OrigOutputControl
    Dim Guid
    Dim InfoVal
    Dim oTCard
    Dim lMedium
    Dim WhqlMode
    
    OrigOutputControl = oNDInfo.ScriptOutputControl
    oNDInfo.ScriptOutputControl = OrigOutputControl + DEBUGWRITE
    
    Set pAdptrLst = oNDInfo.AdapterList
    
    oLog.Write("*****************************************************************")
    oLog.Write("Date/Time:  " & Date & "  " & Time)
    oLog.Write("Script:     " & WScript.ScriptFullName)
    oLog.Write("NDIS Test:  " & oNdtSession("NdtVersion"))
    oLog.Write(oNdtSession("SystemType"))
    oLog.Write(oNdtSession("SystemOSVer"))
    oLog.Write(oNdtSession("BIOSDate"))
    oLog.Write(oNdtSession("BIOSName"))
    oLog.Write(oNdtSession("CPUType"))
    oLog.Write(oNdtSession("CPUNum"))
    oLog.Write("Loop Count: " & oNdtSession("LoopCount"))
    oLog.Write("Driver Verifier Selection: " & oNdtSession("DriverVerifier"))
    WhqlMode = oNDTSession ("WHQL_TESTS")
    If (WhqlMode <> "") Then
       If (WhqlMode = 0) Then
          oLog.Write("WHQL Test Mode: No")
       Else
          oLog.Write("WHQL Test Mode: Yes")
       End If
    Else
       oLog.Write("WHQL Test Mode: Unable to determine")
    End If
    
    DriverName = "ndis.sys"
    oNDTSupp.DriverInfo DriverName,Size,TimeStamp,Version,Checked
    if (Checked = 0) Then
        Checked = " Free"
    Else
        Checked = " Checked"
    End If
    oLog.Write("ndis.sys:   " & Size & " " & TimeStamp & "  " & Version & Checked)	
    Call PrintVerifierSetting(DriverName)
    
    Index = 1
    For Each Adptr In pAdptrLst
        if (Adptr.AdapterType = ADAPTERTYPE_TEST) Then
            oLog.Write(vblf & "Test Device")
        ElseIf (Adptr.AdapterType = ADAPTERTYPE_SUPPORT) Then
            oLog.Write(vblf & "Support Device")
        ElseIf (Adptr.AdapterType = ADAPTERTYPE_MESSAGE) Then
            oLog.Write(vblf & "Message Device")
        ElseIf (Adptr.AdapterType = ADAPTERTYPE_WANVIRTUAL) Then
            oLog.Write(vblf & "Virtual Wan Device")
        End If
        
        oLog.Write(Adptr.MachineName & ": " & Adptr.Description)
        
        lMedium = CLng(Adptr.NdisMedium)
        If (Adptr.AdapterType = ADAPTERTYPE_TEST OR Adptr.AdapterType = ADAPTERTYPE_SUPPORT) Then
            
            'if (Adptr.ConnectionId = 0 AND (lMedium = NDISMEDIUM802_3 OR lMedium = NDISMEDIUM802_5 OR lMedium = NDISMEDIUM802_FDDI OR lMedium = NDISMEDIUMWAN OR lMedium=NDISMEDIUMCOWAN OR lMedium = NDISMEDIUMATM)) Then
            if (Adptr.ConnectionId = 0 AND (lMedium = 0 OR lMedium = 1 OR lMedium = 2 OR lMedium = 3 OR lMedium = 8 OR lMedium = 10 OR lMedium = 12 OR lMedium = 13)) Then
                DriverName = oNdtSession(Index & "DriverName")
                if (DriverName <> "") Then
                    oNDTSupp.DriverInfo DriverName,Size,TimeStamp,Version,Checked
                    if (Checked = 0) Then
                        Checked = " Free"
                    Else
                        Checked = " Checked"
                    End If
                    oLog.Write(DriverName)
                    oLog.Write(Size & " " & TimeStamp & "  " & Version & Checked)

                    Call PrintVerifierSetting(DriverName)                    
                End If
                
                oLog.Write(oNdtSession(Index & "DriverMedium") & " " & oNdtSession(Index & "DriverPhysicalMedium") & " " & oNdtSession(Index & "DriverBus"))
                
                Guid = oNdtSession(Index & "DriverGUID")
                If (Guid <> "") Then
                    oLog.Write(Guid)
                End If

                DriverComponentId = oNdtSession(Index & "DriverComponentId")
                If (DriverComponentId <> "") Then
                    oLog.Write(DriverComponentId)
                End If
                
                ' Check to see if this is the first time or not
                InfoVal = oNDTSession(Index & "OID_GEN_MINIPORT_INFO")
                
                if (IsEmpty (InfoVal)) Then
                    
                    oNDInfo.ScriptOutputControl = 0
                    Set oTCard = oNDTCore.CreateAdapter(Adptr)
                    If(oTCard is Nothing) Then
                        call oLog.Failed ("Failed to create adapter object in DumpTestConfiguration2!" , 22751)
                    Else
                        GatherInfoToSession oTCard,Index, lMedium
                        set oTCard = nothing
                    End If
                    oNDInfo.ScriptOutputControl = OrigOutputControl + DEBUGWRITE
                End If
                
                InfoVal = oNDTSession(Index & "OID_GEN_MAXIMUM_TOTAL_SIZE")
                if (not(IsEmpty (InfoVal))) Then
                    oLog.Write("MAXIMUM_TOTAL_SIZE = " & InfoVal)
                End If
                
                InfoVal = oNDTSession(Index & "MAC_ADDRESS")
                if (not(IsEmpty (InfoVal))) Then
                    oLog.Write("MAC_ADDRESS = " & InfoVal)
                End If
                
                DumpLinkSpeed(Index)
                DumpPnpCapabilities(Index)
                DumpMacOptions(Index)
                DumpMiniportInfo(Index)
                
            End If
        End If
        Index = Index + 1
        
    Next	
    oLog.Write("*****************************************************************" )
    
    oNDInfo.ScriptOutputControl = OrigOutputControl
    Set pAdptrLst = Nothing
    
End Function

Function GatherInfoToSession(oTCard, Index, lMedium)
    Dim ReturnVal
    Dim bResult

    bResult = oTCard.QueryInfo(OID_GEN_MINIPORT_INFO, ReturnVal, QUERY_SELECTED_STATS)
    if (bResult) Then
        oNDTSession(Index & "OID_GEN_MINIPORT_INFO") = ReturnVal
    End If
    
    bResult = oTCard.QueryInfo(OID_GEN_DRIVER_VERSION, ReturnVal)
    if (bResult) Then
        oNDTSession (Index & "OID_GEN_DRIVER_VERSION") = ReturnVal
    End If
    
    bResult = oTCard.QueryInfo(OID_GEN_LINK_SPEED, ReturnVal)
    if (bResult) Then
        oNDTSession(Index & "OID_GEN_LINK_SPEED") = ReturnVal
    End If
    
    bResult = oTCard.QueryInfo(OID_GEN_MAXIMUM_TOTAL_SIZE, ReturnVal)
    if (bResult) Then
        oNDTSession(Index & "OID_GEN_MAXIMUM_TOTAL_SIZE") = ReturnVal
    End If
    
    bResult = oTCard.QueryInfo(OID_GEN_MAC_OPTIONS, ReturnVal)
    if (bResult) Then
        oNDTSession(Index & "OID_GEN_MAC_OPTIONS") = ReturnVal
    End If
    
    Dim Levels()
    Dim ArraySize
    bResult = oTCard.QueryInfo(OID_PNP_CAPABILITIES, Levels)
    If (bResult) Then
        ArraySize = UBound(Levels) + 1
        
        if (ArraySize = 16) Then
            oNDTSession(Index & "OID_PNP_CAPABILITIESFlags")   = Levels(0) + (2^8 * Levels(1)) + (2^16 * Levels(2)) + (2^24 * Levels(3))
            oNDTSession(Index & "OID_PNP_CAPABILITIESMagic")   = Levels(4) + (2^8 * Levels(5)) + (2^16 * Levels(6)) + (2^24 * Levels(7))
            oNDTSession(Index & "OID_PNP_CAPABILITIESPattern") = Levels(8) + (2^8 * Levels(9)) + (2^16 * Levels(10)) + (2^24 * Levels(11))
            oNDTSession(Index & "OID_PNP_CAPABILITIESLink")    = Levels(12) + (2^8 * Levels(13)) + (2^16 * Levels(14)) + (2^24 * Levels(15))
        End If
    End If
    
    Dim Addr
    Addr = GetCardAddress(oTCard, oLog, lMedium)
    
    if (NOT (Addr(0) = 0 AND Addr(1) = 0 AND Addr(2) = 0 AND Addr(3) = 0 AND Addr(4) = 0 AND Addr(5) = 0)) Then
        oNDTSession(Index & "MAC_ADDRESS") = Hex(Addr(0)) & "-" & Hex(Addr(1)) & "-" & Hex(Addr(2)) & "-" & Hex(Addr(3)) & "-" & Hex(Addr(4)) & "-" & Hex(Addr(5))
    End If
    
    
End Function

Function DumpPnpCapabilities(Index)
    Dim InfoVal
    Dim Magic,Pattern,Link
    
    InfoVal = oNDTSession(Index & "OID_PNP_CAPABILITIESFlags")
    if (not(IsEmpty (InfoVal))) Then
        oLog.Write("OID_PNP_CAPABILITIES Flags = 0x" & hex(InfoVal))
    Else
        Exit Function
    End If
    
    Magic = oNDTSession(Index & "OID_PNP_CAPABILITIESMagic")
    if (not(IsEmpty (Magic))) Then
        Magic = ConvertDeviceState(Magic)
    Else
        Magic = "none"
    End If
    
    Pattern = oNDTSession(Index & "OID_PNP_CAPABILITIESPattern")
    if (not(IsEmpty (Pattern))) Then
        Pattern = ConvertDeviceState(Pattern)
    Else
        Pattern = "none"
    End If
    
    Link = oNDTSession(Index & "OID_PNP_CAPABILITIESLink")
    if (not(IsEmpty (Link))) Then
        Link = ConvertDeviceState(Link)
    Else
        Link = "none"
    End If
    
    oLog.Write("   Magic\Pattern\Link Wake " & Magic &"\"& Pattern &"\"& Link)
    
End Function

Function ConvertDeviceState(State)
    if (State = NDISDEVICESTATEUNSPECIFIED) Then
        ConvertDeviceState = "Unspecified"
    ElseIf (State = NDISDEVICESTATED0) Then
        ConvertDeviceState = "D0"
    ElseIf (State = NDISDEVICESTATED1) Then
        ConvertDeviceState = "D1"
    ElseIf (State = NDISDEVICESTATED2) Then
        ConvertDeviceState = "D2"
    ElseIf (State = NDISDEVICESTATED3) Then
        ConvertDeviceState = "D3"
    Else
        ConvertDeviceState = "Unknown " & State & " "
    End If
End Function

Function DumpMacOptions(Index)
    Dim InfoVal
    
    InfoVal = oNDTSession(Index & "OID_GEN_MAC_OPTIONS")
    if (not(IsEmpty (InfoVal))) Then
        if (InfoVal) Then
            oLog.Write("MAC_OPTIONS = 0x" & hex(InfoVal))
            
            if (InfoVal AND NDIS_MAC_OPTION_COPY_LOOKAHEAD_DATA) Then
                oLog.Write("   Copy Lookahead Data")
            Else
                oLog.Write("   Lookahead buffer cannot be copied directly")
            End If
            
            if (InfoVal AND NDIS_MAC_OPTION_RECEIVE_SERIALIZED) Then
                oLog.Write("   Receives are Serialized")
            Else
                oLog.Write("   Receives are not Serialized")
            End If
            
            if (InfoVal AND NDIS_MAC_OPTION_TRANSFERS_NOT_PEND) Then
                oLog.Write("   Transfers never Pend")
            Else
                oLog.Write("   Transfers can be Pended")
            End If
            
            if (InfoVal AND NDIS_MAC_OPTION_NO_LOOPBACK) Then
                oLog.Write("   NDIS handles Loopback")
            Else
                oLog.Write("   Driver handles Loopback")
            End If
            
            if (InfoVal AND NDIS_MAC_OPTION_FULL_DUPLEX) Then
                oLog.Write("   Transmit's do not need to be serialized with other requests")
            Else
                oLog.Write("   Transmit's must be serialized with other requests")
            End If
            
            'if (InfoVal AND NDIS_MAC_OPTION_EOTX_INDICATION) Then
            '    oLog.Write("   EOTX Indication")
            'Else
            '    oLog.Write("   EOTX Indication not selected")
            'End If
            
            if (InfoVal AND NDIS_MAC_OPTION_8021P_PRIORITY) Then
                oLog.Write("   802.1p Priority is supported")
            Else
                oLog.Write("   802.1p Priority is not supported")
            End If
            
            if (InfoVal AND NDIS_MAC_OPTION_SUPPORTS_MAC_ADDRESS_OVERWRITE) Then
                oLog.Write("   Mac Address can be Overwritten")
            Else
                oLog.Write("   Mac Address cannot be Overwritten")
            End If
            
            'if (InfoVal AND NDIS_MAC_OPTION_RECEIVE_AT_DPC) Then
            '    oLog.Write("   Receive at Dpc")
            'Else
            '    oLog.Write("   Does not Receive at Dpc")
            'End If
            
            if (InfoVal AND NDIS_MAC_OPTION_8021Q_VLAN) Then
                oLog.Write("   802.1q VLAN is supported")
            Else
                oLog.Write("   802.1q VLAN is not supported")
            End If
        End If
    End If
End Function

Function DumpLinkSpeed(Index)
    Dim InfoVal
    
    InfoVal = oNDTSession(Index & "OID_GEN_LINK_SPEED")
    if (not(IsEmpty (InfoVal))) Then
        If (InfoVal > 9999999) Then
            oLog.Write("LINK_SPEED = " & InfoVal/10000000 & " Gbps")
        ElseIf (InfoVal > 9999) Then
            oLog.Write("LINK_SPEED = " & InfoVal/10000 & " Mbps")
        Else
            oLog.Write("LINK_SPEED = " & InfoVal/10 & " kbps")
        End If
    End If
End Function

Function DumpMiniportInfo(Index)
    Dim InfoVal
    InfoVal = oNDTSession(Index & "OID_GEN_MINIPORT_INFO")
    
    if (not(IsEmpty (InfoVal))) Then
        oLog.Write("MINIPORT_INFO = 0x" & hex(InfoVal))
        
        if (InfoVal AND NDIS_MINIPORT_BUS_MASTER) Then
            oLog.Write("   Bus Master")
        Else
            oLog.Write("   Not a Bus Master")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_WDM_DRIVER) Then
            oLog.Write("   WDM Driver")
        Else
            oLog.Write("   Not a WDM Driver")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_SG_LIST) Then
            oLog.Write("   Uses Scatter Gather List")
        Else
            oLog.Write("   Does not use Scatter Gather List")
        End If
        
'        if (InfoVal AND NDIS_MINIPORT_SUPPORTS_MEDIA_QUERY) Then
'            oLog.Write("   Supports Media Query")
'        Else
'            oLog.Write("   Does not supports Media Query")
'        End If
        
        if (InfoVal AND NDIS_MINIPORT_INDICATES_PACKETS) Then
            oLog.Write("   Indicates Packets")
        Else
            oLog.Write("   Does not Indicate Packets")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_IGNORE_PACKET_QUEUE) Then
            oLog.Write("   Outstanding packets can cause reset to be called")
        Else
            oLog.Write("   Outstanding packets cannot cause reset to be called")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_IGNORE_REQUEST_QUEUE) Then
            oLog.Write("   Outstanding requests can cause reset to be called")
        Else
            oLog.Write("   Outstanding requests cannot cause reset to be called")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_IGNORE_TOKEN_RING_ERRORS) Then
            oLog.Write("   Ignore Token Ring Errors")
        Else
            oLog.Write("   Do not Ignore Token Ring Errors")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_INTERMEDIATE_DRIVER) Then
            oLog.Write("   IM Driver")
        Else
            oLog.Write("   Not an IM Driver")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_IS_NDIS_5) Then
            oLog.Write("   Ndis 5 driver")
        Else
            oLog.Write("   Is not an Ndis 5 driver")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_IS_CO) Then
            oLog.Write("   Connection Oriented")
        Else
            oLog.Write("   Is not Connection Oriented")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_DESERIALIZE) Then
            oLog.Write("   Deserialized")
        Else
            oLog.Write("   Is not Deserialized")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_REQUIRES_MEDIA_POLLING) Then
            oLog.Write("   Requires Media Polling")
        Else
            oLog.Write("   Does not require Media Polling")
        End If
        
'        if (InfoVal AND NDIS_MINIPORT_SUPPORTS_MEDIA_SENSE) Then
'            oLog.Write("   Supports Media Sense")
'        Else
'            oLog.Write("   Does not support Media Sense")
'        End If
        
        if (InfoVal AND NDIS_MINIPORT_NETBOOT_CARD) Then
            oLog.Write("   NetBoot Card")
        Else
            oLog.Write("   Is not a NetBoot Card")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_PM_SUPPORTED) Then
            oLog.Write("   Power Management is supported")
        Else
            oLog.Write("   Power Management is not supported")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_SUPPORTS_MAC_ADDRESS_OVERWRITE) Then
            oLog.Write("   Supports Mac Address Overwrite")
        Else
            oLog.Write("   Does not supports Mac Address Overwrite")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_USES_SAFE_BUFFER_APIS) Then
            oLog.Write("   Uses Safe Buffer Apis")
        Else
            oLog.Write("   Does not use Safe Buffer Apis")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_HIDDEN) Then
            oLog.Write("   Hidden")
        Else
            oLog.Write("   Is not Hidden")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_SWENUM) Then
            oLog.Write("   Is Software Enumerated")
        Else
            oLog.Write("   Is not Software Enumerated")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_SURPRISE_REMOVE_OK) Then
            oLog.Write("   Surprise Remove OK")
        Else
            oLog.Write("   Surprise Remove is not OK")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_NO_HALT_ON_SUSPEND) Then
            oLog.Write("   Do not Halt on Suspend")
        Else
            oLog.Write("   Halt on Suspend")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_HARDWARE_DEVICE) Then
            oLog.Write("   Hardware Device")
        Else
            oLog.Write("   Is not a Hardware Device")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_SUPPORTS_CANCEL_SEND_PACKETS) Then
            oLog.Write("   Supports Cancel Send Packets")
        Else
            oLog.Write("   Does not support Cancel Send Packets")
        End If
        
        if (InfoVal AND NDIS_MINIPORT_64BITS_DMA) Then
            oLog.Write("   64 Bit DMA")
        Else
            oLog.Write("   Does not do 64 Bit DMA")
        End If
        
        oLog.Write(" ") ' Extra Carriage Return
    End If
End Function

Function SetupTestForIP(oTestOpen, lTestAdapterIndex, oSuppOpen, lSupportAdapterIndex)
    Dim TestIP, SuppIP
    Dim TestGW, SuppGW
    Dim TestGWAddr,SuppGWAddr
    Dim bResult, bUseIP
    
    SetupTestForIP = TRUE
    
    bUseIP = oNDTSession("UseIPPackets")
    
    If (not(IsEmpty (bUseIP))) Then
        If (bUseIP = 1) Then
            TestIP = oNDInfo.AdapterList(lTestAdapterIndex).IPAddress
            SuppIP = oNDInfo.AdapterList(lSupportAdapterIndex).IPAddress
            TestGW = oNDInfo.AdapterList(lTestAdapterIndex).GatewayMac
            SuppGW = oNDInfo.AdapterList(lSupportAdapterIndex).GatewayMac
            
            TestGWAddr = Str2NetAddr(TestGW)
            SuppGWAddr = Str2NetAddr(SuppGW)
            
            
            bResult = oTestOpen.SetIPAddress(TestIP, SuppIP, TestGWAddr)
            If(Not bResult) Then
                SetupTestForIP = FALSE
            End If
            
            bResult = oSuppOpen.SetIPAddress(SuppIP, TestIP, SuppGWAddr)
            If(Not bResult) Then
                SetupTestForIP = FALSE
            End If
        End If
    End If
    
    If (Not SetupTestForIP) Then
        call oLog.SafeFailed("Unable to Set IP Related Information for Test and support Card", 88888)
    End If
    
End Function

'//===============================================================================================//
'/**
'This function sets the Source and Destination IP addresses on the support instance
'@param oSuppOpen Support adapter open instance
'@param lSupportAdapterIndex Index of the support adapter in NDInfo adapter list. Uses this to find IP address
'@param strIPAddress     IPAddress of test adapter
'@return	    Returns true if succesful else return false
'*/
Function SetupSupportCardForIP(oSuppOpen,lSupportAdapterIndex, strIPAddress)
    Dim SuppIP
    Dim SuppGW
    Dim SuppGWAddr
    Dim bResult, bUseIP
    
    SetupSupportCardForIP = TRUE
    
    bUseIP = oNDTSession("UseIPPackets")
    
    If (not(IsEmpty (bUseIP))) Then
        If (bUseIP = 1) Then
            SuppIP = oNDInfo.AdapterList(lSupportAdapterIndex).IPAddress
            SuppGW = oNDInfo.AdapterList(lSupportAdapterIndex).GatewayMac
            
            SuppGWAddr = Str2NetAddr(SuppGW)
            
            bResult = oSuppOpen.SetIPAddress(SuppIP, strIPAddress, SuppGWAddr)
            If(Not bResult) Then
                SetupSupportCardForIP = FALSE
            End If
        End If
    End If
    
    If (Not SetupSupportCardForIP) Then
        Call oLog.SafeFailed("Unable to Set IP Related Information for support Card", 88888)
    End If
    
End Function

'//===============================================================================================//
'/**
'This function sets the Source and Destination IP addresses on the test instance
'@param oTestOpen test adapter open instance
'@param lTestAdapterIndex Index of the test adapter in NDInfo adapter list. Uses this to find IP address
'@param strIPAddress     IPAddress of support adapter
'@return	    Returns true if succesful else return false
'*/
Function SetupTestCardForIP(oTestOpen, lTestAdapterIndex, strIPAddress)
    Dim TestIP
    Dim TestGW
    Dim TestGWAddr
    Dim bResult, bUseIP
    
    SetupTestCardForIP = TRUE
    
    bUseIP = oNDTSession("UseIPPackets")
    
    If (not(IsEmpty (bUseIP))) Then
        If (bUseIP = 1) Then
            TestIP = oNDInfo.AdapterList(lTestAdapterIndex).IPAddress
            TestGW = oNDInfo.AdapterList(lTestAdapterIndex).GatewayMac
            
            TestGWAddr = Str2NetAddr(TestGW)
            
            bResult = oTestOpen.SetIPAddress(TestIP, strIPAddress, TestGWAddr)
            If(Not bResult) Then
                SetupTestCardForIP = FALSE
            End If
        End If
    End If
    
    If(Not SetupTestCardForIP) Then
        Call oLog.SafeFailed("Unable to Set IP Related Information for Test Card", 88888)
    End If
End Function

Function Associate1x(nTestCardIndex)
Dim cTestCard', cOpen
Dim bRetval	
Dim nNdisStatus
Dim sSsid, sKeyMaterial', sCurrentSsid
Dim nInfraMode, nAuthMode, nWepStatus, nKeyIndex', nConnectStatus', nSsidLength, nResultSize
'Dim CONNECTED, DISCONNECTED
    
    'CONNECTED       = 0
    'DISCONNECTED    = 1
    'nResultSize     = 4
    
    sSsid           = DEFAULTAP.Ssid           
    sKeyMaterial    = DEFAULTAP.KeyMaterial    
    nInfraMode      = DEFAULTAP.InfrastructureMode  
    nAuthMode       = DEFAULTAP.AuthenticationMode       
    nWepStatus      = DEFAULTAP.WepStatus      
    nKeyIndex       = DEFAULTAP.KeyIndex  
    
    Set cTestCard = New CWlan
         
    oLog.Variation("Attempting to associate with default access point...")
    bRetval = cTestCard.CreateAdapter(nTestCardIndex)
    if(bRetval = false) then
        Exit Function
    end if
    
    '
    ' Check Test Adapter
    'Set cOpen = cTestCard.AdapterOpen
    'bRetval = cOpen.QueryInfo(OID_GEN_MEDIA_CONNECT_STATUS, nConnectStatus, nResultSize)
    'i'f(bRetval = false) Then
        'call oLog.Warned ("Unable to query test card media connect status!")
       ' Exit Function
    'end if
    
    'Call cTestCard.SsidQe(nSsidLength, sCurrentSsid, nNdisStatus)
    
    'if((nConnectStatus = DISCONNECTED) Or (Not sCurrentSsid = sSsid)) then
    bRetval = cTestCard.ReAssociate(sSsid, nInfraMode, nAuthMode, nKeyIndex, sKeyMaterial, nWepStatus)
    'end if
        
    cTestCard.CloseAdapter()
    Set cTestCard = Nothing
    
    Associate1x = true
    
End Function

Function Associate2x(nTestCardIndex, nSupportCardIndex)
Dim cTestCard, cSuppCard', cOpen
Dim bRetval
Dim sSsid, sKeyMaterial', sCurrentSsid
Dim nInfraMode, nAuthMode, nWepStatus, nKeyIndex, nNdisStatus', nConnectStatus, nSsidLength, nResultSize
Dim oList
'Dim CONNECTED, DISCONNECTED
    
    'CONNECTED       = 0
    'DISCONNECTED    = 1
    'nResultSize     = 4
    
    sSsid           = DEFAULTAP.Ssid           
    sKeyMaterial    = DEFAULTAP.KeyMaterial    
    nInfraMode      = DEFAULTAP.InfrastructureMode  
    nAuthMode       = DEFAULTAP.AuthenticationMode       
    nWepStatus      = DEFAULTAP.WepStatus      
    nKeyIndex       = DEFAULTAP.KeyIndex    
   
    Set cTestCard = New CWlan
    Set cSuppCard = New CWlan
    
    oLog.Variation("Attempting to associate with default access point...")
            
    bRetval = cTestCard.CreateAdapter(nTestCardIndex)
    if(bRetval = false) then
        Exit Function
    end if

    bRetval = cSuppCard.CreateAdapter(nSupportCardIndex)
    if(bRetval = false) then
        Exit Function
    end if
    
    '
    ' Check Test Adapter
    'Set cOpen = cTestCard.AdapterOpen
    'bRetval = cOpen.QueryInfo(OID_GEN_MEDIA_CONNECT_STATUS, nConnectStatus, nResultSize)
    'if(bRetval = false) Then
    '    call oLog.Warned ("Unable to query test card media connect status!")
    '    Exit Function
    'end if
    
    'Call cTestCard.SsidQe(nSsidLength, sCurrentSsid, nNdisStatus)
    
    'if((nConnectStatus = DISCONNECTED) Or (Not sCurrentSsid = sSsid)) then
    bRetval = cTestCard.ReAssociate(sSsid, nInfraMode, nAuthMode, nKeyIndex, sKeyMaterial, nWepStatus)
    'end if
         
    '
    ' Check support Adapter
    'Set cOpen = cSuppCard.AdapterOpen
   ' bRetval = cOpen.QueryInfo(OID_GEN_MEDIA_CONNECT_STATUS, nConnectStatus, nResultSize)
    'if(bRetval = false) Then
    '    call oLog.Warned ("Unable to query support card media connect status!")
    '    Exit Function
   ' end if
    
    'Call cSuppCard.SsidQe(nSsidLength, sCurrentSsid, nNdisStatus)
    
    'if((nConnectStatus = DISCONNECTED) Or (Not sCurrentSsid = sSsid)) then
    bRetval = cSuppCard.ReAssociate(sSsid, nInfraMode, nAuthMode, nKeyIndex, sKeyMaterial, nWepStatus)
    'end if
    
    cTestCard.CloseAdapter()
    cSuppCard.CloseAdapter()

    Set cTestCard = Nothing
    Set cSuppCard = Nothing
    
    Associate2x = true
    
End Function

Function PrintVerifierSetting (FullDriverName)
   Dim DriverName
   Dim arrParts
   Dim ulLevel
   
   PrintVerifierSetting = False
   
   ' The driver name may contain the whole path, need to extract past the last \

   On Error Resume Next
   arrParts = Split(FullDriverName, "\", -1)
   DriverName = arrParts(UBound(arrParts))
   If (Err <> 0) Then
      oLog.Write ("Driver Verifier Level: Unable to parse")
      Err.Clear
      Exit Function
   End If
   On Error Goto 0

   If (DriverName <> "") Then
      If (oNdtSupp.VerifierSetting(DriverName, ulLevel)) Then
         If (ulLevel <> 0) Then
            oLog.Write ("Driver Verifier Level: 0x" & Hex(ulLevel))
         Else
            oLog.Write ("Driver Verifier Level: Disabled")
         End If
      Else
         oLog.Write ("Driver Verifier Level: Unable to determine")   
      End If
   End If
   
   PrintVerifierSetting = True

End Function



'<!-- CRC = 0x739e3283 --->
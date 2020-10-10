Option Explicit

Function NullAddr()
    NullAddr = Array(CByte(0), CByte(0), CByte(0), _
    CByte(0), CByte(0), CByte(0))
End Function

Function NetAddr(val0, val1, val2, val3, val4, val5)
    NetAddr = Array(CByte(val0), CByte(val1), CByte(val2), _
    CByte(val3), CByte(val4), CByte(val5))
End Function

Function FunctAddr(val0, val1, val2, val3)
    FunctAddr = Array(CByte(val0), CByte(val1), CByte(val2), _
    CByte(val3))
End Function

Function GrpAddr(val0, val1, val2, val3)
    GrpAddr = Array(CByte(val0), CByte(val1), CByte(val2), _
    CByte(val3))
End Function

'==========================================================================
'
' Copies an array into another
'
Sub CopyArray (Dest, Src, Leng)
    Dim Idx
    Idx = 0
    Do While (Idx < Leng)
        Dest(Idx) = Src(Idx)
        Idx = Idx + 1
    Loop
End Sub

'==========================================================================
'
' Copies an array into another starting from position StartIndex in Dest
'
Sub CopyArrayAt (Dest, Src, Leng, StartIndex)
    Dim Idx
    Idx = 0
    Do While (Idx < Leng)
        Dest(Idx + StartIndex) = Src(Idx)
        Idx = Idx + 1
    Loop
End Sub

'==========================================================================
'
' Converts a functional address to a netaddr
'
Function Funct2NetAddr(FunctAddr1)
    Funct2NetAddr = NetAddr(&HC0&, &H00&, FunctAddr1(0), FunctAddr1(1), _
    FunctAddr1(2), FunctAddr1(3))
End Function


'==========================================================================
'
' Converts a group address to a netaddr
'
Function Grp2NetAddr(GroupAddr1)
    Grp2NetAddr = NetAddr(&HC0&, &H00&, GroupAddr1(0), GroupAddr1(1), _
    GroupAddr1(2), GroupAddr1(3))
End Function


'==========================================================================
'
' Compares two functional addresses
'
Function FunctAddrCmp(FunctAddr1, FunctAddr2)
    If ( (FunctAddr1(0) = FunctAddr2(0)) And _
        (FunctAddr1(1) = FunctAddr2(1)) And _
        (FunctAddr1(2) = FunctAddr2(2)) And _
        (FunctAddr1(3) = FunctAddr2(3)) ) Then
        FunctAddrCmp = TRUE
    Else
        FunctAddrCmp = FALSE     
    End If
End Function

'==========================================================================
'
' Compares two group addresses
'
Function GroupAddrCmp(GroupAddr1, GroupAddr2)
    If ( (GroupAddr1(0) = GroupAddr2(0)) And _
        (GroupAddr1(1) = GroupAddr2(1)) And _
        (GroupAddr1(2) = GroupAddr2(2)) And _
        (GroupAddr1(3) = GroupAddr2(3)) ) Then
        GroupAddrCmp = TRUE
    Else
        GroupAddrCmp = FALSE     
    End If
End Function

'==========================================================================
'
' Checks if the 6 bytes in the NetAddrList array starting from position Index 
' are the same as NetAddr
'
Function NetAddrCmpI(NetAddrList, NetAddr1, Index)
    If ( (NetAddrList(Index + 0) = NetAddr1(0)) And _
        (NetAddrList(Index + 1) = NetAddr1(1)) And _
        (NetAddrList(Index + 2) = NetAddr1(2)) And _
        (NetAddrList(Index + 3) = NetAddr1(3)) And _
        (NetAddrList(Index + 4) = NetAddr1(4)) And _                
        (NetAddrList(Index + 5) = NetAddr1(5)) ) Then
        NetAddrCmpI = TRUE
    Else
        NetAddrCmpI = FALSE     
    End If
End Function

'==========================================================================
'
' Checks if the Len bytes from ArrSmaller addr are the same as Len bytes in ArrLarger starting
' at position StartAt
'
Function ArrayCmpAt(ArrLarger, ArrSmaller, Len, StartAt)
    Dim iIndex
    iIndex = 0

    ArrayCmpAt = TRUE
    While (iIndex < Len)
        If (ArrLarger (StartAt + iIndex) <> ArrSmaller (iIndex)) Then
            ArrayCmpAt = FALSE
            Exit Function
        End If 
    WEnd
End Function

'==========================================================================
'Returns the netaddress as a string
'
Function NetAddr2Str(NetAddr1)
    NetAddr2Str = Hex(NetAddr1(0)) & "-" & _
    Hex(NetAddr1(1)) & "-" & _
    Hex(NetAddr1(2)) & "-" & _
    Hex(NetAddr1(3)) & "-" & _
    Hex(NetAddr1(4)) & "-" & _
    Hex(NetAddr1(5))
End Function

'==========================================================================
'Returns the string as a netaddr
'
Function Str2NetAddr(MacString)
    Dim arrMacAddr,MacAddr
    MacAddr = NullAddr()
    arrMacAddr = Split(MacString,"-",-1,1)
    MacAddr(0) = CByte("&H" & arrMacAddr(0))
    MacAddr(1) = CByte("&H" & arrMacAddr(1))
    MacAddr(2) = CByte("&H" & arrMacAddr(2))
    MacAddr(3) = CByte("&H" & arrMacAddr(3))
    MacAddr(4) = CByte("&H" & arrMacAddr(4))
    MacAddr(5) = CByte("&H" & arrMacAddr(5))
    Str2NetAddr = MacAddr
End Function

'==========================================================================
'
' Sets the packet filter for the open instance, and returns the status
' returned by NDIS request
'
Function SetPacketFilter(oTestOpen, ParamNewFilter)
    Dim BytesWritten, BytesNeeded, NdisStatus
    Dim strFilters
    Dim NewFilter
    NewFilter = ParamNewFilter ' Do this because NdisRequest can change it


    If (oTestOpen is Nothing) Then
        Err.Raise 32000, "SetPacketFilter", _
        "Require an open adapter instance"
    End If

    BytesWritten = CLng(0)
    BytesNeeded = CLng(0)

    strFilters = "SetPacketFilter is setting the packet filter to (0x" & hex(NewFilter) & ") "

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

    if (NewFilter AND SMT)Then
        strFilters = strFilters & "SMT "
    End If

    strFilters = strFilters  & vblf

    oLog.Write(strFilters)

    SetPacketFilter = oTestOpen.NdisRequest( _
    OID_GEN_CURRENT_PACKET_FILTER, _
    NewFilter, _
    4, _
    REQUEST_SET_INFO, _
    BytesWritten, _
    BytesNeeded, _
    NdisStatus)

    If (Not SetPacketFilter) Then
        Call oLog.Write("NdisRequest failed during OID_GEN_CURRENT_PACKET_FILTER" )
    ElseIf (NdisStatus <> 0) Then
        SetPacketFilter = FALSE
        oLog.Write("NdisRequest OID_GEN_CURRENT_PACKET_FILTER returned NdisStatus " & hex(NdisStatus) )
    End If

End Function

'==========================================================================
'
' Queries the specified OID on the open object, and returns the
' resulting value, in the result variable. Resultsize contains
' the size allocated to the result variable on the call in, and
' returns the actual number of bytes written on the call out
'
Function QueryInfo(oTestOpen, ulOid, Result, ResultSize)
    Dim BytesWritten, BytesNeeded, NdisStatus

    If (oTestOpen is Nothing) Then
        Err.Raise 32000, "QueryInfo", _
        "Require an open adapter instance"
    End If
    BytesWritten = CLng(0)
    BytesNeeded = CLng(0)

    QueryInfo = oTestOpen.NdisRequest( _
            ulOid, _
            Result, _
            ResultSize, _
            REQUEST_QUERY_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus)

    ResultSize =  BytesWritten

End Function

'==========================================================================
'
' Checks if the Item is present in the List whose length is ListLength
'
' This function should only be called with either a netaddress, or a numeric
' value
'
Function isItemInList( Item, List, ListLength)
    Dim iIndex
    Dim Found

    Found = FALSE
    If (IsNumeric(Item)) Then
        iIndex = CLng(0)
        Do While (iIndex < ListLength)
            If (List(iIndex) = Item) Then
                Found = TRUE
                Exit Do
            End If   
            iIndex = iIndex + 1
        Loop
    Else
        ' Since Item can only be a Long or a Netaddr, if it is not numeric,
        ' we can directly work with the assumption that it is a netaddr
        iIndex = CLng(0)
        Do While (lIndex < ListLength)
            If (NetAddrCmpI(Item, List(iIndex), 0)) Then
                Found = TRUE
                Exit Do
            End If
            iIndex = iIndex + 1
        Loop
    End If
    isItemInList = Found
End Function

'==========================================================================
'
' A cleaner version of NDIS close. This ensures that if the instance
' was not opened successfully, vbscript would not give an error about
' being unable to find the object.
'
Function Close(oTestOpen)
    Dim bResult
    bResult = TRUE
    If (Not (oTestOpen is Nothing)) Then
        bResult = oTestOpen.NdisClose()
    End If
    Close = bResult
End Function

'==========================================================================
'If this is a IA64 machine, this function returns a true, else false
'
Function IsIA64Machine ()
    Dim Win64
    Win64 = oNDTSession ("Win64")
    If (IsEmpty (Win64)) Then
        oLog.SafeWarned ("IA 64 info could not be found in the session!!!")
        ' Assuming 64 bit and pressing on with the test
        IsIA64Machine = FALSE
    End If

    If (Win64 = 0) Then
        IsIA64Machine = FALSE
    Else
        IsIA64Machine = TRUE
    End If
End Function

'==========================================================================
'If this is an IM Driver, this function returns a true, else false
'
Function IsIMDriver(lDeviceIndex)
    Dim InfoVal
    InfoVal = oNDTSession(lDeviceIndex & "OID_GEN_MINIPORT_INFO")
    
    If (IsEmpty (InfoVal)) Then
        ' Maybe OID_GEN_MINIPORT_INFO is not supported, lets check if 
        ' we have set the DriverType bits to see if its an IM
        InfoVal = oNDTSession(lDeviceIndex & "DriverType")
        If (IsEmpty(InfoVal)) Then
           oLog.SafeWarned ("Unable to determine if device is an intermediate driver")
           ' Assuming not an IM driver and quitting
           IsIMDriver = FALSE
        Else
           If (InfoVal = 1) Then
              IsIMDriver = TRUE
           Else
              IsIMDriver = FALSE
           End If
        End If
    Else
       If (InfoVal AND NDIS_MINIPORT_INTERMEDIATE_DRIVER) Then
           IsIMDriver = TRUE
       Else
           IsIMDriver = FALSE
       End If
    End If

End Function

'==========================================================================
'If this is a USB bus, this function returns a true, else false
'
Function IsUSBDevice(lDeviceIndex)
    Dim strDriverBus
    strDriverBus = oNDTSession (lDeviceIndex & "DriverBus")
    If (IsEmpty (strDriverBus)) Then
        oLog.SafeWarned (lDeviceIndex & "DriverBus could not be found in the session!!!")
        ' Assuming non USB and quitting
        IsUSBDevice = FALSE
        Exit Function
    End If

    If (UCase(strDriverBus) = "USB") Then
        IsUSBDevice = TRUE
    Else
        IsUSBDevice = FALSE
    End If
End Function

'==========================================================================
'If this is a Laptop, this function returns a true, else false
'
Function IsLaptop()
    IsLaptop = oNDTSession ("IsLaptop")
    If (IsEmpty (IsLaptop)) Then
        oLog.SafeWarned ("IsLaptop could not be found in the session!!!")
        ' Assume non Laptop
        IsLaptop = FALSE
    End If
End Function

'==========================================================================
'This function returns the index of the test adapter in the adapter list
'
Function GetTestAdapterIndex(pAdapterList, lLastIndex)
    ' Find the adapter from the adapter list that has type 1 => Test Adapter
    Dim lTestId, lCounter
    Dim oAdapter

    lTestId = lLastIndex

    For lCounter = lLastIndex+1 to pAdapterList.Count
        If (pAdapterList(lCounter).AdapterType = 1) Then
            lTestId = lCounter
            Exit For
        End If
    Next

    If lTestId = 0 Then
        Err.Raise 32000, "Internal NDTest failure", _
        "Cannot find a test adapter in adapter list"
    End If

    GetTestAdapterIndex = lTestId
End Function

'==========================================================================
'This function returns the index of the first support adapter in the adapter list. It tries to find a remote adapter,
'but if unsuccessful to find a remote support, just returns the first support adapter it found
Function GetSupportAdapterIndex(pAdapterList, lLastIndex)
    ' Find the adapter from the adapter list that has type 2 => Support Adapter
    Dim lSuppId, lCounter, lFound
    Dim oAdapter

    lSuppId = lLastIndex
    lFound = CLng(0)

    For lCounter = lLastIndex+1 To pAdapterList.Count
        If (pAdapterList(lCounter).AdapterType = 2) Then

            ' We want to use the first support adapter found if this one is not remote
            If (lFound = 0) Then
                lSuppId = lCounter
                lFound = 1
            End If
            
            If (pAdapterList(lCounter).ConnectionId <> 0) Then
                ' This is a remote support adapter, use it
                lSuppId = lCounter
                Exit For
            End If
        End If
    Next

    ' Since the lLastIndex would be 0 only for the first time the call is made, if we find that
    ' lSuppId is still 0, then it means that we did not find any support adapter
    If lSuppId = 0 Then
        Err.Raise 32000, "Internal NDTest failure", _
        "Cannot find a support adapter in adapter list"
    End If

    GetSupportAdapterIndex = lSuppId
End Function

'==========================================================================
'This function is a stricter version of GetSupportAdapterIndex. It is used for 2 machine tests,
'where it is necessary for the support adapter to be on a remote machine
Function GetRemoteSupportAdapter(pAdapterList, lLastIndex)
    Dim lSupportAdapterIndex
    lSupportAdapterIndex = GetSupportAdapterIndex (pAdapterList, lLastIndex)

    If (lSupportAdapterIndex <> 0) Then
        If (oNDInfo.AdapterList(lSupportAdapterIndex).ConnectionId <> 0) Then
            GetRemoteSupportAdapter = lSupportAdapterIndex
        Else
            ' This means GetSupportAdapterIndex did not find a support adapter on remote.
            ' Since it will always find a remote adapter if available, we check if we had found
            ' a remote adapter before.
            If (lLastIndex = 0) Then
                ' Not found a remote adapter before
                Err.Raise 32000, "Internal NDTest failure", _
                "Cannot find a remote support adapter in adapter list"
                GetRemoteSupportAdapter = 0
            Else
                ' Had found a remote adapter before, return
                GetRemoteSupportAdapter = lLastIndex
            End If
        End If
    Else
        GetRemoteSupportAdapter = 0
    End If
End Function

Function ShowTimedPopup(strText, nSecondsToWait, strTitle, nType)
   Dim oWshShell
   Set oWshShell = Wscript.CreateObject("WScript.Shell")   
   If (oWshShell is Nothing) Then
      Call oLog.Write ("Unable to create WScript.Shell object")
      ShowTimedPopup = 0
      Exit Function
   End If

   ' Return status from call (always a systemmodal text box
   ShowTimedPopup = oWshShell.Popup(strText, nSecondsToWait, "NDIS Tester - " & strTitle & " (timeout after " & nSecondsToWait & " seconds)", nType + vbSystemModal)

   Set oWshShell = Nothing
End Function


'<!-- CRC = 0x69eb68d2 --->
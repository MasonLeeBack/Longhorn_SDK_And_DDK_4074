Option Explicit

'================================================================================================='
'/**
' * This function is used to initiailize an address variable. Internally it just
' * returns an array of 6 bytes containing 0s
' * @return    A blank address buffer
' * @sa        NetAddr
' */
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

Function IPAddr(val0, val1, val2, val3)
   IPAddr = Array(CByte(val0), CByte(val1), CByte(val2), CByte(val3))
End Function

Function IPv6Addr(val0, val1, val2, val3)
   IPv6Addr = Array(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CByte(val0), CByte(val1), CByte(val2), CByte(val3))
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

Function UseIPHeaders
   Dim bUseIPHeaders
   UseIPHeaders = FALSE
   bUseIPHeaders = oNDTSession("UseIPPackets")
   If (not(IsEmpty (bUseIPHeaders))) Then
      If (bUseIPHeaders = 1) Then
         oLog.Write("This test is not supported with IP Packets. Please disable Force IP Packet Headers option from menu and try again.")
         UseIPHeaders = TRUE
      End If
   End If
End Function

'================================================================================================='
'/**
'This function creates an appropriate Card leaf object so that multiple media types can be
'worked on using a single script.
'@return    As appropriate, a CLanCard or CIrdaCard, .. object
'@code
'  Set oTestCard = CreateCardObject (oNDInfo.AdapterList(1))
'@endcode
'@date      12/07/01
'@author    Mitesh Desai
'@alias     miteshd@microsoft.com
'*/
Function CreateCardObject(oCOMAdapter)
   Dim nNdisMedium

   nNdisMedium = CLng(oCOMAdapter.NdisMedium)
   Select Case nNdisMedium
      Case NDISMEDIUM802_3
         If (g_UseNdis6Protocol) Then
            Set CreateCardObject = New CLanCard6
         Else
            Set CreateCardObject = New CLanCard
         End If
      Case NDISMEDIUM802_5
         Set CreateCardObject = New CLanCard
      Case NDISMEDIUMFDDI
         Set CreateCardObject = New CLanCard
      Case NDISMEDIUMIRDA
         Set CreateCardObject = New CIrdaCard
      Case Else
         ' For all other NdisMedium, we create the
         ' base CCard object
         Set CreateCardObject = New CCard
   End Select

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


         bResult = oTestOpen.vbSetIPAddress(TestIP, SuppIP, TestGWAddr)
         If(Not bResult) Then
            SetupTestForIP = FALSE
         End If

         bResult = oSuppOpen.vbSetIPAddress(SuppIP, TestIP, SuppGWAddr)
         If(Not bResult) Then
            SetupTestForIP = FALSE
         End If
      End If
   End If

   If (Not SetupTestForIP) Then
      call oLog.SafeFailed("Unable to Set IP Related Information for Test and support Card", 88888)
   End If

End Function

'===============================================================================================//
'/**
'This function sets the Source and Destination IP addresses on the support instance
'@params
'  !  object Support adapter open instance
'  !  number Index of the support adapter in NDInfo adapter list. Uses this to find IP address
'  !  string IPAddress of test adapter
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

         bResult = oSuppOpen.vbSetIPAddress(SuppIP, strIPAddress, SuppGWAddr)
         If(Not bResult) Then
            SetupSupportCardForIP = FALSE
         End If
      End If
   End If

   If (Not SetupSupportCardForIP) Then
      Call oLog.SafeFailed("Unable to Set IP Related Information for support Card", 88888)
   End If

End Function

'===============================================================================================//
'/**
'This function sets the Source and Destination IP addresses on the test instance
'@params
'  !  object test adapter open instance
'  !  number Index of the test adapter in NDInfo adapter list. Uses this to find IP address
'  !  string IPAddress of support adapter
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

         bResult = oTestOpen.vbSetIPAddress(TestIP, strIPAddress, TestGWAddr)
         If(Not bResult) Then
            SetupTestCardForIP = FALSE
         End If
      End If
   End If

   If(Not SetupTestCardForIP) Then
      Call oLog.SafeFailed("Unable to Set IP Related Information for Test Card", 88888)
   End If
End Function

'==========================================================================
'This function returns the version of a file as exposed to the file system
Function WinFileVersion(strFileName)
   Dim oFS, WshShell, WshSysEnv, WinDir, FVersion

   Set WshShell = WScript.CreateObject("WScript.Shell")
   Set WshSysEnv = WshShell.Environment("PROCESS")
   WinDir = WshSysEnv("WINDIR")

   ' Check to make sure we got the actual path and not an alias
   If InStr (WinDir, ":") <> 0 Then
      Set oFS = CreateObject ("Scripting.FileSystemObject")
      FVersion = oFS.GetFileVersion (WinDir & strFileName)
   Else
      FVersion = ""
   End If

   WinFileVersion = FVersion
End Function


'==========================================================================
'This function returns the index of the test adapter in the adapter list
'
Function GetTestAdapterIndex(pAdapterList, lLastIndex)
   ' Find the adapter from the adapter list that has type 1 => Test Adapter
   Dim lTestId, nCount
   Dim oAdapter

   lTestId = lLastIndex

   For nCount = lLastIndex+1 to pAdapterList.Count
      If (pAdapterList(nCount).AdapterType = 1) Then
         lTestId = nCount
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
   Dim lSuppId, nCount, lFound
   Dim oAdapter

   lSuppId = lLastIndex
   lFound = CLng(0)

   For nCount = lLastIndex+1 To pAdapterList.Count
      If (pAdapterList(nCount).AdapterType = 2) Then

         ' We want to use the first support adapter found if this one is not remote
         If (lFound = 0) Then
            lSuppId = nCount
            lFound = 1
         End If

         If (pAdapterList(nCount).ConnectionId <> 0) Then
            ' This is a remote support adapter, use it
            lSuppId = nCount
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

'==================================================================================================
'/**
' This function will return the instance name from a given GUID. This function can only return 
' the instance name for a local device 
' @params
' ! variant An adapterInfo object from the adapter list or a guid string
' */
Function vbGetInstanceNameFromGuid(byval object)
Dim locator    : Set locator     = CreateObject("WbemScripting.SWbemLocator")
Dim services   : Set services    = locator.ConnectServer ("", "root\wmi")
Dim properties : Set properties  = services.ExecQuery("Select * From MSNdis_EnumerateAdapter")
Dim prop       : Set prop        = Nothing
Dim guid       : guid            = "\Device\"
   
   vbGetInstanceNameFromGuid = ""
   
   If(IsObject(object) = True) Then
      guid = guid & object.GUID
   Else
      guid = guid & object
   End If
    
   For Each prop In properties
      If( StrComp(prop.DeviceName, guid, 1) = 0 ) Then
         vbGetInstanceNameFromGuid = prop.InstanceName
         Exit For
      End If
   Next
   
End Function

'==================================================================================================
'/**
' This function will take a mac address array and convert it to a string
' @params
' ! array Array of 6 bytes to be converted to a MAC address string
' */
Function vbConvertMacAddressArrayToString(byval macAddressArray)
   vbConvertMacAddressArrayToString =       Hex(macAddressArray(0)) &   _
                                      "-" & Hex(macAddressArray(1)) &   _
                                      "-" & Hex(macAddressArray(2)) &   _
                                      "-" & Hex(macAddressArray(3)) &   _
                                      "-" & Hex(macAddressArray(4)) &   _
                                      "-" & Hex(macAddressArray(5))
End Function

'==================================================================================================
'/**
' This function will take a 6 different byte value and return an array of those 6 bytes
' */
Function vbCreateMacAddressArray(byval byte1, byval byte2, byval byte3, byval byte4, byval byte5, byval byte6)

   vbCreateMacAddressArray = Array(CByte(byte1),CByte(byte2),CByte(byte3),CByte(byte4),CByte(byte5),CByte(byte6))
   
End Function

Function vbPercentToPassDirected(nPhysicalMedium)
   Select Case nPhysicalMedium
      Case NDISPHYSICALMEDIUMWIRELESSLAN:
         vbPercentToPassDirected = gWlanPercentToPassDirected
      Case NDISPHYSICALMEDIUMWIRELESSWAN:
         vbPercentToPassDirected = glPercentToPassWWANDirected
      Case NDISPHYSICALMEDIUMPOWERLINE:
         vbPercentToPassDirected = glPercentToPassPowerLineDirected
      Case Else
         vbPercentToPassDirected = glPercentToPass
   End Select
End Function

Function vbPercentToPassMulticast(nPhysicalMedium)
   Select Case nPhysicalMedium
      Case NDISPHYSICALMEDIUMWIRELESSLAN:
         vbPercentToPassMulticast = gWlanPercentToPassBroadcast
      Case NDISPHYSICALMEDIUMWIRELESSWAN:
         vbPercentToPassMulticast = glPercentToPassWWANMulticast
      Case NDISPHYSICALMEDIUMPOWERLINE:
         vbPercentToPassMulticast = glPercentToPassPowerLineMulticast
      Case Else
         vbPercentToPassMulticast = glPercentToPass
   End Select
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


'<!-- CRC = 0xef8cb1d2 --->
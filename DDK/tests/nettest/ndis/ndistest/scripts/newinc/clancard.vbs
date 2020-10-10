Option Explicit

'================================================================================================='
'/**
'This class encapsulates the various operations that can be performed on a LAN NDTCore::Card
'object. It uses functionality provided by the connection less card object and also augments
'it with additional LAN specific functions
'@sa        CLanOpen, CCLCard, COffloadCard
'@date      12/07/2001
'@author    Mitesh Desai
'@alias     miteshd
'*/
Class CLanCard
   Dim m_oCLCard
   
   Private Sub Class_Initialize
      Set m_oCLCard = New CCLCard
   End Sub
   
   Private Sub Class_Terminate
      Set m_oCLCard = Nothing
   End Sub

   '================================================================================================='
   '/**
   '@sa CCard::COMAdapter
   '*/
   Public Property Get COMAdapter
      Set COMAdapter = m_oCLCard.COMAdapter
   End Property
   
   '================================================================================================='
   '/**
   '@sa CCard::AdapterType
   '*/
   Public Property Get AdapterType
      AdapterType = m_oCLCard.AdapterType
   End Property  
   
   '================================================================================================='
   '/**
   '@sa CCard::vbCreateAdapter
   '*/
   Public Function vbCreateAdapter(oCOMAdapter)
      vbCreateAdapter = m_oCLCard.vbCreateAdapter(oCOMAdapter)
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
   '@sa    CLanCard::vbSetupBasicTest, CCLCard::vbCreateOpen, CLanOpen::CLOpen
   '*/
   Public Function vbCreateOpen
      Dim l_oCLOpen
      Set l_oCLOpen = m_oCLCard.vbCreateOpen
      If (l_oCLOpen is Nothing) Then
         Set vbCreateOpen = Nothing
      Else
      
         Dim l_oLanOpen
         
         Set l_oLanOpen          = New CLanOpen
         Set l_oLanOpen.CLOpen   = l_oCLOpen
         Set vbCreateOpen        = l_oLanOpen
            
      End If
      Set l_oCLOpen = Nothing
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::NdisMedium
   '*/
   Public Property Get NdisMedium
      NdisMedium = m_oCLCard.NdisMedium
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
   '@sa  CLanCard::vbCreateOpen, CLanOpen::vbNdisOpen, CLanCard::vbSetupBasicTest
   '*/
   Public Function vbOpenAdapter
   Dim l_oLanOpen
      
      Set l_oLanOpen = Me.vbCreateOpen
                
      If (Not (l_oLanOpen is Nothing)) Then
         If (Not l_oLanOpen.vbNdisOpen) Then
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
   '   Set oTestCard = New CLanCard
   '   Set oTestOpen = oTestCard.vbSetupBasicTest(oNDInfo.AdapterList(lTestAdapterIndex))
   '   If (oTestOpen is Nothing) Then
   '     Exit Function
   '   End If
   '@endcode
   '@sa  CLanCard::vbCreateAdapter, CLanCard::vbCreateOpen, CLanOpen::vbNdisOpen
   '*/
   Public Function vbSetupBasicTest (oCOMAdapter)
      If (Me.vbCreateAdapter(oCOMAdapter)) Then
         Set vbSetupBasicTest = Me.vbOpenAdapter
      Else
         Set vbSetupBasicTest = Nothing
      End If
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::vbNdisIOControl
   '*/
   Public Function vbNdisIOControl(Oid, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
      vbNdisIOControl = m_oCLCard.vbNdisIOControl (Oid, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
   End Function

   '================================================================================================='
   '/**
   '@sa CCard::vbNdisIOControlEx
   '*/
   Public Function vbNdisIOControlEx(Oid, BufferLen, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
      vbNdisIOControlEx = m_oCLCard.vbNdisIOControlEx (Oid, BufferLen, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::vbFastNdisIOControl
   '*/
   Public Function vbFastNdisIOControl(ByVal Oid, ByRef DataBuffer, ByVal QueryMode)
      vbFastNdisIOControl = m_oCLCard.vbFastNdisIOControl (Oid, DataBuffer, QueryMode)
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::vbQueryGuid
   '*/
   Public Function vbQueryGuid (OidGuid, DataBuffer)
      vbQueryGuid = m_oCLCard.vbQueryGuid (OidGuid, DataBuffer)
   End Function

   '================================================================================================='
   '/**
   '@sa CCard::vbWmiRequest
   '*/
   Public Function vbWmiRequest (strGuid, DataBuffer, BufferLength, RequestType, ErrorStatus, nBytesNeeded)
      vbWmiRequest = m_oCLCard.vbWmiRequest (strGuid, DataBuffer, BufferLength, RequestType, ErrorStatus, nBytesNeeded)
   End Function   
   
   
   '================================================================================================='
   '/**
   '@sa CCard::vbGetMaxPacketSize
   '*/
'   Public Function vbGetMaxPacketSize
'      vbGetMaxPacketSize = m_oCLCard.vbGetMaxPacketSize
'   End Function
   
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
'      Select Case m_oCLCard.NdisMedium
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
'         bResult = m_oCLCard.vbFastNdisIOControl(AddrOid, CardAddr, QUERY_GLOBAL_STATS)
'         If (Not bResult) Then
'            call oLog.SafeFailed ("Could not obtain address of " & m_oCLCard.AdapterType, 22866)
'         End If
'      End If
'      
'      vbGetCardAddress = CardAddr
'   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::vbGetPhysicalMedium
   '*/
   Public Function vbGetPhysicalMedium
      vbGetPhysicalMedium = m_oCLCard.vbGetPhysicalMedium
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::vbGetLinkSpeed
   '*/
   Public Function vbGetLinkSpeed
      vbGetLinkSpeed = m_oCLCard.vbGetLinkSpeed
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
      Dim Media
      
      Media = m_oCLCard.NdisMedium
      
      Select Case Media
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
   
   '================================================================================================='
   '/**
   '@sa CCard::vbWaitForLink
   '*/
   Public Function vbWaitForLink(WaitTime)
      vbWaitForLink = m_oCLCard.vbWaitForLink(WaitTime)
   End Function

   '============================================================================================='
   '/**
   '@sa CCard::vbWaitForLinkWithDelay
   '*/
   Function vbWaitForLinkWithDelay(WaitTime, ExtraWaitDelay)
      vbWaitForLinkWithDelay = m_oCLCard.vbWaitForLinkWithDelay(WaitTime, ExtraWaitDelay)
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
      bResult = m_oCLCard.vbFastNdisIOControl(OID_PNP_CAPABILITIES, Levels, QUERY_GLOBAL_STATS)
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


'<!-- CRC = 0xabff9a22 --->
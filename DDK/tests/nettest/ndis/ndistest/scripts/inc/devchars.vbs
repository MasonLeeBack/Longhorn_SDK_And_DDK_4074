''==========================================================================
'
' COMMENT: Gets the required characteristics of the adapter. 
'          If the Err.Raise is called, then it means the VBScript code is
'          not calling the function properly
'
'==========================================================================
Option Explicit

'==========================================================================
'
' A local function that takes a filter and open test card, tries to set that
' that filter, and returns the status obtained by the NdisRequest
'
Function DoSetPacketFilter(ParamFilterType, oTestOpen)
    Dim BytesWritten, BytesNeeded
    Dim NdisStatus
    Dim FilterType
    FilterType = ParamFilterType ' Do this because NdisRequest can change it
    
    BytesWritten = CLng(0)
    BytesNeeded = CLng(0)
    
    DoSetPacketFilter = oTestOpen.NdisRequest( _
                OID_GEN_CURRENT_PACKET_FILTER, _
                FilterType, _
                4, _
                REQUEST_SET_INFO, _
                BytesWritten, _
                BytesNeeded, _
                NdisStatus)
    
    If (DoSetPacketFilter AND NdisStatus <> 0) Then
        DoSetPacketFilter = FALSE
    End If
    
End Function

'==========================================================================
'
' Gets all the filters supported by the card. The only way to obtain this
' list is to try setting a filter, and if it suceeds, the filter is assumed
' to be supported, else not.
'
Function GetFilters(oTestCard, oTestOpen)
    Dim bResult
    Dim locFilters
    Dim Media
    
    Media = oTestCard.GetNdisMedium()
    
    locFilters = CLng(0)     
    If (Media = NDISMEDIUM802_3) Then
        locFilters = DIRECTED + BROADCAST + MULTICAST
        
        bResult = DoSetPacketFilter(ALL_MULTICAST, oTestOpen)
        If (bResult) Then
            locFilters = locFilters + ALL_MULTICAST
        End If
    ElseIf (Media = NDISMEDIUM802_5) Then
        locFilters = DIRECTED + BROADCAST + FUNCTIONAL + GROUP_PKT
        
        bResult = DoSetPacketFilter(ALL_FUNCTIONAL, oTestOpen)
        If (bResult) Then
            locFilters = locFilters + ALL_FUNCTIONAL
        End If
        
        bResult = DoSetPacketFilter(SOURCE_ROUTING, oTestOpen)
        If (bResult) Then
            locFilters = locFilters + SOURCE_ROUTING
        End If
        
        bResult = DoSetPacketFilter(MAC_FRAME, oTestOpen)
        If (bResult) Then
            locFilters = locFilters + MAC_FRAME
        End If
        
    ElseIf (Media = NDISMEDIUMFDDI) Then
        locFilters = DIRECTED + BROADCAST + MULTICAST
        
        bResult = DoSetPacketFilter(ALL_MULTICAST, oTestOpen)
        If (bResult) Then
            locFilters = locFilters + ALL_MULTICAST
        End If
        
        bResult = DoSetPacketFilter(SOURCE_ROUTING, oTestOpen)
        If (bResult) Then
            locFilters = locFilters + SOURCE_ROUTING
        End If
        
        bResult = DoSetPacketFilter(MAC_FRAME, oTestOpen)
        If (bResult) Then
            locFilters = locFilters + MAC_FRAME
        End If
        
        bResult = DoSetPacketFilter(SMT, oTestOpen)
        If (bResult) Then
            locFilters = locFilters + SMT
        End If
    End If
    
    bResult = DoSetPacketFilter(PROMISCUOUS, oTestOpen)
    If (bResult) Then
        locFilters = locFilters + PROMISCUOUS
    Else
        Dim lPhysicalMedium
        lPhysicalMedium = oTestCard.GetPhysicalMedium()
        ' We are supporting only NDIS version 5
        If (lPhysicalMedium <> NDISPHYSICALMEDIUMWIRELESSLAN And lPhysicalMedium <> NDISPHYSICALMEDIUMCABLEMODEM) Then
            call oLog.Failed ("Promiscuous mode support is required for NDIS 5 drivers." , 22860)
        End If
    End If
    
    bResult = DoSetPacketFilter(ALL_LOCAL, oTestOpen)
    If (bResult) Then
        locFilters = locFilters + ALL_LOCAL
    End If
    
    bResult = DoSetPacketFilter(CLng(0), oTestOpen)
    If (Not bResult) Then
        call oLog.Failed ("Unable to reset filter type to NONE" , 22861)
    End If
    
    GetFilters = locFilters
End Function


'==========================================================================
'
' Returns the maximum total packet length in bytes that the NIC supports
'
Function GetMaxPacketSize(oTestCard, oLog)  
    Dim ulOid
    Dim bResult
    Dim mMaxTotalSize
    
    ulOid = OID_GEN_MAXIMUM_TOTAL_SIZE
    
    If oTestCard is Nothing Then
        Err.Raise 32000, "MaxPacketSize", _
        "Require a test card to query"
    End If
    
    If oLog is Nothing Then
        Err.Raise 32000, "MaxPacketSize", _
        "Require a log file"
    End If
    
    bResult = oTestCard.QueryInfo(ulOid, mMaxTotalSize)
    If(bResult) Then
        If (mMaxTotalSize < 40) Then
            call oLog.Failed ("Invalid value received from test card for maximum total size" , 22862)
            mMaxTotalSize = 50
        End If
    Else
        call oLog.Failed ("Unable to get maximum total size from test card" , 22863)
        mMaxTotalSize = 50
    End If
    
    GetMaxPacketSize = mMaxTotalSize
End Function


'==========================================================================
'
' Returns the address that the NIC is currently using
'
Function GetCardAddress(oCard, oLog, Media)
    Dim CardAddr, bResult
    CardAddr = NullAddr()
    
    If (Media < 0) Then
        Err.Raise 32000, "GetCardAddress", _
        "Media not found yet"
    End If
    
    Select Case Media
        Case NDISMEDIUM802_3
            bResult = oCard.QueryInfo(OID_802_3_CURRENT_ADDRESS, CardAddr)
            If (Not bResult) Then
                call oLog.Failed ("Could not obtain address of card" , 22866)
            End If
        Case NDISMEDIUM802_5
            bResult = oCard.QueryInfo(OID_802_5_CURRENT_ADDRESS, CardAddr)
            If (Not bResult) Then
                call oLog.Failed ("Could not obtain address of card" , 22867)
            End If
        Case NDISMEDIUMFDDI
            bResult = oCard.QueryInfo(OID_FDDI_LONG_CURRENT_ADDR, CardAddr)
            If (Not bResult) Then
                call oLog.Failed ("Could not obtain address of card" , 22868)
            End If
        Case Else
            ' fail silently because this is caused during initialization
            ' call oLog.Failed ("GetCardAddress: Unknown media" , 22869)
    End Select
    GetCardAddress = CardAddr
End Function


'<!-- CRC = 0xd0a5b54b --->
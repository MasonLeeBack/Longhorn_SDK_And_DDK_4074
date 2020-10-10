Option Explicit

Function NullAddr()
   NullAddr = Array(CByte(0), CByte(0), CByte(0), _
   CByte(0), CByte(0), CByte(0))
End Function

Function NetAddr(val0, val1, val2, val3, val4, val5)
   NetAddr = Array(CByte(val0), CByte(val1), CByte(val2), _
   CByte(val3), CByte(val4), CByte(val5))
End Function

Function NetPrefix(val0, val1, val2, val3, val4, val5, val6, _
val7, val8, val9, val10, val11, val12)
   NetPrefix = Array(CByte(val0), CByte(val1), CByte(val2), _
   CByte(val3), CByte(val4), CByte(val5), CByte(val6), CByte(val7), CByte(val8), _
   CByte(val9), CByte(val10), CByte(val11), CByte(val12))
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
Function NetAddrCmpI(NetAddr1, NetAddr2, Index)
   If ( (NetAddr1(Index + 0) = NetAddr2(0)) And _
        (NetAddr1(Index + 1) = NetAddr2(1)) And _
        (NetAddr1(Index + 2) = NetAddr2(2)) And _
        (NetAddr1(Index + 3) = NetAddr2(3)) And _
        (NetAddr1(Index + 4) = NetAddr2(4)) And _                
        (NetAddr1(Index + 5) = NetAddr2(5)) ) Then
      NetAddrCmpI = TRUE
   Else
      NetAddrCmpI = FALSE     
   End If
End Function


   
'==========================================================================
Function SetPacketFilter(oTestOpen, ParamNewFilter)
   Dim BytesWritten, BytesNeeded, NdisStatus
   Dim NewFilter

   NewFilter = ParamNewFilter ' Do this because NdisRequest can change it
   
  If (oTestOpen is Nothing) Then
      Err.Raise 32000, "SetPacketFilter", _
          "Require an open adapter instance"
   End If

   BytesWritten = CLng(0)
   BytesNeeded = CLng(0)

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
Function SetLookahead(oTestOpen, ParamLookahead)
   Dim BytesWritten, BytesNeeded, NdisStatus
   Dim Lookahead

   Lookahead = ParamLookahead ' Do this because NdisRequest can change it
   
   If (oTestOpen is Nothing) Then
      Err.Raise 32000, "SetLookahead", _
          "Require an open adapter instance"
   End If

   BytesWritten = CLng(0)
   BytesNeeded = CLng(0)

   SetLookahead = oTestOpen.NdisRequest( _
      OID_GEN_CURRENT_LOOKAHEAD, _
      Lookahead, _
      4, _
      REQUEST_SET_INFO, _
      BytesWritten, _
      BytesNeeded, _
      NdisStatus)

   If (Not SetLookahead) Then
      Call oLog.Write("NdisRequest failed during OID_GEN_CURRENT_LOOKAHEAD" )
   ElseIf (NdisStatus <> 0) Then
      SetLookahead = FALSE
      oLog.Write("NdisRequest OID_GEN_CURRENT_LOOKAHEAD returned NdisStatus " & hex(NdisStatus) )
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
' This function, prints the information obtained from the query
' of the oid into the log file. 
' It takes the open instances of the adapter to query, and the
' oid to query for
Function GetQueryInfo(oTestOpen, ulOid)
   Dim BytesWritten, BytesNeeded, NdisStatus
   Dim ResultBuffer()
   Dim BufferSize
   Dim bResult
   
   BufferSize=256
   ReDim ResultBuffer(BufferSize)
   
   BytesWritten = CLng(0)
   BytesNeeded = CLng(0)

   bResult = oTestOpen.NdisRequest( _
      ulOid, _
      ResultBuffer, _
      BufferSize, _
      REQUEST_QUERY_INFO, _
      BytesWritten, _
      BytesNeeded, _
      NdisStatus)

   If (Not bResult) Then
      If (BytesNeeded <> 0) Then
         '
         ' Did not allocate enough space for the buffer. Try again
         '
         oLog.Write("Retrying after allocating a larger size for the buffer" )
         BufferSize = 256+BytesNeeded
         ReDim ResultBuffer(BufferSize)
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)

         bResult = oTestOpen.NdisRequest( _
            ulOid, _
            ResultBuffer, _
            BufferSize, _
            REQUEST_QUERY_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus)
      End If
   End If

   GetQueryInfo = bResult
End Function
'-----------------------------------------------------
' Function:    WaitForLink
' Arguments:   WorkCard : Test card
'              oNDTLog     : Log file to use
'
' Loop until link is established or 1 minute
'
'-----------------------------------------------------
Function WaitForLink(WorkCard, oLog)
   Dim ConnectStatus
   Dim Connected
   Dim lCount
   Dim bResult
   Dim bReturnVal

   ConnectStatus = 0
   Connected = 0
   lCount = 0

   bReturnVal = FALSE
   Do While(TRUE)
      Wscript.Sleep 1000
      bResult = WorkCard.QueryInfo(OID_GEN_MEDIA_CONNECT_STATUS, ConnectStatus)
      If (Not bResult) Then
         call oLog.Failed ("Unable to query media connect status" , 22767)
         Exit Do
      ElseIf (ConnectStatus = Connected) Then
         bReturnVal = TRUE
         Exit Do
      End If

      If(lCount = 90) Then
         call oLog.Failed ("Link is not established within 90 seconds", 22768)
         Exit Do
      End If

      lCount = lCount + 1
   Loop
   WaitForLink = bReturnVal
End Function

Function GetMaximumVCs(WorkCard, bIsADSL, oLog)
    Dim ulOid
    Dim lMaxVCs
    Dim bResult

    ulOid = OID_ATM_MAX_ACTIVE_VCS
    bResult = WorkCard.QueryInfo(ulOid, lMaxVCs, 4)
    If(bResult) Then 
        oLog.Write("Maximum Active VCs = " & lMaxVCs )
    End If

    If (bIsADSL = 1) Then
        if (lMaxVCs < 4) Then
            call oLog.Failed ("Not enough VCs available to run ADSL certification test", 22769)
            oLog.Write("Minimum requirement is 4")
            lMaxVCs = 0
        Else
            lMaxVCs = lMaxVCs - 2
        End If
    Else
        if (lMaxVCs < 12) Then
            call oLog.Failed ("Not enough VCs available to run certification test", 22770)
            oLog.Write("Card must be certified as ATMLANE only")
            lMaxVCs = 0
        End If
        lMaxVCs = lMaxVCs - 7
    End If

   GetMaximumVCs = lMaxVCs
End Function
	

'==========================================================================
'
' Obtains the medium currently in use by the NIC
'
Function GetMedia(oTestCard, oLog)
   Dim arrMedia()
   Dim bResult
   Dim ulOid
   Dim Media

   Media = CLng(0)

   If oTestCard is Nothing Then
      Err.Raise 32000, "Media", _
             "Require a test card to query"
   End If

   If oLog is Nothing Then
      Err.Raise 32000, "Media", _
             "Require a log file"
   End If

   ulOid = OID_GEN_MEDIA_IN_USE
   bResult = oTestCard.QueryInfo(ulOid, arrMedia)
   If(bResult) Then
      Media = arrMedia(0)
   End If


   GetMedia = Media
End Function

'==========================================================================
'
' Obtains the physical medium supported by the NIC
'
Function GetPhysicalMedium(oTestCard, oLog)
   Dim arrMedia()
   Dim bResult
   Dim ulOid
   Dim Media

   Media = CLng(0)

   If oTestCard is Nothing Then
      Err.Raise 32000, "PhysicalMedium", _
             "Require a test card to query"
   End If

   If oLog is Nothing Then
      Err.Raise 32000, "PhysicalMedium", _
             "Require a log file"
   End If

   ulOid = OID_GEN_PHYSICAL_MEDIUM
   bResult = oTestCard.QueryInfo(ulOid, arrMedia)
   If(bResult) Then
      Media = arrMedia(0)
   End If


   GetPhysicalMedium = Media
End Function

'==========================================================================
'
' Obtains the Maximum Packet size supported by the NIC
'
Function GetAAL5MaxPacketSize(oTestCard, oLog)
   Dim bResult
   Dim ulOid
   Dim MaxPacketSize

   If oTestCard is Nothing Then
      Err.Raise 32000, "MaxPacketSize", _
             "Require a test card to query"
   End If

   If oLog is Nothing Then
      Err.Raise 32000, "MaxPacketSize", _
             "Require a log file"
   End If

   ulOid = OID_ATM_MAX_AAL5_PACKET_SIZE
   bResult = oTestCard.QueryInfo(ulOid, MaxPacketSize, 4)
   If(bResult) Then 
       oLog.Write("MaxPacketSize = " & MaxPacketSize )
   End If

   GetAAL5MaxPacketSize = MaxPacketSize
End Function

'==========================================================================
'
' Obtains the service type supported by the NIC
'
Function GetServiceType(oTestCard, oLog)
   Dim bResult
   Dim ulOid
   Dim ServiceType
   Dim arrService()

   If oTestCard is Nothing Then
      Err.Raise 32000, "ServiceType", _
             "Require a test card to query"
   End If

   If oLog is Nothing Then
      Err.Raise 32000, "ServiceType", _
             "Require a log file"
   End If

   ulOid = OID_ATM_SUPPORTED_SERVICE_CATEGORY
   bResult = oTestCard.QueryInfo(ulOid, arrService)
   If(bResult) Then
        ServiceType = arrService(0)
   End If

   GetServiceType = ServiceType
End Function
'==========================================================================
'
' Sets the Send and Receive FlowSpecs for a particular CALL Type
'
Function SetFlowSpecs(oTestCard, SendFlowSpec, RecvFlowSpec, uCallType, bIsAdsl)
    Dim bResult
    Dim ulOid 
    Dim MaxPacketSize

    Dim arrLinkSpeed(2)
    Dim PeakSendBandwidth, PeakRecvBandwidth


    ulOid = OID_ATM_MAX_AAL5_PACKET_SIZE
    bResult = oTestCard.QueryInfo(ulOid, MaxPacketSize, 4)
    If(bResult) Then
        oLog.Write("MaxPacketSize = " & MaxPacketSize )
    End If


    arrLinkSpeed(0) = CLng(0)
    arrLinkSpeed(1) = CLng(0)

    ulOid = OID_GEN_CO_LINK_SPEED
    bResult = oTestCard.QueryInfo(ulOid, arrLinkSpeed, 8)
    If(bResult) Then 
        PeakSendBandwidth = arrLinkSpeed(0) * 12.5   ' why? 
        PeakRecvBandwidth = arrLinkSpeed(1) * 12.5   ' why? 
    Else
        PeakSendBandwidth = 10000 
        PeakRecvBandwidth = 10000 
    End If

    if (uCallType = 0) Then
        '
        ' ubr low speed send
        '
        SendFlowSpec.TokenRate        =  100000
        SendFlowSpec.PeakBandwidth    =  240000
        SendFlowSpec.TokenBucketSize  =  4096
        SendFlowSpec.ServiceType      =  BEST_EFFORT
        SendFlowSpec.MaxSduSize       =  4096

        '
        ' ubr low speed recv
        '
        RecvFlowSpec.TokenRate        =  100000
        RecvFlowSpec.TokenBucketSize  =  4096
        RecvFlowSpec.PeakBandwidth    =  240000
        RecvFlowSpec.ServiceType      =  BEST_EFFORT
        RecvFlowSpec.MaxSduSize       =  4096

        '
        ' adjust these flowspecs for adsl, if necessary
        '
        if (bIsAdsl = 1) Then
            if (( PeakSendBandwidth / 4) < 100000) Then
                SendFlowSpec.TokenRate  = PeakSendBandwidth / 4
                RecvFlowSpec.TokenRate  = PeakSendBandwidth / 4
            End If
   	    if (( PeakSendBandwidth / 2) < 240000) Then
                SendFlowSpec.PeakBandwidth = PeakSendBandwidth / 2
                RecvFlowSpec.PeakBandwidth = PeakSendBandwidth / 2
            End If
        End If
    End If

    if (uCallType = 1) Then
        '
        ' ubr high speed send
        '
        SendFlowSpec.TokenRate        =  100000
        SendFlowSpec.PeakBandwidth    =  PeakSendBandwidth
        SendFlowSpec.TokenBucketSize  =  32768
        SendFlowSpec.ServiceType      =  BEST_EFFORT
        SendFlowSpec.MaxSduSize       =  MaxPacketSize

        '
        ' ubr high speed recv
        '
        RecvFlowSpec.TokenRate        =  100000
        RecvFlowSpec.TokenBucketSize  =  32768
        RecvFlowSpec.PeakBandwidth    =  PeakRecvBandwidth
        RecvFlowSpec.ServiceType      =  BEST_EFFORT
        RecvFlowSpec.MaxSduSize       =  MaxPacketSize

        '
        ' adjust these flowspecs for adsl, if necessary
        '
        if (bIsAdsl = 1) Then
            SendFlowSpec.TokenRate  =  PeakSendBandwidth / 2
            RecvFlowSpec.TokenRate  =  PeakSendBandwidth / 2
            RecvFlowSpec.PeakBandwidth = PeakSendBandwidth 
        End If
    End If

    if (uCallType = 2) Then
        '
        ' cbr low speed send
        '
        SendFlowSpec.TokenRate        =  10000
        SendFlowSpec.PeakBandwidth    =  10000
        SendFlowSpec.TokenBucketSize  =  4096
        SendFlowSpec.ServiceType      =  GUARANTEED
        SendFlowSpec.MaxSduSize       =  4096

        '
        ' cbr low speed recv
        '
        RecvFlowSpec.TokenRate        =  10000
        RecvFlowSpec.TokenBucketSize  =  4096
        RecvFlowSpec.PeakBandwidth    =  10000
        RecvFlowSpec.ServiceType      =  GUARANTEED
        RecvFlowSpec.MaxSduSize       =  4096

        '
        ' adjust these flowspecs for adsl, if necessary
        '
        if (bIsAdsl = 1) Then
            if (( PeakSendBandwidth / 10) < 10000) Then
                SendFlowSpec.TokenRate  =  PeakSendBandwidth / 10
                RecvFlowSpec.TokenRate  =  PeakSendBandwidth / 10
                SendFlowSpec.PeakBandwidth =  PeakSendBandwidth / 10
                RecvFlowSpec.PeakBandwidth =  PeakSendBandwidth / 10
            End If
        End If
    End If

    if (uCallType = 3) Then
        '
        ' cbr high speed send
        '
        SendFlowSpec.TokenRate        =  100000
        SendFlowSpec.PeakBandwidth    =  100000
        SendFlowSpec.TokenBucketSize  =  32768
        SendFlowSpec.ServiceType      =  GUARANTEED
        SendFlowSpec.MaxSduSize       =  MaxPacketSize

        '
        ' cbr high speed recv
        '
        RecvFlowSpec.TokenRate        =  100000
        RecvFlowSpec.TokenBucketSize  =  32768
        RecvFlowSpec.PeakBandwidth    =  100000
        RecvFlowSpec.ServiceType      =  GUARANTEED
        RecvFlowSpec.MaxSduSize       =  MaxPacketSize

        '
        ' adjust these flowspecs for adsl, if necessary
        '
        if (bIsAdsl = 1) Then
            SendFlowSpec.TokenRate  =  PeakSendBandwidth / 2
            SendFlowSpec.PeakBandwidth = PeakSendBandwidth / 2
            RecvFlowSpec.TokenRate  =  PeakSendBandwidth / 2
            RecvFlowSpec.PeakBandwidth = PeakSendBandwidth / 2
        End If
    End If

    if (uCallType = 4) Then
        '
        ' ubr high speed send
        '
        SendFlowSpec.TokenRate        =  100000
        SendFlowSpec.PeakBandwidth    =  PeakSendBandwidth
        SendFlowSpec.TokenBucketSize  =  32768
        SendFlowSpec.ServiceType      =  BEST_EFFORT
        SendFlowSpec.MaxSduSize       =  MaxPacketSize

        '
        ' No Reverse Traffic
        '
        RecvFlowSpec.TokenRate        =  100000
        RecvFlowSpec.TokenBucketSize  =  4096
        RecvFlowSpec.PeakBandwidth    =  240000
        RecvFlowSpec.ServiceType      =  NO_TRAFFIC
        RecvFlowSpec.MaxSduSize       =  4096

        '
        ' adjust these flowspecs for adsl, if necessary
        '
        if (bIsAdsl = 1) Then
            if (( PeakSendBandwidth / 4) < 100000) Then
                RecvFlowSpec.TokenRate  = PeakSendBandwidth / 4
            End If
   	    if (( PeakSendBandwidth / 2) < 240000) Then
                RecvFlowSpec.PeakBandwidth = PeakSendBandwidth / 2
            End If
            SendFlowSpec.TokenRate  =  PeakSendBandwidth / 2
        End If
    End If

    if (uCallType = 5) Then
        '
        ' No Forward Traffic
        '
        SendFlowSpec.TokenRate        =  100000
        SendFlowSpec.PeakBandwidth    =  240000
        SendFlowSpec.TokenBucketSize  =  4096
        SendFlowSpec.ServiceType      =  NO_TRAFFIC
        SendFlowSpec.MaxSduSize       =  4096

        '
        ' ubr high speed recv
        '
        RecvFlowSpec.TokenRate        =  100000
        RecvFlowSpec.TokenBucketSize  =  32768
        RecvFlowSpec.PeakBandwidth    =  PeakRecvBandwidth
        RecvFlowSpec.ServiceType      =  BEST_EFFORT
        RecvFlowSpec.MaxSduSize       =  MaxPacketSize

        '
        ' adjust these flowspecs for adsl, if necessary
        '
        if (bIsAdsl = 1) Then
            if (( PeakSendBandwidth / 4) < 100000) Then
                SendFlowSpec.TokenRate  = PeakSendBandwidth / 4
            End If
   	    if (( PeakSendBandwidth / 2) < 240000) Then
                SendFlowSpec.PeakBandwidth = PeakSendBandwidth / 2
            End If
            RecvFlowSpec.TokenRate  =  PeakSendBandwidth / 2
            RecvFlowSpec.PeakBandwidth = PeakSendBandwidth
        End If
    End If

End Function
'==========================================================================
'
' Obtains the maximum calls supported by the NIC for specific call type
'
Function GetMaxCalls(oTestCard, oLog, uCallType)
    Dim bResult
    Dim MaxCalls,SuccessfulCalls,FailedCalls
    Dim Count
    Dim MaxAllowCBR,MaxUBRCalls,MaxCBRCalls
    Dim MaxVCs
    Dim ServiceType
    Dim PhyMedium,bIsAdsl

    Const CONSTANT_BIT_RATE = &H00000001
    Const VARIABLE_BIT_RATE = &H00000002
    Const UNSPECIFIED_BIT_RATE = &H00000004
    Const AVAILABLE_BIT_RATE = &H00000008


    Dim VC_Array(),SAP_Array1()
    Dim NetPrefixOne, NetAddrOne

    Dim OpenOne,bForceNdis30,Medium


    NetPrefixOne = NetPrefix(&H00&, &H00&, &H00&, &H00&, &H00&, &H00&, &H00&, &H00&, &H00&, &H00&, &H00&, &H00&, &H00&)
    NetAddrOne   = NetAddr(&H00&, &H00&, &H00&, &H00&, &H00&, &H00&)


    MaxCalls = 0
    SuccessfulCalls = 0
    MaxAllowCBR = 0

    If oTestCard is Nothing Then
    Err.Raise 32000, "MaxCalls", _
         "Require a test card to query"
    End If

    If oLog is Nothing Then
    Err.Raise 32000, "MaxCalls", _
         "Require a log file"
    End If

    PhyMedium = GetPhysicalMedium(oTestCard, oLog)
    if PhyMedium = NDISPHYSICALMEDIUMDSL Then
        bIsAdsl = 1
    Else
        bIsAdsl = 0
    End If

    ServiceType = GetServiceType(oTestCard, oLog)
    MaxVCs = GetMaximumVCs(oTestCard, bIsAdsl, oLog)

    MaxUBRCalls = 256
    MaxAllowCBR = 256

    If (MaxUBRCalls > (MaxVCs / 2)) Then
        MaxUBRCalls = MaxVCs / 2
    End If

    ReDim VC_Array(MaxUBRCalls)
    ReDim SAP_Array1(MaxUBRCalls)

    If ServiceType AND CONSTANT_BIT_RATE = 1 Then
        If (MaxUBRCalls > MaxAllowCBR) Then
            MaxCBRCalls = MaxAllowCBR
        Else
            MaxCBRCalls = MaxUBRCalls
        End If
    End If

    oLog.Variation("CreateOpen")
    Set OpenOne = oTestCard.CreateOpen()
    If(OpenOne is Nothing) Then
        call oLog.Failed ("Failed to create open object on test adapter!", 22771)
        WScript.Quit
    End If
        
    bForceNdis30 = False
    Medium = GetMedia(oTestCard, oLog)
        
    oLog.Variation("NdisOpen")
    ' Create binding on Test Adapter 
    bResult = OpenOne.NdisOpen(Medium, bForceNdis30)
    If(Not bResult) Then
        call oLog.Failed ("Failed to create binding on Test Adapter !!!", 22772)
        WScript.Quit  
    End If
        

    oLog.Variation("OpenAddressFamily")
    ' Open Address Family
'    bResult = OpenOne.OpenAddressFamily(ADDRESS_FAMILY_Q2931, 3, 1)
    bResult = OpenOne.OpenAddressFamily(1, 3, 1)
    If(Not bResult) Then
        call oLog.Failed ("Failed to open address family on Test Adapter !!!", 22773)
        WScript.Quit  
    End If

    oLog.Variation("GetAtmAddress")
    ' Get ATM address
    bResult = OpenOne.GetAtmAddress(0, NetPrefixOne, NetAddrOne)
    If(Not bResult) Then
        call oLog.Failed ("Failed to get ATM address of Test Adapter !!!", 22774)
        WScript.Quit  
    End If


    Dim SendFlowSpec,RecvFlowSpec

    Set SendFlowSpec = oNDTCore.CreateFlowSpec()
    Set RecvFlowSpec = oNDTCore.CreateFlowSpec()

    SetFlowSpecs oTestCard,SendFlowSpec,RecvFlowSpec,uCallType,bIsAdsl 

    if ((uCallType = 1) OR (uCallType = 0)) Then
	MaxCalls = MaxUBRCalls
    End If

    if ((uCallType = 2) OR (uCallType = 3)) Then
	MaxCalls = MaxCBRCalls
    End If

    Count = 0
    Do While (Count < MaxCalls)
        Set SAP_Array1(Count) = Nothing
        Set VC_Array(Count) = Nothing
	
        Count = Count + 1
    Loop

    Count = 0
    SuccessfulCalls = 0
    FailedCalls = 0

    Do While (Count < MaxCalls)
        Set SAP_Array1(Count) = OpenOne.AfOpenSap(Count)
        If (SAP_Array1(Count) is Nothing) Then
            Exit Do
        End If

        Set VC_Array(Count) = OpenOne.AfCreateVc()
        If (VC_Array(Count) is Nothing) Then
            SAP_Array1(Count).AfCloseSap()
            Exit Do
        End If

        bResult = VC_Array(Count).MakeCall(NetPrefixOne, NetAddrOne, Count, SendFlowSpec, RecvFlowSpec)

        if (bResult) Then
            SuccessfulCalls = SuccessfulCalls + 1
        Else
            FailedCalls = FailedCalls + 1
            VC_Array(Count).AfDeleteVC()
	    Set VC_Array(Count) = Nothing
        End If 

        If (FailedCalls >= 5) Then
            Exit Do
        End IF

        Count = Count + 1
    Loop

    Count = 0
    Do While (Count < MaxCalls)
        If (Not(VC_Array(Count)) is Nothing) Then
            VC_Array(Count).CloseCall()
            VC_Array(Count).AfDeleteVc()
            Set VC_Array(Count) = Nothing
        End IF
        Count = Count + 1
    Loop

    WScript.Sleep(5000)

    Count = 0
    Do While (Count < MaxCalls)
        If (Not(SAP_Array1(Count)) is Nothing) Then
            SAP_Array1(Count).AfCloseSap()
            Set SAP_Array1(Count) = Nothing
        End IF
        Count = Count + 1
    Loop

    oLog.Write("Successfully made " & SuccessfulCalls & " calls" )

    OpenOne.CloseAddressFamily()
    oLog.Variation("NdisClose")
    OpenOne.NdisClose()
    Set OpenOne = Nothing

    GetMaxCalls = SuccessfulCalls

End Function

'<!-- CRC = 0x3bfc0be5 --->
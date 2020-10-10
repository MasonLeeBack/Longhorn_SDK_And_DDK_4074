Option Explicit

Dim GlobTaskOffloadSupport, GlobSnapTaskOffloadSupport, GlobUnspecEncapTaskOffloadSupport
Dim GlobCksumTasks, GlobSnapCksumTasks, GlobUnspecEncapCksumTasks
Dim GlobLargeSendTasks, GlobSnapLargeSendTasks, GlobUnspecEncapLargeSendTasks
Dim GlobIpsecOffloadTasks, GlobSnapIpsecOffloadTasks, GlobUnspecEncapIpsecOffloadTasks
Dim GlobCksumOffloadInfo(5), GlobSnapCksumOffloadInfo(5), GlobUnspecEncapCksumOffloadInfo(5)
Dim GlobLargeSendOffloadInfo(5), GlobSnapLargeSendOffloadInfo(5), GlobUnspecEncapLargeSendOffloadInfo(5)
Dim GlobIpsecOffloadInfo(5), GlobSnapIpsecOffloadInfo(5), GlobUnspecEncapIpsecOffloadInfo(5)

GlobTaskOffloadSupport = CBool(FALSE)
GlobSnapTaskOffloadSupport = CBool(FALSE)
GlobUnspecEncapTaskOffloadSupport = CBool(FALSE)
GlobCksumTasks = CLng(0)
GlobSnapCksumTasks = CLng(0)
GlobUnspecEncapCksumTasks = CLng(0)
GlobLargeSendTasks = CLng(0)
GlobSnapLargeSendTasks = CLng(0)
GlobUnspecEncapLargeSendTasks = CLng(0)
GlobIpsecOffloadTasks = CLng(0)
GlobSnapIpsecOffloadTasks = CLng(0)
GlobUnspecEncapIpsecOffloadTasks = CLng(0)

'================================================================
'
' This function compares two IPSecOffloadStat objects and
' returns true if they are equal
'

Function CompareIPSecStats (stat1, stat2)
    if (stat1.NumBytesAuthTx <> stat2.NumBytesAuthTx) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumBytesAuthRx <> stat2.NumBytesAuthRx) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumBytesConfTx <> stat2.NumBytesConfTx) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumBytesConfRx <> stat2.NumBytesConfRx) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsRxUnknown <> stat2.NumPktsRxUnknown) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsCryptoDone <> stat2.NumPktsCryptoDone) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsNextCryptoDone <> stat2.NumPktsNextCryptoDone) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsSADeleteRequest <> stat2.NumPktsSADeleteRequest) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsGenericError <> stat2.NumPktsGenericError) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsTransportAHAuthFailed <> stat2.NumPktsTransportAHAuthFailed) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsTransportESPAuthFailed <> stat2.NumPktsTransportESPAuthFailed) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsTunnelAHAuthFailed <> stat2.NumPktsTunnelAHAuthFailed) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsTunnelESPAuthFailed <> stat2.NumPktsTunnelESPAuthFailed) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsInvalidPktSyntax <> stat2.NumPktsInvalidPktSyntax) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsInvalidProtocol <> stat2.NumPktsInvalidProtocol) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsStatusUnknown <> stat2.NumPktsStatusUnknown) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsCryptoNotDone <> stat2.NumPktsCryptoNotDone) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsIPAddrMismatch <> stat2.NumPktsIPAddrMismatch) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsPortMismatch <> stat2.NumPktsPortMismatch) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsBadSPI <> stat2.NumPktsBadSPI) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsBadOperation <> stat2.NumPktsBadOperation) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsBadSeqNum <> stat2.NumPktsBadSeqNum) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsBadOptionLen <> stat2.NumPktsBadOptionLen) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsBadOptions <> stat2.NumPktsBadOptions) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsMalformedHeader <> stat2.NumPktsMalformedHeader) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsAHESPUnexpected <> stat2.NumPktsAHESPUnexpected) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsProtocolUnexpected <> stat2.NumPktsProtocolUnexpected) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsMalformedPayload <> stat2.NumPktsMalformedPayload) Then
        CompareIPSecStats = false
    ElseIf (stat1.NumPktsNoIPSecPerPktInfo <> stat2.NumPktsNoIPSecPerPktInfo) Then
        CompareIPSecStats = false
    Else
        CompareIPSecStats = true
    End If
End Function



'================================================================
'
' This function coverts an IPSecStat object to a string
' Used to print IP Sec data onto Log
'

Function IPSecStatsToString (IPSecStat)
    Dim Output
    Output = "  (IP Security Statistics=>" & vblf 
    Output = Output & "	NumBytesAuthTx                   = " & IpSecStat.NumBytesAuthTx & vblf
    Output = Output & "	NumBytesAuthRx                   = " & IpSecStat.NumBytesAuthRx & vblf
    Output = Output & "	NumBytesConfTx                   = " & IpSecStat.NumBytesConfTx & vblf
    Output = Output & "	NumBytesConfRx                   = " & IpSecStat.NumBytesConfRx & vblf
    Output = Output & "	NumPktsRxUnknown                 = " & IpSecStat.NumPktsRxUnknown & vblf
    Output = Output & "	NumPktsCryptoDone                = " & IpSecStat.NumPktsCryptoDone & vblf
    Output = Output & "	NumPktsNextCryptoDone            = " & IpSecStat.NumPktsNextCryptoDone & vblf
    Output = Output & "	NumPktsSADeleteRequest           = " & IpSecStat.NumPktsSADeleteRequest & vblf
    Output = Output & "	NumPktsCryptoSuccess             = " & IpSecStat.NumPktsCryptoSuccess & vblf
    Output = Output & "	NumPktsGenericError              = " & IpSecStat.NumPktsGenericError & vblf
    Output = Output & "	NumPktsTransportAHAuthFailed     = " & IpSecStat.NumPktsTransportAHAuthFailed & vblf
    Output = Output & "	NumPktsTransportESPAuthFailed    = " & IpSecStat.NumPktsTransportESPAuthFailed & vblf
    Output = Output & "	NumPktsTunnelAHAuthFailed        = " & IpSecStat.NumPktsTunnelAHAuthFailed & vblf
    Output = Output & "	NumPktsTunnelESPAuthFailed       = " & IpSecStat.NumPktsTunnelESPAuthFailed & vblf
    Output = Output & "	NumPktsInvalidPktSyntax          = " & IpSecStat.NumPktsInvalidPktSyntax & vblf
    Output = Output & "	NumPktsInvalidProtocol           = " & IpSecStat.NumPktsInvalidProtocol & vblf
    Output = Output & "	NumPktsStatusUnknown             = " & IpSecStat.NumPktsStatusUnknown & vblf
    Output = Output & "	NumPktsCryptoNotDone             = " & IpSecStat.NumPktsCryptoNotDone & vblf
    Output = Output & "	NumPktsNextCryptoNotDone         = " & IpSecStat.NumPktsNextCryptoNotDone & vblf
    Output = Output & "	NumPktsIPAddrMismatch            = " & IpSecStat.NumPktsIPAddrMismatch & vblf
    Output = Output & "	NumPktsPortMismatch              = " & IpSecStat.NumPktsPortMismatch & vblf
    Output = Output & "	NumPktsBadSPI                    = " & IpSecStat.NumPktsBadSPI & vblf
    Output = Output & "	NumPktsBadOperation              = " & IpSecStat.NumPktsBadOperation & vblf
    Output = Output & "	NumPktsBadSeqNum                 = " & IpSecStat.NumPktsBadSeqNum & vblf
    Output = Output & "	NumPktsBadOptionLen              = " & IpSecStat.NumPktsBadOptionLen & vblf
    Output = Output & "	NumPktsBadOptions                = " & IpSecStat.NumPktsBadOptions & vblf
    Output = Output & "	NumPktsMalformedHeader           = " & IpSecStat.NumPktsMalformedHeader & vblf
    Output = Output & "	NumPktsAHESPUnexpected           = " & IpSecStat.NumPktsAHESPUnexpected & vblf
    Output = Output & "	NumPktsProtocolUnexpected        = " & IpSecStat.NumPktsProtocolUnexpected & vblf
    Output = Output & "	NumPktsMalformedPayload          = " & IpSecStat.NumPktsMalformedPayload & vblf
    Output = Output & "	NumPktsNoIPSecPerPktInfo         = " & IpSecStat.NumPktsNoIPSecPerPktInfo & vblf
    IPSecStatsToString = Output
End Function

'<!-- CRC = 0x4fad79a1 --->
Option Explicit
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
        bResult = WorkCard.QueryInfo(OID_GEN_MEDIA_CONNECT_STATUS, ConnectStatus, 2)
        If (Not bResult) Then
            call oLog.Write ("Unable to query media connect status.  If this is transient then it is not a failure." )
        ElseIf (ConnectStatus = Connected) Then
            bReturnVal = TRUE
            Exit Do
        End If
        
        If(lCount = 90) Then
            call oLog.Failed ("Timed out (90 seconds) waiting for link", 22932)
            Exit Do
        End If
        
        lCount = lCount + 1  
    Loop
    WaitForLink = bReturnVal
End Function
'-----------------------------------------------------------
' end of file WaitForLink.vbs
'-----------------------------------------------------------

'<!-- CRC = 0xb0528575 --->
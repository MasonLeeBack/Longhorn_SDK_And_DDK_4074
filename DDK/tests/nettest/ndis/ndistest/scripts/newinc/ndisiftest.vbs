

Function AddLastAllocatedNetLuidWMI(IfType, NetLuidIndex)

	Dim lRC, lRC1
	Dim sPath,sValueName
	Dim objRegistry 

	Set objRegistry = GetObject("winmgmts:{impersonationLevel=impersonate}!\\." _
      & "\root\default:StdRegProv")

  	sPath = "Software\Microsoft\NDTEST\NDISIF"

	lRC = objRegistry.CreateKey(HKEY_CURRENT_USER, sPath)

	sValueName = "" & IfType

	If (lRC = 0) Then
		lRC1 = objRegistry.SetDWORDValue(HKEY_CURRENT_USER, _
		                                sPath, _
		                                sValueName, _
		                                NetLuidIndex)

		If (lRC1 <> 0) Then
			AddLastAllocatedNetLuid = FALSE
	   Else
      	AddLastAllocatedNetLuid = TRUE
		End If
	Else
		AddLastAllocatedNetLuid = FALSE
	End If
End Function

Function AddLastAllocatedNetLuid(IfType, NetLuidIndex)
	Dim sPath,sValueName
   Dim oWshShell

   Set oWshShell = CreateObject("WScript.Shell")
   AddLastAllocatedNetLuid = TRUE
   
   On Error Resume Next
     	sPath = "HKCU\Software\Microsoft\NDTEST\NDISIF\"

      ' Create key
     	Call oWshShell.RegWrite(sPath, "")
      If (Err <> 0) Then
         ' Create key failed (maybe its already present?)
         Err.Clear
      End If

      
      ' Create item
    	sValueName = sPath & IfType
      Call oWshShell.RegWrite(sValueName, NetLuidIndex, "REG_DWORD")
      If (Err <> 0) Then
         ' Create data value failed
         AddLastAllocatedNetLuid = FALSE
         Err.Clear
      End If      
   On Error Goto 0
  
	Set oWshShell = Nothing
End Function

Function ReadLastAllocatedNetLuidWMI(IfType)

	Dim lRC, lRC1
	Dim sPath,sValueName
	Dim objRegistry 
	Dim lLastAllocatedNetLuid
	
	Set objRegistry = GetObject("winmgmts:{impersonationLevel=impersonate}!\\." _
      & "\root\default:StdRegProv")

	sPath = "Software\Microsoft\NDTEST\NDISIF"
	sValueName = "" & IfType

	If (lRC = 0) Then
		lRC1 = objRegistry.GetDWORDValue(HKEY_CURRENT_USER, _
		                                sPath, _
		                                sValueName, _
		                                lLastAllocatedNetLuid)

		If (lRC1 <> 0) Then
			ReadLastAllocatedNetLuid = -1
		Else
   	   ReadLastAllocatedNetLuid = lLastAllocatedNetLuid
		End If
	Else
		ReadLastAllocatedNetLuid = -1
	End If

End Function

Function ReadLastAllocatedNetLuid(IfType)
	Dim sPath,sValueName
	Dim lLastAllocatedNetLuid
   Dim oWshShell

   Set oWshShell = CreateObject("WScript.Shell")
  	sPath = "HKCU\Software\Microsoft\NDTEST\NDISIF\"
	sValueName = sPath & IfType

   On Error Resume Next
      lLastAllocatedNetLuid = oWshShell.RegRead(sValueName)
      If (Err <> 0) Then
         ReadLastAllocatedNetLuid = -1
         Err.Clear
      Else
         ReadLastAllocatedNetLuid = lLastAllocatedNetLuid
      End If
   On Error Goto 0

   Set oWshShell = Nothing
End Function


Function DeleteLastAllocatedNetLuidWMI()

	Dim lRC
	Dim sPath
	Dim objRegistry 
	Set objRegistry = GetObject("winmgmts:root\default:StdRegProv")

	sPath = "Software\Microsoft\NDTEST\NDISIF"
	lRC = objRegistry.DeleteKey(HKEY_CURRENT_USER, sPath)

	If (lRC = 0) Then
		DeleteLastAllocatedNetLuid = TRUE
	Else
		DeleteLastAllocatedNetLuid = FALSE
	End If

End Function

Function DeleteLastAllocatedNetLuid()
	Dim sPath
   Dim oWshShell

   DeleteLastAllocatedNetLuid = TRUE
   Set oWshShell = CreateObject("WScript.Shell")
  	sPath = "HKCU\Software\Microsoft\NDTEST\NDISIF\"

   On Error Resume Next
      ' Delete Key
  	   Call oWshShell.RegDelete(sPath)
  	   If (Err <> 0) Then
         DeleteLastAllocatedNetLuid = FALSE
         Err.Clear
  	   End If
  	On Error Goto 0
  	
   Set oWshShell = Nothing
End Function



'<!-- CRC = 0x7319fd4d --->
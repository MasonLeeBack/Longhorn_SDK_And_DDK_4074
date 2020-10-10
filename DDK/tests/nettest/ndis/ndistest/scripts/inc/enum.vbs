'<!-- CRC = 0x2597cd3e -->
'==========================================================================
'
' NAME: 	Enum.vbs
'
' AUTHOR: 	David Harding , Microsoft
' DATE  : 	11/22/2000
'
'==========================================================================
Option Explicit
Const MAX_PHONENUMBERS = 24

Dim g_Device
Dim g_NumDevices
Dim g_LineNumbers(24)
 
'//////////////////////////////////////////////////////////////////////////////////////////////////
Function Enumerate()		
Dim oObj
Dim AdapterList, Adapter
Dim i, nNumLines
Dim bReturn			
Dim arLines
Dim Devices()
Dim sLineName, sProviderName
Dim nCurrentDevice

	Enumerate 	= vbTrue
	
	nCurrentDevice = 0
		
	Set AdapterList = oNDInfo.AdapterList 
	If(AdapterList Is Nothing) Then
		MsgBox "Failed to retreive adapter list!", vbExclamation Or vbOKOnly or vbSystemModal, "Enumeration Failed"
		Enumerate = vbFalse
		Exit Function
	End If 

	g_Device = oNDTSession("g_Device")
	If(IsEmpty(g_Device)) Then
	
		For Each Adapter In AdapterList		
			
			'
			' Test Adapter
			'		
			If(Adapter.AdapterType = ADAPTERTYPE_TEST) Then	
				
				g_NumDevices = g_NumDevices + 1
				
				bReturn = oNDTWan.GetAvailableLines(Adapter.GUID, arLines, nNumLines)	
				If(bReturn = vbFalse) Then
					Msgbox "oNDTWan.GetAvailableLines() failed!", vbExclamation Or vbOKOnly or vbSystemModal, "Enumeration Failed"
					Enumerate = vbFalse
					Exit Function
				End If
			
				ReDim Preserve Devices(g_NumDevices)
				
				Set oObj = oNDTSession.CreateObject("Enum.wsc")
				If(oObj Is Nothing) Then
					Msgbox "oNDTSession.CreateObject() failed!", vbExclamation Or vbOKOnly or vbSystemModal, "Enumeration Failed"
					Enumerate = vbFalse
					Exit Function
				End If
				
				oObj.NumLines		= nNumLines
				oObj.ConnectionID 	= Adapter.ConnectionID
				oObj.DeviceName		= Adapter.Description
				oObj.GUID			= Adapter.GUID
				oObj.NdisMedium		= Adapter.NdisMedium
				oObj.PhoneNumber	= Adapter.PhoneNum
				oObj.AdapterType	= Adapter.AdapterType
					
				For i = 0 To nNumLines - 1
					bReturn  = oNDTWan.GetLineInformation(Adapter.ConnectionID, arLines(i), sLineName, sProviderName)
					If(bReturn = vbFalse) Then
						Msgbox "oNDTWan.GetLineInformation() failed", vbExclamation Or vbOKOnly or vbSystemModal, "Enumeration Failed"
						Enumerate = vbFalse
						Exit Function
					End If
					
					oObj.AddLine arLines(i), sLineName, sProviderName
				Next
				
				Set Devices(nCurrentDevice) = oObj
				nCurrentDevice = nCurrentDevice + 1
				
			End If		
			
			'
			' Server Adapter
			' 
			If(Adapter.AdapterType = ADAPTERTYPE_SUPPORT) Then
				
				g_NumDevices = g_NumDevices + 1
				
				ReDim Preserve Devices(g_NumDevices)
				
				Set oObj = oNDTSession.CreateObject("Enum.wsc")
				If(oObj Is Nothing) Then
					Msgbox "oNDTSession.CreateObject() failed!", vbExclamation Or vbOKOnly or vbSystemModal, "Enumeration Failed"
					Enumerate = vbFalse
					Exit Function
				End If
				
				oObj.NumLines		= nNumLines
				oObj.ConnectionID 	= Adapter.ConnectionID
				oObj.DeviceName		= Adapter.Description
				oObj.GUID			= Adapter.GUID
				oObj.NdisMedium		= Adapter.NdisMedium
				oObj.PhoneNumber	= Adapter.PhoneNum
				oObj.AdapterType	= Adapter.AdapterType
								
				Set Devices(nCurrentDevice) = oObj
				nCurrentDevice = nCurrentDevice + 1
				
			End If
			
		Next	
		
		oNDTSession("g_Device") 		= Devices
		oNDTSession("g_NumDevices") 	= g_NumDevices
		
		g_Device = oNDTSession("g_Device")
		If(IsEmpty(g_Device)) Then
			MsgBox "Failed to get Line array from NDTSession! (Error 1)", vbExclamation Or vbOKOnly or vbSystemModal, "Enumeration Failed"
			Enumerate = vbFalse
			Exit Function
		End If
		
		g_NumDevices = oNDTSession("g_NumDevices")
		If(IsEmpty(g_NumDevices)) Then
			MsgBox "Failed to get g_NumLines from NDTSession! (Error 1)", vbExclamation Or vbOKOnly or vbSystemModal, "Enumeration Failed"
			Enumerate = vbFalse
			Exit Function
		End If
			
	Else
		
		g_Device = oNDTSession("g_Device")
		If(IsEmpty(g_Device)) Then
			MsgBox "Failed to get Line array from NDTSession! (Error 2)", vbExclamation Or vbOKOnly or vbSystemModal, "Enumeration Failed"
			Enumerate = vbFalse
			Exit Function
		End If
		
		g_NumDevices = oNDTSession("g_NumDevices")
		If(IsEmpty(g_NumDevices)) Then
			MsgBox "Failed to get g_NumLines from NDTSession! (Error 2)", vbExclamation Or vbOKOnly or vbSystemModal, "Enumeration Failed"
			Enumerate = vbFalse
			Exit Function
		End If
			
	End If
	
	if(g_NumDevices > 1) then
		if(g_Device(1).PhoneNumber = "") then
			msgbox "No phone number was set for the remote device!" & vblf & _
				   "Make sure you set the phone number in the Advanced menu for this device on the server!", vbOkOnly or vbExclamation or vbSystemModal, "Missing Phone Number"
			Enumerate = false
			exit function
		end if
		
		Dim tmp
		tmp = split(g_Device(1).PhoneNumber,";", -1)
		
		if(ubound(tmp) > 0) then
			g_LineNumbers(0) = tmp(0)
			g_LineNumbers(1) = tmp(1) 
		else
			for i = 0 to MAX_PHONENUMBERS
				g_LineNumbers(i) = g_Device(1).PhoneNumber
			next
		end if
		
	end if
	
	Set AdapterList = Nothing
		
End Function

'<!-- CRC = 0x9eb73fd9 --->
'==========================================================================
'
'
' NAME: <filename>
'
' AUTHOR: David Harding , Microsoft
' DATE  : 10/23/2000
'
'
'==========================================================================
' Gloabals
Option Explicit
Dim bConnected
Dim bDisConnected

bConnected 		= vbFalse
bDisConnected	= vbFalse

Class clsDATACLASS
	' Data Variables
	Private m_OpenHandle
	Private m_AdapterHandle
	Private m_TAPIHandle
	Private m_ConnectionID
	Private m_GUID
			
	'--------------------------------------------------------------------------
	Public Property Get ConnectionID()
		ConnectionID = m_ConnectionID
	End Property
	Public Property Let ConnectionID(newVal)
		m_ConnectionID = newVal
	End Property
	'--------------------------------------------------------------------------
	
	'--------------------------------------------------------------------------
	Public Property Get GUID()
		GUID = m_GUID
	End Property
	Public Property Let GUID(newVal)
		m_GUID = newVal
	End Property
	'--------------------------------------------------------------------------
	
	'--------------------------------------------------------------------------
	Public Property Get OpenHandle()
		Set OpenHandle = m_OpenHandle
	End Property
	Public Property Set OpenHandle(Obj)
		Set m_OpenHandle = Obj
	End Property
	'--------------------------------------------------------------------------
	
	'--------------------------------------------------------------------------
	Public Property Get TAPIHandle()
		Set TAPIHandle = m_TAPIHandle
	End Property
	Public Property Set TAPIHandle(Obj)
		Set m_TAPIHandle = Obj
	End Property
	'--------------------------------------------------------------------------

	'--------------------------------------------------------------------------
	Public Property Get AdapterHandle()
		Set AdapterHandle = m_AdapterHandle
	End Property
	Public Property Set AdapterHandle(Obj)
		Set m_AdapterHandle = Obj
	End Property
	'--------------------------------------------------------------------------
	
	'//////////////////////////////////////////////////////////////////////////////////////////////
	Private Sub Class_Initialize()	
		Set m_OpenHandle 	= Nothing
		Set m_AdapterHandle	= Nothing
		Set m_TAPIHandle	= Nothing
	End Sub
	'//////////////////////////////////////////////////////////////////////////////////////////////
	Private Sub Class_Terminate
		Set m_OpenHandle 	= Nothing
		Set m_AdapterHandle	= Nothing
		Set m_TAPIHandle	= Nothing	
	End Sub
		
End Class

'//////////////////////////////////////////////////////////////////////////////////////////////
Function OpenLine(cData, nLineID, nMediaMode, nPrivledges)
Dim pExtID,nStatus,hLineHndle,nAPIVersion
	
	OpenLine = vbTrue
	
	Do
		Set pExtID = cData.TAPIHandle.CreateStructure("LINEEXTENSIONID")
		If(pExtID is Nothing) Then
		   	call oLog.Failed ("Failed to create LINEEXTENSIONID structure!" , 22909)
			Exit Do
		End If
			
		nStatus = cData.TAPIHandle.LineNegotiateAPIVersion(nLineID, 0,API_VERSION, nAPIVersion, pExtID)
		If(Not nStatus = SUCCESS) Then
			call oLog.Failed ("LineNegotiateAPIVersion() failed! (Status = 0x" & Hex(nStatus) & ")"  , 22910)
			Exit Do
		End If
						
		'
		' Open the line 
		nStatus = cData.TAPIHandle.LineOpen(nLineID, hLineHndle, nAPIVersion, 0, nPrivledges, nMediaMode)
		If(Not nStatus = SUCCESS) Then
			call oLog.Failed ("LineOpen() failed! (Status = 0x" & Hex(nStatus) & ")"  , 22911)
			Exit Do
		End If	
				
		OpenLine = hLineHndle
				
	Loop While(vbFalse)
	
	Set pExtID = Nothing

End Function
'//////////////////////////////////////////////////////////////////////////////////////////////
		
'//////////////////////////////////////////////////////////////////////////////////////////////
Function CloseLine(cData, nLineHandle)
Dim nStatus

	CloseLine = vbTrue
			
	nStatus = cData.TAPIHandle.LineClose(nLineHandle)
	If(Not nStatus = SUCCESS) Then
		call oLog.Failed ("LineClose() failed! (Status = 0x" & Hex(nStatus) & ")"  , 22912)
		CloseLine = vbFalse
	End If
	
End Function
'//////////////////////////////////////////////////////////////////////////////////////////////

'//////////////////////////////////////////////////////////////////////////////////////////////
Function StartServer(cData, nAnswerMode)
Dim bReturn
	
	StartServer = vbFalse
	
	Do
		'
		' Tell the server to setup and prepare
		' 
		bReturn = oNDTWan.InitializeServer(cData.ConnectionID, cData.GUID)
		If(bReturn = vbFalse) Then
			call oLog.Failed ("Failed to initaialize server!", 22913)
			Exit Do
		End If
		
		'
		' Must create this object in order to talk to the server
		'
		Set cData.TAPIHandle = oNDTWan.CreateTAPI(cData.ConnectionID)
		If(cData.TAPIHandle Is Nothing) Then
			call oLog.Failed ("oNDTWan.CreateTAPI() failed!" , 22914)
			Exit Do
		End If
		
		If(nAnswerMode = ANSWERMODE_ROUTE) Then
			
			'
			' Open virtual adapter on server
			'
			bReturn = OpenNdisWan(cData, cData.GUID)
			If(bReturn = vbFalse) Then
				Set cData.TAPIHandle = Nothing
				Exit Do
			End If
			
		End If
		
		cData.TAPIHandle.AnswerMode	= nAnswerMode
		cData.TAPIHandle.AnswerCalls = vbTrue
		
		StartServer = vbTrue
	
	Loop While(vbFalse)
		
End Function
'//////////////////////////////////////////////////////////////////////////////////////////////

'//////////////////////////////////////////////////////////////////////////////////////////////
Function StopServer(cData)
Dim bReturn
	
	StopServer = vbFalse
	
	Do
		cData.TAPIHandle.AnswerCalls = vbFalse
		
		If(Not cData.OpenHandle Is Nothing) Then
			'
			' Close Vritual adapter
			'
			CloseNdisWan(cData)
		End If
	
		'
		' Shut down server
		'
		bReturn = oNDTWan.UninitializeServer(cData.ConnectionID)
		If(bReturn = vbFalse) Then
			call oLog.Failed ("Failed to Uninitialize server!", 22915)
			Exit Do
		End If
		
		StopServer = vbTrue
		
	Loop While(vbFalse)
		
	Set cData.TAPIHandle = Nothing
	
End Function
'//////////////////////////////////////////////////////////////////////////////////////////////

'//////////////////////////////////////////////////////////////////////////////////////////////
Function StartClient(cData, nAnswerMode)
Dim bReturn
	
	StartClient = vbFalse
	
	do
		'
		' Must create this object in order to talk to the server
		'
		Set cData.TAPIHandle = oNDTWan.CreateTAPI(cData.ConnectionID)
		If(cData.TAPIHandle Is Nothing) Then
			call oLog.Failed ("oNDTWan.CreateTAPI() failed!" , 22916)
			Exit Do
		End If
		
		If(nAnswerMode = ANSWERMODE_ROUTE) Then
					
			'
			' Open virtual adapter on server
			'
			bReturn = OpenNdisWan(cData, cData.GUID)
			If(bReturn = vbFalse) Then
				Set cData.TAPIHandle = Nothing
				Exit Do
			End If
			
		End If
		
		cData.TAPIHandle.AnswerMode	= nAnswerMode
		cData.TAPIHandle.AnswerCalls = vbTrue
		
		StartClient = vbTrue
	
	Loop While(vbFalse)
		
End Function
'//////////////////////////////////////////////////////////////////////////////////////////////

'//////////////////////////////////////////////////////////////////////////////////////////////
Function StopClient(cData)
Dim bReturn

	StopClient = vbFalse
	
	Do
		cData.TAPIHandle.AnswerCalls = vbFalse
		
		If(Not cData.OpenHandle Is Nothing) Then
			'
			' Close Vritual adapter
			'
			bReturn = CloseNdisWan(cData)
			If(bReturn = vbFalse) Then
				Exit Do
			End If
			
		End If
		
		StopClient = vbTrue
		
	Loop While(vbFalse)
	
	Set cData.TAPIHandle = Nothing
	
End Function
'//////////////////////////////////////////////////////////////////////////////////////////////

'//////////////////////////////////////////////////////////////////////////////////////////////
Function MakeCall(cData, hLine, szPhoneNumber, nMediaMode, nBearerMode, nMinRate, nMaxRate)
Dim pCallParams,nStatus, nRate
Dim hCallHndle
Dim bCallConnected, bReturn
	
	bCallConnected = vbTrue	
				
	Do				
		Set pCallParams = cData.TAPIHandle.CreateStructure("LINECALLPARAMS")
		If(pCallParams is Nothing) Then
			call oLog.Failed ("Failed to create LINECALLPARAMS structure!" , 22917)
			bCallConnected = vbFalse
		   	Exit Do
		End If
					
		pCallParams.dwBearerMode 	= nBearerMode
		pCallParams.dwMediaMode  	= nMediaMode
		pCallParams.dwMinRate		= nMinRate
		pCallParams.dwMaxRate		= nMaxRate
				
		oLog.Write(vblf)
		oLog.Write("CALLPARAMS")
		oLog.Write("-> dwBearerMode = " & cData.TAPIHandle.DisplayString("LINEBEARERMODE", pCallParams.dwBearerMode))
		oLog.Write("-> dwMediaMode  = " & cData.TAPIHandle.DisplayString("LINEMEDIAMODE", pCallParams.dwMediaMode))
		oLog.Write("-> dwMinRate    = " & pCallParams.dwMinRate)
		oLog.Write("-> dwMaxRate    = " & pCallParams.dwMaxRate)
		oLog.Write(vblf)
		
		WScript.Sleep(1000)
		
		if(szPhoneNumber = "") then
			szPhoneNumber = InputBox("Enter Phone Numer", "Phone Number")
		end if
		
		nStatus = cData.TAPIHandle.LineMakeCall(hLine, hCallHndle, szPhoneNumber, 0, pCallParams)
		If(Not nStatus = SUCCESS) Then
			call oLog.Failed ("LineMakeCall() failed! (Status = 0x" & Hex(nStatus) & ")" , 22918)
			bCallConnected = vbFalse
		   	Exit Do
		End If
			
		oLog.Write(vblf & "Waiting for call to connect...")

		bReturn = cData.TAPIHandle.WaitCall()
		If(bReturn = vbFalse) Then
			call oLog.Failed ("Failed to Connect call in 10 Seconds!" , 22919)
			bCallConnected = vbFalse
		End If
				
	Loop While(vbFalse)
	
	If(bCallConnected = vbTrue) Then
		MakeCall = hCallHndle
	Else
		MakeCall = -1
	End If
		
	Set pCallParams = Nothing
					
End Function
'//////////////////////////////////////////////////////////////////////////////////////////////

'//////////////////////////////////////////////////////////////////////////////////////////////
Function CloseCall(cData,hCall)
Dim nStatus, User, i
		
	CloseCall = vbTrue
	
	nStatus = cData.TAPIHandle.LineDrop(hCall, User, 0)
	If(Not nStatus = SUCCESS) Then
		call oLog.Failed ("LineDrop() failed! (Status = 0x" & Hex(nStatus) & ")" , 22920)
		CloseCall = vbFalse
	End If
	
	WScript.Sleep(1000)
	
End Function
'//////////////////////////////////////////////////////////////////////////////////////////////

'//////////////////////////////////////////////////////////////////////////////////////////////
Function DeallocateCall(cData,hCall)
Dim nStatus
		
	DeallocateCall = vbTrue
	
	nStatus = cData.TAPIHandle.LineDeallocateCall(hCall)
	If(Not nStatus = SUCCESS) Then
		call oLog.Failed ("LineDeallocateCall() failed! (Status = 0x" & Hex(nStatus) & ")" , 22921)
		DeallocateCall = vbFalse
	End If
		
End Function
'//////////////////////////////////////////////////////////////////////////////////////////////
	
'//////////////////////////////////////////////////////////////////////////////////////////////
Public Function OpenNdisWan(cData, szGUID)
Dim AdapterList, Adapter
Dim bForceNdis30, bResult

	OpenNdisWan = vbFalse
	
	Do 													
		Set AdapterList = oNDInfo.AdapterList 
		If(AdapterList Is Nothing) Then
			call oLog.Failed ("Unable to retreive Adapter list!" , 22922)
			Exit Do
		End If 
			
		For Each Adapter In AdapterList			
			If((Adapter.AdapterType = ADAPTERTYPE_WANVIRTUAL) And (Adapter.BoundTo = szGUID)) Then
				
				'
				' Tell our TAPI Object what virtual device to route too.
				' 
				cData.TAPIHandle.RouteTo = Adapter.Description
				oNDTCore.LogPtr = oLog.LogPtr
						
				Set cData.AdapterHandle = oNDTCore.CreateAdapter(Adapter)
				If(cData.AdapterHandle is Nothing) Then
				   	call oLog.Failed ("Failed to create test adapter object!" , 22923)
					Exit Do
				End If
				
				Set cData.OpenHandle = cData.AdapterHandle.CreateOpen()
				If(cData.OpenHandle is Nothing) Then
				   	call oLog.Failed ("Failed to create open object on test adapter!" , 22924)
					Exit Do
				End If
				
				bResult = cData.OpenHandle.NdisOpen(NDISMEDIUMWAN, bForceNdis30)
				If(bResult = vbFalse) Then
					call oLog.Failed ("NdisOpen() failed for WAN Virtual device!" , 22925)
					Exit Do	
				End If
								
				OpenNdisWan = vbTrue
				Exit For
				
			End If
		Next
		
	Loop While(vbFalse)
	
	Set AdapterList = Nothing
		
End Function
'//////////////////////////////////////////////////////////////////////////////////////////////

'//////////////////////////////////////////////////////////////////////////////////////////////
Function CloseNdisWan(cData)
Dim bResult
				
	CloseNdisWan = vbFalse
		
	Do
		bResult = cData.OpenHandle.NdisClose()
		If(bResult = vbFalse) Then
			call oLog.Failed ("NdisClose() failed for WAN Virtual device!" , 22926)
			Exit Do
		End If
		
		CloseNdisWan = vbTrue
		
	Loop While(vbFalse)
		
	Set cData.OpenHandle 	= Nothing
	Set cData.AdapterHandle	= Nothing
		
End Function
'//////////////////////////////////////////////////////////////////////////////////////////////
	
'//////////////////////////////////////////////////////////////////////////////////////////////
Function GetMaxRate(oTAPI, nLineID)
Dim pDevCaps, pExtID
Dim nAPIVersion, nStatus
	
	GetMaxRate = 0
	
	Do		
		Set pExtID = oTAPI.CreateStructure("LINEEXTENSIONID")
		If(pExtID is Nothing) Then
			call oLog.Failed ("Failed to create LINEEXTENSIONID structure!" , 22927)
			Exit Do
		End If
		
		Set pDevCaps = oTAPI.CreateStructure("LINEDEVCAPS")
		If(pDevCaps is Nothing) Then
			call oLog.Failed ("Failed to create LINEDEVCAPS structure!" , 22928)
			Exit Do
		End If
				
		'
		' Negotiate the API version for this line
		'
		nStatus = oTAPI.LineNegotiateAPIVersion(nLineID, 0,API_VERSION, nAPIVersion, pExtID)
		If(Not nStatus = SUCCESS) Then
			call oLog.Failed ("LineNegotiateAPIVersion() failed! (Status = 0x" & Hex(nStatus) & ")"  , 22929)
			Exit Do
		End If
				
		nStatus = oTAPI.LineGetDevCaps(nLineID, nAPIVersion, 0, pDevCaps)
		If(Not nStatus = SUCCESS) Then
			call oLog.Failed ("LineGetDevCaps() failed! (Status = 0x" & Hex(nStatus) & ")" , 22930)
			Exit Do
		End If
				
		GetMaxRate = pDevCaps.dwMaxRate
	
	Loop While(vbFalse)
	
	Set pDevCaps	= Nothing
	Set pExtID 		= Nothing
	
End Function
'//////////////////////////////////////////////////////////////////////////////////////////////

'//////////////////////////////////////////////////////////////////////////////
'TERMINATE HANDLERS
'----------------------------------------------------------------------------------------------
' Function:		TapiEvent_OnDisconnect()
'
' Arguments:
'
' Returns:
'----------------------------------------------------------------------------------------------
''Sub TapiEvent_OnDisconnect()
''	bDisConnected = vbTrue
''End Sub

'----------------------------------------------------------------------------------------------
' Function:		TapiEvent_OnConnect()
'
' Arguments:
'
' Returns:
'----------------------------------------------------------------------------------------------
''Sub TapiEvent_OnConnect()
''	bConnected = vbTrue
''End Sub

'----------------------------------------------------------------------------------------------
' Function:		TapiEvent_OnConnect()
'
' Arguments:
'
' Returns:
'----------------------------------------------------------------------------------------------
''Sub TapiEvent_OnRoute(nBundleHandle)
	
''End Sub

'<!-- CRC = 0x66845333 --->
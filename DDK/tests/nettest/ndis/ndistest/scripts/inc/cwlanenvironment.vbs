Option Explicit

Const ACCESSPOINT_A = 1
Const ACCESSPOINT_B = 2
Const ADHOC         = 3

'================================================================================================='
'/**
' * This class is used to return and set access point information in a structured form. It is used
' * by CWlanEnvironment to return access point information collect from the snmp queries. It can also
' * be created and initialized individual and passed as a parmeter to set information on the access
' * point
' * @sa
' * CWlanEnvironment
' * @date
' * 11/27/2001
' * @author
' * David Harding
' * @alias
' * davhar@microsoft.com
' */
Class CAccessPoint

	Private m_sSsid
	Private m_nWepIndex

	Public Sub Class_Initialize()
    	m_sSsid 	= "NDTestDefault"
    	m_nWepIndex	= 0
    End Sub
	
	Public Sub Class_Terminate()
	End Sub
	
	'================================================================================================='
	'/**
	' * This property will return the currently stored SSID value from the class.
	' * @returns
	' *	A string value that is the current SSID.
	' * @example
	' * sValue = Obj.Ssid
	' */
	Public Property Get Ssid
		Ssid = m_sSsid
	End Property 
	
	'================================================================================================='
	'/**
	' * This property will set the SSID value for the class. The assigned value must be a string.
	' * @params
	' * ! string New string value for the SSID.
	' * @example
	' * Obj.Ssid = "NEWSSID"
	' */
	Public Property Let Ssid(newVal)
		m_sSsid = newVal
	End Property
	
	'================================================================================================='
	'/**
	' * This property will return the currently stored WepIndex value from the class.
	' * @returns
	' * A numeric value that is the current WepIndex. This value should be between 0-3.
	' * @example
	' * nValue = Obj.WepIndex
	' */
	Public Property Get WepIndex
		WepIndex = m_nWepIndex
	End Property 
	
	'================================================================================================='
	'/**
	' * This property will set the WepIndex value for the class. The assigned value must be numeric
	' * 0-3.
	' * @params
	' * ! number A numeric value between 0-3.
	' * @example
	' * Obj.WepIndex = 2
	' */
	Public Property Let WepIndex(newVal)
		m_nWepIndex = newVal
	End Property
	
End Class

'================================================================================================='
'/**
' * This class is used to configure the wireless lan environment. Properties and methods are 
' * provided to configure the access points and the wireless devices. Additional methods are 
' * provided to allow the access points to be changed at run-time.
' * @sa 
' *	CAccessPoint
' * @date
' * 11/27/2001
' * @author
' * David Harding
' * @alias
' * davhar@microsoft.com
' */
Class CWlanEnvironment

	Private m_oSnmp
	Private m_oShell
    Private m_oConnection
    Private m_oRecordSet
    Private m_sInstallDirectory
    Private m_oNDTCore
    Private m_oAccessPointA
    Private m_oAccessPointB
    Private m_oAPADefaults
    Private m_oAPBDefaults
    
    Public Sub Class_Initialize()
    	    
    	Set m_oNDTCore		= oNDTCore 'CreateObject("NDTCore.base.1")
    	Set m_oShell		= CreateObject("WScript.Shell")
    	Set m_oSnmp			= CreateObject("ndtsnmp.snmpcore.1")
        Set m_oConnection 	= CreateObject("ADODB.Connection")
        Set m_oRecordSet	= CreateObject("ADODB.Recordset")
        
        Set m_oAccessPointA	= New CAccessPoint
        Set m_oAccessPointB	= New CAccessPoint
        Set m_oAPADefaults	= New CAccessPoint
        Set m_oAPBDefaults	= New CAccessPoint
        
        m_sInstallDirectory = m_oShell.RegRead("HKCU\Software\Microsoft\NDTEST\CommonInfo\InstallDir")
        m_oConnection.Open("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=" & m_sInstallDirectory & "\ndtestdb.mdb")
        
    End Sub
	
	Public Sub Class_Terminate()
	    
	    m_oConnection.Close()
	   	Set m_oConnection 	= Nothing
	    Set m_oRecordSet 	= Nothing
	    Set m_oSnmp			= Nothing
	    Set m_oAccessPointA	= Nothing
		Set m_oAccessPointB	= Nothing
		Set m_oNDTCore		= Nothing
		Set m_oAPADefaults	= Nothing
        Set m_oAPBDefaults	= Nothing
			    
	End Sub
	
	'============================================================================================='
	'/**
	' * This function will return the default SSID for the access point that is stored in the 
	' * database.
	' * @params
	' * ! constant  Specifies the access point that the value should be returned for. This value can be one
	' *             of the following constants.
	' *             +   ACCESSPOINT_A
	' *             +   ACCESSPOINT_B   
	' * @return 
	' * The SSID for the access point from the database.
	' * @example
	' * sSsid = Obj.DefaultSsid(ACCESSPOINT_A)
	' */
	Public Function DefaultSsid(nAccessPoint)
    
        DefaultSsid = GetDefaultSsid(nAccessPoint)
	    if(DefaultSsid = "") then
	        Call oLog.Failed("Failed to get default SSID!", 88888)
	    end if
	    	    	
	End Function
	
	'============================================================================================='
	'/**
	' * This function will return the default WepIndex for the access point that is stored in the 
	' * database.
	' * This is a read only property.
	' * @params
	' * ! constant  Specifies the access point that the value should be returned for. This value can be one
	' *             of the following constants.
	' *             +   ACCESSPOINT_A
	' *             +   ACCESSPOINT_B   
	' * @return 
	' * The WepIndex for the access point from the database.
	' * @example
	' * nWepIndex = Obj.DefaultWepIndex(ACCESSPOINT_A)
	' */
	Public Function DefaultWepIndex(nAccessPoint)
	Dim nWepIndex
	
	    nWepIndex = GetDefaultWepIndex(nAccessPoint)
	    if((nWepIndex < 0) Or (nWepIndex > 3)) then
	        Call oLog.Failed("Failed to get default wep index!", 88888)
        else
            DefaultWepIndex = &H80000000& + nWepIndex
	    end if
 	    
	End Function
	
	'============================================================================================='
	'/**
	' * This function will return the default Wep Key for the access point that is stored in the 
	' * database.
	' * @params
	' * ! constant Specifies the access point that the value should be returned for. This value can be one
	' *            of the following constants.
	' *            +   ACCESSPOINT_A
	' *            +   ACCESSPOINT_B   
	' * @return 
	' * The Wep Key for the access point from the database.
	' * @example
	' * sWepKey = Obj.DefaulWepKey(ACCESSPOINT_A)
	' */
	Public Function DefaultWepKey(nAccessPoint)
	
	    DefaultWepKey = GetDefaultWepKey(nAccessPoint)
	    if(DefaultWepKey = "") then
	        Call oLog.Failed("Failed to get default key material!", 88888)
	    end if
	
	End Function
	
	'============================================================================================='
	'
	'
	Private Function GetDefaultSsid(nAccessPoint)
	    
	    GetDefaultSsid = ""
		
 	    select case nAccessPoint
		case ACCESSPOINT_A
		    m_oRecordSet.Open "SELECT * From Wlan_APA", m_oConnection, 2, 3
		case ACCESSPOINT_B
		    m_oRecordSet.Open "SELECT * From Wlan_APB", m_oConnection, 2, 3
		case ADHOC
		    m_oRecordSet.Open "SELECT * From Wlan_Adhoc", m_oConnection, 2, 3
		end select
		
        GetDefaultSsid = m_oRecordSet("Ssid")   
          
 	    m_oRecordSet.Close()
 	    
	End Function
	
	'============================================================================================='
	'
	'
	Private Function GetDefaultWepIndex(nAccessPoint)
	
	    GetDefaultWepIndex = ""
		
 	    select case nAccessPoint
		case ACCESSPOINT_A
		    m_oRecordSet.Open "SELECT * From Wlan_APA", m_oConnection, 2, 3
		case ACCESSPOINT_B
		    m_oRecordSet.Open "SELECT * From Wlan_APB", m_oConnection, 2, 3
		case ADHOC
		    m_oRecordSet.Open "SELECT * From Wlan_Adhoc", m_oConnection, 2, 3
		end select
		
        GetDefaultWepIndex = CLng(m_oRecordSet("WepIndex"))   
          
 	    m_oRecordSet.Close()
	
	End Function
	
	'============================================================================================='
	'
	'
	Private Function GetDefaultWepKey(nAccessPoint)
	Dim sColumn 
	
	    GetDefaultWepKey = ""
		
		select case nAccessPoint
		case ACCESSPOINT_A
		    m_oRecordSet.Open "SELECT * From Wlan_APA", m_oConnection, 2, 3
		case ACCESSPOINT_B
		    m_oRecordSet.Open "SELECT * From Wlan_APB", m_oConnection, 2, 3
		case ADHOC
		    m_oRecordSet.Open "SELECT * From Wlan_Adhoc", m_oConnection, 2, 3
		end select
	
		sColumn         = "Key" & CStr(m_oRecordSet("WepIndex") + 1)	'///@bug Remove this hack by renaming the key columns		
		GetDefaultWepKey   = CStr(m_oRecordSet(sColumn))
		   
 	    m_oRecordSet.Close()
 	    
	End Function
	
	'============================================================================================='
	'/**
	' * This function will cause the access point to simulate a connect by setting the SSID to the
	' * default SSID value from the database that is associated with access point argument. 
	' * @params
	' * ! constant Specifies the access point that the value should be returned for. This value can be one
	' *            of the following constants.
	' *            +   ACCESSPOINT_A
	' *            +   ACCESSPOINT_B   
	' * @return 
	' * True if the function succeeded, otherwise returns false.
	' * @sa     
	' * CWlanEnvironment::Disconnect
	' * @example
	' * bRetval = Obj.Connect(ACCESSPOINT_A)
	' * if(bRetval = false) then
	' *     ' Handle Error
	' * end if
	' */
	Public Function Connect(nAccessPoint)
	Dim bRetval

	    bRetval = APConnect(nAccessPoint)
	    if(bRetval = false) then
	        Exit Function
	    end if
	    
	End Function
	
	'============================================================================================='
	'/**
	' * This function will cause the access point to simulate a disconnect by setting the SSID to the
	' * on the access point to a bogus value. This will cause all associated client to disconnect. 
	' * @params
	' * ! constant Specifies the access point that the value should be returned for. This value can be one
	' *            of the following constants.
	' *            +   ACCESSPOINT_A
	' *            +   ACCESSPOINT_B   
	' * @return 
	' * True if the function succeeded, otherwise returns false.
	' * @sa     
	' * CWlanEnvironment::Connect
	' * @example
	' * bRetval = Obj.Disconnect(ACCESSPOINT_A)
	' * if(bRetval = false) then
	' *     ' Handle Error
	' * end if
	' */
	Public Function Disconnect(nAccessPoint)
	Dim bRetval
	
	    bRetval = APDisconnect(nAccessPoint)
	    if(bRetval = false) then
	        Exit Function
	    end if
	    
	End Function
		
	'============================================================================================='
	'
	'
	Private Function APDisconnect(nAccessPoint)
	Dim bRetval
	Dim oAgent
	Dim sIPAddress, sSsid
	
	    select case nAccessPoint
		case ACCESSPOINT_A
		    m_oRecordSet.Open "SELECT * From Wlan_APA", m_oConnection, 2, 3
		case ACCESSPOINT_B
		    m_oRecordSet.Open "SELECT * From Wlan_APB", m_oConnection, 2, 3
		end select
		
		sIPAddress  = m_oRecordSet("IPAddress")
		sSsid       = "NDTESTAPDisconnectState"
		
		m_oRecordSet.Close()
		
		do
	    	' Connect to the remote agent
			bRetval = m_oSnmp.OpenAgent(sIPAddress, "public")
			if(bRetval = false) then
				Call oLog.SafeFailed ("Failed to open agaent!", 88888)
			 	Exit Do
			end if
	    	
	    	' Create an agent object for the cisco access point
	    	Set oAgent = m_oSnmp.Agent("\\accesspoint\cisco")
			if(oAgent Is Nothing) then
	    		Call oLog.SafeFailed ("Failed to create agent object!", 88888)
	            Exit Do
	    	end if
	    	
			' Set the SSID on the access point to the new value
			oAgent.Ssid = "APDisconnectState"
	        if(Not Err.Number = 0) then
	            Call oLog.SafeFailed ("Failed to set SSID to disconnect state! - " & Err.Description, 88888)
	            Exit Do
	        end if
	        	       		
	        APDisconnect = true
	        				    		    		    	
	    loop while(false)
		
        if(APDisconnect = false) then
            Call oLog.Failed("Failed to disconnect access point!", 88888)
        end if
	
	End Function
	
	'============================================================================================='
	'
	'
	Private Function APConnect(nAccessPoint)
	Dim bRetval
	Dim oAgent
	Dim sIPAddress, sSsid
	Dim nTimeout, nTime
	
	    nTimeout = 30
	
	    select case nAccessPoint
		case ACCESSPOINT_A
		    m_oRecordSet.Open "SELECT * From Wlan_APA", m_oConnection, 2, 3
		case ACCESSPOINT_B
		    m_oRecordSet.Open "SELECT * From Wlan_APB", m_oConnection, 2, 3
		end select
		
		sIPAddress  = m_oRecordSet("IPAddress")
		sSsid       = m_oRecordSet("Ssid")
		
		m_oRecordSet.Close()
				
		do
	    	' Connect to the remote agent
			bRetval = m_oSnmp.OpenAgent(sIPAddress, "public")
			if(bRetval = false) then
				Call oLog.SafeFailed ("Failed to open agaent!", 88888)
			 	Exit Do
			end if
	    	
	    	' Create an agent object for the cisco access point
	    	Set oAgent = m_oSnmp.Agent("\\accesspoint\cisco")
			if(oAgent Is Nothing) then
	    		Call oLog.SafeFailed ("Failed to create agent object!", 88888)
	            Exit Do
	    	end if
	    		    	
			' Set the SSID on the access point to the new value
			oAgent.Ssid = sSsid
	        if(Not Err.Number = 0) then
	            Call oLog.SafeFailed ("Failed to set SSID to disconnect state! - " & Err.Description, 88888)
	            Exit Do
	        end if
	        
	        Dim sTemp 
	        
	        do
			    sTemp = oAgent.Ssid
	            if(sTemp = sSsid) then
	                APConnect = true
	                Exit Do
	            end if
	                			
			    if(nTime > nTimeout) then
				    Exit Do
			    end if 
			
			    WScript.Sleep(1000)
			    nTime = nTime + 1
		    loop while(true)
		    						    		    		    	
	    loop while(false)
			
		m_oSnmp.CloseAgent()
		
		if(APConnect = false) then
            Call oLog.Failed("Failed to connect access point!", 88888)
        end if
                		
	End Function
	
	'============================================================================================='
	'/**
	' * This property connects to the access point and querys the access point for specific information.
	' * The return values are placed in an access point class which is returned to the caller.
	' * @return	
	' * A reference to an access point class. 
	' * @sa
	' * CAccessPoint,CWlanEnvironment::AccessPointB
	' * @example
	' * Set oAP = oClass.AccessPointA
	' * if(oAP Is Nothing) then
	' * 	' Handle Error
	' *	end if
	' */
	Public Property Get AccessPointA	
	Dim bRetval
	Dim oAgent
	
	On Error Resume Next
		
		Set AccessPointA = Nothing
		
	    do
	    	' Connect to the remote agent
	    	m_oRecordSet.Open "SELECT * From Wlan_APA", m_oConnection, 2, 3
			bRetval = m_oSnmp.OpenAgent(m_oRecordSet("IPAddress") , "public")
			if(bRetval = false) then
				Call oLog.SafeFailed ("OpenAgent() failed! (AP A)", 88888)
			 	Exit Do
			end if
	    	
	    	' Create an agent object for the cisco access point
	    	Set oAgent = m_oSnmp.Agent("\\accesspoint\cisco")
			if(oAgent Is Nothing) then
	    		Call oLog.SafeFailed ("Failed to create agent object! (AP A)", 88888)
	            Exit Do
	    	end if
	    	
			' Get the SSID from the access point
			m_oAccessPointA.Ssid = oAgent.Ssid
	        if(Not Err.Number = 0) then
	            Call oLog.SafeFailed ("oAgent.Ssid failed! (AP A) - " & Err.Description, 88888)
	            Exit Do
	        end if
	       	
	       	' Get the Transmit Key (WepIndex) from the access point
			m_oAccessPointA.WepIndex = oAgent.WepIndex
	        if(Not Err.Number = 0) then
	            Call oLog.SafeFailed ("oAgent.WepIndex failed! (AP A) - " & Err.Description, 88888)
	            Exit Do
	        end if
			
			m_oSnmp.CloseAgent()
	    	m_oRecordSet.Close()
	    		    		    	
	    loop while(false)
		
		' If the recordset is still opened.
		if(m_oRecordSet.State = 1) then
			m_oRecordSet.Close()
		end if
		
		m_oSnmp.CloseAgent()
		
		Set AccessPointA = m_oAccessPointA	
		
	On Error Goto 0
		    	
	End Property
	
	'============================================================================================='
	'/**
	' * This property connects to the access point and querys the access point for specific information.
	' * The return values are placed in an access point class which is returned to the caller.
	' * @return
	' *	A reference to an access point class. 
	' * @sa
	' * CAccessPoint,CWlanEnvironment::AccessPointB
	' * @example
	' * Set oAP = oClass.AccessPointA
	' * if(oAP Is Nothing) then
	' * 	' Handle Error
	' *	end if
	' */
	Public Property Set AccessPointA(newVal)
	Dim bRetval
	Dim oAgent
	
	On Error Resume Next
			
	    do
	    	' Connect to the remote agent
	    	m_oRecordSet.Open "SELECT * From Wlan_APA", m_oConnection, 2, 3
			bRetval = m_oSnmp.OpenAgent(m_oRecordSet("IPAddress") , "public")
			if(bRetval = false) then
				Call oLog.SafeFailed ("OpenAgent() failed! (AP A)", 88888)
			 	Exit Do
			end if
	    	
	    	' Create an agent object for the cisco access point
	    	Set oAgent = m_oSnmp.Agent("\\accesspoint\cisco")
			if(oAgent Is Nothing) then
	    		Call oLog.SafeFailed ("Failed to create agent object! (AP A)", 88888)
	            Exit Do
	    	end if
	    	
			' Set the SSID on the access point to the new value
			oAgent.Ssid = newVal.Ssid
	        if(Not Err.Number = 0) then
	            Call oLog.SafeFailed ("oAgent.Ssid failed! (AP A) - " & Err.Description, 88888)
	            Exit Do
	        end if
	       	
	       	' Set the Transmit Key (WepIndex) on the access point to the new value
			oAgent.WepIndex = newVal.WepIndex
	        if(Not Err.Number = 0) then
	            Call oLog.SafeFailed ("oAgent.WepIndex failed! (AP A) - " & Err.Description, 88888)
	            Exit Do
	        end if
			
			m_oSnmp.CloseAgent()
	    	m_oRecordSet.Close()
	    		    		    	
	    loop while(false)
		
		' If the recordset is still opened.
		if(m_oRecordSet.State = 1) then
			m_oRecordSet.Close()
		end if
		
		m_oSnmp.CloseAgent()
		
	On Error Goto 0
		    	
	End Property
		
	'============================================================================================='
	'/**
	' * This property connects to the access point and querys the access point for specific information.
	' * The return values are placed in an access point class which is returned to the caller.
	' * @return
	' *	A reference to an access point class.
	' * @sa
	' *	CAccessPoint,CWlanEnvironment::AccessPointA
	' * @example
	' * Set oAP = oClass.AccessPointB
	' * if(oAP Is Nothing) then
	' * 	' Handle Error
	' *	end if
	' */
	Public Property Get AccessPointB
	Dim bRetval
	Dim oAgent
	
	On Error Resume Next
	
	    do
	    	' Connect to the remote agent
	    	m_oRecordSet.Open "SELECT * From Wlan_APB", m_oConnection, 2, 3
			bRetval = m_oSnmp.OpenAgent(m_oRecordSet("IPAddress") , "public")
			if(bRetval = false) then
				Call oLog.SafeFailed ("OpenAgent() failed! (AP B)", 88888)
			 	Exit Do
			end if
	    	
	    	' Create an agent object for the cisco access point
	    	Set oAgent = m_oSnmp.Agent("\\accesspoint\cisco")
			if(oAgent Is Nothing) then
	    		Call oLog.SafeFailed ("Failed to create agent object! (AP B)", 88888)
	            Exit Do
	    	end if
	    	
			' Get the SSID from the access point
			m_oAccessPointB.Ssid = oAgent.Ssid
	        if(Not Err.Number = 0) then
	            Call oLog.SafeFailed ("oAgent.Ssid failed! (AP B) - " & Err.Description, 88888)
	            Exit Do
	        end if
	       	
	       	' Get the Transmit Key (WepIndex) from the access point
 			m_oAccessPointB.WepIndex = oAgent.WepIndex
	        if(Not Err.Number = 0) then
	            Call oLog.SafeFailed ("oAgent.WepIndex failed! (AP B) - " & Err.Description, 88888)
	            Exit Do
	        end if
			
			m_oSnmp.CloseAgent()
	    	m_oRecordSet.Close()
	    		    		    	
	    loop while(false)
		
		' If the recordset is still opened.
		if(m_oRecordSet.State = 1) then
			m_oRecordSet.Close()
		end if
		
		m_oSnmp.CloseAgent()
		
		Set AccessPointB = m_oAccessPointB	
		
	On Error Goto 0
		    	
	End Property
	
	Public Property Set AccessPointB(newVal)
	Dim bRetval
	Dim oAgent
	
	On Error Resume Next
			
	    do
	    	' Connect to the remote agent
	    	m_oRecordSet.Open "SELECT * From Wlan_APB", m_oConnection, 2, 3
			bRetval = m_oSnmp.OpenAgent(m_oRecordSet("IPAddress") , "public")
			if(bRetval = false) then
				Call oLog.SafeFailed ("OpenAgent() failed! (AP A)", 88888)
			 	Exit Do
			end if
	    	
	    	' Create an agent object for the cisco access point
	    	Set oAgent = m_oSnmp.Agent("\\accesspoint\cisco")
			if(oAgent Is Nothing) then
	    		Call oLog.SafeFailed ("Failed to create agent object! (AP A)", 88888)
	            Exit Do
	    	end if
	    	
			' Set the SSID to new value 
			oAgent.Ssid = newVal.Ssid
	        if(Not Err.Number = 0) then
	            Call oLog.SafeFailed ("oAgent.Ssid failed! (AP A) - " & Err.Description, 88888)
	            Exit Do
	        end if
	       	
	       	' Set the Transmit Key (WepIndex) to new value
			oAgent.WepIndex = newVal.WepIndex
	        if(Not Err.Number = 0) then
	            Call oLog.SafeFailed ("oAgent.WepIndex failed! (AP A) - " & Err.Description, 88888)
	            Exit Do
	        end if
			
			m_oSnmp.CloseAgent()
	    	m_oRecordSet.Close()
	    		    		    	
	    loop while(false)
		
		' If the recordset is still opened.
		if(m_oRecordSet.State = 1) then
			m_oRecordSet.Close()
		end if
		
		m_oSnmp.CloseAgent()
		
	On Error Goto 0
		    	
	End Property
	
	'============================================================================================='
	'/**
	' * This function configures the access points using the parameters stored in the NDIS Test 
	' * database. Only the SSID and transmit key values are set here because the other options 
	' * should not change from one execution to the next.
	' * @return
	' *	If successful then this function will return true, otherwise false.
	' * @sa
	' * CWlanEnvironment::Configure
	' * @example
	' * bRetval = oClass.ConfigureAPs()
	' * if(bRetval = false) then
	' * 	' Handle Error
	' *	end if
	' */
	Public Function ConfigureAPs()
	Dim bRetval
	Dim oAgent
	
	On Error Resume Next
	
	    do
	    	' Connect to the remote agent
	    	m_oRecordSet.Open "SELECT * From Wlan_APA", m_oConnection, 2, 3
			bRetval = m_oSnmp.OpenAgent(m_oRecordSet("IPAddress") , "public")
			if(bRetval = false) then
				Call oLog.Write("Failed to open the SNMP agent! (AP A)")
			 	Exit Do
			end if
	    	
	    	' Create an agent object for the cisco access point
	    	Set oAgent = m_oSnmp.Agent("\\accesspoint\cisco")
			if(oAgent Is Nothing) then
	    		Call oLog.Write("Failed to create agent object! (AP A)")
	            Exit Do
	    	end if
	    	
			' Set the SSID 
			oAgent.Ssid = m_oRecordSet("Ssid")
	        if(Not Err.Number = 0) then
	            Call oLog.Write("Failed to set the SSID on the access point! (AP A) - " & Err.Description)
	            Exit Do
	        end if
	       	
	       	' Set the Transmit Key (WepIndex)
			oAgent.WepIndex = CLng(m_oRecordSet("WepIndex"))
	        if(Not Err.Number = 0) then
	            Call oLog.Write("Failed to set the transmit key (WepIndex) on the access point! (AP A) - " & Err.Description)
	            Exit Do
	        end if
			
			m_oSnmp.CloseAgent()
	    	m_oRecordSet.Close()
	    	
	    	' Connect to the remote agent
	    	m_oRecordSet.Open "SELECT * From Wlan_APB", m_oConnection, 2, 3
			bRetval = m_oSnmp.OpenAgent(m_oRecordSet("IPAddress") , "public")
			if(bRetval = false) then
				Call oLog.Write("Failed to open the SNMP agent! (AP B)")
			 	Exit Do
			end if
	    	
	    	' Create an agent object for the cisco access point
	    	Set oAgent = m_oSnmp.Agent("\\accesspoint\cisco")
	    	if(oAgent Is Nothing) then
	    		Call oLog.Write("Failed to create agent object! (AP B)")
	            Exit Do
	    	end if
			
			' Set the SSID 
			oAgent.Ssid = m_oRecordSet("Ssid")
	        if(Not Err.Number = 0) then
	            Call oLog.Write("Failed to set the SSID on the access point! (AP B) - " & Err.Description)
	            Exit Do
	        end if
	       	
	       	' Set the Transmit Key (WepIndex)
			oAgent.WepIndex = CLng(m_oRecordSet("WepIndex"))
	        if(Not Err.Number = 0) then
	            Call oLog.Write("Failed to set the transmit key (WepIndex) on the access point! (AP B) - " & Err.Description)
	            Exit Do
	        end if

	    	m_oSnmp.CloseAgent()
	    	m_oRecordSet.Close()
	    	
	    	ConfigureAPs = true
	    	
	    loop while(false)
		
		' If the recordset is still opened.
		if(m_oRecordSet.State = 1) then
			m_oRecordSet.Close()
		end if
		
		m_oSnmp.CloseAgent()
		
		WScript.Sleep(4000)
		
	On Error Goto 0

	End Function
	
	'============================================================================================='
	'
	'
	Public Function GetAPBssid(nAccessPoint)
	Dim bRetval
	Dim oAgent
	Dim sIPAddress, sSsid
	    
	    GetAPBssid = ""
	    
	    select case nAccessPoint
		case ACCESSPOINT_A
		    m_oRecordSet.Open "SELECT * From Wlan_APA", m_oConnection, 2, 3
		case ACCESSPOINT_B
		    m_oRecordSet.Open "SELECT * From Wlan_APB", m_oConnection, 2, 3
		end select
		
		sIPAddress  = m_oRecordSet("IPAddress")
		sSsid       = "NDTESTAPDisconnectState"
		
		m_oRecordSet.Close()
		
		do
	    	' Connect to the remote agent
			bRetval = m_oSnmp.OpenAgent(sIPAddress, "public")
			if(bRetval = false) then
				Call oLog.SafeFailed ("Failed to open agaent!", 88888)
			 	Exit Do
			end if
	    	
	    	' Create an agent object for the cisco access point
	    	Set oAgent = m_oSnmp.Agent("\\accesspoint\cisco")
			if(oAgent Is Nothing) then
	    		Call oLog.SafeFailed ("Failed to create agent object!", 88888)
	            Exit Do
	    	end if
	    	
			' Set the SSID on the access point to the new value
			GetAPBssid = oAgent.Bssid
	        if(Not Err.Number = 0) then
	            Call oLog.SafeFailed ("Failed to get AP BSSID! - " & Err.Description, 88888)
	            Exit Do
	        end if
	        	       
	        				    		    		    	
	    loop while(false)
	
	End Function
		
End Class
'<!-- CRC = 0x596ad87e --->
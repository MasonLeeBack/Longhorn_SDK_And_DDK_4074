'================================================================================================='
'/**
' * @date   4/26/2002
' * @author David Harding
' *
' * modified:
' * 2/26/2003 davhar
' * Adding new functionality ported from 4.03
'*/
'================================================================================================='
Option Explicit

'================================================================================================='
Class CWlanOpen
   Private m_oCLOpen
   Private m_sAdapterName
   Private m_oAdapter
   Private m_oAdapterOpen
   Private m_oCard
   Private m_nConnectionID
   Private m_sAdapterGUID
   Private m_nAdapterType
   Private m_IsWPASupported
   Private m_IsWPAAdhocSupported
   Private m_IsTKIPSupported
   Private m_IsAESSupported
    
   Private Sub Class_Initialize
      Set m_oCLOpen = Nothing
      
      m_sAdapterName             = ""
	   m_sAdapterGUID             = ""
	   m_IsWPASupported           = False
      m_IsWPAAdhocSupported      = False
      m_IsTKIPSupported          = False
      m_IsAESSupported           = False
      
   End Sub
   
   Private Sub Class_Terminate
     Set m_oCLOpen = Nothing
   End Sub
      
   '================================================================================================='
   '/**
   '@exclude
   'The set property that is used by a CLanCard object to set the connectionless open
   'object that is required by this class. It is a hack used to obtain some kind of 
   'inheritance structure in VBScript.
   '@params
   '! class This is the CCLOpen object that was created in the Card hierarchy
   '*/
   Public Property Set CLanOpen(p_oCLOpen)
     Set m_oCLOpen = p_oCLOpen
     Initialize()
   End Property
   
   '================================================================================================='
   Public Property Get COMOpen
     Set COMOpen = m_oCLOpen.COMOpen
   End Property
   
   '================================================================================================='
   Public Property Get NdisMedium
     NdisMedium = m_oCLOpen.NdisMedium
   End Property
   
   '================================================================================================='
   Public Property Get AdapterType
     AdapterType = m_oCLOpen.AdapterType
   End Property
   
   '================================================================================================='
   Public Property Get IsWPASupported
   
      IsWPASupported = m_IsWPASupported 
      
   End Property
   
   '================================================================================================='
   Public Property Get IsWPAAdhocSupported
   
      IsWPAAdhocSupported = m_IsWPAAdhocSupported 
      
   End Property
   
   '================================================================================================='
   Public Property Get IsTKIPSupported
   
      IsTKIPSupported = m_IsTKIPSupported 
      
   End Property
   
   '================================================================================================='
   Public Property Get IsAESSupported
   
      IsAESSupported = m_IsAESSupported 
      
   End Property
  
   '================================================================================================='
   Public Property Get vbConnectionID
   
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbConnectionID" & CWLAN_PRINT_END
      ConnectionID = m_nConnectionID
      
   End Property
   
   '================================================================================================='
   Public Property Get vbAdapterGUID
      
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAdapterGUID" & CWLAN_PRINT_END
      vbAdapterGUID = m_sAdapterGUID
      
   End Property 
    
   '================================================================================================='
    Public Property Get vbAdapter
    
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAdapter" & CWLAN_PRINT_END
      Set vbAdapter = m_oCard
      
    End Property
    
   '================================================================================================='
    Public Property Get vbAdapterOpen
 
      Set vbAdapterOpen = m_oCLOpen
      
    End Property
    
   '================================================================================================='
    Public Property Let vbAdapterOpen(byref newVal)
   
      Set m_oCLOpen = newVal
      
    End Property
    
   '########################################################## NEW INCLUSION #########################################################
   
   Private Function Initialize()           
   
      m_oCLOpen.vbNdisOpen()
      
		' ' Get Adapter collection
' 		Set oAdapterList = oNDInfo.AdapterList
' 		If(oAdapterList Is Nothing) Then
' 	      oLog.Failed "vbCreateAdapter() Failed to access adapter list!", 88888
' 			Exit Function
' 		End If
' 		
' 		' Store adapter related info.
' 		m_nConnectionID   = nConnectionID
' 		m_sAdapterGUID    = oAdapterList(nConnectionID).GUID
' 		m_nAdapterType    = oAdapterList(nConnectionID).AdapterType
		        	   	   
	   ' Does driver support WPA
      If(vbIsWPASupported() = True) Then
         m_IsWPASupported = True
      End If
      
      ' Does driver support WPA in adhoc mode
      If(vbIsWPAAdhocSupported() = True) Then
         m_IsWPAAdhocSupported = True
      End If
      
      ' Does driver support TKIP
      If(vbIsTKIPSupported() = True) Then
         m_IsTKIPSupported = True
      End If
      
      ' Does driver support AES
      If(vbIsAESSupported() = True) Then
         m_IsAESSupported = True
      End If
	   
	   ' If the driver does not support WPA then reset the encryption strings
	   If(m_IsWPASupported = False) Then
	       	   
	      g_aEncryptionStatus  = Array("Ndis802_11WEPEnabled",     _
                                      "Ndis802_11WEPDisabled",    _
                                      "Ndis802_11WEPKeyAbsent",   _
                                      "Ndis802_11WEPNotSupported")
	   End If
	   
	   ' Reset the device
	   vbResetDevice()
	   
	   m_oCLOpen.vbNdisClose
	  	 		
   End Function
   
   '================================================================================================='
   Public Function vbNetworkTypeInUseGE(byref nNetworkTypeInUse)	
   
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbNetworkTypeInUseGE" & CWLAN_PRINT_END & vbCrLf 
	   
	   vbNetworkTypeInUseGE = vbNetworkTypeInUse(CWLAN_OID_QUERY, nNetworkTypeInUse)
	         
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbNetworkTypeInUseGE) & "</b>" & vbCrLf
      		
	End Function
	
	'================================================================================================='
   Public Function vbNetworkTypeInUseSE(byval nNetworkTypeInUse)	
   
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbNetworkTypeInUseSE" & CWLAN_PRINT_END & vbCrLf 
	   
	   vbNetworkTypeInUseSE = vbNetworkTypeInUse(CWLAN_OID_SET, nNetworkTypeInUse)
	         
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbNetworkTypeInUseSE) & "</b>" & vbCrLf
      		
	End Function
	
	'================================================================================================='
	Public Function vbNdisRequest2(byval nOID, byref oObjStruct, byval nType, byref nNdisStatus)
    Dim bRetval : bRetval = False
        
        bRetval = m_oCLOpen.COMOpen.NdisRequest2(nOID, oObjStruct, nType, nNdisStatus)
        If(bRetval = False) Then
            Exit Function
        End If	
        
        vbNdisRequest2 = True
        
    End Function
    
   '================================================================================================='
   Public Function vbNetworkTypeInUse(byval nType, byref nNetworkTypeInUse)	
   Dim oUlong        : Set oUlong   = Nothing
   Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
		
		vbNetworkTypeInUse = nNdisStatus
			      
		Set oUlong = CreateObject("StructRep.SO_ULONG.1")
      If(oUlong Is Nothing) Then
         oLog.Failed "vbNetworkTypeInUse(): Failed to create ULONG structure object", 88888
         Exit Function
      End If
   	
		If(nType = CWLAN_OID_SET) Then
		   If(nNetworkTypeInUse > UBound(g_aNetworkTypesSupported)) Then
            oLog.Write "NetworkTypeInUse = Invalid " & "(" & nNetworkTypeInUse & ")"
         Else  
            oLog.Write "NetworkTypeInUse = " & g_aNetworkTypesSupported(nNetworkTypeInUse) & "(" & nNetworkTypeInUse & ")"
         End If
		End If
		
		oUlong.Ulong = nNetworkTypeInUse
	   
	   nNdisStatus = NdisRequestEx(nType, OID_802_11_NETWORK_TYPE_IN_USE, oUlong)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
			
    	nNetworkTypeInUse = oUlong.Ulong
    	
    	If(nType = CWLAN_OID_QUERY AND nNdisStatus = NDIS_STATUS_SUCCESS) Then
		   If(nNetworkTypeInUse > UBound(g_aNetworkTypesSupported)) Then
            oLog.Write "NetworkTypeInUse = Invalid"
         Else  
            oLog.Write "NetworkTypeInUse = " & g_aNetworkTypesSupported(nNetworkTypeInUse) & "(" & nNetworkTypeInUse & ")"
         End If
		End If
    	
		vbNetworkTypeInUse = nNdisStatus
		
	End Function
	
	'================================================================================================='
   Public Function vbSupportedRatesGE(byref aRates)	
   
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbSupportedRatesGE" & CWLAN_PRINT_END & vbCrLf 
	   
	   vbSupportedRatesGE = vbSupportedRates(CWLAN_OID_QUERY, aRates)
	         
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbSupportedRatesGE) & "</b>" & vbCrLf
      		
	End Function
	
	'================================================================================================='
   ' Public Function vbSupportedRatesSE(byval nNetworkTypeInUse)	
'    
'       oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbNetworkTypeInUseSE" & CWLAN_PRINT_END & vbCrLf 
' 	   
' 	   vbNetworkTypeInUseSE = vbNetworkTypeInUse(CWLAN_OID_SET, nNetworkTypeInUse)
' 	         
'       oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbNetworkTypeInUseSE) & "</b>" & vbCrLf
'       		
' 	End Function
	
   '================================================================================================='
   Public Function vbSupportedRates(byval nType, byref aRates)	
   Dim oRates        : Set oRates   = Nothing
   Dim bRetval       : bRetval      = False
   Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE

      vbSupportedRates = nNdisStatus
      	      
      Set oRates = CreateObject("StructRep.SO_NDIS_802_11_RATES_EX.1")
      If(oRates Is Nothing) Then
         oLog.Failed "vbSupportedRates(): Failed to create NDIS_802_11_RATES_EX structure object", 88888
         Exit Function
      End If
      	   
      nNdisStatus = NdisRequestEx(nType, OID_802_11_SUPPORTED_RATES, oRates)
      If(nNdisStatus = GENERIC_FAILURE) Then
         Exit Function
      End If
      	                     
      If(nType = CWLAN_OID_QUERY AND nNdisStatus = NDIS_STATUS_SUCCESS) Then
         aRates = oRates.SupportedRates
         If(IsArray(aRates) = True) Then
            Dim i       : i      = 0
            Dim sByte   : sByte  = ""
            For i = LBound(aRates) To UBound(aRates)
               sByte = sByte & " " & Hex(aRates(i))
            Next     
            oLog.Write "SupportedRates: " & sByte
         End If      
      End If
      	
      vbSupportedRates = nNdisStatus

   End Function
	
	'================================================================================================='
   Public Function NdisRequestEx(byval requestType, byval oidVal, byref oidData)
   Dim ndisStatus : ndisStatus   = GENERIC_FAILURE
   Dim returnVal  : returnVal    = False

      NdisRequestEx = ndisStatus

      returnVal = Me.vbNdisRequest2(oidVal, oidData, requestType, ndisStatus)
      If(returnVal = False) Then
         oLog.Failed "NdisRequestEx(): NdisRequest2() failed!", 88888
         Exit Function
      End If

      NdisRequestEx = ndisStatus 

   End Function
	
	'================================================================================================='
   Public Function vbNetworkTypesSuppportedGE(byref aNetList)	
   
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbNetworkTypesSuppportedGE" & CWLAN_PRINT_END & vbCrLf 
	   
	   vbNetworkTypesSuppportedGE = vbNetworkTypesSupported(CWLAN_OID_QUERY, aNetList)
	         
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbNetworkTypesSuppportedGE) & "</b>" & vbCrLf
      		
	End Function
	
   '================================================================================================='
   Public Function vbNetworkTypesSupported(byval nType, byref aNetList)	
   Dim oNetList      : Set oNetList = Nothing
   Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
   Dim nIndex        : nIndex       = 0
   
		vbNetworkTypesSupported = nNdisStatus
		
		Set oNetList = CreateObject("StructRep.SO_NDIS_802_11_NETWORK_TYPE_LIST.1")
      If(oNetList Is Nothing) Then
         oLog.Failed "vbNetworkTypesSupported(): Failed to create NDIS_802_11_NETWORK_TYPE_LIST structure object", 88888
         Exit Function
      End If
     
      nNdisStatus = NdisRequestEx(nType, OID_802_11_NETWORK_TYPES_SUPPORTED, oNetList)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
		    	
    	aNetList = oNetList.NetworkTypesSupported
    	
    	If(nType = CWLAN_OID_QUERY AND nNdisStatus = NDIS_STATUS_SUCCESS) Then
    	   
    	   oLog.Write("NumberOfItems = " & oNetList.NumberOfItems)
    	   
		   For nIndex = LBound(aNetList) To UBound(aNetList)
		      If(aNetList(nIndex) > UBound(g_aNetworkTypesSupported)) Then
               oLog.Write "NetworkType = Invalid"
            Else  
               oLog.Write "NetworkType = " & g_aNetworkTypesSupported(aNetList(nIndex)) & "(" & aNetList(nIndex) & ")"
            End If
		   Next
		End If
    	    	
		vbNetworkTypesSupported = nNdisStatus
		
	End Function
	
	'================================================================================================='
   '/**
   ' This function is used to disassocate the wireless device with the current AP or IBSS node.
   ' @params
   ' ! boolean Specfies if the disconnect, should be verified.
   ' @returns
   ' NDIS_STATUS_SUCCESS if successful, otherwise returns the NDIS_STATUS specified by the driver.
   '*/
   Public Function vbDisassociateSE()
	     
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbDisassociateSE" & CWLAN_PRINT_END
            
	 vbDisassociateSE = vbDisassociate(CWLAN_OID_SET)

      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbDisassociateSE) & "</b>" & vbCrLf
		
	End Function
	
	'================================================================================================='
   Private Function vbDisassociate(byval nType)
   Dim oNull                    : Set oNull             = Nothing
   Dim bRetval                : bRetval               = False
   Dim nNdisStatus         : nNdisStatus         = GENERIC_FAILURE
   Dim nConnectStatus   : nConnectStatus   = 0

      vbDisassociate = nNdisStatus
       
      Set oNull = CreateObject("StructRep.SO_NULL.1")
      If(oNull Is Nothing) Then
         oLog.Failed "vbDisassociate(): Failed to create NULL structure object", 88888
         Exit Function
      End If
      		
      nNdisStatus = NdisRequestEx(nType, OID_802_11_DISASSOCIATE, oNull)
      If(nNdisStatus = GENERIC_FAILURE) Then
         Exit Function
      End If

      Wscript.Sleep(1000)
      	                             		
      vbDisassociate = nNdisStatus

   End Function
	
	'================================================================================================='
   '/**
   ' This function is used to set the infrastrucutre mode on the device.
   ' @params
   ' ! number Infrastructure mode value to set.
   ' @returns
   ' NDIS_STATUS_SUCCESS if successful, otherwise returns an NDIS_STATUS failure code.
   '*/
   Public Function vbInfrastructureSE(byval nInfrastructureMode)	
      
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbInfrastructureSE" & CWLAN_PRINT_END  
            	              	
    	vbInfrastructureSE = vbInfrastructure(CWLAN_OID_SET, nInfrastructureMode)              		
		
		oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbInfrastructureSE) & "</b>" & vbCrLf
		
	End Function
	
	'================================================================================================='
   '/**
   ' This function is used to retreive the current infrastrucutre mode in use.
   ' @params
   ' ! number Reference to a variable that will receive the infrastructure mode.
   ' @returns
   ' NDIS_STATUS_SUCCESS if successful, otherwise returns an NDIS_STATUS failure code.
   '*/
   Public Function vbInfrastructureGE(byref nInfrastructureMode)	
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbInfrastructureGE" & CWLAN_PRINT_END & vbCrLf 
	   
	   vbInfrastructureGE = vbInfrastructure(CWLAN_OID_QUERY, nInfrastructureMode)
	         
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbInfrastructureGE) & "</b>" & vbCrLf
       		
	End Function
	
	'================================================================================================='
   Private Function vbInfrastructure(byval nType, byref nInfrastructureMode)	
   Dim oUlong        : Set oUlong   = Nothing
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
		
		vbInfrastructure = nNdisStatus
		
      Set oUlong = CreateObject("StructRep.SO_ULONG.1")
      If(oUlong Is Nothing) Then
         oLog.Failed "vbInfrastructure(): Failed to create ULONG structure object", 88888
         Exit Function
      End If
        
		If(nType = CWLAN_OID_SET) Then
		   If(nInfrastructureMode > UBound(g_aInfrastructureMode)) Then
            oLog.Write "Infrastructure Mode = Invalid"
         Else  
            oLog.Write "Infrastructure Mode = " & g_aInfrastructureMode(nInfrastructureMode) & "(" & nInfrastructureMode & ")"
         End If
		End If
		
		oUlong.Ulong = nInfrastructureMode
		
		nNdisStatus = NdisRequestEx(nType, OID_802_11_INFRASTRUCTURE_MODE, oUlong)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
    			    	
    	nInfrastructureMode = oUlong.Ulong
    	
    	If(nType = CWLAN_OID_QUERY And nNdisStatus = NDIS_STATUS_SUCCESS) Then
		   If(nInfrastructureMode > UBound(g_aInfrastructureMode)) Then
            oLog.Write "Infrastructure Mode = Invalid"
         Else  
            oLog.Write "Infrastructure Mode = " & g_aInfrastructureMode(nInfrastructureMode) & "(" & nInfrastructureMode & ")"
         End If
		End If
    	
		vbInfrastructure = nNdisStatus
		
	End Function
		
	'================================================================================================='
   '/**
   ' This function is used to set the authentication mode for the driver to use.
   ' @params
   ' ! number A value that is the authentication mode to use.
   ' @returns
   ' NDIS_STATUS_SUCCESS if successful, otherwise returns an NDIS_STATUS failure code.
   '*/
   Public Function vbAuthenticationSE(byval nAuthenticationMode)
      
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAuthenticationSE"& CWLAN_PRINT_END   
                      
      vbAuthenticationSE = vbAuthentication(CWLAN_OID_SET, nAuthenticationMode)
	   
	   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbAuthenticationSE) & "</b>" & vbCrLf
    	
	End Function
	
	'================================================================================================='
   '/**
   ' This function is used to get the authentication mode the driver is currently using.
   ' @params
   ' ! number Reference to a variable the will receive the authentication mode.
   ' !returns
   ' NDIS_STATUS_SUCCESS if successful, otherwise returns an NDIS_STATUS failure code.
   '*/
   Public Function vbAuthenticationGE(byref nAuthenticationMode)
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAuthenticationGE" & CWLAN_PRINT_END     
	   
	   vbAuthenticationGE = vbAuthentication(CWLAN_OID_QUERY, nAuthenticationMode)
	          	
    	oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbAuthenticationGE) & "</b>" & vbCrLf
    	
	End Function
	
	'================================================================================================='
   Private Function vbAuthentication(byval nType, byref nAuthenticationMode)
	Dim oUlong        : Set oUlong   = Nothing
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
		
		vbAuthentication = nNdisStatus
		
		Set oUlong = CreateObject("StructRep.SO_ULONG.1")
      If(oUlong Is Nothing) Then
         oLog.Failed "vbAuthentication(): Failed to create ULONG structure object", 88888
         Exit Function
      End If
      
		If(nType = CWLAN_OID_SET) Then
		   If(nAuthenticationMode > UBound(g_aAuthenticationMode)) Then
            oLog.Write "Authentication Mode = Invalid (" & nAuthenticationMode & ")"
         Else  
            oLog.Write "Authentication Mode = " & g_aAuthenticationMode(nAuthenticationMode) & "(" & nAuthenticationMode & ")"
         End If
		End If
		
		oUlong.Ulong = nAuthenticationMode
		
		nNdisStatus = NdisRequestEx(nType, OID_802_11_AUTHENTICATION_MODE, oUlong)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
		    						
		nAuthenticationMode = oUlong.Ulong
    	
    	If(nType = CWLAN_OID_QUERY AND nNdisStatus = NDIS_STATUS_SUCCESS) Then
		   If(nAuthenticationMode > UBound(g_aAuthenticationMode)) Then
            oLog.Write "Authentication Mode = Invalid (" & nAuthenticationMode & ")"
         Else  
            oLog.Write "Authentication Mode = " & g_aAuthenticationMode(nAuthenticationMode) & "(" & nAuthenticationMode & ")"
         End If
		End If
		
		vbAuthentication = nNdisStatus
				
	End Function
   
   '================================================================================================='
   '/**
   ' This function is used to set the encryption status for the driver to use.
   ' @params
   ' ! number A value that is the new encryption status to use.
   ' !returns
   ' NDIS_STATUS_SUCCESS if successful, otherwise returns an NDIS_STATUS failure code
   '*/
   Public Function vbEncryptionSE(byval nEncryption)
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbEncryptionSE" & CWLAN_PRINT_END   
                      
      vbEncryptionSE = vbEncryption(CWLAN_OID_SET, nEncryption)
	   
	   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbEncryptionSE) & "</b>" & vbCrLf
	   			
	End Function
	
	'================================================================================================='
   '/**
   ' This function is used to get the encryption status the driver is currently using.
   ' @params
   ' ! number Reference to a variable the will receive the authentication mode.
   ' !returns
   ' NDIS_STATUS_SUCCESS if successful, otherwise returns an NDIS_STATUS failure code.
   '*/
   Public Function vbEncryptionGE(byref nEncryption)
	
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbEncryptionGE" & CWLAN_PRINT_END & vbCrLf     
	   
	   vbEncryptionGE = vbEncryption(CWLAN_OID_QUERY, nEncryption)
	          	
    	oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbEncryptionGE) & "</b>" & vbCrLf
				
	End Function
				
	'================================================================================================='
   Private Function vbEncryption(byval nType, Byref nEncryption)
	Dim oUlong        : Set oUlong   = Nothing
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
		
		vbEncryption = nNdisStatus
		
		Set oUlong = CreateObject("StructRep.SO_ULONG.1")
      If(oUlong Is Nothing) Then
         oLog.Failed "vbInfrastructure(): Failed to create ULONG structure object", 88888
         Exit Function
      End If
   	
		If(nType = CWLAN_OID_SET) Then
		   If(nEncryption > UBound(g_aEncryptionStatus)) Then
            oLog.Write "Encryption = Invalid"
         Else  
            oLog.Write "Encryption = " & g_aEncryptionStatus(nEncryption) & "(" & nEncryption & ")"
         End If
		End If
		
		oUlong.Ulong = nEncryption
		
		nNdisStatus = NdisRequestEx(nType, OID_802_11_ENCRYPTION_STATUS, oUlong)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
		
		nEncryption = oUlong.Ulong
		
		If(nType = CWLAN_OID_QUERY AND nNdisStatus = NDIS_STATUS_SUCCESS) Then
		   If(nEncryption > UBound(g_aEncryptionStatus)) Then
            oLog.Write "Encryption = Invalid"
         Else  
            oLog.Write "Encryption = " & g_aEncryptionStatus(nEncryption) & "(" & nEncryption & ")"
         End If
		End If
                      		
		vbEncryption = nNdisStatus
				
	End Function
	
	'================================================================================================='
	'/**
	' This function is used to set the new SSID value of the STA or AP to associate with.
	' @params
	' ! string A string that is the SSID of the STA or AP to associate with.
	' @returns
	' NDIS_STATUS_SUCCESS if successful, otherwise returns an NDIS_STATUS failure code.
	' */ 	
   Public Function vbSsidSE(byval sSsid)
      
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbSsidSE" & CWLAN_PRINT_END   
            	              	
    	vbSsidSE = vbSsid(CWLAN_OID_SET, sSsid)              		
		
		oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbSsidSE) & "</b>" & vbCrLf
      		
   End Function
    
   '================================================================================================='
   Public Function vbSsidGE(byref sSsid)
         
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbSsidGE" & CWLAN_PRINT_END
	   
	   vbSsidGE = vbSsid(CWLAN_OID_QUERY, sSsid)
	         
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbSsidGE) & "</b>" & vbCrLf
      		
   End Function
    
   '================================================================================================='
   Private Function vbSsid(byval nType, byref sSsid)
   Dim oSsid            : Set oSsid       = Nothing
   Dim bRetval          : bRetval         = False
   Dim nNdisStatus      : nNdisStatus     = GENERIC_FAILURE
   Dim nStartTime       : nStartTime	   = 0
   Dim nEndTime         : nEndTime        = 0
   Dim nTimeout         : nTimeout        = 0
   Dim nConnectStatus   : nConnectStatus  = 0
		
	   vbSsid = nNdisStatus
	   
	   Set oSsid = CreateObject("StructRep.SO_NDIS_802_11_SSID.1")
      If(oSsid Is Nothing) Then
         oLog.Failed "vbSsid(): Failed to create NDIS_802_11_SSID structure object", 88888
         Exit Function
      End If
      
	   oSsid.Ssid = sSsid
	   
	   If(nType = CWLAN_OID_SET) Then
		   oLog.Write "SSID = " & oSsid.Ssid
		End If
		
		nNdisStatus = NdisRequestEx(nType, OID_802_11_SSID, oSsid)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
      
      If(nType = CWLAN_OID_SET) Then
         WaitForAssociation(WLAN_SSID_TIMEOUT / 1000)
      End If
          
      If(nType = CWLAN_OID_QUERY AND nNdisStatus = NDIS_STATUS_SUCCESS) Then
         sSsid = oSsid.Ssid
		   oLog.Write "SSID = " & sSsid
		End If
		                             		
		vbSsid = nNdisStatus
		
    End Function
   
   '================================================================================================='
   Private Function WaitForAssociation(byval timeOut)
   Dim nStartTime       : nStartTime      = Timer
   Dim nEndTime         : nEndTime        = 0 
   Dim nTimeout         : nTimeout        = 0
   Dim nConnectStatus   : nConnectStatus  = 0
   Dim nNdisStatus      : nNdisStatus     = GENERIC_FAILURE
   
      WaitForAssociation = False
   
      Do 
        
         WScript.Sleep(1000)
         nEndTime = Timer
         nTimeout = nEndTime - nStartTime
         
         oLog.MaskWrite()
         If(vbMediaConnectStatus(nConnectStatus) = False) Then
            oLog.Write "WaitForAssociation(): Failed to get MediaConnectStatus"
            oLog.UnMaskWrite
            Exit Do
         End If
         oLog.UnMaskWrite
                  
         If(nConnectStatus = CWLAN_MEDIA_CONNECTED) Then
            oLog.Write("Associate Time: " & nEndTime - nStartTime & " second(s)")
            WaitForAssociation = True
            Exit Do
         End If
         
         If(nTimeout > timeOut) Then
            oLog.Write "Device not connected within " & WLAN_SSID_TIMEOUT / 1000 & " seconds"
            Exit Do
         End If
         
      Loop
          
   End Function
   
   '================================================================================================='
   Public Function vbAssociate(byval nInfraMode, byval nAuthMode, byval sSsid, byval bVerifyConnect)
   Dim sCurrentSsid     : sCurrentSsid    = ""
   Dim bRetval          : bRetval         = False
   Dim nNdisStatus      : nNdisStatus     = GENERIC_FAILURE
   Dim nConnectStatus   : nConnectStatus  = 0
   
      vbAssociate = nNdisStatus
   	
   	oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAssociate" & CWLAN_PRINT_END
      oLog.Write "- InfrastructureMode   = "   & g_aInfrastructureMode(nInfraMode)
      oLog.Write "- AuthenticationMode   = "   & g_aAuthenticationMode(nAuthMode)
      oLog.Write "- SSID                 = "   & sSsid
      oLog.Write "- CheckConnection      = "   & bVerifyConnect
            	
      Do 
         
         nNdisStatus = vbInfrastructureSE(nInfraMode)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
       
         nNdisStatus = vbAuthenticationSE(nAuthMode)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) then
             Exit Do
         End If
                           
 		   nNdisStatus = vbSsidSE(sSsid)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) then
             Exit Do
         End If
         
         If(bVerifyConnect = True) Then    
                           	
            If(vbMediaConnectStatus(nConnectStatus) = False) Then
               oLog.Write "vbAssociate() - vbMediaConnectStatus() failed!"
               nNdisStatus = GENERIC_FAILURE
               Exit Do
            End If
                        
            nNdisStatus = vbSsidGe(sCurrentSsid)
            If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
                Exit Do
            End If
                
            If((nConnectStatus = CWLAN_MEDIA_DISCONNECTED) Or (Not sCurrentSsid = sSsid)) then
                oLog.Write "vbAssociate() - Failed to associate with " & sSsid & "!"
                nNdisStatus = GENERIC_FAILURE
                Exit Do
            End If
                        
         End If
         
     Loop While(False)
 			      	    
     vbAssociate = nNdisStatus
     
     'oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(nNdisStatus) & "</b>" & vbCrLf
        
    End Function
    
   '================================================================================================='
   Public Function vbAssociateWPA(byval nInfraMode, byval nAuthMode, byval nEncryption, byval sSsid, byval bVerifyConnect)
   Dim sCurrentSsid     : sCurrentSsid    = ""
   Dim bRetval          : bRetval         = False
   Dim nNdisStatus      : nNdisStatus     = GENERIC_FAILURE
   Dim nConnectStatus   : nConnectStatus  = 0
   
      vbAssociateWPA = nNdisStatus
   	
   	oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAssociateWPA" & CWLAN_PRINT_END
      oLog.Write "- InfrastructureMode   = "   & g_aInfrastructureMode(nInfraMode)
      oLog.Write "- AuthenticationMode   = "   & g_aAuthenticationMode(nAuthMode)
      oLog.Write "- Encryption           = "   & g_aEncryptionStatus(nEncryption)
      oLog.Write "- SSID                 = "   & sSsid
      oLog.Write "- CheckConnection      = "   & bVerifyConnect
            	
      Do 
        
         nNdisStatus = vbInfrastructureSE(nInfraMode)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
       
         nNdisStatus = vbAuthenticationSE(nAuthMode)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) then
             Exit Do
         End If
         
         nNdisStatus = vbEncryptionSE(nEncryption)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) then
             Exit Do
         End If
                           
 		   nNdisStatus = vbSsidSE(sSsid)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) then
             Exit Do
         End If
         
         If(bVerifyConnect = True) Then    
                           	
            If(vbMediaConnectStatus(nConnectStatus) = False) Then
               oLog.Write "vbAssociateWPA(): vbMediaConnectStatus() failed!"
               nNdisStatus = GENERIC_FAILURE
               Exit Do
            End If
                        
            nNdisStatus = vbSsidGe(sCurrentSsid)
            If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
                Exit Do
            End If
                
            If((nConnectStatus = CWLAN_MEDIA_DISCONNECTED) Or (Not sCurrentSsid = sSsid)) then
                oLog.Write "vbAssociateWPA(): Failed to associate with " & sSsid & "!"
                nNdisStatus = GENERIC_FAILURE
                Exit Do
            End If
                        
         End If
         
     Loop While(False)
 			      	    
     vbAssociateWPA = nNdisStatus
     
     'oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(nNdisStatus) & "</b>" & vbCrLf
        
    End Function
    
   '================================================================================================='
   Public Function vbAssociateEx(byval nInfraMode, byval nAuthMode, byval sSsid, byval nKeyIndex, byval sKeyMaterial, byval nEncryption, byval bVerifyConnect)
   Dim sCurrentSsid     : sCurrentSsid    = ""
   Dim bRetval          : bRetval         = False
   Dim nNdisStatus      : nNdisStatus     = GENERIC_FAILURE
   Dim nConnectStatus   : nConnectStatus  = 0
   
      vbAssociateEx = nNdisStatus
   	
   	oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAssociateEx" & CWLAN_PRINT_END
      oLog.Write "- InfrastructureMode   = "   & g_aInfrastructureMode(nInfraMode)
      oLog.Write "- AuthenticationMode   = "   & g_aAuthenticationMode(nAuthMode)
      oLog.Write "- SSID                 = "   & sSsid
      oLog.Write "- KeyIndex             = 0x" & Hex(nKeyIndex)
      oLog.Write "- KeyMaterial          = "   & sKeyMaterial
      oLog.Write "- Encryption           = "   & g_aEncryptionStatus(nEncryption)
      oLog.Write "- CheckConnection      = "   & bVerifyConnect
            	
      Do 
                     
         nNdisStatus = vbInfrastructureSE(nInfraMode)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
       
         nNdisStatus = vbAuthenticationSE(nAuthMode)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) then
             Exit Do
         End If
         
         nNdisStatus = vbAddWepSE(nKeyIndex, sKeyMaterial)
   	   If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
   	      Exit Do
   	   End If
   	
         nNdisStatus = vbWepStatusSE(nEncryption)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
                           
 		   nNdisStatus = vbSsidSE(sSsid)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) then
             Exit Do
         End If
         
         If(bVerifyConnect = True) Then    
            
            If(vbMediaConnectStatus(nConnectStatus) = False) Then
               oLog.Write "vbAssociateEx(): Failed to get media connect status"
               nNdisStatus = GENERIC_FAILURE
               Exit Do
            End If
             	                                       	                        
            nNdisStatus = vbSsidGe(sCurrentSsid)
            If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
                Exit Do
            End If
                
            If((nConnectStatus = CWLAN_MEDIA_DISCONNECTED) Or (Not sCurrentSsid = sSsid)) then
                nNdisStatus = GENERIC_FAILURE
                Exit Do
            End If
                        
         End If
         
     Loop While(False)
 			      	    
     vbAssociateEx = nNdisStatus
     
     'oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(nNdisStatus) & "</b>" & vbCrLf
        
    End Function
       
   '================================================================================================='
   Public Function vbBssidGE(byref oBssid)

      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbBssidGE" & CWLAN_PRINT_END & vbCrLf     

      vbBssidGE = vbBssid(CWLAN_OID_QUERY, oBssid)
                     
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbBssidGE) & "</b>" & vbCrLf
   			
   End Function
	
   '================================================================================================='
   Private Function vbBssid(byval nType, byref oBssid)
   Dim bRetval     : bRetval       = False
   Dim nNdisStatus : nNdisStatus   = GENERIC_FAILURE

      vbBssid = nNdisStatus

      nNdisStatus = NdisRequestEx(nType, OID_802_11_BSSID, oBssid)
      If(nNdisStatus = GENERIC_FAILURE) Then
         Exit Function
      End If

      If(nType = CWLAN_OID_QUERY) Then
         oLog.Write "BSSID = " & oBssid.Bssid
      End If
                       		
      vbBssid = nNdisStatus
   	
   End Function
   
   '================================================================================================='
	Public Function vbRemoveKeySE(byval nKeyIndex, byval vMacAddr)
	
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbRemoveKeySE" & CWLAN_PRINT_END   
	   
      oLog.Write "- KeyIndex     = 0x" & Hex(nKeyIndex)
      If(TypeName(vMacAddr) = "String") Then
 	      oLog.Write "- BSSID        = " & vMacAddr
 	   ElseIf(IsObject(vMacAddr) = True) Then
 	      oLog.Write "- BSSID        = " & vMacAddr.Bssid
 	   End If
 	   
      vbRemoveKeySE = vbRemoveKey(CWLAN_OID_SET, nKeyIndex, vMacAddr)
	  
	   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbRemoveKeySE) & "</b>" & vbCrLf
	   		
	End Function
	
	'================================================================================================='
	Public Function vbRemoveKey(byval nType, byval nKeyIndex, byval vMacAddr)
	Dim oRemoveKey    : Set oRemoveKey  = Nothing
	Dim oMacAddr      : Set oMacAddr    = Nothing
	Dim bRetval       : bRetval         = False
	Dim nNdisStatus   : nNdisStatus     = GENERIC_FAILURE
		
		vbRemoveKey = nNdisStatus	
		
		Set oRemoveKey = CreateObject("StructRep.SO_NDIS_802_11_REMOVE_KEY.1")
      If(oRemoveKey Is Nothing) Then
         oLog.Failed "Failed to create NDIS_802_11_REMOVE_KEY structure object", 88888
         Exit Function
      End If
      
      Set oMacAddr = CreateObject("StructRep.SO_NDIS_802_11_MAC_ADDRESS.1")
      If(oMacAddr Is Nothing) Then
         oLog.Failed "Failed to create NDIS_802_11_MAC_ADDRESS structure object", 88888
         Exit Function
      End If

		oRemoveKey.KeyIndex = nKeyIndex
		
		If(TypeName(vMacAddr) = "String") Then
        oMacAddr.Byte1   = CByte(&HFF&)
        oMacAddr.Byte2   = CByte(&HFF&)
        oMacAddr.Byte3   = CByte(&HFF&)
        oMacAddr.Byte4   = CByte(&HFF&)
        oMacAddr.Byte5   = CByte(&HFF&)
        oMacAddr.Byte6   = CByte(&HFF&) 
 	     oRemoveKey.Bssid   = oMacAddr
 	   ElseIf(IsObject(vMacAddr) = True) Then
 	      oRemoveKey.Bssid = vMacAddr
 	   Else
 	      oLog.Write("Invalid MacAddr type specified!")
 	      Exit Function
 	   End If
 	   	
 	   nNdisStatus = NdisRequestEx(nType, OID_802_11_REMOVE_KEY, oRemoveKey)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If

      oLog.Write "KeyIndex    = 0x"   & Hex(nKeyIndex)
      If(TypeName(vMacAddr) = "String") Then
 	   oLog.Write "KeyBssid    = "     & vMacAddr
 	   ElseIf(IsObject(vMacAddr) = True) Then
 	   oLog.Write "KeyBssid    = "     & vMacAddr.Bssid  
 	   End If
      oLog.Write ""
				
		vbRemoveKey = nNdisStatus
		
	End Function
			
	'================================================================================================='
   '/**
   ' This function will cause the driver to flush all keys previously added through the ADD_KEY OID.
   '*/	
	Public Function vbRemoveAllKeys()
	Dim nNdisStatus         : nNdisStatus           = NDIS_STATUS_FAILURE
   Dim nIndex              : nIndex                = 0
      
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbRemoveAllKeys" & CWLAN_PRINT_END  
	   
	   vbRemoveAllKeys = nNdisStatus
	   
	   oLog.MaskWrite()   
	   
      Do
	      
	      ' If the device supports WPA
	      If(m_IsWPASupported = True) Then
	      	         
            ' The scripts will never use more than 4 group keys
            ' so this should remove all the group keys added by the test.
            For nIndex = 0 To 3
               vbRemoveAllKeys = vbRemoveKey(CWLAN_OID_SET, nIndex, CWLAN_KEY_DEFAULT)
               If(vbRemoveAllKeys <> NDIS_STATUS_SUCCESS) Then
                  Exit Do         
               End If
            Next
            
            ' This should remove all the pairwise keys
            vbRemoveAllKeys = vbRemoveKey(CWLAN_OID_SET, &H40000000&, CWLAN_KEY_DEFAULT)
            If(vbRemoveAllKeys <> NDIS_STATUS_SUCCESS) Then
               Exit Do         
            End If
            
         Else
         
            ' The scripts will never use more than three group keys
            ' so this should remove all the group keys added by the test.
            For nIndex = 0 To 3
            
               vbRemoveAllKeys = vbRemoveWep(CWLAN_OID_SET, nIndex)
               If(vbRemoveAllKeys <> NDIS_STATUS_SUCCESS) Then
                  Exit Do         
               End If
            
            Next
            
         End If
         
      Loop While(False)
      
      oLog.UnMaskWrite()
      
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbRemoveAllKeys) & "</b>" & vbCrLf
      	     		
	End Function
				
	'================================================================================================='
	Public Function vbBroadcastSend(byref oReceiver, byval nPacketsToSend)
	Dim bRetval          : bRetval            = False
	Dim nPacketsResent   : nPacketsResent     = 0
	Dim nPacketsSent     : nPacketsSent       = 0
	Dim nPacketsReceived : nPacketsReceived   = 0 
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbBroadcastSend" & CWLAN_PRINT_END
	   oLog.Write "- PacketsToSend  = " & nPacketsToSend
	   
	   vbBroadcastSend = 0
	   
	   oReceiver.vbSetPacketFilter(BROADCAST)
	   
	   bRetval = oReceiver.vbStartReceive()
      If(bRetval = False) Then
         oLog.Write "vbBroadcastSend(): StartReceive() failed!"
         Exit Function
      End If
     
      Do
      
         nPacketsSent = m_oCLOpen.vbVerifiedSend(NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&), 250, nPacketsToSend, 0, Null)
         If(nPacketsSent < nPacketsToSend) Then
            oLog.Write "vbBroadcastSend(): VerifiedSend() failed!"
            Exit Do
         End If
         
      Loop While(False)
      
      bRetval = oReceiver.vbStopReceive()
      If(bRetval = False) Then
         oLog.Write "vbBroadcastSend(): StopReceive() failed!"
         Exit Function
      End If
      
      bRetval = oReceiver.vbGetReceiveResults(nPacketsReceived, nPacketsResent)
      If(bRetval = False) Then
         oLog.Write "vbBroadcastSend(): GetReceiveResults() failed!"
         Exit Function
      End If
      
      vbBroadcastSend = nPacketsReceived
	
	End Function
		
	'================================================================================================='
	Public Function vbBroadcastRecv(byref oSender, byval nPacketsToSend)
	Dim bRetval          : bRetval            = False
	Dim nPacketsResent   : nPacketsResent     = 0
	Dim nPacketsSent     : nPacketsSent       = 0
	Dim nPacketsReceived : nPacketsReceived   = 0 
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbBroadcastRecv" & CWLAN_PRINT_END
	   oLog.Write "- PacketsToSend  = " & nPacketsToSend
	   
	   vbBroadcastRecv = 0
	   
	   m_oCLOpen.vbSetPacketFilter(BROADCAST)
	   
	   bRetval = m_oCLOpen.vbStartReceive()
      If(bRetval = False) Then
         oLog.Write "vbBroadcastRecv(): StartReceive() failed!"
         Exit Function
      End If
     
      Do
      
         nPacketsSent = oSender.vbVerifiedSend(NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&), 250, nPacketsToSend, 0, Null)
         If(nPacketsSent < nPacketsToSend) Then
            oLog.Write "vbBroadcastRecv(): VerifiedSend() failed!"
            Exit Do
         End If
         
      Loop While(False)
      
      bRetval = m_oCLOpen.vbStopReceive()
      If(bRetval = False) Then
         oLog.Write "vbBroadcastRecv(): StopReceive() failed!"
         Exit Function
      End If
      
      bRetval = m_oCLOpen.vbGetReceiveResults(nPacketsReceived, nPacketsResent)
      If(bRetval = False) Then
         oLog.Write "vbBroadcastRecv(): GetReceiveResults() failed!"
         Exit Function
      End If
      
      vbBroadcastRecv = nPacketsReceived
	
	End Function
	   	
	'================================================================================================='
	Public Function vbDirectedSend(byref oReceiver, byval nPacketsToSend)
	Dim bRetval          : bRetval            = False
	Dim nPacketsReceived : nPacketsReceived   = 0
	Dim nPacketsResent   : nPacketsResent     = 0
	Dim nPacketsSent     : nPacketsSent       = 0
	
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbDirectedSend" & CWLAN_PRINT_END
	   oLog.Write "- PacketsToSend  = " & nPacketsToSend
	   
	   vbDirectedSend = 0
	   
	   oReceiver.vbSetPacketFilter(DIRECTED)
	   
	   bRetval = oReceiver.vbStartReceive()
      If(bRetval = False) Then
         oLog.Write "vbDirectedSend(): StartReceive() failed!"
         Exit Function
      End If
      
      Do
      
         nPacketsSent = m_oCLOpen.vbVerifiedSend(oReceiver.vbGetCardAddress(), 250, nPacketsToSend, 0, Null)
         If(nPacketsSent < nPacketsToSend) Then
            oLog.Write "vbDirectedSend(): VerifiedSend() failed!"
            Exit Do
         End If
      
      Loop While(False)
      
      bRetval = oReceiver.vbStopReceive()
      If(bRetval = False) Then
         oLog.Write "vbDirectedSend(): StopReceive() failed!"
         Exit Function
      End If
      
      bRetval = oReceiver.vbGetReceiveResults(nPacketsReceived, nPacketsResent)
      If(bRetval = False) Then
         oLog.Write "vbDirectedSend(): vbGetReceiveResults() failed!"
         Exit Function
      End If
      
      oLog.Write "PacketsReceived  = " & nPacketsReceived
      
      vbDirectedSend = nPacketsReceived
	
	End Function
	
	'================================================================================================='
   Public Function vbDirectedRecv(byref oSender, byval nPacketsToSend)
   Dim bRetval          : bRetval            = False
   Dim nPacketsReceived : nPacketsReceived   = 0
   Dim nPacketsResent   : nPacketsResent     = 0
   Dim nPacketsSent     : nPacketsSent       = 0
	
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbDirectedRecv" & CWLAN_PRINT_END
	   oLog.Write "- PacketsToSend  = " & nPacketsToSend
	   
	   vbDirectedRecv = 0
	   
	   m_oCLOpen.vbSetPacketFilter(DIRECTED)
	   
      If(m_oCLOpen.vbStartReceive() = False) Then
         oLog.Write "vbDirectedRecv(): StartReceive() failed!"
         Exit Function
      End If
      
      Do
      
         nPacketsSent = oSender.vbVerifiedSend(m_oCLOpen.vbGetCardAddress(), 250, nPacketsToSend, 0, Null)
         If(nPacketsSent < nPacketsToSend) Then
            oLog.Write "vbDirectedRecv() - VerifiedSend() failed!"
            Exit Do
         End If
         
      Loop While(False)
      
      If(m_oCLOpen.vbStopReceive() = False) Then
         oLog.Write "vbDirectedRecv(): StopReceive() failed!"
         Exit Function
      End If
      
      If(m_oCLOpen.vbGetReceiveResults(nPacketsReceived, nPacketsResent) = False) Then
         oLog.Write "vbDirectedRecv(): GetReceiveResults() failed!"
         Exit Function
      End If
      
      oLog.Write "PacketsReceived  = " & nPacketsReceived
      
      vbDirectedRecv = nPacketsReceived
	
	End Function
			   
   '================================================================================================='
   Public Function vbBssidListScanSE(byval bShowList)
      
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbBssidListScanSE" & CWLAN_PRINT_END & vbCrLf     
	   oLog.Write "- ShowList  = " & bShowList
	   
	   vbBssidListScanSE = vbBssidListScan(CWLAN_OID_SET, bShowList)
	                  
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbBssidListScanSE) & "</b>" & vbCrLf
      
   End Function
   
   '================================================================================================='
   Public Function vbBssidListScan(byval nType, byval bDisplayResults)
   Dim oNull         : Set oNull       = Nothing
   Dim oBssidList    : Set oBssidList  = Nothing
   Dim oBssid        : Set oBssid      = Nothing
   Dim bRetval       : bRetval         = False
	Dim nNdisStatus   : nNdisStatus     = GENERIC_FAILURE
   Dim nIndex        : nIndex          = 0
   Dim nCount        : nCount          = 0
   Dim nRate         : nRate           = 0
   Dim aSuppRates
   Dim aBssid
   
	   vbBssidListScan = nNdisStatus
	   
	   nNdisStatus = NdisRequestEx(nType, OID_802_11_BSSID_LIST_SCAN, oNull)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
      
      WScript.Sleep(WLAN_BSSID_LIST_SCAN_TIMEOUT)
      
      If(bDisplayResults = True) Then
         
         Set oBssidList = CreateObject("StructRep.SO_NDIS_802_11_BSSID_LIST_EX.1")
         If(oBssidList Is Nothing) Then
            oLog.Failed "Failed to create NDIS_802_11_BSSID_LIST_EX structure object", 88888
            Exit Function
         End If
              	 	   
         nNdisStatus = vbBssidList(CWLAN_OID_QUERY, oBssidList)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
            oLog.Write "vbBssidListScan(): Failed to query OID_802_11_BSSID_LIST"
            Exit Function
         End If
         
         vbPrintBssidList(oBssidList)
   
      End If
                                		
		vbBssidListScan = nNdisStatus
				
	End Function
	
	'================================================================================================='
   '/**
   '*/
   Public Function vbBssidListGE(byref oBssidList) 
	
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbBssidListGE" & CWLAN_PRINT_END & vbCrLf     
	   
	   vbBssidListGE = vbBssidList(CWLAN_OID_QUERY, oBssidList)
	                  
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbBssidListGE) & "</b>" & vbCrLf
					
	End Function
	
   '================================================================================================='
   '/**
   '*/
   Public Function vbBssidList(byval nType, byref oBssidList) 
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
	Dim nDriverType   : nDriverType  = 0
	
	   vbBssidList = nNdisStatus
      
      nNdisStatus = NdisRequestEx(nType, OID_802_11_BSSID_LIST, oBssidList)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
    	
      If(nType = CWLAN_OID_QUERY) Then
         oLog.Write "NumberOfItems = " & oBssidList.NumberOfItems
      End If 
                       		
		vbBssidList = nNdisStatus
				
	End Function
	      
   '================================================================================================='
   '/**
   '*/
   Public Function vbAddKeySE(byval nKeyIndex, byval sKeyMaterial, byval vMacAddr)
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAddKeySE" & CWLAN_PRINT_END   
      oLog.Write "- KeyIndex     = 0x" & Hex(nKeyIndex)
      oLog.Write "- KeyMaterial  = " & sKeyMaterial
      If(TypeName(vMacAddr) = "String") Then
 	      oLog.Write "- BSSID        = " & vMacAddr
 	   ElseIf(IsObject(vMacAddr) = True) Then
 	      oLog.Write "- BSSID        = " & vMacAddr.Bssid
 	   End If
 	   
      vbAddKeySE = vbAddKey(CWLAN_OID_SET, nKeyIndex, sKeyMaterial, vMacAddr)
	  
	   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbAddKeySE) & "</b>" & vbCrLf
	   				
	End Function
		
	'================================================================================================='
   '/**
   '*/
   Private Function vbAddKey(byval nType, byval nKeyIndex, byval sKeyMaterial, byval vMacAddr)
	Dim oAddKey       : Set oAddKey  = Nothing
	Dim oMacAddr      : Set oMacAddr = Nothing
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
		
	   vbAddKey = nNdisStatus
	   
	   Set oAddKey = CreateObject("StructRep.SO_NDIS_802_11_KEY.1")
      If(oAddKey Is Nothing) Then
         oLog.Failed "Failed to create NDIS_802_11_KEY structure object", 88888
         Exit Function
      End If
      
      Set oMacAddr = CreateObject("StructRep.SO_NDIS_802_11_MAC_ADDRESS.1")
      If(oMacAddr Is Nothing) Then
         oLog.Failed "Failed to create NDIS_802_11_MAC_ADDRESS structure object", 88888
         Exit Function
      End If
	
	   oAddKey.KeyIndex      = nKeyIndex
 	   oAddKey.KeyMaterial   = sKeyMaterial
 	   ' Not using this field yet, it will be set to null by the COM object
 	   'oAddKey.KeyRSC        = 
 	    
 	   If(TypeName(vMacAddr) = "String") Then
 	   
 	      If(vMacAddr = CWLAN_KEY_DEFAULT) Then
 	         oMacAddr.Byte1    = CByte(&HFF&)
 	         oMacAddr.Byte2    = CByte(&HFF&)
 	         oMacAddr.Byte3    = CByte(&HFF&)
 	         oMacAddr.Byte4    = CByte(&HFF&)
 	         oMacAddr.Byte5    = CByte(&HFF&)
 	         oMacAddr.Byte6    = CByte(&HFF&)
 	      End If
 	      
 	      oAddKey.Bssid = oMacAddr
 	
 	   ElseIf(IsObject(vMacAddr) = True) Then
 	      oAddKey.Bssid = vMacAddr
 	   Else
 	      msgbox "Invalid MacAddr type specified!"
 	      Exit Function
 	   End If
		
		nNdisStatus = NdisRequestEx(nType, OID_802_11_ADD_KEY, oAddKey)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
    		                            		
		vbAddKey = nNdisStatus
				
	End Function
			
	'================================================================================================='
   '/**
   '*/
   Public Function vbAssociationInformationSE(byref oInfo)	
			
		oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAssociationInformationSE" & CWLAN_PRINT_END   
            
    	vbAssociationInformationSE = vbAssociationInformation(CWLAN_OID_SET, oInfo)
				
		oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbAssociationInformationSE) & "</b>" & vbCrLf
		
	End Function
	
	'================================================================================================='
   '/**
   '*/
   Public Function vbAssociationInformationGE(byref oInfo)	
			
		oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAssociationInformationGE" & CWLAN_PRINT_END   
            		           	
    	vbAssociationInformationGE = vbAssociationInformation(CWLAN_OID_QUERY, oInfo)
				
		oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbAssociationInformationGE) & "</b>" & vbCrLf
		
	End Function
	
	'================================================================================================='
   '/**
   '*/
   Public Function vbAssociationInformation(byval nType, byref oInfo)	
	Dim bRetval     : bRetval       = False
	Dim nNdisStatus : nNdisStatus   = GENERIC_FAILURE
		      
		vbAssociationInformation = nNdisStatus
		
		nNdisStatus = NdisRequestEx(nType, OID_802_11_ASSOCIATION_INFORMATION, oInfo)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
		   	   		                             		
		vbAssociationInformation = nNdisStatus
		
	End Function
	
	'================================================================================================='
   '/**
   '*/
   Public Function vbReloadDefaultsSE(byval nDefaults)	
      
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbReloadDefaultsSE" & CWLAN_PRINT_END  
      oLog.Write "- Reload Defaults = " & g_aReloadDefaults(nDefaults) & "(" & nDefaults & ")"
            	              	
    	vbReloadDefaultsSE = vbReloadDefaults(CWLAN_OID_SET, nDefaults)              		
		
		oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbReloadDefaultsSE) & "</b>" & vbCrLf
		
	End Function
		
	'================================================================================================='
   '/**
   '*/
   Private Function vbReloadDefaults(byval nType, byref nDefaults)	
   Dim oUlong        : Set oUlong   = Nothing
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
		
		vbReloadDefaults = nNdisStatus
		
		Set oUlong = CreateObject("StructRep.SO_ULONG.1")
      If(oUlong Is Nothing) Then
         oLog.Failed "vbReloadDefaults(): Failed to create ULONG structure object", 88888
         Exit Function
      End If
      
		oUlong.Ulong = nDefaults
		
		nNdisStatus = NdisRequestEx(nType, OID_802_11_RELOAD_DEFAULTS, oUlong)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If

		vbReloadDefaults = nNdisStatus
		
	End Function
	
	'================================================================================================='
   '/**
   '*/
   Public Function vbTestSE(byref oTest)
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbTestSE" & CWLAN_PRINT_END   
                      
      vbTestSE = vbTest(CWLAN_OID_SET, oTest)
	   
	   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbTestSE) & "</b>" & vbCrLf
	   			
	End Function
	
	'================================================================================================='
   Private Function vbTest(byref nType, byval oTest)
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
			
		If(nType = CWLAN_OID_SET) Then
		   oLog.Write "Type = " & oTest.Type
		End If
	
	   nNdisStatus = NdisRequestEx(nType, OID_802_11_TEST, oTest)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
					                      		
		vbTest = nNdisStatus
				
	End Function
	
	'================================================================================================='
   '/**
   '*/
   Public Function vbConfigurationGE(byref oConfig) 
	
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbConfigurationGE" & CWLAN_PRINT_END & vbCrLf     
	   
	   vbConfigurationGE = vbConfiguration(CWLAN_OID_QUERY, oConfig)
	                  
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbConfigurationGE) & "</b>" & vbCrLf
					
	End Function
	
	'================================================================================================='
   '/**
   '*/
	Public Function vbConfigurationSE(byref oConfig)
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbConfigurationSE" & CWLAN_PRINT_END   
                      
      vbConfigurationSE = vbConfiguration(CWLAN_OID_SET, oConfig)
	   
	   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbConfigurationSE) & "</b>" & vbCrLf
	   			
	End Function
	
   '================================================================================================='
   '/**
   '*/
   Public Function vbConfiguration(byval nType, byref oConfig) 
	Dim bRetval     : bRetval        = False
	Dim nNdisStatus : nNdisStatus    = GENERIC_FAILURE
	    
	   vbConfiguration = nNdisStatus
	   
	   nNdisStatus = NdisRequestEx(nType, OID_802_11_CONFIGURATION, oConfig)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
    	                       		
		vbConfiguration = nNdisStatus
						
	End Function
	
	'================================================================================================='
	Public Function vbResetDevice()
	Dim nOrgTimeout   : nOrgTimeout  = WLAN_SSID_TIMEOUT
	
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbResetDevice" & CWLAN_PRINT_END   
      
      ' Reset the SSID timeout because we know this is not going to connect
      WLAN_SSID_TIMEOUT = 0
      
      Do
         vbResetDevice = vbInfrastructure(CWLAN_OID_SET, Ndis802_11Infrastructure)
         If(vbResetDevice <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If
         
         ' This call will ensure the radio is turned on and the device is not associated
         vbResetDevice = vbSsid(CWLAN_OID_SET, "RADIO_ON")
         If(vbResetDevice <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If
         
         ' If(m_nSecurityType And WLAN_SECURITY_TYPE_WPA) Then
'             ' This call will ensure the radio is turned on and the device is not associated
'             vbResetDevice = vbEncryption(CWLAN_OID_SET, Ndis802_11EncryptionDisabled)
'             If(vbResetDevice <> NDIS_STATUS_SUCCESS) Then
'                Exit Do
'             End If
'          Else
'             vbResetDevice = vbWepStatus(CWLAN_OID_SET, Ndis802_11WEPDisabled)
'             If(vbResetDevice <> NDIS_STATUS_SUCCESS) Then
'                Exit Do
'             End If
'          End If
                  
         vbResetDevice = vbRemoveAllKeys()
         If(vbResetDevice <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If
         
         vbClearEvents()
                               
      Loop While(False)
		
		WLAN_SSID_TIMEOUT = nOrgTimeout
				    	
	   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbResetDevice) & "</b>" & vbCrLf
	  	     		
   End Function
   
   '================================================================================================='
   '/**
   '*/
	Public Function vbRssiGE(byref nRssi)
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbRssiGE" & CWLAN_PRINT_END   
                      
      vbRssiGE = vbRssi(CWLAN_OID_QUERY, nRssi)
	   
	   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbRssiGE) & "</b>" & vbCrLf
	   			
	End Function
	
   '================================================================================================='
   '/**
   '*/
   Public Function vbRssi(byval nType, byref nRssi) 
   Dim oRssi         : Set oRssi    = Nothing
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
	    
	   vbRssi = nNdisStatus
	   
	   Set oRssi = CreateObject("StructRep.SO_NDIS_802_11_RSSI.1")
      If(oRssi Is Nothing) Then
         oLog.Failed "Failed to create NDIS_802_11_RSSI structure object", 88888
         Exit Function
      End If
		
		nNdisStatus = NdisRequestEx(nType, OID_802_11_RSSI, oRssi)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
		
		nRssi = oRssi.Rssi
      
      If(nType = CWLAN_OID_QUERY) Then
		   oLog.Write "RSSI = " & nRssi
		End If
    	                       		
		vbRssi = nNdisStatus
				
	End Function
	   
   '================================================================================================='
   '/**
   '*/
   Function vbBssidFromMacAddr(byref oBssid)
   Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
   Dim aMacAddr   
      
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbBssidFromMacAddr" & CWLAN_PRINT_END
      
      vbBssidFromMacAddr = nNdisStatus
      
      Set oBssid = CreateObject("StructRep.SO_NDIS_802_11_MAC_ADDRESS.1")
      If(oBssid Is Nothing) Then
         oLog.Failed "vbMacAddrToBssid(): Failed to create NDIS_802_11_MAC_ADDRESS structure object", 88888
         Set oBssid = Nothing
         Exit Function
      End If
               
      aMacAddr = vbGetCardAddress()
   
      oBssid.Byte1 = CByte(aMacAddr(0))
      oBssid.Byte2 = CByte(aMacAddr(1))
      oBssid.Byte3 = CByte(aMacAddr(2))
      oBssid.Byte4 = CByte(aMacAddr(3))
      oBssid.Byte5 = CByte(aMacAddr(4))
      oBssid.Byte6 = CByte(aMacAddr(5))
      
      vbBssidFromMacAddr = NDIS_STATUS_SUCCESS
      
   End Function
   
   '================================================================================================='
   Public Function vbWepStatusSE(byref nWepStatus)
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbWepStatusSE" & CWLAN_PRINT_END   
                      
      vbWepStatusSE = vbWepStatus(CWLAN_OID_SET, nWepStatus)
	   
	   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbWepStatusSE) & "</b>" & vbCrLf
	   			
	End Function
	
	'================================================================================================='
   Public Function vbWepStatusGE(byref nWepStatus)
	
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbWepStatusGE" & CWLAN_PRINT_END & vbCrLf     
	   
	   vbWepStatusGE = vbWepStatus(CWLAN_OID_QUERY, nWepStatus)
	          	
    	oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbWepStatusGE) & "</b>" & vbCrLf
				
	End Function
				
	'================================================================================================='
   Private Function vbWepStatus(byval nType, Byref nWepStatus)
	Dim oUlong        : Set oUlong   = Nothing
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
  
		vbWepStatus = nNdisStatus
		
		Set oUlong = CreateObject("StructRep.SO_ULONG.1")
      If(oUlong Is Nothing) Then
         oLog.Failed "vbWepStatus(): Failed to create ULONG structure object", 88888
         Exit Function
      End If
   	
		If(nType = CWLAN_OID_SET) Then
		   If(nWepStatus > UBound(g_aEncryptionStatus)) Then
            oLog.Write "WepStatus = Invalid"
         Else  
            oLog.Write "WepStatus = " & g_aEncryptionStatus(nWepStatus) & "(" & nWepStatus & ")"
         End If
		End If
		
		oUlong.Ulong = nWepStatus
		
		nNdisStatus = NdisRequestEx(nType, OID_802_11_WEP_STATUS, oUlong)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
					
		nWepStatus = oUlong.Ulong
		
		If(nType = CWLAN_OID_QUERY AND nNdisStatus = NDIS_STATUS_SUCCESS) Then
		   If(nWepStatus > UBound(g_aEncryptionStatus)) Then
            oLog.Write "WepStatus = Invalid"
         Else  
            oLog.Write "WepStatus = " & g_aEncryptionStatus(nWepStatus) & "(" & nWepStatus & ")"
         End If
		End If
                      		
		vbWepStatus = nNdisStatus
				
	End Function
	
	'================================================================================================='
   '/**
   '*/
   Public Function vbAddWepSE(byval nKeyIndex, byval sKeyMaterial)
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAddWepSE" & CWLAN_PRINT_END   
      		
      vbAddWepSE = vbAddWep(CWLAN_OID_SET, nKeyIndex, sKeyMaterial)
	  
	   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbAddWepSE) & "</b>" & vbCrLf
	   				
	End Function
		
	'================================================================================================='
   '/**
   '*/
   Private Function vbAddWep(byval nType, byval nKeyIndex, byval sKeyMaterial)
	Dim oWepKey       : Set oWepKey  = Nothing
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
		
		oLog.Write "- KeyIndex     = 0x" & Hex(nKeyIndex)
      oLog.Write "- KeyMaterial  = " & sKeyMaterial
      
	   vbAddWep = nNdisStatus
	   
	   Set oWepKey = CreateObject("StructRep.SO_NDIS_802_11_WEP.1")
      If(oWepKey Is Nothing) Then
         oLog.Failed "vbAddWep(): Failed to create NDIS_802_11_WEP structure object", 88888
         Exit Function
      End If

	   oWepKey.KeyIndex      = nKeyIndex
 	   oWepKey.KeyMaterial   = sKeyMaterial
 	   
 	   nNdisStatus = NdisRequestEx(nType, OID_802_11_ADD_WEP, oWepKey)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
				    		                            		
		vbAddWep = nNdisStatus
				
	End Function
	
	'================================================================================================='
	Public Function vbRemoveWepSE(byval nKeyIndex)
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbRemoveWepSE" & CWLAN_PRINT_END
	   oLog.Write "KeyIndex = " & nKeyIndex
	   
	   vbRemoveWepSE = vbRemoveWep(CWLAN_OID_SET, nKeyIndex)
	   
	   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbRemoveWepSE) & "</b>" & vbCrLf
	   
	End Function
	
	'================================================================================================='
	Public Function vbRemoveWep(byval nType, byval nKeyIndex)
	Dim oUlong        : Set oUlong   = Nothing
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
				
		vbRemoveWep = nNdisStatus	
			
      Set oUlong = CreateObject("StructRep.SO_ULONG.1")
      If(oUlong Is Nothing) Then
         oLog.Failed "vbRemoveWep(): Failed to create ULONG structure object", 88888
         Exit Function
      End If
         
      oUlong.Value = nKeyIndex
    			
    	nNdisStatus = NdisRequestEx(nType, OID_802_11_REMOVE_WEP, oUlong)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
		     				
		vbRemoveWep = nNdisStatus
		
	End Function
         
   '================================================================================================='
   Public Function vbCreateIBSS(byval nInfraMode, byval nAuthMode, byval nEncryption,  byval sSsid)
   Dim bRetval          : bRetval         = False
   Dim nNdisStatus      : nNdisStatus     = GENERIC_FAILURE
      
      vbCreateIBSS = nNdisStatus
      	   
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbCreateIBSS" & CWLAN_PRINT_END

      oLog.Write "- InfrastructureMode = "   & g_aInfrastructureMode(nInfraMode)
      oLog.Write "- Authentication     = "   & g_aAuthenticationMode(nAuthMode)
      oLog.Write "- Encryption         = "   & g_aEncryptionStatus(nEncryption)
      oLog.Write "- SSID               = "   & sSsid

      Do

         nNdisStatus = vbInfrastructure(CWLAN_OID_SET, nInfraMode)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
       
         nNdisStatus = vbAuthentication(CWLAN_OID_SET, nAuthMode)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
         
         nNdisStatus = vbEncryption(CWLAN_OID_SET, nEncryption)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
                               
         nNdisStatus = vbSsid(CWLAN_OID_SET, sSsid)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
             
      Loop While(False)
        			                  			      	    
      vbCreateIBSS = nNdisStatus

      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbCreateIBSS) & "</b>" & vbCrLf
     
   End Function
   
   '================================================================================================='
   Public Function vbJoinIBSS(byval nInfraMode, byval nAuthMode, byval nEncryption, byval sSsid)
   Dim bRetval          : bRetval         = False
   Dim nNdisStatus      : nNdisStatus     = GENERIC_FAILURE
   Dim nConnectStatus   : nConnectStatus  = 0
   Dim sCurrentSsid     : sCurrentSsid    = ""

      vbJoinIBSS = nNdisStatus
         
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbJoinIBSS" & CWLAN_PRINT_END

      oLog.Write "- InfrastructureMode = "   & g_aInfrastructureMode(nInfraMode)
      oLog.Write "- Authentication     = "   & g_aAuthenticationMode(nAuthMode)
      oLog.Write "- Encryption         = "   & g_aEncryptionStatus(nEncryption)
      oLog.Write "- SSID               = "   & sSsid

      Do

      nNdisStatus = vbInfrastructure(CWLAN_OID_SET, nInfraMode)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
          Exit Do
      End If

      nNdisStatus = vbAuthentication(CWLAN_OID_SET, nAuthMode)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) then
          Exit Do
      End If

      nNdisStatus = vbEncryption(CWLAN_OID_SET, nEncryption)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
          Exit Do
      End If
                            
      nNdisStatus = vbSsid(CWLAN_OID_SET, sSsid)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) then
          Exit Do
      End If
                        
      nNdisStatus = vbSsid(CWLAN_OID_QUERY, sCurrentSsid)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Do
      End If

      If(vbMediaConnectStatus(nConnectStatus) = False) Then
         oLog.Write "vbJoinIBSS(): vbMediaConnectStatus() failed!"
         nNdisStatus = GENERIC_FAILURE
         Exit Do
      End If
                  
      nNdisStatus = vbSsidGe(sCurrentSsid)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
          Exit Do
      End If
          
      If((nConnectStatus = CWLAN_MEDIA_DISCONNECTED) Or (Not sCurrentSsid = sSsid)) then
          oLog.Write "vbJoinIBSS(): Failed to associate with " & sSsid & "!"
          nNdisStatus = GENERIC_FAILURE
          Exit Do
      End If
             			      	    
      Loop While(False)

      vbJoinIBSS = nNdisStatus
       
   End Function

   '================================================================================================='
   Public Function vbCreateIBSSEx(byval nInfraMode, byval nAuthMode, byval nEncryption,  byval nKeyIndex, byval sKeyMaterial, byval sSsid)
   Dim bRetval          : bRetval         = False
   Dim nNdisStatus      : nNdisStatus     = GENERIC_FAILURE
      
      vbCreateIBSSEx = nNdisStatus
      	   
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbCreateIBSSEx" & CWLAN_PRINT_END

      oLog.Write "- InfrastructureMode = "   & g_aInfrastructureMode(nInfraMode)
      oLog.Write "- Authentication     = "   & g_aAuthenticationMode(nAuthMode)
      oLog.Write "- Encryption         = "   & g_aEncryptionStatus(nEncryption)
      oLog.Write "- KeyIndex           = 0x" & Hex(nKeyIndex)
      oLog.Write "- KeyMaterial        = "   & sKeyMaterial
      oLog.Write "- SSID               = "   & sSsid

      Do

         nNdisStatus = vbInfrastructure(CWLAN_OID_SET, nInfraMode)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
       
         nNdisStatus = vbAuthentication(CWLAN_OID_SET, nAuthMode)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If

         nNdisStatus = vbAddWep(CWLAN_OID_SET, nKeyIndex, sKeyMaterial)
   	   If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
   	      Exit Do
   	   End If
   	         
         nNdisStatus = vbEncryption(CWLAN_OID_SET, nEncryption)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
                               
         nNdisStatus = vbSsid(CWLAN_OID_SET, sSsid)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
             
      Loop While(False)
        			                  			      	    
      vbCreateIBSSEx = nNdisStatus

      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbCreateIBSSEx) & "</b>" & vbCrLf
     
   End Function

   '================================================================================================='
   Public Function vbJoinIBSSEx(byval nInfraMode, byval nAuthMode, byval nEncryption, byval nKeyIndex, byval sKeyMaterial, byval sSsid)
   Dim bRetval          : bRetval         = False
   Dim nNdisStatus      : nNdisStatus     = GENERIC_FAILURE
   Dim nConnectStatus   : nConnectStatus  = 0
   Dim sCurrentSsid     : sCurrentSsid    = ""

      vbJoinIBSSEx = nNdisStatus
         
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbJoinIBSSEx" & CWLAN_PRINT_END

      oLog.Write "- InfrastructureMode = "   & g_aInfrastructureMode(nInfraMode)
      oLog.Write "- Authentication     = "   & g_aAuthenticationMode(nAuthMode)
      oLog.Write "- Encryption         = "   & g_aEncryptionStatus(nEncryption)
      oLog.Write "- KeyIndex           = 0x" & Hex(nKeyIndex)
      oLog.Write "- KeyMaterial        = "   & sKeyMaterial
      oLog.Write "- SSID               = "   & sSsid

      Do

      nNdisStatus = vbInfrastructure(CWLAN_OID_SET, nInfraMode)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
          Exit Do
      End If

      nNdisStatus = vbAuthentication(CWLAN_OID_SET, nAuthMode)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) then
          Exit Do
      End If

      nNdisStatus = vbAddWep(CWLAN_OID_SET, nKeyIndex, sKeyMaterial)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Do
      End If

      nNdisStatus = vbEncryption(CWLAN_OID_SET, nEncryption)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
          Exit Do
      End If
                            
      nNdisStatus = vbSsid(CWLAN_OID_SET, sSsid)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) then
          Exit Do
      End If
                        
      nNdisStatus = vbSsid(CWLAN_OID_QUERY, sCurrentSsid)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Do
      End If
      
      If(vbMediaConnectStatus(nConnectStatus) = False) Then
         oLog.Write "vbJoinIBSSEx(): vbMediaConnectStatus() failed!"
         nNdisStatus = GENERIC_FAILURE
         Exit Do
      End If
                  
      nNdisStatus = vbSsidGe(sCurrentSsid)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
          Exit Do
      End If
          
      If((nConnectStatus = CWLAN_MEDIA_DISCONNECTED) Or (Not sCurrentSsid = sSsid)) then
          oLog.Write "vbJoinIBSSEx(): Failed to associate with " & sSsid & "!"
          nNdisStatus = GENERIC_FAILURE
          Exit Do
      End If
             			      	    
      Loop While(False)

      vbJoinIBSSEx = nNdisStatus

      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbJoinIBSSEx) & "</b>" & vbCrLf
       
   End Function
   
   '================================================================================================='
   Function vbWaitForSSID(byval sSsid, byval nScanCount)
   Dim oBssidList    : Set oBssidList  = Nothing
   Dim oBssid        : Set oBssid      = Nothing
   Dim bRetval       : bRetval         = False
	Dim nNdisStatus   : nNdisStatus     = GENERIC_FAILURE
   Dim nNumScans     : nNumScans       = 0
   Dim nIndex        : nIndex          = 0
   
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbWaitForSSID" & CWLAN_PRINT_END
      oLog.Write "SSID      = " & sSsid
      oLog.Write "ScanCount = " & nScanCount
      
	   vbWaitForSSID = nNdisStatus
	   
      Set oBssidList = CreateObject("StructRep.SO_NDIS_802_11_BSSID_LIST_EX.1")
      If(oBssidList Is Nothing) Then
         oLog.Failed "Failed to create NDIS_802_11_BSSID_LIST_EX structure object", 88888
         Exit Function
      End If
   	
   	nNdisStatus = vbBssidListScan(CWLAN_OID_SET, False)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
         
   	Do
   	   
   	   If(nNumScans = nScanCount) Then
	         oLog.Write("vbWaitForSSID(): Unable to find " & sSsid & " in " &  nNumScans & " scans")
	         nNdisStatus = GENERIC_FAILURE
	         Exit Do
	      End If  	   
         
         nNdisStatus = vbBssidList(CWLAN_OID_QUERY, oBssidList)
         If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
            Exit Do
         End If
         
         vbPrintBssidList(oBssidList)
               	       	        					
   	   For nIndex = 0 To oBssidList.NumberOfItems - 1
   	      
   	      Set oBssid = oBssidList.Bssid(nIndex)
   	      If(oBssid Is Nothing) Then
   	         oLog.Write "vbWaitForSSID(): Failed to get BSSID list item " & nIndex
   	      End If
   	      
   	      ' If we found the SSID in the list then bail out
   	      If(sSsid = oBssid.Ssid) Then
   	         Exit Do
   	      End If
   	        	        								
   	   Next 
   	   
   	   nNumScans = nNumScans + 1
   	   
   	   WScript.Sleep(2000)
   	   	  
   	Loop While(True)      
                                		
		vbWaitForSSID = nNdisStatus
		
		oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbWaitForSSID) & "</b>" & vbCrLf
		
   End Function

   '================================================================================================='
   Public Function vbPowerModeSE(byval nPowerMode)	
      
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbPowerModeSE" & CWLAN_PRINT_END  
            	              	
    	vbPowerModeSE = vbPowerMode(CWLAN_OID_SET, nPowerMode)              		
		
		oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbPowerModeSE) & "</b>" & vbCrLf
		
	End Function
	
	'================================================================================================='
   Public Function vbPowerModeGE(byref nPowerMode)	
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbPowerModeGE" & CWLAN_PRINT_END & vbCrLf 
	   
	   vbPowerModeGE = vbPowerMode(CWLAN_OID_QUERY, nPowerMode)
	         
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbPowerModeGE) & "</b>" & vbCrLf
       		
	End Function
	
	'================================================================================================='
   Private Function vbPowerMode(byval nType, byref nPowerMode)	
   Dim oUlong        : Set oUlong   = Nothing
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
		
		vbPowerMode = nNdisStatus
		
		Set oUlong = CreateObject("StructRep.SO_ULONG.1")
      If(oUlong Is Nothing) Then
         oLog.Failed "vbPowerMode(): Failed to create ULONG structure object", 88888
         Exit Function
      End If
   	
		If(nType = CWLAN_OID_SET) Then
		   If(nPowerMode > UBound(g_aPowerModes)) Then
            oLog.Write "Power Mode = Invalid" & " (" & nPowerMode & ")"
         Else  
            oLog.Write "Power Mode = " & g_aPowerModes(nPowerMode) & " (" & nPowerMode & ")"
         End If
		End If
		
		oUlong.Ulong = nPowerMode
		
		nNdisStatus = NdisRequestEx(nType, OID_802_11_POWER_MODE, oUlong)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If

    	nPowerMode = oUlong.Ulong
    	
    	If(nType = CWLAN_OID_QUERY AND nNdisStatus = NDIS_STATUS_SUCCESS) Then
		   If(nPowerMode > UBound(g_aPowerModes)) Then
            oLog.Write "Power Mode = Invalid" & " (" & nPowerMode & ")"
         Else  
            oLog.Write "Power Mode = " & g_aPowerModes(nPowerMode) & " (" & nPowerMode & ")"
         End If
		End If
    	
		vbPowerMode = nNdisStatus
		
	End Function
	
	'================================================================================================='
   Public Function vbStatisticsGE()	
	   
	   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbStatisticsGE" & CWLAN_PRINT_END & vbCrLf 
	   
	   vbStatisticsGE = vbStatistics(CWLAN_OID_QUERY)
	         
      oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(vbStatisticsGE) & "</b>" & vbCrLf
       		
	End Function
	
	'================================================================================================='
   Private Function vbStatistics(byval nType)	
   Dim oStats        : Set oStats   = Nothing
	Dim bRetval       : bRetval      = False
	Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
		
		vbStatistics = nNdisStatus
		
		Set oStats = CreateObject("StructRep.SO_NDIS_802_11_STATISTICS.1")
      If(oStats Is Nothing) Then
         oLog.Failed "vbStatistics(): Failed to create NDIS_802_11_STATISTICS structure object", 88888
         Exit Function
      End If
      
   	nNdisStatus = NdisRequestEx(nType, OID_802_11_STATISTICS, oStats)
		If(nNdisStatus = GENERIC_FAILURE) Then
		   Exit Function
		End If
		
    	' bRetval = m_oCLOpen.NdisRequest2(OID_802_11_STATISTICS, oStats, nType, nNdisStatus)
    	If(nType = CWLAN_OID_QUERY AND nNdisStatus = NDIS_STATUS_SUCCESS) Then
		   oStats.Print()
		End If
    	
		vbStatistics = nNdisStatus
		
	End Function

   '================================================================================================='
   Public Function vbIsWPASupported()
   Dim nAuthenticationMode : nAuthenticationMode   = 0
   Dim bRetval             : bRetval               = False
   Dim nNdisStatus         : nNdisStatus           = GENERIC_FAILURE
      
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbIsWPASupported" & CWLAN_PRINT_END 
      
      vbIsWPASupported = False
             
    	nNdisStatus = Me.vbAuthenticationSE(Ndis802_11AuthModeWPA)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
   
      nNdisStatus = Me.vbAuthenticationGE(nAuthenticationMode)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
   
      If(nAuthenticationMode <> Ndis802_11AuthModeWPA) Then
         Exit Function
      End If
      
      vbIsWPASupported = True
   		
   End Function
   
   '================================================================================================='
   Public Function vbIsAESSupported()
   Dim nEncryption   : nEncryption  = -1
   Dim bRetval       : bRetval      = False
   Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
   
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbIsAESSupported" & CWLAN_PRINT_END 
      
      vbIsAESSupported = False
      
    	nNdisStatus = Me.vbInfrastructureSE(Ndis802_11Infrastructure)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
      
      nNdisStatus = Me.vbAuthenticationSE(Ndis802_11AuthModeWPA)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
      
      nNdisStatus = Me.vbEncryptionSE(Ndis802_11Encryption3Enabled)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
           
      nNdisStatus = Me.vbEncryptionGE(nEncryption)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
      
      If((nEncryption <> Ndis802_11Encryption3Enabled) And (nEncryption <> Ndis802_11Encryption3KeyAbsent)) Then
         Exit Function
      End If
     
      vbIsAESSupported = True
   		
   End Function
   
   '================================================================================================='
   Public Function vbIsTKIPSupported()
   Dim nEncryption   : nEncryption  = -1
   Dim bRetval       : bRetval      = False
   Dim nNdisStatus   : nNdisStatus  = GENERIC_FAILURE
   
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbIsTKIPSupported" & CWLAN_PRINT_END 
      
      vbIsTKIPSupported = False
      
    	nNdisStatus = Me.vbInfrastructureSE(Ndis802_11Infrastructure)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
      
      nNdisStatus = Me.vbAuthenticationSE(Ndis802_11AuthModeWPA)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
      
      nNdisStatus = Me.vbEncryptionSE(Ndis802_11Encryption2Enabled)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
           
      nNdisStatus = Me.vbEncryptionGE(nEncryption)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
      
      If((nEncryption <> Ndis802_11Encryption2Enabled) And (nEncryption <> Ndis802_11Encryption2KeyAbsent)) Then
         Exit Function
      End If
     
      vbIsTKIPSupported = True
   		
   End Function
   
   '================================================================================================='
   Public Function vbIsWPAAdhocSupported()
   Dim nNdisStatus   : nNdisStatus  = NDIS_STATUS_FAILURE
   Dim nAuthMode     : nAuthMode    = -1
      
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbIsWPAAdhocSupported" & CWLAN_PRINT_END
      
      vbIsWPAAdhocSupported = False
               
      nNdisStatus = Me.vbAuthenticationSE(Ndis802_11AuthModeWPANone)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If 
      
      nNdisStatus = Me.vbAuthenticationGE(nAuthMode)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If 
      
      If(nAuthMode <> Ndis802_11AuthModeWPANone) Then
         Exit Function
      End If
               
      vbIsWPAAdhocSupported = True
      
   End Function
   
   '##################################################################################################################################
    
   '================================================================================================='
   '/**
   'This function returns the MAC address being currently used by the device. It is only
   'valid for Lan media. It will query the appropriate CURRENT_ADDRESS oid to obtain
   'this address.
   '@return    The mac address currently in use by the media (Null Address on error)
   '@code
   '  DestAddr = oSuppOpen.vbGetCardAddress
   '@endcode
   '*/
   Public Function vbGetCardAddress
      Dim CardAddr
      Dim AddrOid
      
      Select Case Me.NdisMedium
         Case NDISMEDIUM802_3
            AddrOid = OID_802_3_CURRENT_ADDRESS
         Case NDISMEDIUM802_5
            AddrOid = OID_802_5_CURRENT_ADDRESS
         Case NDISMEDIUMFDDI
            AddrOid = OID_FDDI_LONG_CURRENT_ADDR
         Case Else
            AddrOid = 0
            Call oLog.SafeFailed ("GetCardAddress: Unknown media" , 88888)
      End Select
      
      CardAddr = NullAddr()
      
      If (AddrOid <> 0) Then
         Dim bResult
         Dim BytesWritten, BytesNeeded
         Dim NdisStatus
         
         bResult = Me.vbNdisRequest( _
               AddrOid, _
               CardAddr, _
               6, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         
         If (Not bResult) Then
            call oLog.SafeFailed ("Could not obtain address of " & m_oCLOpen.AdapterType, 88888)
         End If
         
         If (NdisStatus <> 0) Then
            call oLog.SafeFailed ("Could not obtain address of " & m_oCLOpen.AdapterType , 88888)
         End If
      End If
      
      vbGetCardAddress = CardAddr
   End Function
   
   '================================================================================================='
   '/**
   '@sa   CCLOpen::vbGetMaxPacketSize
   '*/
   Public Function vbGetMaxPacketSize
      vbGetMaxPacketSize = m_oCLOpen.vbGetMaxPacketSize
   End Function

   '================================================================================================='
   '/**
   '@sa CCLOpen::vbGetReceiveDelay
   '*/
   Public Function vbGetReceiveDelay
      vbGetReceiveDelay = m_oCLOpen.vbGetReceiveDelay
   End Function
   
   
   '================================================================================================='
   '/**
   'This function sets the packet filter. It also prints the filter it is trying to set.
   'Internally it makes a ndisrequest with oid OID_GEN_CURRENT_PACKET_FILTER.
   '@params
   ' ! number The filter we are trying to set
   '@return    True or false depending on whether the oid set was successful or not
   '@code
   '  If (Not oTestOpen.vbSetPacketFilter(DIRECTED)) Then
   '     Exit Function
   '  End If
   '@endcode
   '@sa CLanOpen::vbGetFilters
   '*/
   Public Function vbSetPacketFilter (ByVal NewFilter)
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim strFilters, bResult
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      strFilters = "SetPacketFilter is setting the packet filter to "
      
      if (NewFilter = 0)Then
         strFilters = strFilters & "NOTHING "
      End if
      
      if (NewFilter AND DIRECTED)Then
         strFilters = strFilters & "DIRECTED "
      End If
      
      if (NewFilter AND BROADCAST)Then
         strFilters = strFilters & "BROADCAST "
      End If
      
      if (NewFilter AND PROMISCUOUS)Then
         strFilters = strFilters & "PROMISCUOUS "
      End If
      
      if (NewFilter AND MULTICAST)Then
         strFilters = strFilters & "MULTICAST "
      End If
      
      if (NewFilter AND ALL_MULTICAST)Then
         strFilters = strFilters & "ALL_MULTICAST "
      End If
      
      if (NewFilter AND FUNCTIONAL)Then
         strFilters = strFilters & "FUNCTIONAL "
      End If

      if (NewFilter AND ALL_FUNCTIONAL)Then
         strFilters = strFilters & "ALL_FUNCTIONAL "
      End If
      
      if (NewFilter AND GROUP_PKT)Then
         strFilters = strFilters & "GROUP "
      End If
      
      if (NewFilter AND MAC_FRAME)Then
         strFilters = strFilters & "MAC_FRAME "
      End If
      
      if (NewFilter AND SOURCE_ROUTING)Then
         strFilters = strFilters & "SOURCE_ROUTING "
      End If
      
      if (NewFilter AND ALL_LOCAL)Then
         strFilters = strFilters & "ALL_LOCAL "
      End If
      
      strFilters = strFilters & vblf
      
      oLog.Write(strFilters)
      
      bResult = m_oCLOpen.vbNdisRequest(OID_GEN_CURRENT_PACKET_FILTER, _
            NewFilter, 4, REQUEST_SET_INFO, BytesWritten, BytesNeeded, NdisStatus, FALSE)
      
      If (Not bResult Or NdisStatus <> 0) then
         call oLog.SafeFailed ("Unable to set packet filter for " & m_oCLOpen.AdapterType & " to " & Hex(NewFilter), 22852)
         vbSetPacketFilter = FALSE
      Else
         vbSetPacketFilter = TRUE
      End if
   End Function   
   
   '================================================================================================='
   '/**
   '@exclude
   'This function sets the packet filter. It only prints messages from core, and none on its own.
   'Internally it makes a ndisrequest with oid OID_GEN_CURRENT_PACKET_FILTER. This is a private function
   'for internal use only
   '@params
   ' ! number The filter we are trying to set
   '@return    True or False depending on whether the oid set was successful
   '@code
   '  If (Not oTestOpen.vbSilentSetPacketFilter(DIRECTED)) Then
   '     Exit Function
   '  End If
   '@endcode
   '@sa  CLanOpen::vbSetPacketFilter
   '*/
   Private Function vbSilentSetPacketFilter(ParamFilterType)
      Dim BytesWritten, BytesNeeded
      Dim NdisStatus
      Dim FilterType
      FilterType = ParamFilterType ' Do this because NdisRequest can change it
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      vbSilentSetPacketFilter = Me.vbNdisRequest( _
            OID_GEN_CURRENT_PACKET_FILTER, _
            FilterType, _
            4, _
            REQUEST_SET_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            FALSE)
      
      If (vbSilentSetPacketFilter AND NdisStatus <> 0) Then
         vbSilentSetPacketFilter = FALSE
      End If
      
   End Function
   
   
   '==========================================================================
   '/**
   'Gets all the filters supported by the card. The only way to obtain this
   'list is to try setting a filter, and if it suceeds, the filter is assumed
   'to be supported, else not. Because of some internal dependancies, it is
   'necessary that a Card::vbGetPhysicalMedium call must be made before 
   'vbGetFilters is invoked
   '@return    Returns a bitmask of the set of filter currently supported
   '@code
   '  AvailFilters = oTestOpen.vbGetFilters()
   '@endcode
   '@sa CLanOpen::vbSetPacketFilter
   '*/  
   Public Function vbGetFilters()
      Dim bResult
      Dim l_nFilters
      Dim Media
      Dim OldFilter, FilterSize
      
      Media = m_oCLOpen.NdisMedium

      ' obtain the current filter, so that we can restore it at the end of this function
      OldFilter = CLng(0)
      FilterSize = 4
      bResult = m_oCLOpen.vbFastNdisRequest(OID_GEN_CURRENT_PACKET_FILTER, OldFilter, FilterSize)
      If (Not bResult) Then
         oLog.Write ("Unable to obtain pretest filter state. Assuming it is NONE")
         OldFilter = 0
      End If
      
      l_nFilters = CLng(0)     
      If (Media = NDISMEDIUM802_3) Then
         l_nFilters = DIRECTED + BROADCAST + MULTICAST
         
         bResult = vbSilentSetPacketFilter(ALL_MULTICAST)
         If (bResult) Then
            l_nFilters = l_nFilters + ALL_MULTICAST
         End If
      ElseIf (Media = NDISMEDIUM802_5) Then
         l_nFilters = DIRECTED + BROADCAST + FUNCTIONAL + GROUP_PKT
         
         bResult = vbSilentSetPacketFilter(ALL_FUNCTIONAL)
         If (bResult) Then
            l_nFilters = l_nFilters + ALL_FUNCTIONAL
         End If
         
         bResult = vbSilentSetPacketFilter(SOURCE_ROUTING)
         If (bResult) Then
            l_nFilters = l_nFilters + SOURCE_ROUTING
         End If
         
         bResult = vbSilentSetPacketFilter(MAC_FRAME)
         If (bResult) Then
            l_nFilters = l_nFilters + MAC_FRAME
         End If
         
      ElseIf (Media = NDISMEDIUMFDDI) Then
         l_nFilters = DIRECTED + BROADCAST + MULTICAST
         
         bResult = vbSilentSetPacketFilter(ALL_MULTICAST)
         If (bResult) Then
            l_nFilters = l_nFilters + ALL_MULTICAST
         End If
         
         bResult = vbSilentSetPacketFilter(SOURCE_ROUTING)
         If (bResult) Then
            l_nFilters = l_nFilters + SOURCE_ROUTING
         End If
         
         bResult = vbSilentSetPacketFilter(MAC_FRAME)
         If (bResult) Then
            l_nFilters = l_nFilters + MAC_FRAME
         End If
         
         bResult = vbSilentSetPacketFilter(SMT)
         If (bResult) Then
            l_nFilters = l_nFilters + SMT
         End If
      Else
         call oLog.SafeFailed ("vbGetFilters called for invalid media type 0x" & Hex(Media), 88888)
      End If
      
      bResult = vbSilentSetPacketFilter(PROMISCUOUS)
      If (bResult) Then
         l_nFilters = l_nFilters + PROMISCUOUS
      Else
         ' Error is logged by LogoCheck.wsf
      End If
      
      bResult = vbSilentSetPacketFilter(ALL_LOCAL)
      If (bResult) Then
         l_nFilters = l_nFilters + ALL_LOCAL
      End If
      
      bResult = vbSilentSetPacketFilter(OldFilter)
      If (Not bResult) Then
         oLog.Write ("Unable to restore filter to pretest state")
      End If
      
      vbGetFilters = l_nFilters
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisOpen, CLanCard::vbSetupBasicTest
   '*/
   Public Function vbMediaConnectStatus(byref nStatus)
   Dim bRetval : bRetval = False
      
      bRetval = vbFastNdisRequest(OID_GEN_MEDIA_CONNECT_STATUS, nStatus, 4)
      If(bRetval = False) Then
         oLog.Write "FAILURE: vbFastNdisRequest() failed!"
         Exit Function
      End If
      
      vbMediaConnectStatus = True
      
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisOpen, CLanCard::vbSetupBasicTest
   '*/
   Public Function vbNdisOpen
      vbNdisOpen = m_oCLOpen.vbNdisOpen()
   End Function
   
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisRequest
   '*/
   Public Function vbNdisRequest(ByVal nOID, ByRef DataArray, ByVal DataLen, ByVal QueryType, ByRef BytesWritten, ByRef BytesNeeded, ByRef nNdisStatus, ByVal bResize)
      vbNdisRequest = m_oCLOpen.vbNdisRequest(nOID, DataArray, DataLen, QueryType, BytesWritten, BytesNeeded, nNdisStatus, bResize)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbSetRemoteId
   '*/
   Public Sub vbSetRemoteId (lTestId)
      m_oCLOpen.vbSetRemoteId lTestId
   End Sub
   
   '================================================================================================='
   '/**
   '@sa COpen::vbSetLocalId
   '*/
   Public Sub vbSetLocalId (lTestId)
      m_oCLOpen.vbSetLocalId lTestId
   End Sub
   
   '================================================================================================='
   '/**
   '@sa COpen::vbSetReceiveOption
   '*/
   Public Sub vbSetReceiveOption (lReceiveOption)
      m_oCLOpen.vbSetReceiveOption lReceiveOption
   End Sub
   
   '================================================================================================='
   '/**
   '@sa COpen::vbSetChannelId
   '*/
   Public Sub vbSetChannelId (lTestId)
      m_oCLOpen.vbSetChannelId lTestId
    End Sub
   
   '================================================================================================='
   '/**
   '@sa COpen::vbVerifiedSendPackets
   '*/
   Public Function vbVerifiedSendPackets (arrDestAddr, nNumAddresses, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
      vbVerifiedSendPackets = m_oCLOpen.vbVerifiedSendPackets(arrDestAddr, nNumAddresses, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbVerifiedSend
   '*/
   Public Function vbVerifiedSend (DestAddr, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
      vbVerifiedSend = m_oCLOpen.vbVerifiedSend (DestAddr, nPacketSize, nPacketsToSend, nBurstSize, ResendAddr)
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbSendPackets
   '*/
   Public Function vbSendPackets(arrDestAddr, lNumAddresses, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
      vbSendPackets = m_oCLOpen.vbSendPackets(arrDestAddr, lNumAddresses, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbSend
   '*/
   Public Function vbSend(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
      vbSend = m_oCLOpen.vbSend(DestAddr, lPacketSize, lNumPackets, lTestDuration, ResendAddr)
   End Function   
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbStopSend
   '*/
   Public Function vbStopSend
      vbStopSend = m_oCLOpen.vbStopSend
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbWaitSend
   '*/
   Public Function vbWaitSend
      vbWaitSend = m_oCLOpen.vbWaitSend
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbGetSendResults
   '*/
   Public Function vbGetSendResults(ByRef lPacketsSent, ByVal lSendFailureType)
      vbGetSendResults = m_oCLOpen.vbGetSendResults(lPacketsSent, lSendFailureType)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbStartReceive
   '*/
   Public Function vbStartReceive
      vbStartReceive = m_oCLOpen.vbStartReceive
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbStopReceive
   '*/
   Public Function vbStopReceive
      vbStopReceive = m_oCLOpen.vbStopReceive
   End Function
   
   
   '================================================================================================='
   '/**
   '@sa COpen::vbGetReceiveResults
   '*/
   Public Function vbGetReceiveResults (ByRef nPacketsReceived, ByRef nPacketsResent)
      vbGetReceiveResults = m_oCLOpen.vbGetReceiveResults (nPacketsReceived, nPacketsResent)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbVerifyReceiveResendRet
   '*/
   Public Function vbVerifyReceiveResendRet(ByRef lRecvExpected, ByVal lMinRecvRequired, ByRef lResendExpected, ByVal lMinResendRequired)
      vbVerifyReceiveResendRet = m_oCLOpen.vbVerifyReceiveResendRet(lRecvExpected, lMinRecvRequired, lResendExpected, lMinResendRequired)
   End Function
   
   '================================================================================================='
   '/**
   'This function is the same as vbVerifyReceiveResendRet, it does not modify the passed variables   '@sa COpen::vbVerifyReceiveResendRet
   '*/
   Public Function vbVerifyReceiveResend(ByVal lRecvExpected, ByVal lMinRecvRequired, ByVal lResendExpected, ByVal lMinResendRequired)
      vbVerifyReceiveResend = Me.vbVerifyReceiveResendRet(lRecvExpected, lMinRecvRequired, lResendExpected, lMinResendRequired)
   End Function

   '================================================================================================='
   '/**
   '@sa COpen::vbSendRaw
   '*/
   Public Function vbSendRaw(ByVal DataArray)
      vbSendRaw = m_oCLOpen.vbSendRaw
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbClearEvents
   '*/
   Public Function vbClearEvents
      oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbClearEvents" & CWLAN_PRINT_END
      vbClearEvents = m_oCLOpen.vbClearEvents()
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisClose
   '*/
   Public Function vbNdisClose
      vbNdisClose = m_oCLOpen.vbNdisClose
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbFastNdisRequest
   '*/
   Public Function vbFastNdisRequest(ByVal nOID, ByRef Result, ByRef ResultSize)
      vbFastNdisRequest = m_oCLOpen.vbFastNdisRequest(nOID, Result, ResultSize)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbPrintNdisRequest
   '*/
   Public Function vbPrintNdisRequest(ByVal nOID)
      vbPrintNdisRequest = m_oCLOpen.vbPrintNdisRequest(nOID)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbNdisReset
   '*/
   Public Function vbNdisReset()
      vbNdisReset = m_oCLOpen.vbNdisReset
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbGetEvents
   '*/
   Public Function vbGetEvents(ByRef nResets, ByRef nDisconnects, ByRef nConnects)
      vbGetEvents = m_oCLOpen.vbGetEvents (nResets, nDisconnects, nConnects)
   End Function
   
   
   '================================================================================================='
   '/**
   '@sa COpen::vbStartPerformance
   '*/
   Public Function vbStartPerformance(oRemoteOpen, DestAddr, TestMode, PacketSize, PktsPerBurst, NumPackets, TestDuration, Delay, CancelPkts)
      vbStartPerformance = m_oCLOpen.vbStartPerformance (oRemoteOpen.COMOpen, DestAddr, TestMode, PacketSize, PktsPerBurst, NumPackets, TestDuration, Delay, CancelPkts)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbWaitPerformance
   '*/
   Public Function vbWaitPerformance ()
      vbWaitPerformance = m_oCLOpen.vbWaitPerformance()
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbGetPerformanceResults
   '*/
   Public Function vbGetPerformanceResults (nDuration, nBytesSent, nBytesReceived)
      vbGetPerformanceResults = m_oCLOpen.vbGetPerformanceResults(nDuration, nBytesSent, nBytesReceived)
   End Function
   
   '================================================================================================='
   '/**
   '@sa COpen::vbStartWaitForEvent
   '*/
   Public Function vbStartWaitForEvent(lEvent)
      vbStartWaitForEvent = m_oCLOpen.vbStartWaitForEvent(lEvent)
      If (Not vbStartWaitForEvent) Then
         Call oLog.SafeFailed ("Unable to start wait for event", 88888)
      End If 
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbEndWaitForEvent
   '*/
   Public Function vbEndWaitForEvent(lTimeOut)
      vbEndWaitForEvent = m_oCLOpen.vbEndWaitForEvent(lTimeOut)
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbStartStress
   '*/
   Public Function vbStartStress(oSvrOpen, lPacketSize, lOptionsMask, lIterations, lTestDuration)
      vbStartStress = m_oCLOpen.vbStartStress(oSvrOpen, lPacketSize, lOptionsMask, lIterations, lTestDuration)
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbWaitStress
   '*/
   Public Function vbWaitStress()
      vbWaitStress = m_oCLOpen.vbWaitStress()
   End Function
   
   '===============================================================================================//
   '/**
   '@sa COpen::vbGetStressResults
   '*/
   Public Function vbGetStressResults()
      vbGetStressResults = m_oCLOpen.vbGetStressResults()
   End Function
   
   '===============================================================================================//
   '/**
   '@sa CCLOpen::vbGetMaxLookahead
   '*/
   Public Function vbGetMaxLookahead(ByRef lMaxLookAhead)
      vbGetMaxLookahead = m_oCLOpen.vbGetMaxLookahead(lMaxLookAhead)
   End Function
   
   
   '============================================================================================='
   '/**
   'Adds the new multicast address into the multicast address list in the NIC
   'enabled for packet reception. It uses either OID_802_3_MULTICAST_LIST or 
   'OID_FDDI_LONG_MULTICAST_LIST for this purpose.
   '@TODO: This function will break after we move to Ndis 6.0
   '@params
   '  !  array The multicast address to be added
   '@return True on success, false otherwise
   '@code
   'If (Not oTestOpen.vbAddMuticastAddr(MultAddr)) Then 
   '   Exit Function
   'End If
   '@endcode
   '@sa CLanOpen::vbRemoveMulticastAddr, CLanOpen::vbSetPacketFilter
   '*/
   Public Function vbAddMulticastAddr(ByVal NewMulticastAddr)
      Dim bResult
      Dim ulOid
      Dim ulSizeOid
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim MaxListSize
      
      Dim MulticastAddrList()
      Dim ListLen
      
      Dim Media
      
      Media = m_oCLOpen.NdisMedium
      Do
         bResult = TRUE
         
         '
         ' check for valid medium and set ulOidCode as appropriate
         '
         If((Media = NDISMEDIUM802_3) Or (Media = NDISMEDIUMDIX)) Then
            ulOid = OID_802_3_MULTICAST_LIST
            ulSizeOid = OID_802_3_MAXIMUM_LIST_SIZE 
         ElseIf (Media = NDISMEDIUMFDDI) Then
            ulOid = OID_FDDI_LONG_MULTICAST_LIST
            ulSizeOid = OID_FDDI_LONG_MAX_LIST_SIZE
         Else
            Call oLog.SafeFailed("Add Multicast Address not valid for this mediatype", 88888)
            bResult = FALSE
            Exit Do
         End If
         
         ' Get the maximum number of multicast addresses possible
         MaxListSize = CLng(0)
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)
         
         bResult = Me.vbNdisRequest( _
               ulSizeOid, _
               MaxListSize, _
               4, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(Not bResult) Then
            Call oLog.SafeFailed("Unable to get max multicast list size from " & m_oCLOpen.AdapterType, 88888 )
            Exit Do
         End If
         
         ' The array MulticastAddrList holds the net addresses, in sequence,
         ' with the first 6 bytes forming one address, the next 6 the second, and so on
         
         ' The maximum size of this array is then 6 times the maximum addresses
         ListLen = 6 * MaxListSize
         
         Redim MulticastAddrList(ListLen-1)
         
         ' Let it be know that MulticastAddrList is an array of bytes
         MulticastAddrList(0) = CByte(MulticastAddrList(0))
         
         bResult = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               TRUE)
         If(Not bResult Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to obtain old multicast address list from " & m_oCLOpen.AdapterType, 88888 )
            bResult = FALSE
            Exit Do
         Else
            ' Actual number of entries in the list
            ListLen = BytesWritten
         End If
         
         If (ListLen = 6*MaxListSize) Then
            ' In this case, the list is full, we should not try
            ' adding this address. But check if the address is already 
            ' present, in which case everything is okay
            
            Dim iIndex
            Dim iCnt
            bResult = FALSE
            iIndex = 0
            For iCnt = 0 To (ListLen \ 6 - 1)
               If (NetAddrCmpI(MulticastAddrList, NewMulticastAddr, iIndex)) Then
                  bResult = TRUE
                  Exit For
               End If
               iIndex = iIndex + 6
            Next  
            
            If (bResult) Then
               oLog.Write("Multicast address to be added already present" )
            Else
               oLog.Write("Multicast address list full. Could not add" )
            End If
            Exit Do
         End If
         
         ' If the multicast address list already contains the address we wish
         ' to add, we donot worry. We just add the new address. The adapter
         ' should be able to eliminate redundancies
         ' If we wish to remove the copy, we can use the loop from the delete 
         ' command below
         
         MulticastAddrList(ListLen+0) = NewMulticastAddr(0)
         MulticastAddrList(ListLen+1) = NewMulticastAddr(1)
         MulticastAddrList(ListLen+2) = NewMulticastAddr(2)
         MulticastAddrList(ListLen+3) = NewMulticastAddr(3)
         MulticastAddrList(ListLen+4) = NewMulticastAddr(4)
         MulticastAddrList(ListLen+5) = NewMulticastAddr(5)
         
         ListLen = ListLen + 6
         
         BytesWritten = 0
         BytesNeeded = 0 
         
         bResult = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(Not bResult) Then
            Call oLog.SafeFailed("Unable to add multicast address to list on " & m_oCLOpen.AdapterType, 88888 )
         ElseIf (NdisStatus = NDIS_STATUS_MULTICAST_FULL) Then
            Call oLog.SafeFailed("Multicast address list full on " & m_oCLOpen.AdapterType, 88888)
            bResult = FALSE
         ElseIf (NdisStatus <> 0) Then
            Call oLog.SafeFailed("Add Multicast address failed on " & m_oCLOpen.AdapterType, 88888)
            bResult = FALSE
         End If
      Loop While(FALSE)
      vbAddMulticastAddr = bResult
   End Function
   
   '============================================================================================='
   '/**
   'Removes the given multicast address from the multicast address list
   'for the NIC.It uses either OID_802_3_MULTICAST_LIST or 
   'OID_FDDI_LONG_MULTICAST_LIST for this purpose.
   '@TODO: This function will break after we move to Ndis 6.0
   '@params
   '  !  array The multicast address to be removed
   '@return True on success, false otherwise
   '@code
   'If (Not oTestOpen.vbRemoveMulticastAddr(MultAddr)) Then 
   '   oLog.Write("Unable to remove multicast address")
   'End If
   '@endcode
   '@sa CLanOpen::vbAddMulticastAddr, CLanOpen::vbSetPacketFilter
   '*/
   Public Function vbRemoveMulticastAddr(ByVal OldMulticastAddr)
      Dim bResult
      Dim ulOid
      Dim ulSizeOid
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim MaxListSize
      Dim NewListLen
      Dim MulticastAddrList()
      Dim ModMulticastAddrList()
      Dim ListLen
      Dim iCnt
      Dim iNewIndex, iOldIndex
      
      Dim Media
      
      Media = m_oCLOpen.NdisMedium
      
      Do
         bResult = TRUE
         
         '
         ' check for valid medium and set ulOidCode as appropriate
         '
         If ((Media = NDISMEDIUM802_3) Or (Media = NDISMEDIUMDIX)) Then
            ulOid = OID_802_3_MULTICAST_LIST
            ulSizeOid = OID_802_3_MAXIMUM_LIST_SIZE 
         ElseIf (Media = NDISMEDIUMFDDI) Then
            ulOid = OID_FDDI_LONG_MULTICAST_LIST
            ulSizeOid = OID_FDDI_LONG_MAX_LIST_SIZE
         Else
            Call oLog.SafeFailed("Delete Multicast Address not valid for this mediatype" , 88888)
            bResult = FALSE
            Exit Do
         End If
         
         ' Get the maximum number of multicast addresses possible
         MaxListSize = CLng(0)
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)
         bResult = Me.vbNdisRequest( _
               ulSizeOid, _
               MaxListSize, _
               4, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(Not bResult Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to get max multicast list size from " & m_oCLOpen.AdapterType, 88888 )
            bResult = FALSE
            Exit Do
         End If
         
         ' The array MulticastAddrList holds the net addresses, in sequence,
         ' with the first 6 bytes forming one address, the next 6 the second, and so on
         
         ' The maximum size of this array is then 6 times the maximum addresses
         ListLen = 6 * MaxListSize
         
         Redim MulticastAddrList(ListLen-1)
         
         ' Let it be know that MulticastAddrList is an array of bytes
         MulticastAddrList(0) = CByte(MulticastAddrList(0))
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)
         
         bResult = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               TRUE)
         If(Not bResult Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to obtain old multicast address list from " & m_oCLOpen.AdapterType, 88888)
            bResult = FALSE
            Exit Do
         Else
            ' Actual number of entries in the list
            ListLen = BytesWritten
         End If
         
         ' Maximum filled size of the new list that we would form
         Redim ModMulticastAddrList(ListLen-1)
         
         iNewIndex = CLng(0)
         iOldIndex = CLng(0)
         
         NewListLen = ListLen
         
         ' Here, we are deleting all the occurences of the address. But,
         ' we can modify to check if the card returns multiple copies of 
         ' an address by removing only the first occurence
         
         For iCnt = 0 To (ListLen \ 6 - 1)
            If (NetAddrCmpI(MulticastAddrList, OldMulticastAddr, iOldIndex)) Then
               NewListLen = NewListLen - 6
            Else
               ModMulticastAddrList(iNewIndex)   = MulticastAddrList(iOldIndex)
               ModMulticastAddrList(iNewIndex+1) = MulticastAddrList(iOldIndex+1)
               ModMulticastAddrList(iNewIndex+2) = MulticastAddrList(iOldIndex+2)
               ModMulticastAddrList(iNewIndex+3) = MulticastAddrList(iOldIndex+3)
               ModMulticastAddrList(iNewIndex+4) = MulticastAddrList(iOldIndex+4)
               ModMulticastAddrList(iNewIndex+5) = MulticastAddrList(iOldIndex+5)
               iNewIndex = iNewIndex + 6
            End If
            iOldIndex = iOldIndex + 6
         Next
         
         ' If we had to copy all the old addresses to the new one, we did not find the 
         ' address to delete
         If (NewListLen = ListLen) Then
            Call oLog.SafeFailed("Unable to find the multicast address to delete on " & m_oCLOpen.AdapterType, 88888)           
            bResult = FALSE
            Exit Do
         End If
         
         ListLen = NewListLen
         
         BytesWritten = 0
         BytesNeeded = 0 
         
         bResult = Me.vbNdisRequest( _
               ulOid, _
               ModMulticastAddrList, _
               ListLen, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(Not bResult Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to delete multicast address from list on " & m_oCLOpen.AdapterType, 88888)
            bResult = FALSE
         End If
         
      Loop While (False)
      vbRemoveMulticastAddr = bResult
   End Function
   
   '============================================================================================='
   '/**
   'This function sets the current functional address for the
   'open instance (token ring). It sets the address using the oid
   'OID_802_5_CURRENT_FUNCTIONAL.
   '@TODO: This function may break after we move to Ndis 6.0
   '@params 
   '  !  array ParamFunctionalAddr       The functional address to set
   '@return True on success, false otherwise
   '@code
   'If (Not oTestOpen.vbSetFunctionalAddr(FuncAddr)) Then 
   '   Exit Function
   'End If
   '@endcode
   '@sa CLanOpen::vbSetGroupAddr, CLanOpen::vbSetPacketFilter
   '*/
   Public Function vbSetFunctionalAddr(ByVal ParamFunctionalAddr)
      Dim bResult
      Dim ulOid
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim FunctionalAddr
      
      Dim Media
      
      Media = m_oCLOpen.NdisMedium
      NdisStatus = CLng(0)
      
      FunctionalAddr = ParamFunctionalAddr ' Do this because NdisRequest can change it
      
      Do
         bResult = FALSE
         
         '
         ' make sure that this is a valid OID code.  ie, must be token ring
         '  
         If (Media <> NDISMEDIUM802_5) Then
            Call oLog.SafeFailed("SetFunctional not valid for this mediatype", 88888)
            Exit Do
         End If
         
         ulOid = OID_802_5_CURRENT_FUNCTIONAL
         
         ' Functional address length is a 4 byte array
         bResult = Me.vbNdisRequest( _
               ulOid, _
               FunctionalAddr, _
               4, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)

      Loop While(FALSE)
      '   SetFunctional = bResult
      If (bResult AND NdisStatus <> 0) Then
         Call oLog.SafeFailed("Unable to set functional address for " & m_oCLOpen.AdapterType, 88888)           
         vbSetFunctionalAddr = FALSE
      Else
         vbSetFunctionalAddr = TRUE
      End If
      
   End Function
   
   '============================================================================================='
   '/**
   'This function sets the group address for the open instance (token ring only)
   'It sets the address using OID_802_5_CURRENT_GROUP oid.
   '@TODO: This function may break after we move to Ndis 6.0
   '@params
   '  ! array The group address to be set to
   '@return True on success, false otherwise
   '@code
   'If (Not oTestOpen.vbSetGroupAddr(GrpAddr)) Then 
   '   Exit Function
   'End If
   '@endcode
   '@sa CLanOpen::vbSetFunctionalAddr, CLanOpen::vbSetPacketFilter
   '*/
   Public Function vbSetGroupAddr(ByVal ParamGroupAddr)
      Dim bResult
      Dim ulOid
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim GroupAddr
      
      Dim Media
      
      Media = m_oCLOpen.NdisMedium
      NdisStatus = CLng(0)
      
      GroupAddr = ParamGroupAddr ' Do this because NdisRequest can change it
      
      Do
         bResult = FALSE
         
         '
         ' make sure that this is a valid OID code.  ie, must be token ring
         '  
         If (Media <> NDISMEDIUM802_5) Then
            Call oLog.SafeFailed("SetGroup not valid for this mediatype", 88888)
            Exit Do
         End If
         
         ulOid = OID_802_5_CURRENT_GROUP
         
         ' Group address length is a 4 byte array
         bResult = Me.vbNdisRequest( _
               ulOid, _
               GroupAddr, _
               4, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         
      Loop While(FALSE)
      If (bResult AND NdisStatus <> 0) Then
         Call oLog.SafeFailed("Unable to set group address for " & m_oCLOpen.AdapterType,88888)
         vbSetGroupAddr = FALSE
      Else
         vbSetGroupAddr = TRUE
      End If
      
   End Function
   
   '============================================================================================='
   '/**
   '@sa CCLOpen::vbSetLookahead
   '*/        
   Public Function vbSetLookahead(ByVal Lookahead)
      vbSetLookahead = m_oCLOpen.vbSetLookahead (Lookahead)
   End Function
   
   '===============================================================================================//
   '/**
   'This function sets the Source and Destination IP addresses on open instance
   '@params 
   '  ! string IP Address of a given adapter
   '  ! string IP Address of the adapter destined to receive IP packets
   '  ! array  MAC Address of the adapter's default gateway
   '@return	    Returns true if succesful else return false
   '@code
   'TestIP = "10.10.10.1"
   'SuppIP = "10.10.10.2"
   'TestGWAddr = Array(CByte(0),CByte(1),CByte(2),CByte(3),CByte(4),CByte(5))
   'bResult = oTestOpen.vbSetIPAddr(TestIP, SuppIP, TestGWAddr)
   '@endcode
   '*/
   Public Function vbSetIPAddress (sSrcIP, sDstIP, SrcGWAddr)
      Dim oCOMOpen
      
      Set oCOMOpen = m_oCLOpen.COMOpen
      vbSetIPAddress = oCOMOpen.SetIPAddr(sSrcIP, sDstIP, SrcGWAddr)
      if (not vbSetIPAddress) Then
         Call oLog.SafeFailed ("SetIPAddr failed for " & m_oCLOpen.AdapterType, 22849)
      end if
      
      Set oCOMOpen = Nothing
   End Function

   '===============================================================================================//
   '/**
   'This API can be used to check if send and receive is working between two devices. 
   'The calling device is the sending instance and the passed device is the receiving/resending instance. 
   'It setups the instances for sending/receiving/resending and then sends 
   'the data and checks if the send/receive/resend was successful. 
   'All functions called by this function would log failures and hence the caller may use 
   'appropriate masks to avoid any kind of failure logging.
   'This function uses NdisSend to send.
   '@params 
   '  ! class  The receiving instance
   '@return	   0 if everything (send-receive?resend) worked<br>
   '           1 if set up error<br>
   '           2 if send-receive failed<br>
   '@code
   '  'Stop logging of failures
   '  nLogMask = oLog.Mask
   '  oLog.Mask = DO_NOTHING
   '  nResult = oTestOpen.vbSimpleSendReceive (oSuppOpen)
   '  oLog.Mask = nLogMask
   '
   '  If (nResult <> 0) Then
   '     Call oLog.Failed ("Send receive does not work after loading/unloading of the driver", 88888)
   '  End If
   '@endcode
   '*/
   Public Function vbSimpleSendReceive (ByVal oRcvrOpen)
      Dim nTestId
      Dim nRetval, bResult, nResult
      Dim nTotalPackets, nPacketSize
      Dim nMinimumPass, nReceiveDelay

      Dim RcvrAddr, SenderAddr

      Const NO_ERROR = 0
      Const SETUP_ERROR = 1
      Const SENDRECV_ERROR = 2
      
      nRetval = NO_ERROR
      '
      ' Set the packet filters
      '
      If (Not oRcvrOpen.vbSetPacketFilter(DIRECTED)) Then
         nRetval = SETUP_ERROR
      End If

      If (Not Me.vbSetPacketFilter(DIRECTED)) Then
         nRetval = SETUP_ERROR
      End If

      nTestId = oNDTSupp.Random(1, 32765)

      ' set the channel id on sending/receiving sides
      Me.vbSetLocalId (nTestId)
      Me.vbSetRemoteId (nTestId)
      oRcvrOpen.vbSetLocalId (nTestId)
      oRcvrOpen.vbSetRemoteId (nTestId)
      
      ' Set receive options
      oRcvrOpen.vbSetReceiveOption(RECEIVE_DEFAULT Or RECEIVE_ALLOW_BUSY_NET)

      nTotalPackets = glPacketsToSend
      nPacketSize = glMinimumPacketSize
      nReceiveDelay = Me.vbGetReceiveDelay()

      ' get the address of the receiving nic
      RcvrAddr = oRcvrOpen.vbGetCardAddress()
      SenderAddr = Me.vbGetCardAddress ()

      ' Start receiving on the other open instance
      oRcvrOpen.vbStartReceive()
      Me.vbStartReceive ()
      
      ' send with resend info
      nResult = Me.vbVerifiedSend(RcvrAddr, nPacketSize, nTotalPackets, 0, SenderAddr)
      
      If (nResult <> nTotalPackets) Then
         nRetval = nRetval Or SENDRECV_ERROR
      End If

      nMinimumPass = (glPercentToPass * nTotalPackets) / 100
      
      Wscript.Sleep nReceiveDelay
      '
      ' the receiving card should receive all packets
      '
      bResult = oRcvrOpen.vbStopReceive
      If (bResult) Then
         ' check if received
         bResult = oRcvrOpen.vbVerifyReceiveResend(nTotalPackets, nMinimumPass, nTotalPackets, nMinimumPass)
         
         If (Not bResult) Then
            nRetval = nRetval Or SENDRECV_ERROR
         End If
      Else
         nRetval = nRetval Or SENDRECV_ERROR
      End If

      Wscript.Sleep nReceiveDelay
      '
      ' the sending should also receive all packets
      '
      
      bResult = Me.vbStopReceive
      If (bResult) Then
         bResult = Me.vbVerifyReceiveResend(nTotalPackets, nMinimumPass, 0, 0)
         If (Not bResult) Then
            nRetval = nRetval Or SENDRECV_ERROR
         End If
      Else
         nRetval = nRetval Or SENDRECV_ERROR
      End If

      vbSimpleSendReceive = nRetval
   End Function
   
   
   '**********************************************************'
   '                                                          '
   '          Function related to priority test               '
   '                                                          ' 
   '**********************************************************'

   '============================================================================================='
   '/**
   'This function tells the driver to start sending packets to
   'the address specified, with size, count, and resend address
   'also specified
   '@params
   '  ! class  The open instance on the server side
   '  ! array  The destination address
   '  ! number The packet size to use
   '  ! number Number of packets to send
   '  ! number The delay between packets
   '  ! constant Send Mode to use (PRIORITY_SEND, PRIORITY_SEND_PACKETS)
   '@return  TRUE or FALSE depending on the success of the operation
   '@sa  CLanOpen::vbWaitPriority, CLanOpen::vbGetPriorityResults
   '*/     
   Public Function vbStartPriority(oRemoteOpen, DestAddr, PacketSize, NumPackets, lDelay, SendMode)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      
      vbStartPriority = oCOMOpen.StartPriority (oRemoteOpen.COMOpen, DestAddr, PacketSize, NumPackets, lDelay, SendMode)
      If (Not vbStartPriority) Then
         Call oLog.SafeFailed ("Unable to start priority tests in " & m_oCLOpen.AdapterType, 21594)
      End If
      Set oCOMOpen = Nothing
   End Function   
   
   '============================================================================================='
   '/**
   ' This function waits until the remote server is done performing a
   ' priority send test, sending packets, then it returns
   '@return TRUE or FALSE depending on the success of the operation
   '@sa  CLanOpen::vbStartPriority, CLanOpen::vbGetPriorityResults
   '*/     
   Public Function vbWaitPriority   
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      
      vbWaitPriority = oCOMOpen.WaitPriority()
      If (Not vbWaitPriority) Then
         Call oLog.SafeFailed ("Unable to wait for priority tests on " & m_oCLOpen.AdapterType, 21595)
      End If
      Set oCOMOpen = Nothing
   End Function

   '============================================================================================='
   '/**
   'This function logs the results of the previous priority
   'tests.  It expects to be called after a waitpriority
   '@sa  CLanOpen::vbWaitPriority, CLanOpen::vbStartPriority
   '*/     
   Public Function vbGetPriorityResults   
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      
      vbGetPriorityResults = oCOMOpen.GetPriorityResults()
      If (Not vbGetPriorityResults) Then
         Call oLog.SafeFailed ("Unable to get priority test results on " & m_oCLOpen.AdapterType, 21596)
      End If    
      Set oCOMOpen = Nothing        
   End Function

   '**********************************************************'
   '                                                          '
   '          Function related to Wake-On-Lan                 '
   '                                                          ' 
   '**********************************************************'

   '============================================================================================='
   '/**
   'This function adds the specified wake pattern to the list kept by the NIC
   '@params
   '  !  number The NdisStatus of the operation is returned in this variable
   '  !  number The first piece of the pattern
   '  !  number The offset position of of the first piece in the pattern
   '  !  number The next piece of the pattern
   '  !  number The offset position of of the second piece in the pattern
   '  !  number The third piece of the pattern
   '  !  number The offset position of of the third piece in the pattern
   '@return True on success or false if failed to set wakeup type
   '@code
   'Piece1 = &H12345&
   'Piece2 = &H6789A&
   'Piece3 = &HBCDEF&
   '
   'If (oTestOpen.vbAddWakePattern (nNdisStatus, 0, Piece1, 4, Piece2, 8, Piece3)) Then
   '  oLog.Write ("Addition failed")
   'Exit Function
   '@endcode
   '@sa CLanOpen::vbRemoveWakePattern, CLanOpen::vbSetWakeupType
   '*/   
   Public Function vbAddWakePattern (nNdisStatus, Offset1, Piece1, Offset2, Piece2, Offset3, Piece3)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      vbAddWakePattern = oCOMOpen.AddWakePattern (nNdisStatus, CLng (Offset1), CLng (Piece1), _
            CLng (Offset2), CLng (Piece2), CLng (Offset3), CLng (Piece3))
      
      If Not vbAddWakePattern Then
         call oLog.SafeFailed ("Failed to Add Wake Pattern to the " & m_oCLOpen.AdapterType, 88888)
      End If
      
      Set oCOMOpen = Nothing
   End Function

   '============================================================================================='
   '/**
   'This function removes the specified wake pattern from the list kept by the NIC
   '@params
   '  !  number The NdisStatus of the operation is returned in this variable
   '  !  number The first piece of the pattern
   '  !  number The offset position of of the first piece in the pattern
   '  !  number The next piece of the pattern
   '  !  number The offset position of of the second piece in the pattern
   '  !  number The third piece of the pattern
   '  !  number The offset position of of the third piece in the pattern
   '@return True on success or false if failed to set wakeup type
   '@code
   'Piece1 = &H12345&
   'Piece2 = &H6789A&
   'Piece3 = &HBCDEF&
   '
   'If (oTestOpen.vbRemoveWakePattern (nNdisStatus, 0, Piece1, 4, Piece2, 8, Piece3)) Then
   '  oLog.Write ("Removal failed")
   'Exit Function
   '@endcode
   '@sa CLanOpen::vbAddWakePattern, CLanOpen::vbSetWakeupType  
   '*/   
   Public Function vbRemoveWakePattern (nNdisStatus, Offset1, Piece1, Offset2, Piece2, Offset3, Piece3)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      vbRemoveWakePattern = oCOMOpen.RemoveWakePattern (nNdisStatus, CLng (Offset1), CLng (Piece1), _
            CLng (Offset2), CLng (Piece2), CLng (Offset3), CLng (Piece3))
      
      If Not vbRemoveWakePattern Then
         call oLog.SafeFailed ("Failed to Remove Wake Pattern from the " & m_oCLOpen.AdapterType, 88888)
      End If
      
      Set oCOMOpen = Nothing
   End Function
   
   '============================================================================================='
   '/**
   'This function sets Wakeup type information onto the NIC.
   '@params !  constant The type of event to wakeup on. The values are<br>
   '                 WAKE_UP_MAGIC_PACKET    Wake on receiving a magic packet<br>
   '                 WAKE_UP_PATTERN_MATCH   Wake up on receiving a registered pattern 
   '@return True on success or false if failed to set wakeup type
   '@code
   'If (not oTestOpen.vbSetWakeupType (WAKE_UP_PATTERN_MATCH)) Then
   '  call oLog.Failed ("Could not set wakeup type on test card", 88888)
   '  Exit Function
   'End If
   '@endcode
   '@sa CLanOpen::vbAddWakePattern, CLanOpen::vbDelayedSendRaw, CLanOpen::vbDelayedSendBuffer, CLanCard::vbWakeOnLanSupportInfo
   '*/
   Public Function vbSetWakeupType (WakeType)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      
      vbSetWakeupType = oCOMOpen.SetWakeupType (WakeType)
      If (Not vbSetWakeupType) Then
         call oLog.SafeFailed ("Unable to set wakeup type for " & m_oCLOpen.AdapterType, 21304)
      End If
      
      Set oCOMOpen = Nothing
   End Function
   
   
   '============================================================================================='
   '/**
   'Delayed send raw tells the Open to send some data (Without making any changes to it)
   'after nDelay amount of time.
   '@return True on success, else failure
   '@code
   '    If (Not oSuppOpen.vbDelayedSendRaw (60, Pattern)) Then
   '       call oLog.Failed ("Unable to get Support card to send delayed pattern")
   '    End If
   '@endcode
   '@sa COpen::vbSend, COpen::vbSendPackets, CLanOpen::vbDelayedSendBuffer
   '*/    
   Public Function vbDelayedSendRaw(nDelay, Data)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      vbDelayedSendRaw = oCOMOpen.DelayedSendRaw (nDelay, Data)
      If (Not vbDelayedSendRaw) Then
         call oLog.SafeFailed ("Delayed Send Raw failed for " & m_oCLOpen.AdapterType, 88888)
      End If
      
      Set oCOMOpen = Nothing
   End Function
   
   '============================================================================================='
   '/**
   'Delayed send Buffer tells the Open to send some data (Without making any changes to it)
   'after nDelay amount of time.
   '@return True on success, else failure
   '@code
   '    If (Not oSuppOpen.vbDelayedSendBuffer (60, BroadcastAddr, Pattern)) Then
   '       call oLog.Failed ("Unable to get Support card to send delayed pattern")
   '    End If
   '@endcode
   '@sa COpen::vbSend, COpen::vbSendPackets, CLanOpen::vbDelayedSendRaw
   '*/    
   Public Function vbDelayedSendBuffer(nDelay, DestAddr, Data)
      Dim oCOMOpen
      Set oCOMOpen = m_oCLOpen.COMOpen
      vbDelayedSendBuffer = oCOMOpen.DelayedSendBuffer (nDelay, DestAddr, Data)
      If (Not vbDelayedSendBuffer) Then
         call oLog.SafeFailed ("Delayed Send Buffer failed for " & m_oCLOpen.AdapterType, 88888)
      End If
      
      Set oCOMOpen = Nothing
   End Function
End Class


'<!-- CRC = 0x0e2825e4 --->
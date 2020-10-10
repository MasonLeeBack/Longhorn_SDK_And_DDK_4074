Option Explicit

Dim oNsiApi
Dim oNsiApiSupp


Function Initialize_NsiApiTest()
   Set oLog = new CLog
   '
   ' Storing global log pointer for backward
   ' compatability with older scripts
   Set oNDTLog = oLog.LogPtr
   
   oLog.Mask = LOG_FAILURE Or LOG_WARNING
   
End Function

Function Terminate_NsiApiTest()
   oLog.LoggingComplete = True
   Set oLog = Nothing
End Function

'===========================================================================
Function SetupTest()
Dim result        : result       = Empty
Dim ndisStatus    : ndisStatus   = -1
   
   SetupTest = False

   'oNDTCore6.DebugLevel = NORMAL_LOGGING_LEVEL
  
   set oNsiApiSupp = Wscript.CreateObject("NDTApi6.NdisNsiSupport.1")
   if (oNsiApiSupp is nothing) then
      oLog.Failed "Failed to create NDIS NSI API support object" , 88888
   exit function
   end if
   oLog.write "NDIS NSI API support object created"
      
      
   set oNsiApi = Wscript.CreateObject("NDTApi6.NsiClientNdis.1")
   if (oNsiApi is nothing) then
      oLog.Failed "Failed to create NSI client object" , 88888
      exit function
   end if
   oLog.write("NSI Client object created")

   '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   oLog.Variation ("Initializing NSI client ...")
   ndisStatus = oNsiApi.InitializeNsiClient()
      
   If ( ndisStatus <> NDIS_STATUS_SUCCESS ) Then
      oLog.Failed "Failed to Initialize NSI client. Status: "& _
                  Hex(ndisStatus) , 88888
      Exit Function
   End If
                 
   SetupTest = True
End Function
 
'==========================================================================

Function CleanupTest()
   Dim ndisStatus : ndisStatus = -1
   ndisStatus = oNsiApi.TerminateNsiClient()
   Set oNsiApiSupp = nothing
   Set oNsiApi = nothing
End Function

'==========================================================================

Function vbPrintBytes(refStr, byteArray, length, offset)
   Dim i
   oLog.Write("Printing "&length &" bytes data from offset "&offset & _
              " in array " &refStr)
   For i = 0 to (length - 1)
      oLog.Write(Hex(byteArray(i+offset)))
   Next
End Function

'==========================================================================
' Take in 8 byte NET_LUID for interface and get the 16 byte Network Guid
Function vbGetNetGuidFromNetLuid(sNetLuid, Byref sNetGuid, Byref lStatus)
   Dim oKeyIfInfo, oSParamIfInfo
   Dim lIfInfoKeyLen, lNetGuidLen, lNetGuidOffset
   Dim oNdtStr, oNsiSupp, oNsiClient
   Dim Status : Status = NDIS_STATUS_FAILURE
  
   Set oNsiSupp = Wscript.CreateObject("NDTApi6.NdisNsiSupport.1")
   Set oNsiClient = Wscript.CreateObject("NDTApi6.NsiClientNdis.1")
   
   vbGetNetGuidFromNetLuid = False
   oLog.Variation("Resolving NetGuid from NetLuid")
   ' Get NetworkGUID for this interface from Information Object GetParameter
   lIfInfoKeyLen = oNsiSupp.Sizeof_NetLuid
   Set oKeyIfInfo = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibKey", lIfInfoKeyLen, TRUE)
   oKeyIfInfo.KeyLength = lIfInfoKeyLen
   oKeyIfInfo.KeyValue = sNetLuid
   lNetGuidLen = oNsiSupp.Sizeof_NetworkGuid
   lNetGuidOffset =  oNsiSupp.OffsetOf_NetworkGuidInInterfaceInformationRW
   Set oSParamIfInfo = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibSingleParam", lNetGuidLen, TRUE)
   oSParamIfInfo.ParamLength = lNetGuidLen   
   oSParamIfInfo.ParamOffset = lNetGuidOffset
   oSParamIfInfo.StructType = NSI_STRUCT_RW
   oLog.Write("Calling GetParameter on IfInfo object for NetworkGuid")
   Status = oNsiApi.GetParameter(NDIS_NSI_INTERFACE_INFORMATION, lNsiStore, _
                                 NSI_GET_EXACT, oKeyIfInfo, oSParamIfInfo)
   lStatus = Status
   
   Set oNdtStr = Nothing
   Set oNsiSupp = Nothing
   Set oNsiClient = Nothing

   if (Status <> NDIS_STATUS_SUCCESS) then
      oLog.Failed "IfInfo GetParameter failed. Status: "& Hex(Status) , 88888
      vbPrintKey(oKeyIfInfo)
      exit function
   end if
  
   sNetGuid = oSParamIfInfo.ParamData

   Set oKeyIfInfo = Nothing
   Set oSParamIfInfo = Nothing

   vbGetNetGuidFromNetLuid = True
End function



'==========================================================================

' Print out the key information
Function vbPrintKey(oKey)
   Dim i, keyData, keyStr

   oLog.Write("Key Length = " & oKey.KeyLength & "     Key Data:")
   keyData = oKey.KeyValue
   For i = 0 to (oKey.KeyLength - 1)
      oLog.Write(Hex(keyData(i)))
   Next
   'For i = 0 to (oKey.KeyLength - 1)
   'Next
   oLog.Write(" ")

End Function

'==========================================================================

Function vbPrintSParameter(oSParam)
   Dim i, sParamData

   oLog.Write("Parameter Length = " & oSParam.ParamLength & _
              "  Parameter Offset = " &oSParam.ParamOffset & _
              "  Parameter Type = " & oSparam.StructType & _
	      "  Parameter Data: ")
   sParamData = oSParam.ParamData
   For i = 0 to (oSParam.ParamLength - 1)
      oLog.Write(Hex(sParamData(i)))
   Next
   oLog.Write(" ")

End Function

'==========================================================================

Function vbPrintParameter(oParam)
   Dim i, paramData, offset

   paramData = oParam.StructData
   oLog.Write("RW Parameter Length = " & oParam.RwStructLength & "RW Data:")
   For i = 0 to (oParam.RwStructLength - 1)
      oLog.Write(Hex(paramData(i)))
   Next
   offset = oParam.RwStructLength
   oLog.Write("ROD Parameter Length = " & oParam.RodStructLength & "ROD Data:")
   For i = 0 to (oParam.RodStructLength - 1)
      oLog.Write(Hex(paramData(offset+i)))
   Next
   offset = offset + oParam.RodStructLength
   oLog.Write("ROS Parameter Length = " & oParam.RosStructLength & "ROS Data:")
   For i = 0 to (oParam.RosStructLength - 1)
      oLog.Write(Hex(paramData(offset+i)))
   Next
   oLog.Write(" ")

End Function

'==========================================================================

Function vbGenRandomByteData(length)
   Dim testData()
   Dim i
   Redim testData(length)
   
   For i = 0 to (length - 1)
      testData(i) = CByte(&HAB&)
   Next
   vbGenRandomByteData = testData
End Function

'==========================================================================
' Return TRUE if every byte matches in both arrays
Function vbCompareBytes(Byref bArray1, off1, Byref bArray2, off2, length)
   Dim i
   vbCompareBytes = True
   For i = 0 to (length - 1)
      if (bArray1(i+off1) <> bArray2(i+off2)) then
         vbCompareBytes = False
	 exit For
      end if
   Next
End Function

'==========================================================================
' Copy bytes from src to dest
Function vbCopyBytes(Byref bArray1, off1, Byref bArray2, off2, length)
   Dim i
   For i = 0 to (length - 1)
      bArray1(i+off1) = bArray2(i+off2)
   Next
   vbCopyBytes = bArray1
End Function
   
'==========================================================================
Function vbCompareKeys(oKey1, oKey2)
   Dim bSts
   vbCompareKeys = False
   If (oKey1.KeyLength <> oKey2.KeyLength) Then
      Exit function
   End If
   bSts = vbCompareBytes(oKey1.KeyValue, 0, oKey2.KeyValue, 0, oKey1.KeyLength)
   If (bSts <> True) Then
      Exit function
   End if
   vbCompareKeys = True
End Function

Function vbCompareSParams(oSParam1, oSParam2)
   Dim bSts
   vbCompareSParams = False
   If (oSParam1.ParamLength <> oSParam2.ParamLength) Then
      Exit function
   End If
   If (oSParam1.StructType <> oSParam2.StructType) Then
      Exit function
   End If
   If (oSParam1.ParamOffset <> oSParam2.ParamOffset) Then
      Exit function
   End If
   bSts = vbCompareBytes(oSParam1.ParamData, 0, oSParam2.ParamData, 0, _
                         oSParam1.ParamLength)
   If (bSts <> True) Then
      Exit function
   End if
   vbCompareSParams = True
End Function

'==========================================================================
Function vbGenRandomByteDataCD(length)
   Dim testData()
   Dim i
   Redim testData(length)
   
   For i = 0 to (length - 1)
      testData(i) = CByte(&HCD&)
   Next
   vbGenRandomByteDataCD = testData
End Function
'==========================================================================
Function vbGenIncrByteData(length, startVal)
   Dim testData()
   Dim i, value
   Redim testData(length)
   
   For i = 0 to (length - 1)
      value = (startVal + i) Mod 256
      testData(i) = CByte(value)
   Next
   vbGenIncrByteData = testData
End Function

'==========================================================================

' This function will call in twice, once with 0 buffer, 0 entry count
' in order to find the required buffer space. Then with the required 
' buffer space allocated in the objects and return the EntryCount, Keys,
' Parameters & the final Status of the second call
' Key is returned as an array of Keys starting at oKey.KeyValue, has
' lNumEntries number of keys, each of length oKey.KeyLength originally
' passed in. Similarly for Parameter Structure values
' The Parameters are organised as follows starting as oParam.StructData:
' lNumEntries * oParam.RwStructLength bytes of lNumEntires RW Struct data
' lNumEntries * oParam.RodStructLength bytes of lNumEntires ROD Struct data
' lNumEntries * oParam.RosStructLength bytes of lNumEntires ROS Struct data
Function vbEnumerateAllParameters(ObjectIndex, NsiStore, NsiGetType, _
                                  Byref NumEntries, Byref oKey, Byref oParam, _
				  Byref lStatus)
   Dim Status
   Dim EntryCount : EntryCount = Clng(0)
   Dim oKeyEnum, oParamEnum
   Dim KeyLen, RwLen, RodLen, RosLen, StructLen
   Dim KeyBufSize, StructBufSize
   Const MORE_ENTRIES = &H00000105&
   Dim bExpectFailure

   ' This means that we expect this call to fail - invalid test
   ' so dont print failure logs
   bExpectFailure = lStatus

   vbEnumerateAllParameters = False

   KeyLen = oKey.KeyLength
   RwLen = oParam.RwStructLength
   RodLen = oParam.RodStructLength
   RosLen = oParam.RosStructLength
   StructLen = RwLen + RodLen + RosLen
   Set oKeyEnum = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibKey", KeyLen, TRUE)
   oKeyEnum.KeyLength = KeyLen
   oKeyEnum.KeyValue = oKey.KeyValue
   Set oParamEnum = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibParam", StructLen, TRUE)
   oParamEnum.RwStructLength = RwLen
   oParamEnum.RodStructLength = RodLen
   oParamEnum.RosStructLength = RosLen
   Status = oNsiApi.EnumerateAllParameters(ObjectIndex, NsiStore, _
                                NsiGetType, EntryCount, oKeyEnum, oParamEnum)
   ' H105 = STATUS_MORE_ENTRIES				
   if ((Status <> NDIS_STATUS_SUCCESS) And (Status <> MORE_ENTRIES)) Then
      If (bExpectFailure = False) Then
         oLog.Failed "Enumerate for querying Count. Status: "& Hex(Status) , _
                     88888
      End if
      lStatus = Status
      exit function
   end if
  
   ' If Entrycount is 0 then there is not data around to return
   if (EntryCount = 0) then 
      oLog.Write("No Data from Enumerate call. Count = "&EntryCount)
      NumEntries = EntryCount
      lStatus = Status
      vbEnumerateAllParameters = True
      exit function
   end if
   
   ' Incase caller passed in Non-zero NumEntries, then use that
   oLog.Write("EntryCount = "& EntryCount &" NumEntries = "& NumEntries)
   If (NumEntries <> 0) Then
      EntryCount = Clng(NumEntries)
   End If
   
   ' Make another call with desired bufferspace allocated
   Set oKeyEnum = Nothing
   Set oParamEnum = Nothing
   KeyBufSize = KeyLen * EntryCount
   StructBufSize = StructLen * EntryCount
   Set oKeyEnum = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibKey", KeyBufSize, TRUE)
   oKeyEnum.KeyLength = KeyLen
   oKeyEnum.EnumCount = EntryCount
   oKeyEnum.KeyValue = oKey.KeyValue
   Set oParamEnum = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibParam", StructBufSize, TRUE)   
   oParamEnum.RwStructLength = RwLen
   oParamEnum.RodStructLength = RodLen
   oParamEnum.RosStructLength = RosLen
   oParamEnum.EnumCount = EntryCount
   
   Status = oNsiApi.EnumerateAllParameters(ObjectIndex, NsiStore, _
                                NsiGetType, EntryCount, oKeyEnum, oParamEnum)   

   NumEntries = EntryCount
   Set oKey = oKeyEnum
   Set oParam = oParamEnum
   lStatus = Status

   if ((Status <> NDIS_STATUS_SUCCESS) And (Status <> MORE_ENTRIES)) Then
      If (bExpectFailure = False) Then
         oLog.Failed "Second Enumerate call went bingo", 88888
      end if
      Exit function
   end if
  
   vbEnumerateAllParameters = True
End Function

'==========================================================================

' Used in conjunction with Enumerated return values of key information
' pass in a key value to search for and returns the number in the record
' where the key was found. If not found -1
Function vbFindKeyIndex(oKey, entryCount, KeyValue, Byref KeyIndex)
   Dim i, offset, keyLen, bStatus
  
   vbFindKeyIndex = True
   
   KeyIndex = -1
   keyLen = oKey.KeyLength
   offset = 0
   'Call vbPrintBytes("Search Key", KeyValue, KeyLen, 0)
   For i = 0 to (entryCount - 1)
      offset = i * KeyLen
      'Call vbPrintBytes("Key", oKey.EnumKeyData, KeyLen, offset)
      bStatus = vbCompareBytes(oKey.EnumKeyData, offset, KeyValue, 0, keyLen)
      'oLog.Write(" i = " &i &" bstatus = " &bStatus)
      if (bStatus = true) then 
         ' Key found at this index
	 KeyIndex = i
	 exit function
      end if
   Next
   oLog.Write("Requested Key Value not found in enumerated key struct")
   vbFindKeyIndex = False
End Function

'==========================================================================

' Used in conjunction with Enumerated return values of key information
' Takes a Key/Param object and returns the key, parameters of requested 
' record number 
Function vbExtractRecord(oKey, oParam, entryCount, recNumber, _
	                 Byref KeyVal, Byref RwParam, _
	                 Byref RodParam, Byref RosParam)
   Dim keyData, rwParamData, rodParamData, rosParamData
   Dim KeyArray, StructArray
   Dim i, offset
   
   Redim keyData(oKey.KeyLength)
   offset = recNumber * oKey.KeyLength
   KeyArray = oKey.EnumKeyData
   For i = 0 to (oKey.KeyLength - 1)
      keyData(i) = KeyArray(offset + i)
   Next
  
   StructArray = oParam.EnumStructData
   
   oLog.Write("EnumKey size: "& (UBound(KeyArray)+1) &" EnumCount: "& _
              oKey.EnumCount)
   oLog.Write("EnumData size: "& (UBound(StructArray)+1) &" EnumCount: "& _
              oParam.EnumCount)
   oLog.Write("Requested Idx: "&recNumber &" EntryCount: "& entryCount)
   oLog.Write("KeyLen: "& oKey.KeyLength &" RWLen: "& oParam.RwStructLength _
     &" RodLen: "& oParam.RodStructLength &" RosLen " &oParam.RosStructLength)
   
   Redim rwParamData(oParam.RwStructLength)
   offset = recNumber * oParam.RwStructLength
   For i = 0 to (oParam.RwStructLength - 1)
      rwParamData(i) = StructArray(offset + i)
   Next
   
   Redim rodParamData(oParam.RodStructLength)
   offset = recNumber * oParam.RodStructLength
   offset = offset + (entryCount * oParam.RwStructLength)
   For i = 0 to (oParam.RodStructLength - 1)
      rodParamData(i) = StructArray(offset + i)
   Next

   Redim rosParamData(oParam.RosStructLength)
   offset = recNumber * oParam.RosStructLength
   offset = (entryCount * (oParam.RwStructLength + oParam.RodStructLength)) _
            + offset
   For i = 0 to (oParam.RosStructLength - 1)
      rosParamData(i) =  StructArray(offset + i)
   Next

   KeyVal = keyData
   RwParam = rwParamData
   RodParam = rodParamData
   RosParam = rosParamData
End Function

' Given a Structure (RW, ROD, ROS or all 3) extract a particular field
Function vbExtractField(StructData, FieldLen, FieldOffset, Byref FieldData)
   Dim fData, i

   Redim fData(FieldLen)
   For i = 0 to (FieldLen - 1)
      fData(i) = StruactData(FieldOffset + i)
   Next
   FieldData = fData
End Function

'==========================================================================

' This polls the change notificaiton context and gets back the first available
' notification event from the kernel queue and prepares them into Key and 
' Param objects and returns these along with notificaion type
Function vbGetChangeNotification(nContext, Byref NotificationType, _
	                         Byref oNotifKey, Byref oNotifParam, _
				 Byref Status)
   Dim oKey : Set oKey = Nothing
   Dim oParam : Set oParam = Nothing
   Dim notifType, lStatus
   Dim sKey, sParam
   Dim keyObjlen, keylen, paramObjlen, paramlen, paramoff, sttype
   Dim keyData, paramData, i
   
   vbGetChangeNotification = False
   Set oNotifKey = Nothing
   Set oNotifParam = Nothing
   NotificationType = -1
   
   lStatus = oNsiApi.GetOneNsiNotificationEvent(nContext, _
                           NSI_NOTIF_GET_DELETE, notifType, sKey, sParam)
   if (lStatus = &H8000001A&) then
      oLog.Write("Notification queue empty for context"& Hex(nContext))
      Status = lStatus
      vbGetChangeNotification = True
      exit  function
   end if
   if (lStatus <> NDIS_STATUS_SUCCESS And lStatus <> &H105&) then
      oLog.Failed "Failed to retrieve change notification for context: "_
                   & Hex(nContext), 88888
      Status = lStatus
      exit function 
   end if

   ' Key Struct obj size = sizeof(ULONG) + Length of the key
   keylen = sKey(0) + (sKey(1)*256) + (sKey(2)*65536) + (sKey(3)*16777216) 
   'keyObjLen = (SIZEOF_ULONG + keyLen + 1)
   Redim keyData(keylen)
   For i = 0 to (keylen - 1)
      keyData(i) = sKey(4 + i)
   Next
   ' Param Struct obj size = 3 * sizeof(ULONG) + Length of the param
   paramlen = sParam(0)+(sParam(1)*256)+(sParam(2)*65536)+(sParam(3)*16777216)
   paramoff = sParam(4)+(sParam(5)*256)+(sParam(6)*65536)+(sParam(7)*16777216)
   sttype = sParam(8)+(sParam(9)*256)+(sParam(10)*65536)+(sParam(11)*16777216)
   Redim paramData(paramlen)
   For i = 0 to (paramlen - 1)
      paramData(i) = sParam(12 + i)
   Next
   'paramObjLen = (3 * SIZEOF_ULONG + paramLen + 1)
   Set oKey = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibKey", keylen, TRUE)
   oKey.KeyLength = keylen
   oKey.KeyValue = keyData
   Set oParam = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibSingleParam", paramlen, TRUE)
   oParam.ParamLength = paramlen
   oParam.ParamOffset = paramoff
   oParam.StructType = sttype
   oParam.ParamData = paramData
 
   ' Assign the values to the reference parameters
   NotificationType = notifType
   Set oNotifKey = oKey
   Set oNotifParam = oParam
   Status = lStatus
   
   vbGetChangeNotification = True
End Function

' Function Resets the notification queue for the context - ie
' Empties any notification events stored there
Function vbResetNotificationQueue(nContext, Byref Status)
   Dim ntype, sKey, sParam, lStatus
   Const NO_MORE_ENTRIES = &H8000001A&

   vbResetNotificationQueue = False
   lStatus = oNsiApi.GetOneNsiNotificationEvent(nContext, _
                              NSI_NOTIF_GET_RESET, ntype, skey, sparam)
   if (lStatus <> NDIS_STATUS_SUCCESS) then
      oLog.Failed "Failed to reset change notification queue for context: "_
                   & Hex(nContext), 88888
      exit function 
   end if
   
   Status = lStatus
   vbResetNotificationQueue = True
End Function

' Function that finds out whether the expected notification parameters
' match what we got in the kernel
Function vbVerifyNotification(tagStr, expNotifType, oExpKey, oExpSParam, _
                              notifType, oKey, oParam)
   Dim bCheckData : bCheckData = True
   vbVerifyNotification = True
 
   If (expNotifType <> notifType) Then
      oLog.Failed "NotificationVerify: Notification type mismatch", 88888
      oLog.Write(tagStr &": Verify Expected "&expNotifType &" Got "&notifType)
      vbVerifyNotification = False
   End if

   If (oExpKey.KeyLength <> oKey.KeyLength) Then
      oLog.Failed "NotificationVerify: KeyLength does not match", 88888
      oLog.Write(tagStr &": Verify Expected "&oExpKey.KeyLength &" Got " _
                 & oKey.KeyLength)
      vbVerifyNotification = False
      bCheckData = False
   End if
    
   If (bCheckDAta = True) Then
      If (vbCompareBytes(oExpKey.KeyValue, 0, oKey.KeyValue, 0, _
          oKey.KeyLength) = False) Then
         oLog.Failed "NotificationVerify: KeyValues do not match", 88888
         vbPrintKey(oExpKey)
         vbPrintKey(oKey)
         vbVerifyNotification = False
      End if
   End if
   
   bCheckData = True
   If (oExpSParam.ParamLength <> oParam.ParamLength) Then
      oLog.Failed "NotificationVerify: ParamLength does not match", 88888
      oLog.Write(tagStr &": Verify Expected "&oExpSParam.ParamLength &" Got "_
                 & oParam.ParamLength)
      vbVerifyNotification = False
      bCheckData = False
   End if

   If (oExpSParam.ParamOffset <> oParam.ParamOffset) Then
      oLog.Failed "NotificationVerify: ParamOffset does not match", 88888
      oLog.Write(tagStr &": Verify Expected "&oExpSParam.ParamOffset &" Got " _
                 & oParam.ParamOffset)
      vbVerifyNotification = False
   End if
   
   If (oExpSParam.StructType <> oParam.StructType) Then
      oLog.Failed "NotificationVerify: StructType does not match", 88888
      oLog.Write(tagStr &": Verify Expected "&oExpSParam.StructType &" Got "& _
                 oParam.StructType)
      vbVerifyNotification = False
   End if

   If (oExpSParam.StructType <> oParam.StructType) Then
      oLog.Failed "NotificationVerify: StructType does not match", 88888
      oLog.Write(tagStr &": Verify Expected "&oExpSParam.StructType &" Got "& _
                 oParam.StructType)
      vbVerifyNotification = False
   End if
   
   If (bCheckData = True) Then
      If (vbCompareBytes(oExpSParam.ParamData, 0, oParam.ParamData, 0, _
          oParam.ParamLength) = False) Then
         oLog.Failed "NotificationVerify: ParamValues do not match", 88888
	 vbPrintSParameter(oExpSParam)
	 vbPrintSParameter(oParam)
         vbVerifyNotification = False
      End if
   End if
End Function

'==========================================================================

' Test NsiGetFirst & NsiGetNext type of GetAllParameters API calls
' Obviously needs that GetAllParameters be exported by the provider
' Takes in enumeration data and if enumeration objects are valid then 
' checks indices from successive NsiGetNext calls. Else, just does successive
' NsiGetNext calls until done. Checks are done on RW fields and ROS fields
' ROD may change between calls - and we hope nobody else is writing to RW
' fields at the same time as this test in progress
Function TestGetAllParameters(lObjIndex, oEnmKey, oEnmParam, lCount, _
                              lKeySize, lRwLen, lRodLen, lRosLen)
   Dim bVerifyEnum : bVerifyEnum = True
   Dim lStore : lStore = NSI_STORE_ACTIVE
   Dim lNsiGetType : lNsiGetType = NSI_GET_FIRST
   Dim lSize : lSize = lRwParamLen + lRodParamLen + lRosParamLen
   Dim oKey, oParam, oKeyNxt, oParamNxt
   Dim sKey, sRwData, sRodData, sRosData, lKeyIdx
   Dim sKeyNxt, sRwDataNxt, sRodDataNxt, sRosDataNxt, lKeyIdxNxt
   Dim Status, bStatus, lOff
   Dim NO_MORE_ENTRIES : NO_MORE_ENTRIES = &H8000001A&
   TestGetAllParameters = True
  
   oLog.Variation("TestGetAllParameters - ObjectID: "& lObjIndex)
   Set oKey = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibKey", lKeySize, TRUE)
   oKey.KeyLength = lKeySize
   Set oParam = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibParam", lSize, TRUE)
   oParam.RwStructLength = lRwLen
   oParam.RodStructLength = lRodLen
   oParam.RosStructLength = lRosLen 
   Set oKeyNxt = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibKey", lKeyLen, TRUE)   
   Status = oNsiApi.GetAllParameters(lObjIndex, lStore, lNsiGetType, _
                                     oKey, oParam)
   if (Status <> NDIS_STATUS_SUCCESS) then
      oLog.Failed "First Key GetAllParameters Failed. Status: " _
                  & Hex(Status) , 88888
      exit function
   end if   
   oKeyNxt.KeyLength = lKeySize
   Set oParamNxt = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibParam", lSize, TRUE)
   oParamNxt.RwStructLength = lRwLen
   oParamNxt.RodStructLength = lRodLen
   oParamNxt.RosStructLength = lRosLen
   
   If ((oEnmKey Is Nothing) Or (oEnmParam Is Nothing)) Then
      bVerifyEnum = False
   End if
 
   oLog.Variation("TestGetAllParameters: GetFirst - ObjectID: "& lObjIndex)
   ' GetAllParameters with GET_FIRST twice and verify the values of key 
   ' and parameters match. Verify if enum index is 0 & match with enum data
   oLog.Write("Calling GetAllParameters to obtain First Key")
   Status = oNsiApi.GetAllParameters(lObjIndex, lStore, lNsiGetType, _
                                     oKey, oParam)
   if (Status <> NDIS_STATUS_SUCCESS) then
      oLog.Failed "First Key GetAllParameters Failed. Status: " _
                  & Hex(Status) , 88888
      exit function
   end if   
   oLog.Write("Repeat GetAllParameters to obtain First Key")
   Status = oNsiApi.GetAllParameters(lObjIndex, lStore, lNsiGetType, _
                                     oKeyNxt, oParamNxt)
   if (Status <> NDIS_STATUS_SUCCESS) then
      oLog.Failed "Repeat First Key GetAllParameters Failed. Status: " _
                  & Hex(Status) , 88888
      exit function
   end if   
   
   ' Verify the values match
   If (vbCompareBytes(oKey.KeyValue, 0, oKeyNxt.KeyValue, 0, lKeySize) <> _
    True) Then
      oLog.Failed "Keys from successive NsiGetFirst mismatch", 88888
      TestGetAllParameters = False
   End if
   If (vbCompareBytes(oParam.StructData, 0, oParamNxt.StructData, 0, lRwLen) _
    <> True) Then
      oLog.Failed "RW Parameters from successive NsiGetFirst mismatch", 88888
      TestGetAllParameters = False
   End if
   lOff = lRwLen + lRodLen
   If (vbCompareBytes(oParam.StructData, lOff, oParamNxt.StructData, lOff, _
    lRosLen) <> True) Then
      oLog.Failed "ROS Parameters from successive NsiGetFirst mismatch", 88888
      TestGetAllParameters = False
   End if
  
   Do 
      If (bVerifyEnum = False) Then
         Exit Do
      End If
      oLog.Write("Checking NsiGetFirst with Enumeration")
      If (vbFindKeyIndex(oEnmKey, lCount, oKey.KeyValue, lKeyIdx)<>True) Then
         oLog.Failed "First Key not found in enumeration", 88888
	 TestGetAllParameters = False
	 Exit Do
      End If

      If (lKeyIdx <> 0) Then
         oLog.Failed "NsiGetFirst not the first record in enum data", 88888
         TestGetAllParameters = False
      End If
      Call vbExtractRecord(oEnmKey, oEnmParam, lCount, lKeyIdx, _
	                   sKey, sRwData, sRodData, sRosData)
      If (vbCompareBytes(oKey.KeyValue, 0, sKey, 0, lKeySize) <> True) Then
         oLog.Failed "NsiGetFirst & enum Key data mismatch" , 88888
         TestGetAllParameters = False
      End If
      If (vbCompareBytes(oParam.StructData, 0, sRwData, 0, lRwLen) <> True) _
      Then
         oLog.Failed "NsiGetFirst & enum RW data mismatch" , 88888
         TestGetAllParameters = False
      End If
      If (vbCompareBytes(oParam.StructData,lOff, sRosData,0, lRosLen) <>True) _
      Then
         oLog.Failed "NsiGetFirst & enum ROS data mismatch" , 88888
         TestGetAllParameters = False
      End If
   Loop While (0)

   ' Keep doing NsiGetNext and compare data till done
   oLog.Variation("TestGetAllParameters: GetNext - ObjectID: "& lObjIndex)
   lNsiGetType = NSI_GET_NEXT
   Dim numNext : numNext = 1
   Do
      oLog.Write("Calling GetAllParameters to obtain Next Key # "& numNext)
      Status = oNsiApi.GetAllParameters(lObjIndex, lStore, lNsiGetType, _
                                        oKey, oParam)
      If (Status = NO_MORE_ENTRIES) Then
	 If (bVerifyEnum <> True) Then
            Exit Do
	 End If
         ' Verify local Count matches enumeration count
         if (numNext <> lCount) Then
            oLog.Failed "EnumCount & Count of NsiGetNext mismatch", 88888
	    TestGetAllParameters = False
	 End if
	 Exit Do
      End If
      if (Status <> NDIS_STATUS_SUCCESS) then
         oLog.Failed "Next Key GetAllParameters Failed. Status: " _
                     & Hex(Status) , 88888
      end if
      If (bVerifyEnum = True) Then
         If (vbFindKeyIndex(oEnmKey, lCount, oKey.KeyValue, lKeyIdx) _ 
	 <> True) Then
            oLog.Failed "Key not found in enumeration", 88888
	    vbPrintKey(oKey)
	    TestGetAllParameters = False
	 Else
            If (lKeyIdx <> numNext) Then
               oLog.Failed "Unexpected Enum KeyIndex! Sorting problem?", 88888 
	    End if
	    ' Compare RW & ROS parameters
            Call vbExtractRecord(oEnmKey, oEnmParam, lCount, lKeyIdx, _
	                         sKey, sRwData, sRodData, sRosData)
            If (vbCompareBytes(oKey.KeyValue, 0, sKey, 0, lKeySize) <> True) _
	    Then
               oLog.Failed "NsiGetNext & enum Key data mismatch" , 88888
               TestGetAllParameters = False
            End If
            If (vbCompareBytes(oParam.StructData, 0, sRwData, 0, lRwLen) <> _
            True) Then
               oLog.Failed "NsiGetNext & enum RW data mismatch" , 88888
               TestGetAllParameters = False
            End If
            If (vbCompareBytes(oParam.StructData,lOff, sRosData,0, lRosLen) _
	    <>True) Then
               oLog.Failed "NsiGetNext & enum ROS data mismatch" , 88888
               TestGetAllParameters = False
            End If	    
         End If         
      End if
      numNext = numNext + 1
   Loop While (Status = NDIS_STATUS_SUCCESS)
   
End Function

'==========================================================================

' Test NsiGetFirst & NsiGetNext type of GetAllParameters API calls
' Needs either GetPArameter or GetAllParameters be exported by the provider
' Note: If only  GetAllParameters is exported then NSI emulates GetParameter
' Takes in enumeration data and if enumeration objects are valid then 
' checks indices from successive NsiGetNext calls. Else, just does successive
' NsiGetNext calls until done. Generally you would pass in RW or ROS fields
' ROD may change between calls
Function TestGetParameter(lObjIndex, oEnmKey, oEnmParam, lCount, _
                          lKeySize, lParamLen, lParamOffset, lParamType)
   Dim bVerifyEnum : bVerifyEnum = True
   Dim lStore : lStore = NSI_STORE_ACTIVE
   Dim lNsiGetType : lNsiGetType = NSI_GET_FIRST
   Dim oKey, oParam, oKeyNxt, oParamNxt, sData
   Dim sKey, sRwData, sRodData, sRosData, lKeyIdx
   Dim sKeyNxt, sRwDataNxt, sRodDataNxt, sRosDataNxt, lKeyIdxNxt
   Dim Status, bStatus 
   Dim NO_MORE_ENTRIES : NO_MORE_ENTRIES = &H8000001A&
   TestGetParameter = True
  
   oLog.Variation("TestGetParameter - ObjectID: "& lObjIndex)
   Set oKey = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibKey", lKeySize, TRUE)
   oKey.KeyLength = lKeySize
   Set oParam = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibSingleParam", lParamLen, TRUE)
   oParam.ParamLength = lParamLen
   oParam.ParamOffset = lParamOffset
   oParam.StructType = lParamType
   Set oKeyNxt = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibKey", lKeyLen, TRUE)
   oKeyNxt.KeyLength = lKeySize
   Set oParamNxt = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibSingleParam", lParamLen, TRUE)
   oParamNxt.ParamLength = lParamLen
   oParamNxt.ParamOffset = lParamOffset
   oParamNxt.StructType = lParamType
   
   If ((oEnmKey Is Nothing) Or (oEnmParam Is Nothing)) Then
      bVerifyEnum = False
   End if
 
   oLog.Variation("TestGetParameter: GetFirst - ObjectID: "& lObjIndex)
   ' GetParameter with GET_FIRST twice and verify the values of key 
   ' and parameters match. Verify if enum index is 0 & match with enum data
   oLog.Write("Calling GetParameter to obtain First Key")
   Status = oNsiApi.GetParameter(lObjIndex, lStore, lNsiGetType, oKey, oParam)
   if (Status <> NDIS_STATUS_SUCCESS) then
      oLog.Failed "First Key GetParameter Failed. Status: " _
                  & Hex(Status) , 88888
      exit function
   end if   
   oLog.Write("Repeat GetParameter to obtain First Key")
   Status = oNsiApi.GetParameter(lObjIndex, lStore, lNsiGetType, _
                                 oKeyNxt, oParamNxt)
   if (Status <> NDIS_STATUS_SUCCESS) then
      oLog.Failed "Repeat First Key GetParameter Failed. Status: " _
                  & Hex(Status) , 88888
      exit function
   end if   
   
   ' Verify the values match
   If (vbCompareBytes(oKey.KeyValue, 0, oKeyNxt.KeyValue, 0, lKeySize) <> _
   True) Then
      oLog.Failed "Keys from successive NsiGetFirst mismatch", 88888
      TestGetParameter = False
   End if
   If (vbCompareSParams(oParam, oParamNxt) <> True) Then
      oLog.Failed "Parameters from successive NsiGetFirst mismatch", 88888
      TestGetParameter = False
   End if
  
   Do 
      If (bVerifyEnum = False) Then
         Exit Do
      End If
      oLog.Write("Checking NsiGetFirst with Enumeration")
      If (vbFindKeyIndex(oEnmKey, lCount, oKey.KeyValue, lKeyIdx)<>True) Then
         oLog.Failed "First Key not found in enumeration", 88888
	 TestGetParameter = False
	 Exit Do
      End If

      If (lKeyIdx <> 0) Then
         oLog.Failed "NsiGetFirst not the first record in enum data", 88888
         TestGetParameter = False
      End If
      Call vbExtractRecord(oEnmKey, oEnmParam, lCount, lKeyIdx, _
	                   sKey, sRwData, sRodData, sRosData)
      If (vbCompareBytes(oKey.KeyValue, 0, sKey, 0, lKeySize) <> True) Then
         oLog.Failed "NsiGetFirst & enum Key data mismatch" , 88888
         TestGetParameter = False
      End If
      Select Case lParamType
         Case NSI_STRUCT_RW
            sData = sRwData
         Case NSI_STRUCT_RODYNAMIC
            sData = sRodData
         Case NSI_STRUCT_ROSTATIC
            sData = sRosData
      End Select
      If (vbCompareBytes(oParam.ParamData, 0, sData, lParamOffset, _
      lParamLen) <> True) Then
         oLog.Failed "NsiGetFirst & enum Parameter data mismatch" , 88888
         TestGetParameter = False
      End If
   Loop While (0)

   ' Keep doing NsiGetNext and compare data till done
   oLog.Variation("TestGetParameter: GetNext - ObjectID: "& lObjIndex)
   lNsiGetType = NSI_GET_NEXT
   Dim numNext : numNext = 1
   Do
      oLog.Write("Calling GetParameter to obtain Next Key # "& numNext)
      Status = oNsiApi.GetParameter(lObjIndex, lStore, lNsiGetType, _
                                        oKey, oParam)
      If (Status = NO_MORE_ENTRIES) Then
	 If (bVerifyEnum <> True) Then
            Exit Do
	 End If
         ' Verify local Count matches enumeration count
         if (numNext <> lCount) Then
            oLog.Failed "EnumCount & Count of NsiGetNext mismatch", 88888
	    oLog.Write("lCount "& lCount &" numNext " & numNext)
	    TestGetParameter = False
	 End if
	 Exit Do
      End If
      if (Status <> NDIS_STATUS_SUCCESS) then
         oLog.Failed "Next Key GetParameter Failed. Status: " _
                     & Hex(Status) , 88888
      end if
      If (bVerifyEnum = True) Then
         If (vbFindKeyIndex(oEnmKey, lCount, oKey.KeyValue, lKeyIdx) _ 
	 <> True) Then
            oLog.Failed "Key not found in enumeration", 88888
	    vbPrintKey(oKey)
	    TestGetParameter = False
	 Else
            If (lKeyIdx <> numNext) Then
               oLog.Failed "Unexpected Enum KeyIndex! Sorting problem?", 88888 
	    End if
	    ' Compare RW & ROS parameters
            Call vbExtractRecord(oEnmKey, oEnmParam, lCount, lKeyIdx, _
	                         sKey, sRwData, sRodData, sRosData)
            If (vbCompareBytes(oKey.KeyValue, 0, sKey, 0, lKeySize) <> True) _
	    Then
               oLog.Failed "NsiGetNext & enum Key data mismatch" , 88888
               TestGetParameter = False
            End If
            Select Case lParamType
               Case NSI_STRUCT_RW
                  sData = sRwData
               Case NSI_STRUCT_RODYNAMIC
                  sData = sRodData
               Case NSI_STRUCT_ROSTATIC
                  sData = sRosData
            End Select
            If (vbCompareBytes(oParam.ParamData, 0, sData, lParamOffset, _
            lParamLen) <> True) Then
               oLog.Failed "NsiGetNext & enum Parameter data mismatch" , 88888
               TestGetParameter = False
            End If
         End If         
      End if
      numNext = numNext + 1
   Loop While (Status = NDIS_STATUS_SUCCESS)
   
End Function

'==========================================================================



'<!-- CRC = 0x650d4d12 --->
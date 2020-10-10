'================================================================================================='
'/**
' This file tries out all the functionality provided by WMI
' @date     02/13/2002
' @author   Mitesh Desai
' @alias    miteshd@microsoft.com
'*/
Option Explicit

' WMIRequest command codes
Const QUERY_CLASS_INSTANCE_PROPERTIES = 1
Const SET_CLASS_INSTANCE_PROPERTIES = 2
Const QUERY_INSTANCE_PROPERTIES = 3
Const SET_INSTANCE_PROPERTIES = 4
Const QUERY_GUID_CLASS_NAME = 5
Const WMI_EVENT_LISTEN = 6
Const FILL_CLASS_PROPERTIES = 7
Const FILL_PROPERTY_QUALIFIERS = 8

' Internal request types
Const DO_QUERY = 1
Const DO_SET = 2

Class CWmi
   Dim oServices
   Dim nLastError
   Dim oLocator
   
   Private Sub Class_Initialize
      nLastError = wbemNoErr
      Set oLocator = CreateObject("WbemScripting.SWbemLocator")
      Set oServices = Nothing
   End Sub
   
   Private Sub Class_Terminate
      Set oLocator = Nothing
      Set oServices = Nothing
   End Sub

   Public Property Get LastWMIError
      LastWMIError = nLastError
   End Property
   
   Private Function GetWMIError
      If (Err <> 0) Then
         ' Now, we know we had an error, lets investigate
         nLastError = Err.Number
         oLog.Write "Error: " & Err.Description
         Err.Clear     
      End If

      GetWMIError = nLastError

   End Function

   Public Function Impersonate(ByVal ImpersonationLevel)
      oServices.Security_.ImpersonationLevel = ImpersonationLevel
   End Function

   Public Function AddPrivilege (ByVal Privilege)
      nLastError = wbemNoErr
      AddPrivilege = True

'      On Error Resume Next
      oServices.Security_.Privileges.Add Privilege
      If (GetWMIError <> 0) Then
         oLog.Write ("Unable to add privilege " & Privilege)
         AddPrivilege = False
      End If
      On Error Goto 0
   End Function

   Public Function RemovePrivilege (ByVal Privilege)
      nLastError = wbemNoErr   
      RemovePrivilege = True
      On Error Resume Next
      oServices.Security_.Privileges.Remove Privilege
      If (GetWMIError <> 0) Then
         If (nLastError = wbemErrNotFound) Then 
            oLog.Write ("Privilege " & Privilege & " does not exist")
         Else
            oLog.Write ("Unable to remove privilege " & Privilege)
         End If
         RemovePrivilege = False
      End If
      On Error Goto 0
   End Function
   
   Public Function Connect(ByVal strServer, ByVal strNameSpace)
      nLastError = wbemNoErr
      
      Connect = False
      If (IsNull (strServer)) Then
         ' Local machine
         strServer = ""
      End If

      If (IsNull (strNameSpace)) Then
         ' Default namespace for ndis stuff
         strNameSpace = "root\wmi"
      End If
      
      ' Calling SWbemLocator::ConnectServert to get SWbemServices
'      On Error Resume Next
      Set oServices = oLocator.ConnectServer (strServer, strNameSpace)
      If (GetWMIError <> 0) Then
         Call oLog.Write ("Unable to connect to " & strServer & ", namespace " & strNameSpace)
         Exit Function
      End If
      On Error Goto 0

      Connect = True
   End Function

   Private Function GetObjectClassName(strCompleteString)
      Dim arrNameSubparts

      GetObjectClassName = "Unknown"
      ' The name is of the form object:ClassName. Lets split the classname out
      arrNameSubparts = Split (strCompleteString, ":")
      If (UBound(arrNameSubparts) <> 1) Then
         oLog.Write ("Embedded object name not in the format expected")
         Exit Function
      End If

      GetObjectClassName = arrNameSubparts(1)
   End Function

   Public Function WMIRequest(ByRef oWMIRequest)
      WMIRequest = True
      Select Case (oWMIRequest.RequestType) 
         Case QUERY_CLASS_INSTANCE_PROPERTIES:
            WMIRequest = QuerySetClassInstanceProperties (oWMIRequest, DO_QUERY)
         Case QUERY_INSTANCE_PROPERTIES:
            WMIRequest = QuerySetInstanceProperties (oWMIRequest, DO_QUERY)
         Case QUERY_GUID_CLASS_NAME:
            WMIRequest = QueryGuidClassName(oWMIRequest)
         Case SET_CLASS_INSTANCE_PROPERTIES:
            WMIRequest = QuerySetClassInstanceProperties (oWMIRequest, DO_SET)
         Case SET_INSTANCE_PROPERTIES:
            WMIRequest = QuerySetInstanceProperties (oWMIRequest, DO_SET)
         Case WMI_EVENT_LISTEN:
            nLastError = wbemErrInvalidParameter
            oLog.Write ("Use StartWaitForWMIEvent and StopWaitForWMIEvent directly")
            WMIRequest = False
         Case FILL_CLASS_PROPERTIES:
            WMIRequest = ObtainClassProperties(oWMIRequest)
         Case FILL_PROPERTY_QUALIFIERS:
            WMIRequest = ObtainPropertyQualifiers(oWMIRequest)            
         Case Else:
            oLog.Write ("Unknown request passed to WMIRequest")
            WMIRequest = False
      End Select      
   End Function

   ' Events
   Public Function StartWaitForWMIEvent (ByRef oWMIRequest)
      Dim oEventSrc, strEventName
      
      nLastError = wbemNoErr
      StartWaitForWMIEvent = False

      strEventName = oWMIRequest.ClassName
      Set oWMIRequest.EventHandle = Nothing
      
'     On Error Resume Next
      Set oEventSrc = oServices.ExecNotificationQuery("Select * From " & strEventName)
      If (GetWMIError <> 0) Then
         Exit Function
      End If
      On Error Goto 0

      Set oWMIRequest.EventHandle = oEventSrc      
      StartWaitForWMIEvent = True
   End Function

   Public Function StopWaitForWMIEvent (ByRef oWMIRequest, ByVal WaitTimeout)
      Dim oEventObj, nCount, nEventCnt
      Dim oEventSrc, strInstance
      Dim oPropertiesSet, oProperty
      Dim nUseThisEvent, bFoundEvent
 
      Const MAX_EVENTS_TO_EXPECT = 5
      
      nLastError = wbemNoErr
      StopWaitForWMIEvent = False

      Set oEventSrc = oWMIRequest.EventHandle

      If (oEventSrc is Nothing) Then
         Exit Function
      End If
      
      bFoundEvent = False
      For nEventCnt = 1 To MAX_EVENTS_TO_EXPECT
         ' This On Error is required to ensure that we do not popup because of timeout
         On Error Resume Next
         Set oEventObj = oEventSrc.NextEvent(WaitTimeout)
         If (GetWMIError <> 0) Then
            Exit Function
         End If
         On Error Goto 0

         ' So we had an event, lets see if the properties of the event match the ones we
         ' have are looking for
'         On Error Resume Next
         Set oPropertiesSet = oEventObj.Properties_
         If (GetWMIError <> 0) Then
            Call oLog.Write ("Unable to obtain properties of indicated event")
            Exit Function
         End If
         On Error Goto 0

         nUseThisEvent = 0
         For Each oProperty in oPropertiesSet            
            ' Check if this is the instance we want to use
            For nCount = 0 To oWMIRequest.InSize-1
               If (StrComp(oProperty.Name, oWMIRequest.InObject(nCount).PropertyName, 1) = 0) Then
                  If (oProperty.Value = oWMIRequest.InObject(nCount).Data) Then
                     ' We may use this event
                     nUseThisEvent = nUseThisEvent+1
                  End If
               End If
            Next
         Next

         If (nUseThisEvent = oWMIRequest.InSize) Then
            ' We have found the event we are concerned with
            bFoundEvent = True
            Exit For
         End If
      Next

      If (bFoundEvent) Then
         If (oWMIRequest.InSize = 0) Then
            ' There were no in buffers, add one
            Dim NewInWMIBuffer

            Set NewInWMIBuffer = New CWMIBuffer
            oWMIRequest.PushInBuffer(NewInWMIBuffer)
         End If
         
         ' We did get the event, fill the required information into the out buffers
         oWMIRequest.RequestType = QUERY_INSTANCE_PROPERTIES

         ' Overwrite the first in buffer with the event obj we received
         Set oWMIRequest.InObject(0).Data = oEventObj
         
         StopWaitForWMIEvent = QuerySetInstanceProperties(oWMIRequest, DO_QUERY)
      Else
         ' Since nEventCnt has already been incremented
         oLog.Write ("Received " & nEventCnt-1 & " events")
         If (nEventCnt > MAX_EVENTS_TO_EXPECT) Then
            oLog.Write ("We received too many events (but none for the device under consideration).")
            oLog.Write ("Please run the test again in a more controlled environment")
         End If
      End If
      
   End Function

   Private Function FillArrayDataQuery (oWMIArray, oOrigWMIRequest, nOutPosition, oArrBuffer)
      Dim oArrayData, ArraySize, nActArraySize
      Dim bFoundSize
      Dim nCount, oWMIBuffer

      FillArrayDataQuery = False
      oArrayData = oWMIArray.OriginalArray
      ArraySize = oArrBuffer.SizeInformation

      bFoundSize = False
      If (VarType(ArraySize) = vbString) Then
         ' We do not already have the array size. We just have the
         ' name of the property that holds the array size. Loop through
         ' the properties and get the array size
         For nCount = 0 To oOrigWMIRequest.OutSize-1
            Set oWMIBuffer = oOrigWMIRequest.OutObject(nCount)
            If (StrComp(oWMIBuffer.PropertyName, ArraySize, 1) = 0) Then
               ' We can have an additional check about the type of data being integer,
               ' but we wont worry about that
               nActArraySize = oWMIBuffer.Data
                
               bFoundSize = True
               Exit For
            End If
         Next
      Else
         nActArraySize = ArraySize
         bFoundSize = True
      End If

      If (Not bFoundSize) Then
         oLog.Write ("Unable to obtain the size of the array")
         Exit Function
      End If

      If (oArrBuffer.DataType = wbemCimtypeObject) Then
         Dim oWMIEObject
   
         ' Each element is a WMIBuffer, whose data section is an EmbeddedObject
         For nCount = 0 To nActArraySize - 1
            FillArrayDataQuery = False

            Set oWMIBuffer = New CWMIBuffer            
            Set oWMIEObject = New CWMIEmbeddedObject

            oWMIBuffer.PropertyName = oArrBuffer.PropertyName
            oWMIBuffer.DataType = wbemCimtypeObject
            oWMIBuffer.ArrayType = False
            oWMIBuffer.EmbeddedObject = oArrBuffer.EmbeddedObject
            Set oWMIEObject.OriginalObject = oArrayData(nCount)

            If (FillObjectDataQuery(oWMIEObject, oOrigWMIRequest, nCount, oArrBuffer)) Then
               FillArrayDataQuery = True
               Set oWMIBuffer.Data = oWMIEObject
               oWMIArray.PushElement(oWMIBuffer)
            Else
               ' If we did not find a printable type inside the elements, we quit
               oLog.Write ("Unable to process object data inside array")
               Exit For
            End If
            
            Set oWMIEObject = Nothing
            Set oWMIBuffer = Nothing
         Next
      ElseIf (oArrBuffer.DataType <> wbemCimtypeReference) Then

         For nCount = 0 To nActArraySize - 1
            Set oWMIBuffer = New CWMIBuffer
            oWMIBuffer.PropertyName = oArrBuffer.PropertyName & " (" & nCount & ")"
            oWMIBuffer.DataType = oArrBuffer.DataType
            oWMIBuffer.ArrayType = False

            oWMIBuffer.Data = oArrayData(nCount)

            oWMIArray.PushElement(oWMIBuffer)
            Set oWMIBuffer = Nothing            
         Next

         FillArrayDataQuery = True
      End If

      

   End Function
   
   Private Function FillObjectDataQuery (oWMIEmbObject, oOrigWMIRequest, nOutPosition, oObjBuffer)
      Dim arrNameSubparts, strClassName
      Dim oWMIRequest, oWMIBuffer

      FillObjectDataQuery = False

      strClassName = oObjBuffer.EmbeddedObject
      ' Create a new request to obtain the property names
      Set oWMIRequest = New CWMIRequest
      oWMIRequest.ClassName = strClassName
      oWMIRequest.RequestType = FILL_CLASS_PROPERTIES
      
      If (ObtainClassProperties(oWMIRequest)) Then

         ' Now query for the data in the properties
         oWMIRequest.RequestType = QUERY_INSTANCE_PROPERTIES

         oWMIRequest.InSize = 0
         
         ' Input side we pass the object instance
         Set oWMIBuffer = New CWMIBuffer
         oWMIBuffer.PropertyName = strClassName
         
         Set oWMIBuffer.Data = oWMIEmbObject.OriginalObject
         oWMIBuffer.DataType = wbemCimtypeObject
         oWMIRequest.PushInBuffer (oWMIBuffer)
         
         If (QuerySetInstanceProperties(oWMIRequest, DO_QUERY)) Then
            ' We might be causing recursion here
            Dim nCount

            For nCount = 0 To oWMIRequest.OutSize-1
               Set oWMIBuffer = oWMIRequest.OutObject(nCount)

'               If (oWMIBuffer.ArrayType) Then
'                  'Its an array, replace the data field with CWMIArray
'                  Dim oWMIArray
'
'                  Set oWMIArray = New CWMIArray
'                  
'                  oWMIArray.OriginalArray = oWMIBuffer.Data
'                  If (FillArrayDataQuery(oWMIArray, oWMIRequest, nCount, oWMIBuffer)) Then
'                     ' Store the array inside our buffer itself
'                     Set oWMIBuffer.Data = oWMIArray
'
'                     ' And push the buffer in
'                     oWMIEmbObject.PushBuffer(oWMIBuffer)
'                  End If
'                  
'               ElseIf (oWMIBuffer.DataType = wbemCimtypeObject Or oWMIBuffer.DataType = wbemCimtypeReference) Then               
'                  ' If its not an array, we do not wish to work with objects inside objects
'                  oLog.Write ("WMI data structure nested with too may complex data types. Ignoring")
'                  ' Still we will push the object in
'                  oWMIEmbObject.PushBuffer(oWMIBuffer)                  
'               Else
'                  ' Just push the buffer into the original data
'                  oWMIEmbObject.PushBuffer(oWMIBuffer)
'               End If
               oWMIEmbObject.PushBuffer(oWMIBuffer)
               FillObjectDataQuery = True

            Next
         End If

      End If
      Set oWMIRequest = Nothing
   End Function


   ' The the WMIRequest object and expand all the data in there
   Private Function ProcessWMIRequestQuery(oWMIRequest)
      Dim nCount
      Dim oCurrWMIBuffer

      ProcessWMIRequestQuery = False
      For nCount = 0 To oWMIRequest.OutSize-1
         ' For each property, check if its an array or an object
         Set oCurrWMIBuffer = oWMIRequest.OutObject(nCount)

         If (oCurrWMIBuffer.ArrayType) Then
            'Its an array, replace the data field with CWMIArray
            Dim oWMIArray

            Set oWMIArray = New CWMIArray           
            oWMIArray.OriginalArray = oCurrWMIBuffer.Data
            If (FillArrayDataQuery(oWMIArray, oWMIRequest, nCount, oCurrWMIBuffer)) Then
               Set oCurrWMIBuffer.Data = oWMIArray
            End If
         ElseIf (oCurrWMIBuffer.DataType = wbemCimtypeObject) Then
            'Its an object, replace the data field with CWMIEmbeddedObject type
            Dim oWMIObject

            Set oWMIObject = New CWMIEmbeddedObject
            
            Set oWMIObject.OriginalObject = oCurrWMIBuffer.Data
            If (FillObjectDataQuery(oWMIObject, oWMIRequest, nCount, oCurrWMIBuffer)) Then
               Set oCurrWMIBuffer.Data = oWMIObject
            End If
            
         End If

         Set oCurrWMIBuffer = Nothing
      Next

      ProcessWMIRequestQuery = True
   End Function

   Private Function FillArrayDataSet (oSetArray, oOrigWMIRequest, nOutPosition, oArrBuffer)
      Dim oWMIArray
      Dim oArrayData, ArraySize
      Dim nCount, oWMIBuffer

      FillArrayDataSet = False

      ' Get the array object we are going to set from
      Set oWMIArray = oArrBuffer.Data

      ' Get the size of the array we are going to set
      ArraySize = oWMIArray.Size
      If (ArraySize < 0) Then
         oLog.Write ("Attempting to set an array of size < 0")
         nLastError = wbemErrInvalidParameter
         Exit Function
      End If

      ' Prepare the array that we are going to pass to WMI
      ReDim oSetArray(ArraySize-1)

      ' oArrayData stores the input array that we want to set
      oArrayData = oWMIArray.ArrElement      
      
      If (oArrBuffer.DataType = wbemCimtypeObject) Then
         Dim oSetObject
         
         ' Each element is a WMIBuffer, whose data section is an EmbeddedObject
         For nCount = 0 To ArraySize - 1
            FillArrayDataSet = False

            Set oWMIBuffer = oArrayData(nCount)

            If (FillObjectDataSet(oSetObject, oOrigWMIRequest, nCount, oWMIBuffer)) Then
               ' Okay, so a set object was created, lets store that in our array
               Set oSetArray(nCount) = oSetObject
               FillArrayDataSet = True
            Else
               ' If we did not find a printable type inside the elements, we quit
               oLog.Write ("Unable to process object data inside array")
               Exit For
            End If

            Set oWMIBuffer = Nothing
         Next
      ElseIf (oArrBuffer.DataType <> wbemCimtypeReference) Then
         For nCount = 0 To ArraySize - 1
            oSetArray(nCount) = oArrayData(nCount).Data
         Next

         FillArrayDataSet = True
      End If

   End Function
   
   Private Function FillObjectDataSet (oSetObject, oOrigWMIRequest, nOutPosition, oObjBuffer)
      Dim oSetClass, strClassName
      Dim oWMIRequest, oWMIBuffer, oEmbeddedObj
      Dim oPropertySet, oProperty
      Dim nCount

      FillObjectDataSet = False

      strClassName = oObjBuffer.EmbeddedObject
      Set oEmbeddedObj = oObjBuffer.Data

'      On Error Resume Next
      Set oSetClass = oServices.Get(strClassName)
      If (GetWMIError <> 0) Then
         Call oLog.Write ("Unable to open classes " & strClassName)
         Exit Function
      End If

      Set oSetObject = oSetClass.SpawnInstance_
      If (GetWMIError <> 0) Then
         Call oLog.Write ("Unable to create new instance of class " & strClassName)
         Exit Function
      End If

      Set oPropertySet = oSetObject.Properties_
      If (GetWMIError <> 0) Then
         Call oLog.Write ("Unable to obtain properties of new instance of " & strClassName)
         Exit Function
      End If
      On Error Goto 0

      ' Create a new request to obtain the property names
      Set oWMIRequest = New CWMIRequest
      oWMIRequest.ClassName = strClassName
      oWMIRequest.RequestType = SET_INSTANCE_PROPERTIES

      ' Input side we pass the object instance we just created
      Set oWMIBuffer = New CWMIBuffer
      oWMIBuffer.PropertyName = strClassName
      
      Set oWMIBuffer.Data = oSetObject
      oWMIBuffer.DataType = wbemCimtypeObject
      oWMIRequest.PushInBuffer (oWMIBuffer)

      ' Copy the data we want to set into our WMIRequest
      For nCount = 0 To oEmbeddedObj.Size-1
         Set oWMIBuffer = oEmbeddedObj.ArrProperty(nCount)

         oWMIRequest.PushOutBuffer(oWMIBuffer)
      Next
      
      ' Lets try and set the values for this instance
      If (QuerySetInstanceProperties(oWMIRequest, DO_SET)) Then
         FillObjectDataSet = True
      End If

      Set oWMIRequest = Nothing
   End Function



   ' Here is where comes the tough part for set, need to do a lot of work to structure the
   ' found instance according to the WMIRequest data
   Private Function ProcessWMIRequestSet(oWMIRequest, oInstance)
      Dim nCount, bAddedProperty
      Dim oCurrWMIBuffer
      Dim oPropertySet, oProperty
      
      ProcessWMIRequestSet = False
      Set oPropertySet = oInstance.Properties_

      ' Go through each of the properties that the object has
      For nCount = 0 To oWMIRequest.OutSize-1
         bAddedProperty = False        ' If we are trying to add a new property

         Set oCurrWMIBuffer = oWMIRequest.OutObject(nCount)

         For Each oProperty in oPropertySet
            If (oCurrWMIBuffer.PropertyName = oProperty.Name) Then
               bAddedProperty = True            ' We found the property (not caring if we could modify)
               
               If (oCurrWMIBuffer.ArrayType) Then
                  ' Its an array, create the data from the 
                  Dim oSetArray()
                  ' This function would create the array we want
                  If (FillArrayDataSet(oSetArray, oWMIRequest, nCount, oCurrWMIBuffer)) Then
'                     On Error Resume Next
                     oProperty.Value = oSetArray
                     If (GetWMIError <> 0) Then
                        Call oLog.Write ("Unable to set array property data")
                        Exit Function
                     End If
                     On Error Goto 0
                     
                  End If
                  
               ElseIf (oCurrWMIBuffer.DataType = wbemCimtypeObject) Then
                  'Its an object, replace the data field with CWMIEmbeddedObject type
                  Dim oSetObject

                  ' This function would create the object we want to set
                  If (FillObjectDataSet(oSetObject, oWMIRequest, nCount, oCurrWMIBuffer)) Then
'                     On Error Resume Next
                     oProperty.Value = oSetObject
                     If (GetWMIError <> 0) Then
                        Call oLog.Write ("Unable to set object property data")
                        Exit Function
                     End If
                     On Error Goto 0
                     
                  End If
                  Set oSetObject = Nothing
               ElseIf (oCurrWMIBuffer.DataType <> wbemCimtypeReference) Then
                  If (oCurrWMIBuffer.DataType = oProperty.CIMType) Then
'                     On Error Resume Next
                     oProperty.Value = oCurrWMIBuffer.Data
                     If (GetWMIError <> 0) Then
                        Call oLog.Write ("Unable to set property data")
                        Exit Function
                     End If
                     On Error Goto 0
                  Else
                     ' WMI is going to give an error, why bother
                     oLog.Write ("Set parameter type mismatch")
                     nLastError = wbemErrTypeMismatch
                  End If
               End If
            End If
         Next

         If (bAddedProperty = False) Then
            ' If we did not find the property in our in buffers, we can have
            ' code here to add the property to the instance. 

            ' Currently we just log it
            oLog.Write ("Have not added property " & oCurrWMIBuffer.PropertyName & " to instance")
         End If
         Set oCurrWMIBuffer = Nothing

      Next
      ProcessWMIRequestSet = True
      
   End Function

   Private Function QuerySetClassInstanceProperties(ByRef oWMIRequest, ByVal RequestType)
      Dim strOidClassName, bResult

      '
      ' Check that we have a service instance
      ' 
      nLastError = wbemNoErr      
      QuerySetClassInstanceProperties = False
      If (oServices is Nothing) Then
         nLastError = wbemErrUnexpected
         Exit Function
      End If

      Dim oOidInstancesSet, oOidInstance
      strOidClassName = oWMIRequest.ClassName

      ' This On Error is needed to catch popups in case there are no instances of the class
      On Error Resume Next
      
      ' Go and find the instances of this particular class. (Do not return until done)
      Set oOidInstancesSet = oServices.InstancesOf(strOidClassName, wbemFlagReturnWhenComplete)      
      If (GetWMIError <> 0) Then
      
         If (nLastError = wbemErrNotSupported) Then
            oLog.Write ("Query for instances of class " & strOidClassName & " returned not supported.")
            oLog.Write ("Assuming that there are no instances of this class and clearing the error code.")
            nLastError = wbemNoErr
         Else
            Call oLog.Write ("Unable to open instances of class " & strOidClassName)
         End If

         Exit Function
      End If
      On Error Goto 0

      bResult = True
      ' We have the instances of this class. (else we would have failed and quit above)
      Dim nCount
      Dim oPropertiesSet, oProperty
      Dim nFoundValues, nUseThisInstance, bContinueLoop
      ' Now, we should have the list of instances of the property
      For Each oOidInstance in oOidInstancesSet
         ' Get the properties of the instance
'         On Error Resume Next
         Set oPropertiesSet = oOidInstance.Properties_
         If (GetWMIError <> 0) Then
            Call oLog.Write ("Unable to obtain properties of instance of class " & strOidClassName)
            Exit Function
         End If
         On Error Goto 0
         
         nUseThisInstance = 0
         nFoundValues = 0
         bContinueLoop = True
         For Each oProperty in oPropertiesSet
            
            ' Check if this is the instance we want to use
            For nCount = 0 To oWMIRequest.InSize-1
               If (StrComp(oProperty.Name, oWMIRequest.InObject(nCount).PropertyName, 1) = 0) Then
                  If (oProperty.Value = oWMIRequest.InObject(nCount).Data) Then
                     ' We have to use this instance
                     nUseThisInstance = nUseThisInstance+1
                  Else
                     ' If the name matches and the value does not match, just continue with
                     ' next instance
                     bContinueLoop = False                  
                  End If
                  Exit For
               End If
            Next
            
            If (Not bContinueLoop) Then
               ' Above we got a name match for the instance, but value did not match, this 
               ' cannot be the instance we are concerned with, do not even try to copy values
               Exit For
            End If

            ' Copy properties data
            For nCount = 0 To oWMIRequest.OutSize-1
               If (StrComp(oProperty.Name, oWMIRequest.OutObject(nCount).PropertyName, 1) = 0) Then
                  If (RequestType = DO_QUERY) Then
                     bResult = CopyDataToBuffer (oWMIRequest.OutObject(nCount), oWMIRequest.ClassName, oProperty)
                  Else
                     ' We will not be writing the data through WMI until later, so we do not 
                     ' care that we are modifying incorrect instance
                     bResult = CopyDataFromBuffer (oWMIRequest.OutObject(nCount), oWMIRequest.ClassName, oProperty)
                  End If
                  nFoundValues = nFoundValues+1
                  Exit For
               End If
            Next

            ' If any previous copy was not successful, we will not try continue
            If (Not bResult) Then
               Exit For
            End If
            
            ' Check if we have the right instance and have obtained the properties
            If (nUseThisInstance = oWMIRequest.InSize And nFoundValues = oWMIRequest.OutSize) Then
               Exit For
            End If
         Next

         ' If any previous copy was not successful, we will not try continue
         If (Not bResult) Then
            Exit For
         End If

         ' If we already found the instance name, then we should have found the property
         ' if not, then something has gone wrong
         If (nUseThisInstance = oWMIRequest.InSize) Then
            Exit For
         End If
         
      Next

      If (nUseThisInstance = oWMIRequest.InSize And nFoundValues = oWMIRequest.OutSize And bResult) Then
         If (RequestType = DO_SET) Then
            ' Process/copy the data to set all the required objects and so on so forth
            bResult = ProcessWMIRequestSet(oWMIRequest, oOidInstance)

            If (bResult) Then

               ' Lets try to commit the written data into WMI
               On Error Resume Next            
               bResult = oOidInstance.Put_
               If (GetWMIError <> 0) Then
                  Call oLog.Write ("Unable to write modified data for an instance of class " & strOidClassName)
                  Exit Function
               End If
               On Error Goto 0
            End If
         Else
            ' Process the data to fill all the object and array data
            bResult = ProcessWMIRequestQuery(oWMIRequest)
         End If            

         QuerySetClassInstanceProperties = bResult
      Else
         oLog.Write ("Unable to find matching instance or all its expected properties in class " & strOidClassName)
         nLastError = wbemErrInvalidParameter
      End If

      
   End Function

   Private Function QuerySetInstanceProperties (ByRef oWMIRequest, ByVal RequestType)
      nLastError = wbemNoErr      
      QuerySetInstanceProperties = False
      If (oServices is Nothing) Then
         nLastError = wbemErrUnexpected
         Exit Function
      End If

      Dim nCount, bResult
      Dim oOidInstance
      
      Dim oPropertiesSet, oProperty
      Dim nFoundValues, strOidClassName

      strOidClassName = oWMIRequest.InObject(0).PropertyName

      ' Obtain the instace we want to query/set the properties. It is stored inside the WMIRequest
      ' structure in the first in object
      Set oOidInstance = oWMIRequest.InObject(0).Data
      
'     On Error Resume Next
      Set oPropertiesSet = oOidInstance.Properties_
      If (GetWMIError <> 0) Then
         Call oLog.Write ("Unable to obtain properties of instance of class " & strOidClassName)
         Exit Function
      End If
      On Error Goto 0
      
      nFoundValues = 0
      bResult = True
      For Each oProperty in oPropertiesSet

         ' Copy properties data
         For nCount = 0 To oWMIRequest.OutSize-1
            If (StrComp(oProperty.Name,oWMIRequest.OutObject(nCount).PropertyName, 1) = 0) Then
               If (RequestType = DO_QUERY) Then
                  bResult = CopyDataToBuffer (oWMIRequest.OutObject(nCount), oWMIRequest.ClassName, oProperty)
               Else
                  bResult = CopyDataFromBuffer (oWMIRequest.OutObject(nCount), oWMIRequest.ClassName, oProperty)
               End If
               nFoundValues = nFoundValues+1
               Exit For
            End If
         Next

         ' If the copies failed anytime
         If (Not bResult) Then
            Exit For
         End If
         
         ' Check if we have obtained the properties
         If (nFoundValues = oWMIRequest.OutSize) Then
            Exit For
         End If
      Next
      
      If (nFoundValues = oWMIRequest.OutSize And bResult) Then
         If (RequestType = DO_SET) Then
            ' Process the data to set all the required objects and so on so forth
            bResult = ProcessWMIRequestSet(oWMIRequest, oOidInstance)
            If (bResult) Then
               ' We will not commit the object here, we will let the caller commit it, 
               ' as he is the one who has created the instance in the first place
'               On Error Resume Next            
               If (GetWMIError <> 0) Then
                  Call oLog.Write ("Unable to write modified data for an instance of class " & strOidClassName)
                  Exit Function
               End If
               On Error Goto 0
            End If
         Else
            ' Process the data to fill all the object and array data
            bResult = ProcessWMIRequestQuery(oWMIRequest)            
         End If      
         QuerySetInstanceProperties = True
      Else
         oLog.Write ("Unable to find matching instance or all its expected properties in class " & strOidClassName)
         nLastError = wbemErrInvalidParameter
      End If
            
   End Function


   Private Function QueryGuidClassName(ByRef oWMIRequest)
      Dim oClass, oRootSubClasses
      Dim oQualifier, oQualifierSet
      Dim strGuid
      Dim nCount, bFound

      nLastError = wbemNoErr
      QueryGuidClassName = False
      
'      On Error Resume Next
      Set oRootSubClasses = oServices.SubClassesOf("", wbemQueryFlagShallow+wbemFlagReturnWhenComplete)
      If (GetWMIError <> 0) Then
         Call oLog.Write ("Unable to obtain subclasses of root wmi object")
         Exit Function
      End If
      On Error Goto 0

      strGuid = oWMIRequest.ClassName
      bFound = False
      For Each oClass in oRootSubClasses

'        On Error Resume Next
         Set oQualifierSet = oClass.Qualifiers_
         If (GetWMIError <> 0) Then
            Call oLog.Write ("Unable to obtain qualifiers of class " & oClass.Path_.Class)
            Exit Function
         End If
         On Error Goto 0

         For Each oQualifier in oQualifierSet
            If (StrComp(oQualifier.Name, "guid", 1) = 0) Then
              ' As there is no shortcircuiting of Ands, need second if
               If (StrComp(oQualifier.Value,strGuid, 1) = 0) Then
                  ' This means that we are at the class that corresponds to the guid. 

                  ' Now, we will fix the WMIRequest structure that was passed in to us
                  ' and send the request onto the QuerySetClassInstanceProperties function

                  bFound = True

                  ' Fill the name of the class into the request
                  oWMIRequest.ClassName = oClass.Path_.Class
                  QueryGuidClassName = True
                  Exit For
               End If
            End If
         Next

         If (bFound) Then
            Exit For
         End If
      Next
      If (Not bFound) Then
         oLog.Write ("Unable to find a class that matches the guid " & strGuid)
         nLastError = wbemErrInvalidParameter
      End If
   End Function

   Private Function ObtainClassProperties (oWMIRequest)
      ' Will take a class name and fill the properties of the class into the 
      ' out sections
      Dim oClassObj, NewWMIOutBuffer

      nLastError = wbemNoErr
      ObtainClassProperties = False
      ' Obtain a handle to the class

      Set oClassObj = oServices.Get(oWMIRequest.ClassName)

      Dim oProperty, oPropertiesSet
      
'     On Error Resume Next
      Set oPropertiesSet = oClassObj.Properties_
      If (GetWMIError <> 0) Then
         Call oLog.Write ("Unable to obtain properties of class " & oWMIRequest.ClassName)
         Exit Function
      End If
      On Error Goto 0

      ' Clear the whole of the out buffer list
      oWMIRequest.OutSize = 0
      For Each oProperty in oPropertiesSet
         Set NewWMIOutBuffer = New CWMIBuffer

         NewWMIOutBuffer.PropertyName = oProperty.Name

         NewWMIOutBuffer.ArrayType = oProperty.IsArray
         If (oProperty.IsArray) Then
            Dim LengthField
                 
            ' Get the length (or key that would give length) of array. This might be 
            ' a waste if we are going to end up querying for the data. But we will still do it
            NewWMIOutBuffer.SizeInformation = GetLengthOfArrayType(oWMIRequest.ClassName, oProperty.Name)
         End If

         NewWMIOutBuffer.DataType = oProperty.CIMType
         If (oProperty.CIMType = wbemCimtypeObject) Then
            Dim strEmbeddedObjName

            strEmbeddedObjName = GetPropertyQualifierValue (oProperty, "CIMType")
            If (Not IsNull (strEmbeddedObjName)) Then
               ' We will use the extrainfo section to pass the embedded object name back
               NewWMIOutBuffer.EmbeddedObject = GetObjectClassName(strEmbeddedObjName)
            Else
               NewWMIOutBuffer.EmbeddedObject = "Unknown"
            End If
         End If
         
         oWMIRequest.PushOutBuffer (NewWMIOutBuffer)
      Next      

      ObtainClassProperties = True

   End Function

   
   Private Function ObtainPropertyQualifiers (oWMIRequest)
      ' Will take a class name and property names and fill the qualifiers of the properties 
      ' into the out sections
      Dim oClassObj, oWMIBuffer, nCount

      nLastError = wbemNoErr
      ObtainPropertyQualifiers = False
      ' Obtain a handle to the class
      Set oClassObj = oServices.Get(oWMIRequest.ClassName)

      Dim oProperty, oPropertiesSet
      
'     On Error Resume Next
      Set oPropertiesSet = oClassObj.Properties_
      If (GetWMIError <> 0) Then
         Call oLog.Write ("Unable to obtain properties of class " & oWMIRequest.ClassName)
         Exit Function
      End If
      On Error Goto 0

      For Each oProperty in oPropertiesSet

         For nCount = 0 To oWMIRequest.OutSize-1
            Set oWMIBuffer = oWMIRequest.OutObject(nCount)
         
            If (StrComp(oWMIBuffer.PropertyName, oProperty.Name, 1) = 0) Then
               oWMIBuffer.ArrayType = oProperty.IsArray
               If (oProperty.IsArray) Then
                  Dim LengthField
                       
                  ' Get the length (or key that would give length) of array. This might be 
                  ' a waste if we are going to end up querying for the data. But we will still do it
                  oWMIBuffer.SizeInformation = GetLengthOfArrayType(oWMIRequest.ClassName, oProperty.Name)
               End If

               oWMIBuffer.DataType = oProperty.CIMType
               If (oProperty.CIMType = wbemCimtypeObject) Then
                  Dim strEmbeddedObjName

                  strEmbeddedObjName = GetPropertyQualifierValue (oProperty, "CIMType")
                  If (Not IsNull (strEmbeddedObjName)) Then
                     ' We will use the extrainfo section to pass the embedded object name back
                     oLog.Write "Setting: " & GetObjectClassName(strEmbeddedObjName)
                     oWMIBuffer.EmbeddedObject = GetObjectClassName(strEmbeddedObjName)
                  Else
                     oWMIBuffer.EmbeddedObject = "Unknown"
                  End If
               End If               
            End If
         Next
      Next      

      ObtainPropertyQualifiers = True

   End Function

   ' Copy data from the property into the buffer that we have
   Private Function CopyDataToBuffer (oWMIBuffer, ByVal strClassName, ByVal oDataProperty)
      Dim PropertyCIMType, PropertyIsArray

      CopyDataToBuffer = False
'      Set oWMIBuffer = oWMIRequest.OutObject(OutIndex)
      oWMIBuffer.DataType = 0
      oWMIBuffer.ArrayType = False

      PropertyIsArray = oDataProperty.IsArray
      PropertyCIMType = oDataProperty.CIMType

      If (PropertyIsArray) Then
         Dim LengthField
         ' Get the name of the class
         oWMIBuffer.ArrayType =  True
         
         ' Get the length (or key that would give length) of array
         oWMIBuffer.SizeInformation = GetLengthOfArrayType(strClassName, oDataProperty.Name)
      End If

      oWMIBuffer.DataType = PropertyCIMType

      If (PropertyCIMType = wbemCimtypeObject) Then
         Dim strEmbeddedObjName

         strEmbeddedObjName = GetPropertyQualifierValue (oDataProperty, "CIMType")
         If (Not IsNull (strEmbeddedObjName)) Then
            ' We will use the extrainfo section to pass the embedded object name back
            oLog.Write "Setting: " & GetObjectClassName(strEmbeddedObjName)            
            oWMIBuffer.EmbeddedObject = GetObjectClassName(strEmbeddedObjName)
         Else
            oWMIBuffer.EmbeddedObject = "Unknown"
         End If

         If (Not PropertyIsArray) Then
            ' Not an array
            Set oWMIBuffer.Data = oDataProperty.Value
         Else
            oWMIBuffer.Data = oDataProperty.Value
         End If
      Else
         oWMIBuffer.Data = oDataProperty.Value
      End If
      
      CopyDataToBuffer = True      
   End Function

   ' Cannot do much in this function because of the limitations of the who process
   Private Function CopyDataFromBuffer (oWMIBuffer, ByVal strClassName, oOrigProperty)
      Dim PropertyCIMType, PropertyIsArray
      Dim nCount

      CopyDataFromBuffer = False

      PropertyIsArray = oOrigProperty.IsArray
      PropertyCIMType = oOrigProperty.CIMType

      If ((oWMIBuffer.ArrayType <> PropertyIsArray) Or _
          (oWMIBuffer.DataType <> PropertyCIMType)) Then
         ' WMI is going to kick back to us, why bother processing and sending down
         oLog.Write ("Set parameter type mismatch")
         nLastError = wbemErrTypeMismatch
         Exit Function
      End If

      CopyDataFromBuffer = True
   End Function


   Private Function GetLengthOfArrayType (ByVal strClassName, ByVal strPropertyName)
      ' We need to extract the WmiSizeIs field from the class
      Dim oClassObj

      ' Obtain a handle to the class
      Set oClassObj = oServices.Get(strClassName)

      Dim oProperty, oPropertiesSet
      GetLengthOfArrayType = Null
      
'      On Error Resume Next
      Set oPropertiesSet = oClassObj.Properties_
      If (GetWMIError <> 0) Then
         Call oLog.Write ("Unable to obtain properties of class " & strClassName)
         Exit Function
      End If
      On Error Goto 0

      For Each oProperty in oPropertiesSet

         If (oProperty.Name = strPropertyName) Then
            ' If its a variable size array, we should have a WMISizeIs field
            GetLengthOfArrayType = GetPropertyQualifierValue(oProperty, "WMISizeIs")
            If (IsNull(GetLengthOfArrayType)) Then
               ' If it is a fixed size array, get the MAX value
               GetLengthOfArrayType = CLng(GetPropertyQualifierValue(oProperty, "MAX"))
            End If
            Exit For
         End If
      Next      
   End Function
   
   Private Function GetPropertyQualifierValue (ByVal oProperty, ByVal strQualifier)
      Dim PropertyQualifierSet, PropertyQualifier
      
      Set PropertyQualifierSet = oProperty.Qualifiers_
      GetPropertyQualifierValue = Null

      For Each PropertyQualifier in PropertyQualifierSet
         If (StrComp(PropertyQualifier.Name, strQualifier, 1) = 0) Then
            GetPropertyQualifierValue = PropertyQualifier.Value
            Exit Function
         End If
      Next
   End Function

End Class

'
' This is a special function that can be used to convert the GUID to adapter
' name
'
Private Function wsfGetAdapterName(oWMI, ByVal AdapterGuid, ByRef strAdapterName)
   Dim oWMIRequest, oWMIBuffer

   wsfGetAdapterName = False
   oLog.Write ("Using WMI to query for device name corresponding to " & AdapterGuid)
   
   Set oWMIRequest = New CWMIRequest

   oWMIRequest.ClassName = "MSNdis_EnumerateAdapter"
   oWMIRequest.RequestType = QUERY_CLASS_INSTANCE_PROPERTIES

   Set oWMIBuffer = New CWMIBuffer
   oWMIBuffer.PropertyName = "DeviceName"
   oWMIBuffer.Data = "\DEVICE\" & AdapterGuid
   oWMIBuffer.DataType = wbemCimtypeString
   oWMIRequest.PushInBuffer(oWMIBuffer)

   Set oWMIBuffer = New CWMIBuffer
   oWMIBuffer.PropertyName = "InstanceName"
   oWMIRequest.PushOutBuffer(oWMIBuffer)

   If (Not oWMI.WMIRequest(oWMIRequest)) Then
      oLog.Write ("Unable to query for complete adapter name from WMI. Error 0x" & Hex(oWMI.LastWMIError))
      Exit Function
   End If
   
   strAdapterName = oWMIRequest.OutObject(0).Data
   oLog.Write ("Adapter name: " & strAdapterName)
   
   wsfGetAdapterName = True
   
   Set oWMIBuffer = Nothing
   Set oWMIRequest = Nothing

End Function


'
' Object that holds all the information that is used for the query/set and the response. Similar to
' 
Class CWMIRequest
   Dim ClassName        ' Name of the class we want to query
   Dim RequestType      ' The request type

   Dim InObject         ' An array of structures of CWMIBuffer. This array is
                        ' used by CWMI to figure out what properties/values must match
   Dim InSize           ' The number of elements in the array

   Dim OutObject        ' An array of CWMIBuffer structures. Holds the results
   Dim OutSize          ' The number of elements in this array

   Dim MaxInSize        ' The number of elements actually allocated for in array
   Dim MaxOutSize       ' The number of elements allocated for out array

   Dim EventHandle      ' An EventSource object that will be filled when we start wait for event
   Private Sub Class_Initialize
      MaxInSize = 1
      MaxOutSize = 3 
      
      InSize = 0
      OutSize = 0
      ReDim InObject(MaxInSize)
      ReDim OutObject(MaxOutSize)    

      Set EventHandle = Nothing
      RequestType = QUERY_CLASS_INSTANCE_PROPERTIES
   End Sub

   Private Sub Class_Terminate
      Dim nCount
      For nCount = 0 To MaxInSize-1
         Set InObject(nCount) = Nothing
      Next

      For nCount = 0 To MaxOutSize-1
         Set OutObject(nCount) = Nothing
      Next

      Erase InObject
      Erase OutObject

      Set EventHandle = Nothing
   End Sub
   
   Public Function PushInBuffer (oWMIBuffer)
      If (InSize = MaxInSize) Then
         MaxInSize = MaxInSize + 2
         ReDim Preserve InObject(MaxInSize)
      End If

      Set InObject(InSize) = oWMIBuffer
      InSize = InSize + 1
   End Function

   Public Function PushOutBuffer (oWMIBuffer)
      If (OutSize = MaxOutSize) Then
         MaxOutSize = MaxOutSize + 5
         ReDim Preserve OutObject(MaxOutSize)
      End If

      Set OutObject(OutSize) = oWMIBuffer
      OutSize = OutSize + 1
   End Function

   Public Function PopInBuffer (nIndex)
      If (nIndex < InSize And nIndex >= 0) Then
         ' Store the buffer we removed
         Set PopInBuffer = InObject(nIndex)
         
         ' Use the last element to replace our current element
         Set InObject(nIndex) = InObject(InSize-1)

         ' reduce the insize as we have now lost an element
         InSize = InSize - 1
      Else
         oLog.Write ("Attempting to pop a non existing buffer")
         Set PopInBuffer = Nothing
      End If
   End Function
   
   Public Function PopOutBuffer (nIndex)
      If (nIndex < OutSize And nIndex >= 0) Then
         ' Store the buffer we removed
         Set PopOutBuffer = OutObject(nIndex)
         
         ' Use the last element to replace our current element
         Set OutObject(nIndex) = OutObject(InSize-1)

         ' reduce the outsize as we have now lost an element
         OutSize = OutSize - 1
      Else
         oLog.Write ("Attempting to pop a non existing buffer")
         Set PopOutBuffer = Nothing
      End If
   End Function
   
   Public Sub ClearRequest
      Dim nCount

      For nCount = 0 To InSize-1
         Set InObject(nCount) = Nothing
      Next
      InSize = 0

      For nCount = 0 To OutSize-1
         Set OutObject(nCount) = Nothing
      Next
      OutSize = 0      

      Set EventHandle = Nothing
   End Sub

   Function CopyRequest(oSrcRequest)
      Dim NewWMIBuffer, nCount

      ClearRequest
      
      ClassName = oSrcRequest.ClassName
      RequestType = oSrcRequest.RequestType
      Set EventHandle = oSrcRequest.EventHandle
      
      For nCount = 0 To oSrcRequest.InSize-1
         Set NewWMIBuffer = New CWMIBuffer
         NewWMIBuffer.CopyBuffer(oSrcRequest.InObject(nCount))

         PushInBuffer (NewWMIBuffer)
         Set NewWMIBuffer = Nothing
      Next
      
      For nCount = 0 To oSrcRequest.OutSize-1
         Set NewWMIBuffer = New CWMIBuffer
         NewWMIBuffer.CopyBuffer(oSrcRequest.OutObject(nCount))

         PushOutBuffer (NewWMIBuffer)
         Set NewWMIBuffer = Nothing         
      Next
      
   End Function
   

End Class

Class CWMIBuffer
   Dim PropertyName     ' String representing the property
   Dim Data             ' Variant that holds result or input data(can be scalar 
                        ' or CWMIEmbeddedObject or CWMIArray)
   Dim DataType         ' The cim type of Data
   Dim ArrayType        ' Whether or not it is an array
   Dim SizeInformation  ' The property name/value holding the number of array elements
   Dim EmbeddedObject   ' The "object:name" of the embedded object held by this instance
   Dim Locked           ' Whether locked from modification or not
   Dim StructName       ' For debug, so we can identify the type of variant object
   Private Sub Class_Initialize
      SizeInformation = Null
      EmbeddedObject = Null
      DataType = wbemCimtypeString  ' Default, we care about
      ArrayType = False
      Locked = False
      StructName = "CWMIBuffer"
   End Sub

   Private Sub Class_Terminate
      If (DataType = wbemCimtypeObject Or ArrayType) Then
         ' its either a CWMIArray or a CWMIEmbeddedObject object
         Set Data = Nothing
      End If
   End Sub

   Public Function CopyBuffer(oSrcBuffer)
      Dim NewWMIEmbObj, NewWMIArray
      
      PropertyName = oSrcBuffer.PropertyName

      DataType = oSrcBuffer.DataType
      ArrayType = oSrcBuffer.ArrayType 

      If (DataType = wbemCimtypeObject) Then
         If (ArrayType) Then
            Set NewWMIArray = New CWMIArray
            NewWMIArray.CopyArray(oSrcBuffer.Data)
            Set Data = NewWMIArray
            Set NewWMIArray = Nothing
         Else
            Set NewWMIEmbObj = New CWMIEmbeddedObject
            NewWMIEmbObj.CopyObject(oSrcBuffer.Data)
            Set Data = NewWMIEmbObj
            Set NewWMIEmbObj = Nothing
         End If
      ElseIf (ArrayType) Then
         Set NewWMIArray = New CWMIArray
         NewWMIArray.CopyArray(oSrcBuffer.Data)
         Set Data = NewWMIArray
         Set NewWMIArray = Nothing
      Else
         Data = oSrcBuffer.Data
      End If

      SizeInformation = oSrcBuffer.SizeInformation
      EmbeddedObject = oSrcBuffer.EmbeddedObject

   End Function
End Class

Class CWMIEmbeddedObject
   Dim ArrProperty      ' Array of all the properties of this object: Arr(CWMIBuffer)
   Dim Size             ' Number of elements in the above array
   Dim nAllocSize       ' Internal variable
   Dim OriginalObject   ' Pointer to original object that this stuct contains info about
   Dim StructName       ' For debug

   Private Sub Class_Initialize
      nAllocSize = 5
      ReDim ArrProperty(nAllocSize)
      Size = 0
      Set OriginalObject = Nothing
      StructName = "CWMIEmbeddedObject"
   End Sub

   Private Sub Class_Terminate
      Dim nCount
      For nCount = 0 To Size-1
         Set ArrProperty(nCount) = Nothing
      Next

      Erase ArrProperty
   End Sub

   Public Function PushBuffer (oWMIBuffer)
      If (Size = nAllocSize) Then
         nAllocSize = nAllocSize + 2
         ReDim Preserve ArrProperty(nAllocSize)
      End If

      Set ArrProperty(Size) = oWMIBuffer
      Size = Size + 1
   End Function

   Public Function CopyObject(oSrcObject)
      Dim nCount, NewWMIBuffer

      Size = 0
      For nCount = 0 To oSrcObject.Size-1
         Set NewWMIBuffer = New CWMIBuffer

         NewWMIBuffer.CopyBuffer (oSrcObject.ArrProperty(nCount))
         PushBuffer(NewWMIBuffer)
         Set NewWMIBuffer = Nothing
      Next
   End Function
   
End Class

Class CWMIArray
   Dim ArrElement       ' Array of elements in this array. Arr(CWMIBuffer)
   Dim Size             ' Size of above array
   Dim nAllocSize       ' Internal size holding variable
   Dim OriginalArray    ' Holds reference to original array
   Dim StructName       ' For debug
   
   Private Sub Class_Initialize
      nAllocSize = 5
      ReDim ArrElement(nAllocSize)
      Size = 0
      OriginalArray = Null
      StructName = "CWMIArray"
   End Sub

   Private Sub Class_Terminate
      Dim nCount
      For nCount = 0 To Size-1
         Set ArrElement(nCount) = Nothing
      Next

      Erase ArrElement
   End Sub
   
   Public Function PushElement (oElement)
      If (Size = nAllocSize) Then
         nAllocSize = nAllocSize + 2
         ReDim Preserve ArrElement(nAllocSize)
      End If

      Set ArrElement(Size) = oElement
      Size = Size + 1
   End Function

   Public Function CopyArray(oSrcArray)
      Dim nCount, NewWMIBuffer

      Size = 0
      For nCount = 0 To oSrcArray.Size-1
         Set NewWMIBuffer = New CWMIBuffer

         NewWMIBuffer.CopyBuffer (oSrcArray.ArrElement(nCount))
         PushElement(NewWMIBuffer)
         Set NewWMIBuffer = Nothing
      Next      
   End Function
End Class

'<!-- CRC = 0x79063caa --->
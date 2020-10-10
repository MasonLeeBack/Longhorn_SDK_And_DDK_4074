
Option Explicit

Const RUN_TEST_CASE          =  1
Const SKIP_SUBKEY_TEST       =  2
Const SKIP_VALUE_TEST        =  3


Const TEST_NO_OP             =  1
Const TEST_RANDOM_DATA       =  2
Const TEST_DELETE_VALUE      =  3
Const TEST_DELETE_SUBKEY     =  4
Const TEST_CHANGE_VALUE_TYPE =  5

Const REG_SZ                 =  1
Const REG_EXPAND_SZ          =  2
Const REG_BINARY             =  3
Const REG_DWORD              =  4
Const REG_MULTI_SZ           =  7

Const HKEY_CLASSES_ROOT      = &H80000000
Const HKEY_CURRENT_USER      = &H80000001
Const HKEY_LOCAL_MACHINE     = &H80000002
Const HKEY_USERS             = &H80000003
Const HKEY_CURRENT_CONFIG    = &H80000005

'============================================================================================='
'/**
' This class tests robustness and security of applications that access the regsitry
'@author    Adeel Siddiqui
'@date      03/31/02
'@alias     adeels
'*/
Class CRegistryTester
   Dim mConfiguration
   Dim mRandomGen
   Dim mxSavedRegName
   Dim mxSavedRegValue
   Dim mxSavedRegType
   Dim moRegObj
    
   Sub Class_Initialize
      Set mConfiguration = Nothing
      Set mRandomGen = Nothing
      Set moRegObj = Nothing
   End Sub

   '================================================================================================='
   '/**
   ' This API should be first to be called on Registry object. Clients will use this 
   ' method to register callback handlers with the registry object.
   ' @params
   ' !oRegConfig    The configuration object that contains callbacks etc.
   ' @return        True on success, else failure
   ' @example
   '               Set oRegistryConfig = new CRegistryConfiguration
   '               Call oRegistryTesterConfig.SetHandlers ("OnChangingRegistry", "OnChangedRegistry")
   '               If Not oRegistryTester.Initialize (oRegistryTesterConfig) Then
   '                  call oLog.Failed ("Failed to initialize the registry tester object", 88888)
   '                  Exit Function
   '               End If
   ' */        
   Function Initialize (oRegConfig)
      If (oRegConfig Is Nothing) Then
          Initialize = False
      Else
          Set mConfiguration = oRegConfig
          Set mRandomGen = New CRandomGenerator
          Initialize = True
      End If
   End Function

   '================================================================================================='
   '/**
   ' Test the specified registry subkey with random data.
   ' For the specified strRootKey, this API will recursively go into all subkey replacing the
   ' Values found with random data. Before the actual change made is to the registry, the callback
   ' handler for OnChangingRegistry is invoked (if registered). That way user has the option of
   ' accepting or rejecting or even editing the suggested change.
   '
   ' For Values of type string, this API will replace the existing value with a random hex string 
   ' of the same length. If the String Value is empty, a random length between 1 and 10 will be used
   ' For Numbers, a random long integer will be used to replace the value in the registry. The number
   ' can be either positive or negative
   '
   ' This API will clean up after itself, replacing the original data in the Value field. However, do note
   ' that fatal errors like script pop ups could cause the test to bail out immediately before registry is
   ' restored. You may want to save the registry subkey and restore it yourself after the test is done.
   ' @params
   ' !hDefKey       Specifies the tree that contains the strRootKey path (HKEY_LOCAL_MACHINE, etc)
   ' !strRootKey    String containing the key whose values (and values of all its subkeys) are to be tested
   ' @return        True on success, else failure
   ' @example
   '    call oRegistryTester.RunRandomTest ("\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\{4D36E972-E325-11CE-BFC1-08002bE10318\0002}")
   ' */            
   Function RunRandomTest (hDefKey, strRootKey)
      ' Setup the test configuration
      mConfiguration.TestToRun = TEST_RANDOM_DATA

      Call StartRegistryTesting(hDefKey, strRootKey)
   End Function

   '================================================================================================='
   '/**
   ' Test the specified registry subkey by changing the type of its Values.
   ' For the specified strRootKey, this API will recursively go into all subkey changing the
   ' type of the Values found with randomly chosen types. Before the actual change is made to
   ' the registry, the callback handler for OnChangingRegistry is invoked (if registered). That 
   ' way user has the option of accepting or rejecting or even editing the suggested change.
   '
   ' This method will also change the contents of the data to match the new type being tested.
   ' For example if the String Value "DriverName" is being changed a Number data type, the contents
   ' of DriverName will be converted to a number.
   '
   ' This API will clean up after itself, replacing the original data and data type for the Value being
   ' tested. However, do note that fatal errors like script pop ups could cause the test to bail out 
   ' immediately before registry is restored. You may want to save the registry subkey and restore it 
   ' yourself after the test is done.
   ' @params
   ' !hDefKey       Specifies the tree that contains the strRootKey path (HKEY_LOCAL_MACHINE, etc)
   ' !strRootKey    String containing the key whose values (and values of all its subkeys) are to be tested
   ' @return        True on success, else failure
   ' @example
   '    call oRegistryTester.RunChangeTypeTest ("\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\{4D36E972-E325-11CE-BFC1-08002bE10318\0002}")
   ' */    
   Function RunChangeTypeTest (hDefKey, strRootKey)
      ' Setup the test configuration
      mConfiguration.TestToRun = TEST_CHANGE_VALUE_TYPE

      Call StartRegistryTesting(hDefKey, strRootKey)        
   End Function

   '================================================================================================='
   '/**
   ' Test the specified registry subkey by deleting each Value found under it
   ' For the specified strRootKey, this API will recursively go into all subkey deleting all
   ' the Values found. Before the actual change is made to the registry, the callback handler
   ' for OnChangingRegistry is invoked (if registered). That way user has the option of 
   ' accepting or rejecting or even editing the suggested change.
   '
   ' This method will delete one value at a time invoking callback handlers to send appropriate
   ' notifications to the client
   '
   ' This API will clean up after itself, placing the original Value being tested back into the registry
   ' However, do note that fatal errors like script pop ups could cause the test to bail out immediately 
   ' before registry is restored. You may want to save the registry subkey and restore it 
   ' yourself after the test is done.
   ' @params
   ' !hDefKey       Specifies the tree that contains the strRootKey path (HKEY_LOCAL_MACHINE, etc)
   ' !strRootKey    String containing the key whose values (and values of all its subkeys) are to be tested
   ' @return        True on success, else failure
   ' @example
   '    call oRegistryTester.RunDeleteValueTest ("\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\{4D36E972-E325-11CE-BFC1-08002bE10318\0002}")
   ' */
   Function RunDeleteValueTest (hDefKey, strRootKey)
      ' Setup the test configuration
      mConfiguration.TestToRun = TEST_DELETE_VALUE

      Call StartRegistryTesting(hDefKey, strRootKey)
   End Function


   '================================================================================================='
   '/**
   ' This is a special methos which takes no action on the registry.
   ' This method allows the caller to iterate through the registry getting callback
   ' notifications for each Value in the registry but for which the Registry object
   ' will take no action. The caller is then completely free to do whatever he pleases
   ' with the registry values being iterated.
   '
   ' An example of such a test case run would be to test boundary conditions on Values. Since
   ' boundaries are different for different values, the control for this kind of test is better
   ' placed in the hands of the callee. Also, testing for specil cases could also be handled this
   ' way.
   '
   ' This API will NOT clean up after itself. The onus of restoring the registry to its original
   ' state is completely that of the caller.
   '
   ' @params
   ' !hDefKey       Specifies the tree that contains the strRootKey path (HKEY_LOCAL_MACHINE, etc)
   ' !strRootKey    String containing the key whose values (and values of all its subkeys) are to be tested
   ' @return        True on success, else failure
   ' @example
   '    call oRegistryTester.RunDeleteValueTest ("\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\{4D36E972-E325-11CE-BFC1-08002bE10318\0002}")
   ' */
   Function RunNoOperationTest (hDefKey, strRootKey)
      ' Setup the test configuration
      mConfiguration.TestToRun = TEST_NO_OP

      Call StartRegistryTesting(hDefKey, strRootKey)
   End Function   


   Private Function StartRegistryTesting (hDefKey, strRootKey)
      Set moRegObj = CreateRegistryObject ()
      If (moRegObj Is Nothing) Then
         ' No reg object, then no game
         Exit Function
      End If

      Call Traverse (hDefKey, strRootKey)

      Set moRegObj = Nothing    
   End Function


   Function Traverse (hDefKey, strBaseKey)
      Dim SubKey, arrSubKeys()
      Dim FullKeyName, nResult
      Dim oRegKey

      Set oRegKey = New CRegistryKey
      Set oRegKey.oRegObject = moRegObj
      oRegKey.hDefKey = hDefKey

      nResult = moRegObj.EnumKey (hDefKey, strBaseKey, arrSubKeys)

      If ((nResult = 0) And (Not IsNull(arrSubKeys))) Then
         For each SubKey in arrSubKeys
            FullKeyName = strBaseKey & "\" & SubKey                
            call Traverse (hDefKey, FullKeyName)

            oRegKey.FullName = FullKeyName
            
            Call TestRegKey (oRegKey)
         Next
      End If

      oRegKey.FullName = strBaseKey
      ' Now to test the values in the root subkey itself
      call TestRegKey (oRegKey)

      Set oRegKey.oRegObject = Nothing
      Set oRegKey = Nothing
   End Function


   Function TestRegKey (oRegKey)
      Dim nResult, nCounter

      nCounter = mConfiguration.IterationsPerCase     
      While (nCounter > 0)
         Select Case mConfiguration.TestToRun
             Case TEST_NO_OP, TEST_RANDOM_DATA, TEST_CHANGE_VALUE_TYPE, TEST_DELETE_VALUE
                 nResult = RunCommonTestPass (oRegKey, mConfiguration.TestToRun)
             Case Else
                 call oLog.Failed ("Invalid test case to run specified", 88888)
                 nResult = 0
         End Select
         
         TestRegKey = nResult
         nCounter = nCounter - 1         
      Wend
   End Function


   Function RunCommonTestPass (oRegKey, nTestCase)       
      Dim oRegVal, xNewRegData
      Dim nResult, nSuccessState

      Dim arrNames
      Dim arrTypes
      Dim i

      ' Get the list of values within this key
      Set oRegVal = New CRegistryValue
      Set oRegVal.oRegObject = moRegObj
      oRegVal.hDefKey = oRegKey.hDefKey
      oRegVal.SubKeyName = oRegKey.FullName

      nResult = moRegObj.EnumValues (oRegKey.hDefKey, oRegKey.FullName, arrNames, arrTypes)
      If ((nResult = 0) And (Not IsNull(arrTypes)) And (Not IsNull(arrNames))) Then
         For i = LBound(arrTypes) To UBound(arrTypes)       
            '
            ' Ascertain the random data we will be assigning to this value
            '
            oRegVal.Name = arrNames(i)
            oRegVal.DataType = arrTypes(i)

            Select Case nTestCase
               Case TEST_NO_OP, TEST_DELETE_VALUE
                   xNewRegData = Null
               Case TEST_RANDOM_DATA
                   xNewRegData = GetRandomDataForRegistryValue (oRegVal)
               Case TEST_CHANGE_VALUE_TYPE
                   xNewRegData = GetNewTypeForValue (oRegVal)
               Case Else

            End Select

            nResult = mConfiguration.NotifyOnChangingRegistry ( _
               oRegKey, _
               oRegVal, _
               nTestCase, _
               xNewRegData _
               )
           
            Select Case nResult

               '
               ' If this test case is to be skipped then we are done
               '
               Case SKIP_SUBKEY_TEST
                  ' Need not test this subkey! Bail out of this subkey enumeration loop
                  Exit For
               case SKIP_VALUE_TEST
                  ' Doing nothing amounts to skipping value test
               Case RUN_TEST_CASE
                  ' Will make changes to the registry but preserves current value first
                  nSuccessState = RunTestCase (oRegKey, oRegVal, nTestCase, xNewRegData)

                  nResult = mConfiguration.NotifyOnRegistryChanged ( _
                      oRegKey, _
                      oRegVal, _
                      nTestCase, _
                      xNewRegData, _
                      nSuccessState _
                      )
                             
                  ' Now restore the value cahnged by RunTestCase
                  call RestoreRegData (oRegKey, oRegVal, nTestCase, xNewRegData)
                   
               Case Else
                  call oLog.Failed ("Invalid test case to run specified", 88888)
            End Select
         Next
      Else
         nResult = SKIP_SUBKEY_TEST
      End If

      Set oRegVal.oRegObject = Nothing
      Set oRegVal = Nothing
      RunCommonTestPass = nResult
   End Function


   ' ****************************************
   '
   '           PRIVATE HELPER API
   '
   ' ****************************************


   Private Function RunTestCase (oRegKey, oRegVal, nTestCase, xNewRegData)
      Dim nResult
      
      RunTestCase = False
      
      Select Case nTestCase
         case TEST_RANDOM_DATA
            '
            ' The caller wants us to edit the registry. Do so now
            ' But save first so we can restore the original value
            '
            nResult = oRegVal.ReadValue   ' Read from registry
            If (nResult = 0) Then
               ' Store old data and overwrite with new data
               mxSavedRegValue = oRegVal.Value
               oRegVal.Value = xNewRegData

               nResult = oRegVal.WriteValue  ' Write to registry
               If (nResult = 0) Then
                  RunTestCase = True
               End If
            End If
            
         case TEST_CHANGE_VALUE_TYPE
            '
            ' The caller wants to change the type of current value
            ' Save the original type so we can restore it! Also change
            ' the value to correspond to new type
            '
            nResult = oRegVal.ReadValue
            If (nResult = 0) Then
               Dim xTempRegVal
               Select Case xNewRegData
                  Case REG_DWORD
                     xTempRegVal = mRandomGen.GetRandomNumber (0, 2147483647)
                  Case REG_SZ
                     xTempRegVal = mRandomGen.GetRandomHexString (mRandomGen.GetRandomNumber (1, 10))
               End Select

               mxSavedRegType = oRegVal.DataType
               mxSavedRegValue = oRegVal.Value

               oRegVal.DataType = xNewRegData
               oRegVal.Value = xTempRegVal

               nResult = oRegVal.ChangeType
               If (nResult = 0) Then
                  RunTestCase = True
               End If
            End If
         case TEST_DELETE_VALUE
            '
            ' The caller wants us to delete the current value
            ' Saved the RegValue object as it needs to be restored
            '
            nResult = oRegVal.ReadValue
            If (nResult = 0) Then
               mxSavedRegName = oRegVal.Name
               mxSavedRegType = oRegVal.DataType
               mxSavedRegValue = oRegVal.Value

               ' Delete the named value from the registry
               nResult = oRegVal.DeleteValue
               If (nResult = 0) Then
                  RunTestCase = True
               End If
            End If
      End Select
     
   End Function


   Function RestoreRegData (oRegKey, oRegVal, nTestCase, xNewRegData)
      Dim nResult
      RestoreRegData = False
      
      Select Case nTestCase
         Case TEST_RANDOM_DATA
            oRegVal.Value = mxSavedRegValue
            nResult = oRegVal.WriteValue
            If (nResult = 0) Then
               RestoreRegData = True
            End If
          
         Case TEST_CHANGE_VALUE_TYPE
            oRegVal.Value = mxSavedRegValue
            oRegVal.DataType = mxSavedRegType

            nResult = oRegVal.ChangeType
            If (nResult = 0) Then
               RestoreRegData = True
            End If

         Case TEST_DELETE_VALUE
            ' Place the deleted value back in the registry

            ' Add the registry value back in
            oRegVal.Name = mxSavedRegName
            oRegVal.DataType = mxSavedRegType
            oRegVal.Value = mxSavedRegValue

            nResult = oRegVal.WriteValue
            If (nResult = 0) Then
               RestoreRegData = True
            End If
      End Select

   End Function


   Private Function GetRandomDataForRegistryValue (oRegVal)
      Dim xData, nDataLen, xRandomData

      Select Case oRegVal.DataType         
         Case REG_SZ      ' String
            oRegVal.ReadValue

            xData = oRegVal.Value
               
            nDataLen = Len (xData)
            If nDataLen = 0 Then
               ' If string is empty, test with some data
               xRandomData = mRandomGen.GetRandomHexString (mRandomGen.GetRandomNumber (1, 10))
            Else
               ' If not empty, test with junk of same size
               xRandomData = mRandomGen.GetRandomHexString (nDataLen)
            End If

'         Case REG_BINARY    ' Binary
'            ' #### WHAT DO DO HERE
'            xRandomData = 123

         Case REG_DWORD      ' Number
            ' Get a random number in the positive range of long
            xRandomData = mRandomGen.GetRandomNumber (0, 2147483647)
            ' Then randomly make it negative
            If ( (mRandomGen.GetRandomNumber (0, 999) mod 2) = 0) Then
               xRandomData = xRandomData * (-1)
            End If

         Case Else
            ' Do nothing (xRandomData stays Empty)
      End Select

      If (Not IsEmpty (xRandomData)) Then
         GetRandomDataForRegistryValue = xRandomData
      Else
         GetRandomDataForRegistryValue = Null
      End If
   End Function


   Function GetNewTypeForValue (oRegVal)
      Dim nNewType

      nNewType = oRegVal.DataType

      '
      ' Get a random type which is different from current type
      '
      While (nNewType = oRegVal.DataType)
         nNewType = mRandomGen.GetRandomNumber (1, 4) ' REG_SZ to REG_DWORD

         ' #### CHEAP trick for now to avoid binary type
         If nNewType = REG_BINARY Then
            nNewType = oRegVal.DataType
         End If
      Wend

      GetNewTypeForValue = nNewType
   End Function

End Class

Class CRegistryConfiguration
   Dim mFuncOnChangingRegistry
   Dim mFuncOnRegistryChanged
   Dim mnTestToRun
   Dim mnIterationsPerCase

   Sub Class_Initialize
      Set mFuncOnChangingRegistry = Nothing
      Set mFuncOnRegistryChanged = Nothing
      mnTestToRun = TEST_RANDOM_DATA
      mnIterationsPerCase = 1
   End Sub
    
   Function SetHandlers (mHandlerOnChanging, mHandlerOnChanged)
      If StrComp (mHandlerOnChanging, "", 1) = 0 Then
         Set mFuncOnChangingRegistry = Nothing
      Else
         Set mFuncOnChangingRegistry = GetRef (mHandlerOnChanging)
      End If

      If StrComp (mHandlerOnChanged, "", 1) = 0 Then
         Set mFuncOnRegistryChanged = Nothing
      Else
         Set mFuncOnRegistryChanged = GetRef (mHandlerOnChanged)
      End If
        
    End Function


   Function NotifyOnChangingRegistry (ByRef oRegKey, ByRef oRegVal, nAction, ByRef xNewRegData)
      If (Not mFuncOnChangingRegistry Is Nothing) Then
         NotifyOnChangingRegistry = mFuncOnChangingRegistry (oRegKey, oRegVal, nAction, xNewRegData)
      End If
   End Function


   Function NotifyOnRegistryChanged (ByRef oRegKey, ByRef oRegVal, nActionType, ByRef xNewRegData, nSuccessStatus)
      If (Not mFuncOnRegistryChanged Is Nothing) Then
         NotifyOnRegistryChanged = mFuncOnRegistryChanged (oRegKey, oRegVal, nActionType, xNewRegData, nSuccessStatus)
      End If
   End Function

   Property Get TestToRun
      TestToRun = mnTestToRun
   End Property
   
   Property Let TestToRun (nVal)
      mnTestToRun = nVal
   End Property    


   Property Get IterationsPerCase
      IterationsPerCase = mnIterationsPerCase
   End Property
   
   Property Let IterationsPerCase (nVal)
      mnIterationsPerCase = nVal
   End Property    

End Class

Function CreateRegistryObject ()
   Set CreateRegistryObject = GetObject("winmgmts://./root/default:StdRegProv")

   If CreateRegistryObject is Nothing Then
      call oLog.SafeFailed ("Failed to create Registry object", 88888)
      Set CreateRegistryObject = Nothing
   End If
End Function

' Convert the type field's data type
Function GetRegistryDataTypeString(DataType)
   Select Case DataType
      Case REG_SZ:
         GetRegistryDataTypeString = "REG_SZ"
            
      Case REG_EXPAND_SZ:
         GetRegistryDataTypeString = "REG_EXPAND_SZ"

      Case REG_BINARY:
         GetRegistryDataTypeString = "REG_BINARY"

      Case REG_DWORD:
         GetRegistryDataTypeString = "REG_DWORD"

      Case REG_MULTI_SZ:
         GetRegistryDataTypeString = "REG_MULTI_SZ"

      Case Else
         GetRegistryDataTypeString = CStr(DataType)
   End Select
End Function

Class CRegistryValue
   Dim oRegObject    ' Object that can be used to work with the object
   Dim hDefKey       ' Specifies the tree (HKLM, HKCU, etc)
   Dim SubKeyName    ' The path that conatins the named values to be enumerated
   Dim Name          ' This the name of the value string 
   Dim DataType      ' This is the type of the element. This should be used
                     ' to determine which of the several Get methods to call   
   Dim Value

   Public Function ReadValue
      Select Case DataType
         Case REG_SZ:
            ReadValue = oRegObject.GetStringValue ( hDefKey, _
               SubKeyName, _
               Name, _
               Value _
               )
               
         Case REG_EXPAND_SZ:
            ReadValue = oRegObject.GetExpandedStringValue ( hDefKey, _
               SubKeyName, _
               Name, _
               Value _
               )

         Case REG_BINARY:
            ReadValue = oRegObject.GetBinaryValue ( hDefKey, _
               SubKeyName, _
               Name, _
               Value _
               )

         Case REG_DWORD:
            ReadValue = oRegObject.GetDWORDValue ( hDefKey, _
               SubKeyName, _
               Name, _
               Value _
               )

         Case REG_MULTI_SZ:
            ReadValue = oRegObject.GetMultiStringValue ( hDefKey, _
               SubKeyName, _
               Name, _
               Value _
               )
         Case Else
            call oLog.Write ("This is as yet an unhandled data type! Not reading it")
            ReadValue = -1
      End Select
   End Function


   Public Function WriteValue
      ' On a write, if the value was not present, we would add it
      Select Case DataType
         Case REG_SZ:
            WriteValue = oRegObject.SetStringValue ( hDefKey, _
               SubKeyName, _
               Name, _
               Value _
               )
               
         Case REG_EXPAND_SZ:
            WriteValue = oRegObject.SetExpandedStringValue ( hDefKey, _
               SubKeyName, _
               Name, _
               Value _
               )

         Case REG_BINARY:
            WriteValue = oRegObject.SetBinaryValue ( hDefKey, _
               SubKeyName, _
               Name, _
               Value _
               )

         Case REG_DWORD:
            WriteValue = oRegObject.SetDWORDValue ( hDefKey, _
               SubKeyName, _
               Name, _
               Value _
               )

         Case REG_MULTI_SZ:
            WriteValue = oRegObject.SetMultiStringValue ( hDefKey, _
               SubKeyName, _
               Name, _
               Value _
               )
               
         Case Else
            call oLog.Write ("This is as yet an unhandled data type! Not writing it")
            WriteValue = -1
      End Select
      
   End Function

   Public Function DeleteValue
      DeleteValue = oRegObject.DeleteValue(hDefKey, _
         SubKeyName, _
         Name _
         )
   End Function

   Public Function ChangeType
      ' We would just write the new value and it should overwrite the previous value
      ChangeType = WriteValue
   End Function
End Class

Class CRegistryKey
   Dim oRegObject    ' Object that can be used to work with the object
   Dim hDefKey       ' Specifies the tree (HKLM, HKCU, etc)
   Dim FullName      ' Name of the registry key
End Class





'<!-- CRC = 0x584254c7 --->
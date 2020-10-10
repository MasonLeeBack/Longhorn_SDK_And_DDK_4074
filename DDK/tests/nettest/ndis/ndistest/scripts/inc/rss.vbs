'<!-- CRC = 0xf85d1ddc -->
Option Explicit
'
' These are the various types of Ndis 6.0 structure
'
Const    NDIS_OBJECT_TYPE_RSS_CAPABILITIES   = &H88&
Const    NDIS_OBJECT_TYPE_RSS_PARAMETERS     = &H89&

'
' What hash functions does NDIS support
'
Const    NdisHashFunctionToeplitz            = &H00000001&
Const    NdisHashFunctionReserved1           = &H00000002&
Const    NdisHashFunctionReserved2           = &H00000004&
Const    NdisHashFunctionReserved3           = &H00000008&

Const    INVALID_HASH_FUNCTION               = &H00000040&
Const    NDIS_HASH_FUNCTION_MASK             = &H000000FF&

'
' What kind of hash field type the protocol what the miniport to do
'
Const    NDIS_HASH_IPV4                      = &H00000100&
Const    NDIS_HASH_TCP_IPV4                  = &H00000200&
Const    NDIS_HASH_IPV6                      = &H00000400&
Const    NDIS_HASH_IPv6_EX                   = &H00000800&
Const    NDIS_HASH_TCP_IPV6                  = &H00001000&
Const    NDIS_HASH_TCP_IPV6_EX               = &H00002000&

Const    INVALID_HASH_TYPE                   = &H00400000&
Const    NDIS_HASH_TYPE_MASK                 = &H00FFFF00&


'
' What kind the receive scale capabilities the miniport can support
'
Const    NDIS_RSS_HASH_FUNCTION_1            = &H00000001&
Const    NDIS_RSS_HASH_FUNCTION_2            = &H00000002&
Const    NDIS_RSS_HASH_FUNCTION_3            = &H00000004&
Const    NDIS_RSS_HASH_FUNCTION_4            = &H00000008&

Const    NDIS_RSS_MESSAGE_SOURCE_INTERRUPTS  = &H00000010&
Const    NDIS_RSS_CLASSIFICATION_AT_ISR      = &H00000020&
Const    NDIS_RSS_CLASSIFICATION_AT_DPC      = &H00000040&

'
' What kind of hash field type the miniport can support
'
Const    NDIS_RSS_HASH_TYPE_TCP_IPV4         = &H00000100&
Const    NDIS_RSS_HASH_TYPE_TCP_IPV6         = &H00000200&
Const    NDIS_RSS_HASH_TYPE_TCP_IPV6_EX      = &H00000400&


Const    MAX_NUMBER_OF_HASH_FUNCTIONS        = 4
Const    MAX_NUMBER_OF_HASH_TYPES            = 5
Const    RSS_PARAMETERS_STRUCT_SIZE          = 28     ' Total RSS struct size
Const    RSS_HASH_FUNCTION_0_KEY_SIZE        = 40     ' 40 bytes of key for

Class CRSSLib
   Dim ValidHashTypes, ValidHashTypesCount
   Dim ValidHashFunctions, ValidHashFunctionsCount
   Dim InvalidHashTypes, InvalidHashTypesCount

   Sub Class_Initialize
      ReDim ValidHashTypes(4)

      ' The raw ones we want to test
      ValidHashTypes(1) = NDIS_HASH_TCP_IPV4
      ValidHashTypes(2) = NDIS_HASH_TCP_IPV4 Or NDIS_HASH_IPV4
      ValidHashTypes(3) = NDIS_HASH_TCP_IPV6
      ValidHashTypes(4) = NDIS_HASH_TCP_IPV6 Or NDIS_HASH_IPV6 Or NDIS_HASH_IPv6_EX

      ValidHashTypesCount = 4

      ReDim ValidHashFunctions(4)

      ValidHashFunctions(1) = NdisHashFunctionToeplitz
      ValidHashFunctions(2) = NdisHashFunctionReserved1
      ValidHashFunctions(3) = NdisHashFunctionReserved2
      ValidHashFunctions(4) = NdisHashFunctionReserved3
      ValidHashFunctionsCount = 4

      ReDim InvalidHashTypes(2)
      InvalidHashTypes(1) = 0
      InvalidHashTypes(2) = INVALID_HASH_TYPE

      InvalidHashTypesCount = 2

   End Sub

   Sub Class_Terminate
   End Sub

   Sub SetFlag(ByRef Value, Flag)
      Value = Value Or Flag
   End Sub

   Sub ClearFlag(ByRef Value, Flag)
      Value = Value Xor Flag
   End Sub

   Function TestFlag(Value, Flag)
      If ((Value And Flag) <> 0) Then
         TestFlag = True
      Else
         TestFlag = False
      End If
   End Function

   Function TestAllFlags(Value, Flags)
      If ((Value And Flags) = Flags) Then
         TestAllFlags = True
      Else
         TestAllFlags = False
      End If
   End Function

   Function HashFunctionFromHashInfo(HashInfo)
      HashFunctionFromHashInfo = HashInfo And NDIS_HASH_FUNCTION_MASK
   End Function

   Function HashTypeFromHashInfo(HashInfo)
      HashTypeFromHashInfo = HashInfo And NDIS_HASH_TYPE_MASK
   End Function

   Function HashInfoFromHashTypeAndFunction(HashType, HashFunction)
      HashInfoFromHashTypeAndFunction = HashType Or HashFunction
   End Function

   '
   ' Returns all supported hash function that the miniport returned as supporting
   '
   Function HashFunctionsFromCapabilitiesFlags(CapabilitiesFlags)
      HashFunctionsFromCapabilitiesFlags = 0

      If (TestFlag(CapabilitiesFlags, NdisHashFunctionToeplitz)) Then
         Call SetFlag (HashFunctionsFromCapabilitiesFlags, NdisHashFunctionToeplitz)
      End If

      If (TestFlag(CapabilitiesFlags, NdisHashFunctionReserved1)) Then
         Call SetFlag (HashFunctionsFromCapabilitiesFlags, NdisHashFunctionReserved1)
      End If

      If (TestFlag(CapabilitiesFlags, NdisHashFunctionReserved2)) Then
         Call SetFlag (HashFunctionsFromCapabilitiesFlags, NdisHashFunctionReserved2)
      End If

      If (TestFlag(CapabilitiesFlags, NdisHashFunctionReserved3)) Then
         Call SetFlag (HashFunctionsFromCapabilitiesFlags, NdisHashFunctionReserved3)
      End If

   End Function

   '
   ' Returns all the valid hash types that we can pass to the miniport based on the
   ' supported hash types that the capabilities oid returned.
   ' Note that this returns the complete list, not selective "valid" ors
   '
   Function HashTypesFromCapabilitiesFlags(CapabilitiesFlags)
      HashTypesFromCapabilitiesFlags = 0

      If (TestFlag(CapabilitiesFlags, NDIS_RSS_HASH_TYPE_TCP_IPV4)) Then
         Call SetFlag (HashTypesFromCapabilitiesFlags, (NDIS_HASH_TCP_IPV4 Or NDIS_HASH_IPV4))
      End If

      If (TestFlag(CapabilitiesFlags, NDIS_RSS_HASH_TYPE_TCP_IPV6)) Then
         Call SetFlag (HashTypesFromCapabilitiesFlags, (NDIS_HASH_TCP_IPV6 Or NDIS_HASH_IPV6))
      End If

      If (TestFlag(CapabilitiesFlags, NDIS_RSS_HASH_TYPE_TCP_IPV6_EX)) Then
         Call SetFlag (HashTypesFromCapabilitiesFlags, (NDIS_HASH_TCP_IPV6_EX Or NDIS_HASH_TCP_IPV6 Or NDIS_HASH_IPV6 Or NDIS_HASH_IPv6_EX))
      End If
   End Function

   '
   ' Takes a capabilities structure and returns lists of the supported and unsupported hash functions
   '
   Sub ClassifyHashFunctions(Capabilities, ByRef SupportedList, ByRef SupportedLength, ByRef UnSupportedList, ByRef UnSupportedLength)
      Dim MiniportHashFunctions, CurrentHashFunction
      Dim nFunctCount

      SupportedLength = 0
      UnSupportedLength = 0

      ' Find the hash functions that the miniport claims to support
      MiniportHashFunctions = HashFunctionsFromCapabilitiesFlags(Capabilities)

      ' oLog.Write ("Miniport Hash Function " & MiniportHashFunctions)

      ' Loop through and find all supported and unsupported hash functions
      For nFunctCount = 1 To ValidHashFunctionsCount
         CurrentHashFunction = ValidHashFunctions(nFunctCount)
         If (TestFlag(MiniportHashFunctions, CurrentHashFunction)) Then
            ' Miniport supports this hash function
            SupportedList(SupportedLength) = CurrentHashFunction
            SupportedLength = SupportedLength + 1
         Else
            ' This valid hash function is not supported by the miniport
            UnSupportedList(UnSupportedLength) = CurrentHashFunction
            UnSupportedLength = UnSupportedLength + 1
         End If
      Next

   End Sub

   '
   ' Takes a capabilities structure and returns lists of the supported and unsupported hash types
   '
   Sub ClassifyHashTypes(Capabilities, ByRef SupportedList, ByRef SupportedLength, ByRef UnSupportedList, ByRef UnSupportedLength)
      Dim MiniportHashTypes, CurrentHashType
      Dim nTypeCount

      SupportedLength = 0
      UnSupportedLength = 0

      ' Find the hash types that the miniport claims to support
      MiniportHashTypes = HashTypesFromCapabilitiesFlags(Capabilities)

      ' oLog.Write ("Miniport Hash Type " & MiniportHashTypes)

      ' Loop through and find all supported and unsupported hash types
      For nTypeCount = 1 To ValidHashTypesCount
         CurrentHashType = ValidHashTypes(nTypeCount)

         If (TestAllFlags(MiniportHashTypes, CurrentHashType)) Then
            ' This hash type combination is supported by the miniport
            SupportedList(SupportedLength) = CurrentHashType
            SupportedLength = SupportedLength + 1
         Else
            ' This valid hash type combination is not supported by the miniport
            UnSupportedList(UnSupportedLength) = CurrentHashType
            UnSupportedLength = UnSupportedLength + 1
         End If
      Next
   End Sub

   Function GenerateValidParameters(ByRef oParameters, Capabilities, IndirectionTableSize, NumProcessors)
      Dim nCount, IndirectionTable()
      Dim nCurrHashValue

      GenerateValidParameters = oParameters.SetInitialize(RSS_PARAMETERS_STRUCT_SIZE + _
         RSS_HASH_FUNCTION_0_KEY_SIZE + _
         IndirectionTableSize)
      If (GenerateValidParameters <> 0) Then
         Call oLog.Write ("Unable to create RSS parameters structure")
         Exit Function
      End If

      ' Fill a really rudimentary hash table

      oParameters.HashInformation = HashInfoFromHashTypeAndFunction( _
         HashTypesFromCapabilitiesFlags(Capabilities), NdisHashFunctionToeplitz)

      oParameters.HashSecretKeyOffset = RSS_PARAMETERS_STRUCT_SIZE
      oParameters.HashSecretKeySize = RSS_HASH_FUNCTION_0_KEY_SIZE
      oParameters.IndirectionTableOffset = oParameters.HashSecretKeyOffset + oParameters.HashSecretKeySize
      oParameters.IndirectionTableSize = IndirectionTableSize

      ' Set the hash secret key
      GenerateValidParameters = oParameters.SetDefaultHashSecretKey(oParameters.HashSecretKeySize)
      If (GenerateValidParameters <> 0) Then
         Call oLog.Write ("Unable to populate RSS parameters structure with hash secret key")
         Exit Function
      End If

      ReDim IndirectionTable(IndirectionTableSize)
      nCurrHashValue = 0
      For nCount = 0 To IndirectionTableSize - 1
         IndirectionTable(nCount) = CByte(nCurrHashValue)
         nCurrHashValue = nCurrHashValue + 1
         If (nCurrHashValue = NumProcessors) Then
            nCurrHashValue = 0
         End If
      Next

      GenerateValidParameters = oParameters.SetIndirectionTable(IndirectionTable, oParameters.IndirectionTableSize)
      If (GenerateValidParameters <> 0) Then
         Call oLog.Write ("Unable to populate RSS parameters structure with hash table")
         Exit Function
      End If

      GenerateValidParameters = 0
   End Function

   ' Fills the IPv4 configuration info such that we would map to the nDesiredIndex +/- some
   ' fixed offset
   Function FillMappingToUniqueIndexIPv4(ByVal nDesiredIndex, HashInformation, ByRef oIPSendNBConfig)
      Dim HashFunction

      HashFunction = HashFunctionFromHashInfo(HashInformation)
      Select Case HashFunction
         Case NdisHashFunctionToeplitz:
            ' TODO: Need to get this correct
            oIPSendNBConfig.DestinationAddress = IPAddr(100, 1, 1, 0)
            oIPSendNBConfig.SourceAddress = IPAddr(200, 1, 0, nDesiredIndex)  ' Only set bits in lower byte
            oIPSendNBConfig.DestinationPort = &H0A00&
            oIPSendNBConfig.SourcePort = &H0B00&

         Case Else
            ' We do not recognize any other hash type
      End Select

   End Function

   ' Fills the IPv6 configuration info such that we would map to the nDesiredIndex +/- some
   ' fixed offset
   Function FillMappingToUniqueIndexIPv6(ByVal nDesiredIndex, HashInformation, ByRef oIPSendNBConfig)
      Dim HashFunction

      HashFunction = HashFunctionFromHashInfo(HashInformation)
      Select Case HashFunction
         Case NdisHashFunctionToeplitz:
            ' TODO: Need to get this correct
            oIPSendNBConfig.DestinationAddress = IPv6Addr(100, 1, 1, 0)
            oIPSendNBConfig.SourceAddress = IPv6Addr(200, 1, 0, nDesiredIndex)  ' Only set bits in lower byte
            oIPSendNBConfig.DestinationPort = &H0A00&
            oIPSendNBConfig.SourcePort = &H0B00&

         Case Else
            ' We do not recognize any other hash type
      End Select

   End Function


   Function GetHashInformationString(HashInformation)
      Dim HashType
      Dim HashFunction

      HashType = HashTypeFromHashInfo(HashInformation)
      HashFunction = HashFunctionFromHashInfo(HashInformation)

      GetHashInformationString = "( "

      ' String the hash function
      If (TestFlag(HashFunction, NdisHashFunctionToeplitz)) Then
         GetHashInformationString = GetHashInformationString & "NdisHashFunctionToeplitz "
      ElseIf (TestFlag(HashFunction, NdisHashFunctionReserved1)) Then
         GetHashInformationString = GetHashInformationString & "NdisHashFunctionReserved1 "
      ElseIf (TestFlag(HashFunction, NdisHashFunctionReserved2)) Then
         GetHashInformationString = GetHashInformationString & "NdisHashFunctionReserved2 "
      ElseIf (TestFlag(HashFunction, NdisHashFunctionReserved3)) Then
         GetHashInformationString = GetHashInformationString & "NdisHashFunctionReserved3 "
      Else
         GetHashInformationString = GetHashInformationString & "INVALID_HASH_FUNCTION "
      End If

      ' String the hash type
      If (TestFlag(HashType, NDIS_HASH_TCP_IPV4)) Then
         GetHashInformationString = GetHashInformationString & "NDIS_HASH_TCP_IPV4 "
      End If

      If (TestFlag(HashType, NDIS_HASH_IPV4)) Then
         GetHashInformationString = GetHashInformationString & "NDIS_HASH_IPV4 "
      End If

      If (TestFlag(HashType, NDIS_HASH_TCP_IPV6)) Then
         GetHashInformationString = GetHashInformationString & "NDIS_HASH_TCP_IPV6 "
      End If

      If (TestFlag(HashType, NDIS_HASH_IPv6_EX)) Then
         GetHashInformationString = GetHashInformationString & "NDIS_HASH_IPv6_EX "
      End If

      If (TestFlag(HashType, NDIS_HASH_IPV6)) Then
         GetHashInformationString = GetHashInformationString & "NDIS_HASH_IPV6 "
      End If

      If (TestFlag(HashType, INVALID_HASH_TYPE)) Then
         GetHashInformationString = GetHashInformationString & "INVALID_HASH_TYPE "
      End If

      GetHashInformationString = GetHashInformationString & ")"

   End Function
End Class



'
'
'
Class CRSSParameters
   Dim HashInformation
   Dim HashSecretKeyOffset    ' Offset of the secret key for hashing
   Dim HashSecretKeySize      ' Size of the hash secret key
   Dim IndirectionTableOffset     ' Offset of the table in the PARAMETERS structure
   Dim IndirectionTableSize       ' Size of the hash table array

   Dim TotalSize              ' Total size of the PARAMETERS structure
   Dim IndirectionTable           ' Actual hash table array

   Sub Class_Initialize
      HashSecretKeyOffset = 0
      HashSecretKeySize = 0
      IndirectionTableOffset = RSS_PARAMETERS_STRUCT_SIZE + RSS_HASH_FUNCTION_0_KEY_SIZE
      IndirectionTableSize = 0
      HashInformation = 0
   End Sub

   Sub ComputeParametersFields
      If (IndirectionTableOffset > HashSecretKeyOffset) Then
         ' Indirection table follows hash secret key
         TotalSize = IndirectionTableOffset + IndirectionTableSize
      Else
         ' Hash secret key follows indirection table
         TotalSize = HashSecretKeyOffset + HashSecretKeySize
      End If

      ReDim IndirectionTable(IndirectionTableSize)
   End Sub
End Class



'<!-- CRC = 0x7ab2518d --->
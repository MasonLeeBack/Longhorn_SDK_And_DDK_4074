
' This is a helper class that helps IF scripts do some NSI work
Class CNdisIfNSIHelper
   Dim oNsiSupport, oNsiClient
   
   Dim oKeyNw, oParamNw    ' Parameters used to create new network
   Dim bNetworkCreated
   
   Sub Class_Initialize()
      Dim NdisStatus
      Set oNsiSupport = Wscript.CreateObject("NDTApi6.NdisNsiSupport.1")
      If (oNsiSupport is nothing) Then
         Call oLog.Failed("Failed to create NDIS NSI API support object", 88888)
         Exit Sub
      End If

      set oNsiClient = Wscript.CreateObject("NDTApi6.NsiClientNdis.1")
      If (oNsiClient is nothing) Then
         Call oLog.Failed("Failed to create NSI client object", 88888)
         Exit Sub
      End If

      NdisStatus = oNsiClient.InitializeNsiClient()      
      If (NdisStatus <> NDIS_STATUS_SUCCESS ) Then
         Call oLog.Failed ("Failed to Initialize NSI client. Status: "& Hex(NdisStatus) , 88888)
         Exit Sub
      End If

      Set oKeyNw = Nothing
      Set oParamNw = Nothing

      bNetworkCreated = FALSE
   End Sub

   Sub Class_Terminate()
      Dim NdisStatus
      
      NdisStatus = oNsiClient.TerminateNsiClient()
      If (NdisStatus <> NDIS_STATUS_SUCCESS) Then
         Call oLog.Failed ("Failed to Terminate NSI client. Status: "& Hex(NdisStatus) , 88888)
         Exit Sub
      End If

      Set oNsiClient = Nothing
      Set oNsiSupport = Nothing
   End Sub

   Private Function GenerateRandomData(DataLength, StartSeed)
      Dim ResultData()
      Dim i, CurrentVal

      ReDim ResultData(DataLength)
      
      For i = 0 to (DataLength - 1)
         CurrentVal = (StartSeed + i) Mod 256
         ResultData(i) = CByte(CurrentVal)
      Next
      
      GenerateRandomData = ResultData
   End Function
   
   Function CreateNewInterfaceNetwork(ByRef NetworkGUID)
      Dim lNetGuidLen, lRwLenNw, sRwData, lProvIfContext, lIfOptions
      Dim Status

      CreateNewInterfaceNetwork = NDIS_STATUS_FAILURE

      lNetGuidLen = oNsiSupport.Sizeof_NetworkGuid
      lRwLenNw = oNsiSupport.Sizeof_NdisNsiNetworkRW

      ' Generate a new random NetworkGUID 
      NetworkGUID = GenerateRandomData(lNetGuidLen, 25)
      
      Set oKeyNw = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibKey", lNetGuidLen, TRUE)
      oKeyNw.KeyLength = lNetGuidLen
      oKeyNw.KeyValue = NetworkGUID
      Set oParamNw = oNDTStruct.vbCreateStructureAndAllocate( _ 
                                  "NsiLibParam", lRwLenNw, TRUE)
      oParamNw.RwStructLength = lRwLenNw
      oParamNw.RodStructLength = 0
      oParamNw.RosStructLength = 0

      sRwData = oParamNw.StructData
      sRwData(0) = CByte(01)   ' Default compartment ID = 1
      sRwData(1) = CByte(00)
      sRwData(2) = CByte(00)
      sRwData(3) = CByte(00)
      oParamNw.StructData = sRwData
      
      Status = oNsiClient.SetAllParameters(NDIS_NSI_NETWORK, NSI_STORE_ACTIVE, _
                                     NSI_SET_CREATE_ONLY, oKeyNw, oParamNw)
      If (Status <> NDIS_STATUS_SUCCESS) Then
         If (Status <> &HC000022A&) Then
            ' Failed with something other than object exists
            oLog.Warned("Network Creation failed. Status: 0x"& Hex(Status))
         Else
            oLog.Write("Network Creation failed since network already exists")
         End If
      Else
         bNetworkCreated = TRUE
      End If

      ' We always assume we succeeded
      CreateNewInterfaceNetwork = NdisStatus
   End Function

   Function DeleteInterfaceNetwork(ByRef NetworkGUID)
      Dim NdisStatus

      If (Not bNetworkCreated) Then
         oLog.Write ("Network was not created. Not deleting")
         Exit Function
      End If
      
      NdisStatus = oNsiClient.SetAllParameters(NDIS_NSI_NETWORK, NSI_STORE_ACTIVE, _
                                     NSI_SET_DELETE, oKeyNw, oParamNw)
      If (NdisStatus <> NDIS_STATUS_SUCCESS) Then
         Call oLog.Warned("Network Deletion failed. Status: 0x"& Hex(NdisStatus))
      End if
   End Function

End Class

'<!-- CRC = 0xdffd92a9 --->
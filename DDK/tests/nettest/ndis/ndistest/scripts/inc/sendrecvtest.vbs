
	Public Function CheckMiniport(oOpen)
		Dim InBuffer(50)
		Dim Oid
		Dim InBufferLen
		Dim VendorDesc
		Dim lByteCount

		Oid = OID_GEN_VENDOR_DESCRIPTION
		InBufferLen = Clng(50)

		Dim ErrorStatus
		Dim BytesWritten, BytesNeeded
		Dim NdisStatus

		ErrorStatus = oOpen.vbNdisRequest( _
		   Oid, _
		   InBuffer, _
		   InBufferLen, _
		   REQUEST_QUERY_INFO, _
		   BytesWritten, _
		   BytesNeeded, _
		   NdisStatus, _
		   FALSE)


		If (ErrorStatus <> 0) Then
			call oLog.SafeFailed ("Could not start Send Complete check ", 88888)
			CheckMiniport = FALSE
			Exit Function
		End If

		If (NdisStatus <> 0) Then
			call oLog.SafeFailed ("Could not start Send Complete check ", 88888)
			CheckMiniport = FALSE
			Exit Function
		End If

		VendorDesc = ""
		for lByteCount = 0 to BytesWritten - 1
			VendorDesc = VendorDesc & Chr(InBuffer(lByteCount))
		Next

		if (StrComp(VendorDesc, "SENDRECEIVETESTADAPTER", 1) = 0) Then
			CheckMiniport = TRUE
		Else
			CheckMiniport = FALSE
		End If

	End Function


   Public Function CheckMiniportSendComplete(oOpen)
      Dim InBuffer
      Dim Oid
      
      Oid = OID_CHECK_FOR_SEND_COMPLETE
      InBuffer = CLng(0)
    
      If (Oid <> 0) Then
         Dim ErrorStatus
         Dim BytesWritten, BytesNeeded
         Dim NdisStatus
         
         ErrorStatus = oOpen.vbNdisRequest( _
               Oid, _
               InBuffer, _
               4, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         
         ' ErrorStatus is boolean for NDIS 5 and long for NDIS 6, ignoring
         
         If (NdisStatus <> 0) Then
            call oLog.SafeFailed ("Could not start Send Complete check ", 88888)
         End If
      End If
      
   End Function

   
   Public Function CheckMiniportRecvReturned(oOpen)
      Dim InBuffer
      Dim Oid
      
      Oid = OID_CHECK_FOR_RECV_RETURNED
      InBuffer = CLng(0)
    
      If (Oid <> 0) Then
         Dim ErrorStatus
         Dim BytesWritten, BytesNeeded
         Dim NdisStatus
         
         ErrorStatus = oOpen.vbNdisRequest( _
               Oid, _
               InBuffer, _
               4, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         
         ' ErrorStatus is boolean for NDIS 5 and long for NDIS 6, ignoring

         If (NdisStatus <> 0) Then
            call oLog.SafeFailed ("Could not start Receives Returned Check ", 88888)
         End If
      End If
      
   End Function


   Public Function StartMiniportIndicateReceive(oOpen)
      Dim InBuffer
      Dim Oid
      
      Oid = OID_READY_TO_INDICATE_RECEIVE
      InBuffer = CLng(0)
    
      If (Oid <> 0) Then
         Dim ErrorStatus
         Dim BytesWritten, BytesNeeded
         Dim NdisStatus
         
         ErrorStatus = oOpen.vbNdisRequest( _
               Oid, _
               InBuffer, _
               4, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         
         ' ErrorStatus is boolean for NDIS 5 and long for NDIS 6, ignoring

         If (NdisStatus <> 0) Then
            call oLog.SafeFailed ("Could not start Miniport Receive Indication ", 88888)
         End If
      End If
      
   End Function

   Public Function StopMiniportIndicateReceive(oOpen)
      Dim InBuffer
      Dim Oid
      
      Oid = OID_STOP_INDICATE_RECEIVE
      InBuffer = CLng(0)
    
      If (Oid <> 0) Then
         Dim ErrorStatus
         Dim BytesWritten, BytesNeeded
         Dim NdisStatus
         
         ErrorStatus = oOpen.vbNdisRequest( _
               Oid, _
               InBuffer, _
               4, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         
         ' ErrorStatus is boolean for NDIS 5 and long for NDIS 6, ignoring

         If (NdisStatus <> 0) Then
            call oLog.SafeFailed ("Could not start Miniport Receive Indication ", 88888)
         End If
      End If
      
   End Function   




'<!-- CRC = 0xac3c9992 --->
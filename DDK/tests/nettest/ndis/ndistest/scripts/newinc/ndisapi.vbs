'==========================================================================
' NAME:     NdisAPI.vbs
'
' AUTHOR:   Omkumar Bhatt , Microsoft Corp.
' DATE  :   4/17/2003
'
' COMMENT:  This script contains functions specific to NDIS API tests
'			using ndistest6.sys
'==========================================================================
Option Explicit


Function Initialize_APITest()
   Set oLog = new CLog
   '
   ' Storing global log pointer for backward
   ' compatability with older scripts
   Set oNDTLog = oLog.LogPtr
   
   oLog.Mask = LOG_FAILURE Or LOG_WARNING
   
End Function



Function Terminate_APITest()
   oLog.LoggingComplete = True
   Set oLog = Nothing
End Function          

Function vbCreateNdisAPIOpen(oInfoAdapter)
	Dim oTestCard,oTestOpen
	Dim Status

	Set oTestCard = oNDTApi6.CreateAdapter(oInfoAdapter)
	Set oTestOpen = oTestCard.CreateOpen(0)

	Status = oTestOpen.NdisOpen(0)
	If (Status <> 0) Then
	  Call oLog.Failed("NDISAPI Open Object Creation Failed", 88888)
	  set vbCreateNdisAPIOpen = Nothing
	Else
	  oLog.Write "Successfully created NDISAPI Open Object"
	  set vbCreateNdisAPIOpen = oTestOpen
	End If

End Function

Function vbFreeNdisAPIOpen(oOpen)
	Dim Status
	Status = oOpen.NdisClose
	If (Status <> 0) Then
	  Call oLog.Failed("NDISAPI Open NdisClose Failed", 88888)
	End If
End Function
	
Function PrintNetBufferList(oTestOpen,oNetBufferList)

Dim NBufferList, NBuffer, MDLList, Mdl
Dim MdlSize, NBDataLength, NBDataOffset

set NBufferList = oNetBufferList.NBufferList
For Each NBuffer in NBufferList
	NBDataLength = CLng(NBuffer.DataLength(oTestOpen))
	NBDataOffset = CLng(NBuffer.DataOffset(oTestOpen))
	oLog.Write("NetBuffer DataLength : " & NBDataLength)
	oLog.Write("NetBuffer DataOffset : " & NBDataOffset)
	set MDLList = NBuffer.MDLList
	For each Mdl in MDLList
		MdlSize = CLng(Mdl.Size(oTestOpen))
		oLog.Write("    MDL Size : " & MdlSize)
	Next
    NBuffer.DeleteMDLList
Next

Set NBufferList = Nothing
Set NBuffer = Nothing
Set MDLList = Nothing
Set Mdl = Nothing

End Function

Function PrintNetBuffer(oTestOpen, oNetBuffer)

Dim MDLList, Mdl
Dim MdlSize, NBDataLength, NBDataOffset

NBDataLength = CLng(oNetBuffer.DataLength(oTestOpen))
NBDataOffset = CLng(oNetBuffer.DataOffset(oTestOpen))

oLog.Write("NetBuffer DataLength : " & NBDataLength)
oLog.Write("NetBuffer DataOffset : " & NBDataOffset)
set MDLList = oNetBuffer.MDLList
For each Mdl in MDLList
	MdlSize = CLng(Mdl.Size(oTestOpen))
	oLog.Write("    MDL Size : " & MdlSize)
Next

Set MDLList = Nothing
Set Mdl = Nothing

End Function

Function GetCheckedNDISSetting
   Dim DriverName, Size, TimeStamp, Version, Checked

   DriverName = "ndis.sys"
   oNDTSupp.DriverInfo DriverName,Size,TimeStamp,Version,Checked
   if (Checked = 0) Then
      ' Free NDIS, dont skip invalid tests
      GetCheckedNDISSetting = FALSE
   Else
      ' Skip invalid tests
      GetCheckedNDISSetting = TRUE
   End If
End Function


'<!-- CRC = 0xf6bfc57a --->
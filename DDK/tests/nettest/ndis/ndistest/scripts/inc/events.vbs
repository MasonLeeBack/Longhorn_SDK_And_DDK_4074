'==========================================================================
' NAME: 	Events.vbs
'
' AUTHOR: 	David Harding , Microsoft
' DATE  : 	12/19/2000
'
' COMMENT: 	This script defines common events that are associated with
'			our COM dll's
'
'==========================================================================
Option Explicit

'//////////////////////////////////////////////////////////////////////////////
' DLL:			NDInfo
'
' Event:		Teminate()
'
' Description:	Called by NDInfo to tell the script to terminate. 
'//////////////////////////////////////////////////////////////////////////////
Sub oNDInfo_Terminate(szMessage)
	
	WScript.Quit
	
End Sub

'<!-- CRC = 0xb052e363 --->
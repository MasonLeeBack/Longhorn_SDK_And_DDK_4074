Option Explicit

Const WBEM_ERR_NO_ERROR                = &H00000000&     ' Call was successful
Const WBEM_ERR_ACCESS_DENIED           = &H80041003&     ' Current user does not have permission to view the result set. 
Const WBEM_ERR_FAILED                  = &H80041001&     ' Unspecified error. 
Const WBEM_ERR_INVALID_PARAMETER       = &H80041008&     ' Invalid parameter was specified. 
Const WBEM_ERR_INVALID_QUERY           = &H80041017&     ' Query syntax is not valid. 
Const WBEM_ERR_INVALID_QUERY_TYPE      = &H80041018&     ' Requested query language is not supported. 
Const WBEM_ERR_OUT_OF_MEMORY           = &H80041006&     ' Not enough memory to complete the operation. 


' Creating a dictionary of NDIS_STATUS's so we can print the status name in the logs
Public Function vbGetWMIError(byval nError)
Dim oError   : Set oError = CreateObject("Scripting.Dictionary")

   oError.Add WBEM_ERR_NO_ERROR,             "WBEM_ERR_NO_ERROR"
   oError.Add WBEM_ERR_ACCESS_DENIED,        "WBEM_ERR_ACCESS_DENIED"
   oError.Add WBEM_ERR_FAILED,               "WBEM_ERR_FAILED"
   oError.Add WBEM_ERR_INVALID_PARAMETER,    "WBEM_ERR_INVALID_PARAMETER"
   oError.Add WBEM_ERR_INVALID_QUERY,        "WBEM_ERR_INVALID_QUERY"
   oError.Add WBEM_ERR_INVALID_QUERY_TYPE,   "WBEM_ERR_INVALID_QUERY_TYPE"
   oError.Add WBEM_ERR_OUT_OF_MEMORY,        "WBEM_ERR_OUT_OF_MEMORY"
    
   If(oError.Exists(nError)) Then
      vbGetWMIError = oError.Item(nError)
   Else
      vbGetWMIError = "UNKNOWN_ERROR " & "(0x" & Hex(nError) & ")"
   End If

End Function
'<!-- CRC = 0xa8f97992 --->
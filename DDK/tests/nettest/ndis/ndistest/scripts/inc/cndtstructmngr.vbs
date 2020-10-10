Option Explicit
Dim oNDTStruct : Set oNDTStruct = New CNDTStructMngr

'================================================================================================='
'/**
' This class provides wrapper function around the NDTStruct object manager
' @author
' David Harding
' @date
' 7/1/2003
' */
Class CNDTStructMngr

   Private m_structMngr
   
   '================================================================================================='
   Public Sub Class_Initialize()
      
      Set m_structMngr = CreateObject("NDTStructs.ObjManager.1")
      
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
      
      Set m_structMngr = Nothing
      
   End Sub
   
   '================================================================================================='
   '/**
   ' This internal (Private) function is called by all vbCreateObjectXXX functions to verify that the newly create structure
   ' object implements the required property and methods. Structure objects must support specific 
   ' properties and methods in order to operate within the framework correctly
   ' @params
   ' !object   Structure object to be validated
   ' @returns
   ' True if the object supports the required properties and methods, else returns False 
   ' */ 
   Private Function vbVerifyStructure(byval struct)
   Dim retval : retval = Empty
      
      vbVerifyStructure = True
      
      On Error Resume Next
         
         Do
            If(IsObject(struct) = False) Then
               MsgBox "Structure paramter is not an object (VarType = " & VarType(struct) & ")", vbExclamation Or vbOkOnly, "Unsupported Type"
               vbVerifyStructure = False
               Exit Do
            End If
         
            retval = struct.BytesAllocated
            If(Err.number <> 0) Then
               MsgBox "Structure object " & TypeName(struct) & " does not support BytesAllocated property", vbExclamation Or vbOkOnly, "Unsupported Property"
               vbVerifyStructure = False
               Exit Do
            End If
            
            retval = struct.SizeOf
            If(Err.number <> 0) Then
               MsgBox "Structure object " & TypeName(struct) & " does not support SizeOf property", vbExclamation Or vbOkOnly, "Unsupported Property"
               vbVerifyStructure = False
               Exit Do
            End If
                     
         Loop While(False)
         
      On Error Goto 0
      
   End Function

   '================================================================================================='
   Public Function vbStructureToArray(byref struct, byref buffer)
   ReDim buffer(struct.BytesAllocated) 
      
      vbStructureToArray = False
      
      ' Verify the structure object supports the required properties and methods
      If(vbVerifyStructure(struct) = False) Then
         Exit Function
      End If
      
      If(m_structMngr.ConvertToArray(struct, buffer) = False) Then
            oLog.Failed "vbStructureToArray: oObjMemManager.ConvertToArray() failed", 88888
            Exit Function
      End If
      
      vbStructureToArray = True
         
   End Function

   '================================================================================================='
   Public Function vbArrayToStructure(byval buffer, byref struct)
      
      vbArrayToStructure = False
     
      ' Verify the structure object supports the required properties and methods
      If(vbVerifyStructure(struct) = False) Then
         Exit Function
      End If
      
      If(m_structMngr.ConvertToBuffer(buffer, struct) = False) Then
         oLog.Failed "vbArrayToStructure: oObjMemManager.ConvertToBuffer() failed", 88888
         Exit Function
      End If
      
      vbArrayToStructure = True
      
   End Function

   '================================================================================================='
   Public Function vbFreeStructure(byref struct)
      
      vbFreeStructure = False
      
      ' Verify the structure object supports the required properties and methods
      If(vbVerifyStructure(struct) = False) Then
         Exit Function
      End If
         
      If(m_structMngr.Free(struct) = False) Then
         oLog.Failed "vbFreeStructure: Failed to free memory for " & TypeName(struct), 88888
         Exit Function
      End If
      
      vbFreeStructure = True
      
   End Function

   '================================================================================================='
   Public Function vbAllocateStructure(byval size, byref struct)
      
      vbAllocateStructure = False
      
      ' Verify the structure object supports the required properties and methods
      If(vbVerifyStructure(struct) = False) Then
         Exit Function
      End If
      
      If(m_structMngr.Allocate(size, struct) = False) Then
         oLog.Failed "vbAllocateStructure: Failed to allocate memory for " & TypeName(struct), 88888
         Exit Function
      End If
      
      vbAllocateStructure = True
      
   End Function

   '================================================================================================='
   '/**
   ' This function is called to create a structure object, the newly create structure object will have
   ' it's internal structure allocate to the sizeof() the structure it represents. 
   ' @params
   ' !string   Name of the structure object as defined by the progid
   ' @returns
   ' A reference to the structure object if successful, else returns Nothing
   ' @example
   ' Set obj = vbCreateStructure("Dot11RateSet")
   ' If(obj Is Nothing) Then
   '    Handle Failure
   ' End If
   ' */
   Public Function vbCreateStructure(byval name)
   Dim struct : Set struct   = Nothing
   Dim progID : progID       = "NDTStructs." & name & ".1"
     
      Set vbCreateStructure = Nothing
     
      Do
      
         ' Create the structure object from the progID
         Set struct = CreateObject(progID)
         If(struct Is Nothing) Then
            oLog.Failed "vbCreateStructure: Failed to create structure object " & progID, 88888
            Exit Do
         End If
         
         ' Verify the structure object supports the required properties and methods
         If(vbVerifyStructure(struct) = False) Then
            Exit Do
         End If
         
         ' Preallocate the structure to sizeof()
         If(vbAllocateStructure(struct.SizeOf, struct) = False) Then
            Exit Do
         End If
                 
         Set vbCreateStructure = struct
      
      Loop While(False)
           
   End Function

   '================================================================================================='
   Public Function vbCreateStructureAndAllocate(byval name, byval size, byval UseSizeOf)
   Dim struct  : Set struct   = Nothing
   Dim length  : length       = 0

      Set vbCreateStructureAndAllocate = Nothing
      
      Do
      
         Set struct = vbCreateStructure(name)
         If(struct Is Nothing) Then
            Exit Do
         End If
         
         If(UseSizeOf = True) Then
            length = CLng(struct.SizeOf) + CLng(size)
         Else
            length = size
         End If
         
         If(vbAllocateStructure(length, struct) = False) Then
            Exit Do
         End If
         
         Set vbCreateStructureAndAllocate = struct
      
      Loop While(False)
           
   End Function

   '================================================================================================='
   'Public Function vbCreateStructureAndFree(byval name)
   'Dim struct : Set struct = Nothing
   '  
   '   Set vbCreateStructureAndFree = Nothing
   '   
   '   Do
   '   
   '      Set struct = vbCreateStructure(name)
   '      If(struct Is Nothing) Then
   '         Exit Do
   '      End If
   '              
   '      If(vbFreeStructure(struct) = False) Then
   '         Exit Do
   '      End If
   '      
   '      Set vbCreateStructureAndFree = struct
   '     
   '   Loop While(False)
   '   
   'End Function

   '================================================================================================='
   '/**
   ' This function is called to print the structure objects internal data structure, if the object
   ' supported the ToString() method. The function will call the Object Manager passing in the structure
   ' object, the object manager will then invoke the ToString() method of the structure object to 
   ' get a formated string of the internal structure and return it to the script to print in the log.
   ' @params
   ' !object   Structure object the will return the string
   ' @returns
   ' A string representation of the internal data structure if ToString() is supported, else a zero length string
   ' @example
   ' vbPrintStructure(obj)
   ' */
   Public Function vbPrintStructure(byval struct)
   Dim text : text = ""
      
      ' Verify the structure object supports the required properties and methods
      If(vbVerifyStructure(struct) = False) Then
         Exit Function
      End If
           
      text = m_structMngr.ToString(struct)
      
      oLog.Write(text)
      
   End Function
   
End Class
'<!-- CRC = 0x84e6bc0d --->
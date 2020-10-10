Option Explicit

'
' CLASS Database Manager
' This class creates and manupilates the dictionary-based
' databases that we construct from the db file on disk
'
Class CDatabaseManager
   Dim oDB
   Dim TagArray
   Dim TagArraySize
   Dim strFileName
   Private Sub Class_Initialize
      Set oDB = Nothing
   End Sub

   Private Sub Class_Terminate
      Set oDB = Nothing
   End Sub

   Public Property Let DBFile (p_strFileName)
      strFileName = p_strFileName
   End Property

   Public Function FillDBFromFile (ByRef p_oDB, ByVal p_TagArray, ByVal p_TagArraySize)
      Dim oFileReader

      Set oDB = p_oDB
      TagArray = p_TagArray
      TagArraySize = p_TagArraySize - 1

      ' Create and open file for reading
      Set oFileReader = new FileReader

      If not oFileReader.Open (strFilename) Then
         ' Unable to open file
         FillDBFromFile = False
         Exit Function
      End If

      FillDBFromFile = ParseDBFile (oFileReader)

   End Function


   Public Function ParseDBFile (oFileReader)
      Dim LineRead
      Dim oStr

      ' Assume failure
      ParseDBFile = False

      Set oStr = new StringProcessor

      Dim BlockActive
      BlockActive = True
      Do
         LineRead = oFileReader.ReadLine()

         ' Read the entire stream
         If IsNull (LineRead) Then
            Set oFileReader = Nothing
            Exit Do
         End If

         LineRead = Trim (LineRead)    ' remove leading & trailing whitespaces

         If LineRead = "" Then
            ' A blank line so do nothing
         Else
            ' We want to find patterns in the line read
            oStr.SearchString = LineRead

            ' Check if its a tag (signified by expression "[.*")
            If (oStr.StartsWith ("'")) Then
               ' This is a remark so just do nothing!
            ElseIf (oStr.StartsWith ("\[")) Then
               if (Not ProcessTagLine (LineRead, BlockActive)) Then
                  Call oLog.Failed ("Possible syntax error in a tag on line " & oFileReader.Line, 88888)
                  Exit Function
               End If
            ElseIf (BlockActive) Then    ' It is a db entry
               If Not ProcessDataLine (LineRead) Then
                  Call oLog.Failed ("Possible syntax error on line " & oFileReader.Line, 88888)
               End If
            End If
         End If
      Loop While (True)

      ' If here then succeeded
      ParseDBFile = True
   End Function


   Private Function ProcessTagLine (Tag, BlockActive)
      Dim oStr

      ' This is set true so that we do not need special conditions below
      BlockActive = True

      ' Assume failure
      ProcessTagLine = False

      Set oStr = new StringProcessor
      oStr.SearchString = Tag

      If oStr.StartsWith ("\[Database") Then
         ' If here, then this is a tag defining start of a database
         Dim Token, bEquality, bFound, nIndex
         Dim TagKeyName, TagKeyValue, TagRegExp

         For nIndex = 0 To TagArraySize
            ' Get the name the key and the value it should be
            TagKeyName = TagArray(nIndex, 0)
            TagKeyValue = "," & TagArray(nIndex, 1) & ","

            ' Obtain the regular expression to be used for matching the key
            TagRegExp = oDB.TagRegExp(TagKeyName)

            Token = oStr.ExtractTagToken (TagRegExp, bEquality)
            If Not IsNull (Token) Then
               bFound = False

               If (InStr(Token, ",ALL,") <> 0) Then
                  bFound = True
               ElseIf (InStr(Token, TagKeyValue) <> 0) Then
                  bFound = True
               End If

               If (bEquality) Then
                  ' Okay, the list was of all valid values
                  If (bFound And BlockActive) Then
                     ' And our value was listed. So, currently the block is active
                     BlockActive = True
                  Else
                     BlockActive = False
                     Exit For
                  End If
               Else
                  ' List is of all invalid values
                  If (Not bFound And BlockActive) Then
                     ' And our value was not found, so the block is active
                     BlockActive = True
                  Else
                     BlockActive = False
                     Exit For
                  End If
               End If
            Else
               oLog.Write ("No " & TagKeyName & " tag in the database")
               Exit Function
            End If
         Next

      ElseIf oStr.StartsWith ("\[/DATABASE") Then
         ' This is end of the database! No more adding of data
         BlockActive = False
      End If

'      If (BlockActive) Then
'         MsgBox "Block Active "  & Tag
'      Else
'         MsgBox "Block InActive "  & Tag
'      End If
      ProcessTagLine = True

   End Function


   Private Function ProcessDataLine (data)
      Dim oStr, nElements, ArrElements()

      ' Assume failure
      ProcessDataLine = False

      Set oStr = new StringProcessor
      oStr.SearchString = data

      Dim Pattern
      ' Obtain the pattern that would be used for extracting the elements
      Pattern = oDB.EntryRegExp (nElements)

      ' Adjust our data array size to be the number of strings to be returned
      ReDim ArrElements(nElements)
      If (Not oStr.ExtractDBEntries (Pattern, ArrElements, nElements)) Then
         Exit Function
      Else
         ProcessDataLine = True
      End If

      ' Add the information to the database
      Call oDB.CreateEntry (ArrElements, nElements)

   End Function

End Class

'
' CLASS Database Reader
' This class creates and manupilates the dictionary-based
' databases that we can read db lines from the a disk file
'
Class CDatabaseReader
   Dim oFileReader
   Dim oStrProc
   Dim BlockActive
   Dim TagArray
   Dim TagArraySize

   Private Sub Class_Initialize
      Set oFileReader = Nothing
      Set oStrProc = new StringProcessor
      BlockActive = False
   End Sub

   Private Sub Class_Terminate
      Set oStrProc = Nothing
      Set oFileReader = Nothing
   End Sub

   Public Function OpenDB(ByVal strFileName, ByVal p_TagArray, ByVal p_TagArraySize)

      ' Create and open file for reading
      Set oFileReader = new FileReader
      TagArray = p_TagArray
      TagArraySize = p_TagArraySize - 1

      If not oFileReader.Open (strFileName) Then
         ' Unable to open file
         OpenDB = False
         Exit Function
      End If

      OpenDB = True
   End Function

   Public Function CloseDB
      Set oFileReader = Nothing
      CloseDB = True
   End Function

   Public Function ReadDBLine (oDBEntry)
      Dim LineRead

      ' Assume failure
      ReadDBLine = False

      Do
         LineRead = oFileReader.ReadLine()

         ' Read the entire stream
         If IsNull (LineRead) Then
            ' Returning false
            Exit Function
         End If

         LineRead = Trim (LineRead)    ' remove leading & trailing whitespaces

         If LineRead = "" Then
            ' A blank line so do nothing
         Else
            ' We want to find patterns in the line read
            oStrProc.SearchString = LineRead

            ' Check if its a tag (signified by expression "[.*")
            If (oStrProc.StartsWith ("'")) Then
               ' This is a remark so just do nothing!
            ElseIf (oStrProc.StartsWith ("\[")) Then
               if (Not ProcessTagLine (LineRead, BlockActive)) Then
                  Call oLog.Failed ("Possible syntax error in a tag on line " & oFileReader.Line, 88888)
                  Exit Function
               End If
            ElseIf (BlockActive) Then    ' It is a db entry
               If Not ProcessDataLine (LineRead, oDBEntry) Then
                  Call oLog.Failed ("Possible syntax error on line " & oFileReader.Line, 88888)
                  Exit Function
               Else
                  ' We just read a line from the data base, return to caller
                  ' to let it do processing
                  Exit Do
               End If
            End If
         End If
      Loop While (True)

      ' If here then succeeded
      ReadDBLine = True
   End Function


   Private Function ProcessTagLine (Tag, ByRef BlockActive)
      ' This is set true so that we do not need special conditions below
      BlockActive = True

      ' Assume failure
      ProcessTagLine = False

      oStrProc.SearchString = Tag

      If oStrProc.StartsWith ("\[Database") Then
         ' If here, then this is a tag defining start of a database
         Dim Token, bEquality, bFound, nIndex
         Dim TagKeyName, TagKeyValue, TagRegExp

         For nIndex = 0 To TagArraySize
            ' Get the name the key and the value it should be
            TagKeyName = TagArray(nIndex, 0)
            TagKeyValue = "," & TagArray(nIndex, 1) & ","

            ' Obtain the regular expression to be used for matching the key to its value
            TagRegExp = TagKeyName & "([=|!])=(\S+[^ ;\]])+"

            Token = oStrProc.ExtractTagToken (TagRegExp, bEquality)
            If Not IsNull (Token) Then
               bFound = False

               If (InStr(Token, ",ALL,") <> 0) Then
                  bFound = True
               ElseIf (InStr(Token, TagKeyValue) <> 0) Then
                  bFound = True
               End If

               If (bEquality) Then
                  ' Okay, the list was of all valid values
                  If (bFound And BlockActive) Then
                     ' And our value was listed. So, currently the block is active
                     BlockActive = True
                  Else
                     BlockActive = False
                     Exit For
                  End If
               Else
                  ' List is of all invalid values
                  If (Not bFound And BlockActive) Then
                     ' And our value was not found, so the block is active
                     BlockActive = True
                  Else
                     BlockActive = False
                     Exit For
                  End If
               End If
            Else
               oLog.Write ("No " & TagKeyName & " tag in the database")
               Exit Function
            End If
         Next

      Else 'If oStrProc.StartsWith ("\[/DATABASE") Then
         ' This is end of the database! No more processing of data
         BlockActive = False
      End If

'      If (BlockActive) Then
'         MsgBox "Block Active "  & Tag
'      Else
'         MsgBox "Block InActive "  & Tag
'      End If
      ProcessTagLine = True

   End Function


   Private Function ProcessDataLine (Data, oDBEntry)
      Dim nElements, ArrElements()

      ' Assume failure
      ProcessDataLine = False

      oStrProc.SearchString = data

      Dim Pattern
      ' Obtain the pattern that would be used for extracting the elements
      Pattern = oDBEntry.EntryRegExp (nElements)

      ' Adjust our data array size to be the number of strings to be returned
      ReDim ArrElements(nElements)
      If (Not oStrProc.ExtractDBEntries (Pattern, ArrElements, nElements)) Then
         Exit Function
      Else
         ProcessDataLine = True
      End If

      ' Fill the data entry object with the information
      Call oDBEntry.FillEntry (ArrElements, nElements)
   End Function

End Class


'
' CLASS FileReader
'
' This class will open an ASCII file for reading
' The class interface can be easily extended to
' give more serives associated with files. Simply
' add more properties and/or methods to the class
' to make it writable or get file attributes etc.
'

Class FileReader
   Dim mFile
   Dim mFileReader

   Sub Class_Initialize

   End Sub

   Sub Class_Terminate
      call close()
   End Sub

   Property Get Line ()
      Line = mFileReader.Line
   End Property

   Public Function Open (filename)
      Dim FileSys
      On Error Resume Next

      Open = False      ' Assume failure

      Set FileSys = CreateObject ("Scripting.FileSystemObject")

      If err.number > 0 Then
         Call oLog.Failed ("Unable to create Scripting.FileSystemObject", 88888)
         WScript.Quit
      End If

      If Not FileSys.FileExists (filename) Then
         Call oLog.Failed ("The file " & filename & " could not be opened", 88888)
         On Error Goto 0
         Exit Function
      End If

      Set mFile = FileSys.GetFile (filename)

      ' the 1 signifies for reading and 0 signifies ASCII
      Set mFileReader = mFile.OpenAsTextStream (1, 0)

      open = True

      If Err.number > 0 Then
         Call oLog.Failed ("Unable to open file " & filename, 88888)
         WScript.Quit
      End If
      On Error goto 0
   End Function


   Public Function Close ()
      On Error Resume Next
      If (Not IsNull (mFileReader) And Not IsEmpty (mFileReader)) Then
         mFileReader.close
         mFileReader = null      ' To signify that file is now closed
      End If
      If err.number > 0 Then
         oLog.Write "Unable to close file"
      End If
      On Error goto 0
   End Function


   ' Function reads one line from the stream. Returns NULL if stream has ended
   Public Function ReadLine
      On Error Resume Next
      If (Not mFileReader.AtEndOfStream) Then
         ReadLine = mFileReader.ReadLine
      Else
         ReadLine = Null
      End If
      If err.number > 0 Then
         Call oLog.Failed ("Unable to read from file", 88888)
         WScript.Quit
      End If
      On Error goto 0
   End Function
End Class

'
' CLASS StringProcessor
'

Class StringProcessor
    ' The string we are searching in
    Dim mSearchString

    ' This is the string used for all the string obtaining and similar functions
    Dim oEntryObject

    ' The RegExp object
    Dim mRegExp

    ' This var contains the matches of the last query executed
    Dim mMatches

    Sub Class_Initialize
        On Error Resume Next
        Set mRegExp = new RegExp
        mRegExp.IgnoreCase = True
        mMatches = FALSE
        If err.number > 0 Then
            Call oLog.Failed ("StringProcessor initialization unsuccessful", 88888)
        End If
        On Error goto 0
    End Sub

    Sub Class_Terminate
        Set mRegExp = Nothing
    End Sub

    Property Let SearchString (newVal)
        mSearchString = newVal
    End Property

    Property Get Matches
        Set Matches = mMatches
    End Property


    Public Function ExtractTagToken (RegExpPattern, bEquality)
        on Error Resume Next
        mRegExp.Global = False

        mRegExp.Pattern = RegExpPattern

        Set mMatches = mRegExp.Execute (mSearchString)

        If mMatches.Count > 0 Then          ' If there was a match found
            Dim Match
            Set Match = mMatches.Item (0)

            If (Match.SubMatches (0) = "=") Then
               bEquality = TRUE
            Else
               bEquality = FALSE
            End If

            ExtractTagToken = "," & Match.SubMatches(1) & ","
        Else
            ExtractTagToken = NULL
        End If
        If err.number > 0 Then
            oLog.Write ("Unable to parse tag token from database file")
            WScript.Quit
        End If
        On Error goto 0
    End Function

    ' This function is called when DB contains unallowed function name & error msg
    Public Function ExtractDBEntries (ByVal RegExpPattern, ByRef ArrElements, ByVal NumElements)
        On Error Resume Next
        mRegExp.Global = True

        ' We know what are the maximum number of entries we expect in the tag field
        mRegExp.Pattern = RegExpPattern
        Set mMatches = mRegExp.Execute (mSearchString)

        If mMatches.Count = 1 Then          ' If there was a match found
            Dim Match, nIndex

            Set Match = mMatches.Item(0)

            ' Fill the array with the extracted information
            For nIndex = 0 To NumElements-1
               ArrElements(nIndex) = Match.SubMatches(nIndex)
            Next

            ExtractDBEntries = True
        Else
            ' Two matches not found
            oLog.Write (mSearchString)
            oLog.Write ("Found invalid entry line in the database")
            ExtractDBEntries = False
        End If

        If err.number > 0 Then
            oLog.Write ("Unable to parse data entries from database")
            WScript.Quit
        End If
        On Error goto 0
    End Function

    Public Function StartsWith (SearchPattern)
        On Error Resume Next
        mRegExp.Global = False
        mRegExp.Pattern = "^" & SearchPattern & ".*"

        ' Run the query
        Set mMatches = mRegExp.Execute (mSearchString)

        If mMatches.Count > 0 Then          ' If there was a match found
            Dim Match
            For Each Match in mMatches
                If Match.FirstIndex = 0 Then  ' and match was at the first character i.e. start of string
                    StartsWith = True          ' then line starts with this pattern
                    Exit For    ' interested in only first match
                Else
                    StartsWith = False
                    Exit For    ' interested in only first match
                End If
            Next
        Else
            StartsWith = False
        End If

        If err.number > 0 Then
            oLog.Write ("Unable to parse database")
            WScript.Quit
        End If
        On Error goto 0
    End Function

    Public Function GetCount (strPattern)
        On Error Resume Next
        mRegExp.Global = True
        mRegExp.Pattern = strPattern

        ' Run the query
        Set mMatches = mRegExp.Execute (mSearchString)

        GetCount = mMatches.Count

        If err.number > 0 Then
            oLog.Write ("Unable to execute parsing query on search string")
            WScript.Quit
        End If
        On Error goto 0
    End Function
End Class


'<!-- CRC = 0x39f067e3 --->
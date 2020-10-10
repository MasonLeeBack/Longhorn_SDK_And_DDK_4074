Function GetUnimodemLog(LogFile, TimeStarted)

Dim fso, ts,  NewLine
Dim hr, min, sec, today, mnth

hr = Hour(TimeStarted)
min = Minute(TimeStarted)
sec = Second(TimeStarted)
today = day(TimeStarted)
mnth = Month(TimeStarted)

Set fso = CreateObject("Scripting.FileSystemObject")
Const ForReading = 1
Const TriStateTrue = -1
NewLine = Chr(10)

if fso.FileExists(LogFile) = False Then
  GetUniModemLog = ""
  Exit Function
End If 

Dim CurLine, LoggingText
Dim lghr, lgmin, lgsec, temp, time, tpsec, strdate
Dim nhr, nmin, nsec
Dim timestmp, curtimestmp, curday, curmnth
Dim dashpos
timestmp = (hr*3600) + (min*60) + sec

Dim RegEx, retval
Set RegEx = new RegExp
RegEx.Pattern = "[0-9]{2}-[0-9]{2}-[0-9]{4} [0-9]{2}:[0-9]{2}:[0-9]{2}" 'Date Time Matching Pattern


Set ts = fso.OpenTextFile(LogFile, ForReading, False, TriStateTrue)
Do While Not ts.AtEndOfStream
  CurLine = ts.ReadLine

  retval = RegEx.Test(CurLine)
  if retval then
  
    temp = Split(CurLine, " ", -1, 1)

    strdate = Split(temp(0), "-", -1, 1)
    curday = CInt(strdate(1))
    curmnth = CInt(strdate(0))
 
    time = Split(temp(1), ":", -1 , 1)
    lghr = time(0)
    lgmin = time(1)
    tpsec = Split(time(2), ".", -1, 1)
    lgsec = tpsec(0)

    nhr = CInt(lghr)
    nmin = CInt(lgmin)
    nsec = CInt(lgsec)

    curtimestmp = (nhr*3600) + (nmin*60) + nsec

    if (curtimestmp >= timestmp) and (curmnth >= mnth) and (curday >= today) Then
      LoggingText = LoggingText & FixCharacters(CurLine) & NewLine
    End If
  End if
Loop


ts.Close
GetUnimodemLog = LoggingText

End Function

Function FixCharacters (InString)
   Dim OutString
   Dim TempChar
   Dim InLen
   Dim i
   
   FixCharacters = ""

   ' Obtain the number of characters in input string
   InLen = Len(InString)
   
   For i = 1 To InLen
      ' Extract the particular character and store its code
      TempChar = Mid(InString, i, 1)

      ' If the string starts with a 00 (instead of ending with it),
      ' we replace the character to be a space
      If (AscB(TempChar) = 0) Then
         TempChar = " "
      End If

      ' Reattach the character
      FixCharacters = FixCharacters & TempChar
   Next
   
End Function



'<!-- CRC = 0xd2ea42ef --->
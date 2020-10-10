Option Explicit
Dim gDbgTrace : Set gDbgTrace   = New CDbgTrace

' To enable script debug prints you must fist create the DbgTraceLevel DWORD below and then 
' set the value equal to the OR'd constants below. For example to enable Failure and Warning traces
' set DbgTraceLevel equal to the hex value of DBGTRACE _FAIL| DBGTRACE_WARN. The default value is DBGTRACE_FAIL
' if the registery value below is not found in the registry
Const DBGTRACE_REGISTRY       = "HKEY_CURRENT_USER\Software\Microsoft\NDTEST\CommonInfo\DbgTraceLevel"

Const DBGTRACE_FAIL           = &H00000001&
Const DBGTRACE_INFO           = &H00000002&
Const DBGTRACE_WARN           = &H00000004&
Const DBGTRACE_ENTER_EXIT     = &H00000008&      
Const DBGTRACE_BREAK          = &H00000010&

'################################################################################################'
Class CDbgTrace
   
   Private m_traceLevel
   Private m_routineName
   
   '=============================================================================================='
   Public Sub Class_Initialize()
   Dim shell   : Set shell = CreateObject("WScript.Shell")
   Dim result  : result    = ""

      m_traceLevel = DBGTRACE_FAIL Or DBGTRACE_ENTER_EXIT
    
      On Error Resume Next

      result = shell.RegRead(DBGTRACE_REGISTRY)
      If(Err.number <> 0) Then
         On Error Goto 0
         Exit Sub
      End If
       
      m_traceLevel = result
      
      On Error Goto 0

   End Sub
   
   '=============================================================================================='
   Public Sub Class_Terminate()
           
   End Sub
   
   '=============================================================================================='
   Public Sub DbgBreak()
      
      If((m_traceLevel And DBGTRACE_BREAK) = DBGTRACE_BREAK) Then
         Msgbox "Script stopped, press OK to continue",  vbExclamation Or vbOkOnly, "Debug Break"
      End If
      
   End Sub
   
   '=============================================================================================='
   Public Sub DbgEnter(byval text)
   Dim format : format = ""
      
      m_routineName = ""
      
      If((m_traceLevel And DBGTRACE_ENTER_EXIT) = DBGTRACE_ENTER_EXIT) Then
         m_routineName  = text
         format = "<u><font color='#8B008B'>" & text & " - Enter </font></u>"
         WriteToLog(format)
         Exit Sub
      End If
          
   End Sub
   
   '=============================================================================================='
   Public Sub DbgExit(byval text)
   Dim format : format = ""
      
      If(m_routineName = "") Then
         Exit Sub
      End If
      
      If((m_traceLevel And DBGTRACE_ENTER_EXIT) = DBGTRACE_ENTER_EXIT) Then
         format = "<u><font color='#8B008B'>" & m_routineName & " - Exit </font></u>"
         WriteToLog(format)
         Exit Sub
      End If
      
   End Sub
   
   '=============================================================================================='
   Public Sub DbgPrint(byval flag, byval text)
   Dim format : format = ""
   
      If((flag And m_traceLevel) = DBGTRACE_FAIL) Then
         format = text  
         WriteToLog(format)
         Exit Sub
      End If
      
      If((flag And m_traceLevel) = DBGTRACE_INFO) Then
         format = text  
         WriteToLog(format)
         Exit Sub
      End If
      
      If((flag And m_traceLevel) = DBGTRACE_WARN) Then
         format = text  
         WriteToLog(format)
         Exit Sub
      End If
      
   End Sub
     
   '=============================================================================================='
   Private Sub WriteToLog(byval text)
      oLog.Write(text)   
   End Sub
   
End Class
'<!-- CRC = 0xc602b9bb --->
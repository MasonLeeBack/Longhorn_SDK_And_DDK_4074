'================================================================================================='
'/**
'This class provides routines for writing to a log file using the logging object COM DLL/
'@author	David Harding (davhar)
'@date		4/13/2001
'*/
Option Explicit
Const SUCC_ERR = 0
Const FAIL_ERR	= 1
Const WARN_ERR	= 2

Const DO_NOTHING  = &H00000000
Const LOG_FAILURE = &H00000001
Const LOG_WARNING = &H00000002

Dim oLog, oNDTLog

Class CLog
    Private m_oLog
    Private m_nLogControl
    Private m_sDescription
    Private m_nErrorNumber
    Private m_nErrorCode
    Private m_nMask

    Sub Class_Initialize()

		m_nMask			= DO_NOTHING          ' set default to silence (no log or fails)
		m_nLogControl	= Empty

        Set m_oLog = oNDInfo.ScriptLog
        if(m_oLog Is Nothing) then
	    	MsgBox "Failed to create logging object", vbOkOnly or vbSystemModal, "Logging.vbs"
	    	WScript.Quit
	   	end if

	   	m_oLog.ScriptName	 		= WSCript.ScriptName
	   	m_oLog.ScriptFullName		= WScript.ScriptFullName

    End Sub

    Sub Class_Terminate()

    	If err.Number <> 0 then
            call m_oLog.Failed ("A VBScript run-time error has occured!", 22838)
        End If

    End Sub

    '================================================================================================='
    '/**
    '*/
    Property Get LogDirectory()
      LogDirectory = m_oLog.LogDirectory
    End Property

    '================================================================================================='
    '/**
    '*/
   	Property Let LoggingComplete(newVal)
   		m_oLog.LoggingComplete = newVal
   	End Property

    '================================================================================================='
    '/**
    '*/
    Public Sub SafePrint()
    	if m_nErrorNumber = FAIL_ERR And (m_nMask And LOG_FAILURE) Then
            call m_oLog.Failed(m_sDescription, m_nErrorCode)
        ElseIf m_nErrorNumber = WARN_ERR And (m_nMask And LOG_WARNING) Then
            m_oLog.Warned (m_sDescription)
        End If
   	End Sub

    '================================================================================================='
    '/**
    '*/
    Public Sub SafeFailed(sErrDesc, nErrCode)
        call SetFailure(sErrDesc, nErrCode)
        SafePrint()
     End Sub
    Public Sub SafeWarned(sErrDesc)
        SetWarning(sErrDesc)
        SafePrint()
    End Sub

    '================================================================================================='
    '/**
    '*/
   	Property Let Mask(newVal)
   		m_nMask = newVal
   	End Property
   	Property Get Mask()
   		Mask = m_nMask
   	End Property

    '================================================================================================='
    '/**
    '*/
   	Property Let ErrorCode(newVal)
   		m_nErrorCode = newVal
   	End Property
   	Property Get ErrorCode()
   		Mask = m_nErrorCode
   	End Property

    '================================================================================================='
    '/**
    '*/
   	Public Property Let Description(newVal)
   	    m_sDescription = newVal
   	End Property
    Public Property Get Description()
        Description = m_sDescription
   	End Property

   	'================================================================================================='
    '/**
    '*/
	Public Sub SetFailure(sErrDesc, nErrCode)
        m_sDescription = sErrDesc
        m_nErrorNumber = FAIL_ERR
        m_nErrorCode = nErrCode
	End Sub
    Public Sub SetWarning(sErrDesc)
    	m_sDescription = sErrDesc
        m_nErrorNumber = WARN_ERR
   	End Sub

    '================================================================================================='
    '/**
    '*/
    Public Property Get LogPtr()
        Set LogPtr = m_oLog
    End Property

    '================================================================================================='
    '/**
    '*/
    Public Sub Variation(sText)
        m_oLog.Variation(sText)
    End Sub

    '================================================================================================='
    '/**
    '*/
    Public Sub VariationEx(byval text, byval description)
      m_oLog.Variation(text)
      If(IsNull(description) = False) Then
         WriteDescription description
      End If
    End Sub

    '================================================================================================='
    '/**
    '*/
    Public Sub Write(sText)
        m_oLog.Write(sText)
    End Sub

    '================================================================================================='
    '/**
    '*/
    Public Sub Failed(sText, nErrCode)
    	call SetFailure(sText, nErrCode)
      	call m_oLog.Failed(sText, m_nErrorCode)
    End Sub

    '================================================================================================='
    '/**
    '*/
    Public Sub FailedEx(byval text, byval description, byval errorCode)
    	   SetFailure text, errorCode
      	m_oLog.Failed text, m_nErrorCode
      	If(IsNull(description) = False) Then
      	   WriteDescription description
      	End If
    End Sub

    '================================================================================================='
    '/**
    '*/
    Public Sub Warned(sText)
    	SetWarning(sText)
        m_oLog.Warned(sText)
    End Sub

    '================================================================================================='
    '/**
    '*/
    Public Sub WarnedEx(byval text, byval description)
      SetWarning(text)
      m_oLog.Warned(text)
      If(IsNull(description) = False) Then
         WriteDescription description
      End If
    End Sub

    '================================================================================================='
    '/**
    '*/
    Public Sub MaskWrite()
        Dim nBit
    	nBit = 1

    	if(m_nLogControl = Empty) then
    	    m_nLogControl			= m_oLog.OutputControl
    	    m_oLog.OutputControl	= (m_nLogControl AND (Not nBit))
    	end if
    End Sub

    '================================================================================================='
    '/**
    '*/
    Public Sub UnMaskWrite()
        if(not m_nLogControl = Empty) then
    	    m_oLog.OutputControl = m_nLogControl
            m_nLogControl = Empty
        end if
    End Sub

   '================================================================================================='
    '/**
    '*/
    Public Sub IsActive()
        if(m_oLog.LogActive = true) then
		    IsActive = true
	    else
		    IsActive = false
	    end if
    End Sub

    '================================================================================================='
    '/**
    '*/
    Private Sub WriteDescription(byval text)
      m_oLog.Write "<table width='100%'><td valign='top'><font size='2' color='#0000FF'><i>" & text & "</i></font></td></table>"
    End Sub

End Class

'<!-- CRC = 0x4418caa4 --->
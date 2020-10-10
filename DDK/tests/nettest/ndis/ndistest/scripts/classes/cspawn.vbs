
'/**
' * This class provides properties and methods for spawning multiple scripts.
' * @author
' * David Harding
' * @alias
' * davhar@microsoft.com
' * @date
' * 3/27/2002
' */
class CSpawn
    
    Private m_oShell
    Private m_nWindowStyle
    Private m_sDefaultDirectory
        
    Sub Class_Initialize() 
    
        m_nWindowStyle = 0
        Set m_oShell = WScript.CreateObject("WScript.Shell")
        
    End Sub
    
    Sub Class_Terminate()
        Set m_oShell = Nothing
    End Sub
    '/**
    ' * This property sets the default directory to use when launching the new script.
    ' * If this property is not set then the default directory for the scripting host is used.
    ' * Also, if the string does not end with '\' then it will be added.
    ' * @params
    ' * ! string The default directory to use when launching the new script.
    ' * @example
    ' * Obj.DefaultDirectory = "C:\foo"
    ' */
    Property Let DefaultDirectory(newVal)
    
        if(Right(newVal, 1) = "\") then
            m_sDefaultDirectory = newVal
        else
            m_sDefaultDirectory = newVal & "\"
        end if
        
    End Property
    
    '/**
    ' * This property returns the default directory that was previously set..
    ' * @return
    ' * The string value that was previously set, if no call was made to set this
    ' * property then a zero length string is returned.
    ' * @example
    ' * msgbox Obj.DefaultDirectory
    ' */
    Property Get DefaultDirectory
    
        DefaultDirectory = m_sDefaultDirectory
        
    End Property
    
    Property Let WindowStyle(newVal)
    
        m_nWindowStyle = newVal
        
    End Property
    
    Property Get WindowStyle
    
        WindowStyle = m_nWindowStyle
        
    End Property
    
    '/**
    ' * This method is used to launch the script. It can take a single script as an argument 
    ' * or an array of scripts. The string that contains the script name to be launched can
    ' * can also include command line parameters. For example "..\test.vbs /s"
    ' * @return
    ' * True if the script(s) were launched successfully, otherwise returns false.
    ' * @example
    ' * This example shows how to launch another script.
    ' * 
    ' * Obj.DefaultDirectory = "C:\foo"
    ' * bRetval = Obj.Spawn("test.vbs")
    ' */
    Function Spawn(ByVal vScript)
    Dim nIndex : nIndex = 0
            
        If(IsArray(vScript) = True) Then 
            For nIndex = 0 to UBound(vScript)
                Call m_oShell.Run(m_sDefaultDirectory & vScript(nIndex), m_nWindowStyle, False)
            Next
            Exit Function
        End If
        
        If(VarType(vScript) = vbString) Then
            Call m_oShell.Run(m_sDefaultDirectory & vScript, m_nWindowStyle, False)
            Exit Function
        End If
        
        Msgbox "Invalid argument type! Expecting string or array of strings", vbOkOnly Or vbExclamation, "Invalid Agument"        
        Spawn = False
        
    End Function
    
End Class
'<!-- CRC = 0x79922baf --->
Option Explicit

Const CSERVICEMGR_SERVICE_STOPPED           = &H00000001&
Const CSERVICEMGR_SERVICE_START_PENDING     = &H00000002&
Const CSERVICEMGR_SERVICE_STOP_PENDING      = &H00000003&
Const CSERVICEMGR_SERVICE_RUNNING           = &H00000004&
Const CSERVICEMGR_SERVICE_CONTINUE_PENDING  = &H00000005&
Const CSERVICEMGR_SERVICE_PAUSE_PENDING     = &H00000006&
Const CSERVICEMGR_SERVICE_PAUSED            = &H00000007&
Const CSERVICEMGR_SERVICE_UNKNOWN           = &H00000008&

Const CSERVICEMGR_STATUS_SUCCESS            = &H00000000&
Const CSERVICEMGR_STATUS_NOT_SUPPORTED      = &H00000001&


Class CServiceMgr
    
    Private m_oService
    Private m_sServiceName
    
    Public Sub Class_Initialize()
        
        Set m_oService = Nothing
        
    End Sub
    
    Public Sub Class_Terminate()
    
    End Sub
    
    '/**
    ' */
    Public Property Get DisplayName
        
        If(Validate() = False) Then
            Exit Property  
        End If
                
        DisplayName = m_oService.DisplayName
        
    End Property 
    
    '/**
    ' */
    Public Property Get ServiceType
        
        If(Validate() = False) Then
            Exit Property  
        End If
        
        ServiceType = m_oService.ServiceType
        
    End Property
    
    '/**
    ' */
    Public Property Get AcceptPause
        
        If(Validate() = False) Then
            Exit Property  
        End If
        
        AcceptPause = m_oService.AcceptPause
        
    End Property
    
    '/**
    ' */
    Public Property Get AcceptStop
        
        If(Validate() = False) Then
            Exit Property  
        End If
        
        AcceptStop = m_oService.AcceptStop
        
    End Property
    
    '/**
    ' */
    Public Property Get State
        
        If(Validate() = False) Then
            Exit Property  
        End If
               
        Select Case m_oService.State
        Case "Stopped"
            State = CSERVICEMGR_SERVICE_STOPPED
        Case "Start Pending"
            State = CSERVICEMGR_SERVICE_START_PENDING
        Case "Stop Pending"
            State = CSERVICEMGR_SERVICE_STOP_PENDING
        Case "Running"
            State = CSERVICEMGR_SERVICE_RUNNING
        Case "Continue Pending"
            State = CSERVICEMGR_SERVICE_CONTINUE_PENDING
        Case "Pause Pending"
            State = CSERVICEMGR_SERVICE_PAUSE_PENDING
        Case "Paused"
            State = CSERVICEMGR_SERVICE_PAUSED
        Case "Unknown"
            State = CSERVICEMGR_SERVICE_UNKNOWN
        End Select
               
    End Property
    
    '/**
    ' */
    Public Property Get StateString
        
        If(Validate() = False) Then
            Exit Property  
        End If
               
        StateString = m_oService.State
                       
    End Property
    
    '/**
    ' */
    Public Function AttachToService(sServiceName)
    Dim oSvcMgr : Set oSvcMgr = getobject("winmgmts:root\cimv2")
        
        m_sServiceName = sServiceName
        Set m_oService = oSvcMgr.get("win32_service='" & m_sServiceName & "'")
                       
    End Function
    
    '/**
    ' */
    Public Function StopService()
    Dim nTimeOut : nTimeOut = 0
    
        If(Validate() = False) Then
            Exit Function  
        End If
                
        m_oService.StopService()
                       
        do while(me.State() <> CSERVICEMGR_SERVICE_STOPPED)
    
            me.AttachToService(m_sServiceName)
            wscript.sleep 1000
            
            if(nTimeOut > 5) then
                Exit Function
            End if
            
            nTimeOut = nTimeOut + 1
            
        loop
        
        StopService = CSERVICEMGR_STATUS_SUCCESS
                                       
    End Function
    
    '/**
    ' */
    Public Function StartService()
    Dim nTimeOut : nTimeOut = 0
    
        If(Validate() = False) Then
            Exit Function  
        End If
        
        m_oService.StartService()
        
        do while(me.State() <> CSERVICEMGR_SERVICE_RUNNING)
    
            me.AttachToService(m_sServiceName)
            wscript.sleep 1000
            
            if(nTimeOut > 5) then
                Exit Function
            End if
            
            nTimeOut = nTimeOut + 1
            
        loop
        
        StartService = CSERVICEMGR_STATUS_SUCCESS
                               
    End Function
    
    '/**
    ' */
    Private Function Validate()
    
        If(IsObject(m_oService) = False) Then
            MsgBox "You must attach to a service before calling any properties or methods!", vbOkOnly Or vbExclamation, "CServiceMgr Error"
            Validate = False
        Else
            Validate = True
        End If
    
    End Function
       
End Class 

'
' This is test code only.
'
If(0) Then 
    Dim oSvcMgr : Set oSvcMgr   = New CServiceMgr
    Dim nRetval : nRetval       = 0
    
    oSvcMgr.AttachToService("ndisuio") 
    
    Msgbox "Stop"
    nRetval = oSvcMgr.StopService()
    If(Not nRetval = CSERVICEMGR_STATUS_SUCCESS) Then
        MsgBox "Failed To Stop Service"
    End If
    
    MsgBox oSvcMgr.StateString
    
    Msgbox "Start"
    nRetval = oSvcMgr.StartService
    If(Not nRetval = CSERVICEMGR_STATUS_SUCCESS) Then
        MsgBox "Failed To Start Service"
    End If
    
    MsgBox oSvcMgr.StateString
End If
'<!-- CRC = 0x3746e490 --->
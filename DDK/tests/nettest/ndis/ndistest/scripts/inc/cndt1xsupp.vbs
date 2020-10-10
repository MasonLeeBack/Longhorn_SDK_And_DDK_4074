'<!-- CRC = 0xe49b7735 -->
Option Explicit

Const WLAN_HANDSHAKE_TIMEOUT     = 5 'seconds
Const WLAN_DEFAULT_PMK_PASSWORD  = "0123456789"

Class CNDT1xSupp

   Private m_supplicant
   Private m_authenticationComplete
   Private m_addPairwiseKey
   Private m_addGroupKey
   Private m_isDeviceOpen
      
   '=============================================================================================='
   Sub Class_Initialize()
      
      Set m_supplicant = CreateObject("Ndt1xsupp.Supplicant.1")
            
      m_authenticationComplete   = False
      m_addPairwiseKey           = True
      m_addGroupKey              = True
          
   End Sub
   
   '=============================================================================================='
   Sub Class_Terminate()
   
      If(m_isDeviceOpen = True) Then
         Me.vbCloseDevice()
      End If
      
      Set m_supplicant = Nothing
         
   End Sub
      
   '================================================================================================='
   Public Property Let vbAddPairwiseKey(byval newVal)
      m_addPairwiseKey = newVal
   End Property
   
   '================================================================================================='
   Public Property Get vbAddPairwiseKey
      vbAddPairwiseKey = m_addPairwiseKey
   End Property
   
    '================================================================================================='
   Public Property Let vbAddGroupKey(byval newVal)
      m_addGroupKey = newVal
   End Property
   
   '================================================================================================='
   Public Property Get vbAddGroupKey
      vbAddGroupKey = m_addGroupKey
   End Property
   
   Public Property Get vbGroupKeyIndex
      vbGroupKeyIndex = m_supplicant.GroupKeyIndex
   End Property
   
   '================================================================================================='
   Public Function OnAuthenticationBeginHandler()

      m_authenticationComplete = False
      
   End Function
   
   '================================================================================================='
   Public Function OnAuthenticationCompleteHandler()

      m_authenticationComplete = True
      
   End Function
   
   '================================================================================================='
   Public Function OnAuthenticationFailedHandler()
      
      m_authenticationComplete = False
      
   End Function
   
   '================================================================================================='
   Public Function OnAddPairwiseKeyHandler()
            
      OnAddPairwiseKeyHandler = m_addPairwiseKey
      
   End Function
   
   '================================================================================================='
   Public Function OnAddGroupKeyHandler()
            
      OnAddGroupKeyHandler = m_addGroupKey
      
   End Function
   
   '=============================================================================================='
   Public Function vbOnAuthenticationBegin(byref handler, byval methodName)
      
      vbOnAuthenticationBegin = m_supplicant.OnAuthenticationBegin(handler, methodName)
      If(vbOnAuthenticationBegin = False) Then
         oLog.Write "vbOnAuthenticationBegin: OnAuthenticationBegin() failed"
      End If
      
   End Function
   
   '=============================================================================================='
   Public Function vbOnAuthenticationComplete(byref handler, byval methodName)
      
      vbOnAuthenticationComplete = m_supplicant.OnAuthenticationComplete(handler, methodName)
      If(vbOnAuthenticationComplete = False) Then
         oLog.Write "vbOnAuthenticationComplete: OnAuthenticationComplete() failed"
      End If
      
   End Function
   
   '=============================================================================================='
   Public Function vbOnAuthenticationFailed(byref handler, byval methodName)
      
      vbOnAuthenticationFailed = m_supplicant.OnAuthenticationFailed(handler, methodName)
      If(vbOnAuthenticationFailed = False) Then
         oLog.Write "vbOnAuthenticationComplete: OnAuthenticationFailed() failed"
      End If
      
   End Function
   
   '=============================================================================================='
   Public Function vbOnAddPairwiseKey(byref handler, byval methodName)
      
      vbOnAddPairwiseKey = m_supplicant.OnAddPairwiseKey(handler, methodName)
      If(vbOnAddPairwiseKey = False) Then
         oLog.Write "vbOnAddPairwiseKey: OnAddPairwiseKey() failed"
      End If
      
   End Function
   
   '=============================================================================================='
   Public Function vbOnAddGroupKey(byref handler, byval methodName)
      
      vbOnAddGroupKey = m_supplicant.OnAddGroupKey(handler, methodName)
      If(vbOnAddGroupKey = False) Then
         oLog.Write "vbOnAddGroupKey: OnAddGroupKey() failed"
      End If
      
   End Function
      
   '=============================================================================================='
   Public Function vbWaitForAuthenticationComplete(byval timeout)
   Dim count : count = 0
      
      vbWaitForAuthenticationComplete = False
            
      Do
         
         WScript.Sleep(timeout * 1000)
         
         count = count + 1
         
         If(count >= timeout) Then
            oLog.Write "Authentication did not complete in " & timeout & " seconds"
            Exit Function
         End If
         
      Loop While(m_authenticationComplete = False)
            
      vbWaitForAuthenticationComplete = True
        
   End Function
   
   '=============================================================================================='
   Public Function vbOpenDevice(byval guid)
      
      vbOpenDevice = False
      
      ' Set the PMK on the supplicant
      vbOpenDevice = Me.vbSetPassword(WLAN_DEFAULT_PMK_PASSWORD)
      If(vbOpenDevice = False) Then
         Exit Function
      End If  
      
      
      vbOpenDevice = m_supplicant.OpenDevice(guid)
      If(vbOpenDevice = False) Then
         oLog.Write "vbOpenDevice: OpenDevice() failed"
         Exit Function
      End If
      
      ' Register for suplicant events
      vbOpenDevice = Me.vbOnAuthenticationComplete(Me, "OnAuthenticationCompleteHandler")
      If(vbOpenDevice = False) Then
         Exit Function
      End If
      
      vbOpenDevice = Me.vbOnAuthenticationBegin(Me, "OnAuthenticationBeginHandler")
      If(vbOpenDevice = False) Then
         Exit Function
      End If
      
      vbOpenDevice = Me.vbOnAuthenticationFailed(Me, "OnAuthenticationFailedHandler")
      If(vbOpenDevice = False) Then
         Exit Function
      End If
      
      vbOpenDevice = Me.vbOnAddPairwiseKey(Me, "OnAddPairwiseKeyHandler")
      If(vbOpenDevice = False) Then
         Exit Function
      End If
      
      vbOpenDevice = Me.vbOnAddGroupKey(Me, "OnAddGroupKeyHandler")
      If(vbOpenDevice = False) Then
         Exit Function
      End If
                  
      m_isDeviceOpen = True
      
      vbOpenDevice = True
       
   End Function
   
   '=============================================================================================='
   Public Function vbCloseDevice()
   
      vbCloseDevice = m_supplicant.CloseDevice()
      If(vbCloseDevice = False) Then
         oLog.Write "vbCloseDevice: CloseDevice() failed"
      End If
      
      m_isDeviceOpen = False
      
   End Function
   
   '=============================================================================================='
   Public Function vbSetPassword(byval password)
 
      vbSetPassword = m_supplicant.SetPassword(password)
      If(vbSetPassword = False) Then
         oLog.Write "vbSetPassword: SetPassword() failed"
      End If
   
   End Function
                    
End Class
'<!-- CRC = 0xffb030db --->
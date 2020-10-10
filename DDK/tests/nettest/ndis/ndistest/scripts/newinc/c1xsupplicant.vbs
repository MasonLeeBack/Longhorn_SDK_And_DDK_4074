'<!-- CRC = 0xe49b7735 -->

Class C1xSupplicant

   Private m_oSupplicant
   
   '=============================================================================================='
   Sub Class_Initialize()
      
      Set m_oSupplicant = CreateObject("Ndt1xsupp.Supplicant.1")
      'm_oSupplicant.DebugLevel = oLog.DebugLevel      
   End Sub
   
   '=============================================================================================='
   Sub Class_Terminate()
   
      If(m_bDeviceOpened = True) Then
         vbCloseDevice()
      End If
      
      Set m_oSupplicant = Nothing
         
   End Sub
   
   '=============================================================================================='
   Public Function vbOpenDevice(byval sGUID)
   
      vbOpenDevice = m_oSupplicant.OpenDevice(sGUID)
            
   End Function
   
   '=============================================================================================='
   Public Function vbCloseDevice()
   
      vbCloseDevice = m_oSupplicant.CloseDevice()
   
   End Function
   
   '=============================================================================================='
   Public Function vbSetPassword(byval sPassword)
   
      vbSetPassword = m_oSupplicant.SetPassword(sPassword)
   
   End Function
   
   '=============================================================================================='
   Public Function vbStartWaitForHandshake()
   
      vbStartWaitForHandshake = m_oSupplicant.StartWaitForHandshake()
   
   End Function
   
   '=============================================================================================='
   Public Function vbEndWaitForHandshake(byval nTimeout)
   
      vbEndWaitForHandshake = m_oSupplicant.EndWaitForHandshake(nTimeout)
   
   End Function  
               
   '=============================================================================================='
   Public Property Let vbDisableKeying(byval newVal)
   
      m_oSupplicant.DisableKeying = newVal
   
   End Property
   
   '=============================================================================================='
   Public Property Get vbDisableKeying
   
      vbDisableKeying = m_oSupplicant.DisableKeying
   
   End Property
   
   '=============================================================================================='
   Public Property Get vbIsPairwiseKeyActive
   
      vbIsPairwiseKeyActive = m_oSupplicant.IsPairwiseKeyActive
   
   End Property
   
   '=============================================================================================='
   Public Property Get vbIsGroupKeyActive
   
      vbIsGroupKeyActive = m_oSupplicant.IsGroupKeyActive
   
   End Property
   
End Class
'<!-- CRC = 0xfda7d85a --->
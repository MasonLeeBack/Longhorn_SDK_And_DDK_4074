Option Explicit

Dim oNDTWMIEvents : Set oNDTWMIEvents = New CNDTWMIEvents

Class CNDTWMIEvents

   Private m_ndtWMIEvents
   
   '=============================================================================================='
   Public Sub Class_Initialize()
      
      Set m_ndtWMIEvents = CreateObject("NDTWMIEvents.Events.1")

   End Sub
   
   '=============================================================================================='
   Public Sub Class_Terminate()
   
      Set m_ndtWMIEvents = Nothing
   
   End Sub
   
   '=============================================================================================='
   Public Function vbWaitForEvent(byval instance, byval eventType, byval dataType, byval timeout, byref eventInfo)
   Dim retval : retval = -1
            
      retval = m_ndtWMIEvents.WaitForEvent(instance, eventType, dataType, timeout, eventInfo)
      If(retval <> EVENT_STATUS_SUCCESS) Then
         oLog.Write "vbWaitForEvent: Failed to get event (error = " & Hex(retval) & ")"
      End If
      
      vbWaitForEvent = retval
      
   End Function
   
   '=============================================================================================='
   Public Function vbWaitForAdapterArrival(byval instance, byval timeout)
   Dim retval     : retval    = -1
   Dim eventInfo  : eventInfo = Empty
      
      vbWaitForAdapterArrival = Me.vbWaitForEvent(instance,                           _ 
                                                  EVENT_MSNDIS_NOTIFYADAPTERARRIVAL,  _
                                                  EVENT_TYPE_BOOLEAN,                 _
                                                  timeout,                            _
                                                  eventInfo)
                               
   End Function
   
   '=============================================================================================='
   Public Function vbWaitForMediaConnect(byval instance, byval timeout)
   Dim retval     : retval    = -1
   Dim eventInfo  : eventInfo = Empty
      
      vbWaitForMediaConnect = Me.vbWaitForEvent(instance,                           _ 
                                                EVENT_MSNDIS_STATUS_MEDIA_CONNECT,  _
                                                EVENT_TYPE_BOOLEAN,                 _
                                                timeout,                            _
                                                eventInfo)
                               
   End Function
   
   '=============================================================================================='
   Public Function vbWaitForMediaDisconnect(byval instance, byval timeout)
   Dim retval     : retval    = -1
   Dim eventInfo  : eventInfo = Empty
      
      vbWaitForMediaDisconnect = Me.vbWaitForEvent(instance,                              _ 
                                                   EVENT_MSNDIS_STATUS_MEDIA_DISCONNECT,  _
                                                   EVENT_TYPE_BOOLEAN,                    _
                                                   timeout,                               _
                                                   eventInfo)
                                                
   End Function
   
   '=============================================================================================='
   Public Function vbWaitForMediaSpecificIndication(byval instance, byval timeout, byval dataType, byref eventInfo)
   Dim retval     : retval    = -1
         
      vbWaitForMediaSpecificIndication = Me.vbWaitForEvent(instance,                                       _ 
                                                           EVENT_MSNDIS_STATUS_MEDIA_SPECIFIC_INDICATION,  _
                                                           dataType,                                       _
                                                           timeout,                                        _
                                                           eventInfo)
                                                
   End Function
   
   '=============================================================================================='
   Public Function vbStartWaitForEvent(byval instance, byval eventType, byval dataType)
            
      vbStartWaitForEvent = m_ndtWMIEvents.StartWaitForEvent(instance, eventType, dataType)
                                                
   End Function
   
   '=============================================================================================='
   Public Function vbEndWaitForEvent(byval eventID, byval timeout, byref eventInfo)
            
      vbEndWaitForEvent = m_ndtWMIEvents.EndWaitForEvent(eventID, timeout, eventInfo)
                                                
   End Function
   
   '=============================================================================================='
   Public Function vbStartWaitForMediaConnect(byval instance)
            
      vbStartWaitForMediaConnect = vbStartWaitForEvent(instance, EVENT_MSNDIS_STATUS_MEDIA_CONNECT, EVENT_TYPE_BOOLEAN)
                                                
   End Function
   
   '=============================================================================================='
   Public Function vbEndWaitForMediaConnect(byval eventID, byval timeout)
   Dim eventInfo : Set eventInfo = Nothing
   
      vbEndWaitForMediaConnect = m_ndtWMIEvents.EndWaitForEvent(eventID, timeout, eventInfo)
                                                
   End Function
   
   '=============================================================================================='
   Public Function vbStartWaitForMediaDisconnect(byval instance)
            
      vbStartWaitForMediaDisconnect = vbStartWaitForEvent(instance, EVENT_MSNDIS_STATUS_MEDIA_DISCONNECT, EVENT_TYPE_BOOLEAN)
                                                
   End Function
   
   '=============================================================================================='
   Public Function vbEndWaitForMediaDisconnect(byval eventID, byval timeout)
   Dim eventInfo : Set eventInfo = Nothing
   
      vbEndWaitForMediaDisconnect = m_ndtWMIEvents.EndWaitForEvent(eventID, timeout, eventInfo)
                                                
   End Function
   
   '=============================================================================================='
   Public Function vbStartWaitForMediaSpecificIndication(byval instance, byval dataType)
            
      vbStartWaitForMediaSpecificIndication = vbStartWaitForEvent(instance, EVENT_MSNDIS_STATUS_MEDIA_SPECIFIC_INDICATION, dataType)
                                                
   End Function
   
   '=============================================================================================='
   Public Function vbEndWaitForMediaSpecificIndication(byval eventID, byval timeout, byref eventInfo)
      
      vbEndWaitForMediaSpecificIndication = m_ndtWMIEvents.EndWaitForEvent(eventID, timeout, eventInfo)
                                                
   End Function
   
End Class



'<!-- CRC = 0xc11ff860 --->
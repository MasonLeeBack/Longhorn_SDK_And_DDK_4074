'================================================================================================='
'/**
'This file contains the functions that can be performed on an NDTCore6::EndPointEx object for LAN
'media only
'@file
'@author    Mitesh Desai
'@alias     miteshd@microsoft.com
'*/
'================================================================================================='
Option Explicit

'================================================================================================='
'3 Document
'/**
'This class encapsulates the various operations that can be performed on a LAN NDTCore6::EndPointEx
'object. It uses functionality provided by the communication functions for LAN objects
'@sa        CLanCard6, CLanOpen6
'@date      02/22/2003
'@author    Mitesh Desai
'@alias     miteshd
'*/
Class CLanEndPointEx6
   Dim m_oCOMEndPoint
   Dim m_sAdapterType
   Dim m_TrafficMgrType
   Dim m_NBModuleStackType
   Dim m_NumStackModules
   Dim m_EndPointType

   Private Sub Class_Initialize
      Set m_oCOMEndPoint = Nothing
      m_TrafficMgrType = TRAFFIC_MGR_ABSENT
      m_NBModuleStackType = NB_MODULE_STACK_ABSENT
      m_NumStackModules = 0
   End Sub

   Private Sub Class_Terminate
      Set m_oCOMEndPoint = Nothing
   End Sub

   '================================================================================================='
   '/**
   '*/
   Public Property Set COMEndPoint(p_oCOMEndPoint)
      Set m_oCOMEndPoint = p_oCOMEndPoint
   End Property

   '================================================================================================='
   '/**
   '*/
   Public Property Get COMEndPoint
      Set COMEndPoint = m_oCOMEndPoint
   End Property

   '================================================================================================='
   '/**
   '*/
   Public Property Get TrafficMgrType
      TrafficMgrType = m_TrafficMgrType
   End Property

   '================================================================================================='
   '/**
   '*/
   Public Property Get NBModuleStackType
      NBModuleStackType = m_NBModuleStackType
   End Property

   '================================================================================================='
   '/**
   '@exclude
   'Stores the adapter type that this open instance represents. Helps printing
   'more relevant error messages
   '@params
   '  ! string The adapter type (Test or support) and so on
   '*/
   Public Property Let AdapterType (sAdapterType)
      m_sAdapterType = sAdapterType
   End Property

   '================================================================================================='
   '/**
   'Returns the adapter type to the children classes so as to print the correct error messages
   '@return    Returns "Test Adapter" or "Support Adapter" or similar depending on what is the adapter type
   '*/
   Public Property Get AdapterType
      AdapterType = m_sAdapterType
   End Property

   '================================================================================================='
   '/**
   '@exclude
   '@params
   '  ! long The endpoint type (Test or support) and so on
   '*/
   Public Property Let EndPointType (lEndPointType)
      m_EndPointType = lEndPointType
   End Property

   '================================================================================================='
   '/**
   'Returns the endpoint type to the children classes so as to print the correct error messages
   '@return    EndPoint Type
   '*/
   Public Property Get EndPointType
      EndPointType = m_EndPointType
   End Property

   '===============================================================================================//
   '/**
   '*/
   Public Function vbOpenCommunicationChannel(lTrafficMgrType, lNBModuleStackType, lStackModuleList, NumStackModule)
      vbOpenCommunicationChannel = m_oCOMEndPoint.OpenCommunicationChannel(lTrafficMgrType, _
         lNBModuleStackType, lStackModuleList, NumStackModule _
         )
      If (vbOpenCommunicationChannel = 0) Then
         m_TrafficMgrType = lTrafficMgrType
         m_NBModuleStackType = lNBModuleStackType
         m_NumStackModules = NumStackModule
      End If
   End Function

   '===============================================================================================//
   '/**
   '*/
   Public Function vbCloseCommunicationChannel()
      vbCloseCommunicationChannel = m_oCOMEndPoint.CloseCommunicationChannel()
      ' Reset the info about the various object types
      m_TrafficMgrType = TRAFFIC_MGR_ABSENT
      m_NBModuleStackType = NB_MODULE_STACK_ABSENT
      m_NumStackModules = 0
   End Function

   '===============================================================================================//
   '/**
   '*/
   Public Function vbSendConfigureModule(ModuleIndex, ModuleType, ModuleConfig)
      vbSendConfigureModule = m_oCOMEndPoint.SendConfigureModule(ModuleIndex, ModuleType, _
         ModuleConfig)
   End Function


   '===============================================================================================//
   '/**
   '*/
   Public Function vbSendNetBufferLists(TrafficMgrConfig, NBModuleStackConfig)
      ' Update the net buffer stack module type in the configs before passing
      ' them to COM
      TrafficMgrConfig.NetBufferModuleStackType = m_NBModuleStackType

      vbSendNetBufferLists = m_oCOMEndPoint.SendNetBufferLists(m_TrafficMgrType, _
         TrafficMgrConfig, NBModuleStackConfig)
   End Function

   '===============================================================================================//
   '/**
   '*/
   Public Function vbStopSend(ulTimeOut)
      If (ulTimeOut = 0) Then
         ' We loop for ever waiting for the sends to stop
         Do
            ' We loop continuously waiting 60 seconds for each StopSend call
            vbStopSend = m_oCOMEndPoint.StopSend(60000)
         Loop While (vbStopSend = NDT_STATUS_TIMEOUT)
      Else
         vbStopSend = m_oCOMEndPoint.StopSend(ulTimeOut)
      End If
   End Function

   '===============================================================================================//
   '/**
   '*/
   Public Function vbWaitForSendsToComplete(ulTimeOut)
      If (ulTimeOut = 0) Then
         ' We loop for ever waiting for the sends to complete
         Do
            ' We loop continuously waiting 60 seconds for each WaitSend call
            vbWaitForSendsToComplete = m_oCOMEndPoint.WaitForSendsToComplete(60000)
         Loop While (vbWaitForSendsToComplete = NDT_STATUS_TIMEOUT)
      Else
         vbWaitForSendsToComplete = m_oCOMEndPoint.WaitForSendsToComplete(ulTimeOut)
      End If
   End Function

   '===============================================================================================//
   '/**
   '*/
   Public Function vbStartAllSends()
      vbStartAllSends = m_oCOMEndPoint.StartAllSends()
   End Function

   '===============================================================================================//
   '/**
   '*/
   Public Function vbGetSendResults(ByRef oCommEngineStats, ByRef NumStats)
      vbGetSendResults = m_oCOMEndPoint.GetSendResults(oCommEngineStats, NumStats)
   End Function


   '===============================================================================================//
   '/**
   '*/
   Public Function vbReceiveConfigureModule(ModuleIndex, ModuleType, ModuleConfig)
      vbReceiveConfigureModule = m_oCOMEndPoint.ReceiveConfigureModule(ModuleIndex, ModuleType, _
         ModuleConfig)
   End Function

   '================================================================================================='
   '/**
   '*/
   Public Function vbStartReceive(TrafficMgrConfig, NBModuleStackConfig)
      ' Update the net buffer stack module type in the configs before passing
      ' them to COM
      TrafficMgrConfig.NetBufferModuleStackType = m_NBModuleStackType

      vbStartReceive = m_oCOMEndPoint.StartReceive(m_TrafficMgrType, _
         TrafficMgrConfig, NBModuleStackConfig)
   End Function

   '================================================================================================='
   '/**
   '*/
   Public Function vbStopReceive()
      vbStopReceive = m_oCOMEndPoint.StopReceive()
   End Function


   '================================================================================================='
   '/**
   '*/
   Public Function vbGetReceiveResults(ByRef oCommEngineStats, ByRef NumStats)
      vbGetReceiveResults = m_oCOMEndPoint.GetReceiveResults(oCommEngineStats, NumStats)
   End Function

End Class




'<!-- CRC = 0xcad513a1 --->
'================================================================================================='
'/**
'This file contains the functions that can be performed on an NDTCore6::EndPoint object for LAN
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
'This class encapsulates the various operations that can be performed on a LAN NDTCore6::EndPoint
'object. It uses functionality provided by the communication functions for LAN objects
'@sa        CLanCard6, CLanOpen6
'@date      02/22/2003
'@author    Mitesh Desai
'@alias     miteshd
'*/
Class CLanEndPoint6
   Dim m_oCOMEndPoint
   Dim m_sAdapterType
   Dim m_CommMgrType
   Dim m_ConstructorType
   Dim m_MediaModuleType
   Dim m_EndPointType

   Private Sub Class_Initialize
      Set m_oCOMEndPoint = Nothing
      m_CommMgrType = COMM_MGR_ABSENT
      m_ConstructorType = CONSTRUCTOR_ABSENT
      m_MediaModuleType = MEDIA_MODULE_ABSENT
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
   Public Property Get CommMgrType
      CommMgrType = m_CommMgrType
   End Property

   '================================================================================================='
   '/**
   '*/
   Public Property Get ConstructorType
      ConstructorType = m_ConstructorType
   End Property

   '================================================================================================='
   '/**
   '*/
   Public Property Get MediaModuleType
      MediaModuleType = m_MediaModuleType
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
   
   '================================================================================================='
   '/**
   'Returns the adapter type to the children classes so as to print the correct error messages
   '@return    Returns "Test Adapter" or "Support Adapter" or similar depending on what is the adapter type
   '*/
   Public Property Get AdapterType
      AdapterType = m_sAdapterType
   End Property

   '===============================================================================================//
   '/**
   '*/
   Public Function vbOpenCommunicationChannel(ulCommMgrType, ulConstructorType, ulMediaModuleType)
      vbOpenCommunicationChannel = m_oCOMEndPoint.OpenCommunicationChannel(ulCommMgrType, ulConstructorType, ulMediaModuleType)
      If (vbOpenCommunicationChannel = 0) Then
         m_CommMgrType = ulCommMgrType
         m_ConstructorType = ulConstructorType
         m_MediaModuleType = ulMediaModuleType
      End If
   End Function

   '===============================================================================================//
   '/**
   '*/
   Public Function vbCloseCommunicationChannel()
      vbCloseCommunicationChannel = m_oCOMEndPoint.CloseCommunicationChannel()
      ' Reset the info about the various object types
      m_CommMgrType = COMM_MGR_ABSENT
      m_ConstructorType = CONSTRUCTOR_ABSENT
      m_MediaModuleType = MEDIA_MODULE_ABSENT
   End Function

   '===============================================================================================//
   '/**
   '*/
   Public Function vbSendNetBufferLists(CommMgrConfig, ConstructorConfig, MediaModuleConfig)
      ' Update the constructor and media module types in the two configs before passing
      ' them to COM
      CommMgrConfig.NetBufferConstructorType = m_ConstructorType
      ConstructorConfig.MediaModuleType = m_MediaModuleType

      vbSendNetBufferLists = m_oCOMEndPoint.SendNetBufferLists(m_CommMgrType, CommMgrConfig, ConstructorConfig, MediaModuleConfig)
   End Function

   '===============================================================================================//
   '/**
   '*/
   Public Function vbStopSend(ulTimeOut)
      vbStopSend = m_oCOMEndPoint.StopSend(ulTimeOut)
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
   Public Function vbSetRSSParameters(CapabilitiesFlags, ParametersStructure, StructureSize)
      vbSetRSSParameters = m_oCOMEndPoint.SetRSSParameters(CapabilitiesFlags, ParametersStructure, StructureSize)
   End Function

   '===============================================================================================//
   '/**
   '*/
   Public Function vbOpenIPHelper(IPHelperType, HelperConfig)
      vbOpenIPHelper = m_oCOMEndPoint.OpenIPHelper(IPHelperType, HelperConfig)
   End Function

   '===============================================================================================//
   '/**
   '*/
   Public Function vbGetSendResults(oCommMgrStats, oConstructorStats)
      Dim lCommMgrType, lConstructorType

      ' Figure out the comm mgr and constructor types to pass to COM
      If (oCommMgrStats is Nothing) Then
         lCommMgrType = COMM_MGR_ABSENT
      Else
         lCommMgrType = m_CommMgrType
      End If

      If (oConstructorStats is Nothing) Then
         lConstructorType = CONSTRUCTOR_ABSENT
      Else
         lConstructorType = m_ConstructorType
      End If

      vbGetSendResults = m_oCOMEndPoint.GetSendResults(lCommMgrType, oCommMgrStats, lConstructorType, oConstructorStats)
   End Function

   '================================================================================================='
   '/**
   '*/
   Public Function vbStartReceive(CommMgrConfig, ConstructorConfig, MediaModuleConfig)
      ' Update the constructor and media module types in the two configs before passing
      ' them to COM
      CommMgrConfig.NetBufferConstructorType = m_ConstructorType
      ConstructorConfig.MediaModuleType = m_MediaModuleType

      vbStartReceive = m_oCOMEndPoint.StartReceive(m_CommMgrType, CommMgrConfig, ConstructorConfig, MediaModuleConfig)
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
   Public Function vbGetReceiveResults(oCommMgrStats, oConstructorStats)
      Dim lCommMgrType, lConstructorType

      ' Figure out the comm mgr and constructor types to pass to COM
      If (oCommMgrStats is Nothing) Then
         lCommMgrType = COMM_MGR_ABSENT
      Else
         lCommMgrType = m_CommMgrType
      End If

      If (oConstructorStats is Nothing) Then
         lConstructorType = CONSTRUCTOR_ABSENT
      Else
         lConstructorType = m_ConstructorType
      End If
      vbGetReceiveResults = m_oCOMEndPoint.GetReceiveResults(lCommMgrType, oCommMgrStats, lConstructorType, oConstructorStats)
   End Function

End Class



'<!-- CRC = 0xbb3b4bb4 --->
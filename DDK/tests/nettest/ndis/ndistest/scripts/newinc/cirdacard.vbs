Option Explicit

'================================================================================================='
'/**
'This class encapsulates the various operations that can be performed on a IRDA NDTCore::Card
'object. It uses functionality provided by the connection less card object and also augments
'it with additional IRDA specific functions
'@sa        CIrdaOpen, CCLCard
'@date      01/09/2002
'@author    Mitesh Desai
'@alias     miteshd
'*/
Class CIrdaCard
   Dim m_oCLCard
   
   Private Sub Class_Initialize
      Set m_oCLCard = New CCLCard
   End Sub
   
   Private Sub Class_Terminate
      Set m_oCLCard = Nothing
   End Sub

   '================================================================================================='
   '/**
   '@sa CCard::COMAdapter
   '*/
   Public Property Get COMAdapter
      Set COMAdapter = m_oCLCard.COMAdapter
   End Property
   
   '================================================================================================='
   '/**
   '@sa CCard::AdapterType
   '*/
   Public Property Get AdapterType
      AdapterType = m_oCLCard.AdapterType
   End Property  
   
   '================================================================================================='
   '/**
   '@sa CCard::vbCreateAdapter
   '*/
   Public Function vbCreateAdapter(oCOMAdapter)
      vbCreateAdapter = m_oCLCard.vbCreateAdapter(oCOMAdapter)
   End Function
   
   '================================================================================================='
   '/**
   'This API is used to Create an Open on the Adapter Object. This API will also setup the CIrdaOpen
   'object that would be used for all the open operations. 
   '@return Instance of CIrdaOpen object created if successful, else Nothing
   '@code
   'Set oSuppOpen = oSuppCard.vbCreateOpen ()
   'If (oSuppOpen Is Nothing) Then
   '   Exit Function
   'End If
   '@endcode
   '@sa    CIrdaCard::vbSetupBasicTest, CCLCard::vbCreateOpen, CIrdaOpen::CLOpen
   '*/
   Public Function vbCreateOpen
      Dim l_oCLOpen
      Set l_oCLOpen = m_oCLCard.vbCreateOpen
      If (l_oCLOpen is Nothing) Then
         Set vbCreateOpen = Nothing
      Else
         Dim l_oIrdaOpen
         Set l_oIrdaOpen = New CIrdaOpen
         Set l_oIrdaOpen.CLOpen = l_oCLOpen
         Set vbCreateOpen = l_oIrdaOpen
      End If
      Set l_oCLOpen = Nothing
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::NdisMedium
   '*/
   Public Property Get NdisMedium
      NdisMedium = m_oCLCard.NdisMedium
   End Property
   
   
   '================================================================================================='
   '/**
   'This function works on the adapter object held within the hierarchy, 
   'creating an open object and performing an ndisopen on that object.
   'Internally, it relies on vbCreateOpen and vbNdisOpen to do the work
   'for it
   '@return The CIrdaOpen object that has a "NdisOpened" instance
   '@code
   'Set oTestOpen = oTestCard.vbOpenAdapter
   'If (oTestOpen is Nothing) Then
   '   Exit Function
   'End If
   '@endcode
   '@sa  CIrdaCard::vbCreateOpen, CIrdaOpen::vbNdisOpen, CIrdaCard::vbSetupBasicTest
   '*/
   Public Function vbOpenAdapter
      Dim l_oIrdaOpen
      
      Set l_oIrdaOpen = Me.vbCreateOpen
      
      If (Not (l_oIrdaOpen is Nothing)) Then
         If (Not l_oIrdaOpen.vbNdisOpen) Then
            Set l_oIrdaOpen = Nothing
         End If
      End If
      
      Set vbOpenAdapter = l_oIrdaOpen
   End Function
   
   '================================================================================================='
   '/**
   'This function takes an NDInfo adapter object and returns a CIrdaOpen object containing
   'a "NdisOpened" instance
   '@params
   '  !  object A NDInfo::Adapter object (element from ndinfo::adapterlist)
   '@return    A CIrdaOpen object or Nothing depending on success
   '@code
   '   Set oTestCard = New CIrdaCard
   '   Set oTestOpen = oTestCard.vbSetupBasicTest(oNDInfo.AdapterList(lTestAdapterIndex))
   '   If (oTestOpen is Nothing) Then
   '     Exit Function
   '   End If
   '@endcode
   '@sa  CIrdaCard::vbCreateAdapter, CIrdaCard::vbCreateOpen, CIrdaOpen::vbNdisOpen
   '*/
   Public Function vbSetupBasicTest (oCOMAdapter)
      If (Me.vbCreateAdapter(oCOMAdapter)) Then
         Set vbSetupBasicTest = Me.vbOpenAdapter
      Else
         Set vbSetupBasicTest = Nothing
      End If
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::vbNdisIOControl
   '*/
   Public Function vbNdisIOControl(Oid, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
      vbNdisIOControl = m_oCLCard.vbNdisIOControl (Oid, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
   End Function

   '================================================================================================='
   '/**
   '@sa CCard::vbNdisIOControlEx
   '*/
   Public Function vbNdisIOControlEx(Oid, BufferLen, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
      vbNdisIOControlEx = m_oCLCard.vbNdisIOControlEx (Oid, BufferLen, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
   End Function
      
   '================================================================================================='
   '/**
   '@sa CCard::vbFastNdisIOControl
   '*/
   Public Function vbFastNdisIOControl(ByVal Oid, ByRef DataBuffer, ByVal QueryMode)
      vbFastNdisIOControl = m_oCLCard.vbFastNdisIOControl (Oid, DataBuffer, QueryMode)
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::vbQueryGuid
   '*/
   Public Function vbQueryGuid (OidGuid, DataBuffer)
      vbQueryGuid = m_oCLCard.vbQueryGuid (OidGuid, DataBuffer)
   End Function

   '================================================================================================='
   '/**
   '@sa CCard::vbWmiRequest
   '*/
   Public Function vbWmiRequest (strGuid, DataBuffer, BufferLength, RequestType, ErrorStatus, nBytesNeeded)
      vbWmiRequest = m_oCLCard.vbWmiRequest (strGuid, DataBuffer, BufferLength, RequestType, ErrorStatus, nBytesNeeded)
   End Function   

   '================================================================================================='
   '/**
   '@sa CCard::vbGetPhysicalMedium
   '*/
   Public Function vbGetPhysicalMedium
      vbGetPhysicalMedium = m_oCLCard.vbGetPhysicalMedium
   End Function

   '================================================================================================='
   '/**
   '@sa CCard::vbGetMaxPacketSize
   '*/
'   Public Function vbGetMaxPacketSize
'      vbGetMaxPacketSize = m_oCLCard.vbGetMaxPacketSize
'   End Function

   '================================================================================================='
   '/**
   '@sa CCard::vbWaitForLink
   '*/
   Public Function vbWaitForLink(WaitTime)
      vbWaitForLink = m_oCLCard.vbWaitForLink(WaitTime)
   End Function
   
   '============================================================================================='
   '/**
   '@sa CCard::vbWaitForLinkWithDelay
   '*/
   Function vbWaitForLinkWithDelay(WaitTime, ExtraWaitDelay)
      vbWaitForLinkWithDelay = m_oCLCard.vbWaitForLinkWithDelay(WaitTime, ExtraWaitDelay)
   End Function

End Class



'<!-- CRC = 0x80b8d3c8 --->
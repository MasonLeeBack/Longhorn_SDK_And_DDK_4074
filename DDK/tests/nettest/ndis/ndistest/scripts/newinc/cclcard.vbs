Option Explicit

'================================================================================================='
'/**
' * The CCLCard class. This is a derived class of CCard. It adds
' * functionality related to connection less devices. 
' * @sa       CCard, CCLOpen
' * @date     01/07/2002
' * @author   Mitesh Desai
' * @alias    miteshd@microsoft.com
'*/
Class CCLCard
   Dim m_oCard
   
   Private Sub Class_Initialize
      Set m_oCard = New CCard
   End Sub
   
   Private Sub Class_Terminate
      Set m_oCard = Nothing
   End Sub
   
   '================================================================================================='
   '/**
   '@sa CCard::NdisMedium
   '*/
   Public Property Get NdisMedium
      NdisMedium = m_oCard.NdisMedium
   End Property
   
   '================================================================================================='
   '/**
   '@sa CCard::COMAdapter
   '*/
   Public Property Get COMAdapter
      Set COMAdapter = m_oCard.COMAdapter
   End Property
   
   '================================================================================================='
   '/**
   '@sa CCard::AdapterType
   '*/
   Public Property Get AdapterType
      AdapterType = m_oCard.AdapterType
   End Property  
   
   '================================================================================================='
   '/**
   '@sa CCard::vbCreateAdapter
   '*/
   Public Function vbCreateAdapter(oCOMAdapter)
      vbCreateAdapter = m_oCard.vbCreateAdapter(oCOMAdapter)
   End Function
   
   '================================================================================================='
   '/**
   'This function is part of the chain of functions used to create an open instance
   'from the adapter instance. It calls CCard::vbCreateOpen and also creates and 
   'initializes the CCLOpen object. This CCLOpen object is passed to the lower
   'levels.
   '@return Returns the CCLOpen object or Nothing
   '@sa    CCLOpen::COpen, CCard::vbCreateOpen
   '*/
   Public Function vbCreateOpen()
      Dim l_oOpen
      Set l_oOpen = m_oCard.vbCreateOpen
      If (l_oOpen is Nothing) Then
         Set vbCreateOpen = Nothing
      Else
         Dim l_oCLOpen
         Set l_oCLOpen = New CCLOpen
         Set l_oCLOpen.Open = l_oOpen
         Set vbCreateOpen = l_oCLOpen
      End If
      Set l_oOpen = Nothing
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::vbNdisIOControl
   '*/
   Public Function vbNdisIOControl(Oid, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
      vbNdisIOControl = m_oCard.vbNdisIOControl (Oid, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
   End Function

   '================================================================================================='
   '/**
   '@sa CCard::vbNdisIOControlEx
   '*/
   Public Function vbNdisIOControlEx(Oid, BufferLen, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
      vbNdisIOControlEx = m_oCard.vbNdisIOControlEx (Oid, BufferLen, DataBuffer, BytesWritten, ErrorStatus, QueryMode)
   End Function
      
   '================================================================================================='
   '/**
   '@sa CCard::vbFastNdisIOControl
   '*/
   Public Function vbFastNdisIOControl(ByVal Oid, ByRef DataBuffer, ByVal QueryMode)
      vbFastNdisIOControl = m_oCard.vbFastNdisIOControl (Oid, DataBuffer, QueryMode)
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::vbQueryGuid
   '*/
   Public Function vbQueryGuid (OidGuid, DataBuffer)
      vbQueryGuid = m_oCard.vbQueryGuid (OidGuid, DataBuffer)
   End Function

   '================================================================================================='
   '/**
   '@sa CCard::vbWmiRequest
   '*/
   Public Function vbWmiRequest (strGuid, DataBuffer, BufferLength, RequestType, ErrorStatus, nBytesNeeded)
      vbWmiRequest = m_oCard.vbWmiRequest (strGuid, DataBuffer, BufferLength, RequestType, ErrorStatus, nBytesNeeded)
   End Function   
   
   '================================================================================================='
   '/**
   '@sa CCard::vbGetMaxPacketSize
   '*/
   Public Function vbGetMaxPacketSize
      vbGetMaxPacketSize = m_oCard.vbGetMaxPacketSize
   End Function
   
   
   '================================================================================================='
   '/**
   '@sa CCard::vbGetPhysicalMedium
   '*/
   Public Function vbGetPhysicalMedium()
      vbGetPhysicalMedium = m_oCard.vbGetPhysicalMedium
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::vbGetLinkSpeed
   '*/
   Public Function vbGetLinkSpeed()
      vbGetLinkSpeed = m_oCard.vbGetLinkSpeed
   End Function
   
   '================================================================================================='
   '/**
   '@sa CCard::vbWaitForLink
   '*/
   Public Function vbWaitForLink(WaitTime)
      vbWaitForLink = m_oCard.vbWaitForLink(WaitTime)
   End Function

   '============================================================================================='
   '/**
   '@sa CCard::vbWaitForLinkWithDelay
   '*/
   Function vbWaitForLinkWithDelay(WaitTime, ExtraWaitDelay)
      vbWaitForLinkWithDelay = m_oCard.vbWaitForLinkWithDelay(WaitTime, ExtraWaitDelay)
   End Function
   
End Class


'<!-- CRC = 0xe9bdba6c --->
Option Explicit

'================================================================================================='
'/**
' * The COffloadCard class. This is a derived class of CLanCard. It provides
' * functionality related to offloading. As not much is different for offloading
' * at the card level, this class is providing wrappers to the CLanCard object.
' * @sa       CLanCard, CLanOpen, COffloadOpen
' * @date     12/19/2001
' * @author   Mitesh Desai
' * @alias    miteshd@microsoft.com
'*/
Class COffloadCard
   Dim m_oLanCard

   Private Sub Class_Initialize
      Set m_oLanCard = New CLanCard
   End Sub


   Private Sub Class_Terminate
      Set m_oLanCard = Nothing
   End Sub


   '================================================================================================='
   '/**
   '@sa CCard::COMAdapter
   '*/
   Public Property Get COMAdapter
      Set COMAdapter = m_oLanCard.COMAdapter
   End Property

   '================================================================================================='
   '/**
   '@sa CCard::AdapterType
   '*/
   Public Property Get AdapterType
      AdapterType = m_oLanCard.AdapterType
   End Property

   '================================================================================================='
   '/**
   '@sa CCard::vbCreateAdapter
   '*/
   Public Function vbCreateAdapter(oCOMAdapter)
      vbCreateAdapter = m_oLanCard.vbCreateAdapter(oCOMAdapter)
   End Function

   '================================================================================================='
   '/**
   'This API is used to Create an Open on the Adapter Object. This API will also setup the CLanOpen
   'object that would be used for all the open operations.
   '@return Instance of COffloadOpen object created if successful, else Nothing
   '@code
   'Set oSuppOpen = oSuppCard.vbCreateOpen ()
   'If (oSuppOpen Is Nothing) Then
   '   Exit Function
   'End If
   '@endcode
   '@sa    COffloadCard::vbSetupBasicTest, CLanCard::vbCreateOpen, COffloadOpen::LanOpen
   '*/
   Public Function vbCreateOpen
      Dim l_oLanOpen
      Set l_oLanOpen = m_oLanCard.vbCreateOpen
      If (l_oLanOpen is Nothing) Then
         Set vbCreateOpen = Nothing
      Else
         Dim l_oOffloadOpen
         Set l_oOffloadOpen = New COffloadOpen
         Set l_oOffloadOpen.LanOpen = l_oLanOpen
         Set vbCreateOpen = l_oOffloadOpen
      End If
      Set l_oLanOpen = Nothing
   End Function

   '================================================================================================='
   '/**
   '@sa CCard::NdisMedium
   '*/
   Public Property Get NdisMedium
      NdisMedium = m_oLanCard.NdisMedium
   End Property


   '================================================================================================='
   '/**
   'This function works on the adapter object held within the hierarchy,
   'creating an open object and performing an ndisopen on that object.
   'Internally, it relies on vbCreateOpen and vbNdisOpen to do the work
   'for it
   '@return The COffloadOpen object that has a "NdisOpened" instance
   '@code
   'Set oTestOpen = oTestCard.vbOpenAdapter
   'If (oTestOpen is Nothing) Then
   '   Exit Function
   'End If
   '@endcode
   '@sa  COffloadCard::vbCreateOpen, COffloadOpen::vbNdisOpen, COffloadCard::vbSetupBasicTest
   '*/
   Public Function vbOpenAdapter
      Dim l_oOffloadOpen

      Set l_oOffloadOpen = Me.vbCreateOpen

      If (Not (l_oOffloadOpen is Nothing)) Then
         If (Not l_oOffloadOpen.vbNdisOpen) Then
            Set l_oOffloadOpen = Nothing
         End If
      End If

      Set vbOpenAdapter = l_oOffloadOpen
   End Function

   '================================================================================================='
   '/**
   'This function takes an NDInfo adapter object and returns a COffloadOpen object containing
   'a "NdisOpened" instance
   '@params
   '  !  A NDInfo::Adapter object (element from ndinfo::adapterlist)
   '@return    A COffloadOpen object or Nothing depending on success
   '@code
   '   Set oTestCard = New COffloadCard
   '   Set oTestOpen = oTestCard.vbSetupBasicTest(oNDInfo.AdapterList(lTestAdapterIndex))
   '   If (oTestOpen is Nothing) Then
   '     Exit Function
   '   End If
   '
   '@endcode
   '@sa     COffloadCard::vbCreateAdapter, COffloadCard::vbCreateOpen, COffloadOpen::vbNdisOpen
   '*/
   Public Function vbSetupBasicTest (oCOMAdapter)
      If (Me.vbCreateAdapter(oCOMAdapter)) Then
         Set vbSetupBasicTest = Me.vbOpenAdapter
      Else
         Set vbSetupBasicTest = Nothing
      End If
   End Function

'   '================================================================================================='
'   '/**
'   '@sa CCard::vbGetMaxPacketSize
'   '*/
'   Public Function vbGetMaxPacketSize
'      vbGetMaxPacketSize = m_oLanCard.vbGetMaxPacketSize
'   End Function
'
   '================================================================================================='
   '/**
   '@sa CCard::vbWaitForLink
   '*/
   Function vbWaitForLink(WaitTime)
      vbWaitForLink = m_oLanCard.vbWaitForLink(WaitTime)
   End Function

   '================================================================================================='
   '/**
   '@sa CCard::vbWaitForLinkWithDelay
   '*/
   Function vbWaitForLinkWithDelay(WaitTime, ExtraWaitDelay)
      vbWaitForLinkWithDelay = m_oLanCard.vbWaitForLinkWithDelay(WaitTime, ExtraWaitDelay)
   End Function

End Class

'<!-- CRC = 0xdd798249 --->
Option Explicit

Class CWin32_Processor

   Private m_sComputer
   Private m_oWMIService
   Private m_oProcessors
   Private m_oCurrentProcessor
   Private m_nCurrent
   Private m_sQuery

   Private m_oCollection
   '================================================================================================='
   Public Sub Class_Initialize()

      m_nCurrent        = 0
      m_sComputer       = "."
      m_sQuery          = "SELECT * FROM Win32_Processor"

      Set m_oWMIService = Nothing
      Set m_oProcessors	= Nothing
      Set m_oCurrentProcessor    = Nothing
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")
      Set m_oCollection = CreateObject("Scripting.Dictionary")

   End Sub

   '================================================================================================='
   Public Sub Class_Terminate()

      Set m_oWMIService = Nothing
      Set m_oProcessors	= Nothing
      Set m_oCurrentProcessor    = Nothing

   End Sub

   '================================================================================================='
   Public Property Get vbCount
      vbCount = m_oCollection.Count
   End Property

   '================================================================================================='
   Public Property Get vbNumProcessors
      vbNumProcessors = m_oCollection.Count
   End Property

   '================================================================================================='
   Public Function vbConnect(byval sComputer)

      m_sComputer = sComputer
      Set m_oWMIService = GetObject("winmgmts:\\" & m_sComputer & "\root\cimv2")

   End Function

   '================================================================================================='
   Public Function vbQuery(byval sQuery)
   On Error Resume Next
   Dim oProcess   : Set oProcess = Nothing
   Dim nIndex     : nIndex       = 0

      m_sQuery = sQuery

      Set m_oProcessors  = m_oWMIService.ExecQuery(m_sQuery,"WQL",0)

      ' Check For Error
      If(Err.Number <> 0) Then
         vbQuery = Err.Number
         Exit Function
      Else
         vbQuery = Err.Number
      End If

      For Each oProcess In m_oProcessors

         nIndex = nIndex + 1
         m_oCollection.Add nIndex, oProcess

      Next

      If(m_oCollection.Count = 0) Then
         vbQuery = WBEM_ERR_FAILED
         Exit Function
      End If

      ' Set the process to the first process in the collection
      Set m_oCurrentProcessor = m_oCollection.Item(1)
      m_nCurrent = 1

   End Function

   '================================================================================================='
   Public Function vbNext
   Dim oProcess   : Set oProcess = Nothing

      m_nCurrent = m_nCurrent + 1

      ' Wrap around to the beginning of the collection
      If(m_nCurrent = m_oCollection.Count + 1) Then
         m_nCurrent = 1
      End If

      Set m_oCurrentProcessor = m_oCollection.Item(m_nCurrent)

   End Function

   '###################################### WMI Properties ###########################################'

   '================================================================================================='
   Public Property Get AddressWidth
      AddressWidth = m_oCurrentProcessor.AddressWidth
   End Property

   '================================================================================================='
   Public Property Get Architecture
      Architecture = m_oCurrentProcessor.Architecture
   End Property

   '================================================================================================='
   Public Property Get Availability
      Availability = m_oCurrentProcessor.Availability
   End Property

   '================================================================================================='
   Public Property Get Caption
      Caption = m_oCurrentProcessor.Caption
   End Property

   '================================================================================================='
   Public Property Get ConfigManagerErrorCode
      ConfigManagerErrorCode = m_oCurrentProcessor.ConfigManagerErrorCode
   End Property

   '================================================================================================='
   Public Property Get ConfigManagerUserConfig
      ConfigManagerUserConfig = m_oCurrentProcessor.ConfigManagerUserConfig
   End Property

   '================================================================================================='
   Public Property Get CpuStatus
      CpuStatus = m_oCurrentProcessor.CpuStatus
   End Property

   '================================================================================================='
   Public Property Get CreationClassName
      CreationClassName = m_oCurrentProcessor.CreationClassName
   End Property

   '================================================================================================='
   Public Property Get CurrentClockSpeed
      CurrentClockSpeed = m_oCurrentProcessor.CurrentClockSpeed
   End Property

   '================================================================================================='
   Public Property Get CurrentVoltage
      CurrentVoltage = m_oCurrentProcessor.CurrentVoltage
   End Property

   '================================================================================================='
   Public Property Get DataWidth
      DataWidth = m_oCurrentProcessor.DataWidth
   End Property

   '================================================================================================='
   Public Property Get Description
      Description = m_oCurrentProcessor.Description
   End Property

   '####################################### WMI Methods #############################################'

End Class

'<!-- CRC = 0xe2207ec1 --->
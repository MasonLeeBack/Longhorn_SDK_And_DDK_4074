'<!-- CRC = 0xbd1836ec -->
Option Explicit

'============================================================================================='
'/**
' This class encapulates the work of NDTSupp.PnPPowerMgmt object
'@author    Adeel Siddiqui (adeels)
'@date      11/06/2001
'@keyword   NDTCore,NDTSupp
'*/
Class PnPPower

    Private m_oPnPPower             ' Reference to the COM object! Saves lookup
    Private m_nPowerCaps            ' Power capabilities of the NIC
    Private m_nSupportedPowerStates ' The support device has for PM
    Private m_nStandbyOverhead      ' Allowed overhead for system to come out of standby
    Private m_nHibernateOverhead    ' Allowed overhead for system to come out of hibernation

    Sub Class_Initialize
        Set m_oPnPPower = CreateObject ("NDTSupp.PnPPowerMgmt.1")
        m_nSupportedPowerStates = 0
        m_nStandbyOverhead = 45
        m_nHibernateOverhead = 70
    End Sub
    

    Property Get SupportedPowerStates
        ' If not yet gotten supported states
        If (SupportedPowerStates = 0) Then
            ' get the supported states
            m_nSupportedPowerStates = m_oPnPPower.PowerStates
        End If
        
        SupportedPowerStates = m_nSupportedPowerStates
    End Property
    


    '============================================================================================='
    '/**
    ' Puts the machine to a sleep state
    '@return  True on success else failure
    '@param nSleepState     Choose from state S1, S2, S3 or S4 to put to sleep
    '@param nTimeToSleep    The time machine should go to sleep for. Valid
    '                       only if system supports Wakeup timer
    '@param nDurationSlept  The time system actually slept for
    '@code
    '   If ( Not oPnPPower.Sleep (SLEEP_STATE_S4, 60, nDurationSlept)) Then
    '       call oLog.Write ("Bailing out! Could not go to sleep (hibernate)")
    '   End If
    '*/
    Function Sleep (nSleepState, nTimeToSleep, ByRef nDurationSlept)
        Dim nResult
        
        If (nSleepState > 0 And nSleepState < 4) Then
            Sleep = Standby (nSleepState, nTimeToSleep, nDurationSlept)
        ElseIf (nSleepState = 4) Then
            Sleep = Hibernate (nTimeToSleep, nDurationSlept)
        Else
            call oLog.SafeFailed ("Invalid sleep state: " & nSleepState & " provided", 88888)
            Sleep = False
        End If
                
    End Function
    
    
    '============================================================================================='
    '/**
    ' Puts the machine to sleep state and verifies that it slept for "correct" amount of time
    ' if possible
    '@return  True on success else failure
    '@param nSleepLevel     Choose from state S1, S2, S3 or S4 to put to sleep
    '@param nTimeToSleep    The time machine should go to sleep for. Valid
    '                       only if system supports Wakeup timer
    '@param nDurationSlept  The time system actually slept for
    '@code
    '   If ( Not oPnPPower.VerifiedSsleep (SLEEP_STATE_S4, 60, nDurationSlept)) Then
    '       Exit Function
    '   End If
    '*/
    Function VerifiedSleep (nSleepState, nTimeToSleep)
        If (nSleepState > 0 And nSleepState < 4) Then
            VerifiedSleep = VerifiedStandby (nSleepState, nTimeToSleep)
        ElseIf (nSleepState = 4) Then
            VerifiedSleep = VerifiedHibernate (nTimeToSleep)
        Else
            call oLog.SafeFailed ("Invalid sleep state: " & nSleepState & " provided", 88888)
            VerifiedSleep = False
        End If
                
    End Function
    

    
    
    '============================================================================================='
    '/**
    ' Puts the machine to standby state
    '@return  True on success else failure
    '@param nSleepState     Choose from state S1, S2, S3 to put in standby
    '@param nTimeToSleep    The time machine should go to standby for. Valid
    '                       only if system supports Wakeup timer
    '@param nDurationSlept  The time system actually slept for
    '@code
    '   If ( Not oPnPPower.Standby (SLEEP_STATE_S3, 60, nDurationSlept)) Then
    '       call oLog.Write ("Bailing out! Could not go to standby")
    '   End If
    '*/
    Function Standby (nSleepState, nTimeToSleep, ByRef nDurationSlept)
        Dim nResult
        
        oLog.Variation ("Standby (S" & nSleepState & ")")
        
        ' Standby state must be S1, S2 or S3
        If (nSleepState < 1 Or nSleepState > 3) Then
            call oLog.SafeFailed ("Invalid standby state " & nSleepState & " provided", 88888)
            nDurationSlept = -1
            Standby = False
            Exit Function
        End If
        
        If (( (2 ^ (nSleepState - 1)) And SupportedPowerStates) > 0) Then
            nDurationSlept = m_oPnPPower.Standby (nSleepState, nTimeToSleep, nResult)
            
            If (nResult = 0) Then
                Standby = True
                oLog.Write ("System slept for " & nDurationSlept & " seconds")
            Else
                call oLog.SafeFailed ("Could not put the machine to standby", 88888)
                nDurationSlept = -1
                Standby = False
            End If
        Else
            call oLog.SafeFailed ("Sleep state S" & nSleepState & " is not supported.", 88888)
            nDurationSlept = -1
            Standby = False
        End If
    End Function
    

    '============================================================================================='
    '/**
    ' Puts the machine to standby state and verifies that it slept for "correct" amount of time
    ' if possible
    '@return  True on success else failure
    '@param nSleepLevel     Choose from state S1, S2, S3 to put in standby
    '@param nTimeToSleep    The time machine should go to standby for. Valid
    '                       only if system supports Wakeup timer
    '@param nDurationSlept  The time system actually slept for
    '@code
    '   If ( Not oPnPPower.VerifiedStandby (SLEEP_STATE_S3, 60, nDurationSlept)) Then
    '       call oLog.Write ("Bailing out! Could not go to standby")
    '   End If
    '*/
    Function VerifiedStandby (nSleepLevel, nTimeToSleep)
        Dim nDurationSlept
        VerifiedStandby = Standby (nSleepLevel, nTimeToSleep, nDurationSlept)
        
        ' If standby was successful in the first place
        If (VerifiedStandby) Then
            If ((SupportedPowerStates And WAKEUP_TIMER_SUPPORTED) <> 0) Then
                If (nDurationSlept < nTimeToSleep) Then
                    oLog.SafeWarned ("woke up too soon" )
                ElseIf (nDurationSlept > (nTimeToSleep + m_nStandbyOverhead)) Then
                    oLog.SafeWarned ("possible wakeup problem! System took very long to come out of sleep")
                End If
            End If
        End If
    End Function


    '============================================================================================='
    '/**
    ' Puts the machine to hibernation state
    '@return  True on success else failure
    '@param nSleepLevel     Choose from state S1, S2, S3 to put in standby
    '@param nTimeToSleep    The time machine should go to standby for. Valid
    '                       only if system supports Wakeup timer
    '@param nDurationSlept  The time system actually slept for
    '@code
    '   If ( Not oPnPPower.Hibernate (60, nDurationSlept)) Then
    '       call oLog.Write (""Bailing out! Could not hibernate")
    '   End If
    '*/
    Function Hibernate (nTimeToSleep, ByRef nDurationSlept)
        Dim nResult
        
        oLog.Variation ("Hibernate")
        If ( (SLEEP_STATE_S4 And SupportedPowerStates) > 0) Then
            nDurationSlept = m_oPnPPower.Hibernate (nTimeToSleep, nResult)
        
            If (nResult = 0) Then
                Hibernate = True
                oLog.Write ("System hibernated for " & nDurationSlept & " seconds")
            Else
                call oLog.SafeFailed ("Could not put the machine to hibernate state", 88888)
                nDurationSlept = -1
                Hibernate = False
            End If
        Else
            call oLog.SafeFailed ("Machine does not support hibernate", 88888)
            nDurationSlept = -1
            Hibernate = False
        End If
    End Function


    '============================================================================================='
    '/**
    ' Puts the machine to hibernation state and verifies that system slept for the
    ' specified amount of time if possible
    '@return  True on success else failure
    '@param nSleepLevel     Choose from state S1, S2, S3 to put in standby
    '@param nTimeToSleep    The time machine should go to standby for. Valid
    '                       only if system supports Wakeup timer
    '@param nDurationSlept  The time system actually slept for
    '@code
    '   If ( Not oPnPPower.VerifiedHibernate (60, nDurationSlept)) Then
    '       call oLog.Write (""Bailing out! Could not hibernate")
    '   End If
    '*/
    Function VerifiedHibernate (nTimeToSleep)
        Dim nDurationSlept
        VerifiedHibernate = Hibernate (nTimeToSleep, nDurationSlept)
        
        ' If standby was successful in the first place
        If (VerifiedHibernate) Then
            If ((SupportedPowerStates And WAKEUP_TIMER_SUPPORTED) <> 0) Then
                If (nDurationSlept < nTimeToSleep) Then
                    oLog.SafeWarned ("woke up too soon" )
                ElseIf (nDurationSlept > (nTimeToSleep + m_nHibernateOverhead)) Then
                    oLog.SafeWarned ("Possible wakeup problem! System took very long to come out of hibernate")
                End If
            End If
        End If
    End Function
    
    
    '============================================================================================='
    '/**
    ' Puts the machine to deepest available standy state and verifies that system slept for the
    ' specified amount of time if possible
    '@return  True on success else failure
    '@param nSleepLevel     Choose from state S1, S2, S3 to put in standby
    '@param nTimeToSleep    The time machine should go to standby for. Valid
    '                       only if system supports Wakeup timer
    '@param nDurationSlept  The time system actually slept for
    '@code
    '   If ( Not oPnPPower.VerifiedHibernate (60, nDurationSlept)) Then
    '       call oLog.Write (""Bailing out! Could not hibernate")
    '   End If
    '*/
    Function VerifiedDeepestStandby (nTimeToSleep)
        Dim nStandbyState
        
        nStandbyState = SupportedPowerStates
        
        ' Find the deepest sleep state supported
        If (nStandbyState And SLEEP_STATE_S3) > 0 Then
            nStandbyState = 3
        ElseIf (nStandbyState And SLEEP_STATE_S2) > 0 Then
            nStandbyState = 2
        ElseIf (nStandbyState And SLEEP_STATE_S1) > 0 Then
            nStandbyState = 1
        Else
            oLog.Write ("Machine does not support any standby state")
            VerifiedDeepestStandby = False
            Exit Function
        End If
                
        VerifiedDeepestStandby = VerifiedStandby (nStandbyState, nTimeToSleep)

    End Function
    
            
End Class

'<!-- CRC = 0x3cb0ea2c --->
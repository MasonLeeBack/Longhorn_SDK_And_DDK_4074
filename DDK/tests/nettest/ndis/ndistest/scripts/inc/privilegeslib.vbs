Option Explicit

'============================================================================================='
'/**
' This class encapulates the work of NDTSupp.PrivilegesController object
'@author    Adeel Siddiqui
'@date      02/04/02
'@alias     adeels
'*/
Class CPrivilegesCtrl
    Private oComPrivilegesController
    
    Sub Class_Initialize ()
        On Error Resume Next
        Set oComPrivilegesController = CreateObject ("NDTSupp.PrivilegesController.1")
        If (err.Number > 0) Then
            ' Print the vbscript error (this helps us track any other exception that get raised)
            call oLog.Failed ("Description = " & err.Description, 88888)
            call oLog.Write ("Number = " & err.Number)
            call oLog.Write ("Source = " & err.Source)
            
            ' Error is being cleared as we have handled the exception and place an error in the
            ' script! We do not want to print the illegal termination method in the log
            err.Clear
            
            WScript.Quit            
        End If
    End Sub
    
    
    Sub Class_Terminate

    End Sub
    
    '================================================================================================='
    '/**
    ' AddPrivilege will enable the requested privilege on the current process. The caller must have
    ' the TOKEN_ADJUST_PRIVILEGES to be able use this call. If the privilege is already held, the call
    ' will still succeed
    ' @params
    ' !strPrivilegeName     String containing name of the privilege to be enabled. <br>
    '                       The list can contain any one of the following privileges: <br>
    '                       "SeCreateTokenPrivilege" <br>
    '                       "SeAssignPrimaryTokenPrivilege" <br>
    '                       "SeLockMemoryPrivilege" <br>
    '                       "SeIncreaseQuotaPrivilege" <br>
    '                       "SeUnsolicitedInputPrivilege" <br>
    '                       "SeMachineAccountPrivilege" <br>
    '                       "SeTcbPrivilege" <br>
    '                       "SeSecurityPrivilege" <br>
    '                       "SeTakeOwnershipPrivilege" <br>
    '                       "SeLoadDriverPrivilege" <br>
    '                       "SeSystemProfilePrivilege" <br>
    '                       "SeSystemtimePrivilege" <br>
    '                       "SeProfileSingleProcessPrivilege" <br>
    '                       "SeIncreaseBasePriorityPrivilege" <br>
    '                       "SeCreatePagefilePrivilege" <br>
    '                       "SeCreatePermanentPrivilege" <br>
    '                       "SeBackupPrivilege" <br>
    '                       "SeRestorePrivilege" <br>
    '                       "SeShutdownPrivilege" <br>
    '                       "SeDebugPrivilege" <br>
    '                       "SeAuditPrivilege" <br>
    '                       "SeSystemEnvironmentPrivilege" <br>
    '                       "SeChangeNotifyPrivilege" <br>
    '                       "SeRemoteShutdownPrivilege" <br>
    '                       "SeUndockPrivilege" <br>
    '                       "SeSyncAgentPrivilege" <br>
    '                       "SeEnableDelegationPrivilege" <br>
    '                       "SeManageVolumePrivilege" <br>    
    ' @return     True on success, false on failure. An error code is placed in the log
    ' @syntax     oPrivilegesCtrl.AddPrivilege ("SeLoadDriverPrivilege")
    ' @sa         CPrivilegesCtrl::RemovePrivilege
    ' @example
    '     If (Not oPrivilegesCtrl.AddPrivilege ("SeShutDownPrivilege")) Then
    '         oLog.Write ("Failed to add privilege! Skipping test")
    '     End If
    ' */    
    Function AddPrivilege (strPrivilegeName)
        AddPrivilege = oComPrivilegesController.AdjustPrivilege (strPrivilegeName, 1)
        If (Not AddPrivilege) Then
            call oLog.SafeFailed ("Failed to add " & strPrivilegeName & " to the current process", 88888)
        End If
    End Function

    '================================================================================================='
    '/**
    ' RemovePrivilege will disable the requested privilege on the current process. The caller must have
    ' the TOKEN_ADJUST_PRIVILEGES to be able use this call. If the privilege is already disable, the call
    ' will still succeed
    ' @params
    ' !strPrivilegeName   String containing name of the privilege to be disabled. <br>
    '                     The list can contain any one of the following privileges: <br>
    '                     "SeCreateTokenPrivilege" <br>
    '                     "SeAssignPrimaryTokenPrivilege" <br>
    '                     "SeLockMemoryPrivilege" <br>
    '                     "SeIncreaseQuotaPrivilege" <br>
    '                     "SeUnsolicitedInputPrivilege" <br>
    '                     "SeMachineAccountPrivilege" <br>
    '                     "SeTcbPrivilege" <br>
    '                     "SeSecurityPrivilege" <br>
    '                     "SeTakeOwnershipPrivilege" <br>
    '                     "SeLoadDriverPrivilege" <br>
    '                     "SeSystemProfilePrivilege" <br>
    '                     "SeSystemtimePrivilege" <br>
    '                     "SeProfileSingleProcessPrivilege" <br>
    '                     "SeIncreaseBasePriorityPrivilege" <br>
    '                     "SeCreatePagefilePrivilege" <br>
    '                     "SeCreatePermanentPrivilege" <br>
    '                     "SeBackupPrivilege" <br>
    '                     "SeRestorePrivilege" <br>
    '                     "SeShutdownPrivilege" <br>
    '                     "SeDebugPrivilege" <br>
    '                     "SeAuditPrivilege" <br>
    '                     "SeSystemEnvironmentPrivilege" <br>
    '                     "SeChangeNotifyPrivilege" <br>
    '                     "SeRemoteShutdownPrivilege" <br>
    '                     "SeUndockPrivilege" <br>
    '                     "SeSyncAgentPrivilege" <br>
    '                     "SeEnableDelegationPrivilege" <br>
    '                     "SeManageVolumePrivilege" <br>        
    ' @return     True on success, false on failure. An error code is placed in the log
    ' @syntax     oPrivilegesCtrl.RemovePrivilege ("SeLoadDriverPrivilege")
    ' @sa         CPrivilegesCtrl::AddPrivilege
    ' @example
    '     If (Not oPrivilegesCtrl.RemovePrivilege ("SeShutDownPrivilege")) Then
    '         oLog.Write ("Failed to remove privilege! Skipping test")
    '     End If
    ' */        
    Function RemovePrivilege (strPrivilegeName)
        RemovePrivilege = oComPrivilegesController.AdjustPrivilege (strPrivilegeName, 0)
        If (Not RemovePrivilege) Then
            call oLog.SafeFailed ("Failed to remove " & strPrivilegeName & " from the current process", 88888)
        End If        
    End Function

End Class

'<!-- CRC = 0xa66f495e --->
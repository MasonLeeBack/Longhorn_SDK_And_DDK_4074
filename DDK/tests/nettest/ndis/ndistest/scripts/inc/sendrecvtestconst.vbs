Option Explicit



'------------------------------------------------------------------------------------
' These are the different types of sending mechanism from protocol for SendRecv Test
'------------------------------------------------------------------------------------
Const    NDT_SEND_DPC                 =  &H00000001&
Const    NDT_SEND_WORKITEM      =  &H00000002&

'------------------------------------------------------------------------------------
' These are the different types of components for SendRecv Test
'------------------------------------------------------------------------------------
Const COMPONENT_ALL                  =  &H00000000&
Const COMPONENT_MINIPORT        =  &H00000001&
Const COMPONENT_PROTOCOL        =  &H00000002&
Const COMPONENT_FILTER             =  &H00000004&
Const COMPONENT_IM                    =  &H00000008&

'------------------------------------------------------------------------------------
' These are the different types of actions for SendRecv Test
'------------------------------------------------------------------------------------
Const ACTION_SEND                        =  &H00000001&
Const ACTION_RECEIVE                   =  &H00000002&
Const ACTION_SEND_COMPLETE      =  &H00000004&
Const ACTION_RETURN                    =  &H00000008&

'------------------------------------------------------------------------------------
' These are the different types of verifications for SendRecv Test
'------------------------------------------------------------------------------------
Const VERIFY_SEND                        =  &H00000001&
Const VERIFY_RECEIVE                   =  &H00000002&
Const VERIFY_SEND_COMPLETE      =  &H00000003&
Const VERIFY_RETURN                    =  &H00000004&

'------------------------------------------------------------------------------------
' These are the different types of sendcompleting mechanism from miniport for SendRecv Test
'------------------------------------------------------------------------------------
Const    NDT_MINI_VERIFY_SEND_COMPLETE_USING_DPC                 =  &H00000001&
Const    NDT_MINI_VERIFY_SEND_COMPLETE_USING_WORKITEM      =  &H00000002&
Const    NDT_MINI_VERIFY_SEND_COMPLETE_FROM_SEND      =  &H00000003&

'------------------------------------------------------------------------------------
' These are the different types of receiving mechanism from miniport for SendRecv Test
'------------------------------------------------------------------------------------
Const    NDT_RECV_DPC                 =  &H00000001&
Const    NDT_RECV_WORKITEM      =  &H00000002&

'------------------------------------------------------------------------------------
' These are the different types of verifying return mechanism from miniport for SendRecv Test
'------------------------------------------------------------------------------------
Const    NDT_MINI_VERIFY_RETURN_USING_DPC                 =  &H00000001&
Const    NDT_MINI_VERIFY_RETURN_USING_WORKITEM      =  &H00000002&

Const OID_READY_TO_INDICATE_RECEIVE            = &HFFA0D001&
Const OID_STOP_INDICATE_RECEIVE            = &HFFA0D002&
Const OID_CHECK_FOR_SEND_COMPLETE            = &HFFA0D003&
Const OID_CHECK_FOR_RECV_RETURNED            = &HFFA0D004&


Const    PASSIVE_LEVEL = &H00000000& 
Const    DISPATCH_LEVEL = &H00000002& 

const  GEN_SET_DPC_LEVEL = &H00000001& 
const  GEN_SET_NBL_MAKEUP = &H00000002&
const  GEN_USE_MULT_THREAD = &H00000003&
const  GEN_USE_MULT_DPC = &H00000004&
const  GEN_SET_OPERATION_STATUS = &H00000005&
const  GEN_SPLIT_OPERATION = &H00000006&
const  GEN_HOLD_ONTO_NBL = &H00000007&

const  MINI_SEND_COMPLETE_FROM_SEND = &H00000022&
const  MINI_RECEIVE_NBL_WITH_RANDOM_ETHTYPE = &H00000025&
const  MINI_RECEIVE_NBL_FROM_SEND = &H00000023&

const  GEN_VERIFY_DPC_LEVEL = &H00000001& 
const  GEN_VERIFY_NBL_MAKEUP = &H00000002& 
const  GEN_VERIFY_OPERATION_STATUS = &H00000003& 
const  GEN_VERIFY_NBL_ETHTYPE = &H00000004& 
const  GEN_VERIFY_NBL_PASSAGE = &H00000005& 



'<!-- CRC = 0xed43b270 --->
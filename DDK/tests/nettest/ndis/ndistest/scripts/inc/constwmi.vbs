' Below are all the standard WBEM constants

'WbemChangeFlagEnum
Const wbemChangeFlagCreateOrUpdate = &H0&
Const wbemChangeFlagUpdateOnly	= &H1&
Const wbemChangeFlagCreateOnly	= &H2&
Const wbemChangeFlagUpdateCompatible	= &H0&
Const wbemChangeFlagUpdateSafeMode	= &H20&
Const wbemChangeFlagUpdateForceMode	= &H40&
Const wbemChangeFlagStrongValidation	= &H80&
Const wbemChangeFlagAdvisory	= &H10000&

'WbemComparisonFlagEnum
Const wbemFlagReturnImmediately	= &H10&
Const wbemFlagReturnWhenComplete	= &H0&
Const wbemFlagBidirectional	= &H0&
Const wbemFlagForwardOnly	= &H20&
Const wbemFlagNoErrorObject	= &H40&
Const wbemFlagReturnErrorObject	= &H0&
Const wbemFlagSendStatus	= &H80&
Const wbemFlagDontSendStatus	= &H0&
Const wbemFlagEnsureLocatable	= &H100&
Const wbemFlagDirectRead	= &H200&
Const wbemFlagSendOnlySelected	= &H0&
Const wbemFlagUseAmendedQualifiers	= &H20000&
Const wbemFlagGetDefault	= &H0&
Const wbemFlagSpawnInstance	= &H1&
Const wbemFlagUseCurrentTime	= &H1&

'WbemQueryFlagEnum
Const wbemQueryFlagDeep	= 0
Const wbemQueryFlagShallow	= 1
Const wbemQueryFlagPrototype	= 2

'WbemTestFlagEnum
Const wbemTextFlagNoFlavors	= 1

'WbemTimeout
Const wbemTimeoutInfinite	= &Hffffffff&

'WbemComparisonFlagEnum
Const wbemComparisonFlagIncludeAll	= &H0&
Const wbemComparisonFlagIgnoreQualifiers	= &H1&
Const wbemComparisonFlagIgnoreObjectSource	= &H2&
Const wbemComparisonFlagIgnoreDefaultValues	= &H4&
Const wbemComparisonFlagIgnoreClass	= &H8&
Const wbemComparisonFlagIgnoreCase	= &H10&
Const wbemComparisonFlagIgnoreFlavor	= &H20&

'WbemCimtypeEnum
Const wbemCimtypeSint16 = 2         'Signed 16-bit integer 
Const wbemCimtypeSint32 = 3         'Signed 32-bit integer 
Const wbemCimtypeReal32 = 4         '32-bit real number 
Const wbemCimtypeReal64 = 5         '64-bit real number 
Const wbemCimtypeString = 8         'String 
Const wbemCimtypeBoolean = 11       'Boolean value 
Const wbemCimtypeObject = 13        'CIM object 
Const wbemCimtypeSint8 = 16         'Signed 8-bit integer 
Const wbemCimtypeUint8 = 17         'Unsigned 8-bit integer 
Const wbemCimtypeUint16 = 18        'Unsigned 16-bit integer 
Const wbemCimtypeUint32 = 19        'Unsigned 32-bit integer 
Const wbemCimtypeSint64 = 20        'Signed 64-bit integer 
Const wbemCimtypeUint64 = 21        'Unsigned 64-bit integer 
Const wbemCimtypeDatetime = 101     'Date/time value 
Const wbemCimtypeReference = 102    'Reference to a CIM object. 
Const wbemCimtypeChar16 = 103       '16-bit character

'Additional value set
Const ArrayTypeProperty = 8192      'Add this to any of the above to show that its an array

'WbemErrorEnum
Const wbemNoErr	= &H0&
Const wbemErrFailed	= &H80041001&
Const wbemErrNotFound	= &H80041002&
Const wbemErrAccessDenied	= &H80041003&
Const wbemErrProviderFailure	= &H80041004&
Const wbemErrTypeMismatch	= &H80041005&
Const wbemErrOutOfMemory	= &H80041006&
Const wbemErrInvalidContext	= &H80041007&
Const wbemErrInvalidParameter	= &H80041008&
Const wbemErrNotAvailable	= &H80041009&
Const wbemErrCriticalError	= &H8004100a&
Const wbemErrInvalidStream	= &H8004100b&
Const wbemErrNotSupported	= &H8004100c&
Const wbemErrInvalidSuperclass	= &H8004100d&
Const wbemErrInvalidNamespace	= &H8004100e&
Const wbemErrInvalidObject	= &H8004100f&
Const wbemErrInvalidClass	= &H80041010&
Const wbemErrProviderNotFound	= &H80041011&
Const wbemErrInvalidProviderRegistration	= &H80041012&
Const wbemErrProviderLoadFailure	= &H80041013&
Const wbemErrInitializationFailure	= &H80041014&
Const wbemErrTransportFailure	= &H80041015&
Const wbemErrInvalidOperation	= &H80041016&
Const wbemErrInvalidQuery	= &H80041017&
Const wbemErrInvalidQueryType	= &H80041018&
Const wbemErrAlreadyExists	= &H80041019&
Const wbemErrOverrideNotAllowed	= &H8004101a&
Const wbemErrPropagatedQualifier	= &H8004101b&
Const wbemErrPropagatedProperty	= &H8004101c&
Const wbemErrUnexpected	= &H8004101d&
Const wbemErrIllegalOperation	= &H8004101e&
Const wbemErrCannotBeKey	= &H8004101f&
Const wbemErrIncompleteClass	= &H80041020&
Const wbemErrInvalidSyntax	= &H80041021&
Const wbemErrNondecoratedObject	= &H80041022&
Const wbemErrReadOnly	= &H80041023&
Const wbemErrProviderNotCapable	= &H80041024&
Const wbemErrClassHasChildren	= &H80041025&
Const wbemErrClassHasInstances	= &H80041026&
Const wbemErrQueryNotImplemented	= &H80041027&
Const wbemErrIllegalNull	= &H80041028&
Const wbemErrInvalidQualifierType	= &H80041029&
Const wbemErrInvalidPropertyType	= &H8004102a&
Const wbemErrValueOutOfRange	= &H8004102b&
Const wbemErrCannotBeSingleton	= &H8004102c&
Const wbemErrInvalidCimType	= &H8004102d&
Const wbemErrInvalidMethod	= &H8004102e&
Const wbemErrInvalidMethodParameters	= &H8004102f&
Const wbemErrSystemProperty	= &H80041030&
Const wbemErrInvalidProperty	= &H80041031&
Const wbemErrCallCancelled	= &H80041032&
Const wbemErrShuttingDown	= &H80041033&
Const wbemErrPropagatedMethod	= &H80041034&
Const wbemErrUnsupportedParameter	= &H80041035&
Const wbemErrMissingParameter	= &H80041036&
Const wbemErrInvalidParameterId	= &H80041037&
Const wbemErrNonConsecutiveParameterIds	= &H80041038&
Const wbemErrParameterIdOnRetval	= &H80041039&
Const wbemErrInvalidObjectPath	= &H8004103a&
Const wbemErrOutOfDiskSpace	= &H8004103b&
Const wbemErrBufferTooSmall	= &H8004103c&
Const wbemErrUnsupportedPutExtension	= &H8004103d&
Const wbemErrUnknownObjectType	= &H8004103e&
Const wbemErrUnknownPacketType	= &H8004103f&
Const wbemErrMarshalVersionMismatch	= &H80041040&
Const wbemErrMarshalInvalidSignature	= &H80041041&
Const wbemErrInvalidQualifier	= &H80041042&
Const wbemErrInvalidDuplicateParameter	= &H80041043&
Const wbemErrTooMuchData	= &H80041044&
Const wbemErrServerTooBusy	= &H80041045&
Const wbemErrInvalidFlavor	= &H80041046&
Const wbemErrCircularReference	= &H80041047&
Const wbemErrUnsupportedClassUpdate	= &H80041048&
Const wbemErrCannotChangeKeyInheritance	= &H80041049&
Const wbemErrCannotChangeIndexInheritance	= &H80041050&
Const wbemErrTooManyProperties	= &H80041051&
Const wbemErrUpdateTypeMismatch	= &H80041052&
Const wbemErrUpdateOverrideNotAllowed	= &H80041053&
Const wbemErrUpdatePropagatedMethod	= &H80041054&
Const wbemErrMethodNotImplemented	= &H80041055&
Const wbemErrMethodDisabled	= &H80041056&
Const wbemErrRefresherBusy	= &H80041057&
Const wbemErrUnparsableQuery	= &H80041058&
Const wbemErrNotEventClass	= &H80041059&
Const wbemErrMissingGroupWithin	= &H8004105a&
Const wbemErrMissingAggregationList	= &H8004105b&
Const wbemErrPropertyNotAnObject	= &H8004105c&
Const wbemErrAggregatingByObject	= &H8004105d&
Const wbemErrUninterpretableProviderQuery	= &H8004105f&
Const wbemErrBackupRestoreWinmgmtRunning	= &H80041060&
Const wbemErrQueueOverflow	= &H80041061&
Const wbemErrPrivilegeNotHeld	= &H80041062&
Const wbemErrInvalidOperator	= &H80041063&
Const wbemErrLocalCredentials	= &H80041064&
Const wbemErrCannotBeAbstract	= &H80041065&
Const wbemErrAmendedObject	= &H80041066&
Const wbemErrClientTooSlow	= &H80041067&
Const wbemErrNullSecurityDescriptor	= &H80041068&
Const wbemErrTimeout	= &H80041069&
Const wbemErrInvalidAssociation	= &H8004106a&
Const wbemErrAmbiguousOperation	= &H8004106b&
Const wbemErrQuotaViolation	= &H8004106c&
Const wbemErrTransactionConflict	= &H8004106d&
Const wbemErrForcedRollback	= &H8004106e&
Const wbemErrUnsupportedLocale	= &H8004106f&
Const wbemErrHandleOutOfDate	= &H80041070&
Const wbemErrConnectionFailed	= &H80041071&
Const wbemErrInvalidHandleRequest	= &H80041072&
Const wbemErrPropertyNameTooWide	= &H80041073&
Const wbemErrClassNameTooWide	= &H80041074&
Const wbemErrMethodNameTooWide	= &H80041075&
Const wbemErrQualifierNameTooWide	= &H80041076&
Const wbemErrRerunCommand	= &H80041077&
Const wbemErrDatabaseVerMismatch	= &H80041078&
Const wbemErrVetoPut	= &H80041079&
Const wbemErrVetoDelete	= &H8004107a&
Const wbemErrInvalidLocale	= &H80041080&
Const wbemErrProviderSuspended	= &H80041081&
Const wbemErrSynchronizationRequired	= &H80041082&
Const wbemErrNoSchema	= &H80041083&
Const wbemErrProviderAlreadyRegistered	= &H80041084&
Const wbemErrProviderNotRegistered	= &H80041085&
Const wbemErrFatalTransportError	= &H80041086&
Const wbemErrEncryptedConnectionRequired	= &H80041087&
Const wbemErrRegistrationTooBroad	= &H80042001&
Const wbemErrRegistrationTooPrecise	= &H80042002&
Const wbemErrTimedout	= &H80043001&
Const wbemErrResetToDefault	= &H80043002&

'WbemAuthenticationLevelEnum
Const wbemAuthenticationLevelDefault	= 0
Const wbemAuthenticationLevelNone	= 1
Const wbemAuthenticationLevelConnect	= 2
Const wbemAuthenticationLevelCall	= 3
Const wbemAuthenticationLevelPkt	= 4
Const wbemAuthenticationLevelPktIntegrity	= 5
Const wbemAuthenticationLevelPktPrivacy	= 6

'WbemImpersonationLevelEnum
Const wbemImpersonationLevelAnonymous	= 1
Const wbemImpersonationLevelIdentify	= 2
Const wbemImpersonationLevelImpersonate	= 3
Const wbemImpersonationLevelDelegate	= 4

'WbemPrivilegeEnum
Const wbemPrivilegeCreateToken	= 1
Const wbemPrivilegePrimaryToken	= 2
Const wbemPrivilegeLockMemory	= 3
Const wbemPrivilegeIncreaseQuota	= 4
Const wbemPrivilegeMachineAccount	= 5
Const wbemPrivilegeTcb	= 6
Const wbemPrivilegeSecurity	= 7
Const wbemPrivilegeTakeOwnership	= 8
Const wbemPrivilegeLoadDriver	= 9
Const wbemPrivilegeSystemProfile	= 10
Const wbemPrivilegeSystemtime	= 11
Const wbemPrivilegeProfileSingleProcess	= 12
Const wbemPrivilegeIncreaseBasePriority	= 13
Const wbemPrivilegeCreatePagefile	= 14
Const wbemPrivilegeCreatePermanent	= 15
Const wbemPrivilegeBackup	= 16
Const wbemPrivilegeRestore	= 17
Const wbemPrivilegeShutdown	= 18
Const wbemPrivilegeDebug	= 19
Const wbemPrivilegeAudit	= 20
Const wbemPrivilegeSystemEnvironment	= 21
Const wbemPrivilegeChangeNotify	= 22
Const wbemPrivilegeRemoteShutdown	= 23
Const wbemPrivilegeUndock	= 24
Const wbemPrivilegeSyncAgent	= 25
Const wbemPrivilegeEnableDelegation	= 26
Const wbemPrivilegeManageVolume	= 27

'WbemObjectTextFormatEnum
Const wbemObjectTextFormatCIMDTD20	= 1
Const wbemObjectTextFormatWMIDTD20	= 2

'WbemConnectOptionsEnum
Const wbemConnectFlagUseMaxWait	= &H80&



'<!-- CRC = 0xf242e1ac --->
//--------------------------------------------------------------------
// Microsoft OLE DB Test
//
// Copyright (C) 1998-2000 Microsoft Corporation
//
// @doc 
//
// @module IDBPromptInitialize.CPP | IDBPromptInitialize source file for all test modules.
//

#include "modstandard.hpp"

#include <initguid.h>
#include "IDBPromptInitialize.h"

#include <wchar.h>
//#include "CPropSet.hpp"
#include "ServiceComp.h"
//#include "DataSource.hpp"
#include "CDSL_Dialog.hpp"
#include "DSL_DB.hpp"
#include "clib.hpp"
#include <direct.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Module Values
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// {{ TCW_MODULE_GLOBALS
DECLARE_MODULE_CLSID = { 0x406ceea, 0x3b9d, 0x11d2, { 0xb0, 0x25, 0x0, 0xc0, 0x4f, 0xc2, 0x27, 0x93 } };
DECLARE_MODULE_NAME("IDBPromptInitialize");
DECLARE_MODULE_OWNER("microsoft");
DECLARE_MODULE_DESCRIP("Testing IDBPrompInitialize");
DECLARE_MODULE_VERSION(795921705);
// TCW_WizardVersion(2)
// TCW_Automation(True)
// }} TCW_MODULE_GLOBALS_END


extern CSourcesSet		*g_pSourcesSet;

WCHAR		*g_wszUDLFileName	= L".\\__nono.udl";



//WCHAR		*g_wszLuxorServer		= L"jedilab6";
//WCHAR		*g_wszLuxorUserName		= L"oledb";
//WCHAR		*g_wszLuxorPassword		= L"oledb";
WCHAR		*g_wszLuxorBadPassword	= L"badPassword";
WCHAR		*g_wszLuxorInitCat		= L"pubs";
WCHAR		*g_wszInexistentLuxorServerName	= L"GandirePozitiva";

WCHAR		*g_wszDSN				= L"jedilab6";
WCHAR		*g_wszSockeyeUserName	= L"oledb";
WCHAR		*g_wszSockeyePassword	= L"oledb";
WCHAR		*g_wszSockeyeBadPassword= L"badPassword";
WCHAR		*g_wszDSNInitCat		= L"pubs";
WCHAR		*g_wszInexistentDSN		= L"GandirePozitiva";

// use a 3.51 Access database for both Jolt3.51 and Jolt4.0
WCHAR		*g_szLocalAccessDB	= L"c:\\jolt351.mdb";
WCHAR		*g_szRemoteAccessDB	= L"\\\\csipos0\\c$\\school\\Nwind.mdb";
WCHAR		*g_szAccessUserName	= L"Admin";
WCHAR		*g_szAccessGoodPassword	= NULL;
WCHAR		*g_szAccessBadPassword	= L"password";

// Canoe global variables
WCHAR		*g_szOracleServer	= L"goliath";
WCHAR		*g_szCanoeUserName	= L"oledb";
WCHAR		*g_szCanoeGoodPassword	= L"oledb";
WCHAR		*g_szCanoeBadPassword	= L"BadPassword";

WCHAR		*g_rgName[]		= {	L"Prince",
								L"Dead_Oyster",
								L"_Suburban",
								L"Not___Here",
								L"ickyickyickypat",
								L"WheresWaldo_",
								L"___LoxStock",
								L" Yummy",
								L"Gary_Spanky_Spangler",
								L"BakingPowder",
								L"WallaWalla",
								L"DolphinSafeTuna",
								L"IYIYIYIYIYIYIY_Ivo",
								L"AckAck  ",
								L"Good_n_Plenty",
								L"RickOSkippO",
								L"Wilbur_Pig",
								L"ColinTheScott",
								L"TCB_EP",
								L"ElePhant_____",
								L"Im_n_debt",
								L"\?GetOut",
								L"BiteME99\?",
								L"Bye\?Bye",
								L"ByeBye\"Again",
								L"\"Frog\"",
								L"Dolp_hin",
								L"Cat1_Fish2",
								L"\'Pearl",
								L"Captain\'2_",
								L"ball_Point_2Pens",
								L"Ball_Point_2Pens______2",
								L"W_IDENT4",
								L"MiCRoNEWs",
								L"WhereWillItAllEnd.",
								L"W_indjammer",
								L"Elvis2_Walks_",
								L"Pink___",
								L"AMX_BILLS",
								L"shARKSkinJack2et",
								L"Beeieeieeieei",
								L"O\'Malley the ... cat",
								L"=User ID",
								L"User=ID",
								L"User ID=",
								L"==User ID",
								L"User==ID",
								L"User ID==",
								L"User ID;",
								L"User;ID",
								L";User ID",
								L"k;User=ID",
								L"98UserID",
								L"98UserID00",
								L"*User/ID\\",
								L"{UserID}",
								L"[x]User/ID\\",
								L"<UserID>",
								L"@5%$#&()~+-_^:",
								L" ",
								L" YummyAckAck  ",
								L" YAck ",
								L""};

typedef CMap <ULONG_PTR, ULONG_PTR, CWString, CWString&> TABLE;



class CPromptInitialize: public CSessionObject
{
protected:

	IDBPromptInitialize		*m_pIDBPromptInitialize;

	// @cmember Builds a long user name
	BOOL					BuildLongUserName(GUID guid, WCHAR **ppwszName, ULONG ulSize=cMaxName);

	TABLE					m_InternationalStrings;
	CLSID					m_ProviderCLSID;
	CPropSets				m_PropSets;

	CWString				m_pwszInitDataSource;
	CWString				m_pwszUserID;
	CWString				m_pwszPassword;

public:

	static HWND				s_hMainWnd;

	CPromptInitialize(WCHAR *wstrTestCaseName);
	virtual ~CPromptInitialize() {;}

	BOOL		GetInternationalStrings();


	// creates an initialized DSO based on provider's guid and properties
	HRESULT		CreateInitDSO(
		GUID		clsidProvider, 
		CPropSets	*pPropSets, 
		REFIID		riid,
		IUnknown	**ppIUnknown
	);

	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	BOOL		CreateSQLServerUser(
		IUnknown	*pIUnknown,		// initialized DSO
		LPCWSTR		pwszUserID, 
		LPCWSTR		pwszPassword,
		LPCWSTR		pwszDBName = NULL
	);
	BOOL		CreateSQLServerDB(
		IUnknown	*pIUnknown,		// initialized DSO
		LPCWSTR pwszDBName
	);

	BOOL		DropSQLServerUser(
		IUnknown	*pIUnknown,		// initialized DSO
		LPCWSTR		pwszUserID 
	);
	BOOL		DropSQLServerDB(
		IUnknown	*pIUnknown,		// initialized DSO
		LPCWSTR pwszDBName
	);

	BOOL		CreateOracleUser(
		IUnknown	*pIUnknown,		// initialized DSO
		LPCWSTR		pwszUserID, 
		LPCWSTR		pwszPassword,
		LPCWSTR		pwszDBName = NULL
	);

	BOOL		DropOracleUser(
		IUnknown	*pIUnknown,		// initialized DSO
		LPCWSTR		pwszUserID 
	);
};



// {{ TCW_TEST_CASE_MAP(LuxorConnection)
//*-----------------------------------------------------------------------
// @class test connection dialog for Luxor
//
class LuxorConnection : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(LuxorConnection,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Set server name, user name, blank password, uncheck save password
	int Variation_1();
	// @cmember Set server name, user name, blank password, check save password
	int Variation_2();
	// @cmember Set server name, user name, password, uncheck save password
	int Variation_3();
	// @cmember Set server name, user name, password, check save password
	int Variation_4();
	// @cmember Server name, integrated security
	int Variation_5();
	// @cmember Check server names against Luxor enumerator
	int Variation_6();
	// @cmember Set inexistent server name
	int Variation_7();
	// @cmember Various values for user name
	int Variation_8();
	// @cmember Various values for password
	int Variation_9();
	// @cmember International name provided for user, password, server
	int Variation_10();
	// @cmember Long user name
	int Variation_11();
	// @cmember Long server name
	int Variation_12();
	// @cmember Long password
	int Variation_13();
	// @cmember Bad password for existing user
	int Variation_14();
	// @cmember Bad password for existing user, push the Test button
	int Variation_15();
	// @cmember Set initial catalog name
	int Variation_16();
	// @cmember Set server name and chose from the init catalog list
	int Variation_17();
	// @cmember Atach a database file as a database name
	int Variation_18();
	// @cmember International strings as user names
	int Variation_19();
	// @cmember International strings as passwords
	int Variation_20();
	// @cmember International strings as initial catalogs
	int Variation_21();
	// @cmember International strings as server name
	int Variation_22();
	// @cmember International strings used for user name, password, initial catalog
	int Variation_23();
	// @cmember Check delay for displaying Connection Property Page
	int Variation_24();
	// @cmember Check delay in seeking network for SQL servers
	int Variation_25();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(LuxorConnection)
#define THE_CLASS LuxorConnection
BEG_TEST_CASE(LuxorConnection, CPromptInitialize, L"test connection dialog for Luxor")
	TEST_VARIATION(1, 		L"Set server name, user name, blank password, uncheck save password")
	TEST_VARIATION(2, 		L"Set server name, user name, blank password, check save password")
	TEST_VARIATION(3, 		L"Set server name, user name, password, uncheck save password")
	TEST_VARIATION(4, 		L"Set server name, user name, password, check save password")
	TEST_VARIATION(5, 		L"Server name, integrated security")
	TEST_VARIATION(6, 		L"Check server names against Luxor enumerator")
	TEST_VARIATION(7, 		L"Set inexistent server name")
	TEST_VARIATION(8, 		L"Various values for user name")
	TEST_VARIATION(9, 		L"Various values for password")
	TEST_VARIATION(10, 		L"International name provided for user, password, server")
	TEST_VARIATION(11, 		L"Long user name")
	TEST_VARIATION(12, 		L"Long server name")
	TEST_VARIATION(13, 		L"Long password")
	TEST_VARIATION(14, 		L"Bad password for existing user")
	TEST_VARIATION(15, 		L"Bad password for existing user, push the Test button")
	TEST_VARIATION(16, 		L"Set initial catalog name")
	TEST_VARIATION(17, 		L"Set server name and chose from the init catalog list")
	TEST_VARIATION(18, 		L"Atach a database file as a database name")
	TEST_VARIATION(19, 		L"International strings as user names")
	TEST_VARIATION(20, 		L"International strings as passwords")
	TEST_VARIATION(21, 		L"International strings as initial catalogs")
	TEST_VARIATION(22, 		L"International strings as server name")
	TEST_VARIATION(23, 		L"International strings used for user name, password, initial catalog")
	TEST_VARIATION(24,		L"Delay in displaying Connection Property Page")
	TEST_VARIATION(25,		L"Delay in seeking network for SQL Servers")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END





// {{ TCW_TEST_CASE_MAP(SockeyeConnection)
//*-----------------------------------------------------------------------
// @class test connection dialog for Sockeye
//
class SockeyeConnection : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(SockeyeConnection,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Set data source name, user name, blank password, uncheck save password
	int Variation_1();
	// @cmember Set data source name, user name, blank password, check save password
	int Variation_2();
	// @cmember Set data source name, user name, password, uncheck save password
	int Variation_3();
	// @cmember Set data source name, user name, password, check save password
	int Variation_4();
	// @cmember International name provided for user, password, data source name
	int Variation_5();
	// @cmember Various values for user name
	int Variation_6();
	// @cmember Various values for password
	int Variation_7();
	// @cmember Long user name
	int Variation_8();
	// @cmember Long data source name
	int Variation_9();
	// @cmember Long password
	int Variation_10();
	// @cmember Check data source names against Sockeye enumerator
	int Variation_11();
	// @cmember Bad password for existing user
	int Variation_12();
	// @cmember Bad password for existing user, push the Test button
	int Variation_13();
	// @cmember Provide initial catalog name
	int Variation_14();
	// @cmember International strings as user names
	int Variation_15();
	// @cmember International strings as passwords
	int Variation_16();
	// @cmember International strings as initial catalogs
	int Variation_17();
	// @cmember International strings as datasource names
	int Variation_18();
	// @cmember International strings for a complete connection
	int Variation_19();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(SockeyeConnection)
#define THE_CLASS SockeyeConnection
BEG_TEST_CASE(SockeyeConnection, CPromptInitialize, L"test connection dialog for Sockeye")
	TEST_VARIATION(1, 		L"Set data source name, user name, blank password, uncheck save password")
	TEST_VARIATION(2, 		L"Set data source name, user name, blank password, check save password")
	TEST_VARIATION(3, 		L"Set data source name, user name, password, uncheck save password")
	TEST_VARIATION(4, 		L"Set data source name, user name, password, check save password")
	TEST_VARIATION(5, 		L"International name provided for user, password, data source name")
	TEST_VARIATION(6, 		L"Various values for user name")
	TEST_VARIATION(7, 		L"Various values for password")
	TEST_VARIATION(8, 		L"Long user name")
	TEST_VARIATION(9, 		L"Long data source name")
	TEST_VARIATION(10, 		L"Long password")
	TEST_VARIATION(11, 		L"Check data source names against Sockeye enumerator")
	TEST_VARIATION(12, 		L"Bad password for existing user")
	TEST_VARIATION(13, 		L"Bad password for existing user, push the Test button")
	TEST_VARIATION(14, 		L"Provide initial catalog name")
	TEST_VARIATION(15, 		L"International strings as user names")
	TEST_VARIATION(16, 		L"International strings as passwords")
	TEST_VARIATION(17, 		L"International strings as initial catalogs")
	TEST_VARIATION(18, 		L"International strings as datasource names")
	TEST_VARIATION(19, 		L"International strings for a complete connection")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END





// {{ TCW_TEST_CASE_MAP(Jolt40Connection)
//*-----------------------------------------------------------------------
// @class test connection dialog for  Jolt40
//
class Jolt40Connection : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(Jolt40Connection,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember General test: select the provider, select or chose a database name, go for authentification, ok
	int Variation_1();
	// @cmember General case, press Test Connection
	int Variation_2();
	// @cmember general test: select the provider, select or chose a remote database name, go for authentification, ok
	int Variation_3();
	// @cmember Various values for user name
	int Variation_4();
	// @cmember Various values for password
	int Variation_5();
	// @cmember International database name, user name, password
	int Variation_6();
	// @cmember A long database name, user name and password
	int Variation_7();
	// @cmember Password and save password
	int Variation_8();
	// @cmember Password and don't save password
	int Variation_9();
	// @cmember Blank password, save password
	int Variation_10();
	// @cmember Blank password, do not save password
	int Variation_11();
	// @cmember Bad password for an existing user
	int Variation_12();
	// @cmember Bad password for an existing user; test connection button
	int Variation_13();
	// @cmember Pop up the browser dialog
	int Variation_14();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(Jolt40Connection)
#define THE_CLASS Jolt40Connection
BEG_TEST_CASE(Jolt40Connection, CPromptInitialize, L"test connection dialog for  Jolt40")
	TEST_VARIATION(1, 		L"General test: select the provider, select or chose a database name, go for authentification, ok")
	TEST_VARIATION(2, 		L"General case, press Test Connection")
	TEST_VARIATION(3, 		L"general test: select the provider, select or chose a remote database name, go for authentification, ok")
	TEST_VARIATION(4, 		L"Various values for user name")
	TEST_VARIATION(5, 		L"Various values for password")
	TEST_VARIATION(6, 		L"International database name, user name, password")
	TEST_VARIATION(7, 		L"A long database name, user name and password")
	TEST_VARIATION(8, 		L"Password and save password")
	TEST_VARIATION(9, 		L"Password and don't save password")
	TEST_VARIATION(10, 		L"Blank password, save password")
	TEST_VARIATION(11, 		L"Blank password, do not save password")
	TEST_VARIATION(12, 		L"Bad password for an existing user")
	TEST_VARIATION(13, 		L"Bad password for an existing user; test connection button")
	TEST_VARIATION(14, 		L"Pop up the browser dialog")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END





// {{ TCW_TEST_CASE_MAP(MSDAORAConnection)
//*-----------------------------------------------------------------------
// @class test connection dialog for  MSDAORA
//
class MSDAORAConnection : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(MSDAORAConnection,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember General test: select the provider, select or chose a name, go for authentification, ok
	int Variation_1();
	// @cmember General case, press Test Connection
	int Variation_2();
	// @cmember Various values for user name
	int Variation_3();
	// @cmember Various values for password
	int Variation_4();
	// @cmember International server name, user name and password
	int Variation_5();
	// @cmember A long server name, user name and password
	int Variation_6();
	// @cmember Password and save password
	int Variation_7();
	// @cmember Password and don't save password
	int Variation_8();
	// @cmember Blank password, save password
	int Variation_9();
	// @cmember Blank password, do not save password
	int Variation_10();
	// @cmember Bad password for an existing user
	int Variation_11();
	// @cmember Bad password for an existing user; test connection button
	int Variation_12();
	// @cmember International strings as user names
	int Variation_13();
	// @cmember International strings as passwords
	int Variation_14();
	// @cmember International strings as server names
	int Variation_15();
	// @cmember International user name and password, initialize DSO
	int Variation_16();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(MSDAORAConnection)
#define THE_CLASS MSDAORAConnection
BEG_TEST_CASE(MSDAORAConnection, CPromptInitialize, L"test connection dialog for  MSDAORA")
	TEST_VARIATION(1, 		L"General test: select the provider, select or chose a name, go for authentification, ok")
	TEST_VARIATION(2, 		L"General case, press Test Connection")
	TEST_VARIATION(3, 		L"Various values for user name")
	TEST_VARIATION(4, 		L"Various values for password")
	TEST_VARIATION(5, 		L"International server name, user name and password")
	TEST_VARIATION(6, 		L"A long server name, user name and password")
	TEST_VARIATION(7, 		L"Password and save password")
	TEST_VARIATION(8, 		L"Password and don't save password")
	TEST_VARIATION(9, 		L"Blank password, save password")
	TEST_VARIATION(10, 		L"Blank password, do not save password")
	TEST_VARIATION(11, 		L"Bad password for an existing user")
	TEST_VARIATION(12, 		L"Bad password for an existing user; test connection button")
	TEST_VARIATION(13, 		L"International strings as user names")
	TEST_VARIATION(14, 		L"International strings as passwords")
	TEST_VARIATION(15, 		L"International strings as server names")
	TEST_VARIATION(16, 		L"International user name and password, initialize DSO")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END




// {{ TCW_TEST_CASE_MAP(GeneralConnection)
//*-----------------------------------------------------------------------
// @class general connection dialog testing
//
class GeneralConnection : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

	BOOL		Common_ANSI_OEM_Scenario(
					BOOL	fUseANSIToCreateUDLFile,
					BOOL	fUseANSIToPopUpDialog
				);

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(GeneralConnection,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Goto Connection page using the Next button in the provider page
	int Variation_1();
	// @cmember Check radio button in the integrated/standard security group
	int Variation_2();
	// @cmember Create and initialize several DSOs using DSL, release them, bring up DSL and select provider; check that only default props are set
	int Variation_3();
	// @cmember Check the list of init catalogs
	int Variation_4();
	// @cmember Bring up the DSL dialog, select provider, drop down the init catalog combo box, close
	int Variation_5();
	// @cmember ANSI -> ANSI
	int Variation_6();
	// @cmember OEM -> OEM
	int Variation_7();
	// @cmember ANSI -> OEM
	int Variation_8();
	// @cmember OEM -> ANSI
	int Variation_9();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(GeneralConnection)
#define THE_CLASS GeneralConnection
BEG_TEST_CASE(GeneralConnection, CPromptInitialize, L"general connection dialog testing")
	TEST_VARIATION(1, 		L"Goto Connection page using the Next button in the provider page")
	TEST_VARIATION(2, 		L"Check radio button in the integrated/standard security group")
	TEST_VARIATION(3, 		L"Create and initialize several DSOs using DSL, release them, bring up DSL and select provider; check that only default props are set")
	TEST_VARIATION(4, 		L"Check the list of init catalogs")
	TEST_VARIATION(5, 		L"Bring up the DSL dialog, select provider, drop down the init catalog combo box, close")
	TEST_VARIATION(6, 		L"ANSI -> ANSI")
	TEST_VARIATION(7, 		L"OEM -> OEM")
	TEST_VARIATION(8, 		L"ANSI -> OEM")
	TEST_VARIATION(9, 		L"OEM -> ANSI")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END




// {{ TCW_TEST_CASE_MAP(CDSOAndRIID)
//*-----------------------------------------------------------------------
// @class various values for ppDataSource in IDBPromptInitialize::PromptDataSource
//
class CDSOAndRIID : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(CDSOAndRIID,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember NULL ppDataSource => E_INVALIDARG
	int Variation_1();
	// @cmember Inexistent DSO (NULL *ppDataSource) => general interface checking for returned DSO
	int Variation_2();
	// @cmember Pass a session pointer as *ppDataSource => E_INVALIDARG
	int Variation_3();
	// @cmember Pass an existent, uninitialized DSO (not aggregated with SC)
	int Variation_4();
	// @cmember Pass an existent, uninitialized DSO (aggregated with SC)
	int Variation_5();
	// @cmember Pass an existent, initialized DSO (not aggregated with SC)
	int Variation_6();
	// @cmember Pass an existent, initialized DSO (aggregated with SC)
	int Variation_7();
	// @cmember Existent, uninitialized DSO, select another provider
	int Variation_8();
	// @cmember Existent, uninit DSO, test with another provider, reselect original provider
	int Variation_9();
	// @cmember Existent, uninit DSO, select and test another provider, CANCEL
	int Variation_10();
	// @cmember Existent, uninit DSO, ask a different interface
	int Variation_11();
	// @cmember Existent, uninit DSO, ask a different interface, CANCEL
	int Variation_12();
	// @cmember riid is IID_NULL => E_NOINTERFACE
	int Variation_13();
	// @cmember riid is IID_IUnknown => S_OK
	int Variation_14();
	// @cmember riid is IID_IDBCreateSession (mandatory)
	int Variation_15();
	// @cmember riid is IID_IDBInitialize (mandatory) => S_OK
	int Variation_16();
	// @cmember riid is IID_IDBProperties (mandatory)=> S_OK
	int Variation_17();
	// @cmember riid is IID_IPersist (mandatory)
	int Variation_18();
	// @cmember riid is IID_IConnectionPointContainer (optional)
	int Variation_19();
	// @cmember riid is IID_IDBAsynchStatus (optional)
	int Variation_20();
	// @cmember riid is IID_IDBDataSourceAdmin (optional)
	int Variation_21();
	// @cmember riid is IID_IDBInfo (optional)
	int Variation_22();
	// @cmember riid is IID_IPersistFile (optional)
	int Variation_23();
	// @cmember riid is IID_ISupportErrorInfo (optional)
	int Variation_24();
	// @cmember riid is IID_IServiceProvider (extensible UI)
	int Variation_25();
	// @cmember riid is IID_IOpenRowset => E_NOINTERFACE
	int Variation_26();
	// @cmember Check that all the OLE DB providers appear in the provider page
	int Variation_27();
	// @cmember Existent DSO, error, check *ppDataSource is preserved
	int Variation_28();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(CDSOAndRIID)
#define THE_CLASS CDSOAndRIID
BEG_TEST_CASE(CDSOAndRIID, CPromptInitialize, L"various values for ppDataSource in IDBPromptInitialize::PromptDataSource")
	TEST_VARIATION(1, 		L"NULL ppDataSource => E_INVALIDARG")
	TEST_VARIATION(2, 		L"Inexistent DSO (NULL *ppDataSource) => general interface checking for returned DSO")
	TEST_VARIATION(3, 		L"Pass a session pointer as *ppDataSource => E_INVALIDARG")
	TEST_VARIATION(4, 		L"Pass an existent, uninitialized DSO (not aggregated with SC)")
	TEST_VARIATION(5, 		L"Pass an existent, uninitialized DSO (aggregated with SC)")
	TEST_VARIATION(6, 		L"Pass an existent, initialized DSO (not aggregated with SC)")
	TEST_VARIATION(7, 		L"Pass an existent, initialized DSO (aggregated with SC)")
	TEST_VARIATION(8, 		L"Existent, uninitialized DSO, select another provider")
	TEST_VARIATION(9, 		L"Existent, uninit DSO, test with another provider, reselect original provider")
	TEST_VARIATION(10, 		L"Existent, uninit DSO, select and test another provider, CANCEL")
	TEST_VARIATION(11, 		L"Existent, uninit DSO, ask a different interface")
	TEST_VARIATION(12, 		L"Existent, uninit DSO, ask a different interface, CANCEL")
	TEST_VARIATION(13, 		L"riid is IID_NULL => E_NOINTERFACE")
	TEST_VARIATION(14, 		L"riid is IID_IUnknown => S_OK")
	TEST_VARIATION(15, 		L"riid is IID_IDBCreateSession (mandatory)")
	TEST_VARIATION(16, 		L"riid is IID_IDBInitialize (mandatory) => S_OK")
	TEST_VARIATION(17, 		L"riid is IID_IDBProperties (mandatory)=> S_OK")
	TEST_VARIATION(18, 		L"riid is IID_IPersist (mandatory)")
	TEST_VARIATION(19, 		L"riid is IID_IConnectionPointContainer (optional)")
	TEST_VARIATION(20, 		L"riid is IID_IDBAsynchStatus (optional)")
	TEST_VARIATION(21, 		L"riid is IID_IDBDataSourceAdmin (optional)")
	TEST_VARIATION(22, 		L"riid is IID_IDBInfo (optional)")
	TEST_VARIATION(23, 		L"riid is IID_IPersistFile (optional)")
	TEST_VARIATION(24, 		L"riid is IID_ISupportErrorInfo (optional)")
	TEST_VARIATION(25, 		L"riid is IID_IServiceProvider (extensible UI)")
	TEST_VARIATION(26, 		L"riid is IID_IOpenRowset => E_NOINTERFACE")
	TEST_VARIATION(27, 		L"Check that all the OLE DB providers appear in the provider page")
	TEST_VARIATION(28, 		L"Existent DSO, error, check *ppDataSource is preserved")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END

// {{ TCW_TEST_CASE_MAP(CAggregation)
//*-----------------------------------------------------------------------
// @class aggregation cases for IDBPromptInitialize::PromptDataSource
//
class CAggregation : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(CAggregation,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Aggregation, ask for IID_IUnknown, inexistent DSO
	int Variation_1();
	// @cmember Aggregation, ask for IID_IUnknown, existent DSO, not aggregated with pIUnkOuter => DB_E_NOAGGREGATION
	int Variation_2();
	// @cmember Aggregation, ask for IID_IUnknown, existent DSO, already aggregated with pIUnkOuter => DB_E_NOAGGREGATION
	int Variation_3();
	// @cmember Aggregation, riid is not IID_IUnknown => DB_E_NOAGGREGATION
	int Variation_4();
	// @cmember Aggregation, general interface checking on the returned DSO
	int Variation_5();
	// @cmember Aggregation, create session and call IGetDataSource::GetDataSource
	int Variation_6();
	// @cmember Agg, select prov. Test conn. Move to another prov. Test conn. Check reference counter on outer obj
	int Variation_7();
	// @cmember Aggegated, existent DSO. Ask for a different interface.
	int Variation_8();
	// @cmember Aggegated, existent DSO. Select a different provider.
	int Variation_9();
	// @cmember Aggregation, bad prompt options => make sure the ref count is the same.
	int Variation_10();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(CAggregation)
#define THE_CLASS CAggregation
BEG_TEST_CASE(CAggregation, CPromptInitialize, L"aggregation cases for IDBPromptInitialize::PromptDataSource")
	TEST_VARIATION(1, 		L"Aggregation, ask for IID_IUnknown, inexistent DSO")
	TEST_VARIATION(2, 		L"Aggregation, ask for IID_IUnknown, existent DSO, not aggregated with pIUnkOuter => DB_E_NOAGGREGATION")
	TEST_VARIATION(3, 		L"Aggregation, ask for IID_IUnknown, existent DSO, already aggregated with pIUnkOuter => DB_E_NOAGGREGATION")
	TEST_VARIATION(4, 		L"Aggregation, riid is not IID_IUnknown => DB_E_NOAGGREGATION")
	TEST_VARIATION(5, 		L"Aggregation, general interface checking on the returned DSO")
	TEST_VARIATION(6, 		L"Aggregation, create session and call IGetDataSource::GetDataSource")
	TEST_VARIATION(7, 		L"Agg, select prov. Test conn. Move to another prov. Test conn. Check reference counter on outer obj")
	TEST_VARIATION(8, 		L"Aggegated, existent DSO. Ask for a different interface.")
	TEST_VARIATION(9, 		L"Aggegated, existent DSO. Select a different provider.")
	TEST_VARIATION(10, 		L"Aggregation, bad prompt options => make sure the ref count is the same.")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END

// {{ TCW_TEST_CASE_MAP(CSourceTypeFilter)
//*-----------------------------------------------------------------------
// @class Source type filters in IDBPromptInitialize::PromptDataSource
//
class CSourceTypeFilter : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(CSourceTypeFilter,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember 0 == cSourceTypeFilter and NULL == rgSourceTypeFilter => S_OK
	int Variation_1();
	// @cmember 0 != cSourceTypeFilter and NULL == rgSourceTypeFilter	=> E_INVALIDARG
	int Variation_2();
	// @cmember 0 == cSourceTypeFilter and NULL != rgSourceTypeFilter	=> S_OK
	int Variation_3();
	// @cmember Valid source filter made of: DBSOURCETYPE_DATASOURCE, DBSOURCETYPE_DATASOURCE_TDP and DBSOURCETYPE_DATASOURCE_MDP
	int Variation_4();
	// @cmember Call IDBPromptInitialize::PromptDataSource in a loop, with and without filter; the DSO pointer obtained in the first call is used in the second one
	int Variation_5();
	// @cmember Use enumerators as source filter => DB_E_NOPROVIDERREGISTERED
	int Variation_6();
	// @cmember Inexistent source type filter => DB_E_NOPROVIDERREGISTERED
	int Variation_7();
	// @cmember Long source type filter
	int Variation_8();
	// @cmember Filter with DBSOURCETYPE_DATASOURCE_TDP, then with DBSOURCETYPE_DATASOURCE_MDP
	int Variation_9();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(CSourceTypeFilter)
#define THE_CLASS CSourceTypeFilter
BEG_TEST_CASE(CSourceTypeFilter, CPromptInitialize, L"Source type filters in IDBPromptInitialize::PromptDataSource")
	TEST_VARIATION(1, 		L"0 == cSourceTypeFilter and NULL == rgSourceTypeFilter => S_OK")
	TEST_VARIATION(2, 		L"0 != cSourceTypeFilter and NULL == rgSourceTypeFilter	=> E_INVALIDARG")
	TEST_VARIATION(3, 		L"0 == cSourceTypeFilter and NULL != rgSourceTypeFilter	=> S_OK")
	TEST_VARIATION(4, 		L"Valid source filter made of: DBSOURCETYPE_DATASOURCE, DBSOURCETYPE_DATASOURCE_TDP and DBSOURCETYPE_DATASOURCE_MDP")
	TEST_VARIATION(5, 		L"Call IDBPromptInitialize::PromptDataSource in a loop, with and without filter; the DSO pointer obtained in the first call is used in the second one")
	TEST_VARIATION(6, 		L"Use enumerators as source filter => DB_E_NOPROVIDERREGISTERED")
	TEST_VARIATION(7, 		L"Inexistent source type filter => DB_E_NOPROVIDERREGISTERED")
	TEST_VARIATION(8, 		L"Long source type filter")
	TEST_VARIATION(9, 		L"Filter with DBSOURCETYPE_DATASOURCE_TDP, then with DBSOURCETYPE_DATASOURCE_MDP")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END

// {{ TCW_TEST_CASE_MAP(CProviderFilter)
//*-----------------------------------------------------------------------
// @class Provider name filtering in IDBPromptInitialize::PromptDataSource
//
class CProviderFilter : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(CProviderFilter,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Inexistent progID provided as a filter => it should be ignored
	int Variation_1();
	// @cmember Filter made of both existent and inexistent progIDs
	int Variation_2();
	// @cmember Filter on providers that allows multiple source type (OLAP)
	int Variation_3();
	// @cmember Singleton filter on each OLE DB provider returned by the enumerator (also check that the active page is the connection one)
	int Variation_4();
	// @cmember Singleton filter on each OLE DB provider returned by the enumerator (using the version independent progID)
	int Variation_5();
	// @cmember Existent DSO, filter name doesn't match the current provider
	int Variation_6();
	// @cmember Bad filter followed by good filter (for each provider)
	int Variation_7();
	// @cmember Long filter for provider name
	int Variation_8();
	// @cmember Empty filter string
	int Variation_9();
	// @cmember Bad filter progID (international string)
	int Variation_10();
	// @cmember Long filter followed by a short filter
	int Variation_11();
	// @cmember Short filter followed by a long filter
	int Variation_12();
	// @cmember Filter, no filter. Repeat.
	int Variation_13();
	// @cmember Use non typo characters in filter (like \t and \n)
	int Variation_14();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(CProviderFilter)
#define THE_CLASS CProviderFilter
BEG_TEST_CASE(CProviderFilter, CPromptInitialize, L"Provider name filtering in IDBPromptInitialize::PromptDataSource")
	TEST_VARIATION(1, 		L"Inexistent progID provided as a filter => it should be ignored")
	TEST_VARIATION(2, 		L"Filter made of both existent and inexistent progIDs")
	TEST_VARIATION(3, 		L"Filter on providers that allows multiple source type (OLAP)")
	TEST_VARIATION(4, 		L"Singleton filter on each OLE DB provider returned by the enumerator (also check that the active page is the connection one)")
	TEST_VARIATION(5, 		L"Singleton filter on each OLE DB provider returned by the enumerator (using the version independent progID)")
	TEST_VARIATION(6, 		L"Existent DSO, filter name doesn't match the current provider")
	TEST_VARIATION(7, 		L"Bad filter followed by good filter (for each provider)")
	TEST_VARIATION(8, 		L"Long filter for provider name")
	TEST_VARIATION(9, 		L"Empty filter string")
	TEST_VARIATION(10, 		L"Bad filter progID (international string)")
	TEST_VARIATION(11, 		L"Long filter followed by a short filter")
	TEST_VARIATION(12, 		L"Short filter followed by a long filter")
	TEST_VARIATION(13, 		L"Filter, no filter. Repeat.")
	TEST_VARIATION(14, 		L"Use non typo characters in filter (like \t and \n)")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END

// {{ TCW_TEST_CASE_MAP(CMixFilters)
//*-----------------------------------------------------------------------
// @class Mixes source type filtering and provider name filtering in IDBPromptInitialize::PromptDataSource
//
class CMixFilters : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(CMixFilters,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Mixed filter (source type + provider names)
	int Variation_1();
	// @cmember Bad mixed filter: DBSOURCETYPE_DATASOURCE source type and provider of type DBSOURCETYPE_DATASOURCE_TDP
	int Variation_2();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(CMixFilters)
#define THE_CLASS CMixFilters
BEG_TEST_CASE(CMixFilters, CPromptInitialize, L"Mixes source type filtering and provider name filtering in IDBPromptInitialize::PromptDataSource")
	TEST_VARIATION(1, 		L"Mixed filter (source type + provider names)")
	TEST_VARIATION(2, 		L"Bad mixed filter: DBSOURCETYPE_DATASOURCE source type and provider of type DBSOURCETYPE_DATASOURCE_TDP")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END

// {{ TCW_TEST_CASE_MAP(CPromptOptions)
//*-----------------------------------------------------------------------
// @class prompt options in IDBPromptInitialize::PromptDataSource
//
class CPromptOptions : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

	// Verifies DBPROMPTOPTIONS_DISABLESAVEPASSWORD with existing DSO
	BOOL	CheckDisSavePasswdOnExistingDSO(
		CLSID	clsidProvider, 
		BOOL	fDisableSavePassword,
		BOOL	fInvokeSC,
		BOOL	fPersistSecurityInfo
	);

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(CPromptOptions,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Not flags at all => E_INVALIDARG
	int Variation_1();
	// @cmember Use DBPROMPTOPTIONS_PROPERTYSHEET
	int Variation_2();
	// @cmember Use DBPROMPTOPTIONS_WIZARDSHEET
	int Variation_3();
	// @cmember Existent DSO (with/without SC) or inexistent DSO and ask for DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION
	int Variation_4();
	// @cmember Single provider filter, existent DSO with/without SC / inexistent DSO, use DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION
	int Variation_5();
	// @cmember Single provider filter, existent DSO with/without SC / inexistent DSO, do not use DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION
	int Variation_6();
	// @cmember NULL == *ppDataSource and ask for disable provider selection => E_INVALIDARG
	int Variation_7();
	// @cmember Use DBPROMPTOPTIONS_DISABLESAVEPASSWORD to create a new DSO
	int Variation_8();
	// @cmember Use DBPROMPTOPTIONS_DISABLESAVEPASSWORD to update an existing DSO
	int Variation_9();
	// @cmember Use DBPROMPTOPTIONS_DISABLESAVEPASSWORD and try to set Persist Sensitive Info in the Summary Page
	int Variation_10();
	// @cmember Use registry key to enable saving password (call with and without DBPROMPTOPTIONS_DISABLESAVEPASSWORD)
	int Variation_11();
	// @cmember Use registry key to disable saving password (call with and without DBPROMPTOPTIONS_DISABLESAVEPASSWORD)
	int Variation_12();
	// @cmember Inexistent flags => E_INVALIDARG
	int Variation_13();
	// @cmember DBPROMPTOPTIONS_WIZARDSHEET | DBPROMPTOPTIONS_PROPERTYSHEET
	int Variation_14();
	// @cmember Use valid flags, but not DBPROMPTOPTIONS_PROPERTYSHEET or DBPROMPTOPTIONS_WIZARDSHEET
	int Variation_15();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(CPromptOptions)
#define THE_CLASS CPromptOptions
BEG_TEST_CASE(CPromptOptions, CPromptInitialize, L"prompt options in IDBPromptInitialize::PromptDataSource")
	TEST_VARIATION(1, 		L"Not flags at all => E_INVALIDARG")
	TEST_VARIATION(2, 		L"Use DBPROMPTOPTIONS_PROPERTYSHEET")
	TEST_VARIATION(3, 		L"Use DBPROMPTOPTIONS_WIZARDSHEET")
	TEST_VARIATION(4, 		L"Existent DSO (with/without SC) or inexistent DSO and ask for DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION")
	TEST_VARIATION(5, 		L"Single provider filter, existent DSO with/without SC / inexistent DSO, use DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION")
	TEST_VARIATION(6, 		L"Single provider filter, existent DSO with/without SC / inexistent DSO, do not use DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION")
	TEST_VARIATION(7, 		L"NULL == *ppDataSource and ask for disable provider selection => E_INVALIDARG")
	TEST_VARIATION(8, 		L"Use DBPROMPTOPTIONS_DISABLESAVEPASSWORD to create a new DSO")
	TEST_VARIATION(9, 		L"Use DBPROMPTOPTIONS_DISABLESAVEPASSWORD to update an existing DSO")
	TEST_VARIATION(10, 		L"Use DBPROMPTOPTIONS_DISABLESAVEPASSWORD and try to set Persist Sensitive Info in the Summary Page")
	TEST_VARIATION(11, 		L"Use registry key to enable saving password (call with and without DBPROMPTOPTIONS_DISABLESAVEPASSWORD)")
	TEST_VARIATION(12, 		L"Use registry key to disable saving password (call with and without DBPROMPTOPTIONS_DISABLESAVEPASSWORD)")
	TEST_VARIATION(13, 		L"Inexistent flags => E_INVALIDARG")
	TEST_VARIATION(14, 		L"DBPROMPTOPTIONS_WIZARDSHEET | DBPROMPTOPTIONS_PROPERTYSHEET")
	TEST_VARIATION(15, 		L"Use valid flags, but not DBPROMPTOPTIONS_PROPERTYSHEET or DBPROMPTOPTIONS_WIZARDSHEET")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END

// {{ TCW_TEST_CASE_MAP(CParentWindow)
//*-----------------------------------------------------------------------
// @class values for hWndParent in IDBPromptInitialize::PromptDataSource
//
class CParentWindow : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(CParentWindow,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember NULL hWndParent => S_OK
	int Variation_1();
	// @cmember hWndParent is the desktop area => centerd to the screen
	int Variation_2();
	// @cmember hWndParent  is LTM window
	int Variation_3();
	// @cmember Parent window is not entirely contained in the screen (center is)
	int Variation_4();
	// @cmember Parent window is not entirely contained in the screen (center is not)
	int Variation_5();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(CParentWindow)
#define THE_CLASS CParentWindow
BEG_TEST_CASE(CParentWindow, CPromptInitialize, L"values for hWndParent in IDBPromptInitialize::PromptDataSource")
	TEST_VARIATION(1, 		L"NULL hWndParent => S_OK")
	TEST_VARIATION(2, 		L"hWndParent is the desktop area => centerd to the screen")
	TEST_VARIATION(3, 		L"hWndParent  is LTM window")
	TEST_VARIATION(4, 		L"Parent window is not entirely contained in the screen (center is)")
	TEST_VARIATION(5, 		L"Parent window is not entirely contained in the screen (center is not)")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END



// {{ TCW_TEST_CASE_MAP(CGenericOp)
//*-----------------------------------------------------------------------
// @class all kinds of scenarios that don't go anywhere else
//
class CGenericOp : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(CGenericOp,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Check the Next button in the provider page
	int Variation_1();
	// @cmember Use a long UDL file
	int Variation_2();
	// @cmember Create a UDL file and then use BindFileToMoniker
	int Variation_3();
	// @cmember Pop up 2 dialogs simultaneoysly
	int Variation_4();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(CGenericOp)
#define THE_CLASS CGenericOp
BEG_TEST_CASE(CGenericOp, CPromptInitialize, L"all kinds of scenarios that don't go anywhere else")
	TEST_VARIATION(1, 		L"Check the Next button in the provider page")
	TEST_VARIATION(2, 		L"Use a long UDL file")
	TEST_VARIATION(3, 		L"Create a UDL file and then use BindFileToMoniker")
	TEST_VARIATION(4, 		L"Pop up 2 dialogs simultaneoysly")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END

// {{ TCW_TEST_CASE_MAP(CPromptFileName)
//*-----------------------------------------------------------------------
// @class Test variations on IDBPromptInitialize::PromptFileName
//
class CPromptFileName : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

	BOOL		CommonScenario(
					WCHAR	*pwszInitialFileName,		// [in] 
					WCHAR	*pwszSelectFileName,		// [in]
					WCHAR	**ppwszSelectedFileName		// [out]
				);

	BOOL		Common_ANSI_OEM_Scenario(
					BOOL	fUseANSIToCreateUDLFile,
					BOOL	fUseANSIToPopUpDialog
				);

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(CPromptFileName,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Unsupported prompt options => E_INVALIDARG
	int Variation_1();
	// @cmember DBPROMPTOPTIONS_BROWSEONLY
	int Variation_2();
	// @cmember Cancel the dialog => DB_E_CANCELED
	int Variation_3();
	// @cmember Use a valid initial path name
	int Variation_4();
	// @cmember Use an inexistent initial path (make sure that the dialog still appears)
	int Variation_5();
	// @cmember Initial directory has no read permission
	int Variation_6();
	// @cmember Long initial directory name
	int Variation_7();
	// @cmember Directory is not local (UNC)
	int Variation_8();
	// @cmember Good initial file name
	int Variation_9();
	// @cmember Long initial file name
	int Variation_10();
	// @cmember Invalid file name (e.g. c:/\\/\\/file)
	int Variation_11();
	// @cmember NULL ppwszSelectedFile
	int Variation_12();
	// @cmember Pass both initial file name and initial directory
	int Variation_13();
	// @cmember Valid UDL and select it through IDBPromptInitialize::PromptFileName
	int Variation_14();
	// @cmember Spaces leading and trailing a file name
	int Variation_15();
	// @cmember Special characters in a file name
	int Variation_16();
	// @cmember UNC file name
	int Variation_17();
	// @cmember ANSI -> ANSI
	int Variation_18();
	// @cmember OEM -> OEM
	int Variation_19();
	// @cmember ANSI -> OEM
	int Variation_20();
	// @cmember OEM -> ANSI
	int Variation_21();
	// @cmember ANSI/OEM API combinations for the initial directory
	int Variation_22();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(CPromptFileName)
#define THE_CLASS CPromptFileName
BEG_TEST_CASE(CPromptFileName, CPromptInitialize, L"Test variations on IDBPromptInitialize::PromptFileName")
	TEST_VARIATION(1, 		L"Unsupported prompt options => E_INVALIDARG")
	TEST_VARIATION(2, 		L"DBPROMPTOPTIONS_BROWSEONLY")
	TEST_VARIATION(3, 		L"Cancel the dialog => DB_E_CANCELED")
	TEST_VARIATION(4, 		L"Use a valid initial path name")
	TEST_VARIATION(5, 		L"Use an inexistent initial path (make sure that the dialog still appears)")
	TEST_VARIATION(6, 		L"Initial directory has no read permission")
	TEST_VARIATION(7, 		L"Long initial directory name")
	TEST_VARIATION(8, 		L"Directory is not local (UNC)")
	TEST_VARIATION(9, 		L"Good initial file name")
	TEST_VARIATION(10, 		L"Long initial file name")
	TEST_VARIATION(11, 		L"Invalid file name (e.g. c:/\\/\\/file)")
	TEST_VARIATION(12, 		L"NULL ppwszSelectedFile")
	TEST_VARIATION(13, 		L"Pass both initial file name and initial directory")
	TEST_VARIATION(14, 		L"Valid UDL and select it through IDBPromptInitialize::PromptFileName")
	TEST_VARIATION(15, 		L"Spaces leading and trailing a file name")
	TEST_VARIATION(16, 		L"Special characters in a file name")
	TEST_VARIATION(17, 		L"UNC file name")
	TEST_VARIATION(18, 		L"ANSI -> ANSI")
	TEST_VARIATION(19, 		L"OEM -> OEM")
	TEST_VARIATION(20, 		L"ANSI -> OEM")
	TEST_VARIATION(21, 		L"OEM -> ANSI")
	TEST_VARIATION(22, 		L"ANSI/OEM API combinations for the initial directory")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END

// {{ TCW_TEST_CASE_MAP(AdvancedPage)
//*-----------------------------------------------------------------------
// @class Tests the Advanced Page of the UI
//
class AdvancedPage : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(AdvancedPage,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Set the Read flag
	int Variation_1();
	// @cmember Set the Write flag
	int Variation_2();
	// @cmember Set the ReadWrite flag
	int Variation_3();
	// @cmember Set the Share Deny None flag
	int Variation_4();
	// @cmember Set the Share Deny Read flag
	int Variation_5();
	// @cmember Set the Share Deny Write flag
	int Variation_6();
	// @cmember Set Read | Share Deny Read
	int Variation_7();
	// @cmember Set Read | Share Deny Read | ShareDeny Write
	int Variation_8();
	// @cmember Set Read | Write | Share Deny Read
	int Variation_9();
	// @cmember Set Read | Write | Share Deny Read | ShareDeny Write
	int Variation_10();
	// @cmember Set access rights, move to All page, close
	int Variation_11();
	// @cmember Set timeout value
	int Variation_12();
	// @cmember Set impersonation level to Anonymous
	int Variation_13();
	// @cmember Set impersonation level to Delegate
	int Variation_14();
	// @cmember Set impersonation level to Identify
	int Variation_15();
	// @cmember Set impersonation level to Impersonate
	int Variation_16();
	// @cmember Set protection level to Call
	int Variation_17();
	// @cmember Set protection level to Connect
	int Variation_18();
	// @cmember Set protection level to None
	int Variation_19();
	// @cmember Set protection level to Pkt
	int Variation_20();
	// @cmember Set protection level to Pkt Integrity
	int Variation_21();
	// @cmember Set protection level to Pkt Privacy
	int Variation_22();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(AdvancedPage)
#define THE_CLASS AdvancedPage
BEG_TEST_CASE(AdvancedPage, CPromptInitialize, L"Tests the Advanced Page of the UI")
	TEST_VARIATION(1, 		L"Set the Read flag")
	TEST_VARIATION(2, 		L"Set the Write flag")
	TEST_VARIATION(3, 		L"Set the ReadWrite flag")
	TEST_VARIATION(4, 		L"Set the Share Deny None flag")
	TEST_VARIATION(5, 		L"Set the Share Deny Read flag")
	TEST_VARIATION(6, 		L"Set the Share Deny Write flag")
	TEST_VARIATION(7, 		L"Set Read | Share Deny Read")
	TEST_VARIATION(8, 		L"Set Read | Share Deny Read | ShareDeny Write")
	TEST_VARIATION(9, 		L"Set Read | Write | Share Deny Read")
	TEST_VARIATION(10, 		L"Set Read | Write | Share Deny Read | ShareDeny Write")
	TEST_VARIATION(11, 		L"Set access rights, move to All page, close")
	TEST_VARIATION(12, 		L"Set timeout value")
	TEST_VARIATION(13, 		L"Set impersonation level to Anonymous")
	TEST_VARIATION(14, 		L"Set impersonation level to Delegate")
	TEST_VARIATION(15, 		L"Set impersonation level to Identify")
	TEST_VARIATION(16, 		L"Set impersonation level to Impersonate")
	TEST_VARIATION(17, 		L"Set protection level to Call")
	TEST_VARIATION(18, 		L"Set protection level to Connect")
	TEST_VARIATION(19, 		L"Set protection level to None")
	TEST_VARIATION(20, 		L"Set protection level to Pkt")
	TEST_VARIATION(21, 		L"Set protection level to Pkt Integrity")
	TEST_VARIATION(22, 		L"Set protection level to Pkt Privacy")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END

// {{ TCW_TEST_CASE_MAP(CSummaryPage)
//*-----------------------------------------------------------------------
// @class test the summary page of the dialog
//
class CSummaryPage : public CPromptInitialize { 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(CSummaryPage,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Find a property of a certain type and set it in a dialog
	BOOL		SetRandProp(VARTYPE vtType);

	// @cmember Find a property of a certain type and set it in a dialog
	BOOL		SetSummaryProp(VARTYPE vtType, WCHAR *pwszValue);
	BOOL		SetSummaryProp(VARIANT *pValue);
	BOOL		SetAndResetProp(VARTYPE vtType);

	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Set some property
	int Variation_1();
	// @cmember VT_I1 property
	int Variation_2();
	// @cmember VT_UI1 property
	int Variation_3();
	// @cmember VT_I2 property
	int Variation_4();
	// @cmember VT_UI2 property
	int Variation_5();
	// @cmember VT_I4 property
	int Variation_6();
	// @cmember VT_UI4 property
	int Variation_7();
	// @cmember VT_BSTR property
	int Variation_8();
	// @cmember VT_R4 property
	int Variation_9();
	// @cmember VT_R8 property
	int Variation_10();
	// @cmember VT_CY property
	int Variation_11();
	// @cmember VT_DATE property
	int Variation_12();
	// @cmember VT_BOOL property
	int Variation_13();
	// @cmember Reset a VT_I1 property
	int Variation_14();
	// @cmember Reset a VT_UI1 property
	int Variation_15();
	// @cmember Reset a VT_I2 property
	int Variation_16();
	// @cmember Reset a VT_UI2 property
	int Variation_17();
	// @cmember Reset a VT_I4 property
	int Variation_18();
	// @cmember Reset a VT_UI4 property
	int Variation_19();
	// @cmember Reset a VT_BSTR property
	int Variation_20();
	// @cmember Reset a VT_R4 property
	int Variation_21();
	// @cmember Reset a VT_R8 property
	int Variation_22();
	// @cmember Reset a VT_CY property
	int Variation_23();
	// @cmember Reset a VT_DATE property
	int Variation_24();
	// @cmember Reset a VT_BOOL property
	int Variation_25();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(CSummaryPage)
#define THE_CLASS CSummaryPage
BEG_TEST_CASE(CSummaryPage, CPromptInitialize, L"test the summary page of the dialog")
	TEST_VARIATION(1, 		L"Set some property")
	TEST_VARIATION(2, 		L"VT_I1 property")
	TEST_VARIATION(3, 		L"VT_UI1 property")
	TEST_VARIATION(4, 		L"VT_I2 property")
	TEST_VARIATION(5, 		L"VT_UI2 property")
	TEST_VARIATION(6, 		L"VT_I4 property")
	TEST_VARIATION(7, 		L"VT_UI4 property")
	TEST_VARIATION(8, 		L"VT_BSTR property")
	TEST_VARIATION(9, 		L"VT_R4 property")
	TEST_VARIATION(10, 		L"VT_R8 property")
	TEST_VARIATION(11, 		L"VT_CY property")
	TEST_VARIATION(12, 		L"VT_DATE property")
	TEST_VARIATION(13, 		L"VT_BOOL property")
	TEST_VARIATION(14, 		L"Reset a VT_I1 property")
	TEST_VARIATION(15, 		L"Reset a VT_UI1 property")
	TEST_VARIATION(16, 		L"Reset a VT_I2 property")
	TEST_VARIATION(17, 		L"Reset a VT_UI2 property")
	TEST_VARIATION(18, 		L"Reset a VT_I4 property")
	TEST_VARIATION(19, 		L"Reset a VT_UI4 property")
	TEST_VARIATION(20, 		L"Reset a VT_BSTR property")
	TEST_VARIATION(21, 		L"Reset a VT_R4 property")
	TEST_VARIATION(22, 		L"Reset a VT_R8 property")
	TEST_VARIATION(23, 		L"Reset a VT_CY property")
	TEST_VARIATION(24, 		L"Reset a VT_DATE property")
	TEST_VARIATION(25, 		L"Reset a VT_BOOL property")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END

// {{ TCW_TEST_CASE_MAP(UDLSpecific)
//*-----------------------------------------------------------------------
// @class Tests tailored for opening the DSL dialog using a udl file
//
class UDLSpecific : public CPromptInitialize{ 
private:
	// @cmember Static array of variations
	DECLARE_TEST_CASE_DATA();

public:
	// {{ TCW_DECLARE_FUNCS
	// @cmember Execution Routine
	DECLARE_TEST_CASE_FUNCS(UDLSpecific,CPromptInitialize);
	// }} TCW_DECLARE_FUNCS_END
	
	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();

	// {{ TCW_TESTVARS()
	// @cmember Create udl file, open it, set props, close it, reopen, close
	int Variation_1();
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(UDLSpecific)
#define THE_CLASS UDLSpecific
BEG_TEST_CASE(UDLSpecific, CPromptInitialize, L"Tests tailored for opening the DSL dialog using a udl file")
	TEST_VARIATION(1, 		L"Create udl file, open it, set props, close it, reopen, close")
END_TEST_CASE()
#undef THE_CLASS
// }} TCW_TESTCASE_END
// }} TCW_TEST_CASE_MAP_END


// static members
HWND		CPromptInitialize::s_hMainWnd = FindWindowA("LTM", "Microsoft Local Test Manager");


//--------------------------------------------------------------------
// @func Module level initialization routine
//
// @rdesc Success or Failure
// 		@flag  TRUE  | Successful initialization
//		@flag  FALSE | Initialization problems
//
BOOL ModuleInit(CThisTestModule * pThisTestModule)
{
	BOOL					bReturn					= FALSE;
	IDBPromptInitialize*	pIDBPromptInitialize	= NULL;
	HRESULT					hr						= E_FAIL;
	
	//Create the session
	ASSERT(pThisTestModule);
	pThisTestModule->m_pIUnknown = NULL;
	pThisTestModule->m_pIUnknown2 = NULL;

	if(!ModuleCreateDBSession(pThisTestModule))
		return FALSE;

// At this time the myprov provider sample cannot be run in Free threaded mode.  But others
// can, so we will ifdef out this check.  If using myprov it will need to be reinserted.
#if 0
	
	// This test only runs in Apartment model at this time
	hr = CoInit(0/*COINIT_MULTITHREADED*/);
	
	if (SUCCEEDED(hr))
	{
		// LTM should have already called CoInitialize(Ex), so we 
		// should always get S_FALSE here if the threading model
		// is the same (Apartment).  But even S_FALSE must be
		// balanced with a CoUninitialize() call.
		CoUninitialize();
	}
	else
	{
		odtLog << L"LTM must be set for Free Threaded to run this test.\n";
		goto CLEANUP;
	}
#endif

	// set g_pIDBInitialize and g_pIOpenRowset
	TESTC(VerifyInterface(pThisTestModule->m_pIUnknown, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&g_pIDBInitialize));
	TESTC(VerifyInterface(pThisTestModule->m_pIUnknown2, IID_IOpenRowset, SESSION_INTERFACE, (IUnknown**)&g_pIOpenRowset));

	TESTC(CDSL_Dialog::GetContextInfo());

	//Create an Instance of IDBPromptInitialize
	TESTC_(CoCreateInstance(CLSID_DataLinks, NULL, CLSCTX_INPROC_SERVER, IID_IDBPromptInitialize, (void**)&pIDBPromptInitialize),S_OK); 
	
	g_pSourcesSet	= new CSourcesSet();
	g_pSourcesSet->FinalInit();

	CDSL_Dialog::s_pSourcesSet = g_pSourcesSet;

	CPropData::s_pTable = new CTable(pThisTestModule->m_pIUnknown2, (LPWSTR)g_wszModuleName);
	CPropData::s_pTable->SetExistingTable(L"Props");

	bReturn = TRUE;

CLEANUP:
	SAFE_RELEASE(pIDBPromptInitialize);
	return bReturn;
}	
  
//--------------------------------------------------------------------
// @func Module level termination routine
//
// @rdesc Success or Failure
// 		@flag  TRUE  | Successful initialization
//		@flag  FALSE | Initialization problems
//
BOOL ModuleTerminate(CThisTestModule * pThisTestModule)
{
	delete CPropData::s_pTable;
	delete g_pSourcesSet;
	CPropData::s_pTable = NULL;

	DestroyWindow(CPromptInitialize::s_hMainWnd);
	
	SAFE_RELEASE(g_pIDBInitialize);
	SAFE_RELEASE(g_pIOpenRowset);

	COMPARE(CDSL_Dialog::FinalFree(), TRUE);
	return ModuleReleaseDBSession(pThisTestModule);
}	





// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Test Case Section
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// }} END_DECLARE_TEST_CASES()

// {{ TCW_TESTMODULE(ThisModule)
TEST_MODULE(17, ThisModule, gwszModuleDescrip)
	TEST_CASE(1, LuxorConnection)
	TEST_CASE(2, SockeyeConnection)
	TEST_CASE(3, Jolt40Connection)
	TEST_CASE(4, MSDAORAConnection)
	TEST_CASE(5, GeneralConnection)
	TEST_CASE(6, CDSOAndRIID)
	TEST_CASE(7, CAggregation)
	TEST_CASE(8, CSourceTypeFilter)
	TEST_CASE(9, CProviderFilter)
	TEST_CASE(10, CMixFilters)
	TEST_CASE(11, CPromptOptions)
	TEST_CASE(12, CParentWindow)
	TEST_CASE(13, CGenericOp)
	TEST_CASE(14, CPromptFileName)
	TEST_CASE(15, AdvancedPage)
	TEST_CASE(16, CSummaryPage)
	TEST_CASE(17, UDLSpecific)
END_TEST_MODULE()
// }} TCW_TESTMODULE_END



//-------------------------------------------------------------------------
//
// CPromptInitialize
//-------------------------------------------------------------------------
CPromptInitialize::CPromptInitialize(WCHAR *wstrTestCaseName) : CSessionObject(wstrTestCaseName) 
{
} // CPromptInitialize::CPromptInitialize



//*-----------------------------------------------------------------------
// 
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//-------------------------------------------------------------------------
BOOL CPromptInitialize::Init()
{
	// NOTE: no need to free this 2, as they are taken over by m_PropSets
	// and freed by it in the end
	ULONG			cPropSets		= 0;
	DBPROPSET		*rgPropSets		= NULL;

	m_pIDBPromptInitialize = NULL;

	if (CSessionObject::Init())
	{
		DBPROP		*pProp;

		//Create an Instance of IDBPromptInitialize
		m_pIDBPromptInitialize = CServiceComp::pIDBPromptInitialize();
		TESTC(NULL != m_pIDBPromptInitialize); //CoCreateInstance(CLSID_DataLinks, NULL, CLSCTX_INPROC_SERVER, IID_IDBPromptInitialize, (void**)&m_pIDBPromptInitialize),S_OK); 
		GetInternationalStrings();

		m_ProviderCLSID = GetModInfo()->GetProviderCLSID();
		if (COMPARE(GetInitProps(&cPropSets, &rgPropSets), TRUE))
			m_PropSets.Attach(cPropSets, rgPropSets);

		// cache the init datasource, as read from the init string
		pProp = m_PropSets.FindProperty(DBPROP_INIT_DATASOURCE, DBPROPSET_DBINIT);
		COMPARE(!pProp || (VT_BSTR == pProp->vValue.vt), TRUE);
		if (pProp && (VT_BSTR == pProp->vValue.vt))
			m_pwszInitDataSource = V_BSTR(&pProp->vValue);

		// cache the user id, as read from the init string
		pProp = m_PropSets.FindProperty(DBPROP_AUTH_USERID, DBPROPSET_DBINIT);
		COMPARE(!pProp || (VT_BSTR == pProp->vValue.vt), TRUE);
		if (pProp && (VT_BSTR == pProp->vValue.vt))
			m_pwszUserID = V_BSTR(&pProp->vValue);

		// cache the password, as read from the init string
		pProp = m_PropSets.FindProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT);
		COMPARE(!pProp || (VT_BSTR == pProp->vValue.vt), TRUE);
		if (pProp && (VT_BSTR == pProp->vValue.vt))
			m_pwszPassword = V_BSTR(&pProp->vValue);

		return TRUE;
	}

CLEANUP:
	return FALSE;
} // CPromptInitialize::Init




//*-----------------------------------------------------------------------
// 
// @mfunc Loads the international strings used in the test
//
// @rdesc TRUE or FALSE
//-------------------------------------------------------------------------
BOOL CPromptInitialize::GetInternationalStrings()
{
	TBEGIN
	CTable			*pTable = new CTable(m_pThisTestModule->m_pIUnknown2, (LPWSTR)g_wszModuleName);
	WCHAR			pwszSQLCmdText[3000] =	L"SELECT ID, Description from BiDiStrings";
	CComfRowset		Rowset;
	IRowset			*pIRowset = NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	HROW			hRow	= 0;
	WCHAR			*pwszString;
	ULONG			ulColOffset;


	QTESTC(S_OK == (m_hr = pTable->SetExistingTable(L"BiDiStrings")));  // ZES - need to report errors back to init better

	TESTC_( (m_hr = pTable->BuildCommand(pwszSQLCmdText, IID_IRowset,
		EXECUTE_ALWAYS, 0, NULL, NULL, NULL, (IUnknown**)&pIRowset, NULL)) ,S_OK);

	Rowset.DropRowset();
	Rowset.SetTable(pTable, DELETETABLE_NO);
	TESTC_PROVIDER(S_OK == Rowset.CreateRowset(pIRowset));

	ulColOffset = (Rowset.m_rgBinding[0].iOrdinal == 0)? 1: 0;

	//Try to find the specified row with this table...
	for (; S_OK == Rowset.GetNextRows(&hRow); )
	{

		TESTC_(m_hr = Rowset.GetRowData(hRow, &Rowset.m_pData),S_OK);

		if (pwszString = (WCHAR*)Rowset.GetValue(1 + ulColOffset))
		{
			odtLog << pwszString << "\n";
		}

		pwszString = (WCHAR*)Rowset.GetValue(0 + ulColOffset);
		if (pwszString)
			m_InternationalStrings.SetAt(m_InternationalStrings.GetCount(), CWString(pwszString));
		Rowset.ReleaseRows(hRow);	
	}

CLEANUP:
	SAFE_RELEASE(pIRowset);
	delete pTable;
	TRETURN
} //CPromptInitialize::GetInternationalStrings



// creates an initialized DSO based on provider's guid and properties
HRESULT CPromptInitialize::CreateInitDSO(
	GUID		clsidProvider, 
	CPropSets	*pPropSets, 
	REFIID		riid,
	IUnknown	**ppIUnknown
)
{
	TBEGIN
	HRESULT			hr = E_FAIL;
	IDBProperties	*pIDBProperties = NULL;
	IDBInitialize	*pIDBInitialize	= NULL;


	TESTC(NULL != pPropSets);
	TESTC(NULL != ppIUnknown);

	*ppIUnknown = NULL;

	TESTC_(hr = GetModInfo()->CreateProvider(clsidProvider, NULL, 
			IID_IDBProperties, (IUnknown**)&pIDBProperties), S_OK);

	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC(SUCCEEDED(hr = pIDBProperties->SetProperties(pPropSets->cPropertySets(), pPropSets->pPropertySets())));

	// initialize the DSO
	TESTC(VerifyInterface(pIDBProperties, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));
	// Initialize
	TESTC_(hr = pIDBInitialize->Initialize(), S_OK);

	// ask for the sought interface
	TESTC(VerifyInterface(pIDBProperties, riid, DATASOURCE_INTERFACE, ppIUnknown));
	
	hr = S_OK;

CLEANUP:
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIDBInitialize);
	return hr;
} //CPromptInitialize::CreateInitDSO



//-------------------------------------------------------------------------
//
//	CPromptInitialize::CreateSQLServerUser
//		Creates a login, user name and password
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CPromptInitialize::CreateSQLServerUser(
	IUnknown	*pIUnknown,		// initialized DSO
	LPCWSTR		pwszUserID, 
	LPCWSTR		pwszPassword, 
	LPCWSTR		pwszDBName/*=NULL*/
)
{
	TBEGIN
	HRESULT				hr;
	WCHAR				wszCommandText[cMaxName];
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IDBCreateCommand	*pIDBCreateCommand	= NULL;
	ICommandText		*pICommandText		= NULL;

	// Get IDBCreateSession pointer
	TESTC(VerifyInterface(pIUnknown, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));
	
	// create a session
	TESTC_(hr = pIDBCreateSession->CreateSession(NULL, IID_IDBCreateCommand, (IUnknown**)&pIDBCreateCommand), S_OK);

	// create a command
	TESTC_(hr = pIDBCreateCommand->CreateCommand(NULL, IID_ICommandText, (IUnknown**)&pICommandText), S_OK);

	// use the command to create the DB
	swprintf(wszCommandText, L"sp_dropuser %s", pwszUserID);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL);

	swprintf(wszCommandText, L"sp_droplogin %s", pwszUserID);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL);

	if (pwszDBName)
	{
		swprintf(wszCommandText, L"use %s", pwszDBName);
		TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
			wszCommandText
			), S_OK);
		TESTC_(hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL), S_OK);
	}

	swprintf(wszCommandText, L"sp_addlogin \"%s\", \"%s\"", pwszUserID, pwszPassword);
	if (pwszDBName)
	{
		wcscat(wszCommandText, L", ");
		wcscat(wszCommandText, pwszDBName);
	}

	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	TESTC_(hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL), S_OK);

	swprintf(wszCommandText, L"sp_adduser \"%s\"", pwszUserID);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	TESTC_(hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL), S_OK);

	swprintf(wszCommandText, L"grant all to %s", pwszUserID);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	TESTC_(hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL), S_OK);

CLEANUP:
	SAFE_RELEASE(pIDBCreateSession);
	SAFE_RELEASE(pIDBCreateCommand);
	SAFE_RELEASE(pICommandText);
	TRETURN
} //CPromptInitialize::CreateSQLServerUser




//-------------------------------------------------------------------------
//
//	CPromptInitialize::CreateSQLServerDB
//		Creates a database
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CPromptInitialize::CreateSQLServerDB(
	IUnknown	*pIUnknown,		// initialized DSO
	LPCWSTR pwszDBName
)
{
	TBEGIN
	HRESULT				hr;
	WCHAR				wszCommandText[cMaxName];
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IDBCreateCommand	*pIDBCreateCommand	= NULL;
	ICommandText		*pICommandText		= NULL;

	// Get IDBCreateSession pointer
	TESTC(VerifyInterface(pIUnknown, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));
	
	// create a session
	TESTC_(hr = pIDBCreateSession->CreateSession(NULL, IID_IDBCreateCommand, (IUnknown**)&pIDBCreateCommand), S_OK);

	// create a command
	TESTC_(hr = pIDBCreateCommand->CreateCommand(NULL, IID_ICommandText, (IUnknown**)&pICommandText), S_OK);

	// use the command to create the DB
	swprintf(wszCommandText, L"DROP DATABASE %s", pwszDBName);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL);

	swprintf(wszCommandText, L"create database %s ", pwszDBName);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	TESTC_(hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL), S_OK);

	swprintf(wszCommandText, L"sp_dboption %s,\"read only\",false", pwszDBName);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	TESTC_(hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL), S_OK);

CLEANUP:
	SAFE_RELEASE(pIDBCreateSession);
	SAFE_RELEASE(pIDBCreateCommand);
	SAFE_RELEASE(pICommandText);
	TRETURN
} //CPromptInitialize::CreateSQLServerDB




//-------------------------------------------------------------------------
//
//	CPromptInitialize::DropSQLServerUser
//		Creates a login, user name and password
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CPromptInitialize::DropSQLServerUser(
	IUnknown	*pIUnknown,		// initialized DSO
	LPCWSTR		pwszUserID
)
{
	TBEGIN
	HRESULT				hr;
	WCHAR				wszCommandText[cMaxName];
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IDBCreateCommand	*pIDBCreateCommand	= NULL;
	ICommandText		*pICommandText		= NULL;

	// Get IDBCreateSession pointer
	TESTC(VerifyInterface(pIUnknown, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));
	
	// create a session
	TESTC_(hr = pIDBCreateSession->CreateSession(NULL, IID_IDBCreateCommand, (IUnknown**)&pIDBCreateCommand), S_OK);

	// create a command
	TESTC_(hr = pIDBCreateCommand->CreateCommand(NULL, IID_ICommandText, (IUnknown**)&pICommandText), S_OK);

	// use the command to create the DB
	swprintf(wszCommandText, L"sp_dropuser %s", pwszUserID);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL);

	swprintf(wszCommandText, L"sp_droplogin %s", pwszUserID);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL);

CLEANUP:
	SAFE_RELEASE(pIDBCreateSession);
	SAFE_RELEASE(pIDBCreateCommand);
	SAFE_RELEASE(pICommandText);
	TRETURN
} //CPromptInitialize::DropSQLServerUser




//-------------------------------------------------------------------------
//
//	CPromptInitialize::DropSQLServerDB
//		Creates a database
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CPromptInitialize::DropSQLServerDB(
	IUnknown	*pIUnknown,		// initialized DSO
	LPCWSTR pwszDBName
)
{
	TBEGIN
	HRESULT				hr;
	WCHAR				wszCommandText[cMaxName];
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IDBCreateCommand	*pIDBCreateCommand	= NULL;
	ICommandText		*pICommandText		= NULL;

	// Get IDBCreateSession pointer
	TESTC(VerifyInterface(pIUnknown, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));
	
	// create a session
	TESTC_(hr = pIDBCreateSession->CreateSession(NULL, IID_IDBCreateCommand, (IUnknown**)&pIDBCreateCommand), S_OK);

	// create a command
	TESTC_(hr = pIDBCreateCommand->CreateCommand(NULL, IID_ICommandText, (IUnknown**)&pICommandText), S_OK);

	// use the command to create the DB
	swprintf(wszCommandText, L"DROP DATABASE %s", pwszDBName);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL);

CLEANUP:
	SAFE_RELEASE(pIDBCreateSession);
	SAFE_RELEASE(pIDBCreateCommand);
	SAFE_RELEASE(pICommandText);
	TRETURN
} //CPromptInitialize::DropSQLServerDB




//-------------------------------------------------------------------------
//
//	CPromptInitialize::CreateOracleUser
//		Creates a user name and password
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CPromptInitialize::CreateOracleUser(
	IUnknown	*pIUnknown,		// initialized DSO
	LPCWSTR		pwszUserID, 
	LPCWSTR		pwszPassword, 
	LPCWSTR		pwszDBName/*=NULL*/
)
{
	TBEGIN
	HRESULT				hr;
	WCHAR				wszCommandText[cMaxName];
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IDBCreateCommand	*pIDBCreateCommand	= NULL;
	ICommandText		*pICommandText		= NULL;

	// Get IDBCreateSession pointer
	TESTC(VerifyInterface(pIUnknown, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));
	
	// create a session
	TESTC_(hr = pIDBCreateSession->CreateSession(NULL, IID_IDBCreateCommand, (IUnknown**)&pIDBCreateCommand), S_OK);

	// create a command
	TESTC_(hr = pIDBCreateCommand->CreateCommand(NULL, IID_ICommandText, (IUnknown**)&pICommandText), S_OK);

	// use the command to create the DB
	swprintf(wszCommandText, L"drop user \"%s\"", pwszUserID);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL);

	swprintf(wszCommandText, L"create user \"%s\" identified by \"%s\"", pwszUserID, pwszPassword);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL);

CLEANUP:
	SAFE_RELEASE(pIDBCreateSession);
	SAFE_RELEASE(pIDBCreateCommand);
	SAFE_RELEASE(pICommandText);
	TRETURN
} //CPromptInitialize::CreateOracleUser




//-------------------------------------------------------------------------
//
//	CPromptInitialize::DropOracleUser
//		Creates a login, user name and password
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CPromptInitialize::DropOracleUser(
	IUnknown	*pIUnknown,		// initialized DSO
	LPCWSTR		pwszUserID
)
{
	TBEGIN
	HRESULT				hr;
	WCHAR				wszCommandText[cMaxName];
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IDBCreateCommand	*pIDBCreateCommand	= NULL;
	ICommandText		*pICommandText		= NULL;

	// Get IDBCreateSession pointer
	TESTC(VerifyInterface(pIUnknown, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));
	
	// create a session
	TESTC_(hr = pIDBCreateSession->CreateSession(NULL, IID_IDBCreateCommand, (IUnknown**)&pIDBCreateCommand), S_OK);

	// create a command
	TESTC_(hr = pIDBCreateCommand->CreateCommand(NULL, IID_ICommandText, (IUnknown**)&pICommandText), S_OK);

	// use the command to create the DB
	swprintf(wszCommandText, L"drop user \"%s\"", pwszUserID);
	TESTC_(hr = pICommandText->SetCommandText(DBGUID_DEFAULT, 
		wszCommandText
		), S_OK);
	hr = pICommandText->Execute(NULL, IID_NULL, NULL, NULL, NULL);

CLEANUP:
	SAFE_RELEASE(pIDBCreateSession);
	SAFE_RELEASE(pIDBCreateCommand);
	SAFE_RELEASE(pICommandText);
	TRETURN
} //CPromptInitialize::DropOracleUser




//-------------------------------------------------------------------------
//
//	CPromptInitialize::BuildLongUserName
//		Creates a long user name
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CPromptInitialize::BuildLongUserName(GUID clsidProvider, WCHAR **ppName, ULONG ulSize/*=cMaxName*/)
{
	BOOL			fRes			= FALSE;
	WCHAR			*pwszName		= NULL;
	ULONG			i;

	ASSERT(NULL != ppName);
	SAFE_ALLOC(pwszName, WCHAR, ulSize);
	memset(pwszName, 0, sizeof(pwszName));

	for (i=0; i < ulSize-1; i++)
	{
		wcscat(pwszName, L"a");
	}

	*ppName = pwszName;
	fRes = TRUE;

CLEANUP:
	return fRes;
} //CPromptInitialize::BuildLongUserName




//-------------------------------------------------------------------------
//	CPromptInitialize::Terminate
//-------------------------------------------------------------------------
BOOL CPromptInitialize::Terminate()
{
	CServiceComp::ReleaseSCInterface(m_pIDBPromptInitialize);
	return CSessionObject::Terminate();
} // CPromptInitialize::Terminate




// {{ TCW_TC_PROTOTYPE(LuxorConnection)
//*-----------------------------------------------------------------------
//| Test Case:		LuxorConnection - test connection dialog for Luxor
//| Created:  	7/21/98
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL LuxorConnection::Init()
{ 
	TBEGIN
	IDBProperties	*pIDBProperties = NULL;
	HRESULT			hr;

	// {{ TCW_INIT_BASECLASS_CHECK
	TESTC(CPromptInitialize::Init());
	// }}

	if (GetModInfo()->GetProviderCLSID() != CLSID_SQLOLEDB)
		return TEST_SKIPPED;

	hr = GetModInfo()->CreateProvider(CLSID_SQLOLEDB, NULL, 
		IID_IDBProperties, (IUnknown**)&pIDBProperties);

	if (REGDB_E_CLASSNOTREG == hr)
		return TEST_SKIPPED;

	TESTC_(hr, S_OK);

CLEANUP:
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Set server name, user name, blank password, uncheck save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_1()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	HRESULT				hr;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	// set DBPROP_INIT_DATASOURCE from init string
	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	// set DBPROP_AUTH_USERID from init string
	if (m_pwszUserID)
		TESTC(Dialog.SetUserID(m_pwszUserID));

	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_UNCHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Set server name, user name, blank password, check save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_2()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	if (m_pwszUserID)
		TESTC(Dialog.SetUserID(m_pwszUserID));

	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Set server name, user name, password, uncheck save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_3()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;

	// first, the negative case, bad password
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	if (m_pwszUserID)
		TESTC(Dialog.SetUserID(m_pwszUserID));

	TESTC(Dialog.SetPassword(g_wszLuxorBadPassword));

	TESTC(Dialog.SetSavePassword(BST_UNCHECKED));
	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitTimeout(3));
	Sleep(1000);
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);
	TESTC_(pIDBInitialize->Uninitialize(), S_OK);

	// the positive case
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.IsCurrentPage(g_nConnection));

	if (m_pwszPassword)
		TESTC(Dialog.SetPassword(m_pwszPassword));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Set server name, user name, password, check save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_4()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	if (m_pwszUserID)
		TESTC(Dialog.SetUserID(m_pwszUserID));

	if (m_pwszPassword)
		TESTC(Dialog.SetPassword(m_pwszPassword));

	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	Sleep(1000);
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Server name, integrated security
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_5()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	TESTC(Dialog.SetSecurityMethod(IDC_USE_INTEGRATED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc Check server names against Luxor enumerator
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_6()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());
	
	TESTC(Dialog.Luxor_CheckServerNameList());

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc Set inexistent server name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_7()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	WCHAR				*pwszDSName			= NULL;

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	TESTC(Dialog.SetInitDataSource(g_wszInexistentLuxorServerName));

	TESTC(Dialog.GotoAllPage());
	TESTC(Dialog.GetProperty(L"Data Source", &pwszDSName));
	TESTC(0 == wcscmp(pwszDSName, g_wszInexistentLuxorServerName));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	SAFE_FREE(pwszDSName);
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Various values for user name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_8()
{ 
	TBEGIN
	ULONG			i;
	IDBInitialize	*pIDBInitialize	= NULL;
	
	for (i=0; g_rgName[i][0] != L'\0'; i++)
	{
		CDSL_Dialog		Dialog;

		odtLog << "User ID: " << g_rgName[i] << "\n";
		
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(m_ProviderCLSID));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetUserID(g_rgName[i]));
		Sleep(1000);
		TESTC(Dialog.KillThread(PSBTN_OK));
		TESTC(Dialog.IsResult(S_OK));
		TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
		SAFE_RELEASE(pIDBInitialize);
	}
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Various values for password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_9()
{ 
	TBEGIN
	ULONG			i;
	IDBInitialize	*pIDBInitialize	= NULL;
	
	for (i=0; g_rgName[i][0] != L'\0'; i++)
	{
		CDSL_Dialog		Dialog;

		odtLog << "Pasword: " << g_rgName[i] << "\n";
		
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(m_ProviderCLSID));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetPassword(g_rgName[i]));
		Sleep(1000);
		TESTC(Dialog.KillThread(PSBTN_OK));
		TESTC(Dialog.IsResult(S_OK));
		TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
		SAFE_RELEASE(pIDBInitialize);
	}
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc International name provided for user, password, server
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_10()
{ 
	TBEGIN
	WCHAR			wszName[cMaxName+1]	= L"";
	IDBInitialize	*pIDBInitialize		= NULL;
	CLocaleInfo		*pCLocaleInfo		= NULL;
	CDSL_Dialog		Dialog;

	// Create CLocaleInfo object instance
	// Use international data only wiht the appropriate registry settings
	// FindIntlSetting looks up the appropriate registry key
	TESTC_PROVIDER(FindIntlSetting());

	pCLocaleInfo = new CLocaleInfo(GetUserDefaultLCID());

	memset(wszName, 0, wcslen(wszName)*sizeof(WCHAR));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "server name: " << wszName << "\n";
	TESTC(Dialog.SetInitDataSource(wszName));
	
	TESTC(Dialog.SetSecurityMethod(IDC_USE_STANDARD));
	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "password: " << wszName << "\n";
	TESTC(Dialog.SetPassword(wszName));

	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "user name: " << wszName << "\n";
	TESTC(Dialog.SetUserID(wszName));
	
	Sleep(1000);
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	delete pCLocaleInfo;
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(11)
//*-----------------------------------------------------------------------
// @mfunc Long user name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_11()
{ 
	TBEGIN
	HRESULT			hr;
	WCHAR			*pwszLongName	= NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	CDSL_Dialog		Dialog;
	
	TESTC_PROVIDER(!BuildLongUserName(m_ProviderCLSID, &pwszLongName));
	TESTC(NULL != pwszLongName);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	TESTC(Dialog.SetSecurityMethod());

	TESTC(Dialog.SetUserID(pwszLongName));
	
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	SAFE_FREE(pwszLongName);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(12)
//*-----------------------------------------------------------------------
// @mfunc Long server name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_12()
{ 
	TBEGIN
	HRESULT			hr;
	WCHAR			*pwszLongName	= NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	CDSL_Dialog		Dialog;
	
	TESTC_PROVIDER(!BuildLongUserName(m_ProviderCLSID, &pwszLongName));
	TESTC(NULL != pwszLongName);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	TESTC(Dialog.SetInitDataSource(pwszLongName));
	
	TESTC(Dialog.SetSecurityMethod());

	if (m_pwszUserID)
		TESTC(Dialog.SetUserID(m_pwszUserID));

	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	SAFE_FREE(pwszLongName);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(13)
//*-----------------------------------------------------------------------
// @mfunc Long password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_13()
{ 
	TBEGIN
	HRESULT			hr;
	WCHAR			*pwszLongName	= NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	CDSL_Dialog		Dialog;
	
	TESTC_PROVIDER(!BuildLongUserName(m_ProviderCLSID, &pwszLongName));
	TESTC(NULL != pwszLongName);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	TESTC(Dialog.SetSecurityMethod());
	
	if (m_pwszUserID)
	TESTC(Dialog.SetUserID(m_pwszUserID));

	TESTC(Dialog.SetPassword(pwszLongName));
	
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	SAFE_FREE(pwszLongName);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(14)
//*-----------------------------------------------------------------------
// @mfunc Bad password for existing user
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_14()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	if (m_pwszUserID)
		TESTC(Dialog.SetUserID(m_pwszUserID));

	// set bad password
	TESTC(Dialog.SetPassword(g_wszLuxorBadPassword));

	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	Sleep(1000);
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(15)
//*-----------------------------------------------------------------------
// @mfunc Bad password for existing user, push the Test button
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_15()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	HRESULT				hr;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	if (m_pwszUserID)
		TESTC(Dialog.SetUserID(m_pwszUserID));

	TESTC(Dialog.SetPassword(g_wszLuxorBadPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	Sleep(1000);
	TESTC(Dialog.TestConnection()); // info might not be correct
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(16)
//*-----------------------------------------------------------------------
// @mfunc Set initial catalog name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_16()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	if (m_pwszUserID)
		TESTC(Dialog.SetUserID(m_pwszUserID));

	if (m_pwszPassword)
		TESTC(Dialog.SetPassword(m_pwszPassword));

	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.SetDatabaseMethod(IDC_UseDatabaseOnServerName));

	TESTC(Dialog.SetDatabaseOnServerName(g_wszLuxorInitCat));
	
	TESTC(Dialog.TestConnection());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(17)
//*-----------------------------------------------------------------------
// @mfunc Set server name and chose from the init catalog list
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_17()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	if (m_pwszUserID)
		TESTC(Dialog.SetUserID(m_pwszUserID));

	if (m_pwszPassword)
		TESTC(Dialog.SetPassword(m_pwszPassword));

	TESTC(Dialog.SetSavePassword(BST_CHECKED));

	TESTC(Dialog.SetDatabaseMethod(IDC_UseDatabaseOnServerName));
	TESTC(Dialog.Luxor_SelectInitCatalog());

	TESTC(Dialog.KillThread(PSBTN_OK, 2000));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(18)
//*-----------------------------------------------------------------------
// @mfunc Atach a database file as a database name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_18()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());

	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));

	if (m_pwszUserID)
		TESTC(Dialog.SetUserID(m_pwszUserID));

	if (m_pwszPassword)
	TESTC(Dialog.SetPassword(m_pwszPassword));

	TESTC(Dialog.SetSavePassword(BST_CHECKED));

	TESTC(Dialog.SetDatabaseMethod(IDC_UseDatabaseFileName));
	TESTC(Dialog.SetDatabaseFileName(L"neueDB"));
	TESTC(Dialog.SetInitFileName(L"\\somefile.mdf"));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(19)
//*-----------------------------------------------------------------------
// @mfunc International strings as user names
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_19()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize	= NULL;
	CWString		wszUserID;
	CDSL_Dialog		Dialog;
	ULONG			ulString;

	for (ulString = 0; ulString < (ULONG)m_InternationalStrings.GetCount(); ulString++)
	{

		TESTC(m_InternationalStrings.Lookup(ulString, wszUserID));

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(m_ProviderCLSID));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetSecurityMethod(IDC_USE_STANDARD));
	
		TESTC(Dialog.SetUserID(wszUserID));

		Sleep(300);
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(20)
//*-----------------------------------------------------------------------
// @mfunc International strings as passwords
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_20()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize	= NULL;
	CWString		wszPassword;
	CDSL_Dialog		Dialog;

	for (ULONG ulString = 0; ulString < (ULONG)m_InternationalStrings.GetCount(); ulString++)
	{
		TESTC(m_InternationalStrings.Lookup(ulString, wszPassword));

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(m_ProviderCLSID));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetSecurityMethod(IDC_USE_STANDARD));
		TESTC(Dialog.SetPassword(wszPassword));
		Sleep(100);
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(21)
//*-----------------------------------------------------------------------
// @mfunc International strings as initial catalogs
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_21()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize	= NULL;
	CWString		wszInitCatalog;
	CDSL_Dialog		Dialog;

	for (ULONG ulString = 0; ulString < (ULONG)m_InternationalStrings.GetCount(); ulString++)
	{
		TESTC(m_InternationalStrings.Lookup(ulString, wszInitCatalog));

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(m_ProviderCLSID));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetSecurityMethod(IDC_USE_STANDARD));
		TESTC(Dialog.SetDatabaseOnServerName(wszInitCatalog));
		Sleep(100);
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(22)
//*-----------------------------------------------------------------------
// @mfunc International strings as server name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_22()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize	= NULL;
	CWString		wszServerName;
	CDSL_Dialog		Dialog;

	for (ULONG ulString = 0; ulString < (ULONG)m_InternationalStrings.GetCount(); ulString++)
	{
		TESTC(m_InternationalStrings.Lookup(ulString, wszServerName));
		
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(m_ProviderCLSID));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetSecurityMethod(IDC_USE_STANDARD));

		TESTC(Dialog.SetInitDataSource(wszServerName));
		
		Sleep(100);
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(23)
//*-----------------------------------------------------------------------
// @mfunc International strings used for user name, password, initial catalog
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int LuxorConnection::Variation_23()
{ 
	TBEGIN
	HRESULT					hr;
	CWString				wszUserID;
	CWString				wszPassword;
	CWString				wszInitialCatalog;
	CDSL_Dialog				Dialog;
	IUnknown				*pIUnknown		= NULL;
	IDBInitialize			*pIDBInitialize = NULL;
	CPropSets				*pPropSets = NULL;
	CPropData				PropData;
	IDBPromptInitialize		*pIDBPromptInitialize	= NULL;

	TESTC_PROVIDER(0 < m_InternationalStrings.GetCount());
	TESTC_(CoCreateInstance(CLSID_DataLinks, NULL, CLSCTX_INPROC_SERVER, IID_IDBPromptInitialize, (void**)&pIDBPromptInitialize),S_OK); 

	TESTC(m_InternationalStrings.Lookup(rand()%m_InternationalStrings.GetCount(), wszUserID));
	TESTC(m_InternationalStrings.Lookup(rand()%m_InternationalStrings.GetCount(), wszPassword));
	TESTC(m_InternationalStrings.Lookup(rand()%m_InternationalStrings.GetCount(), wszInitialCatalog));

	// get properties to connect to a SQL Server where user can be added
	PropData.m_pwszRecordName = wcsDuplicate(L"Luxor");
	TESTC(PropData.InitFromFilter());
	TESTC_(PropData.GetNext(), S_OK);
	pPropSets = PropData.GetPropSets();
	TESTC(NULL != pPropSets);

	TESTC_(m_hr = CreateInitDSO(m_ProviderCLSID, pPropSets, IID_IDBInitialize, &pIUnknown), S_OK);
	
	// create the databse and the user
	TESTC(CreateSQLServerDB(pIUnknown, wszInitialCatalog));
	TESTC(CreateSQLServerUser(pIUnknown, wszUserID, wszPassword, wszInitialCatalog));
	
	TESTC(Dialog.SpawnPromptDataSource(pIDBPromptInitialize, NULL, 0, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetSecurityMethod(IDC_USE_STANDARD));

	// set server name
	if (m_pwszInitDataSource)
		TESTC(Dialog.SetInitDataSource(m_pwszInitDataSource));
	Sleep(1000);
	
	TESTC(Dialog.SetUserID(wszUserID));
	Sleep(1000);
	
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(wszPassword));
	Sleep(1000);
	
	TESTC(Dialog.SetDatabaseMethod());
	TESTC(Dialog.SetDatabaseOnServerName(wszInitialCatalog));

	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	PropData.Release();
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBPromptInitialize);

	// drop the databse and the user
	SAFE_RELEASE(pIUnknown);
	if (pPropSets)
	{
		CHECK(m_hr = CreateInitDSO(m_ProviderCLSID, pPropSets, IID_IDBInitialize, &pIUnknown), S_OK);
		DropSQLServerUser(pIUnknown, wszUserID);
		DropSQLServerDB(pIUnknown, wszInitialCatalog);
	}
	delete pPropSets;
	SAFE_RELEASE(pIUnknown);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END

int LuxorConnection::Variation_24()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	clock_t				ctStartTime, ctTotalTime;

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));

	ctStartTime = clock();
	TESTC(Dialog.GotoConnectionPage());
	ctTotalTime = clock() - ctStartTime;

	odtLog << "Performance (in clock ticks): " << ctTotalTime << "\n";
	odtLog << "Maximum delay allowed (in clock ticks): " << CLOCKS_PER_SEC << "\n";

	// The time to display the property page should
	// be within reasonable range. This check has been added because earlier when user
	// switch to Connection page, before displaying the contents of property page, the
	// provider tried to get all the SQL servers available on the network, causing
	// delays of upto 7 second. The network search for SQL Servers was later delayed
	// till user clicks on the combo box or the Refresh button.

	// Currently, we only allow 1 Second to switch to Connection page.
	TESTC(Dialog.KillThread(PSBTN_OK));

	TESTC(ctTotalTime <= CLOCKS_PER_SEC);
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 


int LuxorConnection::Variation_25() {

	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	clock_t				ctTotalTime;
	ULONG				ulTotalServers;

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));

	TESTC(Dialog.GotoConnectionPage());

	ulTotalServers = Dialog.Luxor_GetTotalServerCount(&ctTotalTime);
	odtLog << "Time to fetch and display " << ulTotalServers << " servers: " << ctTotalTime << " (in clock ticks)\n";
	odtLog << "Maximum time allowed (in clock ticks): " << (CLOCKS_PER_SEC<<1) << "\n";

	// Maximum tolerance for this procedure is set to be 2 seconds.
	// Although, this value highly depends on number of servers available
	// on network, but 2 seconds in pretty good value and luxor should
	// fetch more than 3000 servers in this time.
	TESTC(ctTotalTime <= (CLOCKS_PER_SEC<<1));

	TESTC(Dialog.KillThread(PSBTN_OK));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
}


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL LuxorConnection::Terminate()
{ 
// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(SockeyeConnection)
//*-----------------------------------------------------------------------
//| Test Case:		SockeyeConnection - test connection dialog for Sockeye
//| Created:  	7/27/98
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL SockeyeConnection::Init()
{ 
	TBEGIN
	IDBProperties	*pIDBProperties = NULL;
	HRESULT			hr;

	// {{ TCW_INIT_BASECLASS_CHECK
	TESTC(CPromptInitialize::Init());
	// }}

	if (GetModInfo()->GetProviderCLSID() != CLSID_MSDASQL)
		return TEST_SKIPPED;

	hr = GetModInfo()->CreateProvider(CLSID_MSDASQL, NULL, 
		IID_IDBProperties, (IUnknown**)&pIDBProperties);

	if (REGDB_E_CLASSNOTREG == hr)
		return TEST_SKIPPED;

	TESTC_(hr, S_OK);

CLEANUP:
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Set data source name, user name, blank password, uncheck save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_1()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_UNCHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Set data source name, user name, blank password, check save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_2()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Set data source name, user name, password, uncheck save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_3()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;

	// first, the negative case, bad password
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyeBadPassword));
	TESTC(Dialog.SetSavePassword(BST_UNCHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

	// the positive case
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

//	TESTC_(pIDBInitialize->Initialize(), S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Set data source name, user name, password, check save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_4()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;

	// first, the negative case, bad password
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyeBadPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

	// the positive case
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

//	TESTC_(pIDBInitialize->Initialize(), S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc International name provided for user, password, data source name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_5()
{ 
	TBEGIN
	WCHAR			wszName[cMaxName+1]	= L"";
	IDBInitialize	*pIDBInitialize		= NULL;
	CLocaleInfo		*pCLocaleInfo		= NULL;
	CDSL_Dialog		Dialog;

	// Create CLocaleInfo object instance
	// Use international data only wiht the appropriate registry settings
	// FindIntlSetting looks up the appropriate registry key
	TESTC_PROVIDER(FindIntlSetting());

	pCLocaleInfo = new CLocaleInfo(GetUserDefaultLCID());

	memset(wszName, 0, wcslen(wszName)*sizeof(WCHAR));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());

	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "server name: " << wszName << "\n";
	TESTC(Dialog.SetInitDataSource(wszName));
	
	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "password: " << wszName << "\n";
	TESTC(Dialog.SetPassword(wszName));

	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "user name: " << wszName << "\n";
	TESTC(Dialog.SetUserID(wszName));
	
	Sleep(1000);
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	delete pCLocaleInfo;
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc Various values for user name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_6()
{ 
	TBEGIN
	ULONG			i;
	IDBInitialize	*pIDBInitialize	= NULL;
	
	for (i=0; g_rgName[i][0] != L'\0'; i++)
	{
		CDSL_Dialog		Dialog;

		odtLog << "User ID: " << g_rgName[i] << "\n";
		
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetUserID(g_rgName[i]));
		Sleep(1000);
		TESTC(Dialog.KillThread(PSBTN_OK));
		TESTC(Dialog.IsResult(S_OK));
		TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
		SAFE_RELEASE(pIDBInitialize);
	}
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc Various values for password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_7()
{ 
	TBEGIN
	ULONG			i;
	IDBInitialize	*pIDBInitialize	= NULL;
	
	for (i=0; g_rgName[i][0] != L'\0'; i++)
	{
		CDSL_Dialog		Dialog;

		odtLog << "User ID: " << g_rgName[i] << "\n";
		
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetPassword(g_rgName[i]));
		Sleep(1000);
		TESTC(Dialog.KillThread(PSBTN_OK));
		TESTC(Dialog.IsResult(S_OK));
		TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
		SAFE_RELEASE(pIDBInitialize);
	}
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Long user name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_8()
{ 
	TBEGIN
	HRESULT			hr;
	WCHAR			*pwszLongName	= NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	CDSL_Dialog		Dialog;
	
	TESTC_PROVIDER(!BuildLongUserName(CLSID_MSDASQL, &pwszLongName));
	TESTC(NULL != pwszLongName);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));

	TESTC(Dialog.SetUserID(pwszLongName));
	
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TEST2C_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED, S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	SAFE_FREE(pwszLongName);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Long data source name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_9()
{ 
	TBEGIN
	HRESULT			hr;
	WCHAR			*pwszLongName	= NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	CDSL_Dialog		Dialog;
	
	TESTC_PROVIDER(!BuildLongUserName(CLSID_MSDASQL, &pwszLongName));
	TESTC(NULL != pwszLongName);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	
	TESTC(Dialog.SetInitDataSource(pwszLongName));
	
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TEST2C_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED, S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	SAFE_FREE(pwszLongName);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc Long password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_10()
{ 
	TBEGIN
	HRESULT			hr;
	WCHAR			*pwszLongName	= NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	CDSL_Dialog		Dialog;
	
	TESTC_PROVIDER(!BuildLongUserName(CLSID_MSDASQL, &pwszLongName));
	TESTC(NULL != pwszLongName);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	
	TESTC(Dialog.SetPassword(pwszLongName));
	
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TEST2C_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED, S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	SAFE_FREE(pwszLongName);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(11)
//*-----------------------------------------------------------------------
// @mfunc Check data source names against Sockeye enumerator
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_11()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	
	TESTC(Dialog.Sockeye_CheckDSNList());

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(12)
//*-----------------------------------------------------------------------
// @mfunc Bad password for existing user
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_12()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	
	TESTC(Dialog.SetPassword(g_wszSockeyeBadPassword));
	
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	Sleep(1000);
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(13)
//*-----------------------------------------------------------------------
// @mfunc Bad password for existing user, push the Test button
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_13()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	
	TESTC(Dialog.SetPassword(g_wszSockeyeBadPassword));
//	TESTC(Dialog.TestConnection(FALSE));
	TESTC(Dialog.TestConnection());

	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	Sleep(1000);
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(14)
//*-----------------------------------------------------------------------
// @mfunc Provide initial catalog name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_14()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));

	TESTC(Dialog.SetInitCatalog(g_wszDSNInitCat));
	
//	TESTC(Dialog.TestConnection(TRUE));
	TESTC(Dialog.TestConnection());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(15)
//*-----------------------------------------------------------------------
// @mfunc International strings as user names
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_15()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize	= NULL;
	CWString		wszUserID;
	CDSL_Dialog		Dialog;
	ULONG			ulString;

	for (ulString = 0; ulString < (ULONG)m_InternationalStrings.GetCount(); ulString++)
	{

		TESTC(m_InternationalStrings.Lookup(ulString, wszUserID));

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetUserID(wszUserID));
		Sleep(3000);
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(16)
//*-----------------------------------------------------------------------
// @mfunc International strings as passwords
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_16()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize	= NULL;
	CWString		wszPasword;
	CDSL_Dialog		Dialog;
	ULONG			ulString;

	for (ulString = 0; ulString < (ULONG)m_InternationalStrings.GetCount(); ulString++)
	{

		TESTC(m_InternationalStrings.Lookup(ulString, wszPasword));

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetUserID(L"something"));
		TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
		TESTC(Dialog.SetPassword(wszPasword));
		Sleep(3000);
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(17)
//*-----------------------------------------------------------------------
// @mfunc International strings as initial catalogs
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_17()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize	= NULL;
	CWString		wszInitCatalog;
	CDSL_Dialog		Dialog;
	ULONG			ulString;

	for (ulString = 0; ulString < (ULONG)m_InternationalStrings.GetCount(); ulString++)
	{

		TESTC(m_InternationalStrings.Lookup(ulString, wszInitCatalog));

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetInitCatalog((LPCWSTR)wszInitCatalog));
		Sleep(3000);
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(18)
//*-----------------------------------------------------------------------
// @mfunc International strings as datasource names
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_18()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize	= NULL;
	CWString		wszDSN;
	CDSL_Dialog		Dialog;
	ULONG			ulString;

	for (ulString = 0; ulString < (ULONG)m_InternationalStrings.GetCount(); ulString++)
	{

		TESTC(m_InternationalStrings.Lookup(ulString, wszDSN));

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetInitDataSource(wszDSN));
		Sleep(3000);
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(19)
//*-----------------------------------------------------------------------
// @mfunc International strings for a complete connection
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int SockeyeConnection::Variation_19()
{ 
	TBEGIN
	HRESULT				hr;
	CWString			wszUserID;
	CWString			wszPassword;
	CWString			wszInitialCatalog;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize = NULL;
	IUnknown			*pIUnknown		= NULL;
	CPropSets			*pPropSets		= NULL;
	CPropData			PropData;
	DBPROP				*pProp;
	IDBPromptInitialize	*pIDBPromptInitialize	= NULL;

	TESTC_PROVIDER(0 < m_InternationalStrings.GetCount());
	TESTC_(CoCreateInstance(CLSID_DataLinks, NULL, CLSCTX_INPROC_SERVER, IID_IDBPromptInitialize, (void**)&pIDBPromptInitialize),S_OK); 

	TESTC(m_InternationalStrings.Lookup(rand()%m_InternationalStrings.GetCount(), wszUserID));
	TESTC(m_InternationalStrings.Lookup(rand()%m_InternationalStrings.GetCount(), wszPassword));
	TESTC(m_InternationalStrings.Lookup(rand()%m_InternationalStrings.GetCount(), wszInitialCatalog));

	// get properties to connect to a SQL Server where user can be added
	PropData.m_pwszRecordName = wcsDuplicate(L"Sockeye_SQLServer");
	TESTC(PropData.InitFromFilter());
	TESTC_(PropData.GetNext(), S_OK);
	pPropSets = PropData.GetPropSets();
	TESTC(NULL != pPropSets);
	
	TESTC_(m_hr = CreateInitDSO(CLSID_MSDASQL, pPropSets, IID_IDBInitialize, &pIUnknown), S_OK);
	
	// create the databse and the user
	TESTC(CreateSQLServerDB(pIUnknown, wszInitialCatalog));
	TESTC(CreateSQLServerUser(pIUnknown, wszUserID, wszPassword, wszInitialCatalog));
	
	TESTC(Dialog.SpawnPromptDataSource(pIDBPromptInitialize, NULL, 0, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());

	// set server name
	pProp = pPropSets->FindProperty(DBPROP_INIT_DATASOURCE, DBPROPSET_DBINIT);
	TESTC_PROVIDER(NULL != pProp);
	TESTC(VT_BSTR == pProp->vValue.vt);
	TESTC(Dialog.SetInitDataSource(V_BSTR(&pProp->vValue)));
	Sleep(1000);
	
	TESTC(Dialog.SetUserID(wszUserID));
	Sleep(1000);
	
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(wszPassword));
	Sleep(1000);
	
	TESTC(Dialog.SetInitCatalog(wszInitialCatalog));

	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

//	TESTC_(pIDBInitialize->Initialize(), S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	PropData.Release();
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBPromptInitialize);

	// drop the databse and the user
	SAFE_RELEASE(pIUnknown);
	if (pPropSets)
	{
		CHECK(m_hr = CreateInitDSO(CLSID_MSDASQL, pPropSets, IID_IDBInitialize, &pIUnknown), S_OK);
		DropSQLServerUser(pIUnknown, wszUserID);
		DropSQLServerDB(pIUnknown, wszInitialCatalog);
	}	
	delete pPropSets;
	SAFE_RELEASE(pIUnknown);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL SockeyeConnection::Terminate()
{ 
// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END




// {{ TCW_TC_PROTOTYPE(Jolt40Connection)
//*-----------------------------------------------------------------------
//| Test Case:		Jolt40Connection - test connection dialog for  Jolt40
//| Created:  	8/21/98
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL Jolt40Connection::Init()
{ 
	TBEGIN
	IDBProperties	*pIDBProperties = NULL;
	HRESULT			hr;

	// {{ TCW_INIT_BASECLASS_CHECK
	TESTC(CPromptInitialize::Init());
	// }}

	if (GetModInfo()->GetProviderCLSID() != CLSID_JOLT40)
		return TEST_SKIPPED;

	hr = GetModInfo()->CreateProvider(CLSID_JOLT40, NULL, 
		IID_IDBProperties, (IUnknown**)&pIDBProperties);

	if (REGDB_E_CLASSNOTREG == hr)
		return TEST_SKIPPED;

	TESTC_(hr, S_OK);

CLEANUP:
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc General test: select the provider, select or chose a database name, go for authentification, ok
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_1()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	HRESULT				hr;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_szLocalAccessDB));
	TESTC(Dialog.SetUserID(g_szAccessUserName));
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_UNCHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END





// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc General case, press Test Connection
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_2()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_szLocalAccessDB));
	TESTC(Dialog.SetUserID(g_szAccessUserName));
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_UNCHECKED));

//	TESTC(Dialog.TestConnection(TRUE));
	TESTC(Dialog.TestConnection());
	TESTC(Dialog.SetInitDataSource(L"Not really a database"));
//	TESTC(Dialog.TestConnection(FALSE));
	TESTC(Dialog.TestConnection());

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc general test: select the provider, select or chose a remote database name, go for authentification, ok
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_3()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_szRemoteAccessDB));
	TESTC(Dialog.SetUserID(g_szAccessUserName));
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

//	TESTC_(m_hr = pIDBInitialize->Initialize(), S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Various values for user name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_4()
{ 
	TBEGIN
	ULONG			i;
	CDSL_Dialog		Dialog;
	IDBInitialize	*pIDBInitialize		= NULL;
	
	for (i=0; g_rgName[i][0] != L'\0'; i++)
	{
		odtLog << "User ID: " << g_rgName[i] << "\n";
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_JOLT40));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetInitDataSource(g_szLocalAccessDB));
		TESTC(Dialog.SetUserID(g_rgName[i]));
		TESTC(Dialog.SetBlankPassword());
		Sleep(1000);
		TESTC(Dialog.KillThread(PSBTN_OK));
		TESTC(Dialog.IsResult(S_OK));

CLEANUP:
		SAFE_RELEASE(pIDBInitialize);
	}

	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Various values for password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_5()
{ 
	TBEGIN
	ULONG			i;
	CDSL_Dialog		Dialog;
	IDBInitialize	*pIDBInitialize		= NULL;
	
	for (i=0; g_rgName[i][0] != L'\0'; i++)
	{
		odtLog << "Password: " << g_rgName[i] << "\n";
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_JOLT40));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetInitDataSource(g_szLocalAccessDB));
		TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
		TESTC(Dialog.SetPassword(g_rgName[i]));
		Sleep(1000);
		TESTC(Dialog.KillThread(PSBTN_OK));
		TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	}

	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc International database name, user name, password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_6()
{ 
	TBEGIN
	WCHAR			wszName[cMaxName+1]	= L"";
	IDBInitialize	*pIDBInitialize		= NULL;
	CLocaleInfo		*pCLocaleInfo		= NULL;
	CDSL_Dialog		Dialog;

	// Create CLocaleInfo object instance
	// Use international data only wiht the appropriate registry settings
	// FindIntlSetting looks up the appropriate registry key
	TESTC_PROVIDER(FindIntlSetting());

	pCLocaleInfo = new CLocaleInfo(GetUserDefaultLCID());

	memset(wszName, 0, wcslen(wszName)*sizeof(WCHAR));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());

	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "server name: " << wszName << "\n";
	TESTC(Dialog.SetInitDataSource(wszName));
	
	TESTC(Dialog.SetSecurityMethod(IDC_USE_STANDARD));
	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "password: " << wszName << "\n";
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(wszName));

	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "user name: " << wszName << "\n";
	TESTC(Dialog.SetUserID(wszName));
	
	Sleep(1000);
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	delete pCLocaleInfo;
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc A long database name, user name and password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_7()
{ 
	TBEGIN
	HRESULT			hr;
	WCHAR			*pwszLongName	= NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	CDSL_Dialog		Dialog;
	
	TESTC_PROVIDER(!BuildLongUserName(CLSID_JOLT40, &pwszLongName));
	TESTC(NULL != pwszLongName);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(pwszLongName));
	TESTC(Dialog.SetUserID(pwszLongName));
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(pwszLongName));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	SAFE_FREE(pwszLongName);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Password and save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_8()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_szLocalAccessDB));
	TESTC(Dialog.SetUserID(g_szAccessUserName));
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(L"Set some 19password"));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Password and don't save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_9()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_szLocalAccessDB));
	TESTC(Dialog.SetUserID(g_szAccessUserName));
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(L"Some other 81 .password"));
	TESTC(Dialog.SetSavePassword(BST_UNCHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc Blank password, save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_10()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_szLocalAccessDB));
	TESTC(Dialog.SetUserID(g_szAccessUserName));
	TESTC(Dialog.SetBlankPassword(BST_CHECKED));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.TestConnection());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(11)
//*-----------------------------------------------------------------------
// @mfunc Blank password, do not save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_11()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_szLocalAccessDB));
	TESTC(Dialog.SetUserID(g_szAccessUserName));
	TESTC(Dialog.SetBlankPassword(BST_CHECKED));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(12)
//*-----------------------------------------------------------------------
// @mfunc Bad password for an existing user
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_12()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_szLocalAccessDB));
	TESTC(Dialog.SetUserID(g_szAccessUserName));
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(g_szAccessBadPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(13)
//*-----------------------------------------------------------------------
// @mfunc Bad password for an existing user; test connection button
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_13()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_szLocalAccessDB));
	TESTC(Dialog.SetUserID(g_szAccessUserName));
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(g_szAccessBadPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
//	TESTC(Dialog.TestConnection(FALSE));
	TESTC(Dialog.TestConnection());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(14)
//*-----------------------------------------------------------------------
// @mfunc Pop up the browser dialog
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int Jolt40Connection::Variation_14()
{ 
	TBEGIN
	CHAR			*szLocalAccessDB		= ConvertToMBCS(g_szLocalAccessDB);
	IDBInitialize	*pIDBInitialize = NULL;
	CDSL_Dialog		Dialog;

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.SelectProvider(CLSID_JOLT40));
	TESTC(Dialog.GotoConnectionPage());
	Sleep(1000);

	// press browser button near database name edit control
	TESTC(Dialog.OpenFileBrowser());
	// simulate that we chose a file
	TESTC(Dialog.SetInitFileNameInBrowser(szLocalAccessDB));
	// close the browser by pressing the open button
	TESTC(Dialog.FileBrowser_OnOpen());

	// once more, this time go for CANCEL
	// press browser button near database name edit control
	TESTC(Dialog.OpenFileBrowser());
	// simulate that we chose a file
	TESTC(Dialog.SetInitFileNameInBrowser("aiurea vorbirea"));
	// close the browser by pressing the open button
	TESTC(Dialog.FileBrowser_OnCancel());
	
	// send completion message
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	SAFE_FREE(szLocalAccessDB);
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL Jolt40Connection::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(MSDAORAConnection)
//*-----------------------------------------------------------------------
//| Test Case:		MSDAORAConnection - test connection dialog for  MSDAORA
//| Created:  	8/21/98
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL MSDAORAConnection::Init()
{ 
	TBEGIN
	IDBProperties	*pIDBProperties = NULL;
	HRESULT			hr;

	// {{ TCW_INIT_BASECLASS_CHECK
	TESTC(CPromptInitialize::Init());
	// }}

	if (GetModInfo()->GetProviderCLSID() != CLSID_MSDAORA)
		return TEST_SKIPPED;

	hr = GetModInfo()->CreateProvider(CLSID_MSDAORA, NULL, 
		IID_IDBProperties, (IUnknown**)&pIDBProperties);

	if (REGDB_E_CLASSNOTREG == hr)
		return TEST_SKIPPED;

	TESTC_(hr, S_OK);

CLEANUP:
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc General test: select the provider, select or chose a name, go for authentification, ok
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_1()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_szOracleServer));
	TESTC(Dialog.SetUserID(g_szCanoeUserName));
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(g_szCanoeGoodPassword));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END





// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc General case, press Test Connection
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_2()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_szOracleServer));
	TESTC(Dialog.SetUserID(g_szCanoeUserName));
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(g_szCanoeGoodPassword));

//	TESTC(Dialog.TestConnection(TRUE));
	TESTC(Dialog.TestConnection());

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Various values for user name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_3()
{ 
	TBEGIN
	ULONG			i;
	IDBInitialize	*pIDBInitialize	= NULL;
	
	for (i=0; g_rgName[i][0] != L'\0'; i++)
	{
		CDSL_Dialog		Dialog;

		odtLog << "User ID: " << g_rgName[i] << "\n";
		
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetUserID(g_rgName[i]));
		Sleep(1000);
		TESTC(Dialog.KillThread(PSBTN_OK));
		TESTC(Dialog.IsResult(S_OK));
		TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
		SAFE_RELEASE(pIDBInitialize);
	}
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Various values for password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_4()
{ 
	TBEGIN
	ULONG			i;
	IDBInitialize	*pIDBInitialize	= NULL;
	
	for (i=0; g_rgName[i][0] != L'\0'; i++)
	{
		CDSL_Dialog		Dialog;

		odtLog << "Password: " << g_rgName[i] << "\n";
		
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetPassword(g_rgName[i]));
		Sleep(1000);
		TESTC(Dialog.KillThread(PSBTN_OK));
		TESTC(Dialog.IsResult(S_OK));
		TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
		SAFE_RELEASE(pIDBInitialize);
	}
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc International server name, user name and password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_5()
{ 
	TBEGIN
	WCHAR			wszName[cMaxName+1]	= L"";
	IDBInitialize	*pIDBInitialize		= NULL;
	CLocaleInfo		*pCLocaleInfo		= NULL;
	CDSL_Dialog		Dialog;

	// Create CLocaleInfo object instance
	// Use international data only wiht the appropriate registry settings
	// FindIntlSetting looks up the appropriate registry key
	TESTC_PROVIDER(FindIntlSetting());

	pCLocaleInfo = new CLocaleInfo(GetUserDefaultLCID());

	memset(wszName, 0, wcslen(wszName)*sizeof(WCHAR));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
	TESTC(Dialog.GotoConnectionPage());

	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "server name: " << wszName << "\n";
	TESTC(Dialog.SetServerName(wszName));
	
	TESTC(Dialog.SetSecurityMethod(IDC_USE_STANDARD));
	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "password: " << wszName << "\n";
	TESTC(Dialog.SetPassword(wszName));

	pCLocaleInfo->MakeUnicodeIntlString(wszName, cMaxName);
	odtLog << "user name: " << wszName << "\n";
	TESTC(Dialog.SetUserID(wszName));
	
	Sleep(1000);
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	delete pCLocaleInfo;
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc A long server name, user name and password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_6()
{ 
	TBEGIN
	HRESULT			hr;
	WCHAR			*pwszLongName	= NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	CDSL_Dialog		Dialog;
	
	TESTC_PROVIDER(!BuildLongUserName(CLSID_MSDAORA, &pwszLongName));
	TESTC(NULL != pwszLongName);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(pwszLongName));
	TESTC(Dialog.SetUserID(pwszLongName));
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(pwszLongName));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	SAFE_FREE(pwszLongName);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc Password and save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_7()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_szOracleServer));
	TESTC(Dialog.SetUserID(g_szCanoeUserName));
	TESTC(Dialog.SetPassword(g_szCanoeGoodPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Password and don't save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_8()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_szOracleServer));
	TESTC(Dialog.SetUserID(g_szCanoeUserName));
	TESTC(Dialog.SetPassword(g_szCanoeGoodPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Blank password, save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_9()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_szOracleServer));
	TESTC(Dialog.SetUserID(g_szCanoeUserName));
	TESTC(Dialog.SetBlankPassword(BST_CHECKED));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc Blank password, do not save password
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_10()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_szOracleServer));
	TESTC(Dialog.SetUserID(g_szCanoeUserName));
	TESTC(Dialog.SetBlankPassword(BST_CHECKED));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(11)
//*-----------------------------------------------------------------------
// @mfunc Bad password for an existing user
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_11()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_szOracleServer));
	TESTC(Dialog.SetUserID(g_szCanoeUserName));
	TESTC(Dialog.SetPassword(g_szCanoeBadPassword));
	TESTC(Dialog.SetSavePassword(BST_UNCHECKED));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(12)
//*-----------------------------------------------------------------------
// @mfunc Bad password for an existing user; test connection button
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_12()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_szOracleServer));
	TESTC(Dialog.SetUserID(g_szCanoeUserName));
	TESTC(Dialog.SetPassword(g_szCanoeBadPassword));
	TESTC(Dialog.SetSavePassword(BST_UNCHECKED));

//	TESTC(Dialog.TestConnection(FALSE));
	TESTC(Dialog.TestConnection());

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

//	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(13)
//*-----------------------------------------------------------------------
// @mfunc International strings as user names
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_13()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize	= NULL;
	CWString		wszUserID;
	CDSL_Dialog		Dialog;
	ULONG			ulString;

	for (ulString = 0; ulString < (ULONG)m_InternationalStrings.GetCount(); ulString++)
	{

		TESTC(m_InternationalStrings.Lookup(ulString, wszUserID));

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetUserID(wszUserID));
		Sleep(3000);
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(14)
//*-----------------------------------------------------------------------
// @mfunc International strings as passwords
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_14()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize	= NULL;
	CWString		wszPassword;
	CDSL_Dialog		Dialog;
	ULONG			ulString;

	for (ulString = 0; ulString < (ULONG)m_InternationalStrings.GetCount(); ulString++)
	{

		TESTC(m_InternationalStrings.Lookup(ulString, wszPassword));

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
		TESTC(Dialog.SetPassword(wszPassword));
		Sleep(3000);
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(15)
//*-----------------------------------------------------------------------
// @mfunc International strings as server names
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_15()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize	= NULL;
	CWString		wszServerName;
	CDSL_Dialog		Dialog;
	ULONG			ulString;

	for (ulString = 0; ulString < (ULONG)m_InternationalStrings.GetCount(); ulString++)
	{

		TESTC(m_InternationalStrings.Lookup(ulString, wszServerName));

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		// select the provider indicated by the init string
		TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetServerName(wszServerName));
		Sleep(3000);
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(16)
//*-----------------------------------------------------------------------
// @mfunc International user name and password, initialize DSO
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int MSDAORAConnection::Variation_16()
{ 
	TBEGIN
	HRESULT					hr;
	CWString				wszUserID;
	CWString				wszPassword;
	CWString				wszInitialCatalog;
	CDSL_Dialog				Dialog;
	IUnknown				*pIUnknown		= NULL;
	IDBInitialize			*pIDBInitialize = NULL;
	CPropSets				*pPropSets = NULL;
	CPropData				PropData;
	DBPROP					*pProp;
	IDBPromptInitialize		*pIDBPromptInitialize	= NULL;

	TESTC_PROVIDER(0 < m_InternationalStrings.GetCount());
	TESTC_(CoCreateInstance(CLSID_DataLinks, NULL, CLSCTX_INPROC_SERVER, IID_IDBPromptInitialize, (void**)&pIDBPromptInitialize),S_OK); 

	TESTC(m_InternationalStrings.Lookup(rand()%m_InternationalStrings.GetCount(), wszUserID));
	TESTC(m_InternationalStrings.Lookup(rand()%m_InternationalStrings.GetCount(), wszPassword));
	TESTC(m_InternationalStrings.Lookup(rand()%m_InternationalStrings.GetCount(), wszInitialCatalog));

	// get properties to connect to a SQL Server where user can be added
	PropData.m_pwszRecordName = wcsDuplicate(L"Canoe");
	TESTC(PropData.InitFromFilter());
	TESTC_(PropData.GetNext(), S_OK);
	pPropSets = PropData.GetPropSets();
	TESTC(NULL != pPropSets);

	TESTC_(m_hr = CreateInitDSO(CLSID_MSDAORA, pPropSets, IID_IDBInitialize, &pIUnknown), S_OK);
	
	// create the databse and the user
	TESTC(CreateOracleUser(pIUnknown, wszUserID, wszPassword, wszInitialCatalog));
	
	TESTC(Dialog.SpawnPromptDataSource(pIDBPromptInitialize, NULL, 0, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_MSDAORA));
	TESTC(Dialog.GotoConnectionPage());

	// set server name
	pProp = pPropSets->FindProperty(DBPROP_INIT_DATASOURCE, DBPROPSET_DBINIT);
	TESTC_PROVIDER(NULL != pProp);
	TESTC(VT_BSTR == pProp->vValue.vt);
	TESTC(Dialog.SetServerName(V_BSTR(&pProp->vValue)));
	Sleep(1000);
	
	TESTC(Dialog.SetUserID(wszUserID));
	Sleep(1000);
	
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(wszPassword));
	Sleep(1000);
	
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

//	TESTC_(pIDBInitialize->Initialize(), S_OK);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);

CLEANUP:
	PropData.Release();
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBPromptInitialize);

	// drop the databse and the user
	SAFE_RELEASE(pIUnknown);
	if (pPropSets)
	{
		CHECK(m_hr = CreateInitDSO(CLSID_MSDAORA, pPropSets, IID_IDBInitialize, &pIUnknown), S_OK);
		DropOracleUser(pIUnknown, wszUserID);
	}
	delete pPropSets;
	SAFE_RELEASE(pIUnknown);
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL MSDAORAConnection::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(GeneralConnection)
//*-----------------------------------------------------------------------
//| Test Case:		GeneralConnection - general connection dialog testing
//| Created:  	8/21/98
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL GeneralConnection::Init()
{ 
	TBEGIN

	TESTC(CPromptInitialize::Init());
	
CLEANUP:
	TRETURN
} 





// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Goto Connection page using the Next button in the provider page
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int GeneralConnection::Variation_1()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize = NULL;
	CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd,
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL,
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.PushButton(IDC_Next));
	TESTC(Dialog.IsCurrentPage(g_nConnection));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Check radio button in the integrated/standard security group
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int GeneralConnection::Variation_2()
{ 
	TBEGIN
	CDSL_Dialog		Dialog;
	IUnknown		*pIUnknown		= NULL;
	ULONG			ulProvIndx;
	ULONG			ulOp;
	BOOL			res = 0;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IUnknown, &pIUnknown));

	TESTC(Dialog.IsInExecution());

	// iterate through all providers
	for (	ulProvIndx = 0;
			ulProvIndx < CDSL_Dialog::s_pSourcesSet->Count();
			ulProvIndx++)
	{
		odtLog << "\n";

		BOOL	fEnIntegrated = FALSE;
		BOOL	fStandardSupp	= FALSE;

		// if datasource is not a provider skip the iteration
		if (	DBSOURCETYPE_DATASOURCE_TDP != (*g_pSourcesSet)[ulProvIndx].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != (*g_pSourcesSet)[ulProvIndx].m_wType
			||	CUSTOM_CONN & (*g_pSourcesSet)[ulProvIndx].m_CustomUI)
			continue;

		TESTC(Dialog.GotoProviderPage());
		TESTC(Dialog.SelectProvider((WCHAR*)(*g_pSourcesSet)[ulProvIndx]));
		if ((res=Dialog.GotoConnectionPage()) == TEST_SKIPPED)
			continue;
		TESTC(res);
		
		// if the property is supported, both radio buttons have to be enabled
		fEnIntegrated = (*g_pSourcesSet)[ulProvIndx].m_PropInfoSets.SupportedProperty(DBPROP_AUTH_INTEGRATED, DBPROPSET_DBINIT);
		if (!fEnIntegrated)
			continue;

		if (	(*g_pSourcesSet)[ulProvIndx].m_PropInfoSets.SupportedProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT)
			||	(*g_pSourcesSet)[ulProvIndx].m_PropInfoSets.SupportedProperty(DBPROP_AUTH_USERID, DBPROPSET_DBINIT)
			)
			fStandardSupp = TRUE;

		for (ulOp = 0; ulOp < 5; ulOp++)
		{
			if (fStandardSupp)
			{
				TESTC(Dialog.IsControlEnabled(IDC_USE_STANDARD));
			}
			else
			{
				TESTC(!Dialog.IsControlEnabled(IDC_USE_STANDARD));
			}
			TESTC(Dialog.IsControlEnabled(IDC_USE_INTEGRATED));
			if (ulOp & 1)
			{
				if (fStandardSupp)
					TESTC(Dialog.SetSecurityMethod(IDC_USE_STANDARD));
			}
			else
			{
				TESTC(Dialog.SetSecurityMethod(IDC_USE_INTEGRATED));
			}
			Sleep(100);
		}
	}
	
	TESTC(Dialog.KillThread	());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIUnknown);


CLEANUP:
	SAFE_RELEASE(pIUnknown);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Create and initialize several DSOs using DSL, release them, bring up DSL and select provider; check that only default props are set
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int GeneralConnection::Variation_3()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize = NULL;
	DBORDINAL		index;
	CDSL_Dialog		*pDialog		= NULL;

	DBPROP			*pPropUserID	= NULL;
	DBPROP			*pPropPassword	= NULL;
	DBPROP			*pPropDataSource= NULL;

	pPropUserID = m_PropSets.FindProperty(DBPROP_AUTH_USERID, DBPROPSET_DBINIT);
	TESTC_PROVIDER(NULL != pPropUserID);

	pPropPassword = m_PropSets.FindProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT);
	TESTC_PROVIDER(NULL != pPropPassword);
	
	pPropDataSource = m_PropSets.FindProperty(DBPROP_INIT_DATASOURCE, DBPROPSET_DBINIT);
	TESTC_PROVIDER(NULL != pPropDataSource);

	for (index = 0; index< 5; index++)
	{
		pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd,
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL,
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

		TESTC(pDialog->IsInExecution());
		TESTC(pDialog->SelectProvider(m_ProviderCLSID));
		TESTC(pDialog->PushButton(IDC_Next));
		TESTC(pDialog->IsCurrentPage(g_nConnection));
		
		if (VT_BSTR == pPropUserID->vValue.vt)
			TESTC(pDialog->SetUserID(V_BSTR(&pPropUserID->vValue)));
		
		if (VT_BSTR == pPropPassword->vValue.vt)
			TESTC(pDialog->SetPassword(V_BSTR(&pPropPassword->vValue)));

		if (VT_BSTR == pPropDataSource->vValue.vt)
			TESTC(pDialog->SetInitDataSource(V_BSTR(&pPropDataSource->vValue)));

		TESTC(pDialog->KillThread());
		TESTC(pDialog->IsResult(S_OK));
		SAFE_DELETE(pDialog);
		TESTC_(pIDBInitialize->Initialize(), S_OK);
		SAFE_RELEASE(pIDBInitialize);
	}

	pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd,
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL,
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(pDialog->IsInExecution());
	TESTC(pDialog->SelectProvider(m_ProviderCLSID));
	TESTC(pDialog->PushButton(IDC_Next));
	TESTC(pDialog->IsCurrentPage(g_nConnection));
	TESTC(pDialog->KillThread());
	TESTC(pDialog->IsResult(S_OK));
	SAFE_DELETE(pDialog);
	TEST2C_(pIDBInitialize->Initialize(), E_FAIL, DB_SEC_E_AUTH_FAILED);
	SAFE_RELEASE(pIDBInitialize);

CLEANUP:
	delete pDialog;
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Check the list of init catalogs
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int GeneralConnection::Variation_4()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize = NULL;
	HWND			hWndInitCatalogs;
	CComboBox		ComboBox;
	CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd,
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL,
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	DBPROP			*pPropUserID	= NULL;
	DBPROP			*pPropPassword	= NULL;
	DBPROP			*pPropDataSource= NULL;
	CLightDataSource	DSO;
	CServiceComp	ServiceComp;
	CCatalogs		*pCatalogs		= NULL;
	CSourceInfo		&SourceInfo		= (*CDSL_Dialog::s_pSourcesSet)[m_ProviderCLSID];
	DBORDINAL		indexCat, indexList;
	IGetDataSource	*pIGetDS		= NULL;

	TESTC_PROVIDER(CLSID_MSDAORA != m_ProviderCLSID
		&&	CLSID_JOLT351 != m_ProviderCLSID 
		&&	CLSID_JOLT40 != m_ProviderCLSID
		&&	(0 == (CUSTOM_CONN & SourceInfo.m_CustomUI)));

	TESTC_PROVIDER(SourceInfo.m_PropInfoSets.SettableProperty(DBPROP_INIT_CATALOG, DBPROPSET_DBINIT));

	TESTC_(ServiceComp.CoCreateDSO(&DSO, m_ProviderCLSID, IID_IDBInitialize, m_PropSets, m_PropSets, TRUE), S_OK);
	TESTC_(((IDBCreateSession*)DSO)->CreateSession(NULL, IID_IGetDataSource, (IUnknown**)&pIGetDS), S_OK);
	pCatalogs = new CCatalogs(pIGetDS);

	pPropUserID = m_PropSets.FindProperty(DBPROP_AUTH_USERID, DBPROPSET_DBINIT);
	TESTC_PROVIDER(NULL != pPropUserID);

	pPropPassword = m_PropSets.FindProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT);
	TESTC_PROVIDER(NULL != pPropPassword);
	
	pPropDataSource = m_PropSets.FindProperty(DBPROP_INIT_DATASOURCE, DBPROPSET_DBINIT);
	TESTC_PROVIDER(NULL != pPropDataSource);

	TESTC(Dialog.IsInExecution());
	
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));

	TESTC(Dialog.PushButton(IDC_Next));
	TESTC(Dialog.IsCurrentPage(g_nConnection));

	if (VT_BSTR == pPropUserID->vValue.vt)
		TESTC(Dialog.SetUserID(V_BSTR(&pPropUserID->vValue)));
	
	if (VT_BSTR == pPropPassword->vValue.vt)
		TESTC(Dialog.SetPassword(V_BSTR(&pPropPassword->vValue)));

	if (VT_BSTR == pPropDataSource->vValue.vt)
		TESTC(Dialog.SetInitDataSource(V_BSTR(&pPropDataSource->vValue)));

	if (CLSID_SQLOLEDB == m_ProviderCLSID)
		TESTC(Dialog.SetDatabaseMethod(IDC_UseDatabaseOnServerName));

	if (CLSID_SQLOLEDB == m_ProviderCLSID)
		hWndInitCatalogs = Dialog.GetDlgItem(IDC_DatabaseOnServerName);
	else
		hWndInitCatalogs = Dialog.GetDlgItem(IDC_DBPROP_INIT_CATALOG);

	// all the authentification elements should have been set by now
	// drop down the combo box and read the initial catalogs available
	TESTC(ComboBox.SetHWND(hWndInitCatalogs));
	TESTC(ComboBox.ShowDropDown(TRUE));
	TESTC(ComboBox.RetrieveListContent());

	// compare the catalogs against the ones obtained from Schema Rowsets
	TESTC(pCatalogs->cCatalogs() == ComboBox.GetListSize());
	for (indexCat = 0; indexCat < pCatalogs->cCatalogs(); indexCat++)
	{
		for (indexList = 0; indexList < ComboBox.GetListSize(); indexList++)
		{
			if (0 == wcscmp((*pCatalogs)[indexCat], ComboBox.GetList()[indexList]))
				break;
		}
		if (indexList >= ComboBox.GetListSize())
		{
			odtLog << (*pCatalogs)[indexCat] << " not found in the list\n";
			TESTC(FALSE);
		}
	}

	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	SAFE_DELETE(pCatalogs);
	SAFE_RELEASE(pIGetDS);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Bring up the DSL dialog, select provider, drop down the init catalog combo box, close
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int GeneralConnection::Variation_5()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize = NULL;
	DBPROP			*pPropDataSource= NULL;
	HWND			hWndInitCatalogs;
	ULONG			ulIndex;
	ULONG			ulIndex2;
	CComboBox		ComboBox;
	CWString		*rgwszStrings	= NULL;
	CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd,
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL,
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize);
	CSourceInfo		&SourceInfo		= (*CDSL_Dialog::s_pSourcesSet)[m_ProviderCLSID];
	// init string in LTM was used to create a session
	// use the session to find out the catalogs available inthe datasource
	CCatalogs		Catalogs(m_pThisTestModule->m_pIUnknown2);

	TESTC_PROVIDER(CLSID_MSDAORA != m_ProviderCLSID
		&&	CLSID_JOLT351 != m_ProviderCLSID 
		&&	CLSID_JOLT40 != m_ProviderCLSID
		&&	(0 == (CUSTOM_CONN & SourceInfo.m_CustomUI)));

	TESTC_PROVIDER(SourceInfo.m_PropInfoSets.SettableProperty(DBPROP_INIT_CATALOG, DBPROPSET_DBINIT));

	TESTC(Dialog.IsInExecution());
	
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));

	TESTC(Dialog.PushButton(IDC_Next));
	TESTC(Dialog.IsCurrentPage(g_nConnection));

	if (CLSID_SQLOLEDB == m_ProviderCLSID)
		TESTC(Dialog.SetDatabaseMethod(IDC_UseDatabaseOnServerName));

	pPropDataSource = m_PropSets.FindProperty(DBPROP_INIT_DATASOURCE, DBPROPSET_DBINIT);
	TESTC_PROVIDER(NULL != pPropDataSource);

	TESTC_PROVIDER(VT_BSTR == pPropDataSource->vValue.vt);
	TESTC(Dialog.SetInitDataSource(V_BSTR(&pPropDataSource->vValue)));

	if (CLSID_SQLOLEDB == m_ProviderCLSID)
	{
		TESTC(Dialog.SetSecurityMethod(IDC_USE_STANDARD));
		hWndInitCatalogs = Dialog.GetDlgItem(IDC_DatabaseOnServerName);
	}
	else
		hWndInitCatalogs = Dialog.GetDlgItem(IDC_DBPROP_INIT_CATALOG);

	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	// all the authentification elements should have been set by now
	// drop down the combo box and read the initial catalogs available
	TESTC(ComboBox.SetHWND(hWndInitCatalogs));
	TESTC(ComboBox.ShowDropDown(TRUE));
	TESTC(ComboBox.RetrieveListContent());

	rgwszStrings = ComboBox.GetList();
	TESTC((0 == ComboBox.GetListSize()) || rgwszStrings);

	// compare the catalogs against the ones obtained from Schema Rowsets
	TESTC(Catalogs.cCatalogs() == ComboBox.GetListSize());
	for (ulIndex = 0; ulIndex < ComboBox.GetListSize(); ulIndex++)
	{
		if (!COMPARE(NULL != (LPWSTR)(LPCWSTR)rgwszStrings[ulIndex], TRUE))
			continue;

		// make sure no duplicates were included in the combo box list
		for (ulIndex2 = 0; ulIndex2 < ulIndex; ulIndex2++)
		{
			if (rgwszStrings[ulIndex2])
				COMPARE(0 != wcscmp((LPWSTR)(LPCWSTR)rgwszStrings[ulIndex], 
									(LPWSTR)(LPCWSTR)rgwszStrings[ulIndex2]), TRUE);
		}

		// make sure the catalog is contained in the data source
		CHECK(Catalogs.DoesCatalogExist((LPWSTR)(LPCWSTR)rgwszStrings[ulIndex]), S_OK);
	}

	TESTC(ComboBox.ShowDropDown(FALSE));

	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




BOOL GeneralConnection::Common_ANSI_OEM_Scenario(
	BOOL	fUseANSIToCreateUDLFile,
	BOOL	fUseANSIToPopUpDialog
)
{
	TBEGIN
	// Currency symbol, English Pound (different on ANSI and OEM)
	WCHAR			wch = 0x00A3;	
	WCHAR			wszUDLFileName[] = { wch, wch, wch, L'.', L'u', L'd', L'l', L'\0' } ;
	CDSL_Dialog		Dialog;

	_wremove(wszUDLFileName);

	//Default is ANSI, (but just make sure)
	TESTC(AreFileApisANSI());

	//Make sure that the file name can actually be converted to ANSI.
	TESTC_PROVIDER( iswcharMappable(wch) );

	//(this is the default but just for completeness will will repeat here)
	if (fUseANSIToCreateUDLFile)
		SetFileApisToANSI();
	else
		SetFileApisToOEM();

	TESTC(Dialog.CreateUDLFile(wszUDLFileName));

	if (fUseANSIToPopUpDialog)
		SetFileApisToANSI();
	else
		SetFileApisToOEM();
	
	TESTC(Dialog.SpawnUDLFile(wszUDLFileName));
	TESTC_PROVIDER(Dialog.IsInExecution());
	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectProvider(m_ProviderCLSID));
	TESTC(Dialog.KillThread());

CLEANUP:
	SetFileApisToANSI();
	_wremove(wszUDLFileName);
	TRETURN
} //GeneralConnection::Common_ANSI_OEM_Scenario




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc ANSI -> ANSI
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int GeneralConnection::Variation_6()
{ 
	return Common_ANSI_OEM_Scenario(TRUE, TRUE);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc OEM -> OEM
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int GeneralConnection::Variation_7()
{ 
	return Common_ANSI_OEM_Scenario(FALSE, FALSE);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc ANSI -> OEM
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int GeneralConnection::Variation_8()
{ 
	return Common_ANSI_OEM_Scenario(TRUE, FALSE);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc OEM -> ANSI
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int GeneralConnection::Variation_9()
{ 
	return Common_ANSI_OEM_Scenario(FALSE, TRUE);
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL GeneralConnection::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END





// {{ TCW_TC_PROTOTYPE(CDSOAndRIID)
//*-----------------------------------------------------------------------
//| Test Case:		CDSOAndRIID - various values for ppDataSource in IDBPromptInitialize::PromptDataSource
//| Created:  	3/8/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL CDSOAndRIID::Init()
{ 
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		// TO DO:  Add your own code here 
		return TRUE;
	} 
	return FALSE;
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc NULL ppDataSource => E_INVALIDARG
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_1()
{ 
	CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd,
	   DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, IID_IUnknown, NULL);

	return Dialog.IsResult(E_INVALIDARG);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Inexistent DSO (NULL *ppDataSource) => general interface checking for returned DSO
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_2()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIUnknown			= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IOpenRowset			*pIOpenRowset		= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	
	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IUnknown, (IUnknown**)&pIUnknown));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIUnknown);

	// the last argument is FALSE to indicate that the DSO is not initialized
	TESTC(DefaultObjectTesting(pIUnknown, DATASOURCE_INTERFACE, FALSE));

	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIUnknown, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC(VerifyInterface(pIUnknown, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), S_OK);

	// Obtain IDBCreateSesson, placing the new DSO interface 
	// in CThisTestModule's m_pIUnknown, so that all testcases can use 
	// it via their back pointer to this object.  No need to call AddRef 
	// here as we will own it, rather than the test module.	 
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));	 
	// Create a DB session object
	TESTC_(pIDBCreateSession->CreateSession(NULL, IID_IOpenRowset, (IUnknown **)&pIOpenRowset), S_OK);

	// the last argument is TRUE to indicate that the DSO is initialized
	TESTC(DefaultObjectTesting(pIUnknown, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	// release interfaces 
	SAFE_RELEASE(pIUnknown);
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_RELEASE(pIDBCreateSession);	
	SAFE_RELEASE(pIOpenRowset);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Pass a session pointer as *ppDataSource => E_INVALIDARG
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_3()
{
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IOpenRowset			*pIOpenRowset		= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	CDSL_Dialog			Dialog;

	// create a session object
	// the case where the DSO is already created and initialized
	TESTC_(GetModInfo()->CreateProvider(NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);
	// Obtain IDBCreateSesson, placing the new DSO interface 
	// in CThisTestModule's m_pIUnknown, so that all testcases can use 
	// it via their back pointer to this object.  No need to call AddRef 
	// here as we will own it, rather than the test module.	 
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));	 
	// Create a DB session object
	TESTC_(pIDBCreateSession->CreateSession(NULL, IID_IOpenRowset, (IUnknown **)&pIOpenRowset), S_OK);

	// execute the scenario
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, DBPROMPTOPTIONS_PROPERTYSHEET, 
		0, NULL, NULL, IID_IUnknown, (IUnknown**)&pIOpenRowset));

	// checked that the call has finished and that the return value was E_INVALIDARG
	// On error in CDSL_Dialog::MyThread we check that *ppDataSource has the same value
	TESTC(Dialog.IsResult(E_INVALIDARG));

	// now try the same asking for a session interface
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, DBPROMPTOPTIONS_PROPERTYSHEET, 
		0, NULL, NULL, IID_IDBCreateCommand, (IUnknown**)&pIOpenRowset));

	// checked that the call has finished and that the return value was E_INVALIDARG
	TESTC(Dialog.IsResult(E_INVALIDARG));

CLEANUP:
	// Clean up our variants we used in the init
	FreeProperties(&cPropSets, &rgPropSets);
	// release interfaces 
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_RELEASE(pIDBCreateSession);	
	SAFE_RELEASE(pIOpenRowset);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Pass an existent, uninitialized DSO (not aggregated with SC)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_4()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBInitialize		*pIDBInitialize2	= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	IUnknown			*pIUnk				= NULL;
	IUnknown			*pIUnk2				= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	DWORD				dwOptions			= GetModInfo()->UseServiceComponents();
	CDSL_Dialog			Dialog;

	// aggregate with SC
	GetModInfo()->PlugInServiceComponents(0);

	// the case where the DSO is already created
	TESTC_(GetModInfo()->CreateProvider(NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	pIDBInitialize2 = pIDBInitialize;

	// make sure the DSO is not going to be released and get its IUnknown interface
	pIDBInitialize2->AddRef();
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

	// check that the object retrieved is different than the one passed in
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk2));
	TESTC(pIUnk == pIUnk2);

	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	GetModInfo()->PlugInServiceComponents(dwOptions);
	SAFE_RELEASE(pIUnk);
	SAFE_RELEASE(pIUnk2);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize2);
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Pass an existent, uninitialized DSO (aggregated with SC)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_5()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBInitialize		*pIDBInitialize2	= NULL;
	IUnknown			*pIUnk				= NULL;
	IUnknown			*pIUnk2				= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	DWORD				dwOptions			= GetModInfo()->UseServiceComponents();
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	CDSL_Dialog			Dialog;

	// aggregate with SC
	GetModInfo()->PlugInServiceComponents(SERVICECOMP_INVOKE);

	// the case where the DSO is already created
	TESTC_(GetModInfo()->CreateProvider(NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	pIDBInitialize2 = pIDBInitialize;

	// make sure the DSO is not going to be released and get its IUnknown interface
	pIDBInitialize2->AddRef();
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

	// check that the object retrieved is different than the one passed in
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk2));
	TESTC(pIUnk == pIUnk2);

	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);
	
CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	// recover the old state
	GetModInfo()->PlugInServiceComponents(dwOptions);
	SAFE_RELEASE(pIUnk);
	SAFE_RELEASE(pIUnk2);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize2);
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc Pass an existent, initialized DSO (not aggregated with SC)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_6()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBInitialize		*pIDBInitialize2	= NULL;
	IUnknown			*pIUnk				= NULL;
	IUnknown			*pIUnk2				= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	DWORD				dwOptions			= GetModInfo()->UseServiceComponents();
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	CDSL_Dialog			Dialog;

	// aggregate with SC
	GetModInfo()->PlugInServiceComponents(0);

	// the case where the DSO is already created
	TESTC_(GetModInfo()->CreateProvider(NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	pIDBInitialize2 = pIDBInitialize;
	// make sure the DSO is not going to be released and get its IUnknown interface
	pIDBInitialize2->AddRef();
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectAnotherProvider());
	TESTC(Dialog.KillThread());
	// no properties were change; DSL will show a warning dialog that props are not
	// settable anymore and on pressing OK it will return with success
	TESTC(Dialog.IsResult(S_OK));

	// check that the object retrieved is different than the one passed in
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk2));
	TESTC(pIUnk != pIUnk2);
	
CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	GetModInfo()->PlugInServiceComponents(dwOptions);
	SAFE_RELEASE(pIUnk);
	SAFE_RELEASE(pIUnk2);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize2);
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc Pass an existent, initialized DSO (aggregated with SC)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_7()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBInitialize		*pIDBInitialize2	= NULL;
	IUnknown			*pIUnk				= NULL;
	IUnknown			*pIUnk2				= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	DWORD				dwOptions			= GetModInfo()->UseServiceComponents();
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	CDSL_Dialog			Dialog;

	// aggregate with SC
	GetModInfo()->PlugInServiceComponents(SERVICECOMP_INVOKE);

	// the case where the DSO is already created
	TESTC_(GetModInfo()->CreateProvider(NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	pIDBInitialize2 = pIDBInitialize;
	// make sure the DSO is not going to be released and get its IUnknown interface
	pIDBInitialize2->AddRef();
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectAnotherProvider());
	TESTC(Dialog.KillThread());
	// no properties were change; DSL will show a warning dialog that props are not
	// settable anymore and on pressing OK it will return with success
	TESTC(Dialog.IsResult(S_OK));

	// check that the object retrieved is different than the one passed in
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk2));
	TESTC(pIUnk != pIUnk2);
	
CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	GetModInfo()->PlugInServiceComponents(dwOptions);
	SAFE_RELEASE(pIUnk);
	SAFE_RELEASE(pIUnk2);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize2);
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Existent, uninitialized DSO, select another provider
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_8()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBInitialize		*pIDBInitialize2	= NULL;
	IUnknown			*pIUnk				= NULL;
	IUnknown			*pIUnk2				= NULL;
	DWORD				dwOptions			= GetModInfo()->UseServiceComponents();
	CDSL_Dialog			Dialog;

	// aggregate with SC
	GetModInfo()->PlugInServiceComponents(0);

	// the case where the DSO is already created
	TESTC_(GetModInfo()->CreateProvider(NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	pIDBInitialize2 = pIDBInitialize;

	// make sure the DSO is not going to be released and get its IUnknown interface
	pIDBInitialize2->AddRef();
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectAnotherProvider());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

	// check that the object retrieved is different than the one passed in
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk2));
	TESTC(pIUnk != pIUnk2);

CLEANUP:
	GetModInfo()->PlugInServiceComponents(dwOptions);
	SAFE_RELEASE(pIUnk);
	SAFE_RELEASE(pIUnk2);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize2);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Existent, uninit DSO, test with another provider, reselect original provider
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_9()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBInitialize		*pIDBInitialize2	= NULL;
	IUnknown			*pIUnk				= NULL;
	IUnknown			*pIUnk2				= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	DWORD				dwOptions			= GetModInfo()->UseServiceComponents();
	CDSL_Dialog			Dialog;

	// aggregate with SC
	GetModInfo()->PlugInServiceComponents(0);

	// the case where the DSO is already created
	TESTC_(GetModInfo()->CreateProvider(NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	pIDBInitialize2 = pIDBInitialize;

	// make sure the DSO is not going to be released and get its IUnknown interface
	pIDBInitialize2->AddRef();
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectAnotherProvider());
	Sleep(2000);
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	Sleep(2000);
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

	// check that the object retrieved is different than the one passed in
	TESTC(VerifyInterface(pIDBInitialize, IID_IUnknown, DATASOURCE_INTERFACE, &pIUnk2));
	TESTC(pIUnk == pIUnk2);

	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	GetModInfo()->PlugInServiceComponents(dwOptions);
	SAFE_RELEASE(pIUnk);
	SAFE_RELEASE(pIUnk2);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize2);
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc Existent, uninit DSO, select and test another provider, CANCEL
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_10()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBInitialize		*pIDBInitialize2	= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	DWORD				dwOptions			= GetModInfo()->UseServiceComponents();
	CDSL_Dialog			Dialog;

	// aggregate with SC
	GetModInfo()->PlugInServiceComponents(0);

	// the case where the DSO is already created
	TESTC_(GetModInfo()->CreateProvider(NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	pIDBInitialize2 = pIDBInitialize;
	// make sure the DSO is not going to be released and get its IUnknown interface
	pIDBInitialize2->AddRef();

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectAnotherProvider());
	Sleep(1000);
//	TESTC(Dialog.TestConnection(FALSE));
	
	TESTC(Dialog.TestConnection());

	TESTC(Dialog.KillThread(PSBTN_CANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));

	// check that the object retrieved is different than the one passed in
	TESTC(pIDBInitialize == pIDBInitialize2);

	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	GetModInfo()->PlugInServiceComponents(dwOptions);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize2);
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(11)
//*-----------------------------------------------------------------------
// @mfunc Existent, uninit DSO, ask a different interface
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_11()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBInitialize		*pIDBInitialize2	= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	DWORD				dwOptions			= GetModInfo()->UseServiceComponents();
	CDSL_Dialog			Dialog;

	// aggregate with SC
	GetModInfo()->PlugInServiceComponents(0);

	// the case where the DSO is already created
	TESTC_(GetModInfo()->CreateProvider(NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	pIDBInitialize2 = pIDBInitialize;
	// make sure the DSO is not going to be released and get its IUnknown interface
	pIDBInitialize2->AddRef();

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		NULL, IID_IDBProperties, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

	// check that the object retrieved is different than the one passed in
	TESTC(pIDBInitialize != pIDBInitialize2);
	pIDBProperties = (IDBProperties*)pIDBInitialize;
	pIDBProperties->AddRef();

	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize (with the second interface since this is the IDBInitialize one)
	TESTC_(pIDBInitialize2->Initialize(), S_OK);

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	GetModInfo()->PlugInServiceComponents(dwOptions);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize2);
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(12)
//*-----------------------------------------------------------------------
// @mfunc Existent, uninit DSO, ask a different interface, CANCEL
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_12()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBInitialize		*pIDBInitialize2	= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	DWORD				dwOptions			= GetModInfo()->UseServiceComponents();
	CDSL_Dialog			Dialog;

	// aggregate with SC
	GetModInfo()->PlugInServiceComponents(0);

	// the case where the DSO is already created
	TESTC_(GetModInfo()->CreateProvider(NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	pIDBInitialize2 = pIDBInitialize;
	// make sure the DSO is not going to be released and get its IUnknown interface
	pIDBInitialize2->AddRef();

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		NULL, IID_IDBProperties, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.KillThread(PSBTN_CANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));

	// check that the object retrieved is different than the one passed in
	TESTC(pIDBInitialize == pIDBInitialize2);

	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	GetModInfo()->PlugInServiceComponents(dwOptions);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize2);
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(13)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_NULL => E_NOINTERFACE
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_13()
{ 
	TBEGIN
	CDSL_Dialog		Dialog;
	IUnknown		*pIUnknown = NULL;
	
	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_NULL, &pIUnknown));

//	TESTC(!Dialog.IsInExecution());
	TESTC(Dialog.KillThread());

	TESTC(Dialog.IsResult(E_NOINTERFACE));
	TESTC(NULL == pIUnknown);

CLEANUP:
	SAFE_RELEASE(pIUnknown);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(14)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IUnknown => S_OK
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_14()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IUnknown			*pIUnknown		= NULL;
	IDBInitialize		*pIDBInitialize	= NULL;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IUnknown, &pIUnknown));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread	());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIUnknown);
	TESTC_(pIUnknown->QueryInterface(IID_IDBInitialize, (void**)&pIDBInitialize), S_OK);

	TESTC(DefaultObjectTesting(pIUnknown, DATASOURCE_INTERFACE, FALSE));

CLEANUP:
	SAFE_RELEASE(pIUnknown);	
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(15)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IDBCreateSession (mandatory)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_15()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IUnknown			*pIUnknown = NULL;
	
	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBCreateSession, &pIUnknown));

	// DSO is uninitialized, so the call should fail
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(E_UNEXPECTED));
	TESTC(NULL == pIUnknown);

CLEANUP:
	SAFE_RELEASE(pIUnknown);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(16)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IDBInitialize (mandatory) => S_OK
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_16()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	IDBProperties		*pIDBProperties	= NULL;
	ULONG				cPropSets		= 0;
	DBPROPSET			*rgPropSets		= NULL;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread	());
	TESTC(Dialog.IsResult(S_OK));


	TESTC(DefaultObjectTesting(pIDBInitialize, DATASOURCE_INTERFACE, FALSE));

	// check that we can initialize the DSO
	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	TESTC(DefaultObjectTesting(pIDBInitialize, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	SAFE_RELEASE(pIDBProperties);	
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(17)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IDBProperties (mandatory)=> S_OK
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_17()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	IDBProperties		*pIDBProperties	= NULL;
	ULONG				cPropSets		= 0;
	DBPROPSET			*rgPropSets		= NULL;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBProperties, (IUnknown**)&pIDBProperties));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread	());
	TESTC(Dialog.IsResult(S_OK));


	TESTC(DefaultObjectTesting(pIDBProperties, DATASOURCE_INTERFACE, FALSE));

	// check that we can initialize the DSO
	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBProperties, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	TESTC(DefaultObjectTesting(pIDBProperties, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	SAFE_RELEASE(pIDBProperties);	
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(18)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IPersist (mandatory)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_18()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	IDBProperties		*pIDBProperties	= NULL;
	IPersist			*pIPersist		= NULL;
	ULONG				cPropSets		= 0;
	DBPROPSET			*rgPropSets		= NULL;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IPersist, (IUnknown**)&pIPersist));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread	());
	TESTC(Dialog.IsResult(S_OK));

	TESTC(DefaultObjectTesting(pIPersist, DATASOURCE_INTERFACE, FALSE));

	TESTC(VerifyInterface(pIPersist, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));

	// check that we can initialize the DSO
	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	TESTC(DefaultObjectTesting(pIPersist, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	SAFE_RELEASE(pIDBProperties);	
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIPersist);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(19)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IConnectionPointContainer (optional)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_19()
{ 
	TBEGIN
	CDSL_Dialog					Dialog;
	IDBInitialize				*pIDBInitialize					= NULL;
	IDBProperties				*pIDBProperties					= NULL;
	IConnectionPointContainer	*pIConnectionPointContainer		= NULL;
	ULONG						cPropSets						= 0;
	DBPROPSET					*rgPropSets						= NULL;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IConnectionPointContainer, (IUnknown**)&pIConnectionPointContainer));

	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread	());
	TESTC(!Dialog.IsInExecution());
	TEST2C_(Dialog.GetHRESULT(), S_OK, E_NOINTERFACE);
	TESTC_PROVIDER(S_OK == Dialog.GetHRESULT());

	TESTC(DefaultObjectTesting(pIConnectionPointContainer, DATASOURCE_INTERFACE, FALSE));

	TESTC(VerifyInterface(pIConnectionPointContainer, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));

	// check that we can initialize the DSO
	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	TESTC(DefaultObjectTesting(pIConnectionPointContainer, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	SAFE_RELEASE(pIDBProperties);	
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIConnectionPointContainer);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(20)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IDBAsynchStatus (optional)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_20()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	IDBAsynchStatus		*pIDBAsynchStatus	= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBAsynchStatus, (IUnknown**)&pIDBAsynchStatus));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread	());
	TESTC(!Dialog.IsInExecution());
	TEST2C_(Dialog.GetHRESULT(), S_OK, E_NOINTERFACE);
	TESTC_PROVIDER(S_OK == Dialog.GetHRESULT());

	TESTC(DefaultObjectTesting(pIDBAsynchStatus, DATASOURCE_INTERFACE, FALSE));

	TESTC(VerifyInterface(pIDBAsynchStatus, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));

	// check that we can initialize the DSO
	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	TESTC(DefaultObjectTesting(pIDBAsynchStatus, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	SAFE_RELEASE(pIDBProperties);	
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBAsynchStatus);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(21)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IDBDataSourceAdmin (optional)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_21()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	IDBDataSourceAdmin	*pIDBDataSourceAdmin= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBDataSourceAdmin, (IUnknown**)&pIDBDataSourceAdmin));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread	());
	TESTC(!Dialog.IsInExecution());
	TEST2C_(Dialog.GetHRESULT(), S_OK, E_NOINTERFACE);
	TESTC_PROVIDER(S_OK == Dialog.GetHRESULT());

	TESTC(DefaultObjectTesting(pIDBDataSourceAdmin, DATASOURCE_INTERFACE, FALSE));

	TESTC(VerifyInterface(pIDBDataSourceAdmin, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));

	// check that we can initialize the DSO
	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	TESTC(DefaultObjectTesting(pIDBDataSourceAdmin, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	SAFE_RELEASE(pIDBProperties);	
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBDataSourceAdmin);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(22)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IDBInfo (optional)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_22()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IUnknown			*pIUnknown = NULL;
	
	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInfo, &pIUnknown));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread());
	// DSO is uninitialized, so the call should fail
	TESTC(Dialog.IsResult(E_NOINTERFACE));
	TESTC(NULL == pIUnknown);

CLEANUP:
	SAFE_RELEASE(pIUnknown);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(23)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IPersistFile (optional)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_23()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	IPersistFile		*pIPersistFile		= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IPersistFile, (IUnknown**)&pIPersistFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread	());
	TESTC(!Dialog.IsInExecution());
	TEST2C_(Dialog.GetHRESULT(), S_OK, E_NOINTERFACE);
	TESTC_PROVIDER(S_OK == Dialog.GetHRESULT());

	TESTC(DefaultObjectTesting(pIPersistFile, DATASOURCE_INTERFACE, FALSE));

	TESTC(VerifyInterface(pIPersistFile, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));

	// check that we can initialize the DSO
	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	TESTC(DefaultObjectTesting(pIPersistFile, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	SAFE_RELEASE(pIDBProperties);	
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIPersistFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(24)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_ISupportErrorInfo (optional)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_24()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	ISupportErrorInfo	*pISupportErrorInfo	= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_ISupportErrorInfo, (IUnknown**)&pISupportErrorInfo));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread	());
	TESTC(!Dialog.IsInExecution());
	TEST2C_(Dialog.GetHRESULT(), S_OK, E_NOINTERFACE);
	TESTC_PROVIDER(S_OK == Dialog.GetHRESULT());

	TESTC(DefaultObjectTesting(pISupportErrorInfo, DATASOURCE_INTERFACE, FALSE));

	TESTC(VerifyInterface(pISupportErrorInfo, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));

	// check that we can initialize the DSO
	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	TESTC(DefaultObjectTesting(pISupportErrorInfo, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	SAFE_RELEASE(pIDBProperties);	
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pISupportErrorInfo);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(25)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IServiceProvider (extensible UI)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_25()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	IServiceProvider	*pIServiceProvider	= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IServiceProvider, (IUnknown**)&pIServiceProvider));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread	());
	TESTC(!Dialog.IsInExecution());
	TEST2C_(Dialog.GetHRESULT(), S_OK, E_NOINTERFACE);
	TESTC_PROVIDER(S_OK == Dialog.GetHRESULT());

	TESTC(DefaultObjectTesting(pIServiceProvider, DATASOURCE_INTERFACE, FALSE));

	TESTC(VerifyInterface(pIServiceProvider, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));

	// check that we can initialize the DSO
	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	TESTC(DefaultObjectTesting(pIServiceProvider, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	SAFE_RELEASE(pIDBProperties);	
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIServiceProvider);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(26)
//*-----------------------------------------------------------------------
// @mfunc riid is IID_IOpenRowset => E_NOINTERFACE
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_26()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IUnknown			*pIUnknown = NULL;
	
	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IOpenRowset, &pIUnknown));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread());
	// DSO is uninitialized, so the call should fail
	TESTC(Dialog.IsResult(E_NOINTERFACE));
	TESTC(NULL == pIUnknown);

CLEANUP:
	SAFE_RELEASE(pIUnknown);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(27)
//*-----------------------------------------------------------------------
// @mfunc Check that all the OLE DB providers appear in the provider page
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_27()
{ 
// pops up a dialog and check that all providers in the sources rowset
// can be selected
	TBEGIN
	IDBInitialize		*pIDBInitialize = NULL;
	ULONG				i;
	CDSL_Dialog			Dialog;

	// set the interface to be returned
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count(); i++)
	{
		// if datasource is not a provider skip the iteration
		if (	DBSOURCETYPE_DATASOURCE_TDP != (*g_pSourcesSet)[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != (*g_pSourcesSet)[i].m_wType
			||	!(CUSTOM_CONN & (*g_pSourcesSet)[i].m_CustomUI)
			)
			continue;

		// if the enumerator returned it as an OLEDB provider, check it can be selected
		odtLog << (*g_pSourcesSet)[i].m_pwszDescription << "\n";
		TESTC(Dialog.SelectProvider((LPWSTR)(LPCWSTR)(*g_pSourcesSet)[i].m_pwszDescription));
		TESTC(Dialog.GotoAllPage());
		Sleep(100);
		TESTC(Dialog.GotoProviderPage());
		// check that the provider is still selected
		TESTC(Dialog.GetProvider());
		TESTC(0 == wcscmp(Dialog.GetProviderName(), (*g_pSourcesSet)[i].m_pwszDescription));
	}
	TESTC(Dialog.CheckFilters());
	
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(28)
//*-----------------------------------------------------------------------
// @mfunc Existent DSO, error, check *ppDataSource is preserved
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CDSOAndRIID::Variation_28()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBInitialize		*pIDBInitialize2	= NULL;
	IDBProperties		*pIDBProperties		= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	CDSL_Dialog			Dialog;

	// the case where the DSO is already created
	TESTC_(GetModInfo()->CreateProvider(NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	pIDBInitialize2 = pIDBInitialize;

	// make sure the DSO is not going to be released and get its IUnknown interface
	pIDBInitialize2->AddRef();

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// cancel the dialog and make sure the *ppDataSource pointer is the same
	TESTC(Dialog.KillThread(PSBTN_CANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));

	// check that the object retrieved is different than the one passed in
	TESTC(pIDBInitialize == pIDBInitialize2);

	// check that the provider can be initialized
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize2);
	SAFE_RELEASE(pIDBProperties);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END



// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL CDSOAndRIID::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(CAggregation)
//*-----------------------------------------------------------------------
//| Test Case:		CAggregation - aggregation cases for IDBPromptInitialize::PromptDataSource
//| Created:  	3/8/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL CAggregation::Init()
{ 
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		// TO DO:  Add your own code here 
		return TRUE;
	} 
	return FALSE;
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Aggregation, ask for IID_IUnknown, inexistent DSO
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CAggregation::Variation_1()
{ 
	TBEGIN
	CAggregate		Aggregate(NULL);
	CDSL_Dialog		Dialog;	

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, 
		(IUnknown*)&Aggregate, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IUnknown, (IUnknown**)&Aggregate.m_pIUnkInner));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != Aggregate.m_pIUnkInner);

	// Verrify Aggregation for this rowset...
	TESTC(Aggregate.VerifyAggregationQI(Dialog.GetHRESULT(), IID_IDBProperties));
	
CLEANUP:
	Aggregate.ReleaseInner();
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Aggregation, ask for IID_IUnknown, existent DSO, not aggregated with pIUnkOuter => DB_E_NOAGGREGATION
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CAggregation::Variation_2()
{
	TBEGIN
	CAggregate		Aggregate(NULL);
	IDBInitialize	*pIDBInitialize	= NULL;
	const ULONG		cRepNo			= 5;
	CDSL_Dialog		Dialog;

	for (ULONG j=0; j<cRepNo; j++)
	{
		// the case where the DSO is already created
		pIDBInitialize = NULL;
		TESTC_(GetModInfo()->CreateProvider(NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

		// ask for aggregation
		Aggregate.m_pIUnkInner = pIDBInitialize;
		Aggregate.m_pIUnkInner->AddRef();

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize,
			(IUnknown*)&Aggregate, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IUnknown, (IUnknown**)&Aggregate.m_pIUnkInner));

		TESTC(Dialog.IsResult(DB_E_NOAGGREGATION));
		TESTC(pIDBInitialize == Aggregate.m_pIUnkInner);
		TESTC(pIDBInitialize == Aggregate.m_pIUnkInner);
		SAFE_RELEASE(pIDBInitialize);
		SAFE_RELEASE(Aggregate.m_pIUnkInner);
	}
	
CLEANUP:
	SAFE_RELEASE(Aggregate.m_pIUnkInner);
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Aggregation, ask for IID_IUnknown, existent DSO, already aggregated with pIUnkOuter => DB_E_NOAGGREGATION
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CAggregation::Variation_3()
{ 
	TBEGIN
	CAggregate		Aggregate(NULL);
	IUnknown		*pIUnknown	= NULL;
	const ULONG		cRepNo		= 5;
	CDSL_Dialog		Dialog;
	
	for (ULONG j=0; j<cRepNo; j++)
	{
		// the case where the DSO is already created
		pIUnknown = NULL;
		TESTC_(GetModInfo()->CreateProvider((IUnknown*)&Aggregate,
			IID_IUnknown, &pIUnknown), S_OK);

		// ask for aggregation
		Aggregate.m_pIUnkInner = pIUnknown;
		Aggregate.m_pIUnkInner->AddRef();

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize,
			(IUnknown*)&Aggregate, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IUnknown, (IUnknown**)&Aggregate.m_pIUnkInner));

		TESTC(Dialog.IsResult(DB_E_NOAGGREGATION));
		TESTC(pIUnknown == Aggregate.m_pIUnkInner);
		SAFE_RELEASE(pIUnknown);
		SAFE_RELEASE(Aggregate.m_pIUnkInner);
	}
	
CLEANUP:
	SAFE_RELEASE(Aggregate.m_pIUnkInner);
	SAFE_RELEASE(pIUnknown);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Aggregation, riid is not IID_IUnknown => DB_E_NOAGGREGATION
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CAggregation::Variation_4()
{ 
	TBEGIN
	CAggregate		Aggregate(NULL);
	CDSL_Dialog		Dialog;	

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, 
		(IUnknown*)&Aggregate, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&Aggregate.m_pIUnkInner));

	TESTC(Dialog.IsResult(DB_E_NOAGGREGATION));
	TESTC(NULL == Aggregate.m_pIUnkInner);

CLEANUP:
	Aggregate.ReleaseInner();
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Aggregation, general interface checking on the returned DSO
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CAggregation::Variation_5()
{ 
	TBEGIN
	IDBProperties		*pIDBProperties		= NULL;
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IOpenRowset			*pIOpenRowset		= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	CAggregate			Aggregate;
	CDSL_Dialog			Dialog;
	
	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, (IUnknown*)&Aggregate, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IUnknown, (IUnknown**)&Aggregate.m_pIUnkInner));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != Aggregate.m_pIUnkInner);

	// DSO is uninitialize, last parameter of the call is therefore FALSE
	TESTC(DefaultObjectTesting(Aggregate.m_pIUnkInner, DATASOURCE_INTERFACE, FALSE));

	TESTC(Aggregate.VerifyAggregationQI(Dialog.GetHRESULT(), IID_IDBProperties));

	// Get IDBProperties Pointer
	TESTC(VerifyInterface(Aggregate.m_pIUnkInner, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC(VerifyInterface(Aggregate.m_pIUnkInner, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));
	TESTC_(pIDBInitialize->Initialize(), S_OK);
	// Obtain IDBCreateSesson, placing the new DSO interface 
	// in CThisTestModule's m_pIUnknown, so that all testcases can use 
	// it via their back pointer to this object.  No need to call AddRef 
	// here as we will own it, rather than the test module.	 
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));	 
	// Create a DB session object
	TESTC_(pIDBCreateSession->CreateSession(NULL, IID_IOpenRowset, (IUnknown **)&pIOpenRowset), S_OK);

	// the last argument is TRUE to indicate that the DSO is initialized
	TESTC(DefaultObjectTesting(Aggregate.m_pIUnkInner, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	// release interfaces 
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_RELEASE(pIDBCreateSession);	
	SAFE_RELEASE(pIOpenRowset);
	Aggregate.ReleaseInner();
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc Aggregation, create session and call IGetDataSource::GetDataSource
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CAggregation::Variation_6()
{ 
	TBEGIN
	IDBProperties		*pIDBProperties		= NULL;
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IOpenRowset			*pIOpenRowset		= NULL;
	IGetDataSource		*pIGetDataSource	= NULL;
	IUnknown			*pIUnknown			= NULL;
	IUnknown			*pIUnknown2			= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	CAggregate			Aggregate;
	CDSL_Dialog			Dialog;

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, (IUnknown*)&Aggregate, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IUnknown, (IUnknown**)&Aggregate.m_pIUnkInner));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != Aggregate.m_pIUnkInner);

	TESTC(Aggregate.VerifyAggregationQI(Dialog.GetHRESULT(), IID_IDBProperties));

	// Get IDBProperties Pointer
	TESTC(VerifyInterface(Aggregate.m_pIUnkInner, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC(VerifyInterface(Aggregate.m_pIUnkInner, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));
	TESTC_(pIDBInitialize->Initialize(), S_OK);
	// Obtain IDBCreateSesson, placing the new DSO interface 
	// in CThisTestModule's m_pIUnknown, so that all testcases can use 
	// it via their back pointer to this object.  No need to call AddRef 
	// here as we will own it, rather than the test module.	 
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));	 
	// Create a DB session object
	TESTC_(pIDBCreateSession->CreateSession(NULL, IID_IOpenRowset, (IUnknown **)&pIOpenRowset), S_OK);

	// check that the outer object is the one returned by IGetDataSource::GetDataSource
	TESTC(VerifyInterface(pIOpenRowset, IID_IGetDataSource, DATASOURCE_INTERFACE, (IUnknown**)&pIGetDataSource));	 
	TESTC_(m_hr = pIGetDataSource->GetDataSource(IID_IUnknown, (IUnknown**)&pIUnknown), S_OK);
	TESTC_(m_hr = Aggregate.QueryInterface(IID_IUnknown, (LPVOID*)&pIUnknown2), S_OK);
	TESTC(pIUnknown2 == pIUnknown);

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	// release interfaces 
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_RELEASE(pIDBCreateSession);	
	SAFE_RELEASE(pIOpenRowset);
	SAFE_RELEASE(pIGetDataSource);
	SAFE_RELEASE(pIUnknown);
	SAFE_RELEASE(pIUnknown2);
	Aggregate.ReleaseInner();
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END





// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc Agg, select prov. Test conn. Move to another prov. Test conn. Check reference counter on outer obj
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CAggregation::Variation_7()
{ 
	TBEGIN
	IDBProperties		*pIDBProperties		= NULL;
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IOpenRowset			*pIOpenRowset		= NULL;
	IGetDataSource		*pIGetDataSource	= NULL;
	IUnknown			*pIUnknown			= NULL;
	IUnknown			*pIUnknown2			= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	CAggregate			Aggregate;
	CDSL_Dialog			Dialog;

	const CLSID *ExcludedProviders[] = { &CLSID_MSDAIPP, &CLSID_MSSearch, NULL };

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, (IUnknown*)&Aggregate, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IUnknown, (IUnknown**)&Aggregate.m_pIUnkInner));

	TESTC(Dialog.IsInExecution());

	TESTC(Dialog.SelectAnotherProvider(&ExcludedProviders[0]));
	TESTC(Dialog.TestConnection());

	TESTC(Dialog.SelectAnotherProvider(&ExcludedProviders[0]));
	TESTC(Dialog.TestConnection());
	
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.TestConnection());
	
	TESTC(Dialog.SelectAnotherProvider(&ExcludedProviders[0]));
	TESTC(Dialog.TestConnection());
	
	TESTC(Dialog.SelectAnotherProvider(&ExcludedProviders[0]));
	TESTC(Dialog.TestConnection());
	
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != Aggregate.m_pIUnkInner);

	TESTC(Aggregate.VerifyAggregationQI(Dialog.GetHRESULT(), IID_IDBProperties));

	// Get IDBProperties Pointer
	TESTC(VerifyInterface(Aggregate.m_pIUnkInner, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC(VerifyInterface(Aggregate.m_pIUnkInner, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));
	TESTC_(pIDBInitialize->Initialize(), S_OK);
	// Obtain IDBCreateSesson, placing the new DSO interface 
	// in CThisTestModule's m_pIUnknown, so that all testcases can use 
	// it via their back pointer to this object.  No need to call AddRef 
	// here as we will own it, rather than the test module.	 
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));	 
	// Create a DB session object
	TESTC_(pIDBCreateSession->CreateSession(NULL, IID_IOpenRowset, (IUnknown **)&pIOpenRowset), S_OK);

	// check that the outer object is the one returned by IGetDataSource::GetDataSource
	TESTC(VerifyInterface(pIOpenRowset, IID_IGetDataSource, DATASOURCE_INTERFACE, (IUnknown**)&pIGetDataSource));	 
	TESTC_(m_hr = pIGetDataSource->GetDataSource(IID_IUnknown, (IUnknown**)&pIUnknown), S_OK);
	TESTC_(m_hr = Aggregate.QueryInterface(IID_IUnknown, (LPVOID*)&pIUnknown2), S_OK);
	TESTC(pIUnknown2 == pIUnknown);

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	// release interfaces 
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_RELEASE(pIDBCreateSession);	
	SAFE_RELEASE(pIOpenRowset);
	SAFE_RELEASE(pIGetDataSource);
	SAFE_RELEASE(pIUnknown);
	SAFE_RELEASE(pIUnknown2);
	Aggregate.ReleaseInner();
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Aggegated, existent DSO. Ask for a different interface.
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CAggregation::Variation_8()
{ 
	TBEGIN
	IDBProperties		*pIDBProperties		= NULL;
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IOpenRowset			*pIOpenRowset		= NULL;
	IGetDataSource		*pIGetDataSource	= NULL;
	IUnknown			*pIUnknown			= NULL;
	IUnknown			*pIUnknown2			= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	CAggregate			Aggregate;
	CDSL_Dialog			Dialog;

	// try this on existing DSO as well
	TEST3C_(m_hr = GetModInfo()->CreateProvider((IUnknown*)&Aggregate, IID_IUnknown, 
		(IUnknown**)&Aggregate.m_pIUnkInner), S_OK, DB_E_NOAGGREGATION, CLASS_E_NOAGGREGATION);
	TESTC_(m_hr = Aggregate.QueryInterface(IID_IUnknown, (LPVOID*)&pIUnknown2), S_OK);
	TESTC_(m_hr = Aggregate.QueryInterface(IID_IDBInitialize, (LPVOID*)&pIDBInitialize), S_OK);
	TESTC_PROVIDER(S_OK == m_hr);
	TESTC(Aggregate.VerifyAggregationQI(S_OK, IID_IDBInitialize));

	// pass the aggregated DSO and ask for a different interface
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

	// Get IDBProperties Pointer and IDBInitialize
	TESTC(VerifyInterface((IUnknown*)&Aggregate, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);
	// Obtain IDBCreateSesson, placing the new DSO interface 
	// in CThisTestModule's m_pIUnknown, so that all testcases can use 
	// it via their back pointer to this object.  No need to call AddRef 
	// here as we will own it, rather than the test module.	 
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));	 
	// Create a DB session object
	TESTC_(pIDBCreateSession->CreateSession(NULL, IID_IOpenRowset, (IUnknown **)&pIOpenRowset), S_OK);

	// check that the outer object is the one returned by IGetDataSource::GetDataSource
	TESTC(VerifyInterface(pIOpenRowset, IID_IGetDataSource, DATASOURCE_INTERFACE, (IUnknown**)&pIGetDataSource));	 
	TESTC_(m_hr = pIGetDataSource->GetDataSource(IID_IUnknown, (IUnknown**)&pIUnknown), S_OK);
	TESTC(pIUnknown2 == pIUnknown);

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	// release interfaces 
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_RELEASE(pIDBCreateSession);	
	SAFE_RELEASE(pIOpenRowset);
	SAFE_RELEASE(pIGetDataSource);
	SAFE_RELEASE(pIUnknown);
	SAFE_RELEASE(pIUnknown2);
	Aggregate.ReleaseInner();
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Aggegated, existent DSO. Select a different provider.
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CAggregation::Variation_9()
{ 
	TBEGIN
	CAggregate			Aggregate;
	IDBInitialize		*pIDBInitialize	= NULL;
	CDSL_Dialog			Dialog;

	// try this on existing DSO as well
	TEST3C_(m_hr = GetModInfo()->CreateProvider((IUnknown*)&Aggregate, IID_IUnknown, 
		(IUnknown**)&Aggregate.m_pIUnkInner), S_OK, DB_E_NOAGGREGATION, CLASS_E_NOAGGREGATION);
	TESTC_PROVIDER(S_OK == m_hr);
	TESTC(Aggregate.VerifyAggregationQI(S_OK, IID_IDBInitialize));
	TESTC_(m_hr = Aggregate.QueryInterface(IID_IDBInitialize, (LPVOID*)&pIDBInitialize), S_OK);

	// pass the aggregated DSO and ask for a different interface
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectAnotherProvider());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

CLEANUP:
	// release interfaces 
	Aggregate.ReleaseInner();
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc Aggregation, bad prompt options => make sure the ref count is the same.
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CAggregation::Variation_10()
{ 
	TBEGIN
	IDBProperties		*pIDBProperties		= NULL;
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBCreateSession	*pIDBCreateSession	= NULL;
	IOpenRowset			*pIOpenRowset		= NULL;
	IGetDataSource		*pIGetDataSource	= NULL;
	IUnknown			*pIUnknown			= NULL;
	IUnknown			*pIUnknown2			= NULL;
	ULONG				cPropSets			= 0;
	DBPROPSET			*rgPropSets			= NULL;
	CAggregate			Aggregate;
	CDSL_Dialog			Dialog;

	// try this on existing DSO as well
	TEST3C_(m_hr = GetModInfo()->CreateProvider((IUnknown*)&Aggregate, IID_IUnknown, 
		(IUnknown**)&Aggregate.m_pIUnkInner), S_OK, DB_E_NOAGGREGATION, CLASS_E_NOAGGREGATION);
	TESTC_PROVIDER(S_OK == m_hr);
	TESTC(Aggregate.VerifyAggregationQI(S_OK, IID_IDBInitialize));
	TESTC_(m_hr = Aggregate.QueryInterface(IID_IDBInitialize, (LPVOID*)&pIDBInitialize), S_OK);

	// pass the aggregated DSO and ask for a different interface
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		0, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsResult(E_INVALIDARG));
	TESTC(NULL != pIDBInitialize);

	// Get IDBProperties Pointer and IDBInitialize
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);
	// Obtain IDBCreateSesson, placing the new DSO interface 
	// in CThisTestModule's m_pIUnknown, so that all testcases can use 
	// it via their back pointer to this object.  No need to call AddRef 
	// here as we will own it, rather than the test module.	 
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBCreateSession, DATASOURCE_INTERFACE, (IUnknown**)&pIDBCreateSession));	 
	// Create a DB session object
	TESTC_(pIDBCreateSession->CreateSession(NULL, IID_IOpenRowset, (IUnknown **)&pIOpenRowset), S_OK);

	// check that the outer object is the one returned by IGetDataSource::GetDataSource
	TESTC(VerifyInterface(pIOpenRowset, IID_IGetDataSource, DATASOURCE_INTERFACE, (IUnknown**)&pIGetDataSource));	 
	TESTC_(m_hr = pIGetDataSource->GetDataSource(IID_IUnknown, (IUnknown**)&pIUnknown), S_OK);
	TESTC_(m_hr = Aggregate.QueryInterface(IID_IUnknown, (LPVOID*)&pIUnknown2), S_OK);
	TESTC(pIUnknown2 == pIUnknown);

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	// release interfaces 
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_RELEASE(pIDBCreateSession);	
	SAFE_RELEASE(pIOpenRowset);
	SAFE_RELEASE(pIGetDataSource);
	SAFE_RELEASE(pIUnknown);
	SAFE_RELEASE(pIUnknown2);
	Aggregate.ReleaseInner();
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL CAggregation::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(CSourceTypeFilter)
//*-----------------------------------------------------------------------
//| Test Case:		CSourceTypeFilter - Source type filters in IDBPromptInitialize::PromptDataSource
//| Created:  	3/8/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL CSourceTypeFilter::Init()
{ 
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		// TO DO:  Add your own code here 
		return TRUE;
	} 
	return FALSE;
} 





// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc 0 == cSourceTypeFilter and NULL == rgSourceTypeFilter => S_OK
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSourceTypeFilter::Variation_1()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize				= NULL;
	const ULONG			cMaxIterations				= 5;
	ULONG				i;
	
	for (i=0; i<cMaxIterations; i++)
	{
		CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);
		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);
		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc 0 != cSourceTypeFilter and NULL == rgSourceTypeFilter	=> E_INVALIDARG
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSourceTypeFilter::Variation_2()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	const ULONG			cMaxIterations		= 5;
	ULONG				cSourceType			= 1;
	DBSOURCETYPE		*rgSourceType		= NULL;
	ULONG				i;
	DWORD				dwServiceComp		=GetModInfo()->UseServiceComponents();
	
	for (i=0; i<cMaxIterations; i++)
	{
		CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSourceType, rgSourceType, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);
		TESTC(Dialog.IsResult(E_INVALIDARG));
		TESTC(NULL == pIDBInitialize);
	}

	// try this on existing DSO as well
	GetModInfo()->PlugInServiceComponents(SERVICECOMP_INVOKE);
	TESTC_(GetModInfo()->CreateProvider(NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	{
		CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSourceType, rgSourceType, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);
		TESTC(Dialog.IsResult(E_INVALIDARG));
		TESTC(NULL != pIDBInitialize);
	}

CLEANUP:
	GetModInfo()->PlugInServiceComponents(dwServiceComp);
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc 0 == cSourceTypeFilter and NULL != rgSourceTypeFilter	=> S_OK
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSourceTypeFilter::Variation_3()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	const ULONG			cMaxIterations		= 5;
	ULONG				cSourceType			= 0;
	DBSOURCETYPE		rgSourceType[2];
	ULONG				i;
	
	for (i=0; i<cMaxIterations; i++)
	{
		CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSourceType, rgSourceType, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);
		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);
		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN;
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Valid source filter made of: DBSOURCETYPE_DATASOURCE, DBSOURCETYPE_DATASOURCE_TDP and DBSOURCETYPE_DATASOURCE_MDP
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSourceTypeFilter::Variation_4()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize				= NULL;
	const ULONG			cGoodSrcType				= 3;
	DBSOURCETYPE		rgGoodSrcType[cGoodSrcType]	= {	DBSOURCETYPE_DATASOURCE, 
														DBSOURCETYPE_DATASOURCE_TDP, 
														DBSOURCETYPE_DATASOURCE_MDP};
	DBSOURCETYPE		rgSrcType[cGoodSrcType];
	ULONG				cSrcType;
	ULONG				uCombination;

	for (uCombination=0; uCombination < pow(2, cGoodSrcType); uCombination++)
	{
		// get the filter 
		odtLog << "\tconfiguration: "; 
		cSrcType	= 0;
		if (uCombination & 0x1)
		{
			rgSrcType[cSrcType++] = rgGoodSrcType[0];
			odtLog << "DBSOURCETYPE_DATASOURCE\t";
		}
		if (uCombination & 0x2)
		{
			rgSrcType[cSrcType++] = rgGoodSrcType[1];
			odtLog << "DBSOURCETYPE_DATASOURCE_TDP\t";
		}
		if (uCombination & 0x4)
		{
			rgSrcType[cSrcType++] = rgGoodSrcType[2];
			odtLog << "DBSOURCETYPE_DATASOURCE_MDP\t";
		}
		odtLog << "\n";

		CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 
			cSrcType, rgSrcType, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.KillThread());
		TESTC(NULL != pIDBInitialize);
		TESTC(Dialog.IsResult(S_OK));
		SAFE_RELEASE(pIDBInitialize);
	}


CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Call IDBPromptInitialize::PromptDataSource in a loop, with and without filter; the DSO pointer obtained in the first call is used in the second one
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSourceTypeFilter::Variation_5()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	DBSOURCETYPE		rgSrcType[]			= {DBSOURCETYPE_DATASOURCE};
	ULONG				cSrcType			= NUMELEM(rgSrcType);
	ULONG				ulReps				= 7;

	for (;0 < ulReps; ulReps--)
	{
		CDSL_Dialog	Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 
			cSrcType, rgSrcType, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.CheckFilters());
		TESTC(Dialog.KillThread(PSBTN_OK));
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		// set the interface to be returned
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);
		SAFE_RELEASE(pIDBInitialize);	
	}		
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc Use enumerators as source filter => DB_E_NOPROVIDERREGISTERED
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSourceTypeFilter::Variation_6()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	DBSOURCETYPE		rgSrcType[]			= {	DBSOURCETYPE_DATASOURCE,
												DBSOURCETYPE_DATASOURCE_TDP,
												DBSOURCETYPE_ENUMERATOR,
												DBSOURCETYPE_DATASOURCE_MDP
												};
	DBSOURCETYPE		dbSrcType			= DBSOURCETYPE_ENUMERATOR;
	ULONG				cSrcType			= NUMELEM(rgSrcType);

	// ask for enumerator as source type, alone
	odtLog << "\tsrc filter is made of DBSOURCETYPE_ENUMERATOR only\n";
	CDSL_Dialog			Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 1, &dbSrcType, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	// thread sinchronization
	TESTC(Dialog.IsResult(DB_E_NOPROVIDERSREGISTERED));
	TESTC(NULL == pIDBInitialize);

	// include enumerator in the filter
	odtLog << "\tsrc filter includes DBSOURCETYPE_ENUMERATOR in a valid filter\n";
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	// thread sinchronization
	TESTC(Dialog.IsResult(DB_E_NOPROVIDERSREGISTERED));
	TESTC(NULL == pIDBInitialize);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc Inexistent source type filter => DB_E_NOPROVIDERREGISTERED
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSourceTypeFilter::Variation_7()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	
	DBSOURCETYPE		rgBadSrcType[]		= {	DBSOURCETYPE_DATASOURCE,
												0xFFFF,
												DBSOURCETYPE_DATASOURCE_TDP
												};
	ULONG				cBadSrcType			= NUMELEM(rgBadSrcType);
	DBSOURCETYPE		dbBadSrcType		= 0xFFFF;
	CDSL_Dialog			Dialog;

	// ask for enumerator as source type, alone
	odtLog << "\tsrc filter is made of bad source type only\n";

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 1, &dbBadSrcType, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsResult(DB_E_NOPROVIDERSREGISTERED));
	TESTC(NULL == pIDBInitialize);

	// include it in a valid filter
	odtLog << "\tsrc filter includes a bad source type\n";
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, cBadSrcType, rgBadSrcType, 
		NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	// invalid filter type is ignored
	Sleep(300);
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Long source type filter
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSourceTypeFilter::Variation_8()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	const ULONG			cSrcType			= 300;
	DBSOURCETYPE		rgSrcType[cSrcType];
	ULONG				ulReps				= 7;

	// set tup the large filter
	for (ulReps=0; ulReps < cSrcType; ulReps++)
	{
		if (rand()%2)
			rgSrcType[ulReps] = DBSOURCETYPE_DATASOURCE;
		else
			rgSrcType[ulReps] = DBSOURCETYPE_DATASOURCE_MDP;
	}

	for (ulReps=7; 0 < ulReps; ulReps--)
	{
		// now, use the large filter
		CDSL_Dialog	Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.CheckFilters());
		TESTC(Dialog.KillThread(PSBTN_OK));
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		// no filter, use the DSO obtained before
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.CheckFilters());
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);
		SAFE_RELEASE(pIDBInitialize);	
	}		
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Filter with DBSOURCETYPE_DATASOURCE_TDP, then with DBSOURCETYPE_DATASOURCE_MDP
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSourceTypeFilter::Variation_9()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	const ULONG			cSrcType			= 1;
	DBSOURCETYPE		rgSrcType[cSrcType]; 
	ULONG				ulReps				= 7;

	for (ulReps=7; 0 < ulReps; ulReps--)
	{
		// filter with DBSOURCETYPE_DATASOURCE_TDP
		rgSrcType[0] = DBSOURCETYPE_DATASOURCE_TDP;
		CDSL_Dialog	Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.CheckFilters());
		TESTC(Dialog.KillThread(PSBTN_OK));
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);
		SAFE_RELEASE(pIDBInitialize);

		// filter with DBSOURCETYPE_DATASOURCE_MDP
		rgSrcType[0] = DBSOURCETYPE_DATASOURCE_MDP;
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.CheckFilters());
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);
		SAFE_RELEASE(pIDBInitialize);	
	}		
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL CSourceTypeFilter::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(CProviderFilter)
//*-----------------------------------------------------------------------
//| Test Case:		CProviderFilter - Provider name filtering in IDBPromptInitialize::PromptDataSource
//| Created:  	3/8/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL CProviderFilter::Init()
{ 
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		// TO DO:  Add your own code here 
		return TRUE;
	} 
	return FALSE;
} 





// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Inexistent progID provided as a filter => it should be ignored
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_1()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	WCHAR				wszProviderFilter[]	= L"Inexistent progID\0\0\0\0";

	// inexistent provider passed as filter
	CDSL_Dialog			Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		wszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(Dialog.IsResult(DB_E_NOPROVIDERSREGISTERED));
	TESTC(NULL == pIDBInitialize);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Filter made of both existent and inexistent progIDs
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_2()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	const WCHAR			wszBadProgID[]		= L"Bad ProgID";
	WCHAR				*pwszProgID			= NULL;
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	ULONG				i;
	CDSL_Dialog			Dialog;

	// find a provider in the root enumerator sources rowset
	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count(); i++)
	{
		if (DBSOURCETYPE_DATASOURCE == (*g_pSourcesSet)[i].m_wType
			&& (CUSTOM_CONN & (*g_pSourcesSet)[i].m_CustomUI))
			break;
	}
	if (i >= CDSL_Dialog::s_pSourcesSet->Count())
		return TEST_SKIPPED;

	// get the progID
	TESTC_(ProgIDFromCLSID((*g_pSourcesSet)[i], &pwszProgID), S_OK);
	
	// try to put the correct progId at the beginning the bad one at the end
	odtLog << "\tgood progID first\n";

	// create provider progID filter
	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
	wcscpy(wszProviderFilter, pwszProgID);
	wcscat(wszProviderFilter+wcslen(pwszProgID)+1, wszBadProgID);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, wszProviderFilter, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize);

	// try to put the bad progID at the beginning the good one at the end
	odtLog << "\tbad progID first\n";

	// create provider progID filter
	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
	wcscpy(wszProviderFilter, wszBadProgID);
	wcscat(wszProviderFilter+wcslen(wszBadProgID)+1, pwszProgID);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, wszProviderFilter, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_FREE(pwszProgID);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Filter on providers that allows multiple source type (OLAP)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_3()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	DBSOURCETYPE		rgSrcType[2];
	ULONG				cSrcType			= NUMELEM(rgSrcType);
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	WCHAR				*pwszProviderFilter = wszProviderFilter;
	ULONG				i, j;
	WCHAR				*pwszProgID	= NULL;
	int					cMProv1 = -1;
	int					cMProv2 = -1;
	CDSL_Dialog			Dialog;

	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count()-1; i++)
	{
		for (j=i+1; j<CDSL_Dialog::s_pSourcesSet->Count(); j++)
		{
			if (0 == wcscmp((*g_pSourcesSet)[i].m_pwszParseName, (*g_pSourcesSet)[j].m_pwszParseName))
			{
				cMProv1 = i;
				cMProv2 = j;
				break;
			}
		}
		if (j<CDSL_Dialog::s_pSourcesSet->Count())
			break;
	}

	if (i>=(int)(CDSL_Dialog::s_pSourcesSet->Count()-1))
		return TEST_SKIPPED;

	TESTC(0 <= cMProv1 && cMProv1 < cMProv2);
	TESTC(cMProv1 < cMProv2 && cMProv2 < (int)CDSL_Dialog::s_pSourcesSet->Count());

	// don't set any src filter and set provider filter
	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
	// get the progID
	pwszProgID = NULL;
	TESTC_(ProgIDFromCLSID((*g_pSourcesSet)[cMProv1], &pwszProgID), S_OK);
	wcscpy(wszProviderFilter, pwszProgID);
	SAFE_FREE(pwszProgID);

	odtLog << "\tno filter on src type\n";
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		pwszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize);

	// try to set the first source type as a filter
	rgSrcType[0]	= (*g_pSourcesSet)[cMProv1].m_wType;
	cSrcType		= 1;

	odtLog << "\tfilter on first src type\n";
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, 
		pwszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize);

	// try to set the second source type as a filter
	rgSrcType[0]	= (*g_pSourcesSet)[cMProv2].m_wType;
	cSrcType		= 1;

	odtLog << "\tfilter on second src type\n";
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, 
		pwszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);
	SAFE_RELEASE(pIDBInitialize);
	
	// set both source types as filter
	rgSrcType[0]	= (*g_pSourcesSet)[cMProv1].m_wType;
	rgSrcType[1]	= (*g_pSourcesSet)[cMProv2].m_wType;
	cSrcType		= 2;

	odtLog << "\tfilter on both src types\n";
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, 
		pwszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_FREE(pwszProgID);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Singleton filter on each OLE DB provider returned by the enumerator (also check that the active page is the connection one)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_4()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	BOOL				fAckProv;
	DBSOURCETYPE		rgSrcType[1];
	ULONG				cSrcType			= NUMELEM(rgSrcType);
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	WCHAR				*pwszProviderFilter = wszProviderFilter;
	ULONG				i;
	WCHAR				*pwszProgID	= NULL;
	GUID				clsid;
	CDSL_Dialog			Dialog;
	
	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator
		fAckProv = (DBSOURCETYPE_DATASOURCE == (*g_pSourcesSet)[i].m_wType
			||	DBSOURCETYPE_DATASOURCE_TDP == (*g_pSourcesSet)[i].m_wType
			||	DBSOURCETYPE_DATASOURCE_MDP == (*g_pSourcesSet)[i].m_wType);

		// set provider filter, don't set any src filter 
		memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
		
		// get the progID
		pwszProgID = NULL;
		TESTC_(ProgIDFromCLSID((*g_pSourcesSet)[i], &pwszProgID), S_OK);
		wcscpy(wszProviderFilter, pwszProgID);
		odtLog << "\tOLEDB provider: " << pwszProgID << "\n";

		odtLog << "\t\tno filter on src type\n";
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, pwszProviderFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		if (fAckProv)
		{
			TESTC(Dialog.IsInExecution());
			TESTC(Dialog.CheckFilters());
			TESTC(Dialog.KillThread());
		}
		TESTC(Dialog.IsResult(fAckProv? S_OK: DB_E_NOPROVIDERSREGISTERED));
		if (fAckProv)
		{
			SAFE_RELEASE(pIDBInitialize);
		}
		else
			TESTC(NULL == pIDBInitialize);

		// try to set the source type as a filter
		rgSrcType[0]	= (*g_pSourcesSet)[i].m_wType;
		cSrcType		= 1;

		odtLog << "\t\tfilter on first src type\n";
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, pwszProviderFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
		
		if (fAckProv)
		{
			TESTC(Dialog.IsInExecution());
			TESTC(Dialog.CheckFilters());
			TESTC(Dialog.KillThread());
		}
		TESTC(Dialog.IsResult(fAckProv? S_OK: DB_E_NOPROVIDERSREGISTERED));
		if (fAckProv)
		{
			SAFE_RELEASE(pIDBInitialize);
		}
		else
			TESTC(NULL == pIDBInitialize);

		// just for the fun of it, make sure that CLSIDFromProgID works
		TESTC_(CLSIDFromProgID(pwszProgID, &clsid), S_OK);

CLEANUP:
		SAFE_RELEASE(pIDBInitialize);	
		SAFE_FREE(pwszProgID);
	}
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Singleton filter on each OLE DB provider returned by the enumerator (using the version independent progID)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_5()
{ 
	// ASSERT(SOURCES_NAME column in the root enumerator's rowset 
	//		contains the version independent ProgIDs of the OLEDB Providers)

	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	BOOL				fAckProv;
	DBSOURCETYPE		rgSrcType[1];
	ULONG				cSrcType			= NUMELEM(rgSrcType);
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	WCHAR				*pwszProviderFilter = wszProviderFilter;
	WCHAR				*pwszProvDesc		= NULL;
	CLSID				clsid;
	CDSL_Dialog			Dialog;
	ULONG				i;

	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator?
		fAckProv = (DBSOURCETYPE_DATASOURCE == (*g_pSourcesSet)[i].m_wType
			||	DBSOURCETYPE_DATASOURCE_TDP == (*g_pSourcesSet)[i].m_wType
			||	DBSOURCETYPE_DATASOURCE_MDP == (*g_pSourcesSet)[i].m_wType);

		// set provider filter, don't set any src filter 
		memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
		
		// get the filter
		wcscpy(wszProviderFilter, (*g_pSourcesSet)[i].m_pwszName);
		odtLog << "\tOLEDB provider: " << (*g_pSourcesSet)[i].m_pwszName << "\n";

		odtLog << "\t\tno filter on src type\n";
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, pwszProviderFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		if (fAckProv)
		{
			TESTC(Dialog.IsInExecution());
			TESTC(Dialog.CheckFilters());
			TESTC(Dialog.KillThread());
		}
		TESTC(Dialog.IsResult(fAckProv? S_OK: DB_E_NOPROVIDERSREGISTERED));
		SAFE_RELEASE(pIDBInitialize);

		// set the source type filter to source's type
		// try to set the first source type as a filter
		rgSrcType[0]	= (*g_pSourcesSet)[i].m_wType;
		cSrcType		= 1;

		odtLog << "\t\tfilter on first src type\n";
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, pwszProviderFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		if (fAckProv)
		{
			TESTC(Dialog.IsInExecution());
			TESTC(Dialog.CheckFilters());
			TESTC(Dialog.KillThread());
		}
		TESTC(Dialog.IsResult(fAckProv? S_OK: DB_E_NOPROVIDERSREGISTERED));

		SAFE_RELEASE(pIDBInitialize);

		// just for the fun of it, make sure that CLSIDFromProgID works
		TESTC_(CLSIDFromProgID((*g_pSourcesSet)[i].m_pwszName, &clsid), S_OK);

CLEANUP:
		TESTC(Dialog.KillThread());
		SAFE_FREE(pwszProvDesc);
		SAFE_RELEASE(pIDBInitialize);	
	}

	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc Existent DSO, filter name doesn't match the current provider
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_6()
{
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	IDBInitialize		*pIDBInitialize2	= NULL;
	WCHAR				*pwszProgID			= NULL;
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	WCHAR				*pNext = wszProviderFilter;
	WCHAR				*pwszClsid			= NULL;
	ULONG				i;
	CDSL_Dialog			Dialog;

	// the case where the DSO is already created
	TESTC_(GetModInfo()->CreateProvider(NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

	pIDBInitialize2 = pIDBInitialize;
	
	// create filter
	TESTC_(StringFromCLSID(m_pThisTestModule->m_ProviderClsid, &pwszClsid), S_OK);
	TESTC(NULL != pwszClsid);
	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count(); i++)
	{
		// get the current clsid
		if (	(	DBSOURCETYPE_DATASOURCE		== (*g_pSourcesSet)[i].m_wType
				||	DBSOURCETYPE_DATASOURCE_TDP	== (*g_pSourcesSet)[i].m_wType
				||	DBSOURCETYPE_DATASOURCE_MDP	== (*g_pSourcesSet)[i].m_wType)
			&&	((*g_pSourcesSet)[i] != m_pThisTestModule->m_ProviderClsid))
		{
			// get the current progID
			pwszProgID = NULL;
			TESTC_(ProgIDFromCLSID((*g_pSourcesSet)[i], &pwszProgID), S_OK);
			// add to filter
			wcscat(pNext, pwszProgID);
			// set pointer to the next possible position
			pNext += wcslen(pwszProgID)+1;
			SAFE_FREE(pwszProgID);
		}
	}
	TEST_PROVIDER(L'\0' != wszProviderFilter[0]);
	
	// create provider progID filter
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, wszProviderFilter, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));	// pending on bug #30134
	TESTC(NULL != pIDBInitialize);
	TESTC(pIDBInitialize != pIDBInitialize2);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_FREE(pwszProgID);
	SAFE_FREE(pwszClsid);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc Bad filter followed by good filter (for each provider)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_7()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	DBSOURCETYPE		rgSrcType[1];
	ULONG				cSrcType			= NUMELEM(rgSrcType);
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	WCHAR				*pNext = wszProviderFilter;
	ULONG				i, j, nChosen;
	WCHAR				*pwszProgID	= NULL;
	CDSL_Dialog			Dialog;

	// get a provider that only supports DBSOURCETYPE_DATASOURCE
	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count(); i++)
	{
		if (DBSOURCETYPE_DATASOURCE == (*g_pSourcesSet)[i].m_wType)
		{
			for (j=i+1; j<CDSL_Dialog::s_pSourcesSet->Count(); j++)
			{
				if (0 == wcscmp((*g_pSourcesSet)[i].m_pwszParseName, (*g_pSourcesSet)[j].m_pwszParseName))
					break;
			}
			if (j >= CDSL_Dialog::s_pSourcesSet->Count())
			{
				nChosen = i;
				break;
			}
		}
	}
	TESTC_PROVIDER(i<CDSL_Dialog::s_pSourcesSet->Count());
			
	// set datasource type filter to a bad value for the provider
	rgSrcType[0] = (DBSOURCETYPE_DATASOURCE_TDP == (*g_pSourcesSet)[i].m_wType)?
			DBSOURCETYPE_DATASOURCE_MDP: DBSOURCETYPE_DATASOURCE_TDP;

	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count(); i++)
	{
		if (DBSOURCETYPE_ENUMERATOR == (*g_pSourcesSet)[i].m_wType)
			continue;

		if (0 == wcscmp((*g_pSourcesSet)[i].m_pwszParseName, 
						(*g_pSourcesSet)[nChosen].m_pwszParseName))
			continue;

		// call with bad filter combination
		memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
		pwszProgID = NULL;
		TESTC_(ProgIDFromCLSID((*g_pSourcesSet)[nChosen], &pwszProgID), S_OK);
		wcscpy(pNext, pwszProgID);
		SAFE_FREE(pwszProgID);

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, 
			wszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsResult(DB_E_NOPROVIDERSREGISTERED));
		TESTC(NULL == pIDBInitialize);

		// call with good filter combination
		memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
		wcscpy(pNext, (*g_pSourcesSet)[i].m_pwszName);
		odtLog << "\t" << (*g_pSourcesSet)[i].m_pwszName << "\n"; 

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
			wszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.CheckFilters());
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		SAFE_RELEASE(pIDBInitialize);	
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_FREE(pwszProgID);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Long filter for provider name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_8()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	WCHAR				*pwszProviderFilter = wszProviderFilter;
	CDSL_Dialog			Dialog;
	ULONG				i;
	ULONG				cProvFilterLen		= 2; // double L'\0'

	// set provider filter, don't set any src filter 
	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));

	odtLog << "\tFilter is made of:\n";
	// add progids to provider filter
	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator?
		if (	DBSOURCETYPE_DATASOURCE != (*g_pSourcesSet)[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_TDP != (*g_pSourcesSet)[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != (*g_pSourcesSet)[i].m_wType)
			continue;
		
		// get the filter
		if (cProvFilterLen + wcslen((*g_pSourcesSet)[i].m_pwszName) > nMaxProv*cMaxName)
			break;
		wcscat(pwszProviderFilter, (*g_pSourcesSet)[i].m_pwszName);
		cProvFilterLen		+= wcslen(pwszProviderFilter) + 1; 
		pwszProviderFilter	+= wcslen(pwszProviderFilter) + 1;
		odtLog << "\t\t" << (WCHAR*)(*g_pSourcesSet)[i] << "\n";
	}

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, wszProviderFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	Sleep(200);
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Empty filter string
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_9()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	WCHAR				wszProviderFilter[]	= L"\0\0\0\0";

	// inexistent provider passed as filter
	CDSL_Dialog			Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		wszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(Dialog.IsResult(DB_E_NOPROVIDERSREGISTERED));
	TESTC(NULL == pIDBInitialize);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc Bad filter progID (international string)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_10()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	WCHAR				wszProviderFilter[cMaxName];
	CTable				Table(m_pThisTestModule->m_pIUnknown2, (LPWSTR)gwszModuleName);

	// privlib will generate an international name for the table
	memset(wszProviderFilter, 0, cMaxName*sizeof(WCHAR));
	Table.MakeTableName(NULL);
	wcscpy(wszProviderFilter, Table.GetTableName());

	// inexistent provider passed as filter
	CDSL_Dialog			Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
		wszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(Dialog.IsResult(DB_E_NOPROVIDERSREGISTERED));
	TESTC(NULL == pIDBInitialize);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(11)
//*-----------------------------------------------------------------------
// @mfunc Long filter followed by a short filter
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_11()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	WCHAR				*pwszProviderFilter = wszProviderFilter;
	WCHAR				wszShortProvFilter[cMaxName];
	CDSL_Dialog			Dialog;
	ULONG				i;
	ULONG				cProvFilterLen		= 2; // double L'\0'

	// set provider filter, don't set any src filter 
	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
	memset(wszShortProvFilter, 0, sizeof(wszShortProvFilter));

	odtLog << "\tFilter is made of:\n";
	// add progids to provider filter
	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator?
		if (	DBSOURCETYPE_DATASOURCE != (*g_pSourcesSet)[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_TDP != (*g_pSourcesSet)[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != (*g_pSourcesSet)[i].m_wType)
			continue;
		
		// get the filter
		if (cProvFilterLen + wcslen((*g_pSourcesSet)[i].m_pwszName) > nMaxProv*cMaxName)
			break;
		wcscat(pwszProviderFilter, (*g_pSourcesSet)[i].m_pwszName);
		cProvFilterLen		+= wcslen(pwszProviderFilter) + 1; 
		pwszProviderFilter	+= wcslen(pwszProviderFilter) + 1;
		odtLog << "\t\t" << (WCHAR*)(*g_pSourcesSet)[i] << "\n";
		wcscpy(wszShortProvFilter, (*g_pSourcesSet)[i].m_pwszName);
	}

	// long provider filter 
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, wszProviderFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	Sleep(2000);
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	SAFE_RELEASE(pIDBInitialize);

	// short provider filter
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, wszShortProvFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	Sleep(2000);
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	SAFE_RELEASE(pIDBInitialize);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(12)
//*-----------------------------------------------------------------------
// @mfunc Short filter followed by a long filter
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_12()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	WCHAR				*pwszProviderFilter = wszProviderFilter;
	WCHAR				wszShortProvFilter[cMaxName];
	CDSL_Dialog			Dialog;
	ULONG				i;
	ULONG				cProvFilterLen		= 2; // double L'\0'

	// set provider filter, don't set any src filter 
	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
	memset(wszShortProvFilter, 0, sizeof(wszShortProvFilter));

	odtLog << "\tFilter is made of:\n";
	// add progids to provider filter
	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator?
		if (	DBSOURCETYPE_DATASOURCE != (*g_pSourcesSet)[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_TDP != (*g_pSourcesSet)[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != (*g_pSourcesSet)[i].m_wType)
			continue;
		
		// get the filter
		if (cProvFilterLen + wcslen((*g_pSourcesSet)[i].m_pwszName) > nMaxProv*cMaxName)
			break;
		wcscat(pwszProviderFilter, (*g_pSourcesSet)[i].m_pwszName);
		cProvFilterLen		+= wcslen(pwszProviderFilter) + 1; 
		pwszProviderFilter	+= wcslen(pwszProviderFilter) + 1;
		odtLog << "\t\t" << (WCHAR*)(*g_pSourcesSet)[i] << "\n";
		wcscpy(wszShortProvFilter, (*g_pSourcesSet)[i].m_pwszName);
	}

	// long provider filter 
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, wszShortProvFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	Sleep(2000);
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	SAFE_RELEASE(pIDBInitialize);

	// short provider filter
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, wszProviderFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	Sleep(2000);
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	SAFE_RELEASE(pIDBInitialize);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(13)
//*-----------------------------------------------------------------------
// @mfunc Filter, no filter. Repeat.
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_13()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	WCHAR				*pwszProgID			= NULL;
	WCHAR				wszProviderFilter[cMaxName];
	const ULONG			cRepNo				= 5;
	ULONG				cIter;
	CDSL_Dialog			Dialog;

	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
	TESTC_(m_hr = ProgIDFromCLSID(GetModInfo()->GetProviderCLSID(), &pwszProgID), S_OK);
	wcscpy(wszProviderFilter, pwszProgID);

	for (cIter = 0; cIter < cRepNo; cIter++)
	{
		// filter
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
			wszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.CheckFilters());
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);
		SAFE_RELEASE(pIDBInitialize);

		// no filter
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.CheckFilters());
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);
		SAFE_RELEASE(pIDBInitialize);
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_FREE(pwszProgID);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(14)
//*-----------------------------------------------------------------------
// @mfunc Use non typo characters in filter (like \t and \n)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CProviderFilter::Variation_14()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	WCHAR				*pwszProviderFilter = wszProviderFilter;
	CDSL_Dialog			Dialog;
	ULONG				i;
	ULONG				cProvFilterLen		= 2; // double L'\0'
	WCHAR				wszSeparator[]		= L" \t\b";
	ULONG				cSep				= 1 + wcslen(wszSeparator);

	// set provider filter, don't set any src filter 
	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));

	odtLog << "\tFilter is made of:\n";
	// add progids to provider filter
	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator?
		if (	DBSOURCETYPE_DATASOURCE != (*g_pSourcesSet)[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_TDP != (*g_pSourcesSet)[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != (*g_pSourcesSet)[i].m_wType)
			continue;
		
		// get the filter
		if (cProvFilterLen + wcslen((*g_pSourcesSet)[i].m_pwszName) > nMaxProv*cMaxName)
			break;
		wcscat(pwszProviderFilter, (*g_pSourcesSet)[i].m_pwszName);
		cProvFilterLen		+= wcslen(pwszProviderFilter) + 1;
		// place a random character
		pwszProviderFilter[wcslen(pwszProviderFilter)] = wszSeparator[rand() % cSep];
		pwszProviderFilter	+= wcslen(pwszProviderFilter) + 1;
		odtLog << "\t\t" << (WCHAR*)(*g_pSourcesSet)[i] << "\n";
	}

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, wszProviderFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	Sleep(2000);
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread(PSBTN_CANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL CProviderFilter::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(CMixFilters)
//*-----------------------------------------------------------------------
//| Test Case:		CMixFilters - Mixes source type filtering and provider name filtering in IDBPromptInitialize::PromptDataSource
//| Created:  	3/8/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL CMixFilters::Init()
{ 
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		// TO DO:  Add your own code here 
		return TRUE;
	} 
	return FALSE;
} 





// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Mixed filter (source type + provider names)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CMixFilters::Variation_1()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	
	DBSOURCETYPE		rgSrcType[]			= {	DBSOURCETYPE_DATASOURCE_MDP,
												DBSOURCETYPE_DATASOURCE_TDP
												};
	ULONG				cSrcType			= NUMELEM(rgSrcType);
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	WCHAR				*pwszProviderFilter = wszProviderFilter;
	WCHAR				*pNext = wszProviderFilter;
	ULONG				i;
	WCHAR				*pwszProgID	= NULL;
	CDSL_Dialog			Dialog;

	// provider name filters will be made of the every second source prog id
	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count(); i++)
	{
		if (i%2)
		{
			TESTC_(ProgIDFromCLSID((*g_pSourcesSet)[i], &pwszProgID), S_OK);
			wcscat(pNext, pwszProgID);
			pNext += 1+wcslen(pwszProgID);
			SAFE_FREE(pwszProgID);
		}
	}
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, 
		pwszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_FREE(pwszProgID);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Bad mixed filter: DBSOURCETYPE_DATASOURCE source type and provider of type DBSOURCETYPE_DATASOURCE_TDP
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CMixFilters::Variation_2()
{
	TBEGIN
	IDBInitialize		*pIDBInitialize		= NULL;
	
	DBSOURCETYPE		rgSrcType[1];
	ULONG				cSrcType			= NUMELEM(rgSrcType);
	WCHAR				wszProviderFilter[nMaxProv*cMaxName];
	WCHAR				*pwszProviderFilter = wszProviderFilter;
	WCHAR				*pNext = wszProviderFilter;
	ULONG				i, j;
	WCHAR				*pwszProgID	= NULL;
	CDSL_Dialog			Dialog;

	// get a provider that only supports DBSOURCETYPE_DATASOURCE
	for (i=0; i<CDSL_Dialog::s_pSourcesSet->Count(); i++)
	{
		if (DBSOURCETYPE_DATASOURCE == (*g_pSourcesSet)[i].m_wType)
		{
			for (j=i+1; j<CDSL_Dialog::s_pSourcesSet->Count(); j++)
			{
				if (0 == wcscmp((*g_pSourcesSet)[i].m_pwszParseName, (*g_pSourcesSet)[j].m_pwszParseName))
					break;
			}
			if (j >= CDSL_Dialog::s_pSourcesSet->Count())
				break;
		}
	}
	TESTC_PROVIDER(i<CDSL_Dialog::s_pSourcesSet->Count());
			
	// set datasource type filter to a bad value for the provider
	rgSrcType[0] = (DBSOURCETYPE_DATASOURCE_TDP == (*g_pSourcesSet)[i].m_wType)?
			DBSOURCETYPE_DATASOURCE_MDP: DBSOURCETYPE_DATASOURCE_TDP;

	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
	TESTC_(ProgIDFromCLSID((*g_pSourcesSet)[i], &pwszProgID), S_OK);
	wcscpy(pNext, pwszProgID);
	SAFE_FREE(pwszProgID);

	for (i=0; i<4; i++)
	{
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, 
			pwszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsResult(DB_E_NOPROVIDERSREGISTERED));
		SAFE_RELEASE(pIDBInitialize);	
	}

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_FREE(pwszProgID);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL CMixFilters::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(CPromptOptions)
//*-----------------------------------------------------------------------
//| Test Case:		CPromptOptions - prompt options in IDBPromptInitialize::PromptDataSource
//| Created:  	3/8/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL CPromptOptions::Init()
{ 
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		// TO DO:  Add your own code here 
		return TRUE;
	} 
	return FALSE;
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Not flags at all => E_INVALIDARG
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_1()
{ 
	CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd,
	   0, 0, NULL, NULL, IID_IUnknown, NULL);

	return Dialog.IsResult(E_INVALIDARG);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Use DBPROMPTOPTIONS_PROPERTYSHEET
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_2()
{ 
	TBEGIN
	IUnknown	*pIUnknown = NULL;
	CDSL_Dialog	Dialog;

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd,
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, IID_IUnknown, (IUnknown**)&pIUnknown));
	
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIUnknown);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Use DBPROMPTOPTIONS_WIZARDSHEET
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_3()
{ 
	TBEGIN
	IUnknown	*pIUnknown = NULL;
	CDSL_Dialog	Dialog;

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd,
		DBPROMPTOPTIONS_WIZARDSHEET, 0, NULL, NULL, IID_IUnknown, (IUnknown**)&pIUnknown));
	
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIUnknown);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END



// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Existent DSO (with/without SC) or inexistent DSO and ask for DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_4()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize			= NULL;
	DWORD				dwOldSCOptions			= GetModInfo()->UseServiceComponents();
	CDSL_Dialog			*pDialog				= NULL;
	CLSID				clsidProvider			= GetModInfo()->GetProviderCLSID();

	// if datasource is not a provider skip the iteration
	TESTC_PROVIDER(!(CUSTOM_CONN & (*g_pSourcesSet)[clsidProvider].m_CustomUI));
		
	odtLog << L" no SC\n";
	// create datasource on the required CLSID
	GetModInfo()->PlugInServiceComponents(0);
	TESTC_(GetModInfo()->CreateProvider((CLSID)(*g_pSourcesSet)[clsidProvider], NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

	pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION, 
			0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(pDialog->IsInExecution());
	TESTC(!pDialog->HasProviderPage());
	TESTC(pDialog->KillThread(PSBTN_OK));
	TESTC(pDialog->IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);
		
	SAFE_DELETE(pDialog);
	SAFE_RELEASE(pIDBInitialize);

	odtLog << L", with SC\n";
	// create datasource on the required CLSID
	GetModInfo()->PlugInServiceComponents(SERVICECOMP_INVOKE);
	TESTC_(GetModInfo()->CreateProvider(clsidProvider, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

	pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION, 
			0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(pDialog->IsInExecution());
	TESTC(!pDialog->HasProviderPage());
	TESTC(pDialog->KillThread(PSBTN_OK));
	TESTC(pDialog->IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);
		
	SAFE_DELETE(pDialog);
	SAFE_RELEASE(pIDBInitialize);

	odtLog << L"\tinexistent DSO\n";
	// create datasource on the required CLSID
	pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION, 
			0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(pDialog->IsResult(E_INVALIDARG));
	TESTC(NULL == pIDBInitialize);


CLEANUP:
	SAFE_DELETE(pDialog);
	SAFE_RELEASE(pIDBInitialize);	

	GetModInfo()->PlugInServiceComponents(dwOldSCOptions);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Single provider filter, existent DSO with/without SC / inexistent DSO, use DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_5()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize			= NULL;
	LPWSTR				pwszszzProviderFilter	= NULL;
	DWORD				dwOptions				= GetModInfo()->UseServiceComponents();
	CDSL_Dialog			*pDialog				= NULL;
	CLSID				clsidProvider			= GetModInfo()->GetProviderCLSID();

	// if datasource is not a provider skip the iteration
	TESTC_PROVIDER(!(CUSTOM_CONN & (*g_pSourcesSet)[clsidProvider].m_CustomUI));

	// assume that the name in sources rowset is the ProgID
	SAFE_ALLOC(pwszszzProviderFilter, WCHAR, 1+wcslen((*g_pSourcesSet)[clsidProvider].m_pwszName));
	wcscpy(pwszszzProviderFilter, (*g_pSourcesSet)[clsidProvider].m_pwszName);
	wcscat(pwszszzProviderFilter, L"\0");	

	TESTC(NULL == pIDBInitialize);

	// Existent DSO
	// SC, create datasource on the required CLSID
	GetModInfo()->PlugInServiceComponents(SERVICECOMP_INVOKE);
	TESTC_(GetModInfo()->CreateProvider(clsidProvider, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

	odtLog << "\t" << " exist_SC\n";		
	pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION, 0, NULL, 
			pwszszzProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(pDialog->IsInExecution());
	TESTC(!pDialog->HasProviderPage());
	TESTC(pDialog->KillThread(PSBTN_OK));
	TESTC(pDialog->IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

	// NO SC, create datasource on the required CLSID
	SAFE_DELETE(pDialog);
	SAFE_RELEASE(pIDBInitialize);	
	GetModInfo()->PlugInServiceComponents(0);
	TESTC_(GetModInfo()->CreateProvider(clsidProvider, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

	odtLog << "\t" << " exist_Non SC \n";		
	pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION, 0, NULL, 
			pwszszzProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(pDialog->IsInExecution());
	TESTC(!pDialog->HasProviderPage());
	TESTC(pDialog->KillThread(PSBTN_OK));
	TESTC(pDialog->IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

	// the same scenario, but this time DSO doesn't exist
	SAFE_DELETE(pDialog);
	SAFE_RELEASE(pIDBInitialize);
	odtLog << "inexist \n";		
	pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION, 0, NULL, 
			pwszszzProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(pDialog->IsResult(E_INVALIDARG));
	TESTC(NULL == pIDBInitialize);

CLEANUP:
	SAFE_DELETE(pDialog);
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_FREE(pwszszzProviderFilter);
	
	GetModInfo()->PlugInServiceComponents(dwOptions);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc Single provider filter, existent DSO with/without SC / inexistent DSO, do not use DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_6()
{ 
	TBEGIN
	IDBInitialize		*pIDBInitialize			= NULL;
	LPWSTR				pwszszzProviderFilter	= NULL;
	DWORD				dwOptions				= GetModInfo()->UseServiceComponents();
	CDSL_Dialog			*pDialog				= NULL;
	CLSID				clsidProvider			= GetModInfo()->GetProviderCLSID();

	// if datasource is not a provider skip the iteration
	TESTC_PROVIDER(!(CUSTOM_CONN & (*g_pSourcesSet)[clsidProvider].m_CustomUI));

	// assume that the name in sources rowset is the ProgID
	SAFE_ALLOC(pwszszzProviderFilter, WCHAR, 1+wcslen((*g_pSourcesSet)[clsidProvider].m_pwszName));
	wcscpy(pwszszzProviderFilter, (*g_pSourcesSet)[clsidProvider].m_pwszName);
	wcscat(pwszszzProviderFilter, L"\0");	

	TESTC(NULL == pIDBInitialize);

	// Existent DSO
	// SC, create datasource on the required CLSID
	GetModInfo()->PlugInServiceComponents(SERVICECOMP_INVOKE);
	TESTC_(GetModInfo()->CreateProvider(clsidProvider, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

	odtLog << "\t" << " exist_SC \n";		
	pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
			pwszszzProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(pDialog->IsInExecution());
	TESTC(pDialog->HasProviderPage());
	TESTC(pDialog->KillThread(PSBTN_OK));
	TESTC(pDialog->IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

	// NO SC, create datasource on the required CLSID
	SAFE_DELETE(pDialog);
	SAFE_RELEASE(pIDBInitialize);	
	GetModInfo()->PlugInServiceComponents(0);
	TESTC_(GetModInfo()->CreateProvider(clsidProvider, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

	odtLog << "\t" << " exist_Non SC \n";		
	pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
			pwszszzProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(pDialog->IsInExecution());
	TESTC(pDialog->HasProviderPage());
	TESTC(pDialog->KillThread(PSBTN_OK));
	TESTC(pDialog->IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

	// the same scenario, but this time DSO doesn't exist
	SAFE_DELETE(pDialog);
	SAFE_RELEASE(pIDBInitialize);
	pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
			pwszszzProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	odtLog << "inexist \n";		
	TESTC(pDialog->IsInExecution());
	TESTC(pDialog->HasProviderPage());
	TESTC(pDialog->KillThread(PSBTN_OK));
	TESTC(pDialog->IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

CLEANUP:
	SAFE_DELETE(pDialog);
	SAFE_RELEASE(pIDBInitialize);	
	SAFE_FREE(pwszszzProviderFilter);
	GetModInfo()->PlugInServiceComponents(dwOptions);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc NULL == *ppDataSource and ask for disable provider selection => E_INVALIDARG
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_7()
{ 
	CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd,
	   DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION, 
	   0, NULL, NULL, IID_IUnknown, NULL);

	return Dialog.IsResult(E_INVALIDARG);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Use DBPROMPTOPTIONS_DISABLESAVEPASSWORD to create a new DSO
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_8()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize = NULL;
	VARIANT_BOOL	fAuthPersist;
	WCHAR			*pwszPassword = NULL;
	WCHAR			wszPassword[] = L"Parola si buna";
	IDBProperties	*pIDBProperties = NULL;
	BOOL			fSupportedAuthPersist = FALSE;
	BOOL			fSupportedPassword;
	DWORD			dwUseSC;
	CDSL_Dialog		Dialog;
	CDSL_Dialog		*pDialog = new CDSL_Dialog;
	CLSID			clsidProvider			= GetModInfo()->GetProviderCLSID();

	dwUseSC = GetModInfo()->UseServiceComponents();
	GetModInfo()->PlugInServiceComponents(SERVICECOMP_INVOKE);
	
	TESTC_PROVIDER(!(CUSTOM_CONN & (*g_pSourcesSet)[clsidProvider].m_CustomUI));
		
	CHECK(GetModInfo()->CreateProvider(clsidProvider, NULL, 
		IID_IDBProperties, (IUnknown**)&pIDBProperties), S_OK);
		fSupportedAuthPersist = SupportedProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO,
		DBPROPSET_DBINIT, pIDBProperties, DATASOURCE_INTERFACE);
	
	fSupportedPassword = SupportedProperty(DBPROP_AUTH_PASSWORD,
			DBPROPSET_DBINIT, pIDBProperties, DATASOURCE_INTERFACE);
	
	SAFE_RELEASE(pIDBInitialize);
	
	// use SAVE_PASSWORD
	odtLog << "\tGeneral testing: set the Allow Set Password box if possible\n";
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
	
	TESTC(Dialog.SelectProvider(clsidProvider));
	TESTC(Dialog.GotoConnectionPage());
	TESTC_PROVIDER(Dialog.IsControlEnabled(IDC_BlankPassword));
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(wszPassword));
	TESTC(Dialog.CheckControlStatus(fSupportedAuthPersist && fSupportedPassword, IDC_SAVEPASSWORD));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
		
	TESTC(!fSupportedPassword 
		|| GetProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT, pIDBInitialize, &pwszPassword));
	
	TESTC(!fSupportedPassword || !pwszPassword || 0 == wcscmp(wszPassword, pwszPassword));
	SAFE_FREE(pwszPassword);
		
	if (fSupportedAuthPersist)
	{
		TESTC(GetProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, 
			DBPROPSET_DBINIT, pIDBInitialize, &fAuthPersist)
			&& VARIANT_TRUE == fAuthPersist || !fSupportedPassword);
	}

	// disable SAVE_PASSWORD
	SAFE_RELEASE(pIDBInitialize);
	odtLog << "\tUse DBPROMPTOPTIONS_DISABLESAVEPASSWORD\n";
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLESAVEPASSWORD, 
			0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
		
	TESTC(Dialog.SelectProvider(clsidProvider));
	TESTC(Dialog.GotoConnectionPage());
	TESTC_PROVIDER(Dialog.IsControlEnabled(IDC_BlankPassword));
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(wszPassword));
	TESTC(Dialog.CheckControlStatus(FALSE, IDC_SAVEPASSWORD));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

	if (fSupportedAuthPersist)
	{
		TESTC(GetProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO,  DBPROPSET_DBINIT, pIDBInitialize, &fAuthPersist)
				&& VARIANT_FALSE == fAuthPersist);
		TESTC(	!(GetProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT, pIDBInitialize, &pwszPassword))
				||	!pwszPassword
				||	0 == wcscmp(wszPassword, pwszPassword))
	}
	else
	{
		TESTC(	!(GetProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT, pIDBInitialize, &pwszPassword))
			||	!pwszPassword
			||	0 == wcscmp(wszPassword, pwszPassword))
	}
		
CLEANUP:
	COMPARE(Dialog.KillThread(), TRUE);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBProperties);
	SAFE_FREE(pwszPassword);
	
	GetModInfo()->PlugInServiceComponents(dwUseSC);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




//------------------------------------------------------------------------
//
// Verifies DBPROMPTOPTIONS_DISABLESAVEPASSWORD with existing DSO
//------------------------------------------------------------------------
BOOL CPromptOptions::CheckDisSavePasswdOnExistingDSO(
	CLSID	clsidProvider, 
	BOOL	fDisableSavePassword,
	BOOL	fInvokeSC,
	BOOL	fPersistSecurityInfo
)
{
	TBEGIN
	IDBInitialize	*pIDBInitialize = NULL;
	VARIANT_BOOL	fAuthPersist;
	VARIANT_BOOL	fRequiredAuthPersist = fPersistSecurityInfo? VARIANT_TRUE: VARIANT_FALSE;
	WCHAR			*pwszPassword = NULL;
	WCHAR			wszPassword[] = L"Parola si buna";
	IDBProperties	*pIDBProperties = NULL;
	BOOL			fSupportedAuthPersist	= FALSE;
	BOOL			fSettableAuthPersist	= FALSE;
	BOOL			fSupportedPassword;
	DBPROP			rgProp[1];
	DBPROPSET		rgPropSet[1];
	HRESULT			hr;
	CDSL_Dialog		Dialog;

	// save current value of service component options
	DWORD			dwVal = GetModInfo()->UseServiceComponents();

	rgProp[0].dwPropertyID	= DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO;
	rgProp[0].dwOptions		= DBPROPOPTIONS_REQUIRED;
	rgProp[0].colid			= DB_NULLID;
	rgProp[0].vValue.vt		= VT_BOOL;
	V_BOOL(&rgProp[0].vValue)	= fRequiredAuthPersist;
	rgPropSet[0].rgProperties		= rgProp;
	rgPropSet[0].cProperties		= 1;
	rgPropSet[0].guidPropertySet	= DBPROPSET_DBINIT;

	odtLog << ((fDisableSavePassword)? "\tdisable password, ": "\tenable password, ");
	odtLog << "on an existing datasource created ";
	odtLog << ((fInvokeSC)? "with SC ": "without SC hooked ");
	odtLog << "and the value of persist security info ";
	odtLog << ((fPersistSecurityInfo)? "set.\n": "reset.\n");

	// hook service components if required
	GetModInfo()->PlugInServiceComponents(fInvokeSC? SERVICECOMP_INVOKE: 0);

	// create datasource on the required CLSID
	CHECK(GetModInfo()->CreateProvider(clsidProvider, NULL, 
		IID_IDBProperties, (IUnknown**)&pIDBProperties), S_OK);
		
	// check if DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO is supported
	fSupportedAuthPersist	= SupportedProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO,
			DBPROPSET_DBINIT, pIDBProperties, DATASOURCE_INTERFACE);
	fSettableAuthPersist	= SettableProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO,
			DBPROPSET_DBINIT, pIDBProperties, DATASOURCE_INTERFACE);
	TESTC_PROVIDER(fSupportedAuthPersist);

	// check if DBPROP_AUTH_PASSWORD is supported
	fSupportedPassword = SupportedProperty(DBPROP_AUTH_PASSWORD,
			DBPROPSET_DBINIT, pIDBProperties, DATASOURCE_INTERFACE);

	// set DBPROP_AURH_PERSIST_SENSITIVE_AUTHINFO
	hr = pIDBProperties->SetProperties(1, rgPropSet);
	TESTC(!fSettableAuthPersist || S_OK == hr);
	TESTC_PROVIDER(S_OK == hr);

	TESTC(GetProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, 
			DBPROPSET_DBINIT, pIDBProperties, &fAuthPersist));
	TESTC(fRequiredAuthPersist == fAuthPersist);

	// build the scenario
	TESTC(VerifyInterface(pIDBProperties, IID_IDBInitialize, 
		DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));


	// use enable/diasable password
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		fDisableSavePassword? DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLESAVEPASSWORD: DBPROMPTOPTIONS_PROPERTYSHEET, 
		0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectProvider(clsidProvider));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
	TESTC(Dialog.SetPassword(wszPassword));

	if (fDisableSavePassword)
	{
		TESTC(!Dialog.IsControlEnabled(IDC_SAVEPASSWORD));
	}
	else
	{
		TESTC(fSupportedPassword == Dialog.IsControlEnabled(IDC_SAVEPASSWORD));
		TESTC(!fSettableAuthPersist && VARIANT_TRUE != fAuthPersist ||
			Dialog.SetSavePassword(BST_CHECKED));
	}

	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

	if (fDisableSavePassword)
	{
		// fSupportedAuthPersist is TRUE
		// DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO must be VARIANT_FALSE
		TESTC(GetProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, 
			DBPROPSET_DBINIT, pIDBInitialize, &fAuthPersist)
			&& VARIANT_FALSE == fAuthPersist);
		// check password is set correctly
		TESTC(	!(GetProperty(DBPROP_AUTH_PASSWORD, 
				DBPROPSET_DBINIT, pIDBInitialize, &pwszPassword))
			||	!pwszPassword
			||	0 == wcscmp(wszPassword, pwszPassword))
	}
	else
	{
		// password should be correctly passed
		TESTC(!fSupportedPassword 
			|| GetProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT, 
			pIDBInitialize, &pwszPassword));
		TESTC(!fSupportedPassword || !pwszPassword
			|| 0 == wcscmp(wszPassword, pwszPassword));
		SAFE_FREE(pwszPassword);
		
		// fSupportedAuthPersist is TRUE
		// DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO must be VARIANT_TRUE
		TESTC(!fSupportedPassword || !fSettableAuthPersist 
			||	GetProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, 
					DBPROPSET_DBINIT, pIDBInitialize, &fAuthPersist)
				&& VARIANT_TRUE == fAuthPersist);
	}
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBProperties);
	SAFE_FREE(pwszPassword);
	GetModInfo()->PlugInServiceComponents(dwVal);
	TRETURN
} //CPromptOptions::CheckDisSavePasswdOnExistingDSO




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Use DBPROMPTOPTIONS_DISABLESAVEPASSWORD to update an existing DSO
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_9()
{ 
	TBEGIN
	CLSID			clsidProvider = GetModInfo()->GetProviderCLSID();

	TESTC_PROVIDER(!(CUSTOM_CONN & (*g_pSourcesSet)[clsidProvider].m_CustomUI));
			
	// check all the cases
	CheckDisSavePasswdOnExistingDSO(clsidProvider, FALSE,	FALSE,	FALSE);
	CheckDisSavePasswdOnExistingDSO(clsidProvider, FALSE,	FALSE,	TRUE);
	CheckDisSavePasswdOnExistingDSO(clsidProvider, FALSE,	TRUE,	FALSE);
	CheckDisSavePasswdOnExistingDSO(clsidProvider, FALSE,	TRUE,	TRUE);
	CheckDisSavePasswdOnExistingDSO(clsidProvider, TRUE,	FALSE,	FALSE);
	CheckDisSavePasswdOnExistingDSO(clsidProvider, TRUE,	FALSE,	TRUE);
	CheckDisSavePasswdOnExistingDSO(clsidProvider, TRUE,	TRUE,	FALSE);
	CheckDisSavePasswdOnExistingDSO(clsidProvider, TRUE,	TRUE,	TRUE);

CLEANUP:
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc Use DBPROMPTOPTIONS_DISABLESAVEPASSWORD and try to set Persist Sensitive Info in the Summary Page
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_10()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize = NULL;
	CDSL_Dialog		Dialog;

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLESAVEPASSWORD, 
			0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoAllPage());
	TESTC(Dialog.CheckError_OnEditing_PersistSecurityInfo());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(11)
//*-----------------------------------------------------------------------
// @mfunc Use registry key to enable saving password (call with and without DBPROMPTOPTIONS_DISABLESAVEPASSWORD)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_11()
{ 
	TBEGIN
	DWORD			cLen		= cMaxName;
	LONG			lRes;
	LONG			lRes2;
	DWORD			dwType;
	CHAR			szSubKey[]	= "CLSID\\{2206CDB2-19C1-11D1-89E0-00C04FD7A829}";
	HKEY			hKey		= 0;
	DWORD			dwOldFDPS;
	DWORD			dwFDPS;
	BOOL			fValueExist = FALSE;
	IDBInitialize	*pIDBInitialize = NULL;
	WCHAR			*pwszSockeyeProgID = NULL;
	CHAR			szValName[] = "fDPS";
	CDSL_Dialog		Dialog;

	// check whether Sockeye is supported
	TESTC_PROVIDER(S_OK == ProgIDFromCLSID(CLSID_MSDASQL, &pwszSockeyeProgID));

	// get to the magic key
	lRes = 	RegOpenKeyExA(
		HKEY_CLASSES_ROOT,         // handle to open key
		szSubKey,  // address of name of subkey to open
		NULL,   // reserved
		KEY_QUERY_VALUE | KEY_WRITE, // security access mask
		&hKey    // address of handle to open key
	);
	TESTC_PROVIDER(ERROR_SUCCESS == lRes);
	lRes = RegQueryValueExA(
		hKey,							// handle to key to query
		szValName,					// name of subkey to query
		NULL,							// reserved
		&dwType,						// address of buffer for value type
		(LPBYTE)&dwOldFDPS,			// buffer for returned string
		&cLen							// receives size of returned string
		);
	fValueExist = ERROR_SUCCESS == lRes;
	if (fValueExist)
		TESTC(REG_DWORD == dwType);

	// enable allow save password
	dwFDPS = 0;
	lRes = RegSetValueEx(
		hKey,			        // handle to key to set value for
		szValName,				// name of the value to set
		NULL,					// reserved
		REG_DWORD,				// flag for value type
		(const BYTE*)&dwFDPS,	// address of value data
		sizeof(DWORD)			// size of value data
	);
	TESTC(ERROR_SUCCESS == lRes);

	// execute the scenario
	TESTC(Dialog.CreateUDLFile(g_wszUDLFileName));
	TESTC(Dialog.SpawnUDLFile(g_wszUDLFileName));
	TESTC_PROVIDER(Dialog.IsInExecution());
	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage	());
	TESTC(Dialog.IsControlEnabled(IDC_SAVEPASSWORD));
	TESTC(Dialog.KillThread(PSBTN_CANCEL));

	// now check that the key does not affect the DSL invoked through IDBPromptInitialize
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 
			0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage	());
	TESTC(Dialog.IsControlEnabled(IDC_SAVEPASSWORD));
	TESTC(Dialog.KillThread(PSBTN_CANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pIDBInitialize);

	// now disable saving password
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLESAVEPASSWORD, 
			0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage	());
	TESTC(!Dialog.IsControlEnabled(IDC_SAVEPASSWORD));
	TESTC(Dialog.KillThread(PSBTN_CANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pIDBInitialize);

CLEANUP:
	SAFE_FREE(pwszSockeyeProgID);

	// reset the value to the original one
	if (fValueExist)
		lRes2 = RegSetValueEx(
			hKey,						// handle to key to set value for
			szValName,						// name of the value to set
			NULL,						// reserved
			REG_DWORD,					// flag for value type
			(const BYTE*)&dwOldFDPS,	// address of value data
			sizeof(DWORD)				// size of value data
		);
	else
		lRes2 = RegDeleteValueA(hKey, szValName);

	lRes2 = RegCloseKey(hKey);
	if (ERROR_SUCCESS != lRes)
	{
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			lRes,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
		// Free the buffer.
		LocalFree( lpMsgBuf );
	}
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(12)
//*-----------------------------------------------------------------------
// @mfunc Use registry key to disable saving password (call with and without DBPROMPTOPTIONS_DISABLESAVEPASSWORD)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_12()
{ 
	TBEGIN
	DWORD			cLen		= cMaxName;
	LONG			lRes;
	LONG			lRes2;
	DWORD			dwType;
	CHAR			szSubKey[]	= "CLSID\\{2206CDB2-19C1-11D1-89E0-00C04FD7A829}";
	HKEY			hKey		= 0;
	DWORD			dwOldFDPS;
	DWORD			dwFDPS;
	BOOL			fValueExist = FALSE;
	IDBInitialize	*pIDBInitialize = NULL;
	WCHAR			*pwszSockeyeProgID = NULL;
	CHAR			szValName[] = "fDPS";
	CDSL_Dialog		Dialog;

	// check whether Sockeye is supported
	TESTC_PROVIDER(S_OK == ProgIDFromCLSID(CLSID_MSDASQL, &pwszSockeyeProgID));

	// get to the magic key
	lRes = 	RegOpenKeyExA(
		HKEY_CLASSES_ROOT,         // handle to open key
		szSubKey,  // address of name of subkey to open
		NULL,   // reserved
		KEY_QUERY_VALUE | KEY_WRITE, // security access mask
		&hKey    // address of handle to open key
	);
	TESTC_PROVIDER(ERROR_SUCCESS == lRes);
	lRes = RegQueryValueExA(
		hKey,							// handle to key to query
		szValName,					// name of subkey to query
		NULL,							// reserved
		&dwType,						// address of buffer for value type
		(LPBYTE)&dwOldFDPS,			// buffer for returned string
		&cLen							// receives size of returned string
		);
	fValueExist = ERROR_SUCCESS == lRes;
	if (fValueExist)
		TESTC(REG_DWORD == dwType);

	// disable allow save password
	dwFDPS = 1;
	lRes = RegSetValueEx(
		hKey,			        // handle to key to set value for
		szValName,				// name of the value to set
		NULL,					// reserved
		REG_DWORD,				// flag for value type
		(const BYTE*)&dwFDPS,	// address of value data
		sizeof(DWORD)			// size of value data
	);
	TESTC(ERROR_SUCCESS == lRes);

	// execute the scenario
	TESTC(Dialog.CreateUDLFile(g_wszUDLFileName));
	TESTC(Dialog.SpawnUDLFile(g_wszUDLFileName));
	TESTC_PROVIDER(Dialog.IsInExecution());
	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage	());
	TESTC(!Dialog.IsControlEnabled(IDC_SAVEPASSWORD));
	TESTC(Dialog.KillThread());

	// now check that the key does not affect the DSL invoked through IDBPromptInitialize
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 
			0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage	());
	TESTC(Dialog.IsControlEnabled(IDC_SAVEPASSWORD));
	TESTC(Dialog.KillThread(PSBTN_CANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pIDBInitialize);

	// now disable saving password
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLESAVEPASSWORD, 
			0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage	());
	TESTC(!Dialog.IsControlEnabled(IDC_SAVEPASSWORD));
	TESTC(Dialog.KillThread(PSBTN_CANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pIDBInitialize);
	
CLEANUP:
	SAFE_FREE(pwszSockeyeProgID);

	// reset the value to the original one
	if (fValueExist)
		lRes2 = RegSetValueEx(
			hKey,						// handle to key to set value for
			szValName,						// name of the value to set
			NULL,						// reserved
			REG_DWORD,					// flag for value type
			(const BYTE*)&dwOldFDPS,	// address of value data
			sizeof(DWORD)				// size of value data
		);
	else
		lRes2 = RegDeleteValueA(hKey, szValName);

	lRes2 = RegCloseKey(hKey);
	if (ERROR_SUCCESS != lRes)
	{
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			lRes,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
		// Free the buffer.
		LocalFree( lpMsgBuf );
	}
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(13)
//*-----------------------------------------------------------------------
// @mfunc Inexistent flags => E_INVALIDARG
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_13()
{ 
	TBEGIN
	DBPROMPTOPTIONS		dwPromptOptions;
	IDBInitialize		*pIDBInitialize = NULL;
	CDSL_Dialog			Dialog;
	
	for (dwPromptOptions=1; dwPromptOptions; dwPromptOptions *= 2)
	{
		if (dwPromptOptions & 
			(DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_WIZARDSHEET
			|DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION
			|DBPROMPTOPTIONS_DISABLESAVEPASSWORD))
			continue;

		// execute the scenario
		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			dwPromptOptions | DBPROMPTOPTIONS_PROPERTYSHEET, 
			0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
		Sleep(2000);
		TESTC(Dialog.IsResult(E_INVALIDARG));
		TESTC(NULL == pIDBInitialize);
	}

CLEANUP:
	TOUTPUT_IF_FAILED(dwPromptOptions);
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(14)
//*-----------------------------------------------------------------------
// @mfunc DBPROMPTOPTIONS_WIZARDSHEET | DBPROMPTOPTIONS_PROPERTYSHEET
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_14()
{ 
	TBEGIN
	IUnknown	*pIUnknown = NULL;
	CDSL_Dialog	Dialog;

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd,
		DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_WIZARDSHEET, 
		0, NULL, NULL, IID_IUnknown, (IUnknown**)&pIUnknown));
	
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIUnknown);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END





// {{ TCW_VAR_PROTOTYPE(15)
//*-----------------------------------------------------------------------
// @mfunc Use valid flags, but not DBPROMPTOPTIONS_PROPERTYSHEET or DBPROMPTOPTIONS_WIZARDSHEET
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptOptions::Variation_15()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize = NULL;
	CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd,
	   DBPROMPTOPTIONS_DISABLESAVEPASSWORD, 0, NULL, NULL, IID_IUnknown, (IUnknown**)&pIDBInitialize);

	TESTC(Dialog.IsResult(E_INVALIDARG));

	// create a session object
	// the case where the DSO is already created and initialized
	TESTC_(GetModInfo()->CreateProvider(NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd,
		DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION, 0, NULL, NULL, IID_IUnknown, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.IsResult(E_INVALIDARG));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd,
		DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION | DBPROMPTOPTIONS_DISABLESAVEPASSWORD, 
		0, NULL, NULL, IID_IUnknown, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.IsResult(E_INVALIDARG));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL CPromptOptions::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(CParentWindow)
//*-----------------------------------------------------------------------
//| Test Case:		CParentWindow - values for hWndParent in IDBPromptInitialize::PromptDataSource
//| Created:  	3/8/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL CParentWindow::Init()
{ 
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		// TO DO:  Add your own code here 
		return TRUE;
	} 
	return FALSE;
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc NULL hWndParent => S_OK
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CParentWindow::Variation_1()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, 0, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc hWndParent is the desktop area => centerd to the screen
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CParentWindow::Variation_2()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, GetDesktopWindow(), 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc hWndParent  is LTM window
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CParentWindow::Variation_3()
{ 
	TBEGIN
	HWND				hWnd;
	CHAR				szWindowName[cMaxName];
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	

	hWnd = GetForegroundWindow();
	TESTC_PROVIDER(NULL != hWnd);
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC_PROVIDER(0 == strcmp(szWindowName, "Microsoft Local Test Manager"));

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, hWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Parent window is not entirely contained in the screen (center is)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CParentWindow::Variation_4()
{ 
	TBEGIN
	HWND				hWnd;
	RECT				rect;
	RECT				rDesktop;
	LONG				width;
	LONG				height;
	CHAR				szWindowName[cMaxName];
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	

	hWnd = GetForegroundWindow();
	TESTC_PROVIDER(NULL != hWnd);
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC_PROVIDER(0 == strcmp(szWindowName, "Microsoft Local Test Manager"));

	// store initial position of the parent window
	TESTC(GetWindowRect(hWnd, &rect));
	TESTC(GetWindowRect(GetDesktopWindow(), &rDesktop));
	width	= rect.right - rect.left;
	height	= rect.bottom - rect.top;
	
	// move LTM a bit off the screen (to the left)
	TESTC(MoveWindow(hWnd, -width/12, 0, width, height, TRUE));
	Sleep(500);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, hWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

	// move LTM a bit off the screen (to the right)
	TESTC(MoveWindow(hWnd, rDesktop.right-width+width/12, 0, width, height, TRUE));
	Sleep(500);

	SAFE_RELEASE(pIDBInitialize);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, hWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());

	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);


	// move LTM a bit off the screen (upward)
	TESTC(MoveWindow(hWnd, 0, -height/12, width, height, TRUE));
	Sleep(500);

	SAFE_RELEASE(pIDBInitialize);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, hWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);


	// move LTM a bit off the screen (downward)
	TESTC(MoveWindow(hWnd, 0, rDesktop.bottom-height+height/12, width, height, TRUE));
	Sleep(500);

	SAFE_RELEASE(pIDBInitialize);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, hWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

CLEANUP:
	TESTC(MoveWindow(hWnd, rect.left, rect.top, width, height, TRUE));
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Parent window is not entirely contained in the screen (center is not)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CParentWindow::Variation_5()
{ 
	TBEGIN
	HWND				hWnd;
	RECT				rect;
	RECT				rDesktop;
	LONG				width;
	LONG				height;
	CHAR				szWindowName[cMaxName];
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	

	hWnd = GetForegroundWindow();
	TESTC_PROVIDER(NULL != hWnd);
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC_PROVIDER(0 == strcmp(szWindowName, "Microsoft Local Test Manager"));

	// store initial position of the parent window
	TESTC(GetWindowRect(hWnd, &rect));
	TESTC(GetWindowRect(GetDesktopWindow(), &rDesktop));
	width	= rect.right - rect.left;
	height	= rect.bottom - rect.top;
	
	// move LTM to the left
	TESTC(MoveWindow(hWnd, (int)(-width*2.0/3.0), 0, width, height, TRUE));
	Sleep(500);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, hWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);


	// move LTM to the right
	TESTC(MoveWindow(hWnd, (int)(rDesktop.right-width/3.0), 0, width, height, TRUE));
	Sleep(500);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, hWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);


	// move LTM down
	TESTC(MoveWindow(hWnd, 0, (int)(-height*2.0/3.0), width, height, TRUE));
	Sleep(500);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, hWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);


	// move LTM up
	TESTC(MoveWindow(hWnd, 0, (int)(rDesktop.bottom-height/3.0), width, height, TRUE));
	Sleep(500);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, hWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));
	TESTC(NULL != pIDBInitialize);

CLEANUP:
	TESTC(MoveWindow(hWnd, rect.left, rect.top, width, height, TRUE));
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END



// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL CParentWindow::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END



// {{ TCW_TC_PROTOTYPE(CGenericOp)
//*-----------------------------------------------------------------------
//| Test Case:		CGenericOp - all kinds of scenarios that don't go anywhere else
//| Created:  	3/26/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL CGenericOp::Init()
{ 
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		// TO DO:  Add your own code here 
		return TRUE;
	} 
	return FALSE;
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Check the Next button in the provider page
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CGenericOp::Variation_1()
{ 
	TBEGIN
	IDBInitialize	*pIDBInitialize = NULL;
	CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd,
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL,
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.PushButton(IDC_Next));
	TESTC(Dialog.IsCurrentPage(g_nConnection));
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Use a long UDL file
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CGenericOp::Variation_2()
{ 
	TBEGIN
	WCHAR			wszFileName[_MAX_PATH]	= L"\\";
	ULONG			cLen;
	ULONG			cTNLen;
	CDSL_Dialog		Dialog;
	CTable			Table(m_pThisTestModule->m_pIUnknown2, (LPWSTR)gwszModuleName);
	
	// prepare a long localized name
	TESTC_(Table.MakeTableName(NULL), S_OK);
	cTNLen = wcslen(Table.GetTableName());
	if (cTNLen < _MAX_PATH/sizeof(WCHAR))
		wcscat(wszFileName, Table.GetTableName());
	for (cLen=wcslen(wszFileName); cLen+cTNLen < _MAX_PATH/sizeof(WCHAR); cLen += cTNLen)
	{
		wcscat(wszFileName, Table.GetTableName());
	}
	for (;cLen < (_MAX_PATH-4)/sizeof(WCHAR); cLen++)
	{
		wcscat(wszFileName, L"a");
	}
	wcscat(wszFileName, L".udl");
	TESTC(Dialog.CreateUDLFile(wszFileName));
	TESTC(Dialog.SpawnUDLFile(wszFileName));
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.IsCurrentPage(g_nConnection));
	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.IsCurrentPage(g_nProvider));
	TESTC(Dialog.PushButton(IDC_Next));
	TESTC(Dialog.IsCurrentPage(g_nConnection));
	TESTC(Dialog.KillThread());

CLEANUP:
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Create a UDL file and then use BindFileToMoniker
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CGenericOp::Variation_3()
{ 
	TBEGIN
	IMoniker		*pIMoniker				= NULL;
	IDBInitialize	*pIDBInitialize			= NULL;
	IBindCtx		*piBindCtx				= NULL;
	IDBProperties	*pIDBProperties			= NULL;
	ULONG			cPropSets				= 0;
	DBPROPSET		*rgPropSets				= NULL;
	WCHAR			wszFileName[_MAX_FNAME]	= L"\\ThisIsMyUDLFile.udl";
	CDSL_Dialog		Dialog;
	
	TESTC(Dialog.CreateUDLFile(wszFileName));
	TESTC(Dialog.SpawnUDLFile(wszFileName));
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.GotoProviderPage());
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.KillThread());

	// now use the file to get an IDBInitialize interface
	TESTC_(CreateFileMoniker(wszFileName, &pIMoniker), S_OK);
	TESTC_(CreateBindCtx(0 /*reserved*/, &piBindCtx), S_OK);
	TESTC_(pIMoniker->BindToObject(piBindCtx, NULL, IID_IDBInitialize, (LPVOID*)&pIDBInitialize), S_OK);

	// set properties
	// Get IDBProperties Pointer
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));
	// Setup the arrays needed for init, based on string LTM passed to us
	TESTC(GetInitProps(&cPropSets, &rgPropSets));
	// Set the properties before we Initialize, only if we have Properties to set...
	TESTC_(pIDBProperties->SetProperties(cPropSets, rgPropSets),S_OK);
	// Initialize
	TESTC_(pIDBInitialize->Initialize(), S_OK);

	// the last argument is TRUE to indicate that the DSO is initialized
	TESTC(DefaultObjectTesting(pIDBInitialize, DATASOURCE_INTERFACE, TRUE));

CLEANUP:
	FreeProperties(&cPropSets, &rgPropSets);
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIMoniker);
	SAFE_RELEASE(piBindCtx);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Pop up 2 dialogs simultaneoysly
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CGenericOp::Variation_4()
{ 
	TBEGIN
	TRETURN
	IDBProperties	*pIDBProperties		= NULL;
	IDBProperties	*pIDBProperties2	= NULL;
	CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd,
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL,
		IID_IDBProperties, (IUnknown**)&pIDBProperties);
	Sleep(2000);
	CDSL_Dialog		Dialog2(m_pIDBPromptInitialize, NULL, s_hMainWnd,
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL,
		IID_IDBProperties, (IUnknown**)&pIDBProperties2);
	Sleep(2000);
	CDSL_Dialog		Dialog3(g_wszUDLFileName);
	CDSL_Dialog		Dialog4;
	WCHAR			wszUDLFileName[]	= L"newone.udl";
	WCHAR			*pwszUserID1		= L"Nono";
	WCHAR			*pwszUserID2		= L"ASDN";
	WCHAR			*pwszUserID			= NULL;

	Sleep(2000);
	TESTC(Dialog4.CreateUDLFile(wszUDLFileName));
	TESTC(Dialog4.SpawnUDLFile(wszUDLFileName));

	odtLog << "Test all dialogs are up\n";
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog2.IsInExecution());
	TESTC(Dialog3.IsInExecution());
	TESTC(Dialog4.IsInExecution());

	Dialog.Activate();
	TESTC(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetUserID(pwszUserID1));
	Sleep(2000);

	Dialog2.Activate();
	TESTC(Dialog2.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog2.GotoConnectionPage());
	TESTC(Dialog2.SetUserID(pwszUserID2));
	Sleep(2000);

	odtLog << "Bring down the fourth dialog\n";
	TESTC(Dialog4.KillThread());

	odtLog << "Bring down the third dialog\n";
	TESTC(Dialog3.KillThread());

	odtLog << "Bring down the second dialog\n";
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

	odtLog << "Bring down the first dialog\n";
	TESTC(Dialog2.KillThread());
	TESTC(Dialog2.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_AUTH_USERID, DBPROPSET_DBINIT, pIDBProperties, &pwszUserID));
	TESTC(pwszUserID && 0 == wcscmp(pwszUserID, pwszUserID1));
	SAFE_FREE(pwszUserID);
	TESTC(GetProperty(DBPROP_AUTH_USERID, DBPROPSET_DBINIT, pIDBProperties2, &pwszUserID));
	TESTC(pwszUserID && 0 == wcscmp(pwszUserID, pwszUserID2));

CLEANUP:
	SAFE_FREE(pwszUserID);
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIDBProperties2);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END



// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL CGenericOp::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(CPromptFileName)
//*-----------------------------------------------------------------------
//| Test Case:		CPromptFileName - Test variations on IDBPromptInitialize::PromptFileName
//| Created:  	3/29/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL CPromptFileName::Init()
{ 
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		// TO DO:  Add your own code here 
		return TRUE;
	} 
	return FALSE;
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Unsupported prompt options => E_INVALIDARG
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_1()
{ 
	TBEGIN
	DBPROMPTOPTIONS		dwPromptOptions;
	WCHAR				*pwszSelectedFile = NULL;
	CDSL_FileDialog		Dialog;
	
	for (dwPromptOptions=1; dwPromptOptions; dwPromptOptions *= 2)
	{
		if (dwPromptOptions & DBPROMPTOPTIONS_BROWSEONLY)
			continue;

		// execute the scenario
		TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			dwPromptOptions, NULL, NULL, &pwszSelectedFile));
		
		TESTC(Dialog.IsResult(E_INVALIDARG));
		TESTC(NULL == pwszSelectedFile);
	}

CLEANUP:
	TOUTPUT_IF_FAILED(dwPromptOptions);
	SAFE_FREE(pwszSelectedFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc DBPROMPTOPTIONS_BROWSEONLY
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_2()
{ 
	TBEGIN
	WCHAR				*pwszSelectedFile = NULL;
	CDSL_FileDialog		Dialog;
	
	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			DBPROMPTOPTIONS_BROWSEONLY, NULL, NULL, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread(IDCANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pwszSelectedFile);

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Cancel the dialog => DB_E_CANCELED
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_3()
{ 
	TBEGIN
	WCHAR				*pwszSelectedFile = NULL;
	CDSL_FileDialog		Dialog;
	
	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, NULL, NULL, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread(IDCANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pwszSelectedFile);

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Use a valid initial path name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_4()
{ 
	TBEGIN
	WCHAR				*pwszSelectedFile = NULL;
	CDSL_FileDialog		Dialog;
	WCHAR				wszCrtPath[cMaxName]	= L"";

	TESTC_PROVIDER(NULL != _wgetcwd(wszCrtPath, cMaxName));

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, wszCrtPath, NULL, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread(IDCANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pwszSelectedFile);

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Use an inexistent initial path (make sure that the dialog still appears)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_5()
{ 
	TBEGIN
	WCHAR				wszInexistentPath[] = L"c:\\probably.inexistent";
	WCHAR				*pwszSelectedFile	= NULL;
	CDSL_FileDialog		Dialog;
	
	// make sure the path doesn't exist
	TESTC_PROVIDER(-1 == _wchdir(wszInexistentPath));

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, wszInexistentPath, NULL, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread(IDCANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pwszSelectedFile);

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc Initial directory has no read permission
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_6()
{ 
	TBEGIN
	WCHAR				*pwszSelectedFile		= NULL;
	WCHAR				wszInitialDirectory[]	= L"\\\\FictiveMachine\\FictiveDir";
	CDSL_FileDialog		Dialog;

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, wszInitialDirectory, NULL, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread(IDCANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pwszSelectedFile);

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc Long initial directory name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_7()
{ 
	TBEGIN
	WCHAR				*pwszSelectedFile				= NULL;
	WCHAR				wszInitialDirectory[_MAX_DIR]	= L"c:\\";
	CDSL_FileDialog		Dialog;
	ULONG				cLen;
	ULONG				cTNLen;
	CTable				Table(m_pThisTestModule->m_pIUnknown2, (LPWSTR)gwszModuleName);
	
	// prepare a long localized name
	TESTC_(Table.MakeTableName(NULL), S_OK);
	cTNLen = wcslen(Table.GetTableName());
	if (cTNLen < _MAX_PATH/sizeof(WCHAR))
		wcscat(wszInitialDirectory, Table.GetTableName());
	for (cLen=wcslen(wszInitialDirectory); cLen+cTNLen < _MAX_PATH/sizeof(WCHAR); cLen += cTNLen)
	{
		wcscat(wszInitialDirectory, Table.GetTableName());
	}
	for (;cLen < _MAX_PATH/sizeof(WCHAR); cLen++)
	{
		wcscat(wszInitialDirectory, L"a");
	}

	odtLog << "Initial directory is: " << wszInitialDirectory << "\n";

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, wszInitialDirectory, NULL, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread(IDCANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pwszSelectedFile);

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Directory is not local (UNC)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_8()
{ 
	TBEGIN
	WCHAR				wszInitialDirectory[]	= L"\\\\oledbsrv1\\drops";
	WCHAR				*pwszSelectedFile		= NULL;
	CDSL_FileDialog		Dialog;
	WCHAR				wszCrtPath[_MAX_PATH]	= L"";

	TESTC(NULL != _wgetcwd(wszCrtPath, _MAX_PATH));

	// make sure the path doesn't exist
	TESTC_PROVIDER(-1 != _wchdir(wszInitialDirectory));

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, wszInitialDirectory, NULL, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread(IDCANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pwszSelectedFile);

CLEANUP:
	COMPARE(-1 != _wchdir(wszCrtPath), TRUE);
	SAFE_FREE(pwszSelectedFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Good initial file name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_9()
{ 
	TBEGIN
	WCHAR				wszInitialFile[]		= L"MyUDLFile.udl";
	WCHAR				*pwszSelectedFile		= NULL;
	CDSL_FileDialog		Dialog;
	WCHAR				wszFName[_MAX_FNAME]	= L"";
	WCHAR				wszExt[_MAX_EXT]		= L"";

	TESTC(Dialog.CreateUDLFile(wszInitialFile));

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, NULL, wszInitialFile, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread(IDOK));
	TESTC(Dialog.IsResult(S_OK));

	// get the file name
	_wsplitpath(pwszSelectedFile, NULL, NULL, wszFName, wszExt);
	wcscat(wszFName, wszExt);

	// check it's the same name
	TESTC(0 == wcscmp(wszFName, wszInitialFile));

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	_wremove(wszInitialFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc Long initial file name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_10()
{ 
	TBEGIN
	WCHAR				*pwszSelectedFile				= NULL;
	WCHAR				wszInitialFileName[_MAX_FNAME]	= L"";
	CDSL_FileDialog		Dialog;
	ULONG				cLen;
	ULONG				cTNLen;
	CTable				Table(m_pThisTestModule->m_pIUnknown2, (LPWSTR)gwszModuleName);
	
	// prepare a long localized name
	TESTC_(Table.MakeTableName(NULL), S_OK);
	cTNLen = wcslen(Table.GetTableName());
	if (cTNLen < _MAX_FNAME/sizeof(WCHAR))
		wcscat(wszInitialFileName, Table.GetTableName());
	for (cLen=wcslen(wszInitialFileName); cLen+cTNLen < _MAX_FNAME/sizeof(WCHAR); cLen += cTNLen)
	{
		wcscat(wszInitialFileName, Table.GetTableName());
	}
	for (;cLen < _MAX_FNAME/sizeof(WCHAR); cLen++)
	{
		wcscat(wszInitialFileName, L"a");
	}

	odtLog << "Initial file is: " << wszInitialFileName << "\n";

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, NULL, wszInitialFileName, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread(IDCANCEL));
	TESTC(Dialog.IsResult(DB_E_CANCELED));
	TESTC(NULL == pwszSelectedFile);

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(11)
//*-----------------------------------------------------------------------
// @mfunc Invalid file name (e.g. c:/\\/\\/file)
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_11()
{ 
	TBEGIN
	WCHAR				wszInitialFile[]	= L"c:/\\/\\/file";
	WCHAR				*pwszSelectedFile	= NULL;
	CDSL_FileDialog		Dialog;
	
	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, NULL, wszInitialFile, &pwszSelectedFile));

	TESTC(Dialog.IsResult(STG_E_FILENOTFOUND));
	TESTC(NULL == pwszSelectedFile);

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(12)
//*-----------------------------------------------------------------------
// @mfunc NULL ppwszSelectedFile
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_12()
{ 
	TBEGIN
	CDSL_FileDialog		Dialog;
	
	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, NULL, NULL, NULL));

	TESTC(Dialog.IsResult(E_INVALIDARG));

CLEANUP:
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(13)
//*-----------------------------------------------------------------------
// @mfunc Pass both initial file name and initial directory
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_13()
{ 
	TBEGIN
	WCHAR				wszInitialFile[]		= L"MyUDLFile.udl";
	WCHAR				*pwszSelectedFile		= NULL;
	CDSL_FileDialog		Dialog;
	WCHAR				wszFName[_MAX_FNAME]	= L"";
	WCHAR				wszExt[_MAX_EXT]		= L"";
	WCHAR				wszDrive[_MAX_DRIVE]	= L"";
	WCHAR				wszDir[_MAX_DIR+_MAX_DRIVE]		= L"";
	WCHAR				wszCrtPath[_MAX_DIR+_MAX_DRIVE]	= L"";	
	TESTC(Dialog.CreateUDLFile(wszInitialFile));

	// get the current path for the default driver
	TESTC(NULL != _wgetcwd(wszCrtPath, _MAX_DIR+_MAX_DRIVE));

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, wszCrtPath, wszInitialFile, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread(IDOK));
	TESTC(Dialog.IsResult(S_OK));

	// get the file name
	_wsplitpath(pwszSelectedFile, wszDrive, wszDir, wszFName, wszExt);
	wcscat(wszFName, wszExt);
	wcscat(wszDrive, wszDir); 
	wcscat(wszCrtPath, L"\\");

	// check it's the same name
	TESTC(0 == wcscmp(wszFName, wszInitialFile));
	TESTC(0 == wcscmp(wszDrive, wszCrtPath));

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	_wremove(wszInitialFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(14)
//*-----------------------------------------------------------------------
// @mfunc Valid UDL and select it through IDBPromptInitialize::PromptFileName
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_14()
{ 
	TBEGIN
	WCHAR				wszInitialFile[]		= L"MyUDLFile.udl";
	WCHAR				*pwszSelectedFile		= NULL;
	CDSL_FileDialog		Dialog;
	WCHAR				wszCrtPath[_MAX_DIR+_MAX_DRIVE]	= L"";	
	WCHAR				wszUDLFile[cMaxName]	= L"";

	// get the current path for the default driver
	TESTC_PROVIDER(NULL != _wgetcwd(wszCrtPath, _MAX_DIR+_MAX_DRIVE));

	wcscpy(wszUDLFile, wszCrtPath);
	wcscat(wszUDLFile, L"\\");
	wcscat(wszUDLFile, wszInitialFile);

	TESTC(Dialog.CreateUDLFile(wszUDLFile));

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, NULL, wszUDLFile, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.KillThread(IDOK));
	TESTC(Dialog.IsResult(S_OK));

	// check it's the same name
	TESTC(0 == wcscmp(wszUDLFile, pwszSelectedFile));

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	_wremove(wszInitialFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END





// {{ TCW_VAR_PROTOTYPE(15)
//*-----------------------------------------------------------------------
// @mfunc Spaces leading and trailing a file name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_15()
{ 
	TBEGIN
	WCHAR				wszInitialFile[]		= L"M,+yU{DL==Fil[]e.udl";
	WCHAR				wszFileName[]			= L"    M,+yU{DL==Fil[]e.udl  ";
	WCHAR				*pwszSelectedFile		= NULL;
	CDSL_FileDialog		Dialog;
	WCHAR				wszFName[_MAX_FNAME]	= L"";
	WCHAR				wszExt[_MAX_EXT]		= L"";

	TESTC(Dialog.CreateUDLFile(wszInitialFile));

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, NULL, wszFileName, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	Sleep(2000);
	TESTC(Dialog.KillThread(IDOK));
	TESTC(Dialog.IsResult(S_OK));

	// get the file name
	_wsplitpath(pwszSelectedFile, NULL, NULL, wszFName, wszExt);
	wcscat(wszFName, wszExt);

	// check it's the same name
	TESTC(0 == wcscmp(wszFName, wszInitialFile));

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, NULL, NULL, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SetFileName(wszFileName));
	TESTC(Dialog.KillThread(IDOK));
	TESTC(Dialog.IsResult(S_OK));

	// get the file name
	_wsplitpath(pwszSelectedFile, NULL, NULL, wszFName, wszExt);
	wcscat(wszFName, wszExt);

	// check it's the same name
	TESTC(0 == wcscmp(wszFName, wszInitialFile));
CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	_wremove(wszInitialFile);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(16)
//*-----------------------------------------------------------------------
// @mfunc Special characters in a file name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_16()
{ 
	TBEGIN
	WCHAR				*rgwszInitialFile[]		= {
							L"M,+yU{DL==Fil[]e.udl",
							L"ce{va}}.udl",
							L"spa  ces.udl",
							L"{]leading spec=chrs.udl",
						};
	ULONG				cInitialFile = NUMELEM(rgwszInitialFile);
	WCHAR				*pwszSelectedFile		= NULL;
	CDSL_FileDialog		Dialog;
	WCHAR				wszFName[_MAX_FNAME]	= L"";
	WCHAR				wszExt[_MAX_EXT]		= L"";
	ULONG				index;

	for (index = 0; index < cInitialFile; index++)
	{
		odtLog << "Set file name: " << rgwszInitialFile[index] << "\n";

		TESTC(Dialog.CreateUDLFile(rgwszInitialFile[index]));

		// execute the scenario
		TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
				0, NULL, NULL, &pwszSelectedFile));

		TESTC(Dialog.IsInExecution());
		TESTC(Dialog.SetFileName(rgwszInitialFile[index]));
		TESTC(Dialog.KillThread(IDOK));
		TESTC(Dialog.IsResult(S_OK));

		// get the file name
		_wsplitpath(pwszSelectedFile, NULL, NULL, wszFName, wszExt);
		wcscat(wszFName, wszExt);

		// check it's the same name
		TESTC(0 == wcscmp(wszFName, rgwszInitialFile[index]));

CLEANUP:
		_wremove(rgwszInitialFile[index]);
		SAFE_FREE(pwszSelectedFile);
	}
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(17)
//*-----------------------------------------------------------------------
// @mfunc UNC file name
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_17()
{ 
	TBEGIN
	WCHAR				wszFileName[cMaxName] = L"\\\\";
	WCHAR				*pwszSelectedFile		= NULL;
	CDSL_FileDialog		Dialog;
	DWORD				nSize = cMaxName;

	TESTC(0 != GetComputerNameW(wszFileName+2, &nSize));
	wcscat(wszFileName, L"\\c$\\a file.udl");
	odtLog << "UDL File: " << wszFileName << "\n";

	TESTC(Dialog.CreateUDLFile(wszFileName));

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, NULL, NULL, &pwszSelectedFile));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.SetFileName(wszFileName));
	TESTC(Dialog.KillThread(IDOK));
	TESTC(Dialog.IsResult(S_OK));

	// check it's the same name
	TESTC(0 == wcscmp(pwszSelectedFile, wszFileName));

CLEANUP:
	SAFE_FREE(pwszSelectedFile);
	_wremove(wszFileName);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




BOOL CPromptFileName::CommonScenario(
	WCHAR	*pwszInitialFileName,		// [in] 
	WCHAR	*pwszSelectFileName,		// [in]
	WCHAR	**ppwszSelectedFileName		// [out]
)
{
	TBEGIN
	CDSL_FileDialog		Dialog;
	WCHAR				wszFName[_MAX_FNAME]	= L"";
	WCHAR				wszExt[_MAX_EXT]		= L"";
	WCHAR				wszCrtPath[_MAX_DIR+_MAX_DRIVE]	= L"";	

	// get the current path for the default driver
	TESTC(NULL != _wgetcwd(wszCrtPath, _MAX_DIR+_MAX_DRIVE));

	TESTC(NULL != ppwszSelectedFileName);

	// execute the scenario
	TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
			0, wszCrtPath, pwszInitialFileName, ppwszSelectedFileName));

	TESTC(Dialog.IsInExecution());
	Sleep(1000);
	if (pwszSelectFileName)
		TESTC(Dialog.SetFileName(pwszSelectFileName));
	TESTC(Dialog.KillThread(IDOK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(NULL != *ppwszSelectedFileName);
	// get the file name
	_wsplitpath(*ppwszSelectedFileName, NULL, NULL, wszFName, wszExt);
	wcscat(wszFName, wszExt);

	// check it's the same name
	TESTC(0 == wcscmp(wszFName, pwszSelectFileName? pwszSelectFileName: pwszInitialFileName));

CLEANUP:
	TRETURN
} //CPromptFileName::CommonScenario




BOOL CPromptFileName::Common_ANSI_OEM_Scenario(
	BOOL	fUseANSIToCreateUDLFile,
	BOOL	fUseANSIToPopUpDialog
)
{
	TBEGIN
	// Currency symbol, English Pound (different on ANSI and OEM)
	WCHAR				wch = 0x00A3;	
	WCHAR				wszInitialFileName[] = { wch, wch, wch, L'.', L'u', L'd', L'l', L'\0' } ;
	WCHAR				*pwszSelectedFile		= NULL;
	CDSL_FileDialog		Dialog;

	_wremove(wszInitialFileName);

	//Default is ANSI, (but just make sure)
	TESTC(AreFileApisANSI());

	//Make sure that the file name can actually be converted to ANSI.
	TESTC_PROVIDER( iswcharMappable(wch) );

	//(this is the default but just for completeness will will repeat here)
	if (fUseANSIToCreateUDLFile)
		SetFileApisToANSI();
	else
		SetFileApisToOEM();

	TESTC(Dialog.CreateUDLFile(wszInitialFileName));

	if (fUseANSIToPopUpDialog)
		SetFileApisToANSI();
	else
		SetFileApisToOEM();
	
	TESTC(CommonScenario(NULL, wszInitialFileName, &pwszSelectedFile));
	SAFE_FREE(pwszSelectedFile);
	TESTC(CommonScenario(wszInitialFileName, NULL, &pwszSelectedFile));

CLEANUP:
	SetFileApisToANSI();
	_wremove(wszInitialFileName);
	SAFE_FREE(pwszSelectedFile);
	TRETURN
} //CPromptFileName::Common_ANSI_OEM_Scenario




// {{ TCW_VAR_PROTOTYPE(18)
//*-----------------------------------------------------------------------
// @mfunc ANSI -> ANSI
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_18()
{ 
	return Common_ANSI_OEM_Scenario(TRUE, TRUE);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(19)
//*-----------------------------------------------------------------------
// @mfunc OEM -> OEM
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_19()
{ 
	return Common_ANSI_OEM_Scenario(FALSE, FALSE);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(20)
//*-----------------------------------------------------------------------
// @mfunc ANSI -> OEM
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_20()
{ 
	return Common_ANSI_OEM_Scenario(TRUE, FALSE);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(21)
//*-----------------------------------------------------------------------
// @mfunc OEM -> ANSI
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_21()
{ 
	return Common_ANSI_OEM_Scenario(FALSE, TRUE);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(22)
//*-----------------------------------------------------------------------
// @mfunc ANSI/OEM API combinations for the initial directory
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CPromptFileName::Variation_22()
{ 
	TBEGIN
	// Currency symbol, English Pound (different on ANSI and OEM)
	WCHAR				wch = 0x00A3;	
	WCHAR				wszDirectory[]		= { wch, wch, L'c', L'\0'};
	CHAR				*pszDirectory		= NULL;
	WCHAR				wszUDLFN[]			= L"ceva.udl";
	WCHAR				wszUDLFileName[cMaxName]	= L"" ;
	WCHAR				*pwszSelectedFileName	= NULL;
	CDSL_FileDialog		Dialog;
	BOOL				fUseANSIToCreateInitDir;
	BOOL				fUseANSIToPopUpDialog;
	WCHAR				wszPath[cMaxName]	= L"";
	ULONG				index;
	WCHAR				wszFName[_MAX_FNAME]= L"";
	WCHAR				wszExt[_MAX_EXT]	= L"";
	WCHAR				wszCrtPath[_MAX_DIR+_MAX_DRIVE]	= L"";	

	//Default is ANSI, (but just make sure)
	TESTC(AreFileApisANSI());

	// TODO: Use ANSI function _getcwd if running on Win9x, Mill.
	TESTC_PROVIDER(NULL != _wgetcwd(wszCrtPath, cMaxName));
	wcscat(wszPath, wszCrtPath);
	wcscat(wszPath, L"\\");
	wcscat(wszPath, wszDirectory);

	for (index=0; index < 4; index++)
	{

		fUseANSIToCreateInitDir = index % 2;
		fUseANSIToPopUpDialog	= index / 2 % 2;

		//Make sure that the file name can actually be converted to ANSI.
		TESTC_PROVIDER( iswcharMappable(wch) );

		//(this is the default but just for completeness will will repeat here)
		if (fUseANSIToCreateInitDir)
		{
			odtLog << "\t Use ANSI to create the init directory\n";
			SetFileApisToANSI();
		}
		else
		{
			odtLog << "\t Use OEM to create the init directory\n";
			SetFileApisToOEM();
		}

		// create the directory to be used as an initial one
		SAFE_FREE(pszDirectory);
		pszDirectory = ConvertToMBCS(wszDirectory, AreFileApisANSI() ? CP_ACP : CP_OEMCP);
		// user might be prevented to write into the current directory
		_rmdir(pszDirectory);
		if (0 != _mkdir(pszDirectory))
		{
			odtLog << strerror(errno) << "\n";
			if ( 0 != _rmdir(pszDirectory))
				odtLog << strerror(errno) << "\n";
			TESTC_PROVIDER(FALSE);
		}

		// create the UDL file
		wcscpy(wszUDLFileName, wszPath);
		wcscat(wszUDLFileName, L"\\");
		wcscat(wszUDLFileName, wszUDLFN);
		TESTC(Dialog.CreateUDLFile(wszUDLFileName));

		if (fUseANSIToPopUpDialog)
		{
			odtLog << "\t Use ANSI to pop up the dialog\n";
			SetFileApisToANSI();
		}
		else
		{
			odtLog << "\t Use OEM to pop up the dialog\n";
			SetFileApisToOEM();
		}

		// execute the scenario
		TESTC(Dialog.SpawnPromptFileName(m_pIDBPromptInitialize, s_hMainWnd, 
				0, wszPath, NULL, &pwszSelectedFileName));

		TESTC(Dialog.IsInExecution());
		Sleep(1000);
		TESTC(Dialog.SetFileName(wszUDLFileName));
		TESTC(Dialog.KillThread(IDOK));
		TESTC(Dialog.IsResult(S_OK));

		_wchdir(wszCrtPath);

		TESTC(NULL != pwszSelectedFileName);
		// get the file name
		_wsplitpath(pwszSelectedFileName, NULL, NULL, wszFName, wszExt);
		wcscat(wszFName, wszExt);

		// check it's the same name
		TESTC(0 == wcscmp(wszFName, wszUDLFN));

		SAFE_FREE(pwszSelectedFileName);
		_wremove(wszUDLFileName);
		_rmdir(pszDirectory);
	}

CLEANUP:
	SetFileApisToANSI();
	_wremove(wszUDLFileName);
	if (pszDirectory)
		_rmdir(pszDirectory);
	SAFE_FREE(pwszSelectedFileName);
	SAFE_FREE(pszDirectory);
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL CPromptFileName::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END







// {{ TCW_TC_PROTOTYPE(AdvancedPage)
//*-----------------------------------------------------------------------
//| Test Case:		AdvancedPage - Tests the Advanced Page of the UI
//| Created:  	4/2/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL AdvancedPage::Init()
{ 
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		// TO DO:  Add your own code here 
		return TRUE;
	} 
	return FALSE;
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Set the Read flag
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_1()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= DB_MODE_READ;
	VARIANT				vValue;

	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc Set the Write flag
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_2()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= DB_MODE_WRITE;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc Set the ReadWrite flag
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_3()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= DB_MODE_READ | DB_MODE_WRITE;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc Set the Share Deny None flag
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_4()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= DB_MODE_READ | DB_MODE_WRITE | DB_MODE_SHARE_DENY_NONE;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc Set the Share Deny Read flag
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_5()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= DB_MODE_SHARE_DENY_READ;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc Set the Share Deny Write flag
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_6()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= DB_MODE_SHARE_DENY_WRITE;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc Set Read | Share Deny Read
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_7()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= DB_MODE_READ | DB_MODE_SHARE_DENY_READ;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc Set Read | Share Deny Read | ShareDeny Write
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_8()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= DB_MODE_READ | DB_MODE_SHARE_DENY_READ | DB_MODE_SHARE_DENY_WRITE;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc Set Read | Write | Share Deny Read
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_9()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= DB_MODE_READ | DB_MODE_WRITE | DB_MODE_SHARE_DENY_READ;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc Set Read | Write | Share Deny Read | ShareDeny Write
//Set Read | Write | Share Deny Read | ShareDeny Write
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_10()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= DB_MODE_READ | DB_MODE_WRITE | DB_MODE_SHARE_DENY_READ | DB_MODE_SHARE_DENY_WRITE;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(11)
//*-----------------------------------------------------------------------
// @mfunc Set access rights, move to All page, close
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_11()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= /*DB_MODE_SHARE_DENY_NONE | */DB_MODE_SHARE_DENY_READ;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.GotoAllPage());

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END





// {{ TCW_VAR_PROTOTYPE(12)
//*-----------------------------------------------------------------------
// @mfunc Set timeout value
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_12()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	LONG				lMode			= DB_MODE_SHARE_DENY_NONE | DB_MODE_READ;
	LONG				lTimeout		= 102;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	// see bug 36346

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));

	TESTC(Dialog.SetInitTimeout(lTimeout));
	Sleep(2000);
	TESTC(Dialog.GotoAllPage());

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_TIMEOUT, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lTimeout == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(13)
//*-----------------------------------------------------------------------
// @mfunc Set impersonation level to Anonymous
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_13()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	LONG				lMode				= DB_MODE_SHARE_DENY_NONE | DB_MODE_READ;
	LONG				lImpersonationLevel	= DB_IMP_LEVEL_ANONYMOUS;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDataShape));
	// see bug 36346

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetImpersonationLevel(lImpersonationLevel));
	Sleep(2000);

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_IMPERSONATION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lImpersonationLevel == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(14)
//*-----------------------------------------------------------------------
// @mfunc Set impersonation level to Delegate
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_14()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	LONG				lMode				= DB_MODE_SHARE_DENY_NONE | DB_MODE_READ;
	LONG				lImpersonationLevel	= DB_IMP_LEVEL_DELEGATE;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDataShape));
	// see bug 36346

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetImpersonationLevel(lImpersonationLevel));
	Sleep(2000);

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_IMPERSONATION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lImpersonationLevel == V_I4(&vValue));

//	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(15)
//*-----------------------------------------------------------------------
// @mfunc Set impersonation level to Identify
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_15()
{ 
	TBEGIN
	HRESULT				hr;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	LONG				lMode				= DB_MODE_SHARE_DENY_NONE | DB_MODE_READ;
	LONG				lImpersonationLevel	= DB_IMP_LEVEL_IDENTIFY;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDataShape));
	// see bug 36346

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetImpersonationLevel(lImpersonationLevel));
	Sleep(2000);

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_IMPERSONATION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lImpersonationLevel == V_I4(&vValue));

//	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	hr = Dialog.GetExpectedInitialize();
	TESTC_(pIDBInitialize->Initialize(), hr);
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(16)
//*-----------------------------------------------------------------------
// @mfunc Set impersonation level to Impersonate
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_16()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	LONG				lMode				= DB_MODE_SHARE_DENY_NONE | DB_MODE_READ;
	LONG				lImpersonationLevel	= DB_IMP_LEVEL_IMPERSONATE;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDataShape));
	// see bug 36346

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetImpersonationLevel(lImpersonationLevel));
	Sleep(2000);

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_IMPERSONATION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lImpersonationLevel == V_I4(&vValue));
	
CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(17)
//*-----------------------------------------------------------------------
// @mfunc Set protection level to Call
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_17()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	LONG				lMode				= DB_MODE_SHARE_DENY_NONE | DB_MODE_READ;
	LONG				lProtectionLevel	= DB_PROT_LEVEL_CALL;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDataShape));
	// see bug 36346

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(18)
//*-----------------------------------------------------------------------
// @mfunc Set protection level to Connect
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_18()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	LONG				lMode				= DB_MODE_SHARE_DENY_NONE | DB_MODE_READ;
	LONG				lProtectionLevel	= DB_PROT_LEVEL_CONNECT;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDataShape));
	// see bug 36346

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(19)
//*-----------------------------------------------------------------------
// @mfunc Set protection level to None
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_19()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	LONG				lMode				= DB_MODE_SHARE_DENY_NONE | DB_MODE_READ;
	LONG				lProtectionLevel	= DB_PROT_LEVEL_NONE;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDataShape));
	// see bug 36346

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(20)
//*-----------------------------------------------------------------------
// @mfunc Set protection level to Pkt
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_20()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	LONG				lMode				= DB_MODE_SHARE_DENY_NONE | DB_MODE_READ;
	LONG				lProtectionLevel	= DB_PROT_LEVEL_PKT;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDataShape));
	// see bug 36346

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(21)
//*-----------------------------------------------------------------------
// @mfunc Set protection level to Pkt Integrity
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_21()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	LONG				lMode				= DB_MODE_SHARE_DENY_NONE | DB_MODE_READ;
	LONG				lProtectionLevel	= DB_PROT_LEVEL_PKT_INTEGRITY;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDataShape));
	// see bug 36346

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(22)
//*-----------------------------------------------------------------------
// @mfunc Set protection level to Pkt Privacy
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int AdvancedPage::Variation_22()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	LONG				lMode				= DB_MODE_SHARE_DENY_NONE | DB_MODE_READ;
	LONG				lProtectionLevel	= DB_PROT_LEVEL_PKT_PRIVACY;
	VARIANT				vValue;
	
	VariantInit(&vValue);
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDataShape));
	// see bug 36346

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL AdvancedPage::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(CSummaryPage)
//*-----------------------------------------------------------------------
//| Test Case:		CSummaryPage - test the summary page of the dialog
//| Created:  	6/8/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL CSummaryPage::Init()
{ 
	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		// TO DO:  Add your own code here 
		return TRUE;
	} 
	return FALSE;
} 




BOOL CSummaryPage::SetRandProp(VARTYPE vtType)
{
	TBEGIN
	WCHAR				wszValue[cMaxName];

	TESTC(CDSL_Dialog::BuildRandomValue(vtType, wszValue));
	return SetSummaryProp(vtType, wszValue);

CLEANUP:
	TRETURN
} //CSummaryPage::SetRandProp




BOOL CSummaryPage::SetSummaryProp(VARIANT *pValue)
{
	TBEGIN
	VARIANT			PropVal;

	VariantInit(&PropVal);
	TESTC(NULL != pValue);

	VariantCopy(&PropVal, pValue);
	
	TESTC_(VariantChangeType(&PropVal, &PropVal, VARIANT_NOVALUEPROP, VT_BSTR), S_OK);
	SetSummaryProp(pValue->vt, V_BSTR(&PropVal));

CLEANUP:
	VariantClear(&PropVal);
	TRETURN
} //CSummaryPage::SetSummaryProp




BOOL CSummaryPage::SetSummaryProp(VARTYPE vType, WCHAR *pwszValue)
{
	TBEGIN
	DBPROPINFO			*pPropInfo;
	GUID				guidPropSet;
	GUID				guidProvider;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	ULONG				cProperties		= 0;
	WCHAR				**rgProperties	= NULL;
	const ULONG			cExclProp		= 7;
	DBPROPID			rgExclPropID[cExclProp] = {
								DBPROP_INIT_MODE, 
								DBPROP_INIT_IMPERSONATION_LEVEL, 
								DBPROP_INIT_PROTECTION_LEVEL,
								DBPROP_INIT_OLEDBSERVICES,
								DBPROP_INIT_HWND,
								DBPROP_INIT_PROMPT,
								DBPROP_INIT_ASYNCH,
						};
	GUID				rgExclPropSet[cExclProp];

	TESTC(NULL != pwszValue);

	rgExclPropSet[0] = DBPROPSET_DBINIT;
	rgExclPropSet[1] = DBPROPSET_DBINIT;
	rgExclPropSet[2] = DBPROPSET_DBINIT;
	rgExclPropSet[3] = DBPROPSET_DBINIT;
	rgExclPropSet[4] = DBPROPSET_DBINIT;
	rgExclPropSet[5] = DBPROPSET_DBINIT;
	rgExclPropSet[6] = DBPROPSET_DBINIT;

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());

	TESTC_PROVIDER(Dialog.s_pSourcesSet->FindProperty(vType, 
		&pPropInfo, &guidPropSet, &guidProvider,
		cExclProp, rgExclPropID, rgExclPropSet));

	TESTC_PROVIDER(Dialog.SelectProvider(guidProvider));

	TESTC(Dialog.GotoAllPage());
	Sleep(100);

	TESTC(Dialog.SetProperty(pPropInfo, guidPropSet, pwszValue));

CLEANUP:
	TRETURN
} //CSummaryPage::SetSummaryProp




BOOL CSummaryPage::SetAndResetProp(VARTYPE vtType)
{
	TBEGIN
	WCHAR				wszValue[cMaxName];
	DBPROPINFO			*pPropInfo;
	GUID				guidPropSet;
	GUID				guidProvider;
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	ULONG				cProperties		= 0;
	WCHAR				**rgProperties	= NULL;
	const ULONG			cExclProp		= 7;
	DBPROPID			rgExclPropID[cExclProp] = {
								DBPROP_INIT_MODE, 
								DBPROP_INIT_IMPERSONATION_LEVEL, 
								DBPROP_INIT_PROTECTION_LEVEL,
								DBPROP_INIT_OLEDBSERVICES,
								DBPROP_INIT_HWND,
								DBPROP_INIT_PROMPT,
								DBPROP_INIT_ASYNCH,
						};
	GUID				rgExclPropSet[cExclProp];

	rgExclPropSet[0] = DBPROPSET_DBINIT;
	rgExclPropSet[1] = DBPROPSET_DBINIT;
	rgExclPropSet[2] = DBPROPSET_DBINIT;
	rgExclPropSet[3] = DBPROPSET_DBINIT;
	rgExclPropSet[4] = DBPROPSET_DBINIT;
	rgExclPropSet[5] = DBPROPSET_DBINIT;
	rgExclPropSet[6] = DBPROPSET_DBINIT;

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());

	TESTC_PROVIDER(Dialog.s_pSourcesSet->FindProperty(vtType, 
		&pPropInfo, &guidPropSet, &guidProvider,
		cExclProp, rgExclPropID, rgExclPropSet));

	TESTC_PROVIDER(Dialog.SelectProvider(guidProvider));

	TESTC(Dialog.GotoAllPage());
	Sleep(100);


	// set the property to some value
	TESTC(CDSL_Dialog::BuildRandomValue(vtType, wszValue));
	TESTC(Dialog.SetProperty(pPropInfo, guidPropSet, wszValue));

	// reset the property
	TESTC(Dialog.ResetProperty(pPropInfo, guidPropSet));

CLEANUP:
	TRETURN
} //CSummaryPage::SetAndResetProp



// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Set some property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_1()
{ 
	TBEGIN
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize	= NULL;
	ULONG				cProperties		= 0;
	WCHAR				**rgProperties	= NULL;
	ULONG				cIndex;

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	TESTC_PROVIDER(Dialog.SelectProvider(CLSID_MSDASQL));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(L"Some initial name"));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAllPage());
	Sleep(1000);

	// set all the properties
	TESTC(Dialog.GetListOfProperties(&cProperties, &rgProperties));
	for (cIndex = 0; cIndex < cProperties; cIndex++)
	{
		COMPARE(Dialog.SetRandValForProp(rgProperties[cIndex]), TRUE);
	}

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

CLEANUP:
	for (cIndex = 0; cIndex < cProperties; cIndex++)
	{
		SAFE_FREE(rgProperties[cIndex]);
	}
	SAFE_FREE(rgProperties);
	SAFE_RELEASE(pIDBInitialize);	
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END





// {{ TCW_VAR_PROTOTYPE(2)
//*-----------------------------------------------------------------------
// @mfunc VT_I1 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_2()
{ 
	TBEGIN
	VARIANT	Variant;
	
	VariantInit(&Variant);
	Variant.vt = VT_I1;
	
	// set a random value
	TESTC_PROVIDER( TEST_PASS == SetRandProp(VT_I1));

	// minimal value
	V_I1(&Variant) = SCHAR_MIN;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// intermediate value
	V_I1(&Variant) = 0;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// maximal value
	V_I1(&Variant) = SCHAR_MAX;
	COMPARE(SetSummaryProp(&Variant), TRUE);

CLEANUP:
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(3)
//*-----------------------------------------------------------------------
// @mfunc VT_UI1 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_3()
{ 
	TBEGIN
	VARIANT	Variant;
	
	VariantInit(&Variant);
	Variant.vt = VT_UI1;
	
	// set a random value
	TESTC_PROVIDER( TEST_PASS == SetRandProp(VT_UI1));

	// minimal 0
	V_UI1(&Variant) = 0;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// intermediate value
	V_UI1(&Variant) = UCHAR_MAX/2;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// maximal value
	V_UI1(&Variant) = UCHAR_MAX;
	COMPARE(SetSummaryProp(&Variant), TRUE);

CLEANUP:
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(4)
//*-----------------------------------------------------------------------
// @mfunc VT_I2 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_4()
{ 
	TBEGIN
	VARIANT	Variant;
	
	VariantInit(&Variant);
	Variant.vt = VT_I2;
	
	// set a random value
	TESTC_PROVIDER( TEST_PASS == SetRandProp(VT_I2));

	// minimal value
	V_I2(&Variant) = SHRT_MIN;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// value out of I1 range
	V_I2(&Variant) = (SHORT)SCHAR_MIN - 1 - rand() % (SHRT_MAX - SCHAR_MAX);
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// and in I1 range, too
	V_I2(&Variant) = (SHORT)SCHAR_MIN + rand() % UCHAR_MAX;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// value out of I1 range
	V_I2(&Variant) = (SHORT)SCHAR_MAX + 1 + rand() % (SHRT_MAX - SCHAR_MAX);
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// maximal value
	V_I2(&Variant) = SHRT_MAX;
	COMPARE(SetSummaryProp(&Variant), TRUE);

CLEANUP:
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(5)
//*-----------------------------------------------------------------------
// @mfunc VT_UI2 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_5()
{ 
	TBEGIN
	VARIANT	Variant;
	
	VariantInit(&Variant);
	Variant.vt = VT_UI2;
	
	// set a random value
	TESTC_PROVIDER( TEST_PASS == SetRandProp(VT_UI2));

	// minimal value: 0
	V_UI2(&Variant) = 0;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// value in UI1 range
	V_UI2(&Variant) = rand() % UCHAR_MAX;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// value out of UI1 range
	V_UI2(&Variant) = (SHORT)UCHAR_MAX + 1 + rand() % (USHRT_MAX - UCHAR_MAX);
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// maximal value
	V_UI2(&Variant) = USHRT_MAX;
	COMPARE(SetSummaryProp(&Variant), TRUE);

CLEANUP:
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(6)
//*-----------------------------------------------------------------------
// @mfunc VT_I4 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_6()
{ 
	TBEGIN
	VARIANT	Variant;
	
	VariantInit(&Variant);
	Variant.vt = VT_I4;
	
	// set a random value
	TESTC_PROVIDER( TEST_PASS == SetRandProp(VT_I4));

	// minimal value
	V_I4(&Variant) = LONG_MIN;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// value outside I2 range
	V_I4(&Variant) = (LONG)SHRT_MIN - 1 - rand() % (LONG_MAX - SHRT_MAX);
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// and inside I2 range, too
	V_I4(&Variant) = (LONG)SHRT_MIN + rand() % ULONG_MAX;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// value outside I2 range
	V_I4(&Variant) = (LONG)SHRT_MAX + 1 + rand() % (LONG_MAX - SHRT_MAX);
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// maximal value
	V_I4(&Variant) = LONG_MAX;
	COMPARE(SetSummaryProp(&Variant), TRUE);

CLEANUP:
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(7)
//*-----------------------------------------------------------------------
// @mfunc VT_UI4 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_7()
{ 
	TBEGIN
	VARIANT	Variant;
	
	VariantInit(&Variant);
	Variant.vt = VT_UI4;
	
	// set a random value
	TESTC_PROVIDER( TEST_PASS == SetRandProp(VT_UI4));

	// minimal value: 0
	V_UI4(&Variant) = 0;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// value inside UI2 range
	V_UI4(&Variant) = rand() % USHRT_MAX;
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// value outside UI2 range
	V_UI4(&Variant) = (LONG)USHRT_MAX + 1 + rand() % (ULONG_MAX - USHRT_MAX);
	COMPARE(SetSummaryProp(&Variant), TRUE);

	// maximal value
	V_UI4(&Variant) = LONG_MAX;
	COMPARE(SetSummaryProp(&Variant), TRUE);

CLEANUP:
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(8)
//*-----------------------------------------------------------------------
// @mfunc VT_BSTR property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_8()
{ 
	return SetRandProp(VT_BSTR);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(9)
//*-----------------------------------------------------------------------
// @mfunc VT_R4 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_9()
{ 
	return SetRandProp(VT_R4);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(10)
//*-----------------------------------------------------------------------
// @mfunc VT_R8 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_10()
{ 
	return SetRandProp(VT_R8);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(11)
//*-----------------------------------------------------------------------
// @mfunc VT_CY property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_11()
{ 
	return SetRandProp(VT_CY);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(12)
//*-----------------------------------------------------------------------
// @mfunc VT_DATE property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_12()
{ 
	return SetRandProp(VT_DATE);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(13)
//*-----------------------------------------------------------------------
// @mfunc VT_BOOL property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_13()
{ 
	return SetRandProp(VT_BOOL);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(14)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_I1 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_14()
{ 
	return SetAndResetProp(VT_I1);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(15)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_UI1 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_15()
{ 
	return SetAndResetProp(VT_UI1);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(16)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_I2 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_16()
{ 
	return SetAndResetProp(VT_I2);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(17)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_UI2 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_17()
{ 
	return SetAndResetProp(VT_UI2);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(18)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_I4 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_18()
{ 
	return SetAndResetProp(VT_I4);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(19)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_UI4 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_19()
{ 
	return SetAndResetProp(VT_UI4);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(20)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_BSTR property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_20()
{ 
	return SetAndResetProp(VT_BSTR);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(21)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_R4 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_21()
{ 
	return SetAndResetProp(VT_R4);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(22)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_R8 property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_22()
{ 
	return SetAndResetProp(VT_R8);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(23)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_CY property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_23()
{ 
	return SetAndResetProp(VT_CY);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(24)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_DATE property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_24()
{ 
	return SetAndResetProp(VT_DATE);
} 
// }} TCW_VAR_PROTOTYPE_END




// {{ TCW_VAR_PROTOTYPE(25)
//*-----------------------------------------------------------------------
// @mfunc Reset a VT_BOOL property
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int CSummaryPage::Variation_25()
{ 
	return SetAndResetProp(VT_BOOL);
} 
// }} TCW_VAR_PROTOTYPE_END


// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL CSummaryPage::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


// {{ TCW_TC_PROTOTYPE(UDLSpecific)
//*-----------------------------------------------------------------------
//| Test Case:	UDLSpecific - Tests tailored for opening the DSL dialog using a udl file
//| Created:  	11/8/99
//*-----------------------------------------------------------------------

//*-----------------------------------------------------------------------
// @mfunc TestCase Initialization Routine
//
// @rdesc TRUE or FALSE
//
BOOL UDLSpecific::Init()
{ 
	TBEGIN

	TESTC(CPromptInitialize::Init());
	// make sure no SC is loaded
	// we want a new SC for each case (because of udl caching)
	TESTC(0 == CServiceComp::ReleaseSCInterface(m_pIDBPromptInitialize));

CLEANUP:
	m_pIDBPromptInitialize = NULL;
	TRETURN
} 




// {{ TCW_VAR_PROTOTYPE(1)
//*-----------------------------------------------------------------------
// @mfunc Create udl file, open it, set props, close it, reopen, close
//
// @rdesc TEST_PASS or TEST_FAIL 
//
int UDLSpecific::Variation_1()
{ 
	TBEGIN
	CDSL_Dialog		Dialog;
	CTable			Table(m_pThisTestModule->m_pIUnknown2, (LPWSTR)gwszModuleName);
	DBPROP			*pPropUserID	= NULL;
	DBPROP			*pPropPassword	= NULL;
	DBPROP			*pPropDataSource= NULL;
	
	pPropUserID = m_PropSets.FindProperty(DBPROP_AUTH_USERID, DBPROPSET_DBINIT);

	pPropPassword = m_PropSets.FindProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT);
	
	pPropDataSource = m_PropSets.FindProperty(DBPROP_INIT_DATASOURCE, DBPROPSET_DBINIT);

	TESTC(Dialog.CreateUDLFile(g_wszUDLFileName));

	TESTC(Dialog.SpawnUDLFile(g_wszUDLFileName));

	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.IsCurrentPage(g_nConnection));
	TESTC(Dialog.GotoProviderPage());

	TESTC(Dialog.SelectProvider(m_ProviderCLSID));

	TESTC(Dialog.IsCurrentPage(g_nProvider));
	TESTC(Dialog.PushButton(IDC_Next));
	TESTC(Dialog.IsCurrentPage(g_nConnection));

	if (pPropUserID && VT_BSTR == pPropUserID->vValue.vt)
		TESTC(Dialog.SetUserID(V_BSTR(&pPropUserID->vValue)));
		
	if (pPropPassword && VT_BSTR == pPropPassword->vValue.vt)
		TESTC(Dialog.SetPassword(V_BSTR(&pPropPassword->vValue)));

	if (pPropDataSource && VT_BSTR == pPropDataSource->vValue.vt)
		TESTC(Dialog.SetInitDataSource(V_BSTR(&pPropDataSource->vValue)));
	
	COMPARE(Dialog.KillThread(), TRUE);

	TESTC(Dialog.SpawnUDLFile(g_wszUDLFileName));
	TESTC(Dialog.IsInExecution());
	COMPARE(Dialog.KillThread(), TRUE);

	TESTC(Dialog.SpawnUDLFile(g_wszUDLFileName));
	TESTC(Dialog.IsInExecution());
	COMPARE(Dialog.KillThread(), TRUE);

CLEANUP:
	TRETURN
} 
// }} TCW_VAR_PROTOTYPE_END



// {{ TCW_TERMINATE_METHOD
//*-----------------------------------------------------------------------
// @mfunc TestCase Termination Routine 
//
// @rdesc TEST_PASS or TEST_FAIL 
//
BOOL UDLSpecific::Terminate()
{ 
	// TO DO:  Add your own code here 

// {{ TCW_TERM_BASECLASS_CHECK2
	return(CPromptInitialize::Terminate());
} 	// }}
// }} TCW_TERMINATE_METHOD_END
// }} TCW_TC_PROTOTYPE_END


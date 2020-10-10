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
#include "commctrl.h"	// InitCommonControls 
#include "oledb.h"
#include "extralib.h"
#define INITGUID
#include <initguid.h>
#include "DSLResource.h"
#include "IDBPrmpt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlgs.h> // required for common dialog ids
#include <winbase.h>
#include <wchar.h>
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


ULONG		g_ulWaitPeriod = 1000;
HINSTANCE	g_hModuleLib;
WORD		g_wLanguage ;

// the title of the DSL window
CHAR		g_szIDS_DSL_TITLE_PROPERTY_PAGE[cMaxName] = "";	//"Data Link Properties"
// titles of the error window
CHAR		g_szIDS_TITLE_DATA_LINK_SUCCESS[cMaxName] = ""; //"Microsoft Data Link"
CHAR		g_szIDS_TITLE_DATA_LINK[cMaxName] = "";			//"Microsoft Data Link Error"

CHAR		g_szIDD_PROVIDER_GENERIC[cMaxName]		= "";	//"Provider"
CHAR		g_szIDD_CONNECTION_GENERIC[cMaxName]	= "";	//"Connection"
CHAR		g_szIDD_ADVANCED_GENERIC[cMaxName]		= "";	//"Advanced"
CHAR		g_szIDD_SUMMARY_GENERIC[cMaxName]		= "";	//"All"

CHAR		g_szIDS_Jolt_OFNTitle[cMaxName]			= "";	// "Select Access Database"
CHAR		g_szOLEDB32DLL[cMaxName] = "";
CHAR		g_szOLEDB32RDLL[cMaxName] = "";


CHAR		g_szIDS_DSL_TITLE_SELECT[cMaxName]		= "";	//"Select Data Link File"
CHAR		g_szIDS_DSL_TITLE_ORGANIZE[cMaxName]	= "";	//"Organize Data Link Files"



class CPromptInitialize;
struct CtrlArg{
	CPromptInitialize	*pThis;
	void				*rgCases;
};


class CBasicDialog{
	protected:
		HWND		m_hWnd;
		BOOL		m_fIsPropertySheet;

	public:
		CBasicDialog(BOOL fIsPropertyPage = FALSE, HWND hWnd = 0): m_hWnd(hWnd) { m_fIsPropertySheet = FALSE;}
		~CBasicDialog() {}

		HWND			GetHWND() {
			return m_fIsPropertySheet? PropSheet_GetCurrentPageHwnd(m_hWnd): m_hWnd;}

		virtual BOOL	PushButton(int nCtrlID);
		virtual BOOL	GetTextFromCtrl(int nCtrlID, WCHAR *pwszText, int cLen);
		virtual BOOL	SetTextToCtrl(int nCtrlID, LPCWSTR pwszTextToSet);
		
		virtual BOOL	AreControlsEnabled(
			ULONG	cCtrlID,	// [in] the number of controls checked
			int		*rgCtrlID	// [in]	array of controls checked
		);

		virtual BOOL	AreControlsDisabled(
			ULONG	cCtrlID,	// [in] the number of controls checked
			int		*rgCtrlID	// [in]	array of controls checked
		);

		virtual BOOL	CheckControlsStatus(
			BOOL	fStatus,	// [in] the expected status of the control
			ULONG	cCtrlID,	// [in] the number of controls checked
			int		*rgCtrlID	// [in]	array of controls checked
		);

		virtual BOOL	CheckControlStatus(
			BOOL	fStatus,	// [in] the expected status of the control
			int		CtrlID		// [in] the ID of the control
		);

		virtual BOOL	CheckDlgButton(
			int		nCtrlID,		// [in] the ID of the control
			UINT	uStatus,		// [in] the status to be set		
			ULONG	ulEnabledID,	// [in] number of elements in rgEnabledID
			int		*rgEnabledID,	// [in] array of elements enabled after the set
			ULONG	ulDisabledID,	// [in]	number of elements in rgDisabledID
			int		*rgDisabledID	// [in] array of elements disabled 
		);

		virtual BOOL	CheckRadioButton(
			int		nIDFirst,		// [in] the ID of the first button in the group
			int		nIDLast,		// [in] the ID of the last button in the group
			int		nCtrlID,		// [in] the ID of the control
			ULONG	ulEnabledID,	// [in] number of elements in rgEnabledID
			int		*rgEnabledID,	// [in] array of elements enabled after the set
			ULONG	ulDisabledID,	// [in]	number of elements in rgDisabledID
			int		*rgDisabledID	// [in] array of elements disabled 
		);

		BOOL			IsControlEnabled(int nCtrlID) {
			return IsWindowEnabled(GetDlgItem(GetHWND(), nCtrlID));}

		void			Activate(){
					SetActiveWindow(m_hWnd);}

		// @cmember Create a UDL file
		BOOL					CreateUDLFile(WCHAR *pwszFileName);
		BOOL					CreateUDLFile(CHAR *pszFileName);
}; //CBasicDialog


enum DSL_CREATION_METHOD{
	DSL_CM_UDL			= 0,
	DSL_CM_INTERFACE	= 1,	// created by calling IDBPromptInitialize::promptDataSource
	DSL_CM_VB			= 2		// created from VB using DataLinks objects
};


class CDSL_Dialog: public CBasicDialog{
	protected:
		HWND		m_hParentWnd;	// handler to the parent window

		// argument when created by IDBPromptInitialize::PromptDataSource
		const GUID				*m_piid;					// ptr to the interface to be created
		IUnknown				*m_pUnkOuter;				// obj to aggregate the DSO
		DBPROMPTOPTIONS			m_dwPromptOptions;			// prompt options
		ULONG					m_cSourceTypeFilter;		// size of the source type filter list
		DBSOURCETYPE			*m_rgSourceTypeFilter;		// source type filter list
		LPCOLESTR				m_pwszszzProviderFilter;	// provider name filter list
		IUnknown				**m_ppDataSource;			// to DSO object
		IDBPromptInitialize		*m_pIDBPromptInitialize;	// IDBPromptInitialize used
		HRESULT					m_hres;						// the return value of IDBPromptInitialize::PromptDataSource call
		
		// thread management
		unsigned				m_IDThread;
		HANDLE					m_hThread;

		//cache window handlers for dialog pages
		HWND					m_hProvider;	// handler to the provider tab
		HWND					m_hConnection;	// handler to the conn tab
		HWND					m_hAdvanced;	// handler to the advanced tab
		HWND					m_hAll;			// handler to all (summary) tab

		// says whether the UI is still up 
		// (assume 2 seconds to bring up the UI)
		BOOL					m_fIsInExecution;

		// flag to detect whether the dialog was opened from 
		// a UDL file which has the password saved in clear
		BOOL					m_fDenySPInClear;

		// status data
		// used to store all properties/values displayed in summary tab
		ULONG					m_cInitProp;
		InitProp				*m_rgInitProp;

		WCHAR					m_wszProviderDescription[cMaxName];
		CLSID					m_clsidProvider;

		// @cmember the list of all provider description mentioned in provider tab
		ULONG					m_cProviderList;
		WCHAR					**m_rgProviderList;

		// @cmember variable to store the User ID string
		WCHAR					m_wszUserID[cMaxName];

		// @cmember variable to store the password string
		WCHAR					m_wszPassword[cMaxName];

		// @cmember variable to store the InitDataSource string
		WCHAR					m_wszInitDataSource[cMaxName];

		// @cmember variable to store the InitDataSource string
		WCHAR					m_wszUDLFileName[cMaxName];

		DSL_CREATION_METHOD		m_CreationMethod;
	
		// @cmember flag for empty (blank) password
		BOOL					m_fBlankPassword;

		// @cmember flag indicating whether the DSL was called with an existing DSO 
		BOOL					m_fExistingDSO;

	public:
		static CSourcesSet		s_SourcesSet;
		static IDataInitialize	*s_pIDataInitialize;

		// this will have 2 constructors: one will create the dialog based on UDL
		// the other by calling IDBPromptInitialize::PromptDataSource
		CDSL_Dialog(WCHAR *wszUDLFileName);
		CDSL_Dialog(CHAR *szUDLFileName);
		
		CDSL_Dialog(
			IDBPromptInitialize		*pIDBPromptInitialize,
			IUnknown				*pUnkOuter,
			HWND					hWndParent,
			DBPROMPTOPTIONS			dwPromptOptions,
			ULONG					cSourceTypeFilter,
			DBSOURCETYPE			*rgSourceTypeFilter,
			LPCOLESTR				pwszszzProviderFilter,
			REFIID					riid,
			IUnknown				**ppDataSource
		);

		CDSL_Dialog();

		~CDSL_Dialog();


		BOOL			SpawnPromptDataSource(
			IDBPromptInitialize		*pIDBPromptInitialize,
			IUnknown				*pUnkOuter,
			HWND					hWndParent,
			DBPROMPTOPTIONS			dwPromptOptions,
			ULONG					cSourceTypeFilter,
			DBSOURCETYPE			*rgSourceTypeFilter,
			LPCOLESTR				pwszszzProviderFilter,
			REFIID					riid,
			IUnknown				**ppDataSource
			);

		BOOL			SpawnUDLFile(WCHAR *wszUDLFileName);

		BOOL			IsInExecution() {
				return m_fIsInExecution;}

		BOOL			HasFinished() {
				return !m_fIsInExecution;} 
		
		HRESULT			GetHRESULT(){
				return m_hres;}

		BOOL			IsResult(HRESULT hr){
			return HasFinished() && DSL_CM_INTERFACE == m_CreationMethod && CHECK(m_hres, hr);}

		BOOL			DenySPInClear() {return m_fDenySPInClear;}
		BOOL			SetDenySPInClear(BOOL fVal) 
								{return m_fDenySPInClear = fVal;}


		// @cmember frees the list of providers
		void					FreeProviderList();

		// @cmember Pop up DSL page
		static unsigned WINAPI	MyThread(void*);
		static unsigned WINAPI	MyUDLThread(void*);

		// @cmember Kill the DSL page thread
		BOOL					KillThread(int nButton = PSBTN_OK, DWORD dwMilliseconds = INFINITE);

		// @cmember GetHandlersToPages
		BOOL					GetPageHandles();

		// @cmember Check if the current page is the one asked
		BOOL					IsCurrentPage(ULONG nPage);

		// @cmember GotoPage
		BOOL					GotoPage(ULONG nPage);

		// @cmember GotoProviderPage
		BOOL					GotoProviderPage();

		// @cmember GotoConnectionPage - Authentification
		BOOL					GotoConnectionPage();

		// @cmember GotoAdvancedPage
		BOOL					GotoAdvancedPage();

		// @cmember GotoAllPage
		BOOL					GotoAllPage();

		// @cmember HasProviderPage
		BOOL					HasProviderPage();

		// @cmember Get the description of the current selected provider
		BOOL					GetProvider();
		
		// @cmember Returns the description of the current selected provider
		WCHAR					*GetProviderName() {
			return m_wszProviderDescription;}

		// @cmember get the list of all providers mentioned in provider tab
		BOOL					GetListOfProviders();

		// methods to get values from the summary page
		BOOL					GetInitMode(LONG*);

		// @cmember Get property value from DBPROPID
		// searches the all tab for the value of a certain property
		BOOL					GetPropertyValueFromSummary(DBPROPID, WCHAR**);
		BOOL					GetPropertyValueFromSummary(WCHAR*, WCHAR**);


		// @cmember Open the file browser (for selecting a datasource file under Jolt)
		BOOL					OpenFileBrowser();
		BOOL					SetFileNameInBrowser(CHAR *szFileName);
		BOOL					FileBrowser_OnOpen();
		BOOL					FileBrowser_OnCancel();

		// @cmember Set values to various edit controls
		BOOL					SetInitDataSource(LPCWSTR);
		BOOL					SetServerName(LPCWSTR);
		BOOL					SetUserID(LPCWSTR);
		BOOL					SetDatabase(LPCWSTR);
		BOOL					SetDatabaseName(LPCWSTR);
		BOOL					SetFileName(LPCWSTR);
		BOOL					SetPassword(LPCWSTR);

		// @cmember Set Save Password
		BOOL					SetSavePassword(UINT uVal = BST_CHECKED);

		// @cmember Set BlankPassword
		BOOL					SetBlankPassword(UINT uVal = BST_CHECKED);
		
		// @cmember Set Security Method
		BOOL					SetSecurityMethod(int nValue = IDC_USE_STANDARD);

		// @cmember Set Database Method
		BOOL					SetDatabaseMethod(int nValue = IDC_UseDatabaseOnServerName);

		// @cmember select provider from list
		BOOL					SelectProvider(CLSID);
		BOOL					SelectProvider(WCHAR*);

		// @cmember select another provider than the current one from Provider Page
		// if the Provider Page doesn't exist, the method fails
		BOOL					SelectAnotherProvider();

		// @cmember set the connection method (datasource name or provider string)
		BOOL	SetConnectionMethod(int);						// Sockeye specific
		
		//@cmember set the initial catalog name
		BOOL	SetInitCatalog(WCHAR *pwszCatalogName);			// Sockeye specific

		//@cmember set provider string
		BOOL	SetProviderString(WCHAR *pwszProviderString);	// Sockeye specific

		// @cmember Test connection through the "Test Connection" button in the connection dlg
		BOOL					TestConnection(BOOL fRes);
		BOOL					TestConnection(BOOL *fRes = NULL);	// this method goes through pressing the "Test Connection" button
													// but does not check the result of the action

		// @cmember Check properties on data source object
		BOOL					CacheAllProperties();
		virtual BOOL			CheckAllProperties();
		BOOL					CheckPropertiesOnDataSourceObject(IUnknown *pIUnknown);

		// @cmember check filtering
		BOOL					CheckFilters();


		// @cmember check that trying to edit the Persist Security Info errors
		BOOL					CheckError_OnEditing_PersistSecurityInfo();

		// for filters
		// @cmember check that the datasource type is valid related to the filter
		BOOL					IsValidDataSourceType(DBSOURCETYPE);
		
		// @cmember check that the datasource parsename is valid related to the filter
		BOOL					IsValidProgID(WCHAR*);
		
		BOOL					GetFilteredProviders(
			ULONG	*pcIdxProv,	//[out] the number of filtered providers
			ULONG	**prgIdxProv	//[out] the array of indexes to filtered providers
		);

		// @cmember Checks the window position related to the parent one and to the desktop range
		BOOL					CheckWindowPosition();

		// @cmember Selects a random init catalog from 
		BOOL					Luxor_SelectInitCatalog();

		// @cmember Get property from the summary page
		BOOL					GetProperty(WCHAR *pwszPropName, WCHAR **ppwszPropValue);

		// @cmember Check the list of server names, displayed in the connection page
		// against the enumerator
		BOOL					Luxor_CheckServerNameList();

		// @cmember Check the list of data source names, displayed in the connection page
		// against the enumerator
		BOOL					Sockeye_CheckDSNList();

		// @cmember Set the mode in the advance page
		BOOL					SetInitMode(LONG);
		
		// @cmember Set the impersonation and protection level in the Advanced PAge
		BOOL					SetImpersonationLevel(LONG);
		BOOL					SetProtectionLevel(LONG lProtectionLevel);

}; //CDSL_Dialog

CSourcesSet		CDSL_Dialog::s_SourcesSet;
IDataInitialize	*CDSL_Dialog::s_pIDataInitialize = NULL;

class CDSL_FileDialog: public CBasicDialog{
	protected:
		HWND		m_hParentWnd;	// handler to the parent window

		// argument when created by IDBPromptInitialize::PromptDataSource
		IDBPromptInitialize		*m_pIDBPromptInitialize;	// IDBPromptInitialize used
		DBPROMPTOPTIONS			m_dwPromptOptions;			// prompt options
		WCHAR					*m_pwszInitialDirectory;		// the initial directory
		WCHAR					*m_pwszInitialFile;			// initial file
		WCHAR					**m_ppwszSelectedFile;		// the returned selected file
		HRESULT					m_hres;						// the return value of IDBPromptInitialize::PromptDataSource call
		
		// thread management
		unsigned				m_IDThread;
		HANDLE					m_hThread;

		// says whether the UI is still up 
		// (assume 2 seconds to bring up the UI)
		BOOL					m_fIsInExecution;

	public:
		CDSL_FileDialog(
			IDBPromptInitialize		*pIDBPromptInitialize,
			HWND					hWndParent,
			DBPROMPTOPTIONS			dwPromptOptions,
			WCHAR					*pwszInitialDirectory,
			WCHAR					*pwszInitialFile,
			WCHAR					**ppwszSelectedFile
		);

		CDSL_FileDialog();

		~CDSL_FileDialog();


		BOOL			SpawnPromptFileName(
			IDBPromptInitialize		*pIDBPromptInitialize,
			HWND					hWndParent,
			DBPROMPTOPTIONS			dwPromptOptions,
			WCHAR					*pwszInitialDirectory,
			WCHAR					*pwszInitialFile,
			WCHAR					**ppwszSelectedFile
			);

		BOOL			IsInExecution() {
				return m_fIsInExecution;}

		BOOL			HasFinished() {
				return !m_fIsInExecution;} 
		
		HRESULT			GetHRESULT(){
				return m_hres;}

		BOOL			IsResult(HRESULT hr){
			return HasFinished() && CHECK(m_hres, hr);}

		// @cmember Pop up DSL page
		static unsigned WINAPI	MyThread(void*);

		// @cmember Kill the DSL page thread
		BOOL					KillThread(int nButton = IDCANCEL, DWORD dwMilliseconds = INFINITE);
}; //CDSL_FileDialog


class CPromptInitialize: public CSessionObject
{
protected:

	IDBPromptInitialize		*m_pIDBPromptInitialize;

	// @cmember Builds a long user name
	BOOL					BuildLongUserName(GUID guid, WCHAR **ppwszName, ULONG ulSize=cMaxName);

public:

	static HWND				s_hMainWnd;

	CPromptInitialize(WCHAR *wstrTestCaseName);
	virtual ~CPromptInitialize() {;}

	// @cmember Initialization Routine
	virtual BOOL Init();
	// @cmember Termination Routine
	virtual BOOL Terminate();
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
	// }} TCW_TESTVARS_END
} ;
// {{ TCW_TESTCASE(GeneralConnection)
#define THE_CLASS GeneralConnection
BEG_TEST_CASE(GeneralConnection, CPromptInitialize, L"general connection dialog testing")
	TEST_VARIATION(1, 		L"Goto Connection page using the Next button in the provider page")
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


// static members
HWND		CPromptInitialize::s_hMainWnd = FindWindowA("LTM", "Microsoft Local Test Manager");


//--LoadString()------------------------------------------------ 
// Loads a string resource by id and language 
// and (A version) converts to the current ANSI code page. 
// Note that strings are stored in blocks of 16, and the ID gives 
// us the number of the block, and the offset into the block. 
// ----------------------------------------------------------------------------- 
int LoadStringA(HINSTANCE hModule, UINT wID, LPSTR szBuf, int cchBuf, WORD wLanguage) 
{ 
    UINT    block, num; 
    int     len = 0;     
    HRSRC   hRC = NULL; 
    HGLOBAL hgl = NULL;; 
    LPWSTR  str = NULL; 
    register UINT i; 
     
 
	szBuf[0] = '\0'; 
 
    block = (wID >> 4) + 1;	// compute block number 
    num = wID & 0xf;		// compute offset into block 
     
    hRC = FindResourceEx(hModule, RT_STRING, MAKEINTRESOURCE(block), wLanguage); 
    if (!hRC)  
	{
		// try with default code page
	    hRC = FindResourceEx(hModule, RT_STRING, MAKEINTRESOURCE(block), 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)); 
		if (!hRC)
			goto Error; 
	}
 
	hgl = LoadResource(hModule, hRC); 
	if (!hgl) 
		goto Error; 
 
    str = (LPWSTR)LockResource(hgl); 
    if (!str)  
		goto Error; 
 
	// Move up block to string we want 
	for (i = 0; i < num; i++) 
		str += *str + 1; 
 
	// convert the string to current code page 
	len = WideCharToMultiByte(wLanguage, //CP_ACP, //code page
	  WC_COMPOSITECHECK, 
	  str + 1, *str, 
	  szBuf, cchBuf - 1, 
	  NULL, NULL); 
 
	szBuf[min(cchBuf-1, *str)] = '\0'; 
 
Error: 
	if (hgl) 
	{ 
		UnlockResource(hgl);	// maybe not needed 
		FreeResource(hgl);		// maybe not needed 
	} 
 
    return len; 
} //LoadStringA


 
int LoadStringW(HINSTANCE hModule, UINT wID, LPWSTR wzBuf, int cchBuf, WORD wLanguage) 
{ 
    UINT    block, num; 
    int     len = 0;     
    HRSRC   hRC = NULL; 
    HGLOBAL hgl = NULL; 
    LPWSTR  str = NULL; 
    register UINT i; 
     
 
	wzBuf[0] = TEXT('\0'); 
 
    block = (wID >> 4) + 1;// compute block number 
    num = wID & 0xf;// compute offset into block 
     
    hRC = FindResourceEx(hModule, RT_STRING, MAKEINTRESOURCE(block), wLanguage); 
    if (!hRC)  
	{
		// try with default code page
	    hRC = FindResourceEx(hModule, RT_STRING, MAKEINTRESOURCE(block), 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)); 
		if (!hRC)
			goto Error; 
	}
 
	hgl = LoadResource(hModule, hRC); 
	if (!hgl) 
		goto Error; 
 
    str = (LPWSTR)LockResource(hgl); 
    if (str)  
    { 
		for (i = 0; i < num; i++) 
			str += *str + 1; 
		wcsncpy(wzBuf, str + 1, min(cchBuf - 1, *str)); 
    } 
 
	wzBuf[min(cchBuf-1, *str) ] = '\0'; 
 	len = *str + 1; 
 
Error: 
	if (hgl) 
	{ 
		UnlockResource(hgl);	// maybe not needed 
		FreeResource(hgl);		// maybe not needed 
	} 
 
    return len; 
}  //LoadStringW


WCHAR *GetDlgTitle(DLGTEMPLATE *pDlgTmp)
// receives a DLGTEMPLATE structure and gets it's title
{
	WCHAR	*pwszTitle	= (WCHAR*)((BYTE*)pDlgTmp + sizeof(DLGTEMPLATE));
	
	// after the DLGTEMPLATE structure there are 3 arrays: menu, class and title
	// each of them is prefixed by 0xFFFF if present or replaced by 0x0000 otherwise 
	
	// jump over the menu array
	if (0 != wcscmp(L"", pwszTitle))
		pwszTitle += 2 + wcslen(pwszTitle+1);
	else
		pwszTitle++; 

	// jump over the class array
	if (0 != wcscmp(L"", pwszTitle))
		pwszTitle += 2 + wcslen(pwszTitle+1);
	else
		pwszTitle++; 

	// return the title of the dialog
	return pwszTitle;
} //GetDlgTitle


 
int LoadDialogTitleA(HINSTANCE hModule, UINT wID, LPSTR szBuf, int cchBuf, WORD wLanguage) 
{ 
    int				len = 0;     
    HRSRC			hRC = NULL; 
    HGLOBAL			hgl = NULL; 
    LPWSTR			str = NULL; 
	DLGTEMPLATE		*pDlgTmp = NULL;
	WCHAR			*pwszTitle = NULL;
	
    hRC = FindResourceEx(hModule, RT_DIALOG, MAKEINTRESOURCE(wID), wLanguage); 
    if (!hRC)  
	{
		// try with default code page
	    hRC = FindResourceEx(hModule, RT_DIALOG, MAKEINTRESOURCE(wID), 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)); 
		if (!hRC)
			goto Error; 
	}
 
	hgl = LoadResource(hModule, hRC); 
	if (!hgl) 
		goto Error; 
 
    pDlgTmp		= (DLGTEMPLATE*)LockResource(hgl); 
	pwszTitle	= GetDlgTitle(pDlgTmp);

	// convert the string to current code page 
	len = WideCharToMultiByte(wLanguage, //code page
	  WC_COMPOSITECHECK, 
	  pwszTitle, wcslen(pwszTitle), 
	  szBuf, cchBuf - 1, 
	  NULL, NULL); 
 
	szBuf[min((unsigned int)(cchBuf-1), wcslen(pwszTitle))] = '\0'; 

Error: 
	if (hgl) 
	{ 
		UnlockResource(hgl);	// maybe not needed 
		FreeResource(hgl);		// maybe not needed 
	} 
 
    return len; 
}  //LoadDialogTitleA




// This function reads the value of 
// HKEY_CLASSES_ROOT\CLSID\{2206CDB2-19C1-11D1-89E0-00C04FD7A829}\InprocServer32
// in order to find the exact address of oledb32.dll 
// oledb32r.dll is supposed to be in the same directory
BOOL GetCompleteNameOfDlls()
{
	TBEGIN
	DWORD		dwVal		= NULL;
	DWORD		cLen = cMaxName;
	LONG		lRes;
	CHAR		drive[_MAX_DRIVE] = "";
	CHAR		dir[_MAX_DIR] = "";
	DWORD		dwType;
	CHAR		szSubKey[] = "CLSID\\{2206CDB2-19C1-11D1-89E0-00C04FD7A829}\\InprocServer32";
	HKEY		hKey = 0;
	CHAR		szValueName[cMaxName] = "";
	
	lRes = 	RegOpenKeyExA(
		HKEY_CLASSES_ROOT,         // handle to open key
		szSubKey,  // address of name of subkey to open
		NULL,   // reserved
		KEY_QUERY_VALUE , // security access mask
		&hKey    // address of handle to open key
	);
	TESTC(ERROR_SUCCESS == lRes);

	lRes = RegQueryValueExA(
		hKey,							// handle to key to query
		szValueName,					// name of subkey to query
		NULL,							// reserved
		&dwType,						// address of buffer for value type
		(LPBYTE)g_szOLEDB32DLL,			// buffer for returned string
		&cLen							// receives size of returned string
		);
	TESTC(ERROR_SUCCESS == lRes);

	// create a complete path for oledb32r.dll under the same directory
   _splitpath(g_szOLEDB32DLL, drive, dir, NULL, NULL);
   _makepath( g_szOLEDB32RDLL, drive, dir, "oledb32r", "dll" );

	
CLEANUP:
	RegCloseKey(hKey);
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
	TRETURN
} //GetCompleteNameOfDlls




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
	const ULONG				cCPLen = 7;
	CHAR					szCodePage[cCPLen];
	ULONG					ulRes = IDS_DSL_TITLE_PROPERTY_PAGE;
	
	//Create the session
	ASSERT(pThisTestModule);
	pThisTestModule->m_pIUnknown = NULL;
	pThisTestModule->m_pIUnknown2 = NULL;

	if(!ModuleCreateDBSession(pThisTestModule))
		return FALSE;
	
	// set g_pIDBInitialize and g_pIOpenRowset
	TESTC(VerifyInterface(pThisTestModule->m_pIUnknown, IID_IDBInitialize, DATASOURCE_INTERFACE, (IUnknown**)&g_pIDBInitialize));
	TESTC(VerifyInterface(pThisTestModule->m_pIUnknown2, IID_IOpenRowset, SESSION_INTERFACE, (IUnknown**)&g_pIOpenRowset));


	TESTC(GetCompleteNameOfDlls());

	g_hLibInst		= LoadLibraryExA(g_szOLEDB32DLL, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	g_hModuleLib	= LoadLibraryExA(g_szOLEDB32RDLL, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

	TESTC(NULL != g_hLibInst);

	GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_IDEFAULTANSICODEPAGE, szCodePage, cCPLen);
	g_wLanguage  = atoi(szCodePage);

	TESTC( 0 < LoadStringA(g_hModuleLib, IDS_DSL_TITLE_PROPERTY_PAGE, 
		g_szIDS_DSL_TITLE_PROPERTY_PAGE, cMaxName, g_wLanguage));

	TESTC( 0 < LoadStringA(g_hModuleLib, IDS_TITLE_DATA_LINK, 
		g_szIDS_TITLE_DATA_LINK, cMaxName, g_wLanguage));

	TESTC( 0 < LoadStringA(g_hModuleLib, IDS_TITLE_DATA_LINK_SUCCESS, 
		g_szIDS_TITLE_DATA_LINK_SUCCESS, cMaxName, g_wLanguage));

	// get the string that gives the title of the browse dialog
	TESTC( 0 < LoadStringA(g_hModuleLib, IDS_Jolt_OFNTitle, 
		g_szIDS_Jolt_OFNTitle, cMaxName, g_wLanguage));

	// load the titles of property sheet pages
	TESTC(0 < LoadDialogTitleA(g_hModuleLib, IDD_PROVIDER_GENERIC, 
		g_szIDD_PROVIDER_GENERIC, cMaxName, g_wLanguage));

	TESTC(0 < LoadDialogTitleA(g_hModuleLib, IDD_CONNECTION_GENERIC, 
		g_szIDD_CONNECTION_GENERIC, cMaxName, g_wLanguage));

	TESTC(0 < LoadDialogTitleA(g_hModuleLib, IDD_ADVANCED_GENERIC, 
		g_szIDD_ADVANCED_GENERIC, cMaxName, g_wLanguage));

	TESTC(0 < LoadDialogTitleA(g_hModuleLib, IDD_SUMMARY_GENERIC, 
		g_szIDD_SUMMARY_GENERIC, cMaxName, g_wLanguage));

	TESTC( 0 < LoadStringA(g_hModuleLib, IDS_DSL_TITLE_SELECT, 
		g_szIDS_DSL_TITLE_SELECT, cMaxName, g_wLanguage));

	TESTC( 0 < LoadStringA(g_hModuleLib, IDS_DSL_TITLE_ORGANIZE, 
		g_szIDS_DSL_TITLE_ORGANIZE, cMaxName, g_wLanguage));

	//Create an Instance of IDBPromptInitialize
	TESTC_(CoCreateInstance(CLSID_DataLinks, NULL, CLSCTX_INPROC_SERVER, IID_IDBPromptInitialize, (void**)&pIDBPromptInitialize),S_OK); 
	
	CDSL_Dialog::s_SourcesSet.FinalInit();
	TESTC_(CoCreateInstance(CLSID_MSDAINITIALIZE, NULL, CLSCTX_INPROC_SERVER, 
			IID_IDataInitialize, (void**)&CDSL_Dialog::s_pIDataInitialize), S_OK);
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
	SAFE_RELEASE(CDSL_Dialog::s_pIDataInitialize)
	DestroyWindow(CPromptInitialize::s_hMainWnd);
	
	SAFE_RELEASE(g_pIDBInitialize);
	SAFE_RELEASE(g_pIOpenRowset);

	if (g_hLibInst)
		FreeLibrary(g_hLibInst);
	if (g_hModuleLib)
		FreeLibrary(g_hModuleLib);
	return ModuleReleaseDBSession(pThisTestModule);
}	



//------------------------------------------------------------------------
//	Helper functions
//------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////
// BOOL LV_SetItemState
//
//////////////////////////////////////////////////////////////////
LONG LV_SetItemState(HWND hWnd, LONG iItem, LONG iSubItem, LONG lState, LONG lStateMask)
{
	//LVM_SETITEM
	LV_ITEM lvItem = { LVIF_STATE, iItem, iSubItem, lState, lStateMask, NULL, 0, 0, 0, 0};
	return SendMessage(hWnd, LVM_SETITEMSTATE, (WPARAM)iItem, (LPARAM)&lvItem);
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Test Case Section
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// }} END_DECLARE_TEST_CASES()

// {{ TCW_TESTMODULE(ThisModule)
TEST_MODULE(15, ThisModule, gwszModuleDescrip)
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
	m_pIDBPromptInitialize	= NULL;

	if (CSessionObject::Init())
	{
		//Create an Instance of IDBPromptInitialize
		TESTC_(CoCreateInstance(CLSID_DataLinks, NULL, CLSCTX_INPROC_SERVER, IID_IDBPromptInitialize, (void**)&m_pIDBPromptInitialize),S_OK); 
		return TRUE;
	}

CLEANUP:
	return FALSE;
} // CPromptInitialize::Init




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
	SAFE_RELEASE(m_pIDBPromptInitialize);
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
	IDBProperties	*pIDBProperties = NULL;

	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		TESTC_(GetModInfo()->CreateProvider(CLSID_SQLOLEDB, NULL, 
			IID_IDBProperties, (IUnknown**)&pIDBProperties), S_OK);
		SAFE_RELEASE(pIDBProperties);
		return TRUE;
	} 
CLEANUP:
	return FALSE;
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
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetUserID(g_wszLuxorUserName));
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_UNCHECKED));
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetUserID(g_wszLuxorUserName));
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;

	// first, the negative case, bad password
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetUserID(g_wszLuxorUserName));
	TESTC(Dialog.SetPassword(g_wszLuxorBadPassword));
	TESTC(Dialog.SetSavePassword(BST_UNCHECKED));
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

	// the positive case
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.IsCurrentPage(g_nConnection));
	TESTC(Dialog.SetPassword(g_wszLuxorPassword));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC_(pIDBInitialize->Initialize(), S_OK);

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
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetUserID(g_wszLuxorUserName));
	TESTC(Dialog.SetPassword(g_wszLuxorPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	Sleep(1000);
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), S_OK);

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
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetSecurityMethod(IDC_USE_INTEGRATED));
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
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
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszInexistentLuxorServerName));

	TESTC(Dialog.GotoAllPage());
	TESTC(Dialog.GetProperty(L"Data Source", &pwszDSName));
	TESTC(0 == wcscmp(pwszDSName, g_wszInexistentLuxorServerName));

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
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
		TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetUserID(g_rgName[i]));
		Sleep(1000);
		TESTC(Dialog.CacheAllProperties());
		TESTC(Dialog.CheckAllProperties());
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
		TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetPassword(g_rgName[i]));
		TESTC(Dialog.CacheAllProperties());
		TESTC(Dialog.CheckAllProperties());
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
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
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
	WCHAR			*pwszLongName	= NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	CDSL_Dialog		Dialog;
	
	TESTC_PROVIDER(!BuildLongUserName(CLSID_SQLOLEDB, &pwszLongName));
	TESTC(NULL != pwszLongName);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetSecurityMethod());

	TESTC(Dialog.SetUserID(pwszLongName));
	
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TEST2C_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED, S_OK);

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
	WCHAR			*pwszLongName	= NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	CDSL_Dialog		Dialog;
	
	TESTC_PROVIDER(!BuildLongUserName(CLSID_SQLOLEDB, &pwszLongName));
	TESTC(NULL != pwszLongName);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());

	TESTC(Dialog.SetServerName(pwszLongName));
	
	TESTC(Dialog.SetSecurityMethod());
	TESTC(Dialog.SetUserID(g_wszLuxorUserName));
	TESTC(Dialog.SetBlankPassword());
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TEST2C_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED, S_OK);

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
	WCHAR			*pwszLongName	= NULL;
	IDBInitialize	*pIDBInitialize	= NULL;
	CDSL_Dialog		Dialog;
	
	TESTC_PROVIDER(!BuildLongUserName(CLSID_SQLOLEDB, &pwszLongName));
	TESTC(NULL != pwszLongName);

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetSecurityMethod());
	TESTC(Dialog.SetUserID(g_wszLuxorUserName));
	TESTC(Dialog.SetPassword(pwszLongName));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TEST2C_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED, S_OK);

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
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetUserID(g_wszLuxorUserName));
	TESTC(Dialog.SetPassword(g_wszLuxorBadPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	Sleep(1000);
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetUserID(g_wszLuxorUserName));
	TESTC(Dialog.SetPassword(g_wszLuxorBadPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	Sleep(1000);
	TESTC(Dialog.TestConnection(FALSE));
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	CDSL_Dialog			Dialog;
	IDBInitialize		*pIDBInitialize		= NULL;
	
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	TESTC(Dialog.IsInExecution());
	// select the provider indicated by the init string
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetUserID(g_wszLuxorUserName));
	TESTC(Dialog.SetPassword(g_wszLuxorPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	TESTC(Dialog.SetDatabaseMethod(IDC_UseDatabaseOnServerName));

	TESTC(Dialog.SetDatabase(g_wszLuxorInitCat));
	
	TESTC(Dialog.TestConnection(TRUE));
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), S_OK);

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
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetUserID(g_wszLuxorUserName));
	TESTC(Dialog.SetPassword(g_wszLuxorPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));

	TESTC(Dialog.SetDatabaseMethod(IDC_UseDatabaseOnServerName));
	TESTC(Dialog.Luxor_SelectInitCatalog());

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
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
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetServerName(g_wszLuxorServer));
	TESTC(Dialog.SetUserID(g_wszLuxorUserName));
	TESTC(Dialog.SetPassword(g_wszLuxorPassword));
	TESTC(Dialog.SetSavePassword(BST_CHECKED));

	TESTC(Dialog.SetDatabaseMethod(IDC_UseDatabaseFileName));
	TESTC(Dialog.SetDatabaseName(L"neueDB"));
	TESTC(Dialog.SetFileName(L"\\somefile.mdf"));

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

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
	IDBProperties	*pIDBProperties = NULL;

	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		TESTC_(GetModInfo()->CreateProvider(CLSID_MSDASQL, NULL, 
			IID_IDBProperties, (IUnknown**)&pIDBProperties), S_OK);
		SAFE_RELEASE(pIDBProperties);
		return TRUE;
	} 
CLEANUP:
	return FALSE;
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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

	// the positive case
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC_(pIDBInitialize->Initialize(), S_OK);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

	// the positive case
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IDBInitialize, (IUnknown**)&pIDBInitialize));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC_(pIDBInitialize->Initialize(), S_OK);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
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
		TESTC(Dialog.CacheAllProperties());
		TESTC(Dialog.CheckAllProperties());
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
		TESTC(Dialog.CacheAllProperties());
		TESTC(Dialog.CheckAllProperties());
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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TEST2C_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED, S_OK);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TEST2C_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED, S_OK);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TEST2C_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED, S_OK);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.TestConnection(FALSE));

	TESTC(Dialog.SetSavePassword(BST_CHECKED));
	Sleep(1000);
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	
	TESTC(Dialog.TestConnection(TRUE));
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), S_OK);

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
	IDBProperties	*pIDBProperties = NULL;

	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		TESTC_(GetModInfo()->CreateProvider(CLSID_JOLT40, NULL, 
			IID_IDBProperties, (IUnknown**)&pIDBProperties), S_OK);
		SAFE_RELEASE(pIDBProperties);
		return TRUE;
	} 
CLEANUP:
	return FALSE;
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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), S_OK);

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

	TESTC(Dialog.TestConnection(TRUE));
	TESTC(Dialog.SetInitDataSource(L"Not really a database"));
	TESTC(Dialog.TestConnection(FALSE));

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
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

	TESTC_(m_hr = pIDBInitialize->Initialize(), S_OK);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.TestConnection(FALSE));
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.SetFileNameInBrowser(szLocalAccessDB));
	// close the browser by pressing the open button
	TESTC(Dialog.FileBrowser_OnOpen());

	// once more, this time go for CANCEL
	// press browser button near database name edit control
	TESTC(Dialog.OpenFileBrowser());
	// simulate that we chose a file
	TESTC(Dialog.SetFileNameInBrowser("aiurea vorbirea"));
	// close the browser by pressing the open button
	TESTC(Dialog.FileBrowser_OnCancel());
	
	// send completion message
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
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
	IDBProperties	*pIDBProperties = NULL;

	// {{ TCW_INIT_BASECLASS_CHECK
	if(CPromptInitialize::Init())
	// }}
	{ 
		TESTC_(GetModInfo()->CreateProvider(CLSID_MSDAORA, NULL, 
			IID_IDBProperties, (IUnknown**)&pIDBProperties), S_OK);
		SAFE_RELEASE(pIDBProperties);
		return TRUE;
	} 
CLEANUP:
	return FALSE;
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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), S_OK);

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

	TESTC(Dialog.TestConnection(TRUE));

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), S_OK);

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
		TESTC(Dialog.CacheAllProperties());
		TESTC(Dialog.CheckAllProperties());
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
		TESTC(Dialog.CacheAllProperties());
		TESTC(Dialog.CheckAllProperties());
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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), S_OK);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), S_OK);

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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
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
	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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

	TESTC(Dialog.TestConnection(FAIL));

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));
	TESTC(Dialog.CheckPropertiesOnDataSourceObject(pIDBInitialize));

	TESTC_(pIDBInitialize->Initialize(), DB_SEC_E_AUTH_FAILED);

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

	TESTC(Dialog.SelectAnotherProvider());
	Sleep(1000);
	TESTC(Dialog.TestConnection(FALSE));
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
	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		// if datasource is not a provider skip the iteration
		if (	DBSOURCETYPE_DATASOURCE_TDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			||	CUSTOM_CONN & CDSL_Dialog::s_SourcesSet[i].m_CustomUI)
			continue;

		// if the enumerator returned it as an OLEDB provider, check it can be selected
		odtLog << CDSL_Dialog::s_SourcesSet[i].m_pwszDescription << "\n";
		TESTC(Dialog.SelectProvider(CDSL_Dialog::s_SourcesSet[i].m_pwszDescription));
		TESTC(Dialog.GotoAllPage());
		Sleep(1000);
		TESTC(Dialog.GotoProviderPage());
		// check that the provider is still selected
		TESTC(Dialog.GetProvider());
		TESTC(0 == wcscmp(Dialog.GetProviderName(), CDSL_Dialog::s_SourcesSet[i].m_pwszDescription));
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

	// ask for aggregation
	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, (IUnknown*)&Aggregate, s_hMainWnd, 
		DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, 
		IID_IUnknown, (IUnknown**)&Aggregate.m_pIUnkInner));

	TESTC(Dialog.IsInExecution());

	TESTC(Dialog.SelectAnotherProvider());
	TESTC(Dialog.TestConnection());

	TESTC(Dialog.SelectAnotherProvider());
	TESTC(Dialog.TestConnection());
	
	TESTC(Dialog.SelectProvider(GetModInfo()->GetProviderCLSID()));
	TESTC(Dialog.TestConnection());
	
	TESTC(Dialog.SelectAnotherProvider());
	TESTC(Dialog.TestConnection());
	
	TESTC(Dialog.SelectAnotherProvider());
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
	
	for (i=0; i<cMaxIterations; i++)
	{
		CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSourceType, rgSourceType, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);
		TESTC(Dialog.IsResult(E_INVALIDARG));
		TESTC(NULL == pIDBInitialize);
	}

	// try this on existing DSO as well
	TESTC_(GetModInfo()->CreateProvider(NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);
	{
		CDSL_Dialog		Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSourceType, rgSourceType, 
			NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);
		TESTC(Dialog.IsResult(E_INVALIDARG));
		TESTC(NULL != pIDBInitialize);
	}

CLEANUP:
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

	TESTC(Dialog.IsResult(E_INVALIDARG));
	TESTC(NULL == pIDBInitialize);

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
	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		if (DBSOURCETYPE_DATASOURCE == CDSL_Dialog::s_SourcesSet[i].m_wType
			&& ! (CUSTOM_CONN & CDSL_Dialog::s_SourcesSet[i].m_CustomUI))
			break;
	}
	if (i >= CDSL_Dialog::s_SourcesSet.Count())
		return TEST_SKIPPED;

	// get the progID
	TESTC_(ProgIDFromCLSID(CDSL_Dialog::s_SourcesSet[i], &pwszProgID), S_OK);
	
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

	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count()-1; i++)
	{
		for (j=i+1; j<CDSL_Dialog::s_SourcesSet.Count(); j++)
		{
			if (0 == wcscmp(CDSL_Dialog::s_SourcesSet[i].m_pwszParseName, CDSL_Dialog::s_SourcesSet[j].m_pwszParseName))
			{
				cMProv1 = i;
				cMProv2 = j;
				break;
			}
		}
		if (j<CDSL_Dialog::s_SourcesSet.Count())
			break;
	}

	if (i>=(int)(CDSL_Dialog::s_SourcesSet.Count()-1))
		return TEST_SKIPPED;

	TESTC(0 <= cMProv1 && cMProv1 < cMProv2);
	TESTC(cMProv1 < cMProv2 && cMProv2 < (int)CDSL_Dialog::s_SourcesSet.Count());

	// don't set any src filter and set provider filter
	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
	// get the progID
	pwszProgID = NULL;
	TESTC_(ProgIDFromCLSID(CDSL_Dialog::s_SourcesSet[cMProv1], &pwszProgID), S_OK);
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
	rgSrcType[0]	= CDSL_Dialog::s_SourcesSet[cMProv1].m_wType;
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
	rgSrcType[0]	= CDSL_Dialog::s_SourcesSet[cMProv2].m_wType;
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
	rgSrcType[0]	= CDSL_Dialog::s_SourcesSet[cMProv1].m_wType;
	rgSrcType[1]	= CDSL_Dialog::s_SourcesSet[cMProv2].m_wType;
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
	
	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator
		fAckProv = (DBSOURCETYPE_DATASOURCE == CDSL_Dialog::s_SourcesSet[i].m_wType
			||	DBSOURCETYPE_DATASOURCE_TDP == CDSL_Dialog::s_SourcesSet[i].m_wType
			||	DBSOURCETYPE_DATASOURCE_MDP == CDSL_Dialog::s_SourcesSet[i].m_wType);

		// set provider filter, don't set any src filter 
		memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
		
		// get the progID
		pwszProgID = NULL;
		TESTC_(ProgIDFromCLSID(CDSL_Dialog::s_SourcesSet[i], &pwszProgID), S_OK);
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
		rgSrcType[0]	= CDSL_Dialog::s_SourcesSet[i].m_wType;
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

	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator?
		fAckProv = (DBSOURCETYPE_DATASOURCE == CDSL_Dialog::s_SourcesSet[i].m_wType
			||	DBSOURCETYPE_DATASOURCE_TDP == CDSL_Dialog::s_SourcesSet[i].m_wType
			||	DBSOURCETYPE_DATASOURCE_MDP == CDSL_Dialog::s_SourcesSet[i].m_wType);

		// set provider filter, don't set any src filter 
		memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
		
		// get the filter
		wcscpy(wszProviderFilter, CDSL_Dialog::s_SourcesSet[i].m_pwszName);
		odtLog << "\tOLEDB provider: " << CDSL_Dialog::s_SourcesSet[i].m_pwszName << "\n";

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
		rgSrcType[0]	= CDSL_Dialog::s_SourcesSet[i].m_wType;
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
		TESTC_(CLSIDFromProgID(CDSL_Dialog::s_SourcesSet[i].m_pwszName, &clsid), S_OK);

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
	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		// get the current clsid
		if (	(	DBSOURCETYPE_DATASOURCE		== CDSL_Dialog::s_SourcesSet[i].m_wType
				||	DBSOURCETYPE_DATASOURCE_TDP	== CDSL_Dialog::s_SourcesSet[i].m_wType
				||	DBSOURCETYPE_DATASOURCE_MDP	== CDSL_Dialog::s_SourcesSet[i].m_wType)
			&&	(CDSL_Dialog::s_SourcesSet[i] != m_pThisTestModule->m_ProviderClsid))
		{
			// get the current progID
			pwszProgID = NULL;
			TESTC_(ProgIDFromCLSID(CDSL_Dialog::s_SourcesSet[i], &pwszProgID), S_OK);
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
	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		if (DBSOURCETYPE_DATASOURCE == CDSL_Dialog::s_SourcesSet[i].m_wType)
		{
			for (j=i+1; j<CDSL_Dialog::s_SourcesSet.Count(); j++)
			{
				if (0 == wcscmp(CDSL_Dialog::s_SourcesSet[i].m_pwszParseName, CDSL_Dialog::s_SourcesSet[j].m_pwszParseName))
					break;
			}
			if (j >= CDSL_Dialog::s_SourcesSet.Count())
			{
				nChosen = i;
				break;
			}
		}
	}
	TESTC_PROVIDER(i<CDSL_Dialog::s_SourcesSet.Count());
			
	// set datasource type filter to a bad value for the provider
	rgSrcType[0] = (DBSOURCETYPE_DATASOURCE_TDP == CDSL_Dialog::s_SourcesSet[i].m_wType)?
			DBSOURCETYPE_DATASOURCE_MDP: DBSOURCETYPE_DATASOURCE_TDP;

	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		if (DBSOURCETYPE_ENUMERATOR == CDSL_Dialog::s_SourcesSet[i].m_wType)
			continue;

		if (0 == wcscmp(CDSL_Dialog::s_SourcesSet[i].m_pwszParseName, 
						CDSL_Dialog::s_SourcesSet[nChosen].m_pwszParseName))
			continue;

		// call with bad filter combination
		memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
		pwszProgID = NULL;
		TESTC_(ProgIDFromCLSID(CDSL_Dialog::s_SourcesSet[nChosen], &pwszProgID), S_OK);
		wcscpy(pNext, pwszProgID);
		SAFE_FREE(pwszProgID);

		TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, cSrcType, rgSrcType, 
			wszProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

		TESTC(Dialog.IsResult(DB_E_NOPROVIDERSREGISTERED));
		TESTC(NULL == pIDBInitialize);

		// call with good filter combination
		memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
		wcscpy(pNext, CDSL_Dialog::s_SourcesSet[i].m_pwszName);
		odtLog << "\t" << CDSL_Dialog::s_SourcesSet[i].m_pwszName << "\n"; 

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
	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator?
		if (	DBSOURCETYPE_DATASOURCE != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_TDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != CDSL_Dialog::s_SourcesSet[i].m_wType)
			continue;
		
		// get the filter
		if (cProvFilterLen + wcslen(CDSL_Dialog::s_SourcesSet[i].m_pwszName) > nMaxProv*cMaxName)
			break;
		wcscat(pwszProviderFilter, CDSL_Dialog::s_SourcesSet[i].m_pwszName);
		cProvFilterLen		+= wcslen(pwszProviderFilter) + 1; 
		pwszProviderFilter	+= wcslen(pwszProviderFilter) + 1;
		odtLog << "\t\t" << (WCHAR*)CDSL_Dialog::s_SourcesSet[i] << "\n";
	}

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, wszProviderFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	Sleep(2000);
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
	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator?
		if (	DBSOURCETYPE_DATASOURCE != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_TDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != CDSL_Dialog::s_SourcesSet[i].m_wType)
			continue;
		
		// get the filter
		if (cProvFilterLen + wcslen(CDSL_Dialog::s_SourcesSet[i].m_pwszName) > nMaxProv*cMaxName)
			break;
		wcscat(pwszProviderFilter, CDSL_Dialog::s_SourcesSet[i].m_pwszName);
		cProvFilterLen		+= wcslen(pwszProviderFilter) + 1; 
		pwszProviderFilter	+= wcslen(pwszProviderFilter) + 1;
		odtLog << "\t\t" << (WCHAR*)CDSL_Dialog::s_SourcesSet[i] << "\n";
		wcscpy(wszShortProvFilter, CDSL_Dialog::s_SourcesSet[i].m_pwszName);
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
	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator?
		if (	DBSOURCETYPE_DATASOURCE != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_TDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != CDSL_Dialog::s_SourcesSet[i].m_wType)
			continue;
		
		// get the filter
		if (cProvFilterLen + wcslen(CDSL_Dialog::s_SourcesSet[i].m_pwszName) > nMaxProv*cMaxName)
			break;
		wcscat(pwszProviderFilter, CDSL_Dialog::s_SourcesSet[i].m_pwszName);
		cProvFilterLen		+= wcslen(pwszProviderFilter) + 1; 
		pwszProviderFilter	+= wcslen(pwszProviderFilter) + 1;
		odtLog << "\t\t" << (WCHAR*)CDSL_Dialog::s_SourcesSet[i] << "\n";
		wcscpy(wszShortProvFilter, CDSL_Dialog::s_SourcesSet[i].m_pwszName);
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
	WCHAR				wszSeparator[]		= L"\n\t\b";
	ULONG				cSep				= 1 + wcslen(wszSeparator);

	// set provider filter, don't set any src filter 
	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));

	odtLog << "\tFilter is made of:\n";
	// add progids to provider filter
	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count()-1; i++)
	{
		// is it an OLEDB Provider or is it an enumerator?
		if (	DBSOURCETYPE_DATASOURCE != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_TDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != CDSL_Dialog::s_SourcesSet[i].m_wType)
			continue;
		
		// get the filter
		if (cProvFilterLen + wcslen(CDSL_Dialog::s_SourcesSet[i].m_pwszName) > nMaxProv*cMaxName)
			break;
		wcscat(pwszProviderFilter, CDSL_Dialog::s_SourcesSet[i].m_pwszName);
		cProvFilterLen		+= wcslen(pwszProviderFilter) + 1;
		// place a random character
		pwszProviderFilter[wcslen(pwszProviderFilter)] = wszSeparator[rand() % cSep];
		pwszProviderFilter	+= wcslen(pwszProviderFilter) + 1;
		odtLog << "\t\t" << (WCHAR*)CDSL_Dialog::s_SourcesSet[i] << "\n";
	}

	TESTC(Dialog.SpawnPromptDataSource(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
			DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, wszProviderFilter, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize));

	Sleep(2000);
	TESTC(Dialog.IsInExecution());
	TESTC(Dialog.CheckFilters());
	TESTC(Dialog.KillThread());
	TESTC(Dialog.IsResult(S_OK));

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
	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		if (i%2)
		{
			TESTC_(ProgIDFromCLSID(CDSL_Dialog::s_SourcesSet[i], &pwszProgID), S_OK);
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
	for (i=0; i<CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		if (DBSOURCETYPE_DATASOURCE == CDSL_Dialog::s_SourcesSet[i].m_wType)
		{
			for (j=i+1; j<CDSL_Dialog::s_SourcesSet.Count(); j++)
			{
				if (0 == wcscmp(CDSL_Dialog::s_SourcesSet[i].m_pwszParseName, CDSL_Dialog::s_SourcesSet[j].m_pwszParseName))
					break;
			}
			if (j >= CDSL_Dialog::s_SourcesSet.Count())
				break;
		}
	}
	TESTC_PROVIDER(i<CDSL_Dialog::s_SourcesSet.Count());
			
	// set datasource type filter to a bad value for the provider
	rgSrcType[0] = (DBSOURCETYPE_DATASOURCE_TDP == CDSL_Dialog::s_SourcesSet[i].m_wType)?
			DBSOURCETYPE_DATASOURCE_MDP: DBSOURCETYPE_DATASOURCE_TDP;

	memset(wszProviderFilter, 0, sizeof(wszProviderFilter));
	TESTC_(ProgIDFromCLSID(CDSL_Dialog::s_SourcesSet[i], &pwszProgID), S_OK);
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
	HRESULT				fResult					= TEST_PASS;
	DWORD				dwOptions				= GetModInfo()->UseServiceComponents();
	CDSL_Dialog			*pDialog				= NULL;
	BOOL				fIter;

	for (ULONG i=0; i< CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		// print source description
		odtLog << (WCHAR*)CDSL_Dialog::s_SourcesSet[i];

		// if datasource is not a provider skip the iteration
		if (	DBSOURCETYPE_DATASOURCE_TDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			||	CUSTOM_CONN & CDSL_Dialog::s_SourcesSet[i].m_CustomUI)
		{
			odtLog << L"\n";
			continue;
		}

		fIter = FALSE;
		
		TESTC(NULL == pIDBInitialize);

		odtLog << L" no SC";
		// create datasource on the required CLSID
		GetModInfo()->PlugInServiceComponents(0);
		TESTC_(GetModInfo()->CreateProvider((CLSID)CDSL_Dialog::s_SourcesSet[i], NULL, 
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

		odtLog << L", with SC";
		// create datasource on the required CLSID
		GetModInfo()->PlugInServiceComponents(SERVICECOMP_INVOKE);
		TESTC_(GetModInfo()->CreateProvider((CLSID)CDSL_Dialog::s_SourcesSet[i], NULL, 
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

		odtLog << L"\tinexistent DSO";
		// create datasource on the required CLSID
		pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
				DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION, 
				0, NULL, NULL, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

		TESTC(pDialog->IsResult(E_INVALIDARG));
		TESTC(NULL == pIDBInitialize);

		fIter = TRUE;

CLEANUP:
		odtLog << L"\n";
		SAFE_DELETE(pDialog);
		SAFE_RELEASE(pIDBInitialize);	
		if (!fIter)
			odtLog << "\tERROR on " << (WCHAR*)CDSL_Dialog::s_SourcesSet[i] << "!\n";
	}
	GetModInfo()->PlugInServiceComponents(dwOptions);
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
	BOOL				fIter;

	for (ULONG i=0; i< CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		// if datasource is not a provider skip the iteration
		if (	DBSOURCETYPE_DATASOURCE_TDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			||	CUSTOM_CONN & CDSL_Dialog::s_SourcesSet[i].m_CustomUI)
			continue;

		fIter = FALSE;
		// assume that the name in sources rowset is the ProgID
		SAFE_ALLOC(pwszszzProviderFilter, WCHAR, 1+wcslen(CDSL_Dialog::s_SourcesSet[i].m_pwszName));
		wcscpy(pwszszzProviderFilter, CDSL_Dialog::s_SourcesSet[i].m_pwszName);
		wcscat(pwszszzProviderFilter, L"\0");	

		TESTC(NULL == pIDBInitialize);

		// Existent DSO
		// SC, create datasource on the required CLSID
		GetModInfo()->PlugInServiceComponents(SERVICECOMP_INVOKE);
		TESTC_(GetModInfo()->CreateProvider(CDSL_Dialog::s_SourcesSet[i], NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

		odtLog << "\t" << (WCHAR*)CDSL_Dialog::s_SourcesSet[i] << " exist_SC ";		
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
		TESTC_(GetModInfo()->CreateProvider(CDSL_Dialog::s_SourcesSet[i], NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

		odtLog << "\t" << (WCHAR*)CDSL_Dialog::s_SourcesSet[i] << " exist_Non SC ";		
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
		pDialog = new CDSL_Dialog(m_pIDBPromptInitialize, NULL, s_hMainWnd, 
				DBPROMPTOPTIONS_PROPERTYSHEET | DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION, 0, NULL, 
				pwszszzProviderFilter, IID_IDBInitialize, (IUnknown**)&pIDBInitialize);

		odtLog << "inexist ";		
		TESTC(pDialog->IsResult(E_INVALIDARG));
		TESTC(NULL == pIDBInitialize);

		fIter = TRUE;

CLEANUP:
		odtLog << "\n";
		SAFE_DELETE(pDialog);
		SAFE_RELEASE(pIDBInitialize);	
		SAFE_FREE(pwszszzProviderFilter);
		if (!fIter)
			odtLog << "\tERROR on " << (WCHAR*)CDSL_Dialog::s_SourcesSet[i] << "!\n";
	}
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
	BOOL				fIter;

	for (ULONG i=0; i< CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		// if datasource is not a provider skip the iteration
		if (	DBSOURCETYPE_DATASOURCE_TDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			||	CUSTOM_CONN & CDSL_Dialog::s_SourcesSet[i].m_CustomUI)
			continue;

		fIter = FALSE;
		// assume that the name in sources rowset is the ProgID
		SAFE_ALLOC(pwszszzProviderFilter, WCHAR, 1+wcslen(CDSL_Dialog::s_SourcesSet[i].m_pwszName));
		wcscpy(pwszszzProviderFilter, CDSL_Dialog::s_SourcesSet[i].m_pwszName);
		wcscat(pwszszzProviderFilter, L"\0");	

		TESTC(NULL == pIDBInitialize);

		// Existent DSO
		// SC, create datasource on the required CLSID
		GetModInfo()->PlugInServiceComponents(SERVICECOMP_INVOKE);
		TESTC_(GetModInfo()->CreateProvider(CDSL_Dialog::s_SourcesSet[i], NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

		odtLog << "\t" << (WCHAR*)CDSL_Dialog::s_SourcesSet[i] << " exist_SC ";		
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
		TESTC_(GetModInfo()->CreateProvider(CDSL_Dialog::s_SourcesSet[i], NULL, 
			IID_IDBInitialize, (IUnknown**)&pIDBInitialize), S_OK);

		odtLog << "\t" << (WCHAR*)CDSL_Dialog::s_SourcesSet[i] << " exist_Non SC ";		
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

		odtLog << "inexist ";		
		TESTC(pDialog->IsInExecution());
		TESTC(pDialog->HasProviderPage());
		TESTC(pDialog->KillThread(PSBTN_OK));
		TESTC(pDialog->IsResult(S_OK));
		TESTC(NULL != pIDBInitialize);

		fIter = TRUE;

CLEANUP:
		odtLog << "\n";
		SAFE_DELETE(pDialog);
		SAFE_RELEASE(pIDBInitialize);	
		SAFE_FREE(pwszszzProviderFilter);
		if (!fIter)
			odtLog << "\tERROR on " << (WCHAR*)CDSL_Dialog::s_SourcesSet[i] << "!\n";
	}
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

	dwUseSC = GetModInfo()->UseServiceComponents();
	GetModInfo()->PlugInServiceComponents(SERVICECOMP_INVOKE);
	
	for (ULONG i=0; i < CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		if (	DBSOURCETYPE_DATASOURCE_TDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			||	CUSTOM_CONN & CDSL_Dialog::s_SourcesSet[i].m_CustomUI)
			continue;
		
		odtLog << CDSL_Dialog::s_SourcesSet[i].m_pwszName << "\n";	
		CHECK(GetModInfo()->CreateProvider((CLSID)CDSL_Dialog::s_SourcesSet[i], NULL, 
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
	
		TESTC(Dialog.SelectProvider((WCHAR*)CDSL_Dialog::s_SourcesSet[i]));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
		TESTC(Dialog.SetPassword(wszPassword));
		TESTC(Dialog.CheckControlStatus(fSupportedAuthPersist && fSupportedPassword, IDC_SAVEPASSWORD));
		TESTC(Dialog.SetSavePassword(BST_CHECKED));
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));
		

		TESTC(!fSupportedPassword 
			|| GetProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT, 
			pIDBInitialize, &pwszPassword));
		TESTC(!fSupportedPassword || !pwszPassword 
			|| 0 == wcscmp(wszPassword, pwszPassword));
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
		
		TESTC(Dialog.SelectProvider((WCHAR*)CDSL_Dialog::s_SourcesSet[i]));
		TESTC(Dialog.GotoConnectionPage());
		TESTC(Dialog.SetBlankPassword(BST_UNCHECKED));
		TESTC(Dialog.SetPassword(wszPassword));
		TESTC(Dialog.CheckControlStatus(FALSE, IDC_SAVEPASSWORD));
		TESTC(Dialog.KillThread());
		TESTC(Dialog.IsResult(S_OK));

		if (fSupportedAuthPersist)
		{
			TESTC(GetProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, 
				DBPROPSET_DBINIT, pIDBInitialize, &fAuthPersist)
				&& VARIANT_FALSE == fAuthPersist);
			TESTC(	!(GetProperty(DBPROP_AUTH_PASSWORD, 
					DBPROPSET_DBINIT, pIDBInitialize, &pwszPassword))
				||	!pwszPassword
				||	0 == wcscmp(wszPassword, pwszPassword))
		}
		else
		{
			TESTC(	!(GetProperty(DBPROP_AUTH_PASSWORD, 
					DBPROPSET_DBINIT, pIDBInitialize, &pwszPassword))
				||	!pwszPassword
				||	0 == wcscmp(wszPassword, pwszPassword))
		}
		
CLEANUP:
		COMPARE(Dialog.KillThread(), TRUE);
		SAFE_RELEASE(pIDBInitialize);
		SAFE_RELEASE(pIDBProperties);
		SAFE_FREE(pwszPassword);
	}
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
	CLSID			clsidProvider;

	for (ULONG i=0; i < CDSL_Dialog::s_SourcesSet.Count(); i++)
	{
		if (	DBSOURCETYPE_DATASOURCE_TDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != CDSL_Dialog::s_SourcesSet[i].m_wType
			||	CUSTOM_CONN & CDSL_Dialog::s_SourcesSet[i].m_CustomUI)
			continue;
		
		odtLog << CDSL_Dialog::s_SourcesSet[i].m_pwszName << "\n";
			
		clsidProvider = CDSL_Dialog::s_SourcesSet[i];

		// check all the cases
		CheckDisSavePasswdOnExistingDSO(clsidProvider, FALSE,	FALSE,	FALSE);
		CheckDisSavePasswdOnExistingDSO(clsidProvider, FALSE,	FALSE,	TRUE);
		CheckDisSavePasswdOnExistingDSO(clsidProvider, FALSE,	TRUE,	FALSE);
		CheckDisSavePasswdOnExistingDSO(clsidProvider, FALSE,	TRUE,	TRUE);
		CheckDisSavePasswdOnExistingDSO(clsidProvider, TRUE,	FALSE,	FALSE);
		CheckDisSavePasswdOnExistingDSO(clsidProvider, TRUE,	FALSE,	TRUE);
		CheckDisSavePasswdOnExistingDSO(clsidProvider, TRUE,	TRUE,	FALSE);
		CheckDisSavePasswdOnExistingDSO(clsidProvider, TRUE,	TRUE,	TRUE);
	}
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
	TESTC(Dialog.SelectProvider(CLSID_SQLOLEDB));
	TESTC(Dialog.GotoConnectionPage	());
	TESTC(Dialog.IsControlEnabled(IDC_SAVEPASSWORD));
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


//-----------------------------------------------------------------------------
// OnUnicodeSystem
//
// @func Determine if the OS that we are on, actually supports the unicode verion
// of the win32 API.  If YES, then g_fAnsiRegistry == FALSE.
//
// @rdesc True of False
//------------------------------------------------------------------------------
BOOL OnUnicodeSystem()
{
	static BOOL	fCheckDone = FALSE;
	static BOOL fUnicode = TRUE;

	if( fCheckDone )
		return fUnicode;

	fCheckDone = TRUE;

	HKEY	hkJunk = HKEY_CURRENT_USER;

	// Check to see if we have win95's broken registry, thus
	// do not have Unicode support in the OS
	if ((RegOpenKeyExW(HKEY_LOCAL_MACHINE,
					 L"SOFTWARE",
					 0,
					 KEY_READ,
					 &hkJunk) == ERROR_SUCCESS) &&
		hkJunk == HKEY_CURRENT_USER)
	{

	   // Try the ANSI version
		if ((RegOpenKeyExA(HKEY_LOCAL_MACHINE,
							 "SOFTWARE",
							 0,
							KEY_READ,
							&hkJunk) == ERROR_SUCCESS) &&
			(hkJunk != HKEY_CURRENT_USER))

		{
			fUnicode = FALSE;
		}
	}

	if (hkJunk != HKEY_CURRENT_USER)
		RegCloseKey(hkJunk);

	return fUnicode;
} // OnUnicode


int __stdcall GetWindowTextANSI(HWND hWnd, LPWSTR lpString, int nMaxCount)
{
	int		nMaxCountA = nMaxCount*sizeof(CHAR);
	LPSTR	lpStringA = NULL;
	int		result;

	SAFE_ALLOC(lpStringA, CHAR, nMaxCountA);
	result = GetWindowTextA(hWnd, lpStringA, nMaxCountA);
	if (0 != result)
		result = S_OK == ConvertToWCHAR(lpStringA, lpString, nMaxCount)? nMaxCount: 0;

CLEANUP:
	SAFE_FREE(lpStringA);
	return result;
} //GetWindowTextANSI


// the independent version of GetWindowText
int __stdcall GetWindowTextWRAP( HWND hWnd, LPWSTR lpString, int nMaxCount)
{
	GetWindowTextI = (OnUnicodeSystem()) ? GetWindowTextW : GetWindowTextANSI;

	return GetWindowTextI( hWnd, lpString, nMaxCount);
} // GetWindowTextWRAP


BOOL __stdcall SetWindowTextANSI(HWND hWnd, LPCWSTR lpString)
{
	LPSTR	lpStringA = ConvertToMBCS((WCHAR*)lpString);
	BOOL	bRet;

	bRet = SetWindowTextA(hWnd, lpStringA);
	SAFE_FREE(lpStringA);
	return bRet;
} //SetWindowTextANSI

 
BOOL __stdcall SetWindowTextWRAP( HWND hWnd, LPCWSTR lpString)
{
	SetWindowTextI = (OnUnicodeSystem()) ? SetWindowTextW : SetWindowTextANSI;

	return SetWindowTextI( hWnd, lpString);
} //SetWindowTextWRAP





//-------------------------------------------------------------------------
//	CBasicDialog::PushButton
//		Pushes a dialog button
//		The proper dialog should already be selected
//-------------------------------------------------------------------------
BOOL CBasicDialog::PushButton(int nCtrlID)
{
	TBEGIN
	HWND	hWnd = GetHWND();
	HWND	hCtrlWnd;

	// checked that the control exists
	hCtrlWnd = GetDlgItem(hWnd, nCtrlID);
	TESTC(NULL != hCtrlWnd);

	// send the appropiate message to the button
	PostMessage(hCtrlWnd, BM_CLICK, 0, 0L);
	Sleep(1000);


CLEANUP:
	TRETURN
} //CBasicDialog::PushButton



//-------------------------------------------------------------------------
//	CBasicDialog::SetTextToCtrl
//		Set text to control (it is assumed that the right dialog is selected)
//-------------------------------------------------------------------------
BOOL CBasicDialog::SetTextToCtrl(int nCtrlID, LPCWSTR pwszTextToSet)
{
	TBEGIN
	HWND	hWndCtrl;
	HWND	hWnd				= GetHWND();
	WCHAR	wszText[cMaxName]	= L"";

	TESTC(NULL != pwszTextToSet);

	// get the handle to the field
	hWndCtrl = GetDlgItem(hWnd, nCtrlID);
	TESTC(NULL != hWndCtrl);

	if (!IsWindowEnabled(hWndCtrl))
		return TRUE;

	//set text to control
	TESTC(SetWindowTextI(hWndCtrl, pwszTextToSet));

	// check that the text was set to the field
	TESTC((int)wcslen(pwszTextToSet) == GetWindowTextI(hWndCtrl, wszText, cMaxName));
	TESTC(0 == wcscmp(pwszTextToSet, wszText));

CLEANUP:
	TRETURN
} //CBasicDialog::SetTextToCtrl



//-------------------------------------------------------------------------
//	CBasicDialog::GetTextFromCtrl
//		Get text from control (it is assumed that the right dialog is selected)
//-------------------------------------------------------------------------
BOOL CBasicDialog::GetTextFromCtrl(int nCtrlID, WCHAR *pwszText, int cLen)
{
	TBEGIN
	HWND	hCtrlWnd;
	HWND	hWnd = GetHWND();

	TESTC(NULL != pwszText);

	// get the handle to the field
	hCtrlWnd = GetDlgItem(hWnd, nCtrlID);
	TESTC(NULL != hCtrlWnd);

	//set text to control
	GetWindowTextI(hCtrlWnd, pwszText, cLen);

CLEANUP:
	TRETURN
} //CBasicDialog::GetTextToCtrl



//-------------------------------------------------------------------------
//
//	CBasicDialog::AreControlsEnabled
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CBasicDialog::AreControlsEnabled(
	ULONG	cCtrlID,	// [in] the number of controls checked
	int		*rgCtrlID	// [in]	array of controls checked
)
{
	return CheckControlsStatus(TRUE, cCtrlID, rgCtrlID);
} //CBasicDialog::AreControlsEnabled



//-------------------------------------------------------------------------
//
//	CBasicDialog::AreControlsDisabled
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CBasicDialog::AreControlsDisabled(
	ULONG	cCtrlID,	// [in] the number of controls checked
	int		*rgCtrlID	// [in]	array of controls checked
)
{
	return CheckControlsStatus(FALSE, cCtrlID, rgCtrlID);
} //CBasicDialog::AreControlsDisabled




//-------------------------------------------------------------------------
//
//	CBasicDialog::CheckControlsStatus
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CBasicDialog::CheckControlsStatus(
	BOOL	fStatus,	// [in] the expected status of the control
	ULONG	cCtrlID,	// [in] the number of controls checked
	int		*rgCtrlID	// [in]	array of controls checked
)
{
	TBEGIN
	HWND	hWnd = GetHWND();
	HWND	hWndCtrl;
	ULONG	iCtrl;

	for (iCtrl=0; iCtrl<cCtrlID; iCtrl++)
	{
		hWndCtrl = GetDlgItem(hWnd, rgCtrlID[iCtrl]);
		TESTC(NULL != hWndCtrl);
		TESTC(fStatus == IsWindowEnabled(hWndCtrl));
	}

CLEANUP:
	TRETURN
} //CBasicDialog::CheckControlsStatus




//-------------------------------------------------------------------------
//
//	CBasicDialog::CheckControlStatus
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CBasicDialog::CheckControlStatus(
	BOOL	fStatus,	// [in] the expected status of the control
	int		CtrlID		// [in] the ID of the control
)
{
	TBEGIN

	TESTC(fStatus == IsWindowEnabled(GetDlgItem(GetHWND(), CtrlID)));
CLEANUP:
	TRETURN 
} //CBasicDialog::CheckControlStatus




//-------------------------------------------------------------------------
//	CBasicDialog::CheckDlgButton
//		Check a radio button
//		The proper dialog should already be selected
//-------------------------------------------------------------------------
BOOL CBasicDialog::CheckDlgButton(
	int		nCtrlID,		// [in] the ID of the control
	UINT	uStatus,		// [in] the status to be set		
	ULONG	ulEnabledID,	// [in] number of elements in rgEnabledID
	int		*rgEnabledID,	// [in] array of elements enabled after the set
	ULONG	ulDisabledID,	// [in]	number of elements in rgDisabledID
	int		*rgDisabledID	// [in] array of elements disabled 
)
{
	TBEGIN
	UINT	status;
	HWND	hCtrlWnd;
	HWND	hWnd = GetHWND();

	// checked that the control exists
	hCtrlWnd = GetDlgItem(hWnd, nCtrlID);
	TESTC(NULL != hCtrlWnd);

	if (!IsWindowEnabled(hCtrlWnd))
		return FALSE;

	// check that the control is not grayed
	status = IsDlgButtonChecked(hWnd, nCtrlID);
	TESTC(BST_CHECKED == status || BST_UNCHECKED == status);

	if (status != uStatus)
	{
		SendMessage(hCtrlWnd, BM_CLICK, 0, 0L);
	}

	Sleep(g_ulWaitPeriod);
	TESTC(IsDlgButtonChecked(hWnd, nCtrlID) == uStatus);

	TESTC(AreControlsEnabled(ulEnabledID, rgEnabledID));
	TESTC(AreControlsDisabled(ulDisabledID, rgDisabledID));
	

CLEANUP:
	TRETURN
} //CBasicDialog::CheckDlgButton



//-------------------------------------------------------------------------
//	CBasicDialog::CheckRadioButton
//		Check a radio button in a group
//		The proper dialog should already be selected
//-------------------------------------------------------------------------
BOOL CBasicDialog::CheckRadioButton(
	int		nIDFirst,		// [in] the ID of the first button in the group
	int		nIDLast,		// [in] the ID of the last button in the group
	int		nCtrlID,		// [in] the ID of the control
	ULONG	ulEnabledID,	// [in] number of elements in rgEnabledID
	int		*rgEnabledID,	// [in] array of elements enabled after the set
	ULONG	ulDisabledID,	// [in]	number of elements in rgDisabledID
	int		*rgDisabledID	// [in] array of elements disabled 
)
{
	TBEGIN
	UINT	status;
	HWND	hCtrlWnd;
	HWND	hWnd = GetHWND();

	// checked that the control exists
	hCtrlWnd = GetDlgItem(hWnd, nCtrlID);
	TESTC(NULL != hCtrlWnd);

	// check that the control is not grayed
	status = IsDlgButtonChecked(hWnd, nCtrlID);
	TESTC(BST_CHECKED == status || BST_UNCHECKED == status);

	if (status != BST_CHECKED)
	{
		SendMessage(hCtrlWnd, BM_CLICK, 0, 0L);
	}
	TESTC(IsDlgButtonChecked(hWnd, nCtrlID) == BST_CHECKED);
	TESTC(AreControlsEnabled(ulEnabledID, rgEnabledID));
	TESTC(AreControlsDisabled(ulDisabledID, rgDisabledID));
	
CLEANUP:
	TRETURN
} //CBasicDialog::CheckRadioButton




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::CDSL_Dialog
//		creates DSL thread
//-------------------------------------------------------------------------
CDSL_Dialog::CDSL_Dialog()
{
	m_fIsInExecution		= FALSE;
	m_hThread				= 0;
	m_pIDBPromptInitialize	= NULL;
	m_rgProviderList	= NULL;
	m_cProviderList		= 0;
} //CDSL_Dialog::CDSL_Dialog




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::CDSL_Dialog
//		creates DSL thread
//-------------------------------------------------------------------------
CDSL_Dialog::CDSL_Dialog(CHAR *szUDLFileName)
{
	WCHAR	wszUDLFileName[cMaxName] = L"";

	m_fIsInExecution		= FALSE;
	m_hThread				= 0;
	m_pIDBPromptInitialize	= NULL;
	m_rgProviderList	= NULL;
	m_cProviderList		= 0;
	
	ConvertToWCHAR(szUDLFileName, wszUDLFileName, cMaxName);
	CDSL_Dialog::CDSL_Dialog(wszUDLFileName);
} //CDSL_Dialog::CDSL_Dialog




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::CDSL_Dialog
//		creates DSL thread
//-------------------------------------------------------------------------
CDSL_Dialog::CDSL_Dialog(WCHAR *wszUDLFileName) : CBasicDialog(TRUE)
{
	m_fIsInExecution		= FALSE;
	m_hThread				= 0;
	m_pIDBPromptInitialize	= NULL;
	m_rgProviderList	= NULL;
	m_cProviderList		= 0;

	TESTC(SpawnUDLFile(wszUDLFileName));
CLEANUP:
	return;
} //CDSL_Dialog::CDSL_Dialog




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::CDSL_Dialog
//		creates DSL thread
//-------------------------------------------------------------------------
CDSL_Dialog::CDSL_Dialog(
	IDBPromptInitialize		*pIDBPromptInitialize,
	IUnknown				*pUnkOuter,
	HWND					hWndParent,
	DBPROMPTOPTIONS			dwPromptOptions,
	ULONG					cSourceTypeFilter,
	DBSOURCETYPE			*rgSourceTypeFilter,
	LPCOLESTR				pwszszzProviderFilter,
	REFIID					riid,
	IUnknown				**ppDataSource
) : CBasicDialog(TRUE)
{
	m_fIsInExecution		= FALSE;
	m_hThread				= 0;
	m_pIDBPromptInitialize	= NULL;
	m_rgProviderList	= NULL;
	m_cProviderList		= 0;

	TESTC(SpawnPromptDataSource(pIDBPromptInitialize, pUnkOuter,
		hWndParent,	dwPromptOptions, cSourceTypeFilter, rgSourceTypeFilter,
		pwszszzProviderFilter, riid, ppDataSource));
CLEANUP:
	return;
} //CDSL_Dialog::CDSL_Dialog




CDSL_Dialog::~CDSL_Dialog()
{
	KillThread();
	FreeProviderList();
} //CDSL_Dialog::~CDSL_Dialog




//-------------------------------------------------------------------------
//	CDSL_Dialog::MyThread
//		this is the thread responsible for creating the DSL page
//		returns TRUE on success and FALSE on fail
//-------------------------------------------------------------------------
unsigned WINAPI CDSL_Dialog::MyThread(void *p)
{
	TBEGIN
	CDSL_Dialog		*pThis = (CDSL_Dialog*)p;
	IUnknown		*pOldDataSource = pThis->m_ppDataSource? *pThis->m_ppDataSource: NULL;

	CoInitialize(NULL);
	
	pThis->m_fIsInExecution = TRUE;
	pThis->m_hWnd			= 0;
	pThis->m_hres = pThis->m_pIDBPromptInitialize ->PromptDataSource(
			pThis->m_pUnkOuter,
			pThis->m_hParentWnd,
			pThis->m_dwPromptOptions,
			pThis->m_cSourceTypeFilter,
			pThis->m_rgSourceTypeFilter,
			pThis->m_pwszszzProviderFilter,
			*(pThis->m_piid),
			pThis->m_ppDataSource
		);
	pThis->m_fIsInExecution = FALSE;

	// if failure *pThis->m_ppDataSource should be NULL
	if (FAILED(pThis->m_hres) 
		&& !COMPARE(pOldDataSource == (pThis->m_ppDataSource? *pThis->m_ppDataSource: NULL), TRUE))
		odtLog << "*ppDataSource was modified on a failing IDBPromptInitialize::PromptDataSource call.\n";

	// if success *pThis->m_ppDataSource should be not NULL	
	if (SUCCEEDED(pThis->m_hres))
	{
		if (!COMPARE(pThis->m_ppDataSource && NULL != *pThis->m_ppDataSource, TRUE))
			odtLog << "On success IDBPromptInitialize pThis->m_ppDataSource is NULL or it returns a NULL pThis->m_ppDataSource\n";
	}

	CoUninitialize();
	_endthreadex(TESTB);
	TRETURN
} //CDSL_Dialog::MyThread




//-------------------------------------------------------------------------
//	CDSL_Dialog::CheckWindowPosition
//		Checks the window position related to the parent one and to the desktop range
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::CheckWindowPosition()
{
	TBEGIN
	HWND	hParent = GetParent(m_hWnd);
	RECT	rParent;
	RECT	rWnd;
	RECT	rDesktop;
	LONG	lParentXCenter;
	LONG	lParentYCenter;
	LONG	lChildWidth;
	LONG	lChildHeight;
	
	// check the position of the dialog box
	COMPARE(hParent == m_hParentWnd
		|| 0 == hParent && GetDesktopWindow() == m_hParentWnd, TRUE);

	if (NULL == hParent)
		hParent = GetDesktopWindow();

	COMPARE(GetWindowRect(m_hWnd, &rWnd), TRUE);
	COMPARE(GetWindowRect(hParent, &rParent), TRUE);
	COMPARE(GetWindowRect(GetDesktopWindow(), &rDesktop), TRUE);

	// compute dimensions of the parent window
	lParentXCenter	= (rParent.right + rParent.left)/2;
	lParentYCenter	= (rParent.bottom + rParent.top)/2;

	// compare the dimensions of the child window
	lChildWidth		= rWnd.right - rWnd.left;
	lChildHeight	= rWnd.bottom - rWnd.top;

	if (lParentXCenter > lChildWidth/2)
	{
		if (rParent.right <= rDesktop.right)
		{
			COMPARE(rWnd.left + lChildWidth/2 == lParentXCenter, TRUE);
		}
		else
		{
			// the parent window exceeds the right limit of the desktop 
			COMPARE(rWnd.right < rDesktop.right, TRUE);
		}
	}
	else
	{
		COMPARE(0 == rWnd.left, TRUE);
	}
	if (lParentYCenter > lChildHeight/2)
	{
		if (rParent.bottom <= rDesktop.bottom)
		{
			COMPARE(rWnd.top + lChildHeight/2 == lParentYCenter, TRUE);
		}
		else
		{
			// the parent window exceeds the right limit of the desktop 
			COMPARE(rWnd.bottom < rDesktop.bottom, TRUE);
		}
	}
	else
	{
			COMPARE(0 == rWnd.top, TRUE);
	}

	TRETURN
} //CDSL_Dialog::CheckWindowPosition




//-------------------------------------------------------------------------
//	CDSL_Dialog::SpawnPromptDataSource
//		spawns a new thread that creates the UI
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SpawnPromptDataSource(
	IDBPromptInitialize		*pIDBPromptInitialize,
	IUnknown				*pUnkOuter,
	HWND					hWndParent,
	DBPROMPTOPTIONS			dwPromptOptions,
	ULONG					cSourceTypeFilter,
	DBSOURCETYPE			*rgSourceTypeFilter,
	LPCOLESTR				pwszszzProviderFilter,
	REFIID					riid,
	IUnknown				**ppDataSource
)
{
	TBEGIN
	HWND			hWnd, hEditWnd;
	HWND			hCrtWnd;
	CHAR			szWindowName[cMaxName] = "";

	m_fIsPropertySheet	= TRUE;
	m_fExistingDSO		= ppDataSource && *ppDataSource;
	if (m_fIsInExecution)
		TESTC(KillThread());

	// spwan a new thread for DSL
	m_CreationMethod = DSL_CM_INTERFACE;
	m_hThread = 0;

	// init some variables
	m_pUnkOuter				= pUnkOuter;
	m_hParentWnd			= hWndParent;
	m_dwPromptOptions		= dwPromptOptions;
	m_cSourceTypeFilter		= cSourceTypeFilter;
	m_rgSourceTypeFilter	= rgSourceTypeFilter;
	m_pwszszzProviderFilter = pwszszzProviderFilter;
	m_piid					= &riid;
	m_ppDataSource			= ppDataSource;

	m_cProviderList			= 0;
	m_rgProviderList		= NULL;

	ASSERT(pIDBPromptInitialize);
	pIDBPromptInitialize->AddRef();
	m_pIDBPromptInitialize	= pIDBPromptInitialize;
	
	wcscpy(m_wszUserID, L"");
	wcscpy(m_wszPassword, L"");
	wcscpy(m_wszInitDataSource, L"");
	SetDenySPInClear(FALSE);
	
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, CDSL_Dialog::MyThread,
					(void*)this,
					0, 
					&m_IDThread);
	
	// check that the thread was created
	TESTC( 0 != m_hThread);

	// wait for the DSL to appear (1 sec)
	// after 1 sec I expect either to have the UI ot the
	// method to have finished its execution
	Sleep(0);
	Sleep(2000);

	// just a hack for easier debugging
	if (FALSE)
	{
		for (; TRUE;)
			Sleep(0);
	}

	// get the foreground window and make sure it has focus
	hWnd = GetForegroundWindow();

	// check its caption
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	if (0 == strcmp(szWindowName, g_szIDS_DSL_TITLE_PROPERTY_PAGE))
		m_hWnd = hWnd;
	else
		// just look for a window of this class
		m_hWnd	= FindWindowA("#32770", g_szIDS_DSL_TITLE_PROPERTY_PAGE);

	TESTC(!m_fIsInExecution || NULL != m_hWnd);

	if (m_fIsInExecution)
	{
		COMPARE(CheckWindowPosition(), TRUE);

		// if dialog is up and filter is made of a single provider
		// check that the connection page is displayed
		if (	m_fExistingDSO
			||	m_pwszszzProviderFilter && L'\0' == m_pwszszzProviderFilter[1+wcslen(m_pwszszzProviderFilter)])
		{
			// make sure the connection page was obtained
			// if the filter is made of a single provider and the DSL is started
			// then the filter must have worked and the page displayed is the connection one
			TESTC(IsCurrentPage(g_nConnection));

			// init the already known values 
			hEditWnd = GetDlgItem(m_hConnection, IDC_DBPROP_INIT_DATASOURCE);
			if (NULL != hEditWnd && IsWindowEnabled(hEditWnd))
				GetTextFromCtrl(IDC_DBPROP_INIT_DATASOURCE, m_wszInitDataSource, cMaxName);

			hEditWnd = GetDlgItem(m_hConnection, IDC_DBPROP_AUTH_USERID);
			if (NULL != hEditWnd && IsWindowEnabled(hEditWnd))
				GetTextFromCtrl(IDC_DBPROP_AUTH_USERID, m_wszUserID, cMaxName);

			hEditWnd = GetDlgItem(m_hConnection, IDC_DBPROP_AUTH_PASSWORD);
			if (NULL != hEditWnd && IsWindowEnabled(hEditWnd))
				GetTextFromCtrl(IDC_DBPROP_AUTH_PASSWORD, m_wszPassword, cMaxName);
		}

		// if filters were specified check them
		if (	m_pwszszzProviderFilter
			||	(0 < m_cSourceTypeFilter && NULL != m_rgSourceTypeFilter))
		{
			TESTC(CheckFilters());
		}

		// get the default values
		hCrtWnd = PropSheet_GetCurrentPageHwnd(m_hWnd);
		TESTC(NULL != hCrtWnd);
		//TESTC(GotoConnectionPage());

		//TESTC(PropSheet_SetCurSel(m_hWnd, hCrtWnd, 0));
	}


CLEANUP:
	TRETURN
} //CDSL_Dialog::SpawnPromptDataSource


//-------------------------------------------------------------------------
//	CDSL_Dialog::MyUDLThread
//		this is the thread responsible for creating the DSL page
//		the method is called from the constructor
//		returns TRUE on success and FALSE on fail
//-------------------------------------------------------------------------
unsigned WINAPI CDSL_Dialog::MyUDLThread(void *p)
{
	TBEGIN
	CDSL_Dialog		*pThis = (CDSL_Dialog*)p;
	void			(CALLBACK *pfOpenDSLFile)(HWND,HINSTANCE,LPSTR,int);
	CHAR			*pszUDLFileName = NULL;

	pThis->m_fIsInExecution = TRUE;
	pThis->m_hres = E_FAIL;
	CoInitialize(NULL);

	pfOpenDSLFile = (void (CALLBACK*)(HWND,HINSTANCE,LPSTR,int))
			GetProcAddress(g_hLibInst, "OpenDSLFile");

	pszUDLFileName = ConvertToMBCS(pThis->m_wszUDLFileName);
	TESTC(NULL != pfOpenDSLFile);
	(*pfOpenDSLFile)(0, g_hLibInst, pszUDLFileName, SW_SHOWNORMAL);
	
	pThis->m_hres = S_OK;

CLEANUP:
	SAFE_FREE(pszUDLFileName);
	pThis->m_fIsInExecution = FALSE;
	CoUninitialize();

	_endthreadex(TESTB);
	TRETURN
} //CDSL_Dialog::MyUDLThread




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::SpawnUDLFile
//		creates DSL thread
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SpawnUDLFile(WCHAR *wszUDLFileName)
{
	TBEGIN
	HWND			hWnd;
	HWND			hEditWnd;
	CHAR			szWindowName[cMaxName] = "";

	m_fIsPropertySheet	= TRUE;
	m_fExistingDSO		= FALSE;
	if (m_fIsInExecution)
		TESTC(KillThread());


	// spwan a new thread for DSL
	m_CreationMethod = DSL_CM_UDL;
	m_hThread = 0;
	wcscpy(m_wszUDLFileName, wszUDLFileName);

	m_cProviderList			= 0;
	m_rgProviderList		= NULL;
	m_hParentWnd			= NULL;

	// init some variables
	wcscpy(m_wszUserID, L"");
	wcscpy(m_wszPassword, L"");
	wcscpy(m_wszInitDataSource, L"");
	SetDenySPInClear(TRUE);
	
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, CDSL_Dialog::MyUDLThread,
					(void*)this,
					0, 
					&m_IDThread);
	
	// check that the thread was created
	TESTC( 0 != m_hThread);

	// wait for the DSL to appear (1sec)
	// after 1 sec I expect either to have the UI ot the
	// method to have finished its execution
	Sleep(1000);

	// this code is just for debugging purposes
	if (FALSE)
	{
		for (; TRUE;)
			Sleep(0);
	}

	// get the foreground window and make sure it has focus
	hWnd	= GetForegroundWindow();

	// check its caption
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	if (0 == strcmp(szWindowName, g_szIDS_DSL_TITLE_PROPERTY_PAGE))
		m_hWnd = hWnd;
	else
		// just look for a window of this class
		m_hWnd	= FindWindowA("#32770", g_szIDS_DSL_TITLE_PROPERTY_PAGE);

	TESTC(!m_fIsInExecution || NULL != m_hWnd);

	if (m_fIsInExecution)
	{
		TESTC(IsCurrentPage(g_nConnection));
//		COMPARE(CheckWindowPosition(), TRUE);

		hEditWnd = GetDlgItem(PropSheet_GetCurrentPageHwnd(m_hWnd), IDC_DBPROP_INIT_DATASOURCE);
		if (NULL != hEditWnd && IsWindowEnabled(hEditWnd))
			GetTextFromCtrl(IDC_DBPROP_INIT_DATASOURCE, m_wszInitDataSource, cMaxName);
		
		hEditWnd = GetDlgItem(PropSheet_GetCurrentPageHwnd(m_hWnd), IDC_DBPROP_AUTH_USERID);
		if (NULL != hEditWnd && IsWindowEnabled(hEditWnd))
			GetTextFromCtrl(IDC_DBPROP_AUTH_USERID, m_wszUserID, cMaxName);

		hEditWnd = GetDlgItem(PropSheet_GetCurrentPageHwnd(m_hWnd), IDC_DBPROP_AUTH_PASSWORD);
		if (NULL != hEditWnd && IsWindowEnabled(hEditWnd))
			GetTextFromCtrl(IDC_DBPROP_AUTH_PASSWORD, m_wszPassword, cMaxName);
	}

CLEANUP:
	TRETURN
} //CDSL_Dialog::SpawnUDLFile


//-------------------------------------------------------------------------
//
//	CDSL_Dialog::IsCurrentPage
//		Check if the current page is the one asked
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::IsCurrentPage(ULONG nPage)
{
	BOOL	fRes						= FALSE;
	CHAR	szText[cMaxName]			= "";
	CHAR	*szDialogName[]	= {	
											g_szIDD_PROVIDER_GENERIC, 
											g_szIDD_CONNECTION_GENERIC, 
											g_szIDD_ADVANCED_GENERIC, 
											g_szIDD_SUMMARY_GENERIC};
	HWND	hCrtWnd						= PropSheet_GetCurrentPageHwnd(m_hWnd);
	BOOL	fDisProv					= m_dwPromptOptions & DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION;

	TESTC(nPage < 4);
	TESTC(!fDisProv || nPage > 0);
	TESTC(NULL != hCrtWnd);

	// get the title of the current dialog
	TESTC(0 != GetWindowTextA(hCrtWnd, szText, cMaxName));
	
	// check whether we already are in the desired dialog
	fRes = (0 == strcmp(szText, szDialogName[nPage]));

CLEANUP:
	return fRes;
} //CDSL_Dialog::IsCurrentPage




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::GotoPage
//		select a certain tab in DSL page
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GotoPage(ULONG nPage)
{
	BOOL	fRes = FALSE;
	HWND	hCrtWnd;
	BOOL	fDisableProvider = m_dwPromptOptions & DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION;
	
	TESTC(nPage < 4);

	// check whether we already are in the desired dialog
	if (!IsCurrentPage(nPage))
	{
		if (fDisableProvider)
		// only 3 pages are displayed (provider page is disabled
			ASSERT(nPage>0);
		
		// select the page
		TESTC(PropSheet_SetCurSel(m_hWnd, 0, fDisableProvider? nPage-1: nPage));
		TESTC(IsCurrentPage(nPage));
	}

	// get the current page
	hCrtWnd = PropSheet_GetCurrentPageHwnd(m_hWnd);

	// and store its handler
	switch (nPage)
	{
		case 0:
			m_hProvider = hCrtWnd;
			break;
		case 1:
			m_hConnection = hCrtWnd;
			break;
		case 2:
			m_hAdvanced = hCrtWnd;
			break;
		case 3:
			m_hAll = hCrtWnd;
			break;
		default:
			ASSERT(FALSE);
	}

	fRes = TRUE;

CLEANUP:
	return fRes;
} //CDSL_Dialog::GotoPage




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::GotoProviderPage
//		select Provider tab in DSL page
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GotoProviderPage()
{
	return GotoPage(g_nProvider);
} //CDSL_Dialog::GotoProviderPage




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::GotoConnectionPage
//		select Connection/Authorize tab in DSL page
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GotoConnectionPage()
{
	CHAR	szText[cMaxName] = "";

	if (GotoPage(g_nConnection))
	{
		// find out whether the password is blank
		if (IsControlEnabled(IDC_BlankPassword))
			m_fBlankPassword = IsDlgButtonChecked(GetHWND(), IDC_BlankPassword);
		return TRUE;
	}
	return FALSE;
} //CDSL_Dialog::GotoConnectionPage




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::GotoAdvancedPage
//		select Advanced tab in DSL page
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GotoAdvancedPage()
{
	return GotoPage(g_nAdvanced);
} //CDSL_Dialog::GotoAdvancedPage




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::GotoAllPage
//		select All tab in DSL page
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GotoAllPage()
{
	return GotoPage(g_nAll);
} //CDSL_Dialog::GotoAllPage




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::GotoAllPage
//		select All tab in DSL page
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::HasProviderPage()
{
	CHAR	szText[cMaxName]			= "";
	CHAR	*szDialogName[]	= {	
											g_szIDD_PROVIDER_GENERIC, 
											g_szIDD_CONNECTION_GENERIC, 
											g_szIDD_ADVANCED_GENERIC, 
											g_szIDD_SUMMARY_GENERIC};
	HWND	hCrtWnd;
	BOOL	fDisProv					= m_dwPromptOptions & DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION;

	TESTC(PropSheet_SetCurSel(m_hWnd, 0, g_nProvider));

	hCrtWnd = PropSheet_GetCurrentPageHwnd(m_hWnd);
	TESTC(NULL != hCrtWnd);

	// get the title of the current dialog
	TESTC(0 != GetWindowTextA(hCrtWnd, szText, cMaxName));
	
	// check whether we already are in the desired dialog
	TESTB = 0 == strcmp(szText, g_szIDD_PROVIDER_GENERIC);

CLEANUP:
	TRETURN
} //CDSL_Dialog::HasProviderPage




//----------------------------------------------------------------------
//
//	CDSL_Dialog::CheckFilters
// check filtering
//----------------------------------------------------------------------
BOOL CDSL_Dialog::CheckFilters()
{
	ULONG	cIdxProv			= 0;
	ULONG	*rgIdxProv			= NULL;
	BOOL	fRes				= FALSE;
	ULONG	cIdxEnum;	// counter on the enumeration array
	ULONG	cIdxPL;		// counter on the provider list
	BOOL	fDisableProvider = m_dwPromptOptions & DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION;

	if (fDisableProvider)
		return TRUE;

	// get the array of index to selected providers
	TESTC(GetFilteredProviders(&cIdxProv, &rgIdxProv));

	// get the list of providers from the list view in the property page
	TESTC(GetListOfProviders());

	// dialog list contains our filtered list
	for (cIdxEnum=0; cIdxEnum<cIdxProv; cIdxEnum++)
	{
		for (cIdxPL=0; cIdxPL<m_cProviderList; cIdxPL++)
		{
			if (0 == wcscmp(m_rgProviderList[cIdxPL], 
				(WCHAR*)s_SourcesSet[rgIdxProv[cIdxEnum]]))
				break;
		}
		// check that the item was found in the provider list
		TESTC(cIdxPL < m_cProviderList);
	}
	
	// dialog list is contained in our filtered list
	for (cIdxPL=0; cIdxPL<m_cProviderList; cIdxPL++)
	{
		for (cIdxEnum=0; cIdxEnum<cIdxProv; cIdxEnum++)
		{
			if (0 == wcscmp(m_rgProviderList[cIdxPL], 
				(WCHAR*)s_SourcesSet[rgIdxProv[cIdxEnum]]))
				break;
		}
		// check that the item was found in the provider list
		TESTC(cIdxEnum<cIdxProv);
	}

	fRes = TRUE;

CLEANUP:
	return fRes;
} //CDSL_Dialog::CheckFilters


//-------------------------------------------------------------------------
//
// Get the description of the current selected provider
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GetProvider()
{
	TBEGIN
	CHAR	szText[cMaxName] = "";

	GotoProviderPage();

	// get the handle to the list of providers
	HWND	hWnd	= GetDlgItem(m_hProvider, IDC_PROVIDER_LIST);
	// get the item that is selected
	ULONG	nItem	= ListView_GetNextItem(hWnd, -1, LVNI_SELECTED);
	ListView_GetItemTextA(hWnd, nItem, 0, szText, cMaxName);
	ConvertToWCHAR(szText, m_wszProviderDescription, cMaxName);
	
	//retrieve the provider from the root sources rowset
	m_clsidProvider = (CLSID)s_SourcesSet[m_wszProviderDescription];
	TRETURN
} //CDSL_Dialog::GetProvider




//-------------------------------------------------------------------------
//
// Get the list of provider descriptions from the provider tab
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GetListOfProviders()
{
	HWND	hWnd = PropSheet_GetCurrentPageHwnd(m_hWnd);
	HWND	hProviderList;
	ULONG	cItem;
	BOOL	fRes = FALSE;
	BOOL	fDisableProvider = m_dwPromptOptions & DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION;
	char	szText[cMaxName] = "";

	if (m_cProviderList)
		FreeProviderList();

	ASSERT(!fDisableProvider);

	GotoProviderPage();
	hProviderList = GetDlgItem(m_hProvider, IDC_PROVIDER_LIST);
	TESTC(NULL != hProviderList);
	
	m_cProviderList	= ListView_GetItemCount(hProviderList);
	SAFE_ALLOC(m_rgProviderList, WCHAR*, m_cProviderList);

	for (cItem=0; cItem<m_cProviderList; cItem++)
	{
		szText[0] = '\0';
		// get the provider description (Ansi or unicode)
		ListView_GetItemTextA(hProviderList, cItem, 0, szText, cMaxName);
		m_rgProviderList[cItem] = ConvertToWCHAR(szText);
	}

	fRes = TRUE;

CLEANUP:
	if (hWnd != m_hProvider)
		PropSheet_SetCurSel(m_hWnd, hWnd, 0);
	
	return fRes;
} //CDSL_Dialog::GetListOfProviders




//--------------------------------------------------------------------------
//	CDSL_Dialog::GetPropertyValueFromSummary
//		Get property value from DBPROPID
//		searches the all tab for the value of a certain property
//		returns TRUE if the property was found|FALSE otherwise
//		(This method assumes that CacheAllProperties was called before it)
//--------------------------------------------------------------------------
BOOL CDSL_Dialog::GetPropertyValueFromSummary(
	DBPROPID	dwPropertyID,	// [in] property ID
	WCHAR		**ppszValue		// [out] property value from summary
)
{
	BOOL			fRes = FALSE;
	IDBProperties	*pIDBProperties = NULL;
	ULONG			cInfoPropSet		= 0;
	DBPROPINFOSET	*rgInfoPropSet		= NULL;
	OLECHAR			*pDescBuffer		= NULL;
	ULONG			cProp, cPropSet;
	WCHAR			*pwszPropDescription	= NULL;

	// get provider's clsid and use it to create a DSO 
	GetProvider();
	TESTC_(GetModInfo()->CreateProvider(m_clsidProvider, NULL, 
		IID_IDBProperties, (IUnknown**)&pIDBProperties), S_OK);

	// get property info set
	TESTC_(pIDBProperties->GetPropertyInfo(	0, NULL, &cInfoPropSet, 
		&rgInfoPropSet, &pDescBuffer), S_OK);

	// look for the property ID and retrieve the description
	for (cPropSet=0; cPropSet<cInfoPropSet; cPropSet++)
	{
		DBPROPINFOSET	*pPropSet = &rgInfoPropSet[cPropSet];
		for (cProp=0; cProp<pPropSet->cPropertyInfos; cProp++)
		{
			// compare description against property description
			if (pPropSet->rgPropertyInfos[cProp].dwPropertyID == dwPropertyID)
			{
				pwszPropDescription = pPropSet->rgPropertyInfos[cProp].pwszDescription;
				TESTC(NULL != pwszPropDescription);
				break;
			}
		}
		if (cProp < rgInfoPropSet[cPropSet].cPropertyInfos)
			break;
	}
	// was the property found (must have been)
	TESTC(cPropSet < cInfoPropSet);

	// pass the call to the other GetPropertyValueFromSummary method
	TESTC(GetPropertyValueFromSummary(pwszPropDescription, ppszValue));

	fRes = TRUE;

CLEANUP:
	FreeProperties(&cInfoPropSet, &rgInfoPropSet, &pDescBuffer);
	SAFE_RELEASE(pIDBProperties);
	return fRes;
} //CDSL_Dialog::GetPropertyValueFromSummary




//--------------------------------------------------------------------------
//	CDSL_Dialog::GetPropertyValueFromSummary
//		Get property value from property description
//		searches the all tab for the value of a certain property
//		returns TRUE if the property was found|FALSE otherwise
//		(This method assumes that CacheAllProperties was called before it)
//--------------------------------------------------------------------------
BOOL CDSL_Dialog::GetPropertyValueFromSummary(
	WCHAR		*pwszPropDesc,	// [in] property ID
	WCHAR		**ppwszValue	// [out] property value from summary
)
{
	BOOL			fRes = FALSE;
	ULONG			cInitProp;

	// look for the description in the property array of summary page
	for (cInitProp=0; cInitProp<m_cInitProp; cInitProp++)
	{
		if (0 == wcscmp(pwszPropDesc, m_rgInitProp[cInitProp].pwszPropDescription))
			break;
	}

	TESTC(cInitProp < m_cInitProp);
	ASSERT(ppwszValue);
	
	*ppwszValue = m_rgInitProp[cInitProp].pwszPropValue;

	fRes = TRUE;

CLEANUP:
	return fRes;
} //CDSL_Dialog::GetPropertyValueFromSummary




//-------------------------------------------------------------------------
//	CDSL_Dialog::GetInitMode
//		Get the init mode
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GetInitMode(LONG *plInitMode)
{
	BOOL	fRes		= FALSE;
	LONG	lInitMode	= 0;
	ULONG	i, cItem;
	char	szText[cMaxName] = "";
	char	*pszMode = NULL;
	HWND	hWnd;
	
	ASSERT(NULL != plInitMode);

	// get the handle of the list view control
	hWnd = GetDlgItem(m_hAll, IDC_ALL_PROPERTIES);
	
	// find the number of the items in the list
	cItem =  ListView_GetItemCount(hWnd);

	for (i=0; i<cItem; i++)
	{
		// build the property description string
		ListView_GetItemTextA(hWnd, i, 0, szText, cMaxName);
		if (0 == strcmp(szText, "Mode"))
			break;
	}
	
	TESTC(i < cItem);
	
	// build the property value string
	szText[0] = '\0';
	ListView_GetItemTextA(hWnd, i, 1, szText, cMaxName);
	pszMode = strtok(szText, "|");
	for (; pszMode; pszMode = strtok(NULL , "|"))
	{
		if ( 0 == strcmp(pszMode, "Read"))
			lInitMode |= DB_MODE_READ;
		else if ( 0 == strcmp(pszMode, "Write"))
			lInitMode |= DB_MODE_WRITE;
		else if ( 0 == strcmp(pszMode, "ReadWrite"))
			lInitMode |= DB_MODE_READWRITE;

		else if ( 0 == strcmp(pszMode, "Share Deny Read"))
			lInitMode |= DB_MODE_SHARE_DENY_READ;
		else if ( 0 == strcmp(pszMode, "Share Deny Write"))
			lInitMode |= DB_MODE_SHARE_DENY_WRITE;
		else if ( 0 == strcmp(pszMode, "Share Deny Exclusive"))
			lInitMode |= DB_MODE_SHARE_EXCLUSIVE;
		else if ( 0 == strcmp(pszMode, "Share Deny None"))
			lInitMode |= DB_MODE_SHARE_DENY_NONE;
		else 
			TESTC(FALSE);
	}

	// set the output value
	*plInitMode = lInitMode;

	fRes = TRUE;

CLEANUP:
	return fRes;
} //CDSL_Dialog::GetInitMode




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetInitDataSource
//		Set text in Data Source field
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetInitDataSource(LPCWSTR wszDataSource)
{
	BOOL	fRes;
	ASSERT(wcslen(wszDataSource) < cMaxName);

	if (!IsControlEnabled(IDC_DBPROP_INIT_DATASOURCE))
		return TRUE;

	fRes = SetTextToCtrl(IDC_DBPROP_INIT_DATASOURCE, wszDataSource);

	if (fRes)
		// set variable to value needed (for later comparison)
		wcscpy(m_wszInitDataSource, wszDataSource);
	return fRes;
} //CDSL_Dialog::SetInitDataSource




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetInitMode
//		Set init mode in the Advanced Page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetInitMode(LONG lMode)
{
	TBEGIN
	struct MODE{
		LONG	dbModeVal;
		CHAR	*szModeName;
	};
	MODE		rgValues[] = {
								{DB_MODE_READ,				"Read"}, 
								{DB_MODE_WRITE,				"Write"},
								{DB_MODE_SHARE_DENY_NONE,	"Share Deny None"}, 
								{DB_MODE_SHARE_DENY_READ,	"Share Deny Read"}, 
								{DB_MODE_SHARE_DENY_WRITE,	"Share Deny Write"}, 
							 };
	ULONG		iItem, iPos;
	HWND		hCtrlWnd;
	
	TESTC(IsCurrentPage(g_nAdvanced));

	TESTC(IsControlEnabled(IDC_DBPROP_INIT_MODE));
	hCtrlWnd = GetDlgItem(GetHWND(), IDC_DBPROP_INIT_MODE);

	for (iItem=0; iItem < NUMELEM(rgValues); iItem++)
	{
		LVFINDINFOA		lvFindInfo = {LVFI_STRING, rgValues[iItem].szModeName, 0, NULL, 0};
		iPos = SendMessage(hCtrlWnd, LVM_FINDITEMA, -1, (LPARAM)&lvFindInfo);

		if (lMode & rgValues[iItem].dbModeVal)
		{
			// set the corresponding check box
			ListView_SetCheckState(hCtrlWnd, iPos, TRUE);
		}
		else
		{
			// set the corresponding check box
			ListView_SetCheckState(hCtrlWnd, iPos, FALSE);
		}
	}

CLEANUP:
	TRETURN
} //CDSL_Dialog::SetInitMode




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetImpersonationLevel
//		Set init mode in the SetImpersonationLevel
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetImpersonationLevel(LONG lImpersonationLevel)
{
	TBEGIN
	LONG		lItem;
	HWND		hCtrlWnd;
	WCHAR		wszImpersonationLevel[cMaxName];
	CHAR		szImpersonationLevel[cMaxName];
	const ULONG	cNoOfItems = 4;
	ULONG		ulNoOfItems;

	TESTC(IsCurrentPage(g_nAdvanced));

	TESTC(IsControlEnabled(IDC_DBPROP_INIT_IMPERSONATION_LEVEL));
	hCtrlWnd = GetDlgItem(GetHWND(), IDC_DBPROP_INIT_IMPERSONATION_LEVEL);
	
	ulNoOfItems = SendMessage(hCtrlWnd, CB_GETCOUNT, 0, 0L);
	TESTC(cNoOfItems == ulNoOfItems);

	switch (lImpersonationLevel)
	{
		case DB_IMP_LEVEL_ANONYMOUS:
			wcscpy(wszImpersonationLevel, L"Anonymous");
			strcpy(szImpersonationLevel, "Anonymous");
			break;

		case DB_IMP_LEVEL_IDENTIFY:
			wcscpy(wszImpersonationLevel, L"Identify");
			strcpy(szImpersonationLevel, "Identify");
			break;

		case DB_IMP_LEVEL_IMPERSONATE:
			wcscpy(wszImpersonationLevel, L"Impersonate");
			strcpy(szImpersonationLevel, "Impersonate");
			break;

		case DB_IMP_LEVEL_DELEGATE:
			wcscpy(wszImpersonationLevel, L"Delegate");
			strcpy(szImpersonationLevel, "Delegate");
			break;
		default:
			ASSERT(FALSE);
	}
 
	SendMessage(hCtrlWnd, CB_SHOWDROPDOWN, TRUE, 0L);
	lItem = SendMessage(hCtrlWnd, CB_FINDSTRING, -1, (LPARAM)wszImpersonationLevel);
	lItem = SendMessageA(hCtrlWnd, CB_FINDSTRING, -1, (LPARAM)szImpersonationLevel);
	TESTC(CB_ERR != lItem);

	TESTC(CB_ERR != SendMessage(hCtrlWnd, CB_SETCURSEL, lItem, 0L));
	//SendMessage(hCtrlWnd, CB_SHOWDROPDOWN, FALSE, 0L);

	Sleep(2000);

CLEANUP:
	TRETURN
} //CDSL_Dialog::SetImpersonationLevel




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetProtectionLevel
//		Set init mode in the SetImpersonationLevel
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetProtectionLevel(LONG lProtectionLevel)
{
	TBEGIN
	LONG		lItem;
	HWND		hCtrlWnd;
	WCHAR		wszProtectionLevel[cMaxName];
	CHAR		szProtectionLevel[cMaxName];
	const ULONG	cNoOfItems = 6;
	ULONG		ulNoOfItems;

	TESTC(IsCurrentPage(g_nAdvanced));

	TESTC(IsControlEnabled(IDC_DBPROP_INIT_PROTECTION_LEVEL));
	hCtrlWnd = GetDlgItem(GetHWND(), IDC_DBPROP_INIT_PROTECTION_LEVEL);
	
	ulNoOfItems = SendMessage(hCtrlWnd, CB_GETCOUNT, 0, 0L);
	TESTC(cNoOfItems == ulNoOfItems);

	switch (lProtectionLevel)
	{
		case DB_PROT_LEVEL_NONE:
			wcscpy(wszProtectionLevel, L"None");
			strcpy(szProtectionLevel, "None");
			break;

		case DB_PROT_LEVEL_CONNECT:
			wcscpy(wszProtectionLevel, L"Connect");
			strcpy(szProtectionLevel, "Connect");
			break;

		case DB_PROT_LEVEL_CALL:
			wcscpy(wszProtectionLevel, L"Call");
			strcpy(szProtectionLevel, "Call");
			break;

		case DB_PROT_LEVEL_PKT:
			wcscpy(wszProtectionLevel, L"Pkt");
			strcpy(szProtectionLevel, "Pkt");
			break;

		case DB_PROT_LEVEL_PKT_INTEGRITY:
			wcscpy(wszProtectionLevel, L"Pkt Integrity");
			strcpy(szProtectionLevel, "Pkt Integrity");
			break;

		case DB_PROT_LEVEL_PKT_PRIVACY:
			wcscpy(wszProtectionLevel, L"Pkt Privacy");
			strcpy(szProtectionLevel, "Pkt Privacy");
			break;

		default:
			ASSERT(FALSE);
	}
 
	SendMessage(hCtrlWnd, CB_SHOWDROPDOWN, TRUE, 0L);
	lItem = SendMessage(hCtrlWnd, CB_FINDSTRING, -1, (LPARAM)wszProtectionLevel);
	lItem = SendMessageA(hCtrlWnd, CB_FINDSTRING, -1, (LPARAM)szProtectionLevel);
	TESTC(CB_ERR != lItem);

	TESTC(CB_ERR != SendMessage(hCtrlWnd, CB_SETCURSEL, lItem, 0L));

	Sleep(2000);

CLEANUP:
	TRETURN
} //CDSL_Dialog::SetProtectionLevel




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetUserID
//		Set UserID name
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetUserID(LPCWSTR wszUserID)
{
	BOOL	fRes;
	ASSERT(wcslen(wszUserID) < cMaxName);

	if (!IsControlEnabled(IDC_DBPROP_AUTH_USERID))
		return TRUE;

	fRes = SetTextToCtrl(IDC_DBPROP_AUTH_USERID, wszUserID);
	
	if (fRes)
		// set variable to value needed (for later comparison)
		wcscpy(m_wszUserID, wszUserID);

	return fRes;
} //CDSL_Dialog::SetUserID




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetPassword
//		Set Password text
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetPassword(LPCWSTR wszPassword)
{
	BOOL	fRes;

	ASSERT(wcslen(wszPassword) < cMaxName);

	if (!IsControlEnabled(IDC_DBPROP_AUTH_PASSWORD))
		return TRUE;

	fRes = SetTextToCtrl(IDC_DBPROP_AUTH_PASSWORD, wszPassword);

	if (fRes)
		// set variable to value needed (for later comparison)
		wcscpy(m_wszPassword, wszPassword);

	m_fBlankPassword = IsDlgButtonChecked(GetHWND(), IDC_BlankPassword);
	return fRes;
} //CDSL_Dialog::SetPassword




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetServerName
//		Set server name
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetServerName(LPCWSTR wszServerName)
{
	BOOL	fRes;

	ASSERT(wcslen(wszServerName) < cMaxName);

	if (!IsControlEnabled(IDC_DBPROP_INIT_DATASOURCE))
		return TRUE;
	
	fRes = SetTextToCtrl(IDC_DBPROP_INIT_DATASOURCE, wszServerName);

	if (fRes)
		// set variable to value needed (for later comparison)
		wcscpy(m_wszInitDataSource, wszServerName);

	return fRes;
} //CDSL_Dialog::SetServerName




//-------------------------------------------------------------------------
//	CDSL_Dialog::Database
//		Set database
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetDatabase(LPCWSTR wszDatabase)
{
	if (!IsControlEnabled(IDC_DatabaseOnServerName))
		return TRUE;
	return SetTextToCtrl(IDC_DatabaseOnServerName, wszDatabase);
} //CDSL_Dialog::SetDatabase




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetDatabaseName
//		Set database name
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetDatabaseName(LPCWSTR wszDatabaseName)
{
	if (!IsControlEnabled(IDC_DatabaseFileName))
		return TRUE;
	return SetTextToCtrl(IDC_DatabaseFileName, wszDatabaseName);
} //CDSL_Dialog::SetDatabaseName




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetFileName
//		Set file name 
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetFileName(LPCWSTR wszFileName)
{
	if (!IsControlEnabled(IDC_DBPROP_INIT_FILENAME))
		return TRUE;
	return SetTextToCtrl(IDC_DBPROP_INIT_FILENAME, wszFileName);
} //CDSL_Dialog::FileName




//-------------------------------------------------------------------------
//	CDSL_Dialog::OpenFileBrowser
//		If the provider is Jolt and the page is the connection page
//		Press the browse button (...)
//-------------------------------------------------------------------------
// @cmember Open the file browser (for selecting a datasource file under Jolt)
BOOL CDSL_Dialog::OpenFileBrowser()
{
	TBEGIN
	HWND	hWnd;
	CHAR	szInitDataSource[cMaxName]	= "";
	CHAR	szWindowName[cMaxName]		= "";

	if (	CLSID_JOLT40 != m_clsidProvider
		&&	CLSID_JOLT351 != m_clsidProvider)
		return FALSE;

	if (!IsCurrentPage(g_nConnection))
		return FALSE;

	TESTC(PushButton(IDC_Browse));
	Sleep(1000);
	
	// check that the window popped-up
	// check that a new dialog box has been created with a proper title
	// and get its handle
	// get the foreground window and make sure it has focus
	hWnd = GetForegroundWindow();

	// check its caption
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDS_Jolt_OFNTitle));

CLEANUP:
	TRETURN
} //CDSL_Dialog::OpenFileBrowser




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetFileNameInBrowser (Jolt specific)
//		Choose file in browser 
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetFileNameInBrowser(CHAR *szFileName)
{
	TBEGIN
	HWND	hWnd;
	HWND	hFileName;
	CHAR	szInitDataSource[cMaxName]	= "";
	CHAR	szWindowName[cMaxName]		= "";

	if (	CLSID_JOLT40 != m_clsidProvider
		&&	CLSID_JOLT351 != m_clsidProvider)
		return FALSE;

	// check that the window popped-up
	// check that a new dialog box has been created with a proper title
	// and get its handle
	// get the foreground window and make sure it has focus
	hWnd = GetForegroundWindow();

	// check its caption
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDS_Jolt_OFNTitle));

	hFileName = GetDlgItem(hWnd, edt1);
	TESTC(NULL != hFileName);

	// set the text to the edit control and check its value
	SetWindowTextA(hFileName, szFileName);
	Sleep(1000);
	GetWindowTextA(hFileName, szInitDataSource, cMaxName);
	TESTC(0 == strcmp(szInitDataSource, szFileName));

CLEANUP:
	TRETURN
} //CDSL_Dialog::SetFileNameInBrowser




//-------------------------------------------------------------------------
//	CDSL_Dialog::FileBrowser_OnOpen (Jolt specific)
//		Press Open button in file browser 
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::FileBrowser_OnOpen()
{
	TBEGIN
	HWND	hWnd;
	HWND	hFileName;
	HWND	hOpen;
	HWND	hCancel;
	//CHAR	szInitDataSource[cMaxName]	= "";
	WCHAR	wszInitDataSource[cMaxName]	= L"";
	WCHAR	wszFileName[cMaxName]		= L"";
	CHAR	szWindowName[cMaxName]		= "";
	BOOL	fOpen = FALSE;

	if (	CLSID_JOLT40 != m_clsidProvider
		&&	CLSID_JOLT351 != m_clsidProvider)
		return FALSE;

	// check that the window popped-up
	// check that a new dialog box has been created with a proper title
	// and get its handle
	// get the foreground window and make sure it has focus
	hWnd = GetForegroundWindow();

	// check its caption
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDS_Jolt_OFNTitle));

	hFileName = GetDlgItem(hWnd, edt1);
	TESTC(NULL != hFileName);

	// set the text to the edit control and check its value
	GetWindowTextI(hFileName, wszFileName, cMaxName);
	
	// get handles to the Open (IDOK) and Cancel (IDCANCEL) button
	hOpen = GetDlgItem(hWnd, IDOK);
	TESTC(NULL != hOpen);
	hCancel = GetDlgItem(hWnd, IDCANCEL);
	TESTC(NULL != hCancel);

	// close this window (tentative)
	PostMessage(hOpen, BM_CLICK, 0, 0L);

	Sleep(1000);
	hWnd = GetForegroundWindow();

	// check the caption of the new foreground window
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	if (0 == strcmp(szWindowName, g_szIDS_Jolt_OFNTitle))
	{
		HWND	hOK = GetDlgItem(hWnd, IDCANCEL);

		COMPARE(0 != hOK, TRUE);
		// the file was not found and error is displayed
		// press OK in the error message box (IDCANCEL)
		SendMessage(hOK, BM_CLICK, 0, 0L);
		Sleep(1000);
		// continue by pressing Cancel in the browser window
		SendMessage(hCancel, BM_CLICK, 0, 0L);
		Sleep(1000);
	}
	else
	{
		fOpen = TRUE;
	}

	// check that the foreground window is Data Link Properties dialog box
	hWnd = GetForegroundWindow();
	// check the caption of the new foreground window
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDS_DSL_TITLE_PROPERTY_PAGE));

	GetTextFromCtrl(IDC_DBPROP_INIT_DATASOURCE, wszInitDataSource, cMaxName);
	if (fOpen)
	{
		// check that the text was sent correctly
		TESTC(0 == wcscmp(wszInitDataSource, wszFileName));
		wcscpy(m_wszInitDataSource, wszInitDataSource);
	}
	else
	{
		// the current value should be the previous value
		//ConvertToWCHAR(szInitDataSource, wszInitDataSource, cMaxName);
		TESTC(0 == wcscmp(m_wszInitDataSource, wszInitDataSource));
	}

CLEANUP:
	TRETURN
} //CDSL_Dialog::FileBrowser_OnOpen




//-------------------------------------------------------------------------
//	CDSL_Dialog::FileBrowser_OnCancel (Jolt specific)
//		Press Cancel button in file browser 
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::FileBrowser_OnCancel()
{
	TBEGIN
	HWND	hWnd;
	HWND	hCancel;
	WCHAR	wszInitDataSource[cMaxName]	= L"";
	//CHAR	szInitDataSource[cMaxName]	= "";
	CHAR	szWindowName[cMaxName]		= "";

	if (	CLSID_JOLT40 != m_clsidProvider
		&&	CLSID_JOLT351 != m_clsidProvider)
		return FALSE;

	// check that the window popped-up
	// check that a new dialog box has been created with a proper title
	// and get its handle
	// get the foreground window and make sure it has focus
	hWnd = GetForegroundWindow();

	// check its caption
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDS_Jolt_OFNTitle));

	// get handle to Cancel (IDCANCEL) button
	hCancel = GetDlgItem(hWnd, IDCANCEL);
	TESTC(NULL != hCancel);

	// close this window (tentative)
	SendMessage(hCancel, BM_CLICK, 0, 0L);
	
	hWnd = GetForegroundWindow();

	// check the caption of the new foreground window
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDS_DSL_TITLE_PROPERTY_PAGE));

	// check that the previous datasource is preserved 
	GetTextFromCtrl(IDC_DBPROP_INIT_DATASOURCE, wszInitDataSource, cMaxName);
	// the current value should be the previous value
	//ConvertToWCHAR(szInitDataSource, wszInitDataSource, cMaxName);
	TESTC(0 == wcscmp(m_wszInitDataSource, wszInitDataSource));

CLEANUP:
	TRETURN
} //CDSL_Dialog::FileBrowser_OnCancel




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetInitCatalog (sockeye specific)
//		Set Initial Catalog
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetInitCatalog(WCHAR *pszCatalogName)
{
	if (!IsControlEnabled(IDC_DBPROP_INIT_CATALOG))
		return TRUE;
	return SetTextToCtrl(IDC_DBPROP_INIT_CATALOG, pszCatalogName);
} //CDSL_Dialog::SetInitCatalog




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetProviderString (Sockeye specific)
//		Set Provider String
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetProviderString(WCHAR *pwszProviderString)
{
	if (!IsControlEnabled(IDC_DBPROP_INIT_PROVIDERSTRING))
		return TRUE;
	return SetTextToCtrl(IDC_DBPROP_INIT_PROVIDERSTRING, pwszProviderString);
} //CDSL_Dialog::SetProviderString



//------------------------------------------------------------------------
// CDSL_Dialog::SetConnectionMethod (Sockeye specific)
// set the connection method (datasource name or provider string)
//------------------------------------------------------------------------
BOOL CDSL_Dialog::SetConnectionMethod(int nValue)
{
	HWND	hWndDSN, hWndDSNless;
	ULONG	status1, status2;
	BOOL	fRes = FALSE;

	ASSERT(IDC_Use_DSN == nValue || IDC_Use_DSNless == nValue);

	// check that the 2 buttons exist and are functional
	hWndDSN	= GetDlgItem(m_hConnection, IDC_Use_DSN);
	hWndDSNless	= GetDlgItem(m_hConnection, IDC_Use_DSNless);

	// check that they exist
	TESTC(NULL != hWndDSN);
	TESTC(NULL != hWndDSNless);
	
	// check that exactly one of them was selected
	status1 = IsDlgButtonChecked(m_hConnection, IDC_Use_DSN);
	status2 = IsDlgButtonChecked(m_hConnection, IDC_Use_DSNless);

	TESTC(	(BST_CHECKED == status1 && BST_UNCHECKED == status2)
		||	(BST_UNCHECKED == status1 && BST_CHECKED == status2));

	// set the security method
	if (IDC_Use_DSN == nValue)
	{
		int		rgCtrlID[]={IDC_Use_DSN, 
					IDC_DBPROP_INIT_DATASOURCE,
					IDC_Refresh,
					IDC_Use_DSNless,
					IDC_DBPROP_AUTH_USERID_LABEL,
					IDC_DBPROP_AUTH_USERID,		
					IDC_DBPROP_AUTH_PASSWORD_LABEL,
					IDC_BlankPassword,
				};

		// set security method
		TESTC(CheckRadioButton(IDC_Use_DSN, IDC_Use_DSNless,  
			IDC_Use_DSN, 
			NUMELEM(rgCtrlID), rgCtrlID, 0, NULL));

		TESTC(BST_CHECKED == IsDlgButtonChecked(m_hConnection, IDC_Use_DSN));
		TESTC(BST_UNCHECKED == IsDlgButtonChecked(m_hConnection, IDC_Use_DSNless));
	}
	else
	{
		HWND	hWndPassword = GetDlgItem(m_hConnection, IDC_DBPROP_AUTH_PASSWORD);
		int		rgEnblID[]={IDC_DBPROP_AUTH_USERID, 
					IDC_DBPROP_AUTH_USERID_LABEL,
					IDC_DBPROP_AUTH_PASSWORD_LABEL,
					IDC_BlankPassword,
					IDC_USE_INTEGRATED,
					IDC_USE_STANDARD};

		// set security method
		TESTC(CheckRadioButton(IDC_Use_DSN, IDC_Use_DSNless,
			IDC_Use_DSNless, 
			NUMELEM(rgEnblID), rgEnblID, 0, NULL));
		TESTC(BST_UNCHECKED == IsDlgButtonChecked(m_hConnection, IDC_Use_DSN));
		TESTC(BST_CHECKED == IsDlgButtonChecked(m_hConnection, IDC_Use_DSNless));
	}
	fRes = TRUE;

CLEANUP:
	return fRes;
} //CDSL_Dialog::SetConnectionMethod



//-------------------------------------------------------------------------
//	CDSL_Dialog::TestConnection
//		Press the "Test Connection" button in the connection dialog
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::TestConnection(BOOL fVal)
{
	TBEGIN
	BOOL		fActualVal;

	TESTC(TestConnection(&fActualVal));
	if (fVal != fActualVal)
		odtLog << "\nThe result of test connection is different than expected\n";
	TESTC(fVal == fActualVal);

CLEANUP:
	TRETURN
} //CDSL_Dialog::TestConnection





//-------------------------------------------------------------------------
//	CDSL_Dialog::TestConnection
//		Press the "Test Connection" button in the connection dialog
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::TestConnection(BOOL *pfVal)
{
	TBEGIN
	CHAR	szWindowName[cMaxName] = "";
	HWND	hWnd;
	HWND	hIDOK;
	BOOL	fActualVal	= FALSE;
	ULONG	nIter		= 30;

	TESTC(GotoConnectionPage());
	Sleep(1000);
	TESTC(PushButton(IDC_TestConnection));
	
	for (;nIter; --nIter)
	{
		Sleep(1000);

		// check whether Rosebud init window has poped up
		hWnd = GetForegroundWindow();
		// check its caption
		GetWindowTextA(hWnd, szWindowName, cMaxName);
		if (0 != strcmp(szWindowName, g_szIDS_DSL_TITLE_PROPERTY_PAGE))
			break;
	}

	if (0 == strcmp(szWindowName, "Microsoft OLE DB Provider for Internet Publishing"))
	{
		// close the friendly window
		CBasicDialog	Dialog(FALSE, hWnd);
		TESTC(Dialog.PushButton(IDCANCEL));
		Sleep(1000);
		hWnd = GetForegroundWindow();
		// check its caption
		GetWindowTextA(hWnd, szWindowName, cMaxName);
	}
 
	if (0 == strcmp(szWindowName, g_szIDS_TITLE_DATA_LINK_SUCCESS))
		fActualVal = TRUE;
	else if (0 == strcmp(szWindowName, g_szIDS_TITLE_DATA_LINK))
		fActualVal = FALSE;
	else
	{
		odtLog << "\n\tUnexpected error when testing connection\n";
		TESTC(FALSE);
	}

	// checked that the control exists
	hIDOK = GetDlgItem(hWnd, IDCANCEL);
	TESTC(NULL != hIDOK);

	// close this window
	SendMessage(hIDOK, BM_CLICK, 0, 0L);

CLEANUP:
	if (pfVal)
		*pfVal = fActualVal;
	TRETURN
} //CDSL_Dialog::TestConnection





//-------------------------------------------------------------------------
//	CDSL_Dialog::SetSavePassword
//		Set save password check box
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetSavePassword(UINT uVal)
{
	if (!IsControlEnabled(IDC_SAVEPASSWORD))
		return TRUE;
	return CheckDlgButton(IDC_SAVEPASSWORD, uVal, 0, NULL, 0, NULL);
} //CDSL_Dialog::SetSavePassword




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetBlankPassword
//		set blank check box 
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetBlankPassword(UINT uVal)
{
	int		rgDisID[]	={IDC_DBPROP_AUTH_PASSWORD};
	BOOL	fRes;

	if (!IsControlEnabled(IDC_BlankPassword))
		return TRUE;

	if (BST_CHECKED == uVal)
		fRes = CheckDlgButton(IDC_BlankPassword, BST_CHECKED, 0, NULL, NUMELEM(rgDisID), rgDisID);
	else
		fRes = CheckDlgButton(IDC_BlankPassword, BST_UNCHECKED, NUMELEM(rgDisID), rgDisID, 0, NULL);
	
	m_fBlankPassword = IsDlgButtonChecked(GetHWND(), IDC_BlankPassword);
	
	return fRes;
} //CDSL_Dialog::SetBlankPassword




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetDatabaseMethod
//		set the database selection method
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetDatabaseMethod(int nValue)
{
	HWND	hWnd1, hWnd2;
	ULONG	status1, status2;
	BOOL	fRes = FALSE;

	ASSERT(	IDC_UseDatabaseOnServerName == nValue 
		||	IDC_UseDatabaseFileName == nValue);

	// check that the 2 buttons exist and are functional
	hWnd1	= GetDlgItem(m_hConnection, IDC_UseDatabaseOnServerName);
	hWnd2	= GetDlgItem(m_hConnection, IDC_UseDatabaseFileName);

	// check that they exist
	TESTC(NULL != hWnd1);
	TESTC(NULL != hWnd2);
	
	// check that exactly one of them was selected
	status1 = IsDlgButtonChecked(m_hConnection, IDC_USE_INTEGRATED);
	status2 = IsDlgButtonChecked(m_hConnection, IDC_USE_STANDARD);

	TESTC(	(BST_CHECKED == status1 && BST_UNCHECKED == status2)
		||	(BST_UNCHECKED == status1 && BST_CHECKED == status2));

	// set the security method
	if (IDC_UseDatabaseOnServerName == nValue)
	{
		int		rgEnID[]	= {IDC_DatabaseOnServerName};
		int		rgDisID[]	= {IDC_DatabaseFileName, IDC_DBPROP_INIT_FILENAME};
								
		// set security method
		TESTC(CheckRadioButton(IDC_UseDatabaseOnServerName, IDC_UseDatabaseFileName,
			IDC_UseDatabaseOnServerName, 
			NUMELEM(rgEnID), rgEnID, NUMELEM(rgDisID), rgDisID));

		//Sleep(1000);
		TESTC(BST_CHECKED == IsDlgButtonChecked(m_hConnection, IDC_UseDatabaseOnServerName));
		TESTC(BST_UNCHECKED == IsDlgButtonChecked(m_hConnection, IDC_UseDatabaseFileName));
	}
	else
	{
		int		rgEnID[]	= {IDC_UseDatabaseFileName, IDC_DBPROP_INIT_FILENAME};
		int		rgDisID[]	= {IDC_DatabaseOnServerName};

		// set security method
		TESTC(CheckRadioButton(IDC_UseDatabaseOnServerName, IDC_UseDatabaseFileName,
			IDC_UseDatabaseFileName,
			NUMELEM(rgEnID), rgEnID, NUMELEM(rgDisID), rgDisID));

		//Sleep(1000);
		TESTC(BST_UNCHECKED == IsDlgButtonChecked(m_hConnection, IDC_UseDatabaseOnServerName));
		TESTC(BST_CHECKED == IsDlgButtonChecked(m_hConnection, IDC_UseDatabaseFileName));
	}
	fRes = TRUE;

CLEANUP:
	return fRes;
} //CDSL_Dialog::SetDatabaseMethod




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetSecurityMethod
//		set the security method
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetSecurityMethod(int nValue)
{
	HWND	hWndNT, hWndSTD;
	ULONG	status1, status2;
	BOOL	fRes = FALSE;

	ASSERT(IDC_USE_INTEGRATED == nValue || IDC_USE_STANDARD == nValue);

	// check that the 2 buttons exist and are functional
	hWndNT	= GetDlgItem(m_hConnection, IDC_USE_INTEGRATED);
	hWndSTD	= GetDlgItem(m_hConnection, IDC_USE_STANDARD);

	// check that they exist
	TESTC(NULL != hWndNT);
	TESTC(NULL != hWndSTD);
	
	// check that exactly one of them was selected
	status1 = IsDlgButtonChecked(m_hConnection, IDC_USE_INTEGRATED);
	status2 = IsDlgButtonChecked(m_hConnection, IDC_USE_STANDARD);

	TESTC(	(BST_CHECKED == status1 && BST_UNCHECKED == status2)
		||	(BST_UNCHECKED == status1 && BST_CHECKED == status2));

	// set the security method
	if (IDC_USE_INTEGRATED == nValue)
	{
		int		rgCtrlID[]={IDC_DBPROP_AUTH_USERID, 
					IDC_DBPROP_AUTH_USERID_LABEL,
					IDC_DBPROP_AUTH_PASSWORD,
					IDC_DBPROP_AUTH_PASSWORD_LABEL,
					IDC_BlankPassword,
					IDC_SAVEPASSWORD};
		int		rgEnCtrlID[]={IDC_USE_INTEGRATED,
					IDC_USE_STANDARD};


		// set security method
		TESTC(CheckRadioButton(IDC_USE_STANDARD, IDC_USE_INTEGRATED,  
			IDC_USE_INTEGRATED, NUMELEM(rgEnCtrlID), rgEnCtrlID,
			NUMELEM(rgCtrlID), rgCtrlID));

		//Sleep(10000);
		TESTC(BST_CHECKED == IsDlgButtonChecked(m_hConnection, IDC_USE_INTEGRATED));
		TESTC(BST_UNCHECKED == IsDlgButtonChecked(m_hConnection, IDC_USE_STANDARD));
	}
	else
	{
		// standard security services
		HWND	hWndPassword = GetDlgItem(m_hConnection, IDC_DBPROP_AUTH_PASSWORD);
		int		rgEnblID[]={IDC_DBPROP_AUTH_USERID, 
					IDC_DBPROP_AUTH_USERID_LABEL,
					IDC_DBPROP_AUTH_PASSWORD_LABEL,
					IDC_BlankPassword,
					IDC_USE_INTEGRATED,
					IDC_USE_STANDARD};

		// set security method
		TESTC(CheckRadioButton(IDC_USE_STANDARD, IDC_USE_INTEGRATED,
			IDC_USE_STANDARD, 
			NUMELEM(rgEnblID), rgEnblID, 0, NULL));
		TESTC(BST_UNCHECKED == IsDlgButtonChecked(m_hConnection, IDC_USE_INTEGRATED));
		TESTC(BST_CHECKED == IsDlgButtonChecked(m_hConnection, IDC_USE_STANDARD));
	}
	fRes = TRUE;

CLEANUP:
	return fRes;
} //CDSL_Dialog::SetSecurityMethod




//-------------------------------------------------------------------------
//	CDSL_Dialog::SelectProvider
//		Get the index of the specified provider in rgEnumInfo
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SelectProvider(CLSID clsidProvider)
{
	return SelectProvider((WCHAR*)s_SourcesSet[clsidProvider]);
} //CDSL_Dialog::SelectProvider




//-------------------------------------------------------------------------
//	CDSL_Dialog::SelectProvider
//		Get the index of the specified provider in rgEnumInfo
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SelectProvider(WCHAR *pwszProviderDescription)
{
	TBEGIN
	HWND	hWndProviderList;
	CHAR	*pszProviderDescription	= NULL;
	ULONG	i;
	ULONG	iSel;

	odtLog << "Provider to be selected:" << pwszProviderDescription << "\n";

	// select provider tab
	GotoProviderPage();
	// get the window handle of the provide listview
	TESTC(NULL != (hWndProviderList = GetDlgItem(m_hProvider, IDC_PROVIDER_LIST)));

	// get a comparable ANSII string
	pszProviderDescription = ConvertToMBCS(pwszProviderDescription);
	TESTC(NULL != pszProviderDescription);

	// find the item that fits description
	{
		LVFINDINFOA		lvFindInfo = {LVFI_STRING, pszProviderDescription, 0, NULL, 0};
		i = SendMessage(hWndProviderList, LVM_FINDITEMA, -1, (LPARAM)&lvFindInfo);
		// select this item
		LV_SetItemState(hWndProviderList, i, 0, LVIS_SELECTED, LVIS_SELECTED);
		iSel = ListView_GetNextItem(hWndProviderList, -1, LVNI_SELECTED);
		TESTC(iSel == i);
	}

	// look for the CLSID
	wcscpy(m_wszProviderDescription, pwszProviderDescription);
	m_clsidProvider = (CLSID)s_SourcesSet[pwszProviderDescription];

	// for Jolt40 set the proper User ID and Password information
	if (!m_fExistingDSO)
	{
		if (CLSID_JOLT40 == m_clsidProvider)
		{
			wcscpy(m_wszUserID, L"Admin");
			wcscpy(m_wszPassword, L"");
			m_fBlankPassword = TRUE;
		}
		else
		{
			wcscpy(m_wszUserID, L"");
			wcscpy(m_wszPassword, L"");
			m_fBlankPassword = FALSE;
		}
	}

CLEANUP:
	SAFE_FREE(pszProviderDescription);
	TRETURN
} //CDSL_Dialog::SelectProvider




//-------------------------------------------------------------------------
//	CDSL_Dialog::SelectAnotherProvider
//		Select another provider than the current one from Provider Page
// if the Provider Page doesn't exist, the method fails
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SelectAnotherProvider()
{
	TBEGIN
	ULONG				ulProvIndx;

	TESTC(GetListOfProviders());

	TESTC_PROVIDER(1 < this->m_cProviderList);
	ulProvIndx = rand() % m_cProviderList;

	// if we have chosen the current provider, we'll try again (harder)
	if (0 == wcscmp(m_wszProviderDescription, m_rgProviderList[ulProvIndx]))
		ulProvIndx = (ulProvIndx + 1 + rand() % (m_cProviderList-1)) % m_cProviderList;
	
	// now select the new provider
	TESTC(SelectProvider(m_rgProviderList[ulProvIndx]));

CLEANUP:
	TRETURN
} //CDSL_Dialog::SelectAnotherProvider




//-------------------------------------------------------------------------
//	CDSL_Dialog::CacheAllProperties
//		Get all the properties from the summary (ALL) tab
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::CacheAllProperties()
{
	BOOL	fRes = FALSE;
	HWND	hWnd;
	ULONG	i, cItem;
	CHAR	szText[cMaxName];
	int		iSubItem;


	// goto the summary tab
	GotoAllPage();
	hWnd = GetDlgItem(m_hAll, IDC_ALL_PROPERTIES);
	
	cItem =  ListView_GetItemCount(hWnd);
	SAFE_ALLOC(m_rgInitProp, InitProp, cItem);
	m_cInitProp = cItem;

	for (i=0; i<cItem; i++)
	{
		// build the property description string
		iSubItem = 0;
		szText[0] = '\0';
		ListView_GetItemTextA(hWnd, i, iSubItem, szText, cMaxName);
		m_rgInitProp[i].pwszPropDescription = ConvertToWCHAR(szText);

		// build the property value string
		iSubItem = 1;
		szText[0] = '\0';
		ListView_GetItemTextA(hWnd, i, iSubItem, szText, cMaxName);
		if (0 == wcscmp(L"Mode", m_rgInitProp[i].pwszPropDescription))
		{
			LONG	lInitMode;

			TESTC(GetInitMode(&lInitMode));
			wsprintf(szText, "%ld", lInitMode);
		}
		m_rgInitProp[i].pwszPropValue = ConvertToWCHAR(szText);
	}
	
	fRes = TRUE;

CLEANUP:
	return fRes;
} //CDSL_Dialog::CacheAllProperties




//-------------------------------------------------------------------------
//	CDSL_Dialog::CheckError_OnEditing_PersistSecurityInfo
//		Check that trrying to edit the prop in the All Page fails
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::CheckError_OnEditing_PersistSecurityInfo()
{
	TBEGIN
	HWND			hWndProp = GetDlgItem(GetHWND(), IDC_ALL_PROPERTIES);
	HWND			hWnd;
	HWND			hOK;
	CHAR			szWindowName[cMaxName]	= "";
	IDBInitialize	*pIDBInitialize = NULL;
	ULONG			nItem;
	LVFINDINFOA		lvFindInfo = {LVFI_STRING, "Persist Security Info", 0, NULL, 0};

	// get the item that is selected
	nItem	= SendMessage(hWndProp, LVM_FINDITEMA, -1, (LPARAM)&lvFindInfo);
	ListView_GetItemTextA(hWndProp, nItem, 0, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, "Persist Security Info"));
	LV_SetItemState(hWndProp, nItem, 0, LVIS_SELECTED, LVIS_SELECTED);

	Sleep(2000);
	TESTC(PushButton(IDC_EditValue));

	// check that a new dialog box has been created with a proper title
	// and get its handle
	// get the foreground window and make sure it has focus
	Sleep(2000);
	hWnd	= GetForegroundWindow();

	// check its caption (should be a warning)
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDS_TITLE_DATA_LINK));

	// checked that the control exists
	hOK = GetDlgItem(hWnd, IDCANCEL);
	TESTC(NULL != hOK);

	// close this window
	SendMessage(hOK, BM_CLICK, 0, 0L);

	// check that the text was sent correctly
	Sleep(1000);
CLEANUP:
	TRETURN
} //CDSL_Dialog::CheckError_OnEditing_PersistSecurityInfo




//-------------------------------------------------------------------------
//	CDSL_Dialog::CheckAllProperties
//		Check all the properties from the summary (ALL) tab
//		Whatever appears in summary must fit with what you have set
//		It is assumed that CacheAllProperties was called before
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::CheckAllProperties()
{
	ULONG	i;
	BOOL	fRes = TRUE;

	for (i=0; i<m_cInitProp; i++)
	{
		// User ID
		if (0 == wcscmp(m_rgInitProp[i].pwszPropDescription, L"User ID"))
		{
			if (!COMPARE(wcscmp(m_rgInitProp[i].pwszPropValue, m_wszUserID), 0))
			{
				odtLog << "\tActual value: " << m_rgInitProp[i].pwszPropValue << "\n";
				fRes = FALSE;
			}
		}
		// Password
		if (0 == wcscmp(m_rgInitProp[i].pwszPropDescription, L"Password"))
		{
			if (!COMPARE(wcslen(m_rgInitProp[i].pwszPropValue), wcslen(m_wszPassword)))
			{
				odtLog << "\tActual value: " << m_rgInitProp[i].pwszPropValue << "\n";
				fRes = FALSE;
			}
		}
		// Data Source
		if (0 == wcscmp(m_rgInitProp[i].pwszPropDescription, L"Data Source"))
		{
			if (!COMPARE(wcscmp(m_rgInitProp[i].pwszPropValue, m_wszInitDataSource), 0))
			{
				odtLog << "\tActual value: " << m_rgInitProp[i].pwszPropValue << "\n";
				fRes = FALSE;
			}
		}
	}
	return fRes;
} //CDSL_Dialog::CheckAllProperties




//-------------------------------------------------------------------------
//	CDSL_Dialog::CheckPropertiesOnDataSourceObject
//		Check all the properties from the summary (ALL) tab
//		Whatever appears in summary must fit DSO's properties
//		This method assumes that CacheAllProperties was called before it
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::CheckPropertiesOnDataSourceObject(IUnknown *pIUnknown)
{
	TBEGIN
	IDBProperties	*pIDBProperties	= NULL;
	ULONG			cGrantedPropSet		= 0;
	DBPROPSET		*rgGrantedPropSet	= NULL;
	ULONG			cInfoPropSet		= 0;
	DBPROPINFOSET	*rgInfoPropSet		= NULL;
	OLECHAR			*pDescBuffer		= NULL;
	ULONG			cInitProp, cProp, cPropSet;
	WCHAR			*pwszText			= NULL;
	WCHAR			*pwszValue			= NULL;
	HRESULT			hr;
	WCHAR			*pwszInitString		= NULL;
	WCHAR			*pwszPassword		= NULL;
	VARIANT			*pvValue			= NULL;
	VARIANT			vValue;
	VARIANT			vVal2, vVal3;
	VARIANT_BOOL	fPersist;

	VariantInit(&vValue);
	VariantInit(&vVal2);
	VariantInit(&vVal3);

	// build a property set based on the cached properties
	TESTC(VerifyInterface(pIUnknown, IID_IDBProperties, 
		DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));

	TESTC_(pIDBProperties->GetPropertyInfo(	0, NULL, &cInfoPropSet, 
											&rgInfoPropSet, &pDescBuffer), S_OK);
	TESTC_(pIDBProperties->GetProperties(0, NULL, 
			&cGrantedPropSet, &rgGrantedPropSet), S_OK);
	for (cInitProp=0; cInitProp<m_cInitProp; cInitProp++)
	{
		if (0 == wcscmp(L"Password", m_rgInitProp[cInitProp].pwszPropDescription))
		{
			// play a bit with the init string
			TESTC(NULL != s_pIDataInitialize);
			TESTC(::GetProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, DBPROPSET_DBINIT, pIUnknown, &fPersist));
			TESTC_(s_pIDataInitialize->GetInitializationString(pIUnknown, TRUE, &pwszInitString), S_OK);
			if (VARIANT_TRUE == fPersist)
			{
				// find the password in the init string
				TESTC(GetModInfo()->GetStringKeywordValue(pwszInitString, L"Password", &pwszPassword));
				TESTC(0 == wcscmp(pwszPassword, m_fBlankPassword? L"": m_wszPassword));
				SAFE_FREE(pwszPassword);
			}
			else
			{
				// make sure password is not in the init string
				TESTC(!GetModInfo()->GetStringKeywordValue(pwszInitString, L"Password", &pwszPassword));
				TESTC(NULL == pwszPassword);
			}
			// now try with exclude password
			SAFE_FREE(pwszInitString);
			TESTC_(s_pIDataInitialize->GetInitializationString(pIUnknown, FALSE, &pwszInitString), S_OK);
			TESTC(!GetModInfo()->GetStringKeywordValue(pwszInitString, L"Password", &pwszPassword));
			TESTC(NULL == pwszPassword);
			continue;
		}

		pwszText	= m_rgInitProp[cInitProp].pwszPropDescription;
		pwszValue	= m_rgInitProp[cInitProp].pwszPropValue;
		TESTC(NULL != pwszText);
		TESTC(NULL != pwszValue);

		for (cPropSet=0; cPropSet<cInfoPropSet; cPropSet++)
		{
			DBPROPINFOSET	*pPropSet = &rgInfoPropSet[cPropSet];
			for (cProp=0; cProp<pPropSet->cPropertyInfos; cProp++)
			{
				// compare description against property description
				if (pPropSet->rgPropertyInfos[cProp].pwszDescription 
					&& 0 == wcscmp(pwszText, 
							pPropSet->rgPropertyInfos[cProp].pwszDescription ))
					break;
			}
			if (cProp < rgInfoPropSet[cPropSet].cPropertyInfos)
				break;
		}
		// was the property found (must have been)
		TESTC(cPropSet < cInfoPropSet);

		// ok, set fields 
		m_rgInitProp[cInitProp].guidPropertySet = 
			rgInfoPropSet[cPropSet].guidPropertySet;
		m_rgInitProp[cInitProp].dwPropertyID = 
			rgInfoPropSet[cPropSet].rgPropertyInfos[cProp].dwPropertyID;
		
		// look for the property
		for (cPropSet=0; cPropSet<cGrantedPropSet; cPropSet++)
		{
			DBPROPSET	*pPropSet = &rgGrantedPropSet[cPropSet];

			if (pPropSet->guidPropertySet != m_rgInitProp[cInitProp].guidPropertySet)
				continue;
			for (cProp=0; cProp<pPropSet->cProperties; cProp++)
			{
				if (pPropSet->rgProperties[cProp].dwPropertyID ==  
					m_rgInitProp[cInitProp].dwPropertyID)
					break;
			}
			if (cProp < pPropSet->cProperties)
				break;
		}
		TESTC(cPropSet < cGrantedPropSet);

		// compare the properties
		pvValue = &rgGrantedPropSet[cPropSet].rgProperties[cProp].vValue;
		
		VariantInit(&vValue);
		VariantInit(&vVal2);
		VariantInit(&vVal3);
		vVal2.vt = VT_BSTR;
		vVal2.bstrVal = SysAllocString(pwszValue);
		TESTC_(hr = VariantChangeType(&vVal3, &vVal2, VARIANT_NOVALUEPROP, pvValue->vt), S_OK);
		
		TESTC_(hr = VariantChangeType(&vValue, pvValue, VARIANT_NOVALUEPROP, VT_BSTR), S_OK);
		if (NULL == vValue.bstrVal)
		{
			TESTC(0 == wcscmp(pwszValue, L""));
		}
		else if (VT_EMPTY != pvValue->vt)
		{
			TESTC(CompareVariant(pvValue, &vVal3, TRUE));
		}
		else
			TESTC(VT_EMPTY == vVal3.vt)
		VariantClear(&vValue);
		VariantClear(&vVal2);
		VariantClear(&vVal3);
	}

CLEANUP:
	SAFE_FREE(pwszInitString);
	SAFE_FREE(pwszPassword);
	VariantClear(&vValue);
	VariantClear(&vVal2);
	VariantClear(&vVal3);
	SAFE_RELEASE(pIDBProperties);
	FreeProperties(&cInfoPropSet, &rgInfoPropSet, &pDescBuffer);
	FreeProperties(&cGrantedPropSet, &rgGrantedPropSet);
	SAFE_FREE(pDescBuffer);
	TRETURN
} //CDSL_Dialog::CheckPropertiesOnDataSourceObject




//-------------------------------------------------------------------------
//	Frees the list of provider descriptions
//-------------------------------------------------------------------------
void CDSL_Dialog::FreeProviderList()
{
	ULONG	i;

	for (i=0; i<m_cProviderList; i++)
	{
		SAFE_FREE(m_rgProviderList[i]);
	}
	SAFE_FREE(m_rgProviderList);
	m_rgProviderList	= NULL;
	m_cProviderList		= 0;
} //CDSL_Dialog::FreeProviderList




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::KillThread
//		terminates the thread responsible for DSL page
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::KillThread(int nButton/* = PSBTN_OK*/, DWORD dwMilliseconds/* = INFINITE*/)
{
	TBEGIN
	DWORD	dwRes;
	HWND	hWnd;
	HWND	hIDYES;
	CHAR	szWindowName[cMaxName] = "";

	if (0 == m_hThread)
		return TRUE;

	// send a message to the DSL page so that it could finish its job
	// a zombie DSL could result in AV since ppDataSource is no more available
	// send the message
	if (m_fIsInExecution)
	{
		Activate();
		PropSheet_PressButton(m_hWnd, nButton);		
	}

	Sleep(200);
	hWnd = GetForegroundWindow();
	// check its caption
	GetWindowTextA(hWnd, szWindowName, cMaxName);

	if (DSL_CM_INTERFACE != m_CreationMethod)
	{
		// a warning might appear if allow save password was checked
		if (0 == strcmp(szWindowName, g_szIDS_TITLE_DATA_LINK_SUCCESS))
		{
			// checked that the control exists
			hIDYES = GetDlgItem(hWnd, IDYES);
			COMPARE(NULL != hIDYES, TRUE);
			// close this window
			SendMessage(hIDYES, BM_CLICK, 0, 0L);
		}		
	}

	// do not let MDAC bug #36264 stop the work
	if (0 == strcmp(szWindowName, g_szIDS_TITLE_DATA_LINK))
	{
		odtLog << L"\nInappropiate window displayed: " << g_szIDS_TITLE_DATA_LINK << "\n";
		COMPARE(TRUE, FALSE);
		// checked that the control exists
		hIDYES = GetDlgItem(hWnd, IDOK);
		COMPARE(NULL != hIDYES, TRUE);
		// close this window
		SendMessage(hIDYES, BM_CLICK, 0, 0L);
	}

	TESTC(WAIT_OBJECT_0 == (dwRes = WaitForSingleObject(m_hThread, dwMilliseconds)));

	TESTC(CloseHandle(m_hThread));
	m_hThread = 0;

	// the only expected return value in here is on IDCANCEL
	TESTC(PSBTN_CANCEL != nButton || DB_E_CANCELED == m_hres);

CLEANUP:
	SAFE_RELEASE(m_pIDBPromptInitialize);
	TRETURN
} //CDSL_Dialog::KillThread




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::IsValidDataSourceType
// check that the datasource type is valid related to the filter
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::IsValidDataSourceType(DBSOURCETYPE wSourceType)
{
	if (0 == m_cSourceTypeFilter)
		return (wSourceType != DBSOURCETYPE_ENUMERATOR);
	
	ASSERT(m_rgSourceTypeFilter);

	for (ULONG i=0; i<m_cSourceTypeFilter; i++)
	{
		if (wSourceType == m_rgSourceTypeFilter[i])
			return TRUE;
	}

	return FALSE;
} //CDSL_Dialog::IsValidDataSourceType
	



//-------------------------------------------------------------------------
//
//	CDSL_Dialog::IsValidProgID
// check that the datasource parsename is valid related to the filter
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::IsValidProgID(WCHAR *pwszParseName)
{
	LPCOLESTR	pwszProviderProgID = m_pwszszzProviderFilter;
	CLSID		clsid;
	CLSID		clsidFilter;

	TESTC_(CLSIDFromString(pwszParseName, &clsid), S_OK);

	if (NULL == m_pwszszzProviderFilter)
		return TRUE;
	
	for (; *pwszProviderProgID; pwszProviderProgID += wcslen(pwszProviderProgID)+1)
	{
		if (S_OK != CLSIDFromString((LPOLESTR)pwszProviderProgID, &clsidFilter))
			continue;

		if (clsid == clsidFilter)
			return TRUE;
	}

CLEANUP:
	return FALSE;
} //CDSL_Dialog::IsValidProgID




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::GetFilteredProviders
// Get the index array of providers filtered in
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GetFilteredProviders(
	ULONG	*pcIdxProv,	//[out] the number of filtered providers
	ULONG	**prgIdxProv	//[out] the array of indexes to filtered providers
)
{
	BOOL	fRes		= FALSE;
	ULONG	cIdxProv	= 0;
	ULONG	*rgIdxProv	= NULL;
	ULONG	i;

	ASSERT(pcIdxProv && prgIdxProv);
	SAFE_ALLOC(rgIdxProv, ULONG, s_SourcesSet.Count());
	
	for (i=0; i<s_SourcesSet.Count(); i++)
	{
		if (	IsValidDataSourceType((DBTYPE)s_SourcesSet[i])
			&&	IsValidProgID(s_SourcesSet[i].m_pwszParseName))
			rgIdxProv[cIdxProv++] = i;
	}
	
	fRes = TRUE;
	SAFE_REALLOC(rgIdxProv, ULONG, cIdxProv);
	*prgIdxProv = rgIdxProv;
	*pcIdxProv	= cIdxProv;
	
CLEANUP:
	return fRes;
} //CDSL_Dialog::GetFilteredProviders



//-------------------------------------------------------------------------
//
//	CDSL_Dialog::Luxor_SelectInitCatalog
//	Selects a random init catalog from 
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::Luxor_SelectInitCatalog()
{
	TBEGIN
	HWND	hWnd;
	ULONG	ulSize;
	ULONG	ulSelItem;
	CHAR	szItemText[cMaxName]	= "";
	WCHAR	*pwszInitCat			= NULL;
	WCHAR	wszInitCat[cMaxName];

	TESTC(SetDatabaseMethod(IDC_UseDatabaseOnServerName));
	hWnd = GetDlgItem(GetHWND(), IDC_DatabaseOnServerName);

	// drop down the list
	SendMessage(hWnd, CB_SHOWDROPDOWN, TRUE, 0L);
	Sleep(3000);
	// if the list is populated, make a selection
	ulSize = SendMessage(hWnd, CB_GETCOUNT, 0, 0L);
	if (0 < ulSize)
	{
		// make a random selection and hide the list box
		ulSelItem = rand() % ulSize;
		SendMessageA(hWnd, CB_GETLBTEXT, ulSelItem, (LPARAM)szItemText);
		odtLog << "Item no " << ulSelItem << ": " << szItemText << "\n";
		TESTC( ulSelItem == (ULONG)SendMessageA(hWnd, CB_SELECTSTRING, -1, (LPARAM)szItemText));
		Sleep(1000);
		TESTC(GetTextFromCtrl(IDC_DatabaseOnServerName, wszInitCat, cMaxName));
		pwszInitCat = ConvertToWCHAR(szItemText);
		TESTC(0 == wcscmp(wszInitCat, pwszInitCat));
	}

CLEANUP:
	TRETURN
} //CDSL_Dialog::Luxor_SelectInitCatalog




//-------------------------------------------------------------------------
//
//	CBasicDialog::Luxor_CheckServerNameList
//		Check the list of server names, displayed in the connection page
//		against the enumerator
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::Luxor_CheckServerNameList()
{
	TBEGIN
	ULONG				index;
	HWND				hWnd = GetDlgItem(GetHWND(), IDC_DBPROP_INIT_DATASOURCE);
	IParseDisplayName	*pIParseDisplayName = NULL;
	ULONG				cEnumInfo			= 0;
	ENUMINFO			*rgEnumInfo			= NULL;
	CHAR				szServerName[cMaxName];
	ULONG				ulSize;

	TESTC_(CoCreateInstance(CLSID_SQLOLEDB_ENUMERATOR, NULL, CLSCTX_INPROC_SERVER, IID_IParseDisplayName, (void**)&pIParseDisplayName),S_OK);
	TESTC_(GetEnumInfo(pIParseDisplayName, &cEnumInfo, &rgEnumInfo), S_OK);

	// get the index of the last element and compar it against the 
	// size of the array
	ulSize = (ULONG)SendMessage(hWnd, CB_GETCOUNT, 0, 0L);
	TESTC(1 + ulSize == cEnumInfo);

	for (index = 0; index < cEnumInfo; index++)
	{
		// find the server in the list
		ConvertToMBCS(rgEnumInfo[index].wszName, szServerName, cMaxName);

		TESTC(LB_ERR  != SendMessageA(hWnd, LB_ERR , -1, (LPARAM)szServerName));
	}

CLEANUP:
	SAFE_RELEASE(pIParseDisplayName);
	SAFE_FREE(rgEnumInfo);
	TRETURN
} //CDSL_Dialog::Luxor_CheckServerNameList




//-------------------------------------------------------------------------
//
//	CBasicDialog::Sockeye_CheckDSNList
//		Check the list of server names, displayed in the connection page
//		against the enumerator
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::Sockeye_CheckDSNList()
{
	TBEGIN
	ULONG				index;
	HWND				hWnd = GetDlgItem(GetHWND(), IDC_DBPROP_INIT_DATASOURCE);
	IParseDisplayName	*pIParseDisplayName = NULL;
	ULONG				cEnumInfo			= 0;
	ENUMINFO			*rgEnumInfo			= NULL;
	CHAR				szDataSourceName[cMaxName];
	ULONG				ulSize;

	TESTC_(CoCreateInstance(CLSID_MSDASQL_ENUMERATOR, NULL, CLSCTX_INPROC_SERVER, IID_IParseDisplayName, (void**)&pIParseDisplayName),S_OK);
	TESTC_(GetEnumInfo(pIParseDisplayName, &cEnumInfo, &rgEnumInfo), S_OK);

	// get the index of the last element and compar it against the 
	// size of the array
	ulSize = (ULONG)SendMessage(hWnd, CB_GETCOUNT, 0, 0L);
	TESTC(1 + ulSize == cEnumInfo);

	for (index = 0; index < cEnumInfo; index++)
	{
		// find the server in the list
		ConvertToMBCS(rgEnumInfo[index].wszName, szDataSourceName, cMaxName);

		TESTC(LB_ERR  != SendMessageA(hWnd, LB_ERR , -1, (LPARAM)szDataSourceName));
	}

CLEANUP:
	SAFE_RELEASE(pIParseDisplayName);
	SAFE_FREE(rgEnumInfo);
	TRETURN
} //CDSL_Dialog::Sockeye_CheckDSNList




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::GetProperty
//	Get property from the summary page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GetProperty(WCHAR *pwszPropName, WCHAR **ppwszPropValue)
{
	TBEGIN
	HWND		hWnd;
	CHAR		szPropName[cMaxName];
	CHAR		szText[cMaxName];
	int			iSubItem;
	ULONG		ulItem;

	ConvertToMBCS(pwszPropName, szPropName, cMaxName);
	LVFINDINFO	lvfi = {LVFI_STRING, szPropName, 0, 0, 0};

	TESTC(NULL != ppwszPropValue);
	*ppwszPropValue = NULL;
	TESTC(NULL != pwszPropName);
	TESTC(IsCurrentPage(g_nAll));

	// goto the summary tab
	hWnd = GetDlgItem(GetHWND(), IDC_ALL_PROPERTIES);

	iSubItem = 1;
	szText[0] = '\0';

	ulItem = SendMessageA(hWnd, LVM_FINDITEM, -1, (LPARAM)&lvfi);
	ListView_GetItemTextA(hWnd, ulItem, iSubItem, szText, cMaxName);

	if (0 == strcmp("Mode", szPropName))
	{
		LONG	lInitMode;

		TESTC(GetInitMode(&lInitMode));
		wsprintf(szText, "%ld", lInitMode);
	}
	*ppwszPropValue = ConvertToWCHAR(szText);

CLEANUP:
	TRETURN
} //CDSL_Dialog::GetProperty




//-------------------------------------------------------------------------
//
//	CBasicDialog::CreateUDLFile
// Create a UDL file
//-------------------------------------------------------------------------
BOOL CBasicDialog::CreateUDLFile(WCHAR *pwszUDLFileName)
{
	TBEGIN
	HKEY			hKey						= NULL;
	int				fh							= -1;
	DWORD			dwType;
	const DWORD		cMaxTextLen					= 2000;
	DWORD			cTextLen					= cMaxTextLen;
	WCHAR			wszInitText[cMaxTextLen]	= L" [oledb]\r\n"
						L"; Everything after this line is an OLE DB initstring\r\n"
						L"Provider=MSDASQL.1;Persist Security Info=False\r\n";
	// put prefix signaling UNICODE file
	wszInitText[0] = 0xFEFF;

	// try to open the associated shell key
	// this might not exist
	// create the udl file and its initial content
	if (ERROR_SUCCESS == RegOpenKeyExA(
		HKEY_CLASSES_ROOT,	// handle to open key
		".UDL\\ShellNew",	// address of name of subkey to open
		0,					// reserved  
		KEY_READ,			// security access mask
		&hKey				// address of handle to open key
		))
	{
		fh = _wopen(pwszUDLFileName, 
			_O_CREAT | _O_BINARY | _O_RDWR | _O_TRUNC , _S_IREAD | _S_IWRITE);
		TESTC(-1 != fh);
	
		TESTC_PROVIDER(ERROR_SUCCESS == RegOpenKeyExA(
			HKEY_CLASSES_ROOT,	// handle to open key
			".UDL\\ShellNew",	// address of name of subkey to open
			0,					// reserved  
			KEY_READ,			// security access mask
			&hKey				// address of handle to open key
		));

		TESTC(ERROR_SUCCESS == RegQueryValueExW(  
			hKey,					// handle to key to query
			L"Data",				// address of name of value to query
			0,						// reserved
			&dwType,				// address of buffer for value type
			(LPBYTE)wszInitText,	// address of data buffer
			&cTextLen				// address of data buffer size
		));

	}
	else
	{
		fh = _wopen(pwszUDLFileName, 
			_O_CREAT | _O_BINARY | _O_RDWR | _O_TRUNC , _S_IREAD | _S_IWRITE);
		TESTC(-1 != fh);
	}
	
	cTextLen = wcslen((WCHAR*)wszInitText)*sizeof(WCHAR);
	TESTC((int)cTextLen == _write(fh, (void*)wszInitText, cTextLen));

CLEANUP:
	if (hKey)
	{
		COMPARE(ERROR_SUCCESS == RegCloseKey(hKey), TRUE);
	}
	if (fh)
	{
		COMPARE(-1 != _close(fh), TRUE);
	}
	TRETURN
} //CBasicDialog::CreateUDLFile




//-------------------------------------------------------------------------
//
//	CBasicDialog::CreateUDLFile
// Create a UDL file
//-------------------------------------------------------------------------
BOOL CBasicDialog::CreateUDLFile(CHAR *pszUDLFileName)
{
	TBEGIN
	HKEY			hKey						= NULL;
	int				fh							= -1;
	DWORD			dwType;
	const DWORD		cMaxTextLen					= 2000;
	DWORD			cTextLen					= cMaxTextLen;
	WCHAR			wszInitText[cMaxTextLen]	= L" [oledb]\r\n"
						L"; Everything after this line is an OLE DB initstring\r\n"
						L"Provider=MSDASQL.1;Persist Security Info=False\r\n";
	// put prefix signaling UNICODE file
	wszInitText[0] = 0xFEFF;

	// try to open the associated shell key
	// this might not exist
	// create the udl file and its initial content
	if (ERROR_SUCCESS == RegOpenKeyExA(
		HKEY_CLASSES_ROOT,	// handle to open key
		".UDL\\ShellNew",	// address of name of subkey to open
		0,					// reserved  
		KEY_READ,			// security access mask
		&hKey				// address of handle to open key
		))
	{
		fh = _open(pszUDLFileName, 
			_O_CREAT | _O_BINARY | _O_RDWR | _O_TRUNC , _S_IREAD | _S_IWRITE);
		TESTC(-1 != fh);
	
		TESTC_PROVIDER(ERROR_SUCCESS == RegOpenKeyExA(
			HKEY_CLASSES_ROOT,	// handle to open key
			".UDL\\ShellNew",	// address of name of subkey to open
			0,					// reserved  
			KEY_READ,			// security access mask
			&hKey				// address of handle to open key
		));

		TESTC(ERROR_SUCCESS == RegQueryValueExW(  
			hKey,					// handle to key to query
			L"Data",				// address of name of value to query
			0,						// reserved
			&dwType,				// address of buffer for value type
			(LPBYTE)wszInitText,	// address of data buffer
			&cTextLen				// address of data buffer size
		));

	}
	else
	{
		fh = _open(pszUDLFileName, 
			_O_CREAT | _O_BINARY | _O_RDWR | _O_TRUNC , _S_IREAD | _S_IWRITE);
		TESTC(-1 != fh);
	}
	
	cTextLen = wcslen((WCHAR*)wszInitText)*sizeof(WCHAR);
	TESTC((int)cTextLen == _write(fh, (void*)wszInitText, cTextLen));

CLEANUP:
	if (hKey)
	{
		COMPARE(ERROR_SUCCESS == RegCloseKey(hKey), TRUE);
	}
	if (fh)
	{
		COMPARE(-1 != _close(fh), TRUE);
	}
	TRETURN
} //CBasicDialog::CreateUDLFile




CSourcesSet::CSourcesSet()
{
	m_cEnumInfo		= 0;
	m_rgEnumInfo	= NULL;
	m_rgCustomUI	= NULL;
	m_rgServices	= NULL;
	m_fInitialized	= 0;
} //CSourcesSet::CSourcesSet


BOOL CSourcesSet::FinalInit()
{
	TBEGIN
	ULONG					ulIter;
	IServiceProvider		*pIServiceProvider		= NULL;
	ISpecifyPropertyPages	*pISpecify				= NULL;
	CLSID					clsid;
	BOOL					*rgExtendsDSL			= NULL;
	CAUUID					Pages;
	WCHAR					wszSubKey[cMaxName]		= L"";
	CHAR					szSubKey[cMaxName]		= "";
	LONG					lRes;
	HKEY					hKey = 0;
	CHAR					szValueName[cMaxName]	= "OLEDB_SERVICES";
	DWORD					dwServices;
	DWORD					cLen					= sizeof(DWORD);
	DWORD					dwType;
	HRESULT					hr;
	

	if (TRUE == m_fInitialized)
		return TRUE;

	m_fInitialized = TRUE;
	TESTC_(GetEnumInfo(NULL, &m_cEnumInfo, &m_rgEnumInfo), S_OK);
	
	TESTC(m_cEnumInfo < nMaxProv);

	SAFE_ALLOC(m_rgCustomUI, CCustomUI, m_cEnumInfo);
	SAFE_ALLOC(m_rgServices, COLEDBServices, m_cEnumInfo);

	// find out which of the providers customize the UI
	// and how they registered for services
	TESTC(NULL != m_rgEnumInfo || 0 == m_cEnumInfo);

	Pages.pElems = NULL;
	for (ulIter = 0; ulIter < m_cEnumInfo; ulIter++)
	{
		//if the source is not a provider, skip the checking
		if (	DBSOURCETYPE_DATASOURCE_TDP != m_rgEnumInfo[ulIter].wType
			&&	DBSOURCETYPE_DATASOURCE_MDP != m_rgEnumInfo[ulIter].wType)
			continue;
		
		m_rgCustomUI[ulIter]	= CUSTOM_NONE;
		m_rgServices[ulIter]	= 0;
			
		// get info about services supported
		wcscpy(wszSubKey, L"CLSID\\");
		wcscat(wszSubKey, m_rgEnumInfo[ulIter].wszParseName);
		ConvertToMBCS(wszSubKey, szSubKey, cMaxName);

		lRes = 	RegOpenKeyExA(
			HKEY_CLASSES_ROOT,         // handle to open key
			szSubKey,  // address of name of subkey to open
			NULL,   // reserved
			KEY_QUERY_VALUE , // security access mask
			&hKey    // address of handle to open key
		);
		TESTC(ERROR_SUCCESS == lRes);

		lRes = RegQueryValueExA(
			hKey,							// handle to key to query
			szValueName,					// name of subkey to query
			NULL,							// reserved
			&dwType,						// address of buffer for value type
			(LPBYTE)&dwServices,			// buffer for returned string
			&cLen							// receives size of returned string
			);

		RegCloseKey(hKey);

		if (ERROR_SUCCESS == lRes)
		{
			m_rgServices[ulIter] |= (dwServices & 0x1) ? DBPROPVAL_OS_RESOURCEPOOLING: 0;
			m_rgServices[ulIter] |= (dwServices & 0x2) ? DBPROPVAL_OS_TXNENLISTMENT: 0;
			m_rgServices[ulIter] |= (dwServices & 0x4) ? DBPROPVAL_OS_CLIENTCURSOR: 0;	
		}

		// look for customized pages
		TESTC(S_OK == CLSIDFromString(m_rgEnumInfo[ulIter].wszParseName, &clsid));
	
		if (S_OK != CoCreateInstance(clsid, NULL, CLSCTX_ALL, 
			IID_IServiceProvider, (LPVOID*)&pIServiceProvider))
			goto LOOP;

		if (S_OK != pIServiceProvider->QueryService(OLEDB_SVC_DSLPropertyPages,
			IID_ISpecifyPropertyPages,(LPVOID *)&pISpecify))
			goto LOOP;

		TESTC_(hr = pISpecify->GetPages(&Pages), S_OK);

		TESTC(3 > Pages.cElems);
		if (0 == Pages.cElems)
			goto LOOP;

		TESTC(2 <= Pages.cElems
			|| Pages.pElems[0] != Pages.pElems[1]);
		
		if (1 >= Pages.cElems && GUID_NULL != Pages.pElems[0])
			m_rgCustomUI[ulIter] |= CUSTOM_CONN;
		if (2 >= Pages.cElems && GUID_NULL != Pages.pElems[1])
			m_rgCustomUI[ulIter] |= CUSTOM_ADV;

LOOP:
		SAFE_RELEASE(pIServiceProvider);
		SAFE_RELEASE(pISpecify);
		SAFE_FREE(Pages.pElems);
	}

CLEANUP:
	SAFE_RELEASE(pIServiceProvider);
	SAFE_RELEASE(pISpecify);
	SAFE_FREE(Pages.pElems);
	TRETURN
} //CSourcesSet::FinalInit


CSourcesSet::~CSourcesSet()
{
	SAFE_FREE(m_rgEnumInfo);
	SAFE_FREE(m_rgCustomUI);
	SAFE_FREE(m_rgServices);
} //CSourcesSet::~CSourcesSet



void CSourcesSet::CopyToCSourceInfo(ULONG nIndex, CSourceInfo *pSourceInfo)
{
	if (nIndex < m_cEnumInfo)
	{
		// fill in the structure
		pSourceInfo->m_pwszName			= m_rgEnumInfo[nIndex].wszName;
		pSourceInfo->m_pwszParseName	= m_rgEnumInfo[nIndex].wszParseName;
		pSourceInfo->m_pwszDescription	= m_rgEnumInfo[nIndex].wszDescription;
		pSourceInfo->m_wType			= m_rgEnumInfo[nIndex].wType;	
		pSourceInfo->m_fIsParent		= m_rgEnumInfo[nIndex].fIsParent;
		pSourceInfo->m_CustomUI			= m_rgCustomUI[nIndex];
		pSourceInfo->m_Services			= m_rgServices[nIndex];
	}
	else
		pSourceInfo->ResetValue();
} //CSourcesSet::CopyToCSourceInfo



CSourceInfo	CSourcesSet::operator[] (ULONG nIndex)
{
	CSourceInfo	SourceInfo;

	CopyToCSourceInfo(nIndex, &SourceInfo);

	return SourceInfo;
} //CSourcesSet::operator[]

		
CSourceInfo	CSourcesSet::operator[] (WCHAR *pwszDescription)
{
	CSourceInfo	SourceInfo;
	ULONG		nIndex;
	
	SourceInfo.ResetValue();

	if (!pwszDescription)
		return SourceInfo;
	
	for (nIndex=0; nIndex < m_cEnumInfo; nIndex++)
	{
		if (	m_rgEnumInfo[nIndex].wszDescription 
			&&	0 == wcscmp(m_rgEnumInfo[nIndex].wszDescription, pwszDescription))
		{
			CopyToCSourceInfo(nIndex, &SourceInfo);
			break;
		}
	}

	return SourceInfo;
} //CSourcesSet::operator[]

		
CSourceInfo	CSourcesSet::operator[] (CLSID clsidProvider)
{
	CSourceInfo	SourceInfo;
	ULONG		nIndex;
	CLSID		clsidCrtProv;

	SourceInfo.ResetValue();

	for (nIndex=0; nIndex < m_cEnumInfo; nIndex++)
	{
		CLSIDFromString(m_rgEnumInfo[nIndex].wszParseName, &clsidCrtProv);
		if (clsidProvider == clsidCrtProv)
		{
			CopyToCSourceInfo(nIndex, &SourceInfo);
			break;
		}
	}

	return SourceInfo;
} //CSourcesSet::operator[]

		
// set filter for the iterator and the first position
BOOL CSourcesSet::SetFilter(
	ULONG			cAllowedSourceTypes, 
	DBTYPE			*rgAllowedSourceTypes,
	ULONG			cExceptedSourceTypes,
	DBTYPE			*rgExceptedSourceTypes,
	CCustomUI		*pCustomUIFilter,
	COLEDBServices	*pServicesFilter
)
{
	m_ulPos = 0;

	// do not copy the filter values; the client should mantain them
	m_cAllowedSourceTypes	= cAllowedSourceTypes;
	m_rgAllowedSourceTypes	= rgAllowedSourceTypes;
	m_cExceptedSourceTypes	= cExceptedSourceTypes;
	m_rgExceptedSourceTypes	= rgExceptedSourceTypes;
	m_pServicesFilter		= pServicesFilter;
	m_pCustomUIFilter		= pCustomUIFilter;

	// get the first, starting with this position
	m_ulPos	= GetNext();
	return m_ulPos < m_cEnumInfo;
} //CSourcesSet::SetFilter


// get the current source information and advance to the next position
BOOL CSourcesSet::GetCurrent(CSourceInfo *pSourceInfo)
{
	if (!pSourceInfo)
		return FALSE;

	m_ulPos++;
	m_ulPos	= GetNext();
	
	if (m_ulPos < m_cEnumInfo)
	{
		CopyToCSourceInfo(m_ulPos, pSourceInfo);
		return TRUE;
	}
	else
		return FALSE;
} //CSourcesSet::GetCurrent



ULONG CSourcesSet::GetNext()
{
	ULONG	ulIndx;

	for (; m_ulPos < m_cEnumInfo; m_ulPos++)
	{
		if (DBSOURCETYPE_DATASOURCE_TDP == m_rgEnumInfo[m_ulPos].wType
			|| DBSOURCETYPE_DATASOURCE_TDP == m_rgEnumInfo[m_ulPos].wType)
		{
			// check the customization
			if (m_pCustomUIFilter && *m_pCustomUIFilter != m_rgCustomUI[m_ulPos])
				continue;
			// service is at least the required one
			if (m_pServicesFilter && 
				*m_pServicesFilter != (*m_pServicesFilter & m_rgServices[m_ulPos]))
				continue;
		}

		// check whether this is among the allowed sources
		if (0 < m_cAllowedSourceTypes && m_rgAllowedSourceTypes)
		{
			// try to identify current source among the allowed ones
			for (ulIndx=0; ulIndx < m_cAllowedSourceTypes; ulIndx++)
			{
				if (m_rgAllowedSourceTypes[ulIndx] == m_rgEnumInfo[m_ulPos].wType)
					break;
			}
			if (ulIndx < m_cAllowedSourceTypes)
				break;		// do not look in the second list, they shouldn't both exist
		}
		else
		// check whether this is among the allowed sources
		if (0 < m_cExceptedSourceTypes && m_rgExceptedSourceTypes)
		{
			// try to identify current source among the allowed ones
			for (ulIndx=0; ulIndx < m_cExceptedSourceTypes; ulIndx++)
			{
				if (m_rgExceptedSourceTypes[ulIndx] == m_rgEnumInfo[m_ulPos].wType)
					break;
			}
			if (ulIndx >= m_cExceptedSourceTypes)
				break;		// do not look in the second list, they shouldn't both exist
		}
	}

	return m_ulPos;
} //CSourcesSet::GetNext

/*
CLSID CSourcesSet::GetSource(WCHAR *pwszProviderDescription)
{
} //CSourcesSet::GetSource
*/

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
	WCHAR			wszFileName[_MAX_FNAME]	= L"c:\\";
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
	for (;cLen < _MAX_PATH/sizeof(WCHAR); cLen++)
	{
		wcscat(wszFileName, L"a");
	}
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
	WCHAR			wszFileName[_MAX_FNAME]	= L"ThisIsMyUDLFile.udl";
	CDSL_Dialog		Dialog;
	
	TESTC(Dialog.CreateUDLFile(wszFileName));
	TESTC(Dialog.SpawnUDLFile(wszFileName));
	TESTC(Dialog.IsInExecution());
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
	WCHAR				wszInitialDirectory[_MAX_PATH]	= L"c:\\";
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






//-------------------------------------------------------------------------
//
//	CDSL_FileDialog::CDSL_FileDialog
//		creates DSL thread
//-------------------------------------------------------------------------
CDSL_FileDialog::CDSL_FileDialog(
	IDBPromptInitialize		*pIDBPromptInitialize,
	HWND					hWndParent,
	DBPROMPTOPTIONS			dwPromptOptions,
	WCHAR					*pwszInitialDirectory,
	WCHAR					*pwszInitialFile,
	WCHAR					**ppwszSelectedFile
)
{
	m_fIsInExecution		= FALSE;
	m_hThread				= 0;
	m_pIDBPromptInitialize	= NULL;
	TESTC(SpawnPromptFileName(pIDBPromptInitialize, hWndParent, dwPromptOptions,
		pwszInitialDirectory, pwszInitialFile, ppwszSelectedFile));
CLEANUP:
	return;
} //CDSL_FileDialog::CDSL_FileDialog



//-------------------------------------------------------------------------
//
//	CDSL_FileDialog::CDSL_FileDialog
//-------------------------------------------------------------------------
CDSL_FileDialog::CDSL_FileDialog()
{	
	m_fIsInExecution		= FALSE;
	m_hThread				= 0;
	m_pIDBPromptInitialize	= NULL;
} //CDSL_FileDialog::CDSL_FileDialog



//-------------------------------------------------------------------------
//
//	CDSL_FileDialog::~CDSL_FileDialog
//-------------------------------------------------------------------------
CDSL_FileDialog::~CDSL_FileDialog()
{
	KillThread(IDCANCEL, 3000);
} //CDSL_FileDialog::CDSL_FileDialog



//-------------------------------------------------------------------------
//
//	CDSL_FileDialog::SpawnPromptFileName
//		creates DSL thread
//-------------------------------------------------------------------------
BOOL CDSL_FileDialog::SpawnPromptFileName(
	IDBPromptInitialize		*pIDBPromptInitialize,
	HWND					hWndParent,
	DBPROMPTOPTIONS			dwPromptOptions,
	WCHAR					*pwszInitialDirectory,
	WCHAR					*pwszInitialFile,
	WCHAR					**ppwszSelectedFile
)
{
	TBEGIN
	HWND			hWnd;
	CHAR			szWindowName[cMaxName] = "";

	m_fIsPropertySheet = FALSE;

	if (m_fIsInExecution)
		TESTC(KillThread());

	// spwan a new thread for DSL
	m_hThread = 0;

	// init some variables
	m_hParentWnd			= hWndParent;
	m_dwPromptOptions		= dwPromptOptions;
	m_pwszInitialDirectory	= pwszInitialDirectory;
	m_pwszInitialFile		= pwszInitialFile;
	m_ppwszSelectedFile		= ppwszSelectedFile;

	ASSERT(pIDBPromptInitialize);
	pIDBPromptInitialize->AddRef();
	m_pIDBPromptInitialize	= pIDBPromptInitialize;
	
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, CDSL_FileDialog::MyThread,
					(void*)this,
					0, 
					&m_IDThread);
	
	// check that the thread was created
	TESTC( 0 != m_hThread);

	// wait for the DSL to appear (1 sec)
	// after 1 sec I expect either to have the UI ot the
	// method to have finished its execution
	Sleep(0);
	Sleep(2000);

	// just a hack for easier debugging
	if (FALSE)
	{
		for (; TRUE;)
			Sleep(0);
	}

	// get the foreground window and make sure it has focus
	hWnd = GetForegroundWindow();

	// check its caption
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	if (0 == strcmp(szWindowName, 
		dwPromptOptions & DBPROMPTOPTIONS_BROWSEONLY? g_szIDS_DSL_TITLE_ORGANIZE: g_szIDS_DSL_TITLE_SELECT))
		m_hWnd = hWnd;
	else
		// just look for a window of this class
		m_hWnd = FindWindowA("#32770", dwPromptOptions & DBPROMPTOPTIONS_BROWSEONLY? g_szIDS_DSL_TITLE_ORGANIZE: g_szIDS_DSL_TITLE_SELECT);

	TESTC(!m_fIsInExecution || NULL != m_hWnd);

	if (m_fIsInExecution)
	{
		//COMPARE(CheckWindowPosition(), TRUE);
	}


CLEANUP:
	TRETURN
} //CDSL_FileDialog::SpawnPromptFileName



//-------------------------------------------------------------------------
//
//	CDSL_FileDialog::MyThread
//		The actual thread
//-------------------------------------------------------------------------
unsigned WINAPI	CDSL_FileDialog::MyThread(void*p)
{
	TBEGIN
	CDSL_FileDialog		*pThis = (CDSL_FileDialog*)p;

	CoInitialize(NULL);
	
	pThis->m_fIsInExecution = TRUE;
	pThis->m_hWnd			= 0;
	pThis->m_hres = pThis->m_pIDBPromptInitialize->PromptFileName(
			pThis->m_hParentWnd,
			pThis->m_dwPromptOptions,
			pThis->m_pwszInitialDirectory,
			pThis->m_pwszInitialFile,
			pThis->m_ppwszSelectedFile
		);
	pThis->m_fIsInExecution = FALSE;

	// if failure *pThis->m_ppDataSource should be NULL
	if (NULL == pThis->m_ppwszSelectedFile)
		CHECK(pThis->m_hres, E_INVALIDARG);

	if (FAILED(pThis->m_hres))
		COMPARE((pThis->m_ppwszSelectedFile? NULL == *(pThis->m_ppwszSelectedFile): 
			TRUE), TRUE);

	// if success *pThis->m_ppDataSource should be not NULL	
	if (SUCCEEDED(pThis->m_hres))
	{
		if (!COMPARE(pThis->m_ppwszSelectedFile && NULL != *pThis->m_ppwszSelectedFile, TRUE))
			odtLog << "On success IDBPromptInitialize pThis->m_ppwszSelectedFile is NULL or it returns a NULL pThis->m_ppwszSelectedFile\n";
	}

	CoUninitialize();
	_endthreadex(TESTB);
	TRETURN
} //CDSL_FileDialog::MyThread



//-------------------------------------------------------------------------
//
//	CDSL_FileDialog::KillThread
//		terminates the thread responsible for DSL page
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_FileDialog::KillThread(int nButton/* = IDCANCEL*/, DWORD dwMilliseconds/* = INFINITE*/)
{
	TBEGIN
	DWORD	dwRes;
	HWND	hWnd;
	CHAR	szWindowName[cMaxName] = "";

	if (0 == m_hThread)
		return TRUE;

	// send a message to the DSL page so that it could finish its job
	// a zombie DSL could result in AV since ppDataSource is no more available
	// send the message
	if (m_fIsInExecution)
	{
		Activate();
		PushButton(nButton);		
	}

	Sleep(200);
	hWnd = GetForegroundWindow();
	// check its caption
	GetWindowTextA(hWnd, szWindowName, cMaxName);

	TESTC(WAIT_OBJECT_0 == (dwRes = WaitForSingleObject(m_hThread, dwMilliseconds)));

	TESTC(CloseHandle(m_hThread));
	m_hThread = 0;

	// the only expected return value in here is on IDCANCEL
	TESTC(PSBTN_CANCEL != nButton || DB_E_CANCELED == m_hres);

CLEANUP:
	SAFE_RELEASE(m_pIDBPromptInitialize);
	TRETURN
} //CDSL_FileDialog::KillThread

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
	TESTC_(pIDBInitialize->Initialize(), S_OK);
	
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
	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	LONG				lMode			= DB_MODE_SHARE_DENY_NONE | DB_MODE_SHARE_DENY_READ;
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
	TESTC(Dialog.GotoAllPage());

	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));
	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	WCHAR				wszInitTime[cMaxName] = L"";
	
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

	swprintf(wszInitTime, L"%u", lTimeout);
	TESTC(Dialog.SetTextToCtrl(IDC_DBPROP_INIT_TIMEOUT, wszInitTime));
	Sleep(2000);
	TESTC(Dialog.GotoAllPage());

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
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


	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetImpersonationLevel(lImpersonationLevel));
	Sleep(2000);

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_IMPERSONATION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lImpersonationLevel == V_I4(&vValue));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetImpersonationLevel(lImpersonationLevel));
	Sleep(2000);

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_IMPERSONATION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lImpersonationLevel == V_I4(&vValue));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetImpersonationLevel(lImpersonationLevel));
	Sleep(2000);

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_IMPERSONATION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lImpersonationLevel == V_I4(&vValue));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetImpersonationLevel(lImpersonationLevel));
	Sleep(2000);

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_IMPERSONATION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lImpersonationLevel == V_I4(&vValue));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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
	TESTC(Dialog.GotoConnectionPage());
	TESTC(Dialog.SetInitDataSource(g_wszDSN));
	TESTC(Dialog.SetUserID(g_wszSockeyeUserName));
	TESTC(Dialog.SetPassword(g_wszSockeyePassword));

	TESTC(Dialog.GotoAdvancedPage());
	TESTC(Dialog.SetInitMode(lMode));
	TESTC(Dialog.SetProtectionLevel(lProtectionLevel));
	Sleep(2000);

	TESTC(Dialog.CacheAllProperties());
	TESTC(Dialog.CheckAllProperties());
	TESTC(Dialog.KillThread(PSBTN_OK));
	TESTC(Dialog.IsResult(S_OK));

	// check the properties from DSO
	TESTC(GetProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt);
	TESTC(lMode == V_I4(&vValue));

	TESTC(GetProperty(DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, pIDBInitialize, &vValue));
	TESTC(VT_I4 == vValue.vt); 
	TESTC(lProtectionLevel == V_I4(&vValue));

	TEST2C_(pIDBInitialize->Initialize(), S_OK, DB_S_ERRORSOCCURRED);
	
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



CSourceInfo::operator CLSID()
{
	CLSID	clsid;

	CLSIDFromString(m_pwszParseName, &clsid);
	return clsid;
} // CSourceInfo::operator CLSID






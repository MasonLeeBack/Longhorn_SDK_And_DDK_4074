// file CDSL_Dialog.hpp
//--------------------------------------------------------------------
// Microsoft OLE DB Test
//
// Copyright (C) 1998-2000 Microsoft Corporation
//
// @doc 
//
// @module IDBPromptInitialize.CPP | IDBPromptInitialize source file for all test modules.

#ifndef _DSL_DIALOG_H_
#define _DSL_DIALOG_H_

#include "extralib.h"
#include "DSLResource.h"
#include "ProviderInfo.h"
#include <prsht.h>

typedef	int (__stdcall *LPFGetWindowText)( HWND , LPWSTR , int );
typedef	BOOL (__stdcall *LPFSetWindowText)( HWND , LPCWSTR );

// constants used for Data Link Properties page tabs
const ULONG		g_nProvider		= 0;
const ULONG		g_nConnection	= 1;
const ULONG		g_nAdvanced		= 2;
const ULONG		g_nAll			= 3;

const DBPROPID	DBPROP_INIT_FILENAME	= 0xc;

int __stdcall		GetWindowTextWRAP( HWND hWnd, LPWSTR lpString, int nMaxCount);
BOOL __stdcall		SetWindowTextWRAP( HWND hWnd, LPCWSTR lpString);

int __stdcall		GetWindowTextANSI(HWND hWnd, LPWSTR lpString, int nMaxCount);
BOOL __stdcall		SetWindowTextANSI( HWND hWnd, LPCWSTR lpString);



//macros
#define ListView_GetItemTextA(hwndLV, i, iSubItem_, pszText_, cchTextMax_)			\
{ LV_ITEM _ms_lvi;																	\
  _ms_lvi.iSubItem = iSubItem_;														\
  _ms_lvi.cchTextMax = cchTextMax_;													\
  _ms_lvi.pszText = pszText_;														\
  SNDMSG((hwndLV), LVM_GETITEMTEXTA, (WPARAM)i, (LPARAM)(LV_ITEM FAR *)&_ms_lvi);	\
}


//------------------------------------------------------------------------
//	Helper functions
//------------------------------------------------------------------------
LRESULT LV_SetItemState(HWND hWnd, LONG iItem, LONG iSubItem, LONG lState, LONG lStateMask);
INDEX LV_GetItemText(HWND hWnd, INDEX iItem, INDEX iSubItem, WCHAR* pwszName, ULONG ulMaxSize);


// CLASSES

// this structure is used to store the value of all the init properties
struct InitProp
{
	WCHAR		*pwszPropDescription;
	WCHAR		*pwszPropValue;
	GUID		guidPropertySet;
	DBPROPID	dwPropertyID;
};


class CComboBox{
	protected:
		HWND		m_hWnd;
		DBORDINAL	m_cListSize;
		CWString	*m_rgList;

	public:
		CComboBox(HWND hWnd = 0) : m_hWnd(hWnd), m_rgList(NULL), m_cListSize(0) {
			RetrieveListContent();
		}
		~CComboBox() {
			FreeList();
		}

		BOOL		FreeList();
		BOOL		RetrieveListContent();
		BOOL		SetHWND(HWND hWnd) {
						FreeList();
						m_hWnd = hWnd;
						return RetrieveListContent();
		}

		CWString	*GetList() {
						return m_rgList;
		}
		DBORDINAL	GetListSize() {
						return m_cListSize;
		}

		LRESULT		ShowDropDown(BOOL bShowIt) {
						return SendMessageA(m_hWnd, CB_SHOWDROPDOWN, bShowIt, 0L);
		}
};



class CBasicDialog{
	public:
		ULONG					m_ulValidSig;
	protected:
		HWND			m_hWnd;
		BOOL			m_fIsPropertySheet;
		BOOL			m_fIsInExecution;

	public:
						CBasicDialog(BOOL fIsPropertyPage = FALSE, HWND hWnd = 0): 
							m_hWnd(hWnd), m_fIsInExecution(TRUE) { 
							m_fIsPropertySheet = fIsPropertyPage;
						}
						~CBasicDialog() {
						}

		HWND			GetHWND() {
							return m_fIsPropertySheet? PropSheet_GetCurrentPageHwnd(m_hWnd): m_hWnd;
		}

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
							return IsWindowEnabled(GetDlgItem(GetHWND(), nCtrlID));
		}

		void			Activate(){
							SetActiveWindow(m_hWnd);
		}

		// @cmember Create a UDL file
		static BOOL		CreateUDLFile(WCHAR *pwszFileName);
		static BOOL		CreateUDLFile(CHAR *pszFileName);

		// says whether the UI is still up 
		// (assume 2 seconds to bring up the UI)
		BOOL			IsInExecution() {
							return m_fIsInExecution;
		}
		BOOL			HasFinished() {
							return !m_fIsInExecution;
		} 
		

		BOOL			WaitForWindow(
							CHAR		*pszWindowTitle,	// [in] window title
							HWND		*phWnd,				// [out] the handler to the window
							DBORDINAL	nWaitForWindow = 0	// [in]
						);

		BOOL			WaitForForegroundWindow(
							CHAR		*pszWindowTitle,	// [in] window title
							HWND		*phWnd,				// [out] the handler to the window
							DBORDINAL	nWaitForWindow = 0	// [in]
						);

		HWND			GetDlgItem(int nIDDlgItem) {
							return GetDlgItem(GetHWND(), nIDDlgItem);
		}
		static HWND		GetDlgItem(HWND hWnd, int nIDDlgItem) {
							return ::GetDlgItem(hWnd, nIDDlgItem);
		}
}; //CBasicDialog


enum DSL_CREATION_METHOD{
	DSL_CM_UDL			= 0,
	DSL_CM_INTERFACE	= 1,	// created by calling IDBPromptInitialize::promptDataSource
	DSL_CM_VB			= 2		// created from VB using DataLinks objects
};


class CDSL_Dialog: public CBasicDialog
{
	protected:
		CProvPropSets			m_ProvProps;		// cache the current properties of all the providers
		CPropSets				m_InitPropSets;		// cache the init properties of the input DSO
		CPropInfoSets			m_InitPropInfoSets;	// cache info about properties of the initial DSO
		CLSID					m_clsidInitDSO;

		HWND					m_hParentWnd;	// handler to the parent window

		// argument when created by IDBPromptInitialize::PromptDataSource
		const GUID				*m_piid;					// ptr to the interface to be created
		IUnknown				*m_pUnkOuter;				// obj to aggregate the DSO
		DBPROMPTOPTIONS			m_dwPromptOptions;			// prompt options
		ULONG					m_cSourceTypeFilter;		// size of the source type filter list
		DBSOURCETYPE			*m_rgSourceTypeFilter;		// source type filter list
		LPCOLESTR				m_pwszszzProviderFilter;	// provider name filter list
		IUnknown				**m_ppDataSource;			// to DSO object
		IUnknown				*m_pInitDSO;

		IDBPromptInitialize		*m_pIDBPromptInitialize;	// IDBPromptInitialize used
		HRESULT					m_hres;						// the return value of IDBPromptInitialize::PromptDataSource call
		
		// thread management
		unsigned				m_IDThread;
		HANDLE					m_hThread;

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

		// @cmember variable to store the InitDataSource string
		WCHAR					m_wszUDLFileName[cMaxName];

		DSL_CREATION_METHOD		m_CreationMethod;
	
		// @cmember flag for empty (blank) password
		BOOL					m_fBlankPassword;

		// @cmember flag indicating whether the DSL was called with an existing DSO 
		BOOL					m_fExistingDSO;
		BOOL					m_fDSLCanceled;


	public:

		static CSourcesSet		*s_pSourcesSet;
		static BOOL				GetContextInfo();
		static BOOL				FinalFree();
		static HINSTANCE		m_hLibInst;

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

		DSL_CREATION_METHOD			GetCreationMethod() {
										return m_CreationMethod;}

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

		BOOL			PushButton(int nCtrlID);
	
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
		BOOL					KillThread(int nButton = PSBTN_OK, DWORD dwMilliseconds = 2000);

		// @cmember IsDisabledProviderPage
		BOOL					IsDisabledProviderPage() {
			return ((DSL_CM_INTERFACE == GetCreationMethod()) 
				&&	(GetPromptOptions() & DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION));
		}

		// the current page is going to change, update info
		BOOL					Notify_KillActivePage(const ULONG *pulCrtPage = NULL);
		BOOL					CheckActivePage(const ULONG *pulCrtPage = NULL);
		BOOL					CheckActiveConnectionPage();

		// get the current page (based on title) - the value returned is
		// independent of the number of pages, it identifies the page
		ULONG					GetCurrentPage();

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
		
		BOOL					GetListOfProperties(ULONG *pcProperties, WCHAR ***prgProperties);

		// methods to get values from the summary page
		BOOL					GetInitMode(HWND hCtrlWnd, LONG *plInitMode);
		BOOL					GetInitMode(CHAR *pszValue, LONG *plInitMode);
		BOOL					GetInitMode(LONG*);

		// @cmember Get property value from DBPROPID
		// searches the all tab for the value of a certain property
		BOOL					GetPropertyValueFromSummary(DBPROPID, WCHAR**);
		BOOL					GetPropertyValueFromSummary(WCHAR*, WCHAR**);


		// @cmember Open the file browser (for selecting a datasource file under Jolt)
		BOOL					OpenFileBrowser();
		BOOL					SetInitFileNameInBrowser(CHAR *szFileName);
		BOOL					FileBrowser_OnOpen();
		BOOL					FileBrowser_OnCancel();

		// @cmember Set values to various edit controls
		BOOL					SetInitDataSource(LPCWSTR);
		BOOL					SetServerName(LPCWSTR);
		BOOL					SetUserID(LPCWSTR);
		BOOL					SetDatabaseOnServerName(LPCWSTR);
		BOOL					SetDatabaseFileName(LPCWSTR);
		BOOL					SetInitFileName(LPCWSTR);
		BOOL					SetPassword(LPCWSTR);

		// @cmember Set Save Password
		BOOL					SetSavePassword(UINT uVal = BST_CHECKED);
		// change the value of the box
		BOOL					FlipSavePassword();

		// @cmember Set BlankPassword
		BOOL					SetBlankPassword(UINT uVal = BST_CHECKED);
		BOOL					FlipBlankPassword();
		
		// @cmember Set Security Method
		BOOL					SetSecurityMethod(int nValue = IDC_USE_STANDARD);

		// @cmember Set Database Method
		BOOL					SetDatabaseMethod(int nValue = IDC_UseDatabaseOnServerName);

		// @cmember Set a property in the summary property page
		BOOL					SetProperty(WCHAR *pwszProperty, WCHAR *pwszValue);
		BOOL					SetProperty(DBPROPID dbPropID, GUID guidPropSet, WCHAR *pwszValue);
		BOOL					SetProperty(DBPROPINFO *pPropInfo, GUID guidPropSet, WCHAR *pwszValue);
		BOOL					SetProperties(
									DBORDINAL	cPropSets,
									DBPROPSET	*rgPropSets
								);

		BOOL					ResetProperty(DBPROPINFO *pPropInfo, GUID guidPropSet);

		// creates a random value for this type
		static BOOL				BuildRandomValue(DBTYPE dbType, WCHAR *pwszValue);

		// sets the property to a random value
		BOOL					SetRandValForProp(WCHAR *pwszProperty);
		BOOL					SetRandValForProp(DBPROPID dbPropID, GUID guidPropSet);
		BOOL					SetRandValForProp(DBPROPINFO *pPropInfo, GUID guidPropSet);

		// @cmember Press the ok button in the Edit Property Value dialog
		BOOL					EditProperty_OK();
		// @cmember Press the cancel button in the Edit Property Value dialog
		BOOL					EditProperty_Cancel();

		// @cmember select provider from list
		BOOL					SelectProvider(CLSID);
		BOOL					SelectProvider(WCHAR*);

		// @cmember select another provider than the current one from Provider Page
		// if the Provider Page doesn't exist, the method fails,
		// ppExcludedProvList - list of undesirable providers
		BOOL SelectAnotherProvider(const CLSID **ppExcludedProvList=NULL);

		// @cmember set the connection method (datasource name or provider string)
		BOOL	SetConnectionMethod(int);						// Sockeye specific
		
		//@cmember set the initial catalog name
		BOOL	SetInitCatalog(LPCWSTR pwszCatalogName);			// Sockeye specific

		//@cmember set provider string
		BOOL	SetProviderString(WCHAR *pwszProviderString);	// Sockeye specific

		// @cmember Test connection through the "Test Connection" button in the connection dlg
		BOOL					TestConnection(BOOL fRes);
		BOOL					TestConnection(BOOL *fRes = NULL);	// this method goes through pressing the "Test Connection" button
													// but does not check the result of the Action

		// @cmember Check properties on data source object
		BOOL					CheckActiveSummaryPage();
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

		// @cmember Check the delay to display server names
		ULONG Luxor_GetTotalServerCount(clock_t* ctTime);

		// @cmember Check the list of data source names, displayed in the connection page
		// against the enumerator
		BOOL					Sockeye_CheckDSNList();

		// @cmember Set the mode in the advance page
		BOOL					SetInitMode(LONG lMode);
		BOOL					SetInitMode(HWND hCtrlWnd, LONG lMode);
		
		// @cmember Set the impersonation and protection level in the Advanced PAge
		BOOL					SetImpersonationLevel(LONG);
		BOOL					SetProtectionLevel(LONG lProtectionLevel);

		// @cmember Set the timeout value in the advance page
		BOOL					SetInitTimeout(LONG lTimeout);

		// look for property in the prop info sets of the current provider
		DBPROPINFO				*FindProperty(DBPROPID PropertyID, GUID guidPropertySet);
		DBPROPINFO				*FindProperty(WCHAR *pwszDesc, GUID guidPropertySet);
		BOOL					FindProperty(WCHAR *pwszDesc, DBPROPINFO **ppPropInfo, GUID *pguidPropertySet);
		BOOL					SettableProperty(DBPROPID PropertyID, GUID guidPropertySet);
		BOOL					SupportedProperty(DBPROPID PropertyID, GUID guidPropertySet);

		DBPROMPTOPTIONS			GetPromptOptions() {
								return m_dwPromptOptions;}

		HRESULT					GetExpectedInitialize();
		HRESULT					GetExpectedPropSetting();
}; //CDSL_Dialog



class CSummaryEditStringDlg: public CBasicDialog{
	public:
		CSummaryEditStringDlg(HWND hWnd): CBasicDialog(FALSE, hWnd) {;}
		BOOL		CancelDlg();
		BOOL		CloseDlg(BOOL *pfOK = NULL);
};



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
/*
		BOOL			IsInExecution() {
				return m_fIsInExecution;}

		BOOL			HasFinished() {
				return !m_fIsInExecution;} 
*/		
		HRESULT			GetHRESULT(){
				return m_hres;}

		BOOL			IsResult(HRESULT hr){
			return HasFinished() && CHECK(m_hres, hr);}

		// @cmember Pop up DSL page
		static unsigned WINAPI	MyThread(void*);

		// @cmember Kill the DSL page thread
		BOOL					KillThread(int nButton = IDCANCEL, DWORD dwMilliseconds = INFINITE);

		BOOL					SetFileName(WCHAR *pwszFileName);
}; //CDSL_FileDialog


// {0C7FF16C-38E3-11d0-97AB-00C04FC2AD98}
DEFINE_GUID(CLSID_SQLOLEDB, 
0x0C7FF16C, 0x38E3, 0x11d0, 0x97, 0xAB, 0x0, 0xC0, 0x4F, 0xC2, 0xAD, 0x98);

// {DFA22B8E-E68D-11d0-97E4-00C04FC2AD98}
DEFINE_GUID(CLSID_SQLOLEDB_ENUMERATOR,
0xDFA22B8E, 0xE68D, 0x11d0, 0x97, 0xE4, 0x0, 0xC0, 0x4F, 0xC2, 0xAD, 0x98);

// {5CF4CA10-EF21-11d0-97E7-00C04FC2AD98};
DEFINE_GUID(DBPROPSET_SQLOLEDB_SPECIFIC, 
0x5CF4CA10, 0xEF21, 0x11d0, 0x97, 0xE7, 0x0, 0xC0, 0x4F, 0xC2, 0xAD, 0x98);

// {e8cc4cbe-fdff-11d0-b865-00a0c9081c1d}
DEFINE_GUID(CLSID_MSDAORA, 
0xe8cc4cbe, 0xfdff, 0x11d0, 0xb8, 0x65, 0x0, 0xa0, 0xc9, 0x08, 0x1c, 0x1d);

// {dee35060-506b-11cf-b1aa-00aa00b8de95}
DEFINE_GUID(CLSID_JOLT351, 
0xdee35060, 0x506b, 0x11cf, 0xb1, 0xaa, 0x0, 0xaa, 0x00, 0xb8, 0xde, 0x95);

// {dee35070-506b-11cf-b1aa-00aa00b8de95}
DEFINE_GUID(CLSID_JOLT40, 
0xdee35070, 0x506b, 0x11cf, 0xb1, 0xaa, 0x0, 0xaa, 0x00, 0xb8, 0xde, 0x95);

// {3449A1C8-C56C-11D0-AD72-00C04FC29863}
DEFINE_GUID(CLSID_MSDataShape, 
0x3449A1C8, 0xC56C, 0x11D0, 0xAD, 0x72, 0x0, 0xC0, 0x4F, 0xC2, 0x98, 0x63);

// Indexing Service
// {c7310550-ac80-11d1-8df3-00c04fb6ef4f}
DEFINE_GUID(CLSID_MSSearch,
0xc7310550, 0xac80, 0x11d1, 0x8d, 0xf3, 0x0, 0xc0, 0x4f, 0xb6, 0xef, 0x4f);

// Internet publishing provider
// {AF320921-9381-11d1-9C3C-0000F875AC61}
DEFINE_GUID(CLSID_MSDAIPP,
0xAF320921, 0x9381, 0x11d1, 0x9C, 0x3C, 0x0, 0x00, 0xF8, 0x75, 0xAC, 0x61);

// Microsoft OLE DB Provider for Visual FoxPro
// {50BAEED9-ED25-11D2-B97B-000000000000}
DEFINE_GUID(CLSID_VFP,
0x50BAEED9, 0xED25, 0x11D2, 0xB9, 0x7B, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00);


#endif _DSL_DIALOG_H_


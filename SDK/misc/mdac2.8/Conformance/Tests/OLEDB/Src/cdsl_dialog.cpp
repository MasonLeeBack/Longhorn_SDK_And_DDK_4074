// file CDSL_Dialog.cpp
//--------------------------------------------------------------------
// Microsoft OLE DB Test
//
// Copyright (C) 1998-2000 Microsoft Corporation
//
// @doc 
//
// @module IDBPromptInitialize.CPP | IDBPromptInitialize source file for all test modules.
#include "modstandard.hpp"
#include "commctrl.h"	// InitCommonControls 

#include "privlib.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>

#include <dlgs.h>

const ULONG cMaxName	= 300;
const int	nMaxProv	= 200;	// maximum number of providers
extern ULONG g_nTabs;

#include "initguid.h"

#include "CVectorEx.cpp"
#include "ServiceComp.h"
#include "CDSL_Dialog.hpp"
								
extern LPFGetComputerName	GetComputerNameI;
								
ULONG		g_ulWaitPeriod = 1000;

// language used
WORD		g_wLanguage ;

// the title of the DSL window
CHAR		g_szIDS_DSL_TITLE_PROPERTY_PAGE[cMaxName];		//"Data Link Properties"

// titles of the error window
CHAR		g_szIDS_TITLE_DATA_LINK_SUCCESS[cMaxName];		//"Microsoft Data Link"
CHAR		g_szIDS_TITLE_DATA_LINK[cMaxName];				//"Microsoft Data Link Error"

CHAR		g_szIDD_PROVIDER_GENERIC[cMaxName];				//"Provider"
CHAR		g_szIDD_CONNECTION_GENERIC[cMaxName];			//"Connection"
CHAR		g_szIDD_ADVANCED_GENERIC[cMaxName];				//"Advanced"
CHAR		g_szIDD_SUMMARY_GENERIC[cMaxName];				//"All"

CHAR		g_szIDD_SUMMARY_EDIT[cMaxName];					//"Edit Property Value"

CHAR		g_szIDS_Jolt_OFNTitle[cMaxName];				// "Select Access Database"
CHAR		g_szOLEDB32DLL[cMaxName];
CHAR		g_szOLEDB32RDLL[cMaxName];

CHAR		g_szIDS_DSL_TITLE_SELECT[cMaxName];				//"Select Data Link File"
CHAR		g_szIDS_DSL_TITLE_ORGANIZE[cMaxName];			//"Organize Data Link Files"

LPFGetWindowText	GetWindowTextI		= GetWindowTextWRAP;
LPFSetWindowText	SetWindowTextI		= SetWindowTextWRAP;

const GUID		DBPROPSET_JETOLEDB_DBINIT			= {0x82cf8156,0x9b40,0x11d0,{0x9e,0xbd,0x00,0xc0,0x4f,0xc2,0xc2,0xe0}};
const DBPROPID	DBPROP_JETOLEDB_DATABASEPASSWORD	= 0x100;	// Password for Database 


CSourcesSet		*CDSL_Dialog::s_pSourcesSet = NULL;
HINSTANCE		CDSL_Dialog::m_hLibInst		= NULL;

const ULONG		g_cWaitForWindow = 100;

HWND GetEdt1(HWND hWnd);


static WCHAR* _GetPropertyName(DBPROPID dwPropertyID, REFGUID guidPropertySet)
{
	WCHAR *p = GetPropertyName(dwPropertyID, guidPropertySet);
	if (p)
		return p;

	static WCHAR buf[12] = { '0', 'x' };
	_itow(dwPropertyID, &buf[2], 16);
	return &buf[0];
}


static WCHAR* _GetPropSetName(REFGUID guidPropertySet)
{
	WCHAR *p = GetPropSetName(guidPropertySet);
	if (p)
		return p;

	static WCHAR buf[100];
	StringFromGUID2(guidPropertySet, &buf[0], sizeof(buf));
	return &buf[0];
}


static void PrintTextOfWarningWindow(HWND hWnd)
{
	ASSERT(hWnd != 0);

	char buf[200],  ClassName[50];
	GetWindowTextA(hWnd, buf, sizeof(buf));
	odtLog << L"\nWARNING WINDOW DISPLAYED: " << &buf[0] << "\n";

	// loop through the child windows of hWnd
	// looking for "Static" control with text
	for (hWnd = GetWindow(hWnd, GW_CHILD); hWnd; hWnd = GetWindow(hWnd, GW_HWNDNEXT))
	{
		GetClassNameA(hWnd, ClassName, sizeof(ClassName));
		if (strcmp(&ClassName[0], "Static") != 0)
			continue;

		int len = GetWindowTextLengthA(hWnd);
		if (!len)
			continue;

		GetWindowTextA(hWnd, &buf[0], sizeof(buf));
		break;
	}

	odtLog << &buf[0] << "\n";
}



BOOL CComboBox::FreeList() 
{
/*	DBORDINAL	index;

	for (index=0; index < m_cListSize; index++)
	{
		SAFE_DELETE(m_rgList[index]);
	}
	SAFE_FREE*/
	delete [] m_rgList;
	m_rgList = NULL;
	m_cListSize = 0;
	return TRUE;
} //CComboBox::FreeList




BOOL CComboBox::RetrieveListContent()
{
	TBEGIN
	DBORDINAL	cItem;
	LRESULT		lLen;
	LRESULT		lResult;
	CHAR		*pszListItem	= NULL;
	WCHAR		*pwszListItem	= NULL;

	// get the number of strings in the combo box
	lResult = SendMessage(m_hWnd, CB_GETCOUNT, 0, 0L);
	TESTC(CB_ERR != lResult);

	m_cListSize = (DBORDINAL)lResult;

	if (0 < m_cListSize)
		m_rgList = new CWString[(ULONG)m_cListSize];

	for (cItem=0; cItem < m_cListSize; cItem++)
	{
		// get the string length
		lLen = SendMessageA(m_hWnd, CB_GETLBTEXTLEN, cItem, 0L);
		
		TESTC(CB_ERR != lLen);

		// alloc memory for the string
		SAFE_ALLOC(pszListItem, CHAR, lLen + 1);

		// get the string
		SendMessageA(m_hWnd, CB_GETLBTEXT, cItem, (LPARAM)pszListItem);

		// convert the string to Unicode
		pwszListItem = ConvertToWCHAR(pszListItem);

		// store the current string
		m_rgList[cItem] = pwszListItem;

		// free temporary strings
		SAFE_FREE(pwszListItem);
		SAFE_FREE(pszListItem);
	}

CLEANUP:
	// free temporary strings
	SAFE_FREE(pszListItem);
	SAFE_FREE(pwszListItem);
	TRETURN
} //CComboBox::RetrieveListContent




// wait for a window with this name to appear and return its handler
BOOL CBasicDialog::WaitForWindow(
	CHAR		*pszWindowTitle,		// [in] window title
	HWND		*phWnd,					// [out] the handler to the window
	DBORDINAL	nWaitForWindow/*=0*/	// [in]
)
{
	BOOL			fFound = FALSE;
	HWND			hWnd;
	DBORDINAL		index;

	TESTC(NULL != phWnd)
	*phWnd = NULL;

	if (0 == nWaitForWindow)
		nWaitForWindow = g_cWaitForWindow;

	for (index = 0; index < nWaitForWindow && m_fIsInExecution; index++)
	{
		hWnd = FindWindowA(NULL, pszWindowTitle);

		if (NULL != hWnd)
			break;

		Sleep(100);
	}
	
	if (NULL != hWnd)
	{
		*phWnd = hWnd;
		fFound = TRUE;
	}

CLEANUP:
	return fFound;
} // CBasicDialog::WaitForWindow


BOOL CBasicDialog::WaitForForegroundWindow(
	CHAR		*pszWindowTitle,	// [in] window title
	HWND		*phWnd,				// [out] the handler to the window
	DBORDINAL	nWaitForWindow/* = 0*/	// [in]
)
{
	BOOL			fFound = FALSE;
	HWND			hWnd;
	const ULONG		cWaitForWindow = 5000;
	CHAR			szWindowName[cMaxName];
	DBORDINAL		index;

	TESTC(NULL != phWnd)
	*phWnd = NULL;

	if (0 == nWaitForWindow)
		nWaitForWindow = cWaitForWindow;

	for (index = 0; index < nWaitForWindow && m_fIsInExecution; index++)
	{
		hWnd = GetForegroundWindow();

		// check the caption of the new foreground window
		GetWindowTextA(hWnd, szWindowName, cMaxName);

		if (0 == strcmp(szWindowName, pszWindowTitle))
			break;

		hWnd = NULL;
		Sleep(100);
	}
	
	if (NULL != hWnd)
	{
		*phWnd = hWnd;
		fFound = TRUE;
	}

CLEANUP:
	return fFound;
} // CBasicDialog::WaitForForegroundWindow


// This function reads the value of 
// HKEY_CLASSES_ROOT\CLSID\{2206CDB2-19C1-11D1-89E0-00C04FD7A829}\InprocServer32
// in order to find the exact address of oledb32.dll 
// oledb32r.dll is supposed to be in the same directory
BOOL GetCompleteNameOfOLEDB32Dlls()
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
} //GetCompleteNameOfOLEDB32Dlls




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
 
	szBuf[min(cchBuf-1, len)] = '\0'; 
 
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
 
	szBuf[min(cchBuf-1, len)] = '\0'; 

Error: 
	if (hgl) 
	{ 
		UnlockResource(hgl);	// maybe not needed 
		FreeResource(hgl);		// maybe not needed 
	} 
 
    return len; 
}  //LoadDialogTitleA




//////////////////////////////////////////////////////////////////
// BOOL LV_SetItemState
//
//////////////////////////////////////////////////////////////////
LRESULT LV_SetItemState(HWND hWnd, LONG iItem, LONG iSubItem, LONG lState, LONG lStateMask)
{
	//LVM_SETITEM
	LV_ITEM lvItem = { LVIF_STATE, iItem, iSubItem, lState, lStateMask, NULL, 0, 0, 0, 0};
	return SendMessage(hWnd, LVM_SETITEMSTATE, (WPARAM)iItem, (LPARAM)&lvItem);
} //LV_SetItemState


//////////////////////////////////////////////////////////////////
// LV_GetItemText
//
//////////////////////////////////////////////////////////////////
INDEX LV_GetItemText(HWND hWnd, INDEX iItem, INDEX iSubItem, WCHAR* pwszName, ULONG ulMaxSize)
{
	ASSERT(pwszName);
	pwszName[0] = L'\0';
	INDEX lReturn = 0;

	//LVM_GETITEMTEXT
	if(IsUnicodeOS())
	{
		LV_ITEMW lvItem = { LVIF_TEXT, (INT)iItem, (INT)iSubItem, 0, 0, pwszName, ulMaxSize, 0, 0, 0};
		lReturn = (INDEX)SendMessage(hWnd, LVM_GETITEMTEXTW, (WPARAM)iItem, (LPARAM)&lvItem);
	}
	else
	{
		CHAR szBuffer[MAX_NAME_LEN] = {0};

		LV_ITEMA lvItem = { LVIF_TEXT, (INT)iItem, (INT)iSubItem, 0, 0, szBuffer, MAX_NAME_LEN, 0, 0, 0};
		lReturn = (INDEX)SendMessage(hWnd, LVM_GETITEMTEXTA, (WPARAM)iItem, (LPARAM)&lvItem);

		ConvertToWCHAR(szBuffer, pwszName, ulMaxSize);
	}

	return lReturn;
} //LV_GetItemText


//-------------------------------------------------------------------------
//	CBasicDialog::PushButton
//		Pushes a dialog button
//		The proper dialog should already be selected
//-------------------------------------------------------------------------
BOOL CBasicDialog::PushButton(int nCtrlID)
{
	TBEGIN
	HWND	hCtrlWnd;

	// checked that the control exists
	hCtrlWnd = GetDlgItem(nCtrlID);
	TESTC(NULL != hCtrlWnd);

	// send the appropiate message to the button
	PostMessage(hCtrlWnd, BM_CLICK, 0, 0L);
//	Sleep(1000);

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
	WCHAR	wszText[cMaxName]	= L"";

	TESTC(NULL != pwszTextToSet);

	// get the handle to the field
	hWndCtrl = GetDlgItem(nCtrlID);
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

	TESTC(NULL != pwszText);

	// get the handle to the field
	hCtrlWnd = GetDlgItem(nCtrlID);
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
	HWND	hWndCtrl;
	ULONG	iCtrl;

	for (iCtrl=0; iCtrl<cCtrlID; iCtrl++)
	{
		hWndCtrl = GetDlgItem(rgCtrlID[iCtrl]);
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

	TESTC(fStatus == IsWindowEnabled(GetDlgItem(CtrlID)));
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
	hCtrlWnd = GetDlgItem(nCtrlID);
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
	hCtrlWnd = GetDlgItem(nCtrlID);
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



BOOL CDSL_Dialog::GetContextInfo()
{
	TBEGIN
	const ULONG				cCPLen = 7;
	CHAR					szCodePage[cCPLen];
	ULONG					ulRes = IDS_DSL_TITLE_PROPERTY_PAGE;
	// instance of the library
	HINSTANCE				hLibInst;
	HINSTANCE				hModuleLib;

	TESTC(GetCompleteNameOfOLEDB32Dlls());

	hLibInst	= LoadLibraryExA(g_szOLEDB32DLL, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	hModuleLib	= LoadLibraryExA(g_szOLEDB32RDLL, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

	TESTC(NULL != hLibInst);

	GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_IDEFAULTANSICODEPAGE, szCodePage, cCPLen);
	g_wLanguage  = (USHORT) atoi(szCodePage);

	TESTC( 0 < LoadStringA(hModuleLib, IDS_DSL_TITLE_PROPERTY_PAGE, 
		g_szIDS_DSL_TITLE_PROPERTY_PAGE, cMaxName, g_wLanguage));

	TESTC( 0 < LoadStringA(hModuleLib, IDS_TITLE_DATA_LINK, 
		g_szIDS_TITLE_DATA_LINK, cMaxName, g_wLanguage));

	TESTC( 0 < LoadStringA(hModuleLib, IDS_TITLE_DATA_LINK_SUCCESS, 
		g_szIDS_TITLE_DATA_LINK_SUCCESS, cMaxName, g_wLanguage));

	// get the string that gives the title of the browse dialog
	TESTC( 0 < LoadStringA(hModuleLib, IDS_Jolt_OFNTitle, 
		g_szIDS_Jolt_OFNTitle, cMaxName, g_wLanguage));

	// load the titles of property sheet pages
	TESTC(0 < LoadDialogTitleA(hModuleLib, IDD_PROVIDER_GENERIC, 
		g_szIDD_PROVIDER_GENERIC, cMaxName, g_wLanguage));

	TESTC(0 < LoadDialogTitleA(hModuleLib, IDD_CONNECTION_GENERIC, 
		g_szIDD_CONNECTION_GENERIC, cMaxName, g_wLanguage));

	TESTC(0 < LoadDialogTitleA(hModuleLib, IDD_ADVANCED_GENERIC, 
		g_szIDD_ADVANCED_GENERIC, cMaxName, g_wLanguage));

	TESTC(0 < LoadDialogTitleA(hModuleLib, IDD_SUMMARY_GENERIC, 
		g_szIDD_SUMMARY_GENERIC, cMaxName, g_wLanguage));

	TESTC( 0 < LoadStringA(hModuleLib, IDS_DSL_TITLE_SELECT, 
		g_szIDS_DSL_TITLE_SELECT, cMaxName, g_wLanguage));

	TESTC( 0 < LoadStringA(hModuleLib, IDS_DSL_TITLE_ORGANIZE, 
		g_szIDS_DSL_TITLE_ORGANIZE, cMaxName, g_wLanguage));

	// get the title of the dialog used to edit property values
	TESTC(0 < LoadDialogTitleA(hModuleLib, IDD_SUMMARY_EDIT_STRING, 
		g_szIDD_SUMMARY_EDIT, cMaxName, g_wLanguage));

CLEANUP:
	if (hLibInst)
		FreeLibrary(hLibInst);
	if (hModuleLib)
		FreeLibrary(hModuleLib);

	TRETURN
} //CDSL_Dialog::GetContextInfo




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::FinalFree
//		Frees the libraries used (see GetContextInfo)
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::FinalFree()
{
	TBEGIN

/*	if (g_hLibInst)
		FreeLibrary(g_hLibInst);
	if (g_hModuleLib)
		FreeLibrary(g_hModuleLib);
*/
	TRETURN
} //CDSL_Dialog::FinalFree




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::CDSL_Dialog
//		creates DSL thread
//-------------------------------------------------------------------------
CDSL_Dialog::CDSL_Dialog()
{
	ASSERT(s_pSourcesSet);
	m_fIsInExecution		= FALSE;
	m_hThread				= 0;
	m_pIDBPromptInitialize	= NULL;
	m_rgProviderList		= NULL;
	m_cProviderList			= 0;
	m_pInitDSO				= NULL;
	m_hLibInst				= NULL;
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
	m_rgProviderList		= NULL;
	m_cProviderList			= 0;
	m_pInitDSO				= NULL;
	
	ConvertToWCHAR(szUDLFileName, wszUDLFileName, cMaxName);
	CDSL_Dialog::CDSL_Dialog(wszUDLFileName);
	
	m_hLibInst				= NULL;
} //CDSL_Dialog::CDSL_Dialog




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::CDSL_Dialog
//		creates DSL thread
//-------------------------------------------------------------------------
CDSL_Dialog::CDSL_Dialog(WCHAR *wszUDLFileName) : CBasicDialog(TRUE)
{
	ASSERT(s_pSourcesSet);
	m_fIsInExecution		= FALSE;
	m_hThread				= 0;
	m_pIDBPromptInitialize	= NULL;
	m_rgProviderList		= NULL;
	m_cProviderList			= 0;
	m_pInitDSO				= NULL;
	m_hLibInst				= NULL;

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
	ASSERT(s_pSourcesSet);

	m_hLibInst				= NULL;
	m_fIsInExecution		= FALSE;
	m_hThread				= 0;
	m_pIDBPromptInitialize	= NULL;
	m_rgProviderList		= NULL;
	m_cProviderList			= 0;
	m_pInitDSO				= NULL;

	TESTC(SpawnPromptDataSource(pIDBPromptInitialize, pUnkOuter,
		hWndParent,	dwPromptOptions, cSourceTypeFilter, rgSourceTypeFilter,
		pwszszzProviderFilter, riid, ppDataSource));
CLEANUP:
	return;
} //CDSL_Dialog::CDSL_Dialog




CDSL_Dialog::~CDSL_Dialog()
{
	KillThread();//PSBTN_CANCEL);
	FreeProviderList();
	SAFE_RELEASE(m_pInitDSO);
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
	HWND			hCrtWnd;
	CHAR			szWindowName[cMaxName] = "";

	IDBProperties	*pIDBProperties	= NULL;

	ULONG			cPropSets		= 0;
	DBPROPSET		*rgPropSets		= NULL;

	ULONG			cPropSets2		= 0;
	DBPROPSET		*rgPropSets2	= NULL;

	ULONG			cIdxProv		= 0;
	ULONG			*rgIdxProv		= NULL;
	BOOL			fOneProvider	= FALSE;

	ULONG			index;

	WCHAR			*pwszInitString	= NULL;
	WCHAR			*pwszProvProgID	= NULL;

	IDataInitialize	*pIDataInit		= NULL;

	g_nTabs++;
	odtLog << "\n";
	Ident();
	odtLog << "<SpawnPromptData>\n";

	m_fIsPropertySheet	= TRUE;
	m_fExistingDSO		= ppDataSource && *ppDataSource;
	m_fDSLCanceled		= FALSE;
	if (m_fIsInExecution)
		TESTC(KillThread());

	// spwan a new thread for DSL
	m_CreationMethod = DSL_CM_INTERFACE;
	m_hThread = 0;
	SAFE_RELEASE(m_pInitDSO);

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
	
	SetDenySPInClear(FALSE);

	m_ProvProps.Free();
	m_InitPropInfoSets.Free();

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, CDSL_Dialog::MyThread,
					(void*)this,
					0, 
					&m_IDThread);
	
	// check that the thread was created
	TESTC( 0 != m_hThread);
	Sleep(100);

	
	fOneProvider = m_ppDataSource && *m_ppDataSource;
	if (!fOneProvider)
	{
		// check whether filtering would result in a single provider
		// get the array of index to selected providers
		TESTC(GetFilteredProviders(&cIdxProv, &rgIdxProv));
			
		fOneProvider = 0 < cIdxProv;

		m_clsidProvider = (fOneProvider)? (CLSID)(*s_pSourcesSet)[rgIdxProv[0]]: CLSID_NULL;

		for (index = 1; index < cIdxProv; index++)
		{
			fOneProvider = fOneProvider && ((CLSID)(*s_pSourcesSet)[rgIdxProv[index-1]] == (CLSID)(*s_pSourcesSet)[rgIdxProv[index]]);		
			if (CLSID_MSDASQL == (CLSID)(*s_pSourcesSet)[rgIdxProv[index]])
				m_clsidProvider = CLSID_MSDASQL;
		}

		// get the clsid
		if (fOneProvider 
		)
		{
			if (CLSID_NULL == m_clsidProvider)
				m_clsidProvider = m_pwszszzProviderFilter ? (CLSID)(*s_pSourcesSet)[rgIdxProv[0]] : CLSID_MSDASQL;
		}
			
		// store the provider's properties
		if (CLSID_NULL != m_clsidProvider) //(m_fIsInExecution)
		{
			wcscpy(m_wszProviderDescription, (WCHAR*)(*s_pSourcesSet)[m_clsidProvider]);
			m_ProvProps.AddProviderWithDefPropValues(m_clsidProvider);
		}
	}
	else
	{
		m_pInitDSO = *m_ppDataSource;
		m_pInitDSO->AddRef();
		(*m_ppDataSource)->QueryInterface(IID_IDBProperties, (void**)&pIDBProperties);
			
		if (pIDBProperties)
		{
			// find out the clsid of the current provider and store it to m_clsidProvider
			pIDataInit = CServiceComp::pIDataInitialize();
			TESTC(NULL != pIDataInit);
			TESTC_(pIDataInit->GetInitializationString(pIDBProperties, TRUE, &pwszInitString), S_OK);
			TESTC(GetModInfo()->GetStringKeywordValue(pwszInitString, L"Provider", &pwszProvProgID));
			CLSIDFromProgID(pwszProvProgID, &m_clsidInitDSO);

			m_clsidProvider = m_clsidInitDSO;
			wcscpy(m_wszProviderDescription, (WCHAR*)(*s_pSourcesSet)[m_clsidProvider]);

			// get the properties
			TESTC_(pIDBProperties->GetProperties(0, NULL, &cPropSets, &rgPropSets), S_OK);
					
			// store the provider's properties
			m_ProvProps.AddProvider(m_clsidProvider, cPropSets, rgPropSets);

			// store those initial properties
			TESTC(DuplicatePropertySets(cPropSets, rgPropSets, &cPropSets2, &rgPropSets2));
			m_InitPropSets.Attach(cPropSets2, rgPropSets2);
			m_InitPropSets.PrintPropSets();

			//get the prop info sets
			TESTC_(m_InitPropInfoSets.CreatePropInfoSet(pIDBProperties), S_OK);
		}
	}

	// get the foreground window and make sure it has focus
	if (CLSID_NULL == m_clsidProvider)
	{
		// make sure there is a warning
		if (	m_fIsInExecution && (0 == cIdxProv) 
			&&	COMPARE(WaitForForegroundWindow(g_szIDS_TITLE_DATA_LINK, &m_hWnd), TRUE))
		{
			// close this window
			HWND			hOK;
			hOK = GetDlgItem(m_hWnd, IDCANCEL);
			
			TESTC(NULL != hOK);
			SendMessage(hOK, BM_CLICK, 0, 0L);			
			Sleep(100);
			m_hWnd = NULL;
		}
	}

	TESTC(WaitForForegroundWindow(g_szIDS_DSL_TITLE_PROPERTY_PAGE, &m_hWnd)
			|| !m_fIsInExecution);

	if (m_fIsInExecution)
	{
		if (CLSID_NULL == m_clsidProvider)
		{
			COMPARE(GetProvider(), TRUE);
			ASSERT(CLSID_NULL != m_clsidProvider);
			m_ProvProps.AddProviderWithDefPropValues(m_clsidProvider);
		}

		ULONG	nCrtPage = GetCurrentPage();

		if (g_nConnection == nCrtPage)
		{
			TESTC(CheckActivePage(&g_nConnection));
		}

		// if dialog is up and filter is made of a single provider
		// check that the connection page is displayed
		if (	m_fExistingDSO
			||	m_pwszszzProviderFilter && L'\0' == m_pwszszzProviderFilter[1+wcslen(m_pwszszzProviderFilter)])
		{
			// make sure the connection page was obtained
			// if the filter is made of a single provider and the DSL is started
			// then the filter must have worked and the page displayed is the connection one
			TESTC(IsCurrentPage(g_nConnection));
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
	}


CLEANUP:
	Ident();
	odtLog << "</SpawnPromptData>\n";
	g_nTabs--;

	SAFE_FREE(pwszInitString);
	SAFE_FREE(pwszProvProgID);
	SAFE_RELEASE(pIDBProperties);
	SAFE_FREE(rgIdxProv);
	CServiceComp::ReleaseSCInterface(pIDataInit);
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

	m_hLibInst	= LoadLibraryExA(g_szOLEDB32DLL, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	pfOpenDSLFile = (void (CALLBACK*)(HWND,HINSTANCE,LPSTR,int))
			GetProcAddress(m_hLibInst, "OpenDSLFile");

	pszUDLFileName = ConvertToMBCS(pThis->m_wszUDLFileName);
	TESTC(NULL != pfOpenDSLFile);
	(*pfOpenDSLFile)(0, m_hLibInst, pszUDLFileName, SW_SHOWNORMAL);
	
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
	CHAR			szWindowName[cMaxName] = "";

	IDBProperties	*pIDBProperties	= NULL;
	IMoniker		*pIMoniker		= NULL;
	IBindCtx		*piBindCtx		= NULL;

	ULONG			cPropSets		= 0;
	DBPROPSET		*rgPropSets		= NULL;

	ULONG			cPropSets2		= 0;
	DBPROPSET		*rgPropSets2	= NULL;
	
	WCHAR			*pwszInitString	= NULL;
	WCHAR			*pwszProvProgID	= NULL;

	IDataInitialize	*pIDataInit		= NULL;

	g_nTabs++;
	odtLog << "\n";
	Ident();
	odtLog << "<SpawnUDLFile value = \"" << wszUDLFileName << "\">\n";

	m_fIsPropertySheet	= TRUE;
	m_fExistingDSO		= FALSE;
	m_fDSLCanceled		= FALSE;
	m_pInitDSO			= NULL;

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
	SetDenySPInClear(TRUE);
	
	m_ProvProps.Free();
	m_InitPropSets.Free();
	m_InitPropInfoSets.Free();

	// create DSO from file, read the props and set
	CreateFileMoniker(wszUDLFileName, &pIMoniker);
	TESTC_(CreateBindCtx(0 /*reserved*/, &piBindCtx), S_OK);
	TESTC_(pIMoniker->BindToObject(piBindCtx, NULL, IID_IDBProperties, (LPVOID*)&pIDBProperties), S_OK);
	// get the properties
	TESTC_(pIDBProperties->GetProperties(0, NULL, &cPropSets, &rgPropSets), S_OK);

	// find out the clsid of the current provider and store it 
	pIDataInit = CServiceComp::pIDataInitialize();
	TESTC(NULL != pIDataInit);
	TESTC_(pIDataInit->GetInitializationString(pIDBProperties, TRUE, &pwszInitString), S_OK);
	TESTC(GetModInfo()->GetStringKeywordValue(pwszInitString, L"Provider", &pwszProvProgID));
	CLSIDFromProgID(pwszProvProgID, &m_clsidProvider);
	
	// store the provider's properties
	m_ProvProps.AddProvider(m_clsidProvider, cPropSets, rgPropSets);

	// store those initial properties
	TESTC(DuplicatePropertySets(cPropSets, rgPropSets, &cPropSets2, &rgPropSets2));
	m_InitPropSets.Attach(cPropSets2, rgPropSets2);
	m_InitPropSets.PrintPropSets();

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, CDSL_Dialog::MyUDLThread,
					(void*)this,
					0, 
					&m_IDThread);
	
	// check that the thread was created
	TESTC( 0 != m_hThread);

	// wait for the DSL to appear (1sec)
	// after 1 sec I expect either to have the UI ot the
	// method to have finished its execution

	// this code is just for debugging purposes
	if (FALSE)
	{
		for (; TRUE;)
			Sleep(0);
	}

	// get the foreground window and make sure it has focus
	Sleep(100);
	TESTC(WaitForForegroundWindow(g_szIDS_DSL_TITLE_PROPERTY_PAGE, &m_hWnd)
		|| !m_fIsInExecution);

	if (m_fIsInExecution)
	{
		TESTC(IsCurrentPage(g_nConnection));
		TESTC(CheckActivePage(&g_nConnection));
	}

CLEANUP:
	Ident();
	odtLog << "</SpawnUDLFile>\n";
	g_nTabs--;

	SAFE_FREE(pwszInitString);
	SAFE_FREE(pwszProvProgID);
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIMoniker);
	SAFE_RELEASE(piBindCtx);
	CServiceComp::ReleaseSCInterface(pIDataInit);
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
	TBEGIN
	CHAR	szText[cMaxName]			= "";
	CHAR	*szDialogName[]	= {	
											g_szIDD_PROVIDER_GENERIC, 
											g_szIDD_CONNECTION_GENERIC, 
											g_szIDD_ADVANCED_GENERIC, 
											g_szIDD_SUMMARY_GENERIC};
	HWND	hCrtWnd						= PropSheet_GetCurrentPageHwnd(m_hWnd);
	BOOL	fDisProv					= (DSL_CM_INTERFACE == m_CreationMethod) && m_dwPromptOptions & DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION;

	TESTC(nPage < 4);
	TESTC(NULL != hCrtWnd);

	// get the title of the current dialog
	TESTC(0 != GetWindowTextA(hCrtWnd, szText, cMaxName));
	
	// check whether we already are in the desired dialog
	TESTB = (0 == strcmp(szText, szDialogName[nPage]));

	if (TESTB)
		TESTC(!fDisProv || nPage > 0);

CLEANUP:
	TRETURN
} //CDSL_Dialog::IsCurrentPage



//-------------------------------------------------------------------------
//
//	CDSL_Dialog::GetCurrentPage
//		Check if the current page is the one asked
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
ULONG CDSL_Dialog::GetCurrentPage()
{
	TBEGIN
	ULONG	ulPage;
	CHAR	szText[cMaxName]			= "";
	CHAR	*szDialogName[]				= {	
											g_szIDD_PROVIDER_GENERIC, 
											g_szIDD_CONNECTION_GENERIC, 
											g_szIDD_ADVANCED_GENERIC, 
											g_szIDD_SUMMARY_GENERIC};
	HWND	hCrtWnd						= PropSheet_GetCurrentPageHwnd(m_hWnd);
	BOOL	fDisProv					= (DSL_CM_INTERFACE == m_CreationMethod) && m_dwPromptOptions & DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION;

	TESTC(NULL != hCrtWnd);

	// get the title of the current dialog
	TESTC(0 != GetWindowTextA(hCrtWnd, szText, cMaxName));
	TESTC(NULL != szText);

	// check whether we already are in the desired dialog
	for (ulPage = 0; ulPage < NUMELEM(szDialogName); ulPage++)
	{
		if (0 == strcmp(szText, szDialogName[ulPage]))
			return ulPage;
	}

CLEANUP:
	TRETURN
} //CDSL_Dialog::GetCurrentPage




//-------------------------------------------------------------------------
//	CDSL_Dialog::PushButton
//		Pushes a dialog button
//		The proper dialog should already be selected
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::PushButton(int nCtrlID)
{
	TBEGIN
	HWND		hCtrlWnd;
	BOOL		fSpecialCase = IsCurrentPage(g_nProvider) && IDC_Next == nCtrlID;

	if (fSpecialCase)
	{
		TESTC(Notify_KillActivePage(&g_nProvider));
	}
	
	// checked that the control exists
	hCtrlWnd = GetDlgItem(nCtrlID);
	TESTC(NULL != hCtrlWnd);

	// send the appropiate message to the button
	PostMessage(hCtrlWnd, BM_CLICK, 0, 0L);

	// the above call is asynch, give it some time to complete before move further
	Sleep(100);

	if (fSpecialCase)
	{
		Sleep(100);
		TESTC(CheckActivePage());
	}

CLEANUP:
	TRETURN
} //CDSL_Dialog::PushButton



//-------------------------------------------------------------------------
//
//	CDSL_Dialog::CheckActivePage
//		Check the current active page
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::CheckActivePage(const ULONG *pulCrtPage/*=NULL*/)
{
	TBEGIN
	ULONG	ulCrtPage = pulCrtPage? *pulCrtPage: GetCurrentPage();

	// put here all the checking related to displaying the crt prop values
	switch (ulCrtPage)
	{
		case g_nProvider:
			break;

		case g_nConnection:
			TESTC(CheckActiveConnectionPage());
			break;

		case g_nAdvanced:
			break;

		case g_nAll:
			TESTC(CheckActiveSummaryPage());
			break;

		default:
			TESTC(FALSE);
	}


CLEANUP:
	TRETURN
} //CDSL_Dialog::CheckActivePage




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::Notify_KillActivePage
//		The current page is going to change, update info
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::Notify_KillActivePage(const ULONG *pulCrtPage/*=NULL*/)
{
	TBEGIN
	ULONG	ulCrtPage = pulCrtPage? *pulCrtPage: GetCurrentPage();
	WCHAR	wszText[cMaxName];

	// if the current page is the Provider Page, store the clsid and the props
	switch (ulCrtPage)
	{
		case g_nProvider:
			// add the provider to the list...
			GetProvider(); // retrieves the selected provide in m_clsidProvider

			// if the provider info does not yet exist, then add it
			if (-1 == m_ProvProps.GetProviderIndex(m_clsidProvider))
				// store the provider's properties
				m_ProvProps.AddProviderWithDefPropValues(m_clsidProvider);
			break;

		case g_nConnection:
			// make sure there is data about the provider
			TESTC(-1 != m_ProvProps.GetProviderIndex(m_clsidProvider));
					
			if (CLSID_SQLOLEDB == m_clsidProvider)
			{
				ULONG	status1, status2;

				// update info related to database method used: init cat or file + init cat name
				status1 = IsDlgButtonChecked(GetHWND(), IDC_UseDatabaseFileName);
				status2 = IsDlgButtonChecked(GetHWND(), IDC_UseDatabaseOnServerName);

				TESTC(	(BST_CHECKED == status1 && BST_UNCHECKED == status2)
					||	(BST_UNCHECKED == status1 && BST_CHECKED == status2));
				
				if (BST_CHECKED == status1)
				{
					// IDC_UseDatabaseFileName is used
					TESTC(GetTextFromCtrl(IDC_DatabaseFileName, wszText, cMaxName));
					TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_CATALOG, 
						DBPROPSET_DBINIT, (wszText[0]!=L'\0')? VT_BSTR: VT_EMPTY, (void*)wszText), S_OK);
					TESTC(GetTextFromCtrl(IDC_DBPROP_INIT_FILENAME, wszText, cMaxName));
					TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_FILENAME, 
						DBPROPSET_SQLOLEDB_SPECIFIC, (wszText[0]!=L'\0')? VT_BSTR: VT_EMPTY, (void*)wszText), S_OK);
				}
				else
				{
					// IDC_DatabaseOnServerName is used
					TESTC(GetTextFromCtrl(IDC_DatabaseOnServerName, wszText, cMaxName));
					TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_CATALOG, 
						DBPROPSET_DBINIT, (wszText[0]!=L'\0')? VT_BSTR: VT_EMPTY, (void*)wszText), S_OK);
					TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_FILENAME, 
						DBPROPSET_SQLOLEDB_SPECIFIC, VT_EMPTY, (void*)NULL), S_OK);
				}
			}		
			break;

		case g_nAdvanced:
		case g_nAll:
			break;

		default:
			TESTC(FALSE);
	}

CLEANUP:
	TRETURN
} //CDSL_Dialog::Notify_KillActivePage




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::GotoPage
//		select a certain tab in DSL page
//		returns TRUE on success or FALSE on failure
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GotoPage(ULONG nPage)
{
	TBEGIN

	CHAR szWindowName[cMaxName]	= "";
	HWND hWnd = NULL, hIDYES=NULL;

	BOOL	fDisableProvider = (DSL_CM_INTERFACE == m_CreationMethod) && m_dwPromptOptions & DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION;
	ULONG	ulCrtPage = GetCurrentPage();

	TESTC(nPage < 4);

	// check whether we already are in the desired dialog
	if (ulCrtPage != nPage)
	{
		if (fDisableProvider)
		{
		// only 3 pages are displayed (provider page is disabled
			ASSERT(nPage>0)
		}

		// update state based on the current page
		COMPARE(Notify_KillActivePage(&ulCrtPage), TRUE);

		// select the page
//		TESTC(PropSheet_SetCurSel(m_hWnd, 0, fDisableProvider? nPage-1: nPage));
		::PostMessage(m_hWnd, PSM_SETCURSEL, (LPARAM)(fDisableProvider? nPage-1: nPage), 0);
		Sleep(200);

		// do not let unavailable providers hang up the test
		hWnd = GetForegroundWindow();

		// check its caption
		GetWindowTextA(hWnd, szWindowName, cMaxName);
		if (0 == strcmp(szWindowName, g_szIDS_TITLE_DATA_LINK))
		{
			PrintTextOfWarningWindow(hWnd);
			odtLog << L" for provider: " << m_wszProviderDescription << "\n";
	
			hIDYES = GetDlgItem(hWnd, IDOK);
			if (!hIDYES)
				hIDYES = GetDlgItem(hWnd, IDCANCEL);
			COMPARE(NULL != hIDYES, TRUE);

			// close this window
			SendMessage(hIDYES, BM_CLICK, 0, 0L);
			TEST_PROVIDER(FALSE);
		}
	}

	TESTC(IsCurrentPage(nPage));
	CheckActivePage(&nPage);

CLEANUP:
	TRETURN
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
	return GotoPage(g_nConnection);
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

	g_nTabs++;
	Ident();
	odtLog << "<CHECK_FILTERS>\n";

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
				(WCHAR*)(*s_pSourcesSet)[rgIdxProv[cIdxEnum]]))
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
				(WCHAR*)(*s_pSourcesSet)[rgIdxProv[cIdxEnum]]))
				break;
		}
		// check that the item was found in the provider list
		TESTC(cIdxEnum<cIdxProv);
	}

	fRes = TRUE;

CLEANUP:
	Ident();
	odtLog << "</CHECK_FILTERS>\n";
	g_nTabs--;


	SAFE_FREE(rgIdxProv);
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
	HWND	hWnd;
	ULONG	nItem;

	TESTC(IsCurrentPage(g_nProvider));

	// get the handle to the list of providers
	hWnd = GetDlgItem(IDC_PROVIDER_LIST);
	// get the item that is selected
	nItem = ListView_GetNextItem(hWnd, -1, LVNI_SELECTED);
	ListView_GetItemTextA(hWnd, nItem, 0, szText, cMaxName);
	ConvertToWCHAR(szText, m_wszProviderDescription, cMaxName);
	
	//retrieve the provider from the root sources rowset
	m_clsidProvider = (CLSID)(*s_pSourcesSet)[m_wszProviderDescription];

CLEANUP:
	TRETURN
} //CDSL_Dialog::GetProvider




//-------------------------------------------------------------------------
//
// Get the list of provider descriptions from the provider tab
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GetListOfProviders()
{
	TBEGIN
	HWND	hProviderList;
	ULONG	cItem;
	BOOL	fDisableProvider = m_dwPromptOptions & DBPROMPTOPTIONS_DISABLE_PROVIDER_SELECTION;
	char	szText[cMaxName] = "";
	ULONG	ulPage = GetCurrentPage();

	if (m_cProviderList)
		FreeProviderList();

	ASSERT(!fDisableProvider);

	TESTC(GotoProviderPage());
	hProviderList = GetDlgItem(IDC_PROVIDER_LIST);
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

CLEANUP:
	GotoPage(ulPage);
	TRETURN
} //CDSL_Dialog::GetListOfProviders




//-------------------------------------------------------------------------
//
// Get the list of properties descriptions from the summary tab
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GetListOfProperties(ULONG *pcProperties, WCHAR ***prgProperties)
{
	TBEGIN
	HWND	hPropertiesList;
	ULONG	cItem;
	char	szText[cMaxName] = "";
	ULONG	ulPage = GetCurrentPage();

	if (m_cProviderList)
		FreeProviderList();

	TESTC(NULL != pcProperties);
	TESTC(NULL != prgProperties);

	TESTC(GotoAllPage());
	hPropertiesList = GetDlgItem(IDC_ALL_PROPERTIES);
	TESTC(NULL != hPropertiesList);
	
	*pcProperties	= ListView_GetItemCount(hPropertiesList);
	SAFE_ALLOC(*prgProperties, WCHAR*, *pcProperties);

	for (cItem=0; cItem<*pcProperties; cItem++)
	{
		szText[0] = '\0';
		// get the provider description (Ansi or unicode)
		ListView_GetItemTextA(hPropertiesList, cItem, 0, szText, cMaxName);
		(*prgProperties)[cItem] = ConvertToWCHAR(szText);
	}

CLEANUP:
	GotoPage(ulPage);
	TRETURN
} //CDSL_Dialog::GetListOfProperties




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
//		Get the init mode from a bitfield
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GetInitMode(HWND hCtrlWnd, LONG *plInitMode)
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
	LONG		lMode = 0;
	
	TESTC(NULL != plInitMode);

	g_nTabs++;
	Ident();
	odtLog << "<GET_InitMode>\n";

	for (iItem=0; iItem < NUMELEM(rgValues); iItem++)
	{
		LVFINDINFOA		lvFindInfo = {LVFI_STRING, rgValues[iItem].szModeName, 0, NULL, 0};
		iPos = (ULONG)SendMessage(hCtrlWnd, LVM_FINDITEMA, -1, (LPARAM)&lvFindInfo);

		if (ListView_GetCheckState(hCtrlWnd, iPos))
		{
			// a bit is set in the mask that makes up the value
			lMode |= rgValues[iItem].dbModeVal;
		}
	}

	*plInitMode = lMode;

CLEANUP:
	Ident();
	odtLog << "</GET_InitMode>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::GetInitMode




//-------------------------------------------------------------------------
//	CDSL_Dialog::GetInitMode
//		Get the init mode
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GetInitMode(LONG *plInitMode)
{
	TBEGIN
	LONG	lInitMode	= 0;
	ULONG	i, cItem;
	char	szText[cMaxName] = "";
	char	*pszMode = NULL;
	HWND	hWnd;
	
	TESTC(NULL != plInitMode);
	TESTC(IsCurrentPage(g_nAll) || IsCurrentPage(g_nAdvanced));

	if (IsCurrentPage(g_nAdvanced))
	{
		hWnd = GetDlgItem(IDC_DBPROP_INIT_MODE);
		TESTC(GetInitMode(hWnd, plInitMode));
		TRETURN;
	}

	// get the handle of the list view control
	hWnd = GetDlgItem(IDC_ALL_PROPERTIES);
	
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

	TESTC(GetInitMode(szText, plInitMode));

CLEANUP:
	TRETURN
} //CDSL_Dialog::GetInitMode




//-------------------------------------------------------------------------
//	CDSL_Dialog::GetInitMode
//		Get the init mode
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::GetInitMode(CHAR *szValue, LONG *plInitMode)
{
	TBEGIN
	CHAR	*pszMode;
	LONG	lInitMode = 0;

	pszMode = strtok(szValue, "|");
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

CLEANUP:
	TRETURN
} //DSL_Dialog::GetInitMode




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetInitDataSource
//		Set text in Data Source field
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetInitDataSource(LPCWSTR wszDataSource)
{
	TBEGIN
	ASSERT(wcslen(wszDataSource) < cMaxName);

	TESTC_PROVIDER(!(CUSTOM_CONN & (*s_pSourcesSet)[m_clsidProvider].m_CustomUI));

	g_nTabs++;
	Ident();
	odtLog << "<SET_InitDataSource value = \"" << wszDataSource << "\">\n";

	TESTC(IsControlEnabled(IDC_DBPROP_INIT_DATASOURCE));

	TESTC(SetTextToCtrl(IDC_DBPROP_INIT_DATASOURCE, wszDataSource));

	// set variable to value needed (for later comparison)
	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_DATASOURCE, 
		DBPROPSET_DBINIT, VT_BSTR, (void*)wszDataSource), S_OK);

CLEANUP:
	Ident();
	odtLog << "</SET_InitDataSource>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetInitDataSource




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetInitMode
//		Set init mode in the Advanced Page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetInitMode(LONG lMode)
{
	TBEGIN
	HWND		hCtrlWnd;
	
	g_nTabs++;
	Ident();
	odtLog << "<SET_InitMode value = " << lMode << ">\n";

	TESTC(IsCurrentPage(g_nAdvanced));

	TESTC(IsControlEnabled(IDC_DBPROP_INIT_MODE));
	hCtrlWnd = GetDlgItem(IDC_DBPROP_INIT_MODE);

	TESTC(SetInitMode(hCtrlWnd, lMode));

	// set the property value
	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_MODE, 
		DBPROPSET_DBINIT, VT_I4, lMode), S_OK);

CLEANUP:
	Ident();
	odtLog << "</SET_InitMode>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetInitMode




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetInitMode
//		Set init mode in the given control window
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetInitMode(HWND hCtrlWnd, LONG lMode)
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
	WCHAR		cSep = L'\0';
	
	g_nTabs++;
	Ident();
	odtLog << "<SET_InitMode value = " << lMode << " = ";

	for (iItem=0; iItem < NUMELEM(rgValues); iItem++)
	{
		LVFINDINFOA		lvFindInfo = {LVFI_STRING, rgValues[iItem].szModeName, 0, NULL, 0};
		iPos = (ULONG)SendMessage(hCtrlWnd, LVM_FINDITEMA, -1, (LPARAM)&lvFindInfo);

		if (lMode & rgValues[iItem].dbModeVal)
		{
			// set the corresponding check box
			ListView_SetCheckState(hCtrlWnd, iPos, TRUE);
			// check that this actually happened
			TESTC(ListView_GetCheckState(hCtrlWnd, iPos));
			odtLog << rgValues[iItem].szModeName << " " << cSep << " ";
			cSep = L'|';
		}
		else
		{
			// set the corresponding check box
			ListView_SetCheckState(hCtrlWnd, iPos, FALSE);
			// check that this actually happened
			TESTC(!ListView_GetCheckState(hCtrlWnd, iPos));
		}
	}

	odtLog << "\n";

CLEANUP:
	Ident();
	odtLog << "</SET_InitMode>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetInitMode




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetImpersonationLevel
//		Set init mode in the SetImpersonationLevel
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetImpersonationLevel(LONG lImpersonationLevel)
{
	TBEGIN
	LONG_PTR	lItem;
	LONG_PTR	lISelItem;
	HWND		hCtrlWnd;
	WCHAR		wszImpersonationLevel[cMaxName];
	CHAR		szImpersonationLevel[cMaxName];
	const ULONG	cNoOfItems = 4;
	ULONG		ulNoOfItems;
	WCHAR		sep[4]=L"";

	g_nTabs++;
	Ident();
	odtLog << "<SET_ImpersonationLevel value = ";

	TESTC(IsCurrentPage(g_nAdvanced));

	TESTC(IsControlEnabled(IDC_DBPROP_INIT_IMPERSONATION_LEVEL));
	hCtrlWnd = GetDlgItem(IDC_DBPROP_INIT_IMPERSONATION_LEVEL);
	
	ulNoOfItems = (ULONG)SendMessage(hCtrlWnd, CB_GETCOUNT, 0, 0L);
	TESTC(cNoOfItems == ulNoOfItems);

	switch (lImpersonationLevel)
	{
		case DB_IMP_LEVEL_ANONYMOUS:
			wcscpy(wszImpersonationLevel, L"Anonymous");
			strcpy(szImpersonationLevel, "Anonymous");
			odtLog << sep << "Anonymous";
			wcscpy(sep, L" | ");
			break;

		case DB_IMP_LEVEL_IDENTIFY:
			wcscpy(wszImpersonationLevel, L"Identify");
			strcpy(szImpersonationLevel, "Identify");
			odtLog << sep << "Anonymous";
			wcscpy(sep, L" | ");
			break;

		case DB_IMP_LEVEL_IMPERSONATE:
			wcscpy(wszImpersonationLevel, L"Impersonate");
			strcpy(szImpersonationLevel, "Impersonate");
			odtLog << sep << "Identify";
			wcscpy(sep, L" | ");
			break;

		case DB_IMP_LEVEL_DELEGATE:
			wcscpy(wszImpersonationLevel, L"Delegate");
			strcpy(szImpersonationLevel, "Delegate");
			odtLog << sep << "Delegate";
			wcscpy(sep, L" | ");
			break;

		default:
			ASSERT(FALSE);
	}
 
	odtLog << ">\n";

	SendMessage(hCtrlWnd, CB_SHOWDROPDOWN, TRUE, 0L);
	lItem = SendMessage(hCtrlWnd, CB_FINDSTRINGEXACT, -1, (LPARAM)wszImpersonationLevel);
	lItem = SendMessageA(hCtrlWnd, CB_FINDSTRINGEXACT, -1, (LPARAM)szImpersonationLevel);
	TESTC(CB_ERR != lItem);

	TESTC(CB_ERR != SendMessage(hCtrlWnd, CB_SETCURSEL, lItem, 0L));
	lISelItem = SendMessage(hCtrlWnd, CB_GETCURSEL, 0, 0L);
	TESTC(lISelItem == lItem);

	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_IMPERSONATION_LEVEL, DBPROPSET_DBINIT, VT_I4, lImpersonationLevel), S_OK);
	Sleep(100);

CLEANUP:
	Ident();
	odtLog << "</SET_ImpersonationLevel>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetImpersonationLevel




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetProtectionLevel
//		Set init mode in the SetImpersonationLevel
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetProtectionLevel(LONG lProtectionLevel)
{
	TBEGIN
	LONG_PTR	lItem;
	LONG_PTR	lISelItem;
	HWND		hCtrlWnd;
	WCHAR		wszProtectionLevel[cMaxName];
	CHAR		szProtectionLevel[cMaxName];
	const ULONG	cNoOfItems = 6;
	ULONG		ulNoOfItems;

	g_nTabs++;
	Ident();
	odtLog << "<SET_ProtectionLevel value = " << lProtectionLevel << ">\n";

	TESTC(IsCurrentPage(g_nAdvanced));

	TESTC(IsControlEnabled(IDC_DBPROP_INIT_PROTECTION_LEVEL));
	hCtrlWnd = GetDlgItem(IDC_DBPROP_INIT_PROTECTION_LEVEL);
	
	ulNoOfItems = (ULONG)SendMessage(hCtrlWnd, CB_GETCOUNT, 0, 0L);
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
	lItem = SendMessage(hCtrlWnd, CB_FINDSTRINGEXACT, -1, (LPARAM)wszProtectionLevel);
	lItem = SendMessageA(hCtrlWnd, CB_FINDSTRINGEXACT, -1, (LPARAM)szProtectionLevel);
	TESTC(CB_ERR != lItem);

	TESTC(CB_ERR != SendMessage(hCtrlWnd, CB_SETCURSEL, lItem, 0L));
	lISelItem = SendMessage(hCtrlWnd, CB_GETCURSEL, 0, 0L);
	TESTC(lISelItem == lItem);
	
	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_PROTECTION_LEVEL, DBPROPSET_DBINIT, VT_I4, lProtectionLevel), S_OK);

	Sleep(100);

CLEANUP:
	Ident();
	odtLog << "</SET_ProtectionLevel>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetProtectionLevel




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetUserID
//		Set UserID name
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetUserID(LPCWSTR wszUserID)
{
	TBEGIN

	g_nTabs++;
	Ident();
	odtLog << "<SET_UserID value = \"" << wszUserID << "\">\n";

	ASSERT(wcslen(wszUserID) < cMaxName);

	if (!(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SettableProperty(DBPROP_AUTH_USERID, DBPROPSET_DBINIT))
		return TRUE;

	TESTC(IsControlEnabled(IDC_DBPROP_AUTH_USERID));
	TESTC(SetTextToCtrl(IDC_DBPROP_AUTH_USERID, wszUserID));
	
	// set variable to value needed (for later comparison)
	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_AUTH_USERID, 
		DBPROPSET_DBINIT, VT_BSTR, (void*)wszUserID), S_OK);

CLEANUP:
	Ident();
	odtLog << "</SET_UserID>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetUserID




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetPassword
//		Set Password text
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetPassword(LPCWSTR wszPassword)
{
	TBEGIN

	ASSERT(wcslen(wszPassword) < cMaxName);

	if (!(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SettableProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT))
		return TRUE;

	g_nTabs++;
	Ident();
	odtLog << "<SET_PASSWORD value = \"" << wszPassword << "\">\n";

	TESTC(IsControlEnabled(IDC_DBPROP_AUTH_PASSWORD));

	TESTC(SetTextToCtrl(IDC_DBPROP_AUTH_PASSWORD, wszPassword));

	m_fBlankPassword = IsControlEnabled(IDC_BlankPassword) && (BST_CHECKED == IsDlgButtonChecked(GetHWND(), IDC_BlankPassword));

	// set variable to value needed (for later comparison)
	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_AUTH_PASSWORD, 
		DBPROPSET_DBINIT, VT_BSTR, (void*)wszPassword), S_OK);
	
CLEANUP:
	Ident();
	odtLog << "</SET_PASSWORD>\n";
	g_nTabs--;
	TRETURN;
} //CDSL_Dialog::SetPassword




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetServerName
//		Set server name
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetServerName(LPCWSTR wszServerName)
{
	TBEGIN

	TESTC(	CLSID_SQLOLEDB == m_clsidProvider
		||	CLSID_MSDAORA == m_clsidProvider);
	TESTC(SetInitDataSource(wszServerName));

CLEANUP:
	TRETURN;
} //CDSL_Dialog::SetServerName




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetDatabaseOnServerName
//		Set database
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetDatabaseOnServerName(LPCWSTR wszDatabaseName)
{
	TBEGIN

	g_nTabs++;
	Ident();
	odtLog << "<SET_DatabaseOnServerName value = \"" << wszDatabaseName << "\">\n";
	TESTC(CLSID_SQLOLEDB == m_clsidProvider);
	TESTC(IsControlEnabled(IDC_DatabaseOnServerName));
	TESTC(SetTextToCtrl(IDC_DatabaseOnServerName, wszDatabaseName));

	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_CATALOG, 
		DBPROPSET_DBINIT, VT_BSTR, (void*)wszDatabaseName), S_OK);

CLEANUP:
	Ident();
	odtLog << "</SET_DatabaseOnServerName>\n";
	g_nTabs--;
	TRETURN
} //CDSL_Dialog::SetDatabaseOnServerName




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetDatabaseFileName
//		Set database name
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetDatabaseFileName(LPCWSTR wszDatabaseName)
{
	TBEGIN

	g_nTabs++;
	Ident();
	odtLog << "<SET_DB_FILENAME value = \"" << wszDatabaseName << "\">\n";

	TESTC(CLSID_SQLOLEDB == m_clsidProvider);
	TESTC(IsControlEnabled(IDC_DatabaseFileName));
	TESTC(SetTextToCtrl(IDC_DatabaseFileName, wszDatabaseName));

	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_CATALOG, 
		DBPROPSET_DBINIT, VT_BSTR, (void*)wszDatabaseName), S_OK);

CLEANUP:
	Ident();
	odtLog << "</SET_DB_FILENAME>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetDatabaseFileName




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetInitFileName
//		Set file name 
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetInitFileName(LPCWSTR wszFileName)
{
	TBEGIN

	g_nTabs++;
	Ident();
	odtLog << "<SET_InitFileName value = \"" << wszFileName << "\">\n";

	TESTC(CLSID_SQLOLEDB == m_clsidProvider);
	TESTC(IsControlEnabled(IDC_DBPROP_INIT_FILENAME));
	TESTC(SetTextToCtrl(IDC_DBPROP_INIT_FILENAME, wszFileName));

	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_FILENAME, 
		DBPROPSET_SQLOLEDB_SPECIFIC, VT_BSTR, (void*)wszFileName), S_OK);

CLEANUP:
	Ident();
	odtLog << "</SET_InitFileName>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetInitFileName




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

	if (	CLSID_JOLT40 != m_clsidProvider
		&&	CLSID_JOLT351 != m_clsidProvider)
		return FALSE;

	if (!IsCurrentPage(g_nConnection))
		return FALSE;

	TESTC(PushButton(IDC_Browse));

	TESTC(WaitForForegroundWindow(g_szIDS_Jolt_OFNTitle, &hWnd));
CLEANUP:
	TRETURN
} //CDSL_Dialog::OpenFileBrowser




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetInitFileNameInBrowser (Jolt specific)
//		Choose file in browser 
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetInitFileNameInBrowser(CHAR *szFileName)
{
	TBEGIN
	HWND	hWnd;
	HWND	hFileName;
	CHAR	szInitDataSource[cMaxName]	= "";
	CHAR	szWindowName[cMaxName]		= "";

	g_nTabs++;
	Ident();
	odtLog << "<SET_InitFileNameInBrowser value = \"" << szFileName << "\">\n";

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

	hFileName = GetEdt1(hWnd);
	TESTC(NULL != hFileName);

	// set the text to the edit control and check its value
	SetWindowTextA(hFileName, szFileName);
	Sleep(100);
	GetWindowTextA(hFileName, szInitDataSource, cMaxName);
	TESTC(0 == strcmp(szInitDataSource, szFileName));

CLEANUP:
	Ident();
	odtLog << "</SET_InitFileNameInBrowser>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetInitFileNameInBrowser




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
	TESTC(WaitForForegroundWindow(g_szIDS_Jolt_OFNTitle, &hWnd));

	/*
	hWnd = GetForegroundWindow();

	// check its caption
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDS_Jolt_OFNTitle));
*/
	hFileName = GetEdt1(hWnd);
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
	Sleep(100);

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
		TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_DATASOURCE, 
			DBPROPSET_DBINIT, VT_BSTR, (void*)wszInitDataSource), S_OK);
	}
	else
	{
		DBPROP	*pProp = m_ProvProps.FindProperty(m_clsidProvider, DBPROP_INIT_DATASOURCE, DBPROPSET_DBINIT);

		// the current value should be the previous value
		TESTC(pProp && VT_BSTR == pProp->vValue.vt && 0 == wcscmp(V_BSTR(&pProp->vValue), wszInitDataSource));
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
	CHAR	szWindowName[cMaxName]		= "";
	DBPROP	*pProp						= NULL;

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
	pProp = m_ProvProps.FindProperty(m_clsidProvider, DBPROP_INIT_DATASOURCE, DBPROPSET_DBINIT);
	TESTC(pProp && VT_BSTR == pProp->vValue.vt);
	TESTC(0 == wcscmp(V_BSTR(&pProp->vValue), wszInitDataSource));

CLEANUP:
	TRETURN
} //CDSL_Dialog::FileBrowser_OnCancel




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetInitCatalog (sockeye specific)
//		Set Initial Catalog
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetInitCatalog(LPCWSTR pwszCatalogName)
{
	TBEGIN

	g_nTabs++;
	Ident();
	odtLog << "<SET_InitCatalog value = \"" << pwszCatalogName << "\">\n";

	TESTC(IsControlEnabled(IDC_DBPROP_INIT_CATALOG));
	TESTC(SetTextToCtrl(IDC_DBPROP_INIT_CATALOG, pwszCatalogName));

	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_CATALOG, 
		DBPROPSET_DBINIT, VT_BSTR, (void*)pwszCatalogName), S_OK);

CLEANUP:
	Ident();
	odtLog << "</SET_InitCatalog>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetInitCatalog




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetProviderString (Sockeye specific)
//		Set Provider String
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetProviderString(WCHAR *pwszProviderString)
{
	TBEGIN

	g_nTabs++;
	Ident();
	odtLog << "<SET_ProviderString value = \"" << pwszProviderString << "\">\n";

	TESTC(IsControlEnabled(IDC_DBPROP_INIT_PROVIDERSTRING));
	TESTC(SetTextToCtrl(IDC_DBPROP_INIT_PROVIDERSTRING, pwszProviderString));

	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_PROVIDERSTRING, 
		DBPROPSET_DBINIT, VT_BSTR, (void*)pwszProviderString), S_OK);

CLEANUP:
	Ident();
	odtLog << "</SET_ProviderString>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetProviderString



//------------------------------------------------------------------------
// CDSL_Dialog::SetConnectionMethod (Sockeye specific)
// set the connection method (datasource name or provider string)
//------------------------------------------------------------------------
BOOL CDSL_Dialog::SetConnectionMethod(int nValue)
{
	TBEGIN
	HWND	hConnection	= GetHWND();
	HWND	hWndDSN, hWndDSNless;
	ULONG	status1, status2;

	ASSERT(IDC_Use_DSN == nValue || IDC_Use_DSNless == nValue);

	g_nTabs++;
	Ident();
	odtLog << "<SET_CONN_METHOD value = " 
		<< ((IDC_Use_DSNless == nValue)? "Use DSN": "DSN-less") << ">\n";

	TESTC(IsCurrentPage(g_nConnection));

	// check that the 2 buttons exist and are functional
	hWndDSN	= GetDlgItem(IDC_Use_DSN);
	hWndDSNless	= GetDlgItem(IDC_Use_DSNless);

	// check that they exist
	TESTC(NULL != hWndDSN);
	TESTC(NULL != hWndDSNless);
	
	// check that exactly one of them was selected
	status1 = IsDlgButtonChecked(hConnection, IDC_Use_DSN);
	status2 = IsDlgButtonChecked(hConnection, IDC_Use_DSNless);

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

		TESTC(BST_CHECKED == IsDlgButtonChecked(hConnection, IDC_Use_DSN));
		TESTC(BST_UNCHECKED == IsDlgButtonChecked(hConnection, IDC_Use_DSNless));
	}
	else
	{
		HWND	hWndPassword = GetDlgItem(hConnection, IDC_DBPROP_AUTH_PASSWORD);
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
		TESTC(BST_UNCHECKED == IsDlgButtonChecked(hConnection, IDC_Use_DSN));
		TESTC(BST_CHECKED == IsDlgButtonChecked(hConnection, IDC_Use_DSNless));
	}

CLEANUP:
	Ident();
	odtLog << "</SET_CONN_METHOD>\n";
	g_nTabs--;
	TRETURN
} //CDSL_Dialog::SetConnectionMethod



//-------------------------------------------------------------------------
//	CDSL_Dialog::TestConnection
//		Press the "Test Connection" button in the connection dialog
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::TestConnection(BOOL fVal)
{
	TBEGIN
	BOOL		fActualVal;

	g_nTabs++;
	Ident();
	odtLog << "<TEST_CONN value = " << fVal << ">\n";

	TESTC(TestConnection(&fActualVal));
	if (fVal != fActualVal)
		odtLog << "\nThe result of test connection is different than expected\n";
	TESTC(fVal == fActualVal);

CLEANUP:
	Ident();
	odtLog << "</TEST_CONN>";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::TestConnection



//-------------------------------------------------------------------------
//	CDSL_Dialog::TestConnection
//		Press the "Test Connection" button in the connection dialog
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::TestConnection(BOOL *pfVal)
{
	TBEGIN
	CHAR			szWindowName[cMaxName] = "";
	HWND			hWnd;
	HWND			hIDOK;
	BOOL			fActualVal				= FALSE;
	ULONG			nIter					= 100;
	ULONG			ulPage					= GetCurrentPage();
	IDBProperties	*pIDBProperties			= NULL;
	IDBInitialize	*pIDBInitialize			= NULL;
	BOOL			fRes;
	CPropSets		*pProvPropSets			= NULL;
	IDataInitialize	*pIDataInit				= NULL;

	g_nTabs++;
	Ident();
	odtLog << "<TEST_CONN>\n";

	TESTC(GotoConnectionPage());
	Sleep(100);

	// find out whether the connection should succeed or not
	if (DSL_CM_INTERFACE != m_CreationMethod || !m_fExistingDSO)
	{
		// see whether it was created from IDataInitialize or not
		pIDataInit = CServiceComp::pIDataInitialize();
		TESTC_(pIDataInit->CreateDBInstance(m_clsidProvider,
		   NULL, CLSCTX_ALL, NULL, IID_IDBProperties, (IUnknown**)&pIDBProperties), S_OK);
		pProvPropSets = m_ProvProps.FindProvCPropSets(m_clsidProvider);
		pIDBProperties->SetProperties(pProvPropSets->cPropertySets(), pProvPropSets->pPropertySets());
		TESTC(VerifyInterface(pIDBProperties, IID_IDBInitialize, 
			DATASOURCE_INTERFACE, (IUnknown**)&pIDBInitialize));
		fRes = SUCCEEDED(pIDBInitialize->Initialize());		
	}

	TESTC(PushButton(IDC_TestConnection));
	for (;nIter; --nIter)
	{
		Sleep(100);

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
	{
		PrintTextOfWarningWindow(hWnd);
		odtLog << L" for provider: " << m_wszProviderDescription << "\n";
		fActualVal = FALSE;
	}
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

	if (DSL_CM_INTERFACE != m_CreationMethod || !m_fExistingDSO)
	{
		TESTC(fRes == fActualVal);
	}

CLEANUP:
	CServiceComp::ReleaseSCInterface(pIDataInit);
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIDBInitialize);
	Ident();
	odtLog << "</TEST_CONN>\n";
	g_nTabs--;

	GotoPage(ulPage);
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
	TBEGIN

	g_nTabs++;
	Ident();
	odtLog << "<SET_SavePassword value = " 
		<< ((BST_CHECKED == uVal)? "CHECKED" : "UNCHECKED") << ">\n";

	// enumerate excepted cases
	if (	!(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SettableProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT) 
		||	m_fExistingDSO  && !(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SettableProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, DBPROPSET_DBINIT))
		return TRUE;

	TESTC(IsControlEnabled(IDC_SAVEPASSWORD));
	TESTC(CheckDlgButton(IDC_SAVEPASSWORD, uVal, 0, NULL, 0, NULL));
	
	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, 
		DBPROPSET_DBINIT, VT_BOOL, ((BST_CHECKED == uVal)? VARIANT_TRUE: VARIANT_FALSE)), S_OK);

CLEANUP:
	Ident();
	odtLog << "</SET_SavePassword>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetSavePassword




//-------------------------------------------------------------------------
//	CDSL_Dialog::FlipSavePassword
//		Change the selection in save password check box
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::FlipSavePassword()
{
	TBEGIN
	BOOL	fVal;

	TESTC(IsControlEnabled(IDC_SAVEPASSWORD));
	
	fVal = (BST_CHECKED == IsDlgButtonChecked(GetHWND(), IDC_SAVEPASSWORD));

	TESTC(SetSavePassword(fVal? BST_UNCHECKED: BST_CHECKED));

CLEANUP:
	TRETURN
} //CDSL_Dialog::FlipSavePassword




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetBlankPassword
//		set blank check box 
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetBlankPassword(UINT uVal)
{
	TBEGIN
	int		rgDisID[]	={IDC_DBPROP_AUTH_PASSWORD};

	if (!(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SettableProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT))
		return TRUE;

	g_nTabs++;
	Ident();
	odtLog << "<SET_PASSWORD value = \"\">\n";

	TESTC(IsControlEnabled(IDC_BlankPassword));

	if (BST_CHECKED == uVal)
	{
		TESTC(CheckDlgButton(IDC_BlankPassword, BST_CHECKED, 0, NULL, NUMELEM(rgDisID), rgDisID));
	}
	else
	{
		TESTC(CheckDlgButton(IDC_BlankPassword, BST_UNCHECKED, NUMELEM(rgDisID), rgDisID, 0, NULL));
	}
	
	m_fBlankPassword = BST_CHECKED == IsDlgButtonChecked(GetHWND(), IDC_BlankPassword);

	// set variable to value needed (for later comparison)
	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_AUTH_PASSWORD, 
		DBPROPSET_DBINIT, VT_BSTR, (void*)L""), S_OK);

CLEANUP:
	Ident();
	odtLog << "</SET_PASSWORD>\n";
	g_nTabs--;
	TRETURN
} //CDSL_Dialog::SetBlankPassword




//-------------------------------------------------------------------------
//	CDSL_Dialog::FlipBlankPassword
//		Change the selection in blank password check box
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::FlipBlankPassword()
{
	TBEGIN
	BOOL	fVal;

	TESTC(IsControlEnabled(IDC_BlankPassword));
	
	fVal = (BST_CHECKED == IsDlgButtonChecked(GetHWND(), IDC_BlankPassword));

	TESTC(SetBlankPassword(fVal? BST_UNCHECKED: BST_CHECKED));

CLEANUP:
	TRETURN
} //CDSL_Dialog::FlipBlankPassword




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetDatabaseMethod
//		set the database selection method
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetDatabaseMethod(int nValue)
{
	TBEGIN
	HWND	hWnd1, hWnd2;
	ULONG	status1, status2;
	HWND	hConnection = GetHWND();

	g_nTabs++;
	Ident();
	odtLog << "<SET_DB_METHOD value = " 
		<< ((IDC_UseDatabaseOnServerName == nValue)? "DatabaseOnServerName": "DatabaseFileName")
		<< ">\n";

	// this method is specific to SQLOLEDB
	TESTC(CLSID_SQLOLEDB == m_clsidProvider);

	ASSERT(	IDC_UseDatabaseOnServerName == nValue 
		||	IDC_UseDatabaseFileName == nValue);

	// check that the 2 buttons exist and are functional
	hWnd1	= GetDlgItem(IDC_UseDatabaseOnServerName);
	hWnd2	= GetDlgItem(IDC_UseDatabaseFileName);

	// check that they exist
	TESTC(NULL != hWnd1);
	TESTC(NULL != hWnd2);
	
	// check that exactly one of them was selected
	status1 = IsDlgButtonChecked(hConnection, IDC_UseDatabaseFileName);
	status2 = IsDlgButtonChecked(hConnection, IDC_UseDatabaseOnServerName);

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

		TESTC(BST_CHECKED == IsDlgButtonChecked(hConnection, IDC_UseDatabaseOnServerName));
		TESTC(BST_UNCHECKED == IsDlgButtonChecked(hConnection, IDC_UseDatabaseFileName));
	}
	else
	{
		int		rgEnID[]	= {IDC_UseDatabaseFileName, IDC_DBPROP_INIT_FILENAME};
		int		rgDisID[]	= {IDC_DatabaseOnServerName};

		// set security method
		TESTC(CheckRadioButton(IDC_UseDatabaseOnServerName, IDC_UseDatabaseFileName,
			IDC_UseDatabaseFileName,
			NUMELEM(rgEnID), rgEnID, NUMELEM(rgDisID), rgDisID));

		TESTC(BST_UNCHECKED == IsDlgButtonChecked(hConnection, IDC_UseDatabaseOnServerName));
		TESTC(BST_CHECKED == IsDlgButtonChecked(hConnection, IDC_UseDatabaseFileName));
	}

CLEANUP:
	Ident();
	odtLog << "</SET_DB_METHOD>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetDatabaseMethod




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetSecurityMethod
//		set the security method
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetSecurityMethod(int nValue)
{
	TBEGIN
	HWND	hWndNT, hWndSTD;
	ULONG	status1, status2;
	HWND	hCrtWnd	= GetHWND();

	ASSERT(IDC_USE_INTEGRATED == nValue || IDC_USE_STANDARD == nValue);

	g_nTabs++;
	Ident();
	odtLog << "<SET_SecurityMethod value = " 
		<< ((IDC_USE_STANDARD == nValue)? "STANDARD" : "INTEGRATED") << ">\n";

	TESTC(IsCurrentPage(g_nConnection));
	// NOTE: we shouldn't have called this method on a provider with a custom connection page
	// because we know nothing about the page's layout
	ASSERT(!(CUSTOM_CONN & (*s_pSourcesSet)[m_clsidProvider].m_CustomUI));

	// check that the 2 buttons exist and are functional
	hWndNT	= GetDlgItem(IDC_USE_INTEGRATED);
	hWndSTD	= GetDlgItem(IDC_USE_STANDARD);

	// check that they exist
	TESTC(NULL != hWndNT);
	TESTC(NULL != hWndSTD);
	
	// check that exactly one of them was selected
	status1 = IsDlgButtonChecked(hCrtWnd, IDC_USE_INTEGRATED);
	status2 = IsDlgButtonChecked(hCrtWnd, IDC_USE_STANDARD);

	TESTC(	(BST_CHECKED == status1 && BST_UNCHECKED == status2)
		||	(BST_UNCHECKED == status1 && BST_CHECKED == status2));

	// set the security method
	if (IDC_USE_INTEGRATED == nValue)
	{
		BOOL		fStandardSupported = FALSE;
		int			rgCtrlID[]={IDC_DBPROP_AUTH_USERID, 
						IDC_DBPROP_AUTH_USERID_LABEL,
						IDC_DBPROP_AUTH_PASSWORD,
						IDC_DBPROP_AUTH_PASSWORD_LABEL,
						IDC_BlankPassword,
						IDC_SAVEPASSWORD, IDC_USE_STANDARD};
		ULONG		cCtrlID = NUMELEM(rgCtrlID) - 1;

		int			rgEnCtrlID[]={IDC_USE_INTEGRATED,
						IDC_USE_STANDARD};
		ULONG		cEnCtrlID = NUMELEM(rgEnCtrlID);

		if (	(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SupportedProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT)
			||	(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SupportedProperty(DBPROP_AUTH_USERID, DBPROPSET_DBINIT)
			)
			fStandardSupported = TRUE;

		if (!fStandardSupported)
		{
			cEnCtrlID--;
			cCtrlID++;
		}

		// set security method
		TESTC(CheckRadioButton(IDC_USE_STANDARD, IDC_USE_INTEGRATED,  
			IDC_USE_INTEGRATED, cEnCtrlID, rgEnCtrlID,
			cCtrlID, rgCtrlID));

		//Sleep(10000);
		TESTC(BST_CHECKED == IsDlgButtonChecked(hCrtWnd, IDC_USE_INTEGRATED));
		TESTC(BST_UNCHECKED == IsDlgButtonChecked(hCrtWnd, IDC_USE_STANDARD));

		TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_AUTH_INTEGRATED, 
			DBPROPSET_DBINIT, VT_BSTR, L"SSPI"), S_OK);
	}
	else
	{
		// standard security services
		HWND	hWndPassword = GetDlgItem(hCrtWnd, IDC_DBPROP_AUTH_PASSWORD);
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
		TESTC(BST_UNCHECKED == IsDlgButtonChecked(hCrtWnd, IDC_USE_INTEGRATED));
		TESTC(BST_CHECKED == IsDlgButtonChecked(hCrtWnd, IDC_USE_STANDARD));

		TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_AUTH_INTEGRATED, 
			DBPROPSET_DBINIT, VT_EMPTY, L""), S_OK);
	}

CLEANUP:
	Ident();
	odtLog << "</SET_SecurityMethod>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetSecurityMethod





//-------------------------------------------------------------------------
//	CDSL_Dialog::BuildRandomValue
//				Creates a random value for this type
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::BuildRandomValue(DBTYPE dbType, WCHAR *pwszValue)
{
	ULONG iPos = 0;

	switch (dbType)
	{
		case VT_I1:
			swprintf(pwszValue, L"%d", -128 + rand() % 256);
			break;

		case VT_I2:
			swprintf(pwszValue, L"%d", -32768 + rand() % 65536);
			break;

		case VT_I4:
			swprintf(pwszValue, L"%ld", -2147483647 -1  + rand() % 4294967296);
			break;

		case VT_I8:
			// working item
			swprintf(pwszValue, L"%ld", -2147483647 -1  + rand() % 4294967296);
			break;

		case VT_UI1:
			swprintf(pwszValue, L"%u", rand() % 256);
			break;

		case VT_UI2:
			swprintf(pwszValue, L"%u", rand() % 65536);
			break;

		case VT_UI4:
			swprintf(pwszValue, L"%lu", rand() % 4294967296);
			break;

		case VT_UI8:
			// working item
			swprintf(pwszValue, L"%lu", rand() % 4294967296);
			break;

		case VT_R4:
			swprintf(pwszValue, L"%f", (float)log((float)rand()));
			break;

		case VT_R8:
			swprintf(pwszValue, L"%f", (double)log((double)rand()));
			break;

		case VT_BSTR:
			memset(pwszValue, 0, sizeof(WCHAR)*cMaxName);
			for (iPos = 0; iPos < 1 + rand() % (cMaxName-1); iPos++)
			{
				if (rand()%2)
					pwszValue[iPos] = L'a' + rand() % (L'z' - L'a');
				else
					pwszValue[iPos] = L'A' + rand() % (L'Z' - L'A');
			}
			break;


		case VT_BOOL:
			swprintf(pwszValue, L"%s", (rand()%2 ? L"False":L"True"));
			break;


		case VT_CY:
			{
				VARIANT			v;

				v.vt		= VT_CY;
				v.cyVal.Hi	= LONG_MIN + rand() % ULONG_MAX;
				v.cyVal.Lo	= LONG_MIN + rand() % ULONG_MAX;

				VariantChangeType(&v, &v, VARIANT_NOVALUEPROP, VT_BSTR);
				wcscpy(pwszValue, V_BSTR(&v));
				VariantClear(&v);
			}
			break;


		case VT_DATE:
			{
				VARIANT	v;

				v.vt = VT_DATE;
				V_DATE(&v) = rand() / (double)3.17;

				VariantChangeType(&v, &v, VARIANT_NOVALUEPROP, VT_BSTR);
				wcscpy(pwszValue, V_BSTR(&v));
				VariantClear(&v);
			}
			break;
/*
DBTYPE_BSTR DBCOLUMNFLAGS_ISLONG = true ntext 
DBTYPE_BSTR DBCOLUMNFLAGS_ISFIXEDLENGTH = true nchar 
DBTYPE_BSTR DBCOLUMNFLAGS_ISFIXEDLENGTH = false nvarchar 
DBTYPE_IDISPATCH   Error 
DBTYPE_ERROR   Error 
DBTYPE_BOOL   bit 
DBTYPE_VARIANT   nvarchar(4000) 
DBTYPE_IUNKNOWN   Error 
DBTYPE_GUID   uniqueidentifier 
DBTYPE_BYTES DBCOLUMNFLAGS_ISLONG = true or Maximum column size > 8,000 bytes image 
DBTYPE_BYTES DBCOLUMNFLAGS_ISROWVER = true, DBCOLUMNFLAGS_ISFIXEDLENGTH = true,
Column size = 8 timestamp 
DBTYPE_BYTES DBCOLUMNFLAGS_ISFIXEDLENGTH = true binary 
DBTYPE_BYTES DBCOLUMNFLAGS_ISFIXEDLENGTH = false varbinary 
DBTYPE_STR DBCOLUMNFLAGS_ISFIXEDLENGTH = true char 
DBTYPE_ STR DBCOLUMNFLAGS_ISFIXEDLENGTH = false varchar 
DBTYPE_STR DBCOLUMNFLAGS_ISLONG = true or Maximum column size > 4,000 characters text 
DBTYPE_WSTR DBCOLUMNFLAGS_ISFIXED nchar 
DBTYPE_WSTR DBCOLUMNFLAGS_ISFIXEDLENGTH = false nvarchar 
DBTYPE_WSTR DBCOLUMNFLAGS_ISLONG = true or Maximum column size > 4,000 characters ntext 
DBTYPE_UDT   Error 
DBTYPE_DATE   datetime 
DBTYPE_DBDATE   Error 
DBTYPE_DBTIME   Error 
DBTYPE_DBTIMESTAMP   datetime 
DBTYPE_ARRAY   Error 
DBTYPE_BYREF   Ignored 
DBTYPE_VECTOR   Error 
DBTYPE_RESERVED 
*/		default:
			TESTC(FALSE);
	}

CLEANUP:
	TRETURN
} //CDSL_Dialog::BuildRandomValue


//-------------------------------------------------------------------------
//	CDSL_Dialog::SetRandValForProp
//		Set a random value for a property in the summary page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetRandValForProp(WCHAR *pwszProperty)
{
	TBEGIN
	CPropInfoSets	*pPropInfoSets;
	DBPROPINFO		*pPropInfo;
	GUID			guidPropSet;

	g_nTabs++;
	Ident();
	odtLog << "<SetRandValForProp name = " << pwszProperty << ">\n";

	// find the CPropInfoSets associated with the current provider
	pPropInfoSets = &(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets;

	// search for a property with the given description
	TESTC(pPropInfoSets->FindProperty(pwszProperty, &pPropInfo, &guidPropSet));
	TESTC(NULL != pPropInfo);

	// delegate the call
	TESTC(SetRandValForProp(pPropInfo, guidPropSet));

CLEANUP:
	Ident();
	odtLog << "</SetRandValForProp>\n";
	g_nTabs--;
	TRETURN
} //CDSL_Dialog::SetRandValForProp




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetRandValForProp
//		Set a random value for a property in the summary page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetRandValForProp(DBPROPID dbPropID, GUID guidPropSet)
{
	TBEGIN
	CPropInfoSets	*pPropInfoSets;
	DBPROPINFO		*pPropInfo;

	// find the CPropInfoSets associated with the current provider
	pPropInfoSets = &(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets;

	// search for a property with the given description
	pPropInfo = pPropInfoSets->FindProperty(dbPropID, guidPropSet);
	TESTC(NULL != pPropInfo);

	// delegate the call
	TESTC(SetRandValForProp(pPropInfo, guidPropSet));

CLEANUP:
	TRETURN
} //CDSL_Dialog::SetRandValForProp




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetRandValForProp
//		Set a random value for a property in the summary page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetRandValForProp(DBPROPINFO *pPropInfo, GUID guidPropSet)
{
	TBEGIN
	WCHAR	pwszValue[cMaxName];

	TESTC(NULL != pPropInfo);

	TESTC(BuildRandomValue(pPropInfo->vtType, pwszValue));
	TESTC(SetProperty(pPropInfo, guidPropSet, pwszValue));

CLEANUP:
	TRETURN;
} //CDSL_Dialog::SetRandValForProp




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetProperties
//		Set a properties through the summary page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetProperties(
	DBORDINAL	cPropSets,
	DBPROPSET	*rgPropSets
)
{
	TBEGIN
	DBORDINAL	cPropSetIndex;
	DBORDINAL	cPropIndex;
	VARIANT		value;
	DBPROP		*pProp;
	DBPROPSET	*pPropSet;

	VariantInit(&value);

	TESTC(0 == cPropSets || NULL != rgPropSets);

	pPropSet = rgPropSets;
	for (cPropSetIndex = 0; cPropSetIndex < cPropSets; cPropSetIndex++, pPropSet++)
	{
		TESTC(	0 == pPropSet->cProperties
			||	NULL != pPropSet->rgProperties);

		pProp = pPropSet->rgProperties;
		for (cPropIndex = 0; cPropIndex < pPropSet->cProperties; cPropIndex++, pProp++)
		{
			if (S_OK == VariantChangeType(&value, &pProp->vValue, VARIANT_NOVALUEPROP,VT_BSTR))
				COMPARE(SetProperty(pProp->dwPropertyID, pPropSet->guidPropertySet, V_BSTR(&value)), TRUE);

			VariantClear(&value);
		}
	}

CLEANUP:
	TRETURN
} //CDSL_Dialog::SetProperties




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetProperty
//		Set a property in the summary page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetProperty(WCHAR *pwszProperty, WCHAR *pwszValue)
{
	TBEGIN
	CPropInfoSets	*pPropInfoSets;
	DBPROPINFO		*pPropInfo;
	GUID			guidPropSet;

	// find the CPropInfoSets associated with the current provider
	pPropInfoSets = &(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets;

	// search for a property with the given description
	TESTC(pPropInfoSets->FindProperty(pwszProperty, &pPropInfo, &guidPropSet));
	TESTC(NULL != pPropInfo);

	// delegate the call
	TESTC(SetProperty(pPropInfo, guidPropSet, pwszValue));

CLEANUP:
	TRETURN
} //CDSL_Dialog::SetProperty




//-------------------------------------------------------------------------
//	CDSL_Dialog::SetProperty
//		Set a property in the summary page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetProperty(DBPROPID dbPropID, GUID guidPropSet, WCHAR *pwszValue)
{
	TBEGIN
	CPropInfoSets	*pPropInfoSets;
	DBPROPINFO		*pPropInfo;

	// find the CPropInfoSets associated with the current provider
	pPropInfoSets = &(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets;

	// search for a property with the given description
	pPropInfo = pPropInfoSets->FindProperty(dbPropID, guidPropSet);
	TESTC(NULL != pPropInfo);

	// delegate the call
	TESTC(SetProperty(pPropInfo, guidPropSet, pwszValue));

CLEANUP:
	TRETURN
} //CDSL_Dialog::SetProperty



enum EDPROP_DLG{
	ED_STR_DLG,
	ED_PSSWD_DLG,
	ED_CL_DLG,
	ED_CB_DLG,
	ED_BF_DLG
};

//-------------------------------------------------------------------------
//	CDSL_Dialog::SetProperty
//		Set a property in the summary page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SetProperty(DBPROPINFO *pPropInfo, GUID guidPropSet, WCHAR *pwszValue)
{
	TBEGIN
	HWND			hWndEditPropVal;
	HWND			hWndList;
	CHAR			*pszProperty	= NULL;
	CHAR			*pszValue		= NULL;
	ULONG			iSel;
	ULONG			i;
	WCHAR			wszCrtValue[cMaxName];
	WCHAR			wszValue[cMaxName];
	CHAR			*pszCrtValue	= NULL;
	EDPROP_DLG		dlgType			= ED_STR_DLG;

	TESTC(NULL != pPropInfo);

	g_nTabs++;
	Ident();
	odtLog << "<SET_Property name = " << pPropInfo->pwszDescription << ", value = \"" << pwszValue << "\">\n";

	TESTC(NULL != (hWndList = GetDlgItem(IDC_ALL_PROPERTIES)));

	// get comparable ANSII strings
	pszProperty = ConvertToMBCS(pPropInfo->pwszDescription);
	TESTC(NULL != pszProperty);
	pszValue = ConvertToMBCS(pwszValue);
	TESTC(NULL != pszValue);

	// find the item that fits description and select it
	{
		LVFINDINFOA		lvFindInfo = {LVFI_STRING, pszProperty, 0, NULL, 0};
		i = (ULONG)SendMessage(hWndList, LVM_FINDITEMA, -1, (LPARAM)&lvFindInfo);
		// select this item
		LV_SetItemState(hWndList, i, 0, LVIS_SELECTED, LVIS_SELECTED);
		iSel = ListView_GetNextItem(hWndList, -1, LVNI_SELECTED);
		TESTC(iSel == i);
	}

	// read the current value (if any)
	LV_GetItemText(hWndList, iSel, 1, wszCrtValue, cMaxName);
	pszCrtValue = ConvertToMBCS(wszCrtValue);

	// press the Edit button
	TESTC(PushButton(IDC_EditValue));
	
	// check that the window popped-up
	// check that a new dialog box has been created with a proper title
	// and get its handle
	// get the foreground window and make sure it has focus
	TESTC(WaitForWindow(g_szIDD_SUMMARY_EDIT, &hWndEditPropVal));

	if (DBPROPSET_DBINIT == guidPropSet)
	{
		switch (pPropInfo->dwPropertyID)
		{
			case DBPROP_INIT_OLEDBSERVICES:
			default :
				{
					CBasicDialog	dialog(FALSE, hWndEditPropVal);
					TESTC(dialog.PushButton(IDCANCEL));
					TESTC(FALSE);
				}
				break;

			case DBPROP_AUTH_INTEGRATED :				
			case DBPROP_AUTH_USERID :					
			case DBPROP_INIT_LOCATION :					
			case DBPROP_INIT_PROVIDERSTRING :			
			case DBPROP_INIT_TIMEOUT :	
			case DBPROP_INIT_GENERALTIMEOUT:				
			case DBPROP_INIT_LCID :						
			case DBPROP_INIT_DATASOURCE:
			case DBPROP_INIT_CATALOG:
				// VT_BSTR, VT_I2, & VT_I4
				//
				dlgType = ED_STR_DLG;
				break;


			case DBPROP_AUTH_PASSWORD :					
				dlgType = ED_PSSWD_DLG;
				break;


			case DBPROP_AUTH_CACHE_AUTHINFO :			
			case DBPROP_AUTH_ENCRYPT_PASSWORD :			
			case DBPROP_AUTH_MASK_PASSWORD :				
			case DBPROP_AUTH_PERSIST_ENCRYPTED :			
			case DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO :
				// VT_BOOL
				//
				dlgType = ED_CL_DLG;
				break;


			case DBPROP_INIT_IMPERSONATION_LEVEL :		
			case DBPROP_INIT_PROTECTION_LEVEL :
				// Special Case
				//
				dlgType = ED_CL_DLG;
				break;


			case DBPROP_INIT_MODE :		
				// Special Case
				//
				dlgType = ED_BF_DLG;
				break;
		}
	}
	else
	{
		if (	DBPROPSET_JETOLEDB_DBINIT == guidPropSet 
			&&	DBPROP_JETOLEDB_DATABASEPASSWORD == pPropInfo->dwPropertyID)
			dlgType = ED_PSSWD_DLG;
		else
		{
			// go based on property type
			dlgType = (DBTYPE_BOOL == pPropInfo->vtType)? ED_CL_DLG: ED_STR_DLG;
		}
	}

	switch (dlgType)
	{
		case ED_STR_DLG:
			{
				CSummaryEditStringDlg	dialog(hWndEditPropVal);
				BOOL					fOK;

				dialog.GetTextFromCtrl(IDC_SUMMARY_EDIT_VALUE, wszValue, cMaxName);
				TESTC(0 == wcscmp(wszValue, wszCrtValue));
				TESTC(dialog.SetTextToCtrl(IDC_SUMMARY_EDIT_VALUE, pwszValue));
				Sleep(100);
				TESTC(dialog.CloseDlg(&fOK));

				// get the new value of the property
				LV_GetItemText(hWndList, iSel, 1, wszValue, cMaxName);
				if (fOK)
				{
					VARIANT	vValue;
					VARIANT	vAsked;

					VariantInit(&vValue);
					VariantInit(&vAsked);

					vValue.vt = VT_BSTR;
					vValue.bstrVal = SysAllocString(pwszValue);

					vAsked.vt = VT_BSTR;
					vAsked.bstrVal = SysAllocString(wszValue);

					if (CHECK(VariantChangeType(&vValue, &vValue, VARIANT_NOVALUEPROP, pPropInfo->vtType), S_OK))
					{
						// set the new value
						CHECK(m_ProvProps.SetProperty(m_clsidProvider, 
								pPropInfo->dwPropertyID, guidPropSet, &vValue), S_OK);
						
						// compare against the asked value
						if (CHECK(VariantChangeType(&vAsked, &vAsked, VARIANT_NOVALUEPROP, pPropInfo->vtType), S_OK))
						{
							COMPARE(CompareVariant(&vValue, &vAsked, TRUE, TRUE), TRUE);
						}
					}
					VariantClear(&vValue);
					VariantClear(&vAsked);
				}
				else
				{	// the value should still be the old value (wszCrtValue)
					TESTC(0 == wcscmp(wszValue, wszCrtValue));
				}
			}
			break;

		case ED_PSSWD_DLG:
			{
				CBasicDialog	dialog(FALSE, hWndEditPropVal);

				TESTC(dialog.SetTextToCtrl(IDC_SUMMARY_EDIT_VALUE, pwszValue));
				Sleep(100);
				TESTC(dialog.PushButton(IDOK));

				m_ProvProps.SetProperty(m_clsidProvider, pPropInfo->dwPropertyID, guidPropSet, 
					pPropInfo->vtType, (void*)pwszValue);
			}
			break;

		case ED_CL_DLG:
			{
				CBasicDialog	dialog(FALSE, hWndEditPropVal);
				HWND			hWndEditList = GetDlgItem(hWndEditPropVal, IDC_SUMMARY_EDIT_VALUE);
				LRESULT			lRes;
				HWND			hWnd;
				DBORDINAL		index;

				dialog.GetTextFromCtrl(IDC_SUMMARY_EDIT_VALUE, wszValue, cMaxName);
				TESTC(0 == wcscmp(wszValue, wszCrtValue));

				lRes = SendMessageA(hWndEditList, CB_SELECTSTRING, -1, (LPARAM)pszValue);
				Sleep(100);

				TESTC(dialog.PushButton(IDOK));

				// check that the upper window is the parent one
				for (index=0; index < 15; index++)
				{
					hWnd = GetForegroundWindow();
					if (hWnd == m_hWnd)
						break;
					Sleep(100);
				}
				TESTC(hWnd == m_hWnd);

				// get the new value of the property
				LV_GetItemText(hWndList, iSel, 1, wszValue, cMaxName);
				if (CB_ERR != lRes)
				{
					TESTC(0 == wcscmp(wszValue, pwszValue));

					if (DBTYPE_BOOL == pPropInfo->vtType)
					{
						VARIANT_BOOL	fValue = (0 == wcscmp(L"True", pwszValue))? VARIANT_TRUE: VARIANT_FALSE;
						
						// get the new value of the property
						m_ProvProps.SetProperty(m_clsidProvider, pPropInfo->dwPropertyID, guidPropSet, 
								VT_BOOL, (ULONG_PTR)fValue);
					}
					else 						
					{
						LONG		lValue;

						TESTC(DBPROPSET_DBINIT == guidPropSet);

						// get the new value of the property
						if (DBPROP_INIT_IMPERSONATION_LEVEL == pPropInfo->dwPropertyID)
						{
							// map the strings to the actual values
							if (0 == wcscmp(L"Anonymous", pwszValue))
								lValue = DB_IMP_LEVEL_ANONYMOUS;
							else if (0 == wcscmp(L"Delegate", pwszValue))
								lValue = DB_IMP_LEVEL_DELEGATE;
							else if (0 == wcscmp(L"Identify", pwszValue))
								lValue = DB_IMP_LEVEL_IDENTIFY;
							else if (0 == wcscmp(L"Impresonate", pwszValue))
								lValue = DB_IMP_LEVEL_IMPERSONATE;
							else
								TESTC(FALSE);
						}
						else if (DBPROP_INIT_PROTECTION_LEVEL == pPropInfo->dwPropertyID)
						{
							// map the strings to the actual values
							if (0 == wcscmp(L"Call", pwszValue))
								lValue = DB_PROT_LEVEL_CALL;
							else if (0 == wcscmp(L"Connect", pwszValue))
								lValue = DB_PROT_LEVEL_CONNECT;
							else if (0 == wcscmp(L"None", pwszValue))
								lValue = DB_PROT_LEVEL_NONE;
							else if (0 == wcscmp(L"Pkt", pwszValue))
								lValue = DB_PROT_LEVEL_PKT;
							else if (0 == wcscmp(L"Pkt Integrity", pwszValue))
								lValue = DB_PROT_LEVEL_PKT_INTEGRITY;
							else if (0 == wcscmp(L"Pkt Privacy", pwszValue))
								lValue = DB_PROT_LEVEL_PKT_PRIVACY;
							else
								TESTC(FALSE);
						}
						else
							TESTC(FALSE);
						m_ProvProps.SetProperty(m_clsidProvider, pPropInfo->dwPropertyID, guidPropSet, 
								VT_BOOL, (ULONG_PTR)lValue);
					}
				}
				else
				{	// the value should still be the old value (wszCrtValue)
					TESTC(0 == wcscmp(wszValue, wszCrtValue));
				}
			}
			break;

		case ED_CB_DLG:
			break;

		case ED_BF_DLG:
			{
				CBasicDialog	dialog(FALSE, hWndEditPropVal);
				HWND			hCtrlWnd;
				LONG			lMode;
				LONG			lMode2;	// the mode as read from the edit property value dlg
				LONG			lModeToSet = *(LONG*)pwszValue &
					(DB_MODE_READWRITE | DB_MODE_SHARE_EXCLUSIVE | DB_MODE_SHARE_DENY_NONE);

				hCtrlWnd = GetDlgItem(hWndEditPropVal, IDC_SUMMARY_EDIT_VALUE);

				TESTC(GetInitMode(pszCrtValue, &lMode));
				TESTC(GetInitMode(hCtrlWnd, &lMode2));
				TESTC(lMode == lMode2);

				// set the value in the bit field control
				TESTC(SetInitMode(hCtrlWnd, lModeToSet));
				Sleep(100);
				TESTC(dialog.PushButton(IDOK));
				Sleep(3000);

				// check that the upper window is the parent one
				TESTC(GetForegroundWindow() == m_hWnd);

				TESTC(GetInitMode(&lMode));
				TESTC(lMode == lModeToSet);

				// get the new value of the property
				TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_MODE, 
					DBPROPSET_DBINIT, VT_I4, lModeToSet), S_OK);
			}
			break;
	}

CLEANUP:
	Ident();
	odtLog << "</SET_Property>\n";
	g_nTabs--;

	SAFE_FREE(pszProperty);
	SAFE_FREE(pszValue);
	SAFE_FREE(pszCrtValue);
	TRETURN
} //CDSL_Dialog::SetProperty




//-------------------------------------------------------------------------
//	CDSL_Dialog::ResetProperty
//		Set a property in the summary page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::ResetProperty(DBPROPINFO *pPropInfo, GUID guidPropSet)
{
	TBEGIN
	HWND			hWndEditPropVal;
	HWND			hWndList;
	HWND			hResetButton;
	HWND			hOK;

	CHAR			*pszProperty	= NULL;
	ULONG			iSel;
	ULONG			i;
	VARIANT			vValue;

	TESTC(NULL != pPropInfo);

	g_nTabs++;
	Ident();
	odtLog << "<RESET_Property name = " << pPropInfo->pwszDescription << ">\n";

	TESTC(NULL != (hWndList = GetDlgItem(IDC_ALL_PROPERTIES)));

	// get comparable ANSII strings
	pszProperty = ConvertToMBCS(pPropInfo->pwszDescription);
	TESTC(NULL != pszProperty);

	// find the item that fits description and select it
	{
		LVFINDINFOA		lvFindInfo = {LVFI_STRING, pszProperty, 0, NULL, 0};
		i = (ULONG)SendMessage(hWndList, LVM_FINDITEMA, -1, (LPARAM)&lvFindInfo);
		// select this item
		LV_SetItemState(hWndList, i, 0, LVIS_SELECTED, LVIS_SELECTED);
		iSel = ListView_GetNextItem(hWndList, -1, LVNI_SELECTED);
		TESTC(iSel == i);
	}

	// press the Edit button
	TESTC(PushButton(IDC_EditValue));
	
	// check that the window popped-up
	// check that a new dialog box has been created with a proper title
	// and get its handle
	// get the foreground window and make sure it has focus
	TESTC(WaitForWindow(g_szIDD_SUMMARY_EDIT, &hWndEditPropVal));

	// press the reset button
	TESTC(NULL != (hResetButton = GetDlgItem(hWndEditPropVal, IDC_ResetValue))); 
	TESTC(PostMessage(hResetButton, BM_CLICK, 0, 0L));

	// set the default value of the property
	VariantInit(&vValue);
	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, 
			pPropInfo->dwPropertyID, guidPropSet, &vValue), S_OK);

	// press the OK button
	TESTC(NULL != (hOK = GetDlgItem(hWndEditPropVal, IDOK))); 
	TESTC(PostMessage(hOK, BM_CLICK, 0, 0L));
	
CLEANUP:
	Ident();
	odtLog << "</SET_Property>\n";
	g_nTabs--;

	SAFE_FREE(pszProperty);
	TRETURN
} //CDSL_Dialog::SetProperty




//-------------------------------------------------------------------------
//	CDSL_Dialog::EditProperty_OK
//		Close the edit property dialog  and return to the summary page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::EditProperty_OK()
{
	TBEGIN
	HWND		hWnd;
	HWND		hOK, hCancel;
	CHAR		szWindowName[cMaxName]		= "";
	DBORDINAL	index;
	BOOL		fErrorOccurred = FALSE;

	g_nTabs++;
	Ident();
	odtLog << "<EditProperty_OK>\n";

	// check that the window popped-up
	// check that a new dialog box has been created with a proper title
	// and get its handle
	// get the foreground window and make sure it has focus
	TESTC(WaitForWindow(g_szIDD_SUMMARY_EDIT, &hWnd));

	// get handles to the Open (IDOK) and Cancel (IDCANCEL) button
	hOK = GetDlgItem(hWnd, IDOK);
	TESTC(NULL != hOK);
	hCancel = GetDlgItem(hWnd, IDCANCEL);
	TESTC(NULL != hCancel);

	// close this window (tentative)
	PostMessage(hOK, BM_CLICK, 0, 0L);
	Sleep(100);

	for (index=0; index < 100; index++)
	{
		hWnd = GetForegroundWindow();

		// check the caption of the new foreground window
		GetWindowTextA(hWnd, szWindowName, cMaxName);

		if (0 == strcmp(szWindowName, g_szIDD_SUMMARY_GENERIC))
			break;

		if (0 == strcmp(szWindowName, g_szIDS_TITLE_DATA_LINK))
		{
			COMPARE(fErrorOccurred, FALSE);
			fErrorOccurred = TRUE;
			// got the error dialog box
			HWND	hOK = GetDlgItem(hWnd, IDCANCEL);

			COMPARE(0 != hOK, TRUE);
			// the file was not found and error is displayed
			// press OK in the error message box (IDCANCEL)
			SendMessage(hOK, BM_CLICK, 0, 0L);
			Sleep(1000);
			// continue by pressing Cancel in the browser window
			SendMessage(hCancel, BM_CLICK, 0, 0L);
		}
		Sleep(100);

	}
	// check that the foreground window is Data Link Properties dialog box
	TESTC(0 == strcmp(szWindowName, g_szIDD_SUMMARY_GENERIC));
	
CLEANUP:
	Ident();
	odtLog << "</EditProperty_OK>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::EditProperty_OK




//-------------------------------------------------------------------------
//	CDSL_Dialog::EditProperty_Cancel
//		Close the edit property dialog  and return to the summary page
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::EditProperty_Cancel()
{
	TBEGIN
	HWND		hWnd;
	HWND		hCancel;
	CHAR		szWindowName[cMaxName]		= "";

	g_nTabs++;
	Ident();
	odtLog << "<EditProperty_Cancel>\n";

	// check that the window popped-up
	// check that a new dialog box has been created with a proper title
	// and get its handle
	// get the foreground window and make sure it has focus
	hWnd = GetForegroundWindow();

	// check its caption
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDD_SUMMARY_EDIT));

	// get handles to the Open (IDOK) and Cancel (IDCANCEL) button
	hCancel = GetDlgItem(hWnd, IDCANCEL);
	TESTC(NULL != hCancel);

	// close this window (tentative)
	PostMessage(hCancel, BM_CLICK, 0, 0L);

	TESTC(WaitForForegroundWindow(g_szIDD_SUMMARY_GENERIC, &hWnd));
/*	Sleep(1000);

	hWnd = GetForegroundWindow();

	// check the caption of the new foreground window
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDD_SUMMARY_GENERIC));
*/	
CLEANUP:
	Ident();
	odtLog << "</EditProperty_Cancel>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::EditProperty_Cancel




//-------------------------------------------------------------------------
//	CDSL_Dialog::SelectProvider
//		Get the index of the specified provider in rgEnumInfo
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SelectProvider(CLSID clsidProvider)
{
	return SelectProvider((WCHAR*)(*s_pSourcesSet)[clsidProvider]);
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

	g_nTabs++;
	Ident();
	odtLog << "<SELECT_PROVIDER value = " << pwszProviderDescription << ">\n";

	// select provider tab
	TESTC(IsCurrentPage(g_nProvider));

	// get the window handle of the provide listview
	TESTC(NULL != (hWndProviderList = GetDlgItem(IDC_PROVIDER_LIST)));

	// get a comparable ANSII string
	pszProviderDescription = ConvertToMBCS(pwszProviderDescription);
	TESTC(NULL != pszProviderDescription);

	// find the item that fits description
	{
		LVFINDINFOA		lvFindInfo = {LVFI_STRING, pszProviderDescription, 0, NULL, 0};
		i = (ULONG)SendMessage(hWndProviderList, LVM_FINDITEMA, -1, (LPARAM)&lvFindInfo);
		// select this item
		LV_SetItemState(hWndProviderList, i, 0, LVIS_SELECTED, LVIS_SELECTED);
		iSel = ListView_GetNextItem(hWndProviderList, -1, LVNI_SELECTED);
		TESTC(iSel == i);
	}

	// look for the CLSID
	wcscpy(m_wszProviderDescription, pwszProviderDescription);
	m_clsidProvider = (CLSID)(*s_pSourcesSet)[pwszProviderDescription];
	// do not set the value of the properties yet; do this just on changing the page

CLEANUP:
	Ident();
	odtLog << "</SELECT_PROVIDER>\n";
	g_nTabs--;

	SAFE_FREE(pszProviderDescription);
	TRETURN
} //CDSL_Dialog::SelectProvider




//-------------------------------------------------------------------------
//	CDSL_Dialog::SelectAnotherProvider
//		Select another provider than the current one from Provider Page
// if the Provider Page doesn't exist, the method fails
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::SelectAnotherProvider(const CLSID **ppExcludedProvList/*=NULL*/)
{
	TBEGIN
	ULONG				ulProvIndx=0;
	ULONG				Count=0;

	TESTC(GetListOfProviders());

	TESTC_PROVIDER(1 < m_cProviderList);
	ulProvIndx = rand() % m_cProviderList;

	// check filter
	for (Count=0; Count<m_cProviderList; Count++,
		ulProvIndx = (ulProvIndx + 1) % m_cProviderList) // prevent ourself from infinite looping
	{
		// if we have chosen the current provider, we'll try again
		if (0 == wcscmp(m_wszProviderDescription, m_rgProviderList[ulProvIndx]))
			ulProvIndx = (ulProvIndx + 1) % m_cProviderList;

		// check list of excluded providers
		if (ppExcludedProvList)
		{
			for(CLSID clsid = (*s_pSourcesSet)[ m_rgProviderList[ulProvIndx] ];
				*ppExcludedProvList; ppExcludedProvList++)
				if (clsid == **ppExcludedProvList) 
					goto CONTINUE;
		}

		break;
CONTINUE:;
	}
	TESTC_PROVIDER(Count < m_cProviderList);

	// now select the new provider
	TESTC(SelectProvider(m_rgProviderList[ulProvIndx]));

CLEANUP:
	TRETURN
} //CDSL_Dialog::SelectAnotherProvider



/*
//-------------------------------------------------------------------------
//	CDSL_Dialog::CacheAllProperties
//		Get all the properties from the summary (ALL) tab
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::CacheAllProperties()
{
	TBEGIN
	HWND	hWnd;
	ULONG	i, cItem;
	CHAR	szText[cMaxName];
	int		iSubItem;
	ULONG	ulPage = GetCurrentPage();

	// goto the summary tab
	GotoAllPage();
	hWnd = GetDlgItem(GetHWND(), IDC_ALL_PROPERTIES);
	
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
	
CLEANUP:
	GotoPage(ulPage);
	TRETURN
} //CDSL_Dialog::CacheAllProperties
*/



//-------------------------------------------------------------------------
//	CDSL_Dialog::CheckError_OnEditing_PersistSecurityInfo
//		Check that trrying to edit the prop in the All Page fails
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::CheckError_OnEditing_PersistSecurityInfo()
{
	TBEGIN
	HWND			hWndProp = GetDlgItem(IDC_ALL_PROPERTIES);
	HWND			hWnd;
	HWND			hOK;
	CHAR			szWindowName[cMaxName]	= "";
	IDBInitialize	*pIDBInitialize = NULL;
	ULONG			nItem;
	LVFINDINFOA		lvFindInfo = {LVFI_STRING, "Persist Security Info", 0, NULL, 0};

	// get the item that is selected
	nItem	= (ULONG)SendMessage(hWndProp, LVM_FINDITEMA, -1, (LPARAM)&lvFindInfo);
	ListView_GetItemTextA(hWndProp, nItem, 0, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, "Persist Security Info"));
	LV_SetItemState(hWndProp, nItem, 0, LVIS_SELECTED, LVIS_SELECTED);

	Sleep(200);
	TESTC(PushButton(IDC_EditValue));

	// check that a new dialog box has been created with a proper title
	// and get its handle
	// get the foreground window and make sure it has focus
	TESTC(WaitForForegroundWindow(g_szIDS_TITLE_DATA_LINK, &hWnd));
	/*
	Sleep(2000);
	hWnd	= GetForegroundWindow();

	// check its caption (should be a warning)
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDS_TITLE_DATA_LINK));
*/
	// checked that the control exists
	hOK = GetDlgItem(hWnd, IDCANCEL);
	TESTC(NULL != hOK);

	// close this window
	SendMessage(hOK, BM_CLICK, 0, 0L);

CLEANUP:
	TRETURN
} //CDSL_Dialog::CheckError_OnEditing_PersistSecurityInfo




//-------------------------------------------------------------------------
//	CDSL_Dialog::CheckActiveConnectionPage
//		Check all the properties from the summary (ALL) tab
//		Whatever appears in summary must fit with what you have set
//		It is assumed that CacheAllProperties was called before
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::CheckActiveConnectionPage()
{
	TBEGIN
	DBPROP	*pProp;
	DBPROP	*pPassword;

	g_nTabs++;
	Ident();
	odtLog << "<CHECK_ACTIVE_PAGE value = ConnectionPage >\n";

	// make sure there is data about the provider
	TESTC(-1 != m_ProvProps.GetProviderIndex(m_clsidProvider));
			
	if (	CLSID_SQLOLEDB == m_clsidProvider
		||	CLSID_MSDASQL == m_clsidProvider)
	{
		HWND	hWndInitDataSource = GetDlgItem(IDC_DBPROP_INIT_DATASOURCE);

		DBPROP	*pProp = m_ProvProps.FindProperty(m_clsidProvider, DBPROP_INIT_DATASOURCE, DBPROPSET_DBINIT);

		// if the server name is set and it corresponds to an existent one, 
		// update it to capital case
		if (pProp && VT_BSTR == pProp->vValue.vt)
		{
			LONG_PTR	lItem;
			CHAR		szInitDataSource[cMaxName];

			// look for the value int the list of available data sources
			// the search is not case sensitive
			ConvertToMBCS(V_BSTR(&pProp->vValue), szInitDataSource, cMaxName);
			lItem = SendMessageA(hWndInitDataSource, CB_FINDSTRINGEXACT, -1, (LPARAM)szInitDataSource);
			if (CB_ERR != lItem)
			{
				// set property to the exact datasource name in the list
				SendMessageA(hWndInitDataSource, CB_GETLBTEXT, (ULONG)lItem, (LPARAM)szInitDataSource);
				ConvertToWCHAR(szInitDataSource, V_BSTR(&pProp->vValue), cMaxName);
			}
		}
	}

	// set DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO to VARIANT_FALSE if 
	// VT_EMPTY or VARIANT_FALSE
	pProp = m_ProvProps.FindProperty(m_clsidProvider, DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, DBPROPSET_DBINIT);
	if (pProp)
	{
		TESTC(VT_BOOL == pProp->vValue.vt || VT_EMPTY == pProp->vValue.vt);
		pPassword = m_ProvProps.FindProperty(m_clsidProvider, DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT);
		// only check the allow save password box when there is a pasword
		if (VT_EMPTY == pProp->vValue.vt || !pPassword || VT_EMPTY == pPassword->vValue.vt)
		{
			pProp->vValue.vt = VT_BOOL;
			V_BOOL(&pProp->vValue)	= VARIANT_FALSE;
		}
	}

	if ((*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SupportedProperty(DBPROP_AUTH_INTEGRATED, DBPROPSET_DBINIT))
	{
		if (	(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SupportedProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT)
			||	(*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SupportedProperty(DBPROP_AUTH_USERID, DBPROPSET_DBINIT)
			)
		// standard is enabled if and only if the password and user id are supported
		{
			TESTC(IsControlEnabled(IDC_USE_STANDARD));
		}
		else
		{
			TESTC(!IsControlEnabled(IDC_USE_STANDARD));
		}

		TESTC(IsControlEnabled(IDC_USE_INTEGRATED));
	}

CLEANUP:
	Ident();
	odtLog << "</CHECK_ACTIVE_PAGE>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::CheckActiveConnectionPage




//-------------------------------------------------------------------------
//	CDSL_Dialog::CheckActiveSummaryPage
//		Check all the properties from the summary (ALL) tab
//		Whatever appears in summary must fit with what you have set
//		It is assumed that CacheAllProperties was called before
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::CheckActiveSummaryPage()
{
	TBEGIN
	HWND		hWnd;
	ULONG		i, cItem;
	CHAR		szText[cMaxName];
	WCHAR		wszDesc[cMaxName];
	WCHAR		wszValue[cMaxName];
	int			iSubItem;
	VARIANT		vValue;

	DBPROP		*pProp;
	DBPROPINFO	*pPropInfo;
	GUID		guidPropertySets;

	g_nTabs++;
	Ident();
	odtLog << "<CHECK_ACTIVE_PAGE value = SummaryPage >\n";

	VariantInit(&vValue);

	// goto the summary tab
	TESTC(IsCurrentPage(g_nAll));
	hWnd = GetDlgItem(IDC_ALL_PROPERTIES);
	
	cItem =  ListView_GetItemCount(hWnd);

	for (i=0; i<cItem; i++)
	{
		// build the property description string
		iSubItem = 0;
		szText[0] = '\0';
		ListView_GetItemTextA(hWnd, i, iSubItem, szText, cMaxName);
		ConvertToWCHAR(szText, wszDesc, cMaxName);

		// build the property value
		iSubItem = 1;
		szText[0] = '\0';
		ListView_GetItemTextA(hWnd, i, iSubItem, szText, cMaxName);
		if (0 == wcscmp(L"Mode", wszDesc))
		{
			LONG	lInitMode;

			TESTC(GetInitMode(&lInitMode));
			if ('\0' != szText[0])
				wsprintf(szText, "%ld", lInitMode);
		}
		ConvertToWCHAR(szText, wszValue, cMaxName);
		VariantClear(&vValue);
		vValue.vt		= VT_BSTR;
		V_BSTR(&vValue)	= SysAllocString(wszValue);

		// retrieve the DBPROPINFO from the description of the property
		FindProperty(wszDesc, &pPropInfo, &guidPropertySets);

		// find the cached property
		pProp = m_ProvProps.FindProperty(m_clsidProvider, pPropInfo->dwPropertyID, guidPropertySets);
		TESTC(NULL != pProp);

		// amd check it
		if (DBPROP_AUTH_PASSWORD != pProp->dwPropertyID || DBPROPSET_DBINIT != guidPropertySets)
		{
			if (VT_EMPTY != pProp->vValue.vt)
			{
				// change the type of the variant
				TESTC_(VariantChangeType(&vValue, &vValue, VARIANT_NOVALUEPROP, pPropInfo->vtType), S_OK);
				TESTC(CompareVariant(&vValue, &pProp->vValue, TRUE));
			}
			else
			{
				TESTC(L'\0' == wszValue[0]);
			}
		}
	}
	
CLEANUP:
	Ident();
	odtLog << "</CHECK_ACTIVE_PAGE>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::CheckActiveSummaryPage




//-------------------------------------------------------------------------
//	CDSL_Dialog::CheckPropertiesOnDataSourceObject
//		Check DSO properties against the cached props
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::CheckPropertiesOnDataSourceObject(IUnknown *pIUnknown)
// this method requires that the interface passed is on a DSO
{
	TBEGIN

	IDBProperties	*pIDBProperties		= NULL;

	ULONG			cPropSet;
	ULONG			cProp;
	ULONG			cGrantedPropSet		= 0;
	DBPROPSET		*rgGrantedPropSet	= NULL;

	CPropSets		*pCachedPropSets	= NULL;

	WCHAR			*pwszInitString		= NULL;
	WCHAR			*pwszPassword		= NULL;

	BOOL			fPersist;

	IDataInitialize	*pIDataInit			= NULL;

	g_nTabs++;
	Ident();
	odtLog << "<CHECK_PROPERTIES_ON_DSO>\n";

	// build a property set based on the cached properties
	TESTC(VerifyInterface(pIUnknown, IID_IDBProperties, 
		DATASOURCE_INTERFACE, (IUnknown**)&pIDBProperties));

	TESTC_(pIDBProperties->GetProperties(0, NULL, 
			&cGrantedPropSet, &rgGrantedPropSet), S_OK);

	// get a pointer to the appropiate CPropSets
	if (m_fDSLCanceled || FAILED(m_hres))
	{
		// the properties stores should be the initial properties
		pCachedPropSets = &m_InitPropSets;
	}
	else
	{
		pCachedPropSets = m_ProvProps.FindProvCPropSets(m_clsidProvider);
	}


	// look for the property
	for (cPropSet=0; cPropSet<cGrantedPropSet; cPropSet++)
	{
		DBPROPSET	*pPropSet = &rgGrantedPropSet[cPropSet];

		for (cProp=0; cProp<pPropSet->cProperties; cProp++)
		{
			DBPROP	&Prop			= pPropSet->rgProperties[cProp];
			DBPROP	*pCachedProp	= pCachedPropSets->FindProperty(Prop.dwPropertyID, pPropSet->guidPropertySet);

			if (NULL != pCachedProp)
			{
				// compare the values
				if (DBPROP_AUTH_PASSWORD != Prop.dwPropertyID || DBPROPSET_DBINIT != pPropSet->guidPropertySet)
				{
					if (!COMPARE(	VT_EMPTY == pCachedProp->vValue.vt 
								||	Prop.vValue.vt == pCachedProp->vValue.vt, TRUE))
					{
						Ident();
						odtLog << "<PROP_ERROR name = " << GetPropertyName(Prop.dwPropertyID, pPropSet->guidPropertySet)
							<< " expected_type = " << pCachedProp->vValue.vt << " actual_type = " << Prop.vValue.vt
							<< "> </PROP_ERROR>\n";
						continue;
					}

					if (	VT_EMPTY != Prop.vValue.vt 
						&&	VT_EMPTY != pCachedProp->vValue.vt
						&& !CompareVariant(&Prop.vValue, &pCachedProp->vValue, TRUE))
					{
						COMPARE(FALSE, TRUE);
						WCHAR	wszExpectedVal[cMaxName];
						WCHAR	wszActualVal[cMaxName];
						g_nTabs++;
						Ident();
						CHECK(VariantToString(&pCachedProp->vValue, wszExpectedVal, cMaxName), S_OK);
						CHECK(VariantToString(&Prop.vValue, wszActualVal, cMaxName), S_OK);
						odtLog << "<PROP_ERROR name = " << GetPropertyName(Prop.dwPropertyID, pPropSet->guidPropertySet)
							<< " expected_value = " << wszExpectedVal << " actual_value = " << wszActualVal
							<< "> </PROP_ERROR>\n";
						g_nTabs--;
					}
				}
				else
				{
					VARIANT		vPersistSI;

					VariantInit(&vPersistSI);

					// check the password

					// get the init string
					pIDataInit = CServiceComp::pIDataInitialize();
					TESTC(NULL != pIDataInit);
					if (::GetProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, DBPROPSET_DBINIT, pIUnknown, &vPersistSI))
						fPersist = VT_BOOL == vPersistSI.vt && VARIANT_TRUE == V_BOOL(&vPersistSI) || VT_EMPTY == vPersistSI.vt;
					else
						fPersist = TRUE;

					TESTC_(pIDataInit->GetInitializationString(pIUnknown, TRUE, &pwszInitString), S_OK);
					if (fPersist)
					{
						// find the password in the init string
						GetModInfo()->GetStringKeywordValue(pwszInitString, L"Password", &pwszPassword);
						// compared against the cached value
						if ((VT_BSTR == pCachedProp->vValue.vt) && (L'\0' != pCachedProp->vValue.bstrVal[0]))
						{
							TESTC(NULL != pwszPassword);
							TESTC(0 == wcscmp(pwszPassword, V_BSTR(&pCachedProp->vValue)));
						}
						else
						{
							TESTC(VT_EMPTY == pCachedProp->vValue.vt
								|| (VT_BSTR == pCachedProp->vValue.vt) && (L'\0' == pCachedProp->vValue.bstrVal[0]));
							TESTC(	(pwszPassword == NULL && pCachedProp->vValue.vt == VT_EMPTY) ||
								(pwszPassword != NULL && pwszPassword[0] == L'\0' && 
								 pCachedProp->vValue.vt == VT_BSTR));
						}
					}
					else
					{
						// make sure password is not in the init string
						TESTC(!GetModInfo()->GetStringKeywordValue(pwszInitString, L"Password", &pwszPassword));
						TESTC(NULL == pwszPassword);
					}

					// now try to exclude password from init string 
					SAFE_FREE(pwszInitString);
					SAFE_FREE(pwszPassword);
					TESTC_(pIDataInit->GetInitializationString(pIUnknown, FALSE, &pwszInitString), S_OK);
					TESTC(!GetModInfo()->GetStringKeywordValue(pwszInitString, L"Password", &pwszPassword));
					TESTC(NULL == pwszPassword);
				}
			}
			else
			{
				odtLog << "Could not find property " 
					<< _GetPropertyName(Prop.dwPropertyID, pPropSet->guidPropertySet)
					<< " in "
					<< _GetPropSetName(pPropSet->guidPropertySet)
					<< " property group "
					<< " for " << m_wszProviderDescription
					<< "\n";
			}
		}
	}

CLEANUP:
	Ident();
	odtLog << "</CHECK_PROPERTIES_ON_DSO>\n";
	g_nTabs--;

	CServiceComp::ReleaseSCInterface(pIDataInit);
	SAFE_FREE(pwszInitString);
	SAFE_FREE(pwszPassword);
	SAFE_RELEASE(pIDBProperties);
	FreeProperties(&cGrantedPropSet, &rgGrantedPropSet);
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
BOOL CDSL_Dialog::KillThread(int nButton/* = PSBTN_OK*/, DWORD dwMilliseconds/* = 2000*/)
{
	TBEGIN
	DWORD			dwRes;
	HWND			hWnd;
	HWND			hIDYES;
	CHAR			szWindowName[cMaxName]	= "";
	IMoniker		*pIMoniker				= NULL;
	IBindCtx		*piBindCtx				= NULL;
	IDBProperties	*pIDBProperties			= NULL;

	SAFE_RELEASE(m_pInitDSO);

	if (0 == m_hThread)
		return TRUE;

	g_nTabs++;
	Ident();
	odtLog << "<KillThread action = " << ((PSBTN_OK == nButton)? "OK" : "CANCEL") << ">\n";

	// send a message to the DSL page so that it could finish its job
	// a zombie DSL could result in AV since ppDataSource is no more available
	// send the message
	if (m_fIsInExecution)
	{
		Activate();
		if (IsCurrentPage(g_nProvider) && -1 == m_ProvProps.GetProviderIndex(m_clsidProvider))
		{
			COMPARE(GetProvider(), TRUE);
			COMPARE(m_ProvProps.AddProviderWithDefPropValues(m_clsidProvider), TRUE);
		}
		PropSheet_PressButton(m_hWnd, nButton);	
		m_fDSLCanceled = PSBTN_CANCEL == nButton;

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
		PrintTextOfWarningWindow(hWnd);
		odtLog << L" for provider: " << m_wszProviderDescription << "\n";
		COMPARE(FAILED(GetExpectedPropSetting()), TRUE);
		//COMPARE(TRUE, FALSE);
		// checked that the control exists
		hIDYES = GetDlgItem(hWnd, IDOK);
		if (!hIDYES)
			hIDYES = GetDlgItem(hWnd, IDCANCEL);
		COMPARE(NULL != hIDYES, TRUE);

		// close this window
		SendMessage(hIDYES, BM_CLICK, 0, 0L);
	}

	dwRes = WaitForSingleObject(m_hThread, dwMilliseconds);
	if (dwRes != WAIT_OBJECT_0)
	{
		// SOME PROBLEMS with closing dialog.
		odtLog << L"\nPROBLEMS WITH CLOSING DIALOG!!!" << "\n";

		PostThreadMessage(m_IDThread, WM_QUIT, 0, 0);
		dwRes = WaitForSingleObject(m_hThread, 3000);

		if (dwRes != WAIT_OBJECT_0)
		{
			odtLog << L"\nTERMINATE THREAD!!!" << "\n";
	
			TerminateThread(m_hThread, TEST_FAIL);
			BOOL b = IsWindowEnabled(m_hParentWnd);
			if (!b)
				EnableWindow(m_hParentWnd, TRUE);
		}
	}


	TESTC(CloseHandle(m_hThread));
	m_hThread = 0;

	if (m_hLibInst)
	{
		FreeLibrary(m_hLibInst);
		Sleep(1000);
	}
	m_hLibInst = NULL;

	// the only expected return value in here is on IDCANCEL
	TESTC(PSBTN_CANCEL != nButton || DSL_CM_INTERFACE != m_CreationMethod || 
		DB_E_CANCELED == m_hres);

	//automatically check the properties
	if (DSL_CM_INTERFACE == m_CreationMethod)
	{
		Ident();
		odtLog << "<IDBPromptInitialize::PromptDataSource retValue = " << GetErrorName(m_hres) << "> </IDBPromptInitialize::PromptDataSource>\n";
		if (m_ppDataSource && *m_ppDataSource && (S_OK == (*m_ppDataSource)->QueryInterface(IID_IDBProperties, (void**)&pIDBProperties)))
			TESTC(CheckPropertiesOnDataSourceObject(pIDBProperties));
	}
	else
	{
		// checking for the udl file 
		TESTC_(CreateFileMoniker(m_wszUDLFileName, &pIMoniker), S_OK);
		TESTC_(CreateBindCtx(0 /*reserved*/, &piBindCtx), S_OK);
		TESTC_(pIMoniker->BindToObject(piBindCtx, NULL, IID_IDBProperties, (LPVOID*)&pIDBProperties), S_OK);
		TESTC(CheckPropertiesOnDataSourceObject(pIDBProperties));
	}

CLEANUP:
	Ident();
	odtLog << "</KillThread>\n";
	g_nTabs--;

	SAFE_RELEASE(m_pIDBPromptInitialize);
	SAFE_RELEASE(pIDBProperties);
	SAFE_RELEASE(pIMoniker);
	SAFE_RELEASE(piBindCtx);
	TRETURN
} //CDSL_Dialog::KillThread




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::IsValidDataSourceType
// check that the datasource type is valid related to the filter
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::IsValidDataSourceType(DBSOURCETYPE wSourceType)
{
	if ((0 == m_cSourceTypeFilter) || !m_rgSourceTypeFilter)
		return (wSourceType != DBSOURCETYPE_ENUMERATOR);
	
	if (wSourceType != DBSOURCETYPE_DATASOURCE_TDP
		&& wSourceType != DBSOURCETYPE_DATASOURCE_MDP)
		return FALSE;
	
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
	TBEGIN
	ULONG	cIdxProv	= 0;
	ULONG	*rgIdxProv	= NULL;
	ULONG	i;

	ASSERT(pcIdxProv && prgIdxProv);
	SAFE_ALLOC(rgIdxProv, ULONG, s_pSourcesSet->Count());
	
	for (i=0; i<s_pSourcesSet->Count(); i++)
	{
		if (	IsValidDataSourceType((DBTYPE)(*s_pSourcesSet)[i])
			&&	IsValidProgID((LPWSTR)(LPCWSTR)(*s_pSourcesSet)[i].m_pwszParseName))
			rgIdxProv[cIdxProv++] = i;
	}
	
	if (0 == cIdxProv)
	{
		SAFE_FREE(rgIdxProv);
	}
	*prgIdxProv = rgIdxProv;
	*pcIdxProv	= cIdxProv;
	
CLEANUP:
	TRETURN
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
	hWnd = GetDlgItem(IDC_DatabaseOnServerName);

	// drop down the list
	SendMessage(hWnd, CB_SHOWDROPDOWN, TRUE, 0L);
	Sleep(3000);
	// if the list is populated, make a selection
	ulSize = (ULONG)SendMessage(hWnd, CB_GETCOUNT, 0, 0L);
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
		TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_CATALOG, 
			DBPROPSET_DBINIT, VT_BSTR, (void*)wszInitCat), S_OK);
	}

CLEANUP:
	TRETURN
} //CDSL_Dialog::Luxor_SelectInitCatalog




//-------------------------------------------------------------------------
//
//	CDSL_Dialog::Luxor_CheckServerNameList
//		Check the list of server names, displayed in the connection page
//		against the enumerator
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::Luxor_CheckServerNameList()
{
	TBEGIN
	ULONG				index;
	HWND				hWnd = GetDlgItem(IDC_DBPROP_INIT_DATASOURCE);
	IParseDisplayName	*pIParseDisplayName = NULL;
	ULONG				cEnumInfo			= 0;
	ENUMINFO			*rgEnumInfo			= NULL;
	CHAR				szServerName[cMaxName];
	ULONG				ulSize;

	TESTC_(CoCreateInstance(CLSID_SQLOLEDB_ENUMERATOR, NULL, CLSCTX_INPROC_SERVER, IID_IParseDisplayName, (void**)&pIParseDisplayName),S_OK);
	TESTC_(GetEnumInfo(pIParseDisplayName, &cEnumInfo, &rgEnumInfo), S_OK);

	// get the index of the last element and compar it against the 
	// size of the array
	// press the refresh button
	SendMessage(hWnd, CB_SHOWDROPDOWN, TRUE, 0L);
	Sleep(3000);

	ulSize = (ULONG)SendMessage(hWnd, CB_GETCOUNT, 0, 0L);
	COMPARE(1 + ulSize == cEnumInfo, TRUE);

	for (index = 0; index < cEnumInfo; index++)
	{
		// find the server in the list
		ConvertToMBCS(rgEnumInfo[index].wszName, szServerName, cMaxName);

		if (!COMPARE(LB_ERR  != SendMessageA(hWnd, LB_FINDSTRINGEXACT, -1, (LPARAM)szServerName), TRUE))
		{
			odtLog << "Could not found " << rgEnumInfo[index].wszName << "\n";
		}
	}

CLEANUP:
	SAFE_RELEASE(pIParseDisplayName);
	SAFE_FREE(rgEnumInfo);
	TRETURN
} //CDSL_Dialog::Luxor_CheckServerNameList


ULONG CDSL_Dialog::Luxor_GetTotalServerCount(clock_t *ctTime)
{
	HWND				hWnd = GetDlgItem(IDC_DBPROP_INIT_DATASOURCE);
	ULONG				ulSize;

	clock_t ctStartTime = clock(), ctTotalTime;
	// press the refresh button
	SendMessage(hWnd, CB_SHOWDROPDOWN, TRUE, 0L);
	ulSize = (ULONG)SendMessage(hWnd, CB_GETCOUNT, 0, 0L);
	ctTotalTime = clock() - ctStartTime;
	return ulSize;
}

//-------------------------------------------------------------------------
//
//	CDSL_Dialog::Sockeye_CheckDSNList
//		Check the list of server names, displayed in the connection page
//		against the enumerator
//-------------------------------------------------------------------------
BOOL CDSL_Dialog::Sockeye_CheckDSNList()
{
	TBEGIN
	ULONG				index;
	HWND				hWnd = GetDlgItem(IDC_DBPROP_INIT_DATASOURCE);
	IParseDisplayName	*pIParseDisplayName = NULL;
	ULONG				cEnumInfo			= 0;
	ENUMINFO			*rgEnumInfo			= NULL;
	CHAR				szDataSourceName[cMaxName];
	ULONG				ulSize;

	TESTC_(CoCreateInstance(CLSID_MSDASQL_ENUMERATOR, NULL, CLSCTX_INPROC_SERVER, IID_IParseDisplayName, (void**)&pIParseDisplayName),S_OK);
	TESTC_(GetEnumInfo(pIParseDisplayName, &cEnumInfo, &rgEnumInfo), S_OK);

	// drop down the list
	SendMessage(hWnd, CB_SHOWDROPDOWN, TRUE, 0L);
	Sleep(3000);

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
	hWnd = GetDlgItem(IDC_ALL_PROPERTIES);

	iSubItem = 1;
	szText[0] = '\0';

	ulItem = (ULONG)SendMessageA(hWnd, LVM_FINDITEM, -1, (LPARAM)&lvfi);
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




BOOL CDSL_Dialog::SetInitTimeout(LONG lTimeout)
{
	TBEGIN
	WCHAR	wszInitTime[cMaxName];

	g_nTabs++;
	Ident();
	odtLog << "<SET_InitTimeout value = " << lTimeout << ">\n";

	swprintf(wszInitTime, L"%u", lTimeout);
	TESTC(SetTextToCtrl(IDC_DBPROP_INIT_TIMEOUT, wszInitTime));

	// set variable to value needed (for later comparison)
	TESTC_(m_ProvProps.SetProperty(m_clsidProvider, DBPROP_INIT_TIMEOUT, 
		DBPROPSET_DBINIT, VT_I4, lTimeout), S_OK);

CLEANUP:
	Ident();
	odtLog << "</SET_InitTimeout>\n";
	g_nTabs--;

	TRETURN
} //CDSL_Dialog::SetInitTimeout




DBPROPINFO *CDSL_Dialog::FindProperty(DBPROPID PropertyID, GUID guidPropertySet)
{
	if (m_fExistingDSO && m_clsidInitDSO == m_clsidProvider)
	{
		return m_InitPropInfoSets.FindProperty(PropertyID, guidPropertySet);
	}
	else
		return (*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.FindProperty(PropertyID, guidPropertySet);
} //CDSL_Dialog::FindProperty



DBPROPINFO *CDSL_Dialog::FindProperty(WCHAR *pwszDesc, GUID guidPropertySet)
{
	if (m_fExistingDSO && m_clsidInitDSO == m_clsidProvider)
	{
		return m_InitPropInfoSets.FindProperty(pwszDesc, guidPropertySet);
	}
	else
		return (*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.FindProperty(pwszDesc, guidPropertySet);
} //CDSL_Dialog::FindProperty





BOOL CDSL_Dialog::FindProperty(WCHAR *pwszDesc, DBPROPINFO **ppPropInfo, GUID *pguidPropertySet)
{
	if (m_fExistingDSO && m_clsidInitDSO == m_clsidProvider)
	{
		return m_InitPropInfoSets.FindProperty(pwszDesc, ppPropInfo, pguidPropertySet);
	}
	else
		return (*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.FindProperty(pwszDesc, ppPropInfo, pguidPropertySet);
} //CDSL_Dialog::FindProperty




BOOL CDSL_Dialog::SettableProperty(DBPROPID PropertyID, GUID guidPropertySet)
{
	if (m_fExistingDSO && m_clsidInitDSO == m_clsidProvider)
	{
		return m_InitPropInfoSets.SettableProperty(PropertyID, guidPropertySet);
	}
	else
		return (*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SettableProperty(PropertyID, guidPropertySet);
} //CDSL_Dialog::SettableProperty




BOOL CDSL_Dialog::SupportedProperty(DBPROPID PropertyID, GUID guidPropertySet)
{
	if (m_fExistingDSO && m_clsidInitDSO == m_clsidProvider)
	{
		return m_InitPropInfoSets.SupportedProperty(PropertyID, guidPropertySet);
	}
	else
		return (*s_pSourcesSet)[m_clsidProvider].m_PropInfoSets.SupportedProperty(PropertyID, guidPropertySet);
} //CDSL_Dialog::SupportedProperty




HRESULT CDSL_Dialog::GetExpectedInitialize()
{
	HRESULT			hr = E_FAIL;
	IDBInitialize	*pIDBInitialize = NULL;
	IDBProperties	*pIDBProperties	= NULL;
	CPropSets		*pProvPropSets	= NULL;

	if (!HasFinished())
		goto CLEANUP;

	TESTC_(CoCreateInstance(m_clsidProvider, NULL, CLSCTX_ALL, 
		IID_IDBInitialize, (LPVOID*)&pIDBInitialize), S_OK);
	TESTC(VerifyInterface(pIDBInitialize, IID_IDBProperties, DATASOURCE_INTERFACE, 
		(IUnknown**)&pIDBProperties));

	pProvPropSets = m_ProvProps.FindProvCPropSets(m_clsidProvider);
	hr = pIDBProperties->SetProperties(pProvPropSets->cPropertySets(), pProvPropSets->pPropertySets());
	TEST3C_(hr, S_OK, DB_S_ERRORSOCCURRED, DB_E_ERRORSOCCURRED);

	hr = pIDBInitialize->Initialize();

CLEANUP:
	SAFE_RELEASE(pIDBInitialize);
	SAFE_RELEASE(pIDBProperties);
	return hr;
} // CDSL_Dialog::GetExpectedInitialize




HRESULT CDSL_Dialog::GetExpectedPropSetting()
{
	HRESULT			hr = E_FAIL;
	IDBProperties	*pIDBProperties	= NULL;
	CPropSets		*pProvPropSets	= NULL;

	TESTC_(CoCreateInstance(m_clsidProvider, NULL, CLSCTX_ALL, 
		IID_IDBProperties, (LPVOID*)&pIDBProperties), S_OK);

	pProvPropSets = m_ProvProps.FindProvCPropSets(m_clsidProvider);
	hr = pIDBProperties->SetProperties(pProvPropSets->cPropertySets(), pProvPropSets->pPropertySets());

CLEANUP:
	SAFE_RELEASE(pIDBProperties);
	return hr;
} // CDSL_Dialog::GetExpectedPropSetting




//-------------------------------------------------------------------------
//
//	CBasicDialog::CreateUDLFile
// Create a UDL file
//-------------------------------------------------------------------------
BOOL CBasicDialog::CreateUDLFile(WCHAR *pwszUDLFileName)
{
	TBEGIN
	CHAR	*pszUDLFileName = ConvertToMBCS(pwszUDLFileName, AreFileApisANSI() ? CP_ACP : CP_OEMCP);

	TESTC(CreateUDLFile(pszUDLFileName));

CLEANUP:
	SAFE_FREE(pszUDLFileName);
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
		if (-1 == fh)
		{
			odtLog << "Error in opening a file: " << strerror(errno) << "\n";
		}
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
		Sleep(100);
	}
	TRETURN
} //CBasicDialog::CreateUDLFile




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
	Sleep(100);
	TESTC(	WaitForForegroundWindow(dwPromptOptions & DBPROMPTOPTIONS_BROWSEONLY? 
				g_szIDS_DSL_TITLE_ORGANIZE: g_szIDS_DSL_TITLE_SELECT, &m_hWnd)
		||	!m_fIsInExecution
	);

	TESTC(!m_fIsInExecution || NULL != m_hWnd);

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




BOOL CDSL_FileDialog::SetFileName(WCHAR *pwszFileName)
{
	TBEGIN
	
	TESTC(SetTextToCtrl(0x480, pwszFileName));

CLEANUP:
	TRETURN
} //CDSL_FileDialog::SetFileName




//-------------------------------------------------------------------------
//	CSummaryEditStringDlg::CancelDlg
//		Close the dialog by pressing the Cancel button
//-------------------------------------------------------------------------
BOOL CSummaryEditStringDlg::CancelDlg()
{
	TBEGIN
	HWND		hWnd;
	HWND		hCancel;
	CHAR		szWindowName[cMaxName]		= "";

	g_nTabs++;
	Ident();
	odtLog << "<SummaryEditStringDlg_Cancel>\n";

	// get handle to Cancel (IDCANCEL) button
	hCancel = GetDlgItem(m_hWnd, IDCANCEL);
	TESTC(NULL != hCancel);

	// close this window (tentative)
	PostMessage(hCancel, BM_CLICK, 0, 0L);
	Sleep(1000);

	hWnd = GetForegroundWindow();

	// check that the caption of the new foreground window
	// is the one of the parent window 
	GetWindowTextA(hWnd, szWindowName, cMaxName);
	TESTC(0 == strcmp(szWindowName, g_szIDS_DSL_TITLE_PROPERTY_PAGE));
	
CLEANUP:
	Ident();
	odtLog << "</SummaryEditStringDlg_Cancel>\n";
	g_nTabs--;

	TRETURN
} //CSummaryEditStringDlg::CancelDlg




//-------------------------------------------------------------------------
//	CSummaryEditStringDlg::CloseDlg
//		Close the dialog by pressing the OK button. If there is an error
//		close with Cancel.
//-------------------------------------------------------------------------
BOOL CSummaryEditStringDlg::CloseDlg(BOOL *pfOK)
{
	TBEGIN
	HWND		hWnd;
	HWND		hOK, hCancel;
	CHAR		szWindowName[cMaxName]		= "";
	DBORDINAL	index;

	g_nTabs++;
	Ident();
	odtLog << "<SummaryEditStringDlg_OK>\n";

	// get handles to the Open (IDOK) and Cancel (IDCANCEL) button
	hOK = GetDlgItem(m_hWnd, IDOK);
	TESTC(NULL != hOK);
	hCancel = GetDlgItem(m_hWnd, IDCANCEL);
	TESTC(NULL != hCancel);

	// close this window (tentative)
	PostMessage(hOK, BM_CLICK, 0, 0L);

	for (index=0; index < g_cWaitForWindow; index++)
	{
		hWnd = GetForegroundWindow();

		// check that the caption of the new foreground window
		// is the one of the parent window
		GetWindowTextA(hWnd, szWindowName, cMaxName);
		if (0 == strcmp(szWindowName, g_szIDS_DSL_TITLE_PROPERTY_PAGE))
		{
			if (pfOK)
				*pfOK = TRUE;
			break;
		}

		if (0 == strcmp(szWindowName, g_szIDS_TITLE_DATA_LINK))
		{
			// an error occurred
			if (pfOK)
				*pfOK = FALSE;

			CBasicDialog	dialog(FALSE, hWnd);

			TESTC(dialog.PushButton(IDCANCEL));

			TESTC(CancelDlg());

			TESTC(WaitForForegroundWindow(g_szIDS_DSL_TITLE_PROPERTY_PAGE, &hWnd));
			break;
		}
		
		Sleep(100);
	}
	
	TESTC(index <= g_cWaitForWindow);

CLEANUP:
	Ident();
	odtLog << "</SummaryEditStringDlg_OK>\n";
	g_nTabs--;

	TRETURN
} //CSummaryEditStringDlg::CloseDlg








int __stdcall GetWindowTextANSI(HWND hWnd, LPWSTR lpString, int nMaxCount)
{
	if (!hWnd || !lpString || 0 == nMaxCount)
		return 0;

	wcscpy(lpString, L"");
	int		nMaxCountA = nMaxCount*sizeof(CHAR);
	LPSTR	lpStringA = NULL;
	int		result;

	SAFE_ALLOC(lpStringA, CHAR, nMaxCountA);
	result = GetWindowTextA(hWnd, lpStringA, nMaxCountA);
	if (0 != result)
		result = (S_OK == ConvertToWCHAR(lpStringA, lpString, nMaxCount))? wcslen(lpString): 0;

CLEANUP:
	SAFE_FREE(lpStringA);
	return result;
} //GetWindowTextANSI


// the independent version of GetWindowText
int __stdcall GetWindowTextWRAP( HWND hWnd, LPWSTR lpString, int nMaxCount)
{
	GetWindowTextI = (IsUnicodeOS()) ? GetWindowTextW : GetWindowTextANSI;

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
	SetWindowTextI = (IsUnicodeOS()) ? SetWindowTextW : SetWindowTextANSI;

	return SetWindowTextI( hWnd, lpString);
} //SetWindowTextWRAP





static	OSVERSIONINFO	*g_posvi		= NULL;
static	BOOL			fIsEdt1Cached	= FALSE;

HWND GetEdt1(HWND hWnd)
{
	static OSVERSIONINFO	s_osvi;
	static HWND				s_hFileName;

	if (fIsEdt1Cached)
		return s_hFileName;

	if (!g_posvi)
	{
		g_posvi = &s_osvi;
		s_osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		GetVersionEx(g_posvi);
	}

	if (5 > s_osvi.dwMajorVersion || VER_PLATFORM_WIN32_NT != s_osvi.dwPlatformId)
		s_hFileName = GetDlgItem(hWnd, edt1);
	else
		// workaround NT5 problem
		s_hFileName = GetDlgItem(hWnd, 0x47C);

	return s_hFileName;
}
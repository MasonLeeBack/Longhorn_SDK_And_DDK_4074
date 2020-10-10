
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

#include "extralib.h"
#include "CPropSet.hpp"
#include "DSL_DB.hpp"

enum PROPCOLS{
	PropDataID = 0,
	RecordName,
	ValidConn, 
	Provider,
	DataSource, 
	IntegratedSecurity,
	UserID, 
	Password, 
	PersistSecurityInfo,
	InitCatalog, 
	InitMode, 
	ExtendedProps,
	InitTimeout, 
	EncryptPassword, 
	MaskPassword,
	PersistEncrypted, 
	CacheAuthInfo, 
	InitAsynch,
	InitBindings, 
	Location, 
	LocaleID, 
	ImpersonationLevel,
	LockOwner, 
	PS1, 
	PS2, 
	PS3, 
	PS4, 
	PS5, 
	PS6, 
	PS7, 
	PS8, 
	PS9, 
	PS10,
	PS11, 
	PS12, 
	PS13, 
	PS14, 
	PS15, 
	PS16, 
	PS17, 
	PS18, 
	PS19, 
	PS20,
};

//class CAction;

CTable	*CPropData::s_pTable	= NULL;




HRESULT CPropData::GetPropData(
	ULONG			ulCol,		// [in] column to be read
	VARIANT_BOOL	**ppbValue	// [out] the value read
)
{
	HRESULT		hr = E_FAIL;

	if (!ppbValue)
		return E_FAIL;

	// Get the column
	DBBINDING	*pBinding = &m_Rowset.m_rgBinding[ulCol];

	// checkings
	if (DBSTATUS_S_OK == STATUS_BINDING(*pBinding, m_Rowset.m_pData))
	{
		SAFE_ALLOC(*ppbValue, VARIANT_BOOL, 1);
		**ppbValue = *(VARIANT_BOOL*)&VALUE_BINDING(*pBinding, m_Rowset.m_pData);
	}
	else if (DBSTATUS_S_ISNULL == STATUS_BINDING(*pBinding, m_Rowset.m_pData))
		*ppbValue = NULL;
	else
		return E_FAIL;

	hr = S_OK;

CLEANUP:
	return hr;
} // CPropData::GetPropData



HRESULT CPropData::GetPropData(
	ULONG			ulCol,		// [in] column to be read
	LONG			**pplValue	// [out] the value read
)
{
	HRESULT		hr = E_FAIL;

	if (!pplValue)
		return E_FAIL;

	// Get the column
	DBBINDING	*pBinding = &m_Rowset.m_rgBinding[ulCol];

	// checkings
	if (DBSTATUS_S_OK == STATUS_BINDING(*pBinding, m_Rowset.m_pData))
	{
		SAFE_ALLOC(*pplValue, LONG, 1);
		**pplValue = *(LONG*)&VALUE_BINDING(*pBinding, m_Rowset.m_pData);
	}
	else if (DBSTATUS_S_ISNULL == STATUS_BINDING(*pBinding, m_Rowset.m_pData))
		*pplValue = NULL;
	else
		return E_FAIL;

	hr = S_OK;

CLEANUP:
	return hr;
} // CPropData::GetPropData



HRESULT CPropData::GetPropData(
	ULONG			ulCol,			// [in] column to be read
	WCHAR			**ppwszValue	// [out] the value read
)
{
	HRESULT		hr = E_FAIL;

	if (!ppwszValue)
		return E_FAIL;

	// Get the column
	DBBINDING	*pBinding = &m_Rowset.m_rgBinding[ulCol];

	// checkings
	if (DBSTATUS_S_OK == STATUS_BINDING(*pBinding, m_Rowset.m_pData))
	{
		*ppwszValue = wcsDuplicate((WCHAR*)&VALUE_BINDING(*pBinding, m_Rowset.m_pData));
	}
	else if (DBSTATUS_S_ISNULL == STATUS_BINDING(*pBinding, m_Rowset.m_pData))
		*ppwszValue = NULL;
	else
		return E_FAIL;

	hr = S_OK;
	return hr;
} // CPropData::GetPropData



//-------------------------------------------------------------------------
//
//	CPropData::LoadProperties
//		Loads data for a scenario
//-------------------------------------------------------------------------
HRESULT CPropData::LoadProperties()
{
	HRESULT		hr = E_FAIL;
	LONG		ulColOffset = ((0 == m_Rowset.m_rgBinding[0].iOrdinal)? 1: 0);

	// if CPropData stored some value, release it
	ReleaseProps();

	TESTC_(GetPropData(ulColOffset + PropDataID, &m_plPropDataID), S_OK);
	TESTC_(GetPropData(ulColOffset + RecordName, &m_pwszRecordName), S_OK);
	TESTC_(GetPropData(ulColOffset + ValidConn, &m_pbValidConn), S_OK);
	TESTC_(GetPropData(ulColOffset + Provider, &m_pwszProvider), S_OK);
	TESTC_(GetPropData(ulColOffset + DataSource, &m_pwszDataSource), S_OK); 
	TESTC_(GetPropData(ulColOffset + IntegratedSecurity, &m_pwszIntegratedSecurity), S_OK);
	TESTC_(GetPropData(ulColOffset + UserID, &m_pwszUserID), S_OK); 
	TESTC_(GetPropData(ulColOffset + Password, &m_pwszPassword), S_OK); 
	TESTC_(GetPropData(ulColOffset + PersistSecurityInfo, &m_pbPersistSecurityInfo), S_OK);
	TESTC_(GetPropData(ulColOffset + InitCatalog, &m_pwszInitCatalog), S_OK); 
	TESTC_(GetPropData(ulColOffset + InitMode, &m_plInitMode), S_OK);
	TESTC_(GetPropData(ulColOffset + ExtendedProps, &m_pwszExtendedProps), S_OK);
	TESTC_(GetPropData(ulColOffset + InitTimeout, &m_plInitTimeout), S_OK); 
	TESTC_(GetPropData(ulColOffset + EncryptPassword, &m_pbEncryptPassword), S_OK);
	TESTC_(GetPropData(ulColOffset + MaskPassword, &m_pbMaskPassword), S_OK);
	TESTC_(GetPropData(ulColOffset + PersistEncrypted, &m_pbPersistEncrypted), S_OK);
	TESTC_(GetPropData(ulColOffset + CacheAuthInfo, &m_pbCacheAuthInfo), S_OK);
	TESTC_(GetPropData(ulColOffset + InitAsynch, &m_plInitAsynch), S_OK);
	TESTC_(GetPropData(ulColOffset + InitBindings, &m_plInitBindings), S_OK);
	TESTC_(GetPropData(ulColOffset + Location, &m_pwszLocation), S_OK);
	TESTC_(GetPropData(ulColOffset + LocaleID, &m_plLocaleID), S_OK);
	TESTC_(GetPropData(ulColOffset + ImpersonationLevel, &m_plImpersonationLevel), S_OK);
	TESTC_(GetPropData(ulColOffset + LockOwner, &m_pwszLockOwner), S_OK);
	TESTC_(GetPropData(ulColOffset + PS1, &m_pwszPS1), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS2, &m_pwszPS2), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS3, &m_pwszPS3), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS4, &m_pwszPS4), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS5, &m_pwszPS5), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS6, &m_pwszPS6), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS7, &m_pwszPS7), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS8, &m_pwszPS8), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS9, &m_pwszPS9), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS10, &m_pwszPS10), S_OK);
	TESTC_(GetPropData(ulColOffset + PS11, &m_pwszPS11), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS12, &m_pwszPS12), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS13, &m_pwszPS13), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS14, &m_pwszPS14), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS15, &m_pwszPS15), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS16, &m_pwszPS16), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS17, &m_pwszPS17), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS18, &m_pwszPS18), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS19, &m_pwszPS19), S_OK); 
	TESTC_(GetPropData(ulColOffset + PS20, &m_pwszPS20), S_OK);

	hr = S_OK;

CLEANUP:
	return hr;
} //CPropData::LoadProperties




// converts the not null fileds of the structure 
// in filtering criteria for a where clause
WCHAR	*CPropData::BuildFilterClause()
{
	WCHAR	wszClause[3000] = L"";
	WCHAR	*pwszRetValue	= NULL;
	WCHAR	wszConjunctie[]	= L" and ";
	WCHAR	wszBuffer[10]	= L"";

#define ADD_WSTR_TO_FILTER(fName, field)	{ if (NULL != field){	\
	wcscat(wszClause, wszConjunctie);									\
	wcscat(wszClause, fName);											\
	wcscat(wszClause, L" = '");											\
	wcscat(wszClause, field);										\
	wcscat(wszClause, L"'");}}


#define ADD_LONG_TO_FILTER(fName, field)	{ if (NULL != field){	\
	_ltow(*field, wszBuffer, 10);									\
	wcscat(wszClause, wszConjunctie);									\
	wcscat(wszClause, fName);											\
	wcscat(wszClause, L" = ");											\
	wcscat(wszClause, wszBuffer);}}


#define ADD_BOOL_TO_FILTER(fName, field)	{ if (NULL != field){	\
	wcscat(wszClause, wszConjunctie);									\
	wcscat(wszClause, fName);											\
	wcscat(wszClause, L" = ");											\
	wcscat(wszClause, (VARIANT_TRUE == *field)? L"True": L"False");}}

	ADD_LONG_TO_FILTER(L"PropDataID", m_plPropDataID);
	ADD_WSTR_TO_FILTER(L"RecordName", m_pwszRecordName);
	ADD_BOOL_TO_FILTER(L"ValidConn", m_pbValidConn);
	ADD_WSTR_TO_FILTER(L"Provider", m_pwszProvider);
	ADD_WSTR_TO_FILTER(L"DataSource", m_pwszDataSource); 

	if (m_pwszIntegratedSecurity && m_pwszIntegratedSecurity[0] == L'\0')
	{
		wcscat(wszClause, wszConjunctie);									\
		wcscat(wszClause, L"IntegratedSecurity IS NULL");											\
	}
	else
	{
		ADD_WSTR_TO_FILTER(L"IntegratedSecurity", m_pwszIntegratedSecurity);
	}

	ADD_WSTR_TO_FILTER(L"UserID", m_pwszUserID); 
	ADD_WSTR_TO_FILTER(L"Password", m_pwszPassword); 
	ADD_BOOL_TO_FILTER(L"PersistSecurityInfo", m_pbPersistSecurityInfo);
	ADD_WSTR_TO_FILTER(L"InitCatalog", m_pwszInitCatalog); 
	ADD_LONG_TO_FILTER(L"InitMode", m_plInitMode);
	ADD_WSTR_TO_FILTER(L"ExtendedProps", m_pwszExtendedProps);
	ADD_LONG_TO_FILTER(L"InitTimeout", m_plInitTimeout); 
	ADD_BOOL_TO_FILTER(L"EncryptPassword", m_pbEncryptPassword);
	ADD_BOOL_TO_FILTER(L"MaskPassword", m_pbMaskPassword);
	ADD_BOOL_TO_FILTER(L"PersistEncrypted", m_pbPersistEncrypted);
	ADD_BOOL_TO_FILTER(L"CacheAuthInfo", m_pbCacheAuthInfo);
	ADD_LONG_TO_FILTER(L"InitAsynch", m_plInitAsynch);
	ADD_LONG_TO_FILTER(L"InitBindings", m_plInitBindings);
	ADD_WSTR_TO_FILTER(L"Location", m_pwszLocation);
	ADD_LONG_TO_FILTER(L"LocaleID", m_plLocaleID);
	ADD_LONG_TO_FILTER(L"ImpersonationLevel", m_plImpersonationLevel);
	ADD_WSTR_TO_FILTER(L"LockOwner", m_pwszLockOwner);
	ADD_WSTR_TO_FILTER(L"PS1", m_pwszPS1); 
	ADD_WSTR_TO_FILTER(L"PS2", m_pwszPS2); 
	ADD_WSTR_TO_FILTER(L"PS3", m_pwszPS3); 
	ADD_WSTR_TO_FILTER(L"PS4", m_pwszPS4); 
	ADD_WSTR_TO_FILTER(L"PS5", m_pwszPS5); 
	ADD_WSTR_TO_FILTER(L"PS6", m_pwszPS6); 
	ADD_WSTR_TO_FILTER(L"PS7", m_pwszPS7); 
	ADD_WSTR_TO_FILTER(L"PS8", m_pwszPS8); 
	ADD_WSTR_TO_FILTER(L"PS9", m_pwszPS9); 
	ADD_WSTR_TO_FILTER(L"PS10", m_pwszPS10);
	ADD_WSTR_TO_FILTER(L"PS11", m_pwszPS11); 
	ADD_WSTR_TO_FILTER(L"PS12", m_pwszPS12); 
	ADD_WSTR_TO_FILTER(L"PS13", m_pwszPS13); 
	ADD_WSTR_TO_FILTER(L"PS14", m_pwszPS14); 
	ADD_WSTR_TO_FILTER(L"PS15", m_pwszPS15); 
	ADD_WSTR_TO_FILTER(L"PS16", m_pwszPS16); 
	ADD_WSTR_TO_FILTER(L"PS17", m_pwszPS17); 
	ADD_WSTR_TO_FILTER(L"PS18", m_pwszPS18); 
	ADD_WSTR_TO_FILTER(L"PS19", m_pwszPS19); 
	ADD_WSTR_TO_FILTER(L"PS20", m_pwszPS20);
	if (wszClause == wcsstr(wszClause, wszConjunctie))
	{
		pwszRetValue = wcsDuplicate(wszClause + wcslen(wszConjunctie));
	}
	else
		pwszRetValue = wcsDuplicate(L"");

	return pwszRetValue;
} //CPropData::BuildFilterClause




BOOL CPropData::InitFromFilter()
{
	
	TBEGIN
	HRESULT		hr;
	IRowset		*pIRowset = NULL;
	ULONG		ulColOffset = 0;
	WCHAR		pwszSQLCmdText[3000] =	L"SELECT PropDataID, RecordName, ValidConn, Provider, "
		L"DataSource, IntegratedSecurity, "
		L"UserID, Password, PersistSecurityInfo, "
		L"InitCatalog, InitMode, ExtendedProps, "
		L"InitTimeout, EncryptPassword, MaskPassword, "
		L"PersistEncrypted, CacheAuthInfo, InitAsynch, "
		L"InitBindings, Location, LocaleID, ImpersonationLevel, "
		L"LockOwner, PS1, PS2, PS3, PS4, PS5, PS6, PS7, PS8, PS9, PS10, "
		L"PS11, PS12, PS13, PS14, PS15, PS16, PS17, PS18, PS19, PS20 "
		L"from props where ";
	WCHAR		wszVarNo[10]		= L"";
	WCHAR		*pwszWhereClause	= NULL;

	// build a command based on the filtering constraints passed though pPropData
	// the non null fields of CPropData structure impose simple restrictions
	pwszWhereClause = BuildFilterClause();		
	wcscat(pwszSQLCmdText, pwszWhereClause);

	TESTC_(hr = s_pTable->BuildCommand(pwszSQLCmdText, IID_IRowset,
		EXECUTE_ALWAYS, 0, NULL, NULL, NULL, (IUnknown**)&pIRowset, NULL), S_OK);

	m_Rowset.DropRowset();
	m_Rowset.SetTable(s_pTable, DELETETABLE_NO);

	TESTC_PROVIDER(S_OK == m_Rowset.CreateRowset(pIRowset));

CLEANUP:
	SAFE_FREE(pwszWhereClause);
	SAFE_RELEASE(pIRowset);
	TRETURN
} //CPropData::InitFromFilter



HRESULT CPropData::GetNext()
{
	HRESULT	hr;
	HROW	hRow	= 0;

	//Try to find the specified row with this table...
	hr = m_Rowset.GetNextRows(&hRow);
	if (S_OK == hr)
	{
		// Load properties for the scenario
		TESTC_(hr = m_Rowset.GetRowData(hRow, &m_Rowset.m_pData),S_OK);

		// get the properties from database
		TESTC_(hr = LoadProperties(), S_OK);
	}

CLEANUP:
	m_Rowset.ReleaseRows(hRow);
	return hr;
} //CPropData::GetNext



// expose all the prop data as property sets
CPropSets *CPropData::GetPropSets()
{
	CPropSets	*pPropSets = new CPropSets();

	if (m_pwszDataSource)
		TESTC_(pPropSets->AddProperty(DBPROP_INIT_DATASOURCE, DBPROPSET_DBINIT, VT_BSTR, m_pwszDataSource), S_OK);

	if (m_pwszIntegratedSecurity)
		TESTC_(pPropSets->AddProperty(DBPROP_AUTH_INTEGRATED, DBPROPSET_DBINIT, VT_BSTR, m_pwszIntegratedSecurity), S_OK);

	if (m_pwszUserID)
		TESTC_(pPropSets->AddProperty(DBPROP_AUTH_USERID, DBPROPSET_DBINIT, VT_BSTR, m_pwszUserID), S_OK);

	if (m_pwszPassword)
		TESTC_(pPropSets->AddProperty(DBPROP_AUTH_PASSWORD, DBPROPSET_DBINIT, VT_BSTR, m_pwszPassword), S_OK);

	if (m_pbPersistSecurityInfo)
		TESTC_(pPropSets->AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, DBPROPSET_DBINIT, VT_BOOL, *m_pbPersistSecurityInfo, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_pwszInitCatalog)
		TESTC_(pPropSets->AddProperty(DBPROP_INIT_CATALOG, DBPROPSET_DBINIT, VT_BSTR, m_pwszInitCatalog), S_OK);

	if (m_plInitMode)
		TESTC_(pPropSets->AddProperty(DBPROP_INIT_MODE, DBPROPSET_DBINIT, VT_I4, *m_plInitMode, DBPROPOPTIONS_OPTIONAL), S_OK);
 
	if (m_pwszExtendedProps)
		TESTC_(pPropSets->AddProperty(DBPROP_INIT_PROVIDERSTRING, DBPROPSET_DBINIT, VT_BSTR, m_pwszExtendedProps, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_plInitTimeout)
		TESTC_(pPropSets->AddProperty(DBPROP_INIT_TIMEOUT, DBPROPSET_DBINIT, VT_I4, *m_plInitTimeout, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_pbEncryptPassword)
		TESTC_(pPropSets->AddProperty(DBPROP_AUTH_ENCRYPT_PASSWORD, DBPROPSET_DBINIT, VT_BOOL, *m_pbEncryptPassword, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_pbMaskPassword)
		TESTC_(pPropSets->AddProperty(DBPROP_AUTH_MASK_PASSWORD, DBPROPSET_DBINIT, VT_BOOL, *m_pbMaskPassword, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_pbPersistEncrypted)
		TESTC_(pPropSets->AddProperty(DBPROP_AUTH_PERSIST_ENCRYPTED, DBPROPSET_DBINIT, VT_BOOL, *m_pbPersistEncrypted, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_pbCacheAuthInfo)
		TESTC_(pPropSets->AddProperty(DBPROP_AUTH_CACHE_AUTHINFO, DBPROPSET_DBINIT, VT_BOOL, *m_pbCacheAuthInfo, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_plInitAsynch)
		TESTC_(pPropSets->AddProperty(DBPROP_INIT_ASYNCH, DBPROPSET_DBINIT, VT_I4, *m_plInitAsynch, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_plInitBindings)
		TESTC_(pPropSets->AddProperty(DBPROP_INIT_BINDFLAGS, DBPROPSET_DBINIT, VT_I4, *m_plInitBindings, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_pwszLocation)
		TESTC_(pPropSets->AddProperty(DBPROP_INIT_LOCATION, DBPROPSET_DBINIT, VT_BSTR, m_pwszLocation, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_plLocaleID)
		TESTC_(pPropSets->AddProperty(DBPROP_INIT_LCID, DBPROPSET_DBINIT, VT_I4, *m_plLocaleID, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_plImpersonationLevel)
		TESTC_(pPropSets->AddProperty(DBPROP_INIT_IMPERSONATION_LEVEL, DBPROPSET_DBINIT, VT_I4, *m_plImpersonationLevel, DBPROPOPTIONS_OPTIONAL), S_OK);

	if (m_pwszLockOwner)
		TESTC_(pPropSets->AddProperty(DBPROP_INIT_LOCKOWNER, DBPROPSET_DBINIT, VT_I4, *m_pwszLockOwner, DBPROPOPTIONS_OPTIONAL), S_OK);
CLEANUP:
	return pPropSets;
} //CPropData::GetPropSets

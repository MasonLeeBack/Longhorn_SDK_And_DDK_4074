// DSL_DB.hpp

// class used to detect the bound variables of the scenario template
class CPropData 
{
public:
	static CTable	*s_pTable;
	
	CRowset			m_Rowset;
	LONG			*m_plPropDataID;
	VARIANT_BOOL	*m_pbValidConn;
	WCHAR			*m_pwszRecordName;
	WCHAR			*m_pwszProvider;
	WCHAR			*m_pwszDataSource; 
	WCHAR			*m_pwszIntegratedSecurity;
	WCHAR			*m_pwszUserID; 
	WCHAR			*m_pwszPassword; 
	VARIANT_BOOL	*m_pbPersistSecurityInfo;
	WCHAR			*m_pwszInitCatalog; 
	LONG			*m_plInitMode;
	WCHAR			*m_pwszExtendedProps;
	LONG			*m_plInitTimeout; 
	VARIANT_BOOL	*m_pbEncryptPassword;
	VARIANT_BOOL	*m_pbMaskPassword;
	VARIANT_BOOL	*m_pbPersistEncrypted;
	VARIANT_BOOL	*m_pbCacheAuthInfo;
	LONG			*m_plInitAsynch;
	LONG			*m_plInitBindings;
	WCHAR			*m_pwszLocation;
	LONG			*m_plLocaleID;
	LONG			*m_plImpersonationLevel;
	WCHAR			*m_pwszLockOwner;
	WCHAR			*m_pwszPS1; 
	WCHAR			*m_pwszPS2; 
	WCHAR			*m_pwszPS3; 
	WCHAR			*m_pwszPS4; 
	WCHAR			*m_pwszPS5; 
	WCHAR			*m_pwszPS6; 
	WCHAR			*m_pwszPS7; 
	WCHAR			*m_pwszPS8; 
	WCHAR			*m_pwszPS9; 
	WCHAR			*m_pwszPS10;
	WCHAR			*m_pwszPS11; 
	WCHAR			*m_pwszPS12; 
	WCHAR			*m_pwszPS13; 
	WCHAR			*m_pwszPS14; 
	WCHAR			*m_pwszPS15; 
	WCHAR			*m_pwszPS16; 
	WCHAR			*m_pwszPS17; 
	WCHAR			*m_pwszPS18; 
	WCHAR			*m_pwszPS19; 
	WCHAR			*m_pwszPS20;

	CPropData():
		m_plPropDataID(NULL),	// prop data is not bound to a particular tuple of the DB
		m_pwszRecordName(NULL),
		m_pbValidConn(NULL),
		m_pwszProvider(NULL),
		m_pwszDataSource(NULL),
		m_pwszIntegratedSecurity(NULL),
		m_pwszUserID(NULL),
		m_pwszPassword(NULL),
		m_pbPersistSecurityInfo(NULL),
		m_pwszInitCatalog(NULL),
		m_plInitMode(NULL),
		m_pwszExtendedProps(NULL),
		m_plInitTimeout(NULL),
		m_pbEncryptPassword(NULL),
		m_pbMaskPassword(NULL),
		m_pbPersistEncrypted(NULL),
		m_pbCacheAuthInfo(NULL),
		m_plInitAsynch(NULL),
		m_plInitBindings(NULL),
		m_pwszLocation(NULL),
		m_plLocaleID(NULL),
		m_plImpersonationLevel(NULL),
		m_pwszLockOwner(NULL),
		m_pwszPS1(NULL),
		m_pwszPS2(NULL),
		m_pwszPS3(NULL),
		m_pwszPS4(NULL),
		m_pwszPS5(NULL),
		m_pwszPS6(NULL),
		m_pwszPS7(NULL),
		m_pwszPS8(NULL),
		m_pwszPS9(NULL),
		m_pwszPS10(NULL),
		m_pwszPS11(NULL),
		m_pwszPS12(NULL),
		m_pwszPS13(NULL),
		m_pwszPS14(NULL),
		m_pwszPS15(NULL),
		m_pwszPS16(NULL),
		m_pwszPS17(NULL),
		m_pwszPS18(NULL),
		m_pwszPS19(NULL),
		m_pwszPS20(NULL)
	{;}


	~CPropData() {Release();}

	void Release()
	{
		// release the rowset
		m_Rowset.DropRowset();

		ReleaseProps();
	}

	void ReleaseProps()
	{
		SAFE_FREE(m_plPropDataID);
		SAFE_FREE(m_pwszRecordName);
		SAFE_FREE(m_pbValidConn);
		SAFE_FREE(m_pwszProvider);
		SAFE_FREE(m_pwszDataSource); 
		SAFE_FREE(m_pwszIntegratedSecurity);
		SAFE_FREE(m_pwszUserID); 
		SAFE_FREE(m_pwszPassword);
		SAFE_FREE(m_pbPersistSecurityInfo);
		SAFE_FREE(m_pwszInitCatalog); 
		SAFE_FREE(m_plInitMode);
		SAFE_FREE(m_pwszExtendedProps);
		SAFE_FREE(m_plInitTimeout); 
		SAFE_FREE(m_pbEncryptPassword);
		SAFE_FREE(m_pbMaskPassword);
		SAFE_FREE(m_pbPersistEncrypted);
		SAFE_FREE(m_pbCacheAuthInfo);
		SAFE_FREE(m_plInitAsynch);
		SAFE_FREE(m_plInitBindings);
		SAFE_FREE(m_pwszLocation);
		SAFE_FREE(m_plLocaleID);
		SAFE_FREE(m_plImpersonationLevel);
		SAFE_FREE(m_pwszLockOwner);
		SAFE_FREE(m_pwszPS1); 
		SAFE_FREE(m_pwszPS2); 
		SAFE_FREE(m_pwszPS3); 
		SAFE_FREE(m_pwszPS4); 
		SAFE_FREE(m_pwszPS5); 
		SAFE_FREE(m_pwszPS6); 
		SAFE_FREE(m_pwszPS7); 
		SAFE_FREE(m_pwszPS8); 
		SAFE_FREE(m_pwszPS9); 
		SAFE_FREE(m_pwszPS10);
		SAFE_FREE(m_pwszPS11); 
		SAFE_FREE(m_pwszPS12); 
		SAFE_FREE(m_pwszPS13); 
		SAFE_FREE(m_pwszPS14); 
		SAFE_FREE(m_pwszPS15); 
		SAFE_FREE(m_pwszPS16); 
		SAFE_FREE(m_pwszPS17); 
		SAFE_FREE(m_pwszPS18); 
		SAFE_FREE(m_pwszPS19); 
		SAFE_FREE(m_pwszPS20);
	}

	// converts the not null fileds of the structure 
	// in filtering criteria for a where clause
	WCHAR	*BuildFilterClause();

	// takes a scenario template and wires it to the properties
//	HRESULT BuildScenario(	
//		ULONG		cAction,				// [in] number of elements in the action array
//		CAction		*rgActionTemplate,		// [in] action array template
//		CAction		**prgActualAction		// [out] action array describing a coplete scenario
//	);

	HRESULT GetPropData(
		ULONG			ulCol,		// [in] column to be read
		VARIANT_BOOL	**ppbValue	// [out] the value read
	);

	HRESULT	GetPropData(
		ULONG			ulCol,		// [in] column to be read
		LONG			**pplValue	// [out] the value read
	);

	HRESULT GetPropData(
		ULONG			ulCol,			// [in] column to be read
		WCHAR			**ppwszValue	// [out] the value read
	);

	HRESULT	LoadProperties();

	BOOL	InitFromFilter();

	// prepares to load the next prop data
	HRESULT GetNext();

	CPropSets	*GetPropSets();
}; //CPropData


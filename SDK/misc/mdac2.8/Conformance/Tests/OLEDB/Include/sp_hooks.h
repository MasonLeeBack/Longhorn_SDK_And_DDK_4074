//SP_Hooks.h
#include "ProvHooks.h"
#include "PoolingHooks.h"

//////////////////////////////////////////////////////////////////////////////////
// SP_TProv guids
//

//	SP_TProv's CLSID
// @msg CLSID_SP_TProv | {E8CCCB79-7C36-101B-AC3A-00AA0044773D} 
// Provider Class Id
DEFINE_GUID(CLSID_SP_TProv, 0xd68dc510, 0xc5cc, 0x11d1, 0xa5, 0x79, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);

//The Pooling tests require tests involving every combination of possible registry settings
//	But Pooling is clever enough to cache this info, and it is sometimes very hard to disengage pooling
//	So the SP_TProv has multiple registry entries that it's ClassFactory can handle, each with different
//		values for OLEDB_SERVICES
DEFINE_GUID(CLSID_SP_TProv_OS_NOENTRY,			0xd68dc511, 0xc5cc, 0x11d1, 0xa5, 0x79, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);
DEFINE_GUID(CLSID_SP_TProv_OS_RESOURCEPOOLING,	0xd68dc512, 0xc5cc, 0x11d1, 0xa5, 0x79, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);
DEFINE_GUID(CLSID_SP_TProv_OS_TXNENLISTMENT,	0xd68dc513, 0xc5cc, 0x11d1, 0xa5, 0x79, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);
DEFINE_GUID(CLSID_SP_TProv_OS_RP_TXN,			0xd68dc514, 0xc5cc, 0x11d1, 0xa5, 0x79, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);
DEFINE_GUID(CLSID_SP_TProv_OS_CLIENTCURSOR,		0xd68dc515, 0xc5cc, 0x11d1, 0xa5, 0x79, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);
DEFINE_GUID(CLSID_SP_TProv_OS_CC_RP,			0xd68dc516, 0xc5cc, 0x11d1, 0xa5, 0x79, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);
DEFINE_GUID(CLSID_SP_TProv_OS_CC_TXN,			0xd68dc517, 0xc5cc, 0x11d1, 0xa5, 0x79, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);
DEFINE_GUID(CLSID_SP_TProv_OS_CC_TXN_RP,		0xd68dc518, 0xc5cc, 0x11d1, 0xa5, 0x79, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);
DEFINE_GUID(CLSID_SP_TProv_ENABLEALL,			0xd68dc519, 0xc5cc, 0x11d1, 0xa5, 0x79, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);

//Provider specific interface
DEFINE_GUID(IID_ISPTProvSpecific, 0xb23bcba0, 0xe51a, 0x11d1, 0xa5, 0x85, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);

DEFINE_GUID(IID_ISPTAsynchNotify, 0x7453f330, 0xef5f, 0x11d1, 0xa5, 0x8f, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);


// 
// @msg DBINIT_OPT_SP_TProv_PATH | {E9FBAF50-D402-11ce-BEDC-00AA00A14D7D}
// option GUID for IDBInitialize::Initialize. SP_TProv-specific GUID indicating path to CSV database file.
DEFINE_GUID(DBINIT_OPT_SP_TProv_PATH, 0xe9fbaf50, 0xd402, 0x11ce, 0xbe, 0xdc, 0x0, 0xaa, 0x0, 0xa1, 0x4d, 0x7d);

DEFINE_GUID(DBPROPSET_SPTINIT, 0xd68dc51a, 0xc5cc, 0x11d1, 0xa5, 0x79, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);

//{0xa57e1690, 0xd0ce, 0x11d1, {0xa5, 0x7b, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf}}
DEFINE_GUID(DBPROPSET_SPTSESSION,0xa57e1690, 0xd0ce, 0x11d1, 0xa5, 0x7b, 0x0, 0xc0, 0x4f, 0xd7, 0xa9, 0xf);
//
// SP_TProv guids
//////////////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////////////
// Class CControlSP_TProv
//

#define SPTPROP_INIT_BIOID		0x1//could be any number, in theory.  Unique property of SPTProv
#define SPTPROP_SESSION_DSOID	0xfff
#define SPT_INVALID_BIOIDVALUE	L"INVALID BIOID VALUE"//This will cause Initialize to return DB_X_ERRORSOCCURRED
#define BAD_PASSWORD			L"JackDawson"//A Password SP_TProv rejects as a BAD_VALUE, which SC couldn't know about.
#define SP_TPROV_DWMINOR		0x07


//CControlSP_TProv
//
//SP_TProv's behavior can be controlled through this class
//	works through registry settings
//	All methods are inline
//	SP_TProv never changes these registry settings 
//		and never calls these methods, so tests using 
//		SP_TProv should call CControlSP_TProv::AllowAll()
//		before running any variations.

class CControlSP_TProv
{	
private:

	bool OpenKey(HKEY * phKey)
	{
		DWORD dwDisposition (0);
		LONG stat = RegCreateKeyEx(
					HKEY_CLASSES_ROOT
					,CONTROL_KEY
					,0
					,NULL
					,REG_OPTION_NON_VOLATILE
					,KEY_ALL_ACCESS
					,NULL
					,phKey
					,&dwDisposition);

		if(ERROR_SUCCESS != stat)
		{
			*phKey = NULL;
			return false;
		}
		return true;
	}

	bool CoreAllow(const char * szValueName, DWORD dwValue)
	{
		HKEY hk;
		if(!OpenKey(&hk))
			return false;

		LONG stat = RegSetValueEx(hk
							,szValueName
							,0
							,REG_DWORD
							,(BYTE *) &dwValue
							,sizeof(DWORD));
		RegCloseKey( hk );

		return (ERROR_SUCCESS == stat);
	}

	bool SetValue(const char * szValueName, DWORD dwValue)
	{
		return CoreAllow(szValueName, dwValue);
	}

	bool OpenKey(HKEY * phKey, const char * szValueName)
	{
		DWORD	dwDisposition	(0);

		char	(*szFullKey)	(NULL);
		szFullKey				= new char[strlen(szValueName) + strlen(CONTROL_KEY) + 2];
		szFullKey[0]			= '\0';

		strcpy( szFullKey, CONTROL_KEY);
		strcat(	szFullKey, "\\");
		strcat( szFullKey, szValueName);
			
		LONG	stat	= RegCreateKeyEx(HKEY_CLASSES_ROOT
										,szFullKey
										,0
										,NULL
										,REG_OPTION_NON_VOLATILE
										,KEY_ALL_ACCESS
										,NULL
										,phKey
										,&dwDisposition);
		
		delete [] szFullKey;

		if(ERROR_SUCCESS != stat)
		{
			*phKey = NULL;
			return false;
		}
		return true;
	}	

	bool SetValue(const char * szValueName, DWORD dwValue, char * szVal)
	{
		HKEY hk;
		if(!OpenKey(&hk, szValueName))
			return false;

		LONG stat = RegSetValueEx(	hk
									,szVal
									,0
									,REG_DWORD 
									,(BYTE *)&dwValue
									,sizeof(DWORD));
		RegCloseKey( hk );
		return (ERROR_SUCCESS == stat);
	}

	bool CoreIs(const char * szValueName)
	{
		HKEY hk;
		if(!OpenKey(&hk))
			return true;//false; //We return true because if we can't tell, we will assume all is OK, and we're doing some other kind of test right now.

		DWORD dwValue	  (0);
		DWORD dwValueType (0);
		DWORD dwcbData    (sizeof(DWORD));

		LONG stat = RegQueryValueEx(hk
							,szValueName
							,0
							,&dwValueType
							,(LPBYTE)&dwValue
							,&dwcbData);
		RegCloseKey( hk );

		if(ERROR_SUCCESS != stat)
			return false;


		return(1ul == dwValue);
	}

	DWORD RetrieveValue(const char * szValueName)
	{
		HKEY hk;
		if(!OpenKey(&hk))
			return false;

		DWORD dwValue		(0);
		DWORD dwValueType	(0);
		DWORD dwcbData		(sizeof(DWORD));

		LONG stat = RegQueryValueEx(hk
							,szValueName
							,0
							,&dwValueType
							,(LPBYTE)&dwValue
							,&dwcbData);
		RegCloseKey( hk );

		if(ERROR_SUCCESS != stat)
			return false;


		return(dwValue);
	}

	bool RetrieveStringValues(const char * szValueName
							, DWORD * rgdwVals
							, char ** rgszVal
							, ULONG * pcVals
							, ULONG	* pcMaxValChars )
	{
		HKEY hk;
		if(!OpenKey(&hk, szValueName))
			return false;

		DWORD cbMaxValChars		(0);

		if((!szValueName) || (!rgdwVals) || (!rgszVal))
		{
			if(ERROR_SUCCESS == RegQueryInfoKey(hk		// handle of key to query 
												,NULL	//buff for class string
												,NULL	//size of class string buffer
												,NULL	//reserved
												,NULL	//number of subkeys
												,NULL	//longest subkey name length
												,NULL	//longest class string length
												,pcVals	//number of value entries
												,&cbMaxValChars //longest val name length
												,NULL	//longest value data length (we know its a DWORD)
												,NULL
												,NULL))
			{


												/*
						LPDWORD lpcbMaxValueNameLen,	// address of buffer for longest value name length 
						LPDWORD lpcbMaxValueLen,		// address of buffer for longest value data length 
						LPDWORD lpcbSecurityDescriptor, // address of buffer for security descriptor length 
						PFILETIME lpftLastWriteTime		// address of buffer for last write time 
 												*/
				*pcMaxValChars = cbMaxValChars / sizeof(char);
				return true;
			}
			else
			{
				*pcMaxValChars  = 0;
				*pcVals			= 0;
				return false;
			}
		}

		DWORD	dwType		(0);
		DWORD	cbData		(4);
		DWORD	dwcMax		=1+ *pcMaxValChars;

		LONG	stat		(ERROR_SUCCESS);


		for(UINT c=0; (c<(*pcVals)) && (stat == ERROR_SUCCESS); c++)
		{
			stat = RegEnumValue(hk					//handle of key to query
								,c					//index of value to query
								,rgszVal[c]			//address of buffer for value string
								,&dwcMax			//address for size of value buffer
								,0					//reserved
								,&dwType			//buffer for type code
								,(BYTE*)&rgdwVals[c]//buffer for value data
								,&cbData);			//address for size of data buffer
			dwcMax = 1 + *pcMaxValChars;
		}
		*pcVals = c;
		
		return (ERROR_SUCCESS == stat);
	}

private:
	const char * CONTROL_KEY;
	const char * PROPDESC_KEY;
	const char * ALLOW_INITIALIZE;
	const char * ALLOW_INIT_BRIEFLY;
	const char * ALLOW_SETPROPERTIES;
	const char * ALLOW_CONNECT;
	const char * ALLOW_JOINTRANSACTION;
	const char * PREVENT_INIT_BRIEFLY;
	const char * BLOCK_CONNECTEDPROP_CTIMES;
	const char * PROMPT_DEFAULT_VAL;
	const char * COUNT_CREATEINSTANCES;
public:
	CControlSP_TProv() :
		CONTROL_KEY					("CLSID\\{D68DC510-C5CC-11d1-A579-00C04FD7A90F}\\Control"),
		PROPDESC_KEY				("PropertyDescriptions"),
		ALLOW_INITIALIZE			("AllowInitialize"),
		ALLOW_INIT_BRIEFLY			("AllowInitBriefly"),
		PREVENT_INIT_BRIEFLY		("PreventInitBriefly"),
		BLOCK_CONNECTEDPROP_CTIMES	("TimesToBlockConnection"),
		ALLOW_SETPROPERTIES			("AllowSetProperties"),
		ALLOW_CONNECT				("ReturnIsConnected"),
		ALLOW_JOINTRANSACTION		("AllowJoinTransaction"),
		PROMPT_DEFAULT_VAL			("InitPromptDefVal"),
		COUNT_CREATEINSTANCES		("CountOfCreateInstCalls")
	{
		//members are initialized above.
	}

	bool ResetCountOfCreateInstanceCalls(DWORD * pdwCountOfCreateInstanceCalls)
	{
		if(!pdwCountOfCreateInstanceCalls)
			return false;

		*pdwCountOfCreateInstanceCalls = RetrieveValue(COUNT_CREATEINSTANCES);
		return SetValue(COUNT_CREATEINSTANCES, 0ul);
	}
	bool IncrementCountOfCreateInstanceCalls()
	{
		DWORD dwNewCount		(0);
		//consider adding a mutext here!!!
		dwNewCount = 1+RetrieveValue(COUNT_CREATEINSTANCES);
		return SetValue(COUNT_CREATEINSTANCES, dwNewCount);
	}
	bool AllowJoinTransaction(bool fAllow)
	{
		return CoreAllow(ALLOW_JOINTRANSACTION, (fAllow ? 1ul : 0ul));
	}

	//Allow or Prevent IDBInitialize::Initialize to succeed
	bool AllowInitialize(bool fAllow)
	{
		bool f1 = CoreAllow(ALLOW_INIT_BRIEFLY,	0ul);
		bool f2 = CoreAllow(PREVENT_INIT_BRIEFLY, 0ul);

		bool f3 = CoreAllow(ALLOW_INITIALIZE, (fAllow ? 1ul : 0ul));

		return (f1 && f2 && f3);
	}
	//Cause Initialization to work only very briefly, possibly only once
	//Any call to AllowInitialize overrides this command
	bool AllowInitializeBriefly()
	{
		//Remove potentially conflicting settings
		bool f1 = CoreAllow(ALLOW_INITIALIZE,		1ul);
		bool f2 = CoreAllow(PREVENT_INIT_BRIEFLY,	0ul);
		
		//Set this
		bool f3 = CoreAllow(ALLOW_INIT_BRIEFLY,		1ul);

		return (f1 && f2 && f3);
	}

	//Prevents Initialization from working very briefly, - usually only failing once, then succeeding on subsequent calls if possible
	bool PreventInitializeSeveralTimes(ULONG ulTimes)
	{
		//bool f1 = CoreAllow(ALLOW_INITIALIZE,		0ul);
		//bool f2 = CoreAllow(ALLOW_INIT_BRIEFLY,		0ul);
		bool f3 = CoreAllow(PREVENT_INIT_BRIEFLY,	ulTimes);

		return(/*f1 && f2 && */f3);
	}

	//Allow or Prevent IDBProperties::SetProperties to succeed
	bool AllowSetProperties(bool fAllow)
	{
		return CoreAllow(ALLOW_SETPROPERTIES, (fAllow ? 1ul : 0ul));
	}
	//Change the state of the connection property returned through GetProperties
	bool AllowConnectedProp(bool fAllow)
	{
		return CoreAllow(ALLOW_CONNECT, (fAllow ? 1ul : 0ul));
	}

	//Block and read how many times we are preventing the connected property from being connected
	bool BlockConnectedProp_cTimes(ULONG cTimes)
	{
		return CoreAllow(BLOCK_CONNECTEDPROP_CTIMES, cTimes);
	}
	ULONG DecrementConnectedPropBlockage()
	{
		ULONG ulRetVal = (ULONG)RetrieveValue(BLOCK_CONNECTEDPROP_CTIMES);
		if(0 != ulRetVal)
		{
			CoreAllow(BLOCK_CONNECTEDPROP_CTIMES, ulRetVal-1);
		}
		return ulRetVal;
	}
	ULONG GetConnectedPropBlockage()
	{
		return (ULONG)RetrieveValue(BLOCK_CONNECTEDPROP_CTIMES);
	}

	bool AllowAll()
	{
		bool f1 = AllowInitialize(true);
		bool f2 = AllowSetProperties(true);
		bool f3 = AllowConnectedProp(true);
		bool f4 = SetPromptDefault(DBPROMPT_NOPROMPT);
		bool f5 = BlockConnectedProp_cTimes(0);
		bool f6 = AllowJoinTransaction(true);

		return(f1 && f2 && f3 && f4 && f5 && f6);
	}

	bool IsJoinTransactionAllowed()
	{
		return CoreIs(ALLOW_JOINTRANSACTION);
	}

	bool IsInitializeAllowed()
	{
		return CoreIs(ALLOW_INITIALIZE);
	}
	bool IsInitializeAllowedBriefly()
	{
		return CoreIs(ALLOW_INIT_BRIEFLY);
	}
	ULONG GetInitializationsToBePrevented()
	{
		return (ULONG)RetrieveValue(PREVENT_INIT_BRIEFLY);
	}
	ULONG DecrementInitializationsToBePrevented()
	{
		ULONG ulRetVal = (ULONG)RetrieveValue(PREVENT_INIT_BRIEFLY);
		if(0 != ulRetVal)
		{
			CoreAllow(PREVENT_INIT_BRIEFLY, ulRetVal-1);
			//if(0==(ulRetVal-1))
			//	AllowInitialize(true);
		}
		return ulRetVal;
	}
	bool IsSetPropertiesAllowed()
	{
		return CoreIs(ALLOW_SETPROPERTIES);
	}
	bool IsConnected()
	{
		return CoreIs(ALLOW_CONNECT);
	}

	bool SetPromptDefault(long lPromptDefaultVal)
	{
		return SetValue(PROMPT_DEFAULT_VAL, (DWORD)lPromptDefaultVal);
	}
	LONG GetPromptDefault()
	{
		long temp = 0;
		return temp = (long)RetrieveValue(PROMPT_DEFAULT_VAL);
	}

	//SetPropertyDescription
	//		Only really appropriate for SPT_Prov specific property descriptions
	//		Effective only if called before Datasource Creation.
	bool SetPropertyDescription(DBPROPID dwID, char * szDescription)
	{	
		return SetValue(PROPDESC_KEY, dwID, szDescription);
	}

	bool GetPropertyDescriptions(DBPROPID * rgdwIDs, char ** rgszDescriptions  //out params
								, ULONG * pcVals, ULONG * pcMaxLenDescriptions)//in/out lengths
	{
		return RetrieveStringValues(PROPDESC_KEY, rgdwIDs, rgszDescriptions, pcVals, pcMaxLenDescriptions);
	}
};
//
// End class CControlSP_TProv
//////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// CSimpleGlobalTrace
//
//
class CSimpleGlobalTrace
{
private:
	const char * DEFAULT_FILENAME;
	const char * REG_VALUE;

	bool OpenKey(HKEY * phKey)
	{
		DWORD dwDisposition (0);
		LONG stat = RegCreateKeyEx(
						HKEY_CLASSES_ROOT
						,"GlobalTrace"
						,0
						,NULL
						,REG_OPTION_NON_VOLATILE
						,KEY_ALL_ACCESS
						,NULL
						,phKey
						,&dwDisposition);

		if(ERROR_SUCCESS != stat)
		{
			*phKey = NULL;
			return false;
		}

		return true;
	}

public:
	CSimpleGlobalTrace() : REG_VALUE ("File1"), DEFAULT_FILENAME ("C:\\GlobalTrace.txt")  
	{
		HKEY hKey;

		if(!OpenKey(&hKey))
			return;

		char szFile[500];
		ZeroMemory(&szFile[0], sizeof(char) * 500);
		
		if(RetrieveFile(szFile, 500) && 
		   (szFile[0] == '\0'))
		{
			SetFile(DEFAULT_FILENAME);
		}
	}

	bool RetrieveFile(char * szFile, ULONG cMaxChars)
	{
		HKEY hk;
		if(!OpenKey(&hk))
			return false;

		DWORD dwValueType (0);
		DWORD dwcbData    (sizeof(char) * cMaxChars);

		LONG stat = RegQueryValueEx(hk
									,REG_VALUE
									,0
									,&dwValueType
									,(LPBYTE)&szFile[0]
									,&dwcbData);
		RegCloseKey(hk);

		return (ERROR_SUCCESS == stat);
	}

	bool SetFile(const char * szFile)
	{
		HKEY hk;
		if(!OpenKey(&hk))
			return false;

		LONG stat = RegSetValueEx(hk
								  ,REG_VALUE
								  ,0
								  ,REG_SZ
								  ,(BYTE *) szFile
								  ,sizeof(char) * (1+strlen(szFile))
								  );
		RegCloseKey(hk);

		return (ERROR_SUCCESS == stat);
	}


	bool Trace(OLECHAR * wszTrace)
	{

		const ULONG cMaxChars = 500;
		char szFile[cMaxChars];
		ZeroMemory(&szFile[0], sizeof(char) * cMaxChars);

		RetrieveFile(&szFile[0], cMaxChars);
		if(szFile[0] == L'\0')
		{
			return false;
		}

		//now append to the file
		FILE * pFile = fopen(&szFile[0], "a+");

		if(!pFile)
			return false;

		bool fRetVal = (EOF != fputws( wszTrace, pFile ));

		fclose(pFile);

		return fRetVal;
	}

	bool ClearTrace()
	{
		return ClearTrace(NULL, 0);
	}
	bool ClearTrace(LPOLESTR wszTraced, ULONG  cMaxChars)
	{
	//	odtLog << "Tracing currently broken!\n";
		return true;//return true temporarily to allow tests to continue working
	}

	bool RetrieveTrace(LPOLESTR wszTraced, ULONG cMaxChars)
	{
	//	odtLog << "Tracing currently broken!\n";
		return true;//returning true temporarily to allow tests to continue working
	}
};
//
//
// CSimpleGlobalTrace
////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////
// IID_ISPTAsynchNotify defined
//	
//	An outgoing interface called when the datasource is being destroyed
//		needed for Death Connection Management tests
//
#ifndef __ISPTAsynchNotify_INTERFACE_DEFINED__
#define __ISPTAsynchNotify_INTERFACE_DEFINED__


EXTERN_C const IID IID_ISPTAsynchNotify;


interface ISPTAsynchNotify : public IUnknown
	{
    public:
        virtual HRESULT STDMETHODCALLTYPE OnDatasourceDestructor(
            /* [out] */ ULONG __RPC_FAR *pulSleepMilliseconds) = 0;
        
	};

#endif
//
//
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
// ISimpleID, otherwise known as ISPTProvSpecific
//		General backdoor interface
//
#ifndef __ISimpleID_INTERFACE_DEFINED__
#define __ISimpleID_INTERFACE_DEFINED__

/*
typedef struct tagTJLogEntry
{
	//ULONG	ulmsSessionAge;
	DWORDLONG	dwlnsSessionAge;
	BOOL		fTransactionCoord;
	ISOLEVEL	isoLevel;
} TJLogEntry;
*/
typedef struct tagSetPropertiesEntry
{
	ULONG		cProperties;
	DBPROPSET *	rgProperties;
	HRESULT		hr;
} SetPropertiesEntry;


//EXTERN_C const IID IID_ISimpleID;

interface ISimpleID : public IUnknown
	{
    public:
        virtual HRESULT STDMETHODCALLTYPE SetID(
            /* [in] */ DWORD dwID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RetrieveID(
            /* [out] */ DWORD __RPC_FAR *pdwID) = 0;

		virtual HRESULT STDMETHODCALLTYPE RetrieveAutoBigID(
			/* [out] */ GUID __RPC_FAR *pguidBigID) = 0;

		virtual HRESULT STDMETHODCALLTYPE SetAllowResetDatasource(
			/* [in] */ BOOL fAllowResetDatasource) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetProperties( 
            /* [in] */ ULONG cPropertyIDSets,
            /* [size_is][in] */ const DBPROPIDSET __RPC_FAR rgPropertyIDSets[  ],
            /* [out][in] */ ULONG __RPC_FAR *pcPropertySets,
            /* [size_is][size_is][out] */ DBPROPSET __RPC_FAR *__RPC_FAR *prgPropertySets) = 0;


		virtual HRESULT STDMETHODCALLTYPE GetTJLog(
				/* [out] */ ULONG __RPC_FAR * pcLogs,
				/* [out] */ TJLogEntry ** prgTJLogEntry) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetSetPropertyLog(
				/* [out] */ ULONG __RPC_FAR * pcEntries,
				/* [out] */ SetPropertiesEntry ** prgSetPropertiesEntries) = 0;

		// resets the initialization counter (how many times was the obj initialized)
        virtual HRESULT STDMETHODCALLTYPE ResetInitCounter() = 0;
		// gets initialization counter
        virtual HRESULT STDMETHODCALLTYPE GetInitCounter(
			/* [out] */ DWORD __RPC_FAR *pdwInitCnt) = 0;
        
		// get the value of DBPROP_INIT_OLEDBSERVICES set on obj at init time
        virtual HRESULT STDMETHODCALLTYPE GetServicesAtInit(
			/* [out] */ LONG __RPC_FAR *plInitServices) = 0;
    };


#endif
//
//
//////////////////////////////////////////////////////////////////////////////////
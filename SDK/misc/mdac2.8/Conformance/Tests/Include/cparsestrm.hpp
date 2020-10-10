//--------------------------------------------------------------------
// Microsoft OLE DB 
// Copyright 1995-2000 Microsoft Corporation.  
//
// @doc
//
// @module CParseStrm.h
//
//
#ifndef _CPARSESTRM_H_
#define _CPARSESTRM_H_



#include "CCol.hpp"
#include "modcommon.hpp"
#include <fstream.h>



//-----------------------------------------------------------------------------
// @comm #pragma warning (disable: 4275) - This warning is generated by having
// fstream as a base class in a class that is exposed through
// a dll interface. This is simply a warning. The fstream member variables
// are not exposed even if they are public data members. There have to be Get/Set
// functions that handle these member variables.
//	
//-----------------------------------------------------------------------------
#pragma warning(disable: 4275)  // deriving exported class from non-exported
#pragma warning(disable: 4251)  // using non-exported as public in exported


//////////////////////////////////////////////////////////////////////////
// Defines
//
//////////////////////////////////////////////////////////////////////////
#define START_OF_TYPE	"\x16"
#define START_OF_DATA	"\x17"
#define END_OF_DATA		"\x18"
#define END_OF_LINE		"\x19"



//////////////////////////////////////////////////////////////////////////////
// CAutoBlock
//
//////////////////////////////////////////////////////////////////////////////
class DLL_EXPORT CAutoBlock 
{
public:
	//Constructors
	CAutoBlock(CRITICAL_SECTION* pCS)
	{
		//Data
		m_pCS = pCS;
		Block();
	}

	~CAutoBlock()
	{
		UnBlock();
	}
	
	inline void Block()
	{
		if (m_pCS)
			EnterCriticalSection( m_pCS );
	}

	inline void UnBlock()
	{
		if(m_pCS)
			LeaveCriticalSection( m_pCS );
		m_pCS = NULL;
	}

private:
	CRITICAL_SECTION*	m_pCS;
};



//////////////////////////////////////////////////////////////////////////////
// CCriticalSection
//
//////////////////////////////////////////////////////////////////////////////
class DLL_EXPORT CCriticalSection
{
public:
	//Constructors
	CCriticalSection()
	{
		InitializeCriticalSection(&m_CS);
	}

	~CCriticalSection()
	{
		DeleteCriticalSection(&m_CS);
	}

	//Helpers
	inline CRITICAL_SECTION* GetCS()
	{
		return &m_CS;
	}
	
	inline void Enter()
	{
		EnterCriticalSection(&m_CS);
	}

	inline void Leave()
	{
		LeaveCriticalSection(&m_CS);
	}

private:
	//Data
	CRITICAL_SECTION	m_CS;
};



//
//--------------------------------------------------------------------
// @class CParseInitFile | Opens and manipulates a given text file.  Allows 
// reads, seeks./TODO - allow deletes?
// 
// @hungarian 
//
class DLL_EXPORT CParseInitFile : private fstream 		//@base public | fstream
{

public: //@access public
	//@cmember Constructor
	CParseInitFile();
	
	//@cmember Destructor
	virtual ~CParseInitFile();
	
	//@cmember Initialization routine
	BOOL Init(WCHAR* pwszFileName);	
	
	//@cmember Return the number of columns in the file
	inline DBORDINAL GetColumnCount() { return m_ColData.GetCount(); }
	
	//@cmember Return the number of rows in the file
	inline DBCOUNTITEM GetRowCount() { return m_cRows; }
	
	//@cmember Return the row offset in the file for each row
	inline DBLENGTH GetRowOffset(DBCOUNTITEM iRow);
	
	//@cmember Return the row offset in the file for each row
	virtual void InitializeNewCol(CCol &NewCol);
		
	//@cmember return the col list
	inline virtual CList<CCol,CCol&> &GetColList() {return m_ColData;}

	virtual HRESULT GetNextLine(CHAR* pszBuffer, DBLENGTH cLength);
	virtual HRESULT FindSection(CHAR* pszSectionName, CHAR* pszFirstReqSec=NULL);

	//@cmember fetch the row
	virtual HRESULT FetchRow(DBCOUNTITEM ulRow);
	
	//@cmember Parset he row
	virtual HRESULT ParseRowValues(DBORDINAL ulColumn, CHAR** ppszOffset, DBLENGTH* pdwLength, DBTYPE *pwType);
	
	//@cmember Get Data
	virtual HRESULT GetData(DBCOUNTITEM ulRow,DBORDINAL ulColumn, WCHAR* pwszData, DBTYPE *pwType);

	//@cmember Obtain the URL for an Object Type.
	virtual WCHAR* GetURL(EINTERFACE eInterface);

	//@cmember Set the URL for an Object Type.
	virtual BOOL SetURL(EINTERFACE eInterface, WCHAR* pwszURL);

	//@cmember Overwrite the Set URL for an Object Type.
	virtual BOOL OverwriteURL(EINTERFACE eInterface, WCHAR* pwszURL);

	//@cmember Obtain the provider specific QueryString
	virtual WCHAR* GetQuery(EQUERY eQuery);


protected: //@access private

	//@cmember Control procedure to Read and parse intitialinformation from the file
	virtual BOOL GenerateFileInfo();
	
	//@cmember Get ProviderInfo from INI file
	virtual BOOL ParseProviderInfo();

	//@cmember Get URLInfo from INI file
	virtual BOOL ParseURLInfo();

	//@cmember Get QueryInfo from INI file
	virtual BOOL ParseQueryInfo();

	//@cmember Break a stream into MetaData information
	virtual BOOL ParseColumnInfo();
	
	//@cmember Get the data offsets into the file
	virtual BOOL ParseDataInfo();

	//@cmember Break a stream into column names
	virtual BOOL GetColumns(CHAR* pszInput);
	
	//@cmember Get the Column DBTYPE
	virtual DBTYPE ConvertToDBTYPE(LPSTR pszDBTYPE);
	
	//@cmember Get the flag types
	virtual void ParseFlags(LPSTR pszColumnFlags, CCol &NewCol);
	
	//@cmember Convert string to byte
	virtual BYTE ConvertToByte(LPSTR pszPrecision);
	
protected: //@access protected
	LPSTR					m_pszFileName;
	//@cmember Count of rows in the table 								 
	DBCOUNTITEM				m_cRows;
	//@cmember Input buffer of size MAX_INPUT_BUFFER
	LPSTR					m_pvInput;
	//@cmember Offset into file for Data
	DBCOUNTITEM				m_cRowOffsets;
	//@cmember Offset into file for each row
	DBLENGTH*				m_rgRowOffsets;

	ULONG					m_cURLs;
	WCHAR*					m_rgURLs[INVALID_INTERFACE];

	ULONG					m_cQueryNames;
	WCHAR*					m_rgQueryNames[LASTENUM+1];

private:
	//@cmember Column Metadat
	CList <CCol, CCol&>		m_ColData;

	//Critical Section (for low level file access)
	CCriticalSection		m_csFile;
};

#endif




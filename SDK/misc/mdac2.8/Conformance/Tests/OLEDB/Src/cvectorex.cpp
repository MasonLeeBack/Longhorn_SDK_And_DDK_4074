//--------------------------------------------------------------------
// Microsoft OLE DB Test
//
// Copyright 1998-2000 Microsoft Corporation.  
//
// @doc 
//
// @module CVectorEx Implementation Module | 	This module contains definition information
//			for the CVectorEx and CVectorExSet classes
//
// @comm
// Special Notes...:	(OPTIONAL NOTES FOR SPECIAL CIRCUMSTANCES)
//
// <nl><nl>
// Revision History:<nl>
//---------------------------------------------------------------------------
// file CVectorEx.cpp

#include "CVectorEx.hpp"

template <typename TYPE>
void CVectorEx <TYPE>::Free()
{
	// before the destructor is invoked, the wrapper class should Allocate or relase the memory
	// allocated for each TYPE element
	CAllocator::Free(&m_ulArraySize, &m_rgArray);
	m_ulMaxArraySize	= 0;
} //CVectorEx <TYPE>::Free



template <typename TYPE>
void CVectorEx <TYPE>::Attach(ULONG cElements, TYPE *rgElements)
{
	Free();

	// just use the memory that was passed in
	m_rgArray			= rgElements;
	m_ulArraySize		= cElements;
	m_ulMaxArraySize	= cElements;
} //CVectorEx <TYPE>::Attach



template <typename TYPE>
HRESULT	CVectorEx <TYPE>::AddElement(TYPE *pEl, ULONG *pulIndex)
{
	HRESULT		hr			= E_FAIL;

	if (m_ulArraySize >= m_ulMaxArraySize)
	{
		// alloc more memory
		CAllocator::Realloc(m_ulMaxArraySize, &m_rgArray, m_ulMaxArraySize + m_ulSizeInc);
		m_ulMaxArraySize	+=	m_ulSizeInc;
	}

	// take care of the new element
	if (pEl)
	{
		m_rgArray[m_ulArraySize] = *pEl;
	}
	if (pulIndex)
		*pulIndex = m_ulArraySize;
	m_ulArraySize++;
	hr = S_OK;

	return hr;
} //CVectorEx<TYPE>::AddElement



template <typename TYPE>
HRESULT CVectorEx<TYPE>::RemoveAt(DBORDINAL index)
{

	if (m_ulArraySize <= index)
		return E_INVALIDARG;
	
	for (index; index < m_ulArraySize - 1; index++)
	{
		m_rgArray[index] = m_rgArray[index + 1];
	}

	// remember in wrappers to take care of the last object
	m_ulArraySize--;
	return S_OK;
} //CVectorEx<TYPE>::RemoveAt



template <typename TYPE>
HRESULT CVectorEx<TYPE>::RemoveElement(TYPE *pEl)
{
	LONG	lIndex = FindElement(pEl);

	if (0 > lIndex)
		return E_FAIL;
	
	return RemoveAt((DBORDINAL)lIndex);
} //CVectorEx<TYPE>::RemoveElement
		


template <typename TYPE>
LONG CVectorEx<TYPE>::FindElement(TYPE *pEl)
{
	DBORDINAL	index;

	if (!pEl)
		return -1L;

	for (index = 0; index < GetCount(); index++)
	{
		if (*pEl == m_rgArray[index])
			return (LONG)index;
	}

	return -1L;	// a negative value means not found
} //CVectorEx<TYPE>::FindElement



template <typename TYPE>
TYPE *CVectorEx<TYPE>::operator = (CVectorEx<TYPE> &X)
{
	Free();

	CAllocator::Alloc(X.GetCount(), &m_rgArray);
	for (ULONG i=0; i<X.GetCount(); i++)
	{
		m_rgArray[i] = X[i];
	}
	m_ulArraySize = X.GetCount();

	return m_rgArray;
} //CVectorEx<TYPE>::operator =




template <typename TSet, typename TYPE>
CVectorExSet <TSet, TYPE>::CVectorExSet(
	ULONG	ulASetSizeInc, 
	ULONG	ulSizeInc
)
{
	// alloc the TSet array
	CAllocator::Alloc(cInitMaxArraySize, &m_rgSets);
	// alloc the array of orthogonal arrays
	m_rgSetWrappers	= new CVectorEx<TYPE>[cInitMaxASetSize]; //m_rgASetWrapper;

	m_cSets			= 0;
	m_cMaxSets		= cInitMaxASetSize;
	m_cSetsInc		= ulASetSizeInc;
	m_cDefSetsInc	= ulSizeInc;
} //CVectorExSet <TSet, TYPE>::CVectorExSet



template <typename TSet, typename TYPE>
void CVectorExSet <TSet, TYPE>::Attach(
	ULONG	cSets, 
	TSet	*rgSets
)
{
	Free();
	
	m_rgSets = rgSets;

	// alloc the array of orthogonal arrays
	// can't actually attach the set wrappers to the actual arrays
	// since the memory outlay is unknown
	// this should be done in the derived class, where this info is available
	m_rgSetWrappers	= new CVectorEx<TYPE>[cSets];

	m_cSets			= cSets;
	m_cMaxSets		= cSets;
	m_cSetsInc		= 1;
	m_cDefSetsInc	= 5;
} //CVectorExSet <TSet, TYPE>::Attach



template <typename TSet, typename TYPE>
void CVectorExSet <TSet, TYPE>::Detach()
{
	DBORDINAL	index;

	m_rgSets = NULL;

	for (index = 0; index < m_cSets; index++)
	{
		m_rgSetWrappers[index].Detach();
	}

	delete [] m_rgSetWrappers;
	m_rgSetWrappers = NULL;

	m_cSets			= 0;
	m_cMaxSets		= 0;
	m_cSetsInc		= 1;
	m_cDefSetsInc	= 5;
} //CVectorExSet <TSet, TYPE>::Detach



template <typename TSet, typename TYPE>
void CVectorExSet <TSet, TYPE>::Free()
{
	ULONG	cSets	= m_cSets;
	TSet	*rgSets	= m_rgSets;

	Detach();
	if (m_rgSetWrappers)
		delete [] m_rgSetWrappers;
	m_rgSetWrappers = NULL;
	CAllocator::Free(&cSets, &rgSets);
	m_cMaxSets	= 0;
} //CVectorExSet <TSet, TYPE>::Free




template <typename TSet, typename TYPE>
CVectorExSet <TSet, TYPE>::~CVectorExSet()
{
	Free();
} //CVectorExSet <TSet, TYPE>::~CVectorExSet




template <typename TSet, typename TYPE>
HRESULT	CVectorExSet<TSet, TYPE>::AddSet(TSet *pSet, ULONG *pulSetIndex)
{
	ULONG						ulSetIndex;
	HRESULT						hr				= E_FAIL;
	CVectorEx<TYPE>	*prgASetWrapper	= NULL;

	if (m_cSets >= m_cMaxSets)
	{
		// we must reallocate the memory
		CAllocator::Realloc(m_cMaxSets, &m_rgSets, m_cMaxSets + m_cSetsInc);

		// reallocate objects?
		prgASetWrapper = new CVectorEx<TYPE>[m_cMaxSets + m_cSetsInc];

		for (ulSetIndex = 0; ulSetIndex < m_cMaxSets; ulSetIndex++)
		{
			prgASetWrapper[ulSetIndex].Attach(m_rgSetWrappers[ulSetIndex].GetCount(), m_rgSetWrappers[ulSetIndex].GetElements());
			m_rgSetWrappers[ulSetIndex].Detach();
		}
		// Remember that outside this class, some adjustments must still be made
		delete [] m_rgSetWrappers;
		m_rgSetWrappers = prgASetWrapper;
		m_cMaxSets += m_cSetsInc;
	}

	// take care of the new element
	m_rgSets[m_cSets] = *pSet;

	if (pulSetIndex)
		*pulSetIndex = m_cSets;
	m_cSets++;
	
	hr = S_OK;

	return hr;
} //CVectorExSet<TSet, TYPE>::AddSet

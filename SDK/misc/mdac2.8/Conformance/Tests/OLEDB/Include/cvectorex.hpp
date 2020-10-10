//--------------------------------------------------------------------
// Microsoft OLE DB Test
//
// Copyright 1998-2000 Microsoft Corporation.  
//
// @doc 
//
// @module CVectorEx Header Module | 	This module contains declaration information
//			for the CVectorEx and CVectorExSet classes
//
// @comm
// Special Notes...:	(OPTIONAL NOTES FOR SPECIAL CIRCUMSTANCES)
//
// <nl><nl>
// Revision History:<nl>
//---------------------------------------------------------------------------

// file CVectorEx.hpp
#ifndef	__VECTOREX_HPP__
#define __VECTOREX_HPP__

#include <WTypes.h>
#include <Limits.h>
#include <assert.h>

#include "allocator.hpp"

// Template class for dynamic array
const ULONG cInitMaxArraySize = 3;


template <typename TYPE> 
class CVectorEx
{
	protected:
		TYPE				*m_rgArray;
		ULONG				m_ulArraySize;
		ULONG				m_ulMaxArraySize;
		ULONG				m_ulSizeInc;


	public:

							CVectorEx(ULONG ulSizeInc = 2)
							{
								CAllocator::Alloc(cInitMaxArraySize, &m_rgArray);

								m_ulArraySize		= 0;
								m_ulMaxArraySize	= cInitMaxArraySize;
								m_ulSizeInc			= ulSizeInc;
							}
						
							CVectorEx(ULONG cElements, TYPE *rgElements) 
							{
								Attach(cElements, rgElements);
							}
						

							~CVectorEx(void) {
								Free();
								m_rgArray = NULL;
							}

		void				Free();

		void				Attach(ULONG cElements, TYPE *rgElements);
		void				Detach() {
								m_rgArray			= NULL;
								m_ulArraySize		= 0;
								m_ulMaxArraySize	= 0;
								m_ulSizeInc			= 5;
		}

		ULONG				GetCount() {
								return m_ulArraySize;
		}
		TYPE				*GetElements() {
								return m_rgArray;
		}

		// this method duplicates the element if added twice; this is by design
		HRESULT				AddElement(TYPE *pEl = NULL, ULONG *pIndex = NULL);
		
		// remove the element from array 
		HRESULT				RemoveAt(DBORDINAL index);
		HRESULT				RemoveElement(TYPE *pEl);	// removes the first occurence only
		
		// Seeking methods
		LONG				FindElement(TYPE *pEl);				// Find index of element
		
		TYPE				&operator [](ULONG ulIndex){
								assert(ulIndex < m_ulArraySize);
								return m_rgArray[ulIndex];
		}
		TYPE				*operator = (CVectorEx<TYPE> &X);
}; //CVectorEx



// Template class for dynamic set of orthogonal arrays
const ULONG cInitMaxASetSize = 2;


template <typename TSet, typename TYPE> 
	class CVectorExSet 
{
	protected:
		// an array of TSet classes
		TSet						*m_rgSets;

		// array of CVectorEx<TYPE> classes that corespond to the TSet classes
		CVectorEx<TYPE>				*m_rgSetWrappers;

		ULONG						m_cSets;
		ULONG						m_cMaxSets;
		ULONG						m_cSetsInc;

		// default values
		ULONG						m_cDefSetsInc;
	

	public:

									CVectorExSet(
										ULONG	ulASetSizeInc = 1, 
										ULONG	ulSizeInc = 2);
									CVectorExSet(ULONG cElements, TSet *rgElements) {
										Attach(cElements, rgElements);
									}
									~CVectorExSet();

		void						Free();
		void						Attach(ULONG cElements, TSet *rgElements);
		void						Detach();

		ULONG						GetCount(){
										return m_cSets;
		}
		TSet						*GetElements(){
										return m_rgSets;
		}

		HRESULT						AddSet(TSet *pSet, ULONG *pulSetIndex = NULL);

									operator CVectorEx<TYPE>*() {
										return m_rgSetWrappers;	}
		TSet						&operator [] (ULONG ulIndex) {
										assert (ulIndex<m_cSets);
										return m_rgSets[ulIndex];}
}; //CVectorExSet



#endif //__VECTOREX_HPP__
#pragma once

#define MIN_PROPID 2

class CWiaItem {
public:
    CWiaItem();
    ~CWiaItem();
    HRESULT SetIWiaItem(IWiaItem2 *pIWiaItem);

    void Release();

    HRESULT ReadPropertyLong(PROPID PropertyID, LONG *plPropertyValue);
    HRESULT ReadPropertyGUID(PROPID PropertyID, GUID *pguidPropertyValue);
    HRESULT ReadPropertyBSTR(PROPID PropertyID, BSTR *pbstrPropertyValue);

    HRESULT WritePropertyLong(PROPID PropertyID, LONG lPropertyValue);
    HRESULT WritePropertyGUID(PROPID PropertyID, GUID guidPropertyValue);

private:
    IWiaPropertyStorage *m_pIWiaPropStg;
protected:
};

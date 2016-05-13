// BoxHolder.h: interface for the CBoxHolder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOXHOLDER_H__F92CBD96_CF5C_46E7_AA98_18B94417D654__INCLUDED_)
#define AFX_BOXHOLDER_H__F92CBD96_CF5C_46E7_AA98_18B94417D654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBoxHolder: public CObject
{
	DECLARE_SERIAL(CBoxHolder)
public:
	int GetTop();
	int GetLeft();
	CString ToMathML();
	int GetHeight();
	int GetWidth();
	void Draw(CDC* pDC);
	int GetChildrenCount();
	void DeleteAll();
	void Serialize(CArchive& ar);
	CBox* GetBox(int nIndex);
	void AddBox(CBox* box);
	CBoxHolder();
	virtual ~CBoxHolder();
private:
	CArray<CBox*, CBox*> m_Children;
};

#endif // !defined(AFX_BOXHOLDER_H__F92CBD96_CF5C_46E7_AA98_18B94417D654__INCLUDED_)

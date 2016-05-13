// MSymbol.h: interface for the CMSymbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSYMBOL_H__E16CFF18_43A9_4907_89F9_F62D27D733BC__INCLUDED_)
#define AFX_MSYMBOL_H__E16CFF18_43A9_4907_89F9_F62D27D733BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompositeBox.h"

class CMSymbol : public CCompositeBox  
{
public:
	void Serialize(CArchive& ar);
	CString ToMathML(int nLevel);
	void SetFontSize(int n);
	void SetCoord(int cx, int cy);
	void Draw(CDC* pDC);
	void Layout(CDC* pDC);
	CString ClassName();
	CMSymbol(CBox* box1, CBox* box2=NULL, CBox* box3=NULL, char Symbol=(char)0xAA);
	CMSymbol();
	virtual ~CMSymbol();

private:
	int m_nExtra;
	int m_nHeightSymbol;
	int m_nWidthSymbol;
	int m_nTopSymbol;
	int m_nLeftSymbol;
	char m_SymbolChar;
	int m_nType;
};

#endif // !defined(AFX_MSYMBOL_H__E16CFF18_43A9_4907_89F9_F62D27D733BC__INCLUDED_)

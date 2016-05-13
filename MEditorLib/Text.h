// Text.h: interface for the CText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXT_H__AFBB8C11_AD51_4F92_9E0E_3BEE2A22E62E__INCLUDED_)
#define AFX_TEXT_H__AFBB8C11_AD51_4F92_9E0E_3BEE2A22E62E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Box.h"

class CText : public CBox  
{
public:
	virtual void Serialize(CArchive& ar);
	virtual CBox* Copy();
	int GetChildrenCount();
	virtual void Draw(CDC* pDC);
	virtual void Layout(CDC* pDC);
	void SetData(CString st);
	CString GetData();
	CText();
	virtual ~CText();

private:
	CString m_Data;
protected:
	BOOL	m_bInverted;
	CString m_FontName;
	BYTE	m_CharSet;
	BYTE m_nItalic;
	CString m_strMathML;
	CString m_strLaTeX;
	CString m_strForm;//InFix, PosFix, PreFix
};

#endif // !defined(AFX_TEXT_H__AFBB8C11_AD51_4F92_9E0E_3BEE2A22E62E__INCLUDED_)

// MEntity.h: interface for the CMEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENTITY_H__B4263C41_8D89_4E9B_9A59_DB901BA65A5E__INCLUDED_)
#define AFX_MENTITY_H__B4263C41_8D89_4E9B_9A59_DB901BA65A5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Text.h"

class CMEntity : public CText  
{
public:
	CString Signature();
	void Serialize(CArchive& ar);
	CString ToMathML(int nLevel);
	void SetFontSize(int n);
	CString ClassName();
	void Draw(CDC* pDC);
	void Layout(CDC* pDC);
	CMEntity(unsigned char nCode, CString strFontName, CString strEntity, CString strMathML, CString strLaTeX, BOOL bOperator, BOOL bInverted);
	CMEntity();
	virtual ~CMEntity();
private:
	unsigned char	m_nCharCode;
	CString			m_strEntity;
	CString			m_strLaTeX;
	CString			m_strMathML;
	BOOL			m_bOperator;
};

#endif // !defined(AFX_MENTITY_H__B4263C41_8D89_4E9B_9A59_DB901BA65A5E__INCLUDED_)

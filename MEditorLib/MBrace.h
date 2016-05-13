// MBrace.h: interface for the CMBrace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MBRACE_H__5C3023E4_8612_465C_BFB5_CC5024002E7D__INCLUDED_)
#define AFX_MBRACE_H__5C3023E4_8612_465C_BFB5_CC5024002E7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompositeBox.h"

class CMBrace : public CCompositeBox  
{
public:
	void Serialize(CArchive& ar);
	CString ToMathML(int nLevel);
	CString ClassName();
	void SetCoord(int cx, int cy);
	void Draw(CDC* pDC);
	void Layout(CDC* pDC);
	CMBrace(CBox* box, int nType=0);
	CMBrace();
	virtual ~CMBrace();

private:
	BOOL m_bUseReplace;
	unsigned char m_BraceReplace2;
	unsigned char m_BraceReplace1;
	int m_BraceWidth;
	int GetPenWidth();
	unsigned char m_BraceChar1;//Upper Left
	unsigned char m_BraceChar2;//Middle Left
	unsigned char m_BraceChar3;//Lower Left
	unsigned char m_BraceChar4;//Upper Right
	unsigned char m_BraceChar5;//Midle Right
	unsigned char m_BraceChar6;//Lower Right
	int m_nType;
};

#endif // !defined(AFX_MBRACE_H__5C3023E4_8612_465C_BFB5_CC5024002E7D__INCLUDED_)

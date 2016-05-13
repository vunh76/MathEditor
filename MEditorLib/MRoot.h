// MRoot.h: interface for the CMRoot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MROOT_H__0F198F1A_1F01_40BE_BC94_579929FAEFAB__INCLUDED_)
#define AFX_MROOT_H__0F198F1A_1F01_40BE_BC94_579929FAEFAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompositeBox.h"

class CMRoot : public CCompositeBox  
{
public:
	void Serialize(CArchive& ar);
	CString ClassName();
	CString ToMathML(int nLevel);
	void Draw(CDC* pDC);
	void SetCoord(int cx, int cy);
	void Layout(CDC* pDC);
	void SetFontSize(int n);
	CMRoot(CBox* box1, CBox* box2=NULL);
	CMRoot();
	virtual ~CMRoot();

private:
	int m_rw;
	int m_rh;
	int GetPenWidth();
	int GetGap();
	int m_nType;
};

#endif // !defined(AFX_MROOT_H__0F198F1A_1F01_40BE_BC94_579929FAEFAB__INCLUDED_)

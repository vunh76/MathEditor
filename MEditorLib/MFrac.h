// MFrac.h: interface for the CMFrac class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFRAC_H__CB765E2C_CBF1_467E_A98F_85FC0ADF044B__INCLUDED_)
#define AFX_MFRAC_H__CB765E2C_CBF1_467E_A98F_85FC0ADF044B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompositeBox.h"

class CMFrac : public CCompositeBox  
{
public:
	CString ToMathML(int nLevel);
	void SetCoord(int cx, int cy);
	CString ClassName();
	void Draw(CDC* pDC);
	void Layout(CDC* pDC);
	CMFrac(CBox *box1, CBox *box2);
	CMFrac();
	virtual ~CMFrac();

private:
	int GetGap();
	int GetPenWidth();

};

#endif // !defined(AFX_MFRAC_H__CB765E2C_CBF1_467E_A98F_85FC0ADF044B__INCLUDED_)

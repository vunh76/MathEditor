// MRow.h: interface for the CMRow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MROW_H__D9B10A39_B8D8_481F_ADAF_43DBE26B0AF7__INCLUDED_)
#define AFX_MROW_H__D9B10A39_B8D8_481F_ADAF_43DBE26B0AF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompositeBox.h"

class CMRow : public CCompositeBox  
{
public:
	CString ToMathML(int nLevel);
	void SetCoord(int cx, int cy);
	CString ClassName();
	void Draw(CDC* pDC);
	void Layout(CDC* pDC);
	CMRow(CBox* box1);
	CMRow(CBox* box1, CBox* box2);
	CMRow(CBox* box1, CBox* box2, CBox *box3);
	CMRow();
	virtual ~CMRow();
private:

};

#endif // !defined(AFX_MROW_H__D9B10A39_B8D8_481F_ADAF_43DBE26B0AF7__INCLUDED_)

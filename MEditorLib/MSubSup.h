// MSubSup.h: interface for the CMSubSup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSUBSUP_H__93054310_75E8_4168_83B3_E67978C92F91__INCLUDED_)
#define AFX_MSUBSUP_H__93054310_75E8_4168_83B3_E67978C92F91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompositeBox.h"

class CMSubSup : public CCompositeBox  
{
public:
	void Serialize(CArchive& ar);
	CString ToMathML(int nLevel);
	void SetFontSize(int n);
	void SetCoord(int cx, int cy);
	void Layout(CDC* pDC);
	CString ClassName();
	CMSubSup(CBox* box1, CBox* box2, CBox* box3);
	CMSubSup();
	virtual ~CMSubSup();

private:
	int m_e2;
	int m_e1;
	int m_nType;//3 for full subscript and supscript
				//2 for supscript only
				//1	for subscript only
};

#endif // !defined(AFX_MSUBSUP_H__93054310_75E8_4168_83B3_E67978C92F91__INCLUDED_)

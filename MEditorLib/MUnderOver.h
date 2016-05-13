// CMUnderOver.h: interface for the CMUnderOver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMUnderOver_H__5E769BA2_8F59_45EA_959B_6F53E1122475__INCLUDED_)
#define AFX_CMUnderOver_H__5E769BA2_8F59_45EA_959B_6F53E1122475__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompositeBox.h"

class CMUnderOver : public CCompositeBox  
{
public:
	void Serialize(CArchive& ar);
	CString ToMathML(int nLevel);
	CString ClassName();
	void SetCoord(int cx, int cy);
	void SetFontSize(int n);
	void Layout(CDC* pDC);
	CMUnderOver(CBox* box1, CBox* box2, CBox* box3);
	CMUnderOver();
	virtual ~CMUnderOver();

private:
	int GetGap();
	int m_nType;	//1: Full
					//2: Under
					//3: Over
};

#endif // !defined(AFX_CMUnderOver_H__5E769BA2_8F59_45EA_959B_6F53E1122475__INCLUDED_)

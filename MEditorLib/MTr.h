// MTr.h: interface for the CMTr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MTR_H__DDEAE33A_0CA4_4883_862C_46EA8E34E06B__INCLUDED_)
#define AFX_MTR_H__DDEAE33A_0CA4_4883_862C_46EA8E34E06B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompositeBox.h"

class CMTr : public CCompositeBox  
{
public:
	void SetColSpace(int n);
	int GetColSpace();
	CString ClassName();
	void SetCoord(int cx, int cy);
	CMTr(CBox* box1, CBox* box2, CBox* box3, CBox* box4);
	CMTr(CBox* box1, CBox* box2, CBox* box3);
	CMTr(CBox* box1, CBox* box2);
	CMTr();
	virtual ~CMTr();

private:
	int m_ColSpace;
};

#endif // !defined(AFX_MTR_H__DDEAE33A_0CA4_4883_862C_46EA8E34E06B__INCLUDED_)

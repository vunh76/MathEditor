// MTd.h: interface for the CMTd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MTD_H__905B4658_7C9A_47EF_8621_3CD30D77378D__INCLUDED_)
#define AFX_MTD_H__905B4658_7C9A_47EF_8621_3CD30D77378D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompositeBox.h"

class CMTd : public CCompositeBox  
{
public:
	CString ClassName();
	void SetCoord(int cx, int cy);
	CMTd(CBox* box);
	virtual ~CMTd();

};

#endif // !defined(AFX_MTD_H__905B4658_7C9A_47EF_8621_3CD30D77378D__INCLUDED_)

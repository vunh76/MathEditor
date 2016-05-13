// MI.h: interface for the CMI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MI_H__928E24DE_01B8_4E25_881C_FD97919D589E__INCLUDED_)
#define AFX_MI_H__928E24DE_01B8_4E25_881C_FD97919D589E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Text.h"

class CMI : public CText  
{
public:
	CString ToMathML(int nLevel);
	CString ClassName();
	CMI();
	CMI(CString st);
	virtual ~CMI();

};

#endif // !defined(AFX_MI_H__928E24DE_01B8_4E25_881C_FD97919D589E__INCLUDED_)

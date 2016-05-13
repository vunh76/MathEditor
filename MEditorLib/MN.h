// MN.h: interface for the CMN class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MN_H__B49A2820_6571_4284_B1E7_7772A1BAED59__INCLUDED_)
#define AFX_MN_H__B49A2820_6571_4284_B1E7_7772A1BAED59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Text.h"

class CMN : public CText  
{
public:
	CString ToMathML(int nLevel);
	CString ClassName();
	CMN(CString st);
	CMN();
	virtual ~CMN();

};

#endif // !defined(AFX_MN_H__B49A2820_6571_4284_B1E7_7772A1BAED59__INCLUDED_)

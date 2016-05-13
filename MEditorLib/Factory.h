// Factory.h: interface for the CFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACTORY_H__DC025DF8_C1F2_47FB_A69D_92027584C874__INCLUDED_)
#define AFX_FACTORY_H__DC025DF8_C1F2_47FB_A69D_92027584C874__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFactory  
{
public:
	static CBox* instance(CString ID);
	CFactory();
	virtual ~CFactory();

};

#endif // !defined(AFX_FACTORY_H__DC025DF8_C1F2_47FB_A69D_92027584C874__INCLUDED_)

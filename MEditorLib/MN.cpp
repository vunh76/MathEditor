// MN.cpp: implementation of the CMN class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MN.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMN::CMN(CString st)
{
	SetData(st);
	m_CharSet=DEFAULT_CHARSET;
	m_FontName="Times New Roman";
	m_nItalic=FALSE;

}

CMN::CMN()
{

}

CMN::~CMN()
{

}

CString CMN::ClassName()
{
	return "MN";
}



CString CMN::ToMathML(int nLevel)
{
	CString tab(' ', 2*nLevel);
	return tab + "<mn>" + GetData() + "</mn>";
}




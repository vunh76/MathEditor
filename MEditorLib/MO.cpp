// MO.cpp: implementation of the CMO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MO.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMO::CMO()
{

}

CMO::CMO(CString st, CString MathML, CString LaTeX, CString form)
{
	m_CharSet=SYMBOL_CHARSET;
	m_FontName="Lucida Bright Math Symbol";
	if (MathML=="")
		m_strMathML=st;
	else
		m_strMathML=MathML;
	if (LaTeX=="")
		m_strLaTeX=st;
	else
		m_strLaTeX=LaTeX;

	m_strForm=form;

	if (st=="+")
		SetData(0x21);
	else if (st=="-"){
		SetData(0x23);
		if (MathML=="")
			m_strMathML="&minus;";
	}
	else if (st=="*"){
		SetData(0x25);
		if (MathML=="")
			m_strMathML="&times;";
	}
	else if (st=="=")
		SetData(0x22);
	else if (st=="<"){
		SetData(0x5E);
		m_FontName="Lucida Bright Math Italic";
	}
	else if (st=="<="){
		SetData((char)0xD4);
		m_FontName="Lucida Bright Math Italic";
	}
	else if (st==">"){
		SetData((char)0x60);
		m_FontName="Lucida Bright Math Italic";
	}
	else if (st==">="){
		SetData((char)0xD5);
		m_FontName="Lucida Bright Math Italic";
	}
	else{
		m_FontName="Times New Roman";
		m_CharSet=DEFAULT_CHARSET;
		SetData(st);
	}
	m_nItalic=FALSE;

}

CMO::~CMO()
{

}

void CMO::Layout(CDC *pDC)
{
	if (IsTemplate()){
		m_CharSet=DEFAULT_CHARSET;
		m_FontName="Times New Roman";
		m_nItalic=TRUE;
	}
	CText::Layout(pDC);
	if (!IsTemplate()){
		int w=GetWidth();
		if (GetData().GetLength()==1)
			SetWidth(w+2);
		else
			SetWidth(w+4);
	}
}

void CMO::Draw(CDC *pDC)
{
	if (IsTemplate()){
		m_CharSet=DEFAULT_CHARSET;
		m_FontName="Times New Roman";
		m_nItalic=TRUE;
	}
	CText::Draw(pDC);
}

CString CMO::ClassName()
{
	return "MO";
}


CString CMO::ToMathML(int nLevel)
{
	CString tab(' ', 2*nLevel);
	if (m_strMathML=="(" || m_strMathML==")" || m_strMathML=="[" || m_strMathML=="]" || m_strMathML=="{" || m_strMathML=="}" || m_strMathML=="|")
		return tab + "<mo stretchy=\"false\">" + m_strMathML + "</mo>";
	else
		return tab + "<mo>" + m_strMathML + "</mo>";
}



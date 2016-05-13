// MEntity.cpp: implementation of the CMEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMEntity::CMEntity()
{

}

CMEntity::CMEntity(unsigned char nCode, CString strFontName, CString strEntity, CString strMathML, CString strLaTeX, BOOL bOperator, BOOL bInverted)
{
	SetData((char)nCode);
	m_FontName=strFontName;
	m_bOperator=bOperator;
	m_CharSet=SYMBOL_CHARSET;
	m_nCharCode=nCode;
	m_nItalic=FALSE;
	/*
	if (m_bOperator || bGreekChar)
		m_nItalic=FALSE;
	else
		m_nItalic=TRUE;
	*/
	m_strMathML=strMathML;
	m_strLaTeX=strLaTeX;
	m_bInverted=bInverted;
	m_strEntity=strEntity;
}

CMEntity::~CMEntity()
{

}

void CMEntity::Layout(CDC *pDC)
{
	if (IsTemplate()){
		m_CharSet=DEFAULT_CHARSET;
		m_FontName="Times New Roman";
		m_nItalic=TRUE;
	}
	CText::Layout(pDC);
	if (!IsTemplate() && m_bOperator){//Special Operator
		int w=GetWidth();
		SetWidth(w+2);
	}
}

void CMEntity::Draw(CDC *pDC)
{
	if (IsTemplate()){
		m_CharSet=DEFAULT_CHARSET;
		m_FontName="Times New Roman";
		m_nItalic=TRUE;
	}
	CText::Draw(pDC);

}

CString CMEntity::ClassName()
{
	if (m_bOperator)
		return "MO";
	else
		return "MI";
}

void CMEntity::SetFontSize(int n)
{
	CBox::SetFontSize(n);
}

CString CMEntity::ToMathML(int nLevel)
{
	CString tab(' ', 2*nLevel);
	if (m_bOperator)
		return tab + "<mo>&" + m_strMathML + ";</mo>";
	else
		return tab + "<mi>&" + m_strMathML + ";</mi>";
}

void CMEntity::Serialize(CArchive &ar)
{
	CText::Serialize(ar);
	if (ar.IsStoring()){
		ar << m_bOperator;
		ar << m_nCharCode;
		ar << m_strEntity;
		ar << m_strLaTeX;
		ar << m_strMathML;
	}
	else{
		ar >> m_bOperator;
		ar >> m_nCharCode;
		ar >> m_strEntity;
		ar >> m_strLaTeX;
		ar >> m_strMathML;
	}
}

CString CMEntity::Signature()
{
	return "MEntity";
}

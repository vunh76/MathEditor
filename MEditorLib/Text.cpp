// Text.cpp: implementation of the CText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Text.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CText::CText()
{
	m_CharSet=DEFAULT_CHARSET;
	m_FontName="Times New Roman";
	m_bInverted=FALSE;
	m_strMathML="";
	m_strLaTeX="";
	m_strForm="infix";
}

CText::~CText()
{

}

CString CText::GetData()
{
	return m_Data;
}

void CText::SetData(CString st)
{
	//st.TrimLeft();
	if (st=="")
		SetTemplate(TRUE);
	m_Data=st;
}

void CText::Layout(CDC *pDC)
{
	LOGFONT lf;
	TEXTMETRIC tm;
	CSize sz;
	CFont *pOldFont;
	CFont *pNewFont;
	CString st;
	ZeroMemory(&lf, sizeof(lf));
	strcpy(lf.lfFaceName,m_FontName);
	lf.lfHeight=-MulDiv(GetFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72); 
	lf.lfCharSet=m_CharSet;
	lf.lfItalic=m_nItalic;
	pNewFont=new CFont();
	pNewFont->CreateFontIndirect(&lf);
	pOldFont=pDC->SelectObject(pNewFont);

	pDC->GetTextMetrics(&tm);
	//TRACE("Layout Text: FontSize: %f, Ascent: %d, Height: %d, ClassName: %s\n",GetFontSize(), tm.tmAscent, tm.tmHeight, ClassName());
	SetAscent(tm.tmAscent);
	st=GetData();
	if (IsTemplate()) st="X";
	sz=pDC->GetTextExtent(st);
	SetWidth(sz.cx);
	SetHeight(sz.cy);
	
	pDC->SelectObject(pOldFont);
	pNewFont->DeleteObject();
	delete pNewFont;
	pNewFont=NULL;
}

void CText::Draw(CDC *pDC)
{
	LOGFONT lf;
	CString st;
	CFont *pOldFont;
	CFont *pNewFont;
	int x1, y1, x2, y2;
	CSize sz;
	CPen *pOldPen;
	CPen *pNewPen;
	ZeroMemory(&lf, sizeof(lf));
	strcpy(lf.lfFaceName,m_FontName);
	lf.lfHeight=-MulDiv(GetFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72); 
	lf.lfCharSet=m_CharSet;
	lf.lfItalic=m_nItalic;
	pNewFont=new CFont();
	pNewFont->CreateFontIndirect(&lf);
	pOldFont=pDC->SelectObject(pNewFont);
	
	x1=GetLeft();
	y1=GetTop();
	x2=x1+GetWidth();
	y2=y1+GetHeight();

	CBox* box=GetParent();//Must have
	if (IsSelected()){//Change backcolor and forecolor
		//pDC->FillSolidRect(CRect(x1,y1,x2,y2),RGB(0,0,0));
		pDC->SetTextColor(RGB(255,255,255));
	}
	else{
		//pDC->FillSolidRect(CRect(x1,y1,x2,y2),RGB(255,255,255));
		pDC->SetTextColor(RGB(0,0,0));
	}

	st=GetData();
	st.TrimLeft();
	
	if (!IsTemplate()){
		sz=pDC->GetTextExtent(st);
		x1+=(GetWidth()-sz.cx)/2;
		pDC->TextOut(x1, y1,st);
		//TRACE("Drawing Text: ClassName: %s, x: %d, y: %d, Ascent: %d\n",ClassName(),x1,y1,GetAscent());
	}
	else{
		pNewPen=new CPen(PS_DOT,1,RGB(0,128,128));
		pOldPen=pDC->SelectObject(pNewPen);
		pDC->Rectangle(x1,y1,x2,y2);
		pDC->SelectObject(pOldPen);
		pNewPen->DeleteObject();
		delete pNewPen;
		pNewPen=NULL;
	}
	
	pDC->SelectObject(pOldFont);
	pNewFont->DeleteObject();
	delete pNewFont;
	pNewFont=NULL;

	if (m_bInverted && !IsTemplate()){
		CSize sz;
		strcpy(lf.lfFaceName,"Lucida Bright Math Symbol");		
		lf.lfItalic=FALSE;
		pNewFont=new CFont();
		pNewFont->CreateFontIndirect(&lf);
		pOldFont=pDC->SelectObject(pNewFont);
		sz=pDC->GetTextExtent(0x59);
		x1=GetLeft();
		x1+=(GetWidth()-sz.cx)/2;
		pDC->TextOut(x1,y1,0x59);
		pDC->SelectObject(pOldFont);
		pNewFont->DeleteObject();
		delete pNewFont;
		pNewFont=NULL;
	}
	
}

int CText::GetChildrenCount()
{
	return 0;
}


CBox* CText::Copy()
{
	return NULL;
}

void CText::Serialize(CArchive &ar)
{
	CBox::Serialize(ar);
	if (ar.IsStoring()){
		ar << m_bInverted;
		ar << m_CharSet;
		ar << m_Data;
		ar << m_FontName;
		ar << m_nItalic;
		ar << m_strForm;
		ar << m_strLaTeX;
		ar << m_strMathML;
	}
	else{
		ar >> m_bInverted;
		ar >> m_CharSet;
		ar >> m_Data;
		ar >> m_FontName;
		ar >> m_nItalic;
		ar >> m_strForm;
		ar >> m_strLaTeX;
		ar >> m_strMathML;
	}
}

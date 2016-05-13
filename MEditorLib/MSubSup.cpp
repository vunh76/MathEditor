// MSubSup.cpp: implementation of the CMSubSup class.
// Implementation of class that represent subscript, supscript and sub-sup
// symbol
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSubSup.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//Box1: Base
//Box2: Subscript, bellow
//Box3: Supscript, above
CMSubSup::CMSubSup(CBox* box1, CBox* box2, CBox* box3)
{
	AddBox(box1);//Base
	if (box1 && box2 && box3){//Full Subscript and Supscript
		m_nType=3;
		AddBox(box2);//Subscript
		AddBox(box3);//Supscript
	}
	else if (box1 && box2){//Subscript
		m_nType=1;
		AddBox(box2);
	}
	else if (box1 && box3){//Supscript
		m_nType=2;
		AddBox(box3);
	}

}

CMSubSup::CMSubSup()
{
}

CMSubSup::~CMSubSup()
{

}

CString CMSubSup::ClassName()
{
	return "MSubSup";
}

void CMSubSup::Layout(CDC *pDC)
{
	CCompositeBox::Layout(pDC);
	CBox* box1=NULL;
	CBox* box2=NULL;
	CBox* box3=NULL;
	int mWidth, mHeight, mAscent, l;
	int h1, h2, h3, w1, w2, w3, a1, a2, a3;
//	for (int i=0; i<GetChildrenCount(); i++)
//		GetBox(i)->Layout(pDC);

	LOGFONT lf;
	TEXTMETRIC tm;
	ZeroMemory(&lf, sizeof(lf));
	strcpy(lf.lfFaceName,"Times New Roman");
	lf.lfHeight=-MulDiv(GetFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72); 
	CFont newFont;
	newFont.CreateFontIndirect(&lf);
	CFont *pOldFont=pDC->SelectObject(&newFont);
	pDC->GetTextMetrics(&tm);
	pDC->SelectObject(pOldFont);
	newFont.DeleteObject();

	box1=GetBox(0);
	if (m_nType==3){//Full Subscript and Supscript
		box2=GetBox(1);
		box3=GetBox(2); 
	}
	else if (m_nType==1){//Subscript only
		box2=GetBox(1);
	}
	else if (m_nType==2){//Supscript only
		box3=GetBox(1);
	}
	h1=box1->GetHeight();
	w1=box1->GetWidth();
	a1=box1->GetAscent();
	if (box2){
		h2=box2->GetHeight();
		w2=box2->GetWidth();
		a2=box2->GetAscent();
	}
	else{
		h2=0;
		w2=0;
		a2=0;
	}

	if (box3){
		h3=box3->GetHeight();
		w3=box3->GetWidth();
		a3=box3->GetAscent();
	}
	else{
		h3=0;
		w3=0;
		a3=0;
	}

	mWidth=w1+(w2>w3?w2:w3)+1;

	mHeight=h1;
	mAscent=a1;
	m_e1=tm.tmAscent/2;
	m_e2=tm.tmDescent;
	if (m_e1<h3){
		mHeight+=h3-m_e1;
		mAscent+=h3-m_e1;
	}

	if (box2){
		l=h2-m_e1*3/4-m_e2*3/4;
		if (l>0)
			mHeight+=l;
	}

	SetHeight(mHeight);
	SetWidth(mWidth);
	SetAscent(mAscent);
}

//DEL void CMSubSup::Draw(CDC *pDC)
//DEL {
//DEL 	CCompositeBox::Draw(pDC);
//DEL //	for (int i=0; i<GetChildrenCount(); i++)
//DEL //		GetBox(i)->Draw(pDC);
//DEL }

void CMSubSup::SetCoord(int cx, int cy)
{
	CBox::SetCoord(cx, cy);
	int x, y;
	CBox* box1=NULL;
	CBox* box2=NULL;
	CBox* box3=NULL;
	box1=GetBox(0);
	if (m_nType==3){//Full
		box2=GetBox(1);
		box3=GetBox(2);
	}
	else if (m_nType==1){//Sub
		box2=GetBox(1);
	}
	else if (m_nType==2){//Sup
		box3=GetBox(1);
	}

	box1->SetCoord(cx, cy+GetAscent()-box1->GetAscent());
	
	x=cx+box1->GetWidth()+1;

	if (box3){
		y=box1->GetTop() + m_e1-box3->GetHeight();
		box3->SetCoord(x, y);
	}
	
	if (box2){
		y=cy+GetHeight()-box2->GetHeight();
		box2->SetCoord(x-1, y);
	}	
}


void CMSubSup::SetFontSize(int n)
{
	CBox::SetFontSize(n);
	GetBox(0)->SetFontSize(n);
	int m;
	m=3*n/4;
	if (m<7)
		m=7;
	for (int i=1; i<GetChildrenCount(); i++)
		GetBox(i)->SetFontSize(m);
}


CString CMSubSup::ToMathML(int nLevel)
{
	CString tab(' ', 2*nLevel);
	if (m_nType==2){//Supscript
		return tab + "<msup>\r\n" + GetBox(0)->ToMathML(nLevel+1) + "\r\n" + GetBox(1)->ToMathML(nLevel+1) + "\r\n" + tab + "</msup>";
	}
	else if (m_nType==1){//Subscript
		return tab + "<msub>\r\n" + GetBox(0)->ToMathML(nLevel+1) + "\r\n" + GetBox(1)->ToMathML(nLevel+1) + "\r\n" + tab + "</msub>";
	}
	else
		return tab + "<msubsup>\r\n" + GetBox(0)->ToMathML(nLevel+1) + "\r\n" + GetBox(1)->ToMathML(nLevel+1) + "\r\n" + GetBox(2)->ToMathML(nLevel+1) + "\r\n" + tab + "</msubsup>";
		  
}

void CMSubSup::Serialize(CArchive &ar)
{
	CCompositeBox::Serialize(ar);
	if (ar.IsStoring())
		ar << m_nType;
	else
		ar >> m_nType;
}

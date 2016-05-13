// CMUnderOver.cpp: implementation of the CMUnderOver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MUnderOver.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//Box1: Content box
//Box2: Over box;
//Box3: Under box;
CMUnderOver::CMUnderOver(CBox* box1, CBox* box2, CBox* box3)
{
	if (box1 && box2 && box3){	//Full
		m_nType=1;
		AddBox(box2);
		AddBox(box1);
		AddBox(box3);
	}
	else if (box1 && box2){	//Over
		m_nType=3;
		AddBox(box2);
		AddBox(box1);
	}
	else if (box1 && box3){	//Under
		m_nType=2;
		AddBox(box1);
		AddBox(box3);
	}
}

CMUnderOver::CMUnderOver()
{

}

CMUnderOver::~CMUnderOver()
{

}

void CMUnderOver::Layout(CDC *pDC)
{
	CCompositeBox::Layout(pDC);
	int w, h, a, g;
	
	CBox *box1=NULL;//Content
	CBox *box2=NULL;//Over
	CBox *box;
	if (m_nType==1 || m_nType==3){
		box1=GetBox(1);
		box2=GetBox(0);
	}
	else
		box1=GetBox(0);

	w=0;
	h=0;
	g=GetGap();
	for (int i=0; i<GetChildrenCount(); i++){
		box=GetBox(i);
		//box->Layout(pDC);
		if (box->GetWidth()>w)
			w=box->GetWidth();
		h+=box->GetHeight()+g;
	}
	h-=g;
	if (m_nType==1 || m_nType==3)//Full or over
		a=box1->GetAscent()+g+box2->GetHeight();
	else
		a=box1->GetAscent();

	SetWidth(w);
	SetHeight(h);
	SetAscent(a);
}


void CMUnderOver::SetFontSize(int n)
{
	int k=(int)3*n/4;
	if (k<7)
		k=7;
	CBox *box1=NULL;//Content
	CBox *box2=NULL;//Over
	CBox *box3=NULL;//Under
	if (m_nType==1){
		box1=GetBox(1);
		box2=GetBox(0);
		box3=GetBox(2);
	}
	else if (m_nType==3){
		box1=GetBox(1);
		box2=GetBox(0);
	}
	else{
		box1=GetBox(0);
		box3=GetBox(1);
	}
	box1->SetFontSize(n);
	if (box2)
		box2->SetFontSize(k);
	if (box3)
		box3->SetFontSize(k);
}

int CMUnderOver::GetGap()
{
	int g=(int)GetFontSize()/6;
	if (g==0)
		g=1;
	return g;
}

void CMUnderOver::SetCoord(int cx, int cy)
{
	CCompositeBox::SetCoord(cx, cy);
	CBox *box1=NULL;//Content
	CBox *box2=NULL;//Over
	CBox *box3=NULL;//Under
	int e;
	if (m_nType==1){
		box1=GetBox(1);
		box2=GetBox(0);
		box3=GetBox(2);
	}
	else if (m_nType==3){
		box1=GetBox(1);
		box2=GetBox(0);
	}
	else{
		box1=GetBox(0);
		box3=GetBox(1);
	}
	if (box2){
		e=(GetWidth()-box2->GetWidth())/2;
		box2->SetCoord(cx+e,cy);
	}
	e=(GetWidth()-box1->GetWidth())/2;
	box1->SetCoord(cx+e,cy+GetAscent()-box1->GetAscent());
	if (box3){
		e=(GetWidth()-box3->GetWidth())/2;
		box3->SetCoord(cx+e, box1->GetTop()+box1->GetHeight()+GetGap());
	}
}

CString CMUnderOver::ClassName()
{
	return "CMUnderOver";
}

CString CMUnderOver::ToMathML(int nLevel)
{
	CString tab(' ', 2*nLevel);
	if (m_nType==1)//FULL
		return tab + "<munderover>" + crlf + GetBox(0)->ToMathML(nLevel+1) + crlf + GetBox(1)->ToMathML(nLevel+1) + crlf + GetBox(2)->ToMathML(nLevel+1) + crlf + tab + "</munderover>";
	else if (m_nType==2)//Under
		return tab + "<munder>" + crlf + GetBox(0)->ToMathML(nLevel+1) + crlf + GetBox(1)->ToMathML(nLevel+1) + crlf + tab + "</munder>";
	else
		return tab + "<mover>" + crlf + GetBox(0)->ToMathML(nLevel+1) + crlf + GetBox(1)->ToMathML(nLevel+1) + crlf + tab + "</mover>";
}

void CMUnderOver::Serialize(CArchive &ar)
{
	CCompositeBox::Serialize(ar);
	if (ar.IsStoring())
		ar << m_nType;
	else
		ar >> m_nType;
}

// MRoot.cpp: implementation of the CMRoot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MRoot.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//Box1: Content that is under radical sign
//Box2: Base that above radical sign
CMRoot::CMRoot(CBox* box1, CBox* box2)
{
	m_nType=2;
	if (box2){
		m_nType=1;
		AddBox(box2);
	}
	AddBox(box1);
}

CMRoot::CMRoot()
{

}

CMRoot::~CMRoot()
{

}

void CMRoot::SetFontSize(int n)
{
	CBox::SetFontSize(n);
	int k=(int)n*1/2;
	if (k<7)
		k=7;
	if (m_nType==2)
		GetBox(0)->SetFontSize(n);
	else if (m_nType==1){
		GetBox(0)->SetFontSize(k);
		GetBox(1)->SetFontSize(n);
	}
}

void CMRoot::Layout(CDC *pDC)
{
	CCompositeBox::Layout(pDC);
	CBox* box1=NULL;
	CBox* box2=NULL;
	int h1, h2, w1, w2, a1, a2, riw;
	int w, h, a;
	int k=GetPenWidth();
	int g=GetGap();
	LOGFONT lf;
	CSize sz;
	if (m_nType==1){
		box1=GetBox(1);
		box2=GetBox(0);
	}
	else
		box1=GetBox(0);

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
	
	m_rh=(h1+g+k)/3;//Height of radical sign

	ZeroMemory(&lf, sizeof(lf));
	strcpy(lf.lfFaceName,"Times New Roman");
	lf.lfHeight=-MulDiv(GetFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72); 

	CFont newFont;
	newFont.CreateFontIndirect(&lf);
	CFont *pOldFont=pDC->SelectObject(&newFont);
	sz=pDC->GetTextExtent("W");
	pDC->SelectObject(pOldFont);
	newFont.DeleteObject();
	
	m_rw=sz.cx;//Width of radical sign
	if (m_rw>1.5*m_rh)
		m_rw=1.5*m_rh;

	riw=2*m_rw/3-1-2*k;
	//Calculation width
	if (w2/2>riw)
		w=w2-riw+m_rw+w1-2*k;
	else if (w2/2<2*k)
		w=m_rw+w1;
	else
		w=w2/2-2*k+m_rw+w1;
	//Calculation height
	h=h1+g+k;
	a=a1+g+k;
	int d=(h2+g+m_rh)-h;
	if (d>0){
		h+=d;
		a+=d;
	}
	SetWidth(w+2);
	SetHeight(h);
	SetAscent(a);
}

int CMRoot::GetGap()
{
	int g=GetFontSize()/6;
	if (g==0)
		g=1;
	return g;
}

int CMRoot::GetPenWidth()
{
	int k=GetFontSize()/12;
	if (k==0)
		k=1;
	return k;
}

void CMRoot::SetCoord(int cx, int cy)
{
	CBox::SetCoord(cx, cy);
	int x1, y1, x2, y2;
	//int w1, h1, w2, h2;
	int w2;
	int k=GetPenWidth();
	int g=GetGap();
	int riw=2*m_rw/3-1-2*k;
	CBox* box1=NULL;
	CBox* box2=NULL;
	if (m_nType==1){
		box1=GetBox(1);
		box2=GetBox(0);
	}
	else
		box1=GetBox(0);

	if (box2){
		x2=cx;
		w2=box2->GetWidth();
		y2=cy+GetHeight()-m_rh-g-box2->GetHeight();
		box2->SetCoord(x2,y2);	
		if (w2/2>riw)
			x1=cx+w2-riw-2*k+m_rw;
		else if (w2/2<2*k)
			x1=cx+m_rw;
		else
			x1=cx+w2/2-2*k+m_rw;

	}
	else
		x1=cx+m_rw;
	
	y1=cy+GetAscent()-box1->GetAscent();
	box1->SetCoord(x1+1,y1);
}

void CMRoot::Draw(CDC *pDC)
{
	CCompositeBox::Draw(pDC);
	int x, y;
	int k=GetPenWidth();
	int g=GetGap();
	CPoint pt[10];
	COLORREF cl;
	CBox *box1=NULL;
	CPen newPen;
	if (IsSelected())
		cl=RGB(255,255,255);
	else
		cl=RGB(0,0,0);
	newPen.CreatePen(PS_SOLID,1, cl);
	CPen* pOldPen=pDC->SelectObject(&newPen);

	CBrush *pNewBr=new CBrush(cl);
	CBrush *pOldBr=pDC->SelectObject(pNewBr);
	
	if (m_nType==1)
		box1=GetBox(1);
	else
		box1=GetBox(0);
	x=box1->GetLeft();
	y=box1->GetTop()-g-k+1;

	pt[0].x=x;
	pt[0].y=y;
	
	pt[1].x=pt[0].x+box1->GetWidth();
	pt[1].y=pt[0].y;

	pt[2].x=pt[1].x;
	pt[2].y=pt[1].y+k-1;

	pt[3].x=pt[0].x;
	pt[3].y=pt[2].y;

	pt[4].x=pt[0].x-m_rw/2;
	pt[4].y=pt[0].y+box1->GetHeight()+g;

	pt[5].x=pt[0].x-m_rw+2*k;
	pt[5].y=pt[4].y-m_rh+2*k;

	pt[6].x=pt[0].x-m_rw;
	pt[6].y=pt[5].y+k;

	pt[7].x=pt[6].x;
	pt[7].y=pt[6].y-k;

	pt[8].x=pt[5].x;
	pt[8].y=pt[5].y-2*k;

	pt[9].x=pt[4].x;
	pt[9].y=pt[4].y-2*k;

	pDC->Polygon(pt,10);

	/*
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x1+box1->GetWidth(),y1);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x1-m_rw/2,y1+g+box1->GetHeight());
	x1=x1-m_rw/2;
	y1=y1+g+box1->GetHeight();
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x1-m_rw/2,y1-m_rh);
	*/

	pDC->SelectObject(pOldBr);
	pNewBr->DeleteObject();
	delete pNewBr;

	pDC->SelectObject(pOldPen);
	newPen.DeleteObject();
}


CString CMRoot::ToMathML(int nLevel)
{
	CString tab(' ', 2*nLevel);
	if (GetBox(1)==NULL){//SQRT
		return tab + "<msqrt>" + crlf + GetBox(0)->ToMathML(nLevel+1) + crlf + tab + "</msqrt>";
	}
	else
		return tab + "<mroot>" + crlf + GetBox(0)->ToMathML(nLevel+1) + crlf + GetBox(1)->ToMathML(nLevel+1) + crlf + tab + "</mroot>";
}

CString CMRoot::ClassName()
{
	return "MRoot";
}

void CMRoot::Serialize(CArchive &ar)
{
	CCompositeBox::Serialize(ar);
	if (ar.IsStoring())
		ar << m_nType;
	else
		ar >> m_nType;
}

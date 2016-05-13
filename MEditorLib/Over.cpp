// Over.cpp: implementation of the COver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Over.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//	nType=1 Single line
//	nType=2 Double line
//	nType=3 Vector line
//	nType=4 Hat sign
//	nType=5 Arc sign
CMOver::CMOver(CBox* box, const int nType)
{
	AddBox(box);
	m_nType=nType;
}

CMOver::CMOver()
{
	m_nType=1;
}

CMOver::~CMOver()
{

}

void CMOver::Layout(CDC *pDC)
{
	CCompositeBox::Layout(pDC);
	CBox* box=GetBox(0);
	//box->Layout(pDC);
	int k=GetPenWidth();
	int g=GetGap();
	int e;
	if (k==0)
		k=1;
	SetWidth(box->GetWidth());
	e=g+k;
	if (m_nType>=2) //Double line
		e+=g+k;
	SetHeight(box->GetHeight()+e);
	SetAscent(box->GetAscent()+e);
}

void CMOver::Draw(CDC *pDC)
{
	CCompositeBox::Draw(pDC);
	int x, y;
	CBox* box=GetBox(0);
	CPoint pt[4];
	CPen *pNewPen;
	CPen *pOldPen;
	CBrush *pNewBr;
	CBrush *pOldBrush;

	int k=GetPenWidth();
	int g=GetGap();
	
	x=box->GetLeft();
	y=box->GetTop();
	pNewPen=new CPen(PS_NULL,0, RGB(0,0,0));
	pOldPen=pDC->SelectObject(pNewPen);

	if (IsSelected())
		pNewBr=new CBrush(RGB(255, 255, 255));
	else
		pNewBr=new CBrush(RGB(0, 0, 0));
   pOldBrush = pDC->SelectObject(pNewBr);
	
	if (m_nType<=2){
		pt[0].x=x;
		pt[0].y=y-g-k;
		pt[1].x=pt[0].x+GetWidth();
		pt[1].y=pt[0].y;
		pt[2].x=pt[1].x;
		pt[2].y=pt[1].y+k;
		pt[3].x=pt[0].x;
		pt[3].y=pt[2].y;
		pDC->Polygon(pt, 4);
	}

	if (m_nType==2){
		y-=g+k;
		pt[0].x=x;
		pt[0].y=y-g-k;
		pt[1].x=pt[0].x+GetWidth();
		pt[1].y=pt[0].y;
		pt[2].x=pt[1].x;
		pt[2].y=pt[1].y+k;
		pt[3].x=pt[0].x;
		pt[3].y=pt[2].y;
		pDC->Polygon(pt, 4);
	}

	if (m_nType==3){//Draw arrow sign
		pt[0].x=x;
		pt[0].y=y-g-k;
		pt[1].x=pt[0].x+GetWidth()-2*g-k;
		pt[1].y=pt[0].y;
		pt[2].x=pt[1].x;
		pt[2].y=pt[1].y+k;
		pt[3].x=pt[0].x;
		pt[3].y=pt[2].y;
		pDC->Polygon(pt, 4);

		pt[0].x=x+GetWidth()-3*g-k;
		pt[0].y=y-2*g-k;
		pt[1].x=x+GetWidth();
		pt[1].y=y-g-k/2;
		pt[2].x=pt[0].x;
		pt[2].y=pt[0].y+2*g+k;
		pt[3].x=pt[0].x+g;
		pt[3].y=pt[0].y+g+k/2;
		pDC->Polygon(pt,4);
	}
	if (m_nType==4){//Draw hat sign
		pt[0].x=x;
		pt[0].y=y;
		pt[1].x=x+GetWidth()/2;
		pt[1].y=GetTop();
		pt[2].x=pt[1].x;
		pt[2].y=pt[1].y+g;	
		pDC->Polygon(pt,3);

		pt[0].x=x+GetWidth();
		pt[0].y=y;
		pt[1].x=x+GetWidth()/2;
		pt[1].y=GetTop();
		pt[2].x=pt[1].x;
		pt[2].y=pt[1].y+g;
		pDC->Polygon(pt,3);
	}

	if (m_nType==5){//Draw arc sign. Very difficult for pretty look. How?
		int x1, y1, x2, y2, x3, y3, x4, y4, r;

		r=GetWidth()>GetHeight()?GetWidth():GetHeight();
		x=GetLeft();
		y=GetTop();

		x1=x;
		y1=y;

		x2=x1+GetWidth();
		y2=y1+GetHeight();

		x3=x2;
		y3=y1+g+2*k;

		x4=x;
		y4=y3;
		
		pDC->Chord(x1,y1,x2,y2,x3,y3,x4,y4);
		CBrush *pbr1;
		CBrush *pbr2;
		if (IsSelected())
			pbr1=new CBrush(RGB(0,0,0));
		else
			pbr1=new CBrush(RGB(255,255,255));
		pbr2=pDC->SelectObject(pbr1);
		x1=x;
		y1=y+k;

		x2=x1+GetWidth();
		y2=y1+GetHeight()-k;

		x3=x2;
		y3=y1+g+k;

		x4=x;
		y4=y3;
		pDC->Chord(x1,y1,x2,y2,x3,y3,x4,y4);

		pDC->SelectObject(pbr2);
		pbr1->DeleteObject();
		delete pbr1;
		pbr1=NULL;
	}

	pDC->SelectObject(pOldPen);
	pNewPen->DeleteObject();
	delete pNewPen;
	pNewPen=NULL;

	pDC->SelectObject(pOldBrush);
	pNewBr->DeleteObject();
	delete pNewBr;
	pNewBr=NULL;

}

void CMOver::SetCoord(int cx, int cy)
{
	CBox::SetCoord(cx, cy);
	int k=GetPenWidth();
	int g=GetGap();
	int e;
	e=g+k;
	if (m_nType>=2)
		e+=g+k;
	CBox* box=GetBox(0);
	box->SetCoord(cx, cy+e);
}

CString CMOver::ClassName()
{
	return "MOver";
}

void CMOver::SetType(int n)
{
	m_nType=n;
}

int CMOver::GetType()
{
	return m_nType;
}

int CMOver::GetGap()
{
	int g=GetFontSize()/6;
	if (g==0)
		g=1;
	return g;
}

int CMOver::GetPenWidth()
{
	int k=GetFontSize()/12;
	if (k==0)
		k=1;
	return k;
}

CString CMOver::ToMathML(int nLevel)
{
	CString tab(' ', 2*nLevel);
	if (m_nType==1)//Single line
		return tab + "<mover accent=\"true\">" + crlf + GetBox(0)->ToMathML(nLevel+1) + crlf + tab + "  " + "<mo stretchy=\"true\">&macr;</mo>" + crlf + tab + "</mover>";
	else if (m_nType==2)//Double line
		return tab + "<mover accent=\"true\">" + crlf + tab + "  " + "<mover accent=\"true\">" + crlf + GetBox(0)->ToMathML(nLevel+2) + crlf + tab + "    " + "<mo stretchy=\"true\">&macr;</mo>" + crlf + tab + "  </mover>" + crlf + tab + "  <mo stretchy=\"true\">&macr;</mo>" + crlf + tab + "</mover>";
	else if (m_nType==3)//Vector line
		return tab + "<mover accent=\"true\">" + crlf + GetBox(0)->ToMathML(nLevel+1) + crlf + tab + "  " + "<mo stretchy=\"true\">&xrarr;</mo>" + crlf + tab + "</mover>";
	else if (m_nType==4)//Hat line
		return tab + "<mover accent=\"true\">" + crlf + GetBox(0)->ToMathML(nLevel+1) + crlf + tab + "  " + "<mo stretchy=\"true\">&circ;</mo>" + crlf + tab + "</mover>";
	else //Arc line
		return tab + "<mover accent=\"true\">" + crlf + GetBox(0)->ToMathML(nLevel+1) + crlf + tab + "  " + "<mo stretchy=\"true\">&frown;</mo>" + crlf + tab + "</mover>";
		
}

void CMOver::Serialize(CArchive &ar)
{
	CCompositeBox::Serialize(ar);
	if (ar.IsStoring())
		ar << m_nType;
	else
		ar >> m_nType;
}

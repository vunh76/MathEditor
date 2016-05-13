// MFrac.cpp: implementation of the CMFrac class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MFrac.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMFrac::CMFrac(CBox *box1, CBox *box2)
{
	AddBox(box1);
	AddBox(box2);
}

CMFrac::CMFrac()
{
	
}

CMFrac::~CMFrac()
{
	
}

void CMFrac::Layout(CDC *pDC)
{
	CCompositeBox::Layout(pDC);
	int nMaxWidth;
	int p=GetPenWidth();
	int g=GetGap();
	LOGFONT lf;
	TEXTMETRIC tm;

	CFont *pNewFont;
	CFont *pOldFont;

	CBox* box1;
	CBox* box2;
	box1=GetBox(0); //Numerator
	box2=GetBox(1); //Denominator

	nMaxWidth=box1->GetWidth()>box2->GetWidth()?box1->GetWidth():box2->GetWidth();
		
	//penwidth=1;
	
	SetWidth(nMaxWidth);
	SetHeight(box1->GetHeight()+box2->GetHeight()+2*g+p);

	ZeroMemory(&lf, sizeof(lf));
	strcpy(lf.lfFaceName,"Lucida Bright Math Symbol");
	lf.lfCharSet=SYMBOL_CHARSET;
	lf.lfHeight=-MulDiv(GetFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72);
	lf.lfItalic=FALSE;
	pNewFont=new CFont();
	pNewFont->CreateFontIndirect(&lf);
	pOldFont=pDC->SelectObject(pNewFont);

	pDC->GetTextMetrics(&tm);

	//TRACE("Before set ascent: FontSize: %f, tmAscent: %d, tmHeight: %d\n",GetFontSize(), tm.tmAscent, tm.tmHeight);	
	SetAscent(box1->GetHeight()+g+p/2-1+tm.tmAscent-tm.tmHeight/2);
	//TRACE("Layout Fraction: Ascent= %d, box1->Height: %d, box2->Height: %d\n",GetAscent(), box1->GetHeight(), box2->GetHeight());
	pDC->SelectObject(pOldFont);

	pNewFont->DeleteObject();
	delete pNewFont;
	pNewFont=NULL;
}

void CMFrac::Draw(CDC *pDC)
{
	CCompositeBox::Draw(pDC);
	int nX, nY;
	int p=GetPenWidth();
	int g=GetGap();
	CBox* box1;
	CBox* box2;
	box1=GetBox(0);
	box2=GetBox(1);
	
	nX=GetLeft();
	nY=GetTop()+box1->GetHeight()+g;

	CPoint pt[4];
	COLORREF cl;

	CPen newPen;
	if (IsSelected())
		cl=RGB(255,255,255);
	else
		cl=RGB(0,0,0);
	newPen.CreatePen(PS_NULL,0, cl);
	CPen* pOldPen=pDC->SelectObject(&newPen);

	CBrush NewBr(cl);
	CBrush *pOldBr=pDC->SelectObject(&NewBr);
	pt[0].x=nX;
	pt[0].y=nY;
	pt[1].x=nX+GetWidth();
	pt[1].y=pt[0].y;
	pt[2].x=pt[1].x;
	pt[2].y=pt[1].y+p;
	pt[3].x=pt[2].x-GetWidth();
	pt[3].y=pt[2].y;
	pDC->Polygon(pt, 4);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBr);
	/*
	if (IsSelected()){
		pDC->FillSolidRect(nX,nY,GetWidth(),p,RGB(255,255,255));
		pDC->SetBkColor(RGB(0,0,0));
	}
	else{
		pDC->FillSolidRect(nX,nY,GetWidth(),p,RGB(0,0,0));
		pDC->SetBkColor(RGB(255,255,255));
	}
	*/
}

CString CMFrac::ClassName()
{
	return "MF";
}

void CMFrac::SetCoord(int cx, int cy)
{
	CBox::SetCoord(cx, cy);
	CBox* box1;
	CBox* box2;
	int p=GetPenWidth();
	int g=GetGap();
	//p=1;

	box1=GetBox(0);
	box2=GetBox(1);
	int nMaxWidth=GetWidth();
	box1->SetCoord(cx+(nMaxWidth-box1->GetWidth())/2, cy);
	box2->SetCoord(cx+(nMaxWidth-box2->GetWidth())/2,cy+box1->GetHeight()+2*g+p);
	//TRACE("SetCoord Fraction: box1->Left: %d, box1->Top: %d, box2->Left: %d, box2->Top: %d\n",box1->GetLeft(), box1->GetTop(), box2->GetLeft(), box2->GetTop());
}

//DEL BOOL CMFrac::IsTemplate()
//DEL {
//DEL 	CBox* box1;
//DEL 	CBox* box2;
//DEL 	box1=GetBox(0);
//DEL 	box2=GetBox(1);
//DEL 	if ((!box1) || (!box2))
//DEL 		return TRUE;
//DEL 	return (box1->IsTemplate() && box2->IsTemplate());
//DEL }


int CMFrac::GetPenWidth()
{
	int k=GetFontSize()/12;
	if (k==0)
		k=1;
	return k;
}

int CMFrac::GetGap()
{
	int k=GetFontSize()/6;
	if (k==0)
		k=1;
	return k;
}

CString CMFrac::ToMathML(int nLevel)
{
	CString tab(' ', 2*nLevel);
	return tab + "<mfrac>" + crlf + GetBox(0)->ToMathML(nLevel+1) + crlf + GetBox(1)->ToMathML(nLevel+1) + crlf + tab + "</mfrac>";
}



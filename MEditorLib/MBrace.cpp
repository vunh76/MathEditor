// MBrace.cpp: implementation of the CMBrace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MBrace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//nType value list
//0:	(box)
//1:	[box]
//2:	|box|
//3:	{box}
//4:	(box
//5:	box)
//6:	[box
//7:	box]
//8:	|box
//9:	box|
//10:	{box
//11:	box}
CMBrace::CMBrace(CBox* box, int nType)
{
	m_nType=nType;
	AddBox(box);
	switch (m_nType){
	case 0://(box)
		m_BraceChar1=0;
		m_BraceChar2=0;
		m_BraceChar3=0;

		m_BraceChar4=0;
		m_BraceChar5=0;
		m_BraceChar6=0;

		m_BraceReplace1='(';
		m_BraceReplace2=')';
		break;
	case 1://||
		m_BraceChar1=0;
		m_BraceChar2=0;
		m_BraceChar3=0;

		m_BraceChar4=0;
		m_BraceChar5=0;
		m_BraceChar6=0;

		m_BraceReplace1='|';
		m_BraceReplace2='|';
		break;
	case 2://[box]
		m_BraceChar1=0;
		m_BraceChar2=0;
		m_BraceChar3=0;

		m_BraceChar4=0;
		m_BraceChar5=0;
		m_BraceChar6=0;

		m_BraceReplace1='[';
		m_BraceReplace2=']';
		break;
	case 3://{box}
		m_BraceChar1=0x51;
		m_BraceChar2=0x5D;
		m_BraceChar3=0x61;

		m_BraceChar4=0x52;
		m_BraceChar5=0x5E;
		m_BraceChar6=0x62;

		m_BraceReplace1='{';
		m_BraceReplace2='}';
		break;
	case 4://(box
		m_BraceChar1=0;
		m_BraceChar2=0;
		m_BraceChar3=0;

		m_BraceChar4=0;
		m_BraceChar5=0;
		m_BraceChar6=0;

		m_BraceReplace1='(';
		m_BraceReplace2=0;
		break;
	case 5://|box
		m_BraceChar1=0;
		m_BraceChar2=0;
		m_BraceChar3=0;

		m_BraceChar4=0;
		m_BraceChar5=0;
		m_BraceChar6=0;

		m_BraceReplace1='|';
		m_BraceReplace2=0;
		break;
	case 6://[box
		m_BraceChar1=0;
		m_BraceChar2=0;
		m_BraceChar3=0;

		m_BraceChar4=0;
		m_BraceChar5=0;
		m_BraceChar6=0;

		m_BraceReplace1='[';
		m_BraceReplace2=0;
		break;
	case 7://{box
		m_BraceChar1=0;
		m_BraceChar2=0;
		m_BraceChar3=0;

		m_BraceChar4=0;
		m_BraceChar5=0;
		m_BraceChar6=0;

		m_BraceReplace1='{';
		m_BraceReplace2=0;
		break;
	case 8://box)
		m_BraceChar1=0;
		m_BraceChar2=0;
		m_BraceChar3=0;

		m_BraceChar4=0;
		m_BraceChar5=0;
		m_BraceChar6=0;

		m_BraceReplace1=0;
		m_BraceReplace2=')';
		break;
	case 9://box|
		m_BraceChar1=0;
		m_BraceChar2=0;
		m_BraceChar3=0;

		m_BraceChar4=0;
		m_BraceChar5=0;
		m_BraceChar6=0;

		m_BraceReplace1=0;
		m_BraceReplace2='|';
		break;
	case 10://box]
		m_BraceChar1=0;
		m_BraceChar2=0;
		m_BraceChar3=0;

		m_BraceChar4=0;
		m_BraceChar5=0;
		m_BraceChar6=0;

		m_BraceReplace1=0;
		m_BraceReplace2=']';
		break;
	case 11://box}
		m_BraceChar1=0;
		m_BraceChar2=0;
		m_BraceChar3=0;

		m_BraceChar4=0;
		m_BraceChar5=0;
		m_BraceChar6=0;

		m_BraceReplace1=0;
		m_BraceReplace2='}';
		break;
	}
}

CMBrace::CMBrace()
{

}

CMBrace::~CMBrace()
{

}

void CMBrace::Layout(CDC *pDC)
{
	CCompositeBox::Layout(pDC);
	LOGFONT lf;
	CFont newFont;
	CSize sz1;
	CSize sz2;
	int h, w;
	ZeroMemory(&lf, sizeof(lf));
	strcpy(lf.lfFaceName,"Lucida Math Bright Extension");
	lf.lfHeight=-MulDiv(GetFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72);
	lf.lfCharSet=SYMBOL_CHARSET;
	newFont.CreateFontIndirect(&lf);
	CFont* pOldFont=pDC->SelectObject(&newFont);
	if (m_BraceChar1>0)
		sz1=pDC->GetTextExtent(m_BraceChar1);
	else
		sz1=pDC->GetTextExtent("X");
	pDC->SelectObject(pOldFont);
	newFont.DeleteObject();

	strcpy(lf.lfFaceName,"Times New Roman");
	lf.lfCharSet=DEFAULT_CHARSET;
	newFont.CreateFontIndirect(&lf);
	pOldFont=pDC->SelectObject(&newFont);
	if (m_BraceReplace1>0)
		sz2=pDC->GetTextExtent(m_BraceReplace1);
	else
		sz2=pDC->GetTextExtent(m_BraceReplace2);
	pDC->SelectObject(pOldFont);
	newFont.DeleteObject();

	if ((sz2.cy+1)>=GetBox(0)->GetHeight() && m_nType!=1 && m_nType!=5 && m_nType!=9){
		m_bUseReplace=TRUE;
		h=sz2.cy>GetBox(0)->GetHeight()?sz2.cy:GetBox(0)->GetHeight();
		m_BraceWidth=sz2.cx;
	}
	else{
		m_bUseReplace=FALSE;
		h=GetBox(0)->GetHeight();
		m_BraceWidth=sz1.cx;
		if (m_nType==1)
			m_BraceWidth/=2;
	}
	if (m_nType<4)
		w=2*m_BraceWidth+GetBox(0)->GetWidth();
	else
		w=m_BraceWidth+GetBox(0)->GetWidth();
	
	SetHeight(h);
	SetWidth(w);
	SetAscent(GetBox(0)->GetAscent());
}

void CMBrace::Draw(CDC *pDC)
{
	CCompositeBox::Draw(pDC);
	int x, y, h,w, x1, y1;
	int x0, y0, r;
	int k=GetPenWidth();
	int bl, br;
	
	CFont newFont;
	CFont *pOldFont;
	LOGFONT lf;
	COLORREF cl;
	COLORREF ocl;
	ZeroMemory(&lf, sizeof(lf));
	CBrush brush;
	if (IsSelected()){
		cl=RGB(255,255,255);
	}
	else{
		cl=RGB(0,0,0);
	}
	brush.CreateSolidBrush(cl);

	h=GetHeight();
	w=GetWidth();
	x=GetLeft();
	y=GetTop();
	if (m_bUseReplace){
		strcpy(lf.lfFaceName,"Times New Roman");
		lf.lfHeight=-MulDiv(GetFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72); 
		newFont.CreateFontIndirect(&lf);
		pOldFont=pDC->SelectObject(&newFont);
		ocl=pDC->SetTextColor(cl);
		if (m_nType<=7)
			pDC->TextOut(x,y,m_BraceReplace1);
		if (m_nType<4)
			pDC->TextOut(x+m_BraceWidth+GetBox(0)->GetWidth(),y,m_BraceReplace2);
		else
			if (m_nType>7)
				pDC->TextOut(x+GetBox(0)->GetWidth(),y,m_BraceReplace2);
		pDC->SelectObject(pOldFont);
		newFont.DeleteObject();
		pDC->SetTextColor(ocl);
		return;
	}
	if (m_nType<4){
		bl=m_BraceWidth;
		br=bl;
	}
	else if (m_nType<8){
		bl=m_BraceWidth;
		br=0;
	}
	else{
		bl=0;
		br=m_BraceWidth;
	}
	
	if (m_nType==1 || m_nType==5 || m_nType==9){//||
		if (br>0)
			x1=GetLeft()+w-br/2-k/2;
		if (bl>0)
			x=GetLeft()+bl/2-k/2;
	}
	else if (m_nType==2 || m_nType==6 || m_nType==10){
		if (bl>0)
			x=GetLeft()+k;
		if (br>0)
			x1=GetLeft()+w-2*k;
	}
	
	CBrush *newBrush;
	CBrush *pOldBrush;
	CPen newPen(PS_NULL,0,cl);
	CPen *pOldPen;
	CPoint pt[12];
	pOldPen=pDC->SelectObject(&newPen);
	newBrush=new CBrush(cl);
	pOldBrush=pDC->SelectObject(newBrush);
	if (m_nType==1 || m_nType==2 || m_nType==5 || m_nType==6){//Left of || or []
		pt[0].x=x;
		pt[0].y=y;
		pt[1].x=pt[0].x+k;
		pt[1].y=pt[0].y;
		pt[2].x=pt[1].x;
		pt[2].y=pt[1].y+h;
		pt[3].x=pt[0].x;
		pt[3].y=pt[2].y;
		pDC->Polygon(pt, 4);
		//pDC->FillSolidRect(x,y,k,h, cl);
	}
	if (m_nType==1 || m_nType==2 || m_nType==9 || m_nType==10){//Right of || or []
		pt[0].x=x1;
		pt[0].y=y;
		pt[1].x=pt[0].x+k;
		pt[1].y=pt[0].y;
		pt[2].x=pt[1].x;
		pt[2].y=pt[1].y+h;
		pt[3].x=pt[0].x;
		pt[3].y=pt[2].y;
		pDC->Polygon(pt, 4);
		//pDC->FillSolidRect(x1,y,k,h, cl);
	}
	if (m_nType==2 || m_nType==6){//[]
		pt[0].x=x;
		pt[0].y=y;
		pt[1].x=pt[0].x+m_BraceWidth/2;
		pt[1].y=pt[0].y;
		pt[2].x=pt[1].x;
		pt[2].y=pt[1].y+k;
		pt[3].x=pt[0].x;
		pt[3].y=pt[2].y;
		pDC->Polygon(pt, 4);
		//pDC->FillSolidRect(x,y,m_BraceWidth/2,k, cl);
		pt[0].x=x;
		pt[0].y=y+h-k;
		pt[1].x=pt[0].x+m_BraceWidth/2;
		pt[1].y=pt[0].y;
		pt[2].x=pt[1].x;
		pt[2].y=pt[1].y+k;
		pt[3].x=pt[0].x;
		pt[3].y=pt[2].y;
		pDC->Polygon(pt, 4);
		//pDC->FillSolidRect(x,y+h-k,m_BraceWidth/2,k, cl);
	}

	if (m_nType==2 || m_nType==10){//[]
		pt[0].x=x1-m_BraceWidth/2+k;
		pt[0].y=y;
		pt[1].x=pt[0].x+m_BraceWidth/2-k;
		pt[1].y=pt[0].y;
		pt[2].x=pt[1].x;
		pt[2].y=pt[1].y+k;
		pt[3].x=pt[0].x;
		pt[3].y=pt[2].y;
		pDC->Polygon(pt, 4);
		//pDC->FillSolidRect(x1-m_BraceWidth/2+k,y,m_BraceWidth/2-k,k, cl);
		pt[0].x=x1-m_BraceWidth/2+k;
		pt[0].y=y+h-k;
		pt[1].x=pt[0].x+m_BraceWidth/2-k;
		pt[1].y=pt[0].y;
		pt[2].x=pt[1].x;
		pt[2].y=pt[1].y+k;
		pt[3].x=pt[0].x;
		pt[3].y=pt[2].y;
		pDC->Polygon(pt, 4);
		//pDC->FillSolidRect(x1-m_BraceWidth/2+k,y+h-k,m_BraceWidth/2-k,k, cl);
	}

	pDC->SelectObject(pOldBrush);
	newBrush->DeleteObject();
	delete newBrush;

	CBrush *OuterBr;
	CBrush *pOldOuterBr;
	CBrush *InnerBr;
	
	if (m_nType==0 || m_nType==4 || m_nType==8){//()
		if (IsSelected()){
			OuterBr=new CBrush(RGB(255,255,255));
			InnerBr=new CBrush(RGB(0,0,0));
		}
		else{
			OuterBr=new CBrush(RGB(0,0,0));
			InnerBr=new CBrush(RGB(255,255,255));
		}

		pOldOuterBr=pDC->SelectObject(OuterBr);
		r=m_BraceWidth-4*k;
		//Left brace
		if (m_nType==0 || m_nType==4){
			x0=GetLeft()+2*k+r;
			y0=GetTop()+2*k+r;
	
			pDC->Chord(x0-r-k,y0-r-k,x0+r+k,y0+r+k,x0-k,y0-r-k,x0-r-k,y0);
			x=x0+k;
			y=y0;
			pDC->SelectObject(InnerBr);
			pDC->Chord(x-r-k,y-r-k,x+r+k,y+r+k,x-k,y-r-k,x-r-k,y);

			x=x0-r-k;
			pDC->FillRect(CRect(x,y-k,x+k,y-k+h-2*k-2*r),&brush);

			y1=h-2*k-r+GetTop();
			pDC->SelectObject(OuterBr);
			pDC->Chord(x0-r-k,y1-r-k,x0+r+k,y1+r+k,x0-r-k, y1, x0-k, y1+r+k);
			x=x0+k;
			y=y1;
			pDC->SelectObject(InnerBr);
			pDC->Chord(x-r-k,y-r-k,x+r+k,y+r+k,x-r-k, y, x-k, y+r+k);
		}

		if (m_nType==0 || m_nType==8){
			//Right brace
			x0=GetLeft()+GetWidth()-2*k-r;
			y0=GetTop()+2*k+r;
			pDC->SelectObject(OuterBr);
			pDC->Chord(x0-r-k,y0-r-k,x0+r+k,y0+r+k,x0+r+k,y0,x0+k,y0-r-k);
			x=x0-k;
			y=y0;
			pDC->SelectObject(InnerBr);
			pDC->Chord(x-r-k,y-r-k,x+r+k,y+r+k,x+r+k,y,x+k,y-r-k);

			x=x0+r;
			pDC->FillRect(CRect(x,y-k,x+k,y-k+h-2*k-2*r),&brush);

			y1=h-2*k-r+GetTop();
			pDC->SelectObject(OuterBr);
			pDC->Chord(x0-r-k,y1-r-k,x0+r+k,y1+r+k,x0+k, y1+r+k, x0+r+k, y1);
			x=x0-k;
			y=y1;
			pDC->SelectObject(InnerBr);
			pDC->Chord(x-r-k,y-r-k,x+r+k,y+r+k,x+k, y+r+k, x+r+k, y);
		}
		pDC->SelectObject(pOldOuterBr);
		OuterBr->DeleteObject();
		InnerBr->DeleteObject();
		delete OuterBr;
		delete InnerBr;
	}

	if (m_nType==3 || m_nType==7 || m_nType==11){//{}
		int d;
		if (IsSelected()){
			OuterBr=new CBrush(RGB(255,255,255));
		}
		else{
			OuterBr=new CBrush(RGB(0,0,0));
		}
		pOldOuterBr=pDC->SelectObject(OuterBr);

		r=m_BraceWidth-4*k;
		d=(r-k)/2;
		if (m_nType==3 || m_nType==7){//Left brace
			x0=GetLeft()+2*k+r;
			y0=GetTop();
			pt[0].x=x0;
			pt[0].y=y0;

			pt[1].x=pt[0].x-d-k;
			pt[1].y=pt[0].y+d;

			pt[2].x=pt[1].x;
			pt[2].y=y0+h/2-d;

			pt[3].x=pt[2].x-d;
			pt[3].y=pt[2].y+d;

			pt[4].x=pt[3].x+d;
			pt[4].y=pt[3].y+d;

			pt[5].x=pt[4].x;
			pt[5].y=y0+h-d;

			pt[6].x=pt[5].x+d+k;
			pt[6].y=y0+h;

			pt[7].x=pt[6].x-d;
			pt[7].y=pt[6].y-d-k;

			pt[8].x=pt[7].x;
			pt[8].y=y0+h/2+d-k;

			pt[9].x=pt[8].x-d+k;
			pt[9].y=y0+h/2;

			pt[10].x=pt[7].x;
			pt[10].y=y0+h/2-d+k;

			pt[11].x=pt[10].x;
			pt[11].y=y0+d+k;

			pDC->Polygon(pt,12);
		}
		if (m_nType==3 || m_nType==11){//Right brace
			x0=GetLeft()+GetWidth()-2*k-r;
			y0=GetTop();
			pt[0].x=x0;
			pt[0].y=y0;

			pt[1].x=pt[0].x+d+k;
			pt[1].y=pt[0].y+d;

			pt[2].x=pt[1].x;
			pt[2].y=y0+h/2-d;

			pt[3].x=pt[2].x+d;
			pt[3].y=y0+h/2;

			pt[4].x=pt[2].x;
			pt[4].y=pt[3].y+d;

			pt[5].x=pt[4].x;
			pt[5].y=y0+h-d;

			pt[6].x=pt[0].x;
			pt[6].y=y0+h;

			pt[7].x=pt[6].x+d;
			pt[7].y=pt[6].y-d-k;

			pt[8].x=pt[7].x;
			pt[8].y=y0+h/2+d-k;

			pt[9].x=pt[8].x+d-k;
			pt[9].y=y0+h/2;

			pt[10].x=pt[8].x;
			pt[10].y=y0+h/2-d+k;

			pt[11].x=pt[10].x;
			pt[11].y=y0+d+k;

			pDC->Polygon(pt,12);
		}
	
		pDC->SelectObject(pOldOuterBr);
		OuterBr->DeleteObject();
		delete OuterBr;
	}
	pDC->SelectObject(pOldPen);
	newPen.DeleteObject();

}

void CMBrace::SetCoord(int cx, int cy)
{
	CBox::SetCoord(cx, cy);
	if (m_nType<8)
		GetBox(0)->SetCoord(cx+m_BraceWidth,cy);
	else
		GetBox(0)->SetCoord(cx,cy);
}

int CMBrace::GetPenWidth()
{
	int k=GetFontSize()/12;
	if (k==0)
		k=1;
	return k;
}

CString CMBrace::ClassName()
{
	return "MBrace";
}

CString CMBrace::ToMathML(int nLevel)
{
	CString tab(' ', 2*nLevel);
	CString br1;
	CString br2;
	CString rs;
	switch (m_nType){
	case 0://(box)
		br1="(";
		br2=")";
		break;
	case 1://||
		br1="|";
		br2="|";
		break;
	case 2://[box]
		br1="[";
		br2="]";
		break;
	case 3://{box}
		br1="{";
		br2="}";
		break;
	case 4://(box
		br1="(";
		br2="";
		break;
	case 5://|box
		br1="|";
		br2="";
		break;
	case 6://[box
		br1="[";
		br2="";
		break;
	case 7://{box
		br1="{";
		br2="";
		break;
	case 8://box)
		br1="";
		br2=")";
		break;
	case 9://box|
		br1="";
		br2="|";
		break;
	case 10://box]
		br1="";
		br2="]";
		break;
	case 11://box}
		br1="";
		br2="}";
		break;
	default:
		_ASSERT(FALSE);
		br1="";
		br2="";
		break;
	}
	rs=tab + "<mrow>" + crlf;
	if (br1!="")
		rs+=tab + "  <mo>"+br1+"</mo>" + crlf;
	rs+=GetBox(0)->ToMathML(nLevel+1) + crlf;
	if (br2!="")
		rs+=tab + "  <mo>"+br2+"</mo>" + crlf;
	rs+=tab + "</mrow>";
	return rs;

}

void CMBrace::Serialize(CArchive &ar)
{
	CCompositeBox::Serialize(ar);
	if (ar.IsStoring()){
		ar << m_BraceChar1;
		ar << m_BraceChar2;
		ar << m_BraceChar3;
		ar << m_BraceChar4;
		ar << m_BraceChar5;
		ar << m_BraceChar6;
		ar << m_BraceReplace1;
		ar << m_BraceReplace2;
		ar << m_nType;
	}
	else{
		ar >> m_BraceChar1;
		ar >> m_BraceChar2;
		ar >> m_BraceChar3;
		ar >> m_BraceChar4;
		ar >> m_BraceChar5;
		ar >> m_BraceChar6;
		ar >> m_BraceReplace1;
		ar >> m_BraceReplace2;
		ar >> m_nType;
	}
}

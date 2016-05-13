// MSymbol.cpp: implementation of the CMSymbol class.
// Implemention of class that represent mathematical symbol such as
// sigma, sum, product, integral...	
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//This class implements for rendering sigma, product...
//Box1: Content box
//Box2: Under box
//Box3: Over box
//Symbol: Sigma, Prod, Union...
CMSymbol::CMSymbol(CBox* box1, CBox* box2, CBox* box3, char Symbol)
{
	if (box1 && box2 && box3){
		AddBox(box3);
		AddBox(box2);
		AddBox(box1);
		m_nType=4;//Full Under, Over
	}
	else if (box1 && box2){
		AddBox(box2);
		AddBox(box1);
		m_nType=3;//Under Only
	}
	else if (box1 && box3){
		AddBox(box3);
		AddBox(box1);
		m_nType=2;//Over Only
	}
	else if (box1){
		AddBox(box1);
		m_nType=1;
	}
	m_SymbolChar=Symbol;
}
CMSymbol::CMSymbol()
{

}

CMSymbol::~CMSymbol()
{

}

CString CMSymbol::ClassName()
{
	return "MSymbol";
}

void CMSymbol::Layout(CDC *pDC)
{
	CCompositeBox::Layout(pDC);
	int w;
	int g=0; //gap between boxs
	int h1, h2, h3, h4, as, ds;
	CBox* box1; //Content
	CBox* box2; //Under
	CBox* box3; //Over
	TEXTMETRIC tm;
	CSize sz;
	LOGFONT lf;

	//for (int i=0; i<GetChildrenCount(); i++)
	//	GetBox(i)->Layout(pDC);
	
	if (m_nType==4){ //Full Under/Over
		box1=GetBox(2); 
		box2=GetBox(1);
		box3=GetBox(0);
		if (box2->GetWidth()>box3->GetWidth())
			w=box2->GetWidth();
		else
			w=box3->GetWidth();
		h1=box3->GetHeight();
		h2=box2->GetHeight();
	}
	else if (m_nType==3){//Under only
		box1=GetBox(1);
		box2=GetBox(0);
		box3=NULL;
		w=box2->GetWidth();
		h1=0;
		h2=box2->GetHeight();
	}
	else if (m_nType==2){//Over only
		box1=GetBox(1);
		box3=GetBox(0);
		box2=NULL;
		w=box3->GetWidth();
		h1=box3->GetHeight();
		h2=0;
	}
	else if (m_nType==1){//Content only
		box1=GetBox(0);
		box3=NULL;
		box2=NULL;
		w=0;
		h1=0;
		h2=0;
	}
	
	ZeroMemory(&lf, sizeof(lf));
	strcpy(lf.lfFaceName,"Lucida Bright Math Symbol");
	lf.lfHeight=-MulDiv(GetFontSize()*2, pDC->GetDeviceCaps(LOGPIXELSY), 72); 
	lf.lfCharSet=SYMBOL_CHARSET;
	lf.lfWeight=800;
	CFont *pNewFont=new CFont;
	CFont *pOldFont;
	pNewFont->CreateFontIndirect(&lf);
	pOldFont=pDC->SelectObject(pNewFont);
	sz=pDC->GetTextExtent(m_SymbolChar);
	pDC->SelectObject(pOldFont);
	pNewFont->DeleteObject();
	delete pNewFont;
	pNewFont=NULL;

	pNewFont=new CFont();
	lf.lfHeight=-MulDiv(GetFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72); 
	lf.lfWeight=400;
	pNewFont->CreateFontIndirect(&lf);
	pOldFont=pDC->SelectObject(pNewFont);
	pDC->GetTextMetrics(&tm);
	pDC->SelectObject(pOldFont);
	pNewFont->DeleteObject();
	delete pNewFont;
	pNewFont=NULL;

	m_nWidthSymbol=sz.cx;
	m_nHeightSymbol=sz.cy;

	if (w<sz.cx)
		w=sz.cx;
	w=w+2+box1->GetWidth();
	m_nExtra=tm.tmAscent-tm.tmHeight/2;

	if (h1>0)
		h1+=g+sz.cy/2+m_nExtra;
	else
		h1=sz.cy/2+m_nExtra;
	if (h2>0)
		h2+=g+sz.cy/2-m_nExtra;
	else
		h2=sz.cy/2-m_nExtra;
	
	h3=box1->GetAscent();
	h4=box1->GetDescent();
	if (h3>h1)
		as=h3;
	else
		as=h1;
	if (h4>h2)
		ds=h4;
	else
		ds=h2;

	SetHeight(as+ds);
	SetAscent(as);
	SetWidth(w);
}

void CMSymbol::Draw(CDC *pDC)
{
	CCompositeBox::Draw(pDC);	
	LOGFONT lf;
//	for (int i=0; i<GetChildrenCount(); i++){
//		
//		GetBox(i)->Draw(pDC);
//	}
	

	if (IsSelected()){//Change backcolor and forecolor
		//pDC->FillSolidRect(CRect(x1,y1,x2,y2),RGB(0,0,0));
		pDC->SetTextColor(RGB(255,255,255));
	}
	else{
		//pDC->FillSolidRect(CRect(x1,y1,x2,y2),RGB(255,255,255));
		pDC->SetTextColor(RGB(0,0,0));
	}

	ZeroMemory(&lf, sizeof(lf));
	strcpy(lf.lfFaceName,"Lucida Bright Math Symbol");
	lf.lfHeight=-MulDiv(GetFontSize()*2, pDC->GetDeviceCaps(LOGPIXELSY), 72); 
	lf.lfCharSet=SYMBOL_CHARSET;
	lf.lfWeight=800;
	CFont *pNewFont=new CFont;
	CFont *pOldFont;
	pNewFont->CreateFontIndirect(&lf);
	pOldFont=pDC->SelectObject(pNewFont);
	pDC->TextOut(m_nLeftSymbol, m_nTopSymbol, m_SymbolChar);
	pDC->SelectObject(pOldFont);
	pNewFont->DeleteObject();
	delete pNewFont;
	pNewFont=NULL;
	TRACE("Draw symbol Ascent %d, Left %d, Top %d, Width %d, Height %d\n",GetAscent(), m_nLeftSymbol, m_nTopSymbol, m_nWidthSymbol, m_nHeightSymbol);
	//Debug only
	//pDC->MoveTo(m_nLeftSymbol,m_nTopSymbol+m_nHeightSymbol/2);
	//pDC->LineTo(m_nLeftSymbol+100,m_nTopSymbol+m_nHeightSymbol/2);
}

void CMSymbol::SetCoord(int cx, int cy)
{
	CBox::SetCoord(cx, cy);

	int w;
	int g=0; //gap between boxs
	int h1, h2;
	CBox* box1;//Content
	CBox* box2;//Under
	CBox* box3;//Over
	
	if (m_nType==4){ //Full Under/Over
		box1=GetBox(2); 
		box2=GetBox(1);
		box3=GetBox(0);
		if (box2->GetWidth()>box3->GetWidth())
			w=box2->GetWidth();
		else
			w=box3->GetWidth();
		h1=box3->GetHeight();
		h2=box2->GetHeight();
	}
	else if (m_nType==3){//Under only
		box1=GetBox(1);
		box2=GetBox(0);
		box3=NULL;
		w=box2->GetWidth();
		h1=0;
		h2=box2->GetHeight();
	}

	else if (m_nType==2){//Over only
		box1=GetBox(1);
		box3=GetBox(0);
		box2=NULL;
		w=box3->GetWidth();
		h1=box3->GetHeight();
		h2=0;
	}

	else if (m_nType==1){//Content only
		box1=GetBox(0);
		box3=NULL;
		box2=NULL;
		w=0;
		h1=0;
		h2=0;
	}

	if (w<m_nWidthSymbol)
		w=m_nWidthSymbol;
	
	box1->SetCoord(cx+w+2,cy+GetAscent()-box1->GetAscent());

	if (box2)
		box2->SetCoord(cx+(w-box2->GetWidth())/2,cy+GetAscent()+g+m_nHeightSymbol/2-m_nExtra);
	if (box3)
		box3->SetCoord(cx+(w-box3->GetWidth())/2,cy+GetAscent()-m_nHeightSymbol/2-g-h1-m_nExtra);
	
	m_nLeftSymbol=cx+(w-m_nWidthSymbol)/2;
	m_nTopSymbol=cy+GetAscent()-m_nHeightSymbol/2-m_nExtra;
}

void CMSymbol::SetFontSize(int n)
{
	CBox::SetFontSize(n);
	GetBox(GetChildrenCount()-1)->SetFontSize(n);
	int k=n*3/4;
	if (k<7)
		k=7;
	for (int i=GetChildrenCount()-2; i>=0; i--)
		GetBox(i)->SetFontSize(k);
}

CString CMSymbol::ToMathML(int nLevel)
{
	CString tab(' ', 2*nLevel);
	CString fun;
	CString rs;
	switch (m_SymbolChar){
	case (char)0xAA:
		fun="&sum;";
		break;
	case (char)0xA9:
		fun="&prod;";
		break;
	case (char)0x7E:
		fun="&cup;";
		break;
	case (char)0x80:
		fun="&cap;";
		break;
	case (char)0x97:
		fun="&int;";
		break;
	case (char)0xB0:
		fun="&Int;";
		break;
	case (char)0xB1:
		fun="&tint;";
		break;
	default:
		_ASSERT(FALSE);
		fun="";
		break;
	}
	fun="<mo>" + fun + "</mo>" + crlf;
	if (m_nType==4)//Full
		return tab + "<munderover>" + crlf + tab + "  " + fun + GetBox(1)->ToMathML(nLevel+1) + crlf + GetBox(0)->ToMathML(nLevel+1) + crlf + tab + "</munderover>" + crlf + GetBox(2)->ToMathML(nLevel);
	else if (m_nType==3)//Under Only
		return tab + "<munder>" + crlf + tab + "  " + fun + GetBox(0)->ToMathML(nLevel+1) + crlf + tab + "</munder>" + crlf + GetBox(1)->ToMathML(nLevel);
	else if (m_nType==2)//Over Only
		return tab + "<mover>" + crlf + tab + "  " + fun + GetBox(0)->ToMathML(nLevel+1) + crlf + tab + "</mover>" + crlf + GetBox(1)->ToMathML(nLevel);
	else 
		return tab + fun + crlf + GetBox(0)->ToMathML(nLevel);
}

void CMSymbol::Serialize(CArchive &ar)
{
	CCompositeBox::Serialize(ar);
	if (ar.IsStoring()){
		ar << m_SymbolChar;
		ar << m_nType;
	}
	else{
		ar >> m_SymbolChar;
		ar >> m_nType;
	}
}

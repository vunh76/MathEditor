// MRow.cpp: implementation of the CMRow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MRow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMRow::CMRow(CBox* box1, CBox *box2, CBox *box3)
{
	AddBox(box1);
	AddBox(box2);
	AddBox(box3);
}

CMRow::CMRow(CBox* box1, CBox *box2)
{
	AddBox(box1);
	AddBox(box2);
}

CMRow::CMRow(CBox* box1)
{
	AddBox(box1);
}

CMRow::CMRow()
{
	
}

CMRow::~CMRow()
{
	
}

void CMRow::Layout(CDC *pDC)
{
	CCompositeBox::Layout(pDC);
	int i;
	int nMaxAscent, nMaxDescent, nMaxWidth;
	CBox* box;
	nMaxAscent=0;
	nMaxDescent=0;
	nMaxWidth=0;
	for (i=0; i<GetChildrenCount(); i++){
		box=GetBox(i);
		//box->Layout(pDC);
		//TRACE("Layout Row: Index=%d, Ascent= %d, ClassName: %s\n",i, box->GetAscent(), box->ClassName());
		if (box->GetAscent()>nMaxAscent)
			nMaxAscent=box->GetAscent();
		if (box->GetDescent()>nMaxDescent)
			nMaxDescent=box->GetDescent();
		nMaxWidth+=box->GetWidth();
		//if (i<(GetChildrenCount()-1))
		//	nMaxWidth+=2;

	}
	SetWidth(nMaxWidth);
	SetHeight(nMaxAscent+nMaxDescent);
	SetAscent(nMaxAscent);
}

void CMRow::Draw(CDC *pDC)
{
	CCompositeBox::Draw(pDC);
//	for (int i=0; i<GetChildrenCount(); i++)
//		GetBox(i)->Draw(pDC);
}

CString CMRow::ClassName()
{
	return "MRow";
}

void CMRow::SetCoord(int cx, int cy)
{
	CBox::SetCoord(cx,cy);
	int nWidth;
	CBox* box;
	nWidth=0;
	for (int i=0; i<GetChildrenCount();i++){
		box=GetBox(i);
		box->SetCoord(cx+nWidth,cy+GetAscent()-box->GetAscent());
		//TRACE("SetCoord Rows: Index: %d, Left: %d, Top: %d, ClassName: %s\n", i, box->GetLeft(), box->GetTop(), box->ClassName());
		nWidth+=box->GetWidth();
	}
}


CString CMRow::ToMathML(int nLevel)
{
	int i;
	CString tab(' ', 2*nLevel);
	CString st;
	BOOL bObmit=(GetChildrenCount()==1 && GetBox(0)->ClassName()!="MSymbol");
	if (!bObmit)
		st=tab + "<mrow>" + crlf;
	else
		st="";
	for (i=0; i<GetChildrenCount(); i++)
		if (!bObmit)
			st+=GetBox(i)->ToMathML(nLevel+1) + crlf;
		else
			st+=GetBox(i)->ToMathML(nLevel);
	if (!bObmit)
		st+=tab + "</mrow>";
	return st;
}	



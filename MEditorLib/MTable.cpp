// MTable.cpp: implementation of the CMTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MTable.h"
#include "MI.h"
#include "Mrow.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//This class implement a table. Each table contains few rows. Each row contains few cell
//Each cell is class MTd.
//Each row is class MRow
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//Create a table nRow x nCol
CMTable::CMTable(int nRow, int nCol)
{
	CBox* box;
	int i;
	for (i=0; i<nRow*nCol; i++){
		box=new CMRow(new CMI(""));
		AddBox(box);
	}
	m_RowSpace=-1;
	m_ColWidth.SetSize(nCol);
	m_RowHeight.SetSize(nRow);
	m_RowAscent.SetSize(nRow);
	m_Cols=nCol;
	m_Rows=nRow;
}
CMTable::CMTable()
{
}

CMTable::~CMTable()
{
	m_ColWidth.RemoveAll();
	m_RowHeight.RemoveAll();
	m_RowAscent.RemoveAll();
}

void CMTable::Layout(CDC *pDC)
{
	CCompositeBox::Layout(pDC);
	int h, w, hh, ww, a, d;
	int i, j;
	CBox *box;
	LOGFONT lf;
	CFont newFont;
	CFont *pOldFont;
	CSize sz;
	TEXTMETRIC tm;
	if (m_RowSpace==-1){//Set row spacing to default value
		ZeroMemory(&lf, sizeof(lf));
		strcpy(lf.lfFaceName,"Times New Roman");
		lf.lfHeight=-MulDiv(GetFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72); 
		newFont.CreateFontIndirect(&lf);
		pOldFont=pDC->SelectObject(&newFont);
		sz=pDC->GetTextExtent(" ");
		pDC->SelectObject(pOldFont);
		newFont.DeleteObject();
		
		CBox* box=GetParent();
		CBox* box1=box->GetParent();
		//Neu ma tran dung doc lap
		if (box1==NULL || box1->ClassName()=="MRow"){
			m_RowSpace=sz.cy/1.5;
			m_ColSpace=sz.cx*2;
		}
		else{//Neu ma tran la mot thanh phan cua bieu thuc lon (thay dau enter)
			m_RowSpace=1;
			m_ColSpace=sz.cx;
		}
	}

	strcpy(lf.lfFaceName,"Lucida Bright Math Symbol");
	lf.lfCharSet=SYMBOL_CHARSET;
	lf.lfHeight=-MulDiv(GetFontSize(), pDC->GetDeviceCaps(LOGPIXELSY), 72); 
	newFont.CreateFontIndirect(&lf);
	pOldFont=pDC->SelectObject(&newFont);
	pDC->GetTextMetrics(&tm);
	pDC->SelectObject(pOldFont);
	newFont.DeleteObject();
	
	hh=0;
	for (i=0; i<m_Rows; i++){
		a=0;
		d=0;
		for (j=0; j<m_Cols; j++){
			box=GetCell(i,j);
			if (a<box->GetAscent())
				a=box->GetAscent();
			if (d<box->GetDescent())
				d=box->GetDescent();
		}
		m_RowAscent[i]=a;
		h=a+d;
		m_RowHeight[i]=h;
		hh+=h+m_RowSpace;
	}
	hh-=m_RowSpace;
	ww=0;
	for (j=0; j<m_Cols; j++){
		w=0;
		for (i=0; i<m_Rows; i++){
			box=GetCell(i,j);
			if (w<box->GetWidth())
				w=box->GetWidth();
		}
		m_ColWidth[j]=w;
		ww+=w+m_ColSpace;
	}
	ww-=m_ColSpace;
	SetHeight(hh);
	SetWidth(ww);
	SetAscent(hh/2+tm.tmAscent-tm.tmHeight/2);
}

void CMTable::Draw(CDC *pDC)
{
	CCompositeBox::Draw(pDC);
}

void CMTable::SetCoord(int cx, int cy)
{
	CBox::SetCoord(cx, cy);
	CBox* box;
	int i, j;
	int x0, y0, x, y;
	y0=cy;
	for (i=0; i<m_Rows; i++){
		x0=cx;
		for (j=0; j<m_Cols; j++){
			box=GetCell(i,j);
			y=y0+m_RowAscent[i]-box->GetAscent();
			x=x0+(m_ColWidth[j]-box->GetWidth())/2;
			box->SetCoord(x, y);
			x0+=m_ColWidth[j]+m_ColSpace;
		}
		y0+=m_RowHeight[i]+m_RowSpace;
	}
}

CString CMTable::ClassName()
{
	return "MTable";
}
//Set spacing between rows
void CMTable::SetRowSpace(int n)
{
	m_RowSpace=n;
}
//Get spacing between rows
int CMTable::GetRowSpace()
{
	return m_RowSpace;
}
//Set whether width of all cols are equal
void CMTable::SetColWidthEqual(BOOL b)
{
	m_bEqualColWidth=b;
}
//Get whether width of all cols are equal
BOOL CMTable::GetColWidthEqual()
{
	return m_bEqualColWidth;
}


CBox* CMTable::GetCell(int r, int c)
{
	int k=r*m_Cols+c;
	return GetBox(k);
}

CString CMTable::ToMathML(int nLevel)
{
	CString tab(' ', 2*nLevel);
	CString stab="  ";
	CString st;
	st=tab + "<mtable>" + crlf;
	for (int row=0; row<m_Rows; row++){
		st+=tab + stab + "<mtr>" + crlf;
		for (int col=0; col<m_Cols; col++){
			st+=tab + stab + stab + "<mtd>" + crlf;
			st+=GetCell(row, col)->ToMathML(nLevel+3) + crlf;
			st+=tab + stab + stab + "</mtd>" + crlf;
		}
		st+=tab + stab + "</mtr>" + crlf;
	}
	st+=tab + "</mtable>";
	return st;
}

void CMTable::Serialize(CArchive &ar)
{
	CCompositeBox::Serialize(ar);
	if (ar.IsStoring()){
		ar << m_Cols;
		ar << m_Rows;
		ar << m_RowSpace;
		ar << m_ColSpace;
	}
	else{
		ar >> m_Cols;
		ar >> m_Rows;
		ar >> m_RowSpace;
		ar >> m_ColSpace;
		m_ColWidth.SetSize(m_Cols);
		m_RowHeight.SetSize(m_Rows);
		m_RowAscent.SetSize(m_Rows);
	}
}

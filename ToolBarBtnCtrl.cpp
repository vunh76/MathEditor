/////////////////////////////////////////////////////////////////////////////
//  File:       CToolBarBtnCtrl.cpp
//  Version:    1.0.0.0
//  Created:    15-april-2001
//
//  Author:     Thorsten Wack
//  E-mail:     wt@umsicht.fhg.de
//
//	ToolBarBtnCtrl.cpp : implementation file
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage whatsoever.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "toolbarbtn.h"
#include "toolbarbtnctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PERFORM_MOUSEMOVE

/////////////////////////////////////////////////////////////////////////////
// CToolBarBtnCtrl

CToolBarBtnCtrl::CToolBarBtnCtrl()
{
    RegisterWindowClass();

	m_nRows=7;
	m_nCols=4;

	m_crLine=::GetSysColor(COLOR_3DFACE);
	m_crBkg=::GetSysColor(COLOR_WINDOW);

	m_nHiliteCol=-1;
	m_nHiliteRow=-1;

	m_nSelect=-1;
}

CToolBarBtnCtrl::~CToolBarBtnCtrl()
{
}

// Register the window class if it has not already been registered.
BOOL CToolBarBtnCtrl::RegisterWindowClass()
{
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();

    if (!(::GetClassInfo(hInst, TOOLBARBTNCTRL_CLASSNAME, &wndcls)))
    {
        // otherwise we need to register a new class
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
        wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = TOOLBARBTNCTRL_CLASSNAME;

        if (!AfxRegisterClass(&wndcls))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}

BEGIN_MESSAGE_MAP(CToolBarBtnCtrl, CWnd)
	//{{AFX_MSG_MAP(CToolBarBtnCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarBtnCtrl message handlers

void CToolBarBtnCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	int i, j;

	CPen linePen(PS_SOLID, 1, m_crLine);

	GetClientRect(m_Rect);

	dc.FillSolidRect(m_Rect, GetSysColor(COLOR_WINDOW));
	
	
	IMAGEINFO ImageInfo;
	m_pImageList->GetImageInfo(0, &ImageInfo);

	m_nStepCol=ImageInfo.rcImage.right-ImageInfo.rcImage.left+1;
	m_nStepRow=ImageInfo.rcImage.bottom-ImageInfo.rcImage.top+1;
	
	m_Rect.right=m_Rect.left+m_nCols*m_nStepCol;
	m_Rect.bottom=m_Rect.top+m_nRows*m_nStepRow;

	for (i=0; i<m_nRows; i++)
	{
		for (j=0; j<m_nCols; j++)
		{
			DrawCell(&dc, i, j);
		}
	}

	CPen* pOldPen=dc.SelectObject(&linePen);
	for (i=1; i<m_nCols; i++)
	{
		dc.MoveTo(m_Rect.left + i*m_nStepCol, m_Rect.top);
		dc.LineTo(m_Rect.left + i*m_nStepCol, m_Rect.Height());
	}
	for (j=1; j<m_nRows; j++)
	{
		dc.MoveTo(m_Rect.left, m_Rect.top + j*m_nStepRow);
		dc.LineTo(m_Rect.Width()+1, m_Rect.top + j*m_nStepRow);
	}

	dc.SelectObject(pOldPen);

	linePen.DeleteObject();
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CToolBarBtnCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return CWnd::OnEraseBkgnd(pDC);
}

void CToolBarBtnCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	// In our case this is not needed - yet - so just drop through to
    // the base class
	CWnd::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarBtnCtrl methods

BOOL CToolBarBtnCtrl::Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle /*=WS_VISIBLE*/)
{
	return CWnd::Create(TOOLBARBTNCTRL_CLASSNAME, _T(""), dwStyle, rect, pParentWnd, nID);
}

void CToolBarBtnCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);

#ifdef PERFORM_MOUSEMOVE
	if(m_Rect.PtInRect(point))
	{
		int nOldHiliteRow=m_nHiliteRow;
		int nOldHiliteCol=m_nHiliteCol;

		m_nHiliteCol = point.x/m_nStepCol;
		m_nHiliteRow = point.y/m_nStepRow;

		if(nOldHiliteCol!=m_nHiliteCol || nOldHiliteRow!=m_nHiliteRow)
		{
			CClientDC dc (this);
			
			DrawCell(&dc, nOldHiliteRow, nOldHiliteCol);
			DrawCell(&dc, m_nHiliteRow, m_nHiliteCol);
			
			if(GetCapture()==this)
			{
				int nChar=m_nCols*m_nHiliteRow+m_nHiliteCol;
				CString strOut;
				strOut="0";
				strOut.SetAt(0, nChar);
				CPoint ptWndTip((m_nHiliteCol+1)*m_nStepCol, m_nHiliteRow*m_nStepRow);
				ClientToScreen(&ptWndTip);
			}
		}		
	}
#endif
}

void CToolBarBtnCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);
	
	SetActiveWindow();
	SetCapture();

	if(m_Rect.PtInRect(point))
	{
		int nTempCol = point.x/m_nStepCol;
		int nTempRow = point.y/m_nStepRow;

		int nChar=m_nCols*nTempRow+nTempCol;
		CString strOut;
		strOut="0";
		strOut.SetAt(0, nChar);
		CPoint ptWndTip((nTempCol+1)*m_nStepCol, nTempRow*m_nStepRow);
		ClientToScreen(&ptWndTip);
	}
}

void CToolBarBtnCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonUp(nFlags, point);

	ReleaseCapture();

	if(m_Rect.PtInRect(point))
	{
		int nTempCol = point.x/m_nStepCol;
		int nTempRow = point.y/m_nStepRow;

		int nChar=m_nCols*nTempRow+nTempCol;
		if(nChar<m_pImageList->GetImageCount())
			SetSelection(nChar);
		else
			SetSelection(-1);
	}
	GetParent()->PostMessage(CS_SELECTED);
}

void CToolBarBtnCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int nCol=m_nSelect%m_nCols;
	int nRow=(int)(m_nSelect/m_nCols);

	if (nChar == VK_RIGHT)
	{
		if(++nCol >= m_nCols)
			nCol=0;
		SetSelection(nRow, nCol);
	}
	if (nChar == VK_DOWN)
	{
		if(++nRow >= m_nRows)
			nRow=0;
		SetSelection(nRow, nCol);
	}
	if (nChar == VK_LEFT)
	{
		if(--nCol < 0)
			nCol=m_nCols-1;
		SetSelection(nRow, nCol);
	}
	if (nChar == VK_UP)
	{
		if(--nRow < 0)
			nRow=m_nRows-1;
		SetSelection(nRow, nCol);
	}
	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CToolBarBtnCtrl::PreTranslateMessage(MSG* pMsg) 
{
	if ( pMsg->message == WM_KEYDOWN )
		switch ( (int)pMsg->wParam )
		{
			case VK_RIGHT:
			case VK_LEFT:
			case VK_UP:
			case VK_DOWN:
				// dipatch keyboard messages directly (skip main accelerators)
				::TranslateMessage(pMsg);
				::DispatchMessage(pMsg);
				return TRUE;
		}
	
	return CWnd::PreTranslateMessage(pMsg);
}

void CToolBarBtnCtrl::DrawCell(CDC* pDC, int nRow, int nCol)
{
	CString strOut;
	strOut="0";

	int nChar=m_nCols*nRow+nCol;
	strOut.SetAt(0, nChar);

	CRect rcHilite(m_Rect.left + nCol*m_nStepCol+1, 
				m_Rect.top + nRow*m_nStepRow+1, 
				m_Rect.left + (nCol+1)*m_nStepCol, 
				m_Rect.top + (nRow+1)*m_nStepRow);

	
	
	CPoint point(m_Rect.left+nCol*m_nStepCol+1, m_Rect.top + nRow*m_nStepRow+1);
	pDC->SetBkMode(TRANSPARENT);

	if(nCol==m_nHiliteCol && nRow==m_nHiliteRow)
	{
		pDC->FillSolidRect(rcHilite, ::GetSysColor(COLOR_3DFACE));
	    pDC->DrawEdge(rcHilite, BDR_RAISEDINNER , BF_RECT);
		m_pImageList->Draw(pDC, nChar, point, ILD_SELECTED);
	}
	else
	{
		pDC->FillSolidRect(rcHilite, ::GetSysColor(COLOR_WINDOW));
		m_pImageList->Draw(pDC, nChar, point, ILD_TRANSPARENT);
	}
}

void CToolBarBtnCtrl::DrawCell(CDC* pDC, int nChar)
{
	int nCol=nChar%m_nCols;
	int nRow=(int)(nChar/m_nCols);
	DrawCell(pDC, nRow, nCol);
}

void CToolBarBtnCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	GetParent()->PostMessage(CS_SELECTED);
	CWnd::OnLButtonDblClk(nFlags, point);
}

//Setter and getter - methods
void CToolBarBtnCtrl::SetSelection(int nRow, int nCol)
{
	int nChar=m_nCols*nRow+nCol;
	SetSelection(nChar);
}

void CToolBarBtnCtrl::SetSelection(int nSelect)
{
	int nOldSelect=m_nSelect;
	m_nSelect=nSelect;
	CClientDC dc (this);
	
	if(nOldSelect!=-1)
		DrawCell(&dc, nOldSelect);
	if(m_nSelect!=-1)
		DrawCell(&dc, m_nSelect);
}

void CToolBarBtnCtrl::SetCols(int nCols)
{
	m_nCols=nCols;
	if(m_pImageList->GetImageCount()%m_nCols)
		m_nRows=(int)(m_pImageList->GetImageCount()/m_nCols)+1;
	else
		m_nRows=(int)(m_pImageList->GetImageCount()/m_nCols);
	Invalidate();
}

void CToolBarBtnCtrl::SetColorLine(COLORREF crLine)
{
	m_crLine=crLine;
	Invalidate();
}

void CToolBarBtnCtrl::SetColorBkg(COLORREF crBkg)
{
	m_crBkg=crBkg;
	Invalidate();
}

int CToolBarBtnCtrl::GetCols()
{
	return m_nCols;
}

int CToolBarBtnCtrl::GetRows()
{
	return m_nRows;
}

COLORREF CToolBarBtnCtrl::GetColorLine()
{
	return m_crLine;
}

COLORREF CToolBarBtnCtrl::GetColorBkg()
{
	return m_crBkg;
}

int CToolBarBtnCtrl::GetSelection()
{
	return m_nSelect;
}

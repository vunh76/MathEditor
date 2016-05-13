/////////////////////////////////////////////////////////////////////////////
//  File:       ToolBarBtn.cpp
//  Version:    1.0.0.0
//  Created:    15-april-2001
//
//  Author:     Thorsten Wack
//  E-mail:     wt@umsicht.fhg.de
//
//	ToolBarBtn.cpp : implementation file
//
//  parts of Code by Shekar Narayanan and S. D. Rajan
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarBtn

CToolBarBtn::CToolBarBtn()
{
	m_nCols=4;
	m_pToolBarDlg=NULL;
	m_nSelection=0;
	m_bUseSelection=FALSE;
	m_bMouseOver=FALSE;
}

CToolBarBtn::~CToolBarBtn()
{
	if (m_pToolBarDlg)
	{
		m_pToolBarDlg->DestroyWindow();
		delete m_pToolBarDlg;
		m_pToolBarDlg=NULL;
	}
}

void CToolBarBtn::InitButton(int nCols, UINT nBitmapID, int nImageWidth, COLORREF crMask)
{
	m_nCols=nCols;
	m_ImageList.Create(nBitmapID, nImageWidth, 1, crMask);
}

BEGIN_MESSAGE_MAP(CToolBarBtn, CButton)
	//{{AFX_MSG_MAP(CToolBarBtn)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_MOUSEMOVE()

	//}}AFX_MSG_MAP
    ON_MESSAGE(CS_SELECTED, ToolBarCtrlSelected)
    ON_MESSAGE(CS_ABORTED, ToolBarCtrlAborted)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarBtn message handlers

void CToolBarBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    ASSERT(lpDrawItemStruct);

    CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
    CRect rect=lpDrawItemStruct->rcItem;
    UINT state=lpDrawItemStruct->itemState;
    
    CRect   rArrow(rect);
	rArrow.left=rArrow.right- ::GetSystemMetrics(SM_CXVSCROLL)*3/4;
	if (m_bMouseOver)
		pDC->DrawFrameControl(&rArrow, DFC_SCROLL, DFCS_SCROLLDOWN | 
			                ((state & ODS_SELECTED) ? DFCS_PUSHED : 0 ) |
				              ((state & ODS_DISABLED) ? DFCS_INACTIVE : 0));
	else
		pDC->DrawFrameControl(&rArrow, DFC_SCROLL, DFCS_SCROLLDOWN | DFCS_FLAT |
			                ((state & ODS_SELECTED) ? DFCS_PUSHED : 0 ) |
				              ((state & ODS_DISABLED) ? DFCS_INACTIVE : 0));
 
	rect.right -= rArrow.Width();

    pDC->FillSolidRect(rect,::GetSysColor(COLOR_BTNFACE));

    if  (state & ODS_DISABLED)
        pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
    else
        pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));

	if(m_bUseSelection)
		m_ImageList.Draw(pDC, m_nSelection, CPoint(rect.left+2, rect.top), ILD_NORMAL);
	else	
		m_ImageList.Draw(pDC, 0, CPoint(rect.left+2, rect.top), ILD_NORMAL);

	rect.DeflateRect(2,2);  

    if (state & ODS_FOCUS) 
		pDC->DrawFocusRect(rect);
    
	rect.InflateRect(2,2);
	if (m_bMouseOver)
		pDC->DrawEdge(rect, (state & ODS_DISABLED) ? EDGE_SUNKEN : BDR_RAISEDINNER, BF_RECT);
	else{
		CBrush brBtnShadow(GetSysColor(COLOR_BTNSHADOW));
		pDC->FrameRect(rect, &brBtnShadow);
	}
}

void CToolBarBtn::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
}

void CToolBarBtn::OnClicked() 
{
    CRect rect;
    CRect childRect;
    GetWindowRect(rect);
    rect.OffsetRect(0,rect.Height());

	EnableWindow(FALSE);

	m_pToolBarDlg = new CToolBarDlg(this);
	m_pToolBarDlg->m_ToolBarBtnCtrl.m_pImageList=&m_ImageList;
	m_pToolBarDlg->m_ToolBarBtnCtrl.SetSelection(m_nSelection);

	m_pToolBarDlg->m_ToolBarBtnCtrl.SetCols(m_nCols);
	m_pToolBarDlg->CalculateRect();
	m_pToolBarDlg->GetWindowRect(childRect);
	childRect.OffsetRect(0,rect.Height());

	m_pToolBarDlg->SetWindowPos(NULL,
		childRect.left, 	
		childRect.top, 	
		childRect.Width(), 	
		childRect.Height(), 	
		SWP_SHOWWINDOW | SWP_NOACTIVATE);

    return;
}

LONG CToolBarBtn::ToolBarCtrlSelected(WPARAM wParam , LPARAM lParam)
{
	if(m_pToolBarDlg)
	{
		m_nSelection=m_pToolBarDlg->m_ToolBarBtnCtrl.GetSelection();
		
		m_pToolBarDlg->DestroyWindow();
		delete m_pToolBarDlg;
		m_pToolBarDlg = NULL;
	}
	GetParent()->PostMessage(CS_SELECTED, m_nSelection, GetDlgCtrlID());
	EnableWindow(TRUE);

	Invalidate();
    return 0L;
}

LONG CToolBarBtn::ToolBarCtrlAborted(WPARAM wParam , LPARAM lParam)
{
	GetParent()->PostMessage(CS_ABORTED);
    EnableWindow(TRUE);
	if(m_pToolBarDlg)
	{
		m_pToolBarDlg->DestroyWindow();
		delete m_pToolBarDlg;
		m_pToolBarDlg = NULL;
	}

    return 0L;
}

void CToolBarBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd*				wndUnderMouse = NULL;
	TRACKMOUSEEVENT		csTME;

	CButton::OnMouseMove(nFlags, point);

	ClientToScreen(&point);
	wndUnderMouse = WindowFromPoint(point);

	// If the mouse enter the button with the left button pressed then do nothing
	if (nFlags & MK_LBUTTON) return;

	if (wndUnderMouse && wndUnderMouse->m_hWnd == m_hWnd)
	{
		if (!m_bMouseOver)
		{
			m_bMouseOver = TRUE;
			Invalidate();

			csTME.cbSize = sizeof(csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = m_hWnd;
			::_TrackMouseEvent(&csTME);
		} 
	} else CancelHover();
}

void CToolBarBtn::CancelHover()
{
	if (m_bMouseOver)
	{
		m_bMouseOver = FALSE;
		Invalidate();
	} // if
}

LRESULT CToolBarBtn::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	CancelHover();
	return 0;
} 
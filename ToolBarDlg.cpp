/////////////////////////////////////////////////////////////////////////////
//  File:       ToolBarDlg.cpp
//  Version:    1.0.0.0
//  Created:    15-april-2001
//
//  Author:     Thorsten Wack
//  E-mail:     wt@umsicht.fhg.de
//
//	CToolBarDlg.cpp : implementation file
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
#include "ToolBarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarDlg dialog

CToolBarDlg::CToolBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolBarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolBarDlg)
	//}}AFX_DATA_INIT
	m_pParent=pParent;
	Create(CToolBarDlg::IDD, pParent);
}

void CToolBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolBarDlg)
    DDX_Control(pDX, IDC_CHARSETCTRL, m_ToolBarBtnCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CToolBarDlg, CDialog)
	//{{AFX_MSG_MAP(CToolBarDlg)
	//}}AFX_MSG_MAP
    ON_MESSAGE(CS_SELECTED, CharSetCtrlSelected)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarDlg message handlers

WNDPROC CToolBarDlg::m_MFCWndProc = NULL;
CToolBarDlg* CToolBarDlg::m_pDialog = NULL;


BOOL CToolBarDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Change of the default window procedure
	WNDPROC temp = reinterpret_cast<WNDPROC>(
		::SetWindowLong(GetSafeHwnd(), 
					GWL_WNDPROC, 
					reinterpret_cast<long>(NewWndProc) ));
	if ( !m_MFCWndProc ) 
		m_MFCWndProc = temp;
	m_pDialog = this;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CToolBarDlg::CalculateRect()
{
	CRect rect;
	GetWindowRect(&rect);
	int nImages=m_ToolBarBtnCtrl.m_pImageList->GetImageCount();
	IMAGEINFO ImageInfo;
	m_ToolBarBtnCtrl.m_pImageList->GetImageInfo(0, &ImageInfo);
	rect.right=rect.left+
				((ImageInfo.rcImage.right-ImageInfo.rcImage.left)+1)
				*m_ToolBarBtnCtrl.GetCols()+2;
	rect.bottom=rect.top+
				((ImageInfo.rcImage.bottom-ImageInfo.rcImage.top)+1)
				*m_ToolBarBtnCtrl.GetRows()+2;

	MoveWindow(rect, TRUE);
	m_ToolBarBtnCtrl.MoveWindow(CRect(0,0,rect.Width(), rect.Height()), TRUE);
}

BOOL CToolBarDlg::PreTranslateMessage(MSG* pMsg) 
{
	// Different management of the WM_KEYDOWN msg when is pressed the ENTER button
	// (the default management closes the dialog) or the ESC (we want to close the
	// dialog)
	if ( pMsg->message == WM_KEYDOWN )
		switch ( (int)pMsg->wParam )
		{
			case VK_RETURN:
				m_pDialog->m_pParent->PostMessage( CS_SELECTED );
				return TRUE;
			case VK_ESCAPE:
				m_pDialog->m_pParent->PostMessage( CS_ABORTED );
				return TRUE;
		}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CToolBarDlg::OnClose() 
{
	m_pDialog->m_pParent->PostMessage( CS_ABORTED );
	CDialog::OnClose();
}

LRESULT CALLBACK CToolBarDlg::NewWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// The new window procedure manages only the dialog inactivate;
	// the other msg are managed by default window procedure
	if ( message == WM_ACTIVATE )
	{
		if ( wParam == 0 )
		{
			m_pDialog->m_pParent->PostMessage( CS_ABORTED );
			return FALSE;
		}

	}
	return ::CallWindowProc( m_MFCWndProc, hWnd, message, wParam, lParam );
}

LONG CToolBarDlg::CharSetCtrlSelected(WPARAM wParam , LPARAM lParam)
{
	m_pDialog->m_pParent->PostMessage(CS_SELECTED);
    return 0L;
}

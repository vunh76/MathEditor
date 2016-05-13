/////////////////////////////////////////////////////////////////////////////
//  File:       ToolBarDlg.h
//  Version:    1.0.0.0
//  Created:    15-april-2001
//
//  Author:     Thorsten Wack
//  E-mail:     wt@umsicht.fhg.de
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

#if !defined(_TOOLBARDLG_H__INCLUDED_)
#define _TOOLBARDLG_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CToolBarDlg dialog

#include "resource.h"
#include "toolbarbtnctrl.h"

#define CS_SELECTED	WM_USER + 50
#define CS_ABORTED	WM_USER + 51

class CToolBarDlg : public CDialog
{
// Construction
public:
	CToolBarDlg(CWnd* pParent = NULL);   // standard constructor
	void CalculateRect();

// Dialog Data
	//{{AFX_DATA(CToolBarDlg)
	enum { IDD = IDD_TOOLBAR_POPUP };
    CToolBarBtnCtrl	m_ToolBarBtnCtrl;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd* m_pParent;// Parent of the dialog
	static WNDPROC m_MFCWndProc;// Pointer to the default MFC window procedure
	static CToolBarDlg* m_pDialog;// Pointer to the active instance of the dialog

	// New window procedure of the dialog
	static LRESULT CALLBACK NewWndProc( HWND, UINT, WPARAM, LPARAM );

	// Generated message map functions
	//{{AFX_MSG(CToolBarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
    afx_msg LONG CharSetCtrlSelected(WPARAM wParam = 0, LPARAM lParam = 0);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_TOOLBARDLG_H__INCLUDED_)

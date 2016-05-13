/////////////////////////////////////////////////////////////////////////////
//  File:       ToolBarBtn.h
//  Version:    1.0.0.0
//  Created:    15-april-2001
//
//  Author:     Thorsten Wack
//  E-mail:     wt@umsicht.fhg.de
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

#if !defined(_TOOLBARBTN_H__INCLUDED_)
#define _TOOLBARBTN_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CToolBarBtn 

#include "toolbardlg.h"
class CToolBarBtn : public CButton
{
// Construction
public:
	CToolBarBtn();
	CImageList m_ImageList;
// Attributes
public:
	CToolBarDlg* m_pToolBarDlg;
	int m_nCols;
	int m_nSelection;
	int m_bUseSelection;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarBtn)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolBarBtn();
	void InitButton(int nCols, UINT nBitmapID, int ImageWidth, COLORREF crMask);

// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarBtn)
	afx_msg void OnClicked();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
    afx_msg LONG ToolBarCtrlSelected(WPARAM wParam = 0, LPARAM lParam = 0);
    afx_msg LONG ToolBarCtrlAborted (WPARAM wParam = 0, LPARAM lParam = 0);

	DECLARE_MESSAGE_MAP()
private:
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	void CancelHover();
	BOOL m_bMouseOver;
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_TOOLBARBTN_H__INCLUDED_)

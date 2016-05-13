/////////////////////////////////////////////////////////////////////////////
//  File:       ToolBarBtnCtrl.h
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

#if !defined(_TOOLBARBTNCTRL_H__INCLUDED_)
#define _TOOLBARBTNCTRL_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CToolBarBtnCtrl window

#define TOOLBARBTNCTRL_CLASSNAME    _T("MFCToolBarBtnCtrl")  // Window class name

class CToolBarBtnCtrl : public CWnd
{
// Construction
public:
	CToolBarBtnCtrl();
	CImageList* m_pImageList;
// Attributes
protected:
	int m_nRows;
	int m_nCols;

	COLORREF m_crLine;
	COLORREF m_crBkg;

	CRect m_Rect;
	int m_nStepCol;
	int m_nStepRow;

	int m_nHiliteCol;
	int m_nHiliteRow;
	int m_nSelect;

// Operations
public:
	BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle = WS_VISIBLE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarBtnCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

public:
	void SetCols(int nCols);

	void SetColorBkg(COLORREF crLine);
	void SetColorLine(COLORREF crBkg);

	void SetSelection(int nSelect);
	void SetSelection(int nRow, int nCol);

	int GetCols();
	int GetRows();

	COLORREF GetColorLine();
	COLORREF GetColorBkg();

	int GetSelection();
// Implementation
public:
	virtual ~CToolBarBtnCtrl();
protected:
    BOOL RegisterWindowClass();

	void DrawCell(CDC*, int, int);
	void DrawCell(CDC*, int);
	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarBtnCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_CTOOLBARBTNCTRL_H__INCLUDED_)

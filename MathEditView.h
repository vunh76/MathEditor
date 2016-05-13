// MathEditView.h : interface of the CMathEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHEDITVIEW_H__56FA8C9C_AEA2_4991_9125_975C579B29F4__INCLUDED_)
#define AFX_MATHEDITVIEW_H__56FA8C9C_AEA2_4991_9125_975C579B29F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MEditorLib/box.h"
#include "MEditorLib/cursor.h"

#define IsSHIFTpressed() ( (GetKeyState(VK_SHIFT) & (1 << (sizeof(SHORT)*8-1))) != 0   )

class CMathEditView : public CView
{
protected: // create from serialization only
	CMathEditView();
	DECLARE_DYNCREATE(CMathEditView)

// Attributes
public:
	CMathEditDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathEditView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMathEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMathEditView)
	afx_msg void OnShoweditor();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

#ifndef _DEBUG  // debug version in MathEditView.cpp
inline CMathEditDoc* CMathEditView::GetDocument()
   { return (CMathEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHEDITVIEW_H__56FA8C9C_AEA2_4991_9125_975C579B29F4__INCLUDED_)

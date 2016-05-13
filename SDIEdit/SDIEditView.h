// SDIEditView.h : interface of the CSDIEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDIEDITVIEW_H__404FA113_4BE1_47DE_B8E1_25221BBADA05__INCLUDED_)
#define AFX_SDIEDITVIEW_H__404FA113_4BE1_47DE_B8E1_25221BBADA05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MEditorLib/EditorCtrl.h"

class CSDIEditView : public CView
{
protected: // create from serialization only
	CSDIEditView();
	DECLARE_DYNCREATE(CSDIEditView)

// Attributes
public:
	CSDIEditDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIEditView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSDIEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSDIEditView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CEditorCtrl m_Editor;
};

#ifndef _DEBUG  // debug version in SDIEditView.cpp
inline CSDIEditDoc* CSDIEditView::GetDocument()
   { return (CSDIEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIEDITVIEW_H__404FA113_4BE1_47DE_B8E1_25221BBADA05__INCLUDED_)

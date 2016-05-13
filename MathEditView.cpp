// MathEditView.cpp : implementation of the CMathEditView class
//

#include "stdafx.h"
#include "MathEdit.h"

#include "MathEditDoc.h"
#include "MathEditView.h"
#include "MEditorLib/common.h"
#include "EditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMathEditView

IMPLEMENT_DYNCREATE(CMathEditView, CView)

BEGIN_MESSAGE_MAP(CMathEditView, CView)
	//{{AFX_MSG_MAP(CMathEditView)
	ON_COMMAND(IDM_SHOWEDITOR, OnShoweditor)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMathEditView construction/destruction

CMathEditView::CMathEditView()
{
	// TODO: add construction code here

}

CMathEditView::~CMathEditView()
{
}

BOOL CMathEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMathEditView drawing

void CMathEditView::OnDraw(CDC* pDC)
{
	CMathEditDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
	pDC->TextOut(10,10,"Choose Edit -> Show Editor or double click on screen to popup formular editor");
}

/////////////////////////////////////////////////////////////////////////////
// CMathEditView printing

BOOL CMathEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMathEditView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMathEditView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMathEditView diagnostics

#ifdef _DEBUG
void CMathEditView::AssertValid() const
{
	CView::AssertValid();
}

void CMathEditView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMathEditDoc* CMathEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMathEditDoc)));
	return (CMathEditDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMathEditView message handlers


void CMathEditView::OnShoweditor() 
{
	// TODO: Add your command handler code here
	CEditorDlg dlg;
	dlg.DoModal();
}

void CMathEditView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OnShoweditor();
	CView::OnLButtonDblClk(nFlags, point);
}

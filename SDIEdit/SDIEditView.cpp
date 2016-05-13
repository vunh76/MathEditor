// SDIEditView.cpp : implementation of the CSDIEditView class
//

#include "stdafx.h"
#include "SDIEdit.h"

#include "SDIEditDoc.h"
#include "SDIEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDIEditView

IMPLEMENT_DYNCREATE(CSDIEditView, CView)

BEGIN_MESSAGE_MAP(CSDIEditView, CView)
	//{{AFX_MSG_MAP(CSDIEditView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDIEditView construction/destruction

CSDIEditView::CSDIEditView()
{
	// TODO: add construction code here

}

CSDIEditView::~CSDIEditView()
{
}

BOOL CSDIEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSDIEditView drawing

void CSDIEditView::OnDraw(CDC* pDC)
{
	CSDIEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSDIEditView printing

BOOL CSDIEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSDIEditView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSDIEditView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSDIEditView diagnostics

#ifdef _DEBUG
void CSDIEditView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIEditView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIEditDoc* CSDIEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIEditDoc)));
	return (CSDIEditDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDIEditView message handlers

void CSDIEditView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_Editor.Create(CRect(0,0,0,0), this, IDC_MATHEDITOR);

}

void CSDIEditView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_Editor.GetSafeHwnd())
		m_Editor.MoveWindow(0,0,cx,cy);
}

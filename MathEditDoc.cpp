// MathEditDoc.cpp : implementation of the CMathEditDoc class
//

#include "stdafx.h"
#include "MathEdit.h"

#include "MathEditDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMathEditDoc

IMPLEMENT_DYNCREATE(CMathEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CMathEditDoc, CDocument)
	//{{AFX_MSG_MAP(CMathEditDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMathEditDoc construction/destruction

CMathEditDoc::CMathEditDoc()
{
	// TODO: add one-time construction code here

}

CMathEditDoc::~CMathEditDoc()
{
}

BOOL CMathEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMathEditDoc serialization

void CMathEditDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMathEditDoc diagnostics

#ifdef _DEBUG
void CMathEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMathEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMathEditDoc commands

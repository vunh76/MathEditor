// SDIEditDoc.cpp : implementation of the CSDIEditDoc class
//

#include "stdafx.h"
#include "SDIEdit.h"

#include "SDIEditDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDIEditDoc

IMPLEMENT_DYNCREATE(CSDIEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDIEditDoc, CDocument)
	//{{AFX_MSG_MAP(CSDIEditDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDIEditDoc construction/destruction

CSDIEditDoc::CSDIEditDoc()
{
	// TODO: add one-time construction code here

}

CSDIEditDoc::~CSDIEditDoc()
{
}

BOOL CSDIEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSDIEditDoc serialization

void CSDIEditDoc::Serialize(CArchive& ar)
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
// CSDIEditDoc diagnostics

#ifdef _DEBUG
void CSDIEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDIEditDoc commands

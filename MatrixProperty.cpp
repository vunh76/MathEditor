// MatrixProperty.cpp : implementation file
//

#include "stdafx.h"
#include "MathEdit.h"
#include "MatrixProperty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatrixProperty dialog


CMatrixProperty::CMatrixProperty(CWnd* pParent /*=NULL*/)
	: CDialog(CMatrixProperty::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatrixProperty)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMatrixProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatrixProperty)
	DDX_Control(pDX, IDC_NUM_ROWS, m_Cols);
	DDX_Control(pDX, IDC_NUM_COLS, m_Rows);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatrixProperty, CDialog)
	//{{AFX_MSG_MAP(CMatrixProperty)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatrixProperty message handlers

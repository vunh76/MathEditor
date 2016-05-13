// MaxtrixProperty.cpp : implementation file
//

#include "stdafx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaxtrixProperty dialog


CMaxtrixProperty::CMaxtrixProperty(CWnd* pParent /*=NULL*/)
	: CDialog(CMaxtrixProperty::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMaxtrixProperty)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMaxtrixProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaxtrixProperty)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaxtrixProperty, CDialog)
	//{{AFX_MSG_MAP(CMaxtrixProperty)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaxtrixProperty message handlers

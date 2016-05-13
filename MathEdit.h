// MathEdit.h : main header file for the MATHEDIT application
//

#if !defined(AFX_MATHEDIT_H__FCD76401_3E45_4AF7_B28B_E1CA0628D639__INCLUDED_)
#define AFX_MATHEDIT_H__FCD76401_3E45_4AF7_B28B_E1CA0628D639__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMathEditApp:
// See MathEdit.cpp for the implementation of this class
//

class CMathEditApp : public CWinApp
{
public:
	CMathEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMathEditApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHEDIT_H__FCD76401_3E45_4AF7_B28B_E1CA0628D639__INCLUDED_)

#if !defined(AFX_MAXTRIXPROPERTY_H__01B3D531_E157_455A_A965_094FD2CC6CFF__INCLUDED_)
#define AFX_MAXTRIXPROPERTY_H__01B3D531_E157_455A_A965_094FD2CC6CFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaxtrixProperty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaxtrixProperty dialog

class CMaxtrixProperty : public CDialog
{
// Construction
public:
	CMaxtrixProperty(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMaxtrixProperty)
	enum { IDD = IDD_MATRIX_PROPERTY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaxtrixProperty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMaxtrixProperty)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAXTRIXPROPERTY_H__01B3D531_E157_455A_A965_094FD2CC6CFF__INCLUDED_)

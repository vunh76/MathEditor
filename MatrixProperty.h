#if !defined(AFX_MATRIXPROPERTY_H__93101E2C_400F_4656_B5DD_F4C017E10F34__INCLUDED_)
#define AFX_MATRIXPROPERTY_H__93101E2C_400F_4656_B5DD_F4C017E10F34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatrixProperty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatrixProperty dialog

class CMatrixProperty : public CDialog
{
// Construction
public:
	CMatrixProperty(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMatrixProperty)
	enum { IDD = IDD_MATRIX };
	CEdit	m_Cols;
	CEdit	m_Rows;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatrixProperty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatrixProperty)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATRIXPROPERTY_H__93101E2C_400F_4656_B5DD_F4C017E10F34__INCLUDED_)

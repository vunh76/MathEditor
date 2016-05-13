#if !defined(AFX_EDITORDLG_H__40341080_170D_4179_AA07_14B9937173D7__INCLUDED_)
#define AFX_EDITORDLG_H__40341080_170D_4179_AA07_14B9937173D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditorDlg.h : header file
//
#include "MEditorLib/EditorCtrl.h"
#include "ToolBarBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CEditorDlg dialog

class CEditorDlg : public CDialog
{
// Construction
public:
	CEditorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditorDlg)
	enum { IDD = IDD_EDITORDLG };
	CComboBox	m_FontSizeList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditorDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg LONG ToolBarCtrlSelected(WPARAM wParam = 0, LPARAM lParam = 0);
	afx_msg void OnSelchangeFontsizeList();
	afx_msg void OnUndo();
	afx_msg void OnRedo();
	afx_msg void OnParser();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnSaveFile();
	afx_msg void OnOpenFile();
	afx_msg void OnCopyImage();
	afx_msg void OnCopyMathml();
	afx_msg void OnCredit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ResetCopyOptions();
	int HexToInt(CString st);
	void InitToolbarEntity();
	void InitEntityList();
	CToolBarBtn	m_btnEquation;
	CToolBarBtn	m_btnBrace;
	CToolBarBtn	m_btnUpperGreek;
	CToolBarBtn	m_btnLowerGreek;
	CToolBarBtn	m_btnSum;
	CToolBarBtn	m_btnProd;
	CToolBarBtn	m_btnIntegral;
	CToolBarBtn	m_btnDerivative;
	CToolBarBtn	m_btnMatrix;
	CToolBarBtn	m_btnPbyq;
	CToolBarBtn	m_btnFunction;
	CToolBarBtn	m_btnCoreData;
	CToolBarBtn	m_btnVector;
	CToolBarBtn	m_btnArrows;
	CToolTipCtrl m_tooltip;

	CEditorCtrl m_Editor;
	CStringArray m_LowerGreek;
	CStringArray m_UpperGreek;
	CStringArray m_StdOp;
	CStringArray m_GeoOp;
	CStringArray m_ArrOp;
	CStringArray m_DotOp;
	CStringArray m_MoreSym;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITORDLG_H__40341080_170D_4179_AA07_14B9937173D7__INCLUDED_)

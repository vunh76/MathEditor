#if !defined(AFX_EDITORCTRL_H__74FBF205_8A3C_4ADC_8C21_C160A8BB9352__INCLUDED_)
#define AFX_EDITORCTRL_H__74FBF205_8A3C_4ADC_8C21_C160A8BB9352__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditorCtrl.h : header file
//
#define FORMULACTRL_CLASSNAME	_T("FormulaEditCtrl")
#define IsSHIFTpressed() ( (GetKeyState(VK_SHIFT) & (1 << (sizeof(SHORT)*8-1))) != 0   )
#define IsCTRLpressed()  ( (GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT)*8-1))) != 0 )
/////////////////////////////////////////////////////////////////////////////
// CEditorCtrl window
#include <afxtempl.h>

#include "Box.h"
#include "Cursor.h"
#include "Command.h"
class CEditorCtrl : public CWnd
{
   DECLARE_DYNCREATE(CEditorCtrl)
// Construction
public:
	CEditorCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditorCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetCopyOption(BOOL bMathML, BOOL bImage);
	BOOL OpenFile(CString strFile, UINT nFormat=0);
	BOOL SaveFile(CString strFileName, UINT nFormat=0);
	int GetTopMargin();
	void SetTopMargin(int n);
	int GetLeftMargin();
	void SetLeftMargin(int n);
	void EnableScrollBars(int nBar);
	BOOL ExportToWMF(CString strPath);
	CString GetMathML();
	void InsertSpecialElement(CString more);
	CBox* InsertEntity(CString en);
	void SortEntityList();
	void AddMathEntity(CString entity, CString fontname, CString mathmlname, CString latexname, BOOL inverted, BOOL boperator, unsigned char code);
	struct MATH_ENTITY{
		unsigned char CharCode;
		CString FontName;
		CString EntityName;
		CString MathMLName;
		CString LaTexName;
		BOOL	bInverted;
		BOOL	bOperator;
	};
	//User-defined typed for holding popular mathematical operator such as !,@,#...
	struct MATH_ORIGINAL{
		BOOL	bOperator;
		CString strName;
		CString strMathML;
		CString strLaTeX;
	};
	MATH_ENTITY GetEntityInfo(CString entity);
	BOOL ParseFormula();
	CString GetFormularText();
	void SetFormulaText(CString formula);
	void InsertFuncOperator(CString id, int more);
	void ScaleUp();
	void ClearSelection();
	void FreeUndoList();
	void SetEndSel(CBox* box);
	void SetStartSel(CBox* box);
	void SetCursor(CBox* box, BOOL bEndBox=TRUE);
	CBox* GetEndSelect();
	CBox* GetStartSelect();
	CCursor* GetCursor();
	int GetBaseFontSize();
	void SetBaseFontSize(int n);
	void InsertElement(CString id, int more=0);
	void DestroyMath();
	CBox* GetMath();
	void SetMath(CBox* box);
	BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID, DWORD dwStyle=WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE);
	virtual ~CEditorCtrl();

	// Generated message map functions
protected:
	BOOL RegisterWindowClass();
	//{{AFX_MSG(CEditorCtrl)
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bCopyMathML;
	BOOL m_bCopyImage;
	void CutToClipboard();
	void PasteFromClipboard();
	void CopyToClipboard();
	UINT CF_MATHEQU;
	BOOL m_bCanAdd;
	void CheckCaretVisible();
	void Redraw(BOOL bResetScroll=TRUE);
	int m_nTopMargin;
	int m_nLeftMargin;
	void ResetScrollBar();
	int FindOriginalChar(CString st);
	CString m_strFormula;
	void ProcessShortCut(UINT nChar);
	void ProcessRIGHTkey(int sh);
	void ProcessLEFTkey(int sh);
	void ProcessHOMEkey(int sh);
	void ProcessENDkey(int sh);
	void OnDraw(CDC* pDC);
	void ProcessBackSpaceKey();
	void ProcessDelKey();
	CBox* InsertRoot(int more);
	CBox* InsertUnderOver(int nType);

	CBox* InsertSum(int more=0, char ch=(char)0xAA);
	int m_nBaseFontSize;
	void SelectBox(CBox* box, BOOL b);
	void InsertBox(CBox* box);
	int DeleteSelection();
	CBox* m_EndBox;
	CBox* m_StartBox;
	CCursor* m_Cursor;
	CBox* m_Math;
	CArray<MATH_ENTITY, MATH_ENTITY&> entities;
	CArray<MATH_ORIGINAL, MATH_ORIGINAL&> origins;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITORCTRL_H__74FBF205_8A3C_4ADC_8C21_C160A8BB9352__INCLUDED_)

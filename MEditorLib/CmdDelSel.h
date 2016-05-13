// CmdDelSel.h: interface for the CCmdDelSel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDDELSEL_H__86A046B0_1E24_4999_813D_7F11CAD7D936__INCLUDED_)
#define AFX_CMDDELSEL_H__86A046B0_1E24_4999_813D_7F11CAD7D936__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Command.h"
#include "EditorCtrl.h"
class CCmdDelSel : public CCommand  
{
public:
	void ClearContent();
	CString ClassName();
	void UnExecute();
	void Execute();
	CCmdDelSel(CEditorCtrl* ed);
	virtual ~CCmdDelSel();

private:
	int m_CursorPos;
	int m_SelStartIndex;
	CBox* m_SelParent;
	CArray<CBox*, CBox*> m_DelBox;
	CEditorCtrl* m_Editor;
};

#endif // !defined(AFX_CMDDELSEL_H__86A046B0_1E24_4999_813D_7F11CAD7D936__INCLUDED_)

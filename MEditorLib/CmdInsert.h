// CmdInsert.h: interface for the CCmdInsert class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDINSERT_H__BE728B2E_402D_4077_A9E8_72BD9132E594__INCLUDED_)
#define AFX_CMDINSERT_H__BE728B2E_402D_4077_A9E8_72BD9132E594__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Command.h"
#include "Box.h"
#include "EditorCtrl.h"
class CCmdInsert : public CCommand  
{
public:
	void ClearContent();
	CString ClassName();
	void UnExecute();
	void Execute();
	CCmdInsert(CEditorCtrl* ed, CBox* box);
	virtual ~CCmdInsert();

private:
	int m_SelStartIndex;
	CArray<CBox*, CBox*> m_SelBox;
	int m_CursorChildCount;
	int m_CursorPos;
	BOOL m_bTemplate;
	BOOL m_bEndBox;
	CBox* m_CursorParent;
	CCursor* m_Cursor;
	CEditorCtrl* m_Editor;
	CBox* m_Box;

};

#endif // !defined(AFX_CMDINSERT_H__BE728B2E_402D_4077_A9E8_72BD9132E594__INCLUDED_)

// CmdDelete.h: interface for the CCmdDelete class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDDELETE_H__25D8F17B_D28D_470B_BF1A_9A1512D2A43E__INCLUDED_)
#define AFX_CMDDELETE_H__25D8F17B_D28D_470B_BF1A_9A1512D2A43E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Command.h"
#include "EditorCtrl.h"
#include "Box.h"
class CCmdDelete : public CCommand  
{
public:
	void ClearContent();
	CString ClassName();
	void UnExecute();
	void Execute();
	CCmdDelete(CEditorCtrl* ed, CBox* box, BOOL bDirection=TRUE);
	virtual ~CCmdDelete();

private:
	BOOL m_bEndBox;
	int m_CursorPos;
	CBox* m_CursorParent;
	BOOL m_bDirect;
	CBox* m_BoxParent;
	int m_BoxIndex;
	CBox* m_Box;
	CEditorCtrl* m_Editor;
};

#endif // !defined(AFX_CMDDELETE_H__25D8F17B_D28D_470B_BF1A_9A1512D2A43E__INCLUDED_)

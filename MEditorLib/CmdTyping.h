// CmdTyping.h: interface for the CCmdTyping class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDTYPING_H__DE84B33A_4ED4_496C_AF65_9ED181763E5E__INCLUDED_)
#define AFX_CMDTYPING_H__DE84B33A_4ED4_496C_AF65_9ED181763E5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Command.h"
#include "EditorCtrl.h"
#include "Box.h"
//This class implements a derived version of command class
//in which performs any typing action from keyboard that make change.
//in editor
class CCmdTyping : public CCommand  
{
public:
	void UnExecute();
	void Execute();
	CCmdTyping(CEditorCtrl* ed, UINT nChar);
	virtual ~CCmdTyping();

private:
	CBox* MakeBox();
	UINT m_Char;
	CBox* m_Box;	//Box to insert
	CEditorCtrl* m_Editor;
	int		m_CursorPos;	//Cursor position
	CBox*	m_ParentBox;	//Parent of cursor where to insert
	int		m_SelStartIndex;
	CArray<CBox*, CBox*> m_SelBox;	//Selected box array
	BOOL	m_bEndBox;
	BOOL	m_bTemplate;
};

#endif // !defined(AFX_CMDTYPING_H__DE84B33A_4ED4_496C_AF65_9ED181763E5E__INCLUDED_)

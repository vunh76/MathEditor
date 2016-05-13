// Cursor.h: interface for the CCursor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURSOR_H__33306EC7_0602_4AF6_AF97_345D1A756441__INCLUDED_)
#define AFX_CURSOR_H__33306EC7_0602_4AF6_AF97_345D1A756441__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Box.h"
class CEditorCtrl;

class CCursor : public CBox  
{
public:
	CBox* MoveDownBox(CBox* box);
	CBox* MoveUpBox(CBox* box);
	BOOL MoveDown();
	BOOL MoveUp();
	int GetChildrenCount();
	CString ClassName();
	BOOL IsTemplate();
	void SetEndBox(BOOL b);
	BOOL IsEndBox();
	CBox* GetParent();
	int GetIndex();
	void MoveInPoint(int cx, int cy);
	CBox* GetRoot();
	void SetRoot(CBox* box);
	CBox* MoveInBox(int cx, int cy, CBox* box);
	void ShowCaret();
	void HideCaret();
	void DestroyCaret();
	CWnd* GetWindow();
	void SetWindow(CEditorCtrl* pWnd);
	CBox* MoveLeftInBox(CBox* box);
	CBox* MoveRightInBox(CBox* box);
	CBox* MoveLeftBox(CBox* box);
	void Draw(CDC* pDC);
	bool MoveRight();
	bool MoveLeft();
	CBox* GetBox();
	void SetBox(CBox* box);
	CCursor();
	virtual ~CCursor();

private:
	CBox* m_Root;
	CEditorCtrl* m_pWnd;
	CBox* MoveRightBox(CBox* box);
	BOOL m_bEndBox;
	CBox* m_CurrentBox;

};

#endif // !defined(AFX_CURSOR_H__33306EC7_0602_4AF6_AF97_345D1A756441__INCLUDED_)

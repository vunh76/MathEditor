// CmdInsert.cpp: implementation of the CCmdInsert class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CmdInsert.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "Cursor.h"
#include "MI.h"
#include "CmdDelSel.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCmdInsert::CCmdInsert(CEditorCtrl* ed, CBox* box)
{
	CCursor* cursor=ed->GetCursor();
	CBox* box1=ed->GetStartSelect();
	CBox* box2=ed->GetEndSelect();
	m_Editor=ed;
	m_Box=box;
	m_CursorParent=cursor->GetParent();
	m_bEndBox=cursor->IsEndBox();
	m_bTemplate=cursor->IsTemplate();
	m_CursorPos=cursor->GetIndex();
	m_CursorChildCount=cursor->GetChildrenCount();
	if (box1 && box2){
		for (int i=box1->GetIndex(); i<=box2->GetIndex(); i++)
			m_SelBox.Add(m_CursorParent->GetBox(i));
		m_SelStartIndex=box1->GetIndex();
	}
	else
		m_SelStartIndex=-1;
}

CCmdInsert::~CCmdInsert()
{
	if (m_Box) delete m_Box;
}

void CCmdInsert::Execute()
{
	if (m_SelStartIndex>=0 && m_Box->GetChildrenCount()==0){
		//Delete Selection
		for (int i=1; i<=m_SelBox.GetSize();i++ )
			m_CursorParent->RemoveBox(m_SelStartIndex);
		m_Editor->SetStartSel(NULL);
		m_Editor->SetEndSel(NULL);
	
		m_CursorParent->InsertBox(m_SelStartIndex,m_Box);
		
		m_Editor->SetCursor(m_Box);
		return;
	}
	
	if (m_SelStartIndex==-1 && m_Box->GetChildrenCount()==0){
		if (m_bTemplate && m_CursorChildCount==0)
			m_CursorParent->SetBox(m_CursorPos, m_Box); 
		else
			if (m_bEndBox)
				m_CursorParent->InsertBox(m_CursorPos+1,m_Box);
			else
				m_CursorParent->InsertBox(m_CursorPos,m_Box);
		m_Editor->SetCursor(m_Box);	
		return;
	}
	/*
	//Neu cursor la mot template va khong chua children
		if (m_bTemplate && m_CursorChildCount==0)
			m_CursorParent->SetBox(m_CursorPos, m_Box); 
		else
			if (m_bEndBox)
				m_CursorParent->InsertBox(m_CursorPos+1,m_Box);
			else{
				m_CursorParent->InsertBox(m_CursorPos,m_Box);
				theCursor->SetEndBox(TRUE);
			}
		theCursor->SetBox(m_Box);	
		return;
	}
	*/
}

void CCmdInsert::UnExecute()
{
	/*
	CBox* box;
	int k;
	box=m_Box->GetParent();
	if (box->GetChildrenCount()==1){
		m_Box=box->RemoveBox(0);
		box->AddBox(new CMI(""));
		m_Editor->SetCursor(box->GetBox(0));
		return;
	}
	k=m_Box->GetIndex();
	m_Box=box->RemoveBox(k);
	if (k==0)
		m_Editor->SetCursor(box->GetBox(0), FALSE);
	else
		m_Editor->SetCursor(box->GetBox(k-1));
	*/
	if (m_CursorParent->GetChildrenCount()==1){
		m_CursorParent->RemoveBox(0);
		if (m_SelStartIndex>=0){
			for (int i=1; i<=m_SelBox.GetSize(); i++)
				m_CursorParent->InsertBox(m_SelStartIndex+i-1, m_SelBox[i-1]);
			m_Editor->SetStartSel(m_CursorParent->GetBox(m_SelStartIndex));
			m_Editor->SetEndSel(m_CursorParent->GetBox(m_SelStartIndex+m_SelBox.GetSize()-1));
		}
		else{
			m_CursorParent->AddBox(new CMI(""));
			m_Editor->SetStartSel(NULL);
			m_Editor->SetEndSel(NULL);
		}
		m_Editor->SetCursor(m_CursorParent->GetBox(m_CursorPos),m_bEndBox);
		return;
	}
	int k=m_Box->GetIndex();
	m_CursorParent->RemoveBox(k);
	if (m_SelStartIndex>=0){
		for (int i=1; i<=m_SelBox.GetSize(); i++)
			m_CursorParent->InsertBox(m_SelStartIndex+i-1, m_SelBox[i-1]);
		m_Editor->SetStartSel(m_CursorParent->GetBox(m_SelStartIndex));
		m_Editor->SetEndSel(m_CursorParent->GetBox(m_SelStartIndex+m_SelBox.GetSize()-1));
	}
	else{
		m_Editor->SetStartSel(NULL);
		m_Editor->SetEndSel(NULL);
	}
	if (k==0)
		m_Editor->SetCursor(m_CursorParent->GetBox(0), FALSE);
	else
		m_Editor->SetCursor(m_CursorParent->GetBox(k-1));
}


CString CCmdInsert::ClassName()
{
	return "INS";
}

void CCmdInsert::ClearContent()
{
	m_Box=NULL;
}

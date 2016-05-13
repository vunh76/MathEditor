// CmdTyping.cpp: implementation of the CCmdTyping class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CmdTyping.h"
#include "Cursor.h"
#include "MI.h"
#include "MN.h"
#include "MO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCmdTyping::CCmdTyping(CEditorCtrl* ed, UINT nChar)
{
	//Only hanlde key that can insert new element into editor
	CCursor* cursor=ed->GetCursor();
	CBox* box1=ed->GetStartSelect();
	CBox* box2=ed->GetEndSelect();
	m_Editor=ed;
	m_CursorPos=cursor->GetIndex();
	m_ParentBox=cursor->GetParent();
	_ASSERT(m_ParentBox->ClassName()=="MRow");
	m_SelStartIndex=-1;
	if (box1 && box2){
		//Cursor must always be at beginning or ending of selection
		_ASSERT(box1->GetParent()==m_ParentBox);
		m_SelStartIndex=box1->GetIndex();
		//Save selection list
		for (int i=box1->GetIndex(); i<=box2->GetIndex(); i++)
			m_SelBox.Add(m_ParentBox->GetBox(i));
	}
	m_Box=MakeBox();
	m_bEndBox=cursor->IsEndBox();
	m_bTemplate=cursor->IsTemplate();
}

CCmdTyping::~CCmdTyping()
{

}

void CCmdTyping::Execute()
{
	//Delete Selection
	if (m_SelStartIndex>=0){
		for (int i=0; i<m_SelBox.GetSize(); i++)
			m_ParentBox->RemoveBox(m_SelStartIndex);
		if (m_ParentBox->GetChildrenCount()==0)
			m_ParentBox->AddBox(new CMI(""));
		m_Editor->SetStartSel(NULL);
		m_Editor->SetEndSel(NULL);
	}
	//Insert new element into that position
	if (m_bTemplate)
		m_ParentBox->SetBox(0,m_Box);
	else if (m_SelStartIndex>=0)
		m_ParentBox->InsertBox(m_SelStartIndex,m_Box);
	else if (m_bEndBox)
		m_ParentBox->InsertBox(m_CursorPos+1,m_Box);
	else
		m_ParentBox->InsertBox(m_CursorPos,m_Box);
	m_Editor->SetCursor(m_Box);
}

void CCmdTyping::UnExecute()
{
	int k;
	//Remove inserted box
	if (m_SelStartIndex>=0)
		k=m_SelStartIndex;
	else if (m_bEndBox)
		k=m_CursorPos+1;
	else
		k=m_CursorPos;
	m_ParentBox->RemoveBox(k);
	//Restore selection
	if (m_SelStartIndex>=0){
		for (int i=0; i<m_SelBox.GetSize(); i++)
			m_ParentBox->InsertBox(i+m_SelStartIndex,m_SelBox[i]);
		m_Editor->SetStartSel(m_ParentBox->GetBox(m_SelStartIndex));
		m_Editor->SetEndSel(m_ParentBox->GetBox(m_SelStartIndex+m_SelBox.GetSize()-1));
	}
	if (m_ParentBox->GetChildrenCount()==0)
		m_ParentBox->AddBox(new CMI(""));
	m_Editor->SetCursor(m_ParentBox->GetBox(m_CursorPos),m_bEndBox);
}


CBox* CCmdTyping::MakeBox()
{
	if (m_Char>='0' && m_Char<='9')
		return new CMN(m_Char);

	switch (m_Char){
	case '+':
	case '-':
	case '*':
	case '<':
	case '>':
		return new CMO(m_Char);
		break;
	}

	if (m_Char>=32)
		return new CMI(m_Char);
	else
		return NULL;
}

// CmdDelSel.cpp: implementation of the CCmdDelSel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CmdDelSel.h"
#include "MI.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCmdDelSel::CCmdDelSel(CEditorCtrl* ed)
{
	m_Editor=ed;
	CBox* box1=ed->GetStartSelect();
	CBox* box2=ed->GetEndSelect();
	m_SelParent=box1->GetParent();
	for (int k=box1->GetIndex(); k<=box2->GetIndex(); k++)
		m_DelBox.Add(m_SelParent->GetBox(k));
	m_SelStartIndex=box1->GetIndex();
	m_CursorPos=ed->GetCursor()->GetIndex();
}

CCmdDelSel::~CCmdDelSel()
{
	for (int i=0; i<m_DelBox.GetSize(); i++)
		delete m_DelBox[i];
	m_DelBox.RemoveAll();
}

void CCmdDelSel::Execute()
{
	for (int i=1; i<=m_DelBox.GetSize();i++)
		m_SelParent->RemoveBox(m_SelStartIndex);
		
	if (m_SelParent->GetChildrenCount()==0)
		m_SelParent->AddBox(new CMI(""));
	if (m_SelStartIndex>0)
		m_Editor->SetCursor(m_SelParent->GetBox(m_SelStartIndex-1));
	else
		m_Editor->SetCursor(m_SelParent->GetBox(m_SelStartIndex));
	m_Editor->SetStartSel(NULL);
	m_Editor->SetStartSel(NULL);
}

void CCmdDelSel::UnExecute()
{
	if (m_SelParent->IsTemplate())
		m_SelParent->DeleteBox(0);
	for (int i=1; i<=m_DelBox.GetSize(); i++)
		m_SelParent->InsertBox(m_SelStartIndex+i-1,m_DelBox[i-1]);
	m_Editor->SetStartSel(m_SelParent->GetBox(m_SelStartIndex));
	m_Editor->SetEndSel(m_SelParent->GetBox(m_SelStartIndex+m_DelBox.GetSize()-1));
	m_Editor->SetCursor(m_SelParent->GetBox(m_CursorPos));
}

CString CCmdDelSel::ClassName()
{
	return "DELSEL";
}

void CCmdDelSel::ClearContent()
{
	for (int i=0; i<m_DelBox.GetSize(); i++)
		m_DelBox[i]=NULL;
	m_DelBox.RemoveAll();
}

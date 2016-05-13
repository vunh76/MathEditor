// CmdDelete.cpp: implementation of the CCmdDelete class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CmdDelete.h"
#include "MI.h"
#include "Cursor.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCmdDelete::CCmdDelete(CEditorCtrl* ed, CBox* box, BOOL bDirection)
{
	CCursor* cursor=ed->GetCursor();
	m_Editor=ed;
	m_Box=box;
	m_BoxIndex=m_Box->GetIndex();
	m_BoxParent=m_Box->GetParent();
	m_bDirect=bDirection;
	m_CursorParent=cursor->GetParent();
	m_CursorPos=cursor->GetIndex();
	m_bEndBox=cursor->IsEndBox();
}

CCmdDelete::~CCmdDelete()
{
	if (m_Box) delete m_Box;
}

void CCmdDelete::Execute()
{
	m_BoxParent->RemoveBox(m_BoxIndex);
	if (m_BoxParent->GetChildrenCount()==0){
		m_BoxParent->AddBox(new CMI(""));
		m_Editor->SetCursor(m_BoxParent->GetBox(0));
	}
	else if (m_CursorPos>0)
		m_Editor->SetCursor(m_BoxParent->GetBox(m_CursorPos-1));
	else
		m_Editor->SetCursor(m_BoxParent->GetBox(0),FALSE);

}

void CCmdDelete::UnExecute()
{
	if (m_BoxIndex==0 && m_BoxParent->IsTemplate() && m_BoxParent->GetChildrenCount()==1)
		m_BoxParent->SetBox(0, m_Box);
	else
		m_BoxParent->InsertBox(m_BoxIndex,m_Box);
	m_Editor->SetCursor(m_Box, m_bEndBox);
}

CString CCmdDelete::ClassName()
{
	return "DEL";
}

void CCmdDelete::ClearContent()
{
	m_Box=NULL;
}

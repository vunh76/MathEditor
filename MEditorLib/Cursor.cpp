// Cursor.cpp: implementation of the CCursor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cursor.h"
#include "EditorCtrl.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCursor::CCursor()
{
	m_bEndBox=TRUE;
}

CCursor::~CCursor()
{

}


void CCursor::SetBox(CBox *box)
{
	m_CurrentBox=box;
}

CBox* CCursor::GetBox()
{
	return m_CurrentBox;
}

bool CCursor::MoveLeft()
{
	CBox* box;
	box=MoveLeftBox(m_CurrentBox);
	if (box){
		m_CurrentBox=box;
		return TRUE;
	}
	return FALSE;
}

bool CCursor::MoveRight()
{
	CBox* box;
	box=MoveRightBox(m_CurrentBox);
	if (box){
		m_CurrentBox=box;
		return TRUE;	
	}
	else
		return FALSE;
}

void CCursor::Draw(CDC *pDC)
{
	COLORREF cl;
	cl=pDC->SetTextColor(RGB(255,0,0));
	m_CurrentBox->Draw(pDC);
	pDC->SetTextColor(cl);
}

CBox* CCursor::MoveRightBox(CBox *box)
{
	CBox* box1;
	CBox* box2;
	int k, l;

	box1=box->GetParent(); 

	if (box1==NULL)
		return NULL;
	
	k=box->GetIndex();
	if (k==0 && !m_bEndBox)
		if (box->GetChildrenCount()==0){
			m_bEndBox=TRUE;
			return box;
		}
		else
			return MoveRightInBox(box);

	if (k==box1->GetChildrenCount()-1){
		box2=box1->GetParent();
		if (!box2)
			return NULL;
		if (box2->ClassName()=="MRow")
			return NULL;

		l=box1->GetIndex();
		if (box2->GetChildrenCount()==3)//If cursor is first child of box that has more than two box
			if (l==0) //Try to move to second box
				return MoveRightInBox(box2->GetBox(l+1));
			else
				return box2; //Return parent box
		else
			return box2; //Return parent box
	}
		
	if (k<(box1->GetChildrenCount()-1))
		return MoveRightInBox(box1->GetBox(k+1));
	return NULL;
}

CBox* CCursor::MoveLeftBox(CBox *box)
{
	CBox* box1;
	CBox* box2;
	int k, l;
	box1=box->GetParent();
	
	if (box1==NULL)
		return NULL;
	
	k=box->GetIndex();
	if (k==0)
		if (!m_bEndBox || (box->IsTemplate() && box->GetChildrenCount()==0)){//Cursor is first child of box and caret is at beginning
			box2=box1->GetParent(); //Try to move to the parent
			if (!box2)
				return NULL;
			if (box2->ClassName()=="MRow")
				return NULL;
			l=box1->GetIndex();
			if (box2->GetChildrenCount()==3 && l==2){	//Special case
				m_bEndBox=TRUE;							//Try to move through first box
				return MoveLeftInBox(box2->GetBox(0));	//For example: MSubSup
			}
			else{
				l=box2->GetIndex();
				if (l==0){ //If the parent is first box
					m_bEndBox=FALSE;
					return box2;//Just return it
				}
				else{
					box1=box2->GetParent();//Try to return previous box
					if (!box1)
						return NULL;
					if (box1->ClassName()!="MRow")
						return NULL;
					m_bEndBox=TRUE;
					return box1->GetBox(l-1);
				}
			}				
		}
		else
			if (box->GetChildrenCount()==0){
				m_bEndBox=FALSE;
				return box;
			}
			else
				return MoveLeftInBox(box);

	if (box->GetChildrenCount()==0)	
		return box1->GetBox(k-1);
	else
		return MoveLeftInBox(box);

}
//Di chuyen vao ben trong mot box cho den khi gap box nguyen to 
//theo chieu tu trai sang
CBox* CCursor::MoveRightInBox(CBox *box)
{
	if (box->GetChildrenCount()==0){
		if (box->GetIndex()==0 && !box->IsTemplate())
			m_bEndBox=FALSE;
		else
			m_bEndBox=TRUE;
		return box;
	}
	return MoveRightInBox(box->GetBox(0));
}
//Di chuyen vao ben trong mot box cho den khi gap box nguyen to 
//theo chieu tu phai sang
CBox* CCursor::MoveLeftInBox(CBox *box)
{
	if (box->GetChildrenCount()==0){
		m_bEndBox=TRUE;
		return box;
	}
	return MoveLeftInBox(box->GetBox(box->GetChildrenCount()-1));
}


void CCursor::SetWindow(CEditorCtrl *pWnd)
{
	m_pWnd=pWnd;
}

CWnd* CCursor::GetWindow()
{
	return m_pWnd;
}

void CCursor::DestroyCaret()
{
	::DestroyCaret();
}

void CCursor::HideCaret()
{
	m_pWnd->HideCaret();
}

void CCursor::ShowCaret()
{
	if (m_CurrentBox->GetHeight()==0)
		return;
	if (CWnd::GetFocus()!=m_pWnd)
		return;

	CPoint vporg;
	vporg.x=-m_pWnd->GetScrollPos(SB_HORZ);
	vporg.y=-m_pWnd->GetScrollPos(SB_VERT);

	DestroyCaret();
	CBox* box;
	box=m_CurrentBox->GetParent();
	if (!box)
		box=m_CurrentBox;
	if (box->ClassName()!="MRow")
		box=m_CurrentBox;
	m_pWnd->CreateSolidCaret(1,box->GetHeight());
	if (m_bEndBox)
		m_pWnd->SetCaretPos(CPoint(m_CurrentBox->GetLeft()+m_CurrentBox->GetWidth()+vporg.x, box->GetTop()+vporg.y));
	else
		m_pWnd->SetCaretPos(CPoint(m_CurrentBox->GetLeft()+vporg.x, box->GetTop()+vporg.y));
	m_pWnd->ShowCaret();
}

CBox* CCursor::MoveInBox(int cx, int cy, CBox *box)
{
	CBox* box1;
	if(cx >= box->GetLeft() && cy >= box->GetTop() && cx <= box->GetLeft() + box->GetWidth() && cy <= box->GetTop() + box->GetHeight())
	{
		for(int i = box->GetChildrenCount()- 1; i >= 0; i--){
			box1 = MoveInBox(cx, cy, box->GetBox(i));
            if(box1 != NULL)
               return box1;
        }
		if (box->ClassName()!="MRow")
			return box;
    } 
    return NULL;
}

void CCursor::SetRoot(CBox *box)
{
	m_Root=box;
}

CBox* CCursor::GetRoot()
{
	return m_Root;
}

void CCursor::MoveInPoint(int cx, int cy)
{
	if (cx<m_Root->GetLeft())
		cx=m_Root->GetLeft();
	if (cx>m_Root->GetLeft()+m_Root->GetWidth())
		cx=m_Root->GetLeft()+m_Root->GetWidth();
	if (cy<m_Root->GetTop())
		cy=m_Root->GetTop();
	if (cy>m_Root->GetTop()+m_Root->GetHeight())
		cy=m_Root->GetTop()+m_Root->GetHeight();

	CBox* box=MoveInBox(cx, cy, m_Root);
	if (box){
		_ASSERT(box->ClassName()!="MRow");
		if (box->GetIndex()==0 && cx<box->GetLeft()+box->GetWidth()/2 && !box->IsTemplate())
			m_bEndBox=FALSE;
		else
			m_bEndBox=TRUE;
		m_CurrentBox=box;
	}
}

int CCursor::GetIndex()
{
	return m_CurrentBox->GetIndex();
}

CBox* CCursor::GetParent()
{
	return m_CurrentBox->GetParent();
}

BOOL CCursor::IsEndBox()
{
	return m_bEndBox;
}

void CCursor::SetEndBox(BOOL b)
{
	m_bEndBox=b;
}

BOOL CCursor::IsTemplate()
{
	return m_CurrentBox->IsTemplate();
}

CString CCursor::ClassName()
{
	return m_CurrentBox->ClassName();
}

int CCursor::GetChildrenCount()
{
	return m_CurrentBox->GetChildrenCount();
}

BOOL CCursor::MoveUp()
{
	CBox* box=MoveUpBox(m_CurrentBox);
	if (box){
		m_CurrentBox=box;
		return TRUE;
	}
	else
		return FALSE;

}

BOOL CCursor::MoveDown()
{
	CBox* box=MoveDownBox(m_CurrentBox);
	if (box){
		m_CurrentBox=box;
		return TRUE;
	}
	else
		return FALSE;
}

CBox* CCursor::MoveUpBox(CBox *box)
{
	CBox* box1;
	CBox* box2;
	int k;

	box1=box->GetParent();
	
	if (!box1)
		return NULL;

	box2=box1->GetParent();
	if (!box2)
		return NULL;
	
	if (box2->ClassName()=="MRow")
		return NULL;

	k=box1->GetIndex();
	if (k>0)
		return MoveLeftInBox(box2->GetBox(k-1));
	else
		return MoveUpBox(box2);
}

CBox* CCursor::MoveDownBox(CBox *box)
{
	CBox* box1;
	CBox* box2;
	int k;
	box1=box->GetParent();

	if (!box1)
		return NULL;

	box2=box1->GetParent();
	if (!box2)
		return NULL;
	
	if (box2->ClassName()=="MRow")
		return NULL;

	k=box1->GetIndex();
	if (k<box2->GetChildrenCount()-1)
		return MoveRightInBox(box2->GetBox(k+1));
	else
		return MoveDownBox(box2);
}

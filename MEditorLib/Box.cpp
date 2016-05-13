// Box.cpp: implementation of the CBox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Box.h"

IMPLEMENT_SERIAL(CBox, CObject, 1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBox::CBox()
{
	m_Parent=NULL;
	m_Left=0;
	m_Top=0;
	m_Width=0;
	m_Height=0;
	m_Ascent=0;
	m_bTemplate=FALSE;
	m_bSelected=FALSE;
	m_FontSize=12;
}

CBox::~CBox()
{

	m_Parent=NULL;
}

void CBox::SetWidth(int n)
{
	m_Width=n;
}

int CBox::GetWidth()
{
	return m_Width;
}

void CBox::SetHeight(int n)
{
	m_Height=n;
}

int CBox::GetHeight()
{
	return m_Height;
}

void CBox::SetAscent(int n)
{
	m_Ascent=n;
}

int CBox::GetAscent()
{
	return m_Ascent;
}

int CBox::GetDescent()
{
	return m_Height-m_Ascent;
}

void CBox::SetLeft(int n)
{
	m_Left=n;
}

int CBox::GetLeft()
{
	return m_Left;
}

void CBox::SetTop(int n)
{
	m_Top=n;
}

int CBox::GetTop()
{
	return m_Top;
}

void CBox::Layout(CDC *pDC)
{
	return;
}

void CBox::Draw(CDC *pDC)
{
	return;
}

CString CBox::ClassName()
{
	return "";
}

CString CBox::ToString()
{
	return "";
}

void CBox::SetFontSize(int n)
{
	m_FontSize=n;
}

int CBox::GetFontSize()
{
	return m_FontSize;
}

void CBox::SetParent(CBox *theParent)
{
	m_Parent=theParent;
}

CBox* CBox::GetParent()
{	
	return m_Parent;
}

void CBox::SetCoord(int cx, int cy)
{
	SetLeft(cx);
	SetTop(cy);
}

void CBox::AddBox(CBox *box)
{

}

int CBox::GetChildrenCount()
{
	return 0;
}

CBox* CBox::GetBox(int nIndex)
{
	return NULL;
}

void CBox::SetBox(int nIndex, CBox *box)
{

}

void CBox::InsertBox(int nIndex, CBox *box)
{

}

void CBox::DeleteBox(int nIndex)
{

}

int CBox::GetIndex()
{
	return m_Index;
}

void CBox::SetIndex(int nIndex)
{
	m_Index=nIndex;
}

void CBox::SetTemplate(BOOL b)
{
	m_bTemplate=b;
}

BOOL CBox::IsTemplate()
{
	return m_bTemplate;
}

void CBox::SetSelect(BOOL b)
{
	m_bSelected=b;
}

BOOL CBox::IsSelected()
{
	return m_bSelected;
}

CBox* CBox::RemoveBox(int nIndex)
{
	return NULL;
}



CString CBox::ToLaTex()
{
	return "";
}

CString CBox::ToMathML(int nLevel)
{
	return "";
}

CRect CBox::GetRect()
{
	int l=GetLeft();
	int t=GetTop();
	int r=l+GetWidth();
	int b=t+GetHeight();
	return CRect(l,t,r,b);
}

void CBox::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring()){
		ar << m_bTemplate;
	}
	else{
		ar >> m_bTemplate;
	}
}
/**************************************
The identifier for box. It has default value
as the same as ClassName but in few certaint
cases, it has diffirence value.
Mainly use for serialize only.
***************************************/
CString CBox::Signature()
{
	return "";
}

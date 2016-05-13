// CompositeBox.cpp: implementation of the CCompositeBox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CompositeBox.h"
#include "Factory.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompositeBox::CCompositeBox()
{
	m_Children.SetSize(0);
}

CCompositeBox::~CCompositeBox()
{
	for (int i=0; i<m_Children.GetSize(); i++){
		delete m_Children[i];
		m_Children[i]=NULL;
	}
	m_Children.RemoveAll();
}

void CCompositeBox::AddBox(CBox *box)
{
	int n;
	m_Children.Add(box);
	n=m_Children.GetSize()-1;
	m_Children[n]->SetParent(this);
	m_Children[n]->SetIndex(n);	
	m_Children[n]->SetFontSize(GetFontSize());
}

void CCompositeBox::DeleteBox(int nIndex)
{
	for (int i=nIndex; i<m_Children.GetSize(); i++)
		m_Children[i]->SetIndex(i-1);
	delete m_Children[nIndex];
	m_Children[nIndex]=NULL;
	m_Children.RemoveAt(nIndex);
}

CBox* CCompositeBox::GetBox(int nIndex)
{
	if (nIndex>=m_Children.GetSize())
		return NULL;
	return m_Children[nIndex];
}

int CCompositeBox::GetChildrenCount()
{
	return m_Children.GetSize();
}

void CCompositeBox::InsertBox(int nIndex, CBox *box)
{
	int i;
	for (i=nIndex; i<m_Children.GetSize(); i++)
		m_Children[i]->SetIndex(i+1);
	if (nIndex>(m_Children.GetSize()-1))
		m_Children.Add(box);
	else
		m_Children.InsertAt(nIndex, box);
	m_Children[nIndex]->SetIndex(nIndex);
	m_Children[nIndex]->SetParent(this);
	m_Children[nIndex]->SetFontSize(GetFontSize());
}

void CCompositeBox::SetBox(int nIndex, CBox *box)
{
	if (nIndex<m_Children.GetSize()){
		delete m_Children[nIndex];
		m_Children.SetAt(nIndex, box);
	}
	else
		m_Children.Add(box);
	m_Children[nIndex]->SetParent(this);
	m_Children[nIndex]->SetIndex(nIndex);
	m_Children[nIndex]->SetFontSize(GetFontSize());
}

void CCompositeBox::SetSelect(BOOL b)
{
	CBox::SetSelect(b);
	for (int i=0; i<m_Children.GetSize(); i++)
		m_Children[i]->SetSelect(b);
}

BOOL CCompositeBox::IsTemplate()
{
	for (int i=0; i<m_Children.GetSize(); i++)
		if (!m_Children[i]->IsTemplate())
			return FALSE;
	return TRUE;
}

//Remove box from children list but do not delete
CBox* CCompositeBox::RemoveBox(int nIndex)
{
	CBox* box=m_Children[nIndex];
	for (int i=nIndex+1; i<m_Children.GetSize(); i++)
		m_Children[i]->SetIndex(i-1);
	m_Children[nIndex]=NULL;
	m_Children.RemoveAt(nIndex);
	return box;
}


void CCompositeBox::SetFontSize(int n)
{
	CBox::SetFontSize(n);
	for (int i=0; i<m_Children.GetSize(); i++){
		m_Children[i]->SetFontSize(n);
	}
}

void CCompositeBox::Draw(CDC *pDC)
{
	for (int i=0; i<GetChildrenCount(); i++)
		GetBox(i)->Draw(pDC);
}

void CCompositeBox::Layout(CDC *pDC)
{
	for (int i=0; i<GetChildrenCount(); i++)
		GetBox(i)->Layout(pDC);
}

void CCompositeBox::Serialize(CArchive &ar)
{
	CBox* box=NULL;
	int n;
	CString st;
	CBox::Serialize(ar);
	if (ar.IsStoring()){
		n=GetChildrenCount();
		ar << n;
		for (int i=0; i<n; i++){
			box=GetBox(i);
			st=box->Signature();
			if (st=="")
				st=box->ClassName();
			TRACE("Serialize Class Name: %s\n", st);
			ar << st;
			box->Serialize(ar);
		}
	}
	else{
		ar >> n;
		for (int i=0; i<n; i++){
			ar >> st;
			box=CFactory::instance(st);
			if (box==NULL)
				AfxThrowArchiveException(CArchiveException::generic,"");
			box->Serialize(ar);
			AddBox(box);
		}
	}
}

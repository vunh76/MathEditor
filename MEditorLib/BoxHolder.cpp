// BoxHolder.cpp: implementation of the CBoxHolder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Box.h"
#include "BoxHolder.h"
#include "Factory.h"
IMPLEMENT_SERIAL(CBoxHolder, CObject, 1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBoxHolder::CBoxHolder()
{
	m_Children.SetSize(0);
}

CBoxHolder::~CBoxHolder()
{
	m_Children.RemoveAll();
}

void CBoxHolder::AddBox(CBox *box)
{
	m_Children.Add(box);
}

CBox* CBoxHolder::GetBox(int nIndex)
{
	return m_Children[nIndex];	
}

void CBoxHolder::Serialize(CArchive &ar)
{
	CBox* box=NULL;
	int n;
	CString st;
	CObject::Serialize(ar);
	if (ar.IsStoring()){
		n=m_Children.GetSize();
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

void CBoxHolder::DeleteAll()
{
	for (int i=0; i<m_Children.GetSize(); i++){
		delete m_Children[i];
		m_Children[i]=NULL;
	}
	m_Children.RemoveAll();
}

int CBoxHolder::GetChildrenCount()
{
	return m_Children.GetSize();
}

void CBoxHolder::Draw(CDC *pDC)
{
	//1. Invert selected state
	int i;
	for (i=0; i<m_Children.GetSize(); i++)
		if (m_Children[i]->IsSelected())
			m_Children[i]->SetSelect(FALSE);
		else
			m_Children[i]->SetSelect(TRUE);

	//2. Drawing each child in the list
	for (i=0; i<m_Children.GetSize(); i++)
		m_Children[i]->Draw(pDC);
	
	//3. Restore selected state
	for (i=0; i<m_Children.GetSize(); i++)
		if (m_Children[i]->IsSelected())
			m_Children[i]->SetSelect(FALSE);
		else
			m_Children[i]->SetSelect(TRUE);
}

int CBoxHolder::GetWidth()
{
	int w=0;
	for (int i=0; i<m_Children.GetSize(); i++)
		w+=m_Children[i]->GetWidth();
	return w;
}

int CBoxHolder::GetHeight()
{
	int ac=0, dc=0;
	for (int i=0; i<m_Children.GetSize(); i++){
		if (m_Children[i]->GetAscent()>ac)
			ac=m_Children[i]->GetAscent();
		if (m_Children[i]->GetDescent()>dc)
			dc=m_Children[i]->GetDescent();
	}
	return ac+dc;
}

CString CBoxHolder::ToMathML()
{
	int i;
	CString tab="";
	CString st;
	BOOL bObmit=(GetChildrenCount()==1 && GetBox(0)->ClassName()!="MSymbol");
	if (!bObmit)
		st=tab + "<mrow>" + crlf;
	else
		st="";
	for (i=0; i<GetChildrenCount(); i++)
		if (!bObmit)
			st+=GetBox(i)->ToMathML(1) + crlf;
		else
			st+=GetBox(i)->ToMathML(0);
	if (!bObmit)
		st+=tab + "</mrow>";
	return st;
}

int CBoxHolder::GetLeft()
{
	if (m_Children.GetSize()==0)
		return -1;
	return m_Children[0]->GetLeft();
}

int CBoxHolder::GetTop()
{
	if (m_Children.GetSize()==0)
		return -1;
	int min=m_Children[0]->GetTop();
	for (int i=1; i<m_Children.GetSize(); i++){
		if (min>m_Children[i]->GetTop())
			min=m_Children[i]->GetTop();
	}
	return min;
}

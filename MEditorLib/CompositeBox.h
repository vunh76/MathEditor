// CompositeBox.h: interface for the CCompositeBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPOSITEBOX_H__A0FE5796_BE4E_46EA_9037_71B261417E02__INCLUDED_)
#define AFX_COMPOSITEBOX_H__A0FE5796_BE4E_46EA_9037_71B261417E02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Box.h"

class CCompositeBox : public CBox  
{
public:
	virtual void Serialize(CArchive& ar);
	virtual void Layout(CDC* pDC);
	virtual void Draw(CDC* pDC);
	virtual void SetFontSize(int n);
	CBox* RemoveBox(int nIndex);
	virtual BOOL IsTemplate();
	virtual void SetSelect(BOOL b);
	virtual void SetBox(int nIndex, CBox* box);
	virtual void InsertBox(int nIndex, CBox* box);
	int GetChildrenCount();
	CBox* GetBox(int nIndex);
	void DeleteBox(int nIndex);
	virtual void AddBox(CBox* box);
	CCompositeBox();
	virtual ~CCompositeBox();

private:
	CArray<CBox*, CBox*> m_Children;
};

#endif // !defined(AFX_COMPOSITEBOX_H__A0FE5796_BE4E_46EA_9037_71B261417E02__INCLUDED_)

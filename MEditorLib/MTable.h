// MTable.h: interface for the CMTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MTABLE_H__D535EEF9_740E_4254_ACCE_E0FEFB4F1FD0__INCLUDED_)
#define AFX_MTABLE_H__D535EEF9_740E_4254_ACCE_E0FEFB4F1FD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompositeBox.h"

class CMTable : public CCompositeBox  
{
public:
	void Serialize(CArchive& ar);
	CString ToMathML(int nLevel);
	CBox* GetCell(int r, int c);
	BOOL GetColWidthEqual();
	void SetColWidthEqual(BOOL b);
	int GetRowSpace();
	void SetRowSpace(int n);
	CString ClassName();
	void SetCoord(int cx, int cy);
	void Draw(CDC* pDC);
	void Layout(CDC* pDC);
	CMTable(int nRow, int nCol);
	CMTable();
	virtual ~CMTable();

private:
	int m_Rows;
	int m_Cols;
	int m_ColSpace;
	BOOL m_bEqualColWidth;
	int m_RowSpace;
	CArray<int, int> m_ColWidth;
	CArray<int, int> m_RowHeight;
	CArray<int, int> m_RowAscent;
};

#endif // !defined(AFX_MTABLE_H__D535EEF9_740E_4254_ACCE_E0FEFB4F1FD0__INCLUDED_)

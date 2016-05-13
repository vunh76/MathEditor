// MTr.cpp: implementation of the CMTr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MTr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMTr::CMTr(CBox* box1, CBox* box2, CBox* box3, CBox* box4)
{
	if (box1)
		AddBox(box1);
	if (box2)
		AddBox(box2);
	if (box3)
		AddBox(box3);
	if (box4)
		AddBox(box4);
}

CMTr::CMTr(CBox* box1, CBox* box2, CBox* box3)
{
	CMTr(box1, box2, box3, NULL);
}

CMTr::CMTr(CBox* box1, CBox* box2)
{
	CMTr(box1, box2, NULL, NULL);
}

CMTr::CMTr()
{

}

CMTr::~CMTr()
{

}

void CMTr::SetCoord(int cx, int cy)
{
	CBox::SetCoord(cx, cy);
}

CString CMTr::ClassName()
{
	return "MTr";
}

int CMTr::GetColSpace()
{
	return m_ColSpace;
}

void CMTr::SetColSpace(int n)
{
	m_ColSpace=n;
}

// MTd.cpp: implementation of the CMTd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MTd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//Box must be a MRow
CMTd::CMTd(CBox* box)
{
	AddBox(box);
}

CMTd::~CMTd()
{

}

void CMTd::SetCoord(int cx, int cy)
{
	CBox::SetCoord(cx, cy);
}

CString CMTd::ClassName()
{
	return "MTd";
}


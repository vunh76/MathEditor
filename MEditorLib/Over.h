// Over.h: interface for the COver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OVER_H__644CE0F1_7846_4F15_961A_BF206B6F84C2__INCLUDED_)
#define AFX_OVER_H__644CE0F1_7846_4F15_961A_BF206B6F84C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CompositeBox.h"

class CMOver : public CCompositeBox  
{
public:
	void Serialize(CArchive& ar);
	CString ToMathML(int nLevel);
	int GetType();
	void SetType(int n);
	CString ClassName();
	void SetCoord(int cx, int cy);
	void Draw(CDC* pDC);
	void Layout(CDC* pDC);
	CMOver(CBox* box, const int nType=1);
	CMOver();
	virtual ~CMOver();

private:
	int GetPenWidth();
	int GetGap();
	int m_nType;	//1: Single line
					//2: Double line
					//3: Vector arrow
					//4: Angle line
					//5: Arc line
					//6: Single dot
					//7: Double dot
					//8: Triad dot
					//9: Single tilde
					//10 Double tilde
					
};

#endif // !defined(AFX_OVER_H__644CE0F1_7846_4F15_961A_BF206B6F84C2__INCLUDED_)

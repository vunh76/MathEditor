// Box.h: interface for the CBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOX1_H__41B14C6F_3462_4620_A34F_61AC80ADA9FB__INCLUDED_)
#define AFX_BOX1_H__41B14C6F_3462_4620_A34F_61AC80ADA9FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
const TCHAR crlf[]	=	_T("\r\n");

class CBox : public CObject
{
	DECLARE_SERIAL(CBox)
public:
	virtual CString Signature();
	virtual void Serialize(CArchive& ar);
	CRect GetRect();
	virtual CString ToMathML(int nLevel);
	virtual CString ToLaTex();
	virtual CBox* RemoveBox(int nIndex);
	virtual BOOL IsSelected();
	virtual void SetSelect(BOOL b);
	virtual BOOL IsTemplate();
	virtual void SetTemplate(BOOL b);
	void SetIndex(int nIndex);
	int GetIndex();
	CBox();
	virtual ~CBox();
	void	SetWidth(int n);
	int		GetWidth();
	void	SetHeight(int n);
	int		GetHeight();
	void	SetAscent(int n);
	int		GetAscent();
	int		GetDescent();
	void	SetLeft(int n);
	int		GetLeft();
	void	SetTop(int n);
	int		GetTop();

	virtual void	Layout(CDC *pDC);
	virtual void	Draw(CDC *pDC);
	virtual CString ClassName();
	virtual CString CBox::ToString();
	virtual void	SetFontSize(int n);
	virtual int 	GetFontSize();
	void	SetParent(CBox *theParent);
	CBox*	GetParent();
	virtual void	SetCoord(int cx, int cy);
	virtual void	AddBox(CBox *box);
	virtual int		GetChildrenCount();
	virtual CBox*	GetBox(int nIndex);
	virtual void	SetBox(int nIndex, CBox *box);
	virtual void	InsertBox(int nIndex, CBox *box);
	virtual void	DeleteBox(int nIndex);
private:
	BOOL m_bSelected;
	BOOL m_bTemplate;
	int m_Index;	//The indexing of box in array (for MRow, MFrac etc)

	int	m_Width; 
	int m_Height;
	int m_Left;
	int m_Top;
	int m_Ascent;
	int m_FontSize;
	CBox* m_Parent;
};

#endif // !defined(AFX_BOX1_H__41B14C6F_3462_4620_A34F_61AC80ADA9FB__INCLUDED_)

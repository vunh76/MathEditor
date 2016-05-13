// SDIEditDoc.h : interface of the CSDIEditDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDIEDITDOC_H__F17CB587_CBD0_4434_9B93_297585AA4873__INCLUDED_)
#define AFX_SDIEDITDOC_H__F17CB587_CBD0_4434_9B93_297585AA4873__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSDIEditDoc : public CDocument
{
protected: // create from serialization only
	CSDIEditDoc();
	DECLARE_DYNCREATE(CSDIEditDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIEditDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSDIEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSDIEditDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIEDITDOC_H__F17CB587_CBD0_4434_9B93_297585AA4873__INCLUDED_)

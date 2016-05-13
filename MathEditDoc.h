// MathEditDoc.h : interface of the CMathEditDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHEDITDOC_H__611F83D9_82AF_4155_AE8A_0A8FBE772B66__INCLUDED_)
#define AFX_MATHEDITDOC_H__611F83D9_82AF_4155_AE8A_0A8FBE772B66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMathEditDoc : public CDocument
{
protected: // create from serialization only
	CMathEditDoc();
	DECLARE_DYNCREATE(CMathEditDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathEditDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMathEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMathEditDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHEDITDOC_H__611F83D9_82AF_4155_AE8A_0A8FBE772B66__INCLUDED_)

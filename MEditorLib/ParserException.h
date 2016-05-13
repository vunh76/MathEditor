// ParserException.h: interface for the CParserException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSEREXCEPTION_H__2A01964C_F48B_4974_89B1_5A4FCEC46C99__INCLUDED_)
#define AFX_PARSEREXCEPTION_H__2A01964C_F48B_4974_89B1_5A4FCEC46C99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParserException : public CException  
{
	DECLARE_DYNAMIC(CParserException)
public:
	CString GetErrMsg();
	CParserException(int errpos=-1, CString msg="");
	virtual ~CParserException();

private:
	CString m_strMsg;
	int m_nErrPos;
};

#endif // !defined(AFX_PARSEREXCEPTION_H__2A01964C_F48B_4974_89B1_5A4FCEC46C99__INCLUDED_)

// ParserMathText.h: interface for the CParserMathText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERMATHTEXT_H__0364469C_BF86_40EE_BD05_24BE59BC1906__INCLUDED_)
#define AFX_PARSERMATHTEXT_H__0364469C_BF86_40EE_BD05_24BE59BC1906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Parser.h"

class CParserMathText : public CParser  
{
public:
	CBox* Parse();
	CParserMathText(CString strSource);
	CParserMathText();
	virtual ~CParserMathText();

private:
	CString Entity();
	BOOL isSpecialChar(TCHAR ch);
	void ThrowInvalidArgument();
	CBox* Function(CString fName, CObArray& arg);
	CBox* Atom();
	TCHAR NextChar();
	CBox* Element();
	CBox* Factor();
	CBox* Term();
	CBox* Expression();
	void SkipSpaces();
	int m_nCurPos;
};

#endif // !defined(AFX_PARSERMATHTEXT_H__0364469C_BF86_40EE_BD05_24BE59BC1906__INCLUDED_)

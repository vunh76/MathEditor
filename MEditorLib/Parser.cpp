// Parser.cpp: implementation of the CParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Parser.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CParser::CParser()
{
	m_strSource="";
}

CParser::CParser(CString strSource)
{
	m_strSource=strSource;
}

CParser::~CParser()
{

}

CBox* CParser::Parse()
{
	return NULL;
}

BOOL CParser::isWhiteSpace(TCHAR ch)
{
	return (ch==' ' || ch=='\t' || ch=='\n');
}

BOOL CParser::isAlphaOrDigit(TCHAR ch)
{
	return ((ch>='0' && ch<='9') || (ch>='a' && ch<='z') || (ch>='A' && ch<='Z'));
}

BOOL CParser::isAlpha(TCHAR ch)
{
	return ((ch>='a' && ch<='z') || (ch>='A' && ch<='Z'));
}

BOOL CParser::isDigit(TCHAR ch)
{
	return (ch>='0' && ch<='9');
}

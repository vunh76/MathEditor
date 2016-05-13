// ParserException.cpp: implementation of the CParserException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ParserException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CParserException, CException)

CParserException::CParserException(int errpos, CString msg)
{
	if (msg="")
		msg="Unexpected error";
	m_nErrPos=errpos;
	m_strMsg=msg;
}

CParserException::~CParserException()
{

}

CString CParserException::GetErrMsg()
{
	return m_strMsg;
}

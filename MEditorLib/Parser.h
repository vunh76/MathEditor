// Parser.h: interface for the CParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSER_H__4BBDB404_985F_4C40_8F56_D3A005CC4273__INCLUDED_)
#define AFX_PARSER_H__4BBDB404_985F_4C40_8F56_D3A005CC4273__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "box.h"
#include "EditorCtrl.h"

class CParser  
{
public:
	CEditorCtrl* m_Editor;
	BOOL isDigit(TCHAR ch);
	BOOL isAlpha(TCHAR ch);
	BOOL isAlphaOrDigit(TCHAR ch);
	BOOL isWhiteSpace(TCHAR ch);
	virtual CBox* Parse();
	CParser(CString strSource);
	CParser();
	virtual ~CParser();

protected:
	CString m_strSource;
};

#endif // !defined(AFX_PARSER_H__4BBDB404_985F_4C40_8F56_D3A005CC4273__INCLUDED_)

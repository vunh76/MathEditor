// MacroCommand.h: interface for the CMacroCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MACROCOMMAND_H__F8CD8ADD_25A3_4D7A_B986_3AC9ADB58D55__INCLUDED_)
#define AFX_MACROCOMMAND_H__F8CD8ADD_25A3_4D7A_B986_3AC9ADB58D55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Command.h"

class CMacroCommand : public CCommand  
{
public:
	void UnExecute();
	void Execute();
	void AddCommand(CCommand* cmd);
	int GetCommandCount();
	CMacroCommand();
	virtual ~CMacroCommand();
private:
	CList<CCommand*,CCommand*> m_CmdList;
};

#endif // !defined(AFX_MACROCOMMAND_H__F8CD8ADD_25A3_4D7A_B986_3AC9ADB58D55__INCLUDED_)

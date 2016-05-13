// MacroCommand.cpp: implementation of the CMacroCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MacroCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMacroCommand::CMacroCommand()
{
	
}

CMacroCommand::~CMacroCommand()
{
	POSITION pos=m_CmdList.GetHeadPosition();
	while (pos)
		delete m_CmdList.GetNext(pos);
	
	m_CmdList.RemoveAll();
}

int CMacroCommand::GetCommandCount()
{
	return m_CmdList.GetCount();
}

void CMacroCommand::AddCommand(CCommand *cmd)
{
	m_CmdList.AddTail(cmd);
}

void CMacroCommand::Execute()
{
	POSITION pos = m_CmdList.GetHeadPosition();
	while (pos!=NULL)
		m_CmdList.GetNext(pos)->Execute();
	return;
}

void CMacroCommand::UnExecute()
{
	POSITION pos = m_CmdList.GetTailPosition();
	while (pos!=NULL)
		m_CmdList.GetPrev(pos)->UnExecute();
	return;
}

// Command.cpp: implementation of the CCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Command.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommand::CCommand()
{
	m_bUndoable=FALSE;
}

CCommand::~CCommand()
{

}

void CCommand::Execute()
{

}

void CCommand::UnExecute()
{

}

BOOL CCommand::IsUndoable()
{
	return m_bUndoable;
}

int CCommand::GetCommandCount()
{
	return 0;
}

void CCommand::AddCommand(CCommand *cmd)
{

}

CString CCommand::ClassName()
{
	return "";
}

void CCommand::ClearContent()
{

}

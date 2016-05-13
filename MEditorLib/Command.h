// Command.h: interface for the CCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMAND_H__A06A1489_2240_41E3_A75C_92E3F0B16BF3__INCLUDED_)
#define AFX_COMMAND_H__A06A1489_2240_41E3_A75C_92E3F0B16BF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommand  
{
public:
	virtual void ClearContent();
	virtual CString ClassName();
	virtual void AddCommand(CCommand* cmd);
	virtual int GetCommandCount();
	virtual BOOL IsUndoable();
	virtual void UnExecute();
	virtual void Execute();
	CCommand();
	virtual ~CCommand();

private:
	BOOL m_bUndoable;
};

#endif // !defined(AFX_COMMAND_H__A06A1489_2240_41E3_A75C_92E3F0B16BF3__INCLUDED_)

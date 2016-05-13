// ParserMathText.cpp: implementation of the CParserMathText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ParserMathText.h"
#include "MO.h"
#include "MRow.h"
#include "MI.h"
#include "MN.h"
#include "MFrac.h"
#include "MSubSup.h"
#include "MBrace.h"
#include "MRoot.h"
#include "MSymbol.h"
#include "Over.h"
#include "MEntity.h"
#include "ParserException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CParserMathText::CParserMathText(CString strSource)
{
	m_strSource=strSource;
}

CParserMathText::CParserMathText()
{

}

CParserMathText::~CParserMathText()
{

}

CBox* CParserMathText::Parse()
{
	CBox* box=NULL;
	CBox* box1=NULL;
	CBox* box2=NULL;
	TCHAR ch;
	m_nCurPos=0;
	try{
		box1=Expression();
		if (box1->ClassName()!="MRow"){
			box=new CMRow();
			box->AddBox(box1);
			box1=box;
		}
	}
	catch (CParserException* pe){
		throw pe;
	}
	
	while (m_nCurPos<m_strSource.GetLength()){
		ch=NextChar();
		if (ch=='='){
			try{
				box2=Expression();
				box1->AddBox(new CMO("="));
				if (box2->ClassName()!="MRow")
					box1->AddBox(box2);
				else{
					while (box2->GetChildrenCount()>0){
						box=box2->RemoveBox(0);
						box1->AddBox(box);
					}
					delete box2;
				}
			}
			catch (CParserException* pe){
				if (box1) delete box1;
				throw pe;
			}
		}
		else{
			if (box1) delete box1;
			throw new CParserException(m_nCurPos, "Expected end of input");	
		}
	}
	
	return box1;
}

void CParserMathText::SkipSpaces()
{
	while (m_nCurPos<m_strSource.GetLength() && isWhiteSpace(m_strSource[m_nCurPos]))
		m_nCurPos++;
}

CBox* CParserMathText::Expression()
{
	CBox* box=NULL;
	CBox* box1=NULL;
	CBox* box2=NULL;
	TCHAR ch;
	TCHAR ch1;
	SkipSpaces();
	try{
		box1=Term();
		if (box1->ClassName()!="MRow"){
			box=new CMRow();
			box->AddBox(box1);
			box1=box;
		}
	}
	catch (CParserException* pe){
		throw pe;
	}
	while (m_nCurPos<m_strSource.GetLength()){
		ch=NextChar();
		switch (ch){
		case '+':
			ch1=NextChar();
			if (ch1=='-'){
				box1->AddBox(new CMEntity(0x29, "Lucida Bright Math Symbol", "plusmn", "plusmn", "plusmn", TRUE, FALSE));
			}
			else{
				m_nCurPos--;
				box1->AddBox(new CMO("+"));
			}
			try{
				box2=Term();
				if (box2->ClassName()=="MRow"){
					while (box2->GetChildrenCount()>0){
						box=box2->RemoveBox(0);
						box1->AddBox(box);
					}
					delete box2;
				}
				else
					box1->AddBox(box2);
			}
			catch (CParserException* pe){
				if (box1) delete box1;
				throw pe;
			}
			break;
		case '-':
			ch1=NextChar();
			if (ch1=='+')
				box1->AddBox(new CMEntity(0x2A, "Lucida Bright Math Symbol", "mnplus", "mnplus", "mnplus", TRUE, FALSE));
			else{
				m_nCurPos--;
				box1->AddBox(new CMO("-","&minus;"));
			}
			try{
				box2=Term();
				if (box2->ClassName()=="MRow"){
					while (box2->GetChildrenCount()>0){
						box=box2->RemoveBox(0);
						box1->AddBox(box);
					}
					delete box2;
				}
				else
					box1->AddBox(box2);
			}
			catch (CParserException* pe){
				if (box1) delete box1;
				throw pe;
			}
			break;
		default:
			m_nCurPos--;
			return box1;
		}
	}
	return box1;
}

CBox* CParserMathText::Term()
{
	CBox* box=NULL;
	CBox* box1=NULL;
	CBox* box2=NULL;
	TCHAR ch;
	TCHAR ch1;
	SkipSpaces();	
	try{
		box1=Factor();
		if (box1->ClassName()!="MRow"){
			box=new CMRow();
			box->AddBox(box1);
			box1=box;
		}
	}
	catch (CParserException* pe){
		throw pe;
	}
	
	while (m_nCurPos<m_strSource.GetLength()){
		ch=NextChar();
		switch (ch){
		case '*':
			try{
				box2=Factor();
				box1->AddBox(new CMO("*","&times;"));
				if (box2->ClassName()=="MRow"){
					while (box2->GetChildrenCount()>0){
						box=box2->RemoveBox(0);
						box1->AddBox(box);
					}
					delete box2;
				}
				else
					box1->AddBox(box2);
			}
			catch (CParserException* pe){
				if (box1) delete box1;
				throw pe;
			}
			break;
		case '/':
			try{
				box2=Factor();
				_ASSERT(box2->ClassName()=="MRow");
				if (box1->GetBox(0)->ClassName()=="MBrace"){
					box=box1->GetBox(0)->RemoveBox(0);
					delete box1;
					box1=box;
				}

				if (box2->GetBox(0)->ClassName()=="MBrace"){
					box=box2->GetBox(0)->RemoveBox(0);
					delete box2;
					box2=box;
				}

				box=new CMFrac(box1, box2);
				box1=box;
				box=new CMRow();
				box->AddBox(box1);
				box1=box;
			}
			catch (CParserException* pe){
				if (box1) delete box1;
				throw pe;
			}
			break;
		case '<':
			ch1=NextChar();
			if (ch1=='=' || ch1=='>'){
				try{
					box2=Factor();
				}
				catch (CParserException* pe){
					if (box1) delete box1;
					throw pe;
				}
			}
			else{
				m_nCurPos--;
				try{
					box2=Factor();
				}
				catch (CParserException* pe){
					if (box1) delete box1;
					throw pe;
				}
			}
			if (ch1=='=')
				box1->AddBox(new CMO("<=","&le;"));
			else if (ch1=='>')
				box1->AddBox(new CMEntity(0x22, "Lucida Bright Math Symbol", "NotEqual", "NotEqual", "ne", TRUE, TRUE));
			else
				box1->AddBox(new CMO("<"));

			if (box2->ClassName()=="MRow"){
				while (box2->GetChildrenCount()>0){
					box=box2->RemoveBox(0);
					box1->AddBox(box);
				}
				delete box2;
			}
			else
				box1->AddBox(box2);

			break;

		case '>':
			ch1=NextChar();
			if (ch1=='='){
				try{
					box2=Factor();
				}
				catch (CParserException* pe){
					if (box1) delete box1;
					throw pe;
				}
			}
			else{
				m_nCurPos--;
				try{
					box2=Factor();
				}
				catch (CParserException* pe){
					if (box1) delete box1;
					throw pe;
				}
			}
			if (ch1=='=')
				box1->AddBox(new CMO(">=","&ge;"));
			else
				box1->AddBox(new CMO(">"));

			if (box2->ClassName()=="MRow"){
				while (box2->GetChildrenCount()>0){
					box=box2->RemoveBox(0);
					box1->AddBox(box);
				}
				delete box2;
			}
			else
				box1->AddBox(box2);

			break;

		default:
			m_nCurPos--;
			return box1;
			//throw new CParserException(m_nCurPos, "Expected an operator likes *, /");
		}
	}
	return box1;
}

CBox* CParserMathText::Factor()
{
	CBox* box;
	CBox* box1;
	CBox* box2;
	TCHAR ch;
	SkipSpaces();
	try{
		box1=Element();
		if (box1->ClassName()!="MRow"){
			box=new CMRow();
			box->AddBox(box1);
			box1=box;
		}
	}
	catch (CParserException* pe){
		throw pe;
	}
	
	while (m_nCurPos<m_strSource.GetLength()){
		ch=NextChar();
		switch (ch){
		case '^':
			try{
				box2=Element();
				//Supscript do not need brace
				if (box2->GetBox(0)->ClassName()=="MBrace"){
					box=box2->GetBox(0)->RemoveBox(0);
					delete box2;
					box2=box;
				}
				box=new CMSubSup(box1,NULL,box2);
				box1=box;

				box=new CMRow();
				box->AddBox(box1);
				box1=box;
			}
			catch (CParserException* pe){
				if (box1) delete box1;
				throw pe;
			}
			break;
		case '_':
			try{
				box2=Element();
				//Subscript do not need brace
				if (box2->GetBox(0)->ClassName()=="MBrace"){
					box=box2->GetBox(0)->RemoveBox(0);
					delete box2;
					box2=box;
				}
				box=new CMSubSup(box1, box2, NULL);
				box1=box;

				box=new CMRow();
				box->AddBox(box1);
				box1=box;
			}
			catch (CParserException* pe){
				if (box1) delete box1;
				throw pe;
			}
			break;
		default:
			m_nCurPos--;
			return box1;
		}
	}
	return box1;
}
/************************************************************
Parsing element. It may be parentheses or atom value
Called by Factor procudure
Input:
Output:
	New box objects
*************************************************************/
CBox* CParserMathText::Element()
{
	CBox* box=NULL;
	CBox* box1=NULL;
	BOOL bSign=FALSE;
	TCHAR ch;
	SkipSpaces();
	ch=NextChar();
	if (ch=='-')
		bSign=TRUE;
	else if (ch!='+')
		m_nCurPos--;
	
	ch=NextChar();
	if (ch=='('){
		try{
			box1=Expression();
			
			ch=NextChar();
			if (ch!=')'){
				if (box1) delete box1;
				throw new CParserException(m_nCurPos, "Expected a closed parentheses");
			}
			else{
				box=new CMBrace(box1);
				box1=box;

				box=new CMRow();
				box->AddBox(box1);
				box1=box;
			}
		}
		catch (CParserException* pe){
			throw pe;
		}
	}
	else{
		m_nCurPos--;
		try{
			box1=Atom();
		}
		catch (CParserException* pe){
			throw pe;
		}
	}
	if (bSign){
		_ASSERT(box1->ClassName()=="MRow");
		box1->InsertBox(0, new CMO("-","&minus;"));
	}
	return box1;
}
/*********************************************************
Return next character in input string and increasing m_nCurPos by one
Input:
Output:
	Next character
*********************************************************/
TCHAR CParserMathText::NextChar()
{
	SkipSpaces();
	if (m_nCurPos>=m_strSource.GetLength())
		return 0;
	m_nCurPos++;
	return m_strSource[m_nCurPos-1];
}
/**************************************************************
Parsing an atom element. It may be a function or any value
Input:
Output:
	New box objects
**************************************************************/
CBox* CParserMathText::Atom()
{
	CBox* box=NULL;
	CBox* box1=NULL;
	CStringArray entities;
	CObArray arg;
	CString st="";
	CString ss;
	TCHAR ch;
	TCHAR ch1;
	BOOL loop;
	CEditorCtrl::MATH_ENTITY me;
	SkipSpaces();
	while (m_nCurPos<m_strSource.GetLength()){
		ch=m_strSource[m_nCurPos];
		if (isAlphaOrDigit(ch)){
			st=st + m_strSource.Mid(m_nCurPos,1);
			entities.Add(m_strSource.Mid(m_nCurPos,1));
			m_nCurPos++;
		}
		else
			if (ch=='\\'){
				m_nCurPos++;		
				ss=Entity();
				if (ss=="")
					throw new CParserException(m_nCurPos,"Expected a special character or an entity name");
				ch1=NextChar();
				if (ch1!='\\' && ss.GetLength()>1)
					throw new CParserException(m_nCurPos,"Expected a ending of entity name");
				st=st+ss;
				entities.Add(ss);
			}
			else
				break;
		
	}
	if (st=="")
		throw new CParserException(m_nCurPos, "Expected an alphaset character");
	
	if (m_nCurPos<m_strSource.GetLength()){
		ch=NextChar();
		if (ch=='('){//Function?
			SkipSpaces();
			loop=TRUE;
			while (m_nCurPos<m_strSource.GetLength() && loop){
				try{
					box1=Expression();
					arg.Add(box1);
					ch=NextChar();
					switch (ch){
					case ')':
						loop=FALSE;
						break;
					case ',':
						break;
					default:
						for (int i=0; i<arg.GetSize(); i++)
							delete arg[i];
						arg.RemoveAll();
						if (box1) delete box1;
						throw new CParserException(m_nCurPos, "Expected ) or ,");
					}
				}
				catch (CParserException* pe){
					for (int i=0; i<arg.GetSize(); i++)
						delete arg[i];
					arg.RemoveAll();
					if (box1) delete box1;
					throw pe;
				}
			}
			box=Function(st, arg);
			box1=new CMRow();
			box1->AddBox(box);
			return box1;
		}
		else
			m_nCurPos--;
	}
	//Not function
	box=new CMRow();
	for (int i=0; i<entities.GetSize(); i++){
		st=entities[i];
		if (st.GetLength()==1){//Single char
			ch=st[0];
			if (isAlpha(ch) || isSpecialChar(ch))
				box->AddBox(new CMI(st));
			else if (isDigit(ch))
				box->AddBox(new CMN(st));
			else{ 
				_ASSERT(FALSE);
			}
		}
		else{
			me=m_Editor->GetEntityInfo(st);
			if (me.CharCode>0)
				box->AddBox(new CMEntity(me.CharCode, me.FontName, me.EntityName, me.MathMLName, me.LaTexName, me.bOperator, me.bInverted));
			else{
				delete box;
				throw new CParserException(m_nCurPos, "Unknown entity");
			}
		}		
	}
	return box;
}

/*******************************************************************
Parsing a function and return a box coresponding with that function
Input:
	CString fName: Function name
	CObArray arg: List of argument of function
Output:
	New box objects that represent function
*******************************************************************/
CBox* CParserMathText::Function(CString fName, CObArray &arg)
{
	CBox* box=NULL;
	TCHAR symsign;
	fName.MakeUpper();
	if (fName=="SQRT" || fName=="ROOT"){//Radical sign
		if (arg.GetSize()==1)
			box=new CMRoot((CBox*)arg[0]);
		else if (arg.GetSize()==2)
			box=new CMRoot((CBox*)arg[0], (CBox*)arg[1]);
		else{
			ThrowInvalidArgument();
		}
	}
	else if (fName=="SUM" || fName=="UNI" || fName=="INSEC" || fName=="PROD" || fName=="INT" || fName=="INT2" || fName=="INT3"){
		if (fName=="SUM")
			symsign=(TCHAR)0xAA;
		else if (fName=="UNI")
			symsign=(TCHAR)0x7E;
		else if (fName=="PROD")
			symsign=(TCHAR)0xA9;
		else if (fName=="INSEC")
			symsign=(TCHAR)0x80;
		else if (fName=="INT")
			symsign=(TCHAR)0x97;
		else if (fName=="INT2")
			symsign=(TCHAR)0xB0;
		else if (fName=="INT3")
			symsign=(TCHAR)0xB1;

		if (arg.GetSize()==1)
			box=new CMSymbol((CBox*)arg[0],NULL,NULL,symsign);
		else if (arg.GetSize()==2)
			box=new CMSymbol((CBox*)arg[0], (CBox*)arg[1],NULL,symsign);
		else if (arg.GetSize()==3)
			box=new CMSymbol((CBox*)arg[0], (CBox*)arg[1],(CBox*)arg[2],symsign);
		else
			ThrowInvalidArgument();
	}
	else if (fName=="OVER"){
		if (arg.GetSize()==1)
			box=new CMOver((CBox*)arg[0], 1);
		else
			ThrowInvalidArgument();
	}
	else if (fName=="DOVER"){//Double over
		if (arg.GetSize()==1)
			box=new CMOver((CBox*)arg[0], 2);
		else
			ThrowInvalidArgument();
	}
	else if (fName=="VEC"){//Vector
		if (arg.GetSize()==1)
			box=new CMOver((CBox*)arg[0], 3);
		else
			ThrowInvalidArgument();
	}
	else if (fName=="HAT"){//Hat
		if (arg.GetSize()==1)
			box=new CMOver((CBox*)arg[0], 4);
		else
			ThrowInvalidArgument();
	}
	else if (fName=="ARC"){//Arc
		if (arg.GetSize()==1)
			box=new CMOver((CBox*)arg[0], 5);
		else
			ThrowInvalidArgument();
	}
	else
		throw new CParserException(m_nCurPos, "Undefined function");
	return box;
}
/***********************************************************************
Throw an exception when number of argument is invalid
Called by Function procudure
***********************************************************************/
void CParserMathText::ThrowInvalidArgument()
{
	throw new CParserException(m_nCurPos, "Invalid number of argument");
}
/********************************************************
Check to see if after \ is an escape character
Input: 
	TCHAR ch: character to check
Output:
	TRUE/FAlSE
*********************************************************/
BOOL CParserMathText::isSpecialChar(TCHAR ch)
{
	return (ch=='~' || 
			ch=='!' || 
			ch=='@' || 
			ch=='#' || 
			ch=='$' || 
			ch=='%' ||
			ch=='^' ||
			ch=='&' ||
			ch=='*' ||
			ch=='(' ||
			ch==')' ||
			ch==':' ||
			ch==';' ||
			ch=='\\' ||
			ch=='|' ||
			ch==',' ||
			ch=='/');
}

CString CParserMathText::Entity()
{
	CString st="";
	TCHAR ch;
	while (m_nCurPos<m_strSource.GetLength()){
		ch=m_strSource[m_nCurPos];
		if (st!="" && isSpecialChar(ch))
			break;
		if (isSpecialChar(ch)){
			st=m_strSource.Mid(m_nCurPos,1);
			m_nCurPos++;
			break;
		}
		else if (isAlpha(ch)){
			st=st+m_strSource.Mid(m_nCurPos,1);
			m_nCurPos++;
		}
		else
			break;
	}
	return st;
}

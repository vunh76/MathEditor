// Factory.cpp: implementation of the CFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Box.h"
#include "MRow.h"
#include "MI.h"
#include "MO.h"
#include "MN.h"
#include "Over.h"
#include "MSubSup.h"
#include "MFrac.h"
#include "MSymbol.h"
#include "MUnderOver.h"
#include "MRoot.h"
#include "MBrace.h"
#include "Mtable.h"
#include "MEntity.h"

#include "Factory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFactory::CFactory()
{

}

CFactory::~CFactory()
{

}

CBox* CFactory::instance(CString ID)
{
	if (ID=="MI")
		return new CMI();
	if (ID=="MN")
		return new CMN();
	if (ID=="MO")
		return new CMO();
	if (ID=="MRow")
		return new CMRow();
	if (ID=="MF")
		return new CMFrac();
	if (ID=="MOver")
		return new CMOver();
	if (ID=="MRoot")
		return new CMRoot();
	if (ID=="MSubSup")
		return new CMSubSup();
	if (ID=="MTable")
		return new CMTable();
	if (ID=="MBrace")
		return new CMBrace();
	if (ID=="MEntity")
		return new CMEntity();
	if (ID=="MSymbol")
		return new CMSymbol();
	_ASSERT(FALSE);
	return NULL;
}

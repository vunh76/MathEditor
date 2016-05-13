// EditorCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "EditorCtrl.h"
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
#include "ParserMathText.h"
#include "ParserException.h"
#include "BoxHolder.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MATH_SYMBOL_FONT1	"Lucida Bright Math Symbol"
#define MATH_SYMBOL_FONT2	"Lucida Bright Math Italic"
#define MAX_WIDTH	5000
#define MAX_HEIGHT	5000
/////////////////////////////////////////////////////////////////////////////
// CEditorCtrl
IMPLEMENT_DYNCREATE(CEditorCtrl, CWnd)
/*****************************************************************************
Default contructor.
Register window class
Initialize m_Math, Selection, Cursor
Initialize array of original operator such as !,@,#...
******************************************************************************/
CEditorCtrl::CEditorCtrl()
{
	RegisterWindowClass();
	CF_MATHEQU=RegisterClipboardFormat("CF_MathEquation");
	_ASSERT(CF_MATHEQU!=0);
	m_nLeftMargin=0;
	m_nTopMargin=0;
	m_Math=new CMRow(new CMI(""));

	m_Cursor=new CCursor();
	m_Cursor->SetWindow(this);
	m_Cursor->SetRoot(m_Math);
	m_Cursor->SetBox(m_Math->GetBox(0));

	
	m_StartBox=NULL;
	m_EndBox=NULL;
	m_nBaseFontSize=12;
	m_Math->SetFontSize(m_nBaseFontSize);
	
	m_bCanAdd=TRUE;
	m_strFormula="";
	m_bCopyMathML=TRUE;
	m_bCopyImage=TRUE;

	origins.SetSize(26);

	origins[0].strName="`";
	origins[0].strMathML="&grave;";
	origins[0].strLaTeX="grave";
	origins[0].bOperator=TRUE;

	origins[1].strName="~";
	origins[1].strMathML="~";
	origins[1].strLaTeX="~";
	origins[1].bOperator=TRUE;

	origins[2].strName="!";
	origins[2].strMathML="!";
	origins[2].strLaTeX="!";
	origins[2].bOperator=TRUE;

	origins[3].strName="@";
	origins[3].strMathML="&commat;";
	origins[3].strLaTeX="commat";
	origins[3].bOperator=TRUE;

	origins[4].strName="#";
	origins[4].strMathML="&num;";
	origins[4].strLaTeX="num";
	origins[4].bOperator=TRUE;

	origins[5].strName="$";
	origins[5].strMathML="$";
	origins[5].strLaTeX="$";
	origins[5].bOperator=FALSE;

	origins[6].strName="%";
	origins[6].strMathML="%";
	origins[6].strLaTeX="%";
	origins[6].bOperator=TRUE;

	origins[7].strName="^";
	origins[7].strMathML="&circ;";
	origins[7].strLaTeX="circ";
	origins[7].bOperator=TRUE;

	origins[8].strName="&";
	origins[8].strMathML="&amp;";
	origins[8].strLaTeX="amp";
	origins[8].bOperator=TRUE;

	origins[9].strName="(";
	origins[9].strMathML="(";
	origins[9].strLaTeX="(";
	origins[9].bOperator=TRUE;

	origins[10].strName=")";
	origins[10].strMathML=")";
	origins[10].strLaTeX=")";
	origins[10].bOperator=TRUE;

	origins[11].strName="_";
	origins[11].strMathML="&lowbar;";
	origins[11].strLaTeX="lowbar";
	origins[11].bOperator=TRUE;

	origins[12].strName="[";
	origins[12].strMathML="[";
	origins[12].strLaTeX="[";
	origins[12].bOperator=TRUE;

	origins[13].strName="{";
	origins[13].strMathML="{";
	origins[13].strLaTeX="{";
	origins[13].bOperator=TRUE;

	origins[14].strName="]";
	origins[14].strMathML="]";
	origins[14].strLaTeX="]";
	origins[14].bOperator=TRUE;

	origins[15].strName="}";
	origins[15].strMathML="}";
	origins[15].strLaTeX="}";
	origins[15].bOperator=TRUE;

	origins[16].strName=":";
	origins[16].strMathML=":";
	origins[16].strLaTeX=":";
	origins[16].bOperator=TRUE;

	origins[17].strName=";";
	origins[17].strMathML=";";
	origins[17].strLaTeX=";";
	origins[17].bOperator=TRUE;

	origins[18].strName="'";
	origins[18].strMathML="&apos;";
	origins[18].strLaTeX="apos";
	origins[18].bOperator=TRUE;

	origins[19].strName="\"";
	origins[19].strMathML="&quot;";
	origins[19].strLaTeX="quot";
	origins[19].bOperator=TRUE;

	origins[20].strName=",";
	origins[20].strMathML=",";
	origins[20].strLaTeX=",";
	origins[20].bOperator=TRUE;

	origins[21].strName=".";
	origins[21].strMathML=".";
	origins[21].strLaTeX=".";
	origins[21].bOperator=TRUE;

	origins[22].strName="/";
	origins[22].strMathML="&sol;";
	origins[22].strLaTeX="sol";
	origins[22].bOperator=TRUE;

	origins[23].strName="?";
	origins[23].strMathML="?";
	origins[23].strLaTeX="?";
	origins[23].bOperator=TRUE;

	origins[24].strName="\\";
	origins[24].strMathML="&bsol;";
	origins[24].strLaTeX="bsol";
	origins[24].bOperator=TRUE;

	origins[25].strName="|";
	origins[25].strMathML="&verbar;";
	origins[25].strLaTeX="verbar";
	origins[25].bOperator=TRUE;

}
/***************************************************************************
Default destructor.
Delete and free memory that hold formula
****************************************************************************/
CEditorCtrl::~CEditorCtrl()
{
	if (m_Math)
		delete m_Math;
	if (m_Cursor)
		delete m_Cursor;
	m_StartBox=NULL;
	m_EndBox=NULL;
	m_Cursor=NULL;
	m_Math=NULL;	
	entities.RemoveAll();
}


BEGIN_MESSAGE_MAP(CEditorCtrl, CWnd)
	//{{AFX_MSG_MAP(CEditorCtrl)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/******************************************************************************
Register window class
Output:
	Success or not	
*******************************************************************************/
BOOL CEditorCtrl::RegisterWindowClass()
{
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();

    if (!(::GetClassInfo(hInst, FORMULACTRL_CLASSNAME, &wndcls)))
    {
        // otherwise we need to register a new class
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground    = ::GetSysColorBrush(COLOR_WINDOW);
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = FORMULACTRL_CLASSNAME;
        if (!AfxRegisterClass(&wndcls))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }
    return TRUE;
}

/**************************************************************************************
Member function to create window. It is same as create function of CWnd
Input:
	RECT rect:	rectangle of window
	CWnd* pParentWnd:	Parent of window
	UINT nID: Identifier of window
	DWORD dwStyle: Style of window.
Output:
	Success or not
Usage:
	In dialog box or anywhere that want to create this control, just call Create function
	to create it before operate any action.
***************************************************************************************/
BOOL CEditorCtrl::Create(const RECT &rect, CWnd *pParentWnd, UINT nID, DWORD dwStyle)
{
    ASSERT(pParentWnd->GetSafeHwnd());
	if (!CWnd::Create(FORMULACTRL_CLASSNAME, NULL, dwStyle, rect, pParentWnd, nID))
		return FALSE;
	//EnableScrollBarCtrl(SB_BOTH, TRUE); 
	return TRUE;
}
/***************************************************************************************
Set m_Math to another box object.
Input:
	CBox* box: box objects that stores in m_Math and display in control
Usage:
	Use this function when creating other box object and want to set it to display in control
	for editing.
***************************************************************************************/
void CEditorCtrl::SetMath(CBox *box)
{
	m_Math=box;
}

/****************************************************************************************
Get mathematical formula object currently appearent on control
Output:
	CBox*
****************************************************************************************/
CBox* CEditorCtrl::GetMath()
{
	return m_Math;
}
/****************************************************************************************
Manual destroy mathematical formula object that currently belong to control
Be carefull when using this function. It may impact with undo list
*****************************************************************************************/
void CEditorCtrl::DestroyMath()
{
	if (m_Math)
		delete m_Math;
	if (m_Cursor)
		delete m_Cursor;
	m_Math=NULL;
	m_Cursor=NULL;
}
/******************************************************************************************
Message handler to process WM_PAINT. Just pass control to OnDraw
******************************************************************************************/
void CEditorCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC MemDC;
	CBitmap bitmap;
	CBitmap *pOldBitmap;
	MemDC.CreateCompatibleDC(&dc);
	CRect rect;
	GetClientRect(rect);

	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
 	pOldBitmap = MemDC.SelectObject(&bitmap);
	
	MemDC.SetWindowOrg(0,0);
	MemDC.FillSolidRect(rect, ::GetSysColor(COLOR_WINDOW));

	CPoint vporg;
	vporg.x=-GetScrollPos(SB_HORZ);
	vporg.y=-GetScrollPos(SB_VERT);
	CPoint pt=MemDC.SetViewportOrg(vporg);	
    OnDraw(&MemDC);
	MemDC.SetViewportOrg(pt);
	dc.BitBlt(0, 
		0, 
		rect.Width(), 
		rect.Height(),
		&MemDC, 
		0,
		0,
		SRCCOPY);

	// Swap back the original bitmap.
	MemDC.SelectObject(pOldBitmap);

	if (!(m_StartBox && m_EndBox) && GetFocus()==this)
		m_Cursor->ShowCaret();

	// Do not call CWnd::OnPaint() for painting messages
}
/******************************************************************************************
Message handler to process when control lost focus. Just hide caret
******************************************************************************************/
void CEditorCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
	if (m_Cursor)
		m_Cursor->DestroyCaret();
	// TODO: Add your message handler code here
	
}
/******************************************************************************************
Message handler to process when control get focus. Just show caret
******************************************************************************************/
void CEditorCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	if (m_Cursor && !m_StartBox && !m_EndBox)
		m_Cursor->ShowCaret();
	// TODO: Add your message handler code here
	
}
/******************************************************************************************
Message handler to process when control get WM_KEYDOWN.
Process arrow keys, HOME, END, shortcut keys...
******************************************************************************************/
void CEditorCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	int sh=IsSHIFTpressed();
	int ctrl=IsCTRLpressed();
	switch (nChar){
	case 'C':
		if (ctrl && !sh)
			CopyToClipboard();
		break;
	case 'V':
		if (ctrl && !sh)
			PasteFromClipboard();
		break;
	case 'X':
		if (ctrl && !sh)
			CutToClipboard();
		break;
	case 'A':
		if (!(ctrl && !sh))
			break;
		if (m_StartBox==m_Math->GetBox(0) && m_EndBox==m_Math->GetBox(m_Math->GetChildrenCount()-1))
			break;
		{
		m_StartBox=m_Math->GetBox(0);
		m_EndBox=m_Math->GetBox(m_Math->GetChildrenCount()-1);
		for (int i=0; i<m_Math->GetChildrenCount(); i++)
			m_Math->GetBox(i)->SetSelect(TRUE);
		m_Cursor->SetBox(m_EndBox);
		m_Cursor->SetEndBox(TRUE);
		m_Cursor->DestroyCaret();
		Invalidate();
		break;
		}
	case VK_RIGHT:
		ProcessRIGHTkey(sh);
		CheckCaretVisible();
		break;
	case VK_LEFT:
		ProcessLEFTkey(sh);
		CheckCaretVisible();
		break;
	case VK_UP:
		ClearSelection();
		m_Cursor->MoveUp();
		m_Cursor->ShowCaret();
		CheckCaretVisible();
		break;
	case VK_DOWN:
		ClearSelection();
		m_Cursor->MoveDown();
		m_Cursor->ShowCaret();
		CheckCaretVisible();
		break;
	case VK_DELETE:
		ProcessDelKey();
		break;
	case VK_HOME:
		ProcessHOMEkey(sh);
		break;
	case VK_END:
		ProcessENDkey(sh);
		break;
	default:
		if (ctrl){
			ProcessShortCut(nChar);
			return;
		}		
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
/******************************************************************************************
Clear current selection range by set all box in that range to not selected state
******************************************************************************************/
void CEditorCtrl::ClearSelection()
{
	if (m_StartBox && m_EndBox){
		CBox* box=m_StartBox->GetParent();
		for (int i=m_StartBox->GetIndex(); i<=m_EndBox->GetIndex(); i++){
			SelectBox(box->GetBox(i),FALSE);
		}
		m_StartBox=NULL;
		m_EndBox=NULL;
	}
}
/******************************************************************************************
Delete current selection range.
******************************************************************************************/
int CEditorCtrl::DeleteSelection()
{
	int k=-1;
	if (m_StartBox && m_EndBox){
		k=m_StartBox->GetIndex();
		CBox* box=m_StartBox->GetParent();
		for (int i=k; i<=m_EndBox->GetIndex();)//Do not increase counter
			box->DeleteBox(i);
		m_StartBox=NULL;
		m_EndBox=NULL;
		if (box->GetChildrenCount()==0)
			box->AddBox(new CMI(""));
		if (k>0){
			m_Cursor->SetBox(box->GetBox(k-1));
			m_Cursor->SetEndBox(TRUE);
		}
		else{
			m_Cursor->SetBox(box->GetBox(k));
			m_Cursor->SetEndBox(FALSE);
		}
		if (box->IsTemplate())
			m_Cursor->SetEndBox(TRUE);

	}
	return k;
}
/******************************************************************************************
Insert a box into formula
Input:
	CBox* box: box object will be inserted
Usage:
	This is a core function when working with WYSIWYG mode.
	Anytime an action which can lead to creating new symbol, a new box will be created
	and insert into formula by calling this function
******************************************************************************************/
void CEditorCtrl::InsertBox(CBox *box)
{
	CBox* box1;
	CBox* box2;
	CBox* box3;
	int k, i, j, l;

	BOOL flag;
	if (m_StartBox && m_EndBox && box->GetChildrenCount()>0){
		//Trong truong hop dang co box duoc chon va box chen vao
		//thuoc dang Composite, chuyen tat ca cac box dang chon thanh
		//the first child cua box can chen bang cach Remove chung
		//ra khoi parent cu, chuyen vao parent moi.
		box1=box->GetBox(0);//Must be MRow;
		box2=m_StartBox->GetParent();//Must be MRow
		k=m_StartBox->GetIndex();
		l=m_EndBox->GetIndex();
		box3=box2->RemoveBox(k);
		//box3->SetSelect(FALSE);
		box1->SetBox(0,box3);//First box of box1 always is template
		i=k;
		j=l-i;
		while (j>0){
			box1->AddBox(box2->RemoveBox(i));
			//box1->GetBox(box1->GetChildrenCount()-1)->SetSelect(FALSE);
			j--;
		}
		//Uncomment two lines bellow to clear selection
		//m_StartBox=NULL;
		//m_EndBox=NULL;
		//Neu m_StartBox va m_EndBox chiem toan bo box2
		//them cho no mot template truoc khi chen box
		//m_Cursor->SetBox(m_EndBox);
		if (box2->GetChildrenCount()==0)
			box2->AddBox(new CMI(""));
		if (!box2->IsTemplate())
			box2->InsertBox(k,box);
		else
			box2->SetBox(k,box);
		//Uncomment two lines bellow to set correct cursor if
		//the selection was cleared.
		//m_Cursor->SetBox(box1->GetBox(box1->GetChildrenCount()-1));
		//m_Cursor->SetEndBox(TRUE);
		return;
	}
	//Truong hop chen box vao equation ma tren do khong co lua chon
	//hoac box can chen khong the chua children.
	//Tim cach chen box vao vi tri cua cursor
	box1=m_Cursor->GetParent();
	k=m_Cursor->GetIndex();
	flag=m_Cursor->IsEndBox();
	//Neu cursor la mot template va khong chua children
	if (m_Cursor->IsTemplate() && m_Cursor->GetChildrenCount()==0){
		box1->SetBox(k, box); 
	}
	else
		if (flag)
			box1->InsertBox(k+1,box);
		else{
			box1->InsertBox(k,box);
			m_Cursor->SetEndBox(TRUE);
		}
	m_Cursor->SetBox(box);	
	if (box->GetChildrenCount()>0)
		m_Cursor->MoveLeft();
	
}
/******************************************************************************************
Message handler to process when control get WM_LBUTTONDOWN. 
Detect which box can get new focus
******************************************************************************************/
void CEditorCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetFocus();
	if (m_StartBox && m_EndBox)
		ClearSelection();
	if (m_Cursor){
		int ox=GetScrollPos(SB_HORZ);
		int oy=GetScrollPos(SB_VERT);
		m_Cursor->MoveInPoint(point.x+ox, point.y+oy);
		m_Cursor->ShowCaret();
	}
	CWnd::OnLButtonDown(nFlags, point);
}
/******************************************************************************************
Switch a box between selected and not selected state
Input:
	CBox* box
	BOOL	b: selected or not
Usage:
	This function only fill in box rectangle with suitale color depend on its state
******************************************************************************************/
void CEditorCtrl::SelectBox(CBox *box, BOOL b)
{
	int x, y, cx, cy;
	int ox, oy;
	ox=-GetScrollPos(SB_HORZ);
	oy=-GetScrollPos(SB_VERT);
	CBox* box1=box->GetParent();
	CDC* pDC=GetDC();
	x=box->GetLeft()+ox;
	y=box1->GetTop()+oy;
	cx=box->GetWidth();
	cy=box1->GetHeight();
	if (b)//Selection
		pDC->FillSolidRect(x,y,cx,cy,RGB(0,0,0));
	else
		pDC->FillSolidRect(x,y,cx,cy,RGB(255,255,255));
	int bk=pDC->SetBkMode(TRANSPARENT);
	box->SetSelect(b);
	CPoint pt=pDC->SetViewportOrg(ox, oy);
	box->Draw(pDC);
	pDC->SetViewportOrg(pt);
	pDC->SetBkColor(bk);
	ReleaseDC(pDC);
}
/******************************************************************************************
Message handler to process when control when get WM_CHAR.
If nChar is one of few special operator such as +, -, *...then it will be treated separatly
******************************************************************************************/
void CEditorCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (nChar!=8 && !m_bCanAdd){
		AfxMessageBox("The mathematical formula's dimentions have excessed the limitation\nPlease remove at least an item");
		return;
	}
	CBox* box=NULL;
	if (nChar>='0' && nChar<='9')
		box=new CMN(nChar);
	else if (nChar=='+')
		box=new CMO('+');
	else if (nChar=='-')
		box=new CMO('-',"&minus;");
	else if (nChar=='*')
		box=new CMO('*',"&times;");
	else if (nChar=='=')
		box=new CMO('=');
	else if (nChar=='<')
		box=new CMO('<');
	else if (nChar=='>')
		box=new CMO('>');
	else if (nChar==32 || (nChar>='a' && nChar<='z') || (nChar>='A' && nChar<='Z'))
		box=new CMI(nChar);
	else{
		int k=FindOriginalChar(nChar);
		if (k>=0)
			if (origins[k].bOperator)
				box=new CMO(nChar, origins[k].strMathML, origins[k].strLaTeX);
			else
				box=new CMI(nChar);
	}
	if (box){
		DeleteSelection();
		InsertBox(box);
	}
	if (nChar==8){//Backspace key
		ProcessBackSpaceKey();
	}
	if (nChar==8)
		Redraw(FALSE);
	else
		Redraw();
	CWnd::OnChar(nChar, nRepCnt, nFlags);
}
/******************************************************************************************
Message handler to make control can get keyboard message
******************************************************************************************/
BOOL CEditorCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_CHAR || pMsg->message == WM_KEYDOWN){
		switch ((int)pMsg->wParam)
		{
			case	VK_TAB:
			case	VK_RETURN:
			case	VK_ESCAPE:
				return FALSE;
		}
 		::TranslateMessage(pMsg);
 		::DispatchMessage(pMsg);
 		return TRUE;
 	}
	return CWnd::PreTranslateMessage(pMsg);
 }

void CEditorCtrl::InsertElement(CString id, int more)
{
	if (!m_bCanAdd)
		return;

	if (id=="MFrac"){
		CMFrac* box=new CMFrac(
							new CMRow(
								new CMI("")
							),
							new CMRow(
								new CMI("")
							)
						);
		InsertBox(box);
	}
	if (id=="MRoot"){
		InsertBox(InsertRoot(more));
	}
	if (id=="MSub"){//Box, Box, NULL
		CMSubSup* box=new CMSubSup(
							new CMRow(
								new CMI("")
							),
							new CMRow(
								new CMI("")
							),
							NULL
						);
		InsertBox(box);
	}
	
	if (id=="MSup"){//Box, NULL, Box
		CMSubSup* box=new CMSubSup(
							new CMRow(
								new CMI("")
							),
							NULL,
							new CMRow(
								new CMI("")
							)
						);
		InsertBox(box);
	}

	if (id=="MSubSup"){//Box, Box, Box
		CMSubSup* box=new CMSubSup(
							new CMRow(
								new CMI("")
							),
							new CMRow(
								new CMI("")
							),
							new CMRow(
								new CMI("")
							)
						);
		InsertBox(box);
	}
	
	if (id=="MUnderOver"){
		InsertBox(InsertUnderOver(more-6));
	}
	if (id=="MOver"){
		CMOver* box=new CMOver(
							new CMRow(
								new CMI("")
							),
							more+1
						);
		InsertBox(box);
	}
	
	if (id=="SUM"){
		if (more<4)
			InsertBox(InsertSum(more, (char)0xAA));
		else if (more<8)
			InsertBox(InsertSum(more-4, (char)0xA9));	
		else if (more<12)
			InsertBox(InsertSum(more-8, (char)0x7E));	
		else if (more<16)
			InsertBox(InsertSum(more-12, (char)0x80));	
	}
	
	if (id=="INT"){
		if (more<4)
			InsertBox(InsertSum(more, (char)0x97));
		else if (more<8)
			InsertBox(InsertSum(more-4, (char)0xB0));
		else if (more<12)
			InsertBox(InsertSum(more-8, (char)0xB1));
	}

	if (id=="Brace"){
		CMBrace* box=new CMBrace( new CMRow (new CMI("")),more);
		InsertBox(box);
	}

	if (id=="MTable"){
		int r, c;
		CMTable* box;
		switch (more){
		case 0:
			r=1;
			c=2;
			break;
		case 1:
			r=2;
			c=1;
			break;
		case 2:
			r=2;
			c=2;
			break;
		case 3:
			r=1;
			c=3;
			break;
		case 4:
			r=3;
			c=1;
			break;
		case 5:
			r=3;
			c=3;
			break;
		case 6:
			r=1;
			c=4;
			break;
		case 7:
			r=4;
			c=1;
			break;
		case 8:
			r=4;
			c=4;
			break;
		default:
			//CMaxtrixProperty dlg;
			//dlg.DoModal();
			r=5;
			c=5;
			break;
		}
		box=new CMTable(r,c);
		InsertBox(box);
	}

	Redraw();
}

void CEditorCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd::PreSubclassWindow();
	static BOOL bInProcedure = FALSE;
    if (bInProcedure)
        return;
    bInProcedure = TRUE;

    if (::IsWindow(m_hWnd))
        ModifyStyleEx(0, WS_EX_CLIENTEDGE);

	// Kludge: Make sure the client edge shows
	// This is so horrible it makes my eyes water.
	CRect rect;
	GetWindowRect(rect);
	CWnd* pParent = GetParent();
	if (pParent != NULL)
		pParent->ScreenToClient(rect);
	rect.InflateRect(1,1);	MoveWindow(rect);
	rect.DeflateRect(1,1);  MoveWindow(rect);
 
    bInProcedure = FALSE;
    return;
}



void CEditorCtrl::SetBaseFontSize(int n)
{
	m_nBaseFontSize=n;
	Invalidate();
}

int CEditorCtrl::GetBaseFontSize()
{
	return m_nBaseFontSize;
}

CBox* CEditorCtrl::InsertSum(int more, char ch)
{
	CBox *box1=new CMRow(new CMI(""));
	CBox *box2=NULL;
	CBox *box3=NULL;
	if (more==0){
		box2=new CMRow(
					new CMI("")
					);
		box3=new CMRow(
					new CMI("")
					);
	}
	if (more==1)
		box2=new CMRow(
					new CMI("")
					);
	if (more==2)
		box3=new CMRow(
					new CMI("")
					);
	return new CMSymbol(box1, box2, box3, ch);
}



CBox* CEditorCtrl::InsertUnderOver(int nType)
{
	CBox* box1=NULL;
	CBox* box2=NULL;
	CBox* box3=NULL;
	box1=new CMRow(new CMI(""));
	if (nType==2){
		box2=new CMRow(new CMI(""));
		box3=new CMRow(new CMI(""));
	}
	else if (nType==0)
		box2=new CMRow(new CMI(""));
	else
		box3=new CMRow(new CMI(""));
	return (new CMUnderOver(box1, box2, box3));
}

CBox* CEditorCtrl::InsertRoot(int more)
{
	CMRoot* box;
	if (more==1)
		box=new CMRoot(
				new CMRow(
					new CMI("")
					)
				);
	else
		box=new CMRoot(
				new CMRow(
					new CMI("")
					),
				new CMRow(
					new CMI("")
					)
				);
	return box;
}

void CEditorCtrl::ProcessDelKey()
{
	int k;
	CBox* box;
	CBox* box1;
	if (DeleteSelection()>=0){
		Redraw(FALSE);
		return;
	}
	k=m_Cursor->GetIndex();
	box=m_Cursor->GetBox();
	box1=m_Cursor->GetParent();
	if (k==0 && !m_Cursor->IsEndBox()){//Cursor's position is first row
		if (box1->GetChildrenCount()>1 || box->IsTemplate()){
			box1->DeleteBox(k);
			if (box1->GetChildrenCount()>0)
				m_Cursor->SetBox(box1->GetBox(k));
			else{
				box1->AddBox(new CMI(""));
				m_Cursor->SetBox(box1->GetBox(0));
				m_Cursor->SetEndBox(TRUE);
			}
			Redraw(FALSE);
			return;
		}
		else if (box->GetChildrenCount()==0){
			box->SetTemplate(TRUE);
			m_Cursor->SetEndBox(TRUE);
			Redraw(FALSE);
			return;
		}
		else{
			m_StartBox=m_Cursor->GetBox();
			m_EndBox=m_StartBox;
			m_Cursor->HideCaret();
			SelectBox(m_StartBox,TRUE);
			return;
		}
	}
	else{
		if (k==box1->GetChildrenCount()-1)
			return;
		if (box1->GetBox(k+1)->GetChildrenCount()==0 || box1->GetBox(k+1)->IsTemplate()){
			box1->DeleteBox(k+1);
			Redraw(FALSE);
			return;
		}
		else{
			m_Cursor->HideCaret();
			m_Cursor->SetBox(box1->GetBox(k+1));
			m_StartBox=m_Cursor->GetBox();
			m_EndBox=m_StartBox;
			SelectBox(m_StartBox,TRUE);
			return;
		}
	}
}

void CEditorCtrl::ProcessBackSpaceKey()
{
	int k;
	CBox* box=NULL;
	CBox* box1=NULL;
	k=DeleteSelection();//Try to delete selection.
	if (k>=0){//If have selection, Just return after redraw
		return;
	}
	k=m_Cursor->GetIndex();
	box1=m_Cursor->GetParent();//Must be MRow
	box=m_Cursor->GetBox();
	if (k>0)
		if (box->GetChildrenCount()==0){ //Cursor la mot box kieu text
			box1->DeleteBox(k);
			m_Cursor->SetBox(box1->GetBox(k-1));
			m_Cursor->SetEndBox(TRUE);
		}
		else{ //Cursor la mot box co children
			//Select box by setting m_StartBox and m_EndBox to Cursor
			m_StartBox=m_Cursor->GetBox();
			m_EndBox=m_StartBox;
			m_Cursor->HideCaret();
			SelectBox(m_StartBox, TRUE);
			return;
		}
	else //k=0. First box on row
		if (m_Cursor->IsEndBox()){ 
			if (box1->GetChildrenCount()>1){
				if  (box->GetChildrenCount()==0){
					box1->DeleteBox(k);
					m_Cursor->SetBox(box1->GetBox(k));
					m_Cursor->SetEndBox(FALSE);
				}
				else{
					m_StartBox=m_Cursor->GetBox();
					m_EndBox=m_StartBox;
					m_Cursor->HideCaret();
					SelectBox(m_StartBox, TRUE);
					return;
				}
			}
			else
				if (box->GetChildrenCount()==0){
					if (!box->IsTemplate()){
						box->SetTemplate(TRUE);
						return;
					}
					else
						if (m_Cursor->MoveLeft()) m_Cursor->ShowCaret();
				}
				else{
					m_Cursor->HideCaret();
					m_StartBox=box;
					m_EndBox=box;
					SelectBox(box, TRUE);
					return;
				}
		}
		else 
			if (m_Cursor->MoveLeft()) m_Cursor->ShowCaret();
		
}

void CEditorCtrl::OnDraw(CDC *pDC)
{
	int oldBkMode=pDC->SetBkMode(TRANSPARENT);
	
	m_Math->Layout(pDC);
	m_Math->SetCoord(m_nLeftMargin,m_nTopMargin);
	if (m_Math->GetWidth()>=MAX_WIDTH || m_Math->GetHeight()>=MAX_HEIGHT)
		m_bCanAdd=FALSE;
	else
		m_bCanAdd=TRUE;
	if (m_StartBox && m_EndBox){
		int x,y,cx,cy;
		CBox* box=m_StartBox->GetParent();
		x=m_StartBox->GetLeft();
		y=box->GetTop();
		cy=box->GetHeight();
		cx=0;
		for (int i=m_StartBox->GetIndex(); i<=m_EndBox->GetIndex(); i++)
			cx+=box->GetBox(i)->GetWidth();
		pDC->FillSolidRect(x,y,cx,cy,RGB(0,0,0));
	}
	m_Math->Draw(pDC);
	pDC->SetBkMode(oldBkMode);	
}

void CEditorCtrl::ProcessENDkey(int sh)
{
	CBox* box;
	box=m_Cursor->GetParent();
	int k;
	if (!sh && m_StartBox && m_EndBox){
			m_Cursor->SetEndBox(TRUE);
			m_Cursor->SetBox(m_EndBox);
			ClearSelection();
			m_Cursor->ShowCaret();
	}
	else if (sh){//Select until reach end of row
		if (!m_StartBox){
			if (!m_Cursor->IsEndBox())
				m_StartBox=m_Cursor->GetBox();
			else{
				k=m_Cursor->GetBox()->GetIndex();
				if (k==box->GetChildrenCount()-1)//End of row
					return;
				m_StartBox=box->GetBox(k+1);
			}
		}
		if (!m_EndBox)
			k=m_StartBox->GetIndex();
		else
			k=m_EndBox->GetIndex();
		for (int i=k; i<box->GetChildrenCount(); i++){
			m_EndBox=box->GetBox(i);
			SelectBox(m_EndBox, TRUE);
		}
		m_Cursor->SetBox(box->GetBox(box->GetChildrenCount()-1));
		m_Cursor->SetEndBox(TRUE);
		m_Cursor->DestroyCaret();
	}
	else{
		m_Cursor->SetBox(box->GetBox(box->GetChildrenCount()-1));
		m_Cursor->SetEndBox(TRUE);
		m_Cursor->ShowCaret();
	}
	CheckCaretVisible();
}

void CEditorCtrl::ProcessHOMEkey(int sh)
{
	CBox* box;
	box=m_Cursor->GetParent();
	int k;
	if (!sh && m_StartBox && m_EndBox){
		m_Cursor->SetEndBox(FALSE);
		m_Cursor->SetBox(m_StartBox);
		ClearSelection();
		m_Cursor->ShowCaret();
	}
	else if (sh){//Select until reach beginning of row
		if (!m_EndBox){
			if (m_Cursor->IsEndBox())
				m_EndBox=m_Cursor->GetBox();
			else{
				k=m_Cursor->GetBox()->GetIndex();
				if (k==0)//Begin of row
					return;
				m_EndBox=box->GetBox(k-1);
			}
		}
		if (!m_StartBox)
			k=m_EndBox->GetIndex();
		else
			k=m_StartBox->GetIndex();
		for (int i=k; i>=0; i--){
			m_StartBox=box->GetBox(i);
			SelectBox(m_StartBox, TRUE);
		}
		m_Cursor->SetBox(box->GetBox(0));
		m_Cursor->SetEndBox(FALSE);
		m_Cursor->DestroyCaret();
	}
	else{
		m_Cursor->SetBox(box->GetBox(0));
		m_Cursor->SetEndBox(FALSE);
		m_Cursor->ShowCaret();
	}
	CheckCaretVisible();
}

void CEditorCtrl::ProcessLEFTkey(int sh)
{
	int k;
	CBox* box;
	CBox* box1;
	if (!sh && m_StartBox && m_EndBox){
		if (m_StartBox->GetIndex()==0){
			m_Cursor->SetEndBox(FALSE);
			m_Cursor->SetBox(m_StartBox);
		}
		else{
			m_Cursor->SetEndBox(TRUE);
			m_Cursor->SetBox(m_StartBox->GetParent()->GetBox(m_StartBox->GetIndex()-1));
		}
		ClearSelection();
		m_Cursor->ShowCaret();
	}
	else if (!sh){
		if (m_Cursor->MoveLeft()) 
			m_Cursor->ShowCaret();
	}
	else{//SHIFT pressed
		k=m_Cursor->GetIndex();
		box=m_Cursor->GetParent();
		if (m_StartBox && m_EndBox){
			if (m_StartBox->GetIndex()<m_EndBox->GetIndex()){
				if (m_EndBox->GetIndex()==k){
					SelectBox(m_EndBox,FALSE);
					box1=m_EndBox->GetParent();
					m_EndBox=box1->GetBox(k-1);
					m_Cursor->SetBox(m_EndBox);
					return;
				}
			}
		}
		if (k==0 && !m_Cursor->IsEndBox()){
			box1=box->GetParent();
			if (!box1) return;
			if (box1->ClassName()=="MRow") return;
			m_EndBox=box1;
			m_StartBox=box1;
			if (box1->GetIndex()>0){
				m_Cursor->SetBox(box1->GetParent()->GetBox(box1->GetIndex()-1));
				m_Cursor->SetEndBox(TRUE);
			}
			else
				m_Cursor->SetEndBox(FALSE);
		}
		else if (k>=0){
			if (!m_EndBox)
				m_EndBox=m_Cursor->GetBox();
			m_StartBox=m_Cursor->GetBox();
			if (k>0){
				m_Cursor->SetBox(box->GetBox(k-1));
				m_Cursor->SetEndBox(TRUE);
			}
			else
				m_Cursor->SetEndBox(FALSE);
		}
		m_Cursor->DestroyCaret();
		SelectBox(m_StartBox,TRUE);
		return;
	}
}

void CEditorCtrl::ProcessRIGHTkey(int sh)
{
	int k;
	CBox* box;
	CBox* box1;
	if (!sh && m_StartBox && m_EndBox){
		m_Cursor->SetEndBox(TRUE);
		m_Cursor->SetBox(m_EndBox);
		ClearSelection();
		m_Cursor->ShowCaret();
	}
	else if (!sh){
		if (m_Cursor->MoveRight()){	
			m_Cursor->ShowCaret();
			TRACE("Index of box: %d\n", m_Cursor->GetBox()->GetIndex());
		}
	}
	else{ //SHIFT pressed
		k=m_Cursor->GetIndex();	
		box=m_Cursor->GetParent();//Must be MRow and the same parent as selection
		if (k==box->GetChildrenCount()-1 && m_Cursor->IsEndBox()){
			box1=box->GetParent();
			if (!box1) return;
			if (box1->ClassName()=="Mrow") return;
			//box1->SetSelect(TRUE);
			m_StartBox=box1;
			m_EndBox=box1;
		}
		else if (k<=box->GetChildrenCount()-1){
			if (m_StartBox && m_EndBox){
				//Neu cursor nam truoc vung chon
				//Huy chon m_StartBox
				//Chuyen m_StartBox sang phai mot box
				if (m_StartBox->GetIndex()<m_EndBox->GetIndex()){
					if (k<m_StartBox->GetIndex() || (k==0 && k==m_StartBox->GetIndex())){
						SelectBox(m_StartBox,FALSE);
						m_Cursor->SetBox(m_StartBox);
						m_Cursor->SetEndBox(TRUE);
						//Lui m_StartBox sang phai
						box1=m_StartBox->GetParent();
						m_StartBox=box1->GetBox(m_StartBox->GetIndex()+1);
						return;			
					}
				}//Limition
			}
			if (k==0 && !m_Cursor->IsEndBox()){
				if (!m_StartBox)
					m_StartBox=box->GetBox(k);
				m_EndBox=box->GetBox(k);
			}
			else{
				if (!m_StartBox)
					m_StartBox=box->GetBox(k+1);
				m_EndBox=box->GetBox(k+1);
			}
		}
		m_Cursor->SetBox(m_EndBox);
		m_Cursor->SetEndBox(TRUE);
		m_Cursor->DestroyCaret();
		SelectBox(m_EndBox,TRUE);
	}
}

void CEditorCtrl::ProcessShortCut(UINT nChar)
{
	CBox* newBox=NULL;
	//CBox* preBox;
	CBox* box;
	CBox* box1;
	CBox* box2;
	int k, l;
	switch (nChar){
		case 0x46://Fraction
			newBox=new CMFrac(
						new CMRow(),
						new CMRow(new CMI(""))
					);
			break;
		case 0x52://Root
			newBox=new CMRoot(new CMRow());
			break;
		case 0x4C://Lower Script
			newBox=new CMSubSup(
						new CMRow(),
						new CMRow(new CMI("")),
						NULL
					);
			break;
		case 0x55://Higher script
			newBox=new CMSubSup(
						new CMRow(),
						NULL,
						new CMRow(new CMI(""))
					);
			break;
		}
	if (!newBox)
		return;
	box=newBox->GetBox(0);
	box1=m_Cursor->GetParent();
	if (m_StartBox && m_EndBox){
		k=m_StartBox->GetIndex();
		l=m_EndBox->GetIndex();
		for (int i=k; i<=l;i++){
			box2=box1->RemoveBox(k);
			box2->SetSelect(FALSE);
			box->AddBox(box2);
		}
		m_StartBox=NULL;
		m_EndBox=NULL;
	}
	else{//Try get previous box
		k=m_Cursor->GetIndex();
		box2=box1->RemoveBox(k);
		box->AddBox(box2);
	}
	if (k>=0)
		box1->InsertBox(k,newBox);
	else if (m_Cursor->IsEndBox())
		box1->InsertBox(m_Cursor->GetIndex()+1,newBox);
	else
		box1->InsertBox(m_Cursor->GetIndex(),newBox);
	if (newBox->GetChildrenCount()==1)
		m_Cursor->SetBox(newBox->GetBox(0)->GetBox(0));
	else
		m_Cursor->SetBox(newBox->GetBox(1)->GetBox(0));
	m_Cursor->SetEndBox(TRUE);
	Redraw();
}

void CEditorCtrl::ScaleUp()
{
	
}
/**************************************************************
Chen cac ky hieu kieu Sum, Prod, Union, Int
***************************************************************/
void CEditorCtrl::InsertFuncOperator(CString id, int more)
{
	if (!m_bCanAdd)
		return;
	CBox* box;
	
	if (more==0){//Binh thuong, khong co chi so
		box=new CMO(id);
		InsertBox(box);
	}

	if (more==1){//Chi so tren
		box=new CMSubSup(
				new CMRow(
					new CMO(id)
					),
					NULL,
				new CMRow(
					new CMI("")
					)
				);
		InsertBox(box);
	}

	if (more==2){//Chi so duoi
		box=new CMSubSup(
				new CMRow(
					new CMO(id)
					),
				new CMRow(
					new CMI("")
					),
				NULL
				);
		InsertBox(box);
	}

	if (more==3){//Under
		box=new CMUnderOver(
					new CMRow(
						new CMO(id)
					),
					NULL,
					new CMRow(
						new CMI("")
					)
				);
		InsertBox(box);
	}
	Redraw();
}

void CEditorCtrl::SetFormulaText(CString formula)
{
	m_strFormula=formula;
}

CString CEditorCtrl::GetFormularText()
{
	return m_strFormula;
}
/*****************************************************************
Translate from formula string to a serial heritable box
******************************************************************/
BOOL CEditorCtrl::ParseFormula()
{
	CBox* box=NULL;
	CParserMathText parser(m_strFormula);
	try{
		parser.m_Editor=this;
		box=parser.Parse();		
		m_StartBox=NULL;
		m_EndBox=NULL;
		delete m_Math;
		m_Math=box;
		m_Cursor->SetRoot(m_Math);
		m_Cursor->SetBox(m_Math->GetBox(0));
		Invalidate(TRUE);
	}
	catch (CParserException* pe){
		if (box) delete box;
		pe->Delete();
		return FALSE;
	}
	return TRUE;
}

CEditorCtrl::MATH_ENTITY CEditorCtrl::GetEntityInfo(CString entity)
{
	int i;
	MATH_ENTITY me;
	me.bInverted=FALSE;
	me.CharCode=0;
	me.EntityName="";
	me.FontName="";
	me.LaTexName="";
	me.MathMLName="";
	for (i=0; i<entities.GetSize(); i++)
		if (entities[i].EntityName==entity){
			me=entities[i];
			break;
		}
	return me;
}

void CEditorCtrl::AddMathEntity(CString entity, CString fontname, CString mathmlname, CString latexname, BOOL inverted, BOOL boperator, unsigned char code)
{
	MATH_ENTITY me;
	me.bInverted=inverted;
	me.CharCode=code;
	me.EntityName=entity;
	me.FontName=fontname;
	me.LaTexName=latexname;
	me.MathMLName=mathmlname;
	me.bOperator=boperator;
	entities.Add(me);
}

void CEditorCtrl::SortEntityList()
{
	
}

CBox* CEditorCtrl::InsertEntity(CString en)
{
	MATH_ENTITY me;
	me=GetEntityInfo(en);
	CBox* box=NULL;
	if (me.CharCode>0){
		box=new CMEntity(me.CharCode, me.FontName, me.EntityName, me.MathMLName, me.LaTexName, me.bOperator, me.bInverted);
	}
	return box;
}
/**************************************************************
Chen cac ky hieu dac biet nhu Greek Char, Arrows...
**************************************************************/
void CEditorCtrl::InsertSpecialElement(CString more)
{
	if (!m_bCanAdd)
		return;
	InsertBox(InsertEntity(more));
	Redraw();
}


CString CEditorCtrl::GetMathML()
{
	if (!m_Math)
		return "";
	else
		return m_Math->ToMathML(1);
}
/***********************************************************************
Look in original table and return index of original operator
Input:
	CString st: Character that typed from keyboard.
Output:
	Index of character in origins array
Usage: Called from OnChar message handler function
************************************************************************/
int CEditorCtrl::FindOriginalChar(CString st)
{
	for (int i=0; i<origins.GetSize(); i++)
		if (origins[i].strName==st)
			return i;
	return -1;
}
/*****************************************************************************
Export mathematical formula to Windows Metafile image format
Input:
	CString strPath: file name that export to
Output:
	Success or not
******************************************************************************/
BOOL CEditorCtrl::ExportToWMF(CString strPath)
{
	CDC DC;
	CDC* pDC = NULL;
	CMetaFileDC MetaDC;
	CString st, ss;
	HENHMETAFILE hEnhMetaFile;
	
	DC.CreateCompatibleDC(NULL);

	// Get the extent of the formula

	CRect rect=m_Math->GetRect();
	
	CRect rectMeta(0,0,0,0);	

	rectMeta.left  = MulDiv(rect.left*100, DC.GetDeviceCaps(HORZSIZE),  DC.GetDeviceCaps(HORZRES));
	rectMeta.top = MulDiv(rect.top*100, DC.GetDeviceCaps(VERTSIZE), DC.GetDeviceCaps(VERTRES));
	rectMeta.right  = MulDiv(rect.right*100, DC.GetDeviceCaps(HORZSIZE),  DC.GetDeviceCaps(HORZRES));
	rectMeta.bottom = MulDiv(rect.bottom*100, DC.GetDeviceCaps(VERTSIZE), DC.GetDeviceCaps(VERTRES));

	// Create an enhanced Metafile DC
	MetaDC.CreateEnhanced(&DC, NULL, rectMeta, _T("Formula\0Image\0\0"));
	MetaDC.SetAttribDC(DC.m_hDC);
	MetaDC.SetMapMode(MM_TEXT);
	pDC = &MetaDC;

	CBrush brush;
	brush.CreateSysColorBrush(COLOR_WINDOW);
	pDC->FillRect(rect, &brush);
	brush.DeleteObject();

	m_Math->Draw(pDC);

	hEnhMetaFile=MetaDC.CloseEnhanced();
	BOOL bRet = FALSE;
	HENHMETAFILE hMetaCopy = ::CopyEnhMetaFile(hEnhMetaFile, strPath); 
	if (hMetaCopy)
	{
		bRet = TRUE;
		DeleteEnhMetaFile(hMetaCopy);
	}
	DeleteEnhMetaFile(hEnhMetaFile);
	return TRUE;
}


void CEditorCtrl::EnableScrollBars(int nBar)
{
	CWnd::EnableScrollBarCtrl(nBar, TRUE);
	ResetScrollBar();
}
/*************************************************************
Tinh toan lai ScrollBar. Thiet lap Range va Enabled
**************************************************************/
void CEditorCtrl::ResetScrollBar()
{
	CRect rc1, rc2;
	int minpos, maxpos;
	GetClientRect(rc1);
	rc2=m_Math->GetRect();
	rc1.DeflateRect(m_nLeftMargin, m_nTopMargin, m_nLeftMargin, m_nTopMargin);
	SCROLLINFO sinfo;
	sinfo.cbSize=sizeof(SCROLLINFO);
	sinfo.fMask=SIF_PAGE | SIF_RANGE;
	if (rc2.Width()<rc1.Width()){
		EnableScrollBar(SB_HORZ, ESB_DISABLE_BOTH);
		sinfo.nPage=rc1.Width();
		sinfo.nMin=0;
		sinfo.nMax=rc1.Width();
		SetScrollInfo(SB_HORZ, &sinfo, TRUE);
		SetScrollPos(SB_HORZ, 0);
	}
	else{
		GetScrollRange(SB_HORZ, &minpos, &maxpos);	
		if (rc2.Width()>=maxpos){
			EnableScrollBar(SB_HORZ, ESB_ENABLE_BOTH);
			sinfo.nPage=rc1.Width();
			sinfo.nMin=0;
			sinfo.nMax=rc2.Width()+rc1.Width()/3;
			SetScrollInfo(SB_HORZ, &sinfo, TRUE);
		}
	}
	if (rc2.Height()<rc1.Height()){
		EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH);
		sinfo.nPage=rc1.Height();
		sinfo.nMin=0;
		sinfo.nMax=rc1.Height();
		SetScrollInfo(SB_VERT, &sinfo, TRUE);
		SetScrollPos(SB_VERT, 0);
	}
	else{
		GetScrollRange(SB_VERT, &minpos, &maxpos);	
		if (rc2.Height()>=maxpos){
			EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);
			sinfo.nPage=rc1.Height();
			sinfo.nMin=0;
			sinfo.nMax=rc2.Height()+rc1.Height()/3;
			SetScrollInfo(SB_VERT, &sinfo, TRUE);
		}
	}
}

void CEditorCtrl::SetLeftMargin(int n)
{
	m_nLeftMargin=n;
}

int CEditorCtrl::GetLeftMargin()
{
	return m_nLeftMargin;
}

void CEditorCtrl::SetTopMargin(int n)
{
	m_nTopMargin=n;
}

int CEditorCtrl::GetTopMargin()
{
	return m_nTopMargin;
}

BOOL CEditorCtrl::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

/******************************************************
Update window and scrollbar
*******************************************************/
void CEditorCtrl::Redraw(BOOL bResetScroll)
{
	Invalidate();
	UpdateWindow();
	if (bResetScroll)
		ResetScrollBar();
	CheckCaretVisible();
}
/************************************************************
Ensure that the caret is always visible
*************************************************************/
void CEditorCtrl::CheckCaretVisible()
{
	if (!m_Cursor)
		return;
	CPoint vporg;
	vporg.x=-GetScrollPos(SB_HORZ);
	vporg.y=-GetScrollPos(SB_VERT);
	CBox* box=m_Cursor->GetBox();
	int cy=box->GetTop()+box->GetHeight();
	int cx;
	if (m_Cursor->IsEndBox())
		cx=box->GetLeft()+box->GetWidth();
	else
		cx=box->GetLeft();

	CRect rc;
	GetClientRect(rc);
	rc.DeflateRect(m_nLeftMargin, m_nTopMargin, m_nLeftMargin, m_nTopMargin);
	if (!rc.PtInRect(CPoint(cx+vporg.x, cy+vporg.y))){
		if (cx>=rc.Width()/3)
			SetScrollPos(SB_HORZ, cx-rc.Width()/3, TRUE);
		else
			SetScrollPos(SB_HORZ, 0, TRUE);
		if (cy>=rc.Height()/3)
			SetScrollPos(SB_VERT, cy-rc.Height()/3, TRUE);
		else
			SetScrollPos(SB_VERT, 0, TRUE);
		Invalidate();
	}
}

void CEditorCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int newpos, curpos;
	int minpos, maxpos;
	SCROLLINFO sinfo;
	sinfo.cbSize=sizeof(SCROLLINFO);
	CClientDC dc(this);
	CSize sz=dc.GetTextExtent("X");;
	
	GetScrollRange(SB_HORZ, &minpos, &maxpos);
	curpos=GetScrollPos(SB_HORZ);
	newpos=curpos;
	switch (nSBCode){
	case SB_LEFT:
		newpos=minpos;
		break;
	case SB_RIGHT:
		newpos=maxpos;
		break;
	case SB_LINELEFT:
		newpos=curpos-sz.cx;
		if (newpos<minpos)
			newpos=minpos;
		break;
	case SB_LINERIGHT:
		newpos=curpos+sz.cx;
		if (newpos>maxpos)
			newpos=maxpos;
		break;
	case SB_PAGELEFT:
		GetScrollInfo(SB_HORZ, &sinfo);
		if (curpos>minpos)
			newpos = max(minpos, curpos - (int) sinfo.nPage);
		break;
	case SB_PAGERIGHT:
		GetScrollInfo(SB_HORZ, &sinfo);
		if (curpos<maxpos)
			newpos = max(maxpos, curpos + (int) sinfo.nPage);
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		newpos=nPos;
		break;
	}
	if (newpos>=minpos){
		sinfo.fMask=SIF_POS;
		sinfo.nPos=newpos;
		SetScrollInfo(SB_HORZ, &sinfo);
		Invalidate();
	}
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CEditorCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int newpos, curpos;
	int minpos, maxpos;
	SCROLLINFO sinfo;
	CClientDC dc(this);
	CSize sz=dc.GetTextExtent("X");
	curpos=GetScrollPos(SB_VERT);
	GetScrollRange(SB_VERT, &minpos, &maxpos);
	newpos=curpos;
	sinfo.cbSize=sizeof(SCROLLINFO);
	switch (nSBCode){
	case SB_TOP:
		newpos=minpos;
		break;
	case SB_BOTTOM:
		newpos=maxpos;
		break;
	case SB_LINEUP:
		newpos=curpos-sz.cy;
		if (newpos<minpos)
			newpos=minpos;
		break;
	case SB_LINEDOWN:
		newpos=curpos+sz.cy;
		if (newpos>maxpos)
			newpos=maxpos;
		break;
	case SB_PAGEUP:
		GetScrollInfo(SB_VERT, &sinfo);
		if (curpos>minpos)
			newpos=max(minpos, curpos - (int)sinfo.nPage);
		break;
	case SB_PAGEDOWN:
		GetScrollInfo(SB_VERT, &sinfo);
		if (curpos<maxpos)
			newpos=max(maxpos, curpos + (int)sinfo.nPage);
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		newpos=nPos;
		break;
	}
	if (newpos>=minpos){
		sinfo.fMask=SIF_POS;
		sinfo.nPos=newpos;
		SetScrollInfo(SB_VERT, &sinfo);
		Invalidate();
	}
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CEditorCtrl::OnSize(UINT nType, int cx, int cy)
{
	if (GetSafeHwnd()){
		CWnd::OnSize(nType, cx, cy);
		ResetScrollBar();
	}
}

BOOL CEditorCtrl::SaveFile(CString strFileName, UINT nFormat)
{
	CFile outFile;
	CFileException ex;

	if (!outFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite, &ex)){
		TCHAR szError[1024];
	    ex.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return FALSE;
	}
	CArchive ar(&outFile, CArchive::store);

	m_Math->Serialize(ar);
	ar.Close();
	outFile.Close();
	return TRUE;
}

BOOL CEditorCtrl::OpenFile(CString strFile, UINT nFormat)
{
	if (!m_Math)
		return FALSE;
	if (!m_Cursor)
		return FALSE;
	CFile inFile;
	CFileException ex;
	BOOL ok=TRUE;
	if (!inFile.Open(strFile, CFile::modeRead, &ex)){
		TCHAR szError[1024];
	    ex.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return FALSE;
	}
	CArchive ar(&inFile, CArchive::load);

	CBox* Temp=new CMRow();
	TRY
	{
		Temp->Serialize(ar);
		m_Cursor->DestroyCaret();
		delete m_Math;
		m_Math=Temp;
		m_Cursor->SetRoot(m_Math);
		m_Cursor->SetBox(m_Math->GetBox(0));
		Redraw();
	}
	CATCH_ALL (e)
	{
		delete Temp;
		delete e;
		ok=FALSE;
	}
	END_CATCH_ALL

	ar.Close();
	inFile.Close();
	return ok;
}

void CEditorCtrl::CopyToClipboard()
{
	if (!m_StartBox || !m_EndBox)
		return;
	CBoxHolder Temp;
	CBox* box=m_StartBox->GetParent();
	int k=m_StartBox->GetIndex();
	int l=m_EndBox->GetIndex();
	for (int i=k; i<=l; i++)
		Temp.AddBox(box->GetBox(i));
	
	CSharedFile sf(GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT);

	CArchive ar (&sf, CArchive::store);
	Temp.Serialize(ar);
	ar.Close();
	
	DWORD dwLen = (DWORD) sf.GetLength();
	HGLOBAL hMem = sf.Detach();
	COleDataSource* pSource=NULL;
	if (hMem){
		hMem = ::GlobalReAlloc(hMem, dwLen, GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT);
		if (hMem){
			pSource = new COleDataSource();
			pSource->CacheGlobalData(CF_MATHEQU, hMem);
		}
	}

	//MathML clipboard implementation
	if (m_bCopyMathML){
		CSharedFile mmlsf(GMEM_ZEROINIT|GMEM_DDESHARE|GMEM_MOVEABLE);
		CString st=Temp.ToMathML();
		mmlsf.Write((LPCTSTR)st, st.GetLength()+1);
		dwLen = (DWORD) mmlsf.GetLength();
		hMem = mmlsf.Detach();
		if (hMem){
			hMem = ::GlobalReAlloc(hMem, dwLen, GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT);
			if (hMem){
				if (!pSource)
					pSource = new COleDataSource();
				pSource->CacheGlobalData(CF_TEXT, hMem);
			}
		}
	}

	//Metafile clipboard implementation
	if (m_bCopyImage){
		CDC DC;
		CDC* pDC = NULL;
		CMetaFileDC MetaDC;

		DC.CreateCompatibleDC(NULL);
		//DC.SetWindowOrg(0,0);

		CRect rect(Temp.GetLeft(),Temp.GetTop(),Temp.GetLeft()+Temp.GetWidth(), Temp.GetTop()+Temp.GetHeight());
		
		CRect rectMeta(0,0,0,0);	

		rectMeta.left  = MulDiv(rect.left*100, DC.GetDeviceCaps(HORZSIZE),  DC.GetDeviceCaps(HORZRES));
		rectMeta.top = MulDiv(rect.top*100, DC.GetDeviceCaps(VERTSIZE), DC.GetDeviceCaps(VERTRES));
		rectMeta.right  = MulDiv(rect.right*100, DC.GetDeviceCaps(HORZSIZE),  DC.GetDeviceCaps(HORZRES));
		rectMeta.bottom = MulDiv(rect.bottom*100, DC.GetDeviceCaps(VERTSIZE), DC.GetDeviceCaps(VERTRES));

		// Create an enhanced Metafile DC
		MetaDC.CreateEnhanced(&DC, NULL, rectMeta, _T("Equation\0Image\0\0"));
		MetaDC.SetAttribDC(DC.m_hDC);
		MetaDC.SetMapMode(MM_TEXT);
		pDC = &MetaDC;

		CBrush brush;
		brush.CreateSysColorBrush(COLOR_WINDOW);
		pDC->FillRect(rect, &brush);
		brush.DeleteObject();
		int oldBkMode=pDC->SetBkMode(TRANSPARENT);
		Temp.Draw(pDC);
		pDC->SetBkMode(oldBkMode);
		
		STGMEDIUM std;
		memset(&std,0,sizeof(std));
		std.tymed=TYMED_ENHMF;
		std.hEnhMetaFile=MetaDC.CloseEnhanced();

		if (!pSource)
			pSource = new COleDataSource();
		pSource->CacheData(CF_ENHMETAFILE, &std);
	}
	//Put on clipboard
	pSource->SetClipboard();
}

void CEditorCtrl::PasteFromClipboard()
{
	if (!m_Math)
		return;
	if (!m_Cursor)
		return;

	COleDataObject pDataObject;
    if (!pDataObject.AttachClipboard())
		return;
	if (!pDataObject.IsDataAvailable(CF_MATHEQU))
		return;
	HGLOBAL hmem = pDataObject.GetGlobalData(CF_MATHEQU);
	if(!hmem)
		return;

	CMemFile sf((BYTE*) ::GlobalLock(hmem), ::GlobalSize(hmem));

	CArchive ar (&sf, CArchive::load);
	CBoxHolder Temp;
	Temp.Serialize(ar);
	ar.Close();
	if (Temp.GetChildrenCount()==0)
		return;
	DeleteSelection();
	CBox* box=NULL;
	CBox* box1=m_Cursor->GetParent();
	int k=m_Cursor->GetIndex();
	bool flag=m_Cursor->IsEndBox();
	if (m_Cursor->IsTemplate() && m_Cursor->GetChildrenCount()==0){
		box1->DeleteBox(k);
		k--;
	}

	for (int i=0; i<Temp.GetChildrenCount(); i++){
		box=Temp.GetBox(i);
		if (flag || k<0){
			box1->InsertBox(k+1,box);
			k++;
		}
		else if (k>=0){
			box1->InsertBox(k,box);
			flag=TRUE;
		}
	}

	if (box){
		m_Cursor->SetBox(box);
		m_Cursor->SetEndBox(TRUE);
	}

	Redraw();
}

void CEditorCtrl::CutToClipboard()
{
	if (!m_StartBox || !m_EndBox)
		return;
	CopyToClipboard();
	DeleteSelection();
	Redraw();
}

void CEditorCtrl::SetCopyOption(BOOL bMathML, BOOL bImage)
{
	m_bCopyMathML=bMathML;
	m_bCopyImage=bImage;
}

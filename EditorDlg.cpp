// EditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MathEdit.h"
#include "EditorDlg.h"
#include "About.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditorDlg dialog


CEditorDlg::CEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditorDlg)
	DDX_Control(pDX, IDC_FONTSIZE_LIST, m_FontSizeList);
	DDX_Control(pDX, IDC_EDITOR, m_Editor); 
	DDX_Control(pDX, IDC_EQUATION,		m_btnEquation);
	DDX_Control(pDX, IDC_BRACE,			m_btnBrace);
	DDX_Control(pDX, IDC_UPPER_GREEK,	m_btnUpperGreek);
	DDX_Control(pDX, IDC_LOWER_GREEK,	m_btnLowerGreek);
	DDX_Control(pDX, IDC_SUM,			m_btnSum);
	DDX_Control(pDX, IDC_PROD,			m_btnProd);
	DDX_Control(pDX, IDC_INTEGRAL,		m_btnIntegral);
	DDX_Control(pDX, IDC_DERIVATIVE,	m_btnDerivative);
	DDX_Control(pDX, IDC_MATRIX,		m_btnMatrix);
	DDX_Control(pDX, IDC_PBYQ,			m_btnPbyq);
	DDX_Control(pDX, IDC_FUNCTION,		m_btnFunction);
	DDX_Control(pDX, IDC_COREDATA,		m_btnCoreData);
	DDX_Control(pDX, IDC_VECTOR,		m_btnVector);
	DDX_Control(pDX, IDC_ARROWS,		m_btnArrows);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CEditorDlg)
	ON_MESSAGE(CS_SELECTED, ToolBarCtrlSelected)
	ON_CBN_SELCHANGE(IDC_FONTSIZE_LIST, OnSelchangeFontsizeList)
	ON_BN_CLICKED(IDC_UNDO, OnUndo)
	ON_BN_CLICKED(IDC_REDO, OnRedo)
	ON_BN_CLICKED(IDC_PARSER, OnParser)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SAVE_FILE, OnSaveFile)
	ON_BN_CLICKED(IDC_OPEN_FILE, OnOpenFile)
	ON_BN_CLICKED(IDC_COPY_IMAGE, OnCopyImage)
	ON_BN_CLICKED(IDC_COPY_MATHML, OnCopyMathml)
	ON_BN_CLICKED(IDC_CREDIT, OnCredit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorDlg message handlers

BOOL CEditorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);

	//Initialize Entities Tables
	InitEntityList();
	InitToolbarEntity();
	m_btnEquation.InitButton	(3, IDB_EQUATION,		21, RGB(255,255,255));
	m_btnBrace.InitButton		(4, IDB_BRACES,			21, RGB(255,255,255));
	m_btnUpperGreek.InitButton	(4, IDB_UPPER_GREEK,	21, RGB(255,255,255));
	m_btnLowerGreek.InitButton	(4, IDB_LOWER_GREEK,	21, RGB(255,255,255));
	m_btnSum.InitButton			(4, IDB_SUM,			21, RGB(255,255,255));
	m_btnProd.InitButton		(3, IDB_DOTSYMB,		21, RGB(255,255,255));
	m_btnIntegral.InitButton	(4, IDB_INTEGRALS,		21, RGB(255,255,255));
	m_btnDerivative.InitButton	(2, IDB_MORESYMBOL,		21, RGB(255,255,255));
	m_btnMatrix.InitButton		(3, IDB_MATRIX,			21, RGB(255,255,255));
	m_btnPbyq.InitButton		(3, IDB_FRS,			21, RGB(255,255,255));
	m_btnFunction.InitButton	(4, IDB_FUNCTION,		32, RGB(255,255,255));
	m_btnCoreData.InitButton	(4, IDB_SPECIALCHARS,	21, RGB(255,255,255));
	m_btnVector.InitButton		(3, IDB_VECTOR,			21, RGB(255,255,255));
	m_btnArrows.InitButton		(3, IDB_ARROWS,			21, RGB(255,255,255));

		// Create the ToolTip control.
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);

	// Add the tools
	//m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_UNDO), "Undo");
	//m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_REDO), "Redo");

	m_tooltip.AddTool(GetDlgItem(IDC_EQUATION),		"Special Operators");
	m_tooltip.AddTool(GetDlgItem(IDC_BRACE),		"Braces");
	m_tooltip.AddTool(GetDlgItem(IDC_UPPER_GREEK),	"Upper Greek");
	m_tooltip.AddTool(GetDlgItem(IDC_LOWER_GREEK),	"Lower Greek");
	m_tooltip.AddTool(GetDlgItem(IDC_SUM),			"Sums, Producs, Unions, Intersections");
	m_tooltip.AddTool(GetDlgItem(IDC_PROD),			"Dot symbols");
	m_tooltip.AddTool(GetDlgItem(IDC_INTEGRAL),		"Integrals");
	m_tooltip.AddTool(GetDlgItem(IDC_DERIVATIVE),	"More symbols");
	m_tooltip.AddTool(GetDlgItem(IDC_MATRIX),		"Matrices");
	m_tooltip.AddTool(GetDlgItem(IDC_PBYQ),			"Common equations");
	m_tooltip.AddTool(GetDlgItem(IDC_FUNCTION),		"Functions");
	m_tooltip.AddTool(GetDlgItem(IDC_COREDATA),		"Special Chars");
	m_tooltip.AddTool(GetDlgItem(IDC_VECTOR),		"Vector, Over, Angle, Arc");
	m_tooltip.AddTool(GetDlgItem(IDC_ARROWS),		"Arrows");
	CString st;
	for (int i=8; i<=72; i++){
		st.Format("%d",i);
		m_FontSizeList.AddString(st);
	}
	m_FontSizeList.SetCurSel(4);
	m_Editor.EnableScrollBars(SB_BOTH);
	m_Editor.SetFocus();
	m_Editor.Invalidate(TRUE);

	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_FORMULA_TEXT);
	pEdit->SetWindowText("x_12=(-b+-sqrt(b^2-4ac))/2a");

	CButton* pButton=(CButton*)GetDlgItem(IDC_COPY_MATHML);
	pButton->SetCheck(TRUE);
	pButton=(CButton*)GetDlgItem(IDC_COPY_IMAGE);
	pButton->SetCheck(TRUE);
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CEditorDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_tooltip.RelayEvent(pMsg);
	UpdateDialogControls( this, FALSE );
	return CDialog::PreTranslateMessage(pMsg);
}

LONG CEditorDlg::ToolBarCtrlSelected(WPARAM wParam , LPARAM lParam)
{
	CString strType;
	int more;
	CString id;
	if(wParam==-1)
		return 0L;

	switch (lParam)
	{
	case IDC_EQUATION: // from Toolbar Equations
		/*
		if (wParam<20)
			m_Editor.InsertElement("EQU",wParam);
		break;
		*/
		if (wParam<m_StdOp.GetSize() && m_StdOp[wParam]!="")
			m_Editor.InsertSpecialElement(m_StdOp[wParam]);
		break;
	case IDC_BRACE: // form toolbar Braces
		m_Editor.InsertElement("Brace",wParam);
		break;
	case IDC_COREDATA: // form toolbar Core Data
		if (wParam<m_GeoOp.GetSize() && m_GeoOp[wParam]!="")
			m_Editor.InsertSpecialElement(m_GeoOp[wParam]);
		break;
	case IDC_SUM: // form toolbar Sum
		m_Editor.InsertElement("SUM", wParam);
		break;

	case IDC_PROD: // form toolbar Prod (same behaviour as sum)
		if (wParam<m_DotOp.GetSize() && m_DotOp[wParam]!="")
			m_Editor.InsertSpecialElement(m_DotOp[wParam]);
		break;

	case IDC_FUNCTION: // form toolbar Function
		switch (wParam){
			case 0:
				id="sin";
				more=0;
				break;
			case 1:
				id="cos";
				more=0;
				break;
			case 2:
				id="tan";
				more=0;
				break;
			case 3:
				id="cot";
				more=0;
				break;
			case 4:
				id="sin";
				more=1;
				break;
			case 5:
				id="cos";
				more=1;
				break;
			case 6:
				id="tan";
				more=1;
				break;
			case 7:
				id="cot";
				more=1;
				break;
			case 8:
				id="sinh";
				more=0;
				break;
			case 9:
				id="cosh";
				more=0;
				break;
			case 10:
				id="tanh";
				more=0;
				break;
			case 11:
				id="coth";
				more=0;
				break;
			case 12:
				id="sinh";
				more=1;
				break;
			case 13:
				id="cosh";
				more=1;
				break;
			case 14:
				id="tanh";
				more=1;
				break;
			case 15:
				id="coth";
				more=1;
				break;
			case 16:
				id="exp";
				more=0;
				break;
			case 17:
				id="ln";
				more=0;
				break;
			case 18:
				id="ln";
				more=2;
				break;
			case 19:
				id="log";
				more=2;
				break;
			case 21:
				id="lim";
				more=3;
				break;
			}
		m_Editor.InsertFuncOperator(id, more);
		break;

	case IDC_INTEGRAL: // form toolbar Integral
		m_Editor.InsertElement("INT",wParam);
		break;

	case IDC_DERIVATIVE: // form toolbar derivative
		if (wParam<m_MoreSym.GetSize() && m_MoreSym[wParam]!="")
			m_Editor.InsertSpecialElement(m_MoreSym[wParam]);
		break;

	case IDC_PBYQ: // form toolbar Operators
		if(wParam== 0)
			m_Editor.InsertElement("MFrac");
		if(wParam== 1 || wParam==2)
			m_Editor.InsertElement("MRoot",wParam);
		if (wParam==3)
			m_Editor.InsertElement("MSup");
		if (wParam==4)
			m_Editor.InsertElement("MSub");
		if (wParam==5)
			m_Editor.InsertElement("MSubSup");
		if (wParam>5)
			m_Editor.InsertElement("MUnderOver", wParam);
		break;
	case IDC_MATRIX: // form toolbar matrix
		m_Editor.InsertElement("MTable",wParam);
		break;
	case IDC_VECTOR: // form toolbar vector
		//if (wParam<2)
		m_Editor.InsertElement("MOver",wParam);
		break;
	case IDC_ARROWS: // form toolbar arrows
		if (wParam<m_ArrOp.GetSize() && m_ArrOp[wParam]!="")
			m_Editor.InsertSpecialElement(m_ArrOp[wParam]);
		break;
	case IDC_UPPER_GREEK: // form toolbar upper greek
		if (wParam<m_UpperGreek.GetSize() && m_UpperGreek[wParam]!="")
			m_Editor.InsertSpecialElement(m_UpperGreek[wParam]);
		break;
	case IDC_LOWER_GREEK: // form toolbar lower greek (same behaviour as upper greek)
		if (wParam<m_LowerGreek.GetSize() && m_LowerGreek[wParam]!="")
			m_Editor.InsertSpecialElement(m_LowerGreek[wParam]);
		break;
	default:
		break;
	}
	m_Editor.SetFocus();
    return 1L;
}

BOOL CEditorDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_Editor.DestroyMath();
	m_LowerGreek.RemoveAll();
	m_UpperGreek.RemoveAll();
	m_StdOp.RemoveAll();
	m_GeoOp.RemoveAll();
	m_ArrOp.RemoveAll();
	return CDialog::DestroyWindow();
}



void CEditorDlg::OnSelchangeFontsizeList() 
{
	// TODO: Add your control notification handler code here
	//return;
	int k=m_FontSizeList.GetCurSel()+8;
	m_Editor.SetBaseFontSize(k);
}

void CEditorDlg::OnUndo() 
{
	// TODO: Add your control notification handler code here
	//m_Editor.ScaleUp();
}

void CEditorDlg::OnRedo() 
{
	// TODO: Add your control notification handler code here
//	m_Editor.Redo();
//	m_Editor.SetFocus();
}

void CEditorDlg::OnParser() 
{
	// TODO: Add your control notification handler code here
	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_FORMULA_TEXT);
	CString st;
	pEdit->GetWindowText(st);
	st.TrimLeft();
	st.TrimRight();
	if (st=="") return;
	m_Editor.SetFormulaText(st);
	m_Editor.ParseFormula();
	m_Editor.SetFocus();
}

void CEditorDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	return;
}

void CEditorDlg::InitEntityList()
{
	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL,path, MAX_PATH);
	CString st(path);
	CStringArray tokens;
	int i, k, j;
	TCHAR ch;
	k=st.ReverseFind('\\');
	st=st.Left(k+1);
	st=st + "Entity.txt";
	CStdioFile file;
	tokens.SetSize(7);
	if (!file.Open(st,CFile::modeRead)){
		AfxMessageBox("Could not open entity list file");
		CDialog::OnCancel();
	}
	while (true){
		if (!file.ReadString(st))
			break;
		if (st=="")
			break;
		if (st[st.GetLength()-1]!='\t')
			st=st+"\t";
		i=0;
		for (j=0; j<7; j++){
			k=i;
			do{
				ch=st[k];
				k=k+1;
				if (k==st.GetLength())
					break;
			} while (ch!='\t'); 
			tokens[j]=st.Mid(i,k-i-1);
			//TRACE(st.Mid(i,k-i-1)+"\n");
			i=k;
		}
		m_Editor.AddMathEntity(tokens[0], tokens[2], tokens[4], tokens[5], (BOOL)atoi(tokens[6]), (BOOL)atoi(tokens[1]), HexToInt(tokens[3]));
	}
}

void CEditorDlg::InitToolbarEntity()
{
	m_LowerGreek.SetSize(28);
	m_LowerGreek[0]="alpha";
	m_LowerGreek[1]="beta";
	m_LowerGreek[2]="chi";
	m_LowerGreek[3]="delta";
	m_LowerGreek[4]="epsi";
	m_LowerGreek[5]="phi";
	m_LowerGreek[6]="phiv";
	m_LowerGreek[7]="gamma";
	m_LowerGreek[8]="eta";
	m_LowerGreek[9]="iota";
	m_LowerGreek[10]="kappa";
	m_LowerGreek[11]="lambda";
	m_LowerGreek[12]="mu";
	m_LowerGreek[13]="nu";
	m_LowerGreek[14]="omicron";
	m_LowerGreek[15]="pi";
	m_LowerGreek[16]="theta";
	m_LowerGreek[17]="rho";
	m_LowerGreek[18]="sigma";
	m_LowerGreek[19]="tau";
	m_LowerGreek[20]="upsi";
	m_LowerGreek[21]="piv";
	m_LowerGreek[22]="omega";
	m_LowerGreek[23]="xi";
	m_LowerGreek[24]="psi";
	m_LowerGreek[25]="zeta";
	m_LowerGreek[26]="part";
	m_LowerGreek[27]="";

	m_UpperGreek.SetSize(26);
	m_UpperGreek[0]="Alpha";
	m_UpperGreek[1]="Beta";
	m_UpperGreek[2]="Chi";
	m_UpperGreek[3]="Delta";
	m_UpperGreek[4]="Epsi";
	m_UpperGreek[5]="Phi";
	m_UpperGreek[6]="Gamma";
	m_UpperGreek[7]="Eta";
	m_UpperGreek[8]="Iota";
	m_UpperGreek[9]="thetav";
	m_UpperGreek[10]="Kappa";
	m_UpperGreek[11]="Lamda";
	m_UpperGreek[12]="Mu";
	m_UpperGreek[13]="Nu";
	m_UpperGreek[14]="Omicron";
	m_UpperGreek[15]="Pi";
	m_UpperGreek[16]="Theta";
	m_UpperGreek[17]="Rho";
	m_UpperGreek[18]="Sigma";
	m_UpperGreek[19]="Tau";
	m_UpperGreek[20]="Upsilon";
	m_UpperGreek[21]="sigmav";
	m_UpperGreek[22]="Omega";
	m_UpperGreek[23]="Xi";
	m_UpperGreek[24]="Psi";
	m_UpperGreek[25]="Zeta";

	m_StdOp.SetSize(20);
	m_StdOp[0]="plusmn";
	m_StdOp[1]="mnplus";
	m_StdOp[2]="divide";
	m_StdOp[3]="le";
	m_StdOp[4]="ge";
	m_StdOp[5]="ne";
	m_StdOp[6]="equiv";
	m_StdOp[7]="ap";
	m_StdOp[8]="cong";
	m_StdOp[9]="cap";
	m_StdOp[10]="cup";
	m_StdOp[11]="sup";
	m_StdOp[12]="supE";
	m_StdOp[13]="nsub";
	m_StdOp[14]="sub";
	m_StdOp[15]="subE";
	m_StdOp[16]="isin";
	m_StdOp[17]="notin";
	m_StdOp[18]="exist";
	m_StdOp[19]="forall";

	m_GeoOp.SetSize(12);
	m_GeoOp[0]="infin";
	m_GeoOp[1]="esim";
	m_GeoOp[2]="sime";
	m_GeoOp[3]="wreath";
	m_GeoOp[4]="ang";
	m_GeoOp[5]="angmsd";
	m_GeoOp[6]="angsph";
	m_GeoOp[7]="par";
	m_GeoOp[8]="vangrt";
	m_GeoOp[9]="lrtri";
	m_GeoOp[10]="xutri";
	m_GeoOp[11]="bottom";

	m_ArrOp.SetSize(12);
	m_ArrOp[0]="rarr";
	m_ArrOp[1]="larr";
	m_ArrOp[2]="harr";
	m_ArrOp[3]="uarr";
	m_ArrOp[4]="darr";
	m_ArrOp[5]="varr";
	m_ArrOp[6]="rArr";
	m_ArrOp[7]="lArr";
	m_ArrOp[8]="hArr";
	m_ArrOp[9]="uArr";
	m_ArrOp[10]="dArr";
	m_ArrOp[11]="vArr";

	m_DotOp.SetSize(12);
	m_DotOp[0]="there4";
	m_DotOp[1]="becaus";
	m_DotOp[2]="ratio";
	m_DotOp[3]="Colon";
	m_DotOp[4]="minusd";
	m_DotOp[5]="mDot";
	m_DotOp[6]="mDDot";
	m_DotOp[7]="homtht";
	m_DotOp[8]="esdot";
	m_DotOp[9]="eDot";
	m_DotOp[10]="efDot";
	m_DotOp[11]="erDot";

	m_MoreSym.SetSize(8);
	m_MoreSym[0]="not";
	m_MoreSym[1]="emptyv";
	m_MoreSym[2]="oplus";
	m_MoreSym[3]="ominus";
	m_MoreSym[4]="odot";
	m_MoreSym[5]="real";
	m_MoreSym[6]="image";
	m_MoreSym[7]="aleph";
}

int CEditorDlg::HexToInt(CString st)
{
	TCHAR ch1, ch2;
	int d1, d2;
	st=st.Right(2);
	st.MakeUpper();
	ch1=st[0];
	ch2=st[1];
	if (ch1>='A')
		d1=10+ch1-'A';
	else
		d1=ch1-'0';

	if (ch2>='A')
		d2=10+ch2-'A';
	else
		d2=ch2-'0';
	return d1*16+d2;
}

void CEditorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CEditorDlg::OnSaveFile() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE szFilter[] = "Math equation files (*.meq)|*.meq|MathML files (*.mml)|*.mml|Windows metafile (*.wmf)|*.wmf|";
	
	CFileDialog fdlg( FALSE, "meq", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , szFilter, NULL );
				
	if (fdlg.DoModal() == IDOK)
	{
		CString strFile=fdlg.m_ofn.lpstrFile;
		CString ext=fdlg.GetFileExt();
		ext.MakeLower();
		if (ext=="wmf")
			m_Editor.ExportToWMF(strFile);
		else if (ext=="meq")
			m_Editor.SaveFile(strFile);
		else{
			CString st=m_Editor.GetMathML();
			CStdioFile ouFile;
			ouFile.Open(strFile, CFile::modeCreate | CFile::modeWrite);
			ouFile.WriteString(st);
			ouFile.Close();
		}
	}	
}

void CEditorDlg::OnOpenFile() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE szFilter[] = "Math equation files (*.meq)|*.meq|";
	
	CFileDialog fdlg( TRUE, "meq", "", OFN_HIDEREADONLY | OFN_FILEMUSTEXIST , szFilter, NULL );
				
	if (fdlg.DoModal() == IDOK)
	{
		CString strFile=fdlg.m_ofn.lpstrFile;
		m_Editor.OpenFile(strFile);
	}	
}

void CEditorDlg::OnCopyImage() 
{
	// TODO: Add your control notification handler code here
	ResetCopyOptions();
}

void CEditorDlg::OnCopyMathml() 
{
	// TODO: Add your control notification handler code here
	ResetCopyOptions();
}

void CEditorDlg::ResetCopyOptions()
{
	CButton* pButton=(CButton*)GetDlgItem(IDC_COPY_MATHML);
	BOOL b1=pButton->GetCheck();
	pButton=(CButton*)GetDlgItem(IDC_COPY_IMAGE);
	BOOL b2=pButton->GetCheck();
	m_Editor.SetCopyOption(b1, b2);
}

void CEditorDlg::OnCredit() 
{
	// TODO: Add your control notification handler code here
	CAbout ab;
	ab.DoModal();
}

; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMaxtrixProperty
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "meditorlib.h"
LastPage=0

ClassCount=4

ResourceCount=3
Resource1=IDD_EDITOR_DLG
Class1=CEditorDlg
Class2=CEditor
Class3=CEditorCtrl
Resource2=IDD_TOOLBAR_POPUP
Class4=CMaxtrixProperty
Resource3=IDD_MATRIX_PROPERTY

[DLG:IDD_EDITOR_DLG]
Type=1
Class=CEditorDlg
ControlCount=15
Control1=IDC_EQUATION,button,1342242816
Control2=IDC_PBYQ,button,1342242816
Control3=IDC_FUNCTION,button,1342242816
Control4=IDC_ARROWS,button,1342242816
Control5=IDC_COREDATA,button,1342242816
Control6=IDC_INTEGRAL,button,1342242816
Control7=IDC_MATRIX,button,1342242816
Control8=IDC_VECTOR,button,1342242816
Control9=IDC_BRACE,button,1342242816
Control10=IDC_DERIVATIVE,button,1342242816
Control11=IDC_UPPER_GREEK,button,1342242816
Control12=IDC_LOWER_GREEK,button,1342242816
Control13=IDC_SUM,button,1342242816
Control14=IDC_PROD,button,1342242816
Control15=IDC_FORMULAR,CEditor,1342242816

[DLG:IDD_TOOLBAR_POPUP]
Type=1
Class=?
ControlCount=1
Control1=IDC_CHARSETCTRL,CToolBarBtnCtrl,1342242816

[CLS:CEditorDlg]
Type=0
HeaderFile=EditorDlg.h
ImplementationFile=EditorDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CEditorDlg
VirtualFilter=dWC

[CLS:CEditor]
Type=0
HeaderFile=Editor.h
ImplementationFile=Editor.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CEditor

[CLS:CEditorCtrl]
Type=0
HeaderFile=EditorCtrl.h
ImplementationFile=EditorCtrl.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CEditorCtrl

[DLG:IDD_MATRIX_PROPERTY]
Type=1
Class=CMaxtrixProperty
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CMaxtrixProperty]
Type=0
HeaderFile=MaxtrixProperty.h
ImplementationFile=MaxtrixProperty.cpp
BaseClass=CDialog
Filter=D


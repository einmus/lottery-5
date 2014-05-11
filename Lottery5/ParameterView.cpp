// ParameterView.cpp : implementation file
//

#include "stdafx.h"
#include "Lottery5.h"
#include "ParameterView.h"


// ParameterView dialog

IMPLEMENT_DYNAMIC(ParameterView, CDialog)

ParameterView::ParameterView(MyParam p, CWnd* pParent /*=NULL*/)
	: CDialog(ParameterView::IDD, pParent)
	, m_bInitialized(false)
	, m_p(p)
{

}

ParameterView::~ParameterView()
{
}

void ParameterView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ParameterView, CDialog)
	ON_EN_CHANGE(IDC_EDIT1201, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1202, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1203, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1204, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1205, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1206, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1207, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1208, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1209, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1210, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1211, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1212, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1213, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1214, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1215, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1216, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1217, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1218, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1219, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1220, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1221, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1222, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1223, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1224, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1225, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1226, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1227, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1228, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1229, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1230, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1231, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1232, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1233, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1234, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1235, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1236, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1237, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1238, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1239, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1240, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1241, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1242, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1243, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1244, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1245, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1246, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1247, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1248, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1249, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1250, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1251, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1252, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1253, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1254, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1255, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1256, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1257, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1258, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1259, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1260, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1261, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1262, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1263, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1264, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1265, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1266, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1267, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1268, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1269, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1270, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1271, &ParameterView::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT1272, &ParameterView::OnEnChangeEdit)
END_MESSAGE_MAP()


// ParameterView message handlers

BOOL ParameterView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	// set buddy
	CSpinButtonCtrl * s;
	CEdit * e;
	TCHAR c[256];
	for (int i = 0; i < 12*6; i++) {
		e = (CEdit *)(GetDlgItem(IDC_EDIT1201 + i));
		_stprintf(c, _T("%d"), ((unsigned int*)&m_p)[i]);
		e->SetWindowText(c);
		s = (CSpinButtonCtrl *)(GetDlgItem(IDC_SPIN1201 + i));
		s->SetBuddy(e);
		s->SetRange(0,100);
	}
	m_bInitialized = true;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void ParameterView::OnEnChangeEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
	if(m_bInitialized) {
		// get current score params		
		CEdit * e = NULL;
		TCHAR t[256];
		for (int i = 0; i < 12*6; i++) {
			e = (CEdit *)(GetDlgItem(IDC_EDIT1201 + i));
			e->GetWindowText(t, 256);
			((unsigned int*)&m_p)[i] = _ttoi(t);
		}
		GetParent()->SendMessage(MY_PARAM_MSG, WPARAM (&m_p), NULL);
	}
}

// BirdView.cpp : implementation file
//

#include "stdafx.h"
#include "Lottery5.h"
#include "BirdView.h"

// BirdView dialog
extern Json::Value theTarget;	// current in process target
extern unsigned int nLoopCount; // current serial id
extern Json::Value theRecords; // all records of current session
extern char * m_pDownloadedBuffer; // the downloaded buffer
extern SOURCEMODE g_SourceMode;
extern const TCHAR  gcURL[256]; // the 256 is a random number

// BirdView dialog

IMPLEMENT_DYNAMIC(BirdView, CDialog)

BirdView::BirdView(CWnd* pParent /*=NULL*/)
	: CDialog(BirdView::IDD, pParent)
{

}

BirdView::~BirdView()
{
}

void BirdView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BirdView, CDialog)
	ON_LBN_DBLCLK(IDC_LISTSHEET, &BirdView::OnLbnDblclkListsheet)
	ON_LBN_SELCHANGE(IDC_LISTISSUE, &BirdView::OnLbnSelchangeListissue)
	ON_LBN_SELCHANGE(IDC_LISTPEOPLE, &BirdView::OnLbnSelchangeListpeople)
END_MESSAGE_MAP()


// BirdView message handlers

BOOL BirdView::OnInitDialog()
{
	CDialog::OnInitDialog();
	// step 0
	m_UNIfont.CreatePointFont(160, _T("宋体"));
	CWnd curritem;
	curritem.Attach(GetDlgItem(IDC_LISTSHEET)->m_hWnd);curritem.SetFont(&m_UNIfont, FALSE);curritem.Detach();
	curritem.Attach(GetDlgItem(IDC_LISTISSUE)->m_hWnd);curritem.SetFont(&m_UNIfont, FALSE);curritem.Detach();
	curritem.Attach(GetDlgItem(IDC_LISTPEOPLE)->m_hWnd);curritem.SetFont(&m_UNIfont, FALSE);curritem.Detach();
	// TODO:  Add extra initialization here

	// step 1: download data
	if(g_SourceMode != ONLINE_DOWNLOAD) {// fetch online data only once
		CInternetSession theSession;
		// use pageSize parameter to grab whole database
		CHttpFile* theContent = (CHttpFile*)theSession.OpenURL(gcURL);
		CString str;
		theContent->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, str);
		size_t theContentLength = _ttoi(LPCTSTR(str));
		if(theContentLength > 10000000) {
			// 10MB, too big? TODO: do something
			//assert(0);
		} else if (theContentLength < 200) { // too little, one record is 252
			MessageBox(_T("数据查询有误!"));
			return TRUE;
		}
		theContent->Read(m_pDownloadedBuffer, theContentLength);

		Json::Features thefeature = Json::Features::strictMode();
		Json::Reader theReader(thefeature);
		Json::Value theRoot;
		if(theReader.parse(m_pDownloadedBuffer, theRoot)) {
			int totalrecordcount = theRoot.get("total", 0).asInt();
			theRecords = theRoot["data"];
		}
		g_SourceMode = ONLINE_DOWNLOAD;
	}


	// step 2: analyze it
	TCHAR theString[256]; // set window text can be happy
	memset(theString, 0, sizeof(theString));
	for(unsigned int i=0; i<theRecords.size();i++) {
		bool f = false;
		// a. people
		for(unsigned int j = 0; j < m_People.size();j++) {
			MultiByteToWideChar(CP_UTF8, NULL, theRecords[i].get("userName", "NA").asCString(), -1, theString, 256);
			if(m_People[j] == theString) {
				f = true;
				break;
			}
		}
		// for i = 0 case
		if(i == 0) MultiByteToWideChar(CP_UTF8, NULL, theRecords[0].get("userName", "NA").asCString(), -1, theString, 256);
		if (!f) m_People.push_back(CString(theString));
		// b. issue
		f = false;
		for(unsigned int j=0; j<m_Issues.size();j++) {
			if(m_Issues[j] == theRecords[i].get("actionNumber1", "0000000").asCString())  {
				f = true;
				break;
			}
		}
		if (!f) m_Issues.push_back(CString(theRecords[i].get("actionNumber1", "0000000").asCString()));

		f = false;
		for(unsigned int j=0; j<m_Issues.size();j++) {
			if(m_Issues[j] == theRecords[i].get("actionNumber2", "0000000").asCString()) {
				f = true;
				break;
			}
		}
		if (!f) m_Issues.push_back(CString(theRecords[i].get("actionNumber2", "0000000").asCString()));

	}

	// we have enough issues, let's display them
	CListBox box;
	box.Attach(GetDlgItem(IDC_LISTISSUE)->m_hWnd);
	box.SetCurSel(0);
	for (unsigned int i=0; i < m_Issues.size(); i++) {
		box.InsertString(i, m_Issues[i]);
	}
	box.Detach();

	box.Attach(GetDlgItem(IDC_LISTPEOPLE)->m_hWnd);
	box.SetCurSel(0);
	for (unsigned int i=0; i < m_People.size(); i++) {
		box.InsertString(i, m_People[i]);
	}
	box.Detach();



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void BirdView::OnCbnEditchangeComboissue()
{
}

void BirdView::OnCbnSelchangeComboissue()
{

}

void BirdView::OnCbnSelchangeCombopeople()
{
}


void BirdView::OnLbnDblclkListsheet()
{
	// TODO: Add your control notification handler code here
	CListBox bigbox;
	bigbox.Attach(GetDlgItem(IDC_LISTSHEET)->m_hWnd);
	int index = bigbox.GetCurSel();
	int nMatch = 0;	
	if(m_Method == BYPEOPLE) {
		CListBox sb;
		sb.Attach(GetDlgItem(IDC_LISTPEOPLE)->m_hWnd);
		int sindex = sb.GetCurSel();
		sb.Detach();
		TCHAR theString[256]; // set window text can be happy
		for (unsigned int i = 0; i < theRecords.size(); i++) {
			MultiByteToWideChar(CP_UTF8, NULL, theRecords[i].get("userName", "NA").asCString(), -1, theString, 256);
			if(m_People[sindex] == CString (theString)) {
				if(nMatch == index) {
					theTarget = theRecords[i];
					break;
				}	
				nMatch++;
				continue;
			}
		} 
	} else if (m_Method == BYISSUE) {
		TCHAR theString[256]; // set window text can be happy
		for (unsigned int i = 0; i < theRecords.size(); i++) {
			MultiByteToWideChar(CP_UTF8, NULL, theRecords[i].get("userName", "NA").asCString(), -1, theString, 256);
			if(m_People[index] == theString) {
				nMatch++;
				if(nMatch == index) {
					theTarget = theRecords[i];
					break;
				}
				continue;
			}
		} 
	} else {
		//assert(0);
	}
	bigbox.Detach();
	EndDialog(IDOK); 
}

void BirdView::OnLbnSelchangeListissue()
{
	// TODO: Add your control notification handler code here
	CListBox bigbox;
	bigbox.Attach(GetDlgItem(IDC_LISTSHEET)->m_hWnd);
	bigbox.ResetContent();
	// get the selected index (n) for the combo box
	int n = 0;	
	TCHAR theString[256]; // set window text can be happy
	CListBox box;
	box.Attach(GetDlgItem(IDC_LISTISSUE)->m_hWnd);
	n = box.GetCurSel();
	box.Detach();
	// update content of the sheet
	for (unsigned int i = 0; i < theRecords.size(); i++) {
		CString s;
		// because issues will not be the same,
		// so we will NOT compare again if we found one match
		if(m_Issues[n] == theRecords[i].get("actionNumber1", "0000000").asCString()) {
			s += theRecords[i].get("actionNumber1", "0000000").asCString();
			s += _T("期 ");
			MultiByteToWideChar(CP_UTF8, NULL, theRecords[i].get("userName", "NA").asCString(), -1, theString, 256);
			s += theString;
			_stprintf(theString, _T(" id号%d "), theRecords[i].get("ticketUseId", "0").asInt());
			s += theString;	
			s += _T(" ");
			s += theRecords[i].get("dataOne1", "0000000").asCString();
			s += _T(" ");
			s += theRecords[i].get("dataOne2", "0000000").asCString();
			s += _T(" 结果 ");
			// TODO: 结果
			bigbox.AddString(s);
			continue;
		}
		if(m_Issues[n] == theRecords[i].get("actionNumber2", "0000000").asCString()) {
			s += theRecords[i].get("actionNumber2", "0000000").asCString();
			s += _T("期 ");
			MultiByteToWideChar(CP_UTF8, NULL, theRecords[i].get("userName", "NA").asCString(), -1, theString, 256);
			s += theString;
			_stprintf(theString, _T(" id号%d "), theRecords[i].get("ticketUseId", "0").asInt());
			s += theString;	
			s += _T(" ");
			s += theRecords[i].get("dataTwo1", "0000000").asCString();
			s += _T(" ");
			s += theRecords[i].get("dataTwo2", "0000000").asCString();
			s += _T(" 结果 ");
			// TODO: 结果
			bigbox.AddString(s);
			continue;
		}
	}
	bigbox.Detach();
	m_Method =  BYISSUE;
}

void BirdView::OnLbnSelchangeListpeople()
{
	// TODO: Add your control notification handler code here
	CListBox bigbox;
	bigbox.Attach(GetDlgItem(IDC_LISTSHEET)->m_hWnd);
	bigbox.ResetContent();
	// get the selected index (n) for the combo box
	int n = 0;	
	TCHAR theString[256]; // set window text can be happy
	CListBox box;
	box.Attach(GetDlgItem(IDC_LISTPEOPLE)->m_hWnd);
	n = box.GetCurSel();
	box.Detach();
	// update content of the sheet
	for (unsigned int i = 0; i < theRecords.size(); i++) {
		CString s;
		MultiByteToWideChar(CP_UTF8, NULL, theRecords[i].get("userName", "NA").asCString(), -1, theString, 256);
		if(m_People[n] == theString) {
			s += theString;	
			_stprintf(theString, _T(" id号%d "), theRecords[i].get("ticketUseId", "0").asInt());
			s += theString;	
			s += theRecords[i].get("actionNumber1", "0000000").asCString();
			s += _T("期 ");
			s += theRecords[i].get("dataOne1", "0000000").asCString();
			s += _T(" ");
			s += theRecords[i].get("dataOne2", "0000000").asCString();
			s += _T(" ");
			s += theRecords[i].get("actionNumber2", "0000000").asCString();
			s += _T("期 ");
			s += theRecords[i].get("dataTwo1", "0000000").asCString();
			s += _T(" ");
			s += theRecords[i].get("dataTwo2", "0000000").asCString();
			s += _T(" 结果 ");
			// TODO: 结果
			bigbox.AddString(s);
			continue;
		}
	}
	bigbox.Detach();
	m_Method =  BYPEOPLE;

}

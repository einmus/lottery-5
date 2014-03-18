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
END_MESSAGE_MAP()


// BirdView message handlers

BOOL BirdView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	// step 1: download data
	if(g_SourceMode != ONLINE_DOWNLOAD) {// fetch online data only once
		CInternetSession theSession;
		// use pageSize parameter to grab whole database
		CHttpFile* theContent = (CHttpFile*)theSession.OpenURL(_T("http://115.28.141.187/TicketManager/recordAction!searchTicket.action?pageSize=10000"));
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
	for(unsigned int i=0; i<theRecords.size();i++) {
		// b. issue
		unsigned int j;
		for(j=0; j<m_Issues.size();j++)
			if(m_Issues[j].first == theRecords[i].get("actionNumber1", "0000000").asCString()) break;
		if (j == m_Issues.size())
			m_Issues.push_back(make_pair(CString(theRecords[i].get("actionNumber1", "0000000").asCString()), theRecords[i]));

		for(j=0; j<m_Issues.size();j++)
			if(m_Issues[j].first == theRecords[i].get("actionNumber2", "0000000").asCString()) break;
		if (j == m_Issues.size())
			m_Issues.push_back(make_pair(CString(theRecords[i].get("actionNumber2", "0000000").asCString()), theRecords[i]));

	}
	// we have enough issues, let's display them
	CComboBox box;
	box.Attach(GetDlgItem(IDC_COMBOISSUE)->m_hWnd);
	box.SetCurSel(0);
	for (unsigned int i=0; i < m_Issues.size(); i++)
	{
		box.InsertString(i, m_Issues[i].first);
	}
	box.Detach();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

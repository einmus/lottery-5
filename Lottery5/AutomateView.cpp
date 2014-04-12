// AutomateView.cpp : implementation file
//

#include "stdafx.h"
#include "Lottery5.h"
#include "AutomateView.h"

extern Json::Value theTarget;	// current in process target
extern unsigned int nLoopCount; // current serial id
extern Json::Value theRecords; // all records of current session
extern char * m_pDownloadedBuffer; // the downloaded buffer
extern SOURCEMODE g_SourceMode;
extern const TCHAR  gcURL[256]; // the 256 is a random number
// AutomateView dialog

IMPLEMENT_DYNAMIC(AutomateView, CDialog)

AutomateView::AutomateView(CWnd* pParent /*=NULL*/)
	: CDialog(AutomateView::IDD, pParent)
{
	m_Thread = NULL;
}

AutomateView::~AutomateView()
{
}

void AutomateView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AutomateView, CDialog)
END_MESSAGE_MAP()


// AutomateView message handlers

BOOL AutomateView::OnInitDialog()
{
	CDialog::OnInitDialog();
	// use another thread to do the work
	m_Thread = AfxBeginThread(MyControllingFunction, this);
	if(m_Thread == NULL) ASSERT(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

UINT __cdecl AutomateView::MyControllingFunction( LPVOID pParam )
{
	AutomateView * v = (AutomateView *)pParam;
	// 1. refresh online data
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
			AfxMessageBox(_T("数据查询有误!"));
			return 0;
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
	// 2. use current method to process it and update progress bar along the way
	CProgressCtrl p;
	p.Attach(v->GetDlgItem(IDC_PROGRESSAUTOMATE)->m_hWnd);
	int s = theRecords.size();
	p.SetRange32(0, theRecords.size());
	for( ; nLoopCount < theRecords.size(); nLoopCount++) {
		//Sleep(1); // emulate work here for 100ms






		p.SetPos(nLoopCount);
	}
	p.Detach();
	return 0;
}

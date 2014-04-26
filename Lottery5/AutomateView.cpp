// AutomateView.cpp : implementation file
//

#include "stdafx.h"
#include "Lottery5.h"
#include "AutomateView.h"
#include "Lottery5Dlg.h"

extern Json::Value theTarget;	// current in process target
extern unsigned int nLoopCount; // current serial id
extern Json::Value theRecords; // all records of current session
extern char * m_pDownloadedBuffer; // the downloaded buffer
extern SOURCEMODE g_SourceMode;
extern const TCHAR  gcURL[256]; // the 256 is a random number

// fill item content to CString
void FillItemContent(CString & s, Json::Value & r) {
	TCHAR zs[256]; // set window text can be happy
	MultiByteToWideChar(CP_UTF8, NULL, r.get("userName", "NA").asCString(), -1, zs, 256);
	s += zs; s += _T("\r\n");
	_stprintf(zs, _T(" id号%d "), r.get("ticketUseId", "0").asInt());
	s += zs; s += _T("\r\n");	
	MultiByteToWideChar(CP_UTF8, NULL, r.get("analyseState", "00").asCString(), -1, zs, 256);
	s += r.get("actionNumber1", "0000000").asCString();
	s += _T("期 ");
	s += r.get("dataOne1", "0000000").asCString();
	s += _T(" ");
	s += r.get("dataOne2", "0000000").asCString();
	s += _T("\r\n");
	s += r.get("actionNumber2", "0000000").asCString();
	s += _T("期 ");
	s += r.get("dataTwo1", "0000000").asCString();
	s += _T(" ");
	s += r.get("dataTwo2", "0000000").asCString();
	s += _T("\r\n");
	s += _T(" 结果 "); s += zs;
}

// AutomateView dialog

IMPLEMENT_DYNAMIC(AutomateView, CDialog)

AutomateView::AutomateView(CWnd* pParent /*=NULL*/)
	: CDialog(AutomateView::IDD, pParent)
{
	m_thread = NULL;
}

AutomateView::~AutomateView()
{
}

void AutomateView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AutomateView, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// AutomateView message handlers

BOOL AutomateView::OnInitDialog()
{
	CDialog::OnInitDialog();
	// use another thread to do the work
	m_thread = AfxBeginThread(MyControllingFunction, this);
	if(m_thread == NULL) ASSERT(0);
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

	CInternetSession theSession;
	for( ; nLoopCount < theRecords.size(); nLoopCount++) {
		double s[4];
		{ // get score
			CLottery5Dlg * d = (CLottery5Dlg *)v->GetParent();
			theTarget = theRecords[nLoopCount];
			d->AnalyzeCurrentChosenTarget(s);
			char zs[256];
			sprintf(zs, "%d%d", s[0] > s[1] ? 1 : 2, s[2] > s[3] ? 1 : 2);
			theRecords[nLoopCount]["analyseState"] = zs;
		}

		CString s_info;FillItemContent(s_info, theRecords[nLoopCount]);

		{ // send back to server
			int targetid = theTarget.get("ticketUseId", "0").asInt();
			TCHAR theURL[256];
			_stprintf(theURL, _T("http://115.28.141.187/TicketManager/recordAction!submitTicketAnalyseState.action?ticketUseId=%d&analyseState=%d%d"), targetid, s[0] > s[1] ? 1 : 2, s[2] > s[3] ? 1 : 2);
			CHttpFile* theContent = (CHttpFile*)theSession.OpenURL(theURL);
			CString str;
			theContent->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, str);
			size_t theContentLength = _ttoi(LPCTSTR(str));
			if(theContentLength > 5000000) {
				// 5MB, too big? TODO: do something
				//assert(0);
			} else if (theContentLength < 5) { // too little, one record is 252
				v->MessageBox(_T("数据通信有误!"));
				return -1;
			}
			char* pBuffer = (char*)malloc(theContentLength);
			theContent->Read(pBuffer, theContentLength);
			Json::Reader theReader;
			Json::Value theRoot;
			if(theReader.parse(pBuffer, theRoot)) {
				int returncode = theRoot.get("code", 0).asInt();
				if(returncode == 1) {
					s_info += _T("\r\n上传成功");
				} else {
					s_info += _T("\r\n上传失败");
				}
			} else {
				s_info += _T("\r\n上传失败");
			}
			free(pBuffer);
		}
		{ // update infos
			CEdit e;e.Attach(v->GetDlgItem(IDC_EDITAUTOMATEINFO)->m_hWnd);
			e.SetWindowText(s_info);
			e.Detach();
		}
		p.SetPos(nLoopCount);
	}
	p.Detach();
	return 0;
}

void AutomateView::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	DWORD exit_code= NULL;
	if (m_thread != NULL)
	{
		GetExitCodeThread(m_thread->m_hThread, &exit_code);
		if(exit_code == STILL_ACTIVE)
		{
			::TerminateThread(m_thread->m_hThread, 0);
			CloseHandle(m_thread->m_hThread);
		}
		m_thread->m_hThread = NULL;
		m_thread = NULL;
	}
	CDialog::OnClose();
}

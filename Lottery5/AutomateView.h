#pragma once


// AutomateView dialog

class AutomateView : public CDialog
{
	DECLARE_DYNAMIC(AutomateView)

public:
	AutomateView(CWnd* pParent = NULL);   // standard constructor
	virtual ~AutomateView();

// Dialog Data
	enum { IDD = IDD_DIALOGAUTOMATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	static UINT __cdecl MyControllingFunction( LPVOID pParam );
private:
	CWinThread* m_thread;
public:
	afx_msg void OnClose();
};

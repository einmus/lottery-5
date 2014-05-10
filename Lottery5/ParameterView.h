#pragma once


// ParameterView dialog

class ParameterView : public CDialog
{
	DECLARE_DYNAMIC(ParameterView)

public:
	ParameterView(MyParam p, CWnd* pParent = NULL);   // standard constructor
	virtual ~ParameterView();

// Dialog Data
	enum { IDD = IDD_DIALOGPARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit();
private:
	bool m_bInitialized;
	MyParam m_p;
};

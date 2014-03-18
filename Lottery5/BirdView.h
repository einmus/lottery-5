#pragma once



class BirdView : public CDialog
{
	DECLARE_DYNAMIC(BirdView)

public:
	BirdView(CWnd* pParent = NULL);   // standard constructor
	virtual ~BirdView();

// Dialog Data
	enum { IDD = IDD_BIRDVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:
	//vector<CString, Json::Value> m_People;
	vector<pair<CString, Json::Value>> m_Issues;
};

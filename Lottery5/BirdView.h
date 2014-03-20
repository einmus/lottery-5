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
	vector<CString> m_People;
	vector<CString> m_Issues;
public:
	afx_msg void OnCbnEditchangeComboissue();
	afx_msg void OnCbnSelchangeComboissue();
};

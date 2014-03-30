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
	CFont m_UNIfont;
	enum SORT_METHOD {
		BYISSUE = 0,
		BYPEOPLE = 1,
	} m_Method;
public:
	afx_msg void OnCbnEditchangeComboissue();
	afx_msg void OnCbnSelchangeComboissue();
	afx_msg void OnCbnSelchangeCombopeople();
	afx_msg void OnLbnDblclkListsheet();
	afx_msg void OnLbnSelchangeListissue();
	afx_msg void OnLbnSelchangeListpeople();
};

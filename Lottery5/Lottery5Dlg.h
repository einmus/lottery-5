
// Lottery5Dlg.h : 头文件
//

#pragma once

// CLottery5Dlg 对话框
class CLottery5Dlg : public CDialog
{
// 构造
public:
	CLottery5Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LOTTERY5_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAction();  
    void Parse8Gua(CString& csGua, int & nIndex0, int & nIndex1);
    void Parse64Gua(CString& csGua, int & iIndex4);
    void Parse64Gua2( CString& csGua, int & iIndex4 );
	bool TackleShiftGua(CString& csGua, CString& csGua1, CString& csGua2);
	bool IsInputLegit(CString& csInput);
    afx_msg void OnBnClickedButton2();
    void OnGroupChange();

private:
    //headline, usual, smaller
    CFont m_UNIfont[4];
    CBitmap m_Gua[8];
    int bInitialResult;
    UINT nCurrDisplayGroup;

public:
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedGroupadd();
    afx_msg void OnBnClickedGroupsubstract();
    void DisplayBallonTip(int iID);
    afx_msg void OnCbnSelchangeWei1(){if(bInitialResult)OnBnClickedButtonAction();}
    afx_msg void OnCbnSelchangeWei2(){if(bInitialResult)OnBnClickedButtonAction();}
    afx_msg void OnCbnSelchangeWei3(){if(bInitialResult)OnBnClickedButtonAction();}
    afx_msg void OnCbnSelchangeAdject1(){if(bInitialResult)OnBnClickedButtonAction();}
    afx_msg void OnCbnSelchangeAdject2(){if(bInitialResult)OnBnClickedButtonAction();}
    afx_msg void OnCbnSelchangeAdject3(){if(bInitialResult)OnBnClickedButtonAction();}
    afx_msg void OnCbnSelchangeCase1(){if(bInitialResult)OnBnClickedButtonAction();}
    afx_msg void OnCbnSelchangeCase2(){if(bInitialResult)OnBnClickedButtonAction();}
    afx_msg void OnCbnSelchangeCase3(){if(bInitialResult)OnBnClickedButtonAction();}
    afx_msg void OnBnClickedButtonclear();
	afx_msg void OnBnClickedButtonRandom();
	afx_msg void OnBnClickedButtongetonline();
	afx_msg void OnBnClickedButtonmark();
	afx_msg void OnBnClickedButtonBirdview();
	afx_msg void OnBnClickedButtonautomate();
	// Analyze current chosen target
	void AnalyzeCurrentChosenTarget(double * score);
	afx_msg LRESULT OnParamChanged(WPARAM wparam , LPARAM lparam);
	afx_msg void OnBnClickedButtonShowParam();
	afx_msg void OnBnClickedButtonP0();
	int iG[4];
	afx_msg void OnBnClickedButtonP1();
	afx_msg void OnBnClickedButtonP2();
	afx_msg void OnBnClickedButtonP3();
};


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
	afx_msg void OnBnClickedButton1();  
    void Parse8Gua(CString& csGua, int & nIndex0, int & nIndex1);
    void Parse64Gua(CString& csGua, int & iIndex4);
    void Parse64Gua2( CString& csGua, int & iIndex4 );
	bool TackleShiftGua(CString& csGua, CString& csGua1, CString& csGua2);
	bool IsInputLegit(CString& csInput);
    void AppendGuaContent(CString &csDisplay, CString csForcast);
    afx_msg void OnBnClickedButton2();
    void AddMarker(CString& csInput, wchar_t wch0, wchar_t wch1, wchar_t wch2);
    void OnGroupChange();

private:
    //headline, usual, smaller
    CFont m_UNIfont[4];
    UINT nCurrDisplayGroup;
    CBitmap m_Gua[8];
    int bInitialResult;
public:
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedGroupadd();
    afx_msg void OnBnClickedGroupsubstract();
    void DisplayBallonTip(int nID);
    afx_msg void OnCbnSelchangeWei1(){if(bInitialResult)OnBnClickedButton1();}
    afx_msg void OnCbnSelchangeWei2(){if(bInitialResult)OnBnClickedButton1();}
    afx_msg void OnCbnSelchangeWei3(){if(bInitialResult)OnBnClickedButton1();}
    afx_msg void OnCbnSelchangeAdject1(){if(bInitialResult)OnBnClickedButton1();}
    afx_msg void OnCbnSelchangeAdject2(){if(bInitialResult)OnBnClickedButton1();}
    afx_msg void OnCbnSelchangeAdject3(){if(bInitialResult)OnBnClickedButton1();}
    afx_msg void OnCbnSelchangeCase1(){if(bInitialResult)OnBnClickedButton1();}
    afx_msg void OnCbnSelchangeCase2(){if(bInitialResult)OnBnClickedButton1();}
    afx_msg void OnCbnSelchangeCase3(){if(bInitialResult)OnBnClickedButton1();}
    afx_msg void OnBnClickedButtonclear();
};

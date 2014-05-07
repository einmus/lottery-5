
// Lottery5Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Lottery5.h"
#include "Lottery5Dlg.h"
#include "NongLi.h"
#include "GanZhi.h"
#include <Richedit.h>
#include "BirdView.h"
#include "AutomateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// TODO: proper handling of these datas
Json::Value theTarget;	// current in process target
unsigned int nLoopCount; // current serial id
Json::Value theRecords; // all records of current session
char * m_pDownloadedBuffer; // the downloaded buffer
SOURCEMODE g_SourceMode;
extern const TCHAR gcURL[] = _T("http://115.28.141.187/TicketManager/recordAction!searchTicket.action?pageSize=10000");

const TCHAR SIXTYFOURGUA[] = _T("地天泰 山天大畜水天需 风天小畜雷天大壮火天大有泽天夬 乾为天 地泽临 山泽损 水泽节 风泽中孚雷泽归妹火泽睽 兑为泽 天泽履 地火明夷山火贲 水火既济风火家人雷火豊 离为火 泽火革 天火同人地雷复 山雷颐 水雷屯 风雷益 震为雷 火雷噬嗑泽雷随 天雷无妄地风升 山风蛊 水风井 巽为风 雷风恒 火风鼎 泽风大过天风姤 地水师 山水蒙 坎为水 风水涣 雷水解 火水未济泽水困 天水讼 地山谦 艮为山 水山蹇 风山渐 雷山小过火山旅 泽山咸 天山遁 坤为地 山地剥 水地比 风地观 雷地豫 火地晋 泽地萃 天地否 ");
const TCHAR EIGHTGUA[] = _T("☰☱☲☳☴☵☶☷");
const TCHAR SHICHEN[] = _T("子丑寅卯辰巳午未申酉戌亥");
const int BXIndex[] = {0,61,7,60,33,62,50,59,53,8,52,15,54,41,51,58,23,44,16,45,34,43,49,46,36,31,37,24,35,42,38,57,1,30,18,27,32,29,39,28,22,9,19,26,21,40,20,47,2,11,17,14,55,12,48,13,3,10,6,25,4,63,5,56};
TCHAR * BXContent[] = {_T("父母壬戌土、世"), _T("兄弟壬申金、"), _T("官鬼壬午火、"), _T("父母甲辰土、应"), _T("妻财甲寅木、"), _T("子孙甲子水"), _T("父母壬戌土、"), _T("兄弟壬申金、"), _T("官鬼壬午火、应"), _T("兄弟辛酉金、"), _T("子孙辛亥水、"), _T("父母辛丑土、、世"), _T("父母壬戌土、"), _T("兄弟壬申金、应"), _T("官鬼壬午火、"), _T("兄弟丙申金、"), _T("官鬼丙午火、、世"), _T("父母丙辰土、、"), _T("父母壬戌土、应"), _T("兄弟壬申金、"), _T("官鬼壬午火、"), _T("妻财乙卯木、、世"), _T("官鬼乙巳火、、"), _T("父母乙未土、、"), _T("妻财辛卯木、"), _T("官鬼辛巳火、"), _T("父母辛未土、、世"), _T("妻财乙卯木、、"), _T("官鬼乙巳火、、"), _T("父母乙未土、、应"), _T("妻财丙寅木、"), _T("子孙丙子水、、世"), _T("父母丙戌土、、"), _T("妻财乙卯木、、"), _T("官鬼乙巳火、、应"), _T("父母乙未土、、"), _T("官鬼己巳火、"), _T("父母己未土、、"), _T("兄弟己酉金、世"), _T("妻财乙卯木、、"), _T("官鬼乙巳火、、"), _T("父母乙未土、、应"), _T("官鬼己巳火、应"), _T("父母己未土、、"), _T("兄弟己酉金、"), _T("父母甲辰土、世"), _T("妻财甲寅木、"), _T("子孙甲子水、"), _T("父母丁未土、、世"), _T("兄弟丁酉金、"), _T("子孙丁亥水、"), _T("父母丁丑土、、应"), _T("妻财丁卯木、"), _T("官鬼丁巳火、"), _T("父母丁未土、、"), _T("兄弟丁酉金、"), _T("子孙丁亥水、应"), _T("官鬼戊午火、、"), _T("父母戊辰土、"), _T("妻财戊寅木、、世"), _T("父母丁未土、、"), _T("兄弟丁酉金、应"), _T("子孙丁亥水、"), _T("妻财乙卯木、、"), _T("官鬼乙巳火、、世"), _T("父母乙未土、、"), _T("父母丁未土、、应"), _T("兄弟丁酉金、"), _T("子孙丁亥水、"), _T("兄弟丙申金、世"), _T("官鬼丙午火、、"), _T("父母丙辰土、、"), _T("子孙戊子水、、"), _T("父母戊戌土、"), _T("兄弟戊申金、、世"), _T("兄弟丙申金、"), _T("官鬼丙午火、、"), _T("父母丙辰土、、应"), _T("兄弟癸酉金、、"), _T("子孙癸亥水、、世"), _T("父母癸丑土、、"), _T("兄弟丙申金、"), _T("官鬼丙午火、、应"), _T("父母丙辰土、、"), _T("父母庚戌土、、"), _T("兄弟庚申金、、"), _T("官鬼庚午火、世"), _T("兄弟丙申金、"), _T("官鬼丙午火、、"), _T("父母丙辰土、、应"), _T("父母庚戌土、、应"), _T("兄弟庚申金、、"), _T("官鬼庚午火、"), _T("父母丁丑土、、世"), _T("妻财丁卯木、"), _T("官鬼丁巳火、"), _T("兄弟己巳火、世"), _T("子孙己未土、、"), _T("妻财己酉金、"), _T("官鬼己亥水、应"), _T("子孙己丑土、、"), _T("父母己卯木、"), _T("兄弟己巳火、"), _T("子孙己未土、、"), _T("妻财己酉金、应"), _T("妻财丙申金、"), _T("兄弟丙午火、、"), _T("子孙丙辰土、、世"), _T("兄弟己巳火、"), _T("子孙己未土、、应"), _T("妻财己酉金、"), _T("妻财辛酉金、"), _T("官鬼辛亥水、世"), _T("子孙辛丑土、、"), _T("兄弟己巳火、应"), _T("子孙己未土、、"), _T("妻财己酉金、"), _T("兄弟戊午火、、世"), _T("子孙戊辰土、"), _T("父母戊寅木、、"), _T("父母丙寅木、"), _T("官鬼丙子水、、"), _T("子孙丙戌土、、世"), _T("兄弟戊午火、、"), _T("子孙戊辰土、"), _T("父母戊寅木、、应"), _T("父母辛卯木、"), _T("兄弟辛巳火、世"), _T("子孙辛未土、、"), _T("兄弟戊午火、、"), _T("子孙戊辰土、应"), _T("父母戊寅木、、"), _T("子孙壬戌土、"), _T("妻财壬申金、"), _T("兄弟壬午火、世"), _T("兄弟戊午火、、"), _T("子孙戊辰土、"), _T("父母戊寅木、、应"), _T("子孙壬戌土、应"), _T("妻财壬申金、"), _T("兄弟壬午火、"), _T("官鬼己亥水、世"), _T("子孙己丑土、、"), _T("父母己卯木、"), _T("妻财庚戌土、、世"), _T("官鬼庚申金、、"), _T("子孙庚午火、"), _T("妻财庚辰土、、应"), _T("兄弟庚寅木、、"), _T("父母庚子水、"), _T("妻财庚戌土、、"), _T("官鬼庚申金、、"), _T("子孙庚午火、应"), _T("兄弟乙卯木、、"), _T("子孙乙巳火、、"), _T("妻财乙未土、、世"), _T("妻财庚戌土、、"), _T("官鬼庚申金、、应"), _T("子孙庚午火、"), _T("子孙戊午火、、"), _T("妻财戊辰土、世"), _T("兄弟戊寅木、、"), _T("妻财庚戌土、、应"), _T("官鬼庚申金、、"), _T("子孙庚午火、"), _T("官鬼辛酉金、世"), _T("父母辛亥水、"), _T("妻财辛丑土、、"), _T("官鬼癸酉金、、"), _T("父母癸亥水、、"), _T("妻财癸丑土、、世"), _T("官鬼辛酉金、"), _T("父母辛亥水、"), _T("妻财辛丑土、、应"), _T("父母戊子水、、"), _T("妻财戊戌土、世"), _T("官鬼戊申金、、"), _T("官鬼辛酉金、"), _T("父母辛亥水、应"), _T("妻财辛丑土、、"), _T("妻财丁未土、、"), _T("官鬼丁酉金、"), _T("父母丁亥水、世"), _T("官鬼辛酉金、"), _T("父母辛亥水、"), _T("妻财辛丑土、、应"), _T("妻财丁未土、、应"), _T("官鬼丁酉金、"), _T("父母丁亥水、"), _T("妻财庚辰土、、世"), _T("兄弟庚寅木、、"), _T("父母庚子水、"), _T("兄弟辛卯木、世"), _T("子孙辛巳火、"), _T("妻财辛未土、、"), _T("官鬼辛酉金、应"), _T("父母辛亥水、"), _T("妻财辛丑土、、"), _T("兄弟辛卯木、"), _T("子孙辛巳火、"), _T("妻财辛未土、、应"), _T("妻财甲辰土、"), _T("兄弟甲寅木、"), _T("父母甲子水、世"), _T("兄弟辛卯木、"), _T("子孙辛巳火、应"), _T("妻财辛未土、、"), _T("父母己亥水、"), _T("妻财己丑土、、世"), _T("兄弟己卯木、"), _T("兄弟辛卯木、应"), _T("子孙辛巳火、"), _T("妻财辛未土、、"), _T("妻财庚辰土、、世"), _T("兄弟庚寅木、、"), _T("父母庚子水、"), _T("妻财壬戌土、"), _T("官鬼壬申金、"), _T("子孙壬午火、世"), _T("妻财庚辰土、、"), _T("兄弟庚寅木、、"), _T("父母庚子水、应"), _T("子孙己巳火、"), _T("妻财己未土、、世"), _T("官鬼己酉金、"), _T("妻财庚辰土、、"), _T("兄弟庚寅木、、应"), _T("父母庚子水、"), _T("兄弟丙寅木、"), _T("父母丙子水、、"), _T("妻财丙戌土、、世"), _T("妻财庚辰土、、"), _T("兄弟庚寅木、、"), _T("父母庚子水、应"), _T("兄弟丙寅木、应"), _T("父母丙子水、、"), _T("妻财丙戌土、、"), _T("官鬼辛酉金、世"), _T("父母辛亥水、"), _T("妻财辛丑土、、"), _T("兄弟戊子水、、世"), _T("官鬼戊戌土、"), _T("父母戊申金、、"), _T("妻财戊午火、、应"), _T("官鬼戊辰土、"), _T("子孙戊寅木、、"), _T("兄弟戊子水、、"), _T("官鬼戊戌土、"), _T("父母戊申金、、应"), _T("官鬼丁丑土、、"), _T("子孙丁卯木、"), _T("妻财丁巳火、世"), _T("兄弟戊子水、、"), _T("官鬼戊戌土、应"), _T("父母戊申金、、"), _T("官鬼庚辰土、、"), _T("子孙庚寅木、、世"), _T("兄弟庚子水、"), _T("兄弟戊子水、、应"), _T("官鬼戊戌土、"), _T("父母戊申金、、"), _T("兄弟己亥水、世"), _T("官鬼己丑土、、"), _T("子孙己卯木、"), _T("官鬼丁未土、、"), _T("父母丁酉金、"), _T("兄弟丁亥水、世"), _T("兄弟己亥水、"), _T("官鬼己丑土、、"), _T("子孙己卯木、应"), _T("官鬼庚戌土、、"), _T("父母庚申金、、世"), _T("妻财庚午火、"), _T("兄弟己亥水、"), _T("官鬼己丑土、、应"), _T("子孙己卯木、"), _T("父母癸酉金、、"), _T("兄弟癸亥水、、"), _T("官鬼癸丑土、、世"), _T("兄弟己亥水、"), _T("官鬼己丑土、、"), _T("子孙己卯木、应"), _T("父母癸酉金、、应"), _T("兄弟癸亥水、、"), _T("官鬼癸丑土、、"), _T("妻财戊午火、、世"), _T("官鬼戊辰土、"), _T("子孙戊寅木、、"), _T("官鬼丙寅木、世"), _T("妻财丙子水、、"), _T("兄弟丙戌土、、"), _T("子孙丙申金、应"), _T("父母丙午火、、"), _T("兄弟丙辰土、、"), _T("官鬼丙寅木、"), _T("妻财丙子水、、"), _T("兄弟丙戌土、、应"), _T("妻财己亥水、"), _T("兄弟己丑土、、"), _T("官鬼己卯木、世"), _T("官鬼丙寅木、"), _T("妻财丙子水、、应"), _T("兄弟丙戌土、、"), _T("兄弟甲辰土、"), _T("官鬼甲寅木、世"), _T("妻财甲子水、"), _T("官鬼丙寅木、应"), _T("妻财丙子水、、"), _T("兄弟丙戌土、、"), _T("兄弟丁丑土、、世"), _T("官鬼丁卯木、"), _T("父母丁巳火、"), _T("父母己巳火、"), _T("兄弟己未土、、"), _T("子孙己酉金、世"), _T("兄弟丁丑土、、"), _T("官鬼丁卯木、"), _T("父母丁巳火、应"), _T("兄弟壬戌土、"), _T("子孙壬申金、世"), _T("父母壬午火、"), _T("兄弟丁丑土、、"), _T("官鬼丁卯木、应"), _T("父母丁巳火、"), _T("官鬼辛卯木、"), _T("父母辛巳火、"), _T("兄弟辛未土、、世"), _T("兄弟丁丑土、、"), _T("官鬼丁卯木、"), _T("父母丁巳火、应"), _T("官鬼辛卯木、应"), _T("父母辛巳火、"), _T("兄弟辛未土、、"), _T("子孙丙申金、世"), _T("父母丙午火、、"), _T("兄弟丙辰土、、"), _T("子孙癸酉金、、世"), _T("妻财癸亥水、、"), _T("兄弟癸丑土、、"), _T("官鬼乙卯木、、应"), _T("父母乙巳火、、"), _T("兄弟乙未土、、"), _T("子孙癸酉金、、"), _T("妻财癸亥水、、"), _T("兄弟癸丑土、、应"), _T("兄弟庚辰土、、"), _T("官鬼庚寅木、、"), _T("妻财庚子水、世"), _T("子孙癸酉金、、"), _T("妻财癸亥水、、应"), _T("兄弟癸丑土、、"), _T("兄弟丁丑土、、"), _T("官鬼丁卯木、世"), _T("父母丁巳火、"), _T("子孙癸酉金、、应"), _T("妻财癸亥水、、"), _T("兄弟癸丑土、、"), _T("兄弟甲辰土、世"), _T("官鬼甲寅木、"), _T("妻财甲子水、"), _T("兄弟庚戌土、、"), _T("子孙庚申金、、"), _T("父母庚午火、世"), _T("兄弟甲辰土、"), _T("官鬼甲寅木、"), _T("妻财甲子水、应"), _T("兄弟丁未土、、"), _T("子孙丁酉金、世"), _T("妻财丁亥水、"), _T("兄弟甲辰土、"), _T("官鬼甲寅木、应"), _T("妻财甲子水、"), _T("妻财戊子水、、"), _T("兄弟戊戌土、"), _T("子孙戊申金、、世"), _T("兄弟甲辰土、"), _T("官鬼甲寅木、"), _T("妻财甲子水、应"), _T("妻财戊子水、、应"), _T("兄弟戊戌土、"), _T("子孙戊申金、、"), _T("官鬼乙卯木、、世"), _T("父母乙巳火、、"), _T("兄弟乙未土、、")};
// vector<CHARRANGE> vCRUpper;
// vector<CHARRANGE> vCRDowner;
CArray<CHARRANGE> vCRUpper; 
CArray<CHARRANGE>  vCRDowner;

//#include <vector>
//using namespace std;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
static DWORD CALLBACK MyStreamOutCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
    CFile* pFile = (CFile*) dwCookie;

    pFile->Write(pbBuff, cb);
    *pcb = cb;

    return 0;
}

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // 对话框数据
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    // 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CLottery5Dlg 对话框




CLottery5Dlg::CLottery5Dlg(CWnd* pParent /*=NULL*/)
: CDialog(CLottery5Dlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLottery5Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLottery5Dlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTONACTION, &CLottery5Dlg::OnBnClickedButtonAction)
    ON_BN_CLICKED(IDC_BUTTON2, &CLottery5Dlg::OnBnClickedButton2)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_GROUPADD, &CLottery5Dlg::OnBnClickedGroupadd)
    ON_BN_CLICKED(IDC_GROUPSUBSTRACT, &CLottery5Dlg::OnBnClickedGroupsubstract)
    ON_CBN_SELCHANGE(IDC_WEI1, &CLottery5Dlg::OnCbnSelchangeWei1)
    ON_CBN_SELCHANGE(IDC_WEI2, &CLottery5Dlg::OnCbnSelchangeWei2)
    ON_CBN_SELCHANGE(IDC_WEI3, &CLottery5Dlg::OnCbnSelchangeWei3)
    ON_CBN_SELCHANGE(IDC_ADJECT1, &CLottery5Dlg::OnCbnSelchangeAdject1)
    ON_CBN_SELCHANGE(IDC_ADJECT2, &CLottery5Dlg::OnCbnSelchangeAdject2)
    ON_CBN_SELCHANGE(IDC_ADJECT3, &CLottery5Dlg::OnCbnSelchangeAdject3)
    ON_CBN_SELCHANGE(IDC_CASE1, &CLottery5Dlg::OnCbnSelchangeCase1)
    ON_CBN_SELCHANGE(IDC_CASE2, &CLottery5Dlg::OnCbnSelchangeCase2)
    ON_CBN_SELCHANGE(IDC_CASE3, &CLottery5Dlg::OnCbnSelchangeCase3)
    ON_BN_CLICKED(IDC_BUTTONCLEAR, &CLottery5Dlg::OnBnClickedButtonclear)
	ON_BN_CLICKED(IDC_BUTTONRANDOM, &CLottery5Dlg::OnBnClickedButtonrandom)
	ON_BN_CLICKED(IDC_BUTTONGETONLINE, &CLottery5Dlg::OnBnClickedButtongetonline)
	ON_BN_CLICKED(IDC_BUTTONMARK, &CLottery5Dlg::OnBnClickedButtonmark)
	ON_BN_CLICKED(IDC_BUTTONBIRDVIEW, &CLottery5Dlg::OnBnClickedButtonbirdview)
	ON_BN_CLICKED(IDC_BUTTONAUTOMATE, &CLottery5Dlg::OnBnClickedButtonautomate)
END_MESSAGE_MAP()


// CLottery5Dlg 消息处理程序

BOOL CLottery5Dlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    // TODO: 在此添加额外的初始化代码

    //创建默认字体
    m_UNIfont[0].CreatePointFont(160, _T("华文楷体"));
    m_UNIfont[1].CreatePointFont(120, _T("华文宋体"));
    m_UNIfont[2].CreatePointFont(100, _T("宋体"));
    m_UNIfont[3].CreatePointFont(160, _T("宋体"));
    //创建八卦图
    for(int i=0;i<8;i++)
        m_Gua[i].LoadBitmap(IDB_BITMAP8-i);
    //创建"组"字
    CWnd curritem;
    curritem.Attach(GetDlgItem(IDC_ZU)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_EDIT7)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_EDIT9)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_EDIT16)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_EDIT17)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_EDIT2)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_EDIT5)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_EDIT14)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_EDIT15)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_SCORE1)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_SCORE2)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_RESULT1)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_RESULT2)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();
    curritem.Attach(GetDlgItem(IDC_EDIT11)->m_hWnd);curritem.SetFont(&m_UNIfont[0], FALSE);curritem.Detach();

    for(int ii=0;ii<12;ii++){
        curritem.Attach(GetDlgItem(IDC_STATIC11+ii)->m_hWnd);curritem.SetFont(&m_UNIfont[2], FALSE);curritem.Detach();
    }

    nCurrDisplayGroup = 1;

    CComboBox box;
    for(int ii=0;ii<3;ii++){
        box.Attach(GetDlgItem(IDC_WEI1+ii)->m_hWnd);box.SetCurSel(0); box.Detach();
        box.Attach(GetDlgItem(IDC_ADJECT1+ii)->m_hWnd);box.SetCurSel(0); box.Detach();
        box.Attach(GetDlgItem(IDC_CASE1+ii)->m_hWnd);box.SetCurSel(0); box.Detach();
    }

    bInitialResult = false;
	// default source mode is from local input
	g_SourceMode = LOCAL_INPUT;
	m_pDownloadedBuffer = (char *)malloc(5000000); // 5MB;
	nLoopCount = 0;

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLottery5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLottery5Dlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLottery5Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

//up 0下，1上
//ori 0变卦，1原卦
int str2gua(CString &in, UINT up, UINT ori){
    int d=up*3;
    in[d+0], in[d+1], in[d+2];
    if(ori)
        return
        ((in[d+2]-_T('0'))%2 == 0?0:1) << 0 |
        ((in[d+1]-_T('0'))%2 == 0?0:1) << 1 |
        ((in[d+0]-_T('0'))%2 == 0?0:1) << 2 ;
    else
        return
        (in[d+2]<(_T('2'))?1:0) << 0 |
        (in[d+1]<(_T('2'))?1:0) << 1 |
        (in[d+0]<(_T('2'))?1:0) << 2 ;
}
int eightguas_64index(int down, int up){
    return (down |  (7-up)<< 3);
}
int eightguas_64index2(int down, int up){
    return ((7-down) |  (7-up)<< 3);
}
bool dyis(TCHAR dy[6], ...){
    va_list arguments;
    TCHAR c;
    va_start ( arguments, dy[6]);
    c = va_arg ( arguments, TCHAR );
    for (int i=0;i<6;i++)
        if (dy[i]==c)
            return true;
    va_end ( arguments );
    return false;
}
bool fC(TCHAR in, TCHAR ref, TCHAR M, TCHAR D, TCHAR H, TCHAR *by)//assume by is 6 , fC fit condition
{
    if(in != ref)
        return true;

    for (int ii=0;ii<6;ii++)
    {
        if (in = by[ii])
            return true;
    }
    switch(in)
    {
    case _T('子'):
        return ((M==_T('酉')||M==_T('申')||M==_T('亥')||M==_T('子'))&&(D==_T('酉')||D==_T('申')||D==_T('亥')||D==_T('子'))) ||
            (D == _T('午'));
    case _T('丑'):
        return ((M==_T('巳')||M==_T('午')||M==_T('辰')||M==_T('戌')||M==_T('丑'))&&(D==_T('巳')||D==_T('午')||D==_T('辰')||D==_T('戌')||D==_T('丑'))) ||
            (D == _T('未'));
    case _T('寅'):
        return ((M==_T('亥')||M==_T('寅')||M==_T('卯')||M==_T('子'))&&(D==_T('亥')||D==_T('寅')||D==_T('卯')||D==_T('子'))) ||
            (D == _T('申'));
    case _T('卯'):
        return ((M==_T('亥')||M==_T('寅')||M==_T('卯')||M==_T('子'))&&(D==_T('亥')||D==_T('寅')||D==_T('卯')||D==_T('子'))) ||
            (D == _T('酉'));
    case _T('辰'):
        return ((M==_T('巳')||M==_T('午')||M==_T('辰')||M==_T('未')||M==_T('丑'))&&(D==_T('巳')||D==_T('午')||D==_T('辰')||D==_T('未')||D==_T('丑'))) ||
            (D == _T('戌'));
    case _T('巳'):
        return ((M==_T('午')||M==_T('寅')||M==_T('卯')||M==_T('巳'))&&(D==_T('午')||D==_T('寅')||D==_T('卯')||D==_T('巳'))) ||
            (D == _T('亥'));
    case _T('午'):
        return ((M==_T('午')||M==_T('寅')||M==_T('卯')||M==_T('巳'))&&(D==_T('午')||D==_T('寅')||D==_T('卯')||D==_T('巳'))) ||
            (D == _T('子'));
    case _T('未'):
        return ((M==_T('巳')||M==_T('午')||M==_T('辰')||M==_T('未')||M==_T('戌'))&&(D==_T('巳')||D==_T('午')||D==_T('辰')||D==_T('未')||D==_T('戌'))) ||
            (D == _T('丑'));
    case _T('申'):
        return ((M==_T('丑')||M==_T('申')||M==_T('辰')||M==_T('未')||M==_T('戌')||M==_T('酉'))&&(D==_T('丑')||D==_T('午')||D==_T('申')||D==_T('未')||D==_T('戌')||D==_T('酉'))) ||
            (D == _T('寅'));
    case _T('酉'):
        return ((M==_T('丑')||M==_T('申')||M==_T('辰')||M==_T('未')||M==_T('戌')||M==_T('酉'))&&(D==_T('丑')||D==_T('午')||D==_T('申')||D==_T('未')||D==_T('戌')||D==_T('酉'))) ||
            (D == _T('卯'));
    case _T('戌'):
        return ((M==_T('巳')||M==_T('午')||M==_T('辰')||M==_T('未')||M==_T('丑'))&&(D==_T('巳')||D==_T('午')||D==_T('辰')||D==_T('未')||D==_T('丑'))) ||
            (D == _T('辰'));
    case _T('亥'):
        return ((M==_T('酉')||M==_T('申')||M==_T('亥')||M==_T('子'))&&(D==_T('酉')||D==_T('申')||D==_T('亥')||D==_T('子'))) ||
            (D == _T('巳'));
    default:
        return true;
    }
}
bool fC2(TCHAR in, TCHAR ref_b, TCHAR M, TCHAR D, TCHAR H, TCHAR *by)//assume by is 6 , fC fit condition
{
    if(in != ref_b)
        return true;
    switch(in)
    {
    case _T('子'):
        return D==_T('丑')||D==_T('子');
    case _T('丑'):
        return D==_T('丑')||D==_T('子');
    case _T('寅'):
        return D==_T('寅')||D==_T('亥');
    case _T('卯'):
        return D==_T('卯')||D==_T('戌');
    case _T('辰'):
        return D==_T('辰')||D==_T('酉');
    case _T('巳'):
        return D==_T('巳')||D==_T('申');
    case _T('午'):
        return D==_T('午')||D==_T('未');
    case _T('未'):
        return D==_T('未')||D==_T('午');
    case _T('申'):
        return D==_T('申')||D==_T('巳');
    case _T('酉'):
        return D==_T('酉')||D==_T('辰');
    case _T('戌'):
        return D==_T('戌')||D==_T('卯');
    case _T('亥'):
        return D==_T('亥')||D==_T('寅');
    default:
        return true;
    }
}
void CLottery5Dlg::OnBnClickedButtonAction()
{

    //authenticate and get input
    CComboBox edits;
    CString r[6];
    TCHAR FP[2]={_T('子'),_T('申')}, FB = _T('戌');
#if 1
    for(int i=0;i<6;i++){
        edits.Attach(GetDlgItem(IDC_YAO11+i)->m_hWnd);
        edits.GetWindowText(r[i]);
        edits.Detach();
        if(!IsInputLegit(r[i])){
            DisplayBallonTip(IDC_YAO11+i);
            return;
        }
    }
#endif
    bInitialResult = true;
    CString tt;
    edits.Attach(GetDlgItem(IDC_CASE1)->m_hWnd);edits.GetLBText(edits.GetCurSel(),tt);edits.Detach();FP[0]= tt[0];
    edits.Attach(GetDlgItem(IDC_CASE2)->m_hWnd);edits.GetLBText(edits.GetCurSel(),tt);edits.Detach();FP[1]= tt[0];
    edits.Attach(GetDlgItem(IDC_CASE3)->m_hWnd);edits.GetLBText(edits.GetCurSel(),tt);edits.Detach();FB= tt[0];
#if 0
    //hahamark
    r[0] = _T("111222");
    r[1] = _T("112221");
    r[2] = _T("012120");
    r[3] = _T("123321");
    r[4] = _T("012123");
    r[5] = _T("013320");
#endif
    {
        TCHAR cText[256];CString text;CEdit box;
        edits.Attach(GetDlgItem(IDC_WEI1+nCurrDisplayGroup-1)->m_hWnd);edits.GetLBText(edits.GetCurSel(), cText);edits.Detach();
        text += cText;text += _T("位是");
        edits.Attach(GetDlgItem(IDC_ADJECT1+nCurrDisplayGroup-1)->m_hWnd);edits.GetLBText(edits.GetCurSel(), cText);edits.Detach();
        text += cText;text += _T("的可能性：\n");
        box.Attach(GetDlgItem(IDC_EDIT11)->m_hWnd);box.SetWindowText(text);box.Detach();
    }
    //TODO: save last used results in registry
    //convert strings to numbers
    int nResults[2][4];//last one
    bool b[2] = {false,false};
    for (int i=0;i<6;i++)
    {
        if(r[nCurrDisplayGroup*2-2][i] == _T('0') || r[nCurrDisplayGroup*2-2][i] == _T('3'))
            b[0] = true;
        if(r[nCurrDisplayGroup*2-1][i] == _T('0') || r[nCurrDisplayGroup*2-1][i] == _T('3'))
            b[1] = true;
    }
    nResults[0][0] = str2gua(r[nCurrDisplayGroup*2-2], 1, 1);
    nResults[0][1] = str2gua(r[nCurrDisplayGroup*2-2], 0, 1);
    nResults[0][2] = str2gua(r[nCurrDisplayGroup*2-1], 1, 1);
    nResults[0][3] = str2gua(r[nCurrDisplayGroup*2-1], 0, 1);
    if(b[0])
    {
        nResults[1][0] = str2gua(r[nCurrDisplayGroup*2-2], 1, 0);
        nResults[1][1] = str2gua(r[nCurrDisplayGroup*2-2], 0, 0);
    }
    if(b[1])
    {
        nResults[1][2] = str2gua(r[nCurrDisplayGroup*2-1], 1, 0);
        nResults[1][3] = str2gua(r[nCurrDisplayGroup*2-1], 0, 0);
    }
    {
        //update group number;
        CEdit groupbox;
        groupbox.Attach(GetDlgItem(IDC_GROUP)->m_hWnd);
        groupbox.SetFont(&m_UNIfont[0],FALSE);
        TCHAR temp[256];
        _stprintf(temp, _T("%d"), nCurrDisplayGroup);
        groupbox.SetWindowText(temp);
        groupbox.Detach();
    }
    //fill time
    int nIndexSHICHEN = 0;
    TCHAR YMD[256]={};
    {
        CString csTime;
        SYSTEMTIME stYMD, stHM;
        CDateTimeCtrl cdtc;
        cdtc.Attach(GetDlgItem(IDC_DATETIMEPICKER4)->m_hWnd);
        cdtc.GetTime(&stYMD);	
        cdtc.Detach();
        cdtc.Attach(GetDlgItem(IDC_DATETIMEPICKER1)->m_hWnd);
        cdtc.GetTime(&stHM);	
        cdtc.Detach();
        TCHAR tcTemp[256]; 
        //公历
        _stprintf(tcTemp, _T("%.4d年%02d月%02d日 %.2d时%02d分 "), stYMD.wYear, stYMD.wMonth, stYMD.wDay, stHM.wHour, stHM.wMinute);
        //农历
        GetDayOf(&stYMD, tcTemp);
        //干支
        YMD2TD(tcTemp, stYMD.wYear, stYMD.wMonth, stYMD.wDay);
        YMD2TD(YMD, stYMD.wYear, stYMD.wMonth, stYMD.wDay);
        csTime += tcTemp;
        //时间
        nIndexSHICHEN = (stHM.wHour + 1)/ 2;
        nIndexSHICHEN = nIndexSHICHEN==12?0:nIndexSHICHEN;
        csTime += SHICHEN[nIndexSHICHEN];
        csTime += _T("时");
        //Display
        CEdit timebox;
        timebox.Attach(GetDlgItem(IDC_TIMEBOX)->m_hWnd);
        timebox.SetFont(&m_UNIfont[3], FALSE);
        timebox.SetWindowText(csTime);
        timebox.Detach();
    }
    {
        //TODO: display gua question.

    }
    {
        //display gua pics
        //original gua 
        CStatic picturecontrol;
        for(int i=0;i<4;i++){
            picturecontrol.Attach(GetDlgItem(IDC_STATIC0+i)->m_hWnd);
            picturecontrol.SetBitmap((HBITMAP)m_Gua[nResults[0][i]].GetSafeHandle());
            picturecontrol.Detach();
            picturecontrol.Attach(GetDlgItem(IDC_STATIC0+i)->m_hWnd);
            picturecontrol.SetBitmap((HBITMAP)m_Gua[nResults[0][i]].GetSafeHandle());
            picturecontrol.Detach();
        }
        //transformed gua
        //item 1
        for(int i=0;i<2;i++){
            picturecontrol.Attach(GetDlgItem(IDC_STATIC4+i)->m_hWnd);
            picturecontrol.SetBitmap(b[0]?(HBITMAP)m_Gua[nResults[1][i]].GetSafeHandle():NULL);
            picturecontrol.Detach();
        }
        //item 2
        for(int i=2;i<4;i++){
            picturecontrol.Attach(GetDlgItem(IDC_STATIC4+i)->m_hWnd);
            picturecontrol.SetBitmap(b[1]?(HBITMAP)m_Gua[nResults[1][i]].GetSafeHandle():NULL);
            picturecontrol.Detach();
        }
        //ticks
        for(int i=0;i<6;i++){
            picturecontrol.Attach(GetDlgItem(IDC_STATIC11+i)->m_hWnd);
            picturecontrol.SetWindowText(
                r[nCurrDisplayGroup*2-2][5 - i] == _T('3')?_T("o") :
                (r[nCurrDisplayGroup*2-2][5 - i] == _T('0')?_T("x") : _T(" "))
                );
            picturecontrol.Detach();    
            
            picturecontrol.Attach(GetDlgItem(IDC_STATIC17+i)->m_hWnd);
            picturecontrol.SetWindowText(
                r[nCurrDisplayGroup*2-1][5 - i] == _T('3')?_T("o") :
                (r[nCurrDisplayGroup*2-1][5 - i] == _T('0')?_T("x") : _T(" "))
                );
            picturecontrol.Detach();
        }
    }
    {
        //display gua title
        //original gua
        CString title;
        CEdit titledit;
        for(int i=0;i<4;++i)title += SIXTYFOURGUA[eightguas_64index(nResults[0][0], nResults[0][1])*4+i];
        titledit.Attach(GetDlgItem(IDC_EDIT2)->m_hWnd);titledit.SetWindowText(title);titledit.Detach();title.Empty();
        for(int i=0;i<4;++i)title += SIXTYFOURGUA[eightguas_64index(nResults[0][2], nResults[0][3])*4+i];
        titledit.Attach(GetDlgItem(IDC_EDIT14)->m_hWnd);titledit.SetWindowText(title);titledit.Detach();title.Empty();
        //transformed gua
        //item 1
        if(b[0]) 
            for(int i=0;i<4;++i)title += SIXTYFOURGUA[eightguas_64index(nResults[1][0], nResults[1][1])*4+i];
        titledit.Attach(GetDlgItem(IDC_EDIT5)->m_hWnd);titledit.SetWindowText(title);titledit.Detach();title.Empty();
        //item 2
        if(b[1])
            for(int i=0;i<4;++i)title += SIXTYFOURGUA[eightguas_64index(nResults[1][2], nResults[1][3])*4+i];
        titledit.Attach(GetDlgItem(IDC_EDIT15)->m_hWnd);titledit.SetWindowText(title);titledit.Detach();title.Empty();
    }

    //display gua content
    TCHAR*  l[2][2][6];//第几项的原卦的内容  
    {
        CString content;
        CEdit guaedit;
        //original gua, item 1
        for(int i=0;i<6;i++)
        {
            //we cannot modify the content of l
            l[0][0][i] = BXContent[BXIndex[eightguas_64index2(nResults[0][0], nResults[0][1])]*6+i];
            content += l[0][0][i];
            if(r[nCurrDisplayGroup*2-2][5 - i] == _T('3')) content += _T("\to");
            if(r[nCurrDisplayGroup*2-2][5 - i] == _T('0')) content += _T("\tx");
            content += _T("\r\n");
        }
        guaedit.Attach(GetDlgItem(IDC_EDIT7)->m_hWnd);
        guaedit.SetWindowText(content);
        guaedit.Detach();
        content.Empty();
        //original gua, item 2
        for(int i=0;i<6;i++)
        {
            l[1][0][i] = BXContent[BXIndex[eightguas_64index2(nResults[0][2], nResults[0][3])]*6+i];
            content += l[1][0][i];   
            if(r[nCurrDisplayGroup*2-1][5 - i] == _T('3')) content += _T("\to");
            if(r[nCurrDisplayGroup*2-1][5 - i] == _T('0')) content += _T("\tx");
            content += _T("\r\n");
        }
        guaedit.Attach(GetDlgItem(IDC_EDIT16)->m_hWnd);
        guaedit.SetWindowText(content);
        guaedit.Detach();
        content.Empty();
        if(b[0]){
            for(int i=0;i<6;i++)
            {
                l[0][1][i] = BXContent[BXIndex[eightguas_64index2(nResults[1][0], nResults[1][1])]*6+i];
                content += l[0][1][i];
                content += _T("\r\n");
            } 
        }
        guaedit.Attach(GetDlgItem(IDC_EDIT9)->m_hWnd);
        guaedit.SetWindowText(content);
        guaedit.Detach();
        content.Empty();

        if(b[1]){
            for(int i=0;i<6;i++)
            {
                l[1][1][i] = BXContent[BXIndex[eightguas_64index2(nResults[1][2], nResults[1][3])]*6+i];
                content += l[1][1][i];
                content += _T("\r\n");
            }
        }
        guaedit.Attach(GetDlgItem(IDC_EDIT17)->m_hWnd);
        guaedit.SetWindowText(content);
        guaedit.Detach();
        content.Empty();

    }   
    TCHAR dyo[2][6]={0}, byo[2][6]={0};
    {
        //calculate score
        TCHAR Yo=YMD[1], Mo=YMD[4], Do=YMD[7],Ho=SHICHEN[nIndexSHICHEN];
        double sA[2]={0}, sB[2]={0}, sC[2]={0}, sD[2]={0}, sE[2]={0}, sF[2]={0};
        //int na[2]={1}, nb[2]={1}, nc[2]={1}, nd[2]={1}, ne[2]={1}, nf[2]={1};
        TCHAR Ft[2][2]={0};//第一组的第一个父
        int nFI[2][2]={-1};

        TCHAR F[2]={0};
        bool Ff[2]={false};//父是否发动
        int nFCount = 0;
        int nKeyIndex = -1;
        //1
        for (int i=0;i<6;i++)
        {
            if (l[0][0][i][0]== _T('父')){
                Ft[0][nFCount] = l[0][0][i][3];
                nFI[0][nFCount] = i;
                nFCount++;
            }
            dyo[0][i] = r[nCurrDisplayGroup*2-2][i] == _T('0')||r[nCurrDisplayGroup*2-2][i] == _T('3')? l[0][0][i][3]:0;//动爻变爻问题
            byo[0][i] = r[nCurrDisplayGroup*2-2][i] == _T('0')||r[nCurrDisplayGroup*2-2][i] == _T('3')? l[0][1][i][3]:0;
            if (l[0][0][i][_tcslen(l[0][0][i])-1]==_T('世'))
                nKeyIndex = i;
        }
       // assert(nKeyIndex!=-1);
        switch(nFCount)
        {
        case 1:
            F[0] = Ft[0][0];
            Ff[0] = r[nCurrDisplayGroup*2-2][nFI[0][0]] == _T('0') || r[nCurrDisplayGroup*2-2][nFI[0][0]] == _T('3') ? true:false;
            break;
        case 2:
            F[0] = abs(nFI[0][0]-nKeyIndex) < abs(nFI[0][1]-nKeyIndex) ? Ft[0][0]:Ft[0][1];
            int nt = abs(nFI[0][0]-nKeyIndex) < abs(nFI[0][1]-nKeyIndex) ? nFI[0][0]:nFI[0][1];
            Ff[0] = r[nCurrDisplayGroup*2-2][nt] == _T('0') || r[nCurrDisplayGroup*2-2][nt] == _T('3') ? true:false;
            break;
        }
        //不处理父爻在原卦找不到的情况        
#if 0
        if (F[0]==0 && b[0])//存在变卦，父找不到
        {
            assert(nFCount==0);
            nKeyIndex=-1;
            for (int i=0;i<6;i++)
            {
                if (l[0][1][i][0]== _T('父')){
                    Ft[0][nFCount] = l[0][1][i][2];
                    nFI[0][nFCount] = i;
                    nFCount++;
                }
                if (l[0][1][i][_tcslen(l[0][1][i])-1]==_T('世'))
                    nKeyIndex = i;
            }
            assert(nKeyIndex!=-1);
            switch(nFCount)
            {
            case 1:
                F[0] = Ft[0][0];
                break;
            case 2:
                F[0] = abs(nFI[0][0]-nKeyIndex) < abs(nFI[0][1]-nKeyIndex) ? Ft[0][0]:Ft[0][1];
                break;
            }
        }
#endif
        //2
        nFCount=0;
        nKeyIndex=-1;
        for (int i=0;i<6;i++)
        {
            if (l[1][0][i][0]== _T('父')){
                Ft[1][nFCount] = l[1][0][i][3];
                nFI[1][nFCount] = i;
                nFCount++;
            }
            dyo[1][i] = r[nCurrDisplayGroup*2-1][i] == _T('0')||r[nCurrDisplayGroup*2-1][i] == _T('3')? l[1][0][i][3]:0;//动爻变爻问题
            byo[1][i] = r[nCurrDisplayGroup*2-1][i] == _T('0')||r[nCurrDisplayGroup*2-1][i] == _T('3')? l[1][1][i][3]:0;
            if (l[1][0][i][_tcslen(l[1][0][i])-1]==_T('世'))
                nKeyIndex = i;
        }
       // assert(nKeyIndex!=-1);
        switch(nFCount)
        {
        case 1:
            F[1] = Ft[1][0];
            Ff[1] = r[nCurrDisplayGroup*2-1][nFI[1][0]] == _T('0') || r[nCurrDisplayGroup*2-1][nFI[1][0]] == _T('3') ? true:false;
            break;
        case 2:
            F[1] = abs(nFI[1][0]-nKeyIndex) < abs(nFI[1][1]-nKeyIndex) ? Ft[1][0]:Ft[1][1];
            int nt = abs(nFI[1][0]-nKeyIndex) < abs(nFI[1][1]-nKeyIndex) ? nFI[1][0]:nFI[1][1];
            Ff[0] = r[nCurrDisplayGroup*2-1][nt] == _T('0') || r[nCurrDisplayGroup*2-1][nt] == _T('3') ? true:false;
            break;
        }
#if 0
        if (F[1]==0 && b[1])//存在变卦，父找不到
        {
            assert(nFCount==0);
            nKeyIndex=-1;
            for (int i=0;i<6;i++)
            {
                if (l[1][1][i][0]== _T('父')){
                    Ft[1][nFCount] = l[1][1][i][2];
                    nFI[1][nFCount] = i;
                    nFCount++;
                }
                if (l[1][1][i][_tcslen(l[1][1][i])-1]==_T('世'))
                    nKeyIndex = i;
            }
            assert(nKeyIndex!=-1);
            switch(nFCount)
            {
            case 1:
                F[1] = Ft[1][0];
                break;
            case 2:
                F[1] = abs(nFI[1][0]-nKeyIndex) < abs(nFI[1][1]-nKeyIndex) ? Ft[1][0]:Ft[1][1];
                break;
            }
        }
#endif
        // TODO: authenticate 父
        //-----------------------------------------------very very long----------------------------//
        double scoreOne = 0, scoreTwo = 0;

        {
            int ii = 0 ;
            TCHAR Y =( fC(Yo, FP[0], Mo, Do, Ho, byo[ii])&&fC(Yo, FP[1], Mo, Do, Ho, byo[ii]))||fC2(Yo, FB, Mo, Do, Ho, byo[ii]) ? Yo:NULL;
            TCHAR M =( fC(Mo, FP[0], Mo, Do, Ho, byo[ii])&&fC(Mo, FP[1], Mo, Do, Ho, byo[ii]))||fC2(Mo, FB, Mo, Do, Ho, byo[ii]) ? Mo:NULL;
            TCHAR D =( fC(Do, FP[0], Mo, Do, Ho, byo[ii])&&fC(Do, FP[1], Mo, Do, Ho, byo[ii]))||fC2(Do, FB, Mo, Do, Ho, byo[ii]) ? Do:NULL;
            TCHAR H =( fC(Ho, FP[0], Mo, Do, Ho, byo[ii])&&fC(Ho, FP[1], Mo, Do, Ho, byo[ii]))||fC2(Ho, FB, Mo, Do, Ho, byo[ii]) ? Ho:NULL;
            TCHAR by[2][6], dy[2][6];
            for (int jj=0;jj<6;jj++)
            {
                by[ii][jj] = (fC(by[ii][jj], FP[0], Mo, Do, Ho, byo[ii])&&fC(by[ii][jj], FP[1], Mo, Do, Ho, byo[ii]))||fC2(by[ii][jj], FB, Mo, Do, Ho, byo[ii]) ? byo[ii][jj]:NULL;
                dy[ii][jj] = (fC(dy[ii][jj], FP[0], Mo, Do, Ho, byo[ii])&&fC(dy[ii][jj], FP[1], Mo, Do, Ho, byo[ii]))||fC2(dy[ii][jj], FB, Mo, Do, Ho, byo[ii]) ? dyo[ii][jj]:NULL;
            }

            switch(F[0])
            {
            case(_T('申')):
                sA[0]=sA[1]= ( (Y==_T('辰')) || (Y==_T('戌')) || (Y==_T('丑')) || (Y==_T('未')) )?1:((Y==_T('酉'))?1.1:((Y==_T('申'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('辰')) || (M==_T('戌')) || (M==_T('丑')) || (M==_T('未')) )?2:((M==_T('酉'))?2.1:((M==_T('申'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('辰')) || (D==_T('戌')) || (D==_T('丑')) || (D==_T('未')) )?2:((D==_T('酉'))?2.1:((D==_T('申'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('辰')) || (H==_T('戌')) || (H==_T('丑')) || (H==_T('未')) )?2:((H==_T('酉'))?2.1:((H==_T('申'))?2.2:0));
                sE[0]= (!Ff[0])?(dyis(dy[0],_T('辰'),_T('戌'),_T('丑'),_T('未'))?1:0):(dyis(dy[0],_T('辰'),_T('戌'),_T('丑'),_T('未'),_T('酉'))?1:0);
                sF[0]= Ff[0]?(dyis(by[0],_T('辰'),_T('戌'),_T('丑'),_T('未'),_T('酉'))?1:0):0;
                break;
            case(_T('酉')):
                sA[0]=sA[1]= ( (Y==_T('辰')) || (Y==_T('戌')) || (Y==_T('丑')) || (Y==_T('未')) )?1:((Y==_T('申'))?1.1:((Y==_T('酉'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('辰')) || (M==_T('戌')) || (M==_T('丑')) || (M==_T('未')) )?2:((M==_T('申'))?2.1:((M==_T('酉'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('辰')) || (D==_T('戌')) || (D==_T('丑')) || (D==_T('未')) )?2:((D==_T('申'))?2.1:((D==_T('酉'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('辰')) || (H==_T('戌')) || (H==_T('丑')) || (H==_T('未')) )?2:((H==_T('申'))?2.1:((H==_T('酉'))?2.2:0));
                sE[0]= (!Ff[0])?(dyis(dy[0],_T('辰'),_T('戌'),_T('丑'),_T('未'))?1:0):(dyis(dy[0],_T('辰'),_T('戌'),_T('丑'),_T('未'),_T('申'))?1:0);
                sF[0]= Ff[0]?(dyis(by[0],_T('辰'),_T('戌'),_T('丑'),_T('未'),_T('酉'))?1:0):0;
                break;
            case(_T('亥')):
                sA[0]=sA[1]= ( (Y==_T('申')) || (Y==_T('酉')) )?1:((Y==_T('子'))?1.1:((Y==_T('亥'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('申')) || (M==_T('酉')) )?2:((M==_T('子'))?2.1:((M==_T('亥'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('申')) || (D==_T('酉')) )?2:((D==_T('子'))?2.1:((D==_T('亥'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('申')) || (H==_T('酉')) )?1:((H==_T('子'))?1.1:((H==_T('亥'))?1.2:0));
                sE[0]= (!Ff[0])?(dyis(dy[0],_T('申'),_T('酉'))?1:0):(dyis(dy[0],_T('申'),_T('酉'),_T('子'))?1:0);
                sF[0]= Ff[0]?(dyis(by[0],_T('申'),_T('酉'),_T('子'))?2.1:0):0;
                break;
            case(_T('子')):
                sA[0]=sA[1]= ( (Y==_T('申')) || (Y==_T('酉')) )?1:((Y==_T('亥'))?1.1:((Y==_T('子'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('申')) || (M==_T('酉')) )?2:((M==_T('亥'))?2.1:((M==_T('子'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('申')) || (D==_T('酉')) )?2:((D==_T('亥'))?2.1:((D==_T('子'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('申')) || (H==_T('酉')) )?1:((H==_T('亥'))?1.1:((H==_T('子'))?1.2:0));
                sE[0]= Ff[0]?(dyis(dy[0],_T('申'),_T('酉'),_T('亥'))?1:0):0;
                sF[0]= Ff[0]?(dyis(by[0],_T('申'),_T('酉'),_T('子'))?1:0):0;
                break;
            case(_T('寅')):
                sA[0]=sA[1]= ( (Y==_T('亥')) || (Y==_T('子')) )?1:((Y==_T('卯'))?1.1:((Y==_T('寅'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('亥')) || (M==_T('子')) )?2:((M==_T('卯'))?2.1:((M==_T('寅'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('亥')) || (D==_T('子')) )?2:((D==_T('卯'))?2.1:((D==_T('寅'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('亥')) || (H==_T('子')) )?1:((H==_T('卯'))?1.1:((H==_T('寅'))?1.2:0));
                sE[0]= Ff[0]?(dyis(dy[0],_T('卯'),_T('寅'),_T('子'),_T('亥'))?1:0):0;
                sF[0]= Ff[0]?(dyis(by[0],_T('卯'),_T('子'),_T('亥'))?1:0):0;
                break;
            case(_T('卯')):
                sA[0]=sA[1]= ( (Y==_T('亥')) || (Y==_T('子')) )?1:((Y==_T('寅'))?1.1:((Y==_T('卯'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('亥')) || (M==_T('子')) )?2:((M==_T('寅'))?2.1:((M==_T('卯'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('亥')) || (D==_T('子')) )?2:((D==_T('寅'))?2.1:((D==_T('卯'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('亥')) || (H==_T('子')) )?1:((H==_T('寅'))?1.1:((H==_T('卯'))?1.2:0));
                sE[0]= Ff[0]?(dyis(dy[0],_T('卯'),_T('寅'),_T('子'),_T('亥'))?1:0):0;
                sF[0]= Ff[0]?(dyis(by[0],_T('子'),_T('亥'))?1:0):0;
                break;
            case(_T('巳')):
                sA[0]=sA[1]= ( (Y==_T('寅')) || (Y==_T('卯')) )?1:((Y==_T('午'))?1.1:((Y==_T('巳'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('寅')) || (M==_T('卯')) )?2:((M==_T('午'))?2.1:((M==_T('巳'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('寅')) || (D==_T('卯')) )?2:((D==_T('午'))?2.1:((D==_T('巳'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('寅')) || (H==_T('卯')) )?1:((H==_T('午'))?1.1:((H==_T('巳'))?1.2:0));
                sE[0]= Ff[0]?(dyis(dy[0],_T('卯'),_T('寅'),_T('巳'),_T('午'))?1:0):0;
                sF[0]= Ff[0]?(dyis(by[0],_T('卯'),_T('寅'),_T('午'))?1:0):0;
                break;
            case(_T('午')):
                sA[0]=sA[1]= ( (Y==_T('寅')) || (Y==_T('卯')) )?1:((Y==_T('巳'))?1.1:((Y==_T('午'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('寅')) || (M==_T('卯')) )?2:((M==_T('巳'))?2.1:((M==_T('午'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('寅')) || (D==_T('卯')) )?2:((D==_T('巳'))?2.1:((D==_T('午'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('寅')) || (H==_T('卯')) )?1:((H==_T('巳'))?1.1:((H==_T('午'))?1.2:0));
                sE[0]= Ff[0]?(dyis(dy[0],_T('卯'),_T('寅'),_T('巳'),_T('午'))?1:0):0;
                sF[0]= Ff[0]?(dyis(by[0],_T('卯'),_T('寅'))?1:0):0;
                break;
            case(_T('辰')):
                sA[0]=sA[1]= ( (Y==_T('巳')) || (Y==_T('午')) )?1:((Y==_T('丑'))||((Y==_T('未')))?1.1:((Y==_T('辰'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('巳')) || (M==_T('午')) )?2:((M==_T('丑'))||((M==_T('未')))?2.1:((M==_T('辰'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('巳')) || (D==_T('午')) )?2:((D==_T('丑'))||((D==_T('未')))?2.1:((D==_T('辰'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('巳')) || (H==_T('午')) )?1:((H==_T('丑'))||((H==_T('未')))?1.1:((H==_T('辰'))?1.2:0));
                sE[0]= Ff[0]?(dyis(dy[0],_T('未'),_T('丑'),_T('巳'),_T('午'))?1:0):0;
                sF[0]= Ff[0]?(dyis(by[0],_T('未'),_T('巳'),_T('午'))?1:0):0;
                break;
            case(_T('戌')):
                sA[0]=sA[1]= ( (Y==_T('巳')) || (Y==_T('午')) )?1:((Y==_T('丑'))||((Y==_T('未')))?1.1:((Y==_T('戌'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('巳')) || (M==_T('午')) )?2:((M==_T('丑'))||((M==_T('未')))?2.1:((M==_T('戌'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('巳')) || (D==_T('午')) )?1:((D==_T('丑'))||((D==_T('未')))?2.1:((D==_T('戌'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('巳')) || (H==_T('午')) )?1:((H==_T('丑'))||((H==_T('未')))?1.1:((H==_T('戌'))?1.2:0));
                sE[0]= Ff[0]?(dyis(dy[0],_T('未'),_T('丑'),_T('巳'),_T('午'))?1:0):0;
                sF[0]= Ff[0]?(dyis(by[0],_T('丑'),_T('巳'),_T('午'))?1:0):0;
                break;
            case(_T('丑')):
                sA[0]=sA[1]= ( (Y==_T('巳')) || (Y==_T('午')) )?1:((Y==_T('辰'))||((Y==_T('戌')))?1.1:((Y==_T('丑'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('巳')) || (M==_T('午')) )?2:((M==_T('辰'))||((M==_T('戌')))?2.1:((M==_T('丑'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('巳')) || (D==_T('午')) )?2:((D==_T('辰'))||((D==_T('戌')))?2.1:((D==_T('丑'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('巳')) || (H==_T('午')) )?1:((H==_T('辰'))||((H==_T('戌')))?1.1:((H==_T('丑'))?1.2:0));
                sE[0]= Ff[0]?(dyis(dy[0],_T('戌'),_T('丑'),_T('巳'),_T('午'))?1:0):0;
                sF[0]= Ff[0]?(dyis(by[0],_T('巳'),_T('午'))?1:0):0;
                break;
            case(_T('未')):
                sA[0]=sA[1]= ( (Y==_T('巳')) || (Y==_T('午')) )?1:((Y==_T('辰'))||((Y==_T('戌')))?1.1:((Y==_T('丑'))?1.2:0));
                sB[0]=sB[1]= ( (M==_T('巳')) || (M==_T('午')) )?2:((M==_T('辰'))||((M==_T('戌')))?2.1:((M==_T('丑'))?2.2:0));
                sC[0]=sC[1]= ( (D==_T('巳')) || (D==_T('午')) )?2:((D==_T('辰'))||((D==_T('戌')))?2.1:((D==_T('丑'))?2.2:0));
                sD[0]=sD[1]= ( (H==_T('巳')) || (H==_T('午')) )?1:((H==_T('辰'))||((H==_T('戌')))?1.1:((H==_T('丑'))?1.2:0));
                sE[0]= Ff[0]?(dyis(dy[0],_T('戌'),_T('辰'),_T('巳'),_T('午'))?1:0):0;
                sF[0]= Ff[0]?(dyis(by[0],_T('巳'),_T('午'))?1:0):0;
                break;
            }
            ii = 1;
            Y = (fC(Yo, FP[0], Mo, Do, Ho, byo[ii])&&fC(Yo, FP[1], Mo, Do, Ho, byo[ii]))||fC2(Yo, FB, Mo, Do, Ho, byo[ii]) ? Yo:NULL;
            M = (fC(Mo, FP[0], Mo, Do, Ho, byo[ii])&&fC(Mo, FP[1], Mo, Do, Ho, byo[ii]))||fC2(Mo, FB, Mo, Do, Ho, byo[ii]) ? Mo:NULL;
            D = (fC(Do, FP[0], Mo, Do, Ho, byo[ii])&&fC(Do, FP[1], Mo, Do, Ho, byo[ii]))||fC2(Do, FB, Mo, Do, Ho, byo[ii]) ? Do:NULL;
            H = (fC(Ho, FP[0], Mo, Do, Ho, byo[ii])&&fC(Ho, FP[1], Mo, Do, Ho, byo[ii]))||fC2(Ho, FB, Mo, Do, Ho, byo[ii]) ? Ho:NULL;
            for (int jj=0;jj<6;jj++)
            {
                by[ii][jj] = (fC(by[ii][jj], FP[0], Mo, Do, Ho, byo[ii])&&fC(by[ii][jj], FP[1], Mo, Do, Ho, byo[ii]))||fC2(by[ii][jj], FB, Mo, Do, Ho, byo[ii]) ? byo[ii][jj]:NULL;
                dy[ii][jj] = (fC(dy[ii][jj], FP[0], Mo, Do, Ho, byo[ii])&&fC(dy[ii][jj], FP[1], Mo, Do, Ho, byo[ii]))||fC2(dy[ii][jj], FB, Mo, Do, Ho, byo[ii]) ? dyo[ii][jj]:NULL;
            }
            switch(F[1])
            {
            case(_T('申')):
                sA[1]= ( (Y==_T('辰')) || (Y==_T('戌')) || (Y==_T('丑')) || (Y==_T('未')) )?1:((Y==_T('酉'))?1.1:((Y==_T('申'))?1.2:0));
                sB[1]= ( (M==_T('辰')) || (M==_T('戌')) || (M==_T('丑')) || (M==_T('未')) )?2:((M==_T('酉'))?2.1:((M==_T('申'))?2.2:0));
                sC[1]= ( (D==_T('辰')) || (D==_T('戌')) || (D==_T('丑')) || (D==_T('未')) )?2:((D==_T('酉'))?2.1:((D==_T('申'))?2.2:0));
                sD[1]= ( (H==_T('辰')) || (H==_T('戌')) || (H==_T('丑')) || (H==_T('未')) )?2:((H==_T('酉'))?2.1:((H==_T('申'))?2.2:0));
                break;
            case(_T('酉')):
                sA[1]= ( (Y==_T('辰')) || (Y==_T('戌')) || (Y==_T('丑')) || (Y==_T('未')) )?1:((Y==_T('申'))?1.1:((Y==_T('酉'))?1.2:0));
                sB[1]= ( (M==_T('辰')) || (M==_T('戌')) || (M==_T('丑')) || (M==_T('未')) )?2:((M==_T('申'))?2.1:((M==_T('酉'))?2.2:0));
                sC[1]= ( (D==_T('辰')) || (D==_T('戌')) || (D==_T('丑')) || (D==_T('未')) )?2:((D==_T('申'))?2.1:((D==_T('酉'))?2.2:0));
                sD[1]= ( (H==_T('辰')) || (H==_T('戌')) || (H==_T('丑')) || (H==_T('未')) )?2:((H==_T('申'))?2.1:((H==_T('酉'))?2.2:0));
                break;
            case(_T('亥')):
                sA[1]= ( (Y==_T('申')) || (Y==_T('酉')) )?1:((Y==_T('子'))?1.1:((Y==_T('亥'))?1.2:0));
                sB[1]= ( (M==_T('申')) || (M==_T('酉')) )?2:((M==_T('子'))?2.1:((M==_T('亥'))?2.2:0));
                sC[1]= ( (D==_T('申')) || (D==_T('酉')) )?2:((D==_T('子'))?2.1:((D==_T('亥'))?2.2:0));
                sD[1]= ( (H==_T('申')) || (H==_T('酉')) )?1:((H==_T('子'))?1.1:((H==_T('亥'))?1.2:0));
                break;
            case(_T('子')):
                sA[1]= ( (Y==_T('申')) || (Y==_T('酉')) )?1:((Y==_T('亥'))?1.1:((Y==_T('子'))?1.2:0));
                sB[1]= ( (M==_T('申')) || (M==_T('酉')) )?2:((M==_T('亥'))?2.1:((M==_T('子'))?2.2:0));
                sC[1]= ( (D==_T('申')) || (D==_T('酉')) )?2:((D==_T('亥'))?2.1:((D==_T('子'))?2.2:0));
                sD[1]= ( (H==_T('申')) || (H==_T('酉')) )?1:((H==_T('亥'))?1.1:((H==_T('子'))?1.2:0));
                break;
            case(_T('寅')):
                sA[1]= ( (Y==_T('亥')) || (Y==_T('子')) )?1:((Y==_T('卯'))?1.1:((Y==_T('寅'))?1.2:0));
                sB[1]= ( (M==_T('亥')) || (M==_T('子')) )?2:((M==_T('卯'))?2.1:((M==_T('寅'))?2.2:0));
                sC[1]= ( (D==_T('亥')) || (D==_T('子')) )?2:((D==_T('卯'))?2.1:((D==_T('寅'))?2.2:0));
                sD[1]= ( (H==_T('亥')) || (H==_T('子')) )?1:((H==_T('卯'))?1.1:((H==_T('寅'))?1.2:0));
                break;
            case(_T('卯')):
                sA[1]= ( (Y==_T('亥')) || (Y==_T('子')) )?1:((Y==_T('寅'))?1.1:((Y==_T('卯'))?1.2:0));
                sB[1]= ( (M==_T('亥')) || (M==_T('子')) )?2:((M==_T('寅'))?2.1:((M==_T('卯'))?2.2:0));
                sC[1]= ( (D==_T('亥')) || (D==_T('子')) )?2:((D==_T('寅'))?2.1:((D==_T('卯'))?2.2:0));
                sD[1]= ( (H==_T('亥')) || (H==_T('子')) )?1:((H==_T('寅'))?1.1:((H==_T('卯'))?1.2:0));
                break;
            case(_T('巳')):
                sA[1]= ( (Y==_T('寅')) || (Y==_T('卯')) )?1:((Y==_T('午'))?1.1:((Y==_T('巳'))?1.2:0));
                sB[1]= ( (M==_T('寅')) || (M==_T('卯')) )?2:((M==_T('午'))?2.1:((M==_T('巳'))?2.2:0));
                sC[1]= ( (D==_T('寅')) || (D==_T('卯')) )?2:((D==_T('午'))?2.1:((D==_T('巳'))?2.2:0));
                sD[1]= ( (H==_T('寅')) || (H==_T('卯')) )?1:((H==_T('午'))?1.1:((H==_T('巳'))?1.2:0));
                break;
            case(_T('午')):
                sA[1]= ( (Y==_T('寅')) || (Y==_T('卯')) )?1:((Y==_T('巳'))?1.1:((Y==_T('午'))?1.2:0));
                sB[1]= ( (M==_T('寅')) || (M==_T('卯')) )?2:((M==_T('巳'))?2.1:((M==_T('午'))?2.2:0));
                sC[1]= ( (D==_T('寅')) || (D==_T('卯')) )?2:((D==_T('巳'))?2.1:((D==_T('午'))?2.2:0));
                sD[1]= ( (H==_T('寅')) || (H==_T('卯')) )?1:((H==_T('巳'))?1.1:((H==_T('午'))?1.2:0));
                break;
            case(_T('辰')):
                sA[1]= ( (Y==_T('巳')) || (Y==_T('午')) )?1:((Y==_T('丑'))||((Y==_T('未')))?1.1:((Y==_T('辰'))?1.2:0));
                sB[1]= ( (M==_T('巳')) || (M==_T('午')) )?2:((M==_T('丑'))||((M==_T('未')))?2.1:((M==_T('辰'))?2.2:0));
                sC[1]= ( (D==_T('巳')) || (D==_T('午')) )?2:((D==_T('丑'))||((D==_T('未')))?2.1:((D==_T('辰'))?2.2:0));
                sD[1]= ( (H==_T('巳')) || (H==_T('午')) )?1:((H==_T('丑'))||((H==_T('未')))?1.1:((H==_T('辰'))?1.2:0));
                break;
            case(_T('戌')):
                sA[1]= ( (Y==_T('巳')) || (Y==_T('午')) )?1:((Y==_T('丑'))||((Y==_T('未')))?1.1:((Y==_T('戌'))?1.2:0));
                sB[1]= ( (M==_T('巳')) || (M==_T('午')) )?2:((M==_T('丑'))||((M==_T('未')))?2.1:((M==_T('戌'))?2.2:0));
                sC[1]= ( (D==_T('巳')) || (D==_T('午')) )?1:((D==_T('丑'))||((D==_T('未')))?2.1:((D==_T('戌'))?2.2:0));
                sD[1]= ( (H==_T('巳')) || (H==_T('午')) )?1:((H==_T('丑'))||((H==_T('未')))?1.1:((H==_T('戌'))?1.2:0));
                break;
            case(_T('丑')):
                sA[1]= ( (Y==_T('巳')) || (Y==_T('午')) )?1:((Y==_T('辰'))||((Y==_T('戌')))?1.1:((Y==_T('丑'))?1.2:0));
                sB[1]= ( (M==_T('巳')) || (M==_T('午')) )?2:((M==_T('辰'))||((M==_T('戌')))?2.1:((M==_T('丑'))?2.2:0));
                sC[1]= ( (D==_T('巳')) || (D==_T('午')) )?2:((D==_T('辰'))||((D==_T('戌')))?2.1:((D==_T('丑'))?2.2:0));
                sD[1]= ( (H==_T('巳')) || (H==_T('午')) )?1:((H==_T('辰'))||((H==_T('戌')))?1.1:((H==_T('丑'))?1.2:0));
                break;
            case(_T('未')):
                sA[1]= ( (Y==_T('巳')) || (Y==_T('午')) )?1:((Y==_T('辰'))||((Y==_T('戌')))?1.1:((Y==_T('丑'))?1.2:0));
                sB[1]= ( (M==_T('巳')) || (M==_T('午')) )?2:((M==_T('辰'))||((M==_T('戌')))?2.1:((M==_T('丑'))?2.2:0));
                sC[1]= ( (D==_T('巳')) || (D==_T('午')) )?2:((D==_T('辰'))||((D==_T('戌')))?2.1:((D==_T('丑'))?2.2:0));
                sD[1]= ( (H==_T('巳')) || (H==_T('午')) )?1:((H==_T('辰'))||((H==_T('戌')))?1.1:((H==_T('丑'))?1.2:0));
                break;
            }
            switch(F[1])
            {
            case(_T('申')):
                sE[1]= (!Ff[1])?(dyis(dy[1],_T('辰'),_T('戌'),_T('丑'),_T('未'))?1:0):(dyis(dy[1],_T('辰'),_T('戌'),_T('丑'),_T('未'),_T('酉'))?1:0);
                sF[1]= Ff[1]?(dyis(by[1],_T('辰'),_T('戌'),_T('丑'),_T('未'),_T('酉'))?1:0):0;
                break;
            case(_T('酉')):
                sE[1]= (!Ff[1])?(dyis(dy[1],_T('辰'),_T('戌'),_T('丑'),_T('未'))?1:0):(dyis(dy[1],_T('辰'),_T('戌'),_T('丑'),_T('未'),_T('申'))?1:0);
                sF[1]= Ff[1]?(dyis(by[1],_T('辰'),_T('戌'),_T('丑'),_T('未'),_T('酉'))?1:0):0;
                break;
            case(_T('亥')):
                sE[1]= (!Ff[1])?(dyis(dy[1],_T('申'),_T('酉'))?1:0):(dyis(dy[1],_T('申'),_T('酉'),_T('子'))?1:0);
                sF[1]= Ff[1]?(dyis(by[1],_T('申'),_T('酉'),_T('子'))?2.1:0):0;
                break;
            case(_T('子')):
                sE[1]= Ff[1]?(dyis(dy[1],_T('申'),_T('酉'),_T('亥'))?1:0):0;
                sF[1]= Ff[1]?(dyis(by[1],_T('申'),_T('酉'),_T('子'))?1:0):0;
                break;
            case(_T('寅')):
                sE[1]= Ff[1]?(dyis(dy[1],_T('卯'),_T('寅'),_T('子'),_T('亥'))?1:0):0;
                sF[1]= Ff[1]?(dyis(by[1],_T('卯'),_T('子'),_T('亥'))?1:0):0;
                break;
            case(_T('卯')):
                sE[1]= Ff[1]?(dyis(dy[1],_T('卯'),_T('寅'),_T('子'),_T('亥'))?1:0):0;
                sF[1]= Ff[1]?(dyis(by[1],_T('子'),_T('亥'))?1:0):0;
                break;
            case(_T('巳')):
                sE[1]= Ff[1]?(dyis(dy[1],_T('卯'),_T('寅'),_T('巳'),_T('午'))?1:0):0;
                sF[1]= Ff[1]?(dyis(by[1],_T('卯'),_T('寅'),_T('午'))?1:0):0;
                break;
            case(_T('午')):
                sE[1]= Ff[1]?(dyis(dy[1],_T('卯'),_T('寅'),_T('巳'),_T('午'))?1:0):0;
                sF[1]= Ff[1]?(dyis(by[1],_T('卯'),_T('寅'))?1:0):0;
                break;
            case(_T('辰')):
                sE[1]= Ff[1]?(dyis(dy[1],_T('未'),_T('丑'),_T('巳'),_T('午'))?1:0):0;
                sF[1]= Ff[1]?(dyis(by[1],_T('未'),_T('巳'),_T('午'))?1:0):0;
                break;
            case(_T('戌')):
                sE[1]= Ff[1]?(dyis(dy[1],_T('未'),_T('丑'),_T('巳'),_T('午'))?1:0):0;
                sF[1]= Ff[1]?(dyis(by[1],_T('丑'),_T('巳'),_T('午'))?1:0):0;
                break;
            case(_T('丑')):
                sE[1]= Ff[1]?(dyis(dy[1],_T('戌'),_T('丑'),_T('巳'),_T('午'))?1:0):0;
                sF[1]= Ff[1]?(dyis(by[1],_T('巳'),_T('午'))?1:0):0;
                break;
            case(_T('未')):
                sE[1]= Ff[1]?(dyis(dy[1],_T('戌'),_T('辰'),_T('巳'),_T('午'))?1:0):0;
                sF[1]= Ff[1]?(dyis(by[1],_T('巳'),_T('午'))?1:0):0;
                break;
            }
            scoreOne = sA[0] + sB[0] + sC[0] + sD[0];
            scoreTwo = sA[1] + sB[1] + sC[1] + sD[1];
            TCHAR boxtext[256];
            if(F[0])_stprintf(boxtext, _T("%.1f\r\n分"), scoreOne);else _stprintf(boxtext, _T("?\r\n分"));
            CEdit scorebox;
            scorebox.Attach(GetDlgItem(IDC_SCORE1)->m_hWnd);scorebox.SetWindowText(boxtext);scorebox.Detach();
            if(F[1])_stprintf(boxtext, _T("%.1f\r\n分"), scoreTwo);else _stprintf(boxtext, _T("?\r\n分"));
            scorebox.Attach(GetDlgItem(IDC_SCORE2)->m_hWnd);scorebox.SetWindowText(boxtext);scorebox.Detach();

            CEdit resultbox;
            resultbox.Attach(GetDlgItem(IDC_RESULT1)->m_hWnd);resultbox.SetWindowText(F[0]?(scoreOne>scoreTwo?_T("√"):_T("x")):_T("?"));resultbox.Detach();
            resultbox.Attach(GetDlgItem(IDC_RESULT2)->m_hWnd);resultbox.SetWindowText(F[1]?(scoreOne<scoreTwo?_T("√"):_T("x")):_T("?"));resultbox.Detach();
        }
    }


    //
}

void CLottery5Dlg::Parse64Gua( CString& csGua, int & iIndex4 )
{
    int nIndex1 = 
        (csGua[0] - _T('1'))*4 +
        (csGua[1] - _T('1'))*2 +
        (csGua[2] - _T('1'))*1;
    int nIndex0 =  
        (csGua[3] - _T('1'))*4 +
        (csGua[4] - _T('1'))*2 +
        (csGua[5] - _T('1'))*1;
    nIndex0 = 7 - nIndex0; //上卦是反的
    iIndex4 = nIndex1*8 + nIndex0;
}

void CLottery5Dlg::Parse64Gua2( CString& csGua, int & iIndex4 )
{
    int nIndex1 = 
        (csGua[0] - _T('1'))*4 +
        (csGua[1] - _T('1'))*2 +
        (csGua[2] - _T('1'))*1;
    int nIndex0 =  
        (csGua[3] - _T('1'))*4 +
        (csGua[4] - _T('1'))*2 +
        (csGua[5] - _T('1'))*1;
    iIndex4 = nIndex1*8 + nIndex0;
}

bool CLottery5Dlg::TackleShiftGua(CString& csGua, CString& csGua1, CString& csGua2)
{
    bool bShift = false;
    for (int i=0;i<6;++i)
    {
        switch (csGua[i])
        {
        case _T('0'):
            csGua1 += _T('2');
            csGua2 += _T('1');
            bShift = true;
            break;
        case _T('3'):
            csGua1 += _T('1');
            csGua2 += _T('2');
            bShift = true;
            break;
        case _T('1'):
        case _T('2'):
            csGua1 += csGua[i];
            csGua2 += csGua[i];
            break;
        }
    }
    return bShift;
}

bool CLottery5Dlg::IsInputLegit(CString& csInput)
{
    if (csInput.GetLength()!=6)
        return false;
    for(int i=0;i<6;++i)
    {
        if ( (csInput[i]>_T('3')) || (csInput[i]<_T('0')))
            return false;
    }
    return true;
}

void CLottery5Dlg::Parse8Gua( CString& csGua, int & nIndex0, int & nIndex1 )
{
    nIndex1 = 
        (csGua[0] - _T('1'))*4 +
        (csGua[1] - _T('1'))*2 +
        (csGua[2] - _T('1'))*1;
    nIndex0 =  
        (csGua[3] - _T('1'))*4 +
        (csGua[4] - _T('1'))*2 +
        (csGua[5] - _T('1'))*1;
}

void CLottery5Dlg::AppendGuaContent( CString &csDisplay, CString csForcast )
{
    //解析
    CString csGua1, csGua2;
    if (TackleShiftGua(csForcast, csGua1, csGua2))
    {//写出原卦和变卦
        int iIndex00, iIndex01, iIndex04, iIndex10, iIndex11, iIndex14, iIndex042, iIndex142;
        Parse8Gua(csGua1, iIndex00, iIndex01);
        Parse64Gua(csGua1, iIndex04); 
        Parse64Gua2(csGua1, iIndex042);
        Parse8Gua(csGua2, iIndex10, iIndex11);
        Parse64Gua(csGua2, iIndex14);
        Parse64Gua2(csGua2, iIndex142);
        //第一行
        csDisplay += _T("\t\t\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+0];
        csDisplay += _T("\t\t");
        csDisplay += BXContent[(BXIndex[iIndex142])*6+0];
        //第二行
        csDisplay += _T("\n");
        for(int i=0;i<4;++i)
            csDisplay += SIXTYFOURGUA[iIndex04*4+i];
        csDisplay += _T("\t\t\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+1];
        csDisplay += _T("\t\t");
        csDisplay += BXContent[(BXIndex[iIndex142])*6+1];
        //第三行
        csDisplay += _T("\n");
        csDisplay += EIGHTGUA[iIndex00];
        AddMarker(csDisplay, csForcast[5], csForcast[4], csForcast[3]);
        csDisplay += _T("\t");
        csDisplay += EIGHTGUA[iIndex10];
        csDisplay += _T("\t\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+2];
        csDisplay += _T("\t\t");
        csDisplay += BXContent[(BXIndex[iIndex142])*6+2];
        //第四行
        csDisplay += _T("\n");
        csDisplay += EIGHTGUA[iIndex01];
        AddMarker(csDisplay, csForcast[2], csForcast[1], csForcast[0]);
        csDisplay += _T("\t");
        csDisplay += EIGHTGUA[iIndex11];
        csDisplay += _T("\t\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+3];
        csDisplay += _T("\t\t");
        csDisplay += BXContent[(BXIndex[iIndex142])*6+3];
        //第五行
        csDisplay += _T("\n");  
        csDisplay += _T("\t");
        for(int i=0;i<4;++i)
            csDisplay += SIXTYFOURGUA[iIndex14*4+i];
        csDisplay += _T("\t\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+4];
        csDisplay += _T("\t\t");
        csDisplay += BXContent[(BXIndex[iIndex142])*6+4];
        //第六行
        csDisplay += _T("\n\t\t\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+5];
        csDisplay += _T("\t\t");
        csDisplay += BXContent[(BXIndex[iIndex142])*6+5];
    }
    else
    {//无变卦
        int iIndex00, iIndex01, iIndex04, iIndex042;
        Parse8Gua(csForcast, iIndex00, iIndex01);
        Parse64Gua(csForcast, iIndex04);
        Parse64Gua2(csForcast, iIndex042);
        //第一行
        csDisplay += _T("\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+0];
        //第二行
        csDisplay += _T("\n");
        for(int i=0;i<4;++i)
            csDisplay += SIXTYFOURGUA[iIndex04*4+i];
        csDisplay += _T("\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+1];
        //第三行
        csDisplay += _T("\n");
        csDisplay += EIGHTGUA[iIndex00];
        csDisplay += _T("\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+2];
        //第四行
        csDisplay += _T("\n");
        csDisplay += EIGHTGUA[iIndex01];
        csDisplay += _T("\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+3];
        //第五行
        csDisplay += _T("\n");  
        csDisplay += _T("\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+4];
        //第六行
        csDisplay += _T("\n");  
        csDisplay += _T("\t");
        csDisplay += BXContent[(BXIndex[iIndex042])*6+5];
    }
    csDisplay += _T("\n\n");  
}

void CLottery5Dlg::OnBnClickedButton2()
{
    // TODO: Add your control notification handler code here
    OnBnClickedButtonAction();

    CFileDialog filedg(FALSE,_T("rtf"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXTENSIONDIFFERENT);
    filedg.m_ofn.lpstrFilter = _T("*.rtf");
    if(IDOK == filedg.DoModal())
    {
        CRichEditCtrl* pEditRes;
        pEditRes = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21);

        CFile cFile(filedg.GetPathName(), CFile::modeCreate|CFile::modeWrite);
        EDITSTREAM es;
        es.dwCookie = (DWORD) &cFile;
        es.pfnCallback = MyStreamOutCallback; 
        pEditRes->StreamOut(SF_RTF, es);
        cFile.Close();
    }
}

void CLottery5Dlg::AddMarker(CString& csInput, wchar_t wch0, wchar_t wch1, wchar_t wch2)
{
    CString csTemp;
    int iCum = 0;
    CHARRANGE cr;
    if (wch0 == L'0')
    {  
        cr.cpMin = csInput.GetLength(), cr.cpMax = cr.cpMin + 1;
        vCRUpper.Add(cr);
        csInput += L'x';
    }
    if (wch0 == L'3')
    {  
        cr.cpMin = csInput.GetLength(), cr.cpMax = cr.cpMin + 1;
        vCRUpper.Add(cr);
        csInput += L'o';
    }
    if (wch1 == L'0')
        csInput += L'x';
    if (wch1 == L'3')
        csInput += L'o';
    if (wch2 == L'0')
    {  
        cr.cpMin = csInput.GetLength(), cr.cpMax = cr.cpMin + 1;
        vCRDowner.Add(cr);
        csInput += L'x';
    }
    if (wch2 == L'3')
    {  
        cr.cpMin = csInput.GetLength(), cr.cpMax = cr.cpMin + 1;
        vCRDowner.Add(cr);
        csInput += L'o';
    }
}

void CLottery5Dlg::OnDestroy()
{


    for(int i=0;i<3;i++)
        m_UNIfont[i].DeleteObject();
	if(m_pDownloadedBuffer != NULL) {
		free(m_pDownloadedBuffer);
		m_pDownloadedBuffer = NULL;
	}

    CDialog::OnDestroy();

    // TODO: Add your message handler code here
}

void CLottery5Dlg::OnBnClickedGroupadd()
{
    // TODO: Add your control notification handler code here
    if(nCurrDisplayGroup<3)
        nCurrDisplayGroup++;
    OnBnClickedButtonAction();
}

void CLottery5Dlg::OnBnClickedGroupsubstract()
{
    // TODO: Add your control notification handler code here
    if(nCurrDisplayGroup>1)
        nCurrDisplayGroup--;
    OnBnClickedButtonAction();
}


void CLottery5Dlg::DisplayBallonTip(int nID)
{
    //预测输入错误
    CEdit ceForecast;
    ceForecast.Attach(GetDlgItem(nID)->m_hWnd);
    ceForecast.ShowBalloonTip(_T("数据有误！"),_T("在这里输入完整的上下卦信息。用1代表一，2代表--，0代表x变卦，3代表o变卦。从下往上输入！"),TTI_ERROR);
    ceForecast.Detach();
}

void CLottery5Dlg::OnBnClickedButtonclear()
{
    // TODO: Add your control notification handler code here
    CStatic curr;
    for(int ii=0;ii<8;ii++){
        curr.Attach(GetDlgItem(IDC_STATIC0+ii)->m_hWnd);
        curr.SetBitmap(NULL);
        curr.Detach();
    }
    for(int ii=0;ii<12;ii++){
        curr.Attach(GetDlgItem(IDC_STATIC11+ii)->m_hWnd);
        curr.SetWindowText(NULL);
        curr.Detach();
    }

    for(int ii=0;ii<6;ii++){
		curr.Attach(GetDlgItem(IDC_YAO11+ii)->m_hWnd);
		curr.SetWindowText(NULL);
		curr.Detach();
	}
	curr.Attach(GetDlgItem(IDC_TIMEBOX)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_GROUP)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_EDIT2)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_EDIT5)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_EDIT14)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_EDIT15)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_EDIT11)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_EDIT7)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_EDIT9)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_EDIT16)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_EDIT17)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_SCORE1)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_SCORE2)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_RESULT1)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();
	curr.Attach(GetDlgItem(IDC_RESULT2)->m_hWnd);curr.SetWindowText(NULL);curr.Detach();

	curr.Attach(GetDlgItem(IDC_YAO11)->m_hWnd);curr.SetFocus();curr.Detach();
}

void CLottery5Dlg::OnBnClickedButtonrandom()
{
	// TODO: Add your control notification handler code here
	srand(time(0));
	TCHAR texts[256] = {0};
	CComboBox edits;
	for(int i=0;i<6;i++){
		edits.Attach(GetDlgItem(IDC_YAO11+i)->m_hWnd);
		_stprintf(texts, _T("%d%d%d%d%d%d"), rand()%3, rand()%3, rand()%3, rand()%3, rand()%3, rand()%3); 
		edits.SetWindowText(texts);
		edits.Detach();
	}
}

void CLottery5Dlg::OnBnClickedButtongetonline()
{
	// TODO: Add your control notification handler code here
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
			MessageBox(_T("数据查询有误!"));
			return;
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
	for(;nLoopCount<theRecords.size();nLoopCount++) {
		CString t("0");
		if(theRecords[nLoopCount].get("analyseState", 1).asCString() == t) {
			// found a match
			theTarget = theRecords[nLoopCount];
			break;
		}
	}
	if(nLoopCount == theRecords.size()) {
		// target not found
		MessageBox(_T("所有记录都已处理完毕"));
		return;
	}
	// the target is found, continue to process it;
	TCHAR zs[256]; // set window text can be happy
	CComboBox edits;

	// update the input content
	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataOne1", "000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_YAO11+0)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();

	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataOne2", "000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_YAO11+1)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();

	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataTwo1", "000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_YAO11+2)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();	

	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataTwo2", "000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_YAO11+3)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();

	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("actionNumber1", "0000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_EDITISSUE1)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();

	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("actionNumber2", "0000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_EDITISSUE2)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();

	// fill last group with 000000
	for(int i=4;i<6;i++){
		edits.Attach(GetDlgItem(IDC_YAO11+i)->m_hWnd);
		edits.SetWindowText(_T("000000"));
		edits.Detach();
	}

	// info
	MultiByteToWideChar(CP_UTF8, NULL, theTarget.get("userName", "NA").asCString(), -1, zs, 256);
	CString text2show;
	text2show += zs;
	_stprintf(zs, _T(" id号%d"), theTarget.get("ticketUseId", "0").asInt());
	text2show += zs;
	edits.Attach(GetDlgItem(IDC_EDITINFO)->m_hWnd);
	edits.SetWindowText(text2show);
	edits.Detach();

	// time 
	CTime theTime(theTarget.get("addTime", "0").asUInt64() / 1000);
	CDateTimeCtrl cdtc;
	cdtc.Attach(GetDlgItem(IDC_DATETIMEPICKER4)->m_hWnd);
	cdtc.SetTime(&theTime);	
	cdtc.Detach();
	cdtc.Attach(GetDlgItem(IDC_DATETIMEPICKER1)->m_hWnd);
	cdtc.SetTime(&theTime);	
	cdtc.Detach();
	//grey out the third record
} 

void CLottery5Dlg::OnBnClickedButtonmark()
{
	// TODO: Add your control notification handler code here
	if(g_SourceMode != ONLINE_DOWNLOAD) {
		// local version
		// TODO warn user not to click it
		return ;
	} else {
		int targetid = theTarget.get("ticketUseId", "0").asInt();
		TCHAR theURL[256];
		_stprintf(theURL, _T("http://115.28.141.187/TicketManager/recordAction!submitTicketAnalyseState.action?ticketUseId=%d&analyseState=1"), targetid);
		CInternetSession theSession;
		CHttpFile* theContent = (CHttpFile*)theSession.OpenURL(theURL);
		CString str;
		theContent->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, str);
		size_t theContentLength = _ttoi(LPCTSTR(str));
		if(theContentLength > 5000000) {
			// 5MB, too big? TODO: do something
			//assert(0);
		} else if (theContentLength < 5) { // too little, one record is 252
			MessageBox(_T("数据通信有误!"));
			return;
		}
		char* pBuffer = (char*)malloc(theContentLength);
		theContent->Read(pBuffer, theContentLength);

		Json::Reader theReader;
		Json::Value theRoot;
		if(theReader.parse(pBuffer, theRoot)) {
			int returncode = theRoot.get("code", 0).asInt();
			if(returncode == 1) {
				MessageBox(_T("成功"));
				theRecords[nLoopCount]["analyseState"] = 1;
			} else {
				MessageBox(_T("失败"));
			}
		} else {
			MessageBox(_T("失败"));
		}
		free(pBuffer);
	}
}
void CLottery5Dlg::OnBnClickedButtonbirdview()
{
	// TODO: Add your control notification handler code here
	BirdView theBirdView;
	if(IDOK == theBirdView.DoModal()) {
		// the target is found, continue to process it;
		TCHAR zs[256]; // set window text can be happy
		CComboBox edits;

		// update the input content
		MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataOne1", "000000").asCString(), -1, zs, 256);
		edits.Attach(GetDlgItem(IDC_YAO11+0)->m_hWnd);
		edits.SetWindowText(zs);
		edits.Detach();

		MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataOne2", "000000").asCString(), -1, zs, 256);
		edits.Attach(GetDlgItem(IDC_YAO11+1)->m_hWnd);
		edits.SetWindowText(zs);
		edits.Detach();

		MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataTwo1", "000000").asCString(), -1, zs, 256);
		edits.Attach(GetDlgItem(IDC_YAO11+2)->m_hWnd);
		edits.SetWindowText(zs);
		edits.Detach();	

		MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataTwo2", "000000").asCString(), -1, zs, 256);
		edits.Attach(GetDlgItem(IDC_YAO11+3)->m_hWnd);
		edits.SetWindowText(zs);
		edits.Detach();

		MultiByteToWideChar(CP_ACP, NULL, theTarget.get("actionNumber1", "0000000").asCString(), -1, zs, 256);
		edits.Attach(GetDlgItem(IDC_EDITISSUE1)->m_hWnd);
		edits.SetWindowText(zs);
		edits.Detach();

		MultiByteToWideChar(CP_ACP, NULL, theTarget.get("actionNumber2", "0000000").asCString(), -1, zs, 256);
		edits.Attach(GetDlgItem(IDC_EDITISSUE2)->m_hWnd);
		edits.SetWindowText(zs);
		edits.Detach();

		// fill last group with 000000
		for(int i=4;i<6;i++){
			edits.Attach(GetDlgItem(IDC_YAO11+i)->m_hWnd);
			edits.SetWindowText(_T("000000"));
			edits.Detach();
		}

		// info
		MultiByteToWideChar(CP_UTF8, NULL, theTarget.get("userName", "NA").asCString(), -1, zs, 256);
		CString text2show;
		text2show += zs;
		_stprintf(zs, _T(" id号%d"), theTarget.get("ticketUseId", "0").asInt());
		text2show += zs;
		edits.Attach(GetDlgItem(IDC_EDITINFO)->m_hWnd);
		edits.SetWindowText(text2show);
		edits.Detach();

		// time 
		CTime theTime(theTarget.get("addTime", "0").asUInt64() / 1000);
		CDateTimeCtrl cdtc;
		cdtc.Attach(GetDlgItem(IDC_DATETIMEPICKER4)->m_hWnd);
		cdtc.SetTime(&theTime);	
		cdtc.Detach();
		cdtc.Attach(GetDlgItem(IDC_DATETIMEPICKER1)->m_hWnd);
		cdtc.SetTime(&theTime);	
		cdtc.Detach();
		//grey out the third record
	}
}

void CLottery5Dlg::OnBnClickedButtonautomate()
{
	// TODO: Add your control notification handler code here
	AutomateView V;
	V.DoModal();
}
// Analyze current chosen target
void CLottery5Dlg::AnalyzeCurrentChosenTarget(double * score)
{
	TCHAR zs[256];
	CEdit edits;
	// update the input content
	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataOne1", "000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_YAO11+0)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();
	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataOne2", "000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_YAO11+1)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();
	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataTwo1", "000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_YAO11+2)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();	
	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("dataTwo2", "000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_YAO11+3)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();
	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("actionNumber1", "0000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_EDITISSUE1)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();
	MultiByteToWideChar(CP_ACP, NULL, theTarget.get("actionNumber2", "0000000").asCString(), -1, zs, 256);
	edits.Attach(GetDlgItem(IDC_EDITISSUE2)->m_hWnd);
	edits.SetWindowText(zs);
	edits.Detach();
	// fill last group with 000000
	for(int i=4;i<6;i++){
		edits.Attach(GetDlgItem(IDC_YAO11+i)->m_hWnd);
		edits.SetWindowText(_T("000000"));
		edits.Detach();
	}
	// TODO: why is this value weird if not set to 1
	nCurrDisplayGroup = 1;
	OnBnClickedButtonAction();
	CEdit w;
	w.Attach(GetDlgItem(IDC_SCORE1)->m_hWnd);w.GetWindowText(zs, 256);w.Detach();	score[0] = _tstof(zs);
	w.Attach(GetDlgItem(IDC_SCORE2)->m_hWnd);w.GetWindowText(zs, 256);w.Detach();	score[1] = _tstof(zs);
	OnBnClickedGroupadd();
	w.Attach(GetDlgItem(IDC_SCORE1)->m_hWnd);w.GetWindowText(zs, 256);w.Detach();	score[2] = _tstof(zs);
	w.Attach(GetDlgItem(IDC_SCORE2)->m_hWnd);w.GetWindowText(zs, 256);w.Detach();	score[3] = _tstof(zs);
}

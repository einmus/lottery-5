#include "stdafx.h"
#include "NongLi.h"
/*------------农历转换函数-----------*/
void GetDayOf(PSYSTEMTIME pSt, TCHAR* pBuffer)
{ 
	/*属相名称*/
	const TCHAR *cShuXiang[] = {_T("鼠"),_T("牛"),_T("虎"),_T("兔"),_T("龙"),_T("蛇"),_T("马"),_T("羊"),_T("猴"),_T("鸡"),_T("狗"),_T("猪")};
	/*农历日期名*/
	const TCHAR *cDayName[] = {_T("*"),_T("初一"),_T("初二"),_T("初三"),_T("初四"),_T("初五"),_T("初六"),_T("初七"),_T("初八"),_T("初九"),_T("初十"),_T("十一"),_T("十二"),_T("十三"),_T("十四"),_T("十五"),_T("十六"),_T("十七"),_T("十八"),_T("十九"),_T("二十"),_T("廿一"),_T("廿二"),_T("廿三"),_T("廿四"),_T("廿五"),_T("廿六"),_T("廿七"),_T("廿八"),_T("廿九"),_T("三十")};
	/*农历月份名*/
	const TCHAR *cMonName[] = {_T("*"),_T("正"),_T("二"),_T("三"),_T("四"),_T("五"),_T("六"),_T("七"),_T("八"),_T("九"),_T("十"),_T("十一"),_T("腊")};
	/*公历每月前面的天数*/
	const int wMonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
	/*农历数据*/
	const int wNongliData[100] = {2635,333387,1701,1748,267701,694,2391,133423,1175,396438
		,3402,3749,331177,1453,694,201326,2350,465197,3221,3402
		,400202,2901,1386,267611,605,2349,137515,2709,464533,1738
		,2901,330421,1242,2651,199255,1323,529706,3733,1706,398762
		,2741,1206,267438,2647,1318,204070,3477,461653,1386,2413
		,330077,1197,2637,268877,3365,531109,2900,2922,398042,2395
		,1179,267415,2635,661067,1701,1748,398772,2742,2391,330031
		,1175,1611,200010,3749,527717,1452,2742,332397,2350,3222
		,268949,3402,3493,133973,1386,464219,605,2349,334123,2709
		,2890,267946,2773,592565,1210,2651,395863,1323,2707,265877};
	static int wCurYear,wCurMonth,wCurDay;
	static int nTheDate,nIsEnd,m,k,n,i,nBit;
	TCHAR szNongli[30], szNongliDay[10],szShuXiang[10];
	/*---取当前公历年、月、日---*/
	wCurYear = pSt->wYear;
	wCurMonth = pSt->wMonth;
	wCurDay = pSt->wDay;
	/*---计算到初始时间1921年2月8日的天数：1921-2-8(正月初一)---*/
	nTheDate = (wCurYear - 1921) * 365 + (wCurYear - 1921) / 4 + wCurDay + wMonthAdd[wCurMonth - 1] - 38;
	if((!(wCurYear % 4)) && (wCurMonth > 2))
		nTheDate = nTheDate + 1;
	/*--计算农历天干、地支、月、日---*/
	nIsEnd = 0;
	m = 0;
	while(nIsEnd != 1)
	{
		if(wNongliData[m] < 4095)
			k = 11;
		else
			k = 12;
		n = k;
		while(n>=0)
		{
			//获取wNongliData(m)的第n个二进制位的值
			nBit = wNongliData[m];
			for(i=1;i<n+1;i++)
				nBit = nBit/2;

			nBit = nBit % 2;

			if (nTheDate <= (29 + nBit))
			{
				nIsEnd = 1;
				break;
			}

			nTheDate = nTheDate - 29 - nBit;
			n = n - 1;
		}
		if(nIsEnd)
			break;
		m = m + 1;
	}
	wCurYear = 1921 + m;
	wCurMonth = k - n + 1;
	wCurDay = nTheDate;
	if (k == 12)
	{
		if (wCurMonth == wNongliData[m] / 65536 + 1)
			wCurMonth = 1 - wCurMonth;
		else if (wCurMonth > wNongliData[m] / 65536 + 1)
			wCurMonth = wCurMonth - 1;
	}

	/*--生成农历属相 ==> wNongli--*/
	_stprintf(szShuXiang,_T("%s"),cShuXiang[((wCurYear - 4) % 60) % 12]);
	_stprintf(szNongli,_T("%s年 "),szShuXiang);

	/*--生成农历月、日 ==> wNongliDay--*/
    if (wCurMonth < 1)
        _stprintf(szNongliDay,_T("闰%s"),cMonName[-1 * wCurMonth]);
    else
        _tcscpy(szNongliDay,cMonName[wCurMonth]);
    _tcscat(szNongliDay,_T("月"));
    _tcscat(szNongliDay,cDayName[wCurDay]);
    _tcscat(szNongli,szNongliDay);
    _tcscat(szNongli,_T(" "));
    _tcscat(pBuffer, szNongli);
}
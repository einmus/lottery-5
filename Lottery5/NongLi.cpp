#include "stdafx.h"
#include "NongLi.h"
/*------------ũ��ת������-----------*/
void GetDayOf(PSYSTEMTIME pSt, TCHAR* pBuffer)
{ 
	/*��������*/
	const TCHAR *cShuXiang[] = {_T("��"),_T("ţ"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��")};
	/*ũ��������*/
	const TCHAR *cDayName[] = {_T("*"),_T("��һ"),_T("����"),_T("����"),_T("����"),_T("����"),_T("����"),_T("����"),_T("����"),_T("����"),_T("��ʮ"),_T("ʮһ"),_T("ʮ��"),_T("ʮ��"),_T("ʮ��"),_T("ʮ��"),_T("ʮ��"),_T("ʮ��"),_T("ʮ��"),_T("ʮ��"),_T("��ʮ"),_T("إһ"),_T("إ��"),_T("إ��"),_T("إ��"),_T("إ��"),_T("إ��"),_T("إ��"),_T("إ��"),_T("إ��"),_T("��ʮ")};
	/*ũ���·���*/
	const TCHAR *cMonName[] = {_T("*"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("ʮ"),_T("ʮһ"),_T("��")};
	/*����ÿ��ǰ�������*/
	const int wMonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
	/*ũ������*/
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
	/*---ȡ��ǰ�����ꡢ�¡���---*/
	wCurYear = pSt->wYear;
	wCurMonth = pSt->wMonth;
	wCurDay = pSt->wDay;
	/*---���㵽��ʼʱ��1921��2��8�յ�������1921-2-8(���³�һ)---*/
	nTheDate = (wCurYear - 1921) * 365 + (wCurYear - 1921) / 4 + wCurDay + wMonthAdd[wCurMonth - 1] - 38;
	if((!(wCurYear % 4)) && (wCurMonth > 2))
		nTheDate = nTheDate + 1;
	/*--����ũ����ɡ���֧���¡���---*/
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
			//��ȡwNongliData(m)�ĵ�n��������λ��ֵ
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

	/*--����ũ������ ==> wNongli--*/
	_stprintf(szShuXiang,_T("%s"),cShuXiang[((wCurYear - 4) % 60) % 12]);
	_stprintf(szNongli,_T("%s�� "),szShuXiang);

	/*--����ũ���¡��� ==> wNongliDay--*/
    if (wCurMonth < 1)
        _stprintf(szNongliDay,_T("��%s"),cMonName[-1 * wCurMonth]);
    else
        _tcscpy(szNongliDay,cMonName[wCurMonth]);
    _tcscat(szNongliDay,_T("��"));
    _tcscat(szNongliDay,cDayName[wCurDay]);
    _tcscat(szNongli,szNongliDay);
    _tcscat(szNongli,_T(" "));
    _tcscat(pBuffer, szNongli);
}
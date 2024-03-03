#include "../Header/CTimeMgr.h"


CTimeMgr::CTimeMgr()
	: llCurCount{}
	, llFrequency{}
	, llPrevCount{}
	, dDT{ 0.f }
{

}

CTimeMgr::~CTimeMgr()
{


}

void CTimeMgr::Init()
{
	//���� ī��Ʈ
	QueryPerformanceCounter(&llCurCount);

	//�ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&llFrequency);

}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&llCurCount);
	
	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�. (�����Ӱ� ������ �ð���)
	dDT = (double)(llCurCount.QuadPart - llPrevCount.QuadPart) / (double)llFrequency.QuadPart;


	llPrevCount = llCurCount;
	
#ifdef _DEBUG
	if (dDT > (1. / 60.))
		dDT = (1. / 60.);
#endif



}

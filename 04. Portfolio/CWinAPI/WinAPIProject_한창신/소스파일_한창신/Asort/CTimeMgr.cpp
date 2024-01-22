#include "CTimeMgr.h"


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
	//현재 카운트
	QueryPerformanceCounter(&llCurCount);

	//초당 카운트 횟수
	QueryPerformanceFrequency(&llFrequency);

}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&llCurCount);
	
	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다. (프레임과 프레임 시간값)
	dDT = (double)(llCurCount.QuadPart - llPrevCount.QuadPart) / (double)llFrequency.QuadPart;


	llPrevCount = llCurCount;
	
#ifdef _DEBUG
	if (dDT > (1. / 60.))
		dDT = (1. / 60.);
#endif



}

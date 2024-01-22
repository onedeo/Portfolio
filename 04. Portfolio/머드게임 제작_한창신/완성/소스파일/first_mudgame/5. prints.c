#include "myheader.h"

//general
char* print_general(int num)
{
	switch (num)
	{
	case 0: 
		//메인화면 출력
		strcpy(str, "\n\n\t\t꿈과 희망이 있는 창신경마에 오신걸 진심으로 환영합니다.\n\n\
\t\t여러분의 목표와 꿈을 단시간에 이루어 드리겠습니다.\n\n\
\t\t진심으로 환영합니다\n\n\n\
\t\t1. 베팅하기: 마에 베팅하여 여러분의 꿈을 이루세요!\n\n\
\t\t2. 확률 아이템 구매: 아이템을 구매해서 당신의 마에 승률을 높히세요!\n\n\
\t\t3. 베팅 초기화: 다시 한번 생각 하고 싶다면 베팅을 초기화 하세요!\n\n\
\t\t4. 종료하기.\n\n\
\t\t0. 당신의 꿈을 이루세요! 경기 시작!\n\n\n");
		break;

	case 1: 
		//메인화면 선택 출력
		strcpy(str, "\t\t1. 베팅하기\t\t\t2.확률 아이템 구매\n\t\t3. 베팅 초기화\t\t\t4.게임 종료\n\n\t\t\t\t  0. 게임시작");
		break;

	case 2:
		//게임 클리어
		strcpy(str, "\n\t\t\t\t\t진심으로 축하드립니다\n\n\n\t당신은 5천만원을 30억으로 만드시는데 성공했습니다.\n\t게임에서와 같은 행운이 항상 당신과 함께하길 기원합니다.\n\t\t\t\t\t플레이 해주셔서 감사합니다.\n\n");
		break;

	case 3:
		//제작자 이름
		strcpy(str, "\n\n\t\t\t\t\t\t\t       제작. 한창신");
		break;

	case 4:
		//게임 목표
		strcpy(str, "\n\n\n\t<게임 방법>\n\n\
\tWAY TO SIGNIEL에 오신걸 환영합니다!\n\
\n\t현재 소유한 돈으로(화면 상단) 경마에 참여해서 돈을 벌어보세요!!\
\n\t목표 금액 30억을 달성하면 롯데 시그니엘 입주 뿐 아니라 특별한 선물이 있습니다!\
\n\n\t경마는 총 5개로 구성되어 있으며 원하는 마에 돈을 베팅합니다.(중복가능)\
\n\t각 경마는 한번 이동 할 때 1칸, 3칸, 5칸을 일정 확률로 이동합니다.\
\n\t각 마의 이동 확률과 배당률이 상이하니 잘 생각해보고 베팅하세요!\
\n\n\t먼저, 초기자본으로 5천만원을 드리겠습니다. 지금 바로 경마에 참여하세요!\n\n");
	
		break;
	}

	return str;
}

//race
char* print_race(int num)
{
	switch (num)
	{
	case 0:
		//배팅 확인
		strcpy(str, "\n\t아래와 같은 금액을 배팅하셨습니다.\n\n\t1번을 눌러 시작하세요.\n\n\t당신의 승리가 한발짝 앞에 있습니다.\n\n");
		break;

	case 1:
		//경기 진행 컨펌
		strcpy(str, "\t이대로 진행하시겠습니까 ?\n\n\t1. 네, 제 직감은 틀림 없습니다.\n\t2. 아니요, 잠깐만요");
		break;
	}

	return str;
}

//bet
char* print_bet(int num)
{
	switch (num)
	{
	case 0:
		//bet 메인화면
		strcpy(str, "\t창신경마에 오신결 환영합니다.\n\n\t모든 경마는 1칸/3칸/5칸 중 하나를 아래와 같은 확률로 이동합니다.\n\t경마를 선택 후 배팅액 입력 후 경마를 시작해주세요. \n\n\t승리는 당신의 것입니다.\n\n");
		break;
		
	case 1:
		//마 정보 구분 행
		strcpy(str, "\t| 번호 |     이름     | 1칸 확률 | 3칸 확률 | 5칸 확률 |  배당율 |    베팅액    |\n");
		break;
	}
	
	return str;
}

//iteam
char* print_iteam(int num)
{
	switch (num)
	{
	case 0:
		//메인 내용
		strcpy(str, "\n\n\t\t철순 샵에 오신걸 환영합니다.\n\n\t\t저희는 승률을 올릴 수 있는 아이템을 판매하고 있습니다.\n\n\
\t\t저희는 1칸이동 확률을 낮추고 3칸이나 5칸 확률을 올려드립니다.\n\n\
\t\t한 아이템만 구매 및 적용 가능합니다.\n\n\n\
\t\t1. [3000만원] 1칸 확률  5% ↓, 3칸 확률  5%↑\n\n\
\t\t2. [5000만원] 1칸 확률  5% ↓, 5칸 확률  5%↑\n\n\
\t\t3. [7000만원] 1칸 확률 10% ↓, 3칸 확률 10%↑\n\n\
\t\t4. [  1 억원] 1칸 확률 10% ↓, 5칸 확률 10%↑\n\n\n");
		break;

	case 1: 
		//아이템 구매 가능시
		strcpy(str, "\t1. 1번 구매\t2. 2번 구매\t3. 3번 구매\t4. 4번 구매\t0. 돌아가기\n\n\n");
		break;

	case 2:
		//구매 확정
		strcpy(str, "\t정말로 구매하시겠습니까?\n\t\t1. 네, 이길 수만 있다면... \n\t\t2. 아니요, 안써도 이길거 같습니다.\n");
		break;

	case 3:
		//돈 부족
		strcpy(str, "\t당신은 이 아이템을 사기에 돈이 부족하군.\n\t이번에 느낌이 좋은데 베팅으로 돈을 더 벌어오는건 어떻겠나?\n\n");
		break;

	case 4:
		//사용 마 선택
		strcpy(str, "\t몇 번 마에게 사용하시겠습니까?\n");
		break;

	case 5:
		//확률 수정 완료
		strcpy(str, "\t확률 수정 적용 완료되었습니다. 감사합니다.\n\n\n\n");
		break;

	case 6:
		//아이템 구매 불가능 (중복구매)
		strcpy(str, "\t한 경기에서 아이템 중복 사용은 불법입니다.\n\t경기를 진행 후 다시 구매하러 와주시길 바랍니다.\n\n\n");
		break;
	}

	return str;
}

//reset bets
char* print_reset(int num)
{
	switch (num)
	{
	case 0: 
		//초기화 진행 컨펌
		strcpy(str, "\t초기화를 정말 진행하시겠습니까? \n\t1. 네, 느낌이 쌔합니다.\n\t2. 아니요, 뭔가 될거 같습니다.\n");
		break;
		
	case 1:
		//초기화 진행시켜
		strcpy(str, "\t배팅액 초기화를 완료하였습니다.\n\n\n\n");
		break;

	case 2:
		//초기화 미진행
		strcpy(str, "\t배팅액 초기화를 취소하셨습니다.\n\n\n\n");
		break;

	case 3:
		//초기화 불가 (배팅 안함)
		strcpy(str, "\t당신은 아직 배팅을 하지 않았습니다.\n\t배팅을 먼저 진행하세요!\n\n\n");
		break;
	}

	return str;
}

	//end game
char* print_end(int num)
{
	switch (num)
	{
	case 0:
		//컨펌1
		strcpy(str, "\t정말로 종료하시겠습니까?\n\t1. 네, 이제 손 씻었습니다.\n\t2. 아니요, 진짜 마지막 한판만 하고 가겠습니다.");
		break;

	case 1:
		//컨펌2
		strcpy(str, "\t기록은 저장되지 않습니다.\n\t30억을 모으시면 선물도 있습니다.\n\t정말로 종료하시겠습니까?\n\t1. 네\n\t2. 아니요");
		break;

	}
}

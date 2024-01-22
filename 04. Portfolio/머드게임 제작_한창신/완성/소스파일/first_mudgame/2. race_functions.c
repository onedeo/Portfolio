#include "myheader.h"

//경기 (글자x)

void reset_horses(struct horses* horse)
{
	set_horses(&horse[0], 1, "이상해씨", "☎", 50, 25, 25, 2);
	set_horses(&horse[1], 2, "키타산블랙", "※", 55, 20, 25, 4);
	set_horses(&horse[2], 3, "까미 냥이", "◎", 60, 20, 20, 6);
	set_horses(&horse[3], 4, "CY.NIRO ", "◈", 65, 15, 20, 8);
	if (GM == 1)set_horses(&horse[4], 5, "우리 우디", "◐", 70, 15, 15, 10);
	else set_horses(&horse[4], 5, "우리 우디", "◐", 0, 0, 100, 10);
}

void set_horses(struct horses* horse, int num, const char* name, const char* imo, int per1, int per3, int per5, int percent)
{
	//확률 합이 100이 아닐 경우 -> exit
	if (per1+per3+per5!=100)
	{
		printf("%s의 확률합이 100이 아닙니다.", name);
		exit(1);
	}

	horse->num = num;
	horse->name = name;
	strcpy(horse->imo, imo);
	horse->per_1 = per1;
	horse->per_3 = per3;
	horse->per_5 = per5;
	horse->percent = percent;

}

int rand_step(struct horses horse)
{
	int dice;

	dice = rand() % 100;
	horse.per_1 -= 1; //0부터이기 위해
	if (dice <= horse.per_1) return 1;
	else if (dice <= horse.per_1 + horse.per_3) return 3;
	else if (dice <= horse.per_1 + horse.per_3 + horse.per_5) return 5;
}

void go_horse(struct horses* horse, int step, int start, int* finish, int* winner)
{
	if (start == 1) step = 1; //시작시 스타트 라인에 한줄로 서있기 위해
	if (*finish == 1) step = 0; //경기 완료 시 아래 함수들이 실행 안되기 위해

	int go = 0;
	printf("\033[0m\n  %d번 %s   베팅금: %d\n", horse->num, horse->name, horse->tot_bet);

	for (int k = 0; k < step; k++) //step 만큼 반복: 삭제->출력
	{
		if (k != 0)
		{
			//한줄 삭제하기 (특수문자는 칸을 2칸 차지하나봄 ㅎ)
			for (int i = 0; i < DIST; i++) printf("\b\b");
		}

		for (int i = 0; i < DIST; i++) //한줄 만들기
		{
			if (horse->tot_steps + go == i) printf("\033[32m%s", horse->imo);
			else if (i < horse->tot_steps + go) PASSED;
			else PATH;

			if (horse->tot_steps + go >= DIST - 1)
			{
				*finish = 1;
				*winner = horse->num-1;
			}
		}
		go++;
		if (*winner != 100) break;

		Sleep(SEC_STEP / step);	//움직이는 속도 조정 (몇 칸을 가든 소모되는 시간은 동일함)
	}
	printf("\n\n");
	horse->tot_steps += step;
}

//경기 (글자)

void start_race()
{
	resetwords_top_bot();
	char str[300] = "안녕하십니까 여러분, 창신 경마에 참여해주셔서 감사합니다.\
\n이제 곧 경기가 시작 됩니다.\
\n행운을 빕니다.\n";
	for (int i = 0; i < strlen(str); i++)
	{
		putchar(str[i]);
		Sleep(WORD_SPEED);
	}
	for (int i = 3; 0 < i; i--)
	{
		Sleep(300);
		printf("%d....", i);
		Sleep(300);
	}
}

void finish_race(struct horses horse)
{
	resetwords_top_bot();

	//40번째: 38(번호), 45번째: m (이름)
	char str[300] = "경기가 끝났습니다!! 승자는 바로바로.... 번마 입니다!!\
\n맞추신 분에게는 축하를, 아쉬운 분들은 다음에 꼭 맞추시길 기원하며,\
\n다음 경기 때 뵙겠습니다!\
\n감사합니다 :)\n";
	for (int i = 0; i < strlen(str); i++)
	{
		if (i == 38) str[i] = horse.num + '0';
		if (i == 45) printf("\033[33m<%s %s %s>\033[0m", horse.imo, horse.name, horse.imo);
		putchar(str[i]);
		Sleep(WORD_SPEED);
	}
}

void printmoneyrace()
{
	int speed = (money - before_money) / 101;
	box_line();
	box_line();
	printf("\033[F");
	printf("\033[F");
	play_music("cash1", 0);
	while (speed > 1)
	{

		printf("\t목표:\033[33m %d억원\t\t \033[0m현재: \033[33m%d억 %04d만원\t\t\033[0m잔액: \033[33m%d억 %d만원\033[0m", \
			get_uk(TARGET_MONEY), get_uk(before_money), get_man(before_money), get_uk(TARGET_MONEY - before_money), get_man(TARGET_MONEY - before_money));
		Sleep(20);
		printf("\r");
		for (int i = 0; i < DIST * 2; i++)
		{
			printf(" ");
		}
		printf("\r");
		before_money += speed;
		if (before_money >= money - speed) break;
	}
	printf("\t목표:\033[33m %d억원\t\t \033[0m현재: \033[33m%d억 %d만원\t\t\033[0m잔액: \033[33m%d억 %d만원\033[0m", \
		get_uk(TARGET_MONEY), get_uk(money), get_man(money), get_uk(TARGET_MONEY - money), get_man(TARGET_MONEY - money));
	box_line();
	printf("\n");
	Sleep(500);
	play_music("cash2", 0);
	Sleep(2000);
}

void if_wins(struct horses horse)
{

	//32: 마 번호, 38: 마 이름, 42: 베팅액 73: 배당률 98: 수령금
	char str[300] = "진심으로 축하드립니다.!! \n\
당신은  번마 에 억 만원\033[0m을 베팅 하셨고, 배당률은  배 입니다.\n\
총 수령 금액은 억  만원\033[0m 입니다. 다시 한번 진심으로 축하드립니다!!!\n\n";

	for (int i = 0; i < strlen(str); i++)
	{
		if (i == 33) str[i] = horse.num + '0';
		if (i == 39) printf("\033[33m%s%s%s\033[0m", horse.imo, horse.name, horse.imo);
		if (i == 42) printf("\033[33m%d", get_uk(horse.tot_bet));
		if (i == 45) printf("%d", get_man(horse.tot_bet));
		if (i == 78) printf("\033[33m%d\033[0m", horse.percent);
		if (i == 105) printf("\033[33m%d", get_uk(horse.tot_bet * horse.percent));
		if (i == 108) printf("%d", get_man(horse.tot_bet * horse.percent));
		putchar(str[i]);
		Sleep(WORD_SPEED);
	}
}

void if_lose()
{
	char str[300] = "아쉽지만 승리 마를 맞추지 못하셨습니다.\n\
다음에는 꼭 더 좋은 기회가 있을 것입니다.\n\
너무 실망하지 마시고, 다음에는 꼭 승리하시길 기원하며,\n\
다음에 뵙겠습니다!!\n";
	for (int i = 0; i < strlen(str); i++)
	{
		putchar(str[i]);
		Sleep(WORD_SPEED);
	}
}
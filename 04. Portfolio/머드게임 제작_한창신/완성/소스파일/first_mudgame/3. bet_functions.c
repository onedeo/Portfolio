#include "myheader.h"

void ask_bet(struct horses horse)
{
	printf("\t%d번 %s에 얼마를 베팅하시겠습니까?(단위: 만원)\n\n\n", horse.num, horse.name);
}

void bet_input(struct horses* horse)
{

	ask_bet(*horse);
	int bet_total;
	//resetwords_bot_top();
	
	while (1)
	{
		horse->bet = input(-999999, 999999);

		bet_total = horse->tot_bet + horse->bet;

		if (money - horse->bet >= 0 &&bet_total >= 0 && bet_total <= 999999) break;
		if (bet_total <= 0)
		{
			resetwords_bot_top();
			printf("\t베팅액이 음수가 될 수 없습니다. 다시 입력 바랍니다: \n\n\n");
		}
		if (money - bet_total < 0)
		{
			resetwords_bot_top();
			printf("\t빚을 져서 베팅을 할 수 없습니다. 도박중독 상담 : 1336번\n\n\n");
		}
	}
}

void inform_line()
{
	printf("\t");
	for (int i = 0; i < DIST * 2 - 19; i++)
	{
		printf("-");
	}
	DOWN;
}

void horseinform(struct horses horse)
{
	printf("\t|%3d   |  %-10s  | %5d    | %5d    | %5d    |   x %2d  |  %d 만원\t|\n", \
		horse.num, horse.name, horse.per_1, horse.per_3, horse.per_5, horse.percent, horse.tot_bet);
	inform_line();
}

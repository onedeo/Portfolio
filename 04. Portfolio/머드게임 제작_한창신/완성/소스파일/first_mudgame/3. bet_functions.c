#include "myheader.h"

void ask_bet(struct horses horse)
{
	printf("\t%d�� %s�� �󸶸� �����Ͻðڽ��ϱ�?(����: ����)\n\n\n", horse.num, horse.name);
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
			printf("\t���þ��� ������ �� �� �����ϴ�. �ٽ� �Է� �ٶ��ϴ�: \n\n\n");
		}
		if (money - bet_total < 0)
		{
			resetwords_bot_top();
			printf("\t���� ���� ������ �� �� �����ϴ�. �����ߵ� ��� : 1336��\n\n\n");
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
	printf("\t|%3d   |  %-10s  | %5d    | %5d    | %5d    |   x %2d  |  %d ����\t|\n", \
		horse.num, horse.name, horse.per_1, horse.per_3, horse.per_5, horse.percent, horse.tot_bet);
	inform_line();
}

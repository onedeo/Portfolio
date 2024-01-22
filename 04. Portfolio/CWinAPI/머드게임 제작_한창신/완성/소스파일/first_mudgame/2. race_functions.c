#include "myheader.h"

//��� (����x)

void reset_horses(struct horses* horse)
{
	set_horses(&horse[0], 1, "�̻��ؾ�", "��", 50, 25, 25, 2);
	set_horses(&horse[1], 2, "ŰŸ���", "��", 55, 20, 25, 4);
	set_horses(&horse[2], 3, "��� ����", "��", 60, 20, 20, 6);
	set_horses(&horse[3], 4, "CY.NIRO ", "��", 65, 15, 20, 8);
	if (GM == 1)set_horses(&horse[4], 5, "�츮 ���", "��", 70, 15, 15, 10);
	else set_horses(&horse[4], 5, "�츮 ���", "��", 0, 0, 100, 10);
}

void set_horses(struct horses* horse, int num, const char* name, const char* imo, int per1, int per3, int per5, int percent)
{
	//Ȯ�� ���� 100�� �ƴ� ��� -> exit
	if (per1+per3+per5!=100)
	{
		printf("%s�� Ȯ������ 100�� �ƴմϴ�.", name);
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
	horse.per_1 -= 1; //0�����̱� ����
	if (dice <= horse.per_1) return 1;
	else if (dice <= horse.per_1 + horse.per_3) return 3;
	else if (dice <= horse.per_1 + horse.per_3 + horse.per_5) return 5;
}

void go_horse(struct horses* horse, int step, int start, int* finish, int* winner)
{
	if (start == 1) step = 1; //���۽� ��ŸƮ ���ο� ���ٷ� ���ֱ� ����
	if (*finish == 1) step = 0; //��� �Ϸ� �� �Ʒ� �Լ����� ���� �ȵǱ� ����

	int go = 0;
	printf("\033[0m\n  %d�� %s   ���ñ�: %d\n", horse->num, horse->name, horse->tot_bet);

	for (int k = 0; k < step; k++) //step ��ŭ �ݺ�: ����->���
	{
		if (k != 0)
		{
			//���� �����ϱ� (Ư�����ڴ� ĭ�� 2ĭ �����ϳ��� ��)
			for (int i = 0; i < DIST; i++) printf("\b\b");
		}

		for (int i = 0; i < DIST; i++) //���� �����
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

		Sleep(SEC_STEP / step);	//�����̴� �ӵ� ���� (�� ĭ�� ���� �Ҹ�Ǵ� �ð��� ������)
	}
	printf("\n\n");
	horse->tot_steps += step;
}

//��� (����)

void start_race()
{
	resetwords_top_bot();
	char str[300] = "�ȳ��Ͻʴϱ� ������, â�� �渶�� �������ּż� �����մϴ�.\
\n���� �� ��Ⱑ ���� �˴ϴ�.\
\n����� ���ϴ�.\n";
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

	//40��°: 38(��ȣ), 45��°: m (�̸�)
	char str[300] = "��Ⱑ �������ϴ�!! ���ڴ� �ٷιٷ�.... ���� �Դϴ�!!\
\n���߽� �п��Դ� ���ϸ�, �ƽ��� �е��� ������ �� ���߽ñ� ����ϸ�,\
\n���� ��� �� �˰ڽ��ϴ�!\
\n�����մϴ� :)\n";
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

		printf("\t��ǥ:\033[33m %d���\t\t \033[0m����: \033[33m%d�� %04d����\t\t\033[0m�ܾ�: \033[33m%d�� %d����\033[0m", \
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
	printf("\t��ǥ:\033[33m %d���\t\t \033[0m����: \033[33m%d�� %d����\t\t\033[0m�ܾ�: \033[33m%d�� %d����\033[0m", \
		get_uk(TARGET_MONEY), get_uk(money), get_man(money), get_uk(TARGET_MONEY - money), get_man(TARGET_MONEY - money));
	box_line();
	printf("\n");
	Sleep(500);
	play_music("cash2", 0);
	Sleep(2000);
}

void if_wins(struct horses horse)
{

	//32: �� ��ȣ, 38: �� �̸�, 42: ���þ� 73: ���� 98: ���ɱ�
	char str[300] = "�������� ���ϵ帳�ϴ�.!! \n\
�����  ���� �� �� ����\033[0m�� ���� �ϼ̰�, ������  �� �Դϴ�.\n\
�� ���� �ݾ��� ��  ����\033[0m �Դϴ�. �ٽ� �ѹ� �������� ���ϵ帳�ϴ�!!!\n\n";

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
	char str[300] = "�ƽ����� �¸� ���� ������ ���ϼ̽��ϴ�.\n\
�������� �� �� ���� ��ȸ�� ���� ���Դϴ�.\n\
�ʹ� �Ǹ����� ���ð�, �������� �� �¸��Ͻñ� ����ϸ�,\n\
������ �˰ڽ��ϴ�!!\n";
	for (int i = 0; i < strlen(str); i++)
	{
		putchar(str[i]);
		Sleep(WORD_SPEED);
	}
}
#include "myheader.h"


/*
1. ���丮
2. �޴�
2-1. �渶 ����, ��� Ȯ��, ����
2-1-1 �渶����: �渶 ����, �ڷΰ���
2-1-1-1 �渶����: ���ñ� �ֱ�, ��� ����
2-1-1-1-1 ��� �ùķ��̼�, ���� ����
2-1 ����

�������
1. �� ���� ������ �̵�
2. �� ���� ���� Ȯ���� 1,3,5, ���� �Ȱ��� Ȯ�� ����
3. 0.5�ʿ� �ѹ��� ������Ʈ
4. 3ĭ, 5ĭ�� 0.5�ʿ� ó���ؾߵ�
5. �� ���� ��¼��� �����ϸ� ��� ��

// �� ���� ������ �� ���� -> 1������ ���ʴ�� �����̸� �ȵǴ� �� ���� ���� �����̴���, �ƴϸ� ���� �����̴� ������ �������� �ؾ���


*/

int money=0;
int before_money=0;
char str[300];

int main()
{
	system("mode con: cols=100 lines=35"); //ȭ�� ����
	SetConsoleTitle(TEXT("Way To Signiel")); //�ܼ� �̸�
	PlaySound(NULL, 0, 0); //���� ���
	

	int begin = (INTRO_SKIP * GM); //ó�� ���۽� õõ�� ����Ʈ, ���߿��� �׳� ����(����ȭ��)
	int shopbegin = INTRO_SKIP * GM;
	int bet_begin = INTRO_SKIP * GM;
	int race_begin = INTRO_SKIP * GM;
	int first_begin = INTRO_SKIP * GM;
	int end = 0;

	if (first_begin != 1)  money = START_MONEY; //GM��� �� �� ����

	//�޴� ���� ������
	int operation;

	//�渶 ��⸦ ���� ������
	struct horses horse[5];
	int step[5];
	int b_start;
	int b_finish;
	int num_winner;

	//�� ����   ����, ��ȣ, �̸�, �̸�Ƽ��, 1ĭ Ȯ��, 3ĭ Ȯ��, 5ĭ Ȯ��, �����
	reset_horses(horse);


	//���� �ʱ�ȭ
	for (int i = 0; i < 5; i++)
	{
		horse[i].bet = 0;
		horse[i].tot_bet = 0;
	}

	//�������� ���� ������
	int iteam_num;
	int iteam_3;
	int iteam_5;
	int b_bought = 0;
	int price[4] = { 3000,5000,7000,10000 };

	//������ ���� ������
	int total_bet = 0;
	int bet_horse;

	//������ ���� ������
	int playmain = 1; //1�� �÷���

	//�������������������ݺ��� ���ۤ���������������������
	while (1)
	{
		if (begin == 1)
		{
			printstart();
		}
		system("cls");

		//���� ���� 
		if (first_begin == 1)
		{
			printmoney();
			printw(print_general(4));
			Sleep(1000);
			pressenter();

			money = START_MONEY;
			RESET;
			printmoneyrace();

			first_begin = 0;
		}

		if (playmain == 1)
			play_music("main", 1);
		playmain = 0;

		system("cls");

		//ó�� ȭ��
		printmoney();
		if (begin == 0)
		{
			printf("%s", print_general(0));
		}
		else
		{
			printw(print_general(0));
			begin = 0;
		}


		resetwords_top_bot();

		printf(print_general(1));
		operation = input(0, 4);

		//��޴� switch
		switch (operation)
		{
		case 1:
			//���� �ݺ���
			while (1)
			{
				system("cls");
				printmoney();
				if (bet_begin != 0)
				{
					printw(print_bet(0));
					Sleep(50);
					bet_begin = 0;
				}
				else
				{
					printf(print_bet(0));
				}

				inform_line();
				printf(print_bet(1));
				inform_line();

				for (int i = 0; i < 5; i++)
				{
					horseinform(horse[i]);
				}

				resetwords_top_bot();

				printf("\t1. %s\t2. %s\t3. %s\t4. %s\t5. %s\n\n\t\t\t\t\t\t\t\t\t 0. ���ư���\n", \
					horse[0].name, horse[1].name, horse[2].name, horse[3].name, horse[4].name);

				operation = input(0, 5);
				if (operation == 0)break;

				//�÷��̾ �����ϴ� �� ��ȣ
				bet_horse = operation - 1;

				resetwords_bot_top();
				bet_input(&horse[bet_horse]);

				total_bet = 0;
				/*for (int i = 0; i < 5; i++)
				{
					money -= horse[i].bet;
					horse[i].tot_bet += horse[i].bet;
					total_bet += horse[i].tot_bet;
					horse[i].bet = 0;
				}*/
				money -= horse[bet_horse].bet;
				horse[bet_horse].tot_bet += horse[bet_horse].bet;
				total_bet += horse[bet_horse].tot_bet;
				horse[bet_horse].bet = 0;

			}
			break;
		case 2:
			play_music("shop", 1);
			//Ȯ�� ������ ���� �����
			//3ĭ 5%, 5ĭ 5% 3ĭ 10% 5ĭ 10%		//3õ, 5õ, 7õ, 1��

			system("cls");
			printmoney();
			//ȭ�� ���
			if (shopbegin != 1)
			{
				printf(print_iteam(0));
			}
			else
			{
				printw(print_iteam(0));
				shopbegin = 0;
			}

			resetwords_top_bot();

			//������ ���� ����
			if (b_bought == 0)
			{
				printf(print_iteam(1));

				iteam_num = input(0, 4);
				if (iteam_num == 0)
				{
					playmain = 1;
					continue;
				}

				resetwords_bot_top();
				printw(print_iteam(2));
				operation = input(1, 2);
				if (operation == 2)
				{
					playmain = 1;
					continue;
				}
				if (price[iteam_num - 1] > money)
				{
					resetwords_bot_top();
					printw(print_iteam(3));
					pressenter();
					playmain = 1;
					continue;
				}

				resetwords_bot_top();
				printw(print_iteam(4));
				printf("\t1. %s\t2. %s\t3. %s\t4. %s\t5. %s\n\n", \
					horse[0].name, horse[1].name, horse[2].name, horse[3].name, horse[4].name);
				operation = input(1, 5);

				//operation-1 = �� ��ȣ iteam_num = ������
				iteam_3 = 0;
				iteam_5 = 0;
				switch (iteam_num)
				{
				case 1:
					iteam_3 = 5;
					money -= price[0];
					break;
				case 2:
					iteam_5 = 5;
					money -= price[1];
					break;
				case 3:
					iteam_3 = 10;
					money -= price[2];
					break;
				case 4:
					iteam_5 = 10;
					money -= price[3];
					break;
				}
				resetwords_bot_top();
				printw(print_iteam(5));
				pressenter();

				steroid(&horse[operation - 1], iteam_3, iteam_5);

				b_bought = 1;
			}
			//������ ���� ������
			else if (b_bought == 1)
			{
				printw(print_iteam(6));
				pressenter();
			}

			playmain = 1;
			break;
		case 3:

			//���� �ʱ�ȭ �ϱ�
			resetwords_bot_top();

			//�ʱ�ȭ Ȯ��

			if (total_bet != 0)
			{
				printw(print_reset(0));
				operation = input(1, 2);

				//�ʱ�ȭ ����
				resetwords_bot_top();
				if (operation == 1)
				{
					for (int i = 0; i < 5; i++)
					{
						money += horse[i].tot_bet;
						horse[i].bet = 0;
						horse[i].tot_bet = 0;
					}
					printw(print_reset(1));
					pressenter();
				}
				//�ʱ�ȭ ������
				else {
					printw(print_reset(2));
					pressenter();
				}
			}
			else
			{
				printw(print_reset(3));
				pressenter();
			}
			break;

		case 4:
			play_music("shop", 1);
			system("cls");
			printf("\n\n");
			printw(print_end(0));
			operation = input(1, 2);
			if (operation == 2)
			{
				playmain = 1;
				continue;
			}
			if (operation == 1)
			{
				system("cls");
				printf("\n\n");
				printw(print_end(1));
				operation = input(1, 2);
				if (operation == 2)
				{
					playmain = 1;
					continue;
				}
				if (operation == 1)
				{
					goodbye();
					end = 1;
				}
			}

			break;
		case 0:
			//��� ����
			play_music("race_music", 1);
			system("cls");
			printmoney();
			if (race_begin == 1)
			{
				printw(print_race(0));
				race_begin = 0;
			}
			else
				printf(print_race(0));
			inform_line();
			printf(print_bet(1));
			inform_line();

			for (int i = 0; i < 5; i++)
			{
				horseinform(horse[i]);
			}

			resetwords_top_bot();
			printw(print_race(1));
			operation = input(1, 2);
			if (operation == 2)
			{
				playmain = 1;
				continue;
			}

			//��� �ϱ�

			//��� ���� ����
			system("cls");
			b_start = 1;
			b_finish = 0;
			num_winner = 100;

			before_money = money;

			for (int i = 0; i < 5; i++)
			{
				horse[i].tot_steps = 0;
			}


			//��� �ݺ���
			while (1) {

				printmoney();



				srand(time(NULL));

				//�� ĭ�� ����������, �̵�
				for (int i = 0; i < 5; i++)
				{
					step[i] = rand_step(horse[i]);
					go_horse(&horse[i], step[i], b_start, &b_finish, &num_winner);
				}

				//��� ���� ���
				if (b_start == 1)
				{
					start_race();
					Sleep(500);
				}
				b_start = 0;

				if (b_finish == 1)
				{
					finish_race(horse[num_winner]);
					pressenter();
					printf("\n");
					break;
				}

				RESET;
			}

			//���� ���� ���
			DOWN;
			resetwords_bot_top();
			if (horse[num_winner].tot_bet == 0)
			{
				play_music("if_lose", 0);
				if_lose();
				pressenter();
			}
			else {
				//if wins ����
				play_music("race_win", 0);
				if_wins(horse[num_winner]);
				pressenter();
				//�� ���
				money += horse[num_winner].tot_bet * horse[num_winner].percent;
				//system("cls");
				RESET;
				printmoneyrace();
			}

			//�ʱ�ȭ
				//���� �ʱ�ȭ
			for (int i = 0; i < 5; i++)
			{
				horse[i].bet = 0;
				horse[i].tot_bet = 0;
			}

				//������ �ʱ�ȭ
			reset_horses(horse);
			total_bet = 0; //��ü���þ� �ʱ�ȭ
			playmain = 1;
			b_bought = 0;

			//��� �� ���� 0���̸�
			if (money == 0)
			{
				operation = game_over();
				if (operation == 1)
				{
					printw("\n\n\t\t\t\t\t\t\t�����ߵ����: 1336��");
					Sleep(1000);
					money = 5000;
					//begin = INTRO_SKIP * GM;
					//shopbegin = INTRO_SKIP * GM;
					//total_bet = INTRO_SKIP * GM;
					playmain = 1;
					continue;
				}
				else
				{
					goodbye();
					end = 1;
				}
			}
			system("cls");

			break;

		}
		if (money >= 300000)
		{
			play_music("clear_game", 0);
			game_clear();
			printw(print_general(2));
			Sleep(500);
			printw(print_general(3));
			Sleep(5000);
			system("cls");
			goodbye();
			end = 1;
		}
		if (end == 1) exit(1);
	}

	return 0;
}
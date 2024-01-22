#include "myheader.h"


/*
1. 什塘軒
2. 五敢
2-1. 井原 凧食, 壕雁 溌昔, 曽戟
2-1-1 井原凧食: 井原 識澱, 及稽亜奄
2-1-1-1 井原識澱: 壕特榎 隔奄, 井奄 遭楳
2-1-1-1-1 井奄 獣皇傾戚芝, 壕雁榎 呪昼
2-1 差瑛

井奄遭楳
1. 唖 原亜 蒋生稽 戚疑
2. 唖 原紺 鯵紺 溌懸稽 1,3,5, 哀走 照哀走 溌懸 糎仙
3. 0.5段拭 廃腰梢 穣汽戚闘
4. 3牒, 5牒亀 0.5段拭 坦軒背醤喫
5. 廃 原亜 衣渋識拭 亀鐸馬檎 井奄 魁

// 廃 原梢 崇送析 呪 赤製 -> 1腰採斗 託景企稽 崇送戚檎 照鞠艦 唖 原亜 旭戚 崇送戚揮亜, 焼艦檎 原亜 崇送戚澗 授辞亀 沓棋生稽 背醤敗


*/

int money=0;
int before_money=0;
char str[300];

int main()
{
	system("mode con: cols=100 lines=35"); //鉢檎 繕舛
	SetConsoleTitle(TEXT("Way To Signiel")); //嬬車 戚硯
	PlaySound(NULL, 0, 0); //製焦 仙持
	

	int begin = (INTRO_SKIP * GM); //坦製 獣拙獣 探探備 覗鍵闘, 蟹掻拭澗 益撹 壱舛(獣拙鉢檎)
	int shopbegin = INTRO_SKIP * GM;
	int bet_begin = INTRO_SKIP * GM;
	int race_begin = INTRO_SKIP * GM;
	int first_begin = INTRO_SKIP * GM;
	int end = 0;

	if (first_begin != 1)  money = START_MONEY; //GM乞球 獣 儀 竺舛

	//五敢 識澱 痕呪級
	int operation;

	//井原 井奄研 是廃 痕呪級
	struct horses horse[5];
	int step[5];
	int b_start;
	int b_finish;
	int num_winner;

	//原 室特   痕呪, 腰硲, 戚硯, 戚乞銅嬬, 1牒 溌懸, 3牒 溌懸, 5牒 溌懸, 壕雁晴
	reset_horses(horse);


	//壕雁榎 段奄鉢
	for (int i = 0; i < 5; i++)
	{
		horse[i].bet = 0;
		horse[i].tot_bet = 0;
	}

	//焼戚奴聖 是廃 痕呪級
	int iteam_num;
	int iteam_3;
	int iteam_5;
	int b_bought = 0;
	int price[4] = { 3000,5000,7000,10000 };

	//今特聖 是廃 痕呪級
	int total_bet = 0;
	int bet_horse;

	//製焦聖 是廃 痕呪級
	int playmain = 1; //1戚 巴傾戚

	//ししししししししし鋼差庚 獣拙ししししししししししし
	while (1)
	{
		if (begin == 1)
		{
			printstart();
		}
		system("cls");

		//惟績 竺誤 
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

		//坦製 鉢檎
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

		//企五敢 switch
		switch (operation)
		{
		case 1:
			//今特 鋼差庚
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

				printf("\t1. %s\t2. %s\t3. %s\t4. %s\t5. %s\n\n\t\t\t\t\t\t\t\t\t 0. 宜焼亜奄\n", \
					horse[0].name, horse[1].name, horse[2].name, horse[3].name, horse[4].name);

				operation = input(0, 5);
				if (operation == 0)break;

				//巴傾戚嬢亜 今特馬澗 原 腰硲
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
			//溌懸 焼戚奴 姥古 幻級奄
			//3牒 5%, 5牒 5% 3牒 10% 5牒 10%		//3探, 5探, 7探, 1常

			system("cls");
			printmoney();
			//鉢檎 窒径
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

			//焼戚奴 姥古 亜管
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

				//operation-1 = 源 腰硲 iteam_num = 焼戚奴
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
			//焼戚奴 姥古 梅生檎
			else if (b_bought == 1)
			{
				printw(print_iteam(6));
				pressenter();
			}

			playmain = 1;
			break;
		case 3:

			//今特 段奄鉢 馬奄
			resetwords_bot_top();

			//段奄鉢 溌昔

			if (total_bet != 0)
			{
				printw(print_reset(0));
				operation = input(1, 2);

				//段奄鉢 遭楳
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
				//段奄鉢 耕遭楳
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
			//井奄 珍鈍
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

			//井奄 馬奄

			//井奄 獣拙 室特
			system("cls");
			b_start = 1;
			b_finish = 0;
			num_winner = 100;

			before_money = money;

			for (int i = 0; i < 5; i++)
			{
				horse[i].tot_steps = 0;
			}


			//井奄 鋼差庚
			while (1) {

				printmoney();



				srand(time(NULL));

				//原 牒呪 沓棋宜軒奄, 戚疑
				for (int i = 0; i < 5; i++)
				{
					step[i] = rand_step(horse[i]);
					go_horse(&horse[i], step[i], b_start, &b_finish, &num_winner);
				}

				//井奄 獣拙 窒径
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

			//渋鳶 鎧遂 窒径
			DOWN;
			resetwords_bot_top();
			if (horse[num_winner].tot_bet == 0)
			{
				play_music("if_lose", 0);
				if_lose();
				pressenter();
			}
			else {
				//if wins 製焦
				play_music("race_win", 0);
				if_wins(horse[num_winner]);
				pressenter();
				//儀 域至
				money += horse[num_winner].tot_bet * horse[num_winner].percent;
				//system("cls");
				RESET;
				printmoneyrace();
			}

			//段奄鉢
				//壕雁榎 段奄鉢
			for (int i = 0; i < 5; i++)
			{
				horse[i].bet = 0;
				horse[i].tot_bet = 0;
			}

				//焼戚奴 段奄鉢
			reset_horses(horse);
			total_bet = 0; //穿端壕特衝 段奄鉢
			playmain = 1;
			b_bought = 0;

			//域至 板 儀戚 0据戚檎
			if (money == 0)
			{
				operation = game_over();
				if (operation == 1)
				{
					printw("\n\n\t\t\t\t\t\t\t亀酵掻偽雌眼: 1336腰");
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
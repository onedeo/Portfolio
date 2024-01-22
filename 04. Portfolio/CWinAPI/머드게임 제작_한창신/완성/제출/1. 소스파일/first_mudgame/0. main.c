#include "myheader.h"


/*
1. 스토리
2. 메뉴
2-1. 경마 참여, 배당 확인, 종료
2-1-1 경마참여: 경마 선택, 뒤로가기
2-1-1-1 경마선택: 배팅금 넣기, 경기 진행
2-1-1-1-1 경기 시뮬레이션, 배당금 수취
2-1 복귀

경기진행
1. 각 마가 앞으로 이동
2. 각 마별 개별 확률로 1,3,5, 갈지 안갈지 확률 존재
3. 0.5초에 한번씩 업데이트
4. 3칸, 5칸도 0.5초에 처리해야됨
5. 한 마가 결승선에 도착하면 경기 끝

// 한 마씩 움직일 수 있음 -> 1번부터 차례대로 움직이면 안되니 각 마가 같이 움직이던가, 아니면 마가 움직이는 순서도 랜덤으로 해야함


*/

int money=0;
int before_money=0;
char str[300];

int main()
{
	system("mode con: cols=100 lines=35"); //화면 조정
	SetConsoleTitle(TEXT("Way To Signiel")); //콘솔 이름
	PlaySound(NULL, 0, 0); //음악 재생
	

	int begin = (INTRO_SKIP * GM); //처음 시작시 천천히 프린트, 나중에는 그냥 고정(시작화면)
	int shopbegin = INTRO_SKIP * GM;
	int bet_begin = INTRO_SKIP * GM;
	int race_begin = INTRO_SKIP * GM;
	int first_begin = INTRO_SKIP * GM;
	int end = 0;

	if (first_begin != 1)  money = START_MONEY; //GM모드 시 돈 설정

	//메뉴 선택 변수들
	int operation;

	//경마 경기를 위한 변수들
	struct horses horse[5];
	int step[5];
	int b_start;
	int b_finish;
	int num_winner;

	//마 세팅   변수, 번호, 이름, 이모티콘, 1칸 확률, 3칸 확률, 5칸 확률, 배당율
	reset_horses(horse);


	//배당금 초기화
	for (int i = 0; i < 5; i++)
	{
		horse[i].bet = 0;
		horse[i].tot_bet = 0;
	}

	//아이템을 위한 변수들
	int iteam_num;
	int iteam_3;
	int iteam_5;
	int b_bought = 0;
	int price[4] = { 3000,5000,7000,10000 };

	//베팅을 위한 변수들
	int total_bet = 0;
	int bet_horse;

	//음악을 위한 변수들
	int playmain = 1; //1이 플레이

	//ㅇㅇㅇㅇㅇㅇㅇㅇㅇ반복문 시작ㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇ
	while (1)
	{
		if (begin == 1)
		{
			printstart();
		}
		system("cls");

		//게임 설명 
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

		//처음 화면
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

		//대메뉴 switch
		switch (operation)
		{
		case 1:
			//베팅 반복문
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

				printf("\t1. %s\t2. %s\t3. %s\t4. %s\t5. %s\n\n\t\t\t\t\t\t\t\t\t 0. 돌아가기\n", \
					horse[0].name, horse[1].name, horse[2].name, horse[3].name, horse[4].name);

				operation = input(0, 5);
				if (operation == 0)break;

				//플레이어가 베팅하는 마 번호
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
			//확률 아이템 구매 만들기
			//3칸 5%, 5칸 5% 3칸 10% 5칸 10%		//3천, 5천, 7천, 1억

			system("cls");
			printmoney();
			//화면 출력
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

			//아이템 구매 가능
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

				//operation-1 = 말 번호 iteam_num = 아이템
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
			//아이템 구매 했으면
			else if (b_bought == 1)
			{
				printw(print_iteam(6));
				pressenter();
			}

			playmain = 1;
			break;
		case 3:

			//베팅 초기화 하기
			resetwords_bot_top();

			//초기화 확인

			if (total_bet != 0)
			{
				printw(print_reset(0));
				operation = input(1, 2);

				//초기화 진행
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
				//초기화 미진행
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
			//경기 컨펌
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

			//경기 하기

			//경기 시작 세팅
			system("cls");
			b_start = 1;
			b_finish = 0;
			num_winner = 100;

			before_money = money;

			for (int i = 0; i < 5; i++)
			{
				horse[i].tot_steps = 0;
			}


			//경기 반복문
			while (1) {

				printmoney();



				srand(time(NULL));

				//마 칸수 랜덤돌리기, 이동
				for (int i = 0; i < 5; i++)
				{
					step[i] = rand_step(horse[i]);
					go_horse(&horse[i], step[i], b_start, &b_finish, &num_winner);
				}

				//경기 시작 출력
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

			//승패 내용 출력
			DOWN;
			resetwords_bot_top();
			if (horse[num_winner].tot_bet == 0)
			{
				play_music("if_lose", 0);
				if_lose();
				pressenter();
			}
			else {
				//if wins 음악
				play_music("race_win", 0);
				if_wins(horse[num_winner]);
				pressenter();
				//돈 계산
				money += horse[num_winner].tot_bet * horse[num_winner].percent;
				//system("cls");
				RESET;
				printmoneyrace();
			}

			//초기화
				//배당금 초기화
			for (int i = 0; i < 5; i++)
			{
				horse[i].bet = 0;
				horse[i].tot_bet = 0;
			}

				//아이템 초기화
			reset_horses(horse);
			total_bet = 0; //전체배팅액 초기화
			playmain = 1;
			b_bought = 0;

			//계산 후 돈이 0원이면
			if (money == 0)
			{
				operation = game_over();
				if (operation == 1)
				{
					printw("\n\n\t\t\t\t\t\t\t도박중독상담: 1336번");
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
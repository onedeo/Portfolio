#include "myheader.h"


//출력 함수 (글자 X, 라인, 지우기 등)
void resetwords_top_bot()
{
	box_line();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < DIST * 2; j++) {
			printf(" ");
		}
		DOWN;
	}
	box_line();

	for (int i = 0; i < 6; i++)
	{
		UP;
	}
}

void resetwords_bot_top()
{
	for (int i = 0; i < 8; i++)
	{
		UP;
	}
	box_line();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < DIST * 2; j++) {
			printf(" ");
		}
		DOWN;
	}
	UP;
	box_line();
	for (int i = 0; i < 6; i++)
	{
		UP;
	}

}

void box_line()
{
	printf("\033[0m\n");
	for (int i = 0; i < DIST * 2; i++)
	{
		printf("=");
	}
	DOWN;
}

void printw(char* input)
{
	char str[500];
	strcpy(str, input);

	for (int i = 0; i < strlen(str); i++)
	{
		putchar(str[i]);
		Sleep(WORD_SPEED);
	}
}


//출력 함수 (글자)
void pressenter()
{
	char* str = "press enter";

	for (int i = 0; i < DIST * 2 - strlen(str)-10; i++)
	{
		printf(" ");
	}
	printf("%s", str);
	_getch();
}

void printmoney()
{
	box_line();
	printf("\t목표:\033[33m %d억원\t\t \033[0m현재: \033[33m%d억 %d만원\t\t\033[0m잔액: \033[33m%d억 %d만원\033[0m",\
	get_uk(TARGET_MONEY), get_uk(money), get_man(money), get_uk(TARGET_MONEY - money), get_man(TARGET_MONEY-money));

	box_line();
	DOWN;
}

void goodbye()
{
	char* str = "\t\t최고의 주사위 던지기는\n\t\t\t주사위를 통에 그냥 넣어두는 것이다.\n\n\n\t\t\t\t감사합니다. 제작자. 한창신.";
	system("cls");
	for (int i = 0; i < 5; i++) DOWN;
	for (int i = 0; i < strlen(str); i++)
	{
		putchar(str[i]);
		Sleep(70);
	}
	Sleep(3000);
}

void printstart()
{
	FILE* fp;
	char str[8][100] = { 0 };

	play_music("opening", 1);

	fp = fopen("text.txt", "r");
	if (fp == 0)
	{
		printf("text.txt 열기 실패");
		exit(1);
	}
	
	system("cls");
		for (int i = 0; i < 8; i++) //str배열에 8줄 문자열 정의
		{
			fgets(str[i], 100, fp);
		}

		for (int i = 0; i < 100; i++) //총 열의 개수
		{
			for (int k = 0; k < 8; k++)	//총 행의 개수
			{
				for (int j = 0; j < i; j++) //출력할 행의 개수 ==> 전체 행을 0 -> 0~1 -> 0~2 -> 0~3... 출력
				{
					if (k == 3 && str[k][j] == '-') printf("\033[33m%c", str[k][j]);
					else printf("\033[0m%c", str[k][j]);

				}
				if (i < strlen(str[k])) DOWN;
			}


			for (int j = 0; j < 8; j++)
			{
				UP;
			}

			Sleep(10);
		}

		for (int i = 0; i < 8; i++)
		{
			DOWN;
		}

		for (int i = 0; i < 6; i++)
		{
			fgets(str[i], 100, fp);
		}
		for (int i = 0; i < 100; i++)
		{
			for (int k = 0; k < 6; k++)
			{
				for (int j = 0; j < i; j++)
				{
					if (k == 3 && str[k][j] == '-') printf("\033[33m%c", str[k][j]);
					else printf("\033[0m%c", str[k][j]);
				}
				if (i < strlen(str[k])) DOWN;
			}


			for (int j = 0; j < 6; j++)
			{
				UP;
			}

			Sleep(10);
		}

		for (int i = 0; i < 12; i++)
		{
			DOWN;
		}
	printf("\t\t\t\t\t\t\t\t\t\t   제작. 한창신");
	Sleep(3000);
	printf("\n\n\n\n");
	{
		char* str = "\033[90mㅡ press enter to start ㅡ";

		for (int i = 0; i < DIST+18 - strlen(str); i++)
		{
			printf(" ");
		}
		printf("%s", str);
		_getch();
	}
	fclose(fp);
	
}


//입력 함수
int input(int min, int max)
{
	int operation;

	printf("\n");
	while (1)
	{
		printf("\t입력: ");

		scanf("%d", &operation);

		if (operation >= min && operation <= max)
		{
			DOWN;
			break;
		}
		else
		{
			DOWN;
			printf("                                 \r");
		}
	}
	
	return operation;
}


//돈 변환 함수
int get_uk(int money)
{
	if (money / 10000 >= 1)
	{
		return (money / 10000);
	}
	return 0;
}

int get_man(int money)
{
		return money % 10000;
}


//게임 종료
void game_clear()
{
	FILE* fp;
	char str[18][100] = { 0 };

	system("cls");

	fp = fopen("building.txt", "r");
	if (fp == 0)
	{
		printf("text.txt 열기 실패");
		exit(1);
	}

	for (int i = 0; i < 18; i++)
	{
		fgets(str[i], 100, fp);
	}

	for(int i=0; i<18;i++)
	{
		printf("%s", str[i]);

		Sleep(250);
	}
	Sleep(1000);
	printf("\n\n");


}

int game_over()
{
	int operation;
	system("cls");
	Sleep(1000);
	PlaySound(TEXT("D:\\HCS\\2023\\first_mudgame\\first_mudgame\\music\\gameover"), NULL, SND_FILENAME | SND_ASYNC);
	printw("\n\n\n\n\t.... 당신은 모든 돈을 잃으셔서 창신경마장에서 쫓겨나셨습니다.\n\t\t\t\t\t\t플레이해주셔서 감사합니다.\n\n\n");
	Sleep(3000);
	printw("\t\t다시 플레이 하시겠습니까?\n\n\t1. 네\n\t2.아니요\n");

	operation = input(1, 2);
	Sleep(2000);

	return operation;
}


//음악 재생
void play_music(const char* file_name, int b_loop)
{
	char path[100] = { 0 };
	strcpy(path, MUSIC_PATH);
	strcat(path, file_name);
	strcat(path, ".wav");

	int len = strlen(path) + 1;
	int size = MultiByteToWideChar(CP_UTF8, 0, path, len, NULL, 0);
	wchar_t* w_path = (wchar_t*)malloc(size * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, path, len, w_path, size);

	if(b_loop==0)
	PlaySound(w_path, NULL, SND_FILENAME | SND_ASYNC);
	else if(b_loop==1)
	PlaySound(w_path, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}




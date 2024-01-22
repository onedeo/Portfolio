#include "myheader.h"


//��� �Լ� (���� X, ����, ����� ��)
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


//��� �Լ� (����)
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
	printf("\t��ǥ:\033[33m %d���\t\t \033[0m����: \033[33m%d�� %d����\t\t\033[0m�ܾ�: \033[33m%d�� %d����\033[0m",\
	get_uk(TARGET_MONEY), get_uk(money), get_man(money), get_uk(TARGET_MONEY - money), get_man(TARGET_MONEY-money));

	box_line();
	DOWN;
}

void goodbye()
{
	char* str = "\t\t�ְ��� �ֻ��� �������\n\t\t\t�ֻ����� �뿡 �׳� �־�δ� ���̴�.\n\n\n\t\t\t\t�����մϴ�. ������. ��â��.";
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
		printf("text.txt ���� ����");
		exit(1);
	}
	
	system("cls");
		for (int i = 0; i < 8; i++) //str�迭�� 8�� ���ڿ� ����
		{
			fgets(str[i], 100, fp);
		}

		for (int i = 0; i < 100; i++) //�� ���� ����
		{
			for (int k = 0; k < 8; k++)	//�� ���� ����
			{
				for (int j = 0; j < i; j++) //����� ���� ���� ==> ��ü ���� 0 -> 0~1 -> 0~2 -> 0~3... ���
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
	printf("\t\t\t\t\t\t\t\t\t\t   ����. ��â��");
	Sleep(3000);
	printf("\n\n\n\n");
	{
		char* str = "\033[90m�� press enter to start ��";

		for (int i = 0; i < DIST+18 - strlen(str); i++)
		{
			printf(" ");
		}
		printf("%s", str);
		_getch();
	}
	fclose(fp);
	
}


//�Է� �Լ�
int input(int min, int max)
{
	int operation;

	printf("\n");
	while (1)
	{
		printf("\t�Է�: ");

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


//�� ��ȯ �Լ�
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


//���� ����
void game_clear()
{
	FILE* fp;
	char str[18][100] = { 0 };

	system("cls");

	fp = fopen("building.txt", "r");
	if (fp == 0)
	{
		printf("text.txt ���� ����");
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
	printw("\n\n\n\n\t.... ����� ��� ���� �����ż� â�Ű渶�忡�� �Ѱܳ��̽��ϴ�.\n\t\t\t\t\t\t�÷������ּż� �����մϴ�.\n\n\n");
	Sleep(3000);
	printw("\t\t�ٽ� �÷��� �Ͻðڽ��ϱ�?\n\n\t1. ��\n\t2.�ƴϿ�\n");

	operation = input(1, 2);
	Sleep(2000);

	return operation;
}


//���� ���
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




#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

//GM ����
#define GM 1									//0�̸� ������, 1�̸� ��������

//���� ���� ��ġ
#define MUSIC_PATH "music\\"

#define INTRO_SKIP 1					//�⺻ 0		//ó�� ���� ���� ���� ���� 0: ����, 1: ����
#define DIST 50							//�⺻ 50		//�渶 �Ÿ�(Ư�����ڷ� ���� 100)���� �����
#define SEC_STEP 70						//�⺻ 70		//�渶 ������Ʈ �ӵ� (��� �ð� �¿�)
#define WORD_SPEED 20					//�⺻ 20		//���ڿ� ��� �ӵ� (�ѱ��ھ� ��� �ӵ�)

//��� ����
	//RACE
#define PATH printf("\033[0m��")			//�渶�� ���� �Ȱ� �� ����
#define PASSED printf("\033[0m��")			//�渶�� ���� �� ����

	//�� ����
#define RESET printf("\033[1;1H")
#define DOWN printf("\n")
#define UP printf("\033[F")

//���� ����, ��ǥ �ݾ� ����
#define START_MONEY 5000
#define TARGET_MONEY 300000

//�������� ����
extern money;
extern before_money;
extern char str[300];

//�� ����ü ����
struct horses {
	int num;
	char* name;
	char imo[5];	//�渶 �ùķ��̼� �� ��� �� �� ������
	int per_1;		//Nĭ �� Ȯ��
	int per_3;
	int per_5;
	int tot_steps;
	int percent;	//�����
	int bet;
	int tot_bet;
};

//1. general_functions -> �Ϲ����� �Լ��� (���������� ���Ǵ� �Լ�)
	//��� �Լ� (���� X, ����, ����� ��)

void resetwords_top_bot(); //==���� �� ����� �Լ� (������ �Ʒ���)
void resetwords_bot_top(); // ���� �� ����� �Լ� (�Ʒ����� ����(���� ����� �ٽ� ����))

void box_line(); //==���� �Լ�
void printw(const char* input);

void play_music(const char* file_name, int b_loop); //���� ��� �Լ�

	//��� �Լ� (����)

void pressanyenter();
void printmoney(); // ��� �ݾ� ���
void goodbye();
void printstart();

	//�Է� �Լ�

int input(int min, int max); //scanf �ϴ� �Լ�

	//�� ��ȯ �Լ�

int get_uk(int money); //����� ��ȯ
int get_man(int money); //õ���� ��ȯ

	//���� ����
void game_clear();
int game_over();


//2. race_functions -> �� ��⿡�� ���Ǵ� �Լ�

	//��� (����X)

void set_horses(struct horses* horse, int num, const char* name, const char* imo, int per1, int per3, int per5, int bet);
void reset_horses(struct horses* horse);
int rand_step(struct horses horse);
void go_horse(struct horses* horse, int step, int start, int* finish, int* winner);

	//��� (����)

void start_race(); //��� ���� ��� �Լ�
void finish_race(struct horses horse); //��� ���� ��� �Լ�
void printmoneyrace(); //��� ���� �� �� �ö󰡴°� �����ִ� �Լ�
void if_wins(struct horses horse);
void if_lose();


//3. bet_functions -> ���� �ݾ� �Է½� ���Ǵ� �Լ�
void ask_bet(struct horses horse);
void bet_input(struct horses* horse);
void inform_line();
void horseinform(struct horses horse);	 //race������ ���

//4. iteam_functions -> ������ ���� �� ���Ǵ� �Լ�
void steroid(struct horses* horse, int per_3, int per_5);

//5. prints -> ��� ���ڵ�
char* print_general(int num);
char* print_race(int num);
char* print_bet(int num);
char* print_iteam(int num);
char* print_reset(int num);
char* print_end(int num);
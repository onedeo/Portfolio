#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

//GM 설정
#define GM 1									//0이면 빠르게, 1이면 정상으로

//음악 폴더 위치
#define MUSIC_PATH "music\\"

#define INTRO_SKIP 1					//기본 0		//처음 시작 내용 생략 설정 0: 생략, 1: 포함
#define DIST 50							//기본 50		//경마 거리(특수문자로 인해 100)으로 보면됨
#define SEC_STEP 70						//기본 70		//경마 업데이트 속도 (경기 시간 좌우)
#define WORD_SPEED 20					//기본 20		//문자열 출력 속도 (한글자씩 출력 속도)

//출력 내용
	//RACE
#define PATH printf("\033[0mㅡ")			//경마가 아직 안간 길 문자
#define PASSED printf("\033[0m□")			//경마가 지난 길 문자

	//줄 설정
#define RESET printf("\033[1;1H")
#define DOWN printf("\n")
#define UP printf("\033[F")

//게임 시작, 목표 금액 설정
#define START_MONEY 5000
#define TARGET_MONEY 300000

//전역변수 선언
extern money;
extern before_money;
extern char str[300];

//마 구조체 선언
struct horses {
	int num;
	char* name;
	char imo[5];	//경마 시뮬레이션 시 출력 될 마 아이콘
	int per_1;		//N칸 갈 확률
	int per_3;
	int per_5;
	int tot_steps;
	int percent;	//배당율
	int bet;
	int tot_bet;
};

//1. general_functions -> 일반적인 함수들 (전반적으로 사용되는 함수)
	//출력 함수 (글자 X, 라인, 지우기 등)

void resetwords_top_bot(); //==라인 외 지우는 함수 (위에서 아래로)
void resetwords_bot_top(); // 라인 외 지우는 함수 (아래에서 위로(문자 지우고 다시 문자))

void box_line(); //==라인 함수
void printw(const char* input);

void play_music(const char* file_name, int b_loop); //음악 출력 함수

	//출력 함수 (글자)

void pressanyenter();
void printmoney(); // 상단 금액 출력
void goodbye();
void printstart();

	//입력 함수

int input(int min, int max); //scanf 하는 함수

	//돈 변환 함수

int get_uk(int money); //억단위 변환
int get_man(int money); //천단위 변환

	//게임 종료
void game_clear();
int game_over();


//2. race_functions -> 마 경기에서 사용되는 함수

	//경기 (글자X)

void set_horses(struct horses* horse, int num, const char* name, const char* imo, int per1, int per3, int per5, int bet);
void reset_horses(struct horses* horse);
int rand_step(struct horses horse);
void go_horse(struct horses* horse, int step, int start, int* finish, int* winner);

	//경기 (글자)

void start_race(); //경기 시작 출력 함수
void finish_race(struct horses horse); //경기 종료 출력 함수
void printmoneyrace(); //경기 종료 후 돈 올라가는거 보여주는 함수
void if_wins(struct horses horse);
void if_lose();


//3. bet_functions -> 베팅 금액 입력시 사용되는 함수
void ask_bet(struct horses horse);
void bet_input(struct horses* horse);
void inform_line();
void horseinform(struct horses horse);	 //race에서도 사용

//4. iteam_functions -> 아이템 구매 시 사용되는 함수
void steroid(struct horses* horse, int per_3, int per_5);

//5. prints -> 출력 문자들
char* print_general(int num);
char* print_race(int num);
char* print_bet(int num);
char* print_iteam(int num);
char* print_reset(int num);
char* print_end(int num);
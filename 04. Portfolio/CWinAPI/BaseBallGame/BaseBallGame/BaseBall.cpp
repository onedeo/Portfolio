#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//야구게임
	/*
	3개의 숫자를 입력 받아서 다음과 같이 숫자가 있지만 그 위치가 틀렸을 때는 n ball 출력
	숫자와 위치가 맞으면 n strike 출력
	숫자와 위치가 전부 틀리면 out 출력
	무엇이 볼이고 스트라이크 인지는 출력x
	세 개의 숫자와 위치가 다 맞으면 homerun 출력, quit;
	*/

int main()
{
	srand(time(NULL));

	int len = 0;
	int target[3];
	int same;
	int input[3];


	//target 배열 숫자 배치
	//0이거나 같으면 안됨
	while (len != 3)
	{
		same = 0;
		target[len] = rand() % 9;
		if (target[len] == 0) continue;
		for (int i = len - 1; 0 <= i; i--)
		{
			if (target[len] == target[i])
			{
				same = 1;
				break;
			}
		}
		if (same == 1) continue;
		len++;
	}

	//게임 시작
	while (1)
	{
		int num = 0;
		int ball = 0;
		int strike = 0;

		printf("1~9 정수\n");

		while (num != 3)
		{
			int ball = 0;
			int strike = 0;

			printf("%d번 입력:", num + 1);
			scanf_s("%d", input + num);


			if (input[num] > 9 || input[num] < 1)
			{
				printf("1~9 정수\n");
				continue; //9보다 크던가 1보다 작으면 다시 while 시작
			}

			//0~2까지의 번호가 있다면, 0번 입력시 1~9인지만 확인
			//1번 입력시 0과 동일한지, 1~9인지 확인
			//2번 입력시 0이나 1과 동일한지, 1~9인지 확인
			same = 0;
			for (int i = num - 1; 0 <= i; i--)
			{
				if (input[num] == input[i])
				{
					printf("같은 숫자가 있습니다.\n");
					same = 1;
					break;
				}
			}
			if (same == 1) continue;
			num++;
		}
		num = 0;

		//맞는지 다른지 확인 (i와 j와 비교)
		// i와 j가 맞다면 strike
		// i와 j가 다르다면 ball

		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < len; j++)
			{
				if (input[i] == target[j])
				{
					if (i == j)
					{
						strike++;
						break;
					}
					else
					{
						ball++;
						break;
					}
				}
			}
		}

		if (strike + ball == 0) printf("!!! OUT !!!\n\n\n");
		else if (strike == 3)
		{
			printf("!!! HOME RUN !!!\n\n\n");
			break;
		}
		else printf("!! %d STRIKE !! %d BALL !!\n\n\n", strike, ball);
	}
	printf("%d%d%d", target[0], target[1], target[2]);

}
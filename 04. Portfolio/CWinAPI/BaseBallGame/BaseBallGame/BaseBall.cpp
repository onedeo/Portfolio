#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//�߱�����
	/*
	3���� ���ڸ� �Է� �޾Ƽ� ������ ���� ���ڰ� ������ �� ��ġ�� Ʋ���� ���� n ball ���
	���ڿ� ��ġ�� ������ n strike ���
	���ڿ� ��ġ�� ���� Ʋ���� out ���
	������ ���̰� ��Ʈ����ũ ������ ���x
	�� ���� ���ڿ� ��ġ�� �� ������ homerun ���, quit;
	*/

int main()
{
	srand(time(NULL));

	int len = 0;
	int target[3];
	int same;
	int input[3];


	//target �迭 ���� ��ġ
	//0�̰ų� ������ �ȵ�
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

	//���� ����
	while (1)
	{
		int num = 0;
		int ball = 0;
		int strike = 0;

		printf("1~9 ����\n");

		while (num != 3)
		{
			int ball = 0;
			int strike = 0;

			printf("%d�� �Է�:", num + 1);
			scanf_s("%d", input + num);


			if (input[num] > 9 || input[num] < 1)
			{
				printf("1~9 ����\n");
				continue; //9���� ũ���� 1���� ������ �ٽ� while ����
			}

			//0~2������ ��ȣ�� �ִٸ�, 0�� �Է½� 1~9������ Ȯ��
			//1�� �Է½� 0�� ��������, 1~9���� Ȯ��
			//2�� �Է½� 0�̳� 1�� ��������, 1~9���� Ȯ��
			same = 0;
			for (int i = num - 1; 0 <= i; i--)
			{
				if (input[num] == input[i])
				{
					printf("���� ���ڰ� �ֽ��ϴ�.\n");
					same = 1;
					break;
				}
			}
			if (same == 1) continue;
			num++;
		}
		num = 0;

		//�´��� �ٸ��� Ȯ�� (i�� j�� ��)
		// i�� j�� �´ٸ� strike
		// i�� j�� �ٸ��ٸ� ball

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
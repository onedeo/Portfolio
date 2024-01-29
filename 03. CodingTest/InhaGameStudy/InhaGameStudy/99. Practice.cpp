#include <iostream>
#include <queue>

using namespace std;

int tomato[1000][1000];

int main()
{
    cin.tie(0);
	ios::sync_with_stdio(0);

	int y, x;
	cin >> y >> x;
	queue<pair<int, int>> que;
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			cin >> tomato[i][j];
			if (tomato[i][j] == 1)
			{
				que.push({ i,j });
			}
		}
	}
	que.push({ -5,-5 });

	int _y[4] = { 0,0,1,-1 };
	int _x[4] = { 1,-1,0,0 };
	int days = 0;
	while (!que.empty())
	{
		//-5: next day, -1 : tomato cant go, 0 : unfinished tomat, 1 : finished tomato
		int crntY = que.front().first;
		int crntX = que.front().second;
		que.pop();
		if (crntY == -5 && crntX == -5)
		{
			days++;
			if (que.empty()) break;
			que.push({ -5, -5 });
			continue;
		}
		for (int i = 0; i < 4; i++)
		{
			int newY = crntY + _y[i];
			int newX = crntX + _x[i];
			if (newY < 0 || newX < 0) continue;
			if (newY >= y || newX >= x) continue;
			if (tomato[newY][newX] != 0) continue;

			tomato[newY][newX] = 1;
			que.push({ newY, newX });
		}

	}

	cout << days;

	return 0;
}
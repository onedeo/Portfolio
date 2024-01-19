#include <iostream>
#include <queue>

using namespace std;

int main()
{
	int y, x, num;
	cin >> y >> x;

	int map[500][500];
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
			cin >> map[i][j];
	}
	
	int _y[4] = { -1, 1, 0, 0 };
	int _x[4] = { 0, 0, -1, 1 };

	int total = 0;
	int size = 0;
	int maxSize = 0;
	int crntX, crntY;

	queue<pair<int, int>> que;
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (map[i][j] == 0 || map[i][j] == -1) continue;
			que.push(make_pair(i, j));
			size = 0;
			while (!que.empty())
			{
				size++;
				crntY = que.front().first;
				crntX = que.front().second;
				map[crntY][crntX] = -1;
				que.pop();
				for (int k = 0; k < 4; k++)
				{
					int newY = crntY + _y[k];
					int newX = crntX + _x[k];
					if (newX < 0 || newY < 0) continue;
					if (newX >= x || newY >= y) continue;
					if (map[newY][newX] != 1) continue;
					
					map[newY][newX] = -1;
					que.push(make_pair(newY, newX));
				}
			}
			total++;
			if (maxSize < size) maxSize = size;
		}
	}

	cout << total << "\n" << maxSize;
	
	

	return 0;
}
#include <iostream>
#include <queue>

using namespace std;
#define Y first
#define X second
char maze[1000][1000];

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);

	int y, x;
	queue<pair<int, int>> player;
	queue<pair<int, int>> fire;
	cin >> y >> x;

	bool succssed = false;
	bool finished = false;
	int steps = 0;

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			cin >> maze[i][j];
			if (maze[i][j] == 'J')
				player.push(make_pair(i, j));
			else if (maze[i][j] == 'F')
				fire.push(make_pair(i, j));
		}
	}
	if (player.front().Y == 0 || player.front().X == 0)
	{
		finished = true;
		succssed = true;
	}
	player.push(make_pair(-1, -1));
	fire.push(make_pair(-1, -1));

	int _y[4] = { 0,0,-1,1 };
	int _x[4] = { 1,-1,0,0 };

	
	while (!finished)
	{
		// >> : FIRE
		while (true)
		{
			if (fire.empty()) break;
			pair<int, int> tempFire = fire.front();
			fire.pop();
			if (tempFire.Y == -1)
			{
				fire.push(make_pair(-1, -1));
				break;
			}
			for (int i = 0; i < 4; i++)
			{
				int newY = tempFire.Y + _y[i];
				int newX = tempFire.X + _x[i];
				if (newY < 0 || newX < 0) continue;
				if (newY >= y || newX >= x) continue;
				if (maze[newY][newX] == 'P' || maze[newY][newX] == '#' || maze[newY][newX] == 'J' || maze[newY][newX] == 'F') continue;
				
				maze[newY][newX] = 'F';
				fire.push(make_pair(newY, newX));
			}
		}
		// << : FIRE

		// >> : Player
		steps++;
		while(true)
		{
			if (player.empty())
			{
				cout << "IMPOSSIBLE";
				return 0;
			}
			pair<int, int> tempPlayer = player.front();
			player.pop();
			if (tempPlayer.Y == -1)
			{
				player.push(make_pair(-1, -1));
				break;
			}
			maze[tempPlayer.Y][tempPlayer.X] = 'P';
			for (int i = 0; i < 4; i++)
			{
				int newY = tempPlayer.Y + _y[i];
				int newX = tempPlayer.X + _x[i];
				if (newY < 0 || newX < 0) continue;
				if (maze[newY][newX] == 'P' || maze[newY][newX] == '#' || maze[newY][newX] == 'F') continue;
				if (newY == y-1 || newX == x-1 || newY==0||newX==0)
				{
					cout << steps + 1;
					return 0;
				}
				maze[newY][newX] = 'J';
				player.push(make_pair(newY, newX));
			}
		}
		// << : Player
	}
	


	return 0;
}
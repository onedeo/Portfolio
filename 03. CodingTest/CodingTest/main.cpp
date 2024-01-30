#include <iostream>
#include <utility>
#include <queue>
#define Y first
#define X second

int main()
{
    using namespace std;
    ios::sync_with_stdio(0);
    cin.tie(0);

    int boardY, boardX;
    cin >> boardX >> boardY;
    cin.ignore();

    int addY[4] = { 0,-1,0,1 };
    int addX[4] = { -1,0,1,0 };

    int** board = new int* [boardY];
    for (int i = 0; i < boardY; i++)
        board[i] = new int[boardX] {};

    int** count = new int* [boardY];
    for (int i = 0; i < boardY; i++)
        count[i] = new int[boardX] {};

    queue<pair<int, int>> tomato;
    for (int i = 0; i < boardY; i++)
    {
        for (int j = 0; j < boardX; j++)
        {
            cin >> board[i][j];
            cin.ignore();
            if (board[i][j] == 1)
            {
                tomato.push({ i,j });
                count[i][j] = 1;
            }
            if (board[i][j] == 0)
                count[i][j] = -1;
            if (board[i][j] == -1)
                count[i][j] = 0;
        }
    }

    for (int i = 0; i < boardY; i++)
    {
        for (int j = 0; j < boardX; j++)
        {
            while (!tomato.empty())
            {
                auto crnt = tomato.front();
                tomato.pop();
                for (int k = 0; k < 4; k++)
                {
                    int ny = addY[k] + crnt.Y;
                    int nx = addX[k] + crnt.X;
                    if (ny < 0 || nx < 0 || ny >= boardY || nx >= boardX) continue;
                    if (count[ny][nx] >= 0) continue;
                    count[ny][nx] = count[crnt.Y][crnt.X] + 1;
                    tomato.push({ ny,nx });
                }
            }
        }
    }
    int max = 0;
    for (int i = 0; i < boardY; i++)
    {
        for (int j = 0; j < boardX; j++)
        {
            if (count[i][j] == -1)
            {
                cout << -1;
                return 0;
            }
            if (count[i][j] > max)
            {
                max = count[i][j];
            }
        }
    }
    cout << max-1;


    return 0;
}
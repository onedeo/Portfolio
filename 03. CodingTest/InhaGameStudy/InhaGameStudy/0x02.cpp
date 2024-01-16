#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);

	int n, num;
	cin >> n;
	string oper;
	queue<int> que;
	queue<int> ans;
	for (int i = 0; i < n; i++)
	{
		cin >> oper;
		if (oper == "push")
		{
			cin >> num;
			que.push(num);
		}
		else if (oper == "pop")
		{
			if (que.empty()) ans.push(-1);
			else
			{
				ans.push(que.front());
				que.pop();
			}
		}
		else if (oper == "size")
		{
			ans.push(que.size());
		}
		else if (oper == "empty")
		{
			ans.push(que.empty());
		}
		else if (oper == "front")
		{
			if (que.empty()) ans.push(-1);
			else ans.push(que.front());
		}
		else if (oper == "back")
		{
			if (que.empty()) ans.push(-1);
			else ans.push(que.back());
		}
	}

	while (!ans.empty())
	{
		cout << ans.front()<<"\n";
		ans.pop();
	}
}
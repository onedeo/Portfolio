#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);

	string str;
	cin >> str;
	int popCount = 0;
	int ans = 0;
	
	stack<char> stk;
	for (int i = 0; i < str.size(); i++)
	{
		if (stk.empty())
		{
			if (popCount > 1)
			{
				ans += popCount;
				popCount = 0;
			}
		}
		if (str[i] == '(')
			stk.push(str[i]);
		else
		{
			stk.pop();
			popCount++;
		}		
	}
	if (popCount > 1)
	{
		ans += popCount;
		popCount = 0;
	}
	cout << ans;
	
	return 0;
}
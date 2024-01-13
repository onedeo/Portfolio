#include <iostream>
#include <stack>

using namespace std;

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);

	stack<int> stk;
	int n, ht;
	int max;
	cin >> n;
	int sum = n - 1;
	while (n--)
	{
		cin >> ht;
		if (stk.empty())
		{
			stk.push(ht);
			max = ht;
		}
		else if (max < ht)
		{
			sum += stk.size() - 1;
			while (!stk.empty()) stk.pop();
			max = ht;
			stk.push(ht);
		}
		else stk.push(ht);
	}
	sum += stk.size() - 1;
	sum--;

	cout << sum;


	return 0;
}
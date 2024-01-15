#include <iostream>
#include <string>

using namespace std;

int main()
{
	int* dat, * ans;
	int n, num;
	cin >> n;
	dat = new int[n];
	ans = new int[n];
	int head = 0;
	int tail = 0;

	string oper;
	int i = 0;
	while (n--)
	{
		cin >> oper;
		if (oper == "push")
		{
			cin >> num;
			dat[tail++] = num;
		}
		else if (oper == "pop")
		{
			if (head < tail)
			{
				ans[i++] = dat[head];
				head++;
			}
			else ans[i++] = -1;
		}
		else if (oper == "size")
		{
			ans[i++] = tail - head;
		}
		else if (oper == "empty")
		{
			if (tail - head == 0) ans[i++] = 1;
			else ans[i++] = 0;
		}
		else if (oper == "front")
		{
			if (head != tail)
				ans[i++] = dat[head];
			else ans[i++] = -1;
		}
		else if (oper == "back")
		{
			if(head!=tail)
			ans[i++] = dat[tail-1];
			else ans[i++] = -1;
		}
	}

	for (int j = 0; j < i; j++)
	{
		cout << ans[j]<<"\n";
	}

	delete[] dat;
	delete[] ans;

	return 0;
}
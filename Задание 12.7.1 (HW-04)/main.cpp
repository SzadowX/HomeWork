#include <iostream>
using namespace std;

bool IsKPeriodic(const string& str, int K)
{
	if (str.length() % K != 0)
		return false;
	for (int i = 0; i < str.length(); i += K)
	{
		if (str.substr(i, K) != str.substr(0, K))
			return false;
	}
	return true;
}

int main()
{
    setlocale(LC_ALL, "");

	string input;
	cout << "Введите строку: \n";
	cin >> input;
	int K;
	cout << "Введите число K: \n";
	cin >> K;
	if (IsKPeriodic(input,K))
	{
		cout << "Строка кратна числу K \n";
	}
	else
	{
		cout << "Строка не кратна числу K \n";
	}
	return 0;
}
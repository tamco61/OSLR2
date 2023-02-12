#include <iostream>

using namespace std;

int main()
{
	float num;
	float sum = 0;
	int n = 0;

	while (cin >> num)
	{
		n += 1;
		if ((n % 3) == 0)
		{  
			sum += num;
			cout << sum << endl;
			sum = 0;
		}
		else
		{
			sum += num;
		}
	}


}
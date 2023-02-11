#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>

using namespace std;

int main()
{
	int fd[2];

	if (pipe(fd) == -1)
	{
		cout << "pipe error" << endl;

		return -1;
	}

	char* filename;
	cin >> filename;
	int file = open(filename, O_RDWR | O_CREAT, 0777)
	
	int id = fork();
    cout << "1";
	if (id == -1)
	{
		cout << "fork error" << endl;
	}
	else if (id == 0)
	{

		cout << "1";
		ifstream in(filename);
		streambuf* cinbuf = cin.rdbuf();
		cin.rdbuf(in.rdbuf());
		float number;
		float sum = 0;
		int n = 0;

		while (cin >> number)
		{
			n += 1;
			sum += number;
			if (n % 3 == 0 && n != 0)
			{
				//write(fd[1], &sum, sizeof(float));
				cout << sum;
				sum = 0;
			}
		}
		close(fd[0]);
		close(fd[1]);
		cin.rdbuf(cinbuf);
		fflush(stdout);
	}
	else 
	{
		fflush(stdout);
		float res;

		while (read(fd[0], &res, sizeof(float)))
		{
			cout << res << endl;
		}

		fflush(stdout);
	}




	return 0;


}
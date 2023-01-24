#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>

using namespace std;

int main()
{

	// ввод имени файла input'а
	string filename;
	cin >> filename;

	// создание пайпа
	int fd[2];
	if (pipe(fd) == -1)
	{
		cout << "pipe error" << endl;

		return -1;
	}

	// создание процесса
	int id = fork();

	if (id == -1)
	{
		cout << "fork error" << endl;

		return -1;
	}
	// дочерний процесс
	else if (id == 0)
	{
		fflush(stdout);
		ifstream file(filename.c_str());
		streambuf* cinbuf = cin.rdbuf();
		cin.rdbuf(file.rdbuf());

		float num;
		float sum = 0;
		int n = 0;

		while (cin >> num)
		{
			n += 1;
			if ((n % 3) == 0)
			{
				write(fd[1], &sum, sizeof(sum));
				sum = 0;
			}
			else
			{
				sum += num;
			}
		}

		close(fd[0]);
		close(fd[1]);
		cin.rdbuf(cinbuf);
		fflush(stdout);
	}
	// родительский процесс
	else
	{
		float res;

		while (read(fd[0], &res, sizeof(float)))
		{
			cout << res << endl;
		}

		close(fd[0]);
		close(fd[1]);
		fflush(stdout);
	}


	return 0;
}
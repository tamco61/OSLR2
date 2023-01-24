#include "unistd.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <fcntl.h>

using namespace std;

int main()
{
	int fd[2];
	pipe(fd);
	char* filename;
	cin >> filename;

	int file = open(filename, O_RDWR | O_CREAT, 0777);

	int id = fork();

	if (id == -1)
	{
		perror("fork error");
		return -1;
	}
	else if (id == 0)
	{
		printf("[%d] It's child\n", getpid());
		fflush(stdout);

		
		float number;
		float sum = 0;
		int n = 0;

		while (cin >> number)
		{
			n += 1;
			sum += number;
			if (n % 3 == 0 && n != 0)
			{
				write(fd[1], &sum, sizeof(float));
				sum = 0;
			}
		}
		close(fd[0]);
		close(fd[1]);

	}
	else
	{

		printf("[%d] It's parent. Child id: %d\n", getpid(), id);
		fflush(stdout);
		
		ifstream in("in.txt");
		streambuf* cinbuf = cin.rdbuf();
		cin.rdbuf(in.rdbuf());

		float res

		while (read(fd[0], &res, sizeof(float)))
		{
			cout << res << endl;
		}

		fflush(stdout);
		close(fd[0]);
		close(fd[1]);
		cin.rdbuf(cinbuf);
	}
	return 0;
}
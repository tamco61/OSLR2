#include <iostream>
#include <fcntl.h>
#include <string>
#include <unistd.h>

using namespace std;

int main()
{
	// file etc
	string filename;
	cin >> filename;

	int file_d = open(filename.c_str(), O_RDONLY);
	if (file_d == -1) return -1;

	// pipe etc
	int fd[2];
	if (pipe(fd) == -1) return -2;

	// fork etc
	int id = fork();
	if (id == -1) return -3;

	// main algo
	if (id == 0)
	{
	
		if (dup2(file_d, STDIN_FILENO) == -1) return -41;
		if (dup2(fd[1], STDOUT_FILENO) == -1) return -42;
		close(fd[0]);

		execl("./slave","./slave", (char *) NULL);

	}
	else
	{
		close(file_d);

		float num;
		while (read(fd[0], &num, sizeof(float)) != sizeof(char))
		{

			cout << num << endl;

		}


	}

	close(fd[0]);
	close(fd[1]);


	return 0;
}

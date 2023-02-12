#include <unistd.h>
#include <iostream>
#include <string>


using namespace std;

int main() 
{

	string filename;
	cin >> filename;

	int file = open(filename.c_str());
	int fd[2];

	if (pipe(fd) == -1) {
		cout << "pipe error" << endl;
		return -1;
	}

	int id = fork();

	if (id == -1)
	{
		cout << "fork error" << endl;

		return -1;
	}
	else if (id == 0)
	{

		dup2(file, 0);
		dup2(fd[1], 1);

		execl("./slave.out");



	}
	else
	{

		dup2(fd[0], 0);
		float num;
		while (cin >> num)
		{
			cout << num << endl;
		}
		close(fd[1]);
		close(fd[0]);
	}


	return 0;
}
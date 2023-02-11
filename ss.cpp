#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

int main()
{

    // ввод имени файла input'а
    string filename;
    cin >> filename;

    cout << "pipe creating" << endl;
    // создание пайпа
    int fd[2];
    if (pipe(fd) == -1)
    {
        cout << "pipe error" << endl;

        return -1;
    }

    cout << "pipe created" << endl;

    cout << "forking" << endl;
    // создание процесса
    pid_t id = fork();
    cout << "forked" << endl;
    if (id == -1)
    {
        cout << "fork error" << endl;

        return -1;
    }
    // дочерний процесс
    else if (id == 0)
    {
        cout << "child process started" << endl;
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

        write(fd[1], &sum, sizeof(sum));
        close(fd[0]);
        close(fd[1]);
        file.close();
        cin.rdbuf(cinbuf);
        cout << "child process done" << endl;
    }
    // родительский процесс
    else
    {
        cout << "parent wait" << endl;
        cout << "parent started" << endl;
        float res;

        while (read(fd[0], &res, sizeof(res)))
        {
            if (res == 0) break;
            cout << res << endl;
        }

        close(fd[0]);
        close(fd[1]);
        cout << "parent done" << endl;
    }


    return 0;
}   
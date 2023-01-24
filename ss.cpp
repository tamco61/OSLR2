#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;



int main()
{
    string filename;
    cin >> filename;

    ifstream file(filename.c_str());
    streambuf* cinbf = cin.rdbuf();
    cin.rdbuf(file.rdbuf());

    float num;

    while (cin >> num)
    {
        cout << num << endl;
    }

    cin.rdbuf(cinbf);

    
    return 0;
}
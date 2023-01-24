#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

int main() 
{
    char* filename;
    cin >> filename;
    ifstream in(filename);
	streambuf* cinbuf = cin.rdbuf();
	cin.rdbuf(in.rdbuf());
    
    float number;
    
    while (cin >> number)
    {
        cout << number;
    }
    
    cin.rdbuf(cinbuf);
    return 0;
}
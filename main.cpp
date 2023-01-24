#include <iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main() 
{
    char* filename;
    cin >> filename;
    int file = open(filename, O_RDONLY);
    cout << file << endl;
    
    return 0;
}
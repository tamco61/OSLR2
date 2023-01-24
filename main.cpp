#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

using namespace std;



int main()
{
    char* filename;
    cin >> filename;
    
    int file = open(filename, O_RDONLY);
    
    char c;
    string s = "";
    float num;
    float sum;
    

    while (read(file, &c, sizeof(c)))
    {
        if (c == ' ')
        {
        	num = stof(s);
            sum = sum + num;
            s = "";
        
        }
        else if (c == 10)
        {
        	cout << sum << endl;
        	sum = 0;
        }
        else
        {
        	s = s + c;
        }
    }
    
    return 0;
}
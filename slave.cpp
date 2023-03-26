#include <iostream>
#include <unistd.h>

int main()
{

	int x = 0, res, n = 1;
	float sum = 0;
	char c;
	int check = 0;
	float k;

	while (1) {
    	res = read(STDIN_FILENO, &c, sizeof(char));
		if (c == ' ' || c == '\n' || c == '\t') 
		{
			k = x;
			k /= n;
			sum += k;
			x = 0;
			n = 1;
			check = 0;
		} 
		else if (c == '.')
		{
			check = 1;
		}	
		else
		{
			x = x*10 + c - '0';
			if (check)
			{
				n *= 10;
			}
		}	

		if (res == 0 || c == '\n') 
		{
			if (res == 0) 
			{
				if ((write(STDOUT_FILENO, "C", sizeof(char)) == -1)) return -51;
				break;
			}
			if ((write(STDOUT_FILENO, &sum, sizeof(float)) == -1)) return -52;
			x = 0;
			sum = 0;
			n = 1;
			check = 0;
		}
	}


	return EOF;
}

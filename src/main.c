#include <stdio.h>
#include <unistd.h>

int main()
{
	char c;
	
	//listen to the user input and then print it out
	while(read(STDIN_FILENO, &c, 1) == 1)
	{
		printf("%c", c);
	}
	
	return 0;
}
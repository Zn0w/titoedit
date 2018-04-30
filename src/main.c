#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void enableTerminalRawMode()
{
	struct termios raw_mode;

	// Get current terminal's attributes
	tcgetattr(STDIN_FILENO, &raw_mode);

	// Turn off echoing
	raw_mode.c_lflag &= ~(ECHO);

	// Set new attributes to the terminal
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_mode);
}

int main()
{
	enableTerminalRawMode();
	
	char c;
	
	//listen to the user input and then print it out
	while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q') // G
	{
		printf("%c", c);
	}
	
	return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void enableTerminalRawMode();
void disableTerminalRawMode();

struct termios original_mode;

int main()
{
	// Get current terminal's attributes
	tcgetattr(STDIN_FILENO, &original_mode);
	
	enableTerminalRawMode();
	
	char c;
	
	//listen to the user input and then print it out
	while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
	{
		printf("%c", c);
	}
	
	return 0;
}

void enableTerminalRawMode()
{
	atexit(disableTerminalRawMode);
	
	struct termios raw_mode;

	raw_mode = original_mode;

	// Shor reference for terminal's mode settings:
	// c_lflag - local flags
	// c_iflag - input flags
	// c_oflag - output flags
	// c_cflag - control flags

	// Turn off echoing and canonical mode (~ is a bitwise-NOT operator)
	raw_mode.c_lflag &= ~(ECHO | ICANON);

	// Set new attributes to the terminal
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_mode);
}

// When program closes, set the previous terminal settings
void disableTerminalRawMode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_mode);
}
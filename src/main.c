#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>

void enableTerminalRawMode();
void disableTerminalRawMode();

struct termios original_mode;

int main()
{
	// Get current terminal's attributes
	tcgetattr(STDIN_FILENO, &original_mode);
	
	enableTerminalRawMode();
	
	//listen to the user input and then print it out
	while(1)
	{
		char c = '\0';
		read(STDIN_FILENO, &c, 1);

		if (c == 'q')
			break;
		
		// iscntrl() - tests whether a character is a control character or not (e.g. F1, alt)
		if (!iscntrl(c))
			printf("%c\r\n", c);
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

	// Turn off (~ is a bitwise-NOT operator): 
	//	echoing 
	//	canonical mode
	//	ctrl-c & ctrl-z signals
	//	ctrl-s & ctrl-q signals
	//	ctrl-v
	//	ctrl-m (carriage return)
	//	output processing (such as "\n", "\r")
	//	other misc flags

	raw_mode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw_mode.c_oflag &= ~(OPOST);
	raw_mode.c_cflag |= (CS8);
	raw_mode.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

	// Sets read() function not to pause untill there is user input, instead it waits for a counple of milliseconds
	// and then the loop proceeds
	raw_mode.c_cc[VMIN] = 0;
  	raw_mode.c_cc[VTIME] = 1;

	// Set new attributes to the terminal
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_mode);
}

// When program closes, set the previous terminal settings
void disableTerminalRawMode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_mode);
}
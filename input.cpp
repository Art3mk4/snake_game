#include "input.h"
#include <termios.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <string>
#include <stdio.h>

using namespace std;

struct termios t;

void input_enter_off()
{
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ICANON;
	t.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void input_enter_on()
{
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= ICANON;
	t.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

enum Direction get_input()
{
	enum Direction result = East;
	char user_input;
	
	// Try non-blocking read
	fd_set fd;
	struct timeval timeout;
	FD_ZERO(&fd);
	FD_SET(STDIN_FILENO, &fd);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	
	if (select(STDIN_FILENO + 1, &fd, NULL, NULL, &timeout) > 0) {
		user_input = getchar();
		switch (user_input) {
		case 'a':
			result = West;
			break;
		case 'w':
			result = North;
			break;
		case 's':
			result = South;
			break;
		case 'd':
			result = East;
			break;
		case '\033': {
			// Escape sequence detected, read next chars
			char seq[3];
			seq[0] = getchar();
			if (seq[0] != '[') {
				return Error;
			}
			seq[1] = getchar();
			seq[2] = '\0';
			switch (seq[1]) {
			case 'A':
				result = North;
				break;
			case 'B':
				result = South;
				break;
			case 'C':
				result = East;
				break;
			case 'D':
				result = West;
				break;
			default:
				return Error;
			}
			break;
		}
		default:
			result = Error;
			break;
		}
	} else {
		// No input available, keep current direction (Error = no change)
		result = Error;
	}
	
	return result;
}

void input_init()
{
	input_enter_off();
}

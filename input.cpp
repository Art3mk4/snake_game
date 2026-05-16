#include "input.h"
#include <termios.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

using namespace std;

static struct termios orig_tios;

void input_enter_off()
{
	tcgetattr(STDIN_FILENO, &orig_tios);
	struct termios t = orig_tios;
	t.c_lflag &= ~(ICANON | ECHO);
	t.c_cc[VMIN] = 0;
	t.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void input_enter_on()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_tios);
}

enum Direction get_input()
{
	enum Direction result = Error;
	char buf[64];
	int n = read(STDIN_FILENO, buf, sizeof(buf));

	if (n <= 0) {
		return Error;
	}

	for (int i = 0; i < n; i++) {
		switch (buf[i]) {
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
		case '\033':
			if (i + 2 < n && buf[i+1] == '[') {
				switch (buf[i+2]) {
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
				}
				i += 2;
			}
			break;
		}
	}

	return result;
}

void input_init()
{
	input_enter_off();
}

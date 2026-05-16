#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unistd.h>
#include <bits/stdc++.h>
#include "input.h"
#include "snake.h"
#include "snake_map.h"
#include <utility>
#include "macros.h"

using namespace std;

Snake snake;
SnakeMap snake_map(&snake);

void poll_input()
{
	char buf[64];
	int n = read(STDIN_FILENO, buf, sizeof(buf));

	if (n <= 0) {
		return;
	}

	for (int i = 0; i < n; i++) {
		enum Direction direction = Error;
		switch (buf[i]) {
		case 'a': direction = West; break;
		case 'w': direction = North; break;
		case 's': direction = South; break;
		case 'd': direction = East; break;
		case '\033':
			if (i + 2 < n && buf[i+1] == '[') {
				switch (buf[i+2]) {
				case 'A': direction = North; break;
				case 'B': direction = South; break;
				case 'C': direction = East; break;
				case 'D': direction = West; break;
				}
				i += 2;
			}
			break;
		}
		if (direction != Error) {
			snake.update_direction(direction);
		}
	}
}

void initialize()
{
	input_init();
	input_enter_off();
}

bool is_game_end()
{
	bool result = false;
	pair<int, int> snake_head = snake.snake_head;
	if (snake_head.first < 0 || snake_head.first >= MAP_HEIGHT || snake_head.second < 0 || snake_head.second >= MAP_WIDTH)
	{
		result = true;
	}
	if (snake.is_dead)
	{
		result = true;
	}
	return result;
}

void game_over()
{
	cout << "GAME IS OVER" << endl;
}

void start_game()
{
	while (true)
	{
		poll_input();
		snake.update_movement();
		if (is_game_end())
		{
			game_over();
			break;
		}
		snake_map.redraw();
		usleep(PAUSE_LENTH);
	}
}

int main()
{

	initialize();
	start_game();
	return 0;
}

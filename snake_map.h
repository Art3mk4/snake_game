#ifndef _snake_map_h
#define _snake_map_h

#include "snake.h"
#include "macros.h"
#include <vector>
#include <string>

class SnakeMap
{
public:
	SnakeMap(Snake *snake);
	void redraw();
	pair<int, int> snake_food;
	void update_snake_food(bool force_update);
	void update_score();
private:
	vector<vector<string>> map_array;
	Snake *snake;
};

void clear_map(vector<vector<string>> &map_array);
void update_snake_head(vector<vector<string>> &map_array, Snake *snake);

#endif

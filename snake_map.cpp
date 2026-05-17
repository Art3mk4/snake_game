#include "snake_map.h"
#include <pthread.h>
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include "macros.h"

using namespace std;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

SnakeMap::SnakeMap(Snake *snake)
{
    this->snake = snake;
    map_array = vector<vector<string>>(MAP_HEIGHT, vector<string>(MAP_WIDTH, MAP_CHAR));
    srand(time(NULL));
    update_snake_food(true);
}

void SnakeMap::redraw(void)
{
    clear_map(map_array);
    for (int i = 0; i < MAP_END; i++)
    {
        cout << endl;
    }
    update_score();
    vector<pair<int, int>> snake_parts = snake->snake_parts;
    for (int i = 0; i < snake_parts.size(); i++)
    {
        pair<int, int> tmp = snake_parts[i];
        map_array[tmp.first][tmp.second] = SNAKE_CHAR;
    }
    update_snake_head(map_array, snake);
    // Random chance to move food (~62.5%)
    int random_i = rand() % MAP_WIDTH;
    int random_j = rand() % MAP_HEIGHT;
    if (snake->food_eaten || random_i > random_j * 3 / 2) {
        update_snake_food(true);
    }

    map_array[snake_food.first][snake_food.second] = SNAKE_FOOD_CHAR;

    // Top border
    cout << "+";
    for (int j = 0; j < MAP_WIDTH; j++) {
        cout << "──";
    }
    cout << "+" << endl;

    // Map rows with side borders
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        cout << "|";
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (map_array[i][j] == MAP_CHAR) {
                cout << "  ";
            } else {
                cout << map_array[i][j];
            }
        }
        cout << "|" << endl;
    }

    // Bottom border
    cout << "+";
    for (int j = 0; j < MAP_WIDTH; j++) {
        cout << "──";
    }
    cout << "+" << endl;
}

void SnakeMap::update_snake_food(bool force_update)
{
    if (snake->food_eaten || force_update)
    {
        while (true)
        {
            int random_i = rand() % MAP_WIDTH;
            int random_j = rand() % MAP_HEIGHT;
            if (map_array[random_i][random_j] == MAP_CHAR)
            {
                snake_food = make_pair(random_i, random_j);
                snake->set_snake_food(snake_food);
                snake->food_eaten = false;
                break;
            }
        }
    }
}

void clear_map(vector<vector<string>> &map_array)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            map_array[i][j] = MAP_CHAR;
        }
    }
}

void update_snake_head(vector<vector<string>> &map_array, Snake *snake)
{
    string snake_head_char = SNAKE_CHAR;
    enum Direction direction = snake->get_direction();
    switch (direction)
    {
    case West:
        snake_head_char = SNAKE_HEAD_WEST;
        break;
    case North:
        snake_head_char = SNAKE_HEAD_NORTH;
        break;
    case East:
        snake_head_char = SNAKE_HEAD_EAST;
        break;
    case South:
        snake_head_char = SNAKE_HEAD_SOUTH;
        break;
    }
    pair<int, int> snake_head = snake->snake_head;
    map_array[snake_head.first][snake_head.second] = snake_head_char;
}

void SnakeMap::update_score(void)
{
    cout << "| Score: " << snake->length << string(32 - to_string(snake->length).length(), ' ') << " |";
    cout << endl;
}

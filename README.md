# Snake Game

Terminal-based snake game written in C++11 with emoji rendering.

## Build & Run

```bash
make        # Build the snake game
./snake      # Run the game
```

## Controls

- **WASD**: Move the snake
- **Arrow keys**: Move the snake

## Architecture

### Core Components

- **`main.cpp`** - Entry point with game loop, initializes input and starts game
- **`snake.h/cpp`** - Snake class manages snake state, movement, food eating detection, and input handling
- **`input.h/cpp`** - Terminal input handling with non-blocking reads, supports WASD and arrow keys
- **`snake_map.h/cpp`** - Map rendering with emoji characters and border display

### Key Design Patterns

- **Direct polling input** - Input is polled each frame instead of using a separate thread
- **Semaphore protection** - `snake_sema` protects direction changes from race conditions
- **Double buffering** - `map_array` is cleared and redrawn each frame

### Direction System

- **West=0, North=1, East=2, South=3** (Error=-1)
- Input thread updates `next_direction`, validated before movement

### Map Rendering

- Emoji characters: `🟩` (snake body), `🐍` (snake head), `🍎` (food)
- Map is 20x20 with `+──+` borders and `|` side walls
- Each emoji occupies 2 terminal columns for proper alignment

### Build Notes

- Requires C++11 with pthread support
- Uses POSIX termios for non-blocking terminal input
- No external dependencies beyond standard library

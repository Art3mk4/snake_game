# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & Run

```bash
make        # Build the snake game
./snake      # Run the game
```

## Architecture

This is a terminal-based snake game written in C++11 with the following structure:

**Core Components:**
- `main.cpp` - Entry point with game loop, initializes input and starts game
- `snake.h/cpp` - Snake class manages snake state, movement, food eating detection, and an input thread
- `input.h/cpp` - Terminal input handling with non-blocking reads, supports WASD and arrow keys
- `snake_map.h/cpp` - Map rendering with ANSI color codes and emoji characters

**Key Design Patterns:**
- Threaded input handling - separate pthread reads inputs while game loop runs
- Semaphore protection - snake_sema protects direction changes from race conditions
- Double buffering - map_array is cleared/redrawn each frame

**Direction System:**
- West=0, North=1, East=2, South=3 (Error=-1)
- Input thread updates next_direction, validated before movement

**Build Notes:**
- Requires C++11 with pthread support
- Uses POSIX termios for non-blocking terminal input
- No external dependencies beyond standard library

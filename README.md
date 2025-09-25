# Snake Game with C & SDL2

A classic Snake game implemented in C using the SDL2 library for graphics and input. This project provides a simple, fun, and extensible foundation for learning about game development, graphics programming, and basic data structures in C.

## Features

- Classic snake gameplay
- Simple and clean graphics using SDL2
- Responsive keyboard controls
- Score tracking
- Easily extendable and modifiable codebase

## Screenshots

![Snake Game Screenshot](./assets/screenshot.png) <!-- Add a screenshot if available -->

## Getting Started

### Prerequisites

- **C Compiler** (e.g., gcc)
- **SDL2 Library**

#### Installing SDL2

- **Linux (Debian/Ubuntu):**
  ```bash
  sudo apt-get install libsdl2-dev
  ```
- **macOS (Homebrew):**
  ```bash
  brew install sdl2
  ```
- **Windows:**
  - Download development libraries from [SDL2 Downloads](https://www.libsdl.org/download-2.0.php)
  - Follow the instructions for your compiler/IDE

### Building the Game

1. Clone the repository:
   ```bash
   git clone https://github.com/RamiBrahimi-c/snake-game-with-c-sdl2.git
   cd snake-game-with-c-sdl2
   ```

2. Build using `make`:
   ```bash
   make
   ```
   Or manually with gcc:
   ```bash
   gcc -o snake main.c -lSDL2
   ```

### Running the Game

After building, run the executable:

```bash
./snake
```

## Controls

- **Arrow Keys** – Move the snake
- **Esc** – Quit the game

## Code Structure

- **main.c** — Main game logic and entry point
- **Makefile** — For building the project

## To Do

Things that could be improved or added in the future:

- [ ] Add sound effects and background music
- [ ] Implement different levels or increasing difficulty
- [ ] Add a high score system
- [ ] Create a main menu and game over screen
- [ ] Add support for touch or mouse controls
- [ ] Refactor the code for better modularity and readability
- [ ] Add settings for customizable controls and speed
- [ ] Implement a pause/resume feature
- [ ] Add power-ups or obstacles
- [ ] Support for different snake skins/colors

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests for improvements, bug fixes, or new features.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgements

- [SDL2](https://www.libsdl.org/) — Simple DirectMedia Layer library

---

Enjoy playing and hacking on the Snake Game!

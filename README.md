# Cub3d

## Summary  
This repository contains a raycasting-based 3D rendering engine written in C, developed as part of the 42 School curriculum. It simulates a first-person view in a maze-like 2D map by casting rays and drawing vertical wall slices, similar to early 3D games like _Wolfenstein 3D_. It supports player movement, texture mapping, and basic collision detection.

---

## Repository Structure  

- **`include/`**  
  - `cub3d.h`       : Main structures, constants, and function prototypes  
  - `map.h`         : `.cub` file parsing and validation  
  - `raycasting.h`  : Raycasting engine declarations  
  - `render.h`      : Rendering routines and texture handling  
  - `player.h`      : Input handling and movement logic  

- **`srcs/`**  
  1. **`main.c`**            : Program entry point; initializes and starts the game loop  
  2. **`map_parser.c`** / **`map_utils.c`**  
                             : Load and validate map, read texture paths  
  3. **`raycasting.c`** / **`dda.c`**  
                             : Core raycasting algorithm using DDA to detect walls  
  4. **`render.c`** / **`draw.c`**  
                             : Draw vertical wall slices, floor and ceiling  
  5. **`player.c`** / **`input.c`**  
                             : Handle keyboard input and update player state  
  6. **`textures.c`**        : Load and manage `.xpm` textures  
  7. **`errors.c`** / **`cleanup.c`**  
                             : Error reporting and resource cleanup  

- **`maps/`**  
  - Sample `.cub` files defining world layouts and configuration  

- **`textures/`**  
  - Wall textures in `.xpm` format

- **`Controls`**  
  - `W` / `S` : Move forward / backward  
  - `A` / `D` : Strafe left / right  
  - `←` / `→` : Rotate view left / right  
  - `ESC`     : Exit  

- **`Makefile`**
  - `make`          : Build the `cub3d` executable  
  - `make clean`    : Remove object files  
  - `make fclean`   : Remove objects and binary  
  - `make re`       : `fclean` + `make`  

- **`.gitignore`**  
  - Ignore build artifacts (`*.o`, `cub3d`), editor swapfiles, etc.

---

## Languages and Tools  

- **C** (96.7%)      : Core implementation (C99)  
- **Makefile** (3.3%): Build automation  
- **MiniLibX**       : Lightweight X11-based graphics library  

---

## How to Build and Run  

```bash
# 1. Clone this repo
git clone https://github.com/Kamiyore/Cub3d.git
cd Cub3d

# 2. Install/build MiniLibX
git clone https://github.com/42Paris/minilibx-linux.git minilibx-linux
make

# 4. Run with a sample map
./cub3d maps/demo.cub

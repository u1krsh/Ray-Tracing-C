# Ray Tracing Simulation

A simple ray tracing simulation using SDL2 in C.

## Demo

![image](https://github.com/user-attachments/assets/7cfdf592-1f4b-4e23-981a-e89221ba4b9b)


## Features
- Real-time ray tracing simulation
- Interactive light source controlled by mouse movement
- Shadows cast by an obstacle

## Installation & Compilation

### Requirements
- GCC (MinGW for Windows)
- SDL2 library

### Compilation
```sh
gcc ray-tracing.c -o raytracing -lmingw32 -lSDL2main -lSDL2
```

### Running the Application
```sh
./raytracing
```

## Usage
- Move the mouse to change the light source position.
- The rays dynamically update and interact with the obstacle.

## Preview

### Light Source Movement
![Screen Recording 2025-02-14 153250](https://github.com/user-attachments/assets/965b974c-c829-460f-bab2-62b68398a79e)


# Tetris

A clone of the popular game [Tetris](https://en.wikipedia.org/wiki/Tetris) written in C++ with the [raylib](https://www.raylib.com/) library.

## Building

### Linux

Run the following commands:
```
git clone https://github.com/AtticusHelvig/tetris.git
cd tetris
mkdir build && cd build
cmake ..
make
```

### Windows

> [!WARNING]
> I developed this project on linux. Building on other systems is largely untested.

Ensure you have MinGW installed.

Run the following commands:
```
git clone https://github.com/AtticusHelvig/tetris.git
cd tetris
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
make
```

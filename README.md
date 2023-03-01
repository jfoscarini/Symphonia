# Symphonia

A prototype SDL2 game engine in the making. The goal of this project is to challenge myself to come up with different approaches to different kinds of problems related to game development. It may have its development abruptly interrupted at any time.

## Requirements
* SDL2
* SDL2_ttf
* SDL2_image
* SDL2_mixer
* Catch2 3 (tests)

## Examples

A few example screens are present and some more are incoming. *Assets are not included with the project. Please provide your own.*

Suppose that you want to try out `TextExample`, you need to change the following files:

* main.cpp

Replace `#include "screens/TitleScreen.h"` with `#include "example_screens/TextExample.h"`.

Replace `std::make_unique<TitleScreen>()` with `std::make_unique<TextExample>()`

* CMakeLists.txt

Add `src/TextExample.cpp src/TextExample.h` to the end of `add_executable` cmake function.

cmake_minimum_required(VERSION 3.24)
project(Symphonia)

set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 3 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

set(SDL2_LIBRARIES /opt/homebrew/lib/libSDL2.dylib)
set(SDL2_IMAGE_LIBRARIES /opt/homebrew/lib/libSDL2_image.dylib)
set(SDL2_TTF_LIBRARIES /opt/homebrew/lib/libSDL2_ttf.dylib)
set(SDL2_MIXER_LIBRARIES /opt/homebrew/lib/libSDL2_mixer.dylib)
set(SDL2_ALL ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

add_executable(test_node ../lib/Game.cpp ../lib/Game.h ../lib/ui/Node.cpp Node.cpp)
target_link_libraries(test_node PRIVATE Catch2::Catch2WithMain ${SDL2_ALL})
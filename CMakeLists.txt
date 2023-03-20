cmake_minimum_required(VERSION 3.23)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(Minesweeper main.cpp MinesweeperBoard.cpp MinesweeperBoard.h GamePanel.cpp GamePanel.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

INCLUDE_DIRECTORIES(C:/SFML/include)
TARGET_LINK_LIBRARIES(Minesweeper sfml-system sfml-window sfml-graphics sfml-audio)
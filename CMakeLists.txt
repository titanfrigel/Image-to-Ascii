cmake_minimum_required(VERSION 3.24)
project( itoa )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ./include )
add_executable( itoa src/main.cpp src/image_to_ascii.cpp )
target_link_libraries( itoa ${OpenCV_LIBS} ncurses )
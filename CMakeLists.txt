cmake_minimum_required(VERSION 3.15)
project(CourseWork)

set(CMAKE_CXX_STANDARD 14)
set(OpenGlLinkers -lGL -lglfw -lGLU -lGLEW -lSOIL -lassimp)

add_executable(CourseWork src/main.cpp src/include/engine.hpp src/include/camera.hpp src/include/shader.hpp src/shader.cpp)
target_link_libraries(CourseWork ${OpenGlLinkers})
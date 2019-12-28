cmake_minimum_required(VERSION 3.15)
project(CourseWork)

set(CMAKE_CXX_STANDARD 17)
set(OpenGlLinkers -lGL -lglfw -lGLU -lGLEW -lSOIL -lassimp)

add_executable(CourseWork src/main.cpp src/include/engine.hpp src/include/camera.hpp src/include/shader.hpp src/shader.cpp src/include/json_config.hpp src/json_config.cpp src/include/def.hpp src/include/input.hpp src/input.cpp src/include/window.hpp src/window.cpp src/include/light.hpp src/light.cpp src/engine.cpp src/camera.cpp src/include/world.hpp src/include/texture.hpp src/texture.cpp)
target_link_libraries(CourseWork ${OpenGlLinkers})
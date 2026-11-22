cmake_minimum_required(VERSION 3.16)
project(digit_gui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(gui
  gui_main.cpp
  preprocess.cpp
  matrix.cpp
  activate_func.cpp
  layer.cpp
  mlp.cpp
  file.cpp
)

target_link_libraries(gui PRIVATE Qt6::Widgets)

# копируем веса рядом с gui.exe, если они лежат в папке проекта
foreach(f w1b1.txt w2b2.txt)
  if(EXISTS "${CMAKE_SOURCE_DIR}/${f}")
    configure_file("${CMAKE_SOURCE_DIR}/${f}" "${CMAKE_BINARY_DIR}/${f}" COPYONLY)
  endif()
endforeach()
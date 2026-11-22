# MLP
Для обучения:

g++ -std=c++17 -O2 -Wall -Wextra main.cpp matrix.cpp activate_func.cpp layer.cpp mlp.cpp mnist.cpp file.cpp -o m.exe

m.exe

Для компиляции и запуска самой программы:

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
build\gui.exe
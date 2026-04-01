cmake_minimum_required(VERSION 3.10)
project(Esercitazione3)

# Attiviamo C++20 per supportare "requires std::integral" e l'header <concepts>
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(es3 main.cpp)
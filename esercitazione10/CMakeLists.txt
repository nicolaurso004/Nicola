cmake_minimum_required(VERSION 3.20)
project(esercitazione10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# Ricerca del pacchetto Eigen3 nel sistema
find_package(Eigen3 REQUIRED)

add_executable(test_cg test_cg.cpp)

# Collegamento dei file di inclusione di Eigen all'eseguibile
target_link_libraries(test_cg PRIVATE Eigen3::Eigen)
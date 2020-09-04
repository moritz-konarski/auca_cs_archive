project(ca_project ASM CXX)
cmake_minimum_required(VERSION 2.8.0)
set(CMAKE_CXX_STANDARD 17)


add_executable(01_x_87 01_section/01_x_87.s)
target_link_libraries(01_x_87)

add_executable(01_int 01_section/01_int.s)
target_link_libraries(01_int)



add_executable(02_x_87 02_section/02_x_87.cpp)
target_link_libraries(02_x_87)

add_executable(02_simd 02_section/02_simd.cpp)
target_link_libraries(02_simd)

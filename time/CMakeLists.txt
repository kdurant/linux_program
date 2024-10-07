cmake_minimum_required(VERSION 3.10)
set(projectName demo)
# 项目名称
project(${projectName})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # 可执行文件位置

add_executable(time time.c)
add_executable(ftime ftime.c)
add_executable(gettimeofday gettimeofday.c)
add_executable(clock_gettime clock_gettime.c)

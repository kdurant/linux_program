cmake_minimum_required(VERSION 3.10)
set(projectName demo)
# 项目名称
project(${projectName})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # 可执行文件位置

add_executable(01_simple_thread simple_thread.c)

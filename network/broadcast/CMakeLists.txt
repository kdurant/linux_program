cmake_minimum_required (VERSION 3.10)
set(projectName broadcast)
# 项目名称
project (${projectName})

add_executable(broadcast udp_boardcast.c)


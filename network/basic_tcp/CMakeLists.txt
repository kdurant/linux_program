cmake_minimum_required (VERSION 3.10)
set(projectName basic_tcp)
# 项目名称
project (${projectName})

add_executable(basic_tcp_client basic_tcp_client.c)
add_executable(basic_tcp_server basic_tcp_server.c)


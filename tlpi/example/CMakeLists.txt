cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(../lib)
set(TLPI_LIB_SRS ../lib/error_functions.c ../lib/file_perms.c ../lib/get_num.c
                 ../lib/ugid_functions.c)

add_executable(copy ./chapter04/copy.c ${TLPI_LIB_SRS})
add_executable(seek_io ./chapter04/seek_io.c ${TLPI_LIB_SRS})
add_executable(t_readv ./chapter05/t_readv.c ${TLPI_LIB_SRS})
add_executable(t_write ./chapter05/t_write.c ${TLPI_LIB_SRS})
add_executable(display_env ./chapter06/display_env.c ${TLPI_LIB_SRS})
add_executable(longjmp ./chapter06/longjmp.c ${TLPI_LIB_SRS})
add_executable(modify_env ./chapter06/modify_env.c ${TLPI_LIB_SRS})
add_executable(mem_segments ./chapter06/mem_segments.c ${TLPI_LIB_SRS})
# add_executable(ugid_functions ./chapter07/ugid_functions.c ${TLPI_LIB_SRS})
add_executable(intquit ./signals/intquit.c ${TLPI_LIB_SRS})
add_executable(ouch ./signals/ouch.c ${TLPI_LIB_SRS})
add_executable(t_kill ./signals/t_kill.c ${TLPI_LIB_SRS})
add_executable(condition ./threads/condition.c ${TLPI_LIB_SRS})
add_executable(simple_thread ./threads/simple_thread.c ${TLPI_LIB_SRS})
add_executable(thread_incr_mutex ./threads/thread_incr_mutex.c ${TLPI_LIB_SRS})
add_executable(thread_multjoin ./threads/thread_multjoin.c ${TLPI_LIB_SRS})

add_executable(check_password ./chapter07/check_password.c ${TLPI_LIB_SRS})
target_link_libraries(check_password crypt)

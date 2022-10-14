cmake_minimum_required(VERSION 3.22)
project(socrate)

set(CMAKE_CXX_STANDARD 14)

add_executable(socrate ft_atoi.c clean_utils.c list_utils.c struct_utils.c routine_utils.c time_utils.c setups.c main.c)

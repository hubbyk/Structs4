cmake_minimum_required(VERSION 3.16)
project(Structs4 C)

set(CMAKE_C_STANDARD 99)

add_executable(Structs4 main.c core.c core.h dbtree.c dbtree.h dbio.c dbio.h dbmainheader.h dbdatamanager.c dbdatamanager.h)
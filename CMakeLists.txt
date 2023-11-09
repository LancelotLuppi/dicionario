cmake_minimum_required(VERSION 3.26)
project(dicionario C)

set(CMAKE_C_STANDARD 11)

add_executable(dicionario
        main.c
        HashTable.h
        domain.h)

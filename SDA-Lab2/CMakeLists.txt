cmake_minimum_required(VERSION 3.27)
project(SDA_Lab2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SDA_Lab2
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedSet.cpp
        SortedSet.h
        SortedSetIterator.cpp
        SortedSetIterator.h)

cmake_minimum_required(VERSION 3.28)
project(Lab5_DSA_Bag)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab5_DSA_Bag
        SortedBag.h
        SortedBag.cpp
        ShortTest.cpp
        App.cpp
        SortedBagIterator.cpp
        ExtendedTest.cpp)

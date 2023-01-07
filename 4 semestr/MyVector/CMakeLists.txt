cmake_minimum_required(VERSION 3.23)
project(MyVector)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MyVector
        Container.h
        GroupContainer.h
        Main.cpp
        Mem.h
        MemoryManager.h
        Vector.cpp
        Vector.h
        VectorAbstract.h)

cmake_minimum_required(VERSION 3.23)
project(SET_MSU_4_semestr)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SET_MSU_4_semestr
        Container.h
        GroupContainer.h
        GroupList.h
        List.cpp
        List.h
        ListAbstract.h
        Mem.h
        MemoryManager.h
        Set.cpp
        Set.h
        SetAbstract.h
        SetMain.cpp
        SetTest.cpp
        SetTest.h)

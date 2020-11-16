cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT links_treat)


project(${PROJECT} VERSION 1.2.3.4 LANGUAGES C CXX)


set(HEADERS 
    src/services.h
    src/tree.h
    src/workers.h
    )

set(SOURCES
    src/main.cpp
    src/tree.cpp
    src/services.cpp
    src/workers.cpp
    )


add_executable (${PROJECT} ${HEADERS} ${SOURCES})

cmake_minimum_required(VERSION 3.0)

set(PROJECT links_treat)

project(${PROJECT} VERSION 1.2.3.4 LANGUAGES C CXX)

set(HEADERS 
    treat_directory.h)

set(SOURCES
    main.cpp
    treat_directory.cpp)

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

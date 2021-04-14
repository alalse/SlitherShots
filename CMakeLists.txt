cmake_minimum_required(VERSION 3.10)
project(sfml)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-ggdb3 -std=c++17 -Wall -Wextra -Wpedantic")

set(SFML_MODULES network graphics window system)

foreach(i ${SFML_MODULES})
    list(APPEND SFML_LIBRARIES "sfml-${i}")
endforeach(i)

set(MAIN
    main.cc
)

include_directories(
    ${PROJECT_SOURCE_DIR}/Framework
    ${PROJECT_SOURCE_DIR}/Game_objects
    ${PROJECT_SOURCE_DIR}/States
)

file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/Framework/*.h"
    "${PROJECT_SOURCE_DIR}/Framework/*.cc"
    "${PROJECT_SOURCE_DIR}/Game_objects/*.h"
    "${PROJECT_SOURCE_DIR}/Game_objects/*.cc"
    "${PROJECT_SOURCE_DIR}/States/*.h"
    "${PROJECT_SOURCE_DIR}/States/*.cc"
)

add_executable(sfml ${MAIN} ${all_SRCS})

target_link_libraries(sfml ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
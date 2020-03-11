cmake_minimum_required(VERSION 3.5.1)
project(midiintonation VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(/usr/include/stk)

set(CMAKE_CXX_FLAGS "-O3 -Wall -D__LITTLE_ENDIAN__ -DHAVE_GETTIMEOFDAY -D__LINUX_ALSA__")
message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_STANDARD_LIBRARIES "-lstk -lpthread -lasound -lm")
message(STATUS "CMAKE_CXX_STANDARD_LIBRARIES = ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
message(STATUS "EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")

add_subdirectory(src)
configure_file(${PROJECT_SOURCE_DIR}/midiintonationConfig.h.in midiintonationConfig.h)

add_subdirectory(test)


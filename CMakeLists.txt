cmake_minimum_required(VERSION 3.20.0)
project(IntentRecognizer)
set(CMAKE_CXX_STANDARD 17)

enable_testing()
include_directories(inc)
add_subdirectory(json-parser)
add_subdirectory(src)
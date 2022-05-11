cmake_minimum_required(VERSION 3.20.0)
project(IntentRecognizer)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Core REQUIRED)
include_directories(${Qt5Core_INCLUDES})
add_definitions(${Qt5Core_DEFINITIONS})

enable_testing()
include_directories(inc)
add_subdirectory(libs/json-parser)
add_subdirectory(src)

install(FILES 
        ${CMAKE_SOURCE_DIR}/data/database.json 
        DESTINATION /etc/ 
        PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ WORLD_WRITE)
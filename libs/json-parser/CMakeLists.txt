add_library(JsonParser STATIC JsonParserFactory.cpp QtJsonParser.cpp)
target_link_libraries(JsonParser Qt5::Core)

add_subdirectory(unit-tests)
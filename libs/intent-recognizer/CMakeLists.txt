add_library(IntentRecognizer STATIC IntentRecognizer.cpp)
target_link_libraries(IntentRecognizer JsonParser)

add_subdirectory(unit-tests)
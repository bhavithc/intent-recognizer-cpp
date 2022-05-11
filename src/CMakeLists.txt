add_executable(IntentRecognizer main.cpp IntentRecognizer.cpp)
target_link_libraries(IntentRecognizer JsonParser)
install(TARGETS IntentRecognizer DESTINATION ${CMAKE_INSTALL_BINDIR})

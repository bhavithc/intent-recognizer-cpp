add_executable(intentrecognizer main.cpp)
target_link_libraries(intentrecognizer JsonParser IntentRecognizer log4cplus)
install(TARGETS intentrecognizer DESTINATION ${CMAKE_INSTALL_BINDIR})

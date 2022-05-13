/**
 * @file main.cpp
 * @author Bhavith C (bhavithc.acharya@gmail.com)
 * @brief Intent recognizer application
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "IntentRecognizer.h"
#include "LoggerHelper.h"

#include <sstream>
#include <string.h>
#include <unistd.h>
#include <memory>
#include <iostream>

#include <log4cplus/initializer.h>
#include <log4cplus/configurator.h>
#include <log4cplus/log4cplus.h>

#define MAX_WORDS_SUPPORTED 10
#define LOGGER_NAME "IntentRecognizer"
#define LOG4CPLUS_CONFIG_FILE "/etc/intent-recognizer.ini"
#define DEFAULT_PATTERN_LOG "[%-5p][%D{%Y-%m-%d %H:%M:%S:%q}][%i]%F:%L %m%n"

log4cplus::Logger magic_logger_x7891;

/**
 * @brief Print the usage of the program
 */
void printHelp()
{
    std::stringstream ss;
    ss << "Usage: IntentRecognizer [--help | -h] <your message here>\n";
    ss << "       @remark: message should not exceed " 
        << MAX_WORDS_SUPPORTED << " word(s)";
    std::cout << ss.str() << "\n";
}

/**
 * @brief Check is the given file exists
 * 
 * @param[in] fileName  File name with full path
 * 
 * @retval  true    If file exists
 * @retval  false   If file doesn't exists
 */
bool isFileExist(const std::string& fileName)
{
    return (access(fileName.c_str(), F_OK) == 0);
}

/**
 * @brief Main program to enter
 * 
 * @param[in]  argc     Arguments count
 * @param[out] pArgv    Argument values
 * 
 * @retval 0    On success
 * @retval -1   On failure
 */
int main(int argc, char** pArgv)
{
    std::string sentence;
    std::string intent;
    log4cplus::SharedAppenderPtr pConsoleAppender;
    log4cplus::initialize();

    if (argc == 1) {
        LOG_ERROR("No message provided !");
        printHelp();
        return -1;
    }

    if (argc > MAX_WORDS_SUPPORTED) {
        LOG_ERROR("Message has more than " << MAX_WORDS_SUPPORTED << " words");
        printHelp();
        return -1;
    }

    if ((strncasecmp(pArgv[1], "--help", sizeof("--help")) == 0) || 
        (strncasecmp(pArgv[1], "-h", sizeof("-h")) == 0)) {
        printHelp();
        return 0;
    }

    if (isFileExist(LOG4CPLUS_CONFIG_FILE)) {
        log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_CONFIG_FILE);
    } else {
        std::cerr << "Initializing with console appender";
        pConsoleAppender = new log4cplus::ConsoleAppender();
        if (pConsoleAppender) {
            const log4cplus::tstring pattern = LOG4CPLUS_TEXT(DEFAULT_PATTERN_LOG);
            pConsoleAppender->setThreshold(log4cplus::TRACE_LOG_LEVEL);
            pConsoleAppender->setName(LOG4CPLUS_TEXT(LOGGER_NAME));
            pConsoleAppender->setLayout(
                std::unique_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(pattern)));
        }
    }
    magic_logger_x7891 = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(LOGGER_NAME));

#if defined(MODE_DEBUG)
    magic_logger_x7891.setLogLevel(log4cplus::DEBUG_LOG_LEVEL);
#else
    magic_logger_x7891.setLogLevel(log4cplus::ERROR_LOG_LEVEL);
#endif

    for (auto i = 1; i < argc; i++) {
        sentence += pArgv[i];
        if (i != argc - 1) {
            sentence += " ";
        }
    }

    IntentRecognizer ir;
    ir.recognizeIntent(sentence, intent);
    std::cout << sentence << " => (Intent: " << intent << ")\n";
    return 0;
}

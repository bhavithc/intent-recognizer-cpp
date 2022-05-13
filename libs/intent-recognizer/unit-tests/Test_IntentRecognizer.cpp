#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#include "IntentRecognizer.h"

#include <log4cplus/initializer.h>
#include <log4cplus/configurator.h>
#include <log4cplus/log4cplus.h>
#define LOG4CPLUS_CONFIG_FILE "/etc/intent-recognizer.ini"

log4cplus::Logger magic_logger_x7891;

class IntentRecognizerTest : public ::testing::Test
{
public:
    void SetUp()
    {
        log4cplus::initialize();
        log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_CONFIG_FILE);
        magic_logger_x7891 = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("unit-test"));
    }
};

TEST_F(IntentRecognizerTest, invalidTest)
{
    IntentRecognizer ir;
    std::string intent;
    std::string bigLenStr;
    for (int i = 0; i < 100; i++) {
        bigLenStr += "C";
    }
    ir.recognizeIntent(bigLenStr, intent);
    EXPECT_STREQ(intent.c_str(), "Please try different sentence");

    bigLenStr += "C";
    ir.recognizeIntent(bigLenStr, intent);
    EXPECT_STREQ(intent.c_str(), "Sentence has too many characters");
}

TEST_F(IntentRecognizerTest, validTest)
{
    IntentRecognizer ir;
    std::string intent;

    // What is the weather like today? => Prints (Intent: Get Weather)
    ir.recognizeIntent("What is the weather like today?", intent);
    std::vector<std::string> ans {"Get", "Weather"};
    for (const auto& s : ans) {
        EXPECT_NE(intent.find(s), std::string::npos);
    }

    // What is the weather like in Paris today? => Prints (Intent: Get Weather City)
    ir.recognizeIntent("What is the weather like in Paris today?", intent);
    ans  = {"Get", "Weather", "City"};
    for (const auto& s : ans) {
        EXPECT_NE(intent.find(s), std::string::npos);
    }

    // Tell me an interesting fact. => Prints (Intent: Get Fact)
    ir.recognizeIntent("Tell me an interesting fact.", intent);
    ans  = {"Get", "Fact"};
    for (const auto& s : ans) {
        EXPECT_NE(intent.find(s), std::string::npos);
    }
}

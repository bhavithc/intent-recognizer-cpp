#include <gtest/gtest.h>
#include <string>
#include <iostream>

#include "QtJsonParser.h"

class QtJsonParserTest : public ::testing::Test
{
public:
    bool isFileExist(const std::string& fileName)
    {
        return (access(fileName.c_str(), F_OK) == 0);
    }
};

TEST_F(QtJsonParserTest, QtJsonParserTestInvalidFile)
{   
    JsonData jsonData;
    QtJsonParser jsonParser;
    EXPECT_THROW(jsonParser.parseJson("/et/database.json", jsonData), JsonParseException);
}

TEST_F(QtJsonParserTest, QtJsonParserTestValidFile)
{
    JsonData jsonData;
    QtJsonParser jsonparser;
    constexpr auto validFile = "/etc/database.json";
    
    if (isFileExist(validFile)) {
        EXPECT_NO_THROW(jsonparser.parseJson("/etc/database.json", jsonData));
    } else {
        std::cerr << "[WARN] Please install project before executing unit test case !\n"; 
    }
}

TEST_F(QtJsonParserTest, QtJsonParserTestValidJsonData)
{
    JsonData jsonData;
    QtJsonParser jsonparser;
    constexpr auto validFile = "/etc/database.json";
    
    if (!isFileExist(validFile)) {
        std::cerr << "[WARN] Please install project before executing unit test case !\n"; 
        return;
    }

    EXPECT_NO_THROW(jsonparser.parseJson("/etc/database.json", jsonData));
    EXPECT_NE(jsonData.size(), 0);
}

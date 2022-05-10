#include <gtest/gtest.h>

#include "IJsonParser.h"
#include "JsonParserFactory.h"

class JsonParserTest : public ::testing::Test
{

};

TEST_F(JsonParserTest, JsonParserTestObj)
{   
    JsonData jsonData;
    auto pJsonParser = JsonParserFactory::getInstance();
    pJsonParser->parseJson("/home/bhavith/Bhavith/Development/intent-recognizer-cpp/data/sample.json", jsonData);

    for (const auto& intent : jsonData) {
        std::cout << intent.first << "\n";
        for (const auto& value : intent.second) {
            std::cout << " - " << value << "\n";
        }
    }
}
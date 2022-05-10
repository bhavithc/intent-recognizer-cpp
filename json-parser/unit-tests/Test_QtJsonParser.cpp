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
    EXPECT_THROW(pJsonParser->parseJson("dummyPath", jsonData), JsonParseException);
}
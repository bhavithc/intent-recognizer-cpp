#include "JsonParserFactory.h"
#include "QtJsonParser.h"

auto JsonParserFactory::getInstance() -> std::unique_ptr<IJsonParser>
{
    return std::make_unique<QtJsonParser>();
}
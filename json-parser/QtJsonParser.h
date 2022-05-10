#include "IJsonParser.h"

class QtJsonParser : public IJsonParser
{
public:
    auto parseJson(const std::string& jsonFilePath,
        JsonData& jsonData) -> void override;

};
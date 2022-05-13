/**
 * @file QtJsonParser.h
 * @author Bhavith C (bhavithc.acharya@gmail.com)
 * @brief Concerete implementation of Json parser using QT library
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "IJsonParser.h"

class QtJsonParser : public IJsonParser
{
public:
    /**< Refer IJsonParser.h for comments**/
    auto parseJson(const std::string& jsonFilePath,
        JsonData& jsonData) -> void override;
};
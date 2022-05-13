/**
 * @file IJsonParser.h
 * @author Bhavith C (bhavithc.acharya@gmail.com)
 * @brief Json parser interface for parsing the JSON file
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <string>
#include <map>
#include <vector>
#include <exception>

typedef std::map<std::string, std::vector<std::string>> JsonData;

class JsonParseException : std::exception
{
public:

    /**
     * @brief Construct a new Json Parse Exception object
     * 
     * @param[in] reason Reason for the failure
     */
    explicit JsonParseException(const std::string& reason)
        : m_reason(reason)
    {

    }

    /**
     * @brief Destroy the Json Parse Exception object
     * 
     */
    ~JsonParseException()
    {
        m_reason = "";
    }

    /**
     * @brief Reason of the failure
     * 
     * @return reason of the failure
     */
    const char* what()
    {
        return m_reason.c_str();
    }
private:
    std::string m_reason;
};

class IJsonParser
{
public:
    /**
     * @brief Prase the given json file and fill the data in jsonData
     * 
     * @param[in]   jsonFilePath    Json file with full path
     * @param[out]  jsonData        Json data to be filled
     * 
     * @throw JsonParseException on failure
     */
    virtual auto parseJson(const std::string& jsonFilePath, JsonData& jsonData) -> void = 0;
};
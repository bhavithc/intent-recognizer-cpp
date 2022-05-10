#pragma once
#include <string>
#include <map>
#include <vector>
#include <exception>

typedef std::map<std::string, std::vector<std::string>> JsonData;

class JsonParseException : std::exception
{
public:

    explicit JsonParseException(const std::string& reason)
        : m_reason(reason)
    {

    }

    ~JsonParseException()
    {
        m_reason = "";
    }

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
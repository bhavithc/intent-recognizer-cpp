/**
 * @file IntentRecognizer.cpp
 * @author Bhavith C (bhavithc.acharya@gmail.com)
 * @brief Implementation of the intent recognizer of the given sentence 
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "IntentRecognizer.h"
#include "IJsonParser.h"
#include "JsonParserFactory.h"
#include "LoggerHelper.h"

#include <sstream>
#include <algorithm>

#define MAX_SUPPORTED_SENTENCE_LENGTH 100
#define INVALID_INTENT "Please try different sentence"
#define DATABASE_FILE "/etc/database.json"

class IntentRecognizer::Impl
{
public:
    /**
     * @brief Get the intent of the given sentence
     * 
     * @param[in]   sentence Sentence for which intent to be find
     * @param[out]  intent   Intent of the sentence
     * 
     * @retval true     On success
     * @retval false    On failure
     */
    auto getIntent(const std::string& sentence, std::string& intent) -> bool
    {
        auto status = false;
        std::stringstream sentenceStream(sentence);
        std::string word;
        std::map<std::string, std::string> intents;

        if (sentence.length() == 0 ||
            sentence.length() > MAX_SUPPORTED_SENTENCE_LENGTH) {
            LOG_ERROR("Invalid sentence length received, unable to get intent");
            return status;
        }

        LOG_DEBUG("Getting intent of sentence '" << sentence << "' ...");
        intent = "Get";

        while (sentenceStream >> word) {
            cleanWord(word);
            std::string intentStr;
            auto success = getIntentOfWord(word, intentStr);
            if (success) {
                intents[intentStr] = intentStr;
            }
        }

        if (intents.size() == 0) {
            intent = INVALID_INTENT;
        } else {
            for (const auto& i : intents) {
                intent += " ";
                auto word = i.first;
                strToLower(word);
                intent += word;
            }
            status = true;
        }

        return status;
    }

    /**
     * @brief Load the json data from the database file
     * 
     * @throw  JsonParseException
     */
    auto loadJsonData() -> void
    {
        auto pJsonParser = JsonParserFactory::getInstance();
        pJsonParser->parseJson(DATABASE_FILE, m_jsonData);
    }

private:

    /**
     * @brief Convert the given string to lowercase
     * 
     * @param[in,out] value  string to converted to lowercase
     */
    auto strToLower(std::string& value) -> void
    {
        std::transform(value.begin(), value.end(), value.begin(),
            [](unsigned char c){ return std::tolower(c); });
    }

    /**
     * @brief Get the intent of the given word
     * 
     * @param[in]  word   word for which to find the intent
     * @param[out] intent intent of the given word
     * 
     * @retval true     On success
     * @retval false    On failure
     */
    auto getIntentOfWord(const std::string& word, std::string& intent) -> bool
    {   
        if (word.size() == 0) {
            intent = "";
            return false;
        }

        intent = INVALID_INTENT;

        for (const auto& jsonData : m_jsonData) {

            const auto found = std::find_if(
                jsonData.second.begin(), jsonData.second.end(), [&](auto& wordInternal) {

                if (wordInternal.size() == 0) {
                    return false;
                }

                auto word1 = word;
                auto word2 = wordInternal;
                strToLower(word1);
                strToLower(word2);

                return word1 == word2;
            });

            if (found != jsonData.second.end()) {
                intent = jsonData.first;
                return true;
            }
        }

        return false;
    }


    /**
     * @brief Clean up the given word by removing the symbols at the
     *        end of the word
     *        ex: list. to list, fine? to fine
     * 
     * @param[in,out] word word be cleaned
     * 
     * @remark Right now it removed only '.' and '?' chars at the end of the word
     */
    auto cleanWord(std::string& word) -> void
    {
        if (word.length() == 0 || word.length() == 1) {
            return;
        }

        const auto pos = word.length() - 1;
        std::vector<char> symbols {'.', '?'};
        auto found = std::find(symbols.begin(), symbols.end(), word[pos]);
        if (found != symbols.end()) {
            word.pop_back();
        }
    }

    JsonData m_jsonData;
};

/**< Refer IntentRecognizer.h for comments**/
IntentRecognizer::IntentRecognizer() 
    : m_pImpl(std::make_unique<IntentRecognizer::Impl>())
{

}

/**< Refer IntentRecognizer.h for comments**/
IntentRecognizer::~IntentRecognizer()
{

}

/**< Refer IntentRecognizer.h for comments**/
auto IntentRecognizer::recognizeIntent(const std::string& sentence, std::string& intent) -> void
{
    try {
        m_pImpl->loadJsonData();
        m_pImpl->getIntent(sentence, intent);
    } catch (JsonParseException& parseException) {
        LOG_ERROR("Failed to parse JSON file : " <<  parseException.what());
        intent = "Error occurred while identifying the intent";    
    } catch (const std::exception& stdException) {
        LOG_ERROR("Failed to parse JSON file : " <<  stdException.what());
        intent = "Error occurred while identifying the intent";
    } catch (...) {
        LOG_ERROR("Failed to parse JSON file for unknown reason");
        intent = "Error occurred while identifying the intent";
    }
}
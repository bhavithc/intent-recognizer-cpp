#include "IntentRecognizer.h"
#include "IJsonParser.h"
#include "JsonParserFactory.h"

#include <sstream>
#include <algorithm>
#include <iostream>

#define MAX_SUPPORTED_SENTENCE_LENGTH 100
#define INVALID_INTENT "Please try different sentence"

class IntentRecognizer::Impl
{
public:
    bool getIntent(const std::string& sentence, std::string& intent)
    {
        intent = "Get";
        auto status = false;

        if (sentence.length() == 0 ||
            sentence.length() > MAX_SUPPORTED_SENTENCE_LENGTH) {
            std::cout << "Invalid sentence length received, unable to get intent\n";
            return status;
        }

        std::stringstream sentenceStream(sentence);
        std::string word;
        std::map<std::string, std::string> intents;

        while (sentenceStream >> word) {
            cleanWord(word);
            std::string intentEnum;
            auto success = getIntentOfWord(word, intentEnum);
            if (success) {
                intents[intentEnum] = intentEnum;
            }
        }

        if (intents.size() == 0) {
            intent = INVALID_INTENT;
        } else {
            for (const auto& i : intents) {
                intent += " ";
                intent += i.first;
            }

            status = true;
        }

        return status;
    }


    void loadJsonData()
    {
        auto pJsonParser = JsonParserFactory::getInstance();
        pJsonParser->parseJson("/home/bhavith/Bhavith/Development/intent-recognizer-cpp/data/sample.json", m_jsonData);
    }

private:
    std::string strToLower(std::string& value)
    {
        std::transform(value.begin(), value.end(), value.begin(),
            [](unsigned char c){ return std::tolower(c); });
        return value;
    }

    bool getIntentOfWord(const std::string& word, std::string& intent)
    {
        if (word.size() == 0) {
            return false;
        }

        intent = INVALID_INTENT;

        for (const auto& w : m_jsonData) {

            const auto found = std::find_if(w.second.begin(), w.second.end(), [&](auto& wordInternal){
                if (wordInternal.size() == 0) {
                    return false;
                }
                std::string tmp = word;
                std::string tmp2 = wordInternal;
                auto success = strToLower(tmp2) == strToLower(tmp);
                return success;
            });

            if (found != w.second.end()) {
                intent = w.first;
                return true;
            }
        }

        return false;
    }

    void cleanWord(std::string& word)
    {
        const auto pos = word.length() - 1;
        std::vector<char> symbols {'.', '?'};
        auto found = std::find(symbols.begin(), symbols.end(), word[pos]);
        if (found != symbols.end()) {
            word.pop_back();
        }
    }

    JsonData m_jsonData;
};

IntentRecognizer::IntentRecognizer() 
    : m_pImpl(std::make_unique<IntentRecognizer::Impl>())
{

}

IntentRecognizer::~IntentRecognizer()
{

}

auto IntentRecognizer::recognizeIntent(const std::string& sentence, std::string& intent) -> void
{
    try {
        m_pImpl->loadJsonData();
        m_pImpl->getIntent(sentence, intent);
    } catch (JsonParseException& parseException) {
        std::cout << "Failed to parse JSON file : " <<  parseException.what() << "\n";
        intent = "Error occurred while identifying the intent \n";    
    } catch (const std::exception& stdException) {
        std::cout << "Failed to parse JSON file : " <<  stdException.what() << "\n";
        intent = "Error occurred while identifying the intent \n";
    } catch (...) {
        std::cout << "Failed to parse JSON file for unknown reason\n";
        intent = "Error occurred while identifying the intent \n";
    }
}
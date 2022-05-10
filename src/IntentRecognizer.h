#pragma once

#include <string>
#include <memory>

class IntentRecognizer
{
public:
    IntentRecognizer();
    ~IntentRecognizer();
    auto recognizeIntent(const std::string& sentence, std::string& intent) -> void;

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};
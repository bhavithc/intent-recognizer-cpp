/**
 * @file IntentRecognizer.h
 * @author Bhavith C (bhavithc.acharya@gmail.com)
 * @brief Interface of intent recognizer
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <string>
#include <memory>

class IntentRecognizer
{
public:
    /**
     * @brief Construct a new Intent Recognizer object
     */
    IntentRecognizer();

    /**
     * @brief Destroy the Intent Recognizer object
     */
    ~IntentRecognizer();

    /**
     * @brief Recognize the intent of the given sentence
     * 
     * @param[in]  sentence Sentence for which intent to be recognized
     * @param[out] intent   Recognized intent
     */
    auto recognizeIntent(const std::string& sentence, std::string& intent) -> void;

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};
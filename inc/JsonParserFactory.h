/**
 * @file JsonParserFactory.h
 * @author Bhavith C (bhavithc.acharya@gmail.com)
 * @brief JSON parser factory 
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "IJsonParser.h"

#include <memory>

class JsonParserFactory
{
public:
    /**
     * @brief Get the Instance object of JsonParser
     * 
     * @return Pointer to an IJsonParser object
     */
    static auto getInstance() -> std::unique_ptr<IJsonParser>;
};
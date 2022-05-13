/**
 * @file JsonParserFactory.cpp
 * @author Bhavith C (bhavithc.acharya@gmail.com)
 * @brief Implementation of Json paser factory using Factory function
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "JsonParserFactory.h"
#include "QtJsonParser.h"

/**< Refer JsonParserFactory.h for comments**/
auto JsonParserFactory::getInstance() -> std::unique_ptr<IJsonParser>
{
    return std::make_unique<QtJsonParser>();
}
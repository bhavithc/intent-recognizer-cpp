/**
 * @file LoggerHelper.h
 * @author Bhavith C (bhavithc.acharya@gmail.com)
 * @brief Utility helper functionalities for logging
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once 
#include <log4cplus/loggingmacros.h>

extern log4cplus::Logger magic_logger_x7891;

#define LOG_INFO(_x) LOG4CPLUS_INFO(magic_logger_x7891, LOG4CPLUS_TEXT("[" << __FUNCTION__ << "]" << " " << _x))
#define LOG_ERROR(_x) LOG4CPLUS_ERROR(magic_logger_x7891, LOG4CPLUS_TEXT("[" << __FUNCTION__ << "]" << " " << _x))
#define LOG_WARN(_x) LOG4CPLUS_WARN(magic_logger_x7891, LOG4CPLUS_TEXT("[" << __FUNCTION__ << "]" << " " << _x))
#define LOG_DEBUG(_x) LOG4CPLUS_DEBUG(magic_logger_x7891, LOG4CPLUS_TEXT("[" << __FUNCTION__ << "]" << " " << _x))
#define LOG_TRACE(_x) LOG4CPLUS_TRACE(magic_logger_x7891, LOG4CPLUS_TEXT("[" << __FUNCTION__ << "]" << " " << _x))

#ifndef LOG_H
#define LOG_H

#include <iostream>

#define LOG_LEVEL_NORMAL 0
#define LOG_LEVEL_DEBUG  1
#define LOG_LEVEL_ERROR  2

void log(int level, std::string message);


#endif
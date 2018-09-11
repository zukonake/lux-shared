#pragma once

#include <cstdlib>
#include <cassert>
//
#include <tinyformat.h>
//
#include <lux/alias/string.hpp>

namespace util
{

enum LogLevel
{
    ALL = 0,
    TRACE, //temporary information used to find bugs in the program
    DEBUG, //additional information that user can use to fix stuff
    INFO,  //information useful for the user
    WARN,  //it's not as it should be, but we can ignore it
    ERROR, //some error, but we try to fix it
    FATAL, //corrupted state, exit the program
    OFF,
};

extern LogLevel logger_report_level;

template<typename... Args>
void log(const char *prefix, LogLevel level, const char *fmt, Args &&...args)
{
    if(level < logger_report_level) { //TODO constexpr?
        return;
    }
    String output = String("[%s] %s: ") + String(fmt) + String("\n");
    String lvl_str;
    switch(level) {
    case OFF: return;
    case FATAL: lvl_str = "FATAL"; break;
    case ERROR: lvl_str = "ERROR"; break;
    case WARN:  lvl_str = "WARN";  break;
    case INFO:  lvl_str = "INFO";  break;
    case DEBUG: lvl_str = "DEBUG"; break;
    case TRACE: lvl_str = "TRACE"; break;
    default: assert(false);
    }
    if(level == FATAL) {
        auto format_list = tfm::makeFormatList(prefix, lvl_str, args...);
        tfm::vformat(std::cerr, output.c_str(), format_list);
        std::quick_exit(EXIT_FAILURE);
    } else {
        tfm::printf(output.c_str(), prefix, lvl_str, args...);
    }
}


}

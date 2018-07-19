#pragma once

#include <string>
//
#include <tinyformat.h>

namespace util
{

enum Level
{
    OFF,
    CRITICAL,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE,
    ALL = TRACE
};

extern Level logger_report_level;

template<typename... Args>
void log(std::string const &prefix, Level level, std::string const &fmt, Args const &...args)
{
    if(level > logger_report_level)
    {
        return;
    }
    std::string output = prefix == "" ? "" : "[" + prefix + "] ";
    switch(level)
    {
    case OFF:
        return;

    case CRITICAL:
        output += "CRIT: ";
        break;

    case ERROR:
        output += "ERROR: ";
        break;

    case WARN:
        output += "WARN: ";
        break;

    case INFO:
        output += "INFO: ";
        break;

    case DEBUG:
        output += "DEBUG: ";
        break;

    case TRACE:
        output += "TRACE: ";
        break;
    }
    output += fmt;
    output += '\n';
    tfm::printf(output.c_str(), args...);
}


}

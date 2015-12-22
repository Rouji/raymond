#include "Log.h"

#include <stdio.h>
#include <stdarg.h>

namespace raymond
{
namespace io
{

void Log(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
}

void LogError(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

}//io
}//raymond

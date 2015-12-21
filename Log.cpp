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
    printf(fmt, args);
}

void LogError(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, fmt, args);
}

}//io
}//raymond

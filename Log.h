#ifndef __LOG_H
#define __LOG_H

namespace raymond
{
namespace io
{

void Log(const char* fmt, ...);
void LogError(const char* fmt, ...);

}
}

#endif

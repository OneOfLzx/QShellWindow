#ifndef TERMINAL_LOG_STREAM_H
#define TERMINAL_LOG_STREAM_H

#include <fstream>
#include <string>
#include "../Log/Log.h"

class TerminalLogStream
{
public:
    TerminalLogStream();
    ~TerminalLogStream();
    bool Open(std::string path);
    void Read(char* pBuf, unsigned size);
    void ReadAll(char* pBuf, unsigned size);
    void Close();
private:
    bool            isOpen;
    unsigned        pos;
    std::ifstream   f;
};

#endif  //  TERMINAL_LOG_STREAM_H
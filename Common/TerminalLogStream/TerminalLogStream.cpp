#include "TerminalLogStream.h"

TerminalLogStream::TerminalLogStream()
    : isOpen(false)
    , f()
{

}

TerminalLogStream::~TerminalLogStream()
{
    Close();
}

bool TerminalLogStream::Open(std::string path)
{
    bool ret = true;

    if (true == isOpen) ret = false;

    if (true == ret)
    {
        f.open(path, std::ios::in);
        if (!f.is_open()) ret = false;
    }

    if (true == ret) isOpen = true;

    return ret;
}

void TerminalLogStream::Close()
{
    if (true == isOpen)
    {
        f.close();
        isOpen = false;
    }
}

void TerminalLogStream::Read(char* pBuf, unsigned size)
{
    if (true == isOpen)
    {
        f.read(pBuf, size);
    }
}
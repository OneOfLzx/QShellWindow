#include "TerminalLogStream.h"

TerminalLogStream::TerminalLogStream()
    : isOpen(false)
    , f()
    , pos(0)
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
        if (!f.is_open())
        {
            ret = false;
            LOGE("open log stream file failed! path: %s", path.c_str());
        }
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
        pos = 0;
    }
}

void TerminalLogStream::Read(char* pBuf, unsigned size)
{
    if (true == isOpen)
    {
        f.clear();
        f.seekg(pos, std::ios::beg);
        f.read(pBuf, size);
        pos += f.gcount();
    }
}

void TerminalLogStream::ReadAll(char* pBuf, unsigned size)
{
    if (true == isOpen)
    {
        f.clear();
        f.seekg(0, std::ios::beg);
        f.read(pBuf, size);
    }
}
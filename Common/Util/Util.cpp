#include "Util.h"

bool Utils::IsDirExist(const std::string& rDir)
{
    if (nullptr != opendir(rDir.c_str()))
    {
        return true;
    }
    return false;
}

bool Utils::IsFileExist(const std::string& rFilePath)
{
    struct stat statBuf = { };
    if (0 == stat(rFilePath.c_str(), &statBuf))
    {
        return true;
    }
    return false;
}

bool Utils::IsDirEmpty(const std::string& rDir)
{
    bool                ret         = true;
    DIR*                pDirStream  = nullptr;
    struct dirent*      pDirEntry   = nullptr;

    if (nullptr != (pDirStream = opendir(rDir.c_str())))
    {
        while (nullptr != (pDirEntry = readdir(pDirStream)))
        {
            if (0 == strcmp(".", pDirEntry->d_name) ||
                0 == strcmp("..", pDirEntry->d_name))
            {
                continue;
            }

            ret = false;
            break;
        }
    }

    return ret;
}

bool Utils::MakeDir(const std::string& rDir)
{
    if (IsDirExist(rDir)) return false;
    int ret = ::mkdir(rDir.c_str(), 0755);
    if (0 != ret)
    {
        return false;
    }
    return true;
}

bool Utils::DeleteDir(const std::string& rDir)
{
    if (!IsDirExist(rDir)) return false;
    int ret = ::rmdir(rDir.c_str());
    if (0 != ret)
    {
        return false;
    }
    return true;
}

std::string Utils::GetPath(const std::string& rDir, const std::string& rName)
{
    const char separator = '/';
    if (rDir.length() > 0 && rDir[rDir.length() - 1] == separator)
    {
        return rDir + rName;
    }
    else
    {
        return rDir + separator + rName;
    }
}
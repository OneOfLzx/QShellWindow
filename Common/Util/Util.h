#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <chrono>
#include <fstream>

class Utils
{
public:
    static bool IsDirExist(const std::string& rDir);
    static bool IsFileExist(const std::string& rFilePath);
    static bool IsDirEmpty(const std::string& rDir);
    static bool MakeDir(const std::string& rDir);
    static bool DeleteDir(const std::string& rDir);
    static std::string GetPath(const std::string& rDir, const std::string& rName);
};


#endif  //  UTILS_H
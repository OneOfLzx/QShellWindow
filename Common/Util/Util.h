#ifndef QSHELLWINDOW_UTILS_H
#define QSHELLWINDOW_UTILS_H

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
    static std::string GetAbsolutePath(const std::string& rPath);
    static void FGetLine(FILE* f, char* buf);
};


#endif  //  QSHELLWINDOW_UTILS_H
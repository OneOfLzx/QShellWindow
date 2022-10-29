#ifndef TERMINAL_WRAPPER_H
#define TERMINAL_WRAPPER_H

#include <string>
#include <stdio.h>
#include <fstream>
#include "../Common/TerminalLogStream/TerminalLogStream.h"
#include "../Common/Util/Util.h"

#define TERMINAL_GET_INPUT_SCRIPT_FILE_NAME         "GetInputScript.sh"
#define TERMINAL_EXECUTE_SCRIPT_FILE_NAME           "ExecuteScript.sh"
#define TERMINAL_TEMP_SCRIPT_FILE_NAME              "Tmp.sh"
#define TERMINAL_LOG_FILE_NAME                      "Log.txt"
#define TERMINAL_EXIT_CMD                           "exit"
#define TERMINAL_STOP_COMMAND_CMD                   "WrapperStopCMD"

enum TerminalWrapperResult
{
    TerminalWrapperResultSuccess = 0,
    TerminalWrapperResultOpened,
    TerminalWrapperResultTempDirError,
    TerminalWrapperResultTempFileError,
    TerminalWrapperResultOpenPipeFailed
};

class TerminalWrapper
{
public:
    TerminalWrapper();
    ~TerminalWrapper();
    TerminalWrapperResult Open(const std::string& rTempDir, TerminalLogStream& rLogStm);
    void ExecuteCommand(const std::string& rCmd);
    void StopCurrentCommand();
    void Close();
private:
    bool SendCommand(const std::string& rCmd);

    bool        isOpen;
    FILE*       pPipeFile;
    std::string tempDir;
};

const std::string GetInputScript;
const std::string ExecuteScript;

#endif  //  TERMINAL_WRAPPER_H
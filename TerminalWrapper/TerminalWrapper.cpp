#include "TerminalWrapper.h"

TerminalWrapper::TerminalWrapper()
    : isOpen(false)
    , pPipeFile(nullptr)
    , tempDir()
{

}

TerminalWrapper::~TerminalWrapper()
{
    Close();
}

TerminalWrapperResult TerminalWrapper::Open(const std::string& rTempDir, TerminalLogStream& rLogStm)
{
    TerminalWrapperResult   ret                 = TerminalWrapperResultSuccess;
    std::string             getInputScriptPath  = Utils::GetPath(rTempDir, TERMINAL_GET_INPUT_SCRIPT_FILE_NAME);
    std::string             executeScriptPath   = Utils::GetPath(rTempDir, TERMINAL_GET_INPUT_SCRIPT_FILE_NAME);
    std::string             logPath             = Utils::GetPath(rTempDir, TERMINAL_LOG_FILE_NAME);

    if (true == isOpen) ret = TerminalWrapperResultOpened;

    if (TerminalWrapperResultSuccess == ret)
    {
        Utils::MakeDir(rTempDir);
        if (!Utils::IsDirExist(rTempDir)) ret = TerminalWrapperResultTempDirError;
        if (!Utils::IsDirEmpty(rTempDir)) ret = TerminalWrapperResultTempDirError;
    }

    if (TerminalWrapperResultSuccess == ret)
    {
        std::ofstream w;
        w.open(getInputScriptPath, std::ios::out | std::ios::trunc);
        if (w.is_open())
        {
            w.write(GetInputScript.c_str(), GetInputScript.length() + 1);
        }
        else
        {
            ret = TerminalWrapperResultTempFileError;
        }
        w.close();
    }

    if (TerminalWrapperResultSuccess == ret)
    {
        std::ofstream w;
        w.open(executeScriptPath, std::ios::out | std::ios::trunc);
        if (w.is_open())
        {
            w.write(ExecuteScript.c_str(), ExecuteScript.length() + 1);
        }
        else
        {
            ret = TerminalWrapperResultTempFileError;
        }
        w.close();
    }

    if (TerminalWrapperResultSuccess == ret)
    {
        std::string cmd = "";
        cmd = "chmod a=rwx " + getInputScriptPath;
        system(cmd.c_str());
        cmd = "chmod a=rwx " + executeScriptPath;
        system(cmd.c_str());
    }

    if (TerminalWrapperResultSuccess == ret)
    {
        std::string cmd = std::string(". ") + getInputScriptPath + " | " +
                        std::string(". ") + executeScriptPath + " 2&> " + logPath;
        pPipeFile       = popen(cmd.c_str(), "w");
        if (nullptr == pPipeFile)
        {
            ret = TerminalWrapperResultOpenPipeFailed;
        }
    }

    if (TerminalWrapperResultSuccess == ret)
    {
        isOpen      = true;
        tempDir     = rTempDir;
        rLogStm.Open(logPath);
        SendCommand("cd ~");
    }

    return ret;
}

void TerminalWrapper::ExecuteCommand(const std::string& rCmd)
{
    if (!isOpen) return;
    SendCommand(rCmd);
}

void TerminalWrapper::StopCurrentCommand()
{
    if (!isOpen) return;
    SendCommand(TERMINAL_STOP_COMMAND_CMD);
}
    
void TerminalWrapper::Close()
{
    if (!isOpen) return;
    SendCommand(TERMINAL_EXIT_CMD);
    fclose(pPipeFile);
}

bool TerminalWrapper::SendCommand(const std::string& rCmd)
{
    std::string command = rCmd + "\n";
    const int   memSize = 1;
    int         nMem    = fwrite(command.c_str(), command.length() + 1, memSize, pPipeFile);
    return nMem == memSize;
}
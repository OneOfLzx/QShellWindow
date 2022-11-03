#include <unistd.h>
#include "../../TerminalWrapper/TerminalWrapper.h"
#include "../../Common/ThreadPool/ThreadPool.h"

bool isClose = false;

void PrintTerminalLog(TerminalLogStream* logger)
{
    char logBuf[1024];
    while (true)
    {
        if (isClose) break;

        memset(logBuf, 0, sizeof(logBuf));
        logger->Read(logBuf, sizeof(logBuf));
        std::cout<<logBuf;
        usleep(100000);
    }
}

int main()
{
    const std::string   cmds[] = {
        "date",
        "ls",
        "cd ..",
        "ls",
        "date",
    };
    const std::string   tempDir = Utils::GetAbsolutePath("~/TerminalWrapperTest");
    TerminalWrapper     w;
    TerminalLogStream   logger;
    ThreadPool          tp(1);

    Utils::DeleteDir(tempDir);
    int ret = w.Open(tempDir, logger);
    if (TerminalWrapperResultSuccess != ret)
    {
        LOGE("Open terminal wrapper failed! code: %d", ret);
        return 0;
    }

    tp.enqueue(PrintTerminalLog, &logger);

    for (int i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++)
    {
        w.ExecuteCommand(cmds[i]);
    }

    ///////////////////////////////////////
    // test stop current command (Ctrl C)
    sleep(3); // sleep 3 second to wait previous command done
    LOGE("");
    LOGD("======= Start testing stop current command (Ctrl C) ========");
    w.ExecuteCommand("sleep 10");
    w.StopCurrentCommand();
    //////////////////////////////////////

    w.Close();

    sleep(1); // wait for printing log
    isClose = true;
    logger.Close();
}
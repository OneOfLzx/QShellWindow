#include "TerminalWrapper.h"

const std::string GetInputScript =
"#!/bin/bash\n"

"executeScriptPath=$1\n"
"thisScriptFileName=\"" TERMINAL_GET_INPUT_SCRIPT_FILE_NAME "\"\n"

"while [ true ]\n"
"do\n"
"    read CMD\n"

"    if [ \"$CMD\" = \"" TERMINAL_EXIT_CMD "\" ]\n"
"    then\n"
"        # Exit signal, exit\n"
"        break\n"
"    elif [ \"$CMD\" = \"" TERMINAL_STOP_COMMAND_CMD "\" ]\n"
"    then\n"
"        # Ctrl C signal, kill children process of ExecuteScript.sh\n"
"        executeScriptPID=`ps -ef | grep $executeScriptPath | grep -v $thisScriptFileName | grep -v grep | awk '{print $2}'`\n"
"        childPID=`ps -ef | grep $executeScriptPID | grep -v grep | awk '{print $2}' | grep -v $executeScriptPID`\n"
"        if [ \"$childPID\" != \"\" ] # Sometime, childPID may be nil because of some error\n"
"        then\n"
"            echo \"" TERMINAL_STOP_COMMAND_CMD "\"\n"
"            kill -9 $childPID\n"
"        fi\n"
"    else\n"
"        echo $CMD\n"
"    fi\n"
"done\n"
"echo \"" TERMINAL_EXIT_CMD "\"\n"
"\0";

const std::string ExecuteScript =
"#!/bin/bash -i\n"

"scriptPath=$(cd \"$(dirname $(readlink -f ${BASH_SOURCE[0]}))\"; pwd)\n"

"while true\n"
"do\n"
"    # echo -e \"\\033[32m\\033[1m\"$(date)$USER@\"\\033[0m\"\"\\033[34m\\033[1m$(pwd)\\033[0m: \\c\"\n"
"    echo -e \"$USER@$(pwd):   \\c\"\n"

"    read CMD\n"

"    if [ \"$CMD\" = \"" TERMINAL_EXIT_CMD "\" ]\n"
"    then\n"
"        echo \"EXE read Exit signal, exit\"\n"
"        break\n"
"    elif [ \"$CMD\" = \"" TERMINAL_STOP_COMMAND_CMD "\" ]\n"
"    then\n"
"        echo \"^C\"\n"
"    else\n"
"        echo $CMD\n"

"        shellText=\"#!/bin/bash -i\\n$CMD\"\n"
"        echo -e $shellText > $scriptPath/tmp.sh\n"
"        . $scriptPath/tmp.sh\n"
"    fi\n"
"done\n"
"\0";
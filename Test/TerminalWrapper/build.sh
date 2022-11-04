#! /bin/bash

srcDirList=". ../../Common ../../TerminalWrapper"

dirPath=""
cppPath=""
for srcDir in $srcDirList
do
    srcDir=`realpath $srcDir`
    incPath=`find $srcDir -type d`
    cppPath="$cppPath `find $srcDir | grep .cpp`"

echo `find $srcDir | grep .cpp`

    for dir in $incPath
    do
        dirPath="$dirPath-I $dir "
    done
done

cmd="g++ $cppPath $dirPath -o demo -lpthread"

echo $cmd
$cmd
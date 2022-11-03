#! /bin/bash

incPath=`find -type d`
cppPath=`find -name *.cpp`
dirPath=""

for dir in $incPath
do
    dirPath="$dirPath-I $dir "
done

cmd="g++ $cppPath $dirPath -o demo -lpthread"

echo $cmd
$cmd
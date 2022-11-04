#! /bin/bash

qmake
make

# Get Target Name
pro_file_name=`ls | grep ".pro"`
target_name=`cat $pro_file_name | grep "TARGET"`
target_name=${target_name##*= }
#

chmod 777 $target_name
./$target_name
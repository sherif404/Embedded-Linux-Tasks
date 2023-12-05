#! /bin/bash

##################################
#Author: Sherif Adel Refay 
#Date: 4/8/2023
#Title: Task 1
#file_permission: chmod 740 Task1_Sherif_Adel.sh
##################################

#file permission command used terminal before execute bash script: chmod 740 Task1_Sherif_Adel.sh  

s_path="$1" 
d_path="$2" 


if [ -d "$d_path" ]; then
    cp "$s_path" "$d_path"

    echo "File copied successfully."
    echo "$s_path -> $d_path"

else
    echo "The directory $d_path not found... Creating it."
    mkdir -p "$d_path"
    cp "$s_path" "$d_path"
    echo "File copied successfully."
    echo "$s_path -> $d_path"

fi

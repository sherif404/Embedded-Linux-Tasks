#!/bin/bash

source_dir="/home/sherif/Desktop/dir1"
backup_dir="/backup"

timestamp=$(date +%Y-%m-%d)
backup_path="$backup_dir/backup_$timestamp"

#Backup using rsync
rsync -av --delete --link-dest="$backup_dir/backup_latest" "$source_dir" "$backup_path"

#Removee old backups,and keeping only the last five
cd "$backup_dir"
ls -td backup_* | tail -n +6 | xargs -r rm -rf#!/bin/bash
echo "Done :)"



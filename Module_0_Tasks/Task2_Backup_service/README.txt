##Brief Explanation
      
    • The backup script will be executed daily at 2 AM according to the schedule specified. It will create a timestamped backup directory within the specified backup directory and perform a full backup using rsync. It will also delete old backups, keeping only the last five.

    • In case you want to modify the timer or make it manually, use the crontab command, and edit the time of backup or remove it to be manual..

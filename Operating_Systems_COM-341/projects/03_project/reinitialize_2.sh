#!/bin/bash

bash ./create_file_system.krffs.sh
bash ./mount.sh
cp create_files.py mount_point
cp test.sh mount_point
cd mount_point
python3 create_files.py
bash test.sh
rm 2_test.txt 5_test.txt
head -c 6621838 /dev/zero > full.txt
cd ..
ls -alh mount_point
bash ./unmount.sh

#!/bin/sh
./astyle.sh
./astyle-remove-backup.sh
./remove-tilda-backup.sh
tar -zcvf ../Backup/BackGenEngine/BackGenEngine\(`date +%d%m%y`\).tar.gz ../BackGenEngine

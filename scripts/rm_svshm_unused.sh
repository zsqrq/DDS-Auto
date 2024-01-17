#!/bin/bash

# 获取所有共享内存段的ID
shmids=$(ipcs -m | awk '/^0x/ {print $2}')

# 遍历每个ID并删除
for id in $shmids
do
    ipcrm -m $id
done

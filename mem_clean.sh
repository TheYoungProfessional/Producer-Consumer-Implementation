#!/bin/bash
killall producer consumer 2>/dev/null
rm /dev/shm/my_shared_mem 2>/dev/null
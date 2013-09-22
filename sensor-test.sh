#!/bin/bash
for ((;;)); do
./WB-Sensor "humidity:%h pressure:%p board_tmp:%b int_tmp:%r ext_tmp:%o\n"
done

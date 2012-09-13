#!/bin/bash
while true; do 
    inotifywait -e modify *.cpp
    make
    killall course2
    ./course2 &
    sleep 0.3
    xte "keydown Super_L"  "keydown Left" "keyup Left" "keyup Super_L"
done

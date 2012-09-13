#!/bin/bash
while true; do 
    inotifywait -e modify *.cpp
    killall course2
    make
    if [ $? -eq 0 ] ; then
        ./course2 &
    fi
    sleep 0.3
#    i3-msg move container to workspace 3;
#    i3-msg workspace 2;
    xte "keydown Super_L"  "keydown Left" "keyup Left" "keyup Super_L"
done

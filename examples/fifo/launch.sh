#!/bin/bash

function close_all {
    killall -9 alsa-capture
    killall -SIGINT shouter
}

trap close_all SIGINT 


./alsa-capture &

sleep 1

./shouter 


#!/bin/bash

function close_all {
    kill -9 $CAPTURE_PID
}

trap close_all SIGINT 


eval "./alsa-capture &"

CAPTURE_PID=$!

sleep 1

./shouter 


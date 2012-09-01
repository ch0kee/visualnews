#!/bin/bash

recordmydesktop --no-sound -o vnews.ogv &
PID=`pgrep -x recordmydesktop`
sleep 3
kill -SIGINT $PID


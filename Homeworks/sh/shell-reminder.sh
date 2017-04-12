#!/bin/bash

argc=$#

argv[0]=$0
argv[1]=$1
argv[2]=$2
argv[3]=$3
argv[4]=$4

_help () {
    echo "Usage: shell-reminder [OPTION] [VALUE]..."
    echo "	-t Set reminder rotation time (DEFALT: 1hour)"
    echo "	-m Set reminder message (DEFALT: \"Stretching time!\")"
    echo "	-h Help"
    exit 0
}

main () {
    interval=3600
    message="Notification!"
    i=1

    if [ $argc -ge 1 ]
    then
        while [ $i -le $argc ]
        do
            case ${argv[$i]} in
                -t ) interval=$(( ${argv[$(($i+1))]} + 9 ));;
                -m ) message=${argv[$(( $i+1 ))]};;
                -h ) _help;;
            esac

            i=$(( $i+2 ))
        done
    fi

    watch -n $interval "notify-send $message"

    exit 0
}

main

#!/bin/bash

argc=$#

argv[0]=$0
argv[1]=$1
argv[2]=$2
argv[3]=$3
argv[4]=$4
argv[5]=$5
argv[6]=$6
argv[7]=$7

_help () {
    echo "Usage: new-shell-reminder [OPTION]* [VALUE]..."
    echo "	-c Set a command to execute in \$VALUE sec (default - echo wake up!)"
    echo "	-m Set a message to show in \$VALUE sec (default - \"wake up!\")"
    echo "	-t Set timer for this amount of sec (default - 5s)" 
    echo "	--beep Beep on notification (default - false)" 
    echo "	-h Help"
    exit 0
}

init_vars () {
    r_time=5
    message="Wake up!"
    cmd="echo wake up!"
    i=1
    beep=false
    cmd_flag=false;
    mes_flag=false;

    if [ $argc -ge 1 ]
    then
        while [ $i -le $argc ]
	do
	    case ${argv[$i]} in
		-c ) cmd=${argv[$(($i+1))]} cmd_flag=true;;
                -m ) message=${argv[$(($i+1))]} mes_flag=true;;
		-t ) r_time=${argv[$(($i+1))]};;
		--beep ) beep=true;;
		-h ) _help;;
	    esac
	    i=$(($i+2))
	done
    fi

   
}

init_vars
sleep ${r_time}s
if [ mes_flag ]; then notify-send -t 10000 $message; fi;
if [ cmd_flag ]; then $cmd; fi;
if [ $beep ]; then echo beep; fi;
# EOF


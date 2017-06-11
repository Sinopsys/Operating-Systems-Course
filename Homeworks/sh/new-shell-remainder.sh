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
    echo "Usage: new-shell-reminder.sh [OPTION] [VALUE]..."
    echo "	-c Set a command to (default - echo wake up!)"
    echo "	-m Set a message to (default - \"Wake up!\")"
    echo "	-t Set timer for this amount of 's/m/h/d' (default - 5s)" 
    echo "	-date Set a notification to pop up on a particular TIME 'HH:MM:SS'" 
    echo "	-h Help"
    exit 0
}

    
init_vars () {
    r_time="5s"
    message="Wake-up!"
    cmd="echo wake up!"
    i=1
    cmd_flag=false
    mes_flag=false
    t_flag=false
    new_date=235959
    date_flag=false
    current_date=$(date +%T | sed -e s/://g)
    echo $current_date

    if [ $argc -ge 1 ]
    then
        while [ $i -le $argc ]
	do
	    case ${argv[$i]} in
		-c ) cmd=${argv[$(($i+1))]} cmd_flag=true;;
                -m ) message=${argv[$(($i+1))]} mes_flag=true;;
		-t ) r_time=${argv[$(($i+1))]} t_flag=true;;
        -date ) new_date=${argv[$(($i+1))]} date_flag=true;;
		-h ) _help;;
	    esac
	    i=$(($i+2))
	done
    fi
    new_date=`echo $new_date | sed -e s/://g`
    echo $new_date
   
}

init_vars

if $time_flag; then sleep ${r_time}; fi

echo $new_date
if $date_flag;
    then
	while [[ $current_date -ge $new_date ]];
	do
            current_date=$(date +%T | sed -e s/://g)
	done;
fi
	


if $mes_flag; then notify-send -t 10000 $message; fi
if $cmd_flag; then $cmd; fi

# EOF



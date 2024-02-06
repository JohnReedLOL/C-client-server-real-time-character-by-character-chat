#!/bin/bash -e

OUTPUT=$(ifconfig)
FLAG=0

for STRING in $OUTPUT
do
  if [ $FLAG -eq 0 ]
  then
    if [ $STRING = "inet" ]
    then
      ((FLAG=FLAG+1))
      # echo "Incremented flag."
    fi
  elif [ $FLAG -eq 1 ]
  then
    # echo "Flag is 1 and STRING is $STRING ."
    ((FLAG=FLAG+1))
  elif [ $FLAG -eq 2 ]
  then
    if [ $STRING = "inet" ]
    then
      ((FLAG=FLAG+1))
      # echo "Incremented flag again."
    fi
  elif [ $FLAG -eq 3 ]
  then
    echo "Your local ip address is $STRING ."
    # ((FLAG=FLAG+1))
    exit 0
  fi
done
exit 1

#!/bin/sh

./test
EXIT_STATUS=$?
if [ $EXIT_STATUS != 0 ] ; then
    echo $EXIT_STATUS
    exit $EXIT_STATUS
fi

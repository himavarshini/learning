#!/bin/sh

case $1 in
	-a | -b | -c \
		| -d | -test )
	ar="ar $1"
	;;
esac

echo " ar is $ar"


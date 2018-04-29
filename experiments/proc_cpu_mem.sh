#!/bin/bash

proc=$1

ps -C $proc -o %cpu,%mem --noheader

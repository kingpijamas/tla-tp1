#!/bin/bash

PARAM=$1;

LINKS=$(ls | grep -e '\.[h|c]')

$(flex "$PARAM.l $LINKS")
gcc -o "$PARAM" lex.yy.c -lfl $LINKS
rm lex.yy.c

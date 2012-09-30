#!/bin/bash

PARAM=$1

$(flex "$PARAM.l")
gcc -o "$PARAM" lex.yy.c -lfl
rm lex.yy.c

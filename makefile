CC = gcc
FLEX = flex
FILES = ./tp.c ./utils.c ./LinkedList.c ./grammarProcessing.c ./Grammar.c ./Automaton.c ./automatonProcessing.c
OUT_DIR=./
OUT_EXE=tp
COPTS= -Wall -g
LDOPTS= -lfl
MATH = -lm

FL_FILES = ./tp.l
CC_FILES = ./tp.yy.c ./tp.c
tp: $(FILES) $(FL_FILES)
	$(CC) $(COPTS) -o $(OUT_EXE) $(FILES) $(CC_FILES) $(LDOPTS)
	-rm -f tp.yy.c

tp.yy.c:	
	$(FLEX) -o tp.yy.c $(FL_FILES)

all: tp

clean_all:
	-rm -f *.o core
	-rm -f tp

#rebuild: clean build

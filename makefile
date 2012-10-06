CC = gcc
FLEX = flex
FILES = lex.yy.c utils.c LinkedList.c grammarProcessing.c Grammar.c Automaton.c automatonProcessing.c
LEXFILES = tp.l
OUT_EXE=tp
COPTS= -Wall -g

tp:
	$(FLEX) $(LEXFILES)
	$(CC) $(COPTS) -o $(OUT_EXE) $(FILES)
	-rm -f *.yy.c

clean:
	-rm -f *.o core
	-rm -f $(OUT_EXE)

#rebuild: clean build

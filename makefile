
         # Basic Makefile -- provides explicit rules
         # Creates "myprogram" from "scan.l" and "myprogram.c"
         #
         LEX=flex
         tp: tp.o 

         tp.o: tp.c LinkedList.c
     
         tp.c: tp.l

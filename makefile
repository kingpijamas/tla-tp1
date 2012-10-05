
         # Crea tp.c
         #
         LEX=flex
         tp: tp.o

         tp.o: tp.c LinkedList.c
     
         tp.c: tp.l

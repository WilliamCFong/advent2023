libsrc = $(wildcard lib/*.c)
libobj = $(libsrc:.c=.o)

day_1: day_1.o

day_2: day_2.o

day_1.o: days/day_1.c 
	gcc -c days/day_1.c

day_2.o: days/day_2.c $(obj)
	gcc -c days/day_2.c

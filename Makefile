CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS= ransom.o
EXEC=prog.exe
RM=rm -rf *o *.exe

$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o prog.exe
	

ransom.o: ransom.c
	$(CC) $(CFLAGS) -c ransom.c
	
clean:
	$(RM)
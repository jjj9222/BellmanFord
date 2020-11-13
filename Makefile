#Define Varibles to hold the programs and Objects
SOURCE = dvrouting.c
PROG = dvrouting
OBJS = $(patsubst %.c, %.o, $(SOURCE))
CC = gcc
CFLAGS = -std=c99 -Wall -O1 -pedantic -g



# Don't print out each executed line
.SILENT:

#The default is to build the app
all: $(PROG)

help:
	echo "make options: all, clean, help"

#Rebuild the solution if any .o file
$(PROG): $(OBJS)
	echo "linking dvrouting"
	$(CC) $(CFLAGS) dvrouting.c -o dvrouting

.c.o: 
	echo "Compile $<"
	$(CC) $(CFLAGS) -c $<


#Remove all of the files we build
clean:
	-rm -f $(PROG)
	-rm -f *.o
	-rm -f $(QSOUT)
	-rm -f $(MEMOUT)

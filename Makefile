# change application name here (executable output name)
TARGET=slide-calculator.out

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=
# warnings
WARN=

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=    main.o


all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) main.o
	    
clean:
	rm -f *.o $(TARGET)

run: all
	./$(TARGET) 

install: run


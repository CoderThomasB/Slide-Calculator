# change application name here (executable output name)
TARGET=slide-calculator.out

# compiler
CC=gcc
# debug
DEBUG=#-g
# optimisation
OPT=-pipe -Ofast
# warnings
WARN=-Wextra

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

all: build

build: main.o
	$(LD) -o $(TARGET) main.o $(LDFLAGS)
	echo "Done"

main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB)  -o main.o
	    
clean:
	rm -f *.o $(TARGET)

run: build
	./$(TARGET) 

install: build
	#mkdir /etc/slide-calculator/ || echo "dir is thare"
	#mkdir /etc/slide-calculator/glade/ || echo "dir is thare"
	#cp ./remove.sh /etc/slide-calculator/
	#cp ./glade/Main.glade /etc/slide-calculator/glade/
	mkdir /usr/share/slide-calculator || echo "dir is thare"
	cp ./remove.sh /usr/share/slide-calculator
	mkdir /usr/share/slide-calculator/glade/ || echo "dir is thare"
	cp ./glade/Main.glade /usr/share/slide-calculator/glade/

	cp ./slide-calculator.out /usr/bin/slide-calculator

remove:
	rm -r /usr/share/slide-calculator
	rm /usr/bin/slide-calculator

#gtk:
#	sudo apt-get install libgtk-3-dev


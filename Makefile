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

all: deb

deb: build
	mkdir ./slide-calculator-1.0/usr/ || echo "dir is thare"
	mkdir ./slide-calculator-1.0/usr/bin/ || echo "dir is thare"
	cp ./slide-calculator.out ./slide-calculator-1.0/usr/bin/slide-calculator

	mkdir ./slide-calculator-1.0/usr/share/ || echo "dir is thare"
	mkdir ./slide-calculator-1.0/usr/share/slide-calculator/ || echo "dir is thare"
	mkdir ./slide-calculator-1.0/usr/share/slide-calculator/glade/ || echo "dir is thare"
	cp ./glade/Main.glade ./slide-calculator-1.0/usr/share/slide-calculator/glade/\

	dpkg-deb --build ./slide-calculator-1.0/

build: main.o
	$(LD) -o $(TARGET) main.o $(LDFLAGS)
	echo "Done"

main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB)  -o main.o
	    
clean:
	rm -f *.o $(TARGET)
	rm slide-calculator.out

run: build
	./$(TARGET) 

install: deb
	dpkg -i slide-calculator-1.0.deb


remove:
	dpkg -r slide-calculator

#gtk:
#	sudo apt-get install libgtk-3-dev


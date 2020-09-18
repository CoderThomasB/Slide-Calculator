
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

mkdir:
	mkdir ./bin/ || echo "dir is thare"

	mkdir ./slide-calculator-1.0/usr/ || echo "dir is thare"
	mkdir ./slide-calculator-1.0/usr/bin/ || echo "dir is thare"

	mkdir ./slide-calculator-1.0/usr/share/ || echo "dir is thare"
	mkdir ./slide-calculator-1.0/usr/share/slide-calculator/ || echo "dir is thare"
	mkdir ./slide-calculator-1.0/usr/share/slide-calculator/glade/ || echo "dir is thare"

deb: mkdir build
	cp ./bin/slide-calculator.out ./slide-calculator-1.0/usr/bin/slide-calculator

	cp ./glade/Main.glade ./slide-calculator-1.0/usr/share/slide-calculator/glade/\

	dpkg-deb --build ./slide-calculator-1.0/

build: mkdir main.o
	$(LD) -o ./bin/slide-calculator.out ./bin/main.o $(LDFLAGS)
	echo "Done"

main.o: mkdir src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB)  -o ./bin/main.o
	    
clean:
	rm -f *.o || echo ""
	rm $(TARGET) || echo ""
	rm -f ./slide-calculator-1.0/usr/ || echo ""
	rm ./bin/slide-calculator.out || echo ""

run: build
	./bin/slide-calculator.out

install: deb
	dpkg -i slide-calculator-1.0.deb


remove:
	dpkg -r slide-calculator

#gtk:
#	sudo apt-get install libgtk-3-dev


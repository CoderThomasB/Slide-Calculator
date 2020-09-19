
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

mkdir-deb:
	mkdir ./slide-calculator-1.0/usr/ || echo "dir is thare"
	mkdir ./slide-calculator-1.0/usr/bin/ || echo "dir is thare"

	mkdir ./slide-calculator-1.0/usr/share/ || echo "dir is thare"
	mkdir ./slide-calculator-1.0/usr/share/slide-calculator/ || echo "dir is thare"
	mkdir ./slide-calculator-1.0/usr/share/slide-calculator/glade/ || echo "dir is thare"

mkdir:
	mkdir ./bin/ || echo "dir is thare"


deb: mkdir-deb build
	cp ./bin/slide-calculator.out ./slide-calculator-1.0/usr/bin/slide-calculator

	cp ./glade/Main.glade ./slide-calculator-1.0/usr/share/slide-calculator/glade/

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

run: install
	slide-calculator

run-deb: install-deb
	slide-calculator

install: build
	sudo cp ./bin/slide-calculator.out /usr/bin/slide-calculator
	sudo cp ./glade/Main.glade /usr/share/slide-calculator/glade/

install-deb: deb
	sudo dpkg -i slide-calculator-1.0.deb

remove-deb:
	sudo dpkg -r slide-calculator

remove:
	sudo rm /usr/bin/slide-calculator
	sudo rm -r /usr/share/slide-calculator

#gtk:
#	sudo apt-get install libgtk-3-dev


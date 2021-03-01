$(eval VERSION=$(shell git describe --tags))
IFLAGS = -I include
CPATH = src/
INC = include/
OPATH = obj/
DOC = doc/
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11


vpath %.h include
vpath %.c src

jdlv: libjeu.a
	gcc -o bin/jdlv libjeu.a
libjeu.a: main.o grille.o jeu.o io.o
	ar -crv libjeu.a $(OPATH)main.o $(OPATH)grille.o $(OPATH)jeu.o $(OPATH)io.o
main.o: main.c grille.h jeu.h io.h 
	gcc -c -g $(CPATH)main.c $(IFLAGS)
	mv main.o $(OPATH)
grille.o: grille.c grille.h
	gcc -c -g $(CPATH)grille.c $(IFLAGS)
	mv grille.o $(OPATH)
jeu.o: jeu.c jeu.h
	gcc -c -g $(CPATH)jeu.c $(IFLAGS)
	mv jeu.o $(OPATH)
io.o: io.c io.h
	gcc -c -g $(CPATH)io.c $(IFLAGS)
	mv io.o $(OPATH)

clean: 
	rm obj/* bin/*


dist: 
	tar -cJf distr.tar.xz src/ include/ doc/ Doxyfile makefile 


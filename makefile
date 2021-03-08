CC = gcc
IFLAGS = -I include
CPATH = src/
INC = include/
OPATH = obj/
DOC = doc/
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11


vpath %.h $(INC)
vpath %.c $(CPATH)
vpath %.o $(OPATH)

jdlv: libjeu.a
	$(CC) -o bin/jdlv libjeu.a
libjeu.a: main.o grille.o jeu.o io.o
	ar -crv libjeu.a $(OPATH)main.o $(OPATH)grille.o $(OPATH)jeu.o $(OPATH)io.o
main.o: main.c grille.h jeu.h io.h 
	$(CC) -c -g $(CPATH)main.c $(IFLAGS)
	mv main.o $(OPATH)
grille.o: grille.c grille.h
	$(CC) -c -g $(CPATH)grille.c $(IFLAGS)
	mv grille.o $(OPATH)
jeu.o: jeu.c jeu.h
	$(CC) -c -g $(CPATH)jeu.c $(IFLAGS)
	mv jeu.o $(OPATH)
io.o: io.c io.h
	$(CC) -c -g $(CPATH)io.c $(IFLAGS)
	mv io.o $(OPATH)

clean: 
	rm obj/* bin/* *.a


dist: 
	tar -cJf distr.tar.xz src/ include/ doc/ Doxyfile makefile grilles/


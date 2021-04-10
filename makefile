CC = gcc
IFLAGS = -I include
CPATH = src/
INC = include/
OPATH = obj/
BPATH = bin/
DOC = doc/

CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
MODE=CAIRO

CFLAGS = $(CPPFLAGS) -Wall -c -g


vpath %.h $(INC)
vpath %.c $(CPATH)
vpath %.o $(OPATH)

jdlv: libjeu.a
	@mkdir -p $(BPATH)
	$(CC) -DMODE$(MODE) -o $(BPATH)jdlv libjeu.a $(LDFLAGS)

libjeu.a: main.o grille.o jeu.o io.o
	ar -crv libjeu.a $(OPATH)main.o $(OPATH)grille.o $(OPATH)jeu.o $(OPATH)io.o


%.o: %.c
	@mkdir -p $(OPATH)
	$(CC) -DMODE$(MODE) $(CFLAGS) -o $(OPATH)$@ $^ $(IFLAGS)


clean: 
	rm obj/* bin/* *.a
	rm -r doc/html doc/latex


dist: 
	tar -cJf distr.tar.xz src/ include/ Doxyfile makefile grilles/

doc:
	@mkdir -p $(DOC)
	doxygen


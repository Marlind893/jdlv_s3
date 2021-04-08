CC = gcc
IFLAGS = -I include
CPATH = src/
INC = include/
OPATH = obj/
BPATH = bin/
DOC = doc/
<<<<<<< HEAD

CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
MODE=CAIRO

CFLAGS = $(CPPFLAGS) -Wall -c -g
=======
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11

CFLAGS = -Wall -c -g
>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b


vpath %.h $(INC)
vpath %.c $(CPATH)
vpath %.o $(OPATH)

jdlv: libjeu.a
	@mkdir -p $(BPATH)
<<<<<<< HEAD
	$(CC) -DMODE$(MODE) -o $(BPATH)jdlv libjeu.a $(LDFLAGS)

=======
	$(CC) -o $(BPATH)jdlv libjeu.a
>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b
libjeu.a: main.o grille.o jeu.o io.o
	ar -crv libjeu.a $(OPATH)main.o $(OPATH)grille.o $(OPATH)jeu.o $(OPATH)io.o


%.o: %.c
	@mkdir -p $(OPATH)
<<<<<<< HEAD
	$(CC) -DMODE$(MODE) $(CFLAGS) -o $(OPATH)$@ $^ $(IFLAGS)
=======
	$(CC) $(CFLAGS) -o $(OPATH)$@ $^ $(IFLAGS)
>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b


clean: 
	rm obj/* bin/* *.a


dist: 
	tar -cJf distr.tar.xz src/ include/ doc/ Doxyfile makefile grilles/

<<<<<<< HEAD
doc:
	@mkdir -p $(DOC)

=======
>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b

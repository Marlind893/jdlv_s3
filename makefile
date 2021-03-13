CC = gcc
IFLAGS = -I include
CPATH = src/
INC = include/
OPATH = obj/
BPATH = bin/
DOC = doc/
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11

CFLAGS = -Wall -c -g


vpath %.h $(INC)
vpath %.c $(CPATH)
vpath %.o $(OPATH)

jdlv: libjeu.a
	@mkdir -p $(BPATH)
	$(CC) -o $(BPATH)jdlv libjeu.a
libjeu.a: main.o grille.o jeu.o io.o
	ar -crv libjeu.a $(OPATH)main.o $(OPATH)grille.o $(OPATH)jeu.o $(OPATH)io.o


%.o: %.c
	@mkdir -p $(OPATH)
	$(CC) $(CFLAGS) -o $(OPATH)$@ $^ $(IFLAGS)


clean: 
	rm obj/* bin/* *.a


dist: 
	tar -cJf distr.tar.xz src/ include/ doc/ Doxyfile makefile grilles/


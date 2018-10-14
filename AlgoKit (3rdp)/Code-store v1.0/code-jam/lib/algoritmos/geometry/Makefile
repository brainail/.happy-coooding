.c.o:
	g++ -c -g $<

HDR = common.h point.h vector.h
SRC = point.c vector.c
OBJ = point.o vector.o
LIB = geometry.a
TAR = geometry.tar

all: ptest vtest

ptest: ptest.c $(LIB)
	g++ -o ptest ptest.c $(LIB)

vtest: vtest.c $(LIB)
	g++ -o vtest vtest.c $(LIB)

$(LIB): $(OBJ)
	ar rcsv $(LIB) $(OBJ)

$(OBJ): $(HDR)

tar: $(TAR)
$(TAR): Readme Makefile $(HDR) $(SRC) ptest.c vtest.c
	tar cvf $(TAR) Readme Makefile $(HDR) $(SRC) ptest.c vtest.c

bare: clean
	rm -f ptest vtest $(LIB)
clean:
	rm -f *.o $(TAR)

CFLAGS=-I include/ -Wall -Werror -lm
OBJ=logger.o parser.o polynomial.o demo.o pbm.o
OUTPUT=demo

default: demo

debug: CFLAGS += -g -O0 -D__DEBUG
debug: demo

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

demo: $(OBJ)
	$(CC) -o $(OUTPUT) $^ $(CFLAGS)
	-rm -f $(OBJ)

clean:
	-rm -f $(OBJ)
	-rm -f $(OUTPUT)
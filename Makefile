EXAMPLE_SRC = examples/example.c
EXAMPLE_OBJ = examples/example.o

COMMON_LIB =

CORE_INCLUDE = include
CORE_LIB   =

CFLAGS = -I${CORE_INCLUDE}

example: ${EXAMPLE_OBJ}
	${CC} ${CFLAGS} -o $@ $<

clean: ${EXAMPLE_OBJ} example
	rm $<

EXAMPLE_SRC = examples/example.c 			\
			  src/core/ray_devif_class.c    \
			  lib/virt/ray_virt_class.c
EXAMPLE_OBJ = examples/example.o    		\
			  src/core/ray_devif_class.o 	\
			  lib/virt/ray_virt_class.o

COMMON_LIB =

CORE_INCLUDE = include
CORE_LIB   =

CFLAGS = -I${CORE_INCLUDE}

example: ${EXAMPLE_OBJ}
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm ${EXAMPLE_OBJ} example

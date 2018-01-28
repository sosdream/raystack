EXAMPLE_SRC = examples/example.c 			\
			  src/core/ray_devif_class.c    \
			  lib/virt/ray_virt_class.c 	\
			  lib/virt/ray_virt_device.c
EXAMPLE_OBJ = examples/example.o    		\
			  src/core/ray_devif_class.o 	\
			  lib/virt/ray_virt_class.o 	\
			  lib/virt/ray_virt_device.o

COMMON_LIB =

CORE_INCLUDE = include
CORE_LIB   =

CFLAGS = -I${CORE_INCLUDE}
LDFLAGS = -lpcap

example: ${EXAMPLE_OBJ}
	${CC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

clean:
	rm ${EXAMPLE_OBJ} example

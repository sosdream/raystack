RAY_BASE_DIR 	= $(pwd)
RAY_DPDK_DIR 	= 3rd-dependency/dpdk
RAY_PF_RING_DIR = 3rd-dependency/PF_RING

# COMMAND
CC 		= gcc
CD 		= cd
LD 		= ld
MAKE 	= make
LN      = ln

EXAMPLE_SRC = examples/example.c 			\
			  src/core/ray_devif_class.c    \
			  lib/virt/ray_virt_class.c 	\
			  lib/virt/ray_virt_device.c 	\
			  lib/dpdk/ray_dpdk_class.c 	\
			  lib/dpdk/ray_dpdk_device.c
EXAMPLE_OBJ = examples/example.o    		\
			  src/core/ray_devif_class.o 	\
			  lib/virt/ray_virt_class.o 	\
			  lib/virt/ray_virt_device.o 	\
			  lib/dpdk/ray_dpdk_class.o 	\
			  lib/dpdk/ray_dpdk_device.o

DPDK_DECONFIG 	= x86_64-native-linuxapp-gcc
CORE_INCLUDE 	= include
DPDK_INCLUDE 	= ${DPDK_DECONFIG}/include

COMMON_LIB =
CORE_LIB   =
DPDK_LIB   = librte_eal.a					\
			 librte_bus_pci.a				\
			 librte_cfgfile.a				\
			 librte_cmdline.a				\
			 librte_cryptodev.a				\
			 librte_ethdev.a				\
			 librte_eventdev.a				\
			 librte_kni.a					\
			 librte_kvargs.a				\
			 librte_mbuf.a					\
			 librte_member.a				\
			 librte_mempool.a				\
			 librte_mempool_octeontx.a		\
			 librte_mempool_ring.a			\
			 librte_mempool_stack.a			\
			 librte_net.a					\
			 librte_pci.a					\
			 librte_pmd_e1000.a				\
			 librte_pmd_ixgbe.a				\
			 librte_port.a					\
			 librte_power.a					\
			 librte_reorder.a				\
			 librte_ring.a					\
			 librte_sched.a					\
			 librte_security.a				\
			 librte_table.a					\
			 librte_timer.a					\
			 librte_vhost.a


CFLAGS 	= -I${CORE_INCLUDE} -I${DPDK_INCLUDE}
LDFLAGS = -lpcap						\
		  -L${DPDK_DECONFIG}/lib 		\
		  -lrte_eal 					\
		  -lrte_bus_pci 				\
		  -lrte_ethdev 					\
		  -lrte_eventdev 				\
		  -lnuma						\
		  -lpthread						\
		  -ldl

dpdk_lib:
	${CD} ${RAY_DPDK_DIR} && ${MAKE} install T=${DPDK_DECONFIG}
	${LN} -f -s  ${RAY_DPDK_DIR}/${DPDK_DECONFIG} ${RAY_BASE_DIR}

example: ${EXAMPLE_OBJ} dpdk_lib
	${CC} ${CFLAGS} -o $@ ${EXAMPLE_OBJ} ${LDFLAGS}

clean:
	rm ${EXAMPLE_OBJ} example

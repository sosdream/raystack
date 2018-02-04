RAY_BASE_DIR 	= $(pwd)
RAY_DPDK_DIR 	= 3rd-dependency/dpdk
RAY_PF_RING_DIR = 3rd-dependency/PF_RING

RTE_TARGET ?= x86_64-native-linuxapp-gcc
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
			  src/core/ray_proto.c 		 	\
			  src/protocol/ethernet.c 		 	\
			  lib/dpdk/ray_dpdk_device.c
EXAMPLE_OBJ = examples/example.o    		\
			  src/core/ray_devif_class.o 	\
			  lib/virt/ray_virt_class.o 	\
			  lib/virt/ray_virt_device.o 	\
			  lib/dpdk/ray_dpdk_class.o 	\
			  src/core/ray_proto.o 		 	\
			  src/protocol/ethernet.o 		 	\
			  lib/dpdk/ray_dpdk_device.o

DPDK_DECONFIG 	= x86_64-native-linuxapp-gcc
CORE_INCLUDE 	= include
DPDK_INCLUDE 	= ${DPDK_DECONFIG}/include

COMMON_LIB =
CORE_LIB   =
DPDK_LIB   := -L${DPDK_DECONFIG}/lib 				\
			  -Wl,-lrte_flow_classify 				\
			  -Wl,-lrte_pipeline 					\
			  -Wl,-lrte_table 						\
			  -Wl,-lrte_port 						\
			  -Wl,-lrte_pdump 						\
			  -Wl,-lrte_distributor 				\
			  -Wl,-lrte_ip_frag 					\
			  -Wl,-lrte_gro 						\
			  -Wl,-lrte_gso 						\
			  -Wl,-lrte_meter 						\
			  -Wl,-lrte_lpm 						\
			  -Wl,--whole-archive 					\
			  -Wl,-lrte_acl 						\
			  -Wl,--no-whole-archive 				\
			  -Wl,-lrte_jobstats 					\
			  -Wl,-lrte_metrics 					\
			  -Wl,-lrte_bitratestats 				\
			  -Wl,-lrte_latencystats 				\
			  -Wl,-lrte_power 						\
			  -Wl,-lrte_timer 						\
			  -Wl,-lrte_efd 						\
			  -Wl,--whole-archive 					\
			  -Wl,-lrte_cfgfile 					\
			  -Wl,-lrte_hash 						\
			  -Wl,-lrte_member 						\
			  -Wl,-lrte_vhost 						\
			  -Wl,-lrte_kvargs 						\
			  -Wl,-lrte_mbuf 						\
			  -Wl,-lrte_net 						\
			  -Wl,-lrte_ethdev 						\
			  -Wl,-lrte_cryptodev  					\
			  -Wl,-lrte_security 					\
			  -Wl,-lrte_eventdev 					\
			  -Wl,-lrte_mempool 					\
			  -Wl,-lrte_mempool_ring 				\
			  -Wl,-lrte_ring 						\
			  -Wl,-lrte_pci 						\
			  -Wl,-lrte_eal 						\
			  -Wl,-lrte_cmdline 					\
			  -Wl,-lrte_reorder 					\
			  -Wl,-lrte_sched 						\
			  -Wl,-lrte_kni 						\
			  -Wl,-lrte_bus_pci 					\
			  -Wl,-lrte_bus_vdev 					\
			  -Wl,-lrte_mempool_stack 				\
			  -Wl,-lrte_pmd_af_packet 				\
			  -Wl,-lrte_pmd_ark 					\
			  -Wl,-lrte_pmd_avp 					\
			  -Wl,-lrte_pmd_bnxt 					\
			  -Wl,-lrte_pmd_bond 					\
			  -Wl,-lrte_pmd_cxgbe 					\
			  -Wl,-lrte_pmd_e1000 					\
			  -Wl,-lrte_pmd_ena 					\
			  -Wl,-lrte_pmd_enic 					\
			  -Wl,-lrte_pmd_fm10k 					\
			  -Wl,-lrte_pmd_failsafe 				\
			  -Wl,-lrte_pmd_i40e 					\
			  -Wl,-lrte_pmd_ixgbe 					\
			  -Wl,-lrte_pmd_kni 					\
			  -Wl,-lrte_pmd_lio 					\
			  -Wl,-lrte_pmd_nfp 					\
			  -Wl,-lrte_pmd_null 					\
			  -Wl,-lrte_pmd_qede 					\
			  -Wl,-lrte_pmd_ring 					\
			  -Wl,-lrte_pmd_softnic 				\
			  -Wl,-lrte_pmd_sfc_efx 				\
			  -Wl,-lrte_pmd_tap 					\
			  -Wl,-lrte_pmd_thunderx_nicvf 			\
			  -Wl,-lrte_pmd_virtio 					\
			  -Wl,-lrte_pmd_vhost 					\
			  -Wl,-lrte_pmd_vmxnet3_uio 			\
			  -Wl,-lrte_pmd_null_crypto 			\
			  -Wl,-lrte_pmd_crypto_scheduler 		\
			  -Wl,-lrte_pmd_skeleton_event 			\
			  -Wl,-lrte_pmd_sw_event 				\
			  -Wl,-lrte_pmd_octeontx_ssovf 			\
			  -Wl,-lrte_mempool_octeontx 			\
			  -Wl,-lrte_pmd_octeontx 				\
			  -Wl,--no-whole-archive 				\
			  -Wl,-lrt -Wl,-lm -Wl,-lnuma -Wl,-ldl -g
#			  -Wl,--cref

CFLAGS = -m64 -pthread								\
	     -march=native 								\
	     -DRTE_MACHINE_CPUFLAG_SSE 					\
	     -DRTE_MACHINE_CPUFLAG_SSE2 				\
	     -DRTE_MACHINE_CPUFLAG_SSE3 				\
	     -DRTE_MACHINE_CPUFLAG_SSSE3 				\
	     -DRTE_MACHINE_CPUFLAG_SSE4_1 				\
	     -DRTE_MACHINE_CPUFLAG_SSE4_2 				\
	     -DRTE_MACHINE_CPUFLAG_AES 					\
	     -DRTE_MACHINE_CPUFLAG_PCLMULQDQ 			\
	     -DRTE_MACHINE_CPUFLAG_AVX 					\
	     -DRTE_MACHINE_CPUFLAG_RDRAND 				\
	     -DRTE_MACHINE_CPUFLAG_FSGSBASE 			\
	     -DRTE_MACHINE_CPUFLAG_F16C 				\
	     -D_GNU_SOURCE 								\
	     -I${CORE_INCLUDE} 							\
	     -I${DPDK_INCLUDE} 							\
	     -include ${DPDK_INCLUDE}/rte_config.h 		\
	     -O3 -W -Wall 								\
	     -Wstrict-prototypes 						\
	     -Wmissing-prototypes 						\
	     -Wmissing-declarations 					\
	     -Wold-style-definition 					\
	     -Wpointer-arith 							\
	     -Wcast-align 								\
	     -Wnested-externs 							\
	     -Wcast-qual 								\
	     -Wformat-nonliteral 						\
	     -Wformat-security 							\
	     -Wundef 									\
	     -Wwrite-strings
#	     -Werror

LDFLAGS += ${DPDK_LIB} -lpcap

dpdk_lib:
	${CD} ${RAY_DPDK_DIR} && ${MAKE} install T=${DPDK_DECONFIG}
	${LN} -f -s  ${RAY_DPDK_DIR}/${DPDK_DECONFIG} ${RAY_BASE_DIR}

example: ${EXAMPLE_OBJ} dpdk_lib
	${CC} -o $@ ${CFLAGS} ${EXAMPLE_OBJ} ${LDFLAGS}

clean:
	rm ${EXAMPLE_OBJ} example

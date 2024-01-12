####################################################################
#                             RTOS 
include ./Makefile.inc
OUTPUT_DIR := ./examples
IMAGE := RTOSDemo.baremetal.elf
# RTOS kernel
FREERTOS_SRC = \
    $(FREERTOS_SOURCE_DIR)/croutine.c \
    $(FREERTOS_SOURCE_DIR)/list.c \
    $(FREERTOS_SOURCE_DIR)/queue.c \
    $(FREERTOS_SOURCE_DIR)/tasks.c \
    $(FREERTOS_SOURCE_DIR)/timers.c \
    $(FREERTOS_SOURCE_DIR)/stream_buffer.c \
    $(FREERTOS_SOURCE_DIR)/event_groups.c \
    $(FREERTOS_SOURCE_DIR)/portable/MemMang/heap_3.c


PORT_SRC = $(FREERTOS_SOURCE_DIR)/portable/GCC/RISC-V/port.c \
        Common/syscalls.c \
        Common/port.c \
        #    Common/syscall.c \
        #    Common/printf.c \

PORT_ASM = $(FREERTOS_SOURCE_DIR)/portable/GCC/RISC-V/portASM.S \
           Common/crt0.S   # start script

# 這裡要更動
DEMO_SRC = ./examples/main.c

CONF_SRC = ./conf/FreeRTOSConfig.h \
           ./conf/freertos_risc_v_chip_specific_extensions.h

RTOS_OBJ = $(FREERTOS_SRC:.c=.o) # RTOS中kernel .c file
PORT_OBJ = $(PORT_SRC:.c=.o)     # RTOS中port .c file
PORT_ASM_OBJ = $(PORT_ASM:.S=.o) # RTOS中port .S file
DEMO_OBJ = $(DEMO_SRC:.c=.o)     # RTOS demo .c file
OBJS = $(PORT_ASM_OBJ) $(PORT_OBJ) $(RTOS_OBJ) $(DEMO_OBJ)
FREERTOS_LIBRARY = libfreertos.a

# Include header files
INCLUDES = \
    -I$(FREERTOS_SOURCE_DIR)/include \
	-I$(FREERTOS_SOURCE_DIR)/portable/GCC/RISC-V \
    -I./conf

CFLAGS   = $(INCLUDES) 
LDFLAGS  = -L. -T Common/link.ld 
# Incclude Library
LIBS     = -lfreertos  -lfreertos 
# Final Target
PROG	 = $(DEMO_SRC:.c=.elf)

# link object
OBJS_NO_PATH = $(notdir $(OBJS))
OBJS_OUTPUT = $(OBJS_NO_PATH:%.o=$(OUTPUT_DIR)/%.o)

####################################################################
#                             Femtorv32
# Setup
FIRMWARE_DIR := ./../../..
include $(FIRMWARE_DIR)/config.mk

RVTOOLCHAIN_BIN_PREFIX=riscv64-unknown-elf
TOOLCHAIN_DL_SUFFIX=-x86_64-linux-ubuntu14
TOOLCHAIN_GCC_VER=8.3.0
TOOLCHAIN_VER=riscv64-unknown-elf-gcc-8.3.0-2020.04.0
RVTOOLCHAIN_DIR=$(FIRMWARE_DIR)/TOOLCHAIN/$(TOOLCHAIN_VER)$(TOOLCHAIN_DL_SUFFIX)
RVTOOLCHAIN_BIN_DIR=$(RVTOOLCHAIN_DIR)/bin
RVTOOLCHAIN_LIB_DIR=$(RVTOOLCHAIN_DIR)/$(RVTOOLCHAIN_BIN_PREFIX)/lib/$(ARCH)/$(ABI)
RVTOOLCHAIN_GCC_LIB_DIR=$(RVTOOLCHAIN_DIR)/lib/gcc/$(RVTOOLCHAIN_BIN_PREFIX)/$(TOOLCHAIN_GCC_VER)/$(ARCH)/$(ABI)

# GNU TOOLCHAIN Setup
RVGCC=$(RVTOOLCHAIN_BIN_DIR)/$(RVTOOLCHAIN_BIN_PREFIX)-gcc
RVLD=$(RVTOOLCHAIN_BIN_DIR)/$(RVTOOLCHAIN_BIN_PREFIX)-ld
RVOBJDUMP = $(RVTOOLCHAIN_BIN_DIR)/$(RVTOOLCHAIN_BIN_PREFIX)-objdump
RVAR = $(RVTOOLCHAIN_BIN_DIR)/$(RVTOOLCHAIN_BIN_PREFIX)-ar

# Flag
RVUSERCFLAGS=-w -DRISCV -DTIME -DUSE_MYSTDLIB -fno-pic
# Include header file
RVINCS=-I$(FIRMWARE_DIR)/LIBFEMTOGL -I$(FIRMWARE_DIR)/LIBFEMTORV32 -I$(FIRMWARE_DIR)/LIBFEMTOC
RVCFLAGS=$(OPTIMIZE) $(RVINCS) $(DEVICES) -fno-pic -march=$(ARCH) -mabi=$(ABI) \
         -fno-stack-protector -w -Wl,--no-relax
RVASFLAGS=-march=$(ARCH) -mabi=$(ABI) $(DEVICES_ASM) $(RVINCS)
RVLDFLAGS=-m elf32lriscv -b elf32-littleriscv --no-relax --print-memory-usage
RVCPPFLAGS=-fno-exceptions -fno-enforce-eh-specs

# Header & Library
FEMTORV32_LIBS_SMALL=-L$(RVTOOLCHAIN_LIB_DIR)\
                     -L$(FIRMWARE_DIR)/CRT\
 	             -L$(FIRMWARE_DIR)/LIBFEMTOGL\
	             -L$(FIRMWARE_DIR)/LIBFEMTORV32\
	             -L$(FIRMWARE_DIR)/LIBFEMTOC\
   	             -lfemtoGL -lfemtorv32 -lfemtoc 
RVGCC_LIB= $(RVTOOLCHAIN_LIB_DIR)/libc.a \
           $(RVTOOLCHAIN_LIB_DIR)/libm.a \
	   $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a

####################################################################
.PHONY: clean show

# Target
all: $(FREERTOS_LIBRARY) $(OUTPUT_DIR)/$(IMAGE)

%.o: %.c
	$(RVGCC) -c  $(CFLAGS) $(RVCFLAGS) $(RVUSERCFLAGS) -o $@  $<

%.o: %.S
	$(RVGCC) -c  $(CFLAGS) $(RVASFLAGS) -o $@  $<

$(FREERTOS_LIBRARY): $(PORT_ASM_OBJ) $(PORT_OBJ) $(RTOS_OBJ)
	$(RVAR) rcs $@ $(PORT_ASM_OBJ) $(PORT_OBJ) $(RTOS_OBJ)

# $(@:.elf=.c) 將目標.elf名稱換成.c 變成source code
# %.elf: %.o Makefile
# 	$(RVLD) -o $@  $(LDFLAGS) $(RVLDFLAGS) $(LIBS) $(FEMTORV32_LIBS_SMALL) $(RVGCC_LIB)
# 	$(RVOBJDUMP) -d $@ > $@.dis


# PROG: %(OBJS) Makefile
# 	$(RVLD) $(@:.elf=.o) -o $@  $(LDFLAGS) $(RVLDFLAGS) $(LIBS) $(FEMTORV32_LIBS_SMALL) $(RVGCC_LIB) -I$(FIRMWARE)/CRT/syscalls.o
# 	$(RVOBJDUMP) -d $@ > $@.dis

$(OUTPUT_DIR)/$(IMAGE): $(OBJS)  Makefile
	@echo ""
	@echo ""
	@echo "--- Final linking ---"
	@echo ""
	$(RVLD) $(OBJS)  $(RVLDFLAGS) $(LDFLAGS) -o $(OUTPUT_DIR)/$(IMAGE) $(FEMTORV32_LIBS_SMALL) $(RVGCC_LIB) $(LIBS) 
	$(RVOBJDUMP) -d $@ > $@.dis

# hartstone: Makefile
# 	$(MAKE) -C hartstone

clean:
	$(RM) -f $(OBJS) $(FREERTOS_LIBRARY) examples/*.elf examples/*.elf.dis
	# $(MAKE) -C hartstone clean


show:
	@echo $(OBJS)



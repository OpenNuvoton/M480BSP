include ./makefile.conf
NAME=ISP_UART_SPIFLASH_M487KM

STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main

# Need following option for LTO as LTO will treat retarget functions as
# unused without following option
CFLAGS+=-fno-builtin

LDSCRIPTS=-L. -L$(BASE)Library/Device/Nuvoton/M480/Source/GCC -T gcc_arm.ld

LFLAGS=$(USE_NANO) $(USE_NOHOST) $(LDSCRIPTS) $(GC) $(MAP)

#$(NAME)-$(CORE).axf: main.c $(NAME).c $(STARTUP)
#	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@
IPATH= \
	../ \
	../../../../Library/CMSIS/Include \
	../../../../Library/Device/Nuvoton/M480/Include \
	../../../../Library/StdDriver/inc \
	../User
SRC=$(wildcard \
	../*.c \
	../../../../Library/Device/Nuvoton/M480/Source/*.c \
	../../../../Library/Device/Nuvoton/M480/Source/GCC/*.c \
	../User/*.c \
)
OBJS = $(patsubst %.c,./Objects/%.o,$(notdir $(SRC)))

$(NAME): $(OBJS)
	cd ./Objects && $(CC) *.o $(CFLAGS) $(LFLAGS) $(STARTUP) -o $@.axf $(addprefix -I ../,$(IPATH)) 
	$(CP) -O binary ./Objects/$@.axf ./Objects/$@.bin

$(OBJS): $(SRC)
	mkdir -p ./Objects
	cd ./Objects && $(CC) $(addprefix ../,$^) $(CFLAGS) -c $(addprefix -I ../,$(IPATH))

.PHONY: clean

clean:
	rm -f ./Objects/*
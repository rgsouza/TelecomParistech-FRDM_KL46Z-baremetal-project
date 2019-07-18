# Makefile SE203
# Author Rayanne Souza

SOURCES = main.c led.c init.c uart.c led_matrix.c irq.c buttons.c pit.c mcg.c 
OBJS = main.o led.o crt0.o init.o uart.o led_matrix.o image.o irq.o buttons.o flash.o pit.o mcg.o
DEPS := $(subst .c,.d,$(SOURCES))
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc

AS = $(CC)

ASFLAGS = -c -g -mcpu=cortex-m0plus

CFLAGS = -g -O1 -mcpu=cortex-m0plus -std=gnu99 -Wall -Wextra -Werror -mthumb

LDFLAGS = -nostdlib -T ld_ram.lds

EXE = main

$(EXE) : $(OBJS)


image.o : image.raw
	$(PREFIX)ld -r -b binary $< -o $@

%.d: %.c
	@$(CC) $(CFLAGS) -MM -MF $@ -MP $<


.PHONY: debug startgdbserver clean
debug : 
	$(PREFIX)gdb main

startgdbserver:
	 JLinkGDBServer -if swd -device "MKL46Z256xxx4" -LocalhostOnly

clean:
	rm -f main $(OBJS) $(DEPS)


-include $(DEPS)

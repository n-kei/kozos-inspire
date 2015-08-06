PREFIX  = /usr/local
ARCH    = h8300-elf
BINDIR  = $(PREFIX)/bin
ADDNAME = $(ARCH)-

VPATH   = ./lowio ./ntlogger ./ntshell

AR      = $(BINDIR)/$(ADDNAME)ar
AS      = $(BINDIR)/$(ADDNAME)as
CC      = $(BINDIR)/$(ADDNAME)gcc
LD      = $(BINDIR)/$(ADDNAME)ld
NM      = $(BINDIR)/$(ADDNAME)nm
OBJCOPY = $(BINDIR)/$(ADDNAME)objcopy
OBJDUMP = $(BINDIR)/$(ADDNAME)objdump
RANLIB  = $(BINDIR)/$(ADDNAME)ranlib
STRIP   = $(BINDIR)/$(ADDNAME)strip

KZ_XMODEM = ../tools/kz_xmodem/kz_xmodem
KZ_XMODEM_SERDEV = /dev/cuaU0

# Low level components
OBJS  = startup.o main.o interrupt.o
OBJS += lib.o serial.o timer.o
OBJS += led.o sg12232c.o
OBJS += re.o sw.o
OBJS += mmc.o pff.o
OBJS += vs1011e.o
OBJS += spi.o spreg.o
OBJS += ntl.o ntlser.o
OBJS += vtsend.o vtrecv.o
OBJS += ntopt.o ntlibc.o ntshell.o
OBJS += text_editor.o text_history.o

# Tasks
OBJS += task_audio.o ipc_audio.o
OBJS += task_display.o ipc_display.o
OBJS += task_menu.o ipc_menu.o
OBJS += task_input.o
OBJS += task_command.o
OBJS += task_fileio.o

# Kernel
OBJS += kozos.o syscall.o memory.o

# Drivers
OBJS += driver_console.o
OBJS += driver_timer.o

TARGET = kozos

CFLAGS = -Wall -mh -nostdinc -nostdlib -fno-builtin
#CFLAGS += -mint32 # intを32ビットにすると掛算／割算ができなくなる
CFLAGS += -I. -I./lowio -I./ntlogger -I./ntshell
#CFLAGS += -g
CFLAGS += -Os
CFLAGS += -DKOZOS

LFLAGS = -static -T ld.scr -L. -lgcc

.SUFFIXES: .c .o
.SUFFIXES: .s .o
.SUFFIXES: .S .o

all :		$(TARGET)

$(TARGET) :	$(OBJS)
		$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)
		cp $(TARGET) $(TARGET).elf
		$(STRIP) $(TARGET)

.c.o :		$<
		$(CC) -c $(CFLAGS) $<

.s.o :		$<
		$(CC) -c $(CFLAGS) $<

.S.o :		$<
		$(CC) -c $(CFLAGS) $<

clean :
		rm -f $(OBJS) $(TARGET) $(TARGET).elf

load :
	$(KZ_XMODEM) $(TARGET) $(KZ_XMODEM_SERDEV)

connect:
		cu -l /dev/cuaU0

console :
	minicom -o console -b 9600 -D $(KZ_XMODEM_SERDEV)


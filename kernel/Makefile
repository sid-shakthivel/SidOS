CC = i686-elf-gcc
ASSEMBLER = nasm

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASSEMBLER_FLAGS = -felf32

OBJ := object_files

C_SOURCES := $(wildcard */*.c) $(wildcard *.c)
ASSEMBLY_SOURCES := $(wildcard */*.s) $(wildcard *.s)
C_OBJECTS := $(patsubst %.c, $(OBJ)/%.o, $(C_SOURCES))
ASSEMBLY_OBJECTS := $(patsubst %.s, $(OBJ)/%.o, $(ASSEMBLY_SOURCES))

# myos.bin: linker.ld object_files/kernel.o object_files/uart.o object_files/vga_text.o object_files/gdt.o object_files/set_gdt.o object_files/boot.o object_files/idt.o object_files/set_idt.o object_files/ISRs.o object_files/io.o object_files/pic.o object_files/keyboard.o object_files/interrupts.o object_files/string.o object_files/page_frame_allocator.o object_files/paging.o object_files/enable_paging.o
# 	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib object_files/boot.o object_files/kernel.o object_files/vga_text.o object_files/gdt.o object_files/uart.o object_files/set_gdt.o object_files/idt.o object_files/set_idt.o object_files/ISRs.o object_files/io.o object_files/pic.o object_files/keyboard.o object_files/interrupts.o object_files/string.o object_files/page_frame_allocator.o object_files/paging.o object_files/enable_paging.o -lgcc

myos.iso: myos.bin
	cp myos.bin isodir/boot/myos.bin
	grub-mkrescue -o myos.iso isodir

myos.bin: linker.ld $(C_OBJECTS) $(ASSEMBLY_OBJECTS)
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib $(ASSEMBLY_OBJECTS) $(C_OBJECTS) -lgcc

all: $(C_OBJECTS) $(ASSEMBLY_OBJECTS)

$(C_OBJECTS): $(C_SOURCES)
	$(CC) $(CFLAGS) -c $(patsubst $(OBJ)/%.o, %.c, $@) -o $@


$(ASSEMBLY_OBJECTS): $(ASSEMBLY_SOURCES)
	$(ASSEMBLER) $(ASSEMBLER_FLAGS) $(patsubst $(OBJ)/%.o, %.s, $@) -o $@
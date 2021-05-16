CC = i686-elf-gcc
ASSEMBLER = nasm

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASSEMBLER_FLAGS = -felf32

OBJ := object_files

C_SOURCES := $(wildcard */*.c) $(wildcard *.c)
ASSEMBLY_SOURCES := $(wildcard */*.s) $(wildcard *.s)
C_OBJECTS := $(patsubst %.c, $(OBJ)/%.o, $(C_SOURCES))
ASSEMBLY_OBJECTS := $(patsubst %.s, $(OBJ)/%.o, $(ASSEMBLY_SOURCES))

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
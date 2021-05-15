myos.iso: myos.bin
	cp myos.bin isodir/boot/myos.bin
	grub-mkrescue -o myos.iso isodir

myos.bin: linker.ld object_files/kernel.o object_files/uart.o object_files/vga_text.o object_files/gdt.o object_files/set_gdt.o object_files/boot.o object_files/idt.o object_files/set_idt.o object_files/ISRs.o object_files/io.o object_files/pic.o object_files/keyboard.o object_files/interrupts.o object_files/string.o object_files/page_frame_allocator.o object_files/paging.o object_files/enable_paging.o
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib object_files/boot.o object_files/kernel.o object_files/vga_text.o object_files/gdt.o object_files/uart.o object_files/set_gdt.o object_files/idt.o object_files/set_idt.o object_files/ISRs.o object_files/io.o object_files/pic.o object_files/keyboard.o object_files/interrupts.o object_files/string.o object_files/page_frame_allocator.o object_files/paging.o object_files/enable_paging.o -lgcc

object_files/kernel.o: kernel.c
	i686-elf-gcc -c kernel.c -o object_files/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/uart.o: io/uart.c
	i686-elf-gcc -c io/uart.c -o object_files/uart.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/vga_text.o: gfx/vga_text.c
	i686-elf-gcc -c gfx/vga_text.c -o object_files/vga_text.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/gdt.o: memory/gdt.c
	i686-elf-gcc -c memory/gdt.c -o object_files/gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/idt.o: memory/idt.c
	i686-elf-gcc -c memory/idt.c -o object_files/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/pic.o: io/pic.c
	i686-elf-gcc -c io/pic.c -o object_files/pic.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/interrupts.o: interrupts/interrupts.c
	i686-elf-gcc -c interrupts/interrupts.c -o object_files/interrupts.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/keyboard.o: interrupts/keyboard.c
	i686-elf-gcc -c interrupts/keyboard.c -o object_files/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/page_frame_allocator.o: memory/page_frame_allocator.c
	i686-elf-gcc -c memory/page_frame_allocator.c -o object_files/page_frame_allocator.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/paging.o: memory/paging.c
	i686-elf-gcc -c memory/paging.c -o object_files/paging.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/string.o: string.c
	i686-elf-gcc -c string.c -o object_files/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/io.o: io/io.c
	i686-elf-gcc -c io/io.c -o object_files/io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

object_files/enable_paging.o: memory/enable_paging.s
	nasm -felf32 memory/enable_paging.s -o object_files/enable_paging.o

object_files/ISRs.o: interrupts/ISRs.s
	nasm -felf32 interrupts/ISRs.s -o object_files/ISRs.o

object_files/set_idt.o: memory/set_idt.s
	nasm -felf32 memory/set_idt.s -o object_files/set_idt.o

object_files/set_gdt.o: memory/set_gdt.s
	nasm -felf32 memory/set_gdt.s -o object_files/set_gdt.o

object_files/boot.o: boot.s
	nasm -felf32 boot.s -o object_files/boot.o

clean:
	rm object_files/kernel.o
	rm object_files/boot.o
	rm object_files/uart.o
	rm object_files/vga_text.o
	rm object_files/set_gdt.o
	rm object_files/gdt.o
	rm myos.bin
	rm myos.iso
	
	
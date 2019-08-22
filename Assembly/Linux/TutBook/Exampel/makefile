# Linux 64 bit yasm debuggablle assembly makefile
all: hello.bin

%.o: %.asm
	yasm -g dwarf2 -f elf64 $^ -l $*.lst

%.bin: %.o
	ld -g -o $@ $^

clean:
	rm -f *.o *.bin *.lst
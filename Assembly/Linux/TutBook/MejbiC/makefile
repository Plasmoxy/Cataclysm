# Linux 64 bit yasm debuggablle assembly makefile

%.o: %.asm
	yasm -g dwarf2 -f elf64 $^ -l $*.lst

%.bin: %.o
	gcc -static -o $@ $^

clean:
	rm -f *.o *.bin *.lst
all: bare

%.o: %.nasm
	nasm -f elf64 $^
%: %.o
	ld -o $@ $^
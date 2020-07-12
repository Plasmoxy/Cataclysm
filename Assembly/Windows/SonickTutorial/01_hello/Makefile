# Windows NASM makefile by Plasmoxy 2020
# Linked using gcc, you can use LINK too

# Binary target name (without extension)
BIN=hello
ASM_LINKER=gcc
OBJS=$(BIN).obj

%.obj: %.asm
	nasm -f win64 $<

$(BIN): $(OBJS)
	ifeq ($(ASM_LINKER), gcc)
	gcc -m64 $< -o $@
	else ifeq ($(ASM_LINKER), link)
	echo not implemented
	endif

run: $(BIN)
	@echo ---
	@./$<
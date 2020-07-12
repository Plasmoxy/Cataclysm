# Windows NASM makefile by Plasmoxy 2020
# Linked using gcc, you can use LINK too

# Binary target name (without extension)
NAME=
OBJS=$(NAME).obj

$(NAME).exe: $(OBJS)
	gcc -m64 $< -o $@

%.obj: %.asm
	nasm -f win64 $< -o $@

clean:
	rm -fr *.obj *.exe bin

run: $(NAME).exe
	@echo ------------------------------
	@./$<
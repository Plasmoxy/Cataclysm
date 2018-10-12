%.obj: %.asm
	nasm -f win32 $<

pointers.exe: pointers.obj
	gcc $< -o $@
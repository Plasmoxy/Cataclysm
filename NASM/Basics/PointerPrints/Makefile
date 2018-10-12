%.obj: %.asm
	nasm -f win32 $<

pointers: pointers.obj
	gcc $< -o $@

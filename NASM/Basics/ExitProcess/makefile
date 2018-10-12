%.obj: %.asm
	nasm -f win32 $<

exitp.exe: exitp.obj
	gcc $< -o $@

run: exitp.exe
	@echo ---
	@exitp
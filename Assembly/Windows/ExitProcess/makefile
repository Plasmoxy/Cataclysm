%.obj: %.asm
	nasm -f win32 $<

%.exe: %.obj
	gcc $< -o $@

run: exitp.exe
	@echo ---
	@$<
BIN=simplefunction
OBJS=$(BIN).obj

%.obj: %.asm
	nasm -f win32 $<

$(BIN): $(OBJS)
	gcc -m32 $< -o $@

run: $(BIN)
	@echo ---
	@$<
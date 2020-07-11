BIN=localvariable
OBJS=$(BIN).obj

%.obj: %.asm
	nasm -f win32 $<

$(BIN): $(OBJS)
	gcc $< -o $@

run: $(BIN)
	@echo ---
	@$<
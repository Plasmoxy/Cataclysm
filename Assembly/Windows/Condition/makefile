BIN=condition
FORMAT=elf32
OBJECTSUFFIX=o
OBJS=$(BIN).$(OBJECTSUFFIX)

%.$(OBJECTSUFFIX): %.asm
	nasm -f $(FORMAT) $<

$(BIN): $(OBJS)
	gcc $< -o $@ -m32

run: $(BIN)
	@echo ---
	@$<

clean:
	rm -f *.obj *.o $(BIN)
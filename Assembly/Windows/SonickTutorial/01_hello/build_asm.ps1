$name = "hello"

if (-Not (Test-Path env:LIB)) {
  vcvars
}

nasm -f win64 -o "$name.obj" "$name.asm"
link "$name.obj" /subsystem:console /entry:main /out:"$name.exe"
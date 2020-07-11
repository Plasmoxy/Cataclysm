@echo off
nasm -f win32 hello.asm
gcc hello.obj
a.exe
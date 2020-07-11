# NASM build script by Plasmoxy 2020, using msvc linker
# vcvars = vcvarsall.bat script relay to PS, if you dont have vars use the VC dev cmd

$name = "hello"

if (-Not (Test-Path env:LIB)) {
  vcvars
}

Write-Host "-> Compiling NASM"
Invoke-Expression "nasm -f win64 -o $name.obj $name.asm"

Write-Host "-> Linking"
# link with universal CRT and legacy stdio (includes printf, etc)
# kinda unstable idk TODO: ignore 4210
$libs = "kernel32.lib ucrt.lib legacy_stdio_definitions.lib"
Invoke-Expression "link $name.obj /IGNORE:4210 /subsystem:console /entry:main /out:$name.exe $libs"

Write-Host "-- Done --"
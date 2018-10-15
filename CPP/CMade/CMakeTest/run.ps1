cmake -G "Unix Makefiles" .
make

if ($?) {
    ./hello
}
cmake -G "Unix Makefiles" .
make

if ($?) {
    ./GLMTest
}
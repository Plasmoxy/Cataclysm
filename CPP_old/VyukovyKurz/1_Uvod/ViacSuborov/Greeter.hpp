#ifndef GREETER_H
#define GREETER_H
#endif

#include <string>

class Greeter {
public:
    Greeter(std::string _name);
    std::string name;
    void greet();
};

// hmm toto by malo ist do cpp suboru hmm

Greeter::Greeter(std::string _name) {
    name = _name;
}

void Greeter::greet() {
    std::cout << "Hello, " << name << std::endl;
}
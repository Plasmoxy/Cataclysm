/*
We	will	start	off	with the	infamous	Fizz buzz	challenge. This	challenge	has	been	used	frequently	in	the	
past	as	an	initial	coding	challenge	to	filter	out	people	who	cannot	write	a	simple	solution.	The	general	
problem	is:
Print	out	all	the	numbers	from	1	to	100.	But	for	every	number	divisible	by	3	print	replace it	with	the	
word	“Fizz,”	for	any	number	divisible	by	5	replace	it	with	the	word	“Buzz”	and	for	a	number	divisible	
by	both	3	and	5	replace	it	with	the	word	“FizzBuzz.”
So	your	program	should	output:
1
2
Fizz
4
Buzz
Fizz
7
.
.
.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<string> fizzBuzz() {
    vector<string> result;
    stringstream add;

    for (int i = 1; i <= 100; i++) {  

        add.str(string());

        if (i%3 == 0) {
            add << "Fizz";
        }

        else if (i%5 == 0) {
            add << "Buzz";
        }

        else {
            add << i;
        }

        result.push_back(add.str());
    }
    
    return result;
}

int main() {

    for (string s : fizzBuzz()) {
        cout << s << endl;
    }

}
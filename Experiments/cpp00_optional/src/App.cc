#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>
#include <optional>
#include <cassert>

struct Person {
	std::string name;
	int age;
};

template <> struct fmt::formatter<std::optional<Person>> {
	constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
	template <typename FormatContext>
	auto format(const std::optional<Person>& p, FormatContext& ctx) {
		return format_to(ctx.out(), p ? "Person {{ {} {} }}" : "none", p->name, p->age);
	}
};

int main(int argc, char* argv[]) {
	using namespace std;

	optional<int> maybe = {};

	fmt::print("has value = {}\n", maybe.has_value());
	fmt::print("maybe = {}\n", maybe ? "YES" : "NO");

	maybe = 4;

	fmt::print("has value = {}\n", maybe.has_value());
	fmt::print("maybe = {}\n", maybe ? "YES" : "NO");

	fmt::print("val = {}\n", *maybe);

	optional<Person> opNone = {};
	fmt::print("person none = {}\n", opNone);

	optional<Person> op = Person {"Sebu", 19};
	fmt::print("person = {}\n", op);

	Person p = Person {"Hanzo", 34};
	fmt::print("Person normal: {} B\nPerson optional: {} B\n", sizeof(p), sizeof(op));

	struct OptInt {
		int value;
		bool hasvalue;
	};

	assert(sizeof(OptInt) == sizeof(optional<int>));

	optional<int> optInt = 1287;
	OptInt* castedOptInt = (OptInt*) &optInt; // reinterpret to OptInt

	assert(sizeof(optInt) == sizeof(*castedOptInt));

	fmt::print("Sizeof bool = {} B\n", sizeof(bool));
	fmt::print("Sizeof castedOptInt = {} B\n", sizeof(castedOptInt));
	fmt::print("Sizeof optInt = {} B\n", sizeof(optInt));
	fmt::print("casted hasvalue = {}\n", castedOptInt->hasvalue);
	fmt::print("casted value = {}\n", castedOptInt->value);

	return 0;
}
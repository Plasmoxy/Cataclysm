#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>
#include <optional>


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
	std::optional<int> maybe = {};

	fmt::print("has value = {}\n", maybe.has_value());
	fmt::print("maybe = {}\n", maybe ? "YES" : "NO");

	maybe = 4;

	fmt::print("has value = {}\n", maybe.has_value());
	fmt::print("maybe = {}\n", maybe ? "YES" : "NO");

	fmt::print("val = {}\n", *maybe);

	std::optional<Person> op = {};
	fmt::print("person = {}\n", op);

	op = Person {"Sebu", 19};
	fmt::print("person = {}\n", op);

	return 0;
}
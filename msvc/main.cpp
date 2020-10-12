#include <string_view>
#include <stdexcept>
#include <array>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "../include/chasm/chasm.hpp"

#include "fixed_vector.hpp"

#include <version>

template <class String>
constexpr bool parse(const String& string) noexcept
{
	return chasm::parse::parser{string}.parse();
}

constexpr auto operator""_split(const char* text, std::size_t size)
{
	//fmt::print("size?: {}", size);
	return chasm::split(text);
}

template <class Tokens>
constexpr auto split_size(const Tokens& tokens)
{
	std::size_t count = 0;
	auto begin = tokens.begin();
	const auto end = tokens.end();

	while (begin != end)
		++begin, count++;

	return count;
}

constexpr auto assemble(const std::string_view text)
{
	auto machine_code = fixed_vector<std::byte>{};
	auto tokens = fixed_vector<chasm::lex::token, 100>{};

	const auto lexemes = chasm::split(text);

	for (const std::string_view lexeme : lexemes)
		tokens.push_back(chasm::lex::match_token(lexeme));

	return tokens;
	//machine_code.emplace_back(std::byte{'x'}, std::byte{'a'});

	//return machine_code;
}

/* Ideas:
** - Make production class (?) whose output for an instruction is the
** corresponding ast?

** - Can't do regular recursive-descent on-the-fly code generation since
** instructions correspond to a class of possible opcodes based on context.
** jmp 0x50 yields a different opcode compared to jmp short 0x50.
** => hash string -> index in asm opcode table

** - Still need to figure out how we're going to handle user-defined variables
** "mov {}, 2" python string format?
** "mov byte{}, 2" c++ ctor-like format mixed with above, for type disambiguation?

** - Take 1 instruction, say "mov" and write out all possible forms
** write proof of concept code to show how we would be able to parse asm and generate
** the corresponding machine code.

** - Btw Dragon book is quite nice...
*/

int main()
{
	try
	{
		constexpr auto string =
			//"mov eax, {long_variable_name};"
			"mov edx, [7535AF5];"
			"mov edx, [7535AF5];";
			"mov edx, [7535AF5];"
			"mov edx, [7535AF5];"
			"mov edx, [7535AF5];"
			"push edx, [7535AF5];"
			//"push bx;"
			//"mov edx, [7535AF5];"
			//"push bx;"
			//"mov edx, [7535AF5];"
			//"push bx;"
			//"mov edx, [7535AF5];"
			//"push bx;"
			//"mov edx, [7535AF5];"
			//"mov edx, [7535AF5];"
			//"push bx;"
			//"mov edx, [7535AF5];"
			//"push bx;"
			//"mov edx, [7535AF5];"
			//"mov edx, [7535AF5];"
			//"push bx;"
			//"mov edx, [7535AF5];"
			//"push bx;"
			//"mov edx, [7535AF5];"
			//"mov edx, [7535AF5];"
			//"push bx;"
			//"mov edx, [7535AF5];"
			//"push bx;"
			//"mov edx, [7535AF5];"
			//"push bx;"
			"nop;";

		constexpr auto asx = assemble("");
	}
	catch (std::exception& e)
	{
		fmt::print("Exception occured: {}", e.what());
	}

	return 0;
}
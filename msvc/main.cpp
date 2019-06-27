#include <iostream>
#include <string_view>
#include <type_traits>

#include <sprout/cctype.hpp>
#include <sprout/array.hpp>
#include <sprout/string.hpp>
#include <sprout/range/algorithm.hpp>
#include <sprout/range/adaptor/to_lower.hpp>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "../include/chasm/lex/split.hpp"
#include "../include/chasm/lex/token.hpp"
#include "../include/chasm/lex/patterns.hpp"
#include "../include/chasm/lex/lexer.hpp"
#include "../include/chasm/parser/parser.hpp"

template <class String>
constexpr bool test(const String& string) noexcept
{
	chasm::parser::parser parser(string);
	return parser.parse();
}

template <class Gen, std::size_t... Vals>
constexpr auto generate_array_impl(Gen fn, std::index_sequence<Vals...> seq) noexcept
{
	return std::array{fn(Vals)...};
}

template <std::size_t N, class Gen>
constexpr auto generate_array(Gen fn) noexcept
{
	return generate_array_impl(fn, std::make_index_sequence<N>{});
}

template <auto Val, auto... Vals>
struct test2
{
	static constexpr auto value = Val;
};

template <class String>
constexpr auto split(const String& string)
{
	const auto splitting = chasm::lex::split(string, chasm::lex::whitespace_skipper, chasm::lex::capture{";,[]"});

	int count = sprout::range::count_if(splitting, [](const auto& x)
	{
		return true;
	});

	return std::pair{splitting, count};
};

int main()
{
	constexpr std::string_view string =
		"mov eax,	   00001443;"
		"mov edx, [75A47960];"
		"push bx;"
		"mov ax, 1242135;"
		"call edx;"
		"ret 0010;"
		"nop;";

	//constexpr auto splitting = chasm::lex::split(
	//	"hello there man "
	//	"hello there man"
	//);

	constexpr auto splitting = split(string);
	constexpr auto array = generate_array<splitting.second>([&](const auto x) { return splitting.first[x]; });

	for (const auto& word : array)
		fmt::print("Word: {}\n", word);

	constexpr unsigned char bytes[] = "\x90\x90";

	fmt::print("Bytes size = {}\n", std::size(bytes));
	fmt::print("First byte = 0x{:x}\n", bytes[0]);

	//constexpr auto splitting = split(string);

	//for (const auto& token : array)
		//fmt::print("token: {}\n", token);

	//constexpr auto t = test(string);

	return 0;
}
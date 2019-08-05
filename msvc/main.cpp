#include <string_view>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "../include/chasm/lex/split.hpp"
#include "../include/chasm/parser/parser.hpp"

template <class String>
constexpr bool test(const String& string) noexcept
{
	return chasm::parse::parser{string}.parse();
}

constexpr auto split(const char* text)
{
	return chasm::lex::split(text, chasm::lex::whitespace_skipper, chasm::lex::capture{";,[]"});
}

constexpr auto operator""_split(const char* text, std::size_t)
{
	return split(text);
}

int main()
{
	try
	{
		constexpr auto string =
			"mov eax, 25;"
			"mov edx, [75];"
			"push bx;"
			"ret 10;"
			"nop;";

		constexpr auto length = chasm::lex::detail::string_length(string);
		//chasm::x86_format()
		//int x = 0;
		//constexpr assembly = R"(
		//	call edx;
		//	ret {{result}};
		//	nop;
		//)"_x86(x);

		constexpr auto assembly = split(string);
		constexpr auto b = test(string);
		//static_assert(b);

		for (const auto& token : assembly)
			fmt::print("Token = {}\n", token);
	}
	catch (std::exception& e)
	{
		fmt::print("Exception occured: {}", e.what());
	}

	return 0;
}
#pragma once

#include <string_view>
#include <array>

namespace chasm::lex
{
	enum class symbol
	{
		nullary_opcode,
		unary_opcode,
		binary_opcode,

		number, reg,
		open_bracket, close_bracket, comma,
		semicolon, end
	};

	struct token
	{
		lex::symbol symbol;
		std::string_view value;
	};
}

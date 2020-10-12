#pragma once

#include <string_view>
#include <array>

namespace chasm::lex
{
	enum class symbol
	{
		binary_opcode,
		unary_opcode,
		nullary_opcode,

		number, registr,
		open_bracket, close_bracket,
		open_brace, close_brace,
		variable,
		comma, semicolon,
		end
	};

	struct token
	{
		lex::symbol symbol = symbol::end;
		std::string_view value = "";
	};
}

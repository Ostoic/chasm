#pragma once

#include <array>
#include "../../lex/token.hpp"

namespace chasm::parser::grammar
{
	// register_or_number -> r | num .
	struct register_or_number
	{
		static constexpr auto first = std::array{
			lex::symbol::number,
			lex::symbol::reg,
		};

		static constexpr auto follow = std::array{
			lex::symbol::semicolon,
			lex::symbol::close_bracket,
			lex::symbol::comma,
		};

		template <class Lexer>
		static constexpr void derive(Lexer& lexer) noexcept
		{
			if (lex::peek(lexer) == lex::symbol::number)
				lexer.expect(lex::symbol::number);
			else
				lexer.expect(lex::symbol::reg);
		}
	};
}

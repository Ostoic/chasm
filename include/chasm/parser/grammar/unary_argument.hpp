#pragma once

#include "register_or_number.hpp"

namespace chasm::parser::grammar
{
	// unary_argument -> [ num_or_r ] | num .
	struct unary_argument
	{
		static constexpr auto first = std::array{
			lex::symbol::open_bracket,
			lex::symbol::number,
			lex::symbol::reg,
		};

		static constexpr auto follow = std::array{
			lex::symbol::semicolon,
		};

		template <class Lexer>
		static constexpr void derive(Lexer& lexer) noexcept
		{
			if (lex::peek(lexer) == lex::symbol::open_bracket)
			{
				lexer.expect(lex::symbol::open_bracket);
				register_or_number::derive(lexer);
				lexer.expect(lex::symbol::close_bracket);
			}
			else
				register_or_number::derive(lexer);
		}
	};
}
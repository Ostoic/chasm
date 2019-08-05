#pragma once

#include "register_or_number.hpp"

namespace chasm::parse::grammar
{
	// binary_argument -> [ r_or_num ] | r_or_num .
	struct binary_argument2
	{
		static constexpr auto first = std::array{
			lex::symbol::reg,
			lex::symbol::number,
			lex::symbol::open_bracket,
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

	// binary_argument -> [ r_or_num ] , r_or_num
	// | r_or_num , binary_argument2 .
	struct binary_argument
	{
		static constexpr auto first = std::array{
			lex::symbol::reg,
			lex::symbol::number,
			lex::symbol::open_bracket,
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
				lexer.expect(lex::symbol::comma);
				register_or_number::derive(lexer);
			}
			else
			{
				register_or_number::derive(lexer);
				lexer.expect(lex::symbol::comma);
				binary_argument2::derive(lexer);
			}
		}
	};
}

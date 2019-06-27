#pragma once

#include "unary_argument.hpp"

namespace chasm::parser::grammar
{
	// unary_instruction -> unary_opcode unary_argument . 
	struct unary_instruction
	{
		static constexpr auto first = std::array{
			lex::symbol::unary_opcode,
		};

		static constexpr auto follow = std::array{
			lex::symbol::semicolon,
		};

		template <class Lexer>
		static constexpr void derive(Lexer& lexer) noexcept
		{
			lexer.expect(lex::symbol::unary_opcode);
			unary_argument::derive(lexer);
		}

	};
}

#pragma once

#include <sprout/range/algorithm/any_of_equal.hpp>
#include "nullary_instruction.hpp"
#include "unary_instruction.hpp"
#include "binary_instruction.hpp"
#include "first_follow.hpp"

namespace chasm::parse::grammar
{
	// instruction -> nullary_instruction | unary_instruction | binary_instruction .
	struct instruction
	{
		template <class Lexer>
		static constexpr void derive(Lexer& lexer) noexcept
		{
			const auto current = lexer.peek();
			if (sprout::range::any_of_equal(grammar::first(nullary_instruction{}), current))
				nullary_instruction::derive(lexer);

			else if (sprout::range::any_of_equal(grammar::first(unary_instruction{}), current))
				unary_instruction::derive(lexer);

			else if (sprout::range::any_of_equal(grammar::first(binary_instruction{}), current))
				binary_instruction::derive(lexer);
		}

		static constexpr auto first = std::array{
			lex::symbol::nullary_opcode,
			lex::symbol::unary_opcode,
			lex::symbol::binary_opcode,
		};

		static constexpr auto follow = std::array{
			lex::symbol::semicolon
		};
	};
}

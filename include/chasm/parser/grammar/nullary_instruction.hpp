#pragma once

#include <array>
#include "../../lex/token.hpp"

namespace chasm::parse::grammar
{
	// nullary_instruction -> nullary_opcode .
	struct nullary_instruction
	{
		static constexpr auto first = std::array{
			lex::symbol::nullary_opcode,
		};

		static constexpr auto follow = std::array{
			lex::symbol::semicolon,
		};

		template <class Lexer>
		static constexpr void derive(Lexer& lexer) noexcept
		{
			lexer.expect(lex::symbol::nullary_opcode);
		}
	};
}

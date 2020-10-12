#pragma once

#include "binary_argument.hpp"

namespace chasm::parse::grammar
{
	// binary_instruction -> binary_opcode binary_argument .
	struct binary_instruction
	{
		static constexpr auto first = std::array{
			lex::symbol::binary_opcode,
		};

		static constexpr auto follow = std::array{
			lex::symbol::semicolon
		};

		static constexpr auto derivation =
			lex::symbol::binary_opcode + binary_argument{};

		template <class Lexer>
		static constexpr void derive(Lexer& lexer) noexcept
		{
			lexer.expect(lex::symbol::binary_opcode);
			binary_argument::derive(lexer);
		}

	};
}

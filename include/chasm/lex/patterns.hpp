#pragma once

#include <array>
#include <sprout/optional.hpp>
#include <sprout/iterator/to_lower_iterator.hpp>

#include "token.hpp"
#include "detail/string_helpers.hpp"

#define CHASM_LEX_CHECK_PATTERN(string, tokens)\
	for (const auto& token : tokens) \
		if (detail::string_equals(token.value, string))\
			return token;

namespace chasm::lex
{
	constexpr auto binary_tokens = std::array{
		token{symbol::binary_opcode, "mov"},
		token{symbol::binary_opcode, "movzx"},
		token{symbol::binary_opcode, "movsxd"},
		token{symbol::binary_opcode, "movsb"},
		token{symbol::binary_opcode, "lea"},

		token{symbol::binary_opcode, "test"},
		token{symbol::binary_opcode, "cmp"},

		token{symbol::binary_opcode, "and"},
		token{symbol::binary_opcode, "or"},
		token{symbol::binary_opcode, "xor"},

		token{symbol::binary_opcode, "add"},
		token{symbol::binary_opcode, "sub"}
	};

	constexpr auto unary_tokens = std::array{
		token{symbol::unary_opcode, "call"},
		token{symbol::unary_opcode, "jmp"},
		token{symbol::unary_opcode, "je"},
		token{symbol::unary_opcode, "jne"},
		token{symbol::unary_opcode, "jle"},
		token{symbol::unary_opcode, "jnl"},
		token{symbol::unary_opcode, "mul"},
		token{symbol::unary_opcode, "inc"},
		token{symbol::unary_opcode, "dec"},

		token{symbol::unary_opcode, "push"},
		token{symbol::unary_opcode, "pop"},

		token{symbol::unary_opcode, "ret"},
	};

	constexpr auto nullary_tokens = std::array{
		token{symbol::nullary_opcode, "pushad"},
		token{symbol::nullary_opcode, "pushfd"},
		token{symbol::nullary_opcode, "popfd"},
		token{symbol::nullary_opcode, "popfd"},
		token{symbol::nullary_opcode, "nop"},
	};

	constexpr auto register_tokens = std::array{
		// instruction pointer
		token{symbol::reg, "eip"},

		// 32-bit registers
		token{symbol::reg, "eax"},
		token{symbol::reg, "ebx"},
		token{symbol::reg, "ecx"},
		token{symbol::reg, "edx"},
		token{symbol::reg, "edi"},
		token{symbol::reg, "esi"},
		token{symbol::reg, "ebp"},
		token{symbol::reg, "esp"},


		// 16-bit registers
		token{symbol::reg, "ax"},
		token{symbol::reg, "bx"},
		token{symbol::reg, "cx"},
		token{symbol::reg, "dx"},
		token{symbol::reg, "di"},
		token{symbol::reg, "si"},
		token{symbol::reg, "bp"},
		token{symbol::reg, "sp"},
	};

		// terminals
	constexpr auto terminal_tokens = std::array{
		token{symbol::comma, ","},
		token{symbol::semicolon, ";"},
		token{symbol::open_bracket, "["},
		token{symbol::close_bracket, "]"},
	};

	template <class String>
	constexpr sprout::optional<token> match_pattern(const String& string) noexcept
	{
		CHASM_LEX_CHECK_PATTERN(string, binary_tokens);
		CHASM_LEX_CHECK_PATTERN(string, unary_tokens);
		CHASM_LEX_CHECK_PATTERN(string, nullary_tokens);
		CHASM_LEX_CHECK_PATTERN(string, register_tokens);
		CHASM_LEX_CHECK_PATTERN(string, terminal_tokens);

		if (detail::is_hex_number(string))
			return token{lex::symbol::number, string};

		return {};
	}
}

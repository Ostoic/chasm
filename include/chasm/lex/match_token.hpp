#pragma once

#include <array>
#include <sprout/optional.hpp>

#include "token.hpp"
#include "detail/string_helpers.hpp"
#include "detail/is_variable.hpp"

#define CHASM_LEX_FIND_TOKEN(string, tokens)\
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
		token{symbol::binary_opcode, "sub"},
		token{symbol::binary_opcode, "shl"},
		token{symbol::binary_opcode, "shr"},
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
		token{symbol::nullary_opcode, "popad"},
		token{symbol::nullary_opcode, "popfd"},
		token{symbol::nullary_opcode, "nop"},
	};

	constexpr auto register_tokens = std::array{
		// instruction pointer
		token{symbol::registr, "eip"},

		// 32-bit registers
		token{symbol::registr, "eax"},
		token{symbol::registr, "ebx"},
		token{symbol::registr, "ecx"},
		token{symbol::registr, "edx"},
		token{symbol::registr, "edi"},
		token{symbol::registr, "esi"},
		token{symbol::registr, "ebp"},
		token{symbol::registr, "esp"},

		// 16-bit registers
		token{symbol::registr, "ax"},
		token{symbol::registr, "bx"},
		token{symbol::registr, "cx"},
		token{symbol::registr, "dx"},
		token{symbol::registr, "di"},
		token{symbol::registr, "si"},
		token{symbol::registr, "bp"},
		token{symbol::registr, "sp"},
	};

	// terminals
	constexpr auto terminal_tokens = std::array{
		token{symbol::comma, ","},
		token{symbol::semicolon, ";"},
		token{symbol::open_bracket, "["},
		token{symbol::close_bracket, "]"},
		token{symbol::open_brace, "{"},
		token{symbol::close_brace, "}"},
		token{symbol::variable, "{}[];,"}, // Use detail::is_variable instead of this
	};

	template <class String>
	constexpr token match_token(const String& string)
	{
		if (detail::is_variable(string))
			return token{
				lex::symbol::variable,
				detail::make_string_view(string).substr(1, detail::string_length(string) - 2)
		};

		CHASM_LEX_FIND_TOKEN(string, binary_tokens);
		CHASM_LEX_FIND_TOKEN(string, unary_tokens);
		CHASM_LEX_FIND_TOKEN(string, nullary_tokens);
		CHASM_LEX_FIND_TOKEN(string, register_tokens);
		CHASM_LEX_FIND_TOKEN(string, terminal_tokens);

		if (detail::is_hex_number(string))
			return token{lex::symbol::number, string};

		else
			return token{lex::symbol::end, string};
	}
}

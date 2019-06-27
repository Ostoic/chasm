#pragma once

#include <array>
#include <sprout/optional.hpp>
#include <sprout/iterator/to_lower_iterator.hpp>

#include "token.hpp"
#include "string_helpers.hpp"

#define CHASM_MAKE_LEX_PATTERN(value, symbol) std::pair{ value,  token{ symbol,	value} }

namespace chasm::lex
{
	constexpr auto patterns = std::array{
		CHASM_MAKE_LEX_PATTERN("mov", symbol::binary_opcode),
		CHASM_MAKE_LEX_PATTERN("movzx", symbol::binary_opcode),
		CHASM_MAKE_LEX_PATTERN("movsxd", symbol::binary_opcode),
		CHASM_MAKE_LEX_PATTERN("movsb", symbol::binary_opcode),
		CHASM_MAKE_LEX_PATTERN("lea", symbol::binary_opcode),

		CHASM_MAKE_LEX_PATTERN("test", symbol::binary_opcode),
		CHASM_MAKE_LEX_PATTERN("cmp", symbol::binary_opcode),
		CHASM_MAKE_LEX_PATTERN("call", symbol::unary_opcode),
		CHASM_MAKE_LEX_PATTERN("jmp", symbol::unary_opcode),
		CHASM_MAKE_LEX_PATTERN("je", symbol::unary_opcode),
		CHASM_MAKE_LEX_PATTERN("jne", symbol::unary_opcode),
		CHASM_MAKE_LEX_PATTERN("jle", symbol::unary_opcode),
		CHASM_MAKE_LEX_PATTERN("jnl", symbol::unary_opcode),

		CHASM_MAKE_LEX_PATTERN("and", symbol::binary_opcode),
		CHASM_MAKE_LEX_PATTERN("or", symbol::binary_opcode),
		CHASM_MAKE_LEX_PATTERN("xor", symbol::binary_opcode),

		CHASM_MAKE_LEX_PATTERN("add", symbol::binary_opcode),
		CHASM_MAKE_LEX_PATTERN("sub", symbol::binary_opcode),
		CHASM_MAKE_LEX_PATTERN("mul", symbol::unary_opcode),
		CHASM_MAKE_LEX_PATTERN("inc", symbol::unary_opcode),
		CHASM_MAKE_LEX_PATTERN("dec", symbol::unary_opcode),

		CHASM_MAKE_LEX_PATTERN("push", symbol::unary_opcode),
		CHASM_MAKE_LEX_PATTERN("pop", symbol::unary_opcode),
		CHASM_MAKE_LEX_PATTERN("pushad", symbol::nullary_opcode),
		CHASM_MAKE_LEX_PATTERN("pushfd", symbol::nullary_opcode),
		CHASM_MAKE_LEX_PATTERN("popfd", symbol::nullary_opcode),
		CHASM_MAKE_LEX_PATTERN("popfd", symbol::nullary_opcode),
		CHASM_MAKE_LEX_PATTERN("ret", symbol::unary_opcode),
		CHASM_MAKE_LEX_PATTERN("nop", symbol::nullary_opcode),

		// instruction pointer
		CHASM_MAKE_LEX_PATTERN("eip", symbol::reg),

		// 32-bit registers
		CHASM_MAKE_LEX_PATTERN("eax", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("ebx", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("ecx", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("edx", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("edi", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("esi", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("ebp", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("esp", symbol::reg),


		// 16-bit registers
		CHASM_MAKE_LEX_PATTERN("ax", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("bx", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("cx", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("dx", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("di", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("si", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("bp", symbol::reg),
		CHASM_MAKE_LEX_PATTERN("sp", symbol::reg),

		// terminals
		CHASM_MAKE_LEX_PATTERN(",", symbol::comma),
		CHASM_MAKE_LEX_PATTERN(";", symbol::semicolon),
		CHASM_MAKE_LEX_PATTERN("[", symbol::open_bracket),
		CHASM_MAKE_LEX_PATTERN("]", symbol::close_bracket),
	};

	template <class String>
	constexpr sprout::optional<token> match_pattern(const String& string) noexcept
	{
		for (const auto& pattern : patterns)
			if (lex::string_equals(pattern.first, string))
				return pattern.second;

		if (lex::is_hex_number(string))
			return token{ lex::symbol::number, string };

		return {};
	}
}

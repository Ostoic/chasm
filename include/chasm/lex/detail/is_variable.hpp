#pragma once

#include "string_helpers.hpp"

namespace chasm::lex::detail
{
	template <class String>
	constexpr bool is_variable(const String& string)
	{
		const auto length = string_length(string);
		if (string[0] != '{' || string[length - 2] != '}')
			return false;

		if (string_has_whitespace(string))
			return false;

		return true;
	}
}
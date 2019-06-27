#pragma once

#include <type_traits>
#include <string_view>
#include <sprout/range/algorithm.hpp>

namespace chasm::lex
{
	template <class String>
	constexpr const char* c_string(const String& string) noexcept
	{
		if constexpr (std::is_class_v<String>)
			return string.data();

		if constexpr (std::is_array_v<String> || std::is_pointer_v<String>)
			return string;

		static_assert("[chasm::lex::c_string] Unable to determine c string of given type");
	}

	template <class LeftString, class RightString>
	constexpr bool string_equals(const LeftString& left, const RightString& right) noexcept
	{
		for (int i = 0; left[i] != 0 && right[i] != 0; ++i)
			if (left[i] != right[i])
				return false;

		return true;
	}

	template <class Char>
	constexpr Char to_upper(const Char c) noexcept
	{
		if ('a' <= c && c <= 'z')
			return c - ('a' - 'A');

		return c;
	}

	template <class Char>
	constexpr bool is_hex_digit(const Char c) noexcept
	{
		return sprout::range::any_of_equal("XABCDEF0123456789", lex::to_upper(c));
	}

	template <class String>
	constexpr bool is_hex_number(const String& string) noexcept
	{
		return sprout::range::all_of(string, lex::is_hex_digit<decltype(string[0])>);
	}

	template <class String>
	constexpr auto string_length(const String& string) noexcept
	{
		int length = 0;
		for (int i = 0; string[i] != 0; ++i)
			length++;

		return length;
	}

	template <class String>
	constexpr auto string_begin(const String& string) noexcept
	{
		return std::begin(string);
	}

	template <class String>
	constexpr auto string_end(const String& string) noexcept
	{
		if constexpr (std::is_pointer_v<String>)
			return string_begin(string) + string_length;

		return std::end(string);
	}

	template <class String>
	constexpr std::string_view make_string_view(const String& string) noexcept
	{
		if constexpr (std::is_same_v<String, std::string_view>)
			return string;

		return std::string_view{lex::c_string(string)};
	}
}

#pragma once

#include <sprout/range/algorithm.hpp>

#include "type_traits.hpp"

namespace chasm::lex::detail
{
	template <class String>
	using c_str_t = decltype(std::declval<String>().c_str());

	template <class String>
	using data_t = decltype(std::declval<String>().data());

	template <class String>
	using size_member_t = decltype(std::declval<String>().size());

	template <class String>
	constexpr bool has_c_str = is_detected_v<c_str_t, String>;

	template <class String>
	constexpr bool has_data = is_detected_v<data_t, String>;

	template <class String>
	constexpr bool has_size = is_detected_v<size_member_t, String>;

	template <class String>
	constexpr const char* c_string(const String& string) noexcept
	{
		if constexpr (has_c_str<String>)
			return string.c_str();

		else if constexpr (has_data<String>)
			return string.data();

		else if constexpr (std::is_array_v<String> || std::is_pointer_v<String>)
			return string;

		static_assert("[chasm::lex::c_string] Unable to determine c-string of given type");
		return "";
	}

	template <class String>
	constexpr auto string_length(const String& string) noexcept
	{
		if constexpr (has_size<String>)
			return string.size();

		std::size_t length = 0;
		for (auto i = 0; string[i] != 0; ++i)
			length++;

		return length;
	}

	template <class LeftString, class RightString>
	constexpr bool string_equals(const LeftString& left, const RightString& right) noexcept
	{
		const auto lhs_size = string_length(left);
		const auto rhs_size = string_length(right);
		if (lhs_size != rhs_size)
			return false;

		for (std::size_t i = 0; i < lhs_size; ++i)
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
		return sprout::range::any_of_equal("XABCDEF0123456789", to_upper(c));
	}

	template <class String>
	constexpr bool is_hex_number(const String& string) noexcept
	{
		return sprout::range::all_of(string, is_hex_digit<decltype(string[0])>);
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

		return std::string_view{c_string(string)};
	}
}

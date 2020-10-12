#pragma once

#include <sprout/range/range_container.hpp>

#include "split_iterator.hpp"
#include "detail/string_helpers.hpp"

namespace chasm::lex
{
	struct capture
	{
		explicit constexpr capture(const char* chars = "")
			: captures(chars)
		{}

		constexpr bool operator()(const char c) const noexcept
		{
			return sprout::range::any_of_equal(captures, c);
		}

		const std::string_view captures;
	};

	using skip = capture;

	constexpr auto empty_capture = capture{""};
	constexpr auto whitespace_skipper = skip{" \t\r\n\b"};
	constexpr auto asm_capture = chasm::lex::capture{":;,[]+-*"};

	template <class String = std::string_view, class Skipper = skip, class Capture = capture>
	using splitter = sprout::range::range_container<split_iterator<String, Skipper, Capture>>;

	/// @brief Split a string into words separated by two types of delimiters.
	/// @param string is the string to split
	/// @param skipper is a predicate describing the skipped delimiters
	/// @param capture is a predicate describing the captured delimiters
	template <class String, class Skipper = skip, class CaptureFn = capture>
	constexpr auto split(
		const String& string,
		const Skipper skipper = whitespace_skipper,
		const CaptureFn capture = asm_capture) noexcept
	{
		using split_it = split_iterator<std::string_view, Skipper, CaptureFn>;

		const auto string_view = detail::make_string_view(string);
		return sprout::range::range_container{
			split_it{string_view, std::begin(string_view), skipper, capture},
			split_it{string_view}
		};
	}

} // end namespace chasm::lex

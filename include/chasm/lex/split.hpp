#pragma once

#include <sprout/range/range_container.hpp>
#include <sprout/iterator/filter_iterator.hpp>
#include <sprout/iterator/transform_iterator.hpp>

#include "split_iterator.hpp"
#include "string_helpers.hpp"

namespace chasm::lex
{
	struct capture
	{
		constexpr capture(const char* chars) : captures(chars) {}

		constexpr bool operator()(const char c) const noexcept
		{
			return sprout::range::any_of_equal(captures, c);
		}

		const std::string_view captures;
	};

	using skip = capture;

	constexpr capture empty_capture{ "" };
	constexpr skip whitespace_skipper{ " \t\r\n\b" };

	template <class String = std::string_view, class Skipper = skip, class Capture = capture>
	using splitter = sprout::range::range_container<split_iterator<String, Skipper, Capture>>;

	/// @brief Split a string into words separated by two types of delimiters.
	/// @param skipper is a predicate describing the skipped delimiters
	/// @param capture is a predicate describing the captured delimiters
	template <class String, class Skipper = skip, class CaptureFn = capture>
	constexpr auto split(const String string, Skipper skipper = whitespace_skipper, CaptureFn capture = empty_capture) noexcept
	{
		const auto string_view = lex::make_string_view(string);
		return sprout::range::range_container{
			split_iterator{string_view, skipper, capture},
			split_iterator{string_view, std::end(string_view), skipper, capture}
		};
	}

} // end namespace chasm::lex

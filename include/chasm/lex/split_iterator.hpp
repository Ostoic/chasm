#pragma once
#include <iterator>
#include <array>
#include <sprout/iterator.hpp>
#include <sprout/algorithm/find_if.hpp>

namespace chasm::lex
{
	template <class StringView, class Skipper, class CaptureFn>
	class split_iterator
		: sprout::iterator<
			std::forward_iterator_tag,
			StringView,
			std::ptrdiff_t,
			StringView,
			StringView
		>
	{
	public:
		using value_type = StringView;
		using string_view = StringView;
		using reference = value_type&;
		using base = sprout::iterator<
			std::forward_iterator_tag,
			StringView,
			std::ptrdiff_t,
			StringView,
			StringView
		>;

	public:
		constexpr split_iterator(
			const string_view string, 
			Skipper skip = {}, CaptureFn capture = {}
		) noexcept
			: split_iterator(string, std::begin(string), skip, capture)
		{}

		constexpr split_iterator(
			const string_view string, const typename string_view::iterator start, 
			Skipper skip = {}, CaptureFn capture = {}
		) noexcept
			: string_(string), current_(start)
			, skip_(skip), capture_(capture)
		{}

		constexpr split_iterator(const split_iterator& other) noexcept
			: string_(other.string_), current_(other.current_)
			, skip_(other.skip_), capture_(other.capture_)
		{}

		constexpr split_iterator& operator=(const split_iterator& other) noexcept
		{
			current_ = other.current_;
			string_ = other.string_;
			skip_ = other.skip_;
			capture_ = other.capture_;
			return *this;
		}

		constexpr value_type operator*() const noexcept
		{
			const auto current_offset = std::distance(std::begin(string_), current_);

			// If the current iterator points to a captured string, then return it
			if (capture_(*current_))
				return string_.substr(current_offset, 1);

			// Skip characters, then find the end of the word
			const auto end_it = this->word_skip(current_);
			const auto count = std::distance(current_, end_it);

			return string_.substr(current_offset, count);
		}

		constexpr split_iterator& operator++() noexcept
		{
			if (capture_(*current_))
			{
				++current_;
				current_ = this->full_skip(current_);
				return *this;
			}

			// Skip over current word
			current_ = this->word_skip(current_);

			// Skip over skipped characters
			current_ = this->full_skip(current_);
			return *this;
		}

		constexpr split_iterator operator++(int) noexcept
		{
			split_iterator temp = *this;
			++(*this);
			return temp;
		}

		constexpr void swap(split_iterator& other) noexcept
		{
			sprout::swap(current_, other.current_);
			sprout::swap(string_, other.string_);
			sprout::swap(skip_, other.skip_);
			sprout::swap(capture_, other.capture_);
		}

		template <class SV, class S, class C>
		friend constexpr bool operator==(const split_iterator<SV, S, C>& lhs, const split_iterator<SV, S, C>& rhs)
		{
			return lhs.current_ == rhs.current_;
		}

		template <class SV, class S, class C>
		friend constexpr bool operator<(const split_iterator<SV, S, C>& lhs, const split_iterator<SV, S, C>& rhs)
		{
			return lhs.current_ < rhs.current_;
		}

	private:
		typename value_type::iterator current_;
		value_type string_;

		Skipper skip_;
		CaptureFn capture_;

	private:
		template <class RandomIt>
		constexpr auto full_skip(RandomIt it) const
		{
			// skip whitespace characters
			while (it != std::end(string_) && skip_(*it))
				std::advance(it, 1);

			return it;
		}

		template <class RandomIt>
		constexpr auto word_skip(RandomIt it) const
		{
			// find the end of the current word
			while (it != std::end(string_) && !skip_(*it) && !capture_(*it))
				std::advance(it, 1);

			return it;
		}

	public:
		constexpr void swap(split_iterator& lhs, split_iterator& rhs) noexcept
		{
			lhs.swap(rhs);
		}
	};

	template <class SV, class S, class C>
	constexpr bool operator!=(const split_iterator<SV, S, C>& lhs, const split_iterator<SV, S, C>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class SV, class S, class C>
	constexpr bool operator>(const split_iterator<SV, S, C>& lhs, const split_iterator<SV, S, C>& rhs)
	{
		return !(lhs < rhs) && (lhs != rhs);
	}

	template <class SV, class S, class C>
	constexpr bool operator<=(const split_iterator<SV, S, C>& lhs, const split_iterator<SV, S, C>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class SV, class S, class C>
	constexpr bool operator>=(const split_iterator<SV, S, C>& lhs, const split_iterator<SV, S, C>& rhs)
	{
		return !(lhs < rhs);
	}

} // end namespace chasm::lex

namespace std
{
	template <class SV, class S, class C>
	struct iterator_traits<chasm::lex::split_iterator<SV, S, C>>
		: iterator_traits<typename chasm::lex::split_iterator<SV, S, C>::base>
	{};
}
#pragma once
#include <iterator>
#include <sprout/iterator.hpp>

namespace chasm::lex
{
	struct capture;

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
		constexpr split_iterator(const string_view string) noexcept
			: split_iterator(string, std::end(string), Skipper{}, CaptureFn{})
		{}

		constexpr split_iterator(const split_iterator& other) noexcept
			: split_iterator(other.string_, other.current_, other.skip_, other.capture_)
		{}

		constexpr split_iterator(
			const string_view string, const typename string_view::iterator start,
			const Skipper skip, const CaptureFn capture
		) noexcept
			: current_{start}, string_(string)
			, skip_(skip), capture_(capture)
		{
			if (current_ != std::end(string) && skip(*current_))
				current_ = this->full_skip(current_);
		}

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
			if (this->capture(*current_))
				return string_.substr(current_offset, 1);

			// Skip characters, then find the end of the word
			const auto end_it = this->word_skip(current_);
			const auto count = std::distance(current_, end_it);

			return string_.substr(current_offset, count);
		}

		constexpr split_iterator& operator++() noexcept
		{
			// If the current character is captured, then skip to the next
			if (this->capture(*current_))
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

		friend constexpr bool operator==(const split_iterator& lhs, const split_iterator& rhs)
		{
			return lhs.current_ == rhs.current_;
		}

		friend constexpr bool operator<(const split_iterator& lhs, const split_iterator& rhs)
		{
			return lhs.current_ < rhs.current_;
		}

	private:
		typename value_type::iterator current_;
		const value_type string_;

		const Skipper skip_;
		const CaptureFn capture_;

	private:

		[[nodiscard]]
		constexpr bool skip(const char c) const noexcept
		{
			return (skip_)(c);
		}

		[[nodiscard]]
		constexpr bool capture(const char c) const noexcept
		{
			return (capture_)(c);
		}

		template <class RandomIt> [[nodiscard]]
		constexpr auto full_skip(RandomIt it) const
		{
			// skip whitespace characters
			while (it != std::end(string_) && this->skip(*it))
				std::advance(it, 1);

			return it;
		}

		template <class RandomIt> [[nodiscard]]
		constexpr auto word_skip(RandomIt it) const
		{
			// find the end of the current word
			while (it != std::end(string_) && !this->skip(*it) && !this->capture(*it))
				std::advance(it, 1);

			return it;
		}

	public:
		static constexpr void swap(split_iterator& lhs, split_iterator& rhs) noexcept
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
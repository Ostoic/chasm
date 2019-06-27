#pragma once

#include "token.hpp"
#include "split.hpp"

#include <sprout/optional.hpp>

namespace chasm::lex
{
	template <class String>
	class lexer
	{
	public:
		constexpr explicit lexer(const String& string) noexcept
			: string_(lex::c_string(string))
			, splitting_(lex::split(string, lex::whitespace_skipper, lex::capture{";,[]+-*"}))
			, it_(std::begin(splitting_))
		{}

		constexpr token next_token() noexcept
		{
			if (it_ == std::end(splitting_))
				return token{symbol::end, "$"};

			const auto symbol = lex::match_pattern(*(it_++));
			if (!symbol)
				return token{symbol::end, "$"};

			return symbol.get();
		}

		constexpr symbol lookahead() const noexcept
		{
			auto next_it = it_; ++next_it;
			if (next_it == std::end(splitting_))
				return symbol::end;

			return lex::match_pattern(*next_it).get().symbol;
		}

		constexpr symbol peek() const noexcept
		{
			if (it_ == std::end(splitting_))
				return symbol::end;

			return lex::match_pattern(*it_).get().symbol;
		}

		constexpr auto expect(lex::symbol s)
		{
			const auto next = this->next_token().symbol;
			assert(next == s);
		}

		constexpr auto string() const noexcept { return string_; }

	private:
		const std::string_view string_;
		const lex::splitter<std::string_view, lex::skip, lex::capture> splitting_;
		typename decltype(splitting_)::iterator it_;
	};

	template <class Lexer>
	constexpr symbol next_token(Lexer& lexer) noexcept
	{
		return lexer.next_token();
	}

	template <class Lexer>
	constexpr symbol lookahead(const Lexer& lexer) noexcept
	{
		return lexer.lookahead();
	}

	template <class Lexer>
	constexpr symbol peek(const Lexer& lexer) noexcept
	{
		return lexer.peek();
	}
}
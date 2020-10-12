#pragma once

#include "token.hpp"
#include "split.hpp"
#include "match_token.hpp"

namespace chasm::lex
{
	template <class String>
	class lexer
	{
	public:
		constexpr explicit lexer(const String& string) noexcept
			: string_{detail::c_string(string)}
			, splitting_{lex::split(string, lex::whitespace_skipper, lex::asm_capture)}
			, it_{std::begin(splitting_)}
		{}

		[[nodiscard]]
		constexpr token next_token() noexcept;

		[[nodiscard]]
		constexpr symbol lookahead() const noexcept;

		[[nodiscard]]
		constexpr symbol peek() const noexcept;

		constexpr void expect(const lex::symbol s);

		[[nodiscard]]
		constexpr std::string_view string() const noexcept;

	private:
		const std::string_view string_;
		const lex::splitter<std::string_view, lex::skip, lex::capture> splitting_;
		typename decltype(splitting_)::iterator it_;
	};

	template <class Lexer>
	constexpr symbol next_token(Lexer& lexer) noexcept;

	template <class Lexer>
	constexpr symbol lookahead(const Lexer& lexer) noexcept;

	template <class Lexer>
	constexpr symbol peek(const Lexer& lexer) noexcept;
}

namespace chasm::lex
{
	template <class String>
	[[nodiscard]]
	constexpr token lexer<String>::next_token() noexcept
	{
		if (it_ == std::end(splitting_))
			return token{symbol::end, "$"};

		return lex::match_token(*(it_++));
	}

	template <class String> [[nodiscard]]
	constexpr symbol lexer<String>::lookahead() const noexcept
	{
		auto next_it = it_; ++next_it;
		if (next_it == std::end(splitting_))
			return symbol::end;

		return lex::match_token(*next_it).symbol;
	}

	template <class String> [[nodiscard]]
	constexpr symbol lexer<String>::peek() const noexcept
	{
		if (it_ == std::end(splitting_))
			return symbol::end;

		return lex::match_token(*it_).symbol;
	}

	template <class String>
	constexpr void lexer<String>::expect(const lex::symbol s)
	{
		const auto next = this->next_token().symbol;
		assert(next == s);
	}

	template <class String> [[nodiscard]]
	constexpr std::string_view lexer<String>::string() const noexcept
	{
		return string_;
	}

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
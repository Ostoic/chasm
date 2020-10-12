#pragma once

#include "../lex/lexer.hpp"
#include "grammar/program.hpp"

namespace chasm::parse
{
	template <class String>
	class parser
	{
	public:
		constexpr explicit parser(const String& string)
			: lexer_{string}
		{}

		constexpr bool parse()
		{
			grammar::program::derive(lexer_);
			return lexer_.peek() == lex::symbol::end;
		}

		constexpr const auto& lexer() const noexcept
		{
			return lexer_;
		}

		constexpr auto& lexer() noexcept
		{
			return lexer_;
		}

	private:
		lex::lexer<String> lexer_;
	};
}

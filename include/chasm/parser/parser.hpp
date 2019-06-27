#pragma once

#include "../lex/lexer.hpp"
#include "grammar/program.hpp"

namespace chasm::parser
{
	template <class String>
	class parser
	{
	public:
		constexpr explicit parser(const String& string)
			: lexer_(string)
		{}

		constexpr auto parse()
		{
			grammar::program::derive(lexer_);
			return lexer_.peek() == lex::symbol::end;
		}

	private:
		lex::lexer<String> lexer_;
	};
}

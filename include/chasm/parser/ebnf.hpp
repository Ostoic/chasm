#pragma once

#include "../lex/token.hpp"
#include "../lex/lexer.hpp"

namespace chasm::parse
{
	// Todo:
	// Fix or just throw it out; not necessary, doesn't really clean up code much.
	// it could if done correctly I suppose?
	// 
	constexpr auto operator+(const lex::symbol lhs, const lex::symbol rhs)
	{
		return [lhs, rhs](const auto& lexer)
		{
			lexer.expect(lhs);
			lexer.expect(rhs);
		};
	}

	template <class Production>
	constexpr auto operator+(const lex::symbol lhs, const Production& rhs)
	{
		return [lhs, rhs](const auto& lexer)
		{
			lexer.expect(lhs);
			Production::derive(lexer);
		};
	}

	template <class Production>
	constexpr auto operator+(const Production& lhs, const lex::symbol rhs)
	{
		return [lhs, rhs](const auto& lexer)
		{
			Production::derive(lexer);
			lexer.expect(rhs);
		};
	}

	// production = lex::symbol::open_bracket + register_or_number{} + lex::symbol::close_bracket
}
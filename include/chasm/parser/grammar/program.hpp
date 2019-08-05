#pragma once

#include "instruction.hpp"

namespace chasm::parse::grammar
{
	namespace detail
	{
		template <class Lexer, class Follow>
		static constexpr void program_nullable_impl(Lexer& lexer) noexcept;
	}

	// program_nullable -> program | .
	struct program_nullable
	{
		static constexpr auto first = std::array{
			lex::symbol::binary_opcode,
			lex::symbol::unary_opcode,
			lex::symbol::nullary_opcode,
		};

		static constexpr auto follow = std::array{
			lex::symbol::end
		};

		template <class Lexer>
		static constexpr void derive(Lexer& lexer) noexcept
		{
			detail::program_nullable_impl(lexer);
		}
	};

	// Used to get around tricky circular dependency of these productions
	namespace detail
	{
		template <class Lexer>
		static constexpr void program_impl(Lexer& lexer) noexcept;

		template <class Lexer>
		static constexpr void program_nullable_impl(Lexer& lexer) noexcept
		{
			if (!sprout::range::any_of_equal(grammar::follow(program_nullable{}), lexer.peek()))
				program_impl(lexer);
		}

		template <class Lexer>
		static constexpr void program_impl(Lexer& lexer) noexcept
		{
			instruction::derive(lexer);
			lexer.expect(lex::symbol::semicolon);
			program_nullable_impl(lexer);
		}
	}

	// program -> instruction ; program_nullable .
	struct program
	{
		static constexpr auto first = std::array{
			lex::symbol::binary_opcode,
			lex::symbol::unary_opcode,
			lex::symbol::nullary_opcode,
		};

		static constexpr auto follow = std::array{
			lex::symbol::end
		};

		template <class Lexer>
		static constexpr void derive(Lexer& lexer) noexcept
		{
			detail::program_impl(lexer);
		}
	};
}

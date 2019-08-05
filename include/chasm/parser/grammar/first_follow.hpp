#pragma once

namespace chasm::parse::grammar
{
	template <class Production>
	constexpr auto first(Production production) noexcept
	{
		return Production::first;
	}

	template <class Production>
	constexpr auto follow(Production production) noexcept
	{
		return Production::follow;
	}
}
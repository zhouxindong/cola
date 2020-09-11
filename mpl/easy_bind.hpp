#pragma once
#ifndef _COLA_MPL_EASY_BIND_HPP_
#define _COLA_MPL_EASY_BIND_HPP_

#include <functional>

namespace cola
{
	// placeholder
	template <int I>
	struct Place_holder
	{
		static constexpr int value = I;
		using type = Place_holder<I>;
	};
}

namespace std
{
	/* stl definitions
	template <int _Nx>
	struct _Ph { // placeholder
	};

	template <class _Tx>
	struct is_placeholder : integral_constant<int, 0> { // template to indicate that _Tx is not a placeholder
	};

	template <int _Nx>
	struct is_placeholder<_Ph<_Nx>>
		: integral_constant<int, _Nx> { // template specialization to indicate that _Ph<_Nx> is a placeholder
	};

	template <class _Tx>
	struct is_placeholder<const _Tx> : is_placeholder<_Tx>::type { // ignore cv-qualifiers
	};

	template <class _Tx>
	struct is_placeholder<volatile _Tx> : is_placeholder<_Tx>::type { // ignore cv-qualifiers
	};

	template <class _Tx>
	struct is_placeholder<const volatile _Tx> : is_placeholder<_Tx>::type { // ignore cv-qualifiers
	};
	*/

	template <int I>
	struct is_placeholder<cola::Place_holder<I>>
		: std::integral_constant<int, I> {};
}

namespace cola
{
	namespace detail
	{
		/*
		Build_indices<N> -> Indices<0, 1, ... , N-1>
		*/

		// Indices
		template <std::size_t... Is>
		struct Indices {};

		// primary template
		template <std::size_t... Is>
		struct Build_indices;

		// recurse
		template <std::size_t N, std::size_t... Is>
		struct Build_indices<N, Is...>
			: Build_indices<N-1, N-1, Is...>
		{};

		// basis
		template <std::size_t... Is>
		struct Build_indices<0, Is...>
			: Indices<Is...>
		{};
	}
}

#endif // !_COLA_MPL_EASY_BIND_HPP_

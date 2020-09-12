#pragma once
#ifndef _COLA_TYPELISTS_VALUE_LIST_HPP_
#define _COLA_TYPELISTS_VALUE_LIST_HPP_

#include "type_list.hpp"

namespace cola
{
	template <typename T, T Value>
	struct CT_value
	{
		static constexpr T value = Value;
	};

	namespace VL
	{
		/**
		* Multiply
		*/
		template <typename T, typename U>
		struct Multiply;

		template <typename T, T Value1, T Value2>
		struct Multiply<CT_value<T, Value1>, CT_value<T, Value2>>
		{
		public:
			using type = CT_value<T, Value1* Value2>;
		};

		template <typename T, typename U>
		using Multiply_t = typename Multiply<T, U>::type;
	}

	template <typename T, T ...Values>
	struct Value_list {};

	namespace TL
	{
		template <typename T, T ...Values>
		struct Is_empty<Value_list<T, Values...>>
		{
			static constexpr bool value = sizeof...(Values) == 0;
		};

		template <typename T, T Head, T ...Tail>
		struct Front<Value_list<T, Head, Tail...>>
		{
			using type = CT_value<T, Head>;
			static constexpr T value = Head;
		};

		template <typename T, T Head, T ...Tail>
		struct Pop_front<Value_list<T, Head, Tail...>>
		{
			using type = Value_list<T, Tail...>;
		};

		template <typename T, T ...Values, T New>
		struct Push_front<Value_list<T, Values...>, CT_value<T, New>>
		{
			using type = Value_list<T, New, Values...>;
		};

		template <typename T, T ...Values, T New>
		struct Push_back<Value_list<T, Values...>, CT_value<T, New>>
		{
			using type = Value_list<T, Values..., New>;
		};
	}

	namespace TL
	{
		template <typename Types, typename Indices>
		class Select;

		template <typename Types, unsigned ...Indices>
		class Select<Types, Value_list<unsigned, Indices...>>
		{
		public:
			using type = Type_list<N_element_t<Types, Indices>...>;
		};

		template <typename Types, typename Indices>
		using Select_t = typename Select<Types, Indices>::type;
	}
}

#endif // !_COLA_TYPELISTS_VALUE_LIST_HPP_

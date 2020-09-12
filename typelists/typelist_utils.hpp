#pragma once
#ifndef _COLA_TYPELISTS_TYPELIST_UTILS_HPP_
#define _COLA_TYPELISTS_TYPELIST_UTILS_HPP_

#include <utility>

#include "type_list.hpp"

//namespace std
//{
//	template <unsigned int N>
//	using unsigned_constant = integral_constant<unsigned int, N>;
//}

namespace cola
{
	namespace TL
	{
		template <typename List, template <typename> class F>
		class Apply;

		// Type_list<>
		template <typename... Elements, template <typename> class F>
		class Apply<Type_list<Elements...>, F>
			: public Apply<Elements, F>...
		{
		};

		// normal T
		template <typename T, template <typename> class F>
		class Apply : public F<T>
		{
		};

		// Type_list<>
		template <template <typename> class F>
		class Apply<Type_list<>, F>
		{
		};

		// 1. cast
		template <typename T, typename List, template <typename> class F>
		F<T>& field(Apply<List, F>& obj)
		{
			return obj;
		}

		template <typename T, typename List, template <typename> class F>
		F<T> const& field(Apply<List, F> const& obj)
		{
			return obj;
		}

		// 2. index
		//template <typename List, template <typename> class F, unsigned N>
		//class Field_impl;

		//template <typename Head, typename... Tail, template <typename> class F, unsigned N>
		//class Field_impl<Type_list<Head, Tail...>, F, N>
		//{
		//public:
		//	//static F<N_element_t<Type_list<Tail...>, N - 1>>& get(Apply<Type_list<Head, Tail...>, F>& obj)
		//	//{

		//	//}
		//};

	}
}

#endif // !_COLA_TYPELISTS_TYPELIST_UTILS_HPP_

#pragma once
#ifndef _COLA_TYPELISTS_TYPELIST_UTILS_HPP_
#define _COLA_TYPELISTS_TYPELIST_UTILS_HPP_

#include "type_list.hpp"

namespace cola
{
	namespace TL
	{
		template <typename List, template <typename> class F>
		class Apply;

		template <typename... Elements, template <typename> class F>
		class Apply<Type_list<Elements...>, F>
			: public Apply<Elements, F>...
		{
		};

		template <typename T, template <typename> class F>
		class Apply : public F<T>
		{
		};

		template <template <typename> class F>
		class Apply<Type_list<>, F>
		{
		};

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
	}
}

#endif // !_COLA_TYPELISTS_TYPELIST_UTILS_HPP_

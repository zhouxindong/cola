#pragma once
#ifndef _COLA_TYPELISTS_TYPELIST_ALGORITHM_HPP_
#define _COLA_TYPELISTS_TYPELIST_ALGORITHM_HPP_

#include "type_list.hpp"

namespace cola
{
	namespace TL
	{
		/**
		* transform (map)
		*/
		template <typename List, template <typename> class MetaFun, bool Empty = Is_empty_v<List>>
		class Transform;

		template <typename... Elements, template <typename> class MetaFun>
		class Transform <Type_list<Elements...>, MetaFun, false>
		{
		public:
			using type = Type_list<typename MetaFun<Elements>::type...>;
		};

		template <template <typename> class MetaFun>
		class Transform <Type_list<>, MetaFun, true>
		{
		public:
			using type = Type_list<>;
		};

		template <typename List, template <typename> class MetaFun, bool Empty = Is_empty_v<List>>
		using Transform_t = typename Transform<List, MetaFun>::type;

		/**
		* accumulate (reduce)
		*/
		template <
			typename List,
			template <typename, typename> class F,
			typename I>
			class Accumulate;

		template <
			typename Head, typename... Tail,
			template <typename, typename> class F,
			typename I>
			class Accumulate <Type_list<Head, Tail...>, F, I> 
		{
		public:
			using type = typename Accumulate<Type_list<Tail...>, F, typename F<I, Head>::type>::type;
		};

		template <
			template <typename, typename> class F,
			typename I>
			class Accumulate <Type_list<>, F, I>
		{
		public:
			using type = I;
		};

		template <
			typename List,
			template <typename, typename> class F,
			typename I>
			using Accumulate_t = typename Accumulate<List, F, I>::type;

		/**
		* filter
		*/
		template <
			typename List,
			template <typename> class Predicate>
		class Filter;

		template <
			template <typename> class Predicate>
		class Filter<Type_list<>, Predicate>
		{
		public:
			using type = Type_list<>;
		};

		template <
			typename Head, typename... Tail,
			template <typename> class Predicate>
		class Filter<Type_list<Head, Tail...>, Predicate>
		{
		private:
			using T1 = typename Filter<Type_list<Tail...>, Predicate>::type;

		public:
			using type = std::conditional_t<
				Predicate<Head>::value,
				Push_front_t<T1, Head>,
				T1>;
		};

		template <typename List, template <typename> class Predicate>
		using Filter_t = typename Filter<List, Predicate>::type;

		/**
		* Insertion_sort
		*/
		//template <
		//	typename List,
		//	template <typename, typename> class Compare>
		//class Insertion_sort;

		//template <
		//	typename Head, 
		//	typename ...Tail, 
		//	template <typename T, typename U> class Compare>
		//class Insertion_sort<Type_list<Head, Tail...>, Compare>
		//{
		//public:
		//	using type = Push_front_t<typename Insertion_sort<Type_list<Tail...>, Compare>::type, Head>;
		//};
		//		 
		//template <template<typename, typename> class Compare>
		//class Insertion_sort<Type_list<>, Compare>
		//{
		//public:
		//	using type = Type_list<>;
		//};
	}
}

#endif // !_COLA_TYPELISTS_TYPELIST_ALGORITHM_HPP_

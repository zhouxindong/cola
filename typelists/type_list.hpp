#pragma once
#ifndef _COLA_TYPELISTS_TYPE_LIST_HPP_
#define _COLA_TYPELISTS_TYPE_LIST_HPP_

#include <type_traits>

namespace cola
{
	// primary class
	template <typename... Elements>
	class Type_list {};

	// Type_list algorithm
	namespace TL
	{
		/*
		* length
		*/
		template <typename>
		class Length;

		template <typename Head, typename... Tail>
		class Length<Type_list<Head, Tail...>>
		{
		public:
			static constexpr int value = 1 + Length<Type_list<Tail...>>::value;
		};

		template <>
		class Length<Type_list<>>
		{
		public:
			static constexpr int value = 0;
		};

		/*
		* Front
		*/
		template <typename>
		class Front;

		template <typename Head, typename... Tail>
		class Front<Type_list<Head, Tail...>>
		{
		public:
			using type = Head;
		};

		template <>
		class Front<Type_list<>>
		{
		public:
			using type = void;
		};

		template <typename List>
		using Front_t = typename Front<List>::type;

		/*
		* Pop_front
		*/
		template <typename>
		class Pop_front;

		template <typename Head, typename... Tail>
		class Pop_front<Type_list<Head, Tail...>>
		{
		public:
			using type = Type_list<Tail...>;
		};

		template <typename List>
		using Pop_front_t = typename Pop_front<List>::type;

		/*
		* Push_front
		*/
		template <typename List, typename NewElement>
		class Push_front;

		template <typename... Elements, typename NewElement>
		class Push_front<Type_list<Elements...>, NewElement>
		{
		public:
			using type = Type_list<NewElement, Elements...>;
		};

		template <typename List, typename NewElement>
		using Push_front_t = typename Push_front<List, NewElement>::type;

		/**
		* N_element
		*/
		template <typename List, unsigned N>
		class N_element : public N_element<Pop_front_t<List>, N-1>
		{
		};

		template <typename List>
		class N_element<List, 0> : public Front<List>
		{
		};

		template <typename List, unsigned N>
		using N_element_t = typename N_element<List, N>::type;

		/**
		* Index_of
		*/
		template <typename List, typename Element>
		class Index_of;

		template <typename Element>
		class Index_of<Type_list<>, Element>
		{
		public:
			static constexpr int value = -1;
		};

		template <typename... Tail, typename Element>
		class Index_of<Type_list<Element, Tail...>, Element>
		{
		public:
			static constexpr int value = 0;
		};

		template <typename Head, typename... Tail, typename Element>
		class Index_of<Type_list<Head, Tail...>, Element>
		{
		private:
			static constexpr int temp = Index_of<Type_list<Tail...>, Element>::value;

		public:
			static constexpr int value = temp == -1 ? -1 : 1 + temp;
		};

		template <typename List, typename Element>
		inline constexpr int Index_of_v = Index_of<List, Element>::value;

		/**
		* Largest
		*/
		template <typename>
		class Largest_type;

		template <typename Head, typename... Tail>
		class Largest_type<Type_list<Head, Tail...>>
		{
		private:
			using Rest = typename Largest_type<Type_list<Tail...>>::type;

		public:
			using type = std::conditional_t<(sizeof(Head) >= sizeof(Rest)), Head, Rest>;
		};

		template <>
		class Largest_type<Type_list<>>
		{
		public:
			using type = char;
		};

		template <typename List>
		using Largest_type_t = typename Largest_type<List>::type;

		/**
		* Is_empty
		*/
		template <typename>
		class Is_empty;

		template <typename... Elements>
		class Is_empty<Type_list<Elements...>>
		{
		public:
			static constexpr bool value = false;
		};

		template <>
		class Is_empty<Type_list<>>
		{
		public:
			static constexpr bool value = true;
		};

		template <typename List>
		inline constexpr bool Is_empty_v = Is_empty<List>::value;

		/**
		* Push_back
		*/
		template <typename List, typename NewElement>
		class Push_back;

		template <typename... Elements, typename NewElement>
		class Push_back<Type_list<Elements...>, NewElement>
		{
		public:
			using type = Type_list<Elements..., NewElement>;
		};

		template <typename List, typename NewElement>
		using Push_back_t = typename Push_back<List, NewElement>::type;

		/**
		* Back
		*/
		template <typename>
		class Back;

		template <typename Head, typename... Tail>
		class Back<Type_list<Head, Tail...>>
		{
		public:
			using type = typename Back<Type_list<Tail...>>::type;
		};

		template <typename T>
		class Back<Type_list<T>>
		{
		public:
			using type = T;
		};

		template <>
		class Back<Type_list<>>
		{
		public:
			using type = void;
		};

		template <typename List>
		using Back_t = typename Back<List>::type;

		/**
		* Pop_back
		*/
		template <typename>
		class Pop_back;

		template <typename Head, typename... Tail>
		class Pop_back<Type_list<Head, Tail...>>
		{
		public:
			using type = Push_front_t<typename Pop_back<Type_list<Tail...>>::type, Head>;
		};

		template <>
		class Pop_back<Type_list<>>
		{
		public:
			using type = Type_list<>;
		};

		template <typename T>
		class Pop_back<Type_list<T>>
		{
		public:
			using type = Type_list<>;
		};

		template <typename T, typename U>
		class Pop_back<Type_list<T, U>>
		{
		public:
			using type = Type_list<T>;
		};

		template <typename List>
		using Pop_back_t = typename Pop_back<List>::type;

		/**
		* Erase
		*/
		template <typename List, typename Element>
		class Erase;

		template <typename... Tail, typename Element>
		class Erase<Type_list<Element, Tail...>, Element>
		{
		public:
			using type = Type_list<Tail...>;
		};

		template <typename Head, typename... Tail, typename Element>
		class Erase<Type_list<Head, Tail...>, Element>
		{
		public:
			using type = Push_front_t<typename Erase<Type_list<Tail...>, Element>::type, Head>;
		};

		template <typename Element>
		class Erase<Type_list<Element>, Element>
		{
		public:
			using type = Type_list<>;
		};

		template <typename Element>
		class Erase<Type_list<>, Element>
		{
		public:
			using type = Type_list<>;
		};

		template <typename List, typename Element>
		using Erase_t = typename Erase<List, Element>::type;

		/**
		* Erase_all
		*/
		template <typename List, typename Element>
		class Erase_all;

		template <typename Element>
		class Erase_all<Type_list<>, Element>
		{
		public:
			using type = Type_list<>;
		};

		template <typename Element>
		class Erase_all<Type_list<Element>, Element>
		{
		public:
			using type = Type_list<>;
		};

		template <typename... Tail, typename Element>
		class Erase_all<Type_list<Element, Tail...>, Element>
		{
		public:
			using type = typename Erase_all<Type_list<Tail...>, Element>::type;
		};

		template <typename Head, typename... Tail, typename Element>
		class Erase_all<Type_list<Head, Tail...>, Element>
		{
		public:
			using type = Push_front_t<typename Erase_all<Type_list<Tail...>, Element>::type, Head>;
		};

		template <typename List, typename Element>
		using Erase_all_t = typename Erase_all<List, Element>::type;

		/**
		* Unique
		*/
		template <typename List>
		class Unique;

		template <>
		class Unique<Type_list<>>
		{
		public:
			using type = Type_list<>;
		};

		template <typename Head, typename... Tail>
		class Unique<Type_list<Head, Tail...>>
		{
		private:
			using L1 = typename Unique<Type_list<Tail...>>::type;
			using L2 = typename Erase<L1, Head>::type;

		public:
			using type = typename Push_front<L2, Head>::type;
		};

		template <typename List>
		using Unique_t = typename Unique<List>::type;

		/**
		* Replace
		*/
		template <typename List, typename From, typename To>
		class Replace;

		template <typename From, typename To>
		class Replace<Type_list<>, From, To>
		{
		public:
			using type = Type_list<>;
		};

		template <typename From, typename... Tail, typename To>
		class Replace<Type_list<From, Tail...>, From, To>
		{
		public:
			using type = Type_list<To, Tail...>;
		};

		template <typename Head, typename... Tail, typename From, typename To>
		class Replace<Type_list<Head, Tail...>, From, To>
		{
		public:
			using type = typename Push_front<typename Replace<Type_list<Tail...>, From, To>::type, Head>::type;
		};

		template <typename List, typename From, typename To>
		using Replace_t = typename Replace<List, From, To>::type;

		/**
		* Replace_all
		*/
		template <typename List, typename From, typename To>
		class Replace_all;

		template <typename From, typename To>
		class Replace_all<Type_list<>, From, To>
		{
		public:
			using type = Type_list<>;
		};

		template <typename From, typename... Tail, typename To>
		class Replace_all<Type_list<From, Tail...>, From, To>
		{
		public:
			using type = typename Push_front<typename Replace_all<Type_list<Tail...>, From, To>::type, To>::type;
		};

		template <typename Head, typename... Tail, typename From, typename To>
		class Replace_all<Type_list<Head, Tail...>, From, To>
		{
		public:
			using type = typename Push_front<typename Replace_all<Type_list<Tail...>, From, To>::type, Head>::type;
		};

		template <typename List, typename From, typename To>
		using Replace_all_t = typename Replace_all<List, From, To>::type;

		/**
		* Reverse
		*/
		template <typename List>
		class Reverse;

		template <>
		class Reverse<Type_list<>>
		{
		public:
			using type = Type_list<>;
		};

		template <typename Head, typename... Tail>
		class Reverse<Type_list<Head, Tail...>>
		{
		public:
			using type = Push_back_t<typename Reverse<Type_list<Tail...>>::type, Head>;
		};

		template <typename List>
		using Reverse_t = typename Reverse<List>::type;

		/**
		* Most_derived
		接受一个typelist和一个base类型，传加typelist中base的最深层派生类型(没有则返回base)
		*/
		template <typename List, typename T>
		class Most_derived;

		template <typename T>
		class Most_derived<Type_list<>, T>
		{
		public:
			using type = T;
		};

		template <typename Head, typename... Tail, typename T>
		class Most_derived<Type_list<Head, Tail...>, T>
		{
			using Candidate = typename Most_derived<Type_list<Tail...>, T>::type;

		public:
			using type = std::conditional_t<
				std::is_base_of_v<Candidate, Head>,
				Head,
				Candidate
			>;
		};

		template <typename List, typename T>
		using Most_derived_t = typename Most_derived<List, T>::type;

		/**
		* Derived_to_front
		*/
		template <typename List>
		class Derived_to_front;

		template <>
		class Derived_to_front<Type_list<>>
		{
		public:
			using type = Type_list<>;
		};

		template <typename Head, typename... Tail>
		class Derived_to_front<Type_list<Head, Tail...>>
		{
			using MD = Most_derived_t<Type_list<Tail...>, Head>;
			using L = Replace_t<Type_list<Tail...>, MD, Head>;

		public:
			using type = Push_front_t<L, MD>;
		};

		template <typename List>
		using Derived_to_front_t = typename Derived_to_front<List>::type;
	}
}

#endif // !_COLA_TYPELISTS_TYPE_LIST_HPP_

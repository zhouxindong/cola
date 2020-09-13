#pragma once
#ifndef _COLA_TYPELISTS_TUPLE_HPP_
#define _COLA_TYPELISTS_TUPLE_HPP_

#include <type_traits>
#include <iostream>

#include "type_list.hpp"

namespace cola
{
#pragma region class Tuple

	// primary
	template <typename ...Types>
	class Tuple;

	// recursive
	template <typename Head, typename ...Tail>
	class Tuple<Head, Tail...>
	{
	private:
		Head head_;
		Tuple<Tail...> tail_;

	public: // ctor
		Tuple() {}

		Tuple(Head const& head, Tuple<Tail...> const& tail)
			: head_(head), tail_(tail) {}

		Tuple(Head const& head, Tail const&... tail) // suport Tuple(17, 3.14, "Hello") ctor
			: head_(head), tail_(tail...) {}

		// the most general ctor: support move-construct and different convertabled type
		// CAUTION: this ctor can aborb any ctor call when others is you intend!
		// please to disable some when you want others can be adopted!
		template <typename VHead, typename ...VTail,
			typename = std::enable_if_t<sizeof...(VTail) == sizeof...(Tail)>>
		Tuple(VHead&& vhead, VTail&&... vtail)
			: head_(std::forward<VHead>(vhead))
			, tail_(std::forward<VTail>(vtail)...) {}

		// ctor from another tuple
		template <typename VHead, typename ...VTail,
			typename = std::enable_if_t<sizeof...(VTail) == sizeof...(Tail)>>
		Tuple(Tuple<VHead, VTail...> const& other)
			: head_(other.get_head())
			, tail_(other.get_tail()) {}
		

	public: // accessors
		Head& get_head() { return head_; }
		Head const& get_head() const { return head_; }
		Tuple<Tail...>& get_tail() { return tail_; }
		Tuple<Tail...> const& get_tail() const { return tail_; }
	};

	// basis
	template <>
	class Tuple<> {};

#pragma endregion

#pragma region class Tuple_get

	template <unsigned N>
	struct Tuple_get
	{
		template <typename Head, typename ...Tail>
		static auto apply(Tuple<Head, Tail...> const& t)
		{
			return Tuple_get<N - 1>::apply(t.get_tail());
		}
	};

	template <>
	struct Tuple_get<0>
	{
		template <typename Head, typename ...Tail>
		static Head const& apply(Tuple<Head, Tail...> const& t)
		{
			return t.get_head();
		}
	};

	template <unsigned N, typename ...Types>
	auto get(Tuple<Types...> const& t)
	{
		return Tuple_get<N>::apply(t);
	}

#pragma endregion

#pragma region make_tuple

	template <typename ...Types>
	auto make_tuple(Types&&... elems)
	{
		return Tuple<std::decay_t<Types>...>(std::forward<Types>(elems)...);
	}

#pragma endregion

#pragma region Tuple operations

	bool operator==(Tuple<> const&, Tuple<> const&)
	{
		return true;
	}

	template <
		typename Head1, typename ...Tail1,
		typename Head2, typename ...Tail2,
		typename = std::enable_if_t<sizeof...(Tail1) == sizeof...(Tail2)>>
		bool operator==(
			Tuple<Head1, Tail1...> const& lhs,
			Tuple<Head2, Tail2...> const& rhs)
	{
		return lhs.get_head() == rhs.get_head() &&
			lhs.get_tail() == rhs.get_tail();
	}

	void print_tuple(std::ostream& strm, Tuple<> const&, bool is_first = true)
	{
		strm << (is_first ? '(' : ')');
	}

	template <typename Head, typename ...Tail>
	void print_tuple(std::ostream& strm, Tuple<Head, Tail...> const& t, bool is_first = true)
	{
		strm << (is_first ? "(" : ", ");
		strm << t.get_head();
		print_tuple(strm, t.get_tail(), false);
	}

	template <typename ...Types>
	std::ostream& operator<<(std::ostream& strm, Tuple<Types...> const& t)
	{
		print_tuple(strm, t);
		return strm;
	}
#pragma endregion

#pragma region Tuple algorithm
	// Type_list algorithms: compile-time computation
	// Tuple algorithms: both compile-time and run-time computation

	namespace TL
	{
		template <typename ...Types>
		struct Is_empty<Tuple<Types...>>
		{
			static constexpr bool value = (sizeof...(Types) == 0);
		};

		template <typename Head, typename ...Tail>
		class Front<Tuple<Head, Tail...>>
		{
		public:
			using type = Head;
		};

		template <>
		class Front<Tuple<>>
		{
		public:
			using type = void;
		};

		template <typename Head, typename ...Tail>
		class Pop_front<Tuple<Head, Tail...>>
		{
		public:
			using type = Tuple<Tail...>;
		};

		template <>
		class Pop_back<Tuple<>>
		{
		public:
			using type = Tuple<>;
		};

		template <typename T>
		class Pop_back<Tuple<T>>
		{
		public:
			using type = Tuple<>;
		};

		template <typename T, typename U>
		class Pop_back<Tuple<T, U>>
		{
		public:
			using type = Tuple<T>;
		};

		template <typename Head, typename ...Tail>
		class Pop_back<Tuple<Head, Tail...>>
		{
		public:
			using type = Push_front_t<typename Pop_back<Tuple<Tail...>>::type, Head>;
		};

		template <typename ...Types, typename Element>
		class Push_front<Tuple<Types...>, Element>
		{
		public:
			using type = Tuple<Element, Types...>;
		};

		template <typename ...Types, typename Element>
		class Push_back<Tuple<Types...>, Element>
		{
		public:
			using type = Tuple<Types..., Element>;
		};

		template <>
		class Reverse<Tuple<>>
		{
		public:
			using type = Tuple<>;
		};

		template <typename Head, typename ...Tail>
		class Reverse<Tuple<Head, Tail...>>
		{
		public:
			using type = Push_back_t<typename Reverse<Tuple<Tail...>>::type, Head>;
		};

		// both compile-time and run-time computation
		template <typename ...Types, typename V>
		Push_front_t<Tuple<Types...>, V> push_front(Tuple<Types...> const& tuple, V const& value)
		{
			return Push_front_t<Tuple<Types...>, V>(value, tuple);
		}

		// basis
		template <typename V>
		Tuple<V> push_back(Tuple<> const&, V const& value)
		{
			return Tuple<V>(value);
		}

		// recursive
		template <typename Head, typename ...Tail, typename V>
		Tuple<Head, Tail..., V> push_back(Tuple<Head, Tail...> const& tuple, V const& value)
		{
			return Tuple<Head, Tail..., V>(tuple.get_head(), push_back(tuple.get_tail(), value));
		}

		template <typename ...Types>
		Pop_front_t<Tuple<Types...>> pop_front(Tuple<Types...> const& tuple)
		{
			return tuple.get_tail();
		}

		Tuple<> reverse(Tuple<> const& t)
		{
			return t;
		}

		template <typename Head, typename ...Tail>
		Reverse_t<Tuple<Head, Tail...>> reverse(Tuple<Head, Tail...> const& t)
		{
			return push_back(reverse(t.get_tail()), t.get_head());
		}

		template <typename ...Types>
		Pop_back_t<Tuple<Types...>> pop_back(Tuple<Types...> const& tuple)
		{
			return reverse(pop_front(reverse(tuple)));
		}
	}

#pragma endregion
}

#endif // !_COLA_TYPELISTS_TUPLE_HPP_

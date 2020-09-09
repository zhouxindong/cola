#include "pch.h"
#include "CppUnitTest.h"
#include <type_traits>
#include <string>
#include <typeinfo>

#include <typelist_algorithm.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace typelistsunittest
{
	template <typename T>
	struct Add_const
	{
		using type = T const;
	};

	template <typename T>
	struct Add_const<T const>
	{
		using type = T const;
	};

	template <typename T, typename U>
	class Larger_type
	{
	public:
		using type = std::conditional_t<(sizeof(T) >= sizeof(U)), T, U>;
	};

	template <typename T>
	class Size4
	{
	public:
		static constexpr bool value = (sizeof(T) == 4);
	};

	TEST_CLASS(typelistalgorithmunittest)
	{
	public:

		using empty_typelist = cola::Type_list<>;
		using integer_typelist = cola::Type_list<char, short, unsigned short,
			int, unsigned int, long long, unsigned long long>;
		using float_typelist = cola::Type_list<float, double>;
		using string_typelist = cola::Type_list<std::string>;

		TEST_METHOD(transform_test)
		{
			Assert::IsTrue(std::is_same_v<
				empty_typelist,
				cola::TL::Transform_t<empty_typelist, Add_const>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<std::string const>,
				cola::TL::Transform_t<string_typelist, Add_const>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<float const, double const>,
				cola::TL::Transform_t<float_typelist, Add_const>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<char const, short const, unsigned short const, int const, 
				unsigned int const, long long const, unsigned long long const>,
				cola::TL::Transform_t<integer_typelist, Add_const>>);
		}

		TEST_METHOD(accumulate_test)
		{
			Assert::IsTrue(std::is_same_v<
				char,
				cola::TL::Accumulate_t<empty_typelist, Larger_type, char>
			>);

			Assert::IsTrue(std::is_same_v<
				std::string,
				cola::TL::Accumulate_t<string_typelist, Larger_type, char>
			>);

			Assert::IsTrue(std::is_same_v<
				double,
				cola::TL::Accumulate_t<float_typelist, Larger_type, char>
			>);

			Assert::IsTrue(std::is_same_v<
				long long,
				cola::TL::Accumulate_t<integer_typelist, Larger_type, char>
			>);
		}

		TEST_METHOD(filter_test)
		{
			Assert::IsTrue(std::is_same_v<
				empty_typelist,
				cola::TL::Filter_t<empty_typelist, Size4>
			>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<>,
				cola::TL::Filter_t<string_typelist, Size4>
			>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<float>,
				cola::TL::Filter_t<float_typelist, Size4>
			>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<int, unsigned int>,
				cola::TL::Filter_t<integer_typelist, Size4>
			>);
		}

	};
}
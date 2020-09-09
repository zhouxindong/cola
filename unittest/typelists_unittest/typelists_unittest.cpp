#include "pch.h"
#include "CppUnitTest.h"
#include <type_traits>
#include <string>
#include <typeinfo>

#include <type_list.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace typelistsunittest
{
	class Base {};

	class Derived1 : public Base {};

	class Derived2 : public Base {};

	class Derived11 : public Derived1 {};

	TEST_CLASS(typelistsunittest)
	{
	public:

		using empty_typelist = cola::Type_list<>;
		using integer_typelist = cola::Type_list<char, short, unsigned short,
			int, unsigned int, long long, unsigned long long>;
		using float_typelist = cola::Type_list<float, double>;
		using string_typelist = cola::Type_list<std::string>;
		
		TEST_METHOD(basic_class_test)
		{
			Assert::IsTrue(std::is_class_v<cola::Type_list<int>>);
		}

		TEST_METHOD(length_test)
		{
			Assert::AreEqual(0, cola::TL::Length<empty_typelist>::value);
			Assert::AreEqual(1, cola::TL::Length<string_typelist>::value);
			Assert::AreEqual(2, cola::TL::Length<float_typelist>::value);
			Assert::AreEqual(7, cola::TL::Length<integer_typelist>::value);
		}

		TEST_METHOD(front_test)
		{
			Assert::IsTrue(std::is_same_v<float, cola::TL::Front_t<float_typelist>>);
			Assert::IsTrue(std::is_same_v<void, cola::TL::Front_t<empty_typelist>>);
			Assert::IsTrue(std::is_same_v<std::string, cola::TL::Front_t<string_typelist>>);
		}

		TEST_METHOD(pop_front_test)
		{
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<short, unsigned short,
				int, unsigned int, long long, unsigned long long>,
				cola::TL::Pop_front_t<integer_typelist>>);
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<double>, cola::TL::Pop_front_t<float_typelist>>);
			Assert::IsTrue(std::is_same_v<cola::Type_list<>, cola::TL::Pop_front_t<string_typelist>>);
		}

		TEST_METHOD(push_front_test)
		{
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<double>, cola::TL::Push_front_t<cola::Type_list<>, double>>);
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<int, std::string>, cola::TL::Push_front_t<string_typelist, int>>);
		}

		TEST_METHOD(n_element_test)
		{
			Assert::IsTrue(std::is_same_v<std::string, cola::TL::N_element_t<string_typelist, 0>>);
			Assert::IsTrue(std::is_same_v<double,
				cola::TL::N_element_t<float_typelist, 1>>);
			Assert::IsTrue(std::is_same_v<void,
				cola::TL::N_element_t<float_typelist, 2>>); // out of range
			Assert::IsTrue(std::is_same_v<long long,
				cola::TL::N_element_t<integer_typelist, 5>>);
		}

		TEST_METHOD(index_of_test)
		{
			Assert::AreEqual(-1, cola::TL::Index_of<empty_typelist, int>::value);
			Assert::AreEqual(0, cola::TL::Index_of<string_typelist, std::string>::value);
			Assert::AreEqual(-1, cola::TL::Index_of<string_typelist, int>::value);
			Assert::AreEqual(1, cola::TL::Index_of<float_typelist, double>::value);
			Assert::AreEqual(4, cola::TL::Index_of<integer_typelist, unsigned int>::value);

			Assert::AreEqual(-1, cola::TL::Index_of_v<empty_typelist, int>);
			Assert::AreEqual(0, cola::TL::Index_of_v<string_typelist, std::string>);
			Assert::AreEqual(-1, cola::TL::Index_of_v<string_typelist, int>);
			Assert::AreEqual(1, cola::TL::Index_of_v<float_typelist, double>);
			Assert::AreEqual(4, cola::TL::Index_of_v<integer_typelist, unsigned int>);
		}

		TEST_METHOD(largest_type_test)
		{
			Assert::IsTrue(std::is_same_v<char, cola::TL::Largest_type_t<empty_typelist>>);
			Assert::IsTrue(std::is_same_v<std::string, cola::TL::Largest_type_t<string_typelist>>);
			Assert::IsTrue(std::is_same_v<double, cola::TL::Largest_type_t<float_typelist>>);
			Assert::IsTrue(std::is_same_v<long long, cola::TL::Largest_type_t<integer_typelist>>);
		}

		TEST_METHOD(is_empty_test)
		{
			Assert::IsTrue(cola::TL::Is_empty_v<empty_typelist>);
			Assert::IsFalse(cola::TL::Is_empty_v<integer_typelist>);
			Assert::IsFalse(cola::TL::Is_empty_v<float_typelist>);
			Assert::IsFalse(cola::TL::Is_empty_v<string_typelist>);
		}

		TEST_METHOD(push_back_test)
		{
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<char>,
				cola::TL::Push_back_t<empty_typelist, char>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<std::string, int>,
				cola::TL::Push_back_t<string_typelist, int>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<float, double, short>,
				cola::TL::Push_back_t<float_typelist, short>>);
		}

		TEST_METHOD(back_test)
		{
			Assert::IsTrue(std::is_same_v<void, cola::TL::Back_t<empty_typelist>>);
			Assert::IsTrue(std::is_same_v<std::string, cola::TL::Back_t<string_typelist>>);
			Assert::IsTrue(std::is_same_v<double, cola::TL::Back_t<float_typelist>>);
			Assert::IsTrue(std::is_same_v<unsigned long long, cola::TL::Back_t<integer_typelist>>);
		}

		TEST_METHOD(pop_back_test)
		{
			Assert::IsTrue(std::is_same_v<cola::Type_list<>, cola::TL::Pop_back_t<empty_typelist>>);
			Assert::IsTrue(std::is_same_v<cola::Type_list<>, cola::TL::Pop_back_t<string_typelist>>);
			Assert::IsTrue(std::is_same_v<cola::Type_list<float>, cola::TL::Pop_back_t<float_typelist>>);
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<char, short>,
				cola::TL::Pop_back_t<cola::Type_list<char, short, unsigned short>>>);
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<char, short, unsigned short, int, unsigned int, long long>,
				cola::TL::Pop_back_t<integer_typelist>>);
		}

		TEST_METHOD(erase_test)
		{
			Assert::IsTrue(std::is_same_v<empty_typelist, cola::TL::Erase_t<empty_typelist, int>>);
			Assert::IsTrue(std::is_same_v<empty_typelist, cola::TL::Erase_t<string_typelist, std::string>>);
			Assert::IsTrue(std::is_same_v<string_typelist, cola::TL::Erase_t<string_typelist, int>>);
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<float>,
				cola::TL::Erase_t<float_typelist, double>
			>);
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<double>,
				cola::TL::Erase_t<float_typelist, float>
			>);
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<char, short, int, unsigned int, long long, unsigned long long>,
				cola::TL::Erase_t<integer_typelist, unsigned short>
			>);
		}

		TEST_METHOD(erase_all_test)
		{
			Assert::IsTrue(std::is_same_v<empty_typelist, cola::TL::Erase_all_t<empty_typelist, char>>);
			Assert::IsTrue(std::is_same_v<empty_typelist, cola::TL::Erase_all_t<string_typelist, std::string>>);
			Assert::IsTrue(std::is_same_v<string_typelist, cola::TL::Erase_all_t<string_typelist, int>>);
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<float>,
				cola::TL::Erase_all_t<float_typelist, double>
			>);
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<double>,
				cola::TL::Erase_all_t<float_typelist, float>
			>);
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<char, short, int, unsigned int, long long, unsigned long long>,
				cola::TL::Erase_all_t<integer_typelist, unsigned short>
			>);
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<>,
				cola::TL::Erase_all_t<cola::Type_list<int, int>, int>
			>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<int, short, double>,
				cola::TL::Erase_all_t<cola::Type_list<char, int, short, char, double>, char>
			>);
		}

		TEST_METHOD(unique_test)
		{
			Assert::IsTrue(std::is_same_v<
				cola::Type_list<>,
				cola::TL::Unique_t<empty_typelist>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<int>,
				cola::TL::Unique_t<cola::Type_list<int>>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<int>,
				cola::TL::Unique_t<cola::Type_list<int, int>>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<int>,
				cola::TL::Unique_t<cola::Type_list<int, int, int>>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<int, double, float>,
				cola::TL::Unique_t<cola::Type_list<int, double, float>>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<int, std::string, double>,
				cola::TL::Unique_t<cola::Type_list<int, std::string, int, double, double, int>>>);
		}

		TEST_METHOD(replace_test)
		{
			Assert::IsTrue(std::is_same_v<
				empty_typelist,
				cola::TL::Replace_t<empty_typelist, int, double>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<int>,
				cola::TL::Replace_t<string_typelist, std::string, int>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<double, double>,
				cola::TL::Replace_t<float_typelist, float, double>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<char, short, std::string, int, unsigned int, long long, unsigned long long>,
				cola::TL::Replace_t<integer_typelist, unsigned short, std::string>>);
		}

		TEST_METHOD(replace_all_test)
		{
			Assert::IsTrue(std::is_same_v<
				empty_typelist,
				cola::TL::Replace_all_t<empty_typelist, int, double>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<int>,
				cola::TL::Replace_all_t<string_typelist, std::string, int>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<double, double>,
				cola::TL::Replace_all_t<float_typelist, float, double>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<char, short, std::string, int, unsigned int, long long, unsigned long long>,
				cola::TL::Replace_all_t<integer_typelist, unsigned short, std::string>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<float, std::string, float, double, char, float>,
				cola::TL::Replace_all_t<cola::Type_list<float, std::string, int, double, char, int>, int, float>>);
		}

		TEST_METHOD(reverse_test)
		{
			Assert::IsTrue(std::is_same_v<
				empty_typelist,
				cola::TL::Reverse_t<empty_typelist>>);

			Assert::IsTrue(std::is_same_v<
				string_typelist,
				cola::TL::Reverse_t<string_typelist>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<double, float>,
				cola::TL::Reverse_t<float_typelist>>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<unsigned long long, long long, unsigned, int, unsigned short, short, char>,
				cola::TL::Reverse_t<integer_typelist>>);
		}

		TEST_METHOD(most_derived_test)
		{
			Assert::IsTrue(std::is_same_v<
				Base,
				cola::TL::Most_derived_t<empty_typelist, Base>
			>);

			Assert::IsTrue(std::is_same_v<
				Base,
				cola::TL::Most_derived_t<integer_typelist, Base>
			>);

			Assert::IsTrue(std::is_same_v<
				Base,
				cola::TL::Most_derived_t<cola::Type_list<double, std::string, Base, int>, Base>
			>);

			Assert::IsTrue(std::is_same_v<
				Derived2,
				cola::TL::Most_derived_t<cola::Type_list<int, Base, Derived1, Derived2>, Base> 
			>);

			Assert::IsTrue(std::is_same_v<
				Derived11,
				cola::TL::Most_derived_t<cola::Type_list<Derived11, Derived1, int>, Base>
			>);
		}

		TEST_METHOD(derived_to_front_test)
		{
			Assert::IsTrue(std::is_same_v<
				empty_typelist,
				cola::TL::Derived_to_front_t<empty_typelist>
			>);

			Assert::IsTrue(std::is_same_v<
				string_typelist,
				cola::TL::Derived_to_front_t<string_typelist>
			>);

			Assert::IsTrue(std::is_same_v<
				float_typelist,
				cola::TL::Derived_to_front_t<float_typelist>
			>);

			Assert::IsTrue(std::is_same_v<
				integer_typelist,
				cola::TL::Derived_to_front_t<integer_typelist>
			>);

			Assert::IsTrue(std::is_same_v<
				cola::Type_list<Derived11, int, Base, Derived1>,
				cola::TL::Derived_to_front_t<cola::Type_list<Base, int, Derived11, Derived1>>
			>);
		}
	};
}

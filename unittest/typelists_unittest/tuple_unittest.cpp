#include "pch.h"
#include "CppUnitTest.h"
#include <type_traits>
#include <string>
#include <typeinfo>

#include <tuple.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace typelistsunittest
{
	TEST_CLASS(tupleunittest)
	{
	public:

		TEST_METHOD(tuple_ctor_test)
		{
			cola::Tuple<int, double, std::string> t(17, 3.14, "hello world");
			Assert::AreEqual(17, cola::get<0>(t));
			Assert::AreEqual(3.14, cola::get<1>(t));
			Assert::IsTrue(cola::get<2>(t) == std::string("hello world"));

			cola::Tuple<long int, long double, std::string> t2(t);
			Assert::AreEqual((long int)17, cola::get<0>(t2));
			Assert::IsTrue((long double)3.14 == cola::get<1>(t2));
			Assert::IsTrue(cola::get<2>(t2) == std::string("hello world"));
		}

		TEST_METHOD(make_tuple_test)
		{
			auto t = cola::make_tuple(17, 3.14, "hello world");
			Assert::AreEqual(17, cola::get<0>(t));
			Assert::AreEqual(3.14, cola::get<1>(t));
			Assert::IsTrue(cola::get<2>(t) == std::string("hello world"));

			cola::Tuple<long int, long double, std::string> t2(t);
			Assert::AreEqual((long int)17, cola::get<0>(t2));
			Assert::IsTrue((long double)3.14 == cola::get<1>(t2));
			Assert::IsTrue(cola::get<2>(t2) == std::string("hello world"));
		}
	};
}

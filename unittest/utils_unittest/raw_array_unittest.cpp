#include "pch.h"
#include "CppUnitTest.h"
#include <raw_array.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace utilsunittest
{
	TEST_CLASS(raw_array_unittest)
	{
	public:
		int a1[1]{ 1 };
		int b1[1]{ 1 };
		int c1[1]{ 0 };
		char d1[1]{ 1 };

		int a9[9]{ 1,2,3,4,5,6,7,8,9 };
		int b9[9]{ 1,2,3,4,5,6,7,8,9 };
		char c9[9]{ 1,2,3,4,5,6,7,8,9 };
		TEST_METHOD(equals_test)
		{
			int a[1]{ 1 };
			int b[1]{ 1 };
			int c[1]{ 0 };
			char d[1]{ 1 };

			Assert::IsTrue(cola::equals(a1, b1));
			Assert::IsFalse(cola::equals(a1, c1));
			Assert::IsTrue(cola::equals(a1, d1));

			Assert::IsFalse(cola::equals(a1, a9));
			Assert::IsTrue(cola::equals(a9, b9));
			Assert::IsTrue(cola::equals(a9, c9));
		}
	};
}

#include "pch.h"
#include "CppUnitTest.h"

#include <vector>
#include <map>
#include <unordered_map>
#include <string>

#include <container.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace utilsunittest
{
	TEST_CLASS(container_unittest)
	{
	public:
		TEST_METHOD(erase_remove_test)
		{
			std::vector<int> v{ 1,2,3,4,5,6,7,8,9 };
			std::vector<int> vv{ 1,2,3,4,5,6,7,8,9 };
			std::vector<int> v2{ 1,3,5,7,9 };
			std::vector<int> v3{ 1,2,3,4 };

			cola::erase_remove(v, [](auto i) {
				return i % 2 == 0;
				});
			
			cola::erase_remove(vv, [](auto& i) {
				return i > 4;
				});

			Assert::IsTrue(v == v2);
			Assert::IsTrue(vv == v3);
		}

		TEST_METHOD(replace_key_test)
		{
			std::map<int, std::string> m{ {1, "one"},{2,"two"},{3,"three"} };
			std::map<int, std::string> m2{ {1, "one"}, {22, "two"}, {3, "three"} };

			cola::replace_key(m, 2, 22);
			Assert::IsTrue(m == m2);
		}
	};
}

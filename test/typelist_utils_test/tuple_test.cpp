
#include "tuple.hpp"

int main()
{
	std::cout << cola::make_tuple(1, 2.5, std::string("hello")) << "\n";

	cola::Tuple<int, double, std::string> t1(17, 3.14, "hello world");
	using T2 = cola::TL::Pop_front_t<cola::TL::Push_back_t<decltype(t1), bool>>;
	T2 t2(cola::get<1>(t1), cola::get<2>(t1), true);
	std::cout << t2 << "\n";

	auto t3 = cola::TL::pop_front(cola::TL::push_back(t1, true));
	std::cout << std::boolalpha << t3 << "\n";

	auto t4 = cola::TL::reverse(cola::make_tuple(1, 2.5, std::string("hello")));
	std::cout << t4 << "\n";

	auto t5 = cola::TL::pop_back(t4);
	std::cout << t5 << "\n";
}
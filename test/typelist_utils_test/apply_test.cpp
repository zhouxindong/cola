// typelist_utils_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "typelist_utils.hpp"

template <typename T>
struct Holder
{
    T value_;
};

int main()
{
    cola::TL::Apply<cola::Type_list<int, double, std::string>, Holder> info;

    int& ri = static_cast<Holder<int>&>(info).value_;
    double& rd = static_cast<Holder<double>&>(info).value_;
    std::string& rs = static_cast<Holder<std::string>&>(info).value_;

    cola::TL::field<int>(info).value_ = 323;
    cola::TL::field<double>(info).value_ = 99.323;
    cola::TL::field<std::string>(info).value_ = "hello, world";

    std::cout << ri << "\n";
    std::cout << rd << "\n";
    std::cout << rs << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include "a.hpp"

A::A(void)
{
    std::cout << "A default constructor" << std::endl;
}

A::A(const A &src)
{
    std::cout << "A copy of constructor" << std::endl;
    *this = src;
}

A::~A(void)
{}

A   &A::operator=(A const &other)
{
    void(other);
    std::cout << "A Assignment operator" << std::endl;
    return *this;
}
#include <iostream>
#include <vector>
#include "easyfind.hpp"

int main(void)
{
    std::vector<int>            vec;
    std::vector<int>::iterator  iter;

    for(int i = 1; i < 59; i += 2)
        vec.push_back(i);
    try
    {
        iter = easyfind(vec, 43);
        std::cout << "iterator: " << *iter << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        iter = easyfind(vec, 42);
        std::cout << "iterator: " << *iter << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return(0);
}
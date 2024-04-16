#include "Bureaucrat.hpp"

int main(void)
{
    try
    {
        Bureaucrat b1 = Bureaucrat("b1", 1);
        std::cout << b1 << std::endl;
        b1.decrementGrade(1);
        std::cout << b1 << std::endl;
        b1.incrementGrade(1);
        std::cout << b1 << std::endl;
        b1.incrementGrade(1);
        std::cout << b1 << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << std::endl;
    
    try
    {
        Bureaucrat b2 = Bureaucrat("b2", 150);
        std::cout << b2 << std::endl;
        b2.incrementGrade(1);
        std::cout << b2 << std::endl;
        b2.decrementGrade(3);
        std::cout << b2 << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << std::endl;
    
    try
    {
        Bureaucrat b3 = Bureaucrat("b3", 0);
        std::cout << b3 << std::endl;
        b3.decrementGrade(1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << std::endl;

    try
    {
        Bureaucrat b4 = Bureaucrat("b4", 151);
        std::cout << b4 << std::endl;
        b4.incrementGrade(1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return (0);
}
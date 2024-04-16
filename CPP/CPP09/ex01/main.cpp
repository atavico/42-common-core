#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./RPN \"expression\"" << std::endl;
        return (1);
    }
    RPN rpn(argv[1]);
    if (!rpn.evaluate())
        return(1);
    return (0);
}
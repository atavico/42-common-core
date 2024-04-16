#include "Brain.hpp"

Brain::Brain(void)
{
    std::cout << "Default Brain" << std::endl;
}

Brain::Brain(const Brain &src)
{
    std::cout << "Copy Brain" << std::endl;
    int i = -1;
    while (++i < Brain::n_idea)
        this->idea[i] = src.getIdea(i);
}

Brain::~Brain(void)
{
    std::cout << "Default destructor" << std::endl;
}

Brain &Brain::operator=(const Brain &other)
{
    int i;
    std::cout << "Assignment opereator" << std::endl;
    if(this == &other)
        return(*this);
    i = -1;
    while(++i < Brain::n_idea)
        this->idea[i] = other.getIdea(i);
    return (*this);
}

std::string Brain::getIdea(int i) const
{
    return(this->idea[i]);
}

void    Brain::setIdea(std::string s, int i)
{
    Brain::idea[i] = s;
}
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include "Span.hpp"

Span::Span(void): _size(0)
{
    std::cout << "default constructor" << std::endl;
}

Span::Span(unsigned int size): _size(size), _storage(0)
{
    std::cout << "Standard constructor" << std::endl;
}

Span::Span(Span const &src)
{
    *this = src;
    std::cout << "Copy constructor" << std::endl;
}

Span::~Span(void)
{
    std::cout << "default destructor" << std::endl;
}

Span    &Span::operator=(Span const &other)
{
    std::cout << "Assignment operator" << std::endl;
    if(this == &other)
        return (*this);
    this->_size = other._size;
    this->_storage = other._storage;
    return(*this);
}

void    Span::addNumber(int number)
{
    if(_storage.size() == _size)
        throw std::out_of_range("Cannot add numbers");
    _storage.push_back(number);
}

int Span::shortestSpan(void) const
{
    std::vector<int>    tmp=_storage;
    std::vector<int>::iterator it;

    if (_storage.size() <= 1)
        throw std::logic_error("Not enough numbers stored");
    sort(tmp.begin(), tmp.end());
    return(*(tmp.end() -1) - *tmp.begin());
}

int Span::longestSpan(void) const
{
    std::vector<int>        tmp=_storage;

    if(_storage.size() <= 1)
        throw std::logic_error("Not enough numbers stored");
    sort(tmp.begin(), tmp.end());
    return(*(tmp.end()-1)-*tmp.begin());
}

unsigned int    Span::size(void)const
{
    return(_storage.size());
}

unsigned int Span::maxSize(void)const
{
    return(_size);
}

unsigned int Span::spaceLeft(void) const
{
    return(maxSize() - size());
}

void Span::randomFill(void)
{
    unsigned int    numbersToFill = this->spaceLeft();

    std::cout << "RANDOM FILL" << std::endl;
    for (unsigned int i = 0; i < numbersToFill; i++)
        this->addNumber(rand() % (this->maxSize() * 10));
}

void    Span::addByIteratorRange(std::vector<int>::iterator begin, 
                                std::vector<int>::iterator end)
{
    std::vector<int>        tmp(begin, end);

    std::cout << "add by iterator" << std::endl;
    if (tmp.size() > this->spaceLeft())
        throw std::out_of_range("Cannot add numbers");
    copy(tmp.begin(), tmp.end(), std::back_inserter(this->_storage));
}

std::ostream	&operator<<(std::ostream &ostr, Span const &instance)
{
	int	shortest = instance.shortestSpan();
	int	longest = instance.longestSpan();

	ostr << "Span of max size " << instance.maxSize() << " contains "
		<< instance.size() << " numbers, shortest span is "
		<< shortest << " and longest is " << longest;
	return ostr;
}
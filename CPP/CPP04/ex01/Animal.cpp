/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:50:55 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 15:24:10 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void):type("")
{
    std::cout << "Default animal\n";
}

Animal::Animal(const Animal &src)
{
    std::cout << "Copy animal";
    this->setType(src.getType());
}

Animal::~Animal(void)
{
    std::cout << "destructor Animal\n";
}

Animal &Animal::operator=(const Animal &other)
{
    std::cout << "Assignment operator!\n";
    this->type = other.getType();
    return *this;
}

void    Animal::makeSound(void) const
{
    std::cout << "No animal type match" << std::endl;
}

const std::string   Animal::getType(void) const
{
    return (this->type);
}

void    Animal::setType(std::string type)
{
    this->type = type;
}

std::ostream& operator<<(std::ostream& os, Animal const & s)
{
    os << s.getType() << std::endl;
    return (os);
}
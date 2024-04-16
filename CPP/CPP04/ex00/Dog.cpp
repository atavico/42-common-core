/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:28:06 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 15:06:11 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void)
{
    this->setType("Dog");
    std::cout << "Default dog\n";           
}

Dog::Dog(const Dog &src) : Animal()
{
    std::cout << "Copy dog\n";
    this->setType(src.getType());
}

Dog::~Dog(void)
{
    std::cout << "destructor dog\n";
}

void    Dog::makeSound(void) const
{
    std::cout << "*wouffff\n";
}

std::ostream& operator<<(std::ostream& os, Dog const & s)
{
    os << s.getType() << std::endl;
    return(os);
}

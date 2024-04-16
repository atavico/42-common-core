/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:04:02 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 14:31:52 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : type("")
{
    std::cout << "Default WrongAnimal\n";
}

WrongAnimal::WrongAnimal(const WrongAnimal &src)
{
    std::cout << "Copy WrongAnimal\n";
    *this = src;
}

WrongAnimal::~WrongAnimal(void)
{
    std::cout << "destructor WrongAnimal\n";
}

WrongAnimal &WrongAnimal::operator=(WrongAnimal const &other)
{
    std::cout << "Assignment operator\n";
    this->type = other.getType();
    return *this;
}

void    WrongAnimal::makeSound(void) const
{
    if (this->getType() == "")
        std::cout << "WrongAnimal sound\n";
    else if (this->getType() == "WrongCat")
        std::cout << "WrongCat sound\n";
}

const std::string &WrongAnimal::getType(void) const
{
    return (this->type);
}
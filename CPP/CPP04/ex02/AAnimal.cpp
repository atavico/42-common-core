/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:02:53 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 15:17:03 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal(void)
{
    this->setType("No type");
    std::cout << "Default animal called\n";
}

AAnimal::AAnimal(AAnimal const &src)
{
    std::cout << "Copy Animal called\n";
    this->setType(src.getType());
}

AAnimal::AAnimal(std::string &type): type(type)
{
    std::cout << "animal with this type " << this->getType() << "has been called" << std::endl;
}

AAnimal::~AAnimal(void)
{
    std::cout << "AAnimal destructor called\n";
}

AAnimal &AAnimal::operator=(AAnimal const &other)
{
    std::cout << "Assignment operator called\n";
    if (this == &other)
        return(*this);
    this->setType(other.getType());
    return (*this);
}

const std::string AAnimal::getType(void) const
{
    return (this->type);
}

void    AAnimal::setType(std::string type)
{
    this->type = type;
}

// void    AAnimal::makeSound(void) const
// {
//     if(!this->getType().compare("Cat"))
//         std::cout << "Meoww" << std::endl;
//     else if(!this->getType().compare("Dog"))
//         std::cout << "Woooooffff" << std::endl;
//     else
//         std::cout << "No animal matching" << std::endl;
// }
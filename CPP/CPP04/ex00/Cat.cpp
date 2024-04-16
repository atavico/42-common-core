/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:20:16 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 15:06:49 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void)
{
    this->type = "Cat";
    std::cout << "Default cat\n";
}

Cat::Cat(Cat const &src) : Animal()
{
    std::cout << "Copy cat\n";
    this->setType(src.getType());
}

Cat::~Cat(void)
{
    std::cout << "destructor cat\n";
}

void Cat::makeSound(void) const
{
    std::cout << "*meow noises *\n";
}

std::ostream&   operator<<(std::ostream& os, Cat const &s)
{
    os << s.getType() << std::endl;
    return(os);
}

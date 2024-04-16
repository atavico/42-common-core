/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:12:48 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 14:32:45 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(void): WrongAnimal()
{
    this->type = "WrongCat";
    std::cout << "Default WrongCat\n";
}

WrongCat::WrongCat(const WrongCat &src)
{
    std::cout << "Copy Wrongcat\n";
    *this = src;
}

WrongCat::~WrongCat(void)
{
    std::cout << "Destructor WrongCat\n";
}

void WrongCat::makeSound(void) const
{
    std::cout << "*wrongcat soundddd\n";
}

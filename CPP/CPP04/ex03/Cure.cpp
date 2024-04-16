/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:21:03 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 18:30:05 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure(void) : _type("cure")
{
    std::cout << "Cure constructor" << std::endl;
}

Cure::Cure(Cure const & ref) : _type(ref.getType())
{
    std::cout << this->_type << "constructor from copy" << std::endl;
}

Cure::~Cure(void)
{
    std::cout << "Cure destructor" << std::endl;
}

Cure    &Cure::operator=(Cure const &other)
{
    std::cout << "Assigned from " << other.getType() << std::endl;
    return (*this);
}

std::string const   &Cure::getType(void) const
{
    return(this->_type);
}

void    Cure::use(ICharacter& target)
{
    std::cout << "Cast cure at " << target.getName() << std::endl;
}

Cure *Cure::clone(void) const
{
    Cure *ret = new Cure;
    return(ret);
}
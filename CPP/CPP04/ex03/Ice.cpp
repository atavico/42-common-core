/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:47:00 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 15:22:01 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice(void) : _type("ice")
{
    std::cout << "Ice constructor" << std::endl;
}

Ice::Ice(const Ice &ref) : _type(ref.getType())
{
    std::cout << this->_type << "constructor from copy" << std::endl;
}

Ice::~Ice(void)
{
    std::cout << "Ice destructor" << std::endl;
}

Ice &Ice::operator=(Ice const &other)
{
   std::cout << "Assigned from " << other.getType() << std::endl;
   return(*this);
}

std::string const &Ice::getType(void) const
{
    return(this->_type);
}

void    Ice::use(ICharacter& target)
{
    std::cout << "Shoots an ice bolt at " << target.getName() << std::endl;
}

Ice *Ice::clone(void) const
{
    Ice * ret = new Ice;
    return(ret);
}
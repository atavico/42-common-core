/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:23:41 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 16:36:50 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(void)
{
    std::cout << "Abstract Materia has been created" << std::endl;
    
}

AMateria::AMateria(std::string const &type): type(type)
{
    std::cout << "AMateria " << this->getType() << "has been created" << std::endl;
}

AMateria::AMateria(AMateria const &ref): type(ref.type)
{
    std::cout << "AMateria clone" << std::endl;
}

AMateria::~AMateria(void)
{
    std::cout << "AMateria destructor\n";
}

std::string const & AMateria::getType(void) const
{
    return(this->type);
}

void    AMateria::use(ICharacter& target)
{
    if(type == "cure")
        std::cout << "*Cure " << target.getName() << std::endl;
    if(type == "ice")
        std::cout << "*Ice: " << target.getName() << std::endl;
}
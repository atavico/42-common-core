/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:21:56 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 15:34:25 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource(void)
{
    for (int i = 0; i < 4; i++)
    {
        this->_inventory[i] = 0;
    }
    std::cout << "MateriaSource Constructor" << std::endl;
}

MateriaSource::MateriaSource(MateriaSource const &src)
{
    for (int i = 0; i < 4; i++)
    {
        (this->_inventory)[i] = (src._inventory[i])->clone();
    }
    std::cout << "MateriaSource Copy Constructor" << std::endl;
}

MateriaSource::~MateriaSource(void)
{
    for (int i = 0; i < 4; i++)
    {
        if (this->_inventory[i] != NULL)
            delete this->_inventory[i];
    }
    std::cout << "MateriaSource Destructor" << std::endl;
}

MateriaSource &MateriaSource::operator=(MateriaSource const & other)
{
    for (int i = 0; i < 4; i++)
    {
        if (this->_inventory[i])
            delete this->_inventory[i];
        if (other._inventory[i])
            this->_inventory[i] = (other._inventory[i])->clone();
    }
    return (*this);
}

void MateriaSource::learnMateria(AMateria* mat)
{
    int i = 0;
    while(_inventory[i] != 0 && i < 4)
        i++;
    if (i >= 4)
    {
        std::cout << "Can't learn more than 4 Materia" << std::endl;
        return;
    }
    this->_inventory[i] = mat;
    std::cout << "Materia " << mat->getType() << " learned" << std::endl;
}

AMateria *MateriaSource::createMateria(std::string const & type)
{
    int i = 0;
    while(this->_inventory[i] && ((this->_inventory[i])->getType() != type) && i < 4)
        i++;
    if (i >= 4 && (!this->_inventory[i]))
    {
        std::cout << "Materia doesn't exist" << std::endl;
        return (NULL);
    }
    std::cout << "Materia " << type << " craeted" << std::endl;
    return((this->_inventory[i])->clone());
}
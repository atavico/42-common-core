/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:42:53 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/19 12:47:19 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(std::string const &name): _name(name)
{
    for (int i = 0; i < 4; i++)
        (this->_slot)[i] = 0;
    for (int i = 0; i < 10; i++)
        (this->_drop)[i] = 0;
}

Character::Character(const Character & ref): _name(ref.getName() + "_copy")
{
    for(int i = 0; i < 4; i++)
    {
        if(ref._slot[i])
            this->_slot[i] = (ref._slot[i])->clone();
    }
    std::cout << "character named " << _name << "was created from copy of " << ref._name << std::endl; 
}

Character::~Character(void)
{
    std::cout << "Deleting Character " << _name << "and freeing Materia" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        if (this->_slot[i])
            delete(this->_slot[i]);
    }
    for (int i = 0; i < 10; i++)
    {
        if(this->_drop[i])
            delete(this->_drop[i]);
    }
}

Character   &Character::operator=(Character const & src)
{
    for(int i = 0; i < 4; i++)
    {
        if (this->_slot[i])
            delete(this->_slot[i]);
        if(src._slot[i])
            this->_slot[i] = (src._slot[i])->clone();
    }
    std::cout << "Assignment Operator" << std::endl;
    return (*this);
}

std::string const &Character::getName(void) const
{
    return(this->_name);
}

void    Character::equip(AMateria* m)
{
    int i = 0;
    if(!m)
        return;
    while((this->_slot[i] != 0 && i < 4))
        i++;
    if (i >= 4)
    {
        std::cout << this->_name << "can't drop more than 4 Materia" << std::endl;
        return;
    }
    (this->_slot)[i] = m;
    std::cout << "Couldn't equip the Materia, try to unequip some slot before" << std::endl;
}

void Character::unequip(int idx)
{
    if(idx >= 0 && idx < 4)
    {
        if(!this->_slot[idx])
            std::cout << "Couldn't unequip Materia, void slot" << std::endl;
        if(this->_slot[idx])
        {
            int i = 0;
            while(_drop[i] != 0)
                i++;
            if (i == 10)
            {
                std::cout << "Can't drop another Materia, the floor is full" << std::endl;
                return;
            }
            _drop[i] = _slot[idx];
            _slot[idx] = NULL;
            std::cout << _drop[i]->getType() << " unequipped at slot " << idx << std::endl;
        }
        else
            std::cout << "I  don't have that slot" << std::endl;
    }
}

void    Character::use(int idx, ICharacter& target)
{
    if (idx >= 0 && idx < 4)
	{
		if ((this->_slot)[idx] != NULL)
		{
			(this->_slot)[idx]->use(target);
		} else {
			std::cout << "There's no Materia in that slot" << std::endl;
		}
	}
}
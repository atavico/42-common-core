/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:58:27 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/04 16:11:17 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void): ClapTrap()
{
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    this->_initialHitpoints = this->_hitPoints;
    std::cout << "Default ScavTrap was built!\n";
}

ScavTrap::ScavTrap(std::string name): ClapTrap(name)
{
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    this->_initialHitpoints = this->_hitPoints;
    std::cout << "ScavTrap" << this->_name << "was built!\n";
}

ScavTrap::ScavTrap(const ScavTrap &src)
{
    *this = src;
    std::cout << "ScavTrap was copied!\n";
}

ScavTrap::~ScavTrap(void) 
{
    std::cout << "ScavTrap" << this->_name << "was destryed!\n";
}


ScavTrap &ScavTrap::operator=(const ScavTrap &other)
{
    std::cout << "Assignment operator\n";
    std::cout << other << std::endl;
    return *this;
}

void	ScavTrap::guardGate(void) const
{
	std::cout << "ScavTrap " << _name << " is keeping SECURE the gate\n";
}

void	ScavTrap::attack(std::string const & target)
{
	if (this->_energyPoints <= 0)
	{
		std::cout << "ScavTrap " << this->_name << " need a recharge\n";
		return ;
	}
	this->_energyPoints -= 1;
	std::cout << "ScavTrap " << this->_name << " attack " << target
		<< " causing " << this->_attackDamage << " points of damage!\n";
}
 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:59:56 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/01 16:21:20 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(const std::string name): _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    this->_initialHitpoints = this->_hitPoints;
    std::cout << "Claptrap" << _name << "was built\n";
}
ClapTrap::ClapTrap(const ClapTrap &src)
{
    std::cout << "ClapTrap was copied\n";
    *this = src;
}

ClapTrap::ClapTrap(void): _name(""), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    this->_initialHitpoints = this->_hitPoints;
    std::cout << "Default ClapTrap was built\n";
}

ClapTrap::~ClapTrap(void) 
{
    std::cout << "ClapTrap" << _name << "was destroyed\n";
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
    std::cout << "Assignment operator\n";
    std::cout << other << std::endl;
    return *this;
}

const std::string   &ClapTrap::getName(void) const
{
    return this->_name;
}

void ClapTrap::attack(const std::string &target)
{
    if (this->_attackDamage <= 0)
    {
        std::cout << "ClapTrap" << _name << "need a recharge\n";
        return;
    }
    this->_energyPoints--;
    std::cout << this->_name << "attack cause" << this->_attackDamage << "points of damage!\n";
}

void ClapTrap::takeDamage(unsigned int ammount)
{
    this->_hitPoints -= ammount;
    std::cout << this->_name << "took" << ammount << "points of damage!\n";
}

void ClapTrap::beRepaired(unsigned int ammount)
{
    if (this->_energyPoints <= 0)
    {
        std::cout << this->_name << "need a recharge!\n";
        return;
    }
    this->_energyPoints--;
    this->_hitPoints += ammount;
    if (this->_hitPoints > this->_initialHitpoints)
	{
		this->_hitPoints = this->_initialHitpoints;
		std::cout << "ClapTrap " << _name << " max healed\n";
	}
	std::cout << "ClapTrap " << _name << " repaired itself\n";
}

std::ostream &operator<<(std::ostream &ostr, ClapTrap const &instance)
{
    ostr << "ClapTrap" << instance.getName();
    return ostr;
}


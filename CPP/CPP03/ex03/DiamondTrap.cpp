/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:13:02 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/04 16:36:02 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(const std::string &name)
{
    ClapTrap::_name = name + "_clap_name";
    this->_name = name;
    this->_hitPoints = FragTrap::_hitPoints;
    this->_energyPoints = ScavTrap::_energyPoints;
    this->_attackDamage = FragTrap::_attackDamage;
    std::cout << "DiamondTrap" << _name << "was built\n";
}

DiamondTrap::DiamondTrap(void)
{
    ClapTrap::_name = "Default_clap_name";
    this->_name = "Default";
    this->_hitPoints = FragTrap::_hitPoints;
    this->_energyPoints = ScavTrap::_energyPoints;
    this->_attackDamage = FragTrap::_attackDamage;
    std::cout << "Default DiamondTrap was built\n";
}

DiamondTrap::~DiamondTrap(void)
{
    std::cout << "DiamondTrap " << _name << "was destroyed\n";
}

DiamondTrap &DiamondTrap::operator=(DiamondTrap const &other)
{
    std::cout << "Assignement operator\n";
    std::cout << other << std::endl;
    return *this;
}

void    DiamondTrap::whoAmI(void) const
{
    std::cout << "Who am I, " << this->_name << " or " << ClapTrap::_name << " ?\n";
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:40:45 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/04 14:59:08 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name): ClapTrap(name)
{
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    std::cout << "Constructor called\n";
}

FragTrap::FragTrap(void): ClapTrap()
{
    this->_hitPoints = 100;
    this->_initialHitpoints = this->_hitPoints;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    std::cout << "FragTrap default constructor called!\n";
}

FragTrap::FragTrap(const FragTrap &src)
{
    *this = src;
    std::cout << "Copy constructor called!\n";
}

FragTrap::~FragTrap(void)
{
    std::cout << "FragTrap " << _name << "was destroy!\n";
}

FragTrap &FragTrap::operator=(const FragTrap &other)
{
    std::cout << "Assignment operator\n";
    std::cout << other << std::endl;
    return *this;
}

void FragTrap::highFiveGuys(void)
{
    std::cout << "Hey Guys! Give me a highFive!\n";
}
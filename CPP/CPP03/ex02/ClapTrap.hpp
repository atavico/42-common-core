/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:56:50 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/28 16:01:49 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>
# include <string>

class ClapTrap
{
    public:
            ClapTrap(const std::string name);
            ClapTrap(const ClapTrap &src);
            ClapTrap(void);
            ~ClapTrap(void);

            ClapTrap &operator=(const ClapTrap &other);

            void                attack(const std::string &target);
            void                takeDamage(unsigned int amount);
            void                beRepaired(unsigned int amount);
            const std::string   &getName(void) const;
    protected:
            std::string const _name;
            int               _hitPoints;
            int               _energyPoints;
            int               _attackDamage;
            int               _initialHitpoints;

};

std::ostream    &operator<<(std::ostream &ostr, ClapTrap const &instance);

#endif
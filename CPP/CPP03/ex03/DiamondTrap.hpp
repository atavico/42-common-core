/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:58:26 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/04 16:34:30 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap: public FragTrap, public ScavTrap
{
    private:
            std::string _name;
    public:
            DiamondTrap(std::string const &name);
            //DiamondTrap(const DiamondTrap &src) : ClapTrap(src){};
            //DiamondTrap(const DiamondTrap &src) : FragTrap(src){};
            //DiamondTrap(const DiamondTrap &src) : ScavTrap(src){};
            DiamondTrap(void);
            ~DiamondTrap(void);
           
            DiamondTrap &operator=(DiamondTrap const &other);
            using ScavTrap::attack;
            void    whoAmI(void) const;
};

#endif
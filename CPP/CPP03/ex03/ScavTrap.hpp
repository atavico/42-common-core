/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:21:07 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/24 19:05:31 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap: virtual public ClapTrap
{
    public:
            ScavTrap(const std::string name);
            ScavTrap(const ScavTrap &src);
            ScavTrap(void);
            ~ScavTrap(void);

            ScavTrap &operator=(const ScavTrap &other);

            void    attack(const std::string &target);
            void    guardGate(void) const;   
};

#endif
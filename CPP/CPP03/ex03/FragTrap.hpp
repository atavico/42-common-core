/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:24:14 by atarsi            #+#    #+#             */
/*   Updated: 2023/02/01 19:56:48 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap: virtual public ClapTrap
{
    public:
            FragTrap(std::string name);
            FragTrap(void);
            FragTrap(const FragTrap &src);
            ~FragTrap(void);

            FragTrap &operator=(const FragTrap &other);
            void highFiveGuys(void);
};

#endif
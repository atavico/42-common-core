/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:10:55 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/09 16:50:43 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"

class HumanB
{
    public:
            HumanB(std::string _name);
            void setWeapon(Weapon& _weapon);
            void attack(void);
    private:
            Weapon      *weapon;
            std::string name;
};

#endif
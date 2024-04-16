/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:10:01 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 15:58:26 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICHARACTER_HPP
# define ICHARACTER_HPP

#include <iostream>
#include "AMateria.hpp"

class AMateria;

class ICharacter
{
    protected:
        std::string name;
    public:
        virtual                   ~ICharacter(void){}
        virtual std::string const &getName() const = 0;
        virtual void              equip(AMateria* m) = 0;
        virtual void              unequip(int idx) = 0;
        virtual void              use(int idx, ICharacter& target) = 0;
};

#endif
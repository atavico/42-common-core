/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:20:13 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 17:13:40 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  CHARACTER_HPP
# define CHARACTER_HPP

#include "ICharacter.hpp"

class Character: public ICharacter
{
    private:
        AMateria          *(_slot[4]);
        std::string const _name;
        AMateria          *(_drop[10]);
    public:
        Character(const std::string &name);
        Character(const Character & ref);
        ~Character(void);

        Character& operator=(Character const & src);

        virtual std::string const &getName() const;
        virtual void              equip(AMateria* m);
        virtual void              unequip(int idx);
        virtual void              use(int idx, ICharacter& target);
};

#endif
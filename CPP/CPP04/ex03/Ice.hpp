/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:51:11 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 18:15:28 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

#include "AMateria.hpp"

class Ice: public AMateria
{
    public:
        Ice(void);
        Ice(const Ice &ref);
        ~Ice(void);

        Ice        &operator=(const Ice &other);

        std::string const   &getType(void) const;
        void                use(ICharacter& target);
        Ice*                clone() const;
    private:
        std::string const _type;
};

#endif
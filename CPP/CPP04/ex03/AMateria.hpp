/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:06:24 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 16:27:46 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

#include "ICharacter.hpp"

class ICharacter;

class AMateria
{
    protected:
        std::string type;
    public:
        AMateria(void);
        AMateria(std::string const &type);
        AMateria(AMateria const &ref);
        virtual ~AMateria(void);

        virtual std::string const   &getType() const;
        virtual AMateria            *clone() const = 0;
        virtual void                use(ICharacter& target);
};

#endif
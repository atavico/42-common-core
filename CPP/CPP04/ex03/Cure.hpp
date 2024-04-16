/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:16:13 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 18:20:02 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

#include "AMateria.hpp"

class Cure: public AMateria
{
    public:
        Cure(const Cure &ref);
        Cure(void);
        ~Cure(void);
        Cure    &operator=(const Cure &other);

        std::string const       &getType(void) const;
        void                    use(ICharacter& target);
        Cure*                   clone(void) const;
    private:
        std::string const   _type;
};

#endif
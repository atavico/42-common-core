/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriasource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:47:48 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/06 17:50:12 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMATERIASOURCE_HPP
# define IMATERIASOURCE_HPP

#include "AMateria.hpp"

class IMateriaSource
{
    public:
            virtual             ~IMateriaSource() {}
            virtual void        learnMateria(AMateria*) = 0;
            virtual AMateria*   createMateria(std::string const & type) = 0;
};
#endif
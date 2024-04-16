/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:05:16 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 15:12:38 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>
#include "Brain.hpp"

class AAnimal
{
    protected:
        std::string type;
        AAnimal(void);
        AAnimal(const AAnimal &src);
        AAnimal(std::string &type);
        virtual ~AAnimal(void);
        AAnimal &operator=(const AAnimal &other);
    public:
        const std::string   getType(void) const;
        virtual void        makeSound(void) const = 0;
        void                setType(std::string type);
        
};

#endif
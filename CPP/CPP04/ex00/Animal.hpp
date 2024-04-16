/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:36:12 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 15:24:20 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class Animal
{
    protected:
            std::string type;
    public:
            Animal  (void);
            Animal  (const Animal &src);
            virtual ~Animal(void);
            Animal              &operator=(const Animal &other);

            virtual void        makeSound(void) const;
            const std::string   getType(void) const;
            void                setType(std::string type);
};

std::ostream &operator<<(std::ostream &os, Animal const &s);

#endif
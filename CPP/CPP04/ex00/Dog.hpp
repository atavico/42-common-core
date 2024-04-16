/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:45:29 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 15:01:04 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal
{
    public:
            Dog(void);
            Dog(const Dog &src);
            ~Dog(void);
            void    makeSound(void) const;
};

std::ostream&   operator<<(std::ostream& os, Dog const &s);

#endif
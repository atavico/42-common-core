/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:45:29 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 15:04:19 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
    public:
            Brain   *brain;
            void            printBrain(void) const;
            virtual Brain   *getBrain(void) const;
            void            copyBrain(Brain* src);
    public:
            Dog(void);
            Dog(const Dog &src);
            ~Dog(void);
            Dog     &operator=(const Dog &other);
            void            makeSound(void) const;
};

std::ostream& operator<<(std::ostream& os, Dog const & s);

#endif
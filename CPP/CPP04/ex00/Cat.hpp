/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:14:06 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/18 15:00:12 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal
{
    public:
            Cat(void);
            Cat(const Cat &src);
            ~Cat(void);
            void makeSound(void) const;
};

std::ostream&   operator<<(std::ostream& os, Cat const & s);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:14:06 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 15:05:01 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal
{
    private:
            Brain *brain;
            Brain*      getBrain() const;
            void        printBrain(void) const;
            void        copyBrain(Brain* src);
    public:
            Cat(void);
            Cat(const Cat &src);
            ~Cat(void);
            Cat &operator=(const Cat &other);
            void        makeSound(void) const;
};

#endif
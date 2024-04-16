/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:00:47 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 15:06:09 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <iostream>

class WrongAnimal
{
    public:
            WrongAnimal(void);
            WrongAnimal(const WrongAnimal &src);
            virtual ~WrongAnimal(void);
            WrongAnimal     &operator=(const WrongAnimal &other);
            virtual void        makeSound(void) const = 0;
            const std::string   &getType(void) const;
    protected:
            std::string type;
};

#endif
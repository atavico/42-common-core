/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:24:37 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/08 13:51:48 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP
#include <iostream>
#include <string>

class Zombie
{
    private: 
        std::string name;
    public:
        //Zombie(std::string name);
        ~Zombie(void);
        void    announce(void);
        void    set_name(std::string _name);
};

Zombie* zombieHorde(int N, std::string name);

#endif

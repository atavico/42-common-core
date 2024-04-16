/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:34:55 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/09 16:53:04 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string _type)
{
    this->type = _type;
}

const   std::string& Weapon::getType(void)
{
    std::string& stringREF = type;
    return (stringREF);
}

void Weapon::setType(std::string _type)
{
    this->type = _type;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:54:19 by atarsi            #+#    #+#             */
/*   Updated: 2023/06/28 13:57:57 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern(void)
{
    std::cout << "Default Intern constructor" << std::endl;
}

Intern::Intern(const Intern &src)
{
    std::cout << "Intern constructor" << std::endl;
    *this = src;
}

Intern::~Intern(void)
{
    std::cout << "Intern Destructor" << std::endl;
}


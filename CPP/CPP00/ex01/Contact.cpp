/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:36:47 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/24 20:28:56 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void Contact::set_name(std::string str)
{
    name = str;
}
void Contact::set_last(std::string str)
{
    last = str;
}
void Contact::set_nick(std::string str)
{
    nick = str;
}
void Contact::set_phone(std::string str)
{
    phone = str;
}
void Contact::set_secret(std::string str)
{
    secret = str;
}

std::string Contact::get_name(void)
{
    return (name);
}
std::string Contact::get_last(void)
{
    return (last);
}
std::string Contact::get_nick(void)
{
    return (nick);
}
std::string Contact::get_phone(void)
{
    return (phone);
}
std::string Contact::get_secret(void)
{
    return (secret);
}

void Contact::print_info(void)
{
    std::cout << "First Name:   " << name << std::endl;
    std::cout << "Last Name:    " << last << std::endl;
    std::cout << "Nick Name:    " << nick << std::endl;
    std::cout << "Phone Number: " << phone << std::endl;
    std::cout << "Dark Secret: " << secret << std::endl;
}

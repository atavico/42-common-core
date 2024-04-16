/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:37:29 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/24 20:27:39 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <iomanip>
#include <string>

class Contact
{
    private:
        std::string name;
        std::string last;
        std::string nick;
        std::string phone;
        std::string secret;
        
    public:
        void    set_name(std::string str);
        void    set_last(std::string str);
        void    set_nick(std::string str);
        void    set_phone(std::string str);
        void    set_secret(std::string str);

        std::string get_name(void);
        std::string get_last(void);
        std::string get_nick(void);
        std::string get_phone(void);
        std::string get_secret(void);

        void print_info (void);
};

#endif
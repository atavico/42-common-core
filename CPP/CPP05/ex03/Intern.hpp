/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:46:49 by atarsi            #+#    #+#             */
/*   Updated: 2023/06/28 13:54:04 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

#include <iostream>
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern
{
    public:
        Intern(void);
        Intern(const Intern &src);
        ~Intern(void);

        Intern &operator=(const Intern &other);

        Form *makeForm(const std::string &form, const std::string &target) const;

    private:
    typedef struct s_forms
    {
        std::string _name;
        Form        *type;
    }            t_form;
    
};

std::ostream	&operator<<( std::ostream &ostr, const Intern &instance );
#endif
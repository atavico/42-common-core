/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:11:12 by alessandrot       #+#    #+#             */
/*   Updated: 2023/02/27 22:54:55 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCREAT_HPP
# define BUREAUCREAT_HPP

#include <iostream>
#include <stdexcept>
#include "Form.hpp"

class Form;

class Bureaucrat{
    public:
        Bureaucrat(void);
        Bureaucrat(const std::string &name, int grade);
        Bureaucrat(const Bureaucrat &src);
        ~Bureaucrat(void);
        
        Bureaucrat  &operator=(const Bureaucrat &other);

        const std::string &getName(void) const;
        int                 getGrade(void) const;
        void    incrementGrade(int quantity);
        void    decrementGrade(int quantity);
        bool    signForm(Form &form) const;
        bool    executeForm(const Form &Form) const;
        
    private:
        std::string const _name;
        int               _grade;

        static const int    lowestGrade = 150;
        static const int    highestGrade = 1;

        void    checkGrade(void) const;
    public:
        class GradeTooHighException : public std::exception
        {
            public:
                virtual const char* what() const throw()
                {
                    return ("The Grade is too hight\n");
                }
        };
        class GradeTooLowException : public std::exception
        {
            public:
                virtual const char* what() const throw()
                {
                    return ("The Grade is too low\n");
                }
        };
};

std::ostream &operator<<(std::ostream &ostr, const Bureaucrat &instance);

#endif
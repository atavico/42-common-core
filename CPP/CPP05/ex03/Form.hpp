/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:49:22 by alessandrot       #+#    #+#             */
/*   Updated: 2023/06/28 12:37:32 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>
#include <stdexcept>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
    private:
        Form(void);

        const   std::string _name;
        bool                _isSigned;
        const int           _gradeToSign;
        const int           _gradeToExecute;

        static const int    lowestGrade = 150;
        static const int    highestGrade = 1;

    public:
        
        Form(const std::string &name, int gradeToSign, int gradeToExecute);
        Form(const Form &src);
        ~Form(void);

        Form    &operator=(const Form &other);

        const std::string   &getName(void) const;
        bool                isSigned(void) const;
        int                 getSigned(void) const;
        int                 getExecute(void) const;

        void                checkGrade(void) const;
        void                checkExecute(const Bureaucrat &Bureaucrat) const;
        bool                beSigned(const Bureaucrat &Bureaucrat);
        virtual void	    execute(const Bureaucrat &executor) const = 0;

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
        class CantExecuteForm : public std::exception
        {
            public:
                virtual const char* what() const throw()
                {
                    return ("The Form can't be execute\n");
                }
        };

};

std::ostream	&operator<<(std::ostream &ostr, const Form &instance);


#endif
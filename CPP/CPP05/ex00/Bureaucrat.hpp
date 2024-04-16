/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandrotarsi <alessandrotarsi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:11:12 by alessandrot       #+#    #+#             */
/*   Updated: 2023/02/20 16:15:16 by alessandrot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCREAT_HPP
# define BUREAUCREAT_HPP

#include <iostream>
#include <stdexcept>

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
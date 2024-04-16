/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandrotarsi <alessandrotarsi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:47:36 by alessandrot       #+#    #+#             */
/*   Updated: 2023/02/20 12:37:18 by alessandrot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void): _name(""), _grade(Bureaucrat::lowestGrade)
{
    std::cout << "Default Bureaucrat\n";
}

Bureaucrat::Bureaucrat(const std::string &name, int grade): _name(name), _grade(grade)
{
    checkGrade();
    std::cout << "Bureaucrat constructor\n";
}

Bureaucrat::Bureaucrat(const Bureaucrat &src)
{
    *this = src;
    std::cout << "Copy Bureaucrat\n";
}

Bureaucrat::~Bureaucrat(void)
{
    std::cout << "Bureaucrat destructor\n";
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
    this->_grade = other._grade;
    std::cout << "assignment operator\n";
    return *this;
}

const std::string &Bureaucrat::getName(void) const
{
    return this->_name;
}

int Bureaucrat::getGrade(void) const
{
    return this->_grade;
}

void    Bureaucrat::incrementGrade(int quantity)
{
    std::cout << "Increment grade of " << quantity << std::endl;
    this->_grade -= quantity;
    checkGrade();
}

void Bureaucrat::decrementGrade(int quantity)
{
    std::cout << "Decrement grade of " << quantity << std::endl;
    this->_grade += quantity;
    checkGrade();
}

void    Bureaucrat::checkGrade(void) const
{
    if (this->_grade < Bureaucrat::highestGrade)
        throw Bureaucrat::GradeTooHighException();
    else if (this->_grade > Bureaucrat::lowestGrade)
        throw Bureaucrat::GradeTooLowException();
}

std::ostream &operator<<(std::ostream &ostr, const Bureaucrat &instance)
{
    ostr << instance.getName() << ", Bureaucrat grade " << instance.getGrade();
    return ostr;
}
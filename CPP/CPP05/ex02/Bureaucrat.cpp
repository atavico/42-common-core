/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:47:36 by alessandrot       #+#    #+#             */
/*   Updated: 2023/06/27 12:51:05 by atarsi           ###   ########.fr       */
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

bool	Bureaucrat::signForm(Form &form) const
{
	if (form.beSigned(*this))
	{
		std::cout << this->_name << " signs form " << form.getName() << std::endl;
		return true;
	}
	else
	{
		std::cout << this->_name << " cannot sign form " << form.getName()
			<< " because their grade is not high enough\n";
		return false;
	}
}

bool	Bureaucrat::executeForm(const Form &form) const
{
	try
	{
		form.checkExecute(*this);
		std::cout << this->_name << " executes form " << form.getName() << std::endl;
		return true;
	}
	catch (Form::CantExecuteForm &e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}

std::ostream &operator<<(std::ostream &ostr, const Bureaucrat &instance)
{
    ostr << instance.getName() << ", Bureaucrat grade " << instance.getGrade();
    return ostr;
}
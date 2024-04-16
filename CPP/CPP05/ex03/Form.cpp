/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:06:47 by atarsi            #+#    #+#             */
/*   Updated: 2023/06/27 12:24:46 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute): _name(name), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
    this->checkGrade();
    std::cout << "Standard Form\n";
}

Form::Form(void): _name(""), _isSigned(false), _gradeToSign(Form::lowestGrade), _gradeToExecute(Form::lowestGrade)
{
    this->checkGrade();
    std::cout << "Default Form\n";
}

Form::~Form(void)
{
    std::cout << "Form destructor\n";
}

Form &Form::operator=(Form const &other)
{
    this->_isSigned = other._isSigned;
    std::cout << "Form assignment\n";
    return *this;
}

Form::Form(Form const &src): _name(src.getName()), _isSigned(src.isSigned()), 
                            _gradeToSign(src.getSigned()), _gradeToExecute(src.getExecute())
{
    std::cout << "Form copy\n";
    *this = src;
}

const std::string &Form::getName(void) const
{
    return this->_name;
}

int Form::getSigned(void) const
{
    return this->_gradeToSign;
}

int Form::getExecute(void) const
{
    return this->_gradeToExecute;
}

bool Form::isSigned(void) const
{
    return this->_isSigned;
}

void Form::checkGrade(void) const
{
    if (this->_gradeToSign < this->highestGrade
        || this->_gradeToExecute < this->highestGrade)
        throw Form::GradeTooHighException();
    if (this->_gradeToSign > this->lowestGrade
        || this->_gradeToExecute > this->lowestGrade)
        throw Form::GradeTooLowException();
}

void Form::checkExecute(const Bureaucrat &Bureaucrat) const
{
    if (this->_isSigned == false || Bureaucrat.getGrade() > this->_gradeToExecute)
        throw Form::CantExecuteForm();
}

bool Form::beSigned(const Bureaucrat &Bureaucrat)
{
    if (Bureaucrat.getGrade() < this->_gradeToSign)
    {
        this->_isSigned = true;
        return true;
    }
    else
    {
        this->_isSigned = false;
        return false;
    }
}

std::ostream	&operator<<(std::ostream & ostr, Form const & instance)
{
	ostr << instance.getName() << " signed by "
		<< instance.getSigned() << ", graded by "
		<< instance.getExecute() << ", it is "
		<< ((instance.isSigned()) ? "" : "not ") << "signed";
	return ostr;
}
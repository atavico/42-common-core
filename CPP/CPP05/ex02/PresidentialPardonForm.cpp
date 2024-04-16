/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:24:26 by atarsi            #+#    #+#             */
/*   Updated: 2023/06/28 12:34:24 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void):
    Form("PresidentialPardonForm", 25, 5), _target("")
{
    std::cout << "Default constructor PPF" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target):
    Form("PresidentialPardonForm", 25, 5), _target(target)
{
    std::cout << "Standard constructor PPF" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &src):
    Form("PresidentialPardonForm", 25, 5), _target(src.getTarget())
{
    std::cout << "Copy constructor PPF" << std::endl;
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{
    std::cout << "PresidentialPardonForm Destructor" << std::endl;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
    other.getTarget();
    std::cout << "Assignment operator" << std::endl;
    return *this;
}

const std::string &PresidentialPardonForm::getTarget(void) const
{
    return this->_target;
}

void PresidentialPardonForm::execute(const Bureaucrat &executor) const
{
    this->checkExecute(executor);
	std::cout << this->_target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:55:46 by atarsi            #+#    #+#             */
/*   Updated: 2023/06/28 12:11:26 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void):
    Form("RobotomyRequestForm", 72, 45), _target("")
{
    std::cout << "Default RobotomyRequestForm" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target):
    Form("RobotomyRequestForm", 72, 45), _target(target)
{
    std::cout << "Standard RobotomyRequestForm" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &src):
    Form("RobotomyRequestForm", 72, 45), _target(src.getTarget())
{
    std::cout << "Copy RobotomyRequestForm" << std::endl;
    *this = src;
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
    std::cout << "RobotomyRequestForm Destructor" << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
    other.getTarget();
    std::cout << "Assignment operator" << std::endl;
    return *this;
}

const std::string &RobotomyRequestForm::getTarget(void) const
{
    return this->_target;
}

void RobotomyRequestForm::execute(const Bureaucrat &execute) const
{
    this->checkExecute(execute);
	std::cout << " * DRILLING NOISES * " << std::endl;
	if (std::rand() % 2)
		std::cout << this->_target << " has been robotomized" << std::endl;
	else
		std::cout << this->_target << " robotomization has failed" << std::endl;
}

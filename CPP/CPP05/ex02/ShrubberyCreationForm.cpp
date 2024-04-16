/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:04:23 by atarsi            #+#    #+#             */
/*   Updated: 2023/06/28 12:39:58 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void):
    Form("ShrubberyCreationForm", 145, 137), _target("")
{
    std::cout << "Default ShrubberyCreationForm\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target):
    Form("ShrubberyCreationForm", 145, 137), _target(target)
{
    std::cout << "Standard ShrubberyCreationForm\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src):
    Form("ShrubberyCreationForm", 145, 137), _target(src.getTarget())
{
    std::cout << "ShrubberyCreationForm assignment\n";
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
    std::cout << "ShrubberyCreationForm Destructor\n";
}

const std::string &ShrubberyCreationForm::getTarget(void) const
{
    return this->_target;
}

void	ShrubberyCreationForm::execute(const Bureaucrat &executor) const
{
	std::ofstream	f;
	std::string		file_name = this->_target + "_shrubbery";

	this->checkExecute(executor);
	f.open(file_name.c_str(), std::ios::out);


	f << "                                                 .\n";
	f << "                                      .         ;\n";
	f << "         .              .              ;%     ;;\n";
	f << "           ,           ,                :;%  %;\n";
	f << "            :         ;                   :;%;'     .,\n";
	f << "   ,.        %;     %;            ;        %;'    ,;\n";
	f << "     ;       ;%;  %%;        ,     %;    ;%;    ,%'\n";
	f << "      %;       %;%;      ,  ;       %;  ;%;   ,%;'\n";
	f << "       ;%;      %;        ;%;        % ;%;  ,%;'\n";
	f << "        `%;.     ;%;     %;'         `;%%;.%;'\n";
	f << "         `:;%.    ;%%. %@;        %; ;@%;%'\n";
	f << "            `:%;.  :;bd%;          %;@%;'\n";
	f << "              `@%:.  :;%.         ;@@%;'\n";
	f << "                `@%.  `;@%.      ;@@%;\n";
	f << "                  `@%%. `@%%    ;@@%;\n";
	f << "                    ;@%. :@%%  %@@%;\n";
	f << "                      %@bd%%%bd%%:;\n";
	f << "                        #@%%%%%:;;\n";
	f << "                        %@@%%%::;\n";
	f << "                        %@@@%(o);  . '\n";
	f << "                        %@@@o%;:(.,'\n";
	f << "                    `.. %@@@o%::;\n";
	f << "                       `)@@@o%::;\n";
	f << "                        %@@(o)::;\n";
	f << "                       .%@@@@%::;\n";
	f << "                       ;%@@@@%::;.\n";
	f << "                      ;%@@@@%%:;;;.\n";
	f << "                  ...;%@@@@@%%:;;;;,..\n";
	f.close();
	std::cout << "A tree grown: " << this->_target << "_shrubbery\n";
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:52:59 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/24 20:46:20 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

void    reset_last(PhoneBook *phonebook)
{
    std::cout << "Field Empty!!\n\n";
    phonebook->phonebook[phonebook->contact].set_name("");
    phonebook->phonebook[phonebook->contact].set_last("");
    phonebook->phonebook[phonebook->contact].set_nick("");
    phonebook->phonebook[phonebook->contact].set_phone("");
}

int add(PhoneBook *phonebook)
{
    std::string input;

    std::cout << "Please enter all information\n";
    std::cout << "First Name: ";
    getline(std::cin, input);
    if (input.length() == 0)
        return (1);
    phonebook->phonebook[phonebook->contact].set_name(input);
    std::cout << "Last Name: ";
    getline(std::cin, input);
    if (input.length() == 0)
        return (1);
    phonebook->phonebook[phonebook->contact].set_last(input);
    std::cout << "Nick Name: ";
    getline(std::cin, input);
    if (input.length() == 0)
        return (1);
    phonebook->phonebook[phonebook->contact].set_nick(input);
    std::cout << "Phone Number: ";
    getline(std::cin, input);
    if (input.length() == 0)
        return (1);
    phonebook->phonebook[phonebook->contact].set_phone(input);
    std::cout << "Dark Secret: ";
    getline(std::cin, input);
    if (input.length() == 0)
        return (1);
    phonebook->phonebook[phonebook->contact].set_secret(input);
    std::cout << "Contact Added to PhoneBook\n\n";
    phonebook->contact++;
    if (phonebook->contact_lim < phonebook->contact)
        phonebook->contact_lim = phonebook->contact;
    return (0);
}

std::string	trunc_str(std::string str)
{
	if (str.length() <= 10)
		return (str);
	return (str.substr(0, 9) + ".");
}

void	search(PhoneBook *phonebook)
{
	std::string	input;

	for (int i = 0; i < phonebook->contact_lim; i++)
	{
		std::cout << "|" << std::setw(10) << i + 1;
		std::cout << "|" << std::setw(10) << trunc_str(phonebook->phonebook[i].get_name());
		std::cout << "|" << std::setw(10) << trunc_str(phonebook->phonebook[i].get_last());
		std::cout << "|" << std::setw(10) << trunc_str(phonebook->phonebook[i].get_nick());
		std::cout << "|" << std::endl;
	}
	std::cout << "Select Contact by Index: ";
	getline(std::cin, input);
	if (input.length() == 1 && ('0' < input[0] && input[0] < '9')
		&& (input[0]-49 < phonebook->contact))
		phonebook->phonebook[input[0] - '0' - 1].print_info();
	else
		std::cout << "Invalid Index!!\n\n";
}

int main(void)
{
    PhoneBook   phonebook;
    std::string input;
    int         run = 1;

    phonebook.contact = 0;
    phonebook.contact_lim = 0;
    while (run)
    {
        std::cout << ">> ";
        getline(std::cin, input);
        if (input == "EXIT")
            run = 0;
        else if (input == "ADD")
        {
            if (phonebook.contact >= 8)
                phonebook.contact = 0;
            if (add(&phonebook))
                reset_last(&phonebook);
        }
        else if (input == "SEARCH")
        {
            if (!phonebook.contact)
                std::cout << "The PhoneBook is empty!!\n";
            else 
                search(&phonebook);
        }
        else
            std::cout << "Command " << input << "not found, try with ADD | SEARCH | EXIT\n";
    }
}

        
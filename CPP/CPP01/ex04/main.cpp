/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:04 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/26 15:07:31 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <ios>
#include <exception>

int main(int argc, char *argv[])
{
    if (argc != 4 || !strlen(argv[1]) || !strlen(argv[2]) || !strlen(argv[3]))
    {
        std::cout << "Error: invalid arguments\n";
        return (1);
    }
    std::string     input;
    std::string     s1 = argv[2];
    std::string     s2 = argv[3];
    std::size_t     re;
    std::size_t     i = 0;
    int             len = strlen(argv[2]);
    std::ofstream   sed;

    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(argv[1], std::ifstream::in);
    }
    catch (const std::ifstream::failure &e)
    {
        std::cout << "Error: The file doesn't exist" << std::endl;
        return (1);
    }
    //std::ofstream   sed;
    sed.open(strcat(argv[1], ".replace"), std::ofstream::trunc);
    std::getline(file, input, '\0');
    re = input.find(s1);
    while (re != std::string::npos)
    {
        while (i != re)
            sed << input[i++];
        sed << s2;
        i += len;
        re = input.find(s1, i);
    }
    while (i != input.size())
        sed << input[i++];
    sed.close();
    file.close();
}
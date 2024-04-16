/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 20:05:10 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/24 20:21:35 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main (int argc, char *argv[])
{
    if (argc == 1)
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    else{
        for (int i = 1; i < argc; i++){
            for (int j = 0; argv[i][j]; j++)
                std::cout << (char)toupper(argv[i][j]);
                }
    }
    std::cout << std::endl;
    return (0);
}

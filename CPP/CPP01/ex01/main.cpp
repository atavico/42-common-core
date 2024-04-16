/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:20:14 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/08 13:50:30 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Zombie.hpp"

int main(void)
{
    int n;
    std::cout << "Enter number of Zombies: ";
    std::cin >> n;

    Zombie *horde = zombieHorde(n, "test");

    for (int i = 0; i < n; i++)
        horde[i].announce();

    std::cout << std::endl;
    delete [] horde;
}
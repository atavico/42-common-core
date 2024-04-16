/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:26:57 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/07 19:58:23 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
    Zombie  test("dritan");
    std::cout <<"test 1\n";
    test.announce();

    std::cout << "\ntest 2\n";
    Zombie  *test_2 = newZombie("mana");
    test_2->announce();


}
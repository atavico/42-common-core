/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:13:54 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/26 15:18:38 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main (void)
{
    Harl    Harl;

    Harl.complain("debug");
    Harl.complain("info");
    Harl.complain("warning");
    Harl.complain("error");
    Harl.complain("testttt");

    return (0);
}
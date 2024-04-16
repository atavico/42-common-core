/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:10:39 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/24 18:10:50 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main() 
{
	ClapTrap clap("clap");
	clap.attack("Handsome Jack");
	clap.takeDamage(6);
	clap.beRepaired(4);
	clap.takeDamage(3);
	clap.beRepaired(8);
	clap.takeDamage(17);
}
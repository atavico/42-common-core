/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:17:24 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 14:50:38 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"

int	main()
{
	const Animal *j[2];
	Dog basic;
	Dog tmp = basic;

	j[0] = new Dog();
	j[1] = new Cat();
	j[0]->makeSound();
	j[1]->makeSound();
	int i = -1;

	while(++i < 2)
		delete j[i];
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:46:57 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/01 14:52:31 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

#include "Point.hpp"

bool	bsp(Point const a, Point const b, Point const c, Point const point);

int	main(void)
{
	std::cout << "a(0, 0), b(0, 5), c(5, 0), point(1, 1): "
		<< bsp(Point(0, 0), Point(0, 5), Point(5, 0), Point(1, 1)) << std::endl;

	std::cout << "a(0, 0), b(0, 5), c(5, 0), point(0, 5): "
		<< bsp(Point(0, 0), Point(0, 5), Point(5, 0), Point(0, 5)) << std::endl;

	std::cout << "a(0, 0), b(0, 5), c(5, 0), point(0, 3): "
	    << bsp(Point(0, 0), Point(0, 5), Point(5, 0), Point(0, 3)) << std::endl;

	std::cout << "a(0, 0), b(0, 5), c(5, 0), point(0, 0): "
		<< bsp(Point(0, 0), Point(0, 5), Point(5, 0), Point(0, 0)) << std::endl;

	std::cout << "a(0, 0), b(0, 5), c(5, 0), point(0.1, 0.01): "
		<< bsp(Point(0, 0), Point(0, 5), Point(5, 0), Point(0.1f, 0.01f)) << std::endl;

	std::cout << "a(0, 0), b(0, 5), c(5, 0), point(10, 0.01): "
		<< bsp(Point(0, 0), Point(0, 5), Point(5, 0), Point(10, 0.01f)) << std::endl;

	std::cout << "a(0, 0), b(0, 5), c(5, 0), point(0, -0.01): "
		<< bsp(Point(0, 0), Point(0, 5), Point(5, 0), Point(0, -0.01f)) << std::endl;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:32:08 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/01 14:52:34 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point(void): _x(0), _y(0) {}

Point::~Point (void)
{
    std::cout << "Point destructor called\n";
}

Point::Point(Point const &other)
{
    std::cout << "Copy constructor called\n";
    *this = other;
}

Point::Point(Fixed const x, Fixed const y): _x(x), _y(y) {}

Point &Point::operator=(Point const &other)
{
    (void)other;
    return *this;
}

Fixed const &Point::getX(void) const
{
    return _x;
}

Fixed const &Point::getY(void) const
{
    return _y;
}






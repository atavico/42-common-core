/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:33:42 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/23 12:37:31 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point
{
    public:
            Point(void);
            Point(Point const &other);
            Point(Fixed const x, Fixed const y);
            ~Point(void);

            Point   &operator=(Point const &other);

            Fixed const &getX(void) const;
            Fixed const &getY(void) const;
    private:
            Fixed const _x;
            Fixed const _y;
};

#endif
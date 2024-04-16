/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:09:02 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/21 16:44:22 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <cmath>
#include <iostream>

class Fixed
{
    public:
            Fixed (void);
            Fixed (const Fixed &src);
            Fixed &operator=(Fixed const &other);
            Fixed (const int n);
            Fixed (const float n);
            ~Fixed (void);
            int     getRawBits (void) const;
            void    setRawBits (int const raw);
            float   toFloat(void) const;
            int     toInt(void) const;
    private:
            int                 _fixed;
            static const int    _fbits = 8;

};

std::ostream &operator<<(std::ostream &stream, Fixed const &instance);

#endif
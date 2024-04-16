/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:57:26 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/17 17:19:46 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP
#include "iostream"

class Brain
{
    public:
        Brain(void);
        Brain(Brain const &src);
        virtual ~Brain(void);
        Brain   &operator=(const Brain &other);
        std::string     getIdea(int i) const;
        void            setIdea(std::string s, int i);
        static const int n_idea = 100;
    private:
        std::string idea[Brain::n_idea];

};
    
#endif
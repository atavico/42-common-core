/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:28:06 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 14:52:33 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void): brain(new Brain())
{
    this->setType("Dog");
    //this->brain = new Brain();
    std::cout << "Default dog\n";           
}

Dog::Dog(const Dog &src) : Animal(), brain(new Brain())
{
    std::cout << "Copy dog\n";
    this->setType(src.getType());
    this->copyBrain(src.getBrain());
}

Dog::~Dog(void)
{
    delete this->brain;
    std::cout << "destructor dog\n";
}

void Dog::makeSound(void) const
{
    std::cout << "*woffff woffff*" << std::endl;
}

Dog &Dog::operator=(Dog const &other)
{
    std::cout << "Assignment operator Dog class" << std::endl;
    if(this == &other)
        return (*this);
    this->setType(other.getType());
    this->brain = new Brain();
    this->copyBrain(other.getBrain());
    return (*this);
}
void    Dog::printBrain(void) const
{
    int i;
    i = -1;
    while(++i < brain->n_idea)
        std::cout << i << "=" << brain->getIdea(i) << std::endl;
}

Brain*  Dog::getBrain(void) const
{
    return(this->brain);
}

void    Dog::copyBrain(Brain* src)
{
    int i;
    i = -1;
    while(++i < brain->n_idea)
        this->brain->setIdea(src->getIdea(i), i);
}

std::ostream& operator<<(std::ostream& os, Dog const & s)
{
    os << s.getType() << std::endl;
    return (os);
}
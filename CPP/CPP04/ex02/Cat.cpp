/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:20:16 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 15:06:40 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void) : brain(new Brain)
{
    this->setType("Cat");
    //this->brain = new Brain();
    std::cout << "Default cat\n";
}

Cat::~Cat(void)
{
    delete this->brain;
    std::cout << "destructor cat\n";
}

void    Cat::makeSound(void) const
{
    std::cout << "*meow noisesssss*" << std::endl;
}
void Cat::copyBrain(Brain* src)
{
    int i;
    std::cout << "Copy Brain in cat class" << std::endl;
    i = -1;
    while (++i < brain->n_idea)
        this->brain->setIdea(src->getIdea(i), i);
}

Cat::Cat(Cat const &src) : AAnimal(), brain(new Brain())
{
    std::cout << "Copy cat\n";
    this->setType(src.getType());
    this->copyBrain(src.getBrain());
}

Cat&    Cat::operator=(Cat const &other)
{
    std::cout << "Assignment operator" << std::endl;
    this->setType(other.getType());
    this->brain = new Brain();
    this->copyBrain(other.getBrain());
    return *this;
}

void    Cat::printBrain(void) const
{
    int i;
    std::cout << "Print brain" << std::endl;
    i = -1;
    while(++i < brain->n_idea)
        std::cout << i << "=" << this->brain->getIdea(i) << std::endl;
}

Brain *Cat::getBrain(void) const
{
    return (this->brain);
}
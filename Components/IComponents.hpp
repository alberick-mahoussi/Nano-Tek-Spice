/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** IComponents
*/

#ifndef ICOMPONENTS_HPP_
#define ICOMPONENTS_HPP_

#include <iostream>

namespace nts {
    
    enum Tristate {
        Undefined = (-true),
        True = true,
        False = false
    };

    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual void simulate(std::size_t tick) = 0;
            virtual nts::Tristate compute(std::size_t pin) = 0;
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
            virtual void setState(const std::string &) = 0;
            virtual bool isInput() = 0;
            virtual bool isOutput() = 0;            
            virtual void debug() = 0;
    };
}


#endif /* !ICOMPONENTS_HPP_ */

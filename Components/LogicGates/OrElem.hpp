/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** OrElem
*/

#ifndef ORELEM_HPP_
#define ORELEM_HPP_

#include "AComponents.hpp"

class OrElem : public nts::AComponent {
    public:
        OrElem(std::string name, size_t pin);
        ~OrElem();
        nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
        void debug() override { std::cout << "Im Or components" << std::endl; };
    protected:
    private:
        size_t _pin;
        std::string _name;
        std::unordered_map<std::size_t, std::pair<IComponent*, std::size_t>> _OrComponent;
};

#endif /* !ORELEM_HPP_ */

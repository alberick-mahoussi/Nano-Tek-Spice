/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** XorElem
*/

#ifndef XORELEM_HPP_
#define XORELEM_HPP_

#include "../AComponents.hpp"

class XorElem : public nts::AComponent {
    public:
        XorElem(std::string name, size_t pin);
        ~XorElem();
        nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
        void debug() override{ std::cout << "Im Xor components" << std::endl; };
    protected:
    private:
        size_t _pin;
        std::string _name;
        std::unordered_map<std::size_t, std::pair<IComponent*, std::size_t>> _XorComponent;
};

#endif /* !XORELEM_HPP_ */

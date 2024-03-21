/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** TrueElem
*/

#ifndef TRUEELEM_HPP_
#define TRUEELEM_HPP_

#include "AComponents.hpp"

class TrueElem : public nts::AComponent {
    public:
        TrueElem(std::string name, int pin);
        ~TrueElem();
        nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
        void setState(const std::string &state) override;
        void debug() override{ std::cout << "False" << std::endl; };
        bool isInput() override{ return true; };
    protected:
    private:
        int _pin;
        std::string _name;
        nts::Tristate _state;
        bool _used;
};

#endif /* !TRUEELEM_HPP_ */

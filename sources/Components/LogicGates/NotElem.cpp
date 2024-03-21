/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** NotElem
*/

#include "LogicGates/NotElem.hpp"

NotElem::NotElem(std::string name, size_t pin)
{
    _name = name;
    _pin = pin;

    _NotComponent[1] = {nullptr, -1};
    _NotComponent[2] = {nullptr, -2};
}

NotElem::~NotElem()
{
}

void NotElem::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin > _pin || pin < 1)
        throw nts::ErrorHandling("Error: Pin doesn't exist");
    if (other.isInput() || other.isOutput()) {
        _NotComponent[pin] = {&other, otherPin};
    } else {
        if (pin == 2)
            other.setLink(otherPin, *this, pin);
        else
            _NotComponent[pin] = {&other, otherPin};
    }
};

nts::Tristate NotElem::compute(std::size_t pin)
{
    if (pin == 1)
        return _NotComponent[pin].first->compute(_NotComponent[pin].second);
    else if (pin == 2) {
        nts::Tristate input1;
        input1 = _NotComponent[1].first->compute(_NotComponent[1].second);
        if (input1 == nts::Tristate::True) {
            return nts::Tristate::False;
        }
        else if (input1 == nts::Tristate::False) {
            return nts::Tristate::True;
        }
        return nts::Tristate::Undefined;
    }
    throw nts::ErrorHandling("Error: Incorrect pin");
};

void NotElem::debug()
{
    std::cout << _name << " cococ" << std::endl;
};

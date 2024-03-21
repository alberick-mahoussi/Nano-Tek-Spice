/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** OrElem
*/

#include "LogicGates/OrElem.hpp"

OrElem::OrElem(std::string name, size_t pin)
{
    _name = name;
    _pin = pin;

    _OrComponent[1] = {nullptr, -1};
    _OrComponent[2] = {nullptr, -1};
    _OrComponent[3] = {nullptr, -2};
}

OrElem::~OrElem()
{
}

void OrElem::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin > _pin || pin < 1)
        throw nts::ErrorHandling("Error: Pin doesn't exist");
    if (other.isInput() || other.isOutput()) {
        _OrComponent[pin] = {&other, otherPin};
    } else {
        if (pin == 3)
            other.setLink(otherPin, *this, pin);
        else
            _OrComponent[pin] = {&other, otherPin};
    }
};

nts::Tristate OrElem::compute(std::size_t pin)
{
    if (pin == 1 || pin == 2) {
        if (_OrComponent[pin].first == nullptr)
            return nts::Tristate::Undefined;
        return _OrComponent[pin].first->compute(_OrComponent[pin].second);
    } else if (pin == 3) {
        nts::Tristate input1, input2;
        input1 = (_OrComponent[1].first == nullptr) ? nts::Tristate::Undefined : _OrComponent[1].first->compute(_OrComponent[1].second);
        input2 = (_OrComponent[2].first == nullptr) ? nts::Tristate::Undefined : _OrComponent[2].first->compute(_OrComponent[2].second);
        if (input1 == nts::Tristate::True || input2 == nts::Tristate::True) {
            return nts::Tristate::True;
        }
        else if (input1 == nts::Tristate::Undefined || input2 == nts::Tristate::Undefined) {
            return nts::Tristate::Undefined;
        }
        return nts::Tristate::False;
    }
    throw nts::ErrorHandling("Error: Incorrect pin");
};

/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** XorElem
*/

#include "LogicGates/XorElem.hpp"

XorElem::XorElem(std::string name, size_t pin)
{
    _name = name;
    _pin = pin;

    _XorComponent[1] = {nullptr, -1};
    _XorComponent[2] = {nullptr, -2};
}

XorElem::~XorElem()
{
}

void XorElem::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin > _pin || pin < 1)
        throw nts::ErrorHandling("Error: Pin doesn't exist");
    if (other.isInput() || other.isOutput()) {
        _XorComponent[pin] = {&other, otherPin};
    } else {
        if (pin == 2)
            other.setLink(otherPin, *this, pin);
        else
            _XorComponent[pin] = {&other, otherPin};
    }
};

nts::Tristate XorElem::compute(std::size_t pin)
{
    if (pin == 1 || pin == 2) {
        if (_XorComponent[pin].first == nullptr)
            return nts::Tristate::Undefined;
        return _XorComponent[pin].first->compute(_XorComponent[pin].second);
    } else if (pin == 3) {
        nts::Tristate input1, input2;
        input1 = (_XorComponent[1].first == nullptr) ? nts::Tristate::Undefined : _XorComponent[1].first->compute(_XorComponent[1].second);
        input2 = (_XorComponent[2].first == nullptr) ? nts::Tristate::Undefined : _XorComponent[2].first->compute(_XorComponent[2].second);
        if (input1 == nts::Tristate::Undefined || input2 == nts::Tristate::Undefined) {
            return nts::Tristate::Undefined;
        }
        else if (input1 != input2) {
            return nts::Tristate::True;
        }
        return nts::Tristate::False;
    }
    throw nts::ErrorHandling("Error: Incorrect pin");
};
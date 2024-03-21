/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** AndElem
*/

#include "LogicGates/AndElem.hpp"

AndElem::AndElem(std::string name, size_t pin)
{
    _name = name;
    _pin = pin;

    _AndComponent[1] = {nullptr, -1};
    _AndComponent[2] = {nullptr, -1};
    _AndComponent[3] = {nullptr, -2};
}

AndElem::~AndElem()
{
}

void AndElem::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin > _pin || pin < 1)
        throw nts::ErrorHandling("Error: Pin doesn't exist");
    if (other.isInput() || other.isOutput()) {
        _AndComponent[pin] = {&other, otherPin};
    } else {
        if (pin == 3)
            other.setLink(otherPin, *this, pin);
        else
            _AndComponent[pin] = {&other, otherPin};
    }
};

nts::Tristate AndElem::compute(std::size_t pin)
{
    nts::Tristate input1, input2;

    if (pin == 1 || pin == 2) {
        if (_AndComponent[pin].first == nullptr)
            return nts::Tristate::Undefined;
        return _AndComponent[pin].first->compute(_AndComponent[pin].second);
    } else if (pin == 3) {
        input1 = (_AndComponent[1].first == nullptr) ? nts::Tristate::Undefined : _AndComponent[1].first->compute(_AndComponent[1].second);
        input2 = (_AndComponent[2].first == nullptr) ? nts::Tristate::Undefined : _AndComponent[2].first->compute(_AndComponent[2].second);
        if (input1 == nts::Tristate::True && input2 == nts::Tristate::True) {
		    return nts::Tristate::True;
        } else if (input1 == nts::Tristate::False || input2 == nts::Tristate::False) {
            return nts::Tristate::False;
        }
        return nts::Tristate::Undefined;
    }
    throw nts::ErrorHandling("Error: Incorrect pin");
};

void AndElem::debug()
{
    std::cout << _name << "cococ" << std::endl;
};

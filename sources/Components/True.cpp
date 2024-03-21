/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** True
*/

#include "TrueElem.hpp"

TrueElem::TrueElem(std::string name, int pin)
{
    _name = name;
    _pin = pin;
    _state = nts::Tristate::True;
    _used = false;
};

TrueElem::~TrueElem() {};

void TrueElem::setState(const std::string &state)
{
    if (state == "0")
        _state = nts::Tristate::True;
    else if (state == "1")
        _state = nts::Tristate::True;
    else
        throw nts::ErrorHandling("Error: Invalid syntax");
};

void TrueElem::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin != 1)
        throw nts::ErrorHandling("Error: Bad input pin");
    if (other.isInput() == true)
        throw nts::ErrorHandling("Error: Try to connect input with input");
    other.setLink(otherPin, *this, pin);
};

nts::Tristate TrueElem::compute(std::size_t pin = 1)
{
    (void)pin;
	return _state;
};


/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** Input
*/

#include "Input.hpp"
#include "ErrorHandling.hpp"

Input::Input(std::string name, int pin)
{
    _name = name;
    _pin = pin;
    _state = nts::Tristate::Undefined;
    _used = false;
};

Input::~Input() {};

void Input::setState(const std::string &state)
{
    if (state == "0")
        _state = nts::Tristate::False;
    else if (state == "1")
        _state = nts::Tristate::True;
    else if (state == "u")
        _state = nts::Tristate::Undefined;
    else
        throw nts::ErrorHandling("Error: Invalid syntaxx");
};

void Input::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin != 1)
        throw nts::ErrorHandling("Error: Bad input pin");
    if (other.isInput() == true)
        throw nts::ErrorHandling("Error: Try to connect input with input");
    other.setLink(otherPin, *this, pin);
};

nts::Tristate Input::compute(std::size_t pin = 1)
{
    (void)pin;
	return _state;
};

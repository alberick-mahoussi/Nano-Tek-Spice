/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** Output
*/

#include "Output.hpp"

Output::Output(std::string name, int pin)
{
    _name = name;
    _pin = pin;
};

Output::~Output()
{
};

void Output::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    (void)other;
    (void)otherPin;
    if (pin != 1)
        throw nts::ErrorHandling("Error: Bad Output pin");
    test = &other;
    _pin = otherPin;
};

nts::Tristate Output::compute(std::size_t pin = 1)
{
    (void)pin;
    if (test == nullptr)
        return nts::Tristate::Undefined;
    return test->compute(_pin);
};

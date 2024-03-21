/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** 4001
*/

#include "Gates/4001Gate.hpp"

Gate4001::Gate4001(std::string name, size_t pin)
{
    _name = name;
    _pin = pin;
    OrGate1 = std::make_shared<OrElem>("Or1", 3);
    OrGate2 = std::make_shared<OrElem>("Or2", 3);
    OrGate3 = std::make_shared<OrElem>("Or3", 3);
    OrGate4 = std::make_shared<OrElem>("Or4", 3);
    std::shared_ptr<nts::IComponent> emptySharedPtr = nullptr;
    
    _4001Component[1] = {OrGate1, 1};
    _4001Component[2] = {OrGate1, 2};
    _4001Component[3] = {OrGate1, 3};
    _4001Component[4] = {OrGate2, 3};
    _4001Component[5] = {OrGate2, 1};
    _4001Component[6] = {OrGate2, 2};
    _4001Component[7] = {emptySharedPtr, -1};
    _4001Component[8] = {OrGate3, 1};
    _4001Component[9] = {OrGate3, 2};
    _4001Component[10] = {OrGate3, 3};
    _4001Component[11] = {OrGate4, 3};
    _4001Component[12] = {OrGate4, 2};
    _4001Component[13] = {OrGate4, 1};
    _4001Component[14] = {emptySharedPtr, -1};
}

Gate4001::~Gate4001()
{
}

void Gate4001::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin > _pin || pin < 1)
        throw nts::ErrorHandling("Error: Pin doesn't exist");
    if (pin == 7 || pin == 14)
        return;
    if (auto component = _4001Component[pin].first.lock())
        component->setLink(_4001Component[pin].second, other, otherPin);
};

nts::Tristate Gate4001::compute(std::size_t pin)
{
    if (std::find(_input.begin(), _input.end(), pin) != _input.end()) {
        if (auto component = _4001Component[pin].first.lock()) {
            return component->compute(_4001Component[pin].second);
        } else {
            throw nts::ErrorHandling("Error: Component is not valid (input)");
        }
    }
    else if (std::find(_output.begin(), _output.end(), pin) != _output.end()) {
        if (auto component = _4001Component[pin].first.lock()) {
            nts::Tristate input1 = component->compute(_4001Component[pin].second);
            if (input1 == nts::Tristate::True) {
                return nts::Tristate::False;
            }
            else if (input1 == nts::Tristate::False) {
                return nts::Tristate::True;
            }
            return nts::Tristate::Undefined;
        } else {
            throw nts::ErrorHandling("Error: Component is not valid (output)");
        }
    }
    throw nts::ErrorHandling("Error: Incorrect pin");
};
/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** 4030Gate
*/

#include "Gates/4030Gate.hpp"

Gate4030::Gate4030(std::string name, size_t pin)
{
    _name = name;
    _pin = pin;
    XorGate1 = std::make_shared<XorElem>("Xor1", 3);
    XorGate2 = std::make_shared<XorElem>("Xor2", 3);
    XorGate3 = std::make_shared<XorElem>("Xor3", 3);
    XorGate4 = std::make_shared<XorElem>("Xor4", 3);
    std::shared_ptr<nts::IComponent> emptySharedPtr;
    
    _4030Component[1] = {XorGate1, 1};
    _4030Component[2] = {XorGate1, 2};
    _4030Component[3] = {XorGate1, 3};
    _4030Component[4] = {XorGate2, 3};
    _4030Component[5] = {XorGate2, 1};
    _4030Component[6] = {XorGate2, 2};
    _4030Component[7] = {emptySharedPtr, -1};
    _4030Component[8] = {XorGate3, 1};
    _4030Component[9] = {XorGate3, 2};
    _4030Component[10] = {XorGate3, 3};
    _4030Component[11] = {XorGate4, 3};
    _4030Component[12] = {XorGate4, 2};
    _4030Component[13] = {XorGate4, 1};
    _4030Component[14] = {emptySharedPtr, -1};
}

Gate4030::~Gate4030()
{
}

void Gate4030::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin > _pin || pin < 1)
        throw nts::ErrorHandling("Error: Pin doesn't exist");
    if (pin == 7 || pin == 14)
        return;
    if (auto component = _4030Component[pin].first.lock())
        component->setLink(_4030Component[pin].second, other, otherPin);
};

nts::Tristate Gate4030::compute(std::size_t pin)
{
    if (std::find(_input.begin(), _input.end(), pin) != _input.end()) {
        if (auto component = _4030Component[pin].first.lock()) {
            return component->compute(_4030Component[pin].second);
        } else {
            throw nts::ErrorHandling("Error: Component is not valid (input)");
        }
    }
    else if (std::find(_output.begin(), _output.end(), pin) != _output.end()) {
        if (auto component = _4030Component[pin].first.lock()) {
            return component->compute(_4030Component[pin].second);
        } else
            throw nts::ErrorHandling("Error: Component is not valid (output)");
    }
    throw nts::ErrorHandling("Error: Incorrect pin");
};

/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** 4071Gate
*/

#include "Gates/4071Gate.hpp"

Gate4071::Gate4071(std::string name, size_t pin)
{
    _name = name;
    _pin = pin;
    OrGate1 = std::make_shared<OrElem>("Or1", 3);
    OrGate2 = std::make_shared<OrElem>("Or2", 3);
    OrGate3 = std::make_shared<OrElem>("Or3", 3);
    OrGate4 = std::make_shared<OrElem>("Or4", 3);
    std::shared_ptr<nts::IComponent> emptySharedPtr;
    
    _4071Component[1] = {OrGate1, 1};
    _4071Component[2] = {OrGate1, 2};
    _4071Component[3] = {OrGate1, 3};
    _4071Component[4] = {OrGate2, 3};
    _4071Component[5] = {OrGate2, 1};
    _4071Component[6] = {OrGate2, 2};
    _4071Component[7] = {emptySharedPtr, -1};
    _4071Component[8] = {OrGate3, 1};
    _4071Component[9] = {OrGate3, 2};
    _4071Component[10] = {OrGate3, 3};
    _4071Component[11] = {OrGate4, 3};
    _4071Component[12] = {OrGate4, 2};
    _4071Component[13] = {OrGate4, 1};
    _4071Component[14] = {emptySharedPtr, -1};
}

Gate4071::~Gate4071()
{
}

void Gate4071::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin > _pin || pin < 1)
        throw nts::ErrorHandling("Error: Pin doesn't exist");
    if (pin == 7 || pin == 14)
        return;
    if (auto component = _4071Component[pin].first.lock())
        component->setLink(_4071Component[pin].second, other, otherPin);
};

nts::Tristate Gate4071::compute(std::size_t pin)
{
    if (std::find(_input.begin(), _input.end(), pin) != _input.end()) {
        if (auto component = _4071Component[pin].first.lock()) {
            return component->compute(_4071Component[pin].second);
        } else {
            throw nts::ErrorHandling("Error: Component is not valid (input)");
        }
    }
    else if (std::find(_output.begin(), _output.end(), pin) != _output.end()) {
        if (auto component = _4071Component[pin].first.lock()) {
            return component->compute(_4071Component[pin].second);
        } else
            throw nts::ErrorHandling("Error: Component is not valid (output)");
    }
    throw nts::ErrorHandling("Error: Incorrect pin");
};
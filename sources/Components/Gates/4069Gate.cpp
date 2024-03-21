/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** 4069Gate
*/

#include "Gates/4069Gate.hpp"

Gate4069::Gate4069(std::string name, size_t pin)
{
    _name = name;
    _pin = pin;
    NotGate1 = std::make_shared<NotElem>("Not1", 2);
    NotGate2 = std::make_shared<NotElem>("Not2", 2);
    NotGate3 = std::make_shared<NotElem>("Not3", 2);
    NotGate4 = std::make_shared<NotElem>("Not4", 2);
    NotGate5 = std::make_shared<NotElem>("Not5", 2);
    NotGate6 = std::make_shared<NotElem>("Not6", 2);
    std::shared_ptr<nts::IComponent> emptySharedPtr;
    
    _4069Component[1] = {NotGate1, 1};
    _4069Component[2] = {NotGate1, 2};
    _4069Component[3] = {NotGate2, 1};
    _4069Component[4] = {NotGate2, 2};
    _4069Component[5] = {NotGate3, 1};
    _4069Component[6] = {NotGate3, 2};
    _4069Component[7] = {emptySharedPtr, -1};
    _4069Component[8] = {NotGate4, 2};
    _4069Component[9] = {NotGate4, 1};
    _4069Component[10] = {NotGate5, 2};
    _4069Component[11] = {NotGate5, 1};
    _4069Component[12] = {NotGate6, 2};
    _4069Component[13] = {NotGate6, 1};
    _4069Component[14] = {emptySharedPtr, -1};
}

Gate4069::~Gate4069()
{
}

void Gate4069::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin > _pin || pin < 1)
        throw nts::ErrorHandling("Error: Pin doesn't exist");
    if (pin == 7 || pin == 14)
        return;
    if (auto component = _4069Component[pin].first.lock())
        component->setLink(_4069Component[pin].second, other, otherPin);
};

nts::Tristate Gate4069::compute(std::size_t pin)
{
    if (std::find(_input.begin(), _input.end(), pin) != _input.end()) {
        if (auto component = _4069Component[pin].first.lock()) {
            return component->compute(_4069Component[pin].second);
        } else {
            throw nts::ErrorHandling("Error: Component is not valid (input)");
        }
    }
    else if (std::find(_output.begin(), _output.end(), pin) != _output.end()) {
        if (auto component = _4069Component[pin].first.lock()) {
            return component->compute(_4069Component[pin].second);
        } else
            throw nts::ErrorHandling("Error: Component is not valid (output)");
    }
    throw nts::ErrorHandling("Error: Incorrect pin");
};

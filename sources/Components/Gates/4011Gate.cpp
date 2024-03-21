/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** 4011Gate
*/

#include "Gates/4011Gate.hpp"

Gate4011::Gate4011(std::string name, size_t pin)
{
    _name = name;
    _pin = pin;
    AndGate1 = std::make_shared<AndElem>("And1", 3);
    AndGate2 = std::make_shared<AndElem>("And2", 3);
    AndGate3 = std::make_shared<AndElem>("And3", 3);
    AndGate4 = std::make_shared<AndElem>("And4", 3);
    std::shared_ptr<nts::IComponent> emptySharedPtr;
    
    _4011Component[1] = {AndGate1, 1};
    _4011Component[2] = {AndGate1, 2};
    _4011Component[3] = {AndGate1, 3};
    _4011Component[4] = {AndGate2, 3};
    _4011Component[5] = {AndGate2, 1};
    _4011Component[6] = {AndGate2, 2};
    _4011Component[7] = {emptySharedPtr, -1};
    _4011Component[8] = {AndGate3, 1};
    _4011Component[9] = {AndGate3, 2};
    _4011Component[10] = {AndGate3, 3};
    _4011Component[11] = {AndGate4, 3};
    _4011Component[12] = {AndGate4, 2};
    _4011Component[13] = {AndGate4, 1};
    _4011Component[14] = {emptySharedPtr, -1};
}

Gate4011::~Gate4011()
{
}

void Gate4011::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin > _pin || pin < 1)
        throw nts::ErrorHandling("Error: Pin doesn't exist");
    if (pin == 7 || pin == 14)
        return;
    if (auto component = _4011Component[pin].first.lock())
        component->setLink(_4011Component[pin].second, other, otherPin);
};

nts::Tristate Gate4011::compute(std::size_t pin)
{
    if (std::find(_input.begin(), _input.end(), pin) != _input.end()) {
        if (auto component = _4011Component[pin].first.lock()) {
            return component->compute(_4011Component[pin].second);
        } else {
            throw nts::ErrorHandling("Error: Component is not valid (input)");
        }
    }
    else if (std::find(_output.begin(), _output.end(), pin) != _output.end()) {
        if (auto component = _4011Component[pin].first.lock()) {
            nts::Tristate input1 = component->compute(_4011Component[pin].second);
            if (input1 == nts::Tristate::True) {
                return nts::Tristate::False;
            }
            else if (input1 == nts::Tristate::False) {
                return nts::Tristate::True;
            }
            return nts::Tristate::Undefined;
        } else
            throw nts::ErrorHandling("Error: Component is not valid (output)");
    }
    throw nts::ErrorHandling("Error: Incorrect pin");
};

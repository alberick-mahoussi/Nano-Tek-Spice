/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** 4001Gate
*/

#ifndef GATE4001_HPP_
#define GATE4001_HPP_

#include "../AComponents.hpp"
#include "../LogicGates/OrElem.hpp"

class Gate4001 : public nts::AComponent {
    public:
        Gate4001(std::string name, size_t pin);
        ~Gate4001();
        nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
        void debug() override { std::cout << "Im gate 4001 components" << std::endl; };
    protected:
    private:
        size_t _pin;
        std::string _name;
        std::unordered_map<std::size_t, std::pair<std::weak_ptr<nts::IComponent>, std::size_t>> _4001Component;
        std::vector<int> _input = {1, 2, 5, 6, 8, 9, 12, 13};
        std::vector<int> _output = {3, 4, 10, 11};
        std::vector<int> _null = {7, 14};
        std::shared_ptr<nts::IComponent> OrGate1;
        std::shared_ptr<nts::IComponent> OrGate2;
        std::shared_ptr<nts::IComponent> OrGate3;
        std::shared_ptr<nts::IComponent> OrGate4;
};

#endif /* !4001GATE_HPP_ */

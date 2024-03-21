/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** 4069Gate
*/

#ifndef GATE4069_HPP_
#define GATE4069_HPP_

#include "../AComponents.hpp"
#include "../LogicGates/NotElem.hpp"

class Gate4069 : public nts::AComponent {
    public:
        Gate4069(std::string name, size_t pin);
        ~Gate4069();
        nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
        void debug() override{ std::cout << "Im gate 4069 components" << std::endl; };
    protected:
    private:
        size_t _pin;
        std::string _name;
        std::unordered_map<std::size_t, std::pair<std::weak_ptr<nts::IComponent>, std::size_t>> _4069Component;
        std::vector<int> _input = {1, 3, 5, 9, 11, 13};
        std::vector<int> _output = {2, 4, 6, 8, 10, 12};
        std::vector<int> _null = {7, 14};
        std::shared_ptr<nts::IComponent> NotGate1;
        std::shared_ptr<nts::IComponent> NotGate2;
        std::shared_ptr<nts::IComponent> NotGate3;
        std::shared_ptr<nts::IComponent> NotGate4;
        std::shared_ptr<nts::IComponent> NotGate5;
        std::shared_ptr<nts::IComponent> NotGate6;
};

#endif /* !4069GATE_HPP_ */

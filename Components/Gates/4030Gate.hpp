/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** 4030Gate
*/

#ifndef GATE4030_HPP_
#define GATE4030_HPP_

#include "../AComponents.hpp"
#include "../LogicGates/XorElem.hpp"

class Gate4030 : public nts::AComponent {
    public:
        Gate4030(std::string name, size_t pin);
        ~Gate4030();
        nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
        void debug() override{ std::cout << "Im gate 4030 components" << std::endl; };
    protected:
    private:
        size_t _pin;
        std::string _name;
        std::unordered_map<std::size_t, std::pair<std::weak_ptr<nts::IComponent>, std::size_t>> _4030Component;
        std::vector<int> _input = {1, 2, 5, 6, 8, 9, 12, 13};
        std::vector<int> _output = {3, 4, 10, 11};
        std::vector<int> _null = {7, 14};
        std::shared_ptr<nts::IComponent> XorGate1;
        std::shared_ptr<nts::IComponent> XorGate2;
        std::shared_ptr<nts::IComponent> XorGate3;
        std::shared_ptr<nts::IComponent> XorGate4;
};

#endif /* !4030GATE_HPP_ */

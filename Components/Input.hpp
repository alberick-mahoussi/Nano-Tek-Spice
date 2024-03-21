/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "AComponents.hpp"

class Input : public nts::AComponent {
    public:
        Input(std::string name, int pin);
        ~Input();
        nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
        void setState(const std::string &state) override;
        void debug() override { std::cout << "Input" << std::endl; };
        bool isInput() override { return true; };
    protected:
    private:
        int _pin;
        std::string _name;
        nts::Tristate _state;
        bool _used;
};

#endif /* !INPUT_HPP_ */

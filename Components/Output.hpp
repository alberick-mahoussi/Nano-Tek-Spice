/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** Output
*/

#ifndef OUTPUT_HPP_
#define OUTPUT_HPP_

#include "AComponents.hpp"

class Output : public nts::AComponent {
    public:
        Output(std::string name, int pin);
        ~Output();
        nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
        void debug() override { std::cout << "Im Output components" << std::endl; };
        bool isOutput() override { return true; };
    protected:
    private:
        int _pin;
        std::string _name;
        IComponent* test;
};
#endif /* !OUTPUT_HPP_ */

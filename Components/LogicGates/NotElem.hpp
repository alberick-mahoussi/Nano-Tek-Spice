/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** NotElem
*/

#ifndef NOTELEM_HPP_
#define NOTELEM_HPP_

#include "AComponents.hpp"

class NotElem : public nts::AComponent {
    public:
        NotElem(std::string name, size_t pin);
        ~NotElem();
        nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
        void debug() override;
    protected:
    private:
        size_t _pin;
        std::string _name;
        std::unordered_map<std::size_t, std::pair<IComponent*, std::size_t>> _NotComponent;
};

#endif /* !NOTELEM_HPP_ */

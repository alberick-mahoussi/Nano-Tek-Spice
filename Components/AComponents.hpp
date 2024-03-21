/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** AComponents
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponents.hpp"
#include <map>
#include <unordered_map>
#include <memory>
#include "ErrorHandling.hpp"

namespace nts {

    class AComponent : public nts::IComponent {
        public:
            AComponent() {};
            ~AComponent() {};
            void simulate(std::size_t tick) { (void)tick;return; };
            nts::Tristate compute(std::size_t pin) { (void)pin;return nts::Tristate::Undefined; };
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) {
                (void)pin;
                (void)other;
                (void)otherPin;
            };
            virtual void setState(const std::string &) {};
            bool isInput() { return false; };
            bool isOutput() { return false; };
            void debug() { return; };
        protected:
            bool used = nts::Tristate::True;
        private:
    };
}

#endif /* !ACOMPONENT_HPP_ */

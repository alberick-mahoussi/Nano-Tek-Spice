/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** CreateChispet
*/

#include "Nanotekspice.hpp"

std::unique_ptr<nts::IComponent> nts::Nanotekspice::createComponent(const std::string& type, const std::string& value) {
    auto it = builders.find(type);
    if (it != builders.end()) {
        return it->second(value);
    }
    throw nts::ErrorHandling("Unknown component type: " + type);
}
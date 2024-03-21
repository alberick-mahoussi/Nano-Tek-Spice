/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** Nanotekspice
*/

#ifndef NANOTEKSPICE_HPP_
#define NANOTEKSPICE_HPP_

#include "ErrorHandling.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include "IComponents.hpp"
#include "AComponents.hpp"
#include "Gates/4001Gate.hpp"
#include "Gates/4011Gate.hpp"
#include "Gates/4030Gate.hpp"
#include "Gates/4069Gate.hpp"
#include "Gates/4071Gate.hpp"
#include "Gates/4081Gate.hpp"
#include "Gates/2716AdvGate.hpp"
#include "Gates/4008AdvGate.hpp"
#include "Gates/4013AdvGate.hpp"
#include "Gates/4017AdvGate.hpp"
#include "Gates/4040AdvGate.hpp"
#include "Gates/4094AdvGate.hpp"
#include "Gates/4512AdvGate.hpp"
#include "Gates/4514AdvGate.hpp"
#include "Gates/4801AdvGate.hpp"
#include "LogicGates/AndElem.hpp"
#include "LogicGates/OrElem.hpp"
#include "LogicGates/NotElem.hpp"
#include "LogicGates/XorElem.hpp"
#include "ClockElem.hpp"
#include "TrueElem.hpp"
#include "FalseElem.hpp"
#include "Output.hpp"
#include "Input.hpp"

namespace nts {
    class type_v {
        public:
            type_v(){};
            ~type_v(){};
            std::string type;
            std::string value;
    };
    
    class Nanotekspice {
        public:
            Nanotekspice(nts::Parsing *);
            ~Nanotekspice();
            int getExit() { return _exit; };
            void setExit(int exit) { _exit = exit; };
            void prompt(nts::Parsing *ns);
            void addTick() { _tick++; };
            std::unique_ptr<IComponent> createComponent(const std::string&, const std::string&);
            void getCommandPrompt(std::string str, nts::Parsing *ns);
            void displayNano(nts::Parsing *ns);
            std::vector<type_v> _inputValue;
        private:
            int _exit = 0;
            std::string _str;
            using ComponentBuilder = std::function<std::unique_ptr<nts::IComponent>(const std::string&)>;
            std::map<std::string, ComponentBuilder> builders = {
                {"input", [](const std::string& value){ return std::make_unique<Input>(value, 1); }},
                {"output", [](const std::string& value){ return std::make_unique<Output>(value, 1); }},
                {"clock", [](const std::string& value){ return std::make_unique<ClockElem>(value, 1); }},
                {"true", [](const std::string& value){ return std::make_unique<TrueElem>(value, 1); }},
                {"false", [](const std::string& value){ return std::make_unique<FalseElem>(value, 1); }},
                {"and", [](const std::string& value) { return std::make_unique<AndElem>(value, 3); }},
                {"or", [](const std::string& value) { return std::make_unique<OrElem>(value, 3); }},
                {"xor", [](const std::string& value) { return std::make_unique<XorElem>(value, 3); }},
                {"not", [](const std::string& value) { return std::make_unique<NotElem>(value, 2); }},
                {"4001", [](const std::string& value) { return std::make_unique<Gate4001>(value, 14); }},
                {"4011", [](const std::string& value) { return std::make_unique<Gate4001>(value, 14); }},
                {"4030", [](const std::string& value) { return std::make_unique<Gate4001>(value, 14); }},
                {"4069", [](const std::string& value) { return std::make_unique<Gate4001>(value, 14); }},
                {"4071", [](const std::string& value) { return std::make_unique<Gate4001>(value, 14); }},
                {"4081", [](const std::string& value) { return std::make_unique<Gate4001>(value, 14); }},
                // {"2716", [](const std::string& value) { return std::make_unique<Gate4001>(value, 1); }},
                // {"4008", [](const std::string& value) { return std::make_unique<Gate4001>(value, 1); }},
                // {"4013", [](const std::string& value) { return std::make_unique<Gate4001>(value, 1); }},
                // {"4017", [](const std::string& value) { return std::make_unique<Gate4001>(value, 1); }},
                // {"4040", [](const std::string& value) { return std::make_unique<Gate4001>(value, 1); }},
                // {"4094", [](const std::string& value) { return std::make_unique<Gate4001>(value, 1); }},
                // {"4512", [](const std::string& value) { return std::make_unique<Gate4001>(value, 1); }},
                // {"4514", [](const std::string& value) { return std::make_unique<Gate4001>(value, 1); }},
                // {"4801", [](const std::string& value) { return std::make_unique<Gate4001>(value, 1); }},
            };
            std::map<std::string, std::unique_ptr<nts::IComponent>> _CircuitComponents;

            int _tick;
    };
}

#endif /* !NANOTEKSPICE_HPP_ */
